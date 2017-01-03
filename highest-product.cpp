/** @file highest-product.cpp
 *  @brief 
 *  
 *  Given a list_of_ints, find the highest_product you can get from three of the integers.
 *  The input list_of_ints will always have at least three integers.
 *  
 *  @author Shawn Mullings (@shawnmullings)
 *  @bug No known bugs.
 */


/* -- Includes -- */

#include <iostream>
#include <algorithm>
#include <cstddef>
#include <random>
#include <ctime>
#include <functional>
#include <numeric>
#include <vector>
#include <iterator>


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
public:
	/* pointer of head node */
    Node *_pHead;
    /* pointer of tail node */
    Node *_pTail;

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
	void push_back(int val)
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


void highest_product(Node *node){
	/* Since we will be using pointer to the original nodes "shuffle_list" does its work in-place. */

	/*  Check that the first node is not NULL */
	if (node == nullptr)
		return;

	std::vector<Node *> vec; 	/*  Node container */
	Node *currentNode = node;	/*  Current node being evaluated */

	/*  Traverse list collecting nodes into vectoer container */
	std::cout << "list contains: ";
	while(currentNode != nullptr){
		std::cout << " " << currentNode->_data << "->";
		vec.push_back(currentNode);
		currentNode = currentNode->_pNext;
	}
	std::cout << " end list" << std::endl;

	/*  Sort vector to get 3 highest values */
	std::sort( vec.begin(), vec.end() );

	/* Multipy 3 highest values to get the  highest product*/
	int ret;

	ret = (vec.back()-2)->_data * (vec.back()-1)->_data * vec.back()->_data;

	std::cout << "highest product: " << ret << std::endl;
}


int main(int argc, const char * argv[])
{
    /* Create a list with only one node */
    LinkedList list(1);

    /* Append nodes to the end of the list */
    list.push_back(2);
    list.push_back(3);
    list.push_back(4);
    list.push_back(5);
    list.push_back(6);
    list.push_back(7);
    list.push_back(8);

    /* Shuffle single linked list in-place */
    highest_product(list._pHead);
    
    return 0;
}

