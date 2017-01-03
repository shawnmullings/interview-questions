
/** @file get-max-stack.cpp
 *  @brief 
 *
 *  You want to be able to access the largest element in a stack.
 *  You've already implemented this Stack class:
 *  
 *  Use your Stack class to implement a new class MaxStack with a function get_max() that returns the largest element in the stack. get_max() should not remove the item.
 *  
 *  Your stacks will contain only integers.
 *  
 *  class Stack:
 *  
 *  # initialize an empty list
 *  def __init__(self):
 *      self.items = []
 *  
 *  # push a new item to the last index
 *  def push(self, item):
 *      self.items.append(item)
 *  
 *  # remove the last item
 *  def pop(self):
 *      # if the stack is empty, return None
 *      # (it would also be reasonable to throw an exception)
 *      if not self.items: 
 *          return None
 *      return self.items.pop()
 *  
 *  # see what the last item is
 *  def peek(self):
 *      if not self.items: 
 *          return None
 *      return self.items[-1]
 *  
 *  @author Shawn Mullings (@shawnmullings)
 *  @bug No known bugs.
 */


/* -- Includes -- */

#include <iostream>
#include <stack>


class MaxStack{
    private:
        int maxElement;
        int minElement;
        std::stack<int> data;

    public:
        /** 
        *
        *   Constructor
        *
        */
        MaxStack(){
            maxElement = 0;
            minElement = 1000000;
        }

        /** 
        *
        *   Destructor
        *
        */
        ~MaxStack(){}

        /** 
        *
        *   Add element to stack container
        *
        *   param int param
        */
        void push(int val){
            /* Calculate maximum element */
            maxElement = (val > maxElement) ? val : maxElement;

            /* Calculate minimum element */
            minElement = (val < minElement) ? val : minElement;

            /* Add element to stack */
            data.push(val);
        }

        /** 
        *
        *   Remove top stack element 
        *
        */
        void pop(){

            /* Remove top stack element */
            data.pop();
        }

        /** 
        *
        *   Access top stack element 
        *
        *   return last/top stack element
        */
        int peek(){

            return data.top();
        }
        /** 
        *
        *   Get max stack element 
        *
        *   return last/top stack element
        */
        int get_max(){ return maxElement; }
};


int main(int argc, char const *argv[])
{
    /* Create MaxStack object */
    MaxStack stk;

    /* Add items to MaxStack object */
    stk.push(30);
    stk.push(4);
    stk.push(300);
    stk.push(51);
    stk.push(16);
    stk.push(1);
    stk.push(50);

    /* Get max element */
    std::cout << "Largest element in the stack: " << stk.get_max() << std::endl;

	return 0;
}

