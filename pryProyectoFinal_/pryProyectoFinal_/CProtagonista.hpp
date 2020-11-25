#pragma once
#include "CEntidad.hpp"

ref class CProtagonista : public CEntidad
{
private:
	short cant_vidas;
	short cant_balas;
	List<CEntidad^>^ balas_disparadas;
public:
	CProtagonista( System::Drawing::Rectangle area, System::Drawing::Rectangle recorte, short n_f, short n_c,short lado)
		: CEntidad("Imagenes\\Protagonista.png",area, recorte, n_f, n_c, direccion,"PROTAGONISTA",lado) {
		this->recorte.Width = this->imagen->Width / this->an_columnas;
		this->recorte.Height = this->imagen->Height / this->an_filas;
		dx = dy = 2;
		this->cant_vidas;
		balas_disparadas = gcnew List<CEntidad^>();
	}
	~CProtagonista() {}

	void to_caminar() { this->dx = this->dy = 5; }
	void to_correr() { this->dx = this->dy = 8; }

	bool gano(short dire, CLaberinto^ escenario) {
		if (mover(dire, escenario) == SALIDA)
			return true;
		else
			return false;
	}

	List<CEntidad^>^ get_balas_disparadas() { return this->balas_disparadas; }
	void recoger_municiones() {
		short aux= (rand() % 3 + 2);
		this->cant_balas +=aux;
	}
	void iniciar_disparo(short tamanho_celda) {
		this->balas_disparadas->Add(gcnew CEntidad("Imagenes\\bala.png", System::Drawing::Rectangle(this->x, this->y, tamanho_celda, tamanho_celda), System::Drawing::Rectangle(0, 0, 0, 0), 4, 1, direccion, "BALA", tamanho_celda));
	}
	void eliminar_bala(short pos_bala) {
		this->balas_disparadas->RemoveAt(pos_bala);
	}
	short get_municion() {
		return this->cant_balas;
	}
	void mostrar_disparo(Graphics^g,CLaberinto^laberinto) {
		if (balas_disparadas->Count > 0) {
			for (short i = balas_disparadas->Count - 1; i >= 0; i--) {
				this->balas_disparadas[i]->dibujar(g);
				if(balas_disparadas[i]->mover(this->balas_disparadas[i]->get_dire(), laberinto)==PAREDMOV){
					this->balas_disparadas->RemoveAt(i);
				}
			}
		}		
	}
	void MostrarMunicion(Graphics^g) {
		g->DrawString("Municion Disponible: " + this->cant_balas, gcnew Font("Courier new", 20), Brushes::Yellow,250, 0);
	}
	void MostrarVidas(int cantV,Graphics^ g) {
		this->cant_vidas = cantV;
		g->DrawString("Vidas: " + cantV, gcnew Font("Courier new", 20), Brushes::LightYellow, 0, 0);
	}
	void set_cant_vidas(short value) { this->cant_vidas += value; }
	short get_cant_vidas() { return cant_vidas; }
	void set_balas(short cant_balas) { this->cant_balas = cant_balas; }
	short get_cant_balas() { return cant_balas; }
};

