/**
 * @file: hash_function.cpp
 * @author: Diney Wankhede
 * @date: 10.29.2014
 *
 * @desc:The hashfunction is based on fnv1a hashfunction. Observing results
 *       I found that it is not efficient for small strings( 5 letters).  
 *       I used the multiplication function along with two suitable constants 
 *       33 and 13 which are prime numbers away from the squares. 
 *       This gave a good distribution for 11 inputs. 
 *       The statistics obtained showed that maximum list lenght ever was 5 & 
 *       initially the distribution was not that good, as average list length
 *       was 1.58. As in the case of fnv1 and fnv1a replacing "*" with "^" 
 *       gave a huge difference in the output. I replaced'*' (multiplication)
 *       in my hash function with XOR "^"(Exclusive Or).
 *       This gave the best results as the longest list  ever was 2 & average 
 *       list length was 1.33.
 * 
 * @hashfunction: My hf uses two special prime number and its XOR with 
 *                ASCII values of each letter of the string(XOR uses binary 
 *                numbers and then calculated).Secondly, multply by
 *                33. Finally HASH_TABLE_SIZE is used to map the hash within
 *                size of HashTable used.             
 *
 * Reference: http://www.isthe.com/chongo/tech/comp/fnv/#FNV-1
 *            http://create.stephan-brumme.com/fnv-hash/
 */

#include <string>
#include "hash.h"

using std::string;

/*
 * Desc: Hash_function described above is implemented here.
 * In:   string- The string whose index is to calculated to place it in 
 *       hashtable.
 * Out:  returns integer- the index calculated by hash_function is returned.
 */

int Hash::hf (string ins)
{
   unsigned int hash = 13;
   for(int i = 0; i < (int)ins.length(); i++)
   {
      hash = (hash ^ ins[i]) * 33;
   }
   return (hash % HASH_TABLE_SIZE);
}
