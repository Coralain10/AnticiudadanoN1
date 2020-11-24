#pragma once
#include "CEntidad.hpp"

ref class CProtagonista : public CEntidad
{
private:
	short cant_vidas;
	short cant_balas;
public:
	CProtagonista( System::Drawing::Rectangle area, System::Drawing::Rectangle recorte, short n_f, short n_c,short lado)
		: CEntidad("Imagenes\\Protagonista.png",area, recorte, n_f, n_c, direccion,"PROTAGONISTA",lado) {
		this->recorte.Width = this->imagen->Width / this->an_columnas;
		this->recorte.Height = this->imagen->Height / this->an_filas;
		dx = dy = 2;
		this->cant_vidas = 5;
	}
	~CProtagonista() {}

	void to_caminar() { this->dx = this->dy = 5; }
	void to_correr() { this->dx = this->dy = 8; }

	bool gano(short dire, CLaberinto^ escenario) {
		if (mover(dire, escenario) == SALIDA)
			return true;
		else
			return false;
	}

	void hacer_portales() {
		//TO DO
	}

	void recoger_municiones(CGrafico^ municion) {
		if (hay_colision(municion))
			this->cant_balas += 2;
	}

	void disparar() {
		//TO DO
	}
	
	void set_cant_vidas(short cant_vidas) { this->cant_vidas = cant_vidas; }
	short get_cant_vidas() { return cant_vidas; }
	void set_balas(short cant_balas) { this->cant_balas = cant_balas; }
	short get_cant_balas() { return cant_balas; }
};

