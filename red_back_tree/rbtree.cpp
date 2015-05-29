/**
 * @file: rbapp.cpp
 * @desc: This file contains implementation of all the functions required
 *	  for creating a rbtree and manipulating the rbtree generated
 *	  by user commands.
 *	  Functions are implemented using functions from Cormen.
 *
 * @author: Diney Wankhede
 * @date:   04/02/2015
 *
 */

#include <iostream>
#include <iomanip>
#include "rbtree.h"

using std::cout;
using std::setw;
using std::endl;

/**
 *  Default constructor of RBTree class. Initializing nil and root.
 *
 */

RBTree::RBTree()
{
   nil = new Node();
   root = nil;
}
 
/**
 * Destructor of RBTree class. Post order traversal to delete entire tree
 * after the program.
 *
 */

RBTree::~RBTree()
{
   postOrderTraversal(root);
   delete nil;
}

/**
 * Constructor of private class Node. This is default constructor
 * which initialized the following members.
 *
 */

RBTree::Node::Node()
{
   key = NULL;
   value = NULL; 
   parent = NULL;
   right = NULL;
   left = NULL;
   color = 'B';
}

/**
 * Desctructor which deallocates the memory given to key and value.
 *
 */

RBTree::Node::~Node()
{
   if(key != NULL)
      delete key;
   if(value != NULL)   
      delete value;
}

/**
 * Parameterized constructor which initializes all members as required.
 * When a new node is called.
 *
 */

RBTree::Node::Node(const string& k,const string& v,Node* nil)
{
   key = new string(k);
   value = new string(v);
   
   parent = nil;
   left = nil;
   right = nil;
   color = 'B';
}

/**
 * Desc: This functions prints out the tree fromt the parameters passed
 *       to it in a reverse inOrder fashion.
 *
 * In:  Node* - Node* from where the tree should be printed.
 *      integer - depth - from where tree should be printed.
 */

void RBTree::reverseInOrderPrint(Node *x, int depth) 
{
   if (x != nil) 
   {
      reverseInOrderPrint(x->right, depth+1);
      cout << setw(depth*4+4) << x->color << " ";
      cout << *(x->key) << " " << *(x->value) << endl;
      reverseInOrderPrint(x->left, depth+1);
   }
}

/**
 * Desc: Public function which is called to insert a new node in the 
 *       red black tree. key and value is passed in here to create a Node.
 *
 * In:   constant string reference of key and value which is passed by the 
 *       user as input.
 * Out:  Creates a new node and calls private mutator rbinsert to place 
 *       the node in the red black tree. Returns nothing.
 */

void RBTree::rbInsert(const string& key, const string& value)
{
   Node* newNode = new Node(key,value,nil); // Calls Parameterized constructor 
   rbInsert(newNode);
}

/**
 * Desc: Private mutator overloaded function which is written as per in 
 *       the Cormen to insert a new node in red black tree.
 *
 * In:   Node* - Node pointer to be inserted in the red black tree.
 * Out:  Returns nothing. Inserts new node in the tree.
 */

void RBTree::rbInsert(Node* z)
{
   Node* y = nil;                //Temporary node* variable
   Node* x = root;               //Temporary node* variable
   
   while (x != nil) 
   {
      y = x;
      if (*(z->key) < *(x->key)) // Places according to key 
      {
         x = x->left;
      }
      else
      {
         x = x->right;
      }
   }
   z->parent = y;
   if (y == nil) 
   {
      root = z;
   }
   else if(*(z->key) < *(y->key))
   {
      y->left = z;
   }
   else
   {
      y->right = z;
   }
   z->left = nil;
   z->right = nil;
   z->color = 'R';
   rbInsertFixup(z);    //Calls the fixup to maintain the tree properties 
}

/**
 * Desc: private mutator function which fixes up the tree properties 
 *       after a successful insert of a new node. As per Cormen.
 *
 * In:  Node* - node pointer which is inserted.
 * Out: void- Returns nothing. Fixes up the properties.  
 *
 */

void RBTree::rbInsertFixup(Node* z)
{
   while (z->parent->color == 'R')
   {
      if (z->parent == z->parent->parent->left)
      {
         Node* y = z->parent->parent->right;
         if (y->color == 'R')
         {
            z->parent->color = 'B';
            y->color = 'B';
            z->parent->parent->color = 'R';
            z = z->parent->parent;
         }
         else if(z == z->parent->right)
         {
            z = z->parent;
            leftRotate(z);
         }
         else
         {
            z->parent->color = 'B';
            z->parent->parent->color = 'R';
            rightRotate(z->parent->parent);
         }
      }
      else
      {
         Node* y = z->parent->parent->left;
         if (y->color == 'R')
         {
            z->parent->color = 'B';
            y->color = 'B';
            z->parent->parent->color = 'R';
            z = z->parent->parent;
         }
         else if(z == z->parent->left)
         {
            z = z->parent;
            rightRotate(z);
         }
         else
         {
            z->parent->color = 'B';
            z->parent->parent->color = 'R';
            leftRotate(z->parent->parent);
         }
      }
   }
   root->color = 'B';
}
   
/**
 * Desc: Private mutator function which manitains the tree balaced by 
 *       restructuring. Left Rotation is performed as per Cormen.
 *
 * In:   Node* - Node pointer on which rotation is performed.
 * Out:  Void - Returns nothing. left rotates on the input node.
 *
 */
   
void RBTree::leftRotate(Node* x)
{
   Node* y;
   y = x->right;
   x->right = y->left;
   if (y->left != nil)
   {
      y->left->parent = x;
   }
   y->parent = x->parent;
   
   if (x->parent == nil)
   {
      root = y;
   }
   else 
   {
      if(x == x->parent->left)
      {
         x->parent->left = y;
      }
      else
      {
         x->parent->right = y;
      }

   }
   y->left = x;
   x->parent = y;
}

/**
 * Desc: Private mutator function which manitains the tree balaced by 
 *       restructuring. Right Rotation is performed as per Cormen.
 *
 * In:   Node* - Node pointer on which rotation is performed.
 * Out:  Void - Returns nothing. Right rotates on the input node.
 *
 */
   
void RBTree::rightRotate(Node* x)
{
   Node* y;
   y = x->left;
   x->left = y->right;
   if (y->right != nil)
   {
      y->right->parent = x;
   }
   y->parent = x->parent;      
   if (x->parent == nil)
   {
      root = y;
   }
   else    
   {
      if(x == x->parent->right)
      {   
         x->parent->right = y;
      }
      else
      {
         x->parent->left = y;
      }
   }
   y->right = x;
   x->parent = y;
}

/**
 * Desc: Public function which locates for the node which is to be 
 *       deleted. Dupicates are also locatated by checking all occrance
 *       of that particular key by using predecessor and successor function.
 *       If Value is matched, duplicates is deleted as well.
 *
 * In:  constant string by reference - key and value of the nodes which
 *      is to be deleted.
 * Out: Returns nothing - locates for the node to be deleted and further
 *      private mutator function is being called.
 */
   
void RBTree::rbDelete(const string& key, const string& value)
{
   if (root == nil)              // Tree doesn't exist 
   {
      return;
   }
   if(root != nil)              // Tree exists
   {
      Node *resultNode = rbTreeSearch(root, key);
      if (resultNode == nil)     // node found points to nil
      {
         return;
      }
      while (resultNode != nil)  //Until all keys(duplicates are looked   
      {
         if(*(resultNode->value) == value)
         {
            rbDelete(resultNode);//deletes the node
            delete(resultNode);  //deallocates its memory
            resultNode = rbTreeSearch(root, key);
         }
         
         Node* pre = resultNode;// Nodes with same key may be present at 
         while( pre != nil)     //predecessors positions.
         {
            pre = rbTreePredecessor(pre);
            if (pre != nil) 
            {
               if((*(pre->key) == key) && (*(pre->value) == value))
               {
                  rbDelete(pre);
                  delete(pre);
                  pre = rbTreeSearch(root, key);
                  
               }
            }
         }		
         
         Node *succ = resultNode; // Nodes with same key may be present at
         while(succ != nil)       //successors positions.
         {
            succ = rbTreeSuccessor(succ);
            if (succ != nil) 
            {
               if((*(succ->key) == key) && (*(succ->value) == value))
               {
                  rbDelete(succ);
                  delete(succ);
                  succ = rbTreeSearch(root, key);        
               }
         
            }
         }
      //Loop untill the value of the node doesnt match the input value
         if(resultNode != nil)
         {
            if(*(resultNode->value) != value)
               break;
         }
      }
   }
}

/**
 * Desc: Private overloaded function to  delete a rbtree node. 
 *       This is as per the Cormen function.
 *  
 * In:   Node* - Node pointer which is to be deleted.
 * Out:  Returns nothing. Deletes the node from tree.
 */

void RBTree::rbDelete(Node* z)
{
   Node* y = z;
   Node* x;
   char ogColor = y->color;
   if (z->left == nil)
   {
      x = z->right;
      rbTransplant(z,z->right);
   }
   else if (z->right == nil)
   {
      x = z->left;
      rbTransplant(z,z->left);
   }
   else
   {
      y = rbTreeMaximum(z->left);   // Predecessor is used
      ogColor = y->color;
      x = y->left;
      if (y->parent == z)
      {
         x->parent = y;
      
      }
      else
      {
         rbTransplant(y,y->left);
         y->left = z->left;
         y->left->parent = y;
      }
      rbTransplant(z,y);
      y->right = z->right;
      y->right->parent = y;
      y->color = z->color;
   }
   if (ogColor == 'B') 
   {
      rbDeleteFixup(x);    //Fixing up the properties after deleting a  node
   }
}

/**
 * Desc: This function performs the fixup after a node is deleted. In order
 *       to maintain the properties of the red black tree. Written as 
 *       per Cormen.
 *
 * In:   Node* - Node pointer whose property is affected after delete.
 * Out:  Nothing - Manages the color of red black tree.
 */

void RBTree::rbDeleteFixup(Node* x)
{
   Node* w;
   while (x !=root && x->color == 'B')
   {
      if (x == x->parent->left) 
      {
         w = x->parent->right;
         if (w->color == 'R')
         {
            w->color = 'B';
            x->parent->color = 'R';
            leftRotate(x->parent);
            w = x->parent->right;
         }
         if (w->left->color == 'B' && w->right->color == 'B')
         {
            w->color = 'R';
            x = x->parent;
         }
         else if (w->right->color == 'B')
         {
            w->left->color = 'B';
            w->color = 'R';
            rightRotate(w);
            w = x->parent->right;
         }
         else
         {
            w->color = x->parent->color;
            x->parent->color = 'B';
            w->right->color = 'B';
            leftRotate(x->parent);
            x = root;
         }
      }
      else
      {
         w = x->parent->left;
         if (w->color == 'R')
         {
            w->color = 'B';
            x->parent->color = 'R';
            rightRotate(x->parent);
            w = x->parent->left;
         }
         if (w->right->color == 'B' && w->left->color == 'B')
         {
            w->color = 'R';
            x = x->parent;
         }
         else if (w->left->color == 'B')
         {
            w->right->color = 'B';
            w->color = 'R';
            leftRotate(w);
            w = x->parent->left;
         }
         else
         {
            w->color = x->parent->color;
            x->parent->color = 'B';
            w->left->color = 'B';
            rightRotate(x->parent);
            x = root;
         }
      }
   }
   x->color = 'B';
}

/**
 * Desc: Trasplant function is a helper function to delete function.
 *       Changes the subtree rooted at a particular to other.
 *
 * In:   2 Node* - first is the which is to be deleted
 *               - second Node pointer is which is to be transplanted.
 *
 * Out: returns nothing - restructes the tree.
 */

void RBTree::rbTransplant(Node* u, Node* v)
{
   if (u->parent == nil)
   {
      root = v;
   }
   else if(u == u->parent->left)
   {
      u->parent->left = v;
   }
   else
   {
      u->parent->right = v;
   }
   v->parent = u->parent;
}



/**
 * Desc: Function which looks out the entire tree to find all the occurance
 *       of the key which is passed to it. Uses tree search,predecessor and 
 *       successor to look through all possible positions for particular key.
 *
 * In:  const string& - Reference to string key which is to be found.
 * Out: vector - vector of type string pointer in order to store all  
 *      occurance of the input key.
 *
 */
vector<const string*> RBTree::rbFind(const string& key)
{
   vector<const string*> foundString;

   if (root != nil)                       //Tree exists
   {
      Node* resultNode = rbTreeSearch(root,key);
      if (resultNode != nil)
      {
         string* resultString = (resultNode->value);
         foundString.push_back(resultString);  // First possible occurance

         Node* pre =  resultNode;      //In order to find dupliates we first 
         while (pre != nil)            //serach of all predecessors & compare
         {
            pre = rbTreePredecessor(pre);
            if (pre !=nil) 
            {
               if (*(pre->key) == key)
               {
                  string* resultString = (pre->value);
                  foundString.push_back(resultString); //push_back
                                                      //if key is same 
               }
            }
         }
        
         Node* succ = resultNode;     //Looking through all the successors
         while (succ != nil)
         {
            succ = rbTreeSuccessor(succ);
            if (succ != nil) 
            {
               if (*(succ->key) == key)
               {
                  string* resultString = (succ->value);
                  foundString.push_back(resultString);
               }
            }
         }
      }
   }
   return foundString;
}

/**
 * Desc: Simple algorithm to search through the entire tree to locate a 
 *       particular node.
 *
 * In:   Node* and key: Node pointer from where searching is required. 
 *       string reference which is to be searched.
 *
 * Out:  Node* - Returns node pointer with  matching key. 
 */

RBTree::Node* RBTree::rbTreeSearch(Node* x,const string& key)
{
   if(x == nil)
   {
      return x;
   }
   else if (key == *x->key)
   {
      return x;
   }
   if (key < *x->key) 
   {
      return rbTreeSearch( x->left,key);
   }
   else
   {
      return rbTreeSearch( x->right,key);
   }
}

/**
 * Desc: Function which is used in many other functions to find the minimum
 *       of a particular tree. Referred from Cormen.
 *
 * In:  Node* - Node pointer whose minimum is required.
 * Out: Node* - Returns the pointer to minimum of a particular tree.
 */


RBTree::Node* RBTree::rbTreeMinimum(Node* x)
{
   while (x->left != nil)
   {
      x = x->left;
   }
   return x;
}

/**
 * Desc: Function which is used in many other functions to find the maximum
 *       of a particular tree. Referred from Cormen.
 *
 * In:  Node* - Node pointer whose maximum is required.
 * Out: Node* - Returns the pointer to maximum of a particular tree.
 */

RBTree::Node* RBTree::rbTreeMaximum(Node* x)
{
   while (x->right != nil)
   {
      x = x->right;
   }
   return x;
}

/**
 * Desc: Function to find the successor of a particalar node. Used the 
 *       algorithm used in Cormen.
 *
 * In:   Node*-Passed a node pointer of the node whose successor is
 *       required.
 * Out:  Node* - returns the pointer to  successor of input node.
 */

RBTree::Node* RBTree::rbTreeSuccessor(Node* x)
{
   if (x->right != nil) 
   {
      return rbTreeMinimum(x->right);
   }
   Node* y = x->parent;
   while ((y != nil) && (x == y->right)) 
   {
      x = y;
      y = y->parent;
   }
   return y;
}

/**
 * Desc: Function to find the predecessor of a particalar node. Used the 
 *       algorithm used in Cormen.
 *
 * In:   Node*-Passed a node pointer of the node whose predecessor is
 *       required.
 * Out:  Node* - returns the pointer to  predecessor of input node.
 */

RBTree::Node* RBTree::rbTreePredecessor(Node* x)
{
   if (x->left != nil) 
   {
      return rbTreeMaximum(x->left);
   }
   Node* y = x->parent;
   while ((y != nil) && (x == y->left)) 
   {
      x = y;
      y = y->parent;
   }
   return y;
}



/**
 * Desc: Function which calls reverseInOrderPrint to print out the tree.
 *       
 * In:   No parameter is passed.private root is used 
 * Out:  None. Helper function which prints the tree.
 *
 */

void RBTree::rbPrintTree()
{
   if (root != nil)                 
   {
      reverseInOrderPrint(root,0); //In order to print the entire tree
   }
}

/**
 * Desc: Function which traverses entire tree in order to delete the tree.
 *       Called in the destructor.
 * In:   Node*-Node pointer to the root to delete the entire tree.
 * Out:  Returns nothing. Traverses and deallocates the memory of the tree.
 */
void RBTree::postOrderTraversal(Node* x)
{ 
   if(x != nil)
   { 
      postOrderTraversal(x->left);
      postOrderTraversal(x->right);
      delete(x);
   }
}
