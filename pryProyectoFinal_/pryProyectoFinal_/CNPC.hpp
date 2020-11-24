#pragma once
#include "CEntidad.hpp"
#include <vector>
using namespace std;

ref class CNPC : public CEntidad
{
protected:
	bool dire_invX, dire_invY;
public:
	CNPC(String^ ruta, System::Drawing::Rectangle area, System::Drawing::Rectangle recorte, short n_f, short n_c,short direccion,short lado)
		: CEntidad(ruta, area, recorte, n_f, n_c, direccion,"NPC",lado) {
		this->recorte.Width = this->imagen->Width / this->an_columnas;
		this->recorte.Height = this->imagen->Height / this->an_filas;
		dx = dy = 3;	
	}
	CNPC(String^ ruta, System::Drawing::Rectangle area, System::Drawing::Rectangle recorte, short n_f, short n_c, short direccion, short lado,bool esinvx,bool esinvy)
		: CEntidad(ruta, area, recorte, n_f, n_c, direccion, "NPC", lado) , dire_invX(esinvx), dire_invY(esinvy){
		this->recorte.Width = this->imagen->Width / this->an_columnas;
		this->recorte.Height = this->imagen->Height / this->an_filas;
		dx = dy = 3;
	}
	~CNPC() {}
	void set_dire_invX(bool esinvdirex) { this->dire_invX = esinvdirex; }
	void set_dire_invY(bool esinvdirey) { this->dire_invY = esinvdirey; }
	void mover_auto(short dire,CLaberinto^ escenario) {

		short dire_aux=dire;

		if (dire_invY == true) {
			if (dire == Arriba)
				dire_aux = Abajo;
			else if (dire == Abajo)
				dire_aux = Arriba;
		}
		if (dire_invX == true) {
			if (dire == Derecha)
				dire_aux = Izquierda;
			else if (dire == Izquierda)
				dire_aux = Derecha;
		}
		
		mover(dire_aux, escenario);
		
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
	CAliado(System::Drawing::Rectangle area, System::Drawing::Rectangle recorte, short n_f, short n_c,short lado):
	      CNPC("Imagenes\\ciudadano_M.png",area, recorte, n_f, n_c, direccion,lado) {
		dx = dy = rand()%3+1;
		short a = rand() % 2;
		if (a % 2 == 0)
			edit_imagen("Imagenes\\ciudadano_F.png",this->ancho, this->alto);
		this->recorte.Width = this->imagen->Width / this->an_columnas;
		this->recorte.Height = this->imagen->Height / this->an_filas;
	}
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
	CAsesino(String^ ruta, System::Drawing::Rectangle area, System::Drawing::Rectangle recorte, short n_f, short n_c,short lado) :
		CNPC(ruta, area, recorte, n_f, n_c, direccion,lado) {}
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
	CCorrupto(String^ ruta, System::Drawing::Rectangle area, System::Drawing::Rectangle recorte, short n_f, short n_c,short lado,bool esinvx,bool esinvy) :
		CNPC(ruta, area, recorte, n_f, n_c, direccion,lado,esinvx,esinvy) {

	}
	~CCorrupto() {}
	
	void seguir() override {
		
	}
	void set_tiempo_corrup(int segundos) { this->tiempo_s_corrupcion; }
	int get_tiempo_s_corrup() { return tiempo_s_corrupcion; }
};
