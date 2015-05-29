/**
*  @file doublylinkedlist.h Declaration of DoublyLinkedList for Playlist.
*
*  @brief 
*       Implementation of DoublyLinkedList and Node class to 
*       support the functionality of the Playlist
* 
*  @author Diney Wankhede
*  @date   1/26/15.
*/

#ifndef ____doublylinkedlist__
#define ____doublylinkedlist__

#include <stdio.h>
using std::string;

class DoublyLinkedList
{
public:
   DoublyLinkedList();              //Constructor for DoublyLinkedist Class
   ~DoublyLinkedList();             //Destructor for DoublyLinkedist Class
   
   bool empty();                    //Checks if the list in empty
   void append(string& s);          //Adds a node to end of list
   void insertBefore(string& s);    //Inserts node before current
   void insertAfter(string& s);     //Inserts node after the current
   void remove(string& s);          //removes the first occurance of song
   void begin();                    //Current points to head
   void end();                      //Current points to tail
   bool next();                     //Current moves to next node
   bool prev();                     //Current moves to previous node
   bool find(string& s);            //Finds the song in the linkedlist
   const string& getData();         //Current data is fetched
    
private:
   class Node
   {
   public:
      Node* next;
      Node* prev;
      string* data;
      Node(string s);              //Parameterized Constructor for Node Class
      ~Node();                     //Destructor for Node Class
   };
    
   Node* head;                     //Pointer to head
   Node* tail;                     //Pointer to tail
   Node* current;                  //Pointer to current
  };

#endif /* defined(____doublylinkedlist__) */
