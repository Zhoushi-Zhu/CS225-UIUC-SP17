CXX = clang++
LD = clang++
CXXFLAGS = -std=c++1y -stdlib=libc++ -c -g -O0 -Wall
LDFLAGS = -std=c++1y -stdlib=libc++ -lpng -lc++abi -lpthread

all : testimage testscene

testscene :testscene.o scene.o image.o rgbapixel.o png.o
	$(LD) image.o png.o rgbapixel.o testscene.o scene.o $(LDFLAGS) -o testscene

testimage : image.o png.o rgbapixel.o testimage.o
	$(LD) image.o png.o rgbapixel.o testimage.o $(LDFLAGS) -o testimage

testscene.o : testscene.cpp scene.h image.h png.h rgbapixel.h
	$(CXX) $(CXXFLAGS) testscene.cpp 

testimage.o : testimage.cpp image.h png.h rgbapixel.h 
	$(CXX) $(CXXFLAGS) testimage.cpp  

scene.o : scene.cpp scene.h image.h rgbapixel.h png.h
	$(CXX) $(CXXFLAGS) scene.cpp	

image.o : image.cpp image.h rgbapixel.h png.h
	$(CXX) $(CXXFLAGS) image.cpp

png.o : png.cpp png.h rgbapixel.h
	$(CXX) $(CXXFLAGS) png.cpp

rgbapixel.o : rgbapixel.cpp rgbapixel.h
	$(CXX) $(CXXFLAGS) rgbapixel.cpp

clean : 
	-rm -f *.o testimage testscene
