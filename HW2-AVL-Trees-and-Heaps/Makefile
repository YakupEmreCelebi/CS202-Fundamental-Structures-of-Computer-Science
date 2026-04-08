# /**
#  * Title: AVL Trees and Heaps
#  * Author: Yakup Emre Celebi
#  * ID: 22302267
#  * Section: 2
#  * Homework: 2
#  * Description: Makefile for compiling scheduler and monitor
#  */

all: scheduler monitor

scheduler: Scheduler.cpp
	g++ -std=c++11 -O2 Scheduler.cpp -o scheduler

monitor: Monitor.cpp
	g++ -std=c++11 -O2 Monitor.cpp -o monitor

clean:
	rm -f scheduler monitor