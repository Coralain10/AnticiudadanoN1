#pragma once
#include "CGrafico.hpp"
#include "CLaberinto.hpp"
#include "CEntidad.hpp"
#include "CProtagonista.hpp"
#include "CNPC.hpp"

using namespace System::Collections::Generic;

ref class CConfiguracion {
public:
	unsigned int tiempo_s_total;
	short aliados_cant, asesinos_cant, corruptos_cant;
	short aliados_rvision, asesinos_rvision, corruptos_rvision;
	int t_aliados_seguir, t_asesinos_ataque, t_corruptos_corrupcion;

	CConfiguracion() {
		//cargando valores por default
		this->tiempo_s_total = 6000;
		this->aliados_cant = 10;
		this->asesinos_cant = (short)(aliados_cant * 0.6);
		this->corruptos_cant = (short)(aliados_cant * 0.4);
		this->aliados_rvision = this->asesinos_rvision = this->corruptos_rvision = 2;
		this->t_aliados_seguir = t_asesinos_ataque = t_corruptos_corrupcion;
	}
	~CConfiguracion() {}
};


ref class CJuego {
private:
	CLaberinto^ laberinto;
	CConfiguracion^ config;
	Bitmap^ fondo_inicio;
	Bitmap^ bg_botones;
	Bitmap^ img_aux;
	List<CAliado^>^ aliados;
	List<CCorrupto^>^ corruptos;
	List<CAsesino^>^ asesinos;
	CGrafico^ ui_personaje;
	CGrafico^ btn_cerrar;
	CGrafico^ btn_comenzar;
	CGrafico^ btn_configurar;
	CGrafico^ cursor;
	bool inicio_juego;

public:
	CJuego(short ancho, short alto, short tamanho_celda) {
		this->inicio_juego = false;
		this->laberinto = gcnew CLaberinto(ancho, alto, tamanho_celda);
		this->config = gcnew CConfiguracion();
		this->bg_botones = gcnew Bitmap("Imagenes\\buttons.png");
		this->fondo_inicio = gcnew Bitmap("Imagenes\\fondoUI.png");
		this->img_aux = gcnew Bitmap("Imagenes\\zion_letrero.png");
		this->ui_personaje = gcnew CGrafico("Imagenes\\protaUI.png", ancho * tamanho_celda, 0, 1392, 1080);
		this->btn_cerrar = gcnew CGrafico("Imagenes\\cerrar.png", (ancho-4)*tamanho_celda, tamanho_celda, 32, 32);
		this->btn_comenzar = gcnew CGrafico(bg_botones, Rectangle(0, 0, 160, 160), tamanho_celda *2, (alto-8)*tamanho_celda, tamanho_celda*4, tamanho_celda);
		this->btn_configurar = gcnew CGrafico(bg_botones, Rectangle(0, 160, 160, 160), tamanho_celda * 2, (alto - 4) * tamanho_celda, tamanho_celda*4, tamanho_celda);
		this->cursor = gcnew CGrafico("Imagenes\\mouse.png", 32, 32);
		this->aliados = gcnew List<CAliado^>();
		this->corruptos = gcnew List<CCorrupto^>();
		this->asesinos = gcnew List<CAsesino^>();
	}
	~CJuego() {
		delete fondo_inicio;
		delete ui_personaje;
		delete bg_botones;
		delete btn_cerrar;
		delete btn_comenzar;
		delete btn_configurar;
		delete img_aux;
		delete cursor;
		delete laberinto;
		delete config;
		for each (CAliado^ aliado in aliados)
			delete aliados;
		delete aliados;
		for each (CCorrupto ^ corrupto in corruptos)
			delete corrupto;
		delete corruptos;
		for each (CAsesino ^ asesino in asesinos)
			delete asesino;
		delete asesinos;
	}

	void menu_principal(Graphics^ graficador, Rectangle tamanho_pantalla) {
		graficador->DrawImage(fondo_inicio, tamanho_pantalla);
		this->btn_cerrar->dibujar(graficador);
		this->btn_comenzar->dibujar(graficador);
		this->btn_configurar->dibujar(graficador);
		bool parpadear = rand() % 2;
		if (parpadear == 1)//hacer parpadear ZION
			graficador->DrawImage(img_aux, tamanho_pantalla.Width / 2 - 52, tamanho_pantalla.Height - 320); 
		this->ui_personaje->set_x(ui_personaje->get_x() - 20);
		this->cursor->dibujar(graficador);
	}

	void pintar_ui(Graphics^ graficador) {
		this->btn_cerrar->dibujar(graficador);
		this->cursor->dibujar(graficador);
	}

	void iniciar_juego(Graphics^ graficador) {
		this->inicio_juego = true;
		for (short i = 0; i < this->config->aliados_cant; i++)
		{
			// crear aliados
		}
		for (short i = 0; i < this->config->asesinos_cant; i++)
		{
			// crear aliados
		}
		for (short i = 0; i < this->config->asesinos_cant; i++)
		{
			// crear corruptos
		}
	}

	void jugar() {
		// movimiento de los aliados, asesinos y corruptos
	}

	void chat() {
		//chat entre los corruptos y asesinos
	}

	void convencer_asesinos() {
		//TO DO
	}

	void mover_personaje(bool accion, System::Windows::Forms::Keys key){
		//TO DO
	}

	CLaberinto^ get_laberinto() { return this->laberinto; }
	CGrafico^ get_btn_cerrar() { return this->btn_cerrar; }
	CGrafico^ get_btn_comenzar() { return this->btn_cerrar; }
	CGrafico^ get_btn_configurar() { return this->btn_cerrar; }
	CGrafico^ get_cursor() { return this->cursor; }
};

