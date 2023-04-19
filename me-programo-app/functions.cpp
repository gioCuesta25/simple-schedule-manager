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

// Funciones para gestionar los cursos

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
    case 2:{
        showAllCourses(courses);
        break;
    }
    default: {
        cout << "Opcion invalida" << endl;
        break;
    }
    }

    courses.close();
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

void showAllCourses(fstream &file)
{
    file.seekg(0, file.end);
    unsigned long long fileLength = file.tellg();
    file.seekg(0, file.beg);

    char * fileContent = new char[fileLength];

    file.read(fileContent, fileLength);

    unsigned long long index = 0;
    unsigned long long total = 0;

    while (index < fileLength) {
        if (fileContent[index] == '\n') total++;
        index++;
    }

    char courses[total][400];

    unsigned long long i = 0;
    unsigned long long j = 0;

    while (i < fileLength && j < total) {
        int k = 0;
        while (i < fileLength && fileContent[i] != '\n' && k < 400-1) {
            courses[j][k] = fileContent[i];
            i++;
            k++;
        }
        courses[j][k] = '\0';
        i++;
        j++;
    }

    unsigned long long totalLines = j;

    for (unsigned long long j = 0; j < totalLines; j++) {
        cout << courses[j] << endl;
    }
}



// Funciones para administrar el horario
void manageSchedule()
{
    int option;

    cout << endl;
    cout << "******************** Administrar horario ********************" << endl;
    cout << "1. Ver mi horario" << endl;
    cout << "2. Actualizar mi horario" << endl;

    cout << "Selecciona una opcion: ";
    cin >> option;

    fstream schedule;
    schedule.open("horario.txt", ios::binary | ios::in | ios::out | ios::ate);

    switch (option) {
    case 1:{
        printSchedule(schedule);
        break;
    }
    case 2: {
        updateSchedule(schedule);
        break;
    }
    default: {
        cout << "Opcion invalida" << endl;
        break;
    }
    }

}

void printSchedule(fstream &file)
{
    file.seekg(0, file.end);
    unsigned long long fileLength = file.tellg();
    file.seekg(0, file.beg);

    char * fileContent = new char[fileLength];

    file.read(fileContent, fileLength);

    int ROWS = 18;
    int COLS = 7;
    int ELEMENT_LENGTH = 8;
    char matrix[ROWS][COLS][ELEMENT_LENGTH];
    char delimiter = ',';

    int row = 0;
    int col = 0;
    int elementIndex = 0;

    for (unsigned long long i = 0; i < fileLength; i++) {
        if (fileContent[i] == delimiter) {
            matrix[row][col][elementIndex] = '\0';
            col++;
            elementIndex = 0;
            continue;
        }
        if (fileContent[i] == '\n') {
            matrix[row][col][elementIndex] = '\0';
            row++;
            col = 0;
            elementIndex = 0;
            continue;
        }
        matrix[row][col][elementIndex] = fileContent[i];
        elementIndex++;
    }
    cout << endl << endl;
    cout << "Lunes" << '\t' << "Martes" << '\t' << "Mierco" << '\t' << "Jueves" << '\t' << "Viernes" << '\t' << "Sabado" << '\t' << "Domingo" << endl;
    for (int k = 0; k < ROWS; k++) {
        for (int l = 0; l < COLS; l++) {
            cout << matrix[k][l] << '\t';
        }
        cout << endl;
    }
}

void updateSchedule(fstream &file)
{
    file.seekg(0, file.end);
    unsigned long long fileLength = file.tellg();
    file.seekg(0, file.beg);

    char * fileContent = new char[fileLength];

    file.read(fileContent, fileLength);

    int ROWS = 18;
    int COLS = 7;
    int ELEMENT_LENGTH = 8;
    char matrix[ROWS][COLS][ELEMENT_LENGTH];
    char delimiter = ',';

    int row = 0;
    int col = 0;
    int elementIndex = 0;

    for (unsigned long long i = 0; i < fileLength; i++) {
        if (fileContent[i] == delimiter) {
            matrix[row][col][elementIndex] = '\0';
            col++;
            elementIndex = 0;
            continue;
        }
        if (fileContent[i] == '\n') {
            matrix[row][col][elementIndex] = '\0';
            row++;
            col = 0;
            elementIndex = 0;
            continue;
        }
        matrix[row][col][elementIndex] = fileContent[i];
        elementIndex++;
    }

    for (int k = 0; k < ROWS; k++) {
        for (int l = 0; l < COLS; l++) {
            cout << matrix[k][l] << " ";
        }
        cout << endl;
    }
}

