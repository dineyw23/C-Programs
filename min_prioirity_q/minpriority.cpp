/**
 *  @file: minpriority.cpp
 *  @desc: This file has implementation of all the functions required to 
 *         maintain minpriority queue using minheap. Most of the functions 
 *         written as per the implementation of Cormen.
 *
 *  @author: Diney Wankhede
 *  @date:  4/22/15
 *
 *
 */

#include "minpriority.h"
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <math.h>

using std::string;
using std::cout;
using std::cin;
using std::stringstream;
using std::endl;
using std::swap;
using std::to_string;

/**
 * Constructor for class MinPriorityQ.
 *
 *
 */

MinPriorityQ::MinPriorityQ ()
{

}

/**
 * Destructor for class MinPriorityQ.
 *
 *
 */

MinPriorityQ::~MinPriorityQ()
{
   for(vector<Element*>::iterator it = minHeap.begin();
      it != minHeap.end();it++)
   {
      delete *(it);
   }

}

/**
 * Desc: Constructor for setting the id and key to the new Element which
 *       will be insertd.
 *
 *
 */

MinPriorityQ::Element::Element(string new_id,int new_key)
{
  id = new_id ;
  key = new_key;
}

/**
 * Destructor for Element class.
 *
 *
 */


MinPriorityQ::Element::~Element()
{

}

/**
 * Desc: Function to insert an element into the queue. Similar to algorithm
 *       in Cormen.
 *
 * In:   String - Id - User input of string
 *       Integer - Key - Key of type integer to min pq
 *
 * Out:  None - Creates new Element and pushes in the vector. Creates minHeap.
 */

void MinPriorityQ::insert(string id, int key)
{
   Element* insert = new Element(id,key);
   minHeap.push_back(insert);
   decreaseKey(id,key);
}

/**
 * Desc: Function to decrease the key as and when an update is required.
 *
 * In:   String - Id - User input of string
 *       Integer - Key - Key of type integer to min pq
 *
 *
 *
 */

void MinPriorityQ::decreaseKey(string id,int key)
{
   int i = 0;
   int j = 0;
   for(vector <Element*>::iterator it = minHeap.begin(); it != minHeap.end();
         it++)
   {
      if((*it)->id == id)
      {
         i = j;
      }
      j++;
   }

   if(key > minHeap[i]->key)
      return;
   minHeap[i]->key = key;
   
   while(i > 0 && (minHeap[parent(i)]->key) > minHeap[i]->key)
   {
      swap(minHeap[i] , minHeap[parent(i)]);
      i = parent(i);
   }
}

/**
 * Desc: This Function extracts and returns a string which is the minimum
 *       and removes that particular element from the queue.
 *
 * In:   None - Using the member minHeap.
 * Out:  string - Returns the minimum string id which is later printed.
 */

string MinPriorityQ::extractMin()
{
   if(minHeap.size() < 1)       //If size 0, return empty.
   {
      string null = "empty";
      return null;
   }
   string min = minHeap[0]->id; //The minimum will be at 1st position always
   minHeap[0] = NULL;
   minHeap.erase(minHeap.begin());
   if((int)minHeap.size() > 1)
      minHeapify(0);             //Maintaining heap property after extract.
   return min;
}

/**
 * Desc: This function checks if the input id is present in the queue or not.
 *
 * In:   String - id - The id which is to be searched.
 * Out:  boolean - true if there exists input string in the queue else false.
 *
 */

bool MinPriorityQ::isMember(string id)
{
   for(vector<Element*>::iterator it = minHeap.begin();
         it != minHeap.end();it++)
   {
      if((*it) -> id == id)
         return true;
   }
   return false;
}

/**
 * Desc: This function is written as per in Cormen. It maintains the minHeap
 *       property on the in input integer.
 *
 * In:   Integer - position of Element which is to be checked.
 * Out:  Returns nothing - MinHeap proprty is maintained on input. 
 *
 */

void MinPriorityQ::minHeapify(int i)
{
   int l = left(i);
   int r = right(i);
   int smallest = i;

   if(l < (int)minHeap.size() && minHeap[l]->key < minHeap[i]->key)
   {
      smallest = l;
   }
   else 
   {
      smallest = i;
   }
   if(r < (int)minHeap.size() && minHeap[r]->key < minHeap[smallest]->key)
   {
      smallest = r;
   }
   if(smallest != i)
   {
      swap(minHeap[i],minHeap[smallest]);
      if((int)minHeap.size() > 1)
         minHeapify(smallest);
   }
}

/**
 * Desc: This function builds Min Heap by maintaining min Heap property.
 *
 * In:   None. 
 * Out:  Returns nothing - Min Heap property of entire heap.
 *
 */

void MinPriorityQ::buildMinHeap()
{
   if(minHeap.size() > 1)
   {
      for(int i = floor((int)minHeap.size()/2); i >= 0; i--)
         minHeapify(i);
   }
}

/**
 * Desc: This Function looks for the parent of input integer.
 * 
 * In:   Integer - The input integer position whose parent is required.
 * Out:  Integer - The parent's position of input in the heap.
 *
 */

int MinPriorityQ::parent(int i)
{
   return (floor(i/2));
}

/**
 * Desc: This Function looks for the left child of input integer.
 * 
 * In:   Integer - The input integer position whose left child is required.
 * Out:  Integer - The left child's position of input in the heap.
 *
 */

int MinPriorityQ::left(int i)
{
   return (2*i);
}

/**
 * Desc: This Function looks for the right child of input integer.
 * 
 * In:   Integer - The input integer position whose right child is required.
 * Out:  Integer - The right child's position of input in the heap.
 *
 */

int MinPriorityQ::right(int i)
{
   return (2*i+1);
}
