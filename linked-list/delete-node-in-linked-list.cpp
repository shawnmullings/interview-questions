
/** @file delete-node-in-linked-list.cpp
 *  @brief 
 *
 *  A linked list is a list constructed using pointers. It is not fixed in
 *  size and could grow and shrink while the program is running.
 *  
 *  A typical defination of list nodes contains at least two parts, both the
 *  content or date of each element and the pointer to the next element,
 *  which is shown in the figure below.
 * 
 *  @author Shawn Mullings (@shawnmullings)
 *  @bug No known bugs.
 */


/* -- Includes -- */

#include <iostream>
#include <cstddef>

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
    list.remove(3);
    /* output the result */
    std::cout << "After removing: " << std::endl;
    list.traverse_and_print();
    
    return 0;
}

