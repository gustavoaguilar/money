
#define MAXINFO 50
#define DATESIZE 11

#ifndef DB_H
#define DB_H
struct Note;

typedef struct List{
  int size;
  struct Note *next;
}List;

List* createList();
void addNote(List* ref, int id, float value, char* info, char* date);
void remNote(List* ref, int id);
void printNote(List* ref, int id);
void printList(List* ref);
float calCurrency(List* ref);

void writeFile(List* ref, int nextId);
List* readFile(char* path, int* id, float* currency);

#endif
