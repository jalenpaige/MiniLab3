COMP=g++
FLAGS = -Wall -g

#output: main.cpp Network.cpp User.cpp
#	$(COMP) $(FLAGS) main.cpp Network.cpp User.cpp -o output

output: main.o Network.o User.o
	$(COMP) $(FLAGS) main.o Network.o User.o -o output

#(I used a copy of my HW2 File for this lab.)
#main.o: main.cpp
#	g++ -c main.cpp -o main.o

#Network.o: Network.cpp
#	g++ -c Network.cpp -o Network.o

#User.o: User.cpp
#	g++ -c User.cpp -o User.o

%.o : %.cpp
	$(COMP) $(FLAGS) -c $<  -o $@

clean:
	rm *.o output
