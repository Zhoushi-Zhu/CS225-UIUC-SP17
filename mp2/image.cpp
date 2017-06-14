#include "image.h"

void Image::flipleft(){

  size_t width = this->width();
  size_t height = this->height();  

  RGBAPixel* temp = new RGBAPixel;
  RGBAPixel* tempR;
  RGBAPixel* tempL;
  
  for (size_t yi = 0; yi < height; yi++){
    for(size_t xi = 0; xi < width/2; xi++){
      // int r,g,b;
      
      //   r = (*this)(xi,yi)->red;
      //   (*this)(xi,yi)->red = (*this)(width-xi-1,yi)->red;
      //  (*this)(width-xi-1,yi)->red = r; 
      
      
      tempL = this->operator()(xi,yi);
      tempR = this->operator()(width-xi-1,yi);

      *temp = *tempL;
      *tempL = *tempR;
      *tempR = *temp;
    }
  }

  delete temp;
}

void Image::adjustbrightness(int r, int g, int b){

  size_t width = this->width();
  size_t height = this->height();  

  for (size_t yi = 0; yi < height; yi++){
    for(size_t xi = 0; xi < width; xi++){
      RGBAPixel* temp = this->operator()(xi,yi);

      if (temp->red + r > 255)
	temp->red = 255;
      else if (temp->red + r < 0)
	temp->red = 0;
      else 
	temp->red = temp->red + r;

      if (temp->green + g > 255)
	temp->green = 255;
      else if (temp->green + g < 0)
	temp->green = 0;
      else 
	temp->green = temp->green + g;
      
      if (temp->blue + b > 255)
	temp->blue = 255;
      else if (temp->blue + b < 0)
	temp->blue = 0;
      else 
	temp->blue = temp->blue + b;
    }
  }
}

void Image::invertcolors(){

  size_t width = this->width();
  size_t height = this->height();  
  
  for (size_t yi = 0; yi < height; yi++){
    for(size_t xi = 0; xi < width; xi++){
      RGBAPixel* temp = this->operator()(xi,yi);
      
     
      temp->red = 255 - temp->red;

     
	temp->green = 255 - temp->green;
      
     
	temp->blue = 255 - temp->blue;
    }
 }
}







