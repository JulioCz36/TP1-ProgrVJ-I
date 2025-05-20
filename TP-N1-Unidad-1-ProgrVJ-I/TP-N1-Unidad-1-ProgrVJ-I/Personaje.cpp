#include "Personaje.h"
Personaje::Personaje(Vector2f pos, float gravedadMundo) : animacion("assets/personaje/personaje_sheet.png", true, 64, 64), gravedad(gravedadMundo) {
    animacion.setPosition(pos);
    animacion.setScale(2.5, 2.5);

    animacion.Add("idle", { 0, 1, 2, 3, 4,5,6,7 }, 8, true);
    animacion.Add("walk", { 8, 9, 10, 11, 12,13,14,15 }, 8, true);
    animacion.Add("run", { 16, 17, 18, 19, 20,21,22,23 }, 8, true);
    animacion.Add("jump", { 24,25 }, 8, true);
    animacion.Add("fall", { 26,27 }, 8, true);
    animacion.Add("land", { 28,29}, 8, true);

    animacion.Play("idle");
}

void Personaje::actualizar(float deltaTime) {
    animacion.Update();
    mover(deltaTime);
    verificarLimitesPantalla();
    aplicarGravedad(deltaTime);
    animacionSalto();
     if (estaQuieto() && !enElAire) {
        animacion.Play("idle");
     }
}
void Personaje::manejarEventos(Event& e) {
    if (e.type == Event::KeyPressed && (e.key.code == saltar1 || e.key.code == saltar2) && !enElAire) {
        velocidadY = -velocidadSalto;
        enElAire = true;
    }
}
void Personaje::dibujar(RenderWindow& w) {
    w.draw(animacion);
}

void Personaje::mover(float deltaTime) {
    float desplazamiento = velocidad * deltaTime;

    if (Keyboard::isKeyPressed(der)) {
        animacion.FlipX(false);
        animacion.move(desplazamiento, 0);
        if(!enElAire)
        animacion.Play("walk");
    }
    if (Keyboard::isKeyPressed(izq)) {
        animacion.FlipX(true);
        animacion.move(-desplazamiento, 0);
        if (!enElAire)
            animacion.Play("walk");
    }
    if (Keyboard::isKeyPressed(der) && Keyboard::isKeyPressed(correr)) {
        animacion.FlipX(false);
        animacion.move(desplazamiento * 1.5f, 0);
        if (!enElAire)
            animacion.Play("run");
    }
    if (Keyboard::isKeyPressed(izq) && Keyboard::isKeyPressed(correr)) {
        animacion.FlipX(true);
        animacion.move(-desplazamiento * 1.5f, 0);
        if (!enElAire)
            animacion.Play("run");
    }   
}
void Personaje::aplicarGravedad(float deltaTime) {
    //gravedad
    velocidadY += gravedad * deltaTime;

    // Mover en Y
    animacion.move(0, velocidadY * deltaTime);

    // Aterrizaje
    if (animacion.getPosition().y >= 520) {
        animacion.setPosition(animacion.getPosition().x, 520);
        velocidadY = 0;
        enElAire = false;
    }
}
void Personaje::animacionSalto() {
    if (enElAire) {
        if (velocidadY < 0 && !saltoIniciado) {
            animacion.Play("jump");
            saltoIniciado = true;
            caidaIniciada = false;
        }
        else if (velocidadY > 0 && !caidaIniciada) {
            animacion.Play("fall");
            caidaIniciada = true;
        }
    }
    else {
        // Si acaba de aterrizar
        if (saltoIniciado || caidaIniciada) {
            saltoIniciado = false;
            caidaIniciada = false;
            animacion.Play("land");
        }
    }
}

Vector2f  Personaje::verPos() { return animacion.getPosition(); }
bool Personaje::estaQuieto() {
    return !(Keyboard::isKeyPressed(der) ||Keyboard::isKeyPressed(izq));
}
void Personaje::verificarLimitesPantalla() {
    FloatRect bounds = animacion.getGlobalBounds();
    Vector2f pos = animacion.getPosition();

    float margenIzquierdo = 55.f;
    float margenDerecho = 55.f;

    float izquierdaReal = pos.x - bounds.width / 2 + margenIzquierdo;
    float derechaReal = pos.x + bounds.width / 2 - margenDerecho;

    if (izquierdaReal  < 0) {
        animacion.setPosition(bounds.width / 2 - margenIzquierdo, pos.y);
    }
    if (derechaReal > 800) {
        animacion.setPosition(800 - bounds.width / 2 + margenDerecho, pos.y);
    }
}
FloatRect Personaje::verBounds() { return animacion.getGlobalBounds(); }
