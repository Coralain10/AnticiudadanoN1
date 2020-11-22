#pragma once
#include "CGrafico.hpp"

using namespace System::Collections::Generic;


ref class CChat {
private:
	CGrafico^ usu1;
	CGrafico^ usu2;
	List<String^>^ chat_usu1;
	List<String^>^ chat_usu2;
	Font^ fmensaje;
	Font^ fusuario;
	Bitmap^ img_flechasAA;
	CGrafico^ fondo;
	CGrafico^ btn_dialogo_sgt;
	CGrafico^ btn_dialogo_ant;
	Rectangle area;
	short pos_chat_act, pos_chat_usu1, pos_chat_usu2;
public:
	CChat(CGrafico^ usu1, CGrafico^ usu2, List<String^>^ chat_usu1, List<String^>^ chat_usu2, Rectangle area, short tamanho_celda) :
		usu1(usu1), usu2(usu2), chat_usu1(chat_usu1), chat_usu2(chat_usu2) {
		pos_chat_act = pos_chat_usu1 = pos_chat_usu2 = 0;
		this->fmensaje = gcnew System::Drawing::Font("Courier new", 16);
		this->fusuario = gcnew System::Drawing::Font("Courier new", 20);
		this->img_flechasAA = gcnew Bitmap("Imagenes\\flechasAA.png");
		this->btn_dialogo_ant = gcnew CGrafico(img_flechasAA, Rectangle(0, 0, 32, 32), area.Width - 2 * tamanho_celda, tamanho_celda * 6, tamanho_celda, tamanho_celda);
		this->btn_dialogo_sgt = gcnew CGrafico(img_flechasAA, Rectangle(0, 32, 32, 32), area.Width - 2 * tamanho_celda, tamanho_celda * 8, tamanho_celda, tamanho_celda);
		this->fondo = gcnew CGrafico("Imagenes\\dialog.png",this->area.Width, this->area.Height/3);
	}
	~CChat() {
		for each (String ^ chat in chat_usu1)
			delete chat;
		delete chat_usu1;
		for each (String ^ chat in chat_usu2)
			delete chat;
		delete chat_usu2;
		delete usu1;
		delete usu2;
		delete fmensaje;
		delete fusuario;
		delete fondo;
	}
	bool avanzar(Graphics^ graficador) {
		this->pos_chat_act++;
		if (this->pos_chat_act < (this->chat_usu1->Count + this->chat_usu2->Count))
			anim_contr(graficador);
		else
			return false;
	}
	bool retroceder(Graphics^ graficador) {
		this->pos_chat_act--;
		if (this->pos_chat_act >= 0)
			anim_contr(graficador);
		else
			return false;
	}
	void set_pos_dialog_act(short pos_chat) { this->pos_chat_act = pos_chat; }
	short get_pos_dialog_act() { return this->pos_chat_act; }

private:
	void anim(Graphics^ graficador) {
		this->fondo->dibujar(graficador);

		if (pos_chat_act % 2 == 0) { //corresponde al user1
			usu1->set_ubicacion(20, (40 * pos_chat_usu1) + 20);
			usu1->dibujar(graficador);
			graficador->DrawString(chat_usu1[pos_chat_usu1], fmensaje, Brushes::White, 80, (40 * pos_chat_usu1) + 20);
			pos_chat_usu1++;
		}
		else {//corresponde al user2
			usu2->set_ubicacion(area.Width - 20 - usu2->get_ancho(), (40 * pos_chat_usu2) + 20);
			usu2->dibujar(graficador);
			graficador->DrawString(chat_usu2[pos_chat_usu2], fmensaje, Brushes::White, area.Width - 80 - usu2->get_ancho(), (40 * pos_chat_usu2) + 20);
			pos_chat_usu2++;
		}

		btn_dialogo_ant->dibujar(graficador);
		btn_dialogo_sgt->dibujar(graficador);
	}
	void anim_contr(Graphics^ graficador) {
		anim(graficador);
		this->btn_dialogo_ant->dibujar(graficador);
		this->btn_dialogo_sgt->dibujar(graficador);
	}
};

ref class CDialogo {
private:
	String^ titulo;
	Rectangle area;
	CGrafico^ grafico_central;
	String^ dialogo;
	Font^ tipografia;
public:
	CDialogo(String^ titulo, String^ dialogo, CGrafico^ grafico_central, Rectangle area) :
		titulo(titulo), tipografia(tipografia), dialogo(dialogo), grafico_central(grafico_central), area(area) {
		this->tipografia = gcnew System::Drawing::Font("Courier new", 20);
		this->grafico_central->set_ubicacion(this->area.Width / 2 - this->grafico_central->get_ancho() / 2, this->area.Height - this->grafico_central->get_alto());
	}
	CDialogo(String^ titulo, String^ dialogo, Rectangle area) :
		titulo(titulo), tipografia(tipografia), dialogo(dialogo), area(area) {
		this->tipografia = gcnew System::Drawing::Font("Courier new", 20);
	}
	CDialogo(String^ dialogo, Rectangle area) :
		tipografia(tipografia), dialogo(dialogo), area(area) {
		this->tipografia = gcnew System::Drawing::Font("Courier new", 20);
	}

	~CDialogo() {
		if (titulo!= nullptr)
			delete titulo;
		if (grafico_central != nullptr)
			delete grafico_central;
		delete dialogo;
		delete tipografia;
	}

	void dibujar_fondo(Graphics^ graficador) {
		graficador->Clear(System::Drawing::Color::Black);
		if (this->grafico_central != nullptr)
			this->grafico_central->dibujar(graficador);
	}
	void dibujar_dialogo(Graphics^ graficador) {
		graficador->DrawString(dialogo, this->tipografia, Brushes::White, 50, 50);
	}
};

ref class CDialogos {
private:
	Rectangle area;
	Bitmap^ img_flechasAA;
	CGrafico^ btn_dialogo_sgt;
	CGrafico^ btn_dialogo_ant;
	List<CDialogo^>^ dialogos;
	CGrafico^ grafico_central;
	bool es_seguido;
	short pos_dialogo_act;
public:
	CDialogos(List<CDialogo^>^ dialogos, CGrafico^ grafico_central, Rectangle area, short tamanho_celda) :
		es_seguido(false), dialogos(dialogos), grafico_central(grafico_central), area(area) {
		this->img_flechasAA = gcnew Bitmap("Imagenes\\flechasAA.png");
		this->btn_dialogo_ant = gcnew CGrafico(img_flechasAA, Rectangle(0, 0, 32, 32), area.Width - 2 * tamanho_celda, tamanho_celda * 6, tamanho_celda, tamanho_celda);
		this->btn_dialogo_sgt = gcnew CGrafico(img_flechasAA, Rectangle(0, 32, 32, 32), area.Width - 2 * tamanho_celda, tamanho_celda * 8, tamanho_celda, tamanho_celda);
		this->grafico_central->set_ubicacion(this->area.Width / 2 - this->grafico_central->get_ancho() / 2, this->area.Height - this->grafico_central->get_alto());
		this->pos_dialogo_act = 0;
	}
	CDialogos(List<CDialogo^>^ dialogos, Rectangle area) : es_seguido(true), dialogos(dialogos), area(area) { }

	~CDialogos() {
		delete img_flechasAA;
		delete btn_dialogo_sgt;
		delete btn_dialogo_ant;
		delete grafico_central;
	}

	CGrafico^ get_btn_dsiguiente() { return this->btn_dialogo_sgt; }
	CGrafico^ get_btn_danterior() { return this->btn_dialogo_ant; }

	void set_grafico_central(CGrafico^ grafico_central) {
		this->grafico_central = grafico_central;
	}

	bool avanzar(Graphics^ graficador) {
		this->pos_dialogo_act++;
		if (this->pos_dialogo_act < dialogos->Count)
		{
			anim_contr(graficador);
			return true;
		}
		else
			return false;
	}
	bool retroceder(Graphics^ graficador) {
		this->pos_dialogo_act--;
		if (this->pos_dialogo_act >= 0)
		{
			anim_contr(graficador);
			return true;
		}
		else
			return false;
	}

	bool anim_auto(Graphics^ graficador) {
		anim(graficador);
		pos_dialogo_act++;

		if (this->pos_dialogo_act < dialogos->Count)
			return true;
		else
			return false;
	}

	void anim(Graphics^ graficador) {
		dialogos[pos_dialogo_act]->dibujar_fondo(graficador);
		if (this->grafico_central != nullptr)
			grafico_central->dibujar(graficador);
		dialogos[pos_dialogo_act]->dibujar_dialogo(graficador);

		if (es_seguido == false) {
			btn_dialogo_ant->dibujar(graficador);
			btn_dialogo_sgt->dibujar(graficador);
		}
	}

	void set_pos_dialog_act(short pos_dialog) { this->pos_dialogo_act = pos_dialog; }
	short get_pos_dialog_act() { return this->pos_dialogo_act; }

private:
	void anim_contr(Graphics^ graficador) {
		anim(graficador);
		this->btn_dialogo_ant->dibujar(graficador);
		this->btn_dialogo_sgt->dibujar(graficador);
	}
};