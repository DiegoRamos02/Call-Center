#ifndef CLIENTMENU_H_INCLUDED
#define CLIENTMENU_H_INCLUDED

#include "clientlist.hpp"
#include "client.hpp"
#include "agent.hpp"
#include "agentlist.hpp"

/// DEFINICION CLASE CLIENT MENU

class ClientMenu {
  private:

    void addClientToAgent(AgentList<Agent>&);
    void deleteClient(AgentList<Agent>&);
    void deleteAllClients(AgentList<Agent>&);
    void modCallTime(AgentList<Agent>&);
    void readFromDisk(AgentList<Agent>&);
  public:
    void userInterface(AgentList<Agent>&);
};

#endif // CLIENTMENU_H_INCLUDED
