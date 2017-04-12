
include ../Makefile.inc

SRC_COMM = helper.cpp helperhex.cpp helperb64.cpp property.cpp logger.cpp \
		   exception_errno.cpp sockethelper.cpp \
		   countdown.cpp hostsox.cpp \
		   snox.cpp tcpsock.cpp selector.cpp \
		   selector_lazy.cpp selector_poll.cpp selector_sel.cpp \
		   Selector_epoll.cpp \
		   mutex.cpp \
		   syslog-nb.cpp logger_nb.cpp measure.cpp
		   #selector_kq.cpp \

# -------------------------------------------------------------------------

#CXXFLAG_R = -Wall -O2 -O3 -D_REENTRANT $(INCLUDE) $(DEFINE_SEL) 

OBJ_COMM  = $(SRC_COMM:.cpp=.o)
OBJ_COMM_R  = $(SRC_COMM:.cpp=.ro)

.SUFFIXES: .o .cpp
.cpp.o:
	$(CXX) $(CXXFLAG) ${INCLUDE} -c -o $@ $<


.SUFFIXES: .ro .cpp
.cpp.ro:
	$(CXX32) $(CXXFLAG_R) ${INCLUDE} -c -o $@ $<

all: sox.a #sox.ra

release: sox.ra

sox.a: $(OBJ_COMM) | ../lib
	$(ARRU) ../lib/sox.a $(OBJ_COMM)
	$(ARRU) ../lib/libsox.a $(OBJ_COMM)
#	ranlib sox.a

../lib:
	mkdir ../lib
  
sox.ra: $(OBJ_COMM_R)
	$(ARRU) ../lib/sox.ra $(OBJ_COMM_R)
#	ranlib sox.ra

test: sox.a test.cpp
	$(CXX) $(CXXFLAG) -o test test.cpp sox.a

depend:
	mkdep $(CXXFLAG) $(SRC_COMM)

install:

clean: 
	rm -f *.o
	rm -f *.ro
	rm -f ../lib/sox.a

