#ifndef AGENT_H_INCLUDED
#define AGENT_H_INCLUDED

#include <iostream>
#include<string>

#include "time.hpp"
#include "name.hpp"
#include "client.hpp"
#include "clientlist.hpp"

/// DEFINICION CLASE AGENTE

class Agent {
  private:
    std::string numEmpleado;
    Name nomEmpleado;
    std::string especialidad;
    int numExt;
    Time horaEntrada;
    Time horaSalida;
    int horasExt;
    ClientList<Client> userList;

  public:
    Agent();
    Agent(const Agent&);

    std::string getNumEmpleado() const;
    Name getNomEmpleado() const;
    std::string getEspecialidad() const;
    int getNumExt() const;
    Time getHoraEntrada() const;
    Time getHoraSalida() const;
    int getHorasExt() const;
    ClientList<Client> getUserList();

    std::string toString(bool) const;

    void setNumEmpleado(const std::string&);
    void setNomEmpleado(const Name&);
    void setEspecialidad(std::string&);
    void setNumExt(const int&);
    void setHoraEntrada(const Time&);
    void setHoraSalida(const Time&);
    void setHorasExt(const int&);
    void setUserList(ClientList<Client>&) ;

    Agent& operator = (const Agent&);

    bool operator == (const Agent&) const;
    bool operator != (const Agent&) const;
    bool operator < (const Agent&) const;
    bool operator <= (const Agent&) const;
    bool operator > (const Agent&) const;
    bool operator >= (const Agent&) const;

    friend std::ostream& operator << (std::ostream&, const Agent&);
    friend std::istream& operator >> (std::istream&, Agent&);

};
#endif // AGENT_H_INCLUDED
