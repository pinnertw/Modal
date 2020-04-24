CXX = g++
CXXFLAGS = --std=c++11

sources = preambule.cpp Q1_naif.cpp Q2_naif.cpp
headers = $(patsubst %.cpp,%.hpp,$(sources))
objects = $(patsubst %.cpp,%.o,$(sources))

preambule.o: preambule.cpp
Q1_naif.o:	Q1_naif.cpp preambule.o
Q2_naif.o:	Q2_naif.cpp preambule.o

simulation: Modal.cpp Q1_naif.o Q2_naif.o preambule.o
	$(CXX) $(CXXFLAGS) -o $@ Modal.cpp Q1_naif.o Q2_naif.o preambule.o

clean-objects:
	rm -vf *.o

clean-programs:
	rm -vf simulation

clean: clean-objects clean-programs
	rm -vf *~
