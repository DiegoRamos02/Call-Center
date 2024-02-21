#ifndef TIME_H_INCLUDED
#define TIME_H_INCLUDED

#include <iostream>
#include<string>

/// DEFINICION DE LA CLASE TIME

class Time {
  private:
    int hour;
    int minute;

    int toInt(const int&);

  public:
    Time();
    Time(const Time&);

    int getHour() const;
    int getMinute() const;

    std::string toString() const;

    void setHour(const int&) ;
    void setMinute(const int&);

    Time& operator = (const Time&);

    bool operator == (const Time&) const;
    bool operator != (const Time&) const;
    bool operator < (const Time&) const;
    bool operator <= (const Time&) const;
    bool operator > (const Time&) const;
    bool operator >= (const Time&) const;

    friend std::ostream& operator << (std::ostream&,const Time&);
    friend std::istream& operator >> (std::istream&, Time&);
};

#endif // TIME_H_INCLUDED
