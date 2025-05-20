#include "Juego.h"

Juego::Juego() : w(VideoMode(800, 600), "Trabajo Práctico Nº 1 - Parte 1", Style::Titlebar | Style::Close) {
	w.setFramerateLimit(60);

	fondoTextura.loadFromFile("assets/mundo/mundo_fondo.png");
	fondo.setTexture(fondoTextura);

	jugador = new Personaje(Vector2f(400, 520), gravedad);
}
Juego::~Juego() {
	delete jugador;
}
void Juego::jugar() {

	while (w.isOpen()) {
		procesoEventos();
		w.clear();

		actualizar();

		dibujar();

		w.display();
	}
}

void Juego::actualizar() {
	float deltaTime = relojDeltaTime.restart().asSeconds();
	jugador->actualizar(deltaTime);
}
void Juego::dibujar() {
	w.draw(fondo); 
	jugador->dibujar(w);
}

void Juego::procesoEventos() {
	Event e;
	while (w.pollEvent(e)) {
		if (e.type == Event::Closed) {
			w.close();
		}
		jugador->manejarEventos(e);
	}
}

