#pragma once
#include "CGrafico.hpp"
//#include "CCamino.hpp"
#include <vector>

using namespace std;
using namespace System::Collections::Generic;
using namespace System::Drawing;

enum tipo_celdas { PISO, PAREDMOV, PAREDFIJA, ENTRADA, SALIDA };
enum posiciones { ARRIBA, ABAJO, IZQUIERDA, DERECHA };

ref class CLaberinto {
private:
	unsigned short ancho, alto;
	unsigned short tamanho_celda;
	float factor_paredes, densidad; //probabilidad que aparezcan
	short prob_balas, espacio_paredes;
	CGrafico^ entrada;
	CGrafico^ salida;
	Point pos_entrada;
	Point pos_salida;
	vector<vector<short>>* mapa;
	CGrafico^ piso;
	Bitmap^ img_partes_lab;
	Bitmap^ img_bala;
	List<CGrafico^>^ paredes_fijas;
	List<CGrafico^>^ paredes_mov;
	List<CGrafico^>^ balas; //municiones

public:
	CLaberinto(short ancho, short alto, short tamanho_celda) : tamanho_celda(tamanho_celda) {
		this->espacio_paredes = 2;
		this->ancho = ancho + ancho % espacio_paredes;
		this->alto = alto + alto % espacio_paredes;
		this->mapa = new vector<vector<short>>();

		img_partes_lab = gcnew Bitmap("Imagenes\\laberinto.png");
		img_bala = gcnew Bitmap("Imagenes\\dialog.png");
		piso = gcnew CGrafico(img_partes_lab, tamanho_celda, tamanho_celda);
		paredes_fijas = gcnew List<CGrafico^>;
		paredes_mov = gcnew List<CGrafico^>;
		entrada = gcnew CGrafico("Imagenes\\buttons.png",tamanho_celda, tamanho_celda);
		salida = gcnew CGrafico("Imagenes\\buttons.png", tamanho_celda, tamanho_celda);
		balas = gcnew List<CGrafico^>;
		prob_balas = 10;
		factor_paredes = .75;
		densidad = .5;
		crear_mapa();
		colocar_balas();
	}
	~CLaberinto() {
		delete mapa;
		delete entrada;
		delete salida;
		delete piso;
		delete img_partes_lab;
		for each (CGrafico ^ pared in paredes_fijas)
			delete pared;
		delete paredes_fijas;
		for each (CGrafico ^ pared in paredes_mov)
			delete pared;
		delete paredes_mov;
		for each (CGrafico ^ bala in balas)
			delete bala;
		delete balas;
		delete img_bala;
	}

	Point get_pos_entrada() { return this->pos_entrada; }
	Point get_pos_salida() { return this->pos_salida; }
	CGrafico^ get_entrada() { return this->entrada; }
	CGrafico^ get_salida() { return this->salida; }

	void pintar_mapa(Graphics^ graficador) {
		for (short i = 0; i < alto; i++)
		{
			for (short j = 0; j < ancho; j++)
			{
				if (mapa->at(i).at(j) == PISO)
				{
					piso->set_ubicacion(j * tamanho_celda, i * tamanho_celda);
					piso->dibujar(graficador, 0, 32, 32, 32);
				}
			}
		}

		for each (CGrafico ^ pared in paredes_fijas)
			pared->dibujar(graficador, 0, 0, 32, 32);
		for each (CGrafico ^ pared in paredes_mov)
			pared->dibujar(graficador, 32, 0, 32, 32);

		entrada->dibujar(graficador, 0, 0, 160, 160);
		salida->dibujar(graficador, 0, 160, 160, 160);
	}

	void colocar_balas() {
		short aux = 0;

		for (short i = 0; i < mapa->size(); i++)
		{
			for (short j = 0; j < mapa->at(i).size(); j++)
			{
				if (mapa->at(i).at(j) == PISO)
				{
					aux = rand() % prob_balas;

					if (aux == 0)
						balas->Add(gcnew CGrafico(img_bala, j * tamanho_celda, i * tamanho_celda, tamanho_celda, tamanho_celda));
				}
			}
		}
	}

	void quitar_bala() {
		//TO DO
	}

	
private:

	void crear_mapa() {
		//AJUSTE DE COMPLEJIDAD
		factor_paredes = (short)(factor_paredes*(ancho + alto));
		densidad = (short)(densidad*ancho*alto);

		//LLENANDO EL VECTOR
		for (short i = 0; i < alto; i++)
		{
			vector<short> aux_fila = vector<short>();

			for (short j = 0; j < ancho; j++)
			{
				//LLENANDO LOS BORDES
				if (i == 0 || i == alto - 1 || j == 0 || j == ancho - 1)
				{
					aux_fila.push_back(PAREDFIJA);
					paredes_fijas->Add(gcnew CGrafico(img_partes_lab, j * tamanho_celda, i * tamanho_celda, tamanho_celda, tamanho_celda));
				}
				else
					aux_fila.push_back(PISO); //POR DEFAULT EL RESTO SERA PISO
			}
			this->mapa->push_back(aux_fila);
		}



		for (short i = 0; i < densidad; i++)
		{
			short x = rand() % ((ancho / espacio_paredes) - (espacio_paredes * 2)) + espacio_paredes,
				y = rand() % ((alto / espacio_paredes) - (espacio_paredes * 2)) + espacio_paredes ;
			x += x % espacio_paredes;
			y += y % espacio_paredes;
			//numero entre el 0 y (ancho o alto/espacio_paredes-1) - los 2 espacios de paredes hacia los bordes + desde el 1er borde

			if (this->mapa->at(y).at(x) != PAREDFIJA) {
				this->mapa->at(y).at(x) = PAREDFIJA;
				paredes_fijas->Add(gcnew CGrafico(img_partes_lab, x * tamanho_celda, y * tamanho_celda, tamanho_celda, tamanho_celda));
			}

			for (short j = 0; j < factor_paredes; j++)
			{
				short vecinos[4][2] = { {x - espacio_paredes,y}, {x + espacio_paredes,y}, {x,y - espacio_paredes}, {x,y + espacio_paredes} };
				short pos_vecino = rand() % 3;
				short x_ = vecinos[pos_vecino][0]; //maximo puede tene 3 vecinos x está en la 1era posición
				short y_ = vecinos[pos_vecino][1]; //maximo puede tene 3 vecinos y está en la 2da posición

				if (x_ > 0 && y_ > 0 && x_ < ancho && y_ < alto)
				{
					if (this->mapa->at(y_).at(x_) == PISO)
					{
						this->mapa->at(y_).at(x_) = PAREDMOV;
						paredes_fijas->Add(gcnew CGrafico(img_partes_lab, x_ * tamanho_celda, y_ * tamanho_celda, tamanho_celda, tamanho_celda));

						short pos_inter[2] = { x_ + (x - x_) / 2, y_ + (y - y_) / 2 };

						this->mapa->at(pos_inter[1]).at(pos_inter[0]) = PAREDMOV;
						paredes_mov->Add(gcnew CGrafico(img_partes_lab, pos_inter[0] * tamanho_celda, (pos_inter[1]) * tamanho_celda, tamanho_celda, tamanho_celda));
						x = x_;
						y = y_;
					}
				}
			}
		}
		set_entrada_salida();
	}

	Point celda_pared() { //Poner la entrada en una pared
		short x, y;
		short ubicacion_lado = rand() % 4;
		switch (ubicacion_lado)
		{
		case ARRIBA:
			y = 0;
			x = rand() % (ancho - 2 - espacio_paredes);//evade esquinas
			x += (x % espacio_paredes) + (short)(espacio_paredes/2); //evade posicion peligrosa
			break;
		case ABAJO:
			y = alto - 1;
			x = rand() % (ancho - 2 - espacio_paredes);//evade esquinas
			x += (x % espacio_paredes) + (short)(espacio_paredes/2); //evade posicion peligrosa
		case IZQUIERDA:
			x = 0;
			y = rand() % (alto - 2 - espacio_paredes);//evade esquinas
			y += (y % espacio_paredes) + (short)(espacio_paredes / 2); //evade posicion peligrosa
		case DERECHA:
			x = ancho - 1;
			y = rand() % (alto - 2 - espacio_paredes);//evade esquinas
			y += (y % espacio_paredes) + (short)(espacio_paredes / 2); //evade posicion peligrosa
		}

		return Point(x,y);
	}
	void set_pos_entrada() { this->pos_entrada = celda_pared(); }
	void set_pos_salida() {
		Point auxCelda = celda_pared();
		if (auxCelda == pos_entrada)
			set_pos_salida();
		else
			this->pos_salida = auxCelda;
	}

	void set_entrada_salida() {
		set_pos_entrada();
		set_pos_salida();
		quitar_parte(this->pos_entrada.X, this->pos_entrada.Y, PAREDFIJA);
		quitar_parte(this->pos_salida.X, this->pos_salida.Y, PAREDFIJA);
		this->entrada->set_ubicacion(this->pos_entrada.X*tamanho_celda, this->pos_entrada.Y*tamanho_celda);
		this->salida->set_ubicacion(this->pos_salida.X*tamanho_celda, this->pos_salida.Y*tamanho_celda);
	}

	void quitar_parte(short x, short y, short TIPO) {
		switch (TIPO)
		{
			case PAREDFIJA:
				for each (CGrafico^ celda in paredes_fijas)
					if (x * tamanho_celda == celda->get_x() && y * tamanho_celda == celda->get_y()) {
						paredes_fijas->Remove(celda);
						break;
					}
				break;
			case PAREDMOV:
				for each (CGrafico ^ celda in paredes_mov)
					if (x * tamanho_celda == celda->get_x() && y * tamanho_celda == celda->get_y()) {
						paredes_fijas->Remove(celda);
						break;
					}
				break;
		}
	}
};
