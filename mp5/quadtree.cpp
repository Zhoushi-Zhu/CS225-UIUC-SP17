/**
 * @file quadtree.cpp
 * Quadtree class implementation.
 * @date Spring 2008
 */
#include "quadtree.h"
#include <iostream>
#include <cmath>

using std::uint8_t;
using namespace std;

Quadtree::Quadtree(){
	root = NULL;
	res = 0;
}

Quadtree::Quadtree(PNG const & source, int resolution){
	if(resolution == 0){
		root = NULL;
		res = 0;
	}else{
		root = NULL;
		buildTree(source, resolution);
		res = resolution;
	}
}

Quadtree::Quadtree(Quadtree const & other){
	copy(root, other.root);
	res = other.res;
}

Quadtree::~Quadtree(){
	clear_helper(root);
	//res = 0;
}

Quadtree const & Quadtree::operator = (Quadtree const & other){
	res = other.res;
	if (this != &other)
    {
      clear_helper(root);
      copy(root, other.root);
    }

  return *this;
}


void Quadtree::copy(QuadtreeNode *& ret, QuadtreeNode * const & other){

		if(other == NULL){
			ret = NULL;
			return;
		}

		ret = new QuadtreeNode();
		copy(ret->nwChild, other->nwChild);
		copy(ret->neChild, other->neChild);
		copy(ret->swChild, other->swChild);
		copy(ret->seChild, other->seChild);
		ret->element = other->element;
}

/*Quadtree::QuadtreeNode* Quadtree::copy_helper(QuadtreeNode* other){

	QuadtreeNode* newnode = NULL;

	if(other){
		newnode = new QuadtreeNode;
		newnode->element = other->element;
		newnode->nwChild = copy_helper(other->nwChild);
		newnode->neChild = copy_helper(other->neChild);
		newnode->swChild = copy_helper(other->swChild);
		newnode->seChild = copy_helper(other->seChild);
	}
	return newnode;
}*/

/*Quadtree::QuadtreeNode* Quadtree::copy_node(QuadtreeNode* const & other){
	QuadtreeNode* newnode = NULL;

	if(other){
		newnode = new QuadtreeNode;
		newnode->element = other->element;
		newnode->nwChild = copy_node(other->nwChild);
		newnode->neChild = copy_node(other->neChild);
		newnode->swChild = copy_node(other->swChild);
		newnode->seChild = copy_node(other->seChild);
	}

	return newnode;
}*/

/*void Quadtree::clear(){
	clear_helper(this->root);
	root = NULL;
}*/

void Quadtree::clear_helper(QuadtreeNode* &root){
	if(root == NULL)
		return;

	clear_helper(root->nwChild);
	clear_helper(root->neChild);
	clear_helper(root->swChild);
	clear_helper(root->seChild);

	delete root;
	root = NULL;
	

}



void Quadtree::buildTree(PNG const & source, int resolution){
	/*int ** flag = new int*[resolution];
	for(int i = 0; i <resolution; i++){
		flag[i] = new int[resolution];
	}*/
	if(root != NULL)
		clear_helper(root);

	res = resolution;
	buildTreeHelper(source, resolution, 0 ,0, root);
}

void Quadtree::buildTreeHelper(PNG const & source, int resolution, int x, int y, QuadtreeNode* &subroot){
	if(resolution == 0){
		return;
	}

	if(resolution == 1){
		subroot = new QuadtreeNode();
		subroot->element = *source(x,y);
		//cout<<x<<" "<<y<<endl;
	}else{
		//subroot->element = RGBAPixel();
		subroot = new QuadtreeNode();
		buildTreeHelper(source, resolution/2, x, y, subroot->nwChild);
		buildTreeHelper(source, resolution/2, x+resolution/2, y, subroot->neChild);
		buildTreeHelper(source, resolution/2, x, y+resolution/2, subroot->swChild);
		buildTreeHelper(source, resolution/2, x+resolution/2, y+resolution/2, subroot->seChild);
		
	if(subroot->nwChild != NULL){	
		uint8_t red1 = (subroot->nwChild->element).red;
		uint8_t red2 = (subroot->neChild->element).red;
		uint8_t red3 = (subroot->swChild->element).red;
		uint8_t red4 = (subroot->seChild->element).red;
		(subroot->element).red = (red1 + red2 + red3 + red4) / 4;

		uint8_t blue1 = (subroot->nwChild->element).blue;
		uint8_t blue2 = (subroot->neChild->element).blue;
		uint8_t blue3 = (subroot->swChild->element).blue;
		uint8_t blue4 = (subroot->seChild->element).blue;
		(subroot->element).blue = (blue1 + blue2 + blue3 + blue4) / 4;

		uint8_t green1 = (subroot->nwChild->element).green;
		uint8_t green2 = (subroot->neChild->element).green;
		uint8_t green3 = (subroot->swChild->element).green;
		uint8_t green4 = (subroot->seChild->element).green;
		(subroot->element).green = (green1 + green2 + green3 + green4) / 4;
	}

	}	

	
}


RGBAPixel Quadtree::getPixel(int x, int y) const {
	if((y >= res) || (x >= res) || (x < 0) || (y < 0))
		return RGBAPixel();
	if(root == NULL)
		return RGBAPixel();

	QuadtreeNode* ret = getPixel_helper(root, x, y, 0, 0, res);

	return ret->element;

	}

Quadtree::QuadtreeNode* Quadtree::getPixel_helper(QuadtreeNode* subroot, int targetX, int targetY, int curX, int curY, int resolution) const {
	//if(targetY >= resolution || targetX >= resolution || targetX < 0 || targetY < 0)
	//	return RGBAPixel();

	if(resolution == 1 || subroot->nwChild == NULL)
		return subroot;

	if(curX+resolution/2 > targetX){
		if(curY+resolution/2 > targetY){
			return getPixel_helper(subroot->nwChild, targetX, targetY, curX, curY, resolution/2);
		}
		else{
			return getPixel_helper(subroot->swChild, targetX, targetY, curX, curY+resolution/2, resolution/2);
		}
	}else{
		if(curY+resolution/2 > targetY){
			return getPixel_helper(subroot->neChild, targetX, targetY, curX+resolution/2, curY, resolution/2);
		}
		else{
			return getPixel_helper(subroot->seChild, targetX, targetY, curX+resolution/2, curY+resolution/2, resolution/2);
		}
	}
}

PNG Quadtree::decompress () const{
	if(root == NULL)
		return PNG();

	PNG ret(res, res);
	for(int i = 0; i < res; i++){
		for(int j = 0; j < res; j++){
			*(ret(i,j)) = getPixel(i,j);
		}
	}

	return ret;

}

/*void Quadtree::decompress_helper(QuadtreeNode* const &subroot,PNG & img, int x, int y, int resolution) const{
	if(resolution == 1){
		*img(x,y) = subroot->element;
		cout<<x<<" "<<y<<endl;
	}
	
	else{
		decompress_helper(root->nwChild, img, x, y, resolution/2);
		decompress_helper(root->neChild, img, x+resolution/2, y, resolution/2);
		decompress_helper(root->swChild, img, x, y+resolution/2, resolution/2);
		decompress_helper(root->seChild, img, x+resolution/2, y+resolution/2, resolution/2);
	}
}*/


void Quadtree::clockwiseRotate(){
	RotateHelper(root);
}	

void Quadtree::RotateHelper(QuadtreeNode* subroot){
	if(subroot == NULL)
		return;

	QuadtreeNode* temp;
	temp = subroot->nwChild;
	subroot->nwChild = subroot->swChild;
	subroot->swChild = subroot->seChild;
	subroot->seChild = subroot->neChild;
	subroot->neChild = temp;

	RotateHelper(subroot->nwChild);
	RotateHelper(subroot->neChild);
	RotateHelper(subroot->swChild);
	RotateHelper(subroot->seChild);


}


void Quadtree::prune(int tolerance){
	pruneHelper(root, tolerance);
}	

void Quadtree::pruneHelper(QuadtreeNode* subroot, int tolerance){
	if(subroot != NULL && subroot->nwChild != NULL){
		if(prunability(subroot, subroot, tolerance)){
			clear_helper(subroot->nwChild);
			clear_helper(subroot->neChild);
			clear_helper(subroot->swChild);
			clear_helper(subroot->seChild);
			subroot->nwChild = NULL;
			subroot->neChild = NULL;
			subroot->swChild = NULL;
			subroot->seChild = NULL;
		}else{
			pruneHelper(subroot->nwChild, tolerance);
			pruneHelper(subroot->neChild, tolerance);
			pruneHelper(subroot->swChild, tolerance);
			pruneHelper(subroot->seChild, tolerance);
		}


	}
}

int Quadtree::pruneSize	(int tolerance)	const{
	return pruneSizeHelper(root, tolerance);
}

int Quadtree::pruneSizeHelper(QuadtreeNode* subroot, int tolerance)const{
	if(subroot == NULL)
		return 0;
	else if(subroot->nwChild == NULL || prunability(subroot, subroot, tolerance))
		return 1;
	else{
		int temp1 = pruneSizeHelper(subroot->nwChild, tolerance);
		int temp2 = pruneSizeHelper(subroot->neChild, tolerance);
		int temp3 = pruneSizeHelper(subroot->swChild, tolerance);
		int temp4 = pruneSizeHelper(subroot->seChild, tolerance);
		return temp1+temp2+temp3+temp4;
	}

	return 0;
}


int Quadtree::idealPrune(int numLeaves)	const{
	int max = 255*255*3;
	int min = 0;

	int tolerance = (max+min)/2;

	while(min <= max){
		tolerance = (max+min)/2;

		if(pruneSize(tolerance) > numLeaves)
			min = tolerance+1;
		else
			max = tolerance-1;

		tolerance = (max+min)/2;
	}

	return min;


}

bool Quadtree::prunability(QuadtreeNode* node, QuadtreeNode* root, int tolerance)const{
	if(node == NULL)
		return true;

	if(node->nwChild != NULL){
		bool temp1 = prunability(node->nwChild, root, tolerance);
		bool temp2 = prunability(node->neChild, root, tolerance);
		bool temp3 = prunability(node->swChild, root, tolerance);
		bool temp4 = prunability(node->seChild, root, tolerance);
		return temp1&&temp2&&temp3&&temp4;
	}else{
		int diff = pow(node->element.red - root->element.red, 2) +
				   pow(node->element.green - root->element.green, 2) +
				   pow(node->element.blue - root->element.blue, 2);

		return diff <= tolerance;

	}

}































