#include "Entity.h"

void posx(Entity& playah, const std::list<std::string>& args){
    f(args.empty()){std::cout<<"Error: argumento vacío, no se puede cambiar posX.";return;}
    double posX=stoi(args.front());
    playah.set_posx(posX);
}

void posy(Entity& playah, const std::list<std::string>& args){
    f(args.empty()){std::cout<<"Error: argumento vacío, no se puede cambiar posY.";return;}
    double posY=stoi(args.front());
    playah.set_posy(posY);
}

void hpsum(Entity& playah, const std::list<std::string>& args){
    if(args.empty()){std::cout<<"Error: argumento vacío, no se puede sumar hp.";return;}
    double hp=std::stoi(args.front());
    playah.set_vida(playah.get_vida()+hp;);
}

void energsum(Entity& playah, const std::list<std::string>& args){
    f(args.empty()){std::cout<<"Error: argumento vacío, no se puede sumar energía.";return;}
    double energ=stoi(args.front());
    playah.set_energia(playah.get_energia()+energ);
}

void lvlsum(Entity& playah, const std::list<std::string>& args){
    f(args.empty()){std::cout<<"Error: argumento vacío, no se puede sumar nivel.";return;}
    double lvl=stoi(args.front());
    playah.set_nivel(playah.get_nivel()+lvl);
}

void resource(Entity& playah, const std::list<std::string>& args){
    f(args.empty()){std::cout<<"Error: argumento vacío, no se puede agregar recurso.";return;}
    double resrc=args.front();
    playah.agregar_recurso(resrc);
}

void statchng(Entity& playah, const std::list<std::string>& args){
    if(args.empty()){std::cout<<"Error: argumento vacío, no se puede cambiar estado.";return;}
    string status=args.front();
    playah.set_estado(estatus); 
}

int main(){
    Entity chara;
    chara.set_nombre("Beetank"); chara.set_vida(290); chara.set_nivel(6);
    chara.agregar_recurso("Lilbomb"); chara.set_posx(6); chara.set_posy(2);

    CommandCenter cmdc;

    std::list<std::string>& args1{  }
    center.registerCommand("hpsum",using Command=std::function<void(const std::list<std::string>& args1)>;







    return 0;
}