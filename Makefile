CXX=clang
FLAGS= -std=c++11 -g \
       -pedantic -Wall -Wextra -Wold-style-cast -Woverloaded-virtual \
       -Wfloat-equal -Wpointer-arith -Wcast-align -Wconversion -Wshadow \
       -Wswitch-default -Wundef -Winline

all: tests

test/obj/test_string.o: test/test_string.cpp src/property.hpp
	$(CXX) $(FLAGS) -c test/test_string.cpp -o test/obj/test_string.o

test/obj/test_int.o: test/test_int.cpp src/property.hpp
	$(CXX) $(FLAGS) -c test/test_int.cpp -o test/obj/test_int.o

test/obj/main.o: test/main.cpp
	$(CXX) $(FLAGS) -c test/main.cpp -o test/obj/main.o

test/tests: test/obj/main.o test/obj/test_int.o test/obj/test_string.o
	$(CXX) test/obj/main.o \
	       test/obj/test_int.o test/obj/test_string.o \
	      -lboost_unit_test_framework -g -o test/tests

tests: test/tests

run_tests:
	./test/tests
	./run_fail_test.pl

clean:
	rm -f test/obj/*
	rm -f obj/*
	rm -f *.o
