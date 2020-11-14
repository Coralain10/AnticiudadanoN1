#pragma once
#include "CLaberinto.hpp"
#include "CEntidad.hpp"
#include "CProtagonista.hpp"
#include "CNPC.hpp"

using namespace System::Collections::Generic;

ref class CJuego {
private:
	int tiempo_s_total;
	CLaberinto^ laberinto;
	short cant_aliados;
	List<CAliado^>^ aliados;
	List<CCorrupto^>^ corruptos;
	List<CAsesino^>^ asesinos;

public:
	CJuego(short ancho, short alto, short tamanho_celda, short cant_aliados) :cant_aliados(cant_aliados) {
		laberinto = gcnew CLaberinto(ancho, alto, tamanho_celda);
		/*for (int i = 0; i < cant_aliados; i++)
			aliados->Add(gcnew CAliado());*/
	}
	~CJuego() {
		delete laberinto;
		/*for (short i = 0; i < aliados->Count; i++)
			delete aliados[i];
		delete aliados;
		for (short i = 0; i < corruptos->Count; i++)
			delete corruptos[i];
		delete aliados;*/
	}

	void convencer_asesinos() {
		//TO DO
	}

	void mover_personaje(bool accion, System::Windows::Forms::Keys key){
		//TO DO
	}

	CLaberinto^ get_laberinto() { return this->laberinto; }
};


ref class CConfiguracion {
private:
	short c_aliados_cant, c_asesinos_cant, c_corruptos_cant;
	short c_aliados_rvision, c_asesinos_rvision, c_corruptos_rvision;
	int c_aliados_tseguir, c_asesinos_tataque, c_corruptos_tcorrupcion;
public:
	//CConfiguracion() {}
	~CConfiguracion() {}

	void actualizar_aliados(short cantidad, short radio_vision, short tiempo_seguir){
		this->c_aliados_cant = cantidad;
		this->c_aliados_rvision = radio_vision;
		this->c_aliados_tseguir = tiempo_seguir;
	}
	void actualizar_asesinos(short radio_vision, short tiempo_seguir) {
		this->c_asesinos_cant = (short)(c_aliados_cant*0.6); //era 60% verdad?
		this->c_asesinos_rvision = radio_vision;
		this->c_asesinos_tataque = tiempo_seguir;
	}
	void actualizar_corruptos(short radio_vision, short tiempo_seguir) {
		this->c_corruptos_cant = (short)(c_aliados_cant * 0.4); //era 40% verdad?
		this->c_corruptos_rvision = radio_vision;
		this->c_corruptos_tcorrupcion = tiempo_seguir;
	}
	/*
	void iniciar_juego() {
		//TO DO
	}*/
};