EXE = output
OBJS = temp.o

COMPILER = g++ -std=c++11
COMPILER_FLAGS = -c -g -O0 -Wall -Werror
LINKER = g++

all : $(EXE)

$(EXE) : $(OBJS)
	$(LINKER) $(OBJS) -o $(EXE)

main.o : main.cpp 
	$(COMPILER) $(COMPILER_FLAGS) main.cpp

clean :
	-rm -f *.o $(EXE)

