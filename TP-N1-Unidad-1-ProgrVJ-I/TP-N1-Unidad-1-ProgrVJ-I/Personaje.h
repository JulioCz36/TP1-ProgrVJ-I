#pragma once
#include "Afichmation.h"
#include <SFML/Graphics.hpp>
using namespace sf;

class Personaje{
    // ==========================
    // Animación
    // ==========================
    Afichmation animacion;

    // ==========================
    // Movimiento horizontal
    // ==========================

    float velocidad = 90.f;
    Keyboard::Key izq = Keyboard::A;
    Keyboard::Key der = Keyboard::D;
    Keyboard::Key correr = Keyboard::LShift;

    // ==========================
    //  Movimiento vertical 
    // ==========================

    float gravedad;              
    float velocidadY = 0.f;      
    float velocidadSalto = 330.f; 

    bool enElAire = false;       
    bool saltoIniciado = false;  
    bool caidaIniciada = false;  

    Keyboard::Key saltar2 = Keyboard::W;       
    Keyboard::Key saltar1 = Keyboard::Space;

public:
    Personaje(Vector2f pos, float gravedadMundo);

    // ==========================
    // Metodos Principales
    // ==========================
    void actualizar(float deltaTime);
    void manejarEventos(Event& e);
    void dibujar(RenderWindow& w);

    // ==========================
    // Movimiento y Física
    // ==========================
    void animacionSalto();
    void mover(float deltaTime);
    void aplicarGravedad(float deltaTime);

    // ==========================
    // Utilidades / Estado
    // ==========================
    Vector2f verPos();                     
    bool estaQuieto();                     
    void verificarLimitesPantalla();     
    FloatRect verBounds();
};


