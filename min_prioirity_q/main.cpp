/**
 * @file: main.cpp
 * @desc: Test driver using the minpriority.h for implementing minpriority 
 *        queue.
 *
 * @date: 04/22/2015
 * @author: Diney Wankhede
 *
 */

#include "minpriority.h"
#include <string>
#include <iostream>
#include <sstream>

using std::string;
using std::cout;
using std::cin;
using std::stringstream;
using std::endl;

/**
 * Desc: main function which is the test driver for the program. It processes 
 *       all commands, inputs and calls the desired function for maintaining
 *       minpriority queue.
 * In:   No input. Uses input from the user and processes it.
 * Out:  Returns 0 - Integer. Calls desired function as per input from user.
 *
 */

int main()
{
   MinPriorityQ myMPQ;
   string input, command, inputId, inputKeyString;
   int inputKey;
   while(!cin.eof())
   {
      getline(cin,input);
      command = input.substr(0,input.find(' '));
      
      if (command == "a")                 //Adds an Element to the queue
      {
         input.erase(0,input.find(' ')+1);
         inputId = input.substr(0,input.find(' '));
         input.erase(0,input.find(' ')+1);
         inputKeyString = input.substr(0,input.find(' '));  
         stringstream ss;
         ss << inputKeyString;          //String to integer for the input
         if (stringstream(inputKeyString) >> inputKey)
         {  
            if(!inputId.empty())
               myMPQ.insert(inputId,inputKey);
         }
      }
      else if (command == "d")          //Updates the element with new key
      {
         input.erase(0,input.find(' ')+1);
         inputId = input.substr(0,input.find(' '));
         input.erase(0,input.find(' ')+1);
         inputKeyString = input.substr(0,input.find(' '));  
         stringstream ss;
         ss << inputKeyString;
         if (stringstream(inputKeyString) >> inputKey)
         {  
            if(!inputId.empty())
            {
               if(myMPQ.isMember(inputId))
               {
                  myMPQ.decreaseKey(inputId, inputKey);  
               }
            }
         }
      }  
      else if (command == "x")       //Extracts the minimum key and prints
      {
         cout<< myMPQ.extractMin() << endl;      
      }
      else if (command == "q")      //Quits the program
      {
         exit(0);
      }
   }
   return 0;
}
