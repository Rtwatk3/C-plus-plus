CXX = g++
CXXFLAGS = -Wall

proj4: War.o Horse.o Warhorse.o Heavy.o Light.o Medium.o Untrained.o driver.cpp
	$(CXX) $(CXXFLAGS) Horse.o Warhorse.o Heavy.o Light.o Medium.o Untrained.o War.o driver.cpp -o proj4

War.o: Warhorse.o Horse.o Heavy.o Light.o Medium.o Untrained.o War.cpp War.h
	$(CXX) $(CXXFLAGS) -c War.cpp

Heavy.o: Warhorse.o Horse.o Heavy.cpp Heavy.h
	$(CXX) $(CXXFLAGS) -c Heavy.cpp

Light.o: Warhorse.o Horse.o Light.cpp Light.h
	$(CXX) $(CXXFLAGS) -c Light.cpp

Medium.o: Warhorse.o Horse.o Medium.cpp Medium.h
	$(CXX) $(CXXFLAGS) -c Medium.cpp

Warhorse.o: Horse.o Warhorse.cpp Warhorse.h
	$(CXX) $(CXXFLAGS) -c Warhorse.cpp

Untrained.o: Horse.o Untrained.cpp Untrained.h
	$(CXX) $(CXXFLAGS) -c Untrained.cpp

Horse.o: Horse.cpp Horse.h
	$(CXX) $(CXXFLAGS) -c Horse.cpp

clean:
	rm *.o*
	rm *~ 

run:
	./proj4 proj4_data.txt
val:
	valgrind ./proj4 proj4_data.txt