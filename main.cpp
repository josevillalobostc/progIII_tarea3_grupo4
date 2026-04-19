#include <iostream>
#include <list>
#include <string>
#include <functional>
#include <sstream>
#include "Entity.h"
#include "CommandCenter.h"
using namespace std;

//Funciones libres (luego serán registradas por el command center)

void heal(Entity& playah,const list<string>& args){
    if(args.empty()){std::cout<<"Error: argumento vacio, no se puede sumar energia.\n";return;}
    double hp=stod(args.front());
    playah.set_vida(playah.get_vida()+hp);
}

void papear(Entity& playah){
    playah.set_vida(playah.get_vida()-99999);
}

void status(Entity& playah) {
    cout << format("Nombre  : {}", playah.get_nombre()) << endl;
    cout << format("Nivel   : {}", playah.get_nivel()) << endl;
    cout << format("Vida    : {:.2f}", playah.get_vida()) << endl;
    cout << format("Energia : {:.2f}", playah.get_energia()) << endl;
    cout << format("Posicion: ({:.2f}, {:.2f})", playah.get_posx(), playah.get_posy()) << endl;
    cout << format("Estado  : {}", playah.get_estado()) << endl;
    
    // si hay recursos:
    cout << "Recursos: ";
    auto recs = playah.get_recursos();
    if (recs.empty()) {
        cout << "Ninguno";
    } else {
        for (const auto& r : recs) cout << "[" << r << "] ";
        cout << endl;
    }
}

void lvlsum(Entity& playah,const list<string>& args){
    if(args.empty()){cout<<"Error: argumento vacio, no se puede sumar nivel.\n";return;}
    double lvl=stod(args.front());
    playah.set_nivel(playah.get_nivel()+lvl);
}

//Functores
struct energysum{
    Entity& playah;
    int usecounter;
    const int maxuses=5;
    energysum(Entity& _playah):playah(_playah),usecounter(0){}
    void operator()(const list<string>& args){
        try{
        if(args.empty()){cout<<"Error: argumento vacio, no se puede sumar energia.\n";return;}
        if (usecounter >= maxuses) {
            cout<<"Error: Se ha alcanzado el limite de usos de este comando.\n";return;
        }
        double energ=stod(args.front());
        playah.set_energia(playah.get_energia()+energ); usecounter++;
        cout<<"energsum usado "<<usecounter<<"/"<<maxuses<<" veces.\n";
        }
        catch(...){cout<<"Error: El argumento es invalido.\n";}
    }

};

int main(){
    Entity chara;
    chara.set_nombre("Beetank"); chara.set_vida(290); chara.set_nivel(6);
    chara.agregar_recurso("Lilbomb"); chara.set_posx(6); chara.set_posy(2);

    CommandCenter cmdc(chara);

    //Creación de las instancias de functores:
    energysum BeetankEnergizer(chara);

    //Registro de los comandos
     
    // Creacion de comandos usando funciones lambda
    cmdc.registerCommand("move",[&chara](const list<string>& args){
        if(args.empty()){cout<<"Error: argumento vacio, no se puede cambiar las coordenadas.\n";return;}
        if(args.size() > 2){cout<<"Error: Demasiados argumentos, solo se permiten maximo dos.\n";return;}
        if(args.size() > 1){
            chara.set_posx(stod(args.front()));
            chara.set_posy(stod(args.back()));
            return;
        } else chara.set_posx(stod(args.front()));
    }
    );
     
    cmdc.registerCommand("posx",[&chara](const list<string>& args){
        if(args.empty()){cout<<"Error: argumento vacio, no se puede cambiar posX.\n";return;}
        double posX=stod(args.front());
        chara.set_posx(posX);});

    cmdc.registerCommand("posy",[&chara](const list<string>& args){
        if(args.empty()){cout<<"Error: argumento vacio, no se puede cambiar posY.\n";return;}
        double posY=stod(args.front());
        chara.set_posy(posY);});

    // usando funcion lambda para usar una funcion libre
    cmdc.registerCommand("heal",[&chara](const list<string>& args){heal(chara,args);});

    // Comando creado usando functor
    cmdc.registerCommand("energsum",BeetankEnergizer);

    // Paso de funcion libre
    cmdc.registerCommand("lvlsum",bind(lvlsum, std::ref(chara), placeholders::_1));

    cmdc.registerCommand("resource",[&chara](const list<string>& args){
        if(args.empty()){cout<<"Error: argumento vacio, no se puede agregar recurso.\n";return;}
        string resrc=args.front();
        chara.agregar_recurso(resrc);});
    
    cmdc.registerCommand("statchng",[&chara](const list<string>& args){
        if(args.empty()){cout<<"Error: argumento vacio, no se puede cambiar estado.\n";return;}
        string status=args.front();
        chara.set_estado(status);});

    cmdc.registerCommand("papear",[&chara](const list<string>& args){papear(chara);});
    
    cmdc.registerCommand("status",[&chara](const list<string>& args){
        if(args.size() != 0){
            cout << "Aviso: No es necesario pasar argumentos al usar status\n";
        }
        status(chara);
    });
    
    // agregando comando que ya existe
    cmdc.registerCommand("status",[&chara](const list<string>& args){cout << "no deberia ejecutarme\n";});
    
    // macro1 para test
    list<pair<string, list<string>>> macro1 = {
            {"lvlsum", {"1"}},
            {"heal", {"500"}},
            {"posx", {"0"}},
            {"posy", {"0"}}
        };
    cmdc.registerMacro("fullheal", macro1);
    
    // macro 2
    list<pair<string, list<string>>> macro2 = {
        {"energsum", {"50"}},
        {"statchng", {"Buffed"}},
        {"resource", {"PocionMagica"}}
    };
    cmdc.registerMacro("buff_and_status", macro2);
    
    // macro con comando falso para testear el error
    list<pair<string, list<string>>> macro3 = {
        {"heal", {"30"}},
        {"noexiste", {"10"}},
        {"papear", {}}
    };
    cmdc.registerMacro("bumbumpatapir", macro3);
    
    // Uso de execute antes de la consola creada para testeo
    cmdc.execute("heal",{"10"});
    cmdc.execute("move",{"40","20"});
    
    
    cmdc.execute("status",{});
    cmdc.execute("papear",{});
    cmdc.execute("heal",{"99999"});
    cmdc.printHistory();
    cmdc.execute("noexiste",{"99999"});
    cmdc.executeMacro("fullheal");
    cmdc.executeMacro("noexisteestemacro");
    cmdc.executeMacro("bumbumpatapir");
    
    
    // consola para probar varios comandos y posibles historiales
    cout << "\n----- Consola iniciada-----\n";
        cout << "Comandos: [nombre] [args...]\n";
        cout << "Macros  : macro [nombre_macro]\n";
        cout << "Especial: 'exit/quit' (salir), 'history' (ver registro).\n";
    
        while(true){
            cout << "> ";
            string input;
            getline(cin, input);
    
            if(input.empty()) continue;
    
            stringstream ss(input);
            string elcomando;
            ss >> elcomando; 
    
            
            if(elcomando == "exit" || elcomando == "quit") {
                cout << "Cerrando consola...\n";
                break;
            } 
            else if (elcomando == "history" || elcomando == "historial") {
                cmdc.printHistory();
                continue;
            }
    
            
            if (elcomando == "macro") {
                string macroName;
                if (ss >> macroName) {
                    cmdc.executeMacro(macroName);
                } else {
                    cout << "Error: Debes especificar el nombre del macro.\n";
                }
                continue;
            }
    
            // ejecuta un comando
            list<string> args;
            string arg;
            while(ss >> arg) {
                args.push_back(arg);
            }
            cmdc.execute(elcomando, args);
        }

    return 0;
}