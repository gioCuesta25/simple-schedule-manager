#include <iostream>
#include <fstream>
#include "functions.h"

using namespace std;

int main()
{
    int opc;

    do {
        opc = menu();
        switch (opc) {
        case 1:{
            manageCourses();
            break;
        }
        case 2:{
            manageSchedule();
            break;
        }
        default: {
            cout << "Opcion invalida" << endl;
            break;
        }
        }
    } while (opc != 0);

    return 0;
}
