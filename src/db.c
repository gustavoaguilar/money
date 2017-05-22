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

Sentinel* createList(){
  Sentinel* new = (Sentinel*) malloc(sizeof(Sentinel));
  if(new == NULL){
    printf("Error on malloc\n");
    return NULL;
  }
  new->size = 0;
  new->next = NULL;
  return new;
}

void addNote(Sentinel* ref, int id, float value, char* info, char* date){
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

void printList(Sentinel* ref){
  Note *aux = ref->next;
  while(aux != NULL){
    printf("[%d]\t%.2f\t\"%s\"\t(%s)\n", aux->id, aux->value, aux->info, aux->date);
    aux = aux->next;
  }
  printf("\n");
}
