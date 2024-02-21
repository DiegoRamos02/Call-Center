#include <iostream>

#include "clientmenu.hpp"
#include "clientlist.hpp"
#include "time.hpp"
#include "name.hpp"
#include "client.hpp"
#include "agent.hpp"
#include "agentlist.hpp"

using namespace std;

/// IMPLEMENTACION DE LA CLASE CLIENT MENU



/// FUNCION QUE DESPLIEGA EL MENU
void ClientMenu::userInterface(AgentList<Agent>& myList) {
    int op;
    bool flag(true);
    do {
        system("cls");
        cout << "\t\t\tMenu de Llamadas" << endl << endl;
        cout << "1.Agregar llamada\n2.Eliminar llamada\n3.Eliminar todas las llamadas\n4.Modificar duracion de llamada" << endl;
        cout << "5.Leer clientes desde almacenamiento secundario\n6.Salir\n";
        cout << "Ingrese una opcion: ";
        cin >> op;
        cin.ignore();
        switch(op) {
        case 1:
            addClientToAgent(myList);
            break;
        case 2:
            deleteClient(myList);
            break;
        case 3:
            deleteAllClients(myList);
            break;
        case 4:
            modCallTime(myList);
            break;
        case 5:
            readFromDisk(myList);
            break;
        case 6:
            flag = false;
            break;
        default:
            cout << "Por favor ingrese una opcion valida 7-7";
        }
    } while(flag==true);
    cout << "Regresando al menu..." << endl;
    system("pause");
    system("cls");
}

/// FUNCION PARA AÑADIR UN CLIENTE AL AGENTE

void ClientMenu::addClientToAgent(AgentList<Agent>& myList) {
    string myStr;
    int myInt;
    Name myName;
    Time myTime;
    Client myClient;
    Agent myAgent,auxAgent;
    bool usrLst(true);
    char op1;
    AgentList<Agent>::Position pos;
    ClientList<Client> lse;

    do {
        system("cls");
        cout << "\t\t\tAgregar llamada a cliente" << endl << endl;
        cout << "Ingrese nombre del cliente: ";
        getline(cin, myStr);
        myName.setFirst(myStr);

        cout << "Ingrese apellido del cliente: ";
        getline(cin, myStr);
        myName.setLast(myStr);
        myClient.setNomClient(myName);

        cout << "Ingrese hora de llamada: ";
        cin >> myInt;
        cin.ignore();
        myTime.setHour(myInt);

        cout << "Ingrese minutos de llamada: ";
        cin >> myInt;
        cin.ignore();
        myTime.setMinute(myInt);
        myClient.setHoraLlamada(myTime);

        cout << "Ingrese hora de duracion de llamada:";
        cin >> myInt;
        cin.ignore();
        myTime.setHour(myInt);

        cout << "Ingrese minutos de duracion de llamada:";
        cin >> myInt;
        cin.ignore();
        myTime.setMinute(myInt);
        myClient.setDurationCall(myTime);

        cout << endl << endl;
        cout << myList.toString(usrLst) << endl << endl;
        cout << "Ingrese el nombre del agente responsable de atender: (Incluya espacios): ";
        getline(cin,myStr, ' ');
        myName.setFirst(myStr);
        getline(cin,myStr);
        myName.setLast(myStr);

        myClient.setAgente(myName);

        auxAgent.setNomEmpleado(myName);
        pos = myList.findData(auxAgent);

        if(pos==nullptr) {
            cout << "El agente no se encuentra en la lista, favor de intentar nuevamente..." << endl;
            system("pause");
            return;
        } else {
            myAgent = myList.retrieve(pos);
            lse = myAgent.getUserList();
            lse.insertOrdered(myClient);
            myAgent.setUserList(lse);
            myList.modData(pos,myAgent);

            cout << myList.toString(usrLst) << endl << endl;
            cout << "Llamada ingresada correctamente! " << endl;
            cout << "Ingresar otra llamada? (S/N): ";
            cin >> op1;
            op1 = toupper(op1);
            cin.ignore();
        }
    } while(op1!='N');

    lse.deleteAll();
    myAgent.setUserList(lse);
    cout << "Regresando al menu..." << endl;
    system("pause");
}

/// FUNCION PARA ELIMINAR UN CLIENTE

void ClientMenu::deleteClient(AgentList<Agent>& myList) {
    string myStr;
    Agent myAgent,auxAgent;
    AgentList<Agent>::Position pos;
    ClientList<Client>::Position pos1;
    ClientList<Client> lse;
    Name myName;
    Client myClient;
    bool usrLst(true);

    system("cls");
    cout << "\t\t\tEliminar llamada" << endl << endl;
    cout << myList.toString(usrLst) << endl << endl;
    cout << "Ingrese el nombre del agente responsable de atender: (Incluya espacios): ";
    getline(cin,myStr, ' ');
    myName.setFirst(myStr);
    getline(cin,myStr);
    myName.setLast(myStr);

    auxAgent.setNomEmpleado(myName);
    pos = myList.findData(auxAgent);

    if(pos==nullptr) {
        cout << "El agente no se encuentra en la lista, favor de intentar nuevamente..." << endl;
        system("pause");
    } else {
        myAgent = myList.retrieve(pos);
        lse = myAgent.getUserList();

        cout << lse.toString() << endl << endl;

        cout << "Ingrese el nombre del cliente: (Incluya espacios): ";
        getline(cin,myStr, ' ');
        myName.setFirst(myStr);
        getline(cin,myStr);
        myName.setLast(myStr);

        myClient.setNomClient(myName);

        pos1 = lse.findData(myClient);

        if(pos1==nullptr) {
            cout << "El cliente no se encuentra en la lista, favor de intentar nuevamente..." << endl;
            system("pause");
        } else {
            lse.deleteData(pos1);
            myAgent.setUserList(lse);
            myList.modData(pos,myAgent);
            cout << myList.toString(usrLst) << endl << endl;
            cout << "Llamada eliminada! " << endl << endl;
            cout << "Regresando al menu..." << endl;
            system("pause");
        }
    }

}

/// FUNCION PARA ELLIMINAR TODOS LOS CLIENTES

void ClientMenu::deleteAllClients(AgentList<Agent>& myList) {
    string myStr;
    Agent myAgent,auxAgent;
    AgentList<Agent>::Position pos;
    ClientList<Client> lse;
    Name myName;
    char op1;
    bool usrLst(true);

    system("cls");
    cout << "\t\t\tEliminar todas las llamadas" << endl << endl;
    cout << myList.toString(usrLst) << endl << endl;
    cout << "Ingrese el nombre del agente responsable de atender: (Incluya espacios): ";
    getline(cin,myStr, ' ');
    myName.setFirst(myStr);
    getline(cin,myStr);
    myName.setLast(myStr);

    auxAgent.setNomEmpleado(myName);
    pos = myList.findData(auxAgent);

    if(pos==nullptr) {
        cout << "El agente no se encuentra en la lista, favor de intentar nuevamente..." << endl;
        system("pause");
    } else {
        myAgent = myList.retrieve(pos);
        lse = myAgent.getUserList();

        cout << "Esta seguro de eliminar todo? (S/N): ";
        cin >> op1;
        cin.ignore();
        op1 = toupper(op1);
        if(op1=='S') {
            lse.deleteAll();
            myAgent.setUserList(lse);
            myList.modData(pos,myAgent);
            cout << myList.retrieve(pos).toString(usrLst) << endl << endl;
            cout << "Eliminado completado! " << endl << endl;
        }
        cout << "Regresando al menu..." << endl;
        system("pause");
    }

}

/// FUNCION PARA MODIFICAR EL TIEMPO DE LA LLAMADA

void ClientMenu::modCallTime(AgentList<Agent>& myList) {
    string myStr;
    Agent myAgent,auxAgent;
    Client myClient;
    AgentList<Agent>::Position pos;
    ClientList<Client> lse;
    ClientList<Client>::Position pos1;
    Name myName;
    Time myTime;
    char op1;
    bool usrLst(true);

    system("cls");
    cout << "\t\t\tModifica hora de llamada" << endl << endl;
    cout << myList.toString(usrLst) << endl << endl;
    cout << "Ingrese el nombre del agente responsable de atender: (Incluya espacios): ";
    getline(cin,myStr, ' ');
    myName.setFirst(myStr);
    getline(cin,myStr);
    myName.setLast(myStr);

    auxAgent.setNomEmpleado(myName);
    pos = myList.findData(auxAgent);

    if(pos==nullptr) {
        cout << "El agente no se encuentra en la lista, favor de intentar nuevamente..." << endl;
        system("pause");
    } else {
        myAgent = myList.retrieve(pos);
        lse = myAgent.getUserList();

        cout << lse.toString() << endl << endl;

        cout << "Ingrese el nombre del cliente: (Incluya espacios): ";
        getline(cin,myStr, ' ');
        myName.setFirst(myStr);
        getline(cin,myStr);
        myName.setLast(myStr);

        myClient.setNomClient(myName);

        pos1 = lse.findData(myClient);

        if(pos1==nullptr) {
            cout << "El cliente no se encuentra en la lista, favor de intentar nuevamente..." << endl;
            system("pause");
        } else {
            cout << "Esta seguro de modificar la llamada? (S/N): ";
            cin >> op1;
            cin.ignore();
            op1 = toupper(op1);
            if(op1=='S') {

                myClient = lse.retrieve(pos1);

                cout << "ingrese la nueva duracion de llamda: (mm:ss): ";
                getline(cin,myStr,':');
                myTime.setHour(stoi(myStr));
                getline(cin,myStr);
                myTime.setMinute(stoi(myStr));
                myClient.setDurationCall(myTime);

                lse.modData(pos1,myClient);
                myAgent.setUserList(lse);
                myList.modData(pos,myAgent);

                cout << myList.toString(usrLst) << endl << endl;
                cout << "Llamada modificada! " << endl << endl;
            }

            cout << "Regresando al menu..." << endl;
            system("pause");
        }
    }
}

/// FUNCION PARA ESCRIBIR AL DISCO LA LISTA DE CLIENTES

void ClientMenu::readFromDisk(AgentList<Agent>& myList) {
    Agent myAgent;
    AgentList<Agent> lde;
    AgentList<Agent>::Position pos1;
    Client myClient;
    ClientList<Client> lse;
    string myStr;
    bool usrLst(true);
    Name myName;

    system("cls");
    cout << "\t\t\tLeer clientes desde almacenamiento secundario\n\n";
    cout << myList.toString(usrLst) << endl << endl;
    cout << "*Nota, los archivos deben estar generados previamente\n\n";
    cout << "Ingresa nombre y apellido (separado por nombre): ";
    getline(cin, myStr, ' ');
    myName.setFirst(myStr);
    getline(cin, myStr);
    myName.setLast(myStr);

    myAgent.setNomEmpleado(myName);

    pos1 = myList.findData(myAgent);

    if(pos1 == nullptr) {
        cout << "El agente no se encuentra en la lista..." << endl;
    } else {
        myAgent = myList.retrieve(pos1);

        lse = myAgent.getUserList();

        cout << "Restaurando registros del agente: " << myAgent.getNomEmpleado() << endl << endl;

        lse.readFromDisk(myAgent.getNumEmpleado() + ".agents");

        myAgent.setUserList(lse);

        myList.modData(pos1,myAgent);

        cout << myList.toString(usrLst) << endl << endl;
        cout << "Los datos se han escrito exitosamente!\n\n";
    }

    cout << "Regresando al menu..." << endl;
    system("pause");
}

