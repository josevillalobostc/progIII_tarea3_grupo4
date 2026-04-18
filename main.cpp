#include <iostream>
#include <list>
#include <string>
#include <functional>
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
        cout<<"energsum usado "<<usecounter<<"/"<<maxuses<<" veces.";
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

    cmdc.registerCommand("posx",[&chara](const list<string>& args){
        if(args.empty()){cout<<"Error: argumento vacio, no se puede cambiar posX.\n";return;}
        double posX=stod(args.front());
        chara.set_posx(posX);});

    cmdc.registerCommand("posy",[&chara](const list<string>& args){
        if(args.empty()){cout<<"Error: argumento vacio, no se puede cambiar posY.\n";return;}
        double posY=stod(args.front());
        chara.set_posy(posY);});

    cmdc.registerCommand("heal",[&chara](const list<string>& args){heal(chara,args);});

    cmdc.registerCommand("energsum",BeetankEnergizer);

    cmdc.registerCommand("lvlsum",[&chara](const list<string>& args){lvlsum(chara,args);});

    cmdc.registerCommand("resource",[&chara](const list<string>& args){
        if(args.empty()){cout<<"Error: argumento vacio, no se puede agregar recurso.\n";return;}
        string resrc=args.front();
        chara.agregar_recurso(resrc);});
    
    cmdc.registerCommand("statchng",[&chara](const list<string>& args){
        if(args.empty()){cout<<"Error: argumento vacio, no se puede cambiar estado.\n";return;}
        string status=args.front();
        chara.set_estado(status);});

    cmdc.registerCommand("papear",[&chara](const list<string>& args){papear(chara);});

    

    return 0;
}