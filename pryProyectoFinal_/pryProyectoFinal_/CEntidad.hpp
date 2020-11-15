#pragma once
#include "CGrafico.hpp"
#include <vector>
#include <string>

using namespace System::Collections::Generic;
using namespace std;


ref class CEntidad : public CGraficoAnimado
{
protected:
	short dx, dy;
	enum acciones;
	short radio_vision;
	vector<vector<short>>* circulo_vision_map;
	string* tipo_grafico;

public:
	CEntidad() {}
	~CEntidad() {
		delete circulo_vision_map;
		delete tipo_grafico;
	}

	void mover() {
		//TO DO
	}

	void set_dx(short dx) { this->dx = dx; }
	short get_dx() { return dx; }
	void set_dy(short dy) { this->dy = dy; }
	short get_dy() { return dy; }
	void set_radio_vision(short radio_vision) { this->radio_vision = radio_vision; }
	short get_radio_vision() { return radio_vision; }
	void set_circulo_vision(vector<vector<short>>* circulo_vision) { this->circulo_vision_map = circulo_vision; }
	//void set_circulo_vision(short radio_vision) { circulo_vision_map = get_circulo_map(radio_vision); }
	vector<vector<short>>* get_circulo_vision() { return circulo_vision_map; }

	/*
	vector<vector<short>>* get_circulo_map(short radio) {
		//TO DO
	}*/

	bool buscar_radio_vision(vector<vector<short>>* circulo, string tipo_grafico){
		//TO DO
		return false;
	}
};

