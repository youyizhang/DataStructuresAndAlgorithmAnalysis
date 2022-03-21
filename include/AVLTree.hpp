#pragma once
#include "dsexceptions.h"
#include <algorithm>

template <typename Comparable>
class AVLTree {
private:
    struct AVLNode{
        Comparable element;
        AVLNode * left;
        AVLNode * right;
        int height;

        AVLNode(const Comparable& ele, AVLNode *lt, AVLNode *rt, int h=0):
        element{ele}, left{lt}, right{rt}, height{h}{}

        AVLNode(Comparable &&ele, AVLNode *lt, AVLNode &rt, int h = 0):
        element{std::move(ele)}, left{lt}, right{rt}, height{h} {}

    };
    AVLNode *root;

    static const int ALLOWED_IMBALANCE = 1;

public:
    AVLTree() : root{nullptr} {};

    AVLTree(const AVLTree & rhs) : root{nullptr}{
        root = clone(rhs.root);
    }
    AVLTree(AVLTree && rhs) : root{rhs.root}{
        rhs.root = nullptr;
    }
    ~AVLTree(){
        makeEmpty();
    }

    AVLTree& operator=(const AVLTree &rhs){
        AVLTree copy = rhs;
        std::swap(*this, copy);
        return *this;
    }

    AVLTree &operator=(AVLTree &&rhs){
        std::swap(root, rhs.root);
        return *this;
    }

    bool isEmpty() const{
        return root == nullptr;
    }

    const Comparable& findMin() const{
        if(isEmpty()){
            throw UnderflowException{};
        }
        return findMin(root)->element;
    }

    const Comparable& findMax() const{
        if(isEmpty()){
            throw UnderflowException{};
        }
        return findMax(root)->element;
    }



    bool contains(const Comparable &x) const {
        return contains(x, root);
    }

    void printTree() const{
        if(isEmpty())
            std::cout << "Empty Tree" << std::endl;
        else
            printTree(root);
    }

    void makeEmpty(){
        makeEmpty(root);
    }

    void insert(const Comparable& x){
        insert(x, root);
    }

    void insert(Comparable &&x){
        insert(std::move(x), root);
    }

    void remove(const Comparable &x){
        remove(x, root);
    }


private:

    void insert(const Comparable& x, AVLNode *t){
        if(t== nullptr)
            t = new AVLNode{x, nullptr, nullptr};
        else if(x < t->element)
            insert(x, t->left);
        else if(x > t->element)
            insert(x, t->right);
        balance(t);
    }

    void insert(Comparable &&x, AVLNode *t){
        if(t== nullptr)
            t = new AVLNode{t, nullptr, nullptr};
        else if(x < t->element)
            insert(std::move(x), t->left);
        else if(x > t->element)
            insert(std::move(x), t->right);
        balance(t);
    }

    void remove(const Comparable& x, AVLNode* &t){
        if(t == nullptr) return;
        else if(x < t->element)
            remove(x, t->left);
        else if(x > t->element)
            remove(x, t->right);
        // the node has two children
        else if(t->left != nullptr && t->right != nullptr){
            t->element = findMin(t->right)->element;
            remove(t->element, t->right);
        // the node has no or one child
        }else{
            AVLNode *oldNode = t;
            t = (t->left != nullptr) ? t->left : t->right;
            delete oldNode;
        }
        balance(t);
    }

    AVLNode * findMin(AVLNode *t) const{
        if(t== nullptr) return nullptr;
        if(t->left == nullptr) return t;
        return findMin(t->left);
    }

    AVLNode* findMax(AVLNode *t) const{
        if(t != nullptr){
            while (t->right != nullptr)
                t = t->right;
        }
        return t;
    }

    bool contains(Comparable &x, AVLNode *t) const{
        if(t== nullptr) return false;
        else if(t->element < x) contains(x, t->left);
        else if(t->element > x) contains(x, t->right);
        else return true;
    }
    /****** NONRECURSIVE VERSION*************************
bool contains(const Comparable& x, AVLNode *t) const{
    while (t != nullptr)
        if (x < t->element)
            t = t->left;
        else if (x > t->element)
            t = t->right;
        else
            return true;
}
*****************************************************/

    void makeEmpty(AVLNode *t){
        if(t != nullptr){
            makeEmpty(t->left);
            makeEmpty(t->right);
            delete t;
        }
        t = nullptr;
    }

    void printTree(AVLNode *t) const{
        if(t!= nullptr){
            printTree(t->left);
            std::cout << t->element << std::endl;
            printTree(t->right);
        }
    }

    AVLNode * clone(AVLNode *t) const{
        if (t == nullptr) return nullptr;
        else
            return new AVLNode{t->element, clone(t->left), clone(t->right)};
    }

    int height(AVLNode *t) const{
        return t == nullptr ? -1 : t->height;
    }

    int max(int lhs, int rhs) const{
        return lhs > rhs ? lhs : rhs;
    }


    bool contains(const Comparable& x, AVLNode *t) const{
        if (t == nullptr) return false;
        else if(x < t->element)
            contains(x, t->left);
        else if(x > t->element)
            contains(x, t->right);
        else
            return true;
    }




void balance(AVLNode* &t){
    if(t == nullptr) return;
    if(height(t->left) - height(t->right) > ALLOWED_IMBALANCE){
        if(height(t->left->left) >= height(t->left->right))
            rotateWithLeftChild(t);
        else
            doubleWithLeftChild(t);
    }else{
        if (height(t->right) - height(t->left) > ALLOWED_IMBALANCE){
            if(height(t->right->right) >= height(t->right->left))
                rotateWithRightChild(t);
            else
                doubleWithRightChild(t);
        }
    }
    t->height = max(height(t->left), height(t->right)) + 1;


}

// book page 126
void rotateWithLeftChild(AVLNode* &k2){
    AVLNode *k1 = k2->left;
    k2->left = k1->right;
    k1->right = k2;
    k2->height = max(height(k2->left), height(k2->right)) + 1;
    k1->height = max(height(k1->left), k2->height) + 1;
    k2 = k1;
}

void rotateWithRightChild(AVLNode* &k1){
    AVLNode *k2 = k1->right;
    k1->right = k2->left;
    k2->left = k1;
    k1->height = max(height(k1->left), height(k1->right)) + 1;
    k2->height = max(height(k2->right), k1->height) + 1;
    k1 = k2;
}

void doubleWithLeftChild(AVLNode *& k3){
    rotateWithRightChild(k3->left);
    rotateWithLeftChild(k3);
}

void doubleWithRightChild(AVLNode *& k1){
    rotateWithRightChild(k1->right);
    rotateWithRightChild(k1);
}

};




