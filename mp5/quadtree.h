/**
 * @file quadtree.h
 * Quadtree class definition.
 * @date Spring 2008
 */

#ifndef QUADTREE_H
#define QUADTREE_H

#include "png.h"

/**
 * A tree structure that is used to compress PNG images.
 */
class Quadtree
{
  public:
    Quadtree();
    Quadtree(PNG const & source, int resolution);
    Quadtree(Quadtree const & other);
    ~Quadtree();
    RGBAPixel getPixel(int x, int y) const;
    PNG decompress () const;
    void buildTree(PNG const & source, int resolution);
    
    int pruneSize (int tolerance) const;
    int idealPrune(int numLeaves) const;
    void prune(int tolerance);
    void clockwiseRotate();
    Quadtree const & operator = (Quadtree const & other);
  private:
    /**
     * A simple class representing a single node of a Quadtree.
     * You may want to add to this class; in particular, it could
     * probably use a constructor or two...
     */
    class QuadtreeNode
    {
      public:
        QuadtreeNode* nwChild; /**< pointer to northwest child */
        QuadtreeNode* neChild; /**< pointer to northeast child */
        QuadtreeNode* swChild; /**< pointer to southwest child */
        QuadtreeNode* seChild; /**< pointer to southeast child */

        RGBAPixel element; /**< the pixel stored as this node's "data" */
    };

    QuadtreeNode* root; /**< pointer to root of quadtree */

    int res;//resolution

    Quadtree::QuadtreeNode* getPixel_helper(QuadtreeNode* subroot, int targetX, int targetY, int curX, int curY, int resolution) const;
  
    void buildTreeHelper(PNG const & source, int resolution, int x, int y, QuadtreeNode* &subroot);

    void copy(QuadtreeNode *& ret, QuadtreeNode * const & other);

    //Quadtree::QuadtreeNode* copy_helper(QuadtreeNode*  other);

    //QuadtreeNode* copy_node(QuadtreeNode* const & other);

    void clear_helper(QuadtreeNode* &root);

    void clear();

    bool prunability(QuadtreeNode* node, QuadtreeNode* root, int tolerance)const;

    //void decompress_helper(QuadtreeNode* const &subroot,PNG & img, int x, int y, int resolution) const ;

    void pruneHelper(QuadtreeNode* subroot, int tolerance);
    
    void RotateHelper(QuadtreeNode* subroot);

    int pruneSizeHelper(QuadtreeNode* subroot, int tolerance) const;

    

/**** Functions for testing/grading                      ****/
/**** Do not remove this line or copy its contents here! ****/
#include "quadtree_given.h"
};

#endif
