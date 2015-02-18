/**
*  @file doublylinkedlist.cpp   Implementation of Doubly Linked List.
*
*  @brief Definition of all the functions of DoublyLinkedList in 
*         order to support the functionality of the Playlistand
*         interact with it using the functions of Node class.
*         Reference: www.cplusplus.com for std::string functions.
*
*  @author Diney Wankhede
*  @date 1/26/15.
*/

#include <string>
#include "doublylinkedlist.h"

using std::string;

/**
 *  Constructor of private Node class
 *  Initilization when memory is allocated
 */

DoublyLinkedList::Node::Node(string s)
{
   data = new string(s);
   next = NULL;
   prev = NULL;
}

/**
 *  Destructor definition of drivate Node class
 *
 */

DoublyLinkedList::Node::~Node()
{
  delete data;
}

/**
 *  Constructor definition for doublylinkedlist Class.
 *  Initilization when memory is allocated.
 */

DoublyLinkedList::DoublyLinkedList()
{
   head = NULL;
   tail = NULL;
   current = NULL;
}

/**
 *  Destructor definition for doublylinkedlist Class
 *  deallocation of memory at the end of scope.
 */

DoublyLinkedList::~DoublyLinkedList()
{
   while (head)
   {
      current = head;
      head = head->next;
      delete current;
   }
}

/**
 *  Function to fetch string pointer data from the
 *  objects of Node.
 *  IN: None
 *  OUT: Returns by string reference of data
 */

const string& DoublyLinkedList::getData()
{
   return *(current->data);
}

/**
 *  Function which insert a new Node with string data
 *  after the current song pointer.
 *  IN: song string to be inserted by reference
 *  OUT: Doesn't return anything
 */

void DoublyLinkedList::insertAfter(string &s)
{
   Node* temp;
   Node* newNode = new Node(s);     //Constructor used to assign s to data.
   if (head == NULL)                //Inserting as first node.
   {
      head = newNode;
      tail = head;
      current = head;
   }
   else if (current->next == NULL)  //Inserting after last node
   {
      newNode->prev = current;
      current->next = newNode;
      tail = newNode;
      current = newNode;
   }
   else                             //Inserting as a middle node.
   {
      temp = current->next;
      temp->prev = newNode;
      current->next = newNode;
      newNode->prev = current;
      newNode->next = temp;
      current = newNode;
   }
}

/**
 *  Function which insert a new Node with string data
 *  before the current song pointer.
 *  IN: song string to be inserted by reference.
 *  OUT: Doesn't return anything.
 */

void DoublyLinkedList::insertBefore(string &s)
{
   Node* temp;
   Node* newNode = new Node(s);
  
   if (head == NULL)                  //Inserting as first node.
   {                                  //No initial node.
      head = newNode;
      tail = head;
      current = head;
   }
   else if (current->prev == NULL)   //Current pointing to first/head node.
   {                                 //Inserting before first node.
      newNode->next = head;
      current->prev = newNode;
      head = newNode;
      current = newNode;
   }
   else                              //Inserting at any other position.
   {
      temp = current->prev;
      newNode->next = current;
      newNode->prev = temp;
      temp->next = newNode;
      current->prev = newNode;
      current = newNode;
   }
}

/**
 *  Function which appends(adds) a new Node with string data
 *  to the end(tail) of the doubly linked list.
 *  IN: song string to be inserted by reference
 *  OUT: Doesn't return anything
 */

void DoublyLinkedList::append(string &s)
{
   if (head == NULL)                    //first node in the linkedlist
   {
      Node* newNode=new Node(s);
      head = newNode;
      tail = head;
      current = head;
   }
   else
   {
      current = head;
      while (current->next != NULL)    //Traversing till the end of linkedlist
      {
         current = current->next;
      }
      Node* newNode=new Node(s);
      newNode->next = NULL;
      newNode->prev = current;
      current->next = newNode;
      tail = newNode;
      current = newNode;
   }
}

/**
 *  Function which checks if the linked list has
 *  atleast one node or not.
 *  IN: None(uses private variable head.
 *  OUT: return bool-true if linked list is empty or
 *       false if it has atleast one Node
 */

bool DoublyLinkedList::empty()
{
   if (head==NULL)
   {
      return true;
   }
   else
   {
      return false;
   }
}

/**
 *  Function which checks if the linked list has
 *  the node with the data which has been passed by reference.
 *  IN: song string to be found by reference
 *  OUT: returns boolean type true if linked list has the input data or
 *       false if it does not have the input string data
 */

bool DoublyLinkedList::find(string& s)
{
   if (s[0] == '\0')
   {
      return false;
   }
   Node *temp = head;
   
   while(!empty())
   {
      if(*(temp->data) == s)    //Comapring string s with data
      {
         current = temp;
         return true;
      }
      else
      {
         temp = temp->next;
      }
   }
   return false;
}

/**
 *  Function which checks if the linked list has
 *  a node present after it. If yes,it moves the current to
 *  the next node else it does nothing.
 *  IN: None
 *  OUT: returns boolean type true if linked list has a
 *        node after it else false if next node is not present.
 */

bool DoublyLinkedList::next()
{
   if (!empty())
   {
      if (current->next != NULL)
      {
         current = current->next;
         return true;
      }
      else
         return false;
   }
   return false;
}

/**
 *  Function which checks if the linked list has a node
 *  present before it. If yes,it moves the current to
 *  the previous node else it does nothing.
 *  IN: None
 *  OUT: Returns boolean type true if linked list has a
 *       node before it else false if next node is  not present.
 */

bool DoublyLinkedList::prev()
{
   if (!empty())
   {
      if (current->prev != NULL)
      {
         current = current->prev;
         return true;
      }
      else
         return false;
   }
   return false;
}

/**
 *  Function which removes the node having the data being passed 
 *  as argument.
 *  IN: String song by reference which is to be removed
 *  OUT: Removes the node from linked list. Returns nothing.
 */

void DoublyLinkedList::remove(string& s)
{
   Node *temp,*temp2;
   temp = head;
   
   while(temp != NULL)
   {
      if(*(temp->data) == s)
      {
         if(temp->prev == NULL && temp->next ==  NULL)//Removing single node
         {
            delete (temp);
            head = NULL;
            tail = NULL;
            current = NULL;
            break;
         }
         else if(temp->prev == NULL)               //Check if it is Head node
         {
            temp2 = temp;
            temp = temp->next;
            temp->prev = NULL;
            head = temp;
            delete(temp2);
            current = temp;
            break;
         }
         else if(temp->next == NULL)               //Check if it is Tail Node
         {
            temp2 = temp;
            temp = temp->prev;
            temp->next = NULL;
            tail = temp;
            delete(temp2);
            current = temp;
            break;
         }
         else if (temp->next != NULL && temp->prev != NULL)
         {                                         //Deleting Middle Node
            temp2 = temp;
            temp = temp->prev;
            temp->next = temp2->next;
            temp2->next->prev = temp;
            delete(temp2);
            current = temp->next;
            break;
         }
      }
      temp = temp->next;
   }
}

/**
 *  Function which moves current pointer to the beginging(head)
 *  of the list if there exists one.
 *  IN: None
 *  OUT: None.Moves current pointer to head of linked list.
 */

void DoublyLinkedList::begin()
{
   if (!empty())
   {
      current = head;
   }
}

/**
 *  Function which moves current pointer to the beginging(head)
 *  of the list if there exists one.
 *  IN: None
 *  OUT: None.Moves current pointer to head of linked list.
 */

void DoublyLinkedList::end()
{
   if (!empty())
   {
      current = tail;
   }
}

