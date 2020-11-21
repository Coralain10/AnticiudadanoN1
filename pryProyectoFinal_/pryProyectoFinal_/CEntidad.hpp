#pragma once
#include "CGrafico.hpp"
#include <vector>
#include <string>


using namespace System::Collections::Generic;
using namespace std;

enum Direccion {Arriba,Abajo,Derecha,Izquierda};
//enum tipoceldas { PISO, PAREDMOV, PAREDFIJA, ENTRADA, SALIDA };

ref class CEntidad : public CGraficoAnimado
{
protected:
	short dx, dy;
	System::Drawing::Rectangle area, recorte;
	short indice; 
	short n_filas, n_columnas, direccion;
	enum acciones;
	short radio_vision;
	//vector<vector<short>>* circulo_vision_map;
	string* tipo_grafico;

public:
	CEntidad() {}
	CEntidad(String^ ruta_imagen, short x, short y ,System::Drawing::Rectangle area, System::Drawing::Rectangle recorte, short  n_f, short n_c,short direccion):
		area(area), recorte(recorte), n_filas(n_f), n_columnas(n_c), indice(0), direccion(direccion) {
		this->imagen = gcnew Bitmap(ruta_imagen);
		this->recorte.Width = this->imagen->Width / this->n_columnas;
		this->recorte.Height = this->imagen->Height / this->n_filas;
		this->imagen->MakeTransparent(this->imagen->GetPixel(0, 0));
	}
	~CEntidad() {
		//delete circulo_vision_map;
		delete tipo_grafico;
	}


	void mover(short dire, short** escenario) {
		short x1, y1, x2, y2;
		switch ((Direccion)dire)
		{
		case DERECHA:	x1 = x2 = (area.X + alto - 1 + 2);
			y1 = (area.Y) ;
			y2 = (area.Y + alto - 1); break;
		case IZQUIERDA: x1 = x2 = (area.X - 2);
			y1 = (area.Y);
			y2 = (area.Y + alto - 1); break;
		case ABAJO: y1 = y2 = (area.Y + ancho - 1 + 2);
			x1 = (area.X);
			x2 = (area.X + ancho - 1) ; break;
		case ARRIBA: y1 = y2 = (area.Y - 2);
			x1 = (area.X) / alto;
			x2 = (area.X + ancho - 1); break;
		}
		if ((escenario[y1][x1] == PISO||ENTRADA) && (escenario[y2][x2] == PISO || ENTRADA)) {
			switch (dire)
			{
			case Arriba:
				this->area.Y -= this->dy;
				break;
			case Abajo:
				this->area.Y += this->dy;
				break;
			case Derecha:
				this->area.X += this->dx;
				break;
			case Izquierda:
				this->area.X -= this->dx;
				break;
			}
		}
	}
	void dibujarSprite(Graphics^ graficador) {
		this->recorte.Location = Point(this->indice * this->recorte.Width, this->direccion * this->recorte.Height);
		graficador->DrawImage(this->imagen, this->area, this->recorte, GraphicsUnit::Pixel);
		++this->indice %= this->n_columnas;
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

