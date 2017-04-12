
DEFINE_SEL=-DHAVE_EPOLL
DEF_NO_SEND_BLOCKED_LOG=-DNO_SEND_BLOCKED_LOG

CC = gcc
CXX32 = g++
CC32 = gcc

ARRU = ar -ru

#MYSQL_INC = /home/mysql/include/mysql
#MYSQL_LIB_R = /home/mysql/lib/mysql/libmysqlclient_r.a -lmd -lz


CXXFLAG = -Wall -ggdb -D_REENTRANT $(DEFINE_SEL) 
CXXFLAG_R = -Wall -O2 -O3 -D_REENTRANT $(DEFINE_SEL)

#INCLUDE = -I../../ -I../../common  
INCLUDE = -I./ -I../ -I../common/
#	vim: ft=make
