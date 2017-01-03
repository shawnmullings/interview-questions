
/** @file reverse-linked-list.cpp
 *  @brief 
 *
 *  Hooray! It's opposite day. Linked lists go the opposite way today.
 *  Write a function for reversing a linked list ↴ . Do it in-place ↴ .
 *  
 *  Your function will have one input: the head of the list.
 *  
 *  Your function should return the new head of the list.
 *  
 *  Here's a sample linked list node class:
 *  
 *   class LinkedListNode:
 *  
 *      def __init__(self, value):
 *          self.value = value
 *          self.next  = None
 * 
 *  @author Shawn Mullings (@shawnmullings)
 *  @bug No known bugs.
 */


/* -- Includes -- */

#include <iostream>
#include <cstddef>
#include <vector> 

/* definition of the list node class */

class Node
{

public:
    int _data; /* data, can be any data type, but use integer for easiness */
    Node *_pNext; /* pointer to the next node */

    /* Constructors with No Arguments */
    Node(void)
    : _pNext(NULL)
    { }
    
    /* Constructors with a given value */
    Node(int val)
    : _data(val), _pNext(NULL)
    { }
    
    /* Constructors with a given value and a link of the next node */
    Node(int val, Node* next)
    : _data(val), _pNext(next)
    {}
};

/* definition of the linked list class */
class LinkedList
{
private:
    /* pointer of head node */
    Node *_pHead;
    /* pointer of tail node */
    Node *_pTail;
    
public:
    /* Constructors with a given value of a list node */
	LinkedList(int val)
	{
	    /* Create a new node, acting as both the head and tail node */
	    _pHead = new Node(val);
	    _pTail = _pHead;
	}

    /* Destructor */
	~LinkedList()
	{
	    /*
	     * Leave it empty temporarily.
	     * It will be described in detail in the example "How to delete a linkedlist".
	     */
	}

	Node * get_Root(){

		return _pHead;
	}
	    
    /* Function to append a node to the end of a linked list */
	void tailAppend(int val)
	{
	    /* The list is empty? */
	    if (_pHead == NULL) {
	        /* the same to create a new list with a given value */
	        _pTail = _pHead = new Node(val);
	    }
	    else
	    {
	        /* Append the new node to the tail */
	        _pTail->_pNext = new Node(val);
	        /* Update the tail pointer */
	        _pTail = _pTail->_pNext;
	    }
	}
    
    /* Remove a node with a specific value if it exists */
	void remove(int val)
	{
	    Node *pPre = NULL, *pDel = NULL;
	    
	    /* Check whether it is the head node?
	     if it is, delete and update the head node */
	    if (_pHead->_data == val) {
	        /* point to the node to be deleted */
	        pDel = _pHead;
	        /* update */
	        _pHead = pDel->_pNext;
	        delete pDel;
	        return;
	    }
	    
	    pPre = _pHead;
	    pDel = _pHead->_pNext;
	    
	    /* traverse the list and check the value of each node */
	    while (pDel != NULL) {
	        if (pDel->_data == val) {
	            /* Update the list */
	            pPre->_pNext = pDel->_pNext;
	            /* If it is the last node, update the tail */
	            if (pDel == _pTail) {
	                _pTail = pPre;
	            }
	            delete pDel; /* Here only remove the first node with the given value */
	            break; /* break and return */
	        }
	        pPre = pDel;
	        pDel = pDel->_pNext;
	    }
	}
    
    /* Traversing the list and printing the value of each node */
	void traverse_and_print()
	{
	    Node *p = _pHead;
	    
	    /* The list is empty? */
	    if (_pHead == NULL) {
	        std::cout << "The list is empty" << std::endl;
	        return;
	    }
	    
	    std::cout << "LinkedList: ";
	    /* A basic way of traversing a linked list */
	    while (p != NULL) { /* while there are some more nodes left */
	        /* output the value */
	        std::cout << p->_data << " ";
	        /* The pointer moves along to the next one */
	        p = p->_pNext;
	    }
	    std::cout << std::endl;
	}
};


void reverse_list(Node *node){
	/* Since we will be using pointer to the original nodes "shuffle_list" does its work in-place. */

	/*  Check that the first node is not NULL */
	if (node == nullptr)
		return;

	std::vector<Node *> vec; 	/*  Node container */
	Node *currentNode = node;	/*  Current node being evaluated */

	/*  Traverse list collecting nodes into vectoer container */
	std::cout << "unshuffled list contains: ";
	while(currentNode != nullptr){
		std::cout << " " << currentNode->_data << "->";
		vec.insert(vec.begin(), currentNode);
		currentNode = currentNode->_pNext;
	}
	std::cout << " end list" << std::endl;

	/* loop through vector linking shuffled nodes and output new list. */
	std::cout << "shuffled list contains: ";
	for (std::vector<Node *>::iterator it=vec.begin(); it!=vec.end(); ++it){
		(*it)->_pNext = (*it+1);
		std::cout << " " << (*it)->_data << "->";
	}

	/*  Point last node's next pointer to NULL signifying this is the end of the list */
	Node *lastItem = vec.back();
	lastItem->_pNext = nullptr;

	std::cout << " end list" << std::endl;
}



int main(int argc, const char * argv[])
{
    /* Create a list with only one node */
    LinkedList list(1);
    /* Append 3 nodes to the end of the list */
    list.tailAppend(2);
    list.tailAppend(3);
    list.tailAppend(4);
    std::cout << "Before removing: " << std::endl;
    /* output the result */
    list.traverse_and_print();
    
    /* Remode the node with value 3 */
    std::cout << "Trying to remove the node with value 3" << std::endl;
    //list.remove(3);
    /* output the result */
    std::cout << "After removing: " << std::endl;
    list.traverse_and_print();

    reverse_list(list.get_Root());
    
    return 0;
}


