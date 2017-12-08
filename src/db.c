#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"db.h"

typedef struct Note{
  int id;
  float value;
  char info[MAXINFO];
  char date[DATESIZE]; // dd/mm/yy

  struct Note *next;
  struct Note *prev;

}Note;

List* createList(){
  List* new = (List*) malloc(sizeof(List));
  if(new == NULL){
    printf("Error on malloc\n");
    return NULL;
  }
  new->size = 0;
  new->next = NULL;
  return new;
}

void addNote(List* ref, int id, float value, char* info, char* date){
  Note* new = (Note*) malloc(sizeof(Note));
  if(new == NULL){
    printf("Error: No memory.\n");
    return;
  }
  new->id = id;
  new->value = value;
  strcpy(new->info, info);
  strcpy(new->date, date);

  if(ref->next == NULL){
    ref->next = new;
    ref->size++;
    return;
  }

  Note *aux = ref->next;
  while(aux->next != NULL){
    aux = aux->next;
  }
  aux->next = new;
}

void remNote(List* ref, int id){

  if(ref->next == NULL){
    printf("Empty List\n");
    return;
  }

  Note* aux = ref->next;

  //The first of the list
  if(aux->id == id){
    if(aux->next != NULL){
      ref->next = aux->next;
      aux->next->prev = NULL;
      free(aux);
      return;
    }else{
      ref->next = NULL;
      free(aux);
      return;
    }
  }

  //Searching
  while(aux->next != NULL && id != aux->id){
    aux = aux->next;
  }

  if(aux->id == id){
    //The middle of the list
    if(aux->next != NULL){
      aux->prev->next = aux->next;
      aux->next->prev = aux->prev;
      free(aux);
    }else{  //The last of the list
      aux->prev->next = NULL;
      free(aux);
    }
    return;
  }
  printf("Not found\n");
}

void printNote(List* ref, int id){
  Note* aux = ref->next;
  while(aux->next != NULL && aux->id != id){
    aux = aux->next;
  }
  if(aux->id == id){
    printf("ID: %d\n", aux->id);
    printf("Value: %.2f\n", aux->value);
    printf("Date: %s\n", aux->date);
    printf("Info: %s\n", aux->info);
    return;
  }
}

void printList(List* ref){
  Note *aux = ref->next;
  if(aux == NULL){
    printf("List Empty\n");
  }
  while(aux != NULL){
    printf("[%d]\t$%6.2f\t\"%30s\"\t(%s)\n", aux->id, aux->value, aux->info, aux->date);
    aux = aux->next;
  }
  printf("\n");
}
