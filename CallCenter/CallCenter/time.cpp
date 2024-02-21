#include <iostream>
#include <string>

#include "time.hpp"

using namespace std;

/// IMPLEMENTACION CLASE TIME

int Time::toInt(const int&) { }

Time::Time() { }

Time::Time(const Time& t) : hour(t.hour),minute(t.minute) { }

/// GETTERS

int Time::getHour() const {
    return hour;
}

int Time::getMinute() const {
    return minute;
}

std::string Time::toString() const {
    char result[6];

    sprintf(result, "%02i:%02i", hour, minute);

    return result;
}

/// SETTERS

void Time::setHour(const int& h) {
    hour = h;
}

void Time::setMinute(const int& m) {
    minute = m;
}

/// OPERADORES

Time& Time::operator = (const Time& t) {
    hour = t.hour;
    minute = t.minute;

    return *this;
}

bool Time::operator==(const Time& t) const {
    return hour == t.hour;
}

bool Time::operator!=(const Time& t) const {
    return hour != t.hour;
}

bool Time::operator<(const Time& t) const {
    return hour < t.hour;
}

bool Time::operator<=(const Time& t) const {
    return hour <= t.hour;
}

bool Time::operator>(const Time& t) const {
    return hour > t.hour;
}

bool Time::operator>=(const Time& t) const {
    return hour >= t.hour;
}

/// FUNCIONES QUE PERMIETEN QUE EL OBJETO SE ESCRIBA AL DISCO Y SE LEA DEL MISMO

ostream& operator << (ostream& os,const Time& t) {
    os << t.toString();

    return os;
}

istream& operator >> (istream& is, Time& t) {
    string myStr;

    getline(is, myStr, ':');
    t.hour = atoi(myStr.c_str());
    getline(is, myStr);
    t.minute = atoi(myStr.c_str());

    return is;
}
