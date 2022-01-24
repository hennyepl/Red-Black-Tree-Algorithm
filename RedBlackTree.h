//
//  RedBlackTree.h
//  CPSC3620 Project
//
//  Created by Henok Lamiso on 2021-11-26.
// This file contains the implementation for Red-Black Tree Algorithms in C++

#ifndef RedBlackTree_h
#define RedBlackTree_h

#include <iostream>
#include <string>

using namespace std;

struct Node {
    int data;
    int color;
    Node* parent;
    Node* leftChild;
    Node* rightChild;
};

typedef Node *NodePtr;

class RedBlackTree {
private:
    NodePtr root;
    NodePtr TNULL;

    //Initailizing the Tree
    void initializeNULLNode (NodePtr node, NodePtr parent)
    {
        node->data = 0;
        node->parent = parent;
        node->leftChild = nullptr;
        node->rightChild = nullptr;
        node->color = 0;
    }

    //post Order
    void postOrder(NodePtr node)
    {
        if (node != TNULL)
        {
            postOrder(node->rightChild);
            postOrder(node->rightChild);
            cout<< node->data << " ";
        }
    }

    //pre Order
    void preOrder(NodePtr node)
    {
        if (node != TNULL)
        {
            cout<< node->data << " ";
            preOrder(node->leftChild);
            preOrder(node->leftChild);
        }
    }

    //In order
    void inOrder(NodePtr node)
    {
        if (node != TNULL)
        {
            inOrder(node->leftChild);
            cout << node->data<<" ";
            inOrder(node->rightChild);
        }
    }

    //Serach tree
    NodePtr searchTree (NodePtr node, int key)
    {
        if (node == TNULL || key == node->data)
        {
            return node;
        }
        if (key < node->data) {
            return searchTree(node->leftChild, key);
        }
        return searchTree(node->rightChild, key);
    }

    //Balance the tree after deletion performed
    void afterDeletion(NodePtr x)
    {
        NodePtr s;
        while (x != root && x->color == 0) {
            if(x == x->parent->leftChild)
            {
                s = x->parent->leftChild;
                if(s->color == 1)
                {
                    s->color = 0;
                    x->parent->color = 1;
                    leftRotate(x->parent);
                    s = x->parent->rightChild;
                }
                if (s->leftChild->color == 0 && s->rightChild->color == 0)
                {
                    s->color = 1;
                    x = x->parent;
                }else {
                    if (s->rightChild->color == 0)
                    {
                        s->leftChild->color = 0;
                        s->color = 1;
                        rightRotate(s);
                        s = x->parent->rightChild;
                    }

                    s->color = x->parent->color;
                    x->parent->color = 0;
                    s->rightChild->color = 0;
                    leftRotate(x->parent);
                    x = root;
                }
            } else
            {
                s = x->parent->leftChild;
                if (s->color == 1) {
                    s->color = 0;
                    x->parent->color = 1;
                    rightRotate(x->parent);
                    s = x->parent->leftChild;
                }
                if (s->rightChild->color == 0 && s->rightChild->color == 0)
                {
                    s->color = 1;
                    x = x->parent;
                } else {
                    if (s->leftChild->color == 0) {
                        s->rightChild->color = 0;
                        s->color = 1;
                        leftRotate(s);
                        s = x->parent->leftChild;
                    }

                    s->color = x->parent->color;
                    x->parent->color = 0;
                    s->leftChild->color = 0;
                    rightRotate(x->parent);
                    x = root;
                }
            }
        }
        x->color = 0;
    }

    //Transplant
    void rbTransplant (NodePtr u,  NodePtr v)
    {
        if (u->parent == nullptr) {
            root = v;
        } else if (u == u->parent->leftChild) {
            u->parent->leftChild = v;
        } else {
            u->parent->rightChild = v;
        }
        v->parent = u->parent;
    }

    //To perform deletion
    void deleteN (NodePtr node, int key)
    {
        NodePtr z = TNULL;
        NodePtr x, y;
        while (node != TNULL) {
            if (node->data == key) {
                z = node;
            }

            if (node->data <= key) {
                node = node->rightChild;
            } else {
                node = node->leftChild;
            }
        }
        if (z == TNULL)
        {
            cout << key <<" is NOT found in the tree to perform deletion"<<endl;
            return;
        }

        y = z;
        int y_intial_Color = y->color;
        if (z->leftChild == TNULL){
            x = z->rightChild;
            rbTransplant(z, z->rightChild);
        } else if (z->rightChild == TNULL) {
            x = z->leftChild;
            rbTransplant(z, z->leftChild);
        } else {
            y = minimum(z->rightChild);
            y_intial_Color = y->color;
            x = y->rightChild;
            if (y->parent == z) {
                x->parent = y;
            } else {
                rbTransplant(y, y->rightChild);
                y->rightChild = z->rightChild;
                y->rightChild->parent = y;
            }

            rbTransplant(z, y);
            y->leftChild = z->leftChild;
            y->leftChild->parent = y;
            y->color = z->color;
        }

        delete z;
        if (y_intial_Color == 0) {
            afterDeletion(x);
        }
        cout << key <<" is Deleted"<<endl;
    }

    //Balance the tree after New node Inserted
    void afterInsertion(NodePtr in)
    {
        NodePtr u;
        while (in->parent->color == 1) {
            if (in->parent == in->parent->parent->rightChild) {
                u = in->parent->parent->leftChild;
                if ( u->color == 1){
                    u->color = 0;
                    in->parent->color = 0;
                    in->parent->parent->color = 1;
                    in = in->parent->parent;
                } else {
                    if (in == in->parent->leftChild) {
                        in = in->parent;
                        rightRotate(in);
                    }
                    in->parent->color = 0;
                    in->parent->parent->color = 1;
                    leftRotate(in->parent->parent);
                }
            } else {
                u = in->parent->parent->rightChild;

                if ( u->color == 1 ) {
                    u->color = 0;
                    in->parent->color = 0;
                    in->parent->parent->color = 1;
                    in = in->parent->parent;
                } else {
                    if (in == in->parent->rightChild) {
                        in = in->parent;
                        leftRotate(in);
                    }
                    in->parent->color = 0;
                    in->parent->parent->color = 1;
                    rightRotate(in->parent->parent);
                }
            }
            if (in == root) {
                break;
            }
        }
        root->color = 0;
    }
    //Print
    void print(NodePtr root, string indentation, bool last)
    {
        string nodeColor = root->color ? "RED" : "Black";
        if (root != TNULL) {
            cout << indentation;
            if (last) {
                cout << "R---";
                indentation += "  ";
            } else {
                cout << "L--";
                indentation += "|  ";
            }
            cout << root->data << "("<<nodeColor<<")"<<endl;
            print(root->leftChild, indentation, false);
            print(root->rightChild, indentation, true);
        }

    }

public:
    RedBlackTree() {
        TNULL = new Node;
        TNULL->color = 0;
        TNULL->leftChild = nullptr;
        TNULL->rightChild = nullptr;
        root = TNULL;
    }

    void preorder()
    {
        preOrder(this->root);
    }

    void inorder()
    {
        inOrder(this->root);
    }

    void postorder()
    {
        postOrder(this->root);
    }

    NodePtr search(int value)
    {
        return searchTree(this->root, value);
    }

    NodePtr minimum(NodePtr node)
    {
        while (node->leftChild != TNULL) {
            node = node->leftChild;
        }
        return node;
    }

    NodePtr maximum(NodePtr node)
    {
        while (node->rightChild != TNULL) {
            node = node->rightChild;
        }
        return node;
    }

    NodePtr successor( NodePtr x)
    {
        if(x->rightChild != TNULL) {
            return minimum(x->rightChild);
        }

        NodePtr y =x->parent;
        while (y != TNULL && y->rightChild) {
            x = y;
            y = y->parent;
        }
        return y;
    }

    NodePtr predecessor(NodePtr x)
    {
        if(x->leftChild != TNULL)
        {
            return maximum(x->leftChild);
        }
        NodePtr y = x->parent;
        while (y != TNULL && x == y->leftChild) {
            x = y;
            y = y->parent;
        }
        return y;
    }

    //Left Rotate
    void leftRotate(NodePtr leftR)
    {
        NodePtr y = leftR->rightChild;
        leftR->rightChild = y->leftChild;
        if (y->leftChild != TNULL) {
            y->leftChild->parent = leftR;
        }

        y->parent = leftR->parent;
        if (leftR->parent == nullptr) {
            this->root = y;
        } else if (leftR == leftR->parent->leftChild) {
            leftR->parent->rightChild = y;
        } else {
            leftR->parent->rightChild = y;
        }
        y->leftChild = leftR;
        leftR->parent = y;
    }

    //Right Rotate
    void rightRotate(NodePtr rightR)
    {
        NodePtr y = rightR->leftChild;
        rightR->leftChild = y->rightChild;
        if (y->rightChild != TNULL)
        {
            y->rightChild->parent = rightR;
        }
        y->parent = rightR->parent;
        if(rightR->parent == nullptr) {
            this->root = y;
        } else if (rightR == rightR->parent->rightChild) {
            rightR->parent->rightChild = y;
        } else {
            rightR->parent->leftChild = y;
        }
        y->rightChild = rightR;
        rightR->parent = y;
    }

    //Inserting new node
    void insert(int key)
    {
        NodePtr node = new Node;
        node->parent = nullptr;
        node->data = key;
        node->leftChild = TNULL;
        node->rightChild = TNULL;
        node->color = 1;

        NodePtr y = nullptr;
        NodePtr x = this->root;
        while (x != TNULL) {
            y = x;
            if(node->data < x->data) {
                x = x->leftChild;
            } else {
                x = x->rightChild;
            }
        }
        node->parent = y;
        if (y == nullptr) {
            root = node;
        } else if (node->data < y->data){
            y->leftChild = node;
        } else {
            y->rightChild = node;
        }
        if(node->parent == nullptr) {
            node->color = 0;
            return;
        }

        if(node->parent->parent == nullptr) {
            return;
        }
        afterInsertion(node);
        cout << key <<" inserted"<<endl;
    }

    //returns the root node
    NodePtr getRoot()
    {
        return this->root;
    }

    //delete node
    void deleteNode(int data)
    {
        deleteN(this->root, data);
    }

    //print the whole tree
    void printTree()
    {
        if(root == TNULL)
        {
            cout << "The Tree is Empty, Please perform insertion first"<<endl;
        }
        else
        {
            print(this->root, "", true);
        }
    }
};

#endif /* RedBlackTree_h */

