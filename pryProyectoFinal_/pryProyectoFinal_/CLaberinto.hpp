#pragma once
#include "CGrafico.hpp"
#include "CCamino.hpp"
#include <vector>
using namespace std;

ref class CLaberinto {
private:
	short ancho;
	short alto;
	CCelda^ entrada;
	CCelda^ salida;
	vector<vector<short>>* mapa;
	vector<CGrafico>* balas; //municiones

	enum paredes_pos { ARRIBA, ABAJO, IZQUIERDA, DERECHA };

public:
	CLaberinto(short ancho, short alto)
:ancho(ancho),alto(alto){}
	~CLaberinto() {
		delete mapa;
		delete balas;
		delete entrada;
		delete salida;
	}

	CCelda^ get_entrada() { return this->entrada; }
	CCelda^ get_salida() { return this->salida; }

	void pintar_mapa() {
		//TO DO
	}

	void colocar_balas() {
		//TO DO
	}
	void quitar_bala() {
		//TO DO
	}

	
private:

	void crear_mapa() {
		vector<vector<short>>* aux_mapa;

		for (short i = 0; i < alto; i++)
			for (short j = 0; j < ancho; j++)
				aux_mapa->at(i).at(j) = rand() % 2;

		set_entrada_salida();

		CCamino^ aux_camino = gcnew CCamino(aux_mapa, entrada, salida);
		if (aux_camino->existe_camino()) {
			this->mapa = aux_mapa;
			return;
		}
		else {
			delete aux_mapa;
			crear_mapa();
		}
	}

	CCelda^ celda_pared() {
		short x, y;
		short ubicacion_lado = rand() % 4;
		switch (ubicacion_lado)
		{
		case ARRIBA:
			y = 0;
			x = rand() % ancho;
			break;
		case ABAJO:
			y = alto - 1;
			x = rand() % ancho;
		case IZQUIERDA:
			x = 0;
			y = rand() % alto;
		case DERECHA:
			x = ancho-1;
			y = rand() % alto;
		}

		return gcnew CCelda(x,y);
	}

	void set_entrada_salida() {
		set_entrada();
		set_salida();
	}

	void set_entrada() { this->entrada = celda_pared(); }
	void set_salida() {
		CCelda^ auxCelda = celda_pared();
		if (auxCelda->get_x() == entrada->get_x() && auxCelda->get_y() == entrada->get_y())
		{
			delete auxCelda;
			set_salida();
		}
		else {
			this->salida = auxCelda;
		}
	}
};
