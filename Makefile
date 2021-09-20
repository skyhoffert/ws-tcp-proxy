# QTPATH is the path to your highest Qt folder for Native compilation.
QTPATH=/home/sky/Qt5.6.2/5.6/gcc_64/

LDLIBS=-lpthread
CPPFLAGS=-fPIC -std=c++11 -Wall -Iinclude

BINDIR=bin/
INCDIR=include/
OBJDIR=obj/
SRCDIR=src/
TESTDIR=tests/

CPP=g++

# Here, all targets are listed.
TARGETS=\
	$(OBJDIR)ws_listener.o \
	$(OBJDIR)tcp_listener.o \
	$(OBJDIR)wstcpproxy.o
TESTS=\
	$(BINDIR)basic_test.test

all: $(BINDIR)wstcpproxy

tests: $(TESTS)

clean:
	$(info Cleaning.)
	rm -rf $(OBJDIR)*.o
	rm -rf $(BINDIR)*.test
	rm -f  $(BINDIR)wstcpproxy

###############################################################################
# Main program is defined below.
###############################################################################

$(BINDIR)wstcpproxy: $(INCDIR)constants.hpp $(TARGETS)
	$(info Building wstcpproxy.)
	$(CPP) $(CPPFLAGS) -o $(BINDIR)wstcpproxy \
		$(OBJDIR)wstcpproxy.o \
		$(OBJDIR)ws_listener.o \
		$(OBJDIR)tcp_listener.o

###############################################################################
# Object recipes are defined below.
###############################################################################

$(OBJDIR)wstcpproxy.o: $(SRCDIR)wstcpproxy.cpp
	$(info Building wstcpproxy obj.)
	$(CPP) $(CPPFLAGS) -o $(OBJDIR)wstcpproxy.o -c \
		$(SRCDIR)wstcpproxy.cpp

$(OBJDIR)ws_listener.o: \
		$(SRCDIR)ws_listener.cpp \
		$(INCDIR)ws_listener.hpp
	$(info Building ws_listener.)
	$(CPP) $(CPPFLAGS) -o $(OBJDIR)ws_listener.o -c \
		$(SRCDIR)ws_listener.cpp \

$(OBJDIR)tcp_listener.o: \
		$(SRCDIR)tcp_listener.cpp \
		$(INCDIR)tcp_listener.hpp
	$(info Building tcp_listener.)
	$(CPP) $(CPPFLAGS) -o $(OBJDIR)tcp_listener.o -c \
		$(SRCDIR)tcp_listener.cpp \

###############################################################################
# Test recipes are defined below.
###############################################################################

$(BINDIR)basic_test.test:
	$(info Building basic_test test.)
	$(CPP) $(CPPFLAGS) -o $(BINDIR)basic_test.test \
		$(TESTDIR)basic_test.test.cpp \
