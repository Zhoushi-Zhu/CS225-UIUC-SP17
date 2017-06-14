#using clang 

CXX = clang++
LD = clang++
CXXFLAGS = -std=c++1y -stdlib=libc++ -c -g -O0 -Wall -Wextra -Werror -pedantic 
LDFLAGS = -std=c++1y -stdlib=libc++ -lpng -lc++abi -lpthread
EXECUTABLE = mp1
OBJ =  main.o png.o rgbapixel.o
HEADER = png.h rgbapixel.h

all : $(EXECUTABLE)

$(EXECUTABLE) : $(OBJ)
	$(LD) $(OBJ) $(LDFLAGS) -o $(EXECUTABLE)

main.o : main.cpp $(HEADER)
	$(CXX) $(CXXFLAGS) main.cpp

png.o : png.cpp $(HEADER)
	$(CXX) $(CXXFLAGS) png.cpp

rgbapixel.o : rgbapixel.cpp rgbapixel.h
	$(CXX) $(CXXFLAGS) rgbapixel.cpp

clean : 
	-rm -f *.o $(EXECUTABLE)
