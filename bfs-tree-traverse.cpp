
/** @file binary-tree-level-order.cpp
 *  @brief 
 *
 *  Write a method that prints out each level of the following unbalanced binary tree structure.
 *  
 *        a
 *      b   c
 *     d e   f
 *            g
 *
 *  output: [a], [bc], [def], [g]
 *
 *  @author Shawn Mullings (@shawnmullings)
 *  @bug No known bugs.
 */


/* -- Includes -- */

#include <iostream>
#include <vector>
#include <queue>

/**
*   Node object
*/
template <class T>
struct Node {
    public:

    T data;
    Node<T> *left;
    Node<T> *right;

    /**
    *   Add node to left child variable
    *   
    *   @param T data 
    *   @return Node
    */
    Node<T> * insert_left(T val){
        this->left = new Node<T>(val);
        return this->left;
    }
    /**
    *   Add node to right child variable
    *   
    *   @param T data 
    *   @return Node
    */
    Node<T> * insert_right(T val){
        this->right = new Node<T>(val);
        return this->right;
    }

    /**
    *   Constructor
    *   
    *   @param T node data 
    *   @return void
    */
    Node(T val) {
        this->data = val;
        this->left = this->right = nullptr;
    }
    /**
    *   Constructor
    *   
    *   @param T node data 
    *   @param T left child node
    *   @param T right child node 
    *   @return void
    */
    Node(T val, Node<T> left, Node<T> right) {
        this->data = val;
        this->left = left;
        this->right = right;
    }

    /**
    *   Delete
    */
    ~Node(){}
};

/**
*   function to print tree scructure level by level
*   
*   @param Root node 
*   @return void
*/
void binary_tree_level_order_print(Node<char> *node){
    
    /* queue - FIFO */
    std::queue<Node<char> *> que;

    /* push first node into the queue */
    que.push(node);

    /* Send node data to console */
    std::cout << "[" << (*que.front()).data << "]";

    while (!que.empty())
    {
        /* temp queue - FIFO */
        std::queue<Node<char> *> tQue;

        std::cout << ", [";

        // get nodes children at level
        while (!que.empty()){
            /* if we are not evaluating a leaf add left and right child nodes to temp queue */
            if((*que.front()).left != nullptr){
                Node<char> *left = (*que.front()).left;
                std::cout << (*left).data;
                tQue.push(left);
            }  
            if((*que.front()).right != nullptr){
                Node<char> *right = (*que.front()).right;
                std::cout << (*right).data;
                tQue.push(right);
            } 
            /* remove evaluated node from front of queue */
            que.pop();
        }

        std::cout << "]";
        que = tQue;
    }

    std::cout << std::endl;
}


int main() {

    /* Create binary tree scructure */
    Node<char> *root =  new Node<char>('a');
    root->left =  new Node<char>('b');
    root->right =  new Node<char>('c');

    root->left->left =  new Node<char>('d');
    root->left->right =  new Node<char>('e');

    root->right->right =  new Node<char>('f');
    root->right->right->right =  new Node<char>('g');

    /* Print binary tree scructure level by level */
    std::cout << "Level Order Print Tree: " << std::endl;
    binary_tree_level_order_print(root);

    return 0;
}
