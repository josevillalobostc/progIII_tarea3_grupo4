#pragma once

#include <string>
#include <vector>
using namespace std;

class Entity {
    double posx, posy;
    double vida, energia;
    string nombre;
    int nivel;
    vector<string> recursos;
public:
    double get_posx(){ return posx;}
    double get_posy(){ return posy;}
    double get_vida(){ return vida;}
    double get_energia(){ return energia;}
    string get_nombre(){ return nombre;}
    int get_nivel(){ return nivel;}
    vector<string> get_recursos() {return recursos;}
    
    void set_posx(double x) { posx = x;}
    void set_posy(const double &y) { posy = y;}
    void set_vida(const double &v) { vida = v;}
    void set_energia(const double &e) { energia = e;}
    void set_nivel(const int& n) { nivel = n; }
    void set_nombre(const string& nomb) { nombre = nomb;}
    void agregar_recurso(const string& rec){ recursos.push_back(rec);}
    
};