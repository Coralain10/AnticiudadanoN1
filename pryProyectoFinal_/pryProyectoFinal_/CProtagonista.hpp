#pragma once
#include "CEntidad.hpp"

ref class CProtagonista : public CEntidad
{
private:
	short cant_vidas;
	short cant_balas;
public:
	CProtagonista(String^ ruta, short x, short y ,System::Drawing::Rectangle area, System::Drawing::Rectangle recorte, short n_f, short n_c)
		: CEntidad(ruta,x,y, area, recorte, n_f, n_c, 2) {
		this->imagen = gcnew Bitmap(ruta);
		this->recorte.Width = this->imagen->Width / this->n_columnas;
		this->recorte.Height = this->imagen->Height / this->n_filas;
		dx = dy = 5;
	}
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

