
/** @file heap.cpp
 *  @brief 

 *  Heap
 *  
 *  @author Shawn Mullings (@shawnmullings)
 *  @bug No known bugs.
 */


/* -- Includes -- */

#include <iostream>
#include <vector>
#include <iterator>

class Heap {
private:
    /**
    *   XXXXXXXXXXXX
    *   
    *   @param
    *   @return void
    */  
    void heapifyup(int index)
    {    
        //std::cout << "index = " << index << std::endl;
        //std::cout << "parent(index) = " << parent(index) << std::endl;
        //std::cout << "heap[parent(index)] = " << heap[parent(index)] << std::endl;
        //std::cout << "heap[index] = " << heap[index] << std::endl;
        while ( ( index > 0 ) && ( parent(index) >= 0 ) &&
                ( heap[parent(index)] > heap[index] ) )
        {
            int tmp = heap[parent(index)];
            heap[parent(index)] = heap[index];
            heap[index] = tmp;
            index = parent(index);
        }
    }
    /**
    *   XXXXXXXXXXXX
    *   
    *   @param
    *   @return void
    */
    void heapifydown(int index)
    {     
        //std::cout << "index = " << index << std::endl;
        //std::cout << "left(index) = " << left(index) << std::endl;
        //std::cout << "right(index) = " << right(index) << std::endl;
        int child = left(index);
        if ( ( child > 0 ) && ( right(index) > 0 ) &&
             ( heap[child] > heap[right(index)] ) )
        {
            child = right(index);
        }
        if ( child > 0 )
        {
            int tmp = heap[index];
            heap[index] = heap[child];
            heap[child] = tmp;
            heapifydown(child);
        }
    }
    /**
    *   XXXXXXXXXXXX
    *   
    *   @param
    *   @return void
    */    int left(int parent)
    {
        int i = ( parent << 1 ) + 1; // 2 * parent + 1
        return ( i < heap.size() ) ? i : -1;
    }
    /**
    *   XXXXXXXXXXXX
    *   
    *   @param
    *   @return void
    */
    int right(int parent)
    {
        int i = ( parent << 1 ) + 2; // 2 * parent + 2
        return ( i < heap.size() ) ? i : -1;
    }
    /**
    *   XXXXXXXXXXXX
    *   
    *   @param
    *   @return void
    */
    int parent(int child)
    {
        if (child != 0)
        {
            int i = (child - 1) >> 1;
            return i;
        }
        return -1;
    } 
private:
    //
    std::vector<int> heap;
public:
    /**
    *   XXXXXXXXXXXX
    *   
    *   @param
    *   @return void
    */
    Heap(){};
    /**
    *   XXXXXXXXXXXX
    *   
    *   @param
    *   @return void
    */
    ~Heap(){};
    /**
    *   XXXXXXXXXXXX
    *   
    *   @param
    *   @return void
    */
    int size() { return heap.size(); }
    /**
    *   XXXXXXXXXXXX
    *   
    *   @param
    *   @return void
    */
    void insert(int element)
    {
        heap.push_back(element);
        heapifyup(heap.size() - 1);
    }
    /**
    *   XXXXXXXXXXXX
    *   
    *   @param
    *   @return void
    */
    int deletemin()
    {
        int min = heap.front();
        heap[0] = heap.at(heap.size() - 1);
        heap.pop_back();
        heapifydown(0);
        return min;
    }
    /**
    *   XXXXXXXXXXXX
    *   
    *   @param
    *   @return void
    */
    void print()
    {
        std::vector<int>::iterator pos = heap.begin();
        std::cout << "Heap = ";
        while ( pos != heap.end() ) {
            std::cout << *pos << " ";
            ++pos;
        }
        std::cout << std::endl;
    }   
};



int main()
{
    // Create the heap
    Heap* myheap = new Heap();
    myheap->insert(700);
    myheap->print();
    myheap->insert(500);
    myheap->print();
    myheap->insert(100);
    myheap->print();
    myheap->insert(800);
    myheap->print();
    myheap->insert(200);
    myheap->print();
    myheap->insert(400);
    myheap->print();
    myheap->insert(900);
    myheap->print();
    myheap->insert(1000);
    myheap->print();
    myheap->insert(300);
    myheap->print();
    myheap->insert(600);
    myheap->print();

    // Get priority element from the heap
    int heapSize = myheap->size();
    for ( int i = 0; i < heapSize; i++ )
        std::cout << "Get min element = " << myheap->deletemin() << std::endl;

    // Cleanup
    delete myheap;
}
