#include "CommandCenter.h"
using namespace std;

void CommandCenter::registerCommand(const std::string& name, Command cmd) {

}

void CommandCenter::execute(const std::string& name, const std::list<std::string>& args) {

}

void CommandCenter::removeCommand(const std::string& name) {

}

void CommandCenter::registerMacro(
    const std::string& name, 
    const std::list<std::pair<std::string, std::list<std::string>>>& steps
) {

}

void CommandCenter::executeMacro(const std::string& name) {

}

void CommandCenter::printHistory() const {

}