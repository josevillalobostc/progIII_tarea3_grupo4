#include "CommandCenter.h"
#include <iostream>
using namespace std;

void CommandCenter::registerCommand(const std::string& name, Command cmd) {
    map<string, Command>::iterator it = commands.find(name);
    if (it != commands.end()){
        commands.insert({name,cmd});
    } else {
        cerr << "Error: El comando ya existe\n";
        return;
    }
}

void CommandCenter::execute(const std::string& name, const std::list<std::string>& args) {
    map<string, Command>::iterator it = commands.find(name);
    if( it != commands.end()){
        it -> second(args);
    } else {
        cerr << "Error: El comando no existe\n";
        return;
    }
}

void CommandCenter::removeCommand(const std::string& name) {
    map<string, Command>::iterator it = commands.find(name);
    if( it != commands.end()){
        commands.erase(it -> first);
    } else {
        cout << "Comando no encontrado\n";
        return;
    }
}

void CommandCenter::registerMacro(
    const std::string& name, 
    const std::list<std::pair<std::string, std::list<std::string>>>& steps
) {
    map<string, list<pair<string, list<string>>>>::iterator it = macros.find(name);
    
    if(it != macros.end()){
        macros.insert(make_pair(name,steps));
    }
}

void CommandCenter::executeMacro(const std::string& name) {
    map<string, list<pair<string, list<string>>>>::iterator it = macros.find(name);
    map<string, Command>::iterator funcIt;
    if(it != macros.end()){
        for(pair<string, list<string>> step : it->second){
            funcIt = commands.find(step.first);
            
            if (funcIt == commands.end()) {
                std::cerr << "Error en macro " << name << ", no existe el comando " << step.first << endl;
                return;
            }
            funcIt -> second(step.second);            
        }
    }
}

void CommandCenter::printHistory() const {

}