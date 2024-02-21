#include <iostream>
#include <string>
#include <fstream>
#include <exception>

#include "agentmenu.hpp"
#include "agentlist.hpp"
#include "agent.hpp"
#include "clientlist.hpp"
#include "clientmenu.hpp"
#include "client.hpp"
#include "time.hpp"
#include "name.hpp"

using namespace std;

AgentMenu::AgentMenu(AgentList<Agent>& myList) {  /// CONSTRUCTOR PARA INICIALIZAR LA INTERFAZ
    userInterface(myList);
}

/// INTERFAZ DE USUARIO DEL MENU DE AGENTES

void AgentMenu::userInterface(AgentList<Agent>& myList) {

    int op;
    ClientList<Client> lse;
    ClientMenu menu;

    bool flag(true);
    do {
        system("cls");
        cout << "\t\t\tMenu de agentes" << endl << endl;
        cout << "1.Mostrar agentes almacenados\n2.Mostrar agentes por especialidad\n3.Agregar agente\n4.Buscar un agente\n5.Eliminar un agente por nombre\n";
        cout << "6.Eliminar todos los agentes\n7.Ordenar agentes por nombre o especialidad\n8.Guardar lista de agentes y clientes atendidos en almacenamiento secundario\n";
        cout << "9.Leer lista de agentes desde almacenamiento secundario\n10.Gestionar llamadas\n11.Salir\n";
        cout << "Ingrese el numero de opcion -> ";
        cin >> op;
        cin.ignore();
        switch(op) {
        case 1:
            showAgents(myList);
            break;
        case 2:
            showAgentsBySpecialty(myList);
            break;
        case 3:
            addAgent(myList);
            break;
        case 4:
            searchAgent(myList);
            break;
        case 5:
            deleteAgentbyName(myList);
            break;
        case 6:
            deleteAllAgents(myList);
            break;
        case 7:
            sortAgents(myList);
            break;
        case 8:
            writeToDisk(myList);
            break;
        case 9:
            readFromDisk(myList);
            break;
        case 10:
            menu.userInterface(myList);
            break;
        case 11:
            flag=false;
            break;
        default:
            cout << "Ingrese una opcion valida 7-7" << endl;
            system("pause");
        }
    } while(flag==true);
    cout << endl<< endl;
    system("cls");
    cout << "\t\t\t\tHasta pronto!!" << endl;
    system("pause");
}

/// FUNCION PARA AÑADIR AGENTE

void AgentMenu::addAgent(AgentList<Agent>& myList) {
    Agent myAgent;
    Time myTime;
    Name myName;
    string myStr;
    int myInt;
    char op;
    bool flag(true);
    bool usrLst(false);


    do {
        system("cls");
        cout << "\t\t\tAgregar agente" << endl << endl;

        cout << "Ingrese numero de agente: ";
        getline(cin,myStr);
        myAgent.setNumEmpleado(myStr);

        cout << "Ingrese nombre de empleado (nombre y apellido): ";
        getline(cin,myStr, ' ');
        myName.setFirst(myStr);
        getline(cin,myStr);
        myName.setLast(myStr);
        myAgent.setNomEmpleado(myName);

        cout << "Ingrese especialidad: ";
        getline(cin,myStr);
        myAgent.setEspecialidad(myStr);

        cout << "Ingrese numero de extension: ";
        cin >> myInt;
        cin.ignore();
        myAgent.setNumExt(myInt);

        cout << "Ingrese hora de entrada: (hh:mm): ";
        getline(cin,myStr,':');
        myTime.setHour(stoi(myStr));
        getline(cin,myStr);
        myTime.setMinute(stoi(myStr));
        myAgent.setHoraEntrada(myTime);

        cout << "Ingrese hora de salida: (hh:mm): ";
        getline(cin,myStr,':');
        myTime.setHour(stoi(myStr));
        getline(cin,myStr);
        myTime.setMinute(stoi(myStr));
        myAgent.setHoraSalida(myTime);

        cout << "Ingrese la cantidad de horas extras del agente: ";
        cin >> myInt;
        cin.ignore();
        myAgent.setHorasExt(myInt);

        myList.insertData(myList.getLastPos(),myAgent);

        cout << endl << endl;
        cout << "Agentes ingresados: " << endl;
        cout << myList.toString(usrLst) << endl << endl;

        cout << "Agente agregado con exito." << endl << endl;

        cout << "Desea agregar otro agente? (S/N): ";
        cin >> op;
        op = toupper(op);
        cin.ignore();
        if(op == 'N') {
            flag = false;
        }
    } while(flag==true);
    cout << "Por favor ingrese las llamadas desde la opcion N.10 -Gestionar llamadas- " << endl<< endl;
}

/// FUNCION PARA ELIMINAR AGENTE POR NOMBRE

void AgentMenu::deleteAgentbyName(AgentList<Agent>& myList) {
    Agent myAgent;
    string myStr;
    Name myName;
    AgentList<Agent>::Position pos;
    char op;
    bool usrLst(true);

    system("cls");
    cout << "\t\t\tEliminar agente" << endl << endl;

    if(myList.toString(usrLst) == "") {
        cout << "No hay agentes para mostrar..." << endl << endl;
    }

    cout << myList.toString(usrLst) << endl;

    cout << "Ingrese nombre del agente a eliminar (Nombre con espacios): ";
    getline(cin,myStr, ' ');
    myName.setFirst(myStr);
    getline(cin,myStr);
    myName.setLast(myStr);
    myAgent.setNomEmpleado(myName);

    pos = myList.findData(myAgent);

    if(pos==nullptr) {
        cout << "Elemento no encontrado...";
        cout << "regresando al menu..." << endl;
        system("pause");

    } else {
        cout << endl << endl;
        cout << "Elemento encontrado: " << myList.retrieve(pos).toString(usrLst) <<endl << endl;
        cout << "Esta seguro de eliminar el elemento? (S/N): ";
        cin >> op;
        op = toupper(op);
        cin.ignore();
        if(op=='S') {
            myList.deleteData(pos);
            cout << myList.toString(usrLst) << endl << endl;
            cout << "Elemento eliminado." << endl << endl;
            cout << "regresando al menu..." << endl;
            system("pause");
        } else {
            cout << "regresando al menu..." << endl;
            system("pause");
        }
    }
}

/// FUNCION PARA ELIMINAR TODOS LOS AGENTES DE LA LISTA

void AgentMenu::deleteAllAgents(AgentList<Agent>& myList) {
    char op;
    bool usrLst(true);
    system("cls");
    cout << "\t\t\tEliminar todos los agentes" << endl << endl;

    if(myList.toString(usrLst) == "") {
        cout << "No hay agentes para mostrar..." << endl << endl;
    }

    cout << myList.toString(usrLst) << endl << endl;

    cout << "Esta seguro de eliminar todos los agentes? (S/N): ";
    cin >> op;
    op = toupper(op);
    cin.ignore();
    if(op=='S') {
        myList.deleteAll();
        cout << "Agentes eliminados." << endl;
    }
    cout << "Regresando al menu..." << endl << endl;
    system("pause");
}

/// FUNCION PARA MODIFICAR AGENTE

void AgentMenu::modAgent(AgentList<Agent>& myList) {
    Agent myAgent;
    string myStr;
    Name myName;
    AgentList<Agent>::Position pos;
    char op;
    bool usrLst(true);

    system("cls");
    cout << "\t\t\tModificar agente" << endl << endl;

    if(myList.toString(usrLst) == "") {
        cout << "No hay agentes para mostrar..." << endl << endl;
    }

    cout << myList.toString(usrLst) << endl;

    cout << "Ingrese nombre del agente a modificar (Nombre con espacios): ";
    getline(cin,myStr, ' ');
    myName.setFirst(myStr);
    getline(cin,myStr);
    myName.setLast(myStr);
    myAgent.setNomEmpleado(myName);

    pos = myList.findData(myAgent);

    if(pos==nullptr) {
        cout << "Elemento no encontrado...";
        cout << "regresando al menu..." << endl;
        system("pause");

    } else {
        cout << "Elemento encontrado: ";
        cout << myList.retrieve(pos).toString(usrLst) << endl;
        cout << "Esta seguro de modificar el nombre del agente? (S/N): ";
        cin >> op;
        op = toupper(op);
        cin.ignore();
        if(op=='S') {
            myAgent = myList.retrieve(pos);
            cout << "Ingrese nombre de empleado (nombre y apellido): ";
            getline(cin,myStr, ' ');
            myName.setFirst(myStr);
            getline(cin,myStr);
            myName.setLast(myStr);
            myAgent.setNomEmpleado(myName);

            myList.modData(pos,myAgent);

            cout << endl << endl;
            cout << myList.toString(usrLst) << endl << endl;
            cout << "Elemento Modificado." << endl << endl;
            cout << "regresando al menu..." << endl;
            system("pause");
        } else {
            cout << "Regresando al menu..." << endl;
            system("pause");
        }
    }

}

/// FUNCION PARA MOSTRAR AGENTES DE LA LISTA

void AgentMenu::showAgents(AgentList<Agent>& myList) {
    char op;
    bool usrLst;

    system("cls");

    if(myList.toString(usrLst) == "") {
        cout << "No hay agentes para mostrar..." << endl << endl;
    }

    else {
        cout << "\t\t\tAgentes: " << endl << endl;
        cout << "Quiere mostrar lista de llamadas atendidas? (S/N): ";
        cin >> op;
        cin.ignore();
        op = toupper(op);

        if(op=='S') {
            usrLst = true;
        } else {
            usrLst = false;
        }
        cout << "N.empleado |         Nombre         | especialidad | Extension | Horario | Horas extras" << endl << endl;
        cout << myList.toString(usrLst) << endl;
    }
    cout <<"Regresando al menu..." << endl;
    system("pause");
}

/// FUNCION DEL MENU PARA BUSCAR AGENTE

void AgentMenu::searchAgent(AgentList<Agent>& myList) {
    Agent myAgent;
    string myStr;
    Name myName;
    AgentList<Agent>::Position pos;
    bool usrLst(true);

    system("cls");
    cout << "\t\t\tBuscar agente" << endl << endl;

    if(myList.toString(usrLst) == "") {
        cout << "No hay agentes para mostrar..." << endl << endl;
    }

    cout << myList.toString(usrLst) << endl;

    cout << "Ingrese nombre del agente a buscar (Nombre con espacios): ";
    getline(cin,myStr, ' ');
    myName.setFirst(myStr);
    getline(cin,myStr);
    myName.setLast(myStr);
    myAgent.setNomEmpleado(myName);

    pos = myList.findData(myAgent);

    if(pos==nullptr) {
        cout << "Elemento no encontrado..." << endl;
        cout << "Regresando al menu..." << endl;
        system("pause");

    } else {
        cout << "Elemento encontrado: ";
        cout << myList.retrieve(pos).toString(usrLst) << endl << endl;
        system("pause");
    }
}

/// FUNCION PARA MOSTRAR AGENTES POR ESPECIALIDAD

void AgentMenu::showAgentsBySpecialty(AgentList<Agent>& myList) {
    char op;
    bool usrLst;

    system("cls");

    if(myList.showBySpecialty(usrLst) == "") {
        cout << "No hay agentes para mostrar..." << endl << endl;
    }

    else {
        cout << "\t\t\tAgentes por especialidad: " << endl << endl;
        cout << "Quiere mostrar lista de llamadas atendidas? (S/N): ";
        cin >> op;
        cin.ignore();
        op = toupper(op);

        if(op=='S') {
            usrLst = true;
        } else {
            usrLst = false;
        }
        cout << "N.empleado |         Nombre         | especialidad | Extension | Horario | Horas extras" << endl << endl;

        try {
            cout << myList.showBySpecialty(usrLst) << endl;
        } catch(Exception ex) {
            cout << "Algo salio mal..." << endl;
            cout << ex.what();
        }
    }
    cout <<"Regresando al menu..." << endl;
    system("pause");
}

/// IMPLEMENTACION DE LA FUNCION ORDENA EN MENU DE AGENTES

void AgentMenu::sortAgents(AgentList<Agent>& myList) {
    Agent myAgent;
    int op;
    bool usrLst(false);

    system("cls");
    cout << "\t\t\tOrdenar agentes\n\n";

    cout << "1.Ordenar por nombre\n2.Ordenar por especialidad\n";
    cout << "Ingrese el numero de opcion ->";
    cin >> op;
    cin.ignore();

    switch(op) {
    case 1:
        myList.sortByName();
        cout << myList.toString(usrLst) << endl << endl;
        cout << "Se ha ordenado correctamente! \n";

        break;
    case 2:
        myList.sortBySpecialty();
        cout << myList.toString(usrLst) << endl << endl;
        cout << "Se ha ordenado correctamente! \n";
        break;
    default:
        cout << "Ingrese un valor valido 7-7\n";
        system("pause");
        //return;
    }
    cout << "Regresando al menu..." << endl << endl;
    system("pause");
}

/// FUNCION PARA ESCRIBIR AL DISCO

void AgentMenu::writeToDisk(AgentList<Agent>& myList) {
    system("cls");
    cout << "Escribiendo al disco..." << endl << endl;

    try {
        myList.writeToDisk("agentslist.txt");
    } catch(Exception ex) {
        cout << "Hubo un problema...";
        cout << ex.what();

        system("pause");

        return;
    }

    cout << "Escritura exitosa! " << endl << endl;
    system("pause");
}

/// FUNCION PARA LEER EL ARCHIVO DEL DISCO

void AgentMenu::readFromDisk(AgentList<Agent>& myList) {
    system("cls");
    cout << "Leyendo archivo..." << endl;

    try {
        myList.readFromDisk("agents.list");
    } catch(Exception ex) {
        cout << "Hubo un problema..." << endl;
        cout << ex.what() << endl << endl;

        system("pause");

        return;
    }

    cout << "La lectura finalizo exitosamente" << endl << endl;
    cout << "Advertencia: para leer los registros de llamadas vaya a la opcion N.10 'Gestionar llamadas'" << endl << endl;
    system("pause");

}
