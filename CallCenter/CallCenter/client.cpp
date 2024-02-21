#include "client.hpp"

using namespace std;

/// IMPLEMENTACION CLASE CLIENT

Client::Client() { }

Client::Client(const Client& c) : nomClient(c.nomClient),horaLlamada(c.horaLlamada),durationCall(c.durationCall),agente(c.agente) { }

/// GETTERS

Name Client::getNomClient() const {
    return nomClient;
}

Time Client::getHoraLlamada() const {
    return horaLlamada;
}

Name Client::getAgente() const {
    return agente;
}

Time Client::getDurationCall() const {
    return durationCall;
}


std::string Client::toString() const {
    string result;

    result+= nomClient.toString();
    result.resize(20,' ');
    result+= " / ";
    result+= horaLlamada.toString();
    result+= " / ";
    result+= agente.toString();
    result+= " / ";
    result+= durationCall.toString();

    return result;
}

/// SETTERS

void Client::setNomClient(const Name& n) {
    nomClient = n;
}

void Client::setHoraLlamada(const Time& h) {
    horaLlamada = h;
}

void Client::setAgente(const Name& a) {
    agente = a;
}


void Client::setDurationCall(const Time& d) {
    durationCall = d;
}

/// OPERADORES

Client& Client::operator = (const Client& c) {
    nomClient = c.nomClient;
    horaLlamada = c.horaLlamada;
    durationCall = c.durationCall;
    agente = c.agente;

    return *this;
}

bool Client::operator==(const Client& c) const {
    return nomClient == c.nomClient;
}

bool Client::operator!=(const Client& c) const {
    return nomClient != c.nomClient;
}

bool Client::operator<(const Client& c) const {
    return nomClient < c.nomClient;
}

bool Client::operator<=(const Client& c) const {
    return nomClient <= c.nomClient;
}

bool Client::operator>(const Client& c) const {
    return nomClient > c.nomClient;
}

bool Client::operator>=(const Client& c) const {
    return nomClient >= c.nomClient;
}

/// FUNCIONES PARA QUE EL OBJETO SE ESCRIBA AL DISCO Y SE LEA DEL MISMO

ostream& operator << (ostream& os,const Client& c) {
    os << c.nomClient << endl;
    os << c.horaLlamada << endl;
    os << c.agente << endl;
    os << c.durationCall;

    return os;
}

istream& operator >> (istream& is, Client& c) {
    is >> c.nomClient;
    is >> c.horaLlamada;
    is >> c.agente;
    is >> c.durationCall;

    return is;
}
