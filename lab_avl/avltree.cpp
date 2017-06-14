/**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

template <class K, class V>
V AVLTree<K, V>::find(const K& key) const
{
    return find(root, key);
}

template <class K, class V>
V AVLTree<K, V>::find(Node* subtree, const K& key) const
{
    if (subtree == NULL)
        return V();
    else if (key == subtree->key)
        return subtree->value;
    else {
        if (key < subtree->key)
            return find(subtree->left, key);
        else
            return find(subtree->right, key);
    }
}

template <class K, class V>
void AVLTree<K, V>::rotateLeft(Node*& t)
{
    *_out << __func__ << endl; // Outputs the rotation name (don't remove this)
    // your code here

    Node * temp = t->right;
    t->right = temp->left;
    temp->left = t;
    t->height = max(heightOrNeg1(t->left),heightOrNeg1(t->right))+1;
    t = temp;
    t->height = max(heightOrNeg1(t->left),heightOrNeg1(t->right))+1;
}

template <class K, class V>
void AVLTree<K, V>::rotateLeftRight(Node*& t)
{
    *_out << __func__ << endl; // Outputs the rotation name (don't remove this)
    // Implemented for you:
    rotateLeft(t->left);
    rotateRight(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateRight(Node*& t)
{
    *_out << __func__ << endl; // Outputs the rotation name (don't remove this)
    // your code here
    Node * temp = t->left;
    t->left = temp->right;
    temp->right = t;
    t->height = max(heightOrNeg1(t->left),heightOrNeg1(t->right))+1;
    t = temp;
    t->height = max(heightOrNeg1(t->left),heightOrNeg1(t->right))+1;

}

template <class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node*& t)
{
    *_out << __func__ << endl; // Outputs the rotation name (don't remove this)
    // your code here
    rotateRight(t->right);
    rotateLeft(t);
}

template <class K, class V>
void AVLTree<K, V>::rebalance(Node*& subtree)
{
    // your code here
    /*if(subtree == NULL)
        return;

    rebalance(subtree->left);
    rebalance(subtree->right);
*/
    


    int hl = -1, hr = -1;

    hl = heightOrNeg1(subtree->left);
    hr = heightOrNeg1(subtree->right);

    if(hr - hl > 1){
        
        if(heightOrNeg1(subtree->right->left) - heightOrNeg1(subtree->right->right) <= 0)
            rotateLeft(subtree);
        else
            rotateRightLeft(subtree);      
        
    }else if(hr - hl < -1){
        if(heightOrNeg1(subtree->left->right) - heightOrNeg1(subtree->left->left) <= 0)
            rotateRight(subtree);
        else
            rotateLeftRight(subtree);
    }

    subtree->height = 1 + max(heightOrNeg1(subtree->left),heightOrNeg1(subtree->right));;

}

template <class K, class V>
void AVLTree<K, V>::insert(const K & key, const V & value)
{
    insert(root, key, value);
    //cout<<"~~~~~~"<<endl;
    //update_height(root);
    //rebalance(root);
}

template <class K, class V>
void AVLTree<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
    // your code here
    if(subtree == NULL)
        subtree = new Node(key, value);
    else if(key < subtree->key){
        insert(subtree->left, key, value);
    }else if(key > subtree->key){
        insert(subtree->right, key, value);    
    }

    rebalance(subtree);
}

template <class K, class V>
void AVLTree<K, V>::remove(const K& key)
{
    remove(root, key);
    //update_height(root);
}

template <class K, class V>
void AVLTree<K, V>::remove(Node*& subtree, const K& key)
{
    if (subtree == NULL)
        return;

    if (key < subtree->key) {
        // your code here
        remove(subtree->left, key);  
        //subtree->height = 1 + max(heightOrNeg1(subtree->left), heightOrNeg1(subtree->right));   
    } else if (key > subtree->key) {
        // your code here
        remove(subtree->right, key);
        //subtree->height = 1 + max(heightOrNeg1(subtree->left), heightOrNeg1(subtree->right));
    } else {
        if (subtree->left == NULL && subtree->right == NULL) {
            // no-child remove 
            // your code here
            /*Node* temp = subtree->left;
                delete subtree;
                subtree = temp;*/
            delete subtree;
            subtree = NULL;
        } else if (subtree->left != NULL && subtree->right != NULL) {
            /* two-child remove */
            // your code here
            Node* cur = subtree->left;
            while(!(cur->right==NULL)){
                cur = cur->right;
            }
            swap(subtree, cur);
            remove(subtree->left, key);
        } else {
            /* one-child remove */
            // your code here
            if(subtree->right == NULL){
                Node* temp = subtree->left;
                delete subtree;
                subtree = temp;
                //subtree->height = 1 + max(heightOrNeg1(subtree->left), heightOrNeg1(subtree->right));
            }else{
                Node* temp = subtree->right;
                delete subtree;
                subtree = temp;
                //subtree->height = 1 + max(heightOrNeg1(subtree->left), heightOrNeg1(subtree->right));

            }
        }
        // your code here
        

    }
    if(subtree){
    
            rebalance(subtree);
        }
}

/*template <class K, class V>
void AVLTree<K, V>::find_left_most(Node* & cur, Node* & root){
    if(cur->left != NULL){
        find_left_most(cur->left,root);
        cur->height = 1 + max(heightOrNeg1(cur->left), heightOrNeg1(cur->right));
    }

    swap(cur, root);
    Node* temp = cur;
    cur = NULL;
    delete temp;


}*/

/*template <class K, class V>
void AVLTree<K, V>::update_height(Node* &root){
    if(root == NULL)
        return;
    update_height(root->right);
    update_height(root->left);

    root->height = getH(root);
    

}*/


/*template <class K, class V>
int AVLTree<K, V>::getH(Node* root){
    if(root == NULL)
        return -1;


    return 1+max(getH(root->left), getH(root->right));
}*/


