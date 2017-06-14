#include "png.h"
#include "rgbapixel.h"

#include <iostream>


using namespace std;

int main(){

  PNG input = PNG("in.png");
  
  size_t width = input.width();
  size_t height = input.height();
   
  PNG output = PNG(width, height);
  
  for (size_t yi = 0; yi < height; yi++) {
    for (size_t xi = 0; xi < width; xi++) {
      output(width-xi-1,height-yi-1)->red = input(xi,yi)->red;
      output(width-xi-1,height-yi-1)->blue = input(xi,yi)->blue;
      output(width-xi-1,height-yi-1)->green = input(xi,yi)->green;
      output(width-xi-1,height-yi-1)->alpha = input(xi,yi)->alpha;
    }
  }

  output.writeToFile("out.png");
  
  return 0;
}

