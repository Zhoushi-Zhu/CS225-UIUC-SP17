/**
 * @file main.cpp
 * Doubly Linked Skip List (lab_gdb2), main function
 *
 * @author Arman Tajback - Created
 * @author Jordi Paris Ferrer & Arman Tajback - Modified
 * @date (created) Fall 2016
 * @date (modified) Spring 2017
 */

// Feel free to modify this file to test more aspects of your list

#include "skipList.h"
#include <iostream>
#include <string>
#include "rgbapixel.h"


using namespace std;


/**
 * Sets the global variable maxLevel to log_2 of imgSize
 * @param imgSize A power of two which gives how large of an image this list represents
 */
int maxLevelLog(int imgSize)
{
    int counter = 0;
    while (imgSize != 1)
    {
        imgSize = imgSize >> 1;
        counter++;
    }
    return counter;
}



/*
 * Returns whether the given value is a power of two, using the magic of bitshifting
 * @param val The value to check for power-of-two-ness
 * @return Whether val was a power of two
 */
bool powerOf2(int val)
{
    unsigned int bitmask = 1;
    int counter = 0;

    if (val<0)
		return false;
    if ((val&(val-1))!=0)
		return false;

    return true;
}

/**
 * Returns a color represented by the string s.
 * @param s The string to parse into a color
 * @param d The default color to use if parsing failed
 * @return The color being represented by the input string
 */
RGBAPixel colorPicker(string s, RGBAPixel d = RGBAPixel(0,0 ,0))
{
    RGBAPixel color;

    if(s=="black")
        color = RGBAPixel(0, 0, 0);
    else if (s== "red")
        color = RGBAPixel(255, 0, 0);
    else if (s== "blue")
        color = RGBAPixel(0, 0, 255);
    else if (s== "green")
        color = RGBAPixel(0, 255, 0);
    else if (s == "white")
        color = RGBAPixel(255, 255, 255);
    else
    {
        cout << "Invalid color. Please choose one of the following: 'black', 'red', 'blue', 'green', 'white'" << endl;
        cout << "Using default of '" << d << "'" << endl;

        return d;
    }

    return color;
}

int main(int argc, char *argv[])
{
    // Setting seed for random number generator use time(NULL) for more random behavior
    // Seed it for deterministic numbers, useful for debugging
    //srand(225);
    srand(time(NULL));

    if (argc < 3 || argc > 5)
    {
        cout << "./lab_gdb2  <image_size>  <probability>  [foreground color]  [background color]" << endl;
        return 0;
    }

    int img_size = stoi(argv[1]);
    int probability = stoi(argv[2]);
    RGBAPixel fore = RGBAPixel(0, 0, 0);
    RGBAPixel back = RGBAPixel(255, 255, 255);

    if(argc >= 4)
    {
        string c(argv[3]);
        transform(c.begin(), c.end(), c.begin(), ::tolower);
        fore = colorPicker(c, RGBAPixel(0, 0 , 0));
    }
    if(argc >= 5)
    {
        string c(argv[4]);
        transform(c.begin(), c.end(), c.begin(), ::tolower);
        back = colorPicker(c, RGBAPixel(255, 255 , 255));
    }



    /* Feel free to change 256 to 512 if you want a bigger image.
     *  Just be aware it will be very slow (it might be too big and break)!
     */
    if (!powerOf2(img_size) || img_size < 4 || img_size > 256)
    {
        cout << "Please enter your an image size greater than 2 and less than 512 "
            "and as a power of 2."
            << endl;
        return 0;
    }
    if (probability > 100 || probability < 1)
    {
        cout << "Please enter an integer between 1 and 100." << endl;
        return 0;
    }

    if(img_size >= 256)
        cout << "Using large image size! out-structure.png will be generated but not viewable in the default editor!"
            " Use something like chrome to view (google-chrome out-structure.png &)" << endl;


    RGBAPixel temp(10,11,12);
    RGBAPixel aaa;
    SkipList * test = new SkipList(probability, maxLevelLog(img_size*img_size));



    for(int i = 0; i < img_size*img_size; i+=2)
    {
        test->insert(i, temp);
    }
    test->insert(5,temp);
    test->insert(8,temp);
    test->insert(1,temp);
    test->insert(0,temp);
    test->insert(9,temp);
    test->insert(1,temp);
    test->insert(20,temp);
    test->insert(11,temp);
    aaa=test->search(3);

    SkipNode *a=test->head;

/*
    SkipList list(50, 50);
    vector<int> soln;
    vector<int> keys;

    RGBAPixel c(137, 137, 137);
    for(int i = 1; i < 999; i += 3)
    {
        keys.push_back(i);
        soln.push_back(i);
    }

    random_shuffle(keys.begin(), keys.end());

    for(int k : keys)
        list.insert(k, c);
*/


    test->makeImage(img_size, fore, back).writeToFile("out-degenerate.png");
    test->toPNG(100, fore, back).writeToFile("out-structure.png");

    delete test;
    return 0;
}
