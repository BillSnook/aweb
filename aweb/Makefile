# Makefile for mtrctl project - control a motorized robot remotely, control an Arduino via I2C

CXX = g++

CXXFLAGS = -std=c++11 -DDEBUG
LDLIBS = -lpthread
# If on Raspberry Pi (as opposed to being developed on a Mac), uncomment these two lines:
#CXXFLAGS += -DON_PI
#LDLIBS += -lwiringPi

HEADERS = mtrctl.hpp signals.hpp threader.hpp commands.hpp listen.hpp sender.hpp minion.hpp # hardware.hpp speed.hpp filer.hpp
OBJECTS = mtrctl.o signals.o threader.o commands.o listen.o sender.o minion.o # hardware.o speed.o filer.o

default: mtrctl

mtrctl: $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ $(LDLIBS) -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(OBJECTS): $(HEADERS)

clean:
	-rm -f $(OBJECTS)
	-rm -f mtrctl
