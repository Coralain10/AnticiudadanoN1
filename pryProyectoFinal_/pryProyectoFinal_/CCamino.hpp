#pragma once
#include <vector>

using namespace System::Collections::Generic;
using namespace std;

ref class CCamino {
private:
	short piso;
	short pared;
	vector<vector<CCelda^>*>* mapa;
	CCelda^ inicio;
	CCelda^ fin;
	List<CCelda^>^ openset; //celdas que estan siendo analizadas
	List<CCelda^>^ closeset; //celdas recorridas / ya revisadas

public:
	CCamino() :piso(0), pared(1) {}
	CCamino(short piso, short pared, CCelda^ inicio, CCelda^ fin)
		:piso(piso), pared(pared), inicio(inicio), fin(fin) { }

	CCamino(vector<vector<CCelda^>*>* mapa, CCelda^ inicio, CCelda^ fin)
		:piso(0), pared(1), mapa(mapa), inicio(inicio), fin(fin) { }
	CCamino(short piso, short pared, vector<vector<CCelda^>*>* mapa, CCelda^ inicio, CCelda^ fin)
		:piso(piso), pared(pared), mapa(mapa), inicio(inicio), fin(fin) { }

	CCamino(vector<vector<short>>* mapa, CCelda^ inicio, CCelda^ fin)
		:piso(0), pared(1), inicio(inicio), fin(fin) {
		mapa_short_to_CCelda(mapa);
	}
	CCamino(short piso, short pared, vector<vector<short>>* mapa, CCelda^ inicio, CCelda^ fin)
		:piso(piso), pared(pared), inicio(inicio), fin(fin) {
		mapa_short_to_CCelda(mapa);
	}

	~CCamino() {
		delete inicio;
		delete fin;

		for (int i = mapa->size(); i >=0; --i) {
			for (int j = mapa->at(i)->size(); j>=0; --j)
			{
				delete mapa->at(i)->at(j);
				mapa->at(i)->erase(mapa->at(i)->begin() + j);
			}
			delete mapa->at(i);
			mapa->erase(mapa->begin()+i);
		}
		delete mapa;

		for (int i = openset->Count; i >= 0; --i)
		{
			delete openset[i];
			openset->RemoveAt(i);
		}
		delete openset;

		for (int i = closeset->Count; i >= 0; --i)
		{
			delete closeset[i];
			openset->RemoveAt(i);
		}
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


	void set_mapa(vector<vector<CCelda^>*>* mapa) { this->mapa = mapa; }
	vector<vector<CCelda^>*>* get_mapa() { return mapa; }

	CCelda^ get_inicio() { return inicio; }
	void set_inicio(CCelda^ inicio) { this->inicio = inicio; }

	CCelda^ get_fin() { return fin; }
	void set_fin(CCelda^ fin) { this->fin = fin; }

private:
	void mapa_short_to_CCelda(vector<vector<short>>* mapa){
		for (int i = mapa->size(); i >= 0; --i)
		{
			vector<CCelda^>* aux_fila;

			for (int j = mapa->at(i).size(); j >= 0; --j)
				aux_fila->push_back(gcnew CCelda(i, j, mapa->at(i).at(j)));

			this->mapa->at(i) = aux_fila;
		}
		delete mapa;

		set_vecinos();
	}

	void set_vecinos() {
		for (int i = this->mapa->size(); i >= 0; --i) //por cada fila
		{
			for (int j = this->mapa->at(i)->size(); j >= 0; --j) //por cada columna
			{
				//vecino izquierdo
				if (this->mapa->at(i)->at(j)->get_x() > 0)
				{
					this->mapa->at(i)->at(j)->addVecino(mapa->at(i)->at(j - 1));
				}
				//vecino derecho
				if (this->mapa->at(i)->at(j)->get_x() < (mapa->at(i)->size()-1) )
				{
					this->mapa->at(i)->at(j)->addVecino(mapa->at(i)->at(j + 1));
				}
				//vecino arriba
				if (this->mapa->at(i)->at(j)->get_y() > 0)
				{
					this->mapa->at(i)->at(j)->addVecino(mapa->at(i - 1)->at(j));
				}
				if (this->mapa->at(i)->at(j)->get_y() < (mapa->size() - 1) ) //vecino abajo
				{
					this->mapa->at(i)->at(j)->addVecino(mapa->at(i + 1)->at(j));
				}
			}
		}
	}
};

ref class CCelda {
private:
	short valor;
	short x, y; //posicion en la matriz
	int g, //pasos dados
		h, //pasos que quedan en el caso ideal (sin obstaculos) - heuristica (estimacion de lo que queda)
		f; // coste total / f = g+h
	vector<CCelda^>* vecinos;
	CCelda^ padre;
public:
	CCelda() {}
	CCelda(short x, short y) : x(x), y(y) {}
	CCelda(short x, short y, short valor) : x(x), y(y), valor(valor) {}
	~CCelda() {
		for (short i = vecinos->size(); i >= 0; --i)
		{
			delete vecinos->at(i);
			vecinos->erase(vecinos->begin() + i);
		}
		delete vecinos;
		delete padre;
	}

	void addVecino(CCelda^ vecino) { this->vecinos->push_back(vecino); }

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