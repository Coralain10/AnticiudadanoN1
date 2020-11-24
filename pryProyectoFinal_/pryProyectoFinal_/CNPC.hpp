#pragma once
#include "CEntidad.hpp"
#include <vector>
using namespace std;

ref class CNPC : public CEntidad
{
public:
	CNPC(String^ ruta, System::Drawing::Rectangle area, System::Drawing::Rectangle recorte, short n_f, short n_c,short direccion)
		: CEntidad(ruta, area, recorte, n_f, n_c, direccion,"NPC") {
		this->recorte.Width = this->imagen->Width / this->an_columnas;
		this->recorte.Height = this->imagen->Height / this->an_filas;
		dx = dy = 3;
	}
	~CNPC() {}

	void mover_auto() {
		//TO DO
	}

	virtual void seguir() {
		//TO DO
	}
};

ref class CAliado : public CNPC {
private:
	short tiempo_s_seguir;
	short porc_vida; //porcentaje de vida, inicia en 100%
	short porc_corrupcion; //porcentaje de corrupción, inicia en 0%
public:
	CAliado(String^ ruta, System::Drawing::Rectangle area, System::Drawing::Rectangle recorte, short n_f, short n_c):
	      CNPC(ruta, area, recorte, n_f, n_c, direccion) {}
	~CAliado() {}

	void seguir() override {
		
	}

	void set_tiempo_seguir(short segundos) { this->tiempo_s_seguir; }
	short get_tiempo_s_seguir() { return tiempo_s_seguir; }
};


//ENEMIGOS

ref class CAsesino : public CNPC {
private:
	int tiempo_s_ataque;
	short radio_peligro;
	vector<vector<short>>* circulo_peligro_map;
public:
	CAsesino(String^ ruta, System::Drawing::Rectangle area, System::Drawing::Rectangle recorte, short n_f, short n_c) :
		CNPC(ruta, area, recorte, n_f, n_c, direccion) {}
	~CAsesino() {
		delete circulo_peligro_map;
	}

	//podria resumirse en un string get_colision_tipoobj
	bool colisiona_aliado() {
		return false;
		//TO DO
	}
	bool colisiona_prota() {
		//TO DO
		return false;
	}

	void seguir() override {
		//TO DO
	}

	void set_tiempo_ataque(int segundos) { this->tiempo_s_ataque; }
	int get_tiempo_s_ataque() { return tiempo_s_ataque; }
	void set_circulo_peligro(vector<vector<short>>* circulo_peligro) { this->circulo_peligro_map = circulo_peligro; }
	//void set_circulo_peligro(short radio_peligro) { circulo_peligro_map = get_circulo_map(radio_peligro); }
	vector<vector<short>>* get_circulo_peligro() { return circulo_peligro_map; }
};

ref class CCorrupto : public CNPC {
private:
	int tiempo_s_corrupcion;

public:
	CCorrupto(String^ ruta, System::Drawing::Rectangle area, System::Drawing::Rectangle recorte, short n_f, short n_c) :
		CNPC(ruta, area, recorte, n_f, n_c, direccion) {}
	~CCorrupto() {}

	void seguir() override {
		//TO DO
	}
	void set_tiempo_corrup(int segundos) { this->tiempo_s_corrupcion; }
	int get_tiempo_s_corrup() { return tiempo_s_corrupcion; }
};