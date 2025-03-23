//
// Created by Joona on 23/03/2025.
//
/*CSV reader
CSV (Comma-Separated Values) files are a common way to store tabular data, making them a
valuable format for data interchange between applicaDons. Write a program that reads house
temperature data from a CSV-file and prints a horizontal bar graph of the temperature in the selected
room. The CSV file starts with a header row and then conDnues with lines of comma separated data.
The header row contains two Dtles: Room and Temperature. Data lines contain room name and the
temperature separated by commas*/
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct Room{
  char name[50];
  double temperature;
}room;


void extractData(char *line, char *name, double *temperature);
void printLines(double amount);

int main(){


  FILE *fileptr; //opens file and checks if the file exists
  char *fileName ="Temperatures.csv";
  fileptr = fopen(fileName,"r");
  if(fileptr == NULL){
    fprintf(stderr, "Error opening file %s\n", fileName);
    exit(1);
  }

  room array[100]; //lets delcare variables for different things we want keep data of
  char arrayName[100][50]; // names of the rooms we have collected, no dubs
  int i = 0, count = 0; //index and count of the different rooms we have
  bool isinList = false; //we use this later to check if the room is dub

  char line[100]; //we read every line with this file
  fgets(line, 100, fileptr); //skip headers

  while(!feof(fileptr) && i< 99){

    room room; //declare temporary room sruct

    fgets(line, 100, fileptr);
    if (strcmp(line, "\n") != 0) { //if the line isnt just empty space
      extractData(line, room.name, &room.temperature);  //we call function and pass pointers to structs name and temp as argumenrts
      array[i++] = room;

      for (int j = 0; j <= count; j++) { //we check if the current room is unique or dub
        if(strcmp(arrayName[j], room.name) == 0) {
          isinList = true; //if it is not unique room, boolean turns true
        }
      }
      if(isinList == false) { // here we add room to the list if it is unique room
        strcpy(arrayName[count++], room.name);

      }else { // we turn variable back to false for the next room
        isinList = false;
      }
    }
  }



  printf("============================================================================\n");
  printf("Data successfully loaded: %d different rooms\n", count);
  for (int j=0; j < count; j++) { //we print each unique room we have found
    printf("%s\n", arrayName[j]);
  }
  room nullroom; //enter last room struct as null
  nullroom.name[0] = '\0';
  nullroom.temperature = 0.0;
  array[i] = nullroom;
  printf("============================================================================\n");



  printf("Enter a name of the room you want to check:");
  char input[50];
  scanf("%[^\n]%*c", input);
  for (int j = 0; j <= count; j++) { //checks through of collected names and checks if input matches any of the room names
    if(strcmp(arrayName[j], input) == 0) {
      isinList = true;
    }
  }
  if (isinList == false) {
    fprintf(stderr, "No room found %s", input);
    exit(2);
  }

  printf("%s:\n", input);  //prints data of temperatures
  for (int j = 0; array[j].name[0] != '\0'; j++) {
    if(strcmp(input, array[j].name) == 0) {
      printf("%.1f ", array[j].temperature);
      printLines(array[j].temperature);
    }
  }

}
void printLines(double amount) {
  if (amount > 30 || amount < 0) { // if temperature is over 30 or under 0 the temp is displayed as X
    printf("X\n");
    return;
  }
  int integer = amount*2; // we double temp to get double amount of lines and round up/down when we turn it into integer
  for (int i = 0; i < integer; i++) {
    printf("-");
  }
  printf("\n");
}


void extractData(char *line, char *name, double *temperature) {
  char *ptr;
  *temperature = strtod(line,&ptr); //we assume first block of data is temperature variable in decimal form
  while (*ptr == ',' || isspace(*ptr)) { //after storing rempreature we skip every , and space in between temp and name
    *ptr++;
  }

  int i = 0;
  if (*ptr == '\0' || *ptr == '\n') {
    return;
  }
  while (*ptr != ',' && i < 49 && *ptr != '\0' && *ptr != '\n' && *ptr != '\t') {
    name[i++] = *ptr++; //we store name to struct 1 character at time
  }
  name[i] = '\0'; //we end name with null incase of memory leaks

}