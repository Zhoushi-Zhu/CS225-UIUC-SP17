/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */
#include <cmath>


template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
    /**
     * @todo Implement this function!
     */
    bool ret;

    if(first[curDim] == second[curDim])
        return first < second;

    return first[curDim] < second[curDim];
}

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
    /**
     * @todo Implement this function!
     */
    //int temp[Dim];
    int curDis = 0, potDis = 0;
    
    curDis = getDis(currentBest, target);
    potDis = getDis(potential, target);

    //cout<<curDis<<" "<<potDis<<endl;
    if(potDis != curDis)
        return curDis > potDis;

    return potential < currentBest;
}

template <int Dim>
int KDTree<Dim>::getDis(Point<Dim> const & first, Point<Dim> const & second) const{
    int curDis = 0;

    for (int i = 0; i < Dim; i++)
    {
        /* code */
        curDis += pow((first[i] - second[i]), 2 );
    }
    return curDis;

}


template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    /**
     * @todo Implement this function!
     */

    points = newPoints;
    buildtreehelper(0, points.size()-1, 0);   
}

template <int Dim>
void KDTree<Dim>::buildtreehelper(int left, int right, int dimension){
    if(right <= left)
        return;

    int temp = (left+right)/2;
    quickselect(left, right, temp, dimension);


    buildtreehelper(left, temp-1, (dimension+1)%Dim);
    buildtreehelper(temp+1, right, (dimension+1)%Dim);
}



template <int Dim>
void KDTree<Dim>::quickselect(int left, int right, int midindex, int dimension){
    if(right <= left)
    //if(left - right <= 1)
        return;

    int pivot = partition(left, right, midindex, dimension);
    if(midindex < pivot){
        quickselect(left, pivot-1, midindex, dimension);
    }else if(midindex > pivot){
        quickselect(pivot+1, right, midindex, dimension);
    }

}

template <int Dim>
int KDTree<Dim>::partition(int left, int right, int pivot, int dimension){
    Point<Dim> pivotValue = points[pivot];
    std::swap(points[pivot], points[right]);

    int storeIndex = left;

    for(int i = left; i < right; i++){
        if(smallerDimVal(points[i], pivotValue, dimension)){
            std::swap(points[storeIndex], points[i]);
            storeIndex++;
        }
    }
    std::swap(points[storeIndex], points[right]);



    return storeIndex;
}




template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */
    Point<Dim> ret;
    int radius = 0;
    bool flag = true;
    findhelper(query, ret, 0, points.size()-1, 0, radius, flag);


    return ret;
}

template <int Dim>
void KDTree<Dim>::findhelper(const Point<Dim>& query, Point<Dim>& currentBest, int left, int right, int dimension, int& radius, bool & flag)const{
    if(left > right )
        return;

    int cur = (left+right)/2;

    if(left == right){
        if(flag){
            currentBest = points[cur];
            radius = getDis(points[cur], query);//radius is the squared
            flag = false;
            
        }else{
            if(shouldReplace(query, currentBest, points[cur])){
                currentBest = points[cur];
                radius = getDis(points[cur], query);
            }
        }
    return;
    }   

    if(smallerDimVal(query, points[cur], dimension)){
        findhelper(query, currentBest, left, cur-1, (dimension+1)%Dim, radius, flag);
        if(shouldReplace(query, currentBest, points[cur])){
            currentBest = points[cur];
            radius = getDis(points[cur], query);
            flag = false;
            
        }
        if(is_range_dimension(points[cur], query, dimension, radius)){
            findhelper(query, currentBest, cur+1, right, (dimension+1)%Dim, radius, flag);
        }
    }else{
        findhelper(query, currentBest, cur+1, right, (dimension+1)%Dim, radius, flag);
        if(shouldReplace(query, currentBest, points[cur])){
            currentBest = points[cur];
            radius = getDis(points[cur], query);
            flag = false;
            
            
        }
        if(is_range_dimension(points[cur], query, dimension, radius)){
            findhelper(query, currentBest, left, cur-1, (dimension+1)%Dim, radius, flag);
        }
    }

}

template <int Dim>
bool KDTree<Dim>::is_range_dimension(Point<Dim> const & cur,  Point<Dim> const & target, int dimension, int radius) const{
    if(pow((cur[dimension]- target[dimension]), 2) <= radius)
        return true;
    else
        return false;



}




