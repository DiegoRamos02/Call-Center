#ifndef CLIENTLIST_H_INCLUDED
#define CLIENTLIST_H_INCLUDED

#include <iostream>
#include <fstream>
#include <string>
#include <exception>

#include "client.hpp"

/// DEFINICION CLASE CLIENT LIST

using namespace std;

template <class T>
class ClientList {
  private:
    class ClientNode { /// CLIENT NODE
      private:
        T data;
        ClientNode* next;
      public:
        ClientNode();
        ClientNode(const T&);

        T getData() const;
        ClientNode* getNext() const;

        void setData(const T&);
        void setNext(ClientNode*);
    };

    ClientNode* anchor;

    void copyAll(const ClientList<T>&);

    bool isValidPos(ClientNode*) const;

  public:
    typedef ClientNode* Position;

    class Exception : public std::exception {
      private:
        std::string msg;

      public:
        explicit Exception(const char* message) : msg(message) {}

        explicit Exception(const std::string& message) : msg(message) {}

        virtual ~Exception() throw () {}

        virtual const char* what() const throw () {
            return msg.c_str();
        }
    };

    ClientList();
    ClientList(const ClientList<T>&);

    ~ClientList();

    bool isEmpty() const;

    void insertData(ClientNode*, const T&);

    void deleteData(ClientNode*);

    void modData(ClientNode*,const T&);

    ClientNode* getFirstPos() const;
    ClientNode* getLastPos() const;
    ClientNode* getPrevPos(ClientNode*) const;
    ClientNode* getNextPos(ClientNode*) const;

    ClientNode* findData(const T&) const;

    T retrieve(ClientNode*) const;

    std::string toString() const;

    void deleteAll();

    ClientList<T>& operator = (const ClientList<T>&);

    void insertOrdered(const T&);

    void writeToDisk(const std::string&);
    void readFromDisk(const std::string&);
};

/// --I M P L E M E N T A C I O N   C L A S E   C L I E N T   L I S T--


/// IMPLEMENTACION CLASE CLIENT NODE


template <class T>
ClientList<T>::ClientNode::ClientNode() : next(nullptr) { }

template <class T>
ClientList<T>::ClientNode::ClientNode(const T& e) : data(e), next(nullptr) { }

template <class T>
T ClientList<T>::ClientNode::getData() const {
    return data;
}

template <class T>
typename ClientList<T>::ClientNode* ClientList<T>::ClientNode::getNext() const {
    return next;
}

template <class T>
void ClientList<T>::ClientNode::setData(const T& e) {
    data = e;
}

template <class T>
void ClientList<T>::ClientNode::setNext(ClientNode* p) {
    next = p;
}

/// IMPLEMENTACION CLIENTLIST

template <class T>

/// COPY ALL METHOD

void ClientList<T>::copyAll(const ClientList<T>& l) {
    ClientNode* aux(l.anchor);
    ClientNode* last(nullptr);
    ClientNode* newNode;

    while(aux != nullptr) {
        newNode = new ClientNode(aux->getData());

        if(last==nullptr) {
            anchor = newNode;
        } else {
            last->setNext(newNode);
        }
        last = newNode;

        aux = aux->getNext();
    }
}

/// COMPROBORAR QUE LA POSICION SEA VALIDA

template <class T>
bool ClientList<T>::isValidPos(ClientNode* p)const {
    ClientNode* aux(anchor);

    while(aux != nullptr) {
        if(aux==p) {
            return true;
        }

        aux= aux->getNext();
    }
    return false;
}

/// CONSTRUCTOR CLASE CLIENTE

template <class T>
ClientList<T>::ClientList() : anchor(nullptr) { }

/// CONSTRUCTOR COPIA

template <class T>
ClientList<T>::ClientList(const ClientList<T>& l) : anchor(nullptr) {
    copyAll(l);
}

/// DESTRUCTOR

template <class T>
ClientList<T>::~ClientList() {
    deleteAll();
}

/// VALIDA QUE LA LISTA ESTE VACIA

template <class T>
bool ClientList<T>::isEmpty() const {
    return anchor == nullptr;
}

/// INSERTA CLIENTES

template <class T>
void ClientList<T>::insertData(ClientNode* p,const T& e) {
    if(p != nullptr and !isValidPos(p)) {
        throw Exception("Posicion invalida, insertData");
    }

    ClientNode* aux(new ClientNode(e));

    if(aux==nullptr) {
        throw Exception("Memoria no disponible, insertData");
    }

    if(p==nullptr) {
        aux->setNext(anchor);
        anchor = aux;
    } else {
        aux->setNext(p->getNext());
        p->setNext(aux);
    }
}

/// ELIMINA CLIENTES

template <class T>
void ClientList<T>::deleteData(ClientNode* p) {
    if(!isValidPos(p)) {
        throw Exception("Posicion invalida, deleteData");
    }

    if(p==anchor) {
        anchor = anchor->getNext();
    } else {
        getPrevPos(p)->setNext(p->getNext());
    }
    delete p;
}

/// OBTIENE LA PRIMERA Y ULTIMA POSICION

template <class T>
typename ClientList<T>::ClientNode* ClientList<T>::getFirstPos() const {
    return anchor;
}

template <class T>
typename ClientList<T>::ClientNode* ClientList<T>::getLastPos() const {
    if(isEmpty()) {
        return nullptr;
    }

    ClientNode* aux(anchor);

    while(aux->getNext() != nullptr) {
        aux = aux->getNext();
    }
    return aux;
}

/// OBTIENE LA POSICION PREVIA Y SIGUIENTE

template <class T>
typename ClientList<T>::ClientNode* ClientList<T>::getPrevPos(ClientNode* p) const {
    if(p==anchor) {
        return nullptr;
    }

    ClientNode* aux(anchor);

    while(aux != nullptr and aux->getNext() != p) {
        aux = aux->getNext();
    }

    return aux;
}

template <class T>
typename ClientList<T>::ClientNode* ClientList<T>::getNextPos(ClientNode* p) const {
    if(!isValidPos(p)) {
        return nullptr;
    }
    return p->getNext();
}

/// FUNCION PARA ENCONTRAR DATOS INGRESADOS

template <class T>
typename ClientList<T>::ClientNode* ClientList<T>::findData(const T& e) const {
    ClientNode* aux(anchor);

    while(aux != nullptr and aux->getData() != e) {
        aux = aux->getNext();
    }
    return aux;
}

/// RECUPERA

template <class T>
T ClientList<T>::retrieve(ClientNode* p) const {
    if(!isValidPos(p)) {
        throw Exception("Posicion invalida, retrieve");
    }

    return p->getData();
}

/// IMPRIME

template <class T>
std::string ClientList<T>::toString() const {
    ClientNode* aux(anchor);
    std::string result;

    while(aux != nullptr) {
        result+= aux->getData().toString() + "\n";

        aux = aux->getNext();
    }
    return result;
}

/// DELETE ALL, ELIMINA TODOS LOS DATOS

template <class T>
void ClientList<T>::deleteAll() {
    ClientNode* aux;

    while(anchor != nullptr) {
        aux = anchor;

        anchor = anchor->getNext();

        delete aux;
    }
}

/// OPERADOR

template <class T>
ClientList<T>& ClientList<T>::operator = (const ClientList<T>& l) {
    deleteAll();
    copyAll(l);
    return *this;
}

/// MODIFICAR DATA

template <class T>
void ClientList<T>::modData(ClientNode* p, const T& e) {
    if(p != nullptr and !isValidPos(p)) {
        throw Exception("Posicion invalida, modData");
    }

    p->setData(e);
}

/// METODO PARA INGRESAR DATOS ORDENADOS

template <class T>
void ClientList<T>::insertOrdered(const T& e) {
    ClientNode* aux(anchor);
    ClientNode* p(nullptr);

    while(aux != nullptr and e.getHoraLlamada() < aux->getData().getHoraLlamada()) {
        p = aux;
        aux = aux->getNext();
    }
    insertData(p,e);
}

/// IMPLEMENTACION DEL METODO DE ESCRITURA

template <class T>
void ClientList<T>::writeToDisk(const std::string& fileName) {
    std::ofstream myFile;

    myFile.open(fileName, myFile.trunc);

    if(!myFile.is_open()) {
        std::string message;
        message = "Error al abrir archivo...";

        throw Exception(message);
    }

    ClientNode* aux(anchor);

    while(aux != nullptr) {
        myFile << aux->getData() << std::endl;

        aux = aux->getNext();
    }

    myFile.close();
}

/// IMPLEMENTACION DEL METODO DE LECTURA

template <class T>
void ClientList<T>::readFromDisk(const std::string& fileName) {
    std::ifstream myFile;

    myFile.open(fileName);

    if(!myFile.is_open()) {
        string message;
        message+= "Error al abrir el archivo ";
        message+= fileName;
        message+= " para lectura";

        throw Exception(message);
    }

    deleteAll();

    T myClient;
    ClientNode* last(nullptr);
    ClientNode* newNode;

    while(myFile >> myClient) {
        if((newNode = new ClientNode(myClient))==nullptr) {
            myFile.close();

            throw Exception("Memoria no disponible, readFromDisk");
        }

        if(last==nullptr) {
            anchor = newNode;
        } else {
            last->setNext(newNode);
        }

        last = newNode;

    }
    myFile.close();
}



#endif // CLIENTLIST_H_INCLUDED
