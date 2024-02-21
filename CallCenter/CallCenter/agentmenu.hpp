#ifndef AGENTMENU_H_INCLUDED
#define AGENTMENU_H_INCLUDED

#include <iostream>
#include <fstream>

#include "agent.hpp"
#include "agentlist.hpp"

/// DEIFNICION CLASE AGENT MENU

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

class AgentMenu {
  private:
    void userInterface(AgentList<Agent>&);

    void showAgents(AgentList<Agent>&);
    void addAgent(AgentList<Agent>&);
    void showAgentsBySpecialty(AgentList<Agent>&);
    void deleteAgentbyName(AgentList<Agent>&);
    void deleteAllAgents(AgentList<Agent>&);
    void sortAgents(AgentList<Agent>&);
    void writeToDisk(AgentList<Agent>&);
    void readFromDisk(AgentList<Agent>&);
    void modAgent(AgentList<Agent>&);
    void searchAgent(AgentList<Agent>&);

  public:
    AgentMenu(AgentList<Agent>&);

};

#endif // AGENTMENU_H_INCLUDED
