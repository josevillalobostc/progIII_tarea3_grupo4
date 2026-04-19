#pragma once

#include <string>
#include <vector>
#include <format>


class Entity {
    double posx, posy;
    double vida, energia;
    std::string nombre;
    int nivel;
    std::vector<std::string> recursos;
    std::string estado;
public:
    double get_posx(){ return posx;}
    double get_posy(){ return posy;}
    double get_vida(){ return vida;}
    double get_energia(){ return energia;}
    std::string get_nombre(){ return nombre;}
    int get_nivel(){ return nivel;}
    std::vector<std::string> get_recursos() {return recursos;}
    std::string get_estado(){ return estado;}
    
    void set_posx(double x) { posx = x;}
    void set_posy(const double &y) { posy = y;}
    void set_vida(const double &v) { vida = v;}
    void set_energia(const double &e) { energia = e;}
    void set_nivel(const int& n) { nivel = n; }
    void set_nombre(const std::string& nomb) { nombre = nomb;}
    void agregar_recurso(const std::string& rec){ recursos.push_back(rec);}
    void set_estado(const std::string& status){ estado=status;}
    
    std::string get_diff(const Entity& other) const {
            std::string diff = "";
            
            if (vida != other.vida) 
                diff += std::format("Vida: {} -> {} | ", other.vida, vida);
                
            if (posx != other.posx || posy != other.posy) 
                diff += std::format("Pos: ({},{}) -> ({},{}) | ", other.posx, other.posy, posx, posy);
                
            if (energia != other.energia) 
                diff += std::format("Energia: {} -> {} | ", other.energia, energia);
                
            if (nivel != other.nivel)
                diff += std::format("Nivel: {} -> {} | ", other.nivel, nivel);
            
            if (nombre != other.nombre)
                diff += std::format("Nombre: {} -> {} | ", other.nombre, nombre);
            
            if (estado != other.estado)
                diff += std::format("Estado: {} -> {} | ", other.estado, estado);
                        
            return (diff == "") ? "Sin cambios" : diff;
        }
    
    
};