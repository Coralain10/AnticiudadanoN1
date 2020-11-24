#pragma once
#pragma once
#include <vector>

using namespace System::Collections::Generic;
using namespace System::Drawing;
using namespace std;

ref class CCelda {
private:
	short valor;
	short x, y; //posicion en la matriz
	int g, //pasos dados
		h, //pasos que quedan en el caso ideal (sin obstaculos) - heuristica (estimacion de lo que queda)
		f; // coste total / f = g+h
	List<CCelda^>^ vecinos;
	CCelda^ padre;
public:
	CCelda() { valor = 0; x = 0; y = 0; g = 0; h = 0; f = 0; }
	//CCelda(short x, short y) : x(x), y(y), padre(nullptr) {}
	CCelda(short x, short y, short valor) : x(x), y(y), valor(valor), padre(nullptr) {}
	~CCelda() {
		for each (CCelda ^ vecino in vecinos)
			delete vecino;
		delete vecinos;
		delete padre;
	}

	void addVecino(CCelda^ vecino) { this->vecinos->Add(vecino); }

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

	CCelda^ get_padre() { return this->padre; }
	void set_padre(CCelda^ padre) { this->padre = padre; }

	List<CCelda^>^ get_vecinos() { return this->vecinos; }
	//void set_vecinos(List<CCelda^>^ vecinos) { this->vecinos = vecinos; }
};

ref class CCamino {
private:
	short piso;
	List<List<CCelda^>^>^ mapa;
	CCelda^ inicio;
	CCelda^ fin;
	short hx, hy; //
	List<CCelda^>^ openset; //celdas que estan siendo analizadas
	List<CCelda^>^ closeset; //celdas recorridas / ya revisadas
	List<CCelda^>^ camino;
	bool terminado;

public:
	/*CCamino(short piso, System::Drawing::Point pos_inicio, System::Drawing::Point pos_fin)
		:piso(piso), inicio(pos_to_celda(pos_inicio.X,pos_inicio.Y,piso)), fin(pos_to_celda(pos_fin.X, pos_fin.Y, piso)),
		hx(abs(pos_fin.X-pos_inicio.X)), hy(abs(pos_fin.Y - pos_inicio.Y)), terminado(false) {}*/
	CCamino(short** mapa, System::Drawing::Point pos_inicio, System::Drawing::Point pos_fin)
		:piso(0), inicio(pos_to_celda(pos_inicio.X, pos_inicio.Y, piso)), fin(pos_to_celda(pos_fin.X, pos_fin.Y, piso)),
		hx(abs(pos_fin.X - pos_inicio.X)), hy(abs(pos_fin.Y - pos_inicio.Y)), terminado(false) {
		mapa_short_to_CCelda(mapa);
	}
	CCamino(short piso, short** mapa, System::Drawing::Point pos_inicio, System::Drawing::Point pos_fin)
		:piso(piso), inicio(pos_to_celda(pos_inicio.X, pos_inicio.Y, piso)), fin(pos_to_celda(pos_fin.X, pos_fin.Y, piso)),
		hx(abs(pos_fin.X - pos_inicio.X)), hy(abs(pos_fin.Y - pos_inicio.Y)) {
		mapa_short_to_CCelda(mapa);
	}

	~CCamino() {
		delete inicio;
		delete fin;
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

		for each (CCelda ^ celda in camino)
			delete celda;
		delete closeset;
	}

	void camino_corto() {//algoritmo a*
		//1ero actual casilla (entrada) dentro de openset (se modificara hasta que sea la de destino)
		openset->Add(inicio);

		calcular_camino();
		
	}


	void set_mapa(List<List<CCelda^>^>^ mapa) { this->mapa = mapa; }
	List<List<CCelda^>^>^ get_mapa() { return mapa; }

	CCelda^ get_inicio() { return inicio; }
	void set_inicio(CCelda^ inicio) { this->inicio = inicio; }

	CCelda^ get_fin() { return fin; }
	void set_fin(CCelda^ fin) { this->fin = fin; }

private:
	CCelda^ pos_to_celda(short x, short y, short valor){
		CCelda^ celda = gcnew CCelda(x, y, valor);
		return celda;
	}

	void mapa_short_to_CCelda(short** map){
		for (int i = hx; i >= 0; --i)
		{
			List<CCelda^>^ aux_fila;

			for (int j = hy; j >= 0; --j)
				aux_fila->Add(gcnew CCelda(j, i, map[i][j]));

			this->mapa[i] = aux_fila;
			delete map[i];
		}
		delete map;

		set_vecinos();
	}

	void set_vecinos() {
		List<CCelda^>^ fila;
		List<CCelda^>^ fila_aux;

		for (short i = this->mapa->Count; i >= 0; --i) //por cada fila
		{
			fila = mapa[i];
			for (short j = this->mapa[i]->Count; j >= 0; --j) //por cada columna
			{
				//vecino izquierdo
				if (fila[j]->get_x() > 0)
					fila[j]->addVecino(fila[j - 1]);
				//vecino derecho
				if (fila[j]->get_x() < (fila->Count - 1) )
					fila[j]->addVecino(fila[j + 1]);
				//vecino arriba
				fila_aux = mapa[i - 1];
				if (fila[j]->get_y() > 0)
					fila[j]->addVecino(fila_aux[j]);
				//vecino abajo
				fila_aux = mapa[i + 1];
				if (fila[j]->get_y() < (mapa->Count - 1) )
					fila[j]->addVecino(fila_aux[j]);
			}
			mapa[i] = fila;
		}

		//delete fila;
		//delete fila_aux;
	}

	void calcular_camino() {
		if (terminado == false)
		{
			if (openset->Count>0)
			{
				short pos_ganador = 0;
				for (short i = 0; i < openset->Count; i++)
					if (openset[i]->get_f() < openset[pos_ganador]->get_f())
						pos_ganador = i;//coste total f mas pequeño

				CCelda^ actual = openset[pos_ganador];
				if (actual == fin)
				{
					CCelda^ temp = actual;
					camino->Add(temp);
					while (temp->get_padre() != nullptr) {
						temp = temp->get_padre();
						camino->Add(temp);
					}
					terminado = true;
				}

				else {
					openset->Remove(actual);
					//mover el analizado a closeset
					closeset->Add(actual);
					
					List<CCelda^>^ vecinos_ = actual->get_vecinos();

					for (short i = 0; i < vecinos_->Count; i++) {
						CCelda^ vecino_ = vecinos_[i];

						if (!closeset->Contains(vecino_) && vecino_->get_valor() == piso)
						{
							//ver las casillas de los lados siempre y cuando no esten en closeset ni sea un muro
							short g_temp = actual->get_g() + 1; //Valor de g es g+1

							if (openset->Contains(vecino_)) {
								if (g_temp < vecino_->get_g())
									vecino_->set_g(g_temp);
							}
							else {
								vecino_->set_g(g_temp);
								openset->Add(vecino_);
							}
							vecino_->set_h(heuristica(vecino_->get_x(), vecino_->get_y(), fin->get_x(), fin->get_y()));
							vecino_->update_f();
							vecino_->set_padre(actual);
						}
					}
				}
			} else {
				//no se encontro camino
			}
		}
	}
	short heuristica(short ax, short ay, short bx, short by) {
		short x = abs(ax - bx);
		short y = abs(ay - by);
		short dist = x + y;

		return dist;
	}
};
