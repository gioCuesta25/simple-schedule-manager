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
    cout << "******************** CURSOS DISPONIBLES ********************" << endl;
    for (unsigned long long j = 0; j < totalLines; j++) {
        cout << courses[j] << endl;
    }
    cout << "************************************************************" << endl << endl;
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
    char*** matrix = new char**[ROWS];

    loadSchedule(schedule, matrix); // Llena la matriz con el horario obtenido desde el archivo

    switch (option) {
    case 1:{
        printSchedule(matrix);
        break;
    }
    case 2: {
        updateSchedule(matrix);
        break;
    }
    default: {
        cout << "Opcion invalida" << endl;
        break;
    }
    }
    //freeMemory(matrix);
}

void printSchedule(char***matrix)
{
    cout << endl << endl;
    cout << "Lunes" << '\t' << "Martes" << '\t' << "Mierco" << '\t' << "Jueves" << '\t' << "Viernes" << '\t' << "Sabado" << '\t' << "Domingo" << endl;
    for (int k = 0; k < ROWS; k++) {
        for (int l = 0; l < COLS; l++) {
            cout << matrix[k][l] << '\t';
        }
        cout << endl;
    }
}

void updateSchedule(char ***matrix)
{
    int option;

    cout << "************* Accines *************" << endl;
    cout << "1. Agregar una clase" << endl;
    cout << "2. Agregar horas de trabajo independiente para una clase" << endl;
    cout << "3. Quitar una clase" << endl;

    cout << "Selecciona un accion: ";
    cin >> option;

    switch (option) {
    case 1: {
        addClass(matrix);
        break;
    }
    default:{
        cout << "Opcion invalida" << endl;
        break;
    }
    }

}


void loadSchedule(fstream &file, char ***matrix)
{
    file.seekg(0, file.end);
    unsigned long long fileLength = file.tellg();
    file.seekg(0, file.beg);

    char * fileContent = new char[fileLength];

    file.read(fileContent, fileLength);

    char delimiter = ',';

    int row = 0;
    int col = 0;
    int elementIndex = 0;

    for (int i = 0; i < ROWS; i++)
    {
        matrix[i] = new char*[COLS];
        for (int j = 0; j < COLS; j++) {
            matrix[i][j] = new char[ELEMENT_LENGTH];
        }
    }

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

}

void freeMemory(char ***matrix)
{
    // Limpiar la memoria
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++) {
            delete[] matrix[i][j];
        }
        delete[] matrix[i];
    }

    delete[] matrix;
}

void addClass(char ***matrix)
{
    fstream courses;
    courses.open("cursos.txt", ios::binary | ios::in | ios::out | ios::ate);

    int option;

    do {
        cout << "************* Acciones *************" << endl;
        cout << "1. Agregar" << endl;
        cout << "2. Guardar" << endl;;

        cout << "Selecciona un accion: ";
        cin >> option;

        switch (option) {
        case 1: {
            printInstructions();
            showAllCourses(courses);


            char courseCode[8];
            int startHour, endHour, day;

            cin.ignore();
            cout << "Ingresa el codigo del curso: ";
            cin.getline(courseCode, 8);

            cout << "Hora de inicio: ";
            cin >> startHour;

            cout << "Hora de fin: ";
            cin >> endHour;

            cout << "Dia: ";
            cin >> day;

            modifySchedule(matrix, courseCode, startHour, endHour, day);
            break;
        }
        case 2: {
            break;
        }
        default: {
            cout << "Opcion invalida" << endl;
            break;
        }
        }

    } while (option != 2);
}

void printInstructions()
{
    cout << endl << endl;
    cout << "******************** INSTRUCCIONES ********************" << endl;
    cout << "Sigue los siguientes pasos para agregar un curso: " << endl;
    cout << "1. Ingresa el codigo del curso que deseas agregar,\nencontraras la lista de cursos luego de este aviso" << endl << endl;
    cout << "2. Luego ingresa la hora de inicio y la hora de fin, debe ser en formato 24h.\nEjemplo: si tu clase inicia a las 10am y finaliza a las 2pm debes ingresar 10 y 14 respectivamente" << endl << endl;
    cout << "3. Ingresa el dia, en este caso debes ingresar el numero del dia.\nEjemplo: para el lunes ingresa el 1, el 2 para el martes, 3 para el miercoles y así hasta el domingo" << endl << endl;
    cout << "************************************************************" << endl << endl;
}

void modifySchedule(char ***matrix, char code[], int start, int end, int day)
{
    int duration = end - start;
    int row = start - 6;
    int col = day - 1;

    for (int i = 0; i < duration; i++) {
        matrix[row + i][col] = code;
    }

    printSchedule(matrix);
}
