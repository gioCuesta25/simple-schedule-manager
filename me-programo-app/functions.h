#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>
#include <fstream>

using namespace std;

// Utilidades
void writeInFile(fstream &file, char* content, unsigned long long length);
void readFile(fstream &file, char* content, unsigned long long length);
unsigned long long getFileLength(fstream &file);
int menu();
void split(char* cadena);

// Functions for manage the courses
void manageCourses();
void addCourse(fstream &file);
void showAllCourses(fstream &file);

// Functions for manage the schedule
void manageSchedule();
void printSchedule(fstream &file);
void updateSchedule(fstream &file);
#endif // FUNCTIONS_H
