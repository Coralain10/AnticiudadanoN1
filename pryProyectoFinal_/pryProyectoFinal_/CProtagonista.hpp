#pragma once
#include "CEntidad.hpp"

ref class CProtagonista : public CEntidad
{
private:
	short cant_vidas;
	short cant_balas;
public:
	CProtagonista() {}
	~CProtagonista() {}

	void caminar() {
		//TO DO
	}

	void correr() {
		//TO DO
	}

	void hacer_portales() {
		//TO DO
	}

	void recoger_municiones() {
		//TO DO
	}

	void disparar() {
		//TO DO
	}

	void set_cant_vidas(short cant_vidas) { this->cant_vidas = cant_vidas; }
	short get_cant_vidas() { return cant_vidas; }
	void set_balas(short cant_balas) { this->cant_balas = cant_balas; }
	short get_cant_balas() { return cant_balas; }
};

