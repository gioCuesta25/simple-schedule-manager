#include <fstream>
#include <iostream>
#include "functions.h"

using namespace std;


void writeInFile(fstream &file, char* content, unsigned long long length)
{
    file.write(content, length);

    if (file.fail()) {
        cout << "Error al escribir en el archivo" << endl;
        return;
    }

    cout << "Archivo actualizado correctamente"  << endl;
}

void readFile(fstream &file, char *content, unsigned long long length)
{
    unsigned long long fileLength = getFileLength(file);

    file.read(content, length);

    if (file.fail()) {
        cout << "Error al escribir en el archivo" << endl;
        return;
    }

    if (fileLength < length) {
        cout << "Advertencia: El contenido del archivo es menor que la longitud especificada" << endl;
    }
}

unsigned long long getFileLength(fstream &file)
{

    file.seekg(0, ios::end);
    unsigned long long length = file.tellg();
    file.seekg(0, std::ios::beg);

    return length;
}
