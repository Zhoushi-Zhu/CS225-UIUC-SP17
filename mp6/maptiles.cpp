/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>
#include "maptiles.h"

using namespace std;

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage> const& theTiles)
{
    /**
     * @todo Implement this function!
     */
	if(theTiles.empty())
		return NULL;

	map<RGBAPixel, int> tileDict;//first: average color, second: index of tile in vector
	vector<Point<3>> points;//input for KDTree
	for(size_t i = 0; i < theTiles.size(); i++){
		RGBAPixel temp = theTiles[i].getAverageColor();
		tileDict[temp] = i;

		points.push_back(RGBA_to_Point(temp));
	}

	KDTree<3> theTree = KDTree<3>(points);

	int row = theSource.getRows();
	int col = theSource.getColumns();

	if(row == 0||col == 0)
		return NULL;

	MosaicCanvas* ret = new MosaicCanvas(row, col);

	for(int i = 0; i < row; i++){
		for(int j = 0; j < col; j++){
			RGBAPixel temp = theSource.getRegionColor(i, j);
			Point<3> output = theTree.findNearestNeighbor(RGBA_to_Point(temp));
			temp = Point_to_RGBA(output);
			int k = tileDict[temp];
			ret->setTile(i, j, theTiles[k]);
		}
	}

    return ret;
}

Point<3> RGBA_to_Point(RGBAPixel& input){
	Point<3> output;
	output[0] = input.red;
	output[1] = input.green;
	output[2] = input.blue;
	return output;
}

RGBAPixel Point_to_RGBA(Point<3>& input){
	RGBAPixel output;
	output.red = input[0];
	output.green = input[1];
	output.blue = input[2];
	return output;

}

