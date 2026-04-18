#pragma once

#include <string>
#include <vector>
#include <format>

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
    
    string get_diff(const Entity& other) const {
            string diff = "";
            
            if (vida != other.vida) 
                diff += format("Vida: {} -> {} | ", other.vida, vida);
                
            if (posx != other.posx || posy != other.posy) 
                diff += format("Pos: ({},{}) -> ({},{}) | ", other.posx, other.posy, posx, posy);
                
            if (energia != other.energia) 
                diff += format("Energia: {} -> {} | ", other.energia, energia);
                
            if (nivel != other.nivel)
                diff += format("Nivel: {} -> {} | ", other.energia, energia);
            
            if (nombre != other.nombre)
                diff += format("Nombre: {} -> {} | ", other.nombre, nombre);
            
                        
            return (diff == "") ? "Sin cambios" : diff;
        }
    
    
};