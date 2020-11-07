#pragma once
#include "CGrafico.hpp"
#include <vector>
using namespace std;

ref class CLaberinto {
private:
	short ancho;
	short alto;
	vector<vector<CGrafico>>* mapa;
	vector<CGrafico>* balas; //municiones

public:
	CLaberinto(){}
	~CLaberinto() {
		delete mapa;
		delete balas;
	}

	vector<vector<CGrafico>>* crear_mapa() {
		//TO DO
	}

	bool existe_camino() {
		//TO DO
	}

	void pintar_mapa() {
		//TO DO
	}

	void colocar_balas() {
		//TO DO
	}
	void quitar_bala() {
		//TO DO
	}
};
