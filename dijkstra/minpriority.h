/**
 *  @file: minpriority.h
 *  @desc: Header file which inlcudes functions necessary for implmenting
 *         minimum priority queue.
 *
 *  @author: Diney Wankhede
 *  @date: 4/22/15
 *
 */

#ifndef ____minpriority__
#define ____minpriority__

#include <string>
#include <vector>


using std::string;
using std::vector;

class MinPriorityQ
{
public:
   MinPriorityQ();              // Constructor
   ~MinPriorityQ();             //Destructor
   
   void insert(string,int);     //Function to insert an entry into heap
   void decreaseKey(string,int);//Descreases key when new key is input
   string extractMin();         //Extracts minimum from queue and removes it
   bool isMember(string);       //Checks if the input id is present or not
   
private:
   class Element                //Private Class
   {
   public:
      Element(string,int);      //Copy constructor
      ~Element();               //Destructor
      string id;                //String id to store 
      int key;                  //Key int which is to be used and compared
   };
   
   void buildMinHeap();         //Function which builds heap after alteration
   void minHeapify(int);        //Called by buildMaxHeap () 
   int parent(int);             //Fetches the parent of input
   int left(int);               //Fetches the left child of input
   int right(int);              //Fecthes the right chicldof input

   vector<Element*> minHeap;    //Vector of type element which stores Heap
};

#endif /* defined(____minpriority__) */
