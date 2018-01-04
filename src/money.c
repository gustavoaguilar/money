#include<stdio.h>
#include<string.h>
#include<time.h>
#include<ctype.h>
#include "db.h"

#define MAX_USR_INPUT 50

int strComp(char str1[], char str2[]){
  int i=0, j=0;
  while(str1[i] != '\x0' && str2[j] != '\x0'){
    //printf("<%c %c> ",str1[i], str2[j]);

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
  int i;
  for(i=0; input[i] != '\x0'; i++){
    if(input[i] == '\n') input[i] = '\x0';
  }
}

int main(){
  int nextId=1;
  float currency=0;
  int running = 1;

  char usrInput[MAX_USR_INPUT];
  List* bd = readFile("data.txt", &nextId, &currency);
  printf("NEXT: %d\n", nextId);

  printf("Wellcome to Money! v0.1\n\nCREATED BY: Gustavo Henrique Aguilar\n\nType \"help\" to list the commands\n");

  while(running){
    printf("<money> ");
    getUsrString(usrInput);
    //printf("INPUT... %s\n", usrInput);
    //printf("%d\n", strComp(usrInput, "quit"));
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
      char info[MAXINFO], date[MAXINFO], c;
      printf("Value: ");
      scanf("%f", &value);
      c = getchar();

      printf("Info(Max 50 characters, use '_' for spaces): ");
      getUsrString(info);

      printf("Date(dd/mm/yyyy, leave blank for automatic): ");
      getUsrString(date);
      //get date from system;
      if(!strComp(date, "")){
        char buffer[4];
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
      nextId++;
    }
    else if(!strComp(usrInput, "rem")){
      int id;
      char c;
      printf("Id: ");
      scanf("%d", &id);
      c = getchar();
      remNote(bd, id);
    }
    else if(!strComp(usrInput, "currency")){
      printf("\n\nYou currency is: $%.2f\n\n", currency);
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
