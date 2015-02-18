/**
 * @file playlist.h   Declaration of a Playlist for music.
 * 
 * @brief
 *    Implementation of Playlist for music, where a doubly linked list is
 *    used to store the song names.
 *
 * @author Judy Challinger
 * @date 2/1/13
 */

#ifndef CSCI_311_PLAYLIST_H
#define CSCI_311_PLAYLIST_H

#include "doublylinkedlist.h"
using std::string;

class Playlist {
public:
   void mainLoop();                    // process commands until done
private:
   DoublyLinkedList dll;               // playlist stored in doubly linked list
   
   void processCommand();              // read and process one playlist command
   void processAppend(string&);
   void processCurrent();
   void processPlayForward();
   void processPlayReverse();
   void processGotoFirst();
   void processGotoLast();
   void processInsertAfter(string&);
   void processInsertBefore(string&);
   void processGotoSong(string&);
   void processNext();
   void processPrev();
   void processRemove(string&);
};

#endif // CSCI_311_PLAYLIST_H