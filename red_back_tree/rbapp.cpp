/**
*  @file: rbapp.cpp
*  @desc: This file has all the implementations of processing the input data
*         and functions required for calling the rbtree functions.
*
*  @author: Diney Wankhede
*  @date:  4/2/15.
*/

#include "rbapp.h"
#include <string>
#include <iostream>

using namespace std;


/**
 * Constructor to initiliaze the member of RBapp Class 
 *
 */

RBapp::RBapp()
{
   done = false;        //Initially false until program ends
}


/**
 * Desc: Main function which initializes the program
 *       Calls mainLoop until end.
 *
 * In:   None.Uses RBapp class object.
 * Out:  Interger. Returns 0.
 */

int main()
{
   RBapp myRBApp;
   myRBApp.mainLoop();
   return 0;
}

/**
 * Desc: Loops until end of file and until done is false.
 *       Returns to main when end of file is reached or quit is called.
 *       (done is true)
 *
 * In:   None. 
 * Out:  Returns nothing. Loops proccess command.
 */
 
void RBapp::mainLoop()
{
   while (!cin.eof() && !done)   // Untill end of file and done = false
   {
      processCommand();
   }
}

/**
 * Desc: Extracts the command from the input string and calls appropriate
 *       function to process the input command.
 *
 * In:   None. Uses the input either from file or command line.
 * Out:  Returns nothing. Fetches the input.
 */

void RBapp::processCommand()
{
   string input;
   getline(cin,input);
   string command;
   command = input.substr(0,input.find(' ')); //Extracting the command
 
   if (command == "insert")
   {
      processInsert(input);
   }
   else if(command == "print")
   {
      processPrint();
   }
   else if(command == "find")
   {
      processFind(input);
   }
   else if(command == "delete")
   {
      processDelete(input);
   }
   else if(command == "quit")
   {
      processQuit();
   }
}

/**
 * Desc: Processing the insert command in order to insert node/nodes.
 *
 * In:   String by reference the entire input line.
 * Out:  Calls the rbtree.cpp function. Separates key and value and passes.
 *
 */

void RBapp::processInsert(string& input)
{
   string key,value;
   input.erase(0,input.find(' ')+1);
   key = input.substr(0,input.find(' '));
   input.erase(0, key.length()+1);
   value = input.substr(0);            //Entire value until end of line
   if (!key.empty() && !value.empty()) //Checks if key & value arent empty
   {
      myRBT.rbInsert(key , value);
   }
}

/**
 * Desc: Calls te rbtree.cpp function to print the tree.
 *
 * In:   None. 
 * Out:  void- Returns nothing.
 */

void RBapp::processPrint()
{
   myRBT.rbPrintTree();
}

/**
 * Desc: Processing the find command in order to search node/nodes.
 *
 * In:   String by reference the entire input line.
 * Out:  Calls the rbtree.cpp function. Separates key and command  passes.
 *
 */

void RBapp::processFind(string& input)
{
   string key;
   input.erase(0,input.find(' ')+1);
   key = input.substr(0,input.find(' '));
   if (!key.empty()) 
   { //Vector stores the values obtained in order to print.
      vector<const string*> foundString = myRBT.rbFind(key);
      for (vector<const string*>::iterator it = foundString.begin();
           it != foundString.end(); it++) 
      {
         cout << key << " " << *(*it) << endl;
      }
   }
}

/**
 * Desc: Processing the delete command in order to delete node/nodes.
 *
 * In:   String by reference the entire input line.
 * Out:  Calls the rbtree.cpp function. Separates key and value and passes.
 *
 */

void RBapp::processDelete(string& input)
{
   string key,value;
   input.erase(0,input.find(' ')+1);
   key = input.substr(0,input.find(' '));
   input.erase(0,key.length()+1);
   value = input.substr(0);
   if (!key.empty() && !value.empty()) 
   {
      myRBT.rbDelete(key , value);
   }
}

/**
 * Desc: Quits the program and changes bool done to true to indicate 
 *       program end.
 *
 * In:   None. Uses private member done.
 * Out:  None. Returns to calling functions.
 */

void RBapp::processQuit()
{
   done = true;
   return;
}
