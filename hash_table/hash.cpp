/**
 *  @file: hash.cpp
 *  @desc: hash.cpp has functions which implements hash table and printing
 *         the statistics as required. 
 *
 *  @author Diney Wankhede on 3/17/15
 *
 */

#include <string>
#include <list>
#include <iostream>
#include <fstream>
#include "hash.h"

using std::string;
using std::list;

using namespace std;

/**
 * Constructor for the hash.h initializing various variables
 * Initializes private member variables declared in hash.h.
 */

Hash::Hash()
{
   avgLength = 0.0;           
   collisions = 0;
   longestList = 0;
   currentAvgListLen = 0.0;
}

/**
 * Desc: This function inputs the file name and extracts each word from the 
 *       file, calls hash_function and inserts the word using the index in the
 *       hash_table.
 * In:   string - file name from which the input is to be taken
 * Out:  Doesn't return anything.Inserts each word of file into the hash table
 */

void Hash::processFile(string fname)
{
   ifstream file(fname.c_str());                 //Reading the input from file
   string word;
   while(getline(file,word))                     //process all the words
   {
      int index = hf(word);
      if(!hashTable[index].empty())
      {
         collisions++;
      }
      hashTable[index].push_back(word);         //adding to hashtable

      if (hashTable[index].size() >= longestList) 
      {
         longestList = hashTable[index].size();//calculating longest list ever
      }
      averageLength();                        //AverageLenght over time after 
   }                                          //insert
}
            
/**
 * Desc: A functions which locates the input word in the hash tables & returns
 *       true or false accordingly.(true if present
 *
 * In:   String - The word that is to be searched in the hashtable
 * Out:  bool- Returns true if the input word is present in the hashtable 
 *       else false.
 */

bool Hash::search(string search)
{
   int index = hf(search);
   if(!hashTable[index].empty())           // Checking Non empty only
   {
      for(int i = 0;i < HASH_TABLE_SIZE; i++)    
      {
         for(list<string>::iterator it = hashTable[i].begin();
             it !=hashTable[i].end(); ++it)
         {  
            if(*it == search)
              return true;
         }
      }
   }  
   return false;
}
            
/**
 *  Desc: A function which removes the input word from the hashtable and 
 *        updates the avergeLength.
 *
 *  In:   String - The word that is to be removed from the hashtable
 *  Out:  Removes the input word and updates statistics 
 *
 */

void Hash::remove(string word)
{
   int index = hf(word);
   if(!hashTable[index].empty())
   {
      if( search(word) ==  true)          // If word found proceed
      {
         hashTable[index].remove(word);   // Removes the words from hashtable
         averageLength();                 // AverageLength after remove
      }
   }
}
            
/**
 *  Desc: A function which prints the hashtable according to index generated
 *
 *  In:   No input.Uses the hashtable
 *  Out:  Prints the hashtable with the index
 */
            
void Hash::print()
{
   for(int i = 0;i < HASH_TABLE_SIZE;i++)
   {
      cout << i << ":\t";
      for(list<string>::iterator it = hashTable[i].begin(); 
          it != hashTable[i].end(); ++it)
      {
         cout << *it << ", ";
      }
      cout << endl;
   }  
}

            
/**
 *  Desc: The function outputs everything to a file similar to the print 
 *        function
 *
 *  In:   String- filename to which the output is to be written 
 *  Out:  The output is written to a file specified by the user
 */
         
void Hash::output(string filename)
{
   ofstream fileObj;
   fileObj.open(filename);                   // Writing to a file(opens it)
   
   for(int i = 0;i < HASH_TABLE_SIZE;i++)
   {
      fileObj << i << ":\t";
      for(list<string>::iterator it = hashTable[i].begin(); 
          it != hashTable[i].end(); ++it)
      {
         fileObj << *it << ", ";
      }
      fileObj << endl;
   }
   fileObj.close();
}

/**
 * Desc: Printing the statistics of hashtable after implementation.
 *       Print total number of collisions, longest list ever generated,
 *       average list length over time(using curentAverage list length,
 *       Load factor of the hash table after entire implementation.   
 *
 * In:   None. Uses memeber variables and functions
 * Out:  Prints four statistics
 */

void Hash::printStats()
{
   cout << "Total Collisions = " << collisions << endl;
   cout << "Longest List Ever = " << longestList << endl;
   cout << "Average List Length Over Time = " << avgLength << endl;
   cout << "Load Factor = " << loadFactor() << endl;
}
            
/**
 * Desc: The function calculates the longest list ever generated. This is
 *       always incremented never decremented.
 *
 * In:   None. Uses the HASH_TABLE_SIZE    
 * Out:  unsigned int - Returns the longestlist which has unsigned int type
 */
         
unsigned int Hash::longList()
{
   longestList = hashTable[0].size();
   for(int i = 0; i < HASH_TABLE_SIZE; i++)
   {
      if(hashTable[i].size() >= longestList)
         longestList = hashTable[i].size();
   }
   return longestList;
}

/**
 * Desc: This function returns the average List Length over the time.
 *       It is calculated(Called) after every insert and remove.
 *
 * In:   No input.Uses the HASH_TABLE_SIZE which is a member variable 
 *       which can be changed dynamically.
 * Out:  Calcualtes the current average length average length over time.
 *
 */
         
void Hash::averageLength()
{
   double nonEmpty = 0.0;
   double totalItems = 0.0;
   for(int i = 0;i < HASH_TABLE_SIZE; i++)
   {
      totalItems = totalItems + (hashTable[i].size());
      if(!hashTable[i].empty())
         nonEmpty = nonEmpty + 1.0;
   }  
   currentAvgListLen = totalItems / nonEmpty;
   avgLength = (currentAvgListLen + avgLength) / 2.0;
}
            
/**
 *  Desc: This function calculates the load factor of the hash table.
 *        It is calculated by no. of elements in the table/ no. of slots 
 *        or no. of linked list( Some may be empty)
 *
 *  In:   None. Uses HASH_TABLE_SIZE.
 *  Out:  double- returns the double loadFactor
 */

double Hash::loadFactor()
{  
   double loadFact = 0.0;
   double totalItems = 0.0;
   for(int i = 0;i < HASH_TABLE_SIZE; i++)
   {
      totalItems = totalItems + hashTable[i].size();
   }
   loadFact = totalItems / HASH_TABLE_SIZE;
   return loadFact;
}
