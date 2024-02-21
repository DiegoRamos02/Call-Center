#ifndef CLIENT_H_INCLUDED
#define CLIENT_H_INCLUDED

#include <iostream>
#include<string>

#include "time.hpp"
#include "name.hpp"

/// DEFINICION CLASE CLIENT

class Client {
  private:
    Name nomClient;
    Time horaLlamada;
    Name agente;
    Time durationCall;

  public:
    Client();
    Client(const Client&);

    Name getNomClient() const;
    Time getHoraLlamada() const;
    Name getAgente() const;
    Time getDurationCall() const;

    std::string toString() const;

    void setNomClient(const Name&);
    void setHoraLlamada(const Time&);
    void setAgente(const Name&);
    void setDurationCall(const Time&);

    Client& operator = (const Client&);

    bool operator == (const Client&) const;
    bool operator != (const Client&) const;
    bool operator < (const Client&) const;
    bool operator <= (const Client&) const;
    bool operator > (const Client&) const;
    bool operator >= (const Client&) const;

    friend std::ostream& operator << (std::ostream&,const Client&);
    friend std::istream& operator >> (std::istream&, Client&);
};

#endif // CLIENT_H_INCLUDED
