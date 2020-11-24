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
	short esp_rest_ancho, esp_rest_alto;
	unsigned short tamanho_celda;
	float factor_paredes, densidad; //probabilidad que aparezcan
	short prob_balas, espacio_paredes;
	CGrafico^ entrada;
	CGrafico^ salida;
	Point pos_entrada;
	Point pos_salida;
	short** mapa;
	CGrafico^ piso;
	CGrafico^ pared_mov;
	CGrafico^ pared_fija;
	Bitmap^ img_partes_lab;
	Bitmap^ img_bala;
	List<CGrafico^>^ balas; //municiones

public:
	CLaberinto(short ancho, short alto, short tamanho_celda) : tamanho_celda(tamanho_celda) {
		this->espacio_paredes = 4;
		this->ancho = ancho - (ancho % espacio_paredes) +1;
		this->alto = alto - (alto % espacio_paredes) +1;
		this->esp_rest_ancho = ancho - this->ancho < 0 ? 0 : ancho - this->ancho + 1;
		this->esp_rest_alto = alto - this->alto < 0 ? 0 : ancho - this->alto + 1;

		img_partes_lab = gcnew Bitmap("Imagenes\\laberinto.png");
		img_bala = gcnew Bitmap("Imagenes\\municion.png");
		piso = gcnew CGrafico(img_partes_lab, System::Drawing::Rectangle(0, 32, 32, 32), tamanho_celda, tamanho_celda);
		pared_mov = gcnew CGrafico("Imagenes\\pared_mov.png", System::Drawing::Rectangle(0, 0, 32, 32), tamanho_celda, tamanho_celda);
		pared_fija = gcnew CGrafico(img_partes_lab, System::Drawing::Rectangle(0, 0, 32, 32), tamanho_celda, tamanho_celda);
		entrada = gcnew CGrafico(img_partes_lab, System::Drawing::Rectangle(32, 0, 32, 32), tamanho_celda, tamanho_celda);
		salida = gcnew CGrafico(img_partes_lab, System::Drawing::Rectangle(32, 32, 32, 32), tamanho_celda, tamanho_celda);
		balas = gcnew List<CGrafico^>;
		prob_balas = 100; //1(siempre)-100(1 de 100 oportunidades)
		factor_paredes = 1; //.75
		densidad = 1; //.5
		crear_mapa();
		entrada->set_ubicacion(pos_entrada.X * tamanho_celda, pos_entrada.Y * tamanho_celda);
		salida->set_ubicacion(pos_salida.X * tamanho_celda, pos_salida.Y * tamanho_celda);
		colocar_balas();
	}
	~CLaberinto() {
		delete mapa;
		delete entrada;
		delete salida;
		delete piso;
		delete pared_mov;
		delete img_partes_lab;
		delete pared_fija;
		for each (CGrafico ^ bala in balas)
			delete bala;
		delete balas;
		delete img_bala;
	}

	Point get_pos_entrada() { return this->pos_entrada; }
	Point get_pos_salida() { return this->pos_salida; }
	CGrafico^ get_entrada() { return this->entrada; }
	CGrafico^ get_salida() { return this->salida; }
	short** get_mapa() { return this->mapa; }
	short get_ancho() { return this->ancho; }
	short get_alto() { return this->alto; }
	short get_tam_celda() { return this->tamanho_celda; }

	void pintar_mapa(Graphics^ graficador) {
		for (short i = 0; i < alto + esp_rest_alto; i++)
		{
			for (short j = 0; j < ancho + esp_rest_ancho; j++)
			{
				if (i < alto && j < ancho)
				{
					switch (mapa[i][j])
					{
						case PISO: piso->set_ubicacion(j * tamanho_celda, i * tamanho_celda);
							piso->dibujar(graficador);
							break;
						case PAREDFIJA: pared_fija->set_ubicacion(j * tamanho_celda, i * tamanho_celda);
							pared_fija->dibujar(graficador);
							break;
						case PAREDMOV: pared_mov->set_ubicacion(j * tamanho_celda, i * tamanho_celda);
							pared_mov->dibujar(graficador);
							break;
						case ENTRADA: entrada->dibujar(graficador); break;
						case SALIDA: salida->dibujar(graficador); break;
					}
				}
				else if (i >= alto || j >= ancho) {
					pared_fija->set_ubicacion(j * tamanho_celda, i * tamanho_celda);
					pared_fija->dibujar(graficador);
				}
			}
		}

		entrada->dibujar(graficador);
		salida->dibujar(graficador);

		for each (CGrafico ^ bala in balas)
			bala->dibujar(graficador);
	}

	void colocar_balas() {
		short aux = 0;

		for (short i = 0; i < alto; i++)
		{
			for (short j = 0; j < ancho; j++)
			{
				if (mapa[i][j] == PISO)
				{
					aux = rand() % prob_balas;

					if (aux == 0)
						balas->Add(gcnew CGrafico(img_bala, j * tamanho_celda, i * tamanho_celda, tamanho_celda, tamanho_celda));
				}
			}
		}
	}

	void quitar_bala(CGrafico^ municion) {
		this->balas->Remove(municion);
	}
	Point pos_cerca(Point pos_actual, short dist_max) {
		return pos_rand_but_pos(pos_actual, 0, dist_max, dist_max);
	}

	Point pos_lejos(Point pos_actual, short dist_min) {
		return pos_rand_but_pos(pos_actual, dist_min, this->ancho, this->alto);
	}

	Point pos_rand_but_pos(Point pos_actual, short dist_min, short dist_max_x, short dist_max_y) {
		Point pos_aux = Point();
		int dist_aux;

		dist_aux = rand() % abs(dist_max_x - dist_min);
		pos_aux.X = dist_aux % 2 == 0 ? pos_actual.X + dist_aux : abs(pos_actual.X - dist_aux);

		dist_aux = rand() % abs(dist_max_y - dist_min);
		pos_aux.Y = dist_aux % 2 == 0 ? pos_actual.Y + dist_aux : abs(pos_actual.Y - dist_aux);

		if ( pos_aux.Y < alto - 1 && pos_aux.Y > 0 &&
			pos_aux.X < ancho - 1 && pos_aux.X > 0 &&//este definido
			this->mapa[pos_aux.Y][pos_aux.X] == PISO /*&& //sea piso
			abs(pos_aux.X - pos_actual.X) >= dist_min && //esté lejos min dist_min celdas
			abs(pos_aux.Y - pos_actual.Y) >= dist_min &&
			abs(pos_aux.X - pos_actual.X) <= dist_max && //esté cerca max dist_max celdas
			abs(pos_aux.Y - pos_actual.Y) <= dist_max*/)
			return pos_aux;
		else
			return pos_rand_but_pos(pos_actual, dist_min, dist_max_x, dist_max_y);
	}
	
private:

	void crear_mapa() {
		//AJUSTE DE COMPLEJIDAD
		factor_paredes = (short)(factor_paredes*(ancho + alto));
		densidad = (short)(densidad*ancho*alto);

		//LLENANDO EL VECTOR
		this->mapa = new short* [this->alto];
		for (short i = 0; i < alto; i++)
		{
			this->mapa[i] = new short[this->ancho];

			for (short j = 0; j < ancho; j++)
			{
				//LLENANDO LOS BORDES
				if (i == 0 || i == alto - 1 || j == 0 || j == ancho - 1)
					mapa[i][j] = PAREDFIJA;
				else
					mapa[i][j] = PISO; //POR DEFAULT EL RESTO SERA PISO
			}
		}

		for (short i = 0; i < densidad; i++)
		{
			short x = (rand() % ((ancho + (espacio_paredes - 1)) / espacio_paredes)) * espacio_paredes,
				y = (rand() % ((alto + (espacio_paredes - 1)) / espacio_paredes)) * espacio_paredes;
			//x += x % espacio_paredes;
			//y += y % espacio_paredes;
			//numero entre el 0 y (ancho o alto/espacio_paredes-1) - los 2 espacios de paredes hacia los bordes + desde el 1er borde

			if (mapa[y][x] != PAREDFIJA)
				this->mapa[y][x] = PAREDFIJA;

			for (short j = 0; j < factor_paredes; j++)
			{
				//ARRIBA ABAJO IZQUIERDA DERECHA
				short vecinos[4][2] = { { x, y - espacio_paredes}, { x, y + espacio_paredes}, { x - espacio_paredes, y}, { x + espacio_paredes, y} };
				short pos_vecino = rand() % 3; //maximo puede tene 3 vecinos
				short x_ = vecinos[pos_vecino][0]; // x está en la 1era posición
				short y_ = vecinos[pos_vecino][1]; // y está en la 2da posición

				if (x_ >= 0 && y_ >= 0 && x_ < ancho && y_ < alto)
				{
					if (this->mapa[y_][x_] == PISO)
					{
						this->mapa[y_][x_] = PAREDMOV;
						
						//short pos_inter[2] = { x_ + (x - x_) / 2, y_ + (y - y_) / 2 };
						
						short pos_inter[2] = { x_, y_ }; //inicia en la semilla
						short inicio, fin; // COMO EL ESPACIADO PUEDE SER + DE 2, se debe calcular en todo el camino, no solo la posicion media
						

						switch (pos_vecino)
						{
							case ARRIBA: //sube en y
								inicio = y_ + 1;
								fin = y - 1;
								break;
							case ABAJO: //baja en y
								inicio = y + 1;
								fin = y_ - 1;
								break;
							case IZQUIERDA: //retrocede en x
								inicio = x_ + 1;
								fin = x - 1;
								break;
							case DERECHA: //avanza en x
								inicio = x + 1;
								fin = x_ - 1;
								break;
						}
						for (short k = inicio; k <= fin; k++)
						{
							if (pos_vecino == IZQUIERDA || pos_vecino == DERECHA)
								pos_inter[0] = k;
							else if (pos_vecino == ARRIBA || pos_vecino == ABAJO)
								pos_inter[1] = k;

							this->mapa[pos_inter[1]][pos_inter[0]] = PAREDMOV;
						}
						//this->mapa->at(pos_inter[1]).at(pos_inter[0]) = PAREDMOV;

						x = x_;
						y = y_;
					}
				}
			}
		}
		set_pos_entrada();
		set_pos_salida();
		this->mapa[pos_entrada.Y][pos_entrada.X] = ENTRADA;
		this->mapa[pos_salida.Y][pos_salida.X] = SALIDA;
	}

	Point celda_pared() { //Poner la entrada en una pared
		short x, y;
		short ubicacion_lado = rand() % 4;
		switch (ubicacion_lado)
		{
		case ARRIBA:
			y = 0;
			x = rand() % (ancho - 2);//evade esquinas
			x += x % espacio_paredes + 1; //evade posicion peligrosa
			break;
		case ABAJO:
			y = alto - 1;
			x = rand() % (ancho - 2);//evade esquinas
			x += x % espacio_paredes + 1; //evade posicion peligrosa
			break;
		case IZQUIERDA:
			x = 0;
			y = rand() % (alto - 2);//evade esquinas
			y += y % espacio_paredes + 1; //evade posicion peligrosa
			break;
		case DERECHA:
			x = ancho - 1;
			y = rand() % (alto - 2);//evade esquinas
			y += y % espacio_paredes + 1; //evade posicion peligrosa
			break;
		}
		x = x > ancho - 1 ? ancho - 1 : x;
		y = y > alto - 1 ? alto - 1 : y;
		(x == ancho - 1 && y == alto - 1) ? x-- : x;

		return Point(x,y);
	}
	void set_pos_entrada() { this->pos_entrada = celda_pared(); }
	void set_pos_salida() {
		Point aux_pos = celda_pared();
		if (aux_pos == pos_entrada)
			set_pos_salida();
		else
		{
			//evitar que coincidan en la misma pared
			if (this->pos_entrada.X == aux_pos.X)
				aux_pos.X == 0 ? aux_pos.X = ancho - 1 : aux_pos.X = 0;
			else if (this->pos_entrada.Y == aux_pos.Y)
				aux_pos.Y == 0 ? aux_pos.Y = alto - 1 : aux_pos.Y = 0;
			//evitar que esten cerca
			else if (abs(this->pos_entrada.Y - aux_pos.Y) < alto / 2 && abs(this->pos_entrada.X - aux_pos.X) < ancho / 2) {
				aux_pos.Y - alto / 2 < 0 ? aux_pos.Y *= 2 : aux_pos.Y /= 2;
				aux_pos.X - ancho / 2 < 0 ? aux_pos.X *= 2 : aux_pos.X /= 2;
				aux_pos.X != 0 ? aux_pos.X += aux_pos.X % espacio_paredes + 1 : aux_pos.X;
				aux_pos.Y != 0 ? aux_pos.Y += aux_pos.Y % espacio_paredes + 1 : aux_pos.Y;
			}
			aux_pos.X = aux_pos.X > ancho - 1 ? ancho - 1 : aux_pos.X;
			aux_pos.Y = aux_pos.Y > alto - 1 ? alto - 1 : aux_pos.Y;
			(aux_pos.X == ancho - 1 && aux_pos.Y == alto - 1) ? aux_pos.X-- : aux_pos.X;

			this->pos_salida = aux_pos;
		}
	}

	/*
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
	}*/

};
