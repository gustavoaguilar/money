
#define MAXINFO 50
#define DATESIZE 11

#ifndef DB_H
#define DB_H
struct Note;

typedef struct Sentinel{
  int size;
  struct Note *next;
}Sentinel;

Sentinel* createList();
void addNote(Sentinel* ref, int id, float value, char* info, char* date);
void printList(Sentinel* ref);
#endif
