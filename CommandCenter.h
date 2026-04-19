#pragma once
#include "Entity.h"


#include <map>
#include <string>
#include <list>
#include <functional>

using Command = std::function<void(const std::list<std::string>&)>;

class CommandCenter{
    std::map<std::string, Command> commands;
    Entity& entity;
    std::map<std::string, std::list<std::pair<std::string, std::list<std::string>>>> macros;
    std::list<std::string> history;
    
public:
    explicit CommandCenter(Entity& _entity) : entity(_entity) {}
    
    // comandos
    void registerCommand(const std::string& name, Command cmd);
    void execute(const std::string& name, const std::list<std::string>& args);
    void removeCommand(const std::string& name);
    
    // macros
    void registerMacro(
        const std::string& name, 
        const std::list<std::pair<std::string, std::list<std::string>>>& steps
    );
    
    void executeMacro(const std::string& name);
    
    // historial
    void printHistory() const;
    
    
};