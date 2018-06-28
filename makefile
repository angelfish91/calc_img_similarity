SHELL=/bin/bash
CC=gcc
CXX=g++
AR=ar
COPY=cp
MAKE=make
TAR=tar

RED= \\e[1m\\e[31m
GREEN= \\e[1m\\e[32m
GRESET= ;echo -ne \\e[m; test -s $@
RESET = \\e[m

CFLAGS= --std c++11 -O3 -w -g 
LDFLAGS= -lopencv_core -lopencv_imgproc -lboost_system -lopencv_highgui


all:do_detect_sim
do_detect_sim:do_detect_sim.o gen_img_fingerprint.o
	@echo -e Compiling $(GREEN) do_detect_sim $(RESET)
	$(CXX) -o $@ $^  $(CFLAGS) $(LDFLAGS)
	rm ./*.o

do_detect_sim.o:do_detect_sim.cpp
	@echo -e Compiling $(GREEN) do_detect_sim.o $(RESET)
	$(CXX) -c -o $@ $<  $(CFLAGS) $(LDFLAGS)

gen_img_fingerprint.o:gen_img_fingerprint.cpp gen_img_fingerprint.h
	@echo -e Compiling $(GREEN) gen_img_fingerprint.o $(RESET)
	$(CXX) -c -o $@ $<  $(CFLAGS) $(LDFLAGS)

.PHONY: clean
	rm ./*.o
	rm ./do_detect_sim

