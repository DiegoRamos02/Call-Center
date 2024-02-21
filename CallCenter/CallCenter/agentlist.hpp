#ifndef AGENTLIST_H_INCLUDED
#define AGENTLIST_H_INCLUDED

#include <iostream>
#include <fstream>
#include <string>
#include <exception>

#include "agent.hpp"
#include "clientlist.hpp"

using namespace std;

/// DEFINICION CLASE AGENT LIST

template <class T>

class AgentList {
  private:
    class AgentNode { /// CLASE AGENT NODE
      private:
        T data;
        AgentNode* prev;
        AgentNode* next;
      public:
        AgentNode();
        AgentNode(const T&);
        T getData() const;
        AgentNode* getPrev() const;
        AgentNode* getNext() const;

        void setData(const T&);
        void setPrev(AgentNode*);
        void setNext(AgentNode*);
    };

    AgentNode* anchor;

    void copyAll(const AgentList<T>&);

    bool isValidPos(AgentNode*) const;

    void swapPtr(AgentNode*, AgentNode*);
    void sortByName(AgentNode*, AgentNode*);
    void sortBySpecialty(AgentNode*, AgentNode*);

  public:
    typedef AgentNode* Position;

    class Exception : public std::exception {
      private:
        std::string msg;

      public:
        explicit Exception(const char* message) : msg(message) { }

        explicit Exception(const std::string& message) : msg(message) { }

        virtual ~Exception() throw () { }

        virtual const char* what() const throw () {
            return msg.c_str();
        }
    };

    AgentList();
    AgentList(const AgentList<T>&);

    ~AgentList();

    bool isEmpty() const;

    void insertData(AgentNode*,const T&);

    void deleteData(AgentNode*);

    AgentNode* getFirstPos() const;
    AgentNode* getLastPos() const;
    AgentNode* getPrevPos(AgentNode*) const;
    AgentNode* getNextPos(AgentNode*) const;

    AgentNode* findData(const T&) const;

    T retrieve(AgentNode*) const;

    std::string toString(bool) const;

    void deleteAll();

    void modData(AgentNode*,const T&);

    void writeToDisk(const std::string&);
    void readFromDisk(const std::string&);

    AgentList<T>& operator = (const AgentList<T>&);

    void sortByName();
    void sortBySpecialty();

    std::string showBySpecialty(bool) const;
};


/// --I M P L E M E N T A C I O N   C L A S E   A G E N T   L I S T--

/// IMPLEMENTACION AGENT NODE

template <class T>
AgentList<T>::AgentNode::AgentNode() : prev(nullptr),next(nullptr) { }

template <class T>
AgentList<T>::AgentNode::AgentNode(const T& e) : data(e),prev(nullptr),next(nullptr) { }

template <class T>
T AgentList<T>::AgentNode::getData() const {
    return data;
}

template <class T>
typename AgentList<T>::AgentNode* AgentList<T>::AgentNode::getPrev() const {
    return prev;
}

template <class T>
typename AgentList<T>::AgentNode* AgentList<T>::AgentNode::getNext() const {
    return next;
}
template <class T>
void AgentList<T>::AgentNode::setData(const T& e) {
    data = e;
}

template <class T>
void AgentList<T>::AgentNode::setPrev(AgentNode* p) {
    prev = p;
}

template <class T>
void AgentList<T>::AgentNode::setNext(AgentNode* p) {
    next = p;
}

/// ############################################

/// COPY ALL

template <class T>
void AgentList<T>::copyAll(const AgentList<T>& l) {
    AgentNode* aux(l.anchor);
    AgentNode* last(nullptr);
    AgentNode* newAgentNode;

    while(aux != nullptr) {
        if((newAgentNode = new AgentNode(aux->getData()))==nullptr) {
            throw Exception("Memoria no disponible, copyAll");
        }
        if(last == nullptr) {
            anchor = newAgentNode;
        } else {
            newAgentNode->setPrev(last);

            last->setNext(newAgentNode);
        }
        last = newAgentNode;

        aux = aux->getNext();
    }
}

/// VALIDPOS

template <class T>
bool AgentList<T>::isValidPos(AgentNode* p) const {
    AgentNode* aux(anchor);

    while(aux!=nullptr) {
        if(aux==p) {
            return true;
        }
        aux = aux->getNext();
    }
    return false;
}

/// CONSTRCUTOR

template <class T>
AgentList<T>::AgentList() : anchor(nullptr) { }

/// CONSTRCUTOR COPIA

template <class T>
AgentList<T>::AgentList(const AgentList<T>& l) : anchor(nullptr) {
    copyAll(l);
}

/// DESTRUCTOR

template <class T>
AgentList<T>::~AgentList() {
    deleteAll();
}

/// FUNCION QUE VALIDA QUE LA LISTA ESTE VACIA

template <class T>
bool AgentList<T>::isEmpty() const {
    return anchor==nullptr;
}

/// FUNCION PARA INSETAR

template <class T>
void AgentList<T>::insertData(AgentNode* p, const T& e) {
    if(p!=nullptr and !isValidPos(p)) {
        throw Exception("Posicion Invalida, insertData");
    }
    AgentNode* aux(new AgentNode(e));

    if(aux==nullptr) {
        throw Exception("Memoria no disponible, insertData");
    }
    if(p==nullptr) {
        aux->setNext(anchor);
        if(anchor!=nullptr) {
            anchor->setPrev(aux);
        }
        anchor=aux;
    } else {
        aux->setPrev(p);
        aux->setNext(p->getNext());

        if(p->getNext() != nullptr) {
            p->getNext()->setPrev(aux);
        }
        p->setNext(aux);
    }
}

/// FUNCION PARA ELIMINAR

template <class T>
void AgentList<T>::deleteData(AgentNode* p) {
    if(!isValidPos(p)) {
        throw Exception("Posicion invalida, deleteData");
    }

    if(p->getPrev()!= nullptr) {
        p->getPrev()->setNext(p->getNext());
    }

    if(p->getNext()!=nullptr) {
        p->getNext()->setPrev(p->getPrev());
    }

    if(p==anchor) {
        anchor = anchor->getNext();
    }

    delete p;
}

/// OBTIENE LA PRIMER POSICION

template <class T>
typename AgentList<T>::AgentNode* AgentList<T>::getFirstPos() const {
    return anchor;
}

/// OBTIENE LA ULTIMA POSICION

template <class T>
typename AgentList<T>::AgentNode* AgentList<T>::getLastPos() const {
    if(isEmpty()) {
        return nullptr;
    }

    AgentNode* aux(anchor);

    while(aux->getNext()!=nullptr) {
        aux=aux->getNext();
    }
    return aux;
}

/// OBTIENE LA POSICION PREVIA

template <class T>
typename AgentList<T>::AgentNode* AgentList<T>::getPrevPos(AgentNode* p) const {
    if(!isValidPos(p)) {
        return nullptr;
    }
    return p->getPrev();
}

///  OBTIENE LA SIGUIENTE POSICION

template <class T>
typename AgentList<T>::AgentNode* AgentList<T>::getNextPos(AgentNode* p) const {
    if(!isValidPos(p)) {
        return nullptr;
    }
    return p->getNext();
}

/// FUNCION PARA ENCONTRAR

template <class T>
typename AgentList<T>::AgentNode* AgentList<T>::findData(const T& e) const {
    AgentNode* aux(anchor);

    while(aux!=nullptr and aux->getData()!=e) {
        aux=aux->getNext();
    }
    return aux;
}

/// FUNCION PARA RECUPERAR

template <class T>
T AgentList<T>::retrieve(AgentNode* p) const {
    if(!isValidPos(p)) {
        throw Exception("Posicion invalida, retrieve");
    }
    return p->getData();
}

/// FUNCION PARA IMPRIMIR

template <class T>
std::string AgentList<T>::toString(bool u) const {
    AgentNode* aux(anchor);
    std::string result;

    while(aux!=nullptr) {
        result+=aux->getData().toString(u) + "\n";

        aux = aux->getNext();
    }
    return result;
}

/// FUNCION PARA ELIMINAR TODO LOS DATOS

template <class T>
void AgentList<T>::deleteAll() {
    AgentNode* aux;

    while(anchor != nullptr) {
        aux = anchor;

        anchor = anchor->getNext();

        delete aux;
    }
}

/// #############################################

template <class T>
AgentList<T>& AgentList<T>:: operator = (const AgentList<T>& l) {
    deleteAll();
    copyAll(l);
    return *this;
}

/// FUNCION PARA MODIFICAR

template <class T>
void AgentList<T>::modData(AgentNode* p, const T& e) {
    if(p!=nullptr and !isValidPos(p)) {
        throw Exception("Posicion Invalida, modData");
    }

    p->setData(e);
}

/// FUNCION PARA INTERCAMBIAR QUE PERMITE LA COMPARACION

template <class T>
void AgentList<T>::swapPtr(AgentNode* a, AgentNode* b) {
    if(a!=b) {
        T aux(a->getData());
        a->setData(b->getData());
        b->setData(aux);

    }
}

/// FUNCION PARA ORDENAR POR NOMBRE

template <class T>
void AgentList<T>::sortByName() {
    sortByName(getFirstPos(),getLastPos());
}

template <class T>
void AgentList<T>::sortByName(AgentNode* l, AgentNode* r) {
    if(l==r) {
        return;
    }

    if(l->getNext() == r) { // son solo dos elementos
        if(l->getData().getNomEmpleado() > r->getData().getNomEmpleado()) {
            swapPtr(l,r);
        }
        return;
    }

    AgentNode* i(l);
    AgentNode* j(r);

    while(i!=j) {
        while(i != j and i->getData().getNomEmpleado() <= r->getData().getNomEmpleado()) {
            i = i->getNext();
        }

        while(i != j and i->getData().getNomEmpleado() >= r->getData().getNomEmpleado()) {
            j = j->getPrev();
        }

        swapPtr(i,j);
    }

    swapPtr(i,r);

    if(i != l) {
        sortByName(l, i->getPrev());
    }

    if(i != r) {
        sortByName(i->getNext(), r);
    }
}

/// FUNCION PARA ORDENAR POR ESPECIALIDAD

template <class T>
void AgentList<T>::sortBySpecialty() {
    sortBySpecialty(getFirstPos(),getLastPos());
}

template <class T>
void AgentList<T>::sortBySpecialty(AgentNode* l, AgentNode* r) {
    if(l==r) {
        return;
    }

    if(l->getNext() == r) { // son solo dos elementos
        if(l->getData().getEspecialidad() > r->getData().getEspecialidad()) {
            swapPtr(l,r);
        }
        return;
    }

    AgentNode* i(l); //particion
    AgentNode* j(r);

    while(i!=j) {
        while(i != j and i->getData().getEspecialidad() <= r->getData().getEspecialidad()) {
            i = i->getNext();
        }

        while(i != j and i->getData().getEspecialidad() >= r->getData().getEspecialidad()) {
            j = j->getPrev();
        }

        swapPtr(i,j);
    }

    swapPtr(i,r);

    if(i != l) { //divide y venceras
        sortBySpecialty(l, i->getPrev());
    }

    if(i != r) {
        sortBySpecialty(i->getNext(), r);
    }
}

/// FUNCION PARA ESCRIBIR AL DISCO

template <class T>
void AgentList<T>::writeToDisk(const std::string& fileName) {
    std::ofstream myFile;
    bool usr(false);

    myFile.open(fileName,myFile.trunc);

    if(!myFile.is_open()) {
        std::string message;

        message = "Error al abrir archivo...";

        throw Exception(message);
    }

    AgentNode* aux(anchor);

    while(aux != nullptr) {
        myFile << aux->getData() << std::endl;

        try {
            aux->getData().getUserList().writeToDisk(aux->getData().getNumEmpleado() + ".agents");
        } catch(Exception ex) {
            cout << ex.what();
        }

        aux = aux->getNext();
    }
    myFile.close();
}

/// FUNCION PARA LEER DEL DISCO

template <class T>
void AgentList<T>::readFromDisk(const std::string& fileName) {
    std::ifstream myFile;

    myFile.open(fileName);

    if(!myFile.is_open()) {
        string message;

        message = "Error al tratar de abrir el archivo ";
        message+= fileName;
        message+= " para lectura";
        throw Exception(message);
    }

    T myAgent;
    AgentNode* aux;
    AgentNode* last(nullptr);

    deleteAll();

    while(myFile >> myAgent) {
        try {
            myAgent.getUserList().readFromDisk(myAgent.getNumEmpleado() + ".agents");
        } catch(Exception ex) {
            cout << ex.what() << endl;
        }

        if((aux = new AgentNode(myAgent))==nullptr) {
            myFile.close();

            throw Exception("Memoria no disponible, readFromDisk");
        }

        if(last == nullptr) {
            anchor = aux;
        } else {
            aux->setPrev(last);

            last->setNext(aux);
        }
        last = aux;
    }

    myFile.close();
}

/// FUNCION PARA MPOSTAR AGENTES POR ESPECIALIDAD

template <class T>
string AgentList<T>::showBySpecialty(bool u) const {
    AgentNode* aux(anchor);

    std::string result;

    while(aux!=nullptr) {
        if(aux->getData().getEspecialidad() == "De escritorio") {
            result+=aux->getData().toString(u) + "\n";
        }
        aux = aux->getNext();
    }
    aux = anchor;
    while(aux!=nullptr) {
        if(aux->getData().getEspecialidad() == "Impresoras") {
            result+=aux->getData().toString(u) + "\n";
        }
        aux = aux->getNext();
    }
    aux = anchor;
    while(aux!=nullptr) {
        if(aux->getData().getEspecialidad() == "Linux") {
            result+=aux->getData().toString(u) + "\n";
        }
        aux = aux->getNext();
    }
    aux = anchor;
    while(aux!=nullptr) {
        if(aux->getData().getEspecialidad() == "Portatiles") {
            result+=aux->getData().toString(u) + "\n";
        }
        aux = aux->getNext();
    }
    aux = anchor;
    while(aux!=nullptr) {
        if(aux->getData().getEspecialidad() == "Redes") {
            result+=aux->getData().toString(u) + "\n";
        }
        aux = aux->getNext();
    }
    aux = anchor;
    while(aux!=nullptr) {
        if(aux->getData().getEspecialidad() == "Servidores") {
            result+=aux->getData().toString(u) + "\n";
        }
        aux = aux->getNext();
    }
    aux = anchor;
    return result;
}

#endif // AGENTLIST_H_INCLUDED
