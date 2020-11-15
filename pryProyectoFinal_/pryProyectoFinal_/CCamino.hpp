#pragma once
#include <vector>

using namespace System::Collections::Generic;
using namespace System::Drawing;
using namespace std;

ref class CCamino {
private:
	short piso;
	//vector<vector<short>>* mapa;
	List<List<CCelda^>^>^ mapa;
	CCelda^ inicio;
	CCelda^ fin;
	List<CCelda^>^ openset; //celdas que estan siendo analizadas
	List<CCelda^>^ closeset; //celdas recorridas / ya revisadas

public:
	CCamino() :piso(0) {}
	CCamino(short piso, CCelda^ inicio, CCelda^ fin)
		:piso(piso), inicio(inicio), fin(fin) { }

	CCamino(List<List<CCelda^>^>^ mapa, CCelda^ inicio, CCelda^ fin)
		:piso(0), mapa(mapa), inicio(inicio), fin(fin) { }
	CCamino(short piso, short pared, List<List<CCelda^>^>^ mapa, CCelda^ inicio, CCelda^ fin)
		:piso(piso), mapa(mapa), inicio(inicio), fin(fin) { }

	CCamino(vector<vector<short>>* mapa, CCelda^ inicio, CCelda^ fin)
		:piso(0), inicio(inicio), fin(fin) {
		mapa_short_to_CCelda(mapa);
	}
	CCamino(short piso, vector<vector<short>>* mapa, CCelda^ inicio, CCelda^ fin)
		:piso(piso), inicio(inicio), fin(fin) {
		mapa_short_to_CCelda(mapa);
	}

	~CCamino() {
		delete inicio;
		delete fin;

		/*
		for (int i = mapa->size(); i >=0; --i) {
			for (int j = mapa->at(i)->size(); j>=0; --j)
			{
				delete mapa->at(i)->at(j);
				mapa->at(i)->erase(mapa->at(i)->begin() + j);
			}
			delete mapa->at(i);
			mapa->erase(mapa->begin()+i);
		}
		*/
		for each (List<CCelda^>^ fila in mapa)
		{
			for each (CCelda^ celda in fila)
				delete celda;
			delete fila;
		}
		delete mapa;

		for each (CCelda^ celda in openset)
			delete celda;
		delete openset;

		for each (CCelda^ celda in closeset)
			delete celda;
		delete closeset;
	}

	bool existe_camino() {
		//TO DO
	}

	void camino_corto() {//algoritmo a*
		//1ero actual casilla (entrada) dentro de openset (se modificara hasta que sea la de destino)
		openset->Add(inicio);

		//coste total f mas pequeño
		//mover el analizado a closeset
		//ver las casillas de los lados siempre y cuando no esten en closeset ni sea un muro
	}


	//void set_mapa(vector<vector<CCelda^>*>* mapa) { this->mapa = mapa; }
	//vector<vector<CCelda^>*>* get_mapa() { return mapa; }
	void set_mapa(List<List<CCelda^>^>^ mapa) { this->mapa = mapa; }
	List<List<CCelda^>^>^ get_mapa() { return mapa; }

	CCelda^ get_inicio() { return inicio; }
	void set_inicio(CCelda^ inicio) { this->inicio = inicio; }

	CCelda^ get_fin() { return fin; }
	void set_fin(CCelda^ fin) { this->fin = fin; }

private:

	void mapa_short_to_CCelda(vector<vector<short>>* mapaShort){
		for (int i = mapaShort->size(); i >= 0; --i)
		{
			List<CCelda^>^ aux_fila;

			for (int j = mapaShort->at(i).size(); j >= 0; --j)
				aux_fila->Add(gcnew CCelda(i, j, mapaShort->at(i).at(j)));

			this->mapa[i] = aux_fila;
		}
		delete mapa;

		set_vecinos();
	}

	void set_vecinos() {
		/*
		List<CCelda^>^ fila;
		List<CCelda^>^ fila_aux;

		for (short i = this->mapa->Count; i >= 0; --i) //por cada fila
		{
			for (short j = this->mapa[i]->Count; j >= 0; --j) //por cada columna
			{
				fila = mapa[i];
				//vecino izquierdo
				if (fila[j]->get_x() > 0)
				{
					fila[j]->addVecino(fila[j - 1]);
				}
				//vecino derecho
				if (fila[j]->get_x() < (fila->Count - 1) )
				{
					fila[j]->addVecino(fila[j + 1]);
				}

				//vecino arriba
				fila_aux = mapa[i - 1];
				if (fila[j]->get_y() > 0)
				{
					fila[j]->addVecino(fila_aux[j]);
				}
				//vecino abajo
				fila_aux = mapa[i + 1];
				if (fila[j]->get_y() < (mapa->Count - 1) )
				{
					fila[j]->addVecino(fila_aux[j]);
				}
			}
		}*/

		/*delete fila;
		delete fila_aux;*/
	}
};


ref class CCelda {
private:
	short valor;
	short x, y; //posicion en la matriz
	int g, //pasos dados
		h, //pasos que quedan en el caso ideal (sin obstaculos) - heuristica (estimacion de lo que queda)
		f; // coste total / f = g+h
	//vector<CCelda^>* vecinos;
	CCelda^ padre;
public:
	CCelda() { valor = 1; x = 0; y = 0; g = 0; h = 0; f = 0; }
	CCelda(short x, short y) : x(x), y(y) {}
	CCelda(short x, short y, short valor) : x(x), y(y), valor(valor) {}
	~CCelda() {
		/*
		for (short i = vecinos->size(); i >= 0; --i)
		{
			delete vecinos->at(i);
			vecinos->erase(vecinos->begin() + i);
		}
		delete vecinos;*/
		delete padre;
	}

	//void addVecino(CCelda^ vecino) { this->vecinos->push_back(vecino); }

	void set_valor(short valor) { this->valor = valor; }
	short get_valor() { return this->valor; }

	short get_x() { return this->x; }
	void set_x(short x) { this->x = x; }
	short get_y() { return this->y; }
	void set_y(short y) { this->y = y; }

	int get_g() { return this->g; }
	void set_g(int g) { this->g = g; }

	int get_h() { return this->h; }
	void set_h(int h) { this->h = h; }

	int get_f() { return this->f; }
	void update_f() { this->f = g + h; }
};