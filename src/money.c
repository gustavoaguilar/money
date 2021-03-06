#include<stdio.h>
#include<string.h>
#include<time.h>
#include<ctype.h>
#include "db.h"

#define MAX_USR_INPUT 50

int strComp(char str1[], char str2[]){
  int i=0, j=0;
  while(str1[i] != '\x0' && str2[j] != '\x0'){

    if(str1[i] != str2[j]) return 1;
    i++;
    j++;
  }
  if(str1[i] == '\x0' && str2[j] == '\x0'){
    return 0;
  }else{
    return 1;
  }
}

void getUsrString(char input[]){
  fgets(input, MAX_USR_INPUT, stdin);
  __fpurge(stdin);
  //fflush(stdin); FOR WINDOWS
  int i;
  for(i=0; input[i] != '\x0'; i++){
    if(input[i] == ' ') input[i] = '_';
    if(input[i] == '\n') input[i] = '\x0';
  }
}

int main(){
  int nextId=1;
  float currency=0;
  int running = 1;

  char usrInput[MAX_USR_INPUT];
  List* bd = readFile("data.txt", &nextId);
  if(bd->next != NULL)
    currency = calCurrency(bd);

  printf("Wellcome to Money! v1.0\n\nCREATED BY: Gustavo Henrique Aguilar\n\nType \"help\" to list the commands\n");

  while(running){
    printf("<money> ");
    getUsrString(usrInput);
    if(!strComp(usrInput, "help")){
      printf("\nList of commands:\n");
      printf("add      (Create a new Note)\n");
      printf("rem      (Remove a Note)\n");
      printf("list     (List all Notes)\n");
      printf("currency (Show your currency)\n");
      printf("exit     (Save and Exit)\n\n");
    }
    else if(!strComp(usrInput, "add")){
      float value;
      char info[MAXINFO], date[DATESIZE], c;
      printf("Value: ");
      scanf("%f", &value);
      c = getchar();

      printf("Info(Max 50 characters): ");
      getUsrString(info);
      printf("Date(dd/mm/yyyy, leave blank for automatic): ");
      getUsrString(date);
      //if the date is blank
      if(!strComp(date, "")){
        char buffer[5];
        //get date from system;
        time_t t = time(NULL);
        struct tm tm = *localtime(&t);
        if(tm.tm_mday < 10) strcat(date, "0");
        sprintf(buffer, "%d", tm.tm_mday);
        strcat(date, buffer);
        strcat(date, "/");

        if(tm.tm_mon + 1 < 10) strcat(date, "0");
        sprintf(buffer, "%d", tm.tm_mon + 1);
        strcat(date, buffer);
        strcat(date, "/");

        sprintf( buffer, "%d", tm.tm_year+ 1900);
        strcat(date, buffer);
      }

      addNote(bd, nextId, value, info, date);
      printf("Added!\n");
      nextId++;
      currency = calCurrency(bd);
    }
    else if(!strComp(usrInput, "rem")){
      int id;
      char c;
      printf("Id: ");
      scanf("%d", &id);
      c = getchar();
      remNote(bd, id);
      currency = calCurrency(bd);
    }
    else if(!strComp(usrInput, "currency")){
      printf("\nYou currency is: $%.2f\n\n", currency);
    }
    else if(!strComp(usrInput, "list")){
      printList(bd);
    }
    else if(!strComp(usrInput, "exit")){
      writeFile(bd, nextId);
      running = 0;
    }
    else{
      printf("Command not found \'%s\'\n", usrInput);
    }
  }
  return 0;
}
