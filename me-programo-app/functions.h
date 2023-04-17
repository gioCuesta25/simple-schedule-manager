#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>
#include <fstream>

using namespace std;

void writeInFile(fstream &file, char* content, unsigned long long length);
void readFile(fstream &file, char* content, unsigned long long length);
unsigned long long getFileLength(fstream &file);
int menu();

// Functions for manage the courses
void manageCourses();
void addCourse(fstream &file);

// Functions for manage the schedule
void manageSchedule();
#endif // FUNCTIONS_H
