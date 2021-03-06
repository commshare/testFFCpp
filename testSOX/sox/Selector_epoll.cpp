#include "Selector_epoll.h"
#include "snox.h"
#include <sys/epoll.h>
//#include "measure.h"

#define EPOLL_SIZE 100
static int pipe_err = 0;
using namespace sox;

static void epoll_timer_click(int) {
	if (sox::env::selector()) {
		sox::env::selector()->increase_elapsed(Countdown::TIME_CLICK);
	}
}

static void epoll_pipe_handler(int){
	pipe_err++;
}

Selector_epoll::Selector_epoll() :
	epfd(-1) {
	struct itimerval timer;

	timer.it_interval.tv_sec = Countdown::TIME_CLICK / 1000;
	timer.it_interval.tv_usec = (Countdown::TIME_CLICK % 1000) * 1000;

	timer.it_value = timer.it_interval;

	if(signal(SIGPIPE, epoll_pipe_handler) == SIG_ERR){
		throw exception_errno("signal");
	}
	if (signal(SIGALRM, epoll_timer_click) == SIG_ERR)
		throw exception_errno("signal");
	if (-1 == setitimer(ITIMER_REAL, &timer, NULL))
		throw exception_errno("setitimer");

	epfd = epoll_create(65535);
	if (-1 == epfd) {
		throw exception_errno("epoll");
	}

}

Selector_epoll::~Selector_epoll() {
	if (-1 != epfd)
		close(epfd);
}

inline void setupEpoll(int efd, int op, int sfd, epoll_event &ev) {
	int ret = epoll_ctl(efd, op, sfd, &ev);
	if (ret != 0) {
		switch (errno) {
		case EBADF:
			log(Info, "epfd or fd is not a valid file descriptor.");
			return;
		case EEXIST:
			log(Info,
					"was EPOLL_CTL_ADD, and the supplied file descriptor fd is already in epfd.");
			return;
		case EINVAL:
			log(
					Info,
					"epfd is not an epoll file descriptor, or fd is the same as epfd, or the requested operation op is not supported by this interface.");
			return;
		case ENOENT:
			log(Info,
					"op was EPOLL_CTL_MOD or EPOLL_CTL_DEL, and fd is not in epfd. ");
			return;
		case ENOMEM:
			log(Info,
					"There was insufficient memory to handle the requested op control operation.");
			return;
		case EPERM:
			log(Info, "The target file fd does not support epoll.");
			return;
		}
	}
}

void Selector_epoll::select(Socket * s, int remove, int add) {
	//sox::log(Debug, "select begin");
	epoll_event ev;
	ev.data.ptr = s;
	ev.events = EPOLLIN;

	std::pair<sockSet_t::iterator, bool> p = sockets.insert(s);
	if (p.second) {
		if (SEL_WRITE & add) {
			ev.events |= EPOLLOUT;
		}
		//sox::log(Debug, "epoll select add event:", s->socket().getsocket());
		setupEpoll(epfd, EPOLL_CTL_ADD, s->socket().getsocket(), ev);
	} else {
		unsigned int currstate=(s->socket().m_sock_flags.selevent & ~remove) | add;
		ev.events=0;
		if (currstate & SEL_READ)  ev.events |= EPOLLIN;
		if (currstate & SEL_WRITE) ev.events |= EPOLLOUT;
		setupEpoll(epfd, EPOLL_CTL_MOD, s->socket().getsocket(), ev);
	}
	//sox::log(Debug, "select end, events is:", ev.events);
}

void Selector_epoll::mainloop() {
	epoll_event events[EPOLL_SIZE];

	time_t oldtime = sox::env::now;
	int ptimes = pipe_err;
	while (isRunning()) {
		// at least can receive all error
		//	sox::log(Debug, "epoll loop 1");
        int waits;
        
        {
            //scoped_measure m(0, 0, 0);
            waits = epoll_wait(epfd, events, EPOLL_SIZE, 500);
        }
//		sox::log(Debug, "epoll loop 2 wait:", waits);
		sox::env::now = time(NULL);
		if(oldtime != sox::env::now){
			//stores the string in a user-supplied buffer which should have room for at least 26 bytes
			char buf[30];
			char *st = ctime_r(&sox::env::now, buf);
			sox::env::strTime = std::string(st, strlen(st) - 1);
		}

#ifndef WIN32
		struct tm tmNow;
                localtime_r(&sox::env::now, &tmNow);

//		struct tm *t = localtime(&sox::env::now);
		uint32_t stamp = tmNow.tm_hour*60*60 + tmNow.tm_min*60 + tmNow.tm_sec;

		struct timeval stv;
		struct timezone stz;
		gettimeofday(&stv,&stz);
		sox::env::haomiao= stamp * 1000 + stv.tv_usec/1000;
#endif
		
		if(ptimes != pipe_err){
			ptimes = pipe_err;
			log(Error, "broken pipe times:%u", pipe_err);
		}

		if (waits < 0) {
			if (EINTR == errno) {
				//do nothing 
			} else {
				log(Info, "epoll error wait:%u str:%s errno:%u str:%s", waits, strerror(waits), errno, strerror(errno));
				//throw exception_errno("epoll");
			}
		}

		if (waits == EPOLL_SIZE) {
			log(Warn, "epoll reach the max size:%d", 100);
		}

		for (int i = 0; i < waits; ++i) {
			//sox::log(Debug, "event is:", events[i].events);
			Socket *sk = (Socket *)events[i].data.ptr;
			if (events[i].events & (EPOLLIN|EPOLLERR|EPOLLHUP)) {
				notify_event(sk, SEL_READ);
			}
			if (events[i].events & EPOLLOUT) {
				notify_event(sk, SEL_WRITE);
			}
		}
		check_timout_run(); // check timeout
		interrupt();
		clearRemoved();
	}
}

void Selector_epoll::remove(Socket * s) {
	//sox::log(Debug, "epoll remove begin socket:", int(s), " fd", s->socket().getsocket());
	epoll_event ev;
	setupEpoll(epfd, EPOLL_CTL_DEL, s->socket().getsocket(), ev);
	sockets.erase(s);
	//sox::log(Debug, "remove end");
}
