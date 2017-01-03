
/** @file binary-tree-level-order.cpp
 *  @brief 
 *
 *  Write a function to see if a binary tree is "superbalanced" (a new tree property we just made up).
 *  A tree is "superbalanced" if the difference between the depths of any two leaf nodes ↴ is no greater than one.
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
*   function to print tree scructure
*   
*   @param Root node 
*   @return void
*/
template <class T>
void print_tree(Node<T> *root) {
    if (!root) return;
    print_tree(root->left);
    std::cout << root->data << ' ';
    print_tree(root->right);
}

/**
*   function to print tree scructure level by level
*   
*   @param Root node 
*   @return void
*/
void binary_tree_level_order_print(Node<int> *node){
    
    /* queue - FIFO */
    std::queue<Node<int> *> que;

    /* push first node into the queue */
    que.push(node);

    while (!que.empty())
    {
        /* Send node data to console */
        std::cout << (*que.front()).data << " ";

        /* if we are not evaluating a leaf add left and right child nodes to queue */
        if((*que.front()).left != nullptr || (*que.front()).right != nullptr){
            Node<int> *left = (*que.front()).left;
            que.push(left);

            Node<int> *right = (*que.front()).right;
            que.push(right);
        }

        /* remove evaluated node from front of queue */
        que.pop();
    }
    std::cout << std::endl;
}


int main() {

    /* Create binary tree scructure */
    Node<int> *root =  new Node<int>(10);
    root->left =  new Node<int>(4);
    root->right =  new Node<int>(16);

    root->left->left =  new Node<int>(2);
    root->left->right =  new Node<int>(5);

    root->right->left =  new Node<int>(13);
    root->right->right =  new Node<int>(20);

    root->left->left->left =  new Node<int>(1);
    root->left->left->right =  new Node<int>(3);

     /* Print binary tree scructure */
    std::cout << "Print Tree: " << std::endl;
    print_tree(root);
    std::cout << "\n" << std::endl;

    /* Print binary tree scructure level by level */
    std::cout << "Level Order Print Tree: " << std::endl;
    binary_tree_level_order_print(root);

    return 0;
}

