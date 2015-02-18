/**
 * @file playlist.cpp   Implementation of a Playlist for music.
 * 
 * @brief
 *    Implementation of a Playlist for music. A doubly linked list is
 *    used to store the song names.
 *
 * @author Judy Challinger
 * @date 2/1/13
 */

#include <iostream>
#include <string>
#include "playlist.h"
#include "doublylinkedlist.h"

using std::string;
using std::cin;
using std::cout;
using std::endl;

using namespace std;

/**
 * Process a playlist command.
 *
 * Gets an entire line from std::cin, extracts the first word as the command,
 * and calls the appropriate processing function. Invalid commands are
 * ignored.
 */

void Playlist::processCommand()
{
   string inputLine;
   getline(cin,inputLine);
   string command = inputLine.substr(0, inputLine.find(' '));

   if (command == "appendSong")
   {
      processAppend(inputLine);
   }
   else if(command == "insertBefore")
   {
      processInsertBefore(inputLine);
   }
   else if (command == "insertAfter")
   {
      processInsertAfter(inputLine);
   }
   else  if(command == "gotoFirstSong")
   {
      processGotoFirst();
   }
   else if (command == "gotoLastSong")
   {
      processGotoLast();
   }
   else if (command == "playCurrent")
   {
      processCurrent();
   }
   else if (command == "removeSong")
   {
      processRemove(inputLine);
   }
   else if (command == "gotoSong")
   {
      processGotoSong(inputLine);
   }
   else if (command == "nextSong")
   {
      processNext();
   }
   else if(command == "prevSong")
   {
      processPrev();
   }
   else if(command == "playForward")
   {
      processPlayForward();
   }
   else if(command == "playReverse")
   {
      processPlayReverse();
   }
}

/**
 *  Processes the append function and appends or adds the song to the
 *  end of the playlist.
 *  IN: String song to be appended
 *  OUT: None
 */

void Playlist::processAppend(string& inputLine)
{
   inputLine.erase(0, inputLine.find(' '));              //Erasing the command
   string song = inputLine.substr(1,inputLine.length()); //Song is extracted
   if (song[0] == '\0')                                  //Checking for empty
      return;
   dll.append(song);
}

/**
 *  Plays(prints) the current song in the playlist.Calls the getData() of
 *  doublylinkedlist to get data of current pointer in the playlist.
 *  IN: None
 *  OUT: prints the current song in the playlist.
 */

void Playlist::processCurrent()
{
   cout<<endl<<"playing current: ";
   if(!dll.empty())
   cout<<dll.getData()<<endl;
}

/**
 *  Plays(prints) the songs till last song from the current song
 *  in the playlist till the last song in the playlist.
 *  IN: None
 *  OUT: prints the list from the current song to end of list.
 */

void Playlist::processPlayForward()
{
   cout<<endl<<"playing forward: "<<endl;
   if(!dll.empty())
   {
      do
      {
         cout<<dll.getData()<<endl;
      }
      while(dll.next());
   }
}

/**
 *  Plays(prints) the songs till first song from the current song
 *  in the playlist till the first song in the playlist.
 *  IN: None
 *  OUT: No return.Prints the list from current to the first song in the list.
 */

void Playlist::processPlayReverse()
{
   cout<<endl<<"playing reverse: "<<endl;
   if(!dll.empty())
   {
      do
      {
         cout<<dll.getData()<<endl;
      }
      while(dll.prev());
   }
}

/**
 *  Moves the current pointer to the first song of playlist.
 *  IN: None
 *  OUT: None. Current song
 */

void Playlist::processGotoFirst()
{
   dll.begin();
}

/**
 *  Moves the current pointer to the last song of playlist.
 *
 */

void Playlist::processGotoLast()
{
   dll.end();
}

/**
 *  Inserts a song following the current song in playlist.
 *  IN: String song to be inserted in playlist.
 *  OUT: None
 */

void Playlist::processInsertAfter(string& inputLine)
{
   inputLine.erase(0, inputLine.find(' '));
   string song = inputLine.substr(1,inputLine.length());
   if (song[0] == '\0')
      return;
   dll.insertAfter(song);
}

/**
 *  Inserts a song preceding the current song in playlist.
 *  IN: String song to be inserted in playlist.
 *
 */

void Playlist::processInsertBefore(string& inputLine)
{
   inputLine.erase(0, inputLine.find(' '));
   string song = inputLine.substr(1,inputLine.length());
   if (song[0] == '\0')
      return;
   dll.insertBefore(song);
}

/**
 *  Moves the current song to the song input given by user.
 *  IN: String song to be set as current song.
 *  OUT: None.
 */

void Playlist::processGotoSong(string& inputLine)
{
   inputLine.erase(0, inputLine.find(' '));
   string song = inputLine.substr(1,inputLine.length());
   if (song[0] == '\0')
      return;
   dll.find(song);
}

/**
 *  Removes the first occurence of the song entered by user and maintains
 *  current song in playlist.If there is a next song.New current song is next
 *  if there exists one else it is prev if there exists one.
 *  IN: String song to be removed from playlist.
 *
 */

void Playlist::processRemove(string& inputLine)
{
   inputLine.erase(0, inputLine.find(' '));
   string song = inputLine.substr(1,inputLine.length());
   if (song[0] == '\0')
      return;
   dll.remove(song);
}

/**
 *  Moves the current song pointer to following next song in the playlist.
 *  IN: None.
 *  OUT: No return.Moves the current pointer to next song if there is one.
 */

void Playlist::processNext()
{
   dll.next();
}

/**
 *  Moves the current song pointer to preceeding song in the playlist.
 *  IN: None.
 *  OUT: No return.Moves the current pointer to previous song if there is one.
 */

void Playlist::processPrev()
{
   dll.prev();
}

/**
 * The Playlist main loop will process command lines until eof.
 *
 */

void Playlist::mainLoop()
{
   while (!cin.eof()) processCommand();         // process all commands
}

/**
 * The main entry point for the program.
 */

int main()
{
   Playlist myPlaylist;
   myPlaylist.mainLoop();
   return 0;
}




