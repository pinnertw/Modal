CXX = g++
CXXFLAGS = --std=c++11

sources = preambule.cpp Q1.cpp Q2.cpp
headers = $(patsubst %.cpp,%.hpp,$(sources))
objects = $(patsubst %.cpp,%.o,$(sources))

preambule.o: preambule.cpp
Q1.o:	Q1.cpp preambule.o
Q2.o:	Q2.cpp preambule.o

simulation: Modal.cpp Q1.o Q2.o preambule.o
	$(CXX) $(CXXFLAGS) -o $@ Modal.cpp Q1.o Q2.o preambule.o

clean-objects:
	rm -vf *.o

clean-programs:
	rm -vf simulation

clean: clean-objects clean-programs
	rm -vf *~
