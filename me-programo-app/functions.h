#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>
#include <fstream>

using namespace std;

int ROWS = 18;
int COLS = 7;
int ELEMENT_LENGTH = 8;

// Utilidades
void writeInFile(fstream &file, char* content, unsigned long long length);
void readFile(fstream &file, char* content, unsigned long long length);
unsigned long long getFileLength(fstream &file);
int menu();
void split(char* cadena);
void freeMemory(char***);
void printInstructions();


// Functions for manage the courses
void manageCourses();
void addCourse(fstream &file);
void showAllCourses(fstream &file);

// Functions for manage the schedule
void manageSchedule();
void printSchedule(char ***matrix);
void updateSchedule(char ***matrix);
void loadSchedule(fstream &file, char***matrix);
void addClass(char ***matrix);
void modifySchedule(char ***matrix, char code[8], int start, int end, int day);
#endif // FUNCTIONS_H
