/**
 *  @file: SSPapp.h
 *  @desc: SSPapp file which has functions to read the graph in entirity 
 *         and process queries.
 *
 *  @author: Diney Wankhede
 *  @date:   4/26/15
 *
 */

#ifndef ____SSPapp__
#define ____SSPapp__

#include "graph.h"

class SSPapp
{
public:
   SSPapp();                  // Constructor 
   ~SSPapp();                 // Destructor
   void readGraph();          // Reading the entire graph
   void processQueries();     // Processing the queries
private:
   Graph myGraph;             //Object of inner class Graph
};

#endif /* defined(____SSPapp__) */
