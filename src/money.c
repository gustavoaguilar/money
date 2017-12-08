#include<stdio.h>
#include "db.h"

int main(){

  long int nextId=0;
  float currency=0;


  List* bd = createList();
  addNote(bd, 1, 999, "Teste", "10/12/21");
  addNote(bd, 2, 24, "Teste2", "12/12/21");
  printList(bd);
  printNote(bd, 2);
  return 0;
}
