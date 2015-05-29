/**
 *  @file: SSPapp.cpp
 *  @desc: Wrapper class of the graph class which takes up all the inputs 
 *         and processes the it further.
 *
 *  @author: Diney Wankhede
 *  @date:  4/26/15.
 *
 */

#include "sspapp.h"
#include <iostream>
#include <string>
#include <sstream>
#include <limits>

using std::cout;
using std::cin;
using std::string;
using std::endl;
using std::stringstream;

/*
 * Desc: Main function for the initializing the program. Reads the entire 
 *       graph and then processes unlimited quries.
 * In:  None - Creates an object of class SSPapp and then reads the graph
 * Out: Returns integer  - 0
 *
 */

int main()
{
   SSPapp mySSPapp;
   mySSPapp.readGraph();
   
   while (!cin.eof())
   {
      mySSPapp.processQueries();
   }
   return 0;
}

/*
 * Desc: Deafult constructor for SSPApp class
 *
 */

SSPapp::SSPapp()
{
   
}

/*
 * Desc: Deafult desstructor for SSPApp class
 *       No dynamic allocation here
 *
 */

SSPapp::~SSPapp()
{
   
}

/*
 * Desc: Reading the entire graph as per the specified input
 *
 * In: None = Takes the user input and parses 
 * Out: None - Calls methods of Graph class.
 *
 */

void SSPapp::readGraph()
{
   int countVertices;
   cin>>countVertices;
   cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //Next Line
   string vertexName;
   
   getline(cin,vertexName);

   for (int i = 0; i < countVertices; i++)
   {
      string add;
      add = vertexName.substr(0,vertexName.find(' '));
      int length = vertexName.find(' ') + 1;
      vertexName.erase(0,length);
      if(!add.empty())
         myGraph.addVertex(add);                 //Add Vertex to Vertices
   }
   
   int countEdges;
   cin>>countEdges;
   cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //Next Line
   
   for (int i = 0; i < countEdges; i++)
   {
      string entirePair;
      getline(cin,entirePair);
      string to, from, weightString;
      int weight;
      from = entirePair.substr(0,entirePair.find(' '));
      entirePair.erase(0,entirePair.find(' ')+1);
      to = entirePair.substr(0,entirePair.find(' '));
      entirePair.erase(0,entirePair.find(' ')+1);
      weightString =  entirePair.substr(0);
      stringstream ss;
      ss << weightString;
      if (stringstream(weightString) >> weight)
      {  
         if (!from.empty() && !to.empty()) 
         {
             myGraph.addEdge(from,to,weight);   //Add Edges to the adjList
            
         }
      }
   }
}

/*
 * Desc: Processes the queries until end of file
 * In: None - Takes queries from user
 * 
 * Out: Returns nothing - Prints the output 
 *
 */

void SSPapp::processQueries()
{
   string query,from, to;
   getline(cin,query);
   
   from = query.substr(0,query.find(' '));
   query.erase(0,query.find(' ')+1);
   to = query.substr(0,query.find(' '));
   query.erase(0,query.find(' ')+1);
   
   if (!from.empty() && !to.empty()) 
   { 
      cout<< myGraph.getShortestPath(from,to) << endl; //Getting shortest path
   }
}
