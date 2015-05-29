/*
 *  @file: graph.h
 *  @desc: Implmentation of Core Single Source Shortest Path Algorithm
 *         of Dijkstra's Algorithm                  
 *
 *  @author: Diney Wankhede 
 *  @date:  4/26/15.
 */

#ifndef ____graph__
#define ____graph__


#include <string>
#include <vector>
#include <map>
#include "minpriority.h"

using std::string;
using std::vector;
using std::map;

class Graph
{
public:
   Graph();                                          //Constructor
   ~Graph();                                         //Destructor
   void addVertex(string name);                      //Add Vertex to Vertices
   void addEdge(string from, string to, int weight); //Add edges to adjList
   string getShortestPath(string from,string to);    //Getting shortest path
   
private:
   class Vertex
   {
   public:
      Vertex(string,int);                        //Copy Constructor
      ~Vertex();                                 //Destructor
      string pi;
      int key;
   };
   class Neighbor 
   {
   public:
      Neighbor(string,int);                      //Copy Constructor
      ~Neighbor();                               //Destructor 
      string name;
      int weight;
   };
   MinPriorityQ minQ;                            //Object of inner class
   string currentSource;                         //currentSource init to "NIL"
   map<string,Vertex*> Vertices;                 //Stroring all vertices
   map<string,vector<Neighbor*>> adjList;        //Adjacency List
   void buildSSPTree(string source);             //Dijkstra function
   void relax(string u, string v, int weight);   //Helper function
   void initializeSingleSource(string);          //Helper
   string myGraphCompute(string,string);         //Print the path     
   void sortNeighbors();                         //Sorting Neighbors
};  

#endif /* defined(____graph__) */
