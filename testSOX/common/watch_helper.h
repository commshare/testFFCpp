#ifndef _WATCH_HELPER_H_FXW_
#define _WATCH_HELPER_H_FXW_
#define MAX_WATCHER_SIZE 200

#include <cassert>

template <class T, class W, int WS=MAX_WATCHER_SIZE> class WatchHelper: public virtual T
{
public:
	typedef W watcher_t;
	WatchHelper(){
		for(int i = 0; i < WS; ++i)
		{
			watchers[i] = NULL;
		}
	}

	virtual void watch(watcher_t *w)
	{
		if(!findInArray(w)){
			for(int i = 0; i < WS; ++i)
			{
				if(watchers[i] == NULL)
				{
					watchers[i] = w;
					return;
				}
			}
			assert(false);
		}

	}

	virtual void revoke(watcher_t *w)
	{
		for(int i = 0; i < WS; ++i)
		{
			if(watchers[i] == w){
				watchers[i] = NULL;
			}
		}
	}

	void clearWatcher()
	{
		for(int i = 0; i < WS; ++i){
			watchers[i] = NULL;
		}
	}

	template<typename U> void forEachWatcher1(void (W::*fun)(U), U param){
		for(int i = 0; i < WS; ++i){
			if(watchers[i] != NULL)
				(watchers[i]->*fun)(param);
		}
	}

	template<typename U, typename V, typename Y> void forEachWatcher3(void (W::*fun)(U, V, Y), U param, V p2, Y p3){
		for(int i = 0; i < WS; ++i){
			if(watchers[i] != NULL)
				(watchers[i]->*fun)(param, p2, p3);
		}
	}

	template<typename U, typename V> void forEachWatcher2(void (W::*fun)(U, V), U param, V p2){
		for(int i = 0; i < WS; ++i){
			if(watchers[i] != NULL)
				(watchers[i]->*fun)(param, p2);
		}
	}

	template<typename U> void forEachWatcherRef1(void (W::*fun)(const U&), const U& param){
		for(int i = 0; i < WS; ++i){
			if(watchers[i] != NULL)
				(watchers[i]->*fun)(param);
		}
	}

	template<typename U, typename V> void forEachWatcherRef1V2(void (W::*fun)(const U&, V), const U& param, V p2){
		for(int i = 0; i < WS; ++i){
			if(watchers[i] != NULL)
				(watchers[i]->*fun)(param, p2);
		}
	}

	template<typename T1, typename T2> void forEachWatcherRef2(void (W::*fun)(const T1&, const T2& ), const T1& p1, const T2& p2)
	{
		for(int i = 0; i < WS; ++i){
			if(watchers[i] != NULL)
				(watchers[i]->*fun)(p1, p2);
		}
	}

	template<typename T1, typename T2, typename T3> void forEachWatcherRef3(void (W::*fun)(const T1&, const T2& ,const T3&), const T1& p1, const T2& p2, const T3& p3){
		for(int i = 0; i < WS; ++i){
			if(watchers[i] != NULL)
				(watchers[i]->*fun)(p1, p2, p3);
		}
	}

	template<typename T1, typename T2, typename T3, typename T4> 
	void forEachWatcherRef4(void (W::*fun)(const T1&, const T2& ,const T3&, const T4&), const T1& p1, const T2& p2, const T3& p3, const T4& p4)
	{
		for(int i = 0; i < WS; ++i){
			if(watchers[i] != NULL)
				(watchers[i]->*fun)(p1, p2, p3, p4);
		}
	}

	template<typename T1, typename T2, typename T3, typename T4, typename T5> 
		void forEachWatcherRef5(void (W::*fun)(const T1&, const T2& ,const T3&, const T4&, const T5&), const T1& p1, const T2& p2, const T3& p3, const T4& p4, const T5& p5)
	{
		for(int i = 0; i < WS; ++i){
			if(watchers[i] != NULL)
				(watchers[i]->*fun)(p1, p2, p3, p4, p5);
		}
	}

	template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6> 
		void forEachWatcherRef6(void (W::*fun)(const T1&, const T2& ,const T3&, const T4&, const T5&, const T6&), const T1& p1, const T2& p2, const T3& p3, const T4& p4, const T5& p5, const T6& p6)
	{
		for(int i = 0; i < WS; ++i){
			if(watchers[i] != NULL)
				(watchers[i]->*fun)(p1, p2, p3, p4, p5, p6);
		}
	}

	template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7> 
		void forEachWatcherRef7(void (W::*fun)(const T1&, const T2& ,const T3&, const T4&, const T5&, const T6&, const T7&), const T1& p1, const T2& p2, const T3& p3, const T4& p4, const T5& p5, const T6& p6, const T7& p7)
	{
		for(int i = 0; i < WS; ++i){
			if(watchers[i] != NULL)
				(watchers[i]->*fun)(p1, p2, p3, p4, p5, p6, p7);
		}
	}

	void forEachWatcher0(void (W::*fun)(void)){
		for(int i = 0; i < WS; ++i){
			if(watchers[i] != NULL)
				(watchers[i]->*fun)();
		}
	}
protected:
	watcher_t* watchers[WS];
private:
	bool findInArray(watcher_t *w){
		for(int i = 0; i < WS; ++i){
			if(watchers[i] == w)
				return true;
		}
		return false;
	}
};
#endif
