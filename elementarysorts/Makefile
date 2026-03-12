CXX := g++
CXXFLAGS := -std=c++23
LDLIBS := -lCatch2
LINK.o := $(CXX)

.PHONY: all clean handin

driver:

driver.cpp: sort.hpp

handin : handin.tar

handin.tar : driver.cpp sort.hpp
	tar cvf $@ $^

all : driver handin

clean :
	rm -f driver driver.o handin.tar
