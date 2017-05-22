#include "db.h"
int main(){
  Sentinel *bd = createList();
  addNote(bd, 1, 12, "Teste", "10/12/21");
  addNote(bd, 2, 24, "Teste2", "12/12/21");
  printList(bd);
  return 0;
}
