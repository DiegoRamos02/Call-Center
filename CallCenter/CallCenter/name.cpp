#include "name.hpp"

using namespace std;

/// IMPLEMENTACION CLASE NAME

Name::Name() { }

Name::Name(const Name& n) : last(n.last),first(n.first) { }

/// GETTERS

std::string Name::getLast() const {
    return last;
}

std::string Name::getFirst() const {
    return first;
}

std::string Name::toString() const {
    return first + " " + last;
}

/// SETTERS

void Name::setLast(const std::string& l) {
    last = l;
}

void Name::setFirst(const std::string& f) {
    first = f;
}

/// OPERADORES

Name& Name::operator = (const Name& n) {
    last = n.last;
    first = n.first;

    return *this;
}

bool Name::operator==(const Name& n) const {
    return first == n.first;
}

bool Name::operator!=(const Name& n) const {
    return first != n.first;
}

bool Name::operator<(const Name& n) const {
    return first < n.first;
}

bool Name::operator<=(const Name& n) const {
    return first <= n.first;
}

bool Name::operator>(const Name& n) const {
    return first > n.first;
}

bool Name::operator>=(const Name& n) const {
    return first >= n.first;
}

/// FUNCIONES QUE PERMITEN QUE EL OBJETO SE ESCRIBA AL DISCO Y SE LEA DEL MISMO

ostream& operator << (ostream& os,const Name& n) {
    os << n.toString();

    return os;
}

istream& operator >> (istream& is, Name& n) {
    getline(is, n.first, ' ');
    getline(is, n.last);

    return is;
}
