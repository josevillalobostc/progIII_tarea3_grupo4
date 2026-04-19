#include "CommandCenter.h"
#include <iostream>
using namespace std;

void CommandCenter::registerCommand(const std::string& name, Command cmd) {
    map<string, Command>::iterator it = commands.find(name);
    if (it == commands.end()){
        commands.insert({name,cmd});
    } else {
        cerr << "Error: El comando "<< name <<" ya existe\n";
        return;
    }
}

void CommandCenter::execute(const std::string& name, const std::list<std::string>& args) {
    map<string, Command>::iterator it = commands.find(name);
    Entity antes = entity;
    
    if( it != commands.end()){
        it -> second(args);
    } else {
        cerr << "Error: El comando no existe\n";
        return;
    }
    string comando = name;
    for(auto it = args.begin(); it != args.end(); ++it){
        comando += " " + *it;
    }
    string cambios = "Comando " + comando + " ejecutado\n"+ entity.get_diff(antes) + "\n";
    history.push_back(cambios);
    
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
    
    if(it == macros.end()){
        macros.insert(make_pair(name,steps));
    } else {
        cerr << "Error: Ya existe un macro con el mismo nombre\n";
    }
}

void CommandCenter::executeMacro(const std::string& name) {
    map<string, list<pair<string, list<string>>>>::iterator it = macros.find(name);

    if(it != macros.end()){
        list<pair<string, list<string>>>::iterator stepIt;
        for(stepIt = it -> second.begin(); stepIt != it->second.end(); ++stepIt){
            if ( commands.find(stepIt -> first) == commands.end()) {
                std::cerr << "Error: En la macro " << name << ", no existe el comando " << stepIt -> first << endl;
                return;
            }
            this -> execute(stepIt -> first, stepIt -> second);          
        }
    } else {
        cerr << "Error: No existe ninguna macro con dicho nombre\n";
    }
}

void CommandCenter::printHistory() const {
    list<string>::const_iterator it;
    for(it = history.begin(); it!=history.end(); ++it){
        cout << *it << endl;
    }
}