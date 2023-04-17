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

int menu()
{
    int opc;

    cout << "\n******************** MENU ********************" << endl;
    cout << "1. Gestionar informacion de cursos" << endl;
    cout << "2. Gestionar mi horario" << endl;

    cout << "Selecciona una opcion (0 para salir): ";
    cin >> opc;

    return opc;
}

void manageCourses()
{
    int option;

    cout << endl;
    cout << "******************** MENU ********************" << endl;
    cout << "1. Agregar nuevo curso" << endl;
    cout << "2. Ver todos los cursos" << endl;

    cout << "Selecciona una opcion: ";
    cin >> option;

    fstream courses;
    courses.open("cursos.txt", ios::binary | ios::in | ios::out | ios::ate);

    switch (option) {
    case 1:{
        addCourse(courses);
        break;
    }
    default: {
        cout << "Opcion invalida" << endl;
        break;
    }
    }
}

void addCourse(fstream &file)
{
    if (!file.is_open()) {
        cout << "Error abriendo el archivo" << endl;
        return;
    }

    char code[100];
    char name[100];
    int htd; // Horas de trabajo con docente
    int credits;
    int hti; // Horas de trabajo independiente

    cout << endl;
    cin.ignore();
    cout << "Codigo de la materia: ";
    cin.getline(code, 100);

    cout << "Nombre de la materia: ";
    cin.getline(name, 100);

    cout << "Creditos de la materia: ";
    cin >> credits;

    cout << "Horas de trabajo docente (HTD): ";
    cin >> htd;

    hti = ((credits * 48)/16) - htd;

    file << code << "," << name << "," << credits << "," << htd << "," << hti << "\n";
}


void manageSchedule()
{

}

