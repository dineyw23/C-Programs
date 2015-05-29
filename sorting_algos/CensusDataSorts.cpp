/**
 * @file CensusDataSorts.cpp   Sort functions for census population data.
 * 
 * @brief
 *    Implements several different types of sorts. Data can be sorted
 * by population or by name of town. This file contains all of the sorting
 * functions and their helpers.
 *
 * @author Judy Challinger
 * @date 2/22/13
 */

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>
#include <math.h>
#include <random>
#include <ctime>
#include "CensusData.h"

using std::string;

/**
*  Insertion Sort sorts data by population and by city name according to 
*  type passed. Uses Insertion as in Cormen.
*  In: integer type. 0 for population and 1 for city.
*  Out:Sorts the data vector by using insertion sort 
*/

void CensusData::insertionSort(int type)
{
   if(type == 0)                            //For Population
   {
      int i,j;
      Record* key=nullptr;                 //Temporary variable
      for(j = 1;j < (int)data.size(); j++)
      {
         key = data[j];       
         i = j - 1;
         while(i >= 0 && (data[i]->population) > key->population)
         {
            data[i+1] = data[i];
            i = i - 1;
         }
         data[i+1] = key;
      }
    }
    else if(type == 1)                      //For City
    {
       int i,j;
      Record* key=nullptr;                //Temporary variable
      for(j = 1;j < (int)data.size(); j++)
      {
         key = data[j];
         i = j-1;
         while(i >= 0 && *(data[i]->city) > *(key->city))
         {
               (data[i+1]) = (data[i]);
               i = i - 1;
         }
         (data[i+1]) = key;
      }
   }
}

/**
*  Implementation of merge sort as per Cormen. Calls individual functions
*  mergeSort Population and mergeSort City. 
*  Basic call to differntiate between Population and City.
*  IN: Integer type: static variable to check if population or city
*  OUT: Initial Calls to MergeSort Population and City
*/

void CensusData::mergeSort(int type)
{
   int p,r;
   if(type == 0)                          //For Population
   {
      p = 0;                             //Staring Index
      r =((int)data.size()-1);           //Ending Index
      mergeSortPopulation(p,r);
   }
   else if(type == 1)                    //For City
   {
      r = ((int)data.size()-1);
      p = 0;
      mergeSortCity(p,r);
   }
}

/**
*  Main implementation of merge sort which for population as per Cormen.   
*  Recurrsive function.
*  IN: Integer p,r : Starting and ending Index of data vector
*  OUT: Nothing. Recurrsive calls to MS City
*/

void CensusData::mergeSortPopulation(int p,int r)
{
   int q;
   if(p < r)
   {  
      q = floor((p+r)/2);                    //Center Element
      mergeSortPopulation(p,q);
      mergeSortPopulation(q+1,r);
      mergePopulation(p,q,r);
   }   
}

/**
*  Main implementation of merge sort which for City as per Cormen.   
*  Recurrsive function.
*  IN: Integer p,r : Starting and ending Index of data vector
*  OUT: Nothing. Recurrsive calls to MS City
*/

void CensusData::mergeSortCity(int p,int r)
{
   int q;
   if(p < r)
   {   
      q = floor((p+r)/2);
      mergeSortCity(p,q);
      mergeSortCity(q+1,r);
      mergeCity(p,q,r);
   }
}

/**
*  Merge part of Merge sort which is implemented as in Cormen.
*  Array to be sorted is broken down into Left and Right to compare and
*  sort the subarrays during recurrsive calls.
*  In: INTEGER p,q,r : p -starting index ,r - ending index,q-Center
*  Out: Returns nothing. Sorts the data as using L and R arrays/vector. 
*
*/

void CensusData::mergePopulation(int p,int q, int r)
{
   int n1 = q-p+1;
   int n2 = r-q;
   int i,j,k;
   vector<Record*> L(n1);                    //Size of Left Array
   vector<Record*> R(n2);                    //Size of Right Array
   for(i=0;i < n1; i++)
   { 
     L[i] = (data[p+i]);
   }
   for(j=0;j < n2; j++)
   {
      R[j]= (data[q+j+1]);
   } 
  
   k=p;
   while (!L.empty() || !R.empty())
   {
       if(L.empty())
       {
           for(int x = 0; x < (int)R.size(); x++)
           {
               data[k] = R[x];
               k = k + 1;
           } 
           break;
        }
  
        else if(R.empty())
        {
            for(int y = 0; y < (int)L.size(); y++)
            {
                data[k] = L[y];
                k = k + 1;
            }
            break;
        } 
 
        else if (!L.empty() && !R.empty())
        {
           if (L.front()->population <= R.front()->population)
           {
               data[k] = L.front();
               L.erase(L.begin());
               k = k + 1;
           }
           else
           {
               data[k] = R.front();
               R.erase(R.begin());
               k = k + 1;  
           }
        }
    } 
}

/**
*  Merge part of Merge sort which is implemented as in Cormen.
*  Array to be sorted is broken down into Left and Right to compare and
*  sort the subarrays during recurrsive calls.
*  In: INTEGER p,q,r : p -starting index ,r - ending index,q-Center
*  Out: Returns nothing. Sorts the data as using L and R arrays/vector. 
*
*/

void CensusData::mergeCity(int p,int q, int r)
{
   int n1 = q-p+1;
   int n2 = r-q;
   int i,j,k;
   vector<Record*> L(n1);                      //Left part of data
   vector<Record*> R(n2);                      //Right array part of data
   for(i=0;i < n1; i++)
   {
      L[i] = (data[p+i]);
   }
   for(j=0;j < n2; j++)
   {
      R[j] = (data[q+j+1]);
   }
   k=p;
   while (!L.empty() || !R.empty())         //Until both arrays have values
   {
      if(L.empty())                         // Case 1- If no element in left
      {
         for(int x = 0; x < (int)R.size(); x++)
         {
            data[k] = R[x];
            k = k+1;
         }
         break;
      }
      else if(R.empty())                  //Case 2- If no element in right
      {
         for(int y = 0; y < (int)L.size(); y++)
         {
            data[k] = L[y];
            k = k + 1;;
         }
         break;
      }
      else if (!L.empty() && !R.empty())
      {
         if ((*L.front()->city) <= (*R.front()->city))
         {
            data[k] = L.front();
            L.erase(L.begin());
            k = k+1;
         }
         else
         {
            data[k] = R.front();
            R.erase(R.begin());
            k = k+1;
         }
      }
   }
}

/**
*  Initial Call to quick sort. Further Randomized QS is implemente.
*  In: Integer: Type: type of input data to be sorted
*  Out: Calls to functions randomized QS.
*/

void CensusData::quickSort(int type)
{
   int p,r;
   int  seed = std::time(0);                //Seeding only once using time
  
   if(type == 0)                            //For Population type=0
   {
      p = 0;
      r =((int)data.size()-1);
      randQuickSortPopulation(p,r,seed);
   }
   else if(type == 1)                       //For City type = 1 
   {
      p = 0;
      r = ((int)data.size()-1);
      randQuickSortCity(p,r,seed);
   }
}

/**
*  This is called recurrsively as in the Cormen for randomized quicksort
*  for sorting the data based on population.
*  In: Integer p,r:= First and Last index of current subproblem 
*  Out: Nothing is returned. Recurrsive calls sorts the data.  
*/

void CensusData::randQuickSortPopulation(int p, int r,int seed) //For population
{
   int q;
   if(p < r)
   {
      q = randPartitionPopulation(p,r,seed);  //(Pivot)result of Partition
      randQuickSortPopulation(p,q-1,seed);
      randQuickSortPopulation(q+1,r,seed);
   }
}

/**
*  This is called recurrsively as in the Cormen for randomized quicksort
*  In: Integer p,r:= First and Last index of current subproblem 
*  Out: Nothing is returned. Recurrsive calls sorts the data.  
*/

void CensusData::randQuickSortCity(int p, int r,int seed)  //For City
{
   int q;
   if(p < r)
   {
      q = randPartitionCity(p,r,seed);       //(Pivot)result of partition
      randQuickSortCity(p,q-1,seed);
      randQuickSortCity(q+1,r,seed);
   }
}

/**
*  This function calls the partition function for the population by randomly 
*  arranging selecting an pivot element rather than the last element.
*  Random Number Generator from seeding it from a private member variable.
*  Reference : http://www.cplusplus.com/forum/general/139011/
*
*  In: Integer p,r := Starting and ending index of vector data.
*  Out:Returns an integer which is obtained by partition function.  
*
*/

int CensusData::randPartitionPopulation(int p, int r,int seed) //Population
{
   std::default_random_engine generator(seed);        //Random number generator
   std::uniform_int_distribution<int> distribution(p, r); //providing Range
   int i = distribution(generator);
   Record* temp;
   temp = data[i];
   data[i] = data[r];
   data[r] = temp;
   return partitionPopulation(p,r);
}

/**
*  This function calls the partition function for the City by randomly 
*  arranging selecting an pivot element rather than the last element.
*  Random Number Generator from seeding it from a private member variable.
*  Reference : http://www.cplusplus.com/forum/general/139011/
*
*  In: Integer p,r := Starting and ending index of vector data.
*  Out:Returns an integer which is obtained by partition function.  
*/

int CensusData::randPartitionCity(int p, int r,int seed)    //For City
{
   std::default_random_engine generator(seed);
   std::uniform_int_distribution<int> distribution(p, r);
   int i = distribution(generator);
   Record* temp;
   temp = data[i];
   data[i] = data[r];
   data[r] = temp;
   return partitionCity(p,r);
}

/*
*  Partition is the helper function of quicksort as described in Cormen
*  It is called by randPartionPopulation for partitioning and placing pivot at
*  required its position.
*  In: Integer p,r:=Starting and ending index of vector<Record*> data
*  Out:Returns an Integer for determining the index of pivot 
*  For Population.
*/

int CensusData::partitionPopulation(int p, int r)
{
   Record* x = data[r];
   Record* temp;
   int i = p - 1;
   for (int j = p; j < r; j++)
   {
      if ((data[j]->population) <= (x->population))
      {
         i = i + 1;
         temp = data[j];
         data[j] = data[i];
         data[i] = temp;
      }
   }
   temp = data[i+1];
   data[i+1] = data[r];
   data[r] = temp;
   return (i+1);
}

/*
*  Partition is the helper function of quicksort as described in Cormen
*  It is called by randPartionCity for partitioning and placing pivot at
*  required its position.
*  In: Integer p,r:=Starting and ending index of vector<Record*> data
*  Out:Returns an Integer for determining the index of pivot 
*  For Sorting by City
*/

int CensusData::partitionCity(int p, int r)
{
   Record* x = data[r];
   Record* temp;
   int i = p - 1;
   for (int j = p; j < r; j++)
   {
      if (*(data[j]->city) <= *(x->city))
      {
         i = i + 1;
         temp = data[j];
         data[j] = data[i];
         data[i] = temp;
      }
   }
   temp = data[i+1];
   data[i+1] = data[r];
   data[r] = temp;
   return (i+1);
}
