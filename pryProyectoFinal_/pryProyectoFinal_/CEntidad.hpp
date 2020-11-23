#pragma once
#include "CGrafico.hpp"
#include "CLaberinto.hpp"
#include <vector>
#include <string>
#include <math.h>

using namespace System::Collections::Generic;
using namespace std;

enum Direccion {Arriba,Abajo,Derecha,Izquierda};
//enum tipoceldas { PISO, PAREDMOV, PAREDFIJA, ENTRADA, SALIDA };

ref class CEntidad : public CGraficoAnimado
{
protected:
	short dx, dy;
	System::Drawing::Rectangle recorte;
	short direccion;
	enum acciones;
	short radio_vision;
	//vector<vector<short>>* circulo_vision_map;
	String^ tipo_grafico;

public:
	CEntidad() {}
	CEntidad(String^ ruta_imagen, System::Drawing::Rectangle area, System::Drawing::Rectangle recorte, short  n_f, short n_c,short direccion, String^ tipo_entidad):
		CGraficoAnimado(ruta_imagen, area, n_f, n_c), recorte(recorte), direccion(direccion), tipo_grafico(tipo_entidad) {
		this->recorte.Width = this->imagen->Width / this->an_columnas;
		this->recorte.Height = this->imagen->Height / this->an_filas;
		//this->imagen->MakeTransparent(this->imagen->GetPixel(0, 0));
	}
	~CEntidad() {
		//delete circulo_vision_map;
		delete tipo_grafico;
	}


	virtual short mover(short dire, CLaberinto^ escenario) {
		short x1, y1, x2, y2;
		switch ((Direccion)dire)
		{
		case IZQUIERDA:	x1 = x2 = (this->area_dibujo.X + this->ancho - 1 + 5) / this->ancho;
			y1 = (this->area_dibujo.Y) / this->alto;
			y2 = (this->area_dibujo.Y + this->alto - 1) / this->alto; break;
		case DERECHA: x1 = x2 = (this->area_dibujo.X - 5) / this->ancho;
			y1 = (this->area_dibujo.Y) / this->alto;
			y2 = (this->area_dibujo.Y + this->alto - 1) / this->alto; break;
		case ABAJO:		y1 = y2 = (this->area_dibujo.Y + this->alto - 1 + 5) / this->alto;
			x1 = (this->area_dibujo.X) / this->ancho;
			x2 = (short)((this->area_dibujo.X + this->ancho - 1) / this->ancho); break;
		case ARRIBA:	y1 = y2 = (this->area_dibujo.Y - 5) / this->alto;
			x1 = (this->area_dibujo.X) / this->ancho;
			x2 = (this->area_dibujo.X + this->ancho - 1) / this->ancho; break;
		}
		if (y1 >= 0 && y1 < escenario->get_alto() && y2 >= 0 && y2 < escenario->get_alto() &&
			x1 >= 0 && x1 < escenario->get_ancho() && x2 >= 0 && x2 < escenario->get_ancho()) {
			if ((escenario->get_mapa()[y1][x1] == PISO && escenario->get_mapa()[y2][x2] == PISO)
				|| (escenario->get_mapa()[y1][x1] == ENTRADA || escenario->get_mapa()[y1][x1] == SALIDA)
				|| (escenario->get_mapa()[y2][x2] == ENTRADA || escenario->get_mapa()[y2][x2] == SALIDA)) {
				switch ((Direccion)dire)
				{
				case Arriba:
					if (this->area_dibujo.Y - this->dy > 1)
						this->area_dibujo.Y -= this->dy;
					break;
				case Abajo:
					if (this->area_dibujo.Y + this->dy < escenario->get_alto() * escenario->get_tam_celda())
						this->area_dibujo.Y += this->dy;
					break;
				case Derecha:
					if (this->area_dibujo.X + this->dx < escenario->get_ancho() * escenario->get_tam_celda())
						this->area_dibujo.X += this->dx;
					break;
				case Izquierda:
					if (this->area_dibujo.X - this->dx > 1)
						this->area_dibujo.X -= this->dx;
					break;
				}
				if (escenario->get_mapa()[y1][x1] == SALIDA || escenario->get_mapa()[y1][x1] == SALIDA)
					return SALIDA;
				else
					return PISO;
			}
		}
		return PAREDMOV;
	}
	void dibujarSprite(Graphics^ graficador) {
		this->recorte.Location = Point(this->indice * this->recorte.Width, this->direccion * this->recorte.Height);
		graficador->DrawImage(this->imagen, this->area_dibujo, this->recorte, GraphicsUnit::Pixel);
		++this->indice %= this->an_columnas;
	}
	void set_dx(short dx) { this->dx = dx; }
	short get_dx() { return dx; }
	void set_dy(short dy) { this->dy = dy; }
	short get_dy() { return dy; }
	void set_radio_vision(short radio_vision) { this->radio_vision = radio_vision; }
	short get_radio_vision() { return radio_vision; }
	//void set_circulo_vision(vector<vector<short>>* circulo_vision) { this->circulo_vision_map = circulo_vision; }
	//void set_circulo_vision(short radio_vision) { circulo_vision_map = get_circulo_map(radio_vision); }
	//vector<vector<short>>* get_circulo_vision() { return circulo_vision_map; }

	/*
	vector<vector<short>>* get_circulo_map(short radio) {
		//TO DO
	}*/

	bool buscar_radio_vision(vector<vector<short>>* circulo, string tipo_grafico){
		//TO DO
		return false;
	}
private:
	System::Drawing::Rectangle calcular_area_recorte() {
		short ancho_subimagen = this->imagen->Width / this->an_columnas;
		short alto_subimagen = this->imagen->Height / this->an_filas;
		short x = this->indice % this->an_columnas * ancho_subimagen;
		short y = this->indice / this->an_columnas * alto_subimagen;
		return System::Drawing::Rectangle(x, y, ancho_subimagen, alto_subimagen);
	}
};

