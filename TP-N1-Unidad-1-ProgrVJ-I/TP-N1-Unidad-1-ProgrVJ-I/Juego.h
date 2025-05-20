#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include "Personaje.h"

using namespace sf;
using namespace std;

class Juego{
	Texture fondoTextura;
	Sprite fondo;
	Clock relojDeltaTime;

	RenderWindow w;
	Personaje* jugador = nullptr;
	float gravedad =787.5f;

public:
	Juego();
	~Juego();
	void jugar();
	void actualizar();
	void dibujar();
	void procesoEventos();
};

