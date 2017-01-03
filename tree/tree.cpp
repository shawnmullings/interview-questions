
/** @file tree.cpp
 *  @brief 
 *
 *  Binary tree
 *
 *  @author Shawn Mullings (@shawnmullings)
 *  @bug No known bugs.
 */


/* -- Includes -- */

#include <iostream>
#include <math.h>

/**
*   Node object
*/
template <class T>
struct Node {
    T data;
    Node *left;
    Node *right;

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
*   Binary tree object Template <class T>
*/
template <class T>
class BinaryTree {

    private:

    // Tree root Node object
    Node<T> *root;

    /**
    *   helper function to add node to tree scructure
    *   
    *   @param node value 
    *   @return void
    */
    void _addHelperFunc(Node<T> *root, T val) {
        if (root->data > val) {
            if (!root->left) {
                root->left = new Node<T>(val);
            } else {
                _addHelperFunc(root->left, val);
            }
        } else {
            if (!root->right) {
                root->right = new Node<T>(val);
            } else {
                _addHelperFunc(root->right, val);
            }
        }
    }

    /**
    *   helper function to get the count of leaf nodes in a tree scructure
    *   
    *   @param node 
    *   @return Leaf count
    */
    int _leafCountFunc(Node<T> *node)
    {
      if (node == nullptr)      
        return 0;
      if(node->left == nullptr && node->right == nullptr)      
        return 1;            
      else
        return _leafCountFunc(node->left) + _leafCountFunc(node->right);      
    }

    /**
    *   helper function to print tree scructure
    *   
    *   @param Root node 
    *   @return void
    */
    void _printHelperFunc(Node<T> *root) {
        if (!root) return;
        _printHelperFunc(root->left);
        std::cout << root->data << ' ';
        _printHelperFunc(root->right);
    }

    /**
    *   helper function to sum node within tree scructure
    *   
    *   @param Root node 
    *   @return node count
    */
    int _countHelperFunc(Node<T> *root) {
        if (!root) return 0;
        else return 1 + _countHelperFunc(root->left) + _countHelperFunc(root->right);
    }

    /**
    *   helper function to sum leaf nodes within tree scructure
    *   
    *   @param node 
    *   @return leaf count
    */
    int countLeavesHelperFunc(Node<T> *node){
      if( node == nullptr )
        return 0;
      if( node->left == nullptr && node->right == nullptr ) {
        return 1;
      } else {
        return countLeavesHelperFunc(node->left) + countLeavesHelperFunc(node->right);
      }
    }

    /**
    *   helper function to calculate tree scructure levels
    *   
    *   @param Root node 
    *   @return void
    */
    int _heightHelperFunc(Node<T> *root) {
        if (!root) return 0;
        else return 1 + std::max(_heightHelperFunc(root->left), _heightHelperFunc(root->right));
    }

    /**
    *   helper function to calcutlate longest path to tree scructure leaves
    *   
    *   @param node value 
    *   @return void
    */
    void _printMaxPathHelperFunc(Node<T> *root) {
        if (!root) return;
        std::cout << root->data << ' ';
        if (_heightHelperFunc(root->left) > _heightHelperFunc(root->right)) {
            _printMaxPathHelperFunc(root->left);
        } else {
            _printMaxPathHelperFunc(root->right);
        }
    }
    /**
    *   helper function to print tree scructure nodes according to the "bottom-up" postorder traversal
    *   
    *   @param node value 
    *   @return void
    */
    void printPostorder(struct Node* node) { 
      if (node == NULL) return;
      // first recur on both subtrees 
      printTree(node->left); 
      printTree(node->right);

      // then deal with the node 
      printf("%d ", node->data); 
    } 

    /**
    *   helper function to add node to tree scructure
    *   
    *   @param parent node
    *   @param current node 
    *   @param value 
    *   @return void
    */
    bool _deleteValueHelperFunc(Node<T>* parent, Node<T>* current, T value) {
        if (!current) return false;
        if (current->data == value) {
            if (current->left == nullptr || current->right == nullptr) {
                Node<T>* temp = current->left;
                if (current->right) temp = current->right;
                if (parent) {
                    if (parent->left == current) {
                        parent->left = temp;
                    } else {
                        parent->right = temp;
                    }
                } else {
                    this->root = temp;
                }
            } else {
                Node<T>* validSubs = current->right;
                while (validSubs->left) {
                    validSubs = validSubs->left;
                }
                T temp = current->data;
                current->data = validSubs->data;
                validSubs->data = temp;
                return _deleteValueHelperFunc(current, current->right, temp);
            }
            delete current;
            return true;
        }
        return _deleteValueHelperFunc(current, current->left, value) ||
               _deleteValueHelperFunc(current, current->right, value);
    }

    public:
    /**
    *   Delete
    */
    ~BinaryTree(){}

    /**
    *   Add node to tree scructure
    *   
    *   @param node value 
    *   @return void
    */
    void addNode(T val) {
        if (root) {
            this->_addHelperFunc(root, val);
        } else {
            root = new Node<T>(val);
        }
    }

    /**
    *   Function to get the count of leaf nodes in a binary tree
    *   
    *   @param node 
    *   @return void
    */
    int leafCount()
    {
        return _leafCountFunc(this->root);     
    }

    /**
    *   Print tree scructure to console
    * 
    *   @return void
    */
    void printTree() {
        _printHelperFunc(this->root); 
    }

    /**
    *   Sum all node within tree scructure
    * 
    *   @return Sum of all node in tree structure
    */
    int count() {
        return _countHelperFunc(this->root);
    }

    /**
    *   Calculate tree scructure level height
    *   
    *   @return tree scructure level height
    */
    int height() {
        return _heightHelperFunc(this->root);
    }

    /**
    *   Calcutlate longest path to tree scructure leaves
    *   
    *   @return void
    */
    void maxPath() {
        _printMaxPathHelperFunc(this->root);
    }

    /**
    *   Remove node value
    *   
    *   @param val Node object 
    *   @return void
    */
    bool deleteNodeValue(T value) {
        return this->_deleteValueHelperFunc(NULL, this->root, value);
    }
};

int main() {

    BinaryTree<char> *bt = new BinaryTree<char>();
    bt->addNode('a');
    bt->addNode('b');
    bt->addNode('c');
    bt->addNode('d');
    bt->addNode('e');
    bt->addNode('f');
    bt->printTree();
    std::cout << std::endl;

    std::cout << "Leaf count: " << bt->leafCount() << std::endl;


    std::cout << "Nodes count: " << bt->count();
    std::cout << std::endl;

    std::cout << "Height: " << bt->height();
    std::cout << std::endl;

    std::cout << "Max path: ";
    bt->maxPath();
    std::cout << std::endl;

    bt->deleteNodeValue('a');
    std::cout << "a removed: ";
    bt->printTree();
    std::cout << std::endl;

    std::cout << "b removed: ";
    bt->deleteNodeValue('b');
    bt->printTree();
    std::cout << std::endl;

    std::cout << "c removed: ";
    bt->deleteNodeValue('c');
    bt->printTree();
    std::cout << std::endl;

    std::cout << "d removed: ";
    bt->deleteNodeValue('d');
    bt->printTree();
    std::cout << std::endl;

    std::cout << "e removed: ";
    bt->deleteNodeValue('e');
    bt->printTree();
    std::cout << std::endl;
    
    std::cout << "f removed: ";
    bt->deleteNodeValue('f');
    bt->printTree();
    std::cout << std::endl;
    

    return 0;
}