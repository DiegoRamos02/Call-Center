#include <locale.h>

#include "mainmenu.hpp"
#include "agent.hpp"
#include "agentlist.hpp"
#include "agentmenu.hpp"

/// PANTALLA DE INICIO DEL PROGRAMA QUE MUESTRA EL NOMBRE DE LA EMPRESA

void MainMenu::menu() {
    setlocale (LC_CTYPE, "Spanish"); // PERMITE CARARCTERES EN ESPAÑOL
    AgentList<Agent> myList;
    cout << endl << endl << endl << endl << endl << endl << endl ;
    cout << "\t\t\t\t\t  W       W    CCCCCC" << endl;
    cout << "\t\t\t\t\t  W       W    C" << endl;
    cout << "\t\t\t\t\t  W   W   W    C" << endl;
    cout << "\t\t\t\t\t   W W W W     C" << endl;
    cout << "\t\t\t\t\t    W   W      CCCCCC" << endl;
    cout << endl <<"\t\t\t\t\t   WORLD COMMUNICATIONS" << endl << endl << endl << endl ;

    cout << " -Diego Eduardo Ramos Gutierrez.\n -Seminario de solucion de problemas de estructuras de datos I .\n\n ";
    system("pause");
    AgentMenu menu(myList);
}
