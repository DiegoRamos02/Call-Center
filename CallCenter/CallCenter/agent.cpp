#include <iostream>
#include <string>

#include "agent.hpp"
#include "client.hpp"
#include "clientlist.hpp"

using namespace std;

/// IMPLEMENTACION DE LA CLASE AGENT

Agent::Agent() { }

Agent::Agent(const Agent& a) : numEmpleado(a.numEmpleado),nomEmpleado(a.nomEmpleado),especialidad(a.especialidad),
    numExt(a.numExt),horaEntrada(a.horaEntrada),horaSalida(a.horaSalida),horasExt(a.horasExt),userList(a.userList) { }

/// GETTERS

string Agent::getNumEmpleado() const {
    return numEmpleado;
}

Name Agent::getNomEmpleado() const {
    return nomEmpleado;
}

string Agent::getEspecialidad() const {
    return especialidad;
}

int Agent::getNumExt() const {
    return numExt;
}

Time Agent::getHoraEntrada() const {
    return horaEntrada;
}

Time Agent::getHoraSalida() const {
    return horaSalida;
}

int Agent::getHorasExt() const {
    return horasExt;
}

ClientList<Client> Agent::getUserList() {
    return userList;
}

string Agent::toString(bool u) const {
    string result;

    result+= numEmpleado;
    result+= " / ";
    result+= nomEmpleado.toString();
    result.resize(35,' ');
    result+= " / ";
    result+= especialidad;
    result.resize(52,' ');
    result+= " / ";
    result+= to_string(numExt);
    result+= " / ";
    result+= horaEntrada.toString();
    result+= "|";
    result+= horaSalida.toString();
    result+= " / ";
    result+= to_string(horasExt);
    if(u==true) {
        result+= " \nLista de clientes\n";
        result+= "*********************************************************\n";
        result+= "Nombre del cliente | Hora de llamada | Agente que atendio | Duracion de llamada\n";
        result+= userList.toString();
    }
    return result;
}

/// SETTERS

void Agent::setNumEmpleado(const std::string& ne) {
    numEmpleado = ne;
}

void Agent::setNomEmpleado(const Name& ne) {
    nomEmpleado = ne;
}

void Agent::setEspecialidad(std::string& e) {
    especialidad = e;
}

void Agent::setNumExt(const int& n) {
    numExt = n;
}

void Agent::setHoraEntrada(const Time& h) {
    horaEntrada = h;
}

void Agent::setHoraSalida(const Time& h) {
    horaSalida = h;
}

void Agent::setHorasExt(const int& h) {
    horasExt = h;
}

void Agent::setUserList(ClientList<Client>& u) {
    userList = u;
}

/// OPERADOR DE COMPARACION

Agent& Agent::operator = (const Agent& a) {
    numEmpleado = a.numEmpleado;
    nomEmpleado = a.nomEmpleado;
    especialidad = a.especialidad;
    numExt = a.numExt;
    horaEntrada = a.horaEntrada;
    horaSalida = a.horaSalida;
    horasExt = a.horasExt;
    userList = a.userList;

    return *this;
}

/// OPERADORES

bool Agent::operator==(const Agent& a) const {
    return nomEmpleado == a.nomEmpleado;
}

bool Agent::operator!=(const Agent& a) const {
    return nomEmpleado != a.nomEmpleado;
}

bool Agent::operator<(const Agent& a) const {
    return nomEmpleado < a.nomEmpleado;
}

bool Agent::operator<=(const Agent& a) const {
    return nomEmpleado <= a.nomEmpleado;
}

bool Agent::operator>(const Agent& a) const {
    return nomEmpleado > a.nomEmpleado;
}

bool Agent::operator>=(const Agent& a) const {
    return nomEmpleado >= a.nomEmpleado;
}

/// FUNCIONES PARA QUE EL OBJETO SE PUEDA ESCRIBIR AL DISCO Y LEER DEL MISMO

ostream& operator << (ostream& os, const Agent& a) {
    char myExt[9],myHorExt[100];
    string myAgent;
    sprintf(myExt, "%i", a.numExt);
    sprintf(myHorExt, "%i", a.horasExt);

    os << a.numEmpleado << endl;
    os << a.nomEmpleado << endl;
    os << a.especialidad << endl;
    os << myExt << endl;
    os << a.horaEntrada << endl;
    os << a.horaSalida << endl;
    os << myHorExt;

    return os;
}

istream& operator >> (istream& is,Agent& a) {
    string myStr;

    getline(is, a.numEmpleado);
    is >> a.nomEmpleado;
    getline(is,a.especialidad);
    getline(is,myStr);
    a.numExt = atoi(myStr.c_str());
    is >> a.horaEntrada;
    is >> a.horaSalida;
    getline(is,myStr);
    a.horasExt = atoi(myStr.c_str());

    return is;
}

