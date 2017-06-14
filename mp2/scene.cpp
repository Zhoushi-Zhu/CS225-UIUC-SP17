#include "scene.h"

using namespace std;

Scene::Scene(int max){

  if(max<0)
    maxImage = 0;

  maxImage = max;
  I = new Image*[max];
  xi = new int[max];
  yi = new int[max];
  
  for(int i = 0; i < max; i++){
    I[i] = NULL;
    xi[i] = 0;
    yi[i] = 0;
  }

  
}

Scene::~Scene(){
  clear();
}

void Scene::clear(){
 for(int i = 0; i < maxImage; i++){
    delete I[i];
    I[i] = NULL;
  }

 delete []I;
 delete []xi;
 delete []yi;
 I = NULL;
 xi = NULL;
 yi = NULL;
}


Scene::Scene(const Scene &source){
  copy(source);
}  

void Scene::copy(const Scene & source){

  maxImage = source.maxImage;
  xi = new int[maxImage];
  yi = new int[maxImage];
  I = new Image*[maxImage];
  
  for(int i = 0; i < maxImage; i++){
    if(source.I[i] != NULL){
      xi[i] = source.xi[i];
      yi[i] = source.yi[i];
      I[i] = new Image;
      *I[i] = *(source.I[i]);
    }
    else{
      xi[i] = 0;
      yi[i] = 0;
      I[i] = NULL;
    }
  }
  
}


const Scene & Scene::operator =(const Scene &source){
  if (this != &source)
    {
      clear();
      copy(source);
    }

  return *this;
}

void Scene::changemaxlayers(int newmax){
  if (newmax < maxImage)
    {
      for(int i = newmax - 1; i < maxImage; i++)
	{
	  if ( I[i] != NULL);
	  {
	    cout << "invalid newmax" << endl;
	    return;
	  }
	}
    }


  if (newmax == maxImage)
    return;
 
    
    int * newx = new int[newmax];
    int * newy = new int[newmax];
    Image ** newI = new Image*[newmax];
    
    if (newmax > maxImage){
      for(int i = 0; i < maxImage; i++){
	newx[i] = xi[i];
	newy[i] = yi[i];
	
	if (I[i] != NULL)
	  newI[i] = new Image(*I[i]);
	else
	  newI[i] = NULL;
      }
      
      for(int i = maxImage; i < newmax; i++)
	newI[i] = NULL;           
    }
    else{
      for(int i = 0; i < newmax; i++){
	newx[i] = xi[i];
	newy[i] = yi[i];
	
	if (I[i] != NULL)
	  newI[i] = new Image(*I[i]);
	else
	  newI[i] = NULL;
      }
    }     
 
    clear();
    
    maxImage = newmax;
    xi = newx;
    yi = newy;
    I = newI;
    
    

}  
void Scene::addpicture(const char *FileName, int index, int x, int y){
  if (index < 0 || index > maxImage-1 )
    {
      cout<<"index out of bounds"<<endl;
      return;
    }


  string file(FileName);
  Image * temp = new Image;
  
  temp->readFromFile(file);
   
  if (I[index] != NULL){
    delete I[index];
    I[index] = temp;
  }
  else
    I[index] = temp;
  
  xi[index] = x;
  yi[index] = y;

  temp = NULL;

}


void Scene::changelayer(int index, int newindex)
{
  if (index < 0 || index > maxImage-1 )
    {
      cout<<"index out of bounds"<<endl;
      return;
    }
  
  if (newindex < 0 || newindex > maxImage-1 )
    {
      cout<<"index out of bounds"<<endl;
      return;
    }
  
  if (newindex == index)
    return;
  
  if (I[newindex] != NULL)
    {
      delete I[newindex];
      I[newindex] = I[index];
      I[index] = NULL;
    }
  else
    {
      I[newindex] = I[index];
      I[index] = NULL;
    }
  
  xi[newindex] = xi[index];
  yi[newindex] = yi[index];

  
}


void Scene::translate(int index, int xcoord, int ycoord){
 if (index < 0 || index > maxImage-1 )
    {
      cout<<"index out of bounds"<<endl;
      return;
    }

 xi[index] = xcoord;
 yi[index] = ycoord;
 
}


void Scene::deletepicture(int index){
  if (index < 0 || index > maxImage-1 )
    {
      cout<<"invalid index"<<endl;
      return;
    }
  
  if (I[index] == NULL)
    {
      cout<<"invalid index"<<endl;
      return;
    }
  
  delete I[index];
  I[index] = NULL;
  
}


Image * Scene::getpicture(int index)const{
  if (index < 0 || index > maxImage-1 )
    {
      cout<<"invalid index"<<endl;
      return NULL;
    }
  
  if (I[index] == NULL)
    {
      cout<<"invalid index"<<endl;
      return NULL;
    }
  
  return I[index];
}


Image Scene::drawscene()const{

  size_t height = 0;
  size_t width = 0;

  for (int i = 0; i < maxImage; i++){
    if(I[i] != NULL){
      if ( (xi[i] + I[i]->width())> width )
	width = xi[i] + I[i]->width();
      if ( (yi[i] + I[i]->height())> height )
	height = yi[i] + I[i]->height();
    }
  }
  
  Image final;

  final.resize(width ,height);

  for (int i = 0; i < maxImage; i++){
    if (I[i] != NULL){
      for (size_t j = xi[i]; j < (xi[i] + I[i]->width()); j++){
	for (size_t k = yi[i]; k < (yi[i] + I[i]->height()); k++){
	  *final(j,k) =*(*I[i])(j - xi[i], k - yi[i]);
	}
      }
    }
  }

  return final;
}
