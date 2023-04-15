#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>
#include <fstream>

using namespace std;

void writeInFile(fstream &file, char* content, unsigned long long length);
void readFile(fstream &file, char* content, unsigned long long length);
unsigned long long getFileLength(fstream &file);
#endif // FUNCTIONS_H
