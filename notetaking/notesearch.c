#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include "hacking.h"

#define FILENAME "/var/notes"

int print_notes(int, int, char*); // Note printing functioning
int find_user_note(int, int); // Seek in file for a note for user
int search_note(char *, char *); // Search for keyword function
void fatal(char *); // Fatal error handler

int main(int argc, char *argv[]) {
  int userid, printing=1, fd; // File descriptor
  char searchstring[100];

  if (argc > 1) // If there are arguments
    strcpy(searchstring, argv[1]); // the first arg is the search string
  else
    searchstring[0] = 0; // no search string provided

  userid = getuid();
  fd = open(FILENAME, O_RDONLY); // Open file in read-only access
  if (fd == -1)
    fatal("in main() while opening file for reading");

  while(printing) {
    printing = print_notes(fd, userid, searchstring);
  }

  printf("-------[ end of note data ]-------\n");
  close(fd);
}

/**
 * A function to print the notes for a given uid that match an optional search string
 * @param fd - The file descriptor
 * @param uid - The uid of the user
 * @param searchstring - The string to search for
 * @returns 0 at the end of file, 1 if there are still more notes
 */
int print_notes(int fd, int uid, char *searchstring) {
  int note_length;
  char byte=0, note_buffer[100];

  note_length = find_user_note(fd, uid);
  if (note_length == -1) { // EOF reached
    return 0;
  }

  read(fd, note_buffer, note_length); // Read note data
  note_buffer[note_length] = 0;

  if (search_note(note_buffer, searchstring)) { // Search string was found
    printf(note_buffer); // print the note
  }

  return 1;
}

/**
 * A function to find the next note for a given userID
 * @param fd - The file descriptor
 * @param user_uid - The uid of the user 
 * @returns -1 if EOF reached
 */
int find_user_note(int fd, int user_uid) {
  int note_uid=-1;
  unsigned char byte;
  int length;

  while (note_uid != user_uid) { // Loop until a note for users id is found
    if (read(fd, &note_uid, 4) != 4) { // Read the uid data
      return -1; // Bytes aren't read, return EOF
    }
    if (read(fd, &byte, 1) != 1) { // Read newline sep
      return -1;
    }

    byte = length = 0;
    while (byte != '\n') { // Figure out how many bytes to the end of line
      if (read(fd, &byte, 1) != 1) { // Read a single byte
        return -1;
      }
      length++;
    }
  }

  lseek(fd, length * -1, SEEK_CUR); // Rewind file reading by length of bytes
  
  printf("[DEBUG] found a %d byte note for user id %d\n", length, note_uid);
  return length;
}

/**
 * A functino to search a note for a given keyword
 * @param note - The note to search
 * @param keyword - The keyword to search for
 * @returns 1 if match found, 0 otherwise
 */
int search_note(char *note, char *keyword) {
  int i, keyword_length, match=0;

  keyword_length = strlen(keyword);
  if (keyword_length == 0) { // no search string
    return 1; // always return a match
  }

  for (i=0; i < strlen(note); i++) { // Iterate over bytes in note
    if (note[i] == keyword[match]) { // If byte matches keyword byte
      match++;
    } else {
      if (note[i] == keyword[0]) { // if that byte matches first keyword byte
        match = 1; // reset match iterator to 1
      } else {
        match = 0; // Otherwise zero
      }
    }

    if (match == keyword_length) { // If ther eis a full match,
      return 1; // return matched
    }
  }

  return 0; // no match found
}

