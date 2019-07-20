CONSERVATIVE_FLAGS = -std=c++11 -Wall -Wextra 
DEBUGGING_FLAGS = -g -O0
CFLAGS = $(CONSERVATIVE_FLAGS) $(DEBUGGING_FLAGS)

branch: branch.o
	g++ -o branch branch.o

branch.o: branch.cpp
	g++ -c branch.cpp $(CFLAGS)

.PHONY: clean
clean:
	rm -f *.o branch
