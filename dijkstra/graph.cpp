/**
 *  @file: graph.cpp
 *  @desc: Graph file is implementation of Dijkstra Algorithm which calculates 
 *         Single Source Shortest path when user inputs a query.
 *
 *  @author: Diney Wankhede
 *  @date: 4/26/15
 *
 */

#include "graph.h"
#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <algorithm>

using std::cout;
using std::endl;
using std::map;
using std::pair;
using std::sort;

/*
 * Desc: Constructor for Graph class which intializes the currentsource.
 *
 */

Graph::Graph()
{
   currentSource = "NIL";
}

/*
 * Desc: Desctructor for the class Graph which is responsible for deleting
 *       the entire Vertices map and AdjList map.
 *
 *       Values are deleted which frees up the memory for the entire Vertices.
 *       Similarly for the adjList map.
 *
 */

Graph::~Graph()
{
   
   for (std::map<string,Vertex*>::iterator it = Vertices.begin();
       it != Vertices.end(); ++it) 
   {
      delete it->second;
   }
   
   Vertices.clear();
   
   for (std::map<string,vector<Neighbor*>>::iterator it = adjList.begin();
        it != adjList.end(); ++it) 
   {
      for (vector<Neighbor*> :: iterator i = it->second.begin(); 
           i != it->second.end(); i++) 
         delete *i;
   }

   adjList.clear();
   
}

/*
 *  Desc: Copy construtor for the private class Neighbor. 
 *        Copies dynamically to the Objects of Neighbors.
 *
 */

Graph::Neighbor::Neighbor(string new_name,int new_weight)
{
   name = new_name;
   weight = new_weight;
}

/*
 * Default destructor for Neighbor.
 * As Neighbor members are not pointers it will be handled automatically.
 */

Graph::Neighbor::~Neighbor()
{
   
}

/*
 * Desc: Copy construtor for the private class Vertex. 
 *       Copies dynamically to the Objects of Vertex.
 *
 */

Graph::Vertex::Vertex(string new_pi,int new_key)
{
   pi = new_pi;
   key = new_key;
}

/*
 * Default destructor for Vertex.
 * As Vertex members are not pointers it will be handled automatically.
 *
 */

Graph::Vertex::~Vertex()
{
   
}

/*
 * Desc: This function will create the nodes for the vertex and add into the
 *       Vertices map.
 *
 * In :  String - name - Name of the Vertex to be added.
 * Out:  None - Adds all the vertex to the map of Vertices.
 *
 */

void Graph::addVertex(string name)
{
   Vertex* insert = new Vertex("NIL",101);
   
   if (!name.empty() && Vertices.count(name) <= 0) //Unique Vertex
   {
      Vertices.insert(pair<string,Vertex*>(name,insert));
   }   
}

/*
 * Desc: This function will create the nodes for the edges and add into the
 *       adjList map accordingly.
 *
 * In:   string from - The starting of vertex of the a edge
 *       string to -  The ending of vertex of the a edge
 *       int weight -  The weight of the a edge
 * Out:  None - Adds all the edges to the map of adjList.
 *
 */

void Graph::addEdge(string from, string to, int weight)
{
   Neighbor* neighborNew = new Neighbor(to,weight); //Creating a neighbor node

   if (adjList.empty())   
   {
      vector<Neighbor*> vectorNeighhbor;
      vectorNeighhbor.push_back(neighborNew);
      adjList.insert(pair<string,vector<Neighbor*>>(from,vectorNeighhbor));
   }
   else if(adjList.count(from) > 0)     //If vertex already exists
   {
      for (std::map<string,vector<Neighbor*>>::iterator it = adjList.begin();
        it != adjList.end(); ++it) 
      {
         if (it->first == from)
         {
            adjList[it->first].push_back(neighborNew);
         }
      }
   }
   else                                 //Adding new edge
   {
      vector<Neighbor*> vectorNeighhbor2;
      vectorNeighhbor2.push_back(neighborNew);
      adjList.insert(pair<string,vector<Neighbor*>>(from,vectorNeighhbor2));
   }
}

/*
 * Desc: Function which processes the queries, computes the single source path
 *       and calls for a new function to form a string to print.
 *
 * In:   string  from- starting of the query (source)
 *       string  to- ending vertex
 * Out:  string - calls function to get the output string 
 *
 */

string Graph::getShortestPath(string from,string to)
{
   sortNeighbors();       //Sort function to sort the neighbors alphabetically
   
   bool temp = false;     // to check if to has a path 
   
   for (std::map<string,vector<Neighbor*>>::iterator it = adjList.begin();
        it != adjList.end(); ++it) 
   {
      for (vector<Neighbor*> :: iterator i = it->second.begin(); 
           i != it->second.end(); i++) 
      {
         if((*i)->name == to)
            temp = true;
      }
   } 
   //To reduce complexity calculating distance only when source is changed.
   if (adjList.count(from) <= 0)       // if from has no outgoing edges.
   {
      return from + " with length 0"; 
   }
   
   if (currentSource == "NIL")        //Initially source is NIL
   {
      buildSSPTree(from); 
      string answer;
      if(temp == true)
         answer = myGraphCompute(from,to);
      else
         answer = from + " with lenght 0";
           return answer;
   }
   else if(from == currentSource)   //If the source is same as that of current
   {
      string answer;
      if(temp == true)
         answer = myGraphCompute(from,to);
      else
         answer = from + " with lenght 0";
           return answer;      
   } 
   else                          //New Source
   {
      string answer;
      if(temp == true)
      {
         buildSSPTree(from); 
         answer = myGraphCompute(from,to);
      }
      else
      {
         answer = from + " with lenght 0";
      }
      return answer;
   }
}

/*
 * Desc: Calculating the path and using concatenation to generate required 
 *       output. Path is caluclated starting from to till we get from and 
 *       appending to a string in  reverse order.
 *
 * In:   string from - starting of the path required
 *       string to - ending of the path 
 * Ouy:  string - returns a string which is the final required output
 */

string Graph::myGraphCompute(string from,string to)
{
   vector<string> local;
   string note = " with length ";
   string space = " ";
   string arrow = "->";
   
   int distance = 0;
   string parent1 = Vertices.find(to)->second->pi;
   
   for(std::map<string,vector<Neighbor*>>::iterator it = adjList.begin();
       it != adjList.end(); ++it)     // Calculating the lenght
   {
      if (parent1 == it->first)
      {
         for (vector<Neighbor*> :: iterator i = it->second.begin(); 
              i != it->second.end(); i++) 
         {
            if ((*i)->name == to) 
            {
               distance = distance + (*i)->weight;
            }
         }
      }
   }
   
   local.push_back(parent1);    // Pushing the parent to local
   
   while (parent1 != from)
   {
      string parentOld = parent1;
      parent1 = Vertices.find(parent1)->second->pi;
      local.push_back(parent1);
 
      for(std::map<string,vector<Neighbor*>>::iterator it = adjList.begin();
          it != adjList.end(); ++it)
      {
         if (parent1 == it->first)
         {
            for (vector<Neighbor*> :: iterator i = it->second.begin(); 
                 i != it->second.end(); i++) 
            {
               if ((*i)->name == parentOld) 
               {
                  distance = distance + (*i)->weight;
               }
            }
         }
      }
   }
   string distanceS = std::to_string(distance);    //Int to String
   string answer;
   
   for (int i = (int)local.size()-1; i >= 0 ; i--) //Generating the string 
   {
      answer.append(local[i]);
      answer.append(arrow);
   }
   answer.append(to);
   answer.append(note);
   
   return answer + distanceS; //Concatenating length to path of string 
}

/*
 * Desc: Buillding the SSPTree from the current source. as per Cormen.
 *
 * In: string - source - Current source which is being queried
 * Out: Returns nothing - Updates the Vertices of the map as per new source
 *      Updates the value of key and each vertex in map of Vertices
 *
 */

void Graph::buildSSPTree(string source)
{
   currentSource = source;   //Setting the current source to New source
   
   initializeSingleSource(source); //Initializing source
   for (std::map<string,Vertex*>::iterator it = Vertices.begin();
        it != Vertices.end(); ++it) 
   {
      minQ.insert(it->first,it->second->key);  //Inserting in minHeap
   }
   int size = Vertices.size();
   
   while (size != 0)
   {
      string u = minQ.extractMin(); //Extracting the min from minHeap
      for (std::map<string,vector<Neighbor*>>::iterator it = adjList.begin();
          it != adjList.end(); ++it) 
      {
         if (it->first == u) 
         {
            for (vector<Neighbor*>::iterator i = it->second.begin(); 
                 i != it->second.end(); i++) 
            {
               relax(u,(*i)->name,(*i)->weight);  
            }
         }
      }
      size --;
   }
}

/*
 * Desc: Relaxing the weights as per requirement. As per Cormen Implementation
 *
 * In: string u - Start of the edge
 *     string v - End of edge
 *     int w - Weight of particular edge u->v
 * Out: Modifies the map of Vertices and updates the weights.
 *
 */

void Graph::relax(string u, string v , int w)
{   
   if (Vertices.find(v)->second->key > (Vertices.find(u)->second->key + w)) 
   {
      Vertices.find(v)->second->key = (Vertices.find(u)->second->key + w);
      Vertices.find(v)->second->pi = u;
      //Updating the value in the minHeap Q
      minQ.decreaseKey(v,(Vertices.find(u)->second->key + w));
   }
}

/*
 * Desc: Intializes the vertices before building the SSP Tree. As per Cormen
 *
 * In: string s - The source which  is the current source
 *
 * Out: None - Vertices will be intialized
 *
 */

void Graph::initializeSingleSource(string s)
{
   for (std::map<string,Vertex*>::iterator it = Vertices.begin();
       it != Vertices.end(); ++it) 
   {
      it->second->key = 101;
      it->second->pi = "NIL";
   }
   Vertices.find(s)->second->key = 0;
}

/*
 * Desc: Function to sort the vector of Neighbors in the adjList list.
 * 
 * In: None - uses map of adjList 
 *
 * Out: None - Sorts the adjList using insertion sort
 *
 */

void Graph::sortNeighbors()
{
   int i;
   Neighbor* key;

   for (std::map<string,vector<Neighbor*>>::iterator it = adjList.begin();
        it != adjList.end(); ++it) 
   {
 
      for(int j = 1; j < (int) it->second.size(); j++)
      {
         key = it->second[j]; 
         i = j - 1;
         while(i >= 0  && (it->second[i]->name) > (key->name))
         {
            it->second[i+1] = it->second[i];
            i = i - 1;
         }
         (it->second[i+1]) = key;
      }
   }
}
