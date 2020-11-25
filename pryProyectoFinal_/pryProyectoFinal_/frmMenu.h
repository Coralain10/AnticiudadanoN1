#pragma once
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#include <MMSystem.h>
#include "CJuego.hpp"
#include <string>
#include "frm_configuracion.h"
namespace pryProyectoFinal {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Media;
	using namespace std;


	public ref class frmMenu : public System::Windows::Forms::Form
	{
		Graphics^ graficador;
		BufferedGraphics^ buffer;
		BufferedGraphics^ buffer_aux;
		CJuego^ juego;
		short tc; //tamanho de celda
		short ancho, alto; //Client size varia cuando recien inicia a cuando carga

	private: System::Windows::Forms::Timer^ tmrMenu;
	private: System::Windows::Forms::Timer^ tmrChat;
	private: System::Windows::Forms::Timer^ tmrIntroJugar;
	private: System::Windows::Forms::Timer^ tmrIntro;
	private: System::Windows::Forms::Timer^ tmrJuegoP1;
	private: System::Windows::Forms::Timer^ tmrJuegoP2;
	private: System::Windows::Forms::Timer^ tmrfin;
	private: System::Windows::Forms::Timer^ tmrCreditos;

	public:
		SoundPlayer^ intro = gcnew SoundPlayer("Imagenes\\intro.wav ");
		frmMenu(void)
		{
			InitializeComponent();
			srand(time(NULL));
			this->graficador = this->CreateGraphics();
			this->buffer = BufferedGraphicsManager::Current->Allocate(this->graficador, this->ClientRectangle);
			this->buffer_aux = BufferedGraphicsManager::Current->Allocate(this->buffer->Graphics, this->ClientRectangle);
			//this->DoubleBuffered == true;
			Windows::Forms::Cursor::Hide();
		}

	protected:

		~frmMenu()
		{
			delete this->juego;

			if (components)
			{
				delete components;
			}
		}
	private: System::ComponentModel::IContainer^ components;
	protected:


#pragma region Windows Form Designer generated code

		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(frmMenu::typeid));
			this->tmrJuegoP1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->tmrMenu = (gcnew System::Windows::Forms::Timer(this->components));
			this->tmrChat = (gcnew System::Windows::Forms::Timer(this->components));
			this->tmrIntroJugar = (gcnew System::Windows::Forms::Timer(this->components));
			this->tmrIntro = (gcnew System::Windows::Forms::Timer(this->components));
			this->tmrJuegoP2 = (gcnew System::Windows::Forms::Timer(this->components));
			this->tmrfin = (gcnew System::Windows::Forms::Timer(this->components));
			this->tmrCreditos = (gcnew System::Windows::Forms::Timer(this->components));
			this->SuspendLayout();
			// 
			// tmrJuegoP1
			// 
			this->tmrJuegoP1->Tick += gcnew System::EventHandler(this, &frmMenu::animar_juegoP1);
			// 
			// tmrMenu
			// 
			this->tmrMenu->Tick += gcnew System::EventHandler(this, &frmMenu::animar_menu);
			// 
			// tmrChat
			// 
			this->tmrChat->Tick += gcnew System::EventHandler(this, &frmMenu::chat_conspiracion);
			// 
			// tmrIntroJugar
			// 
			this->tmrIntroJugar->Tick += gcnew System::EventHandler(this, &frmMenu::anim_intro_jugar);
			// 
			// tmrIntro
			// 
			this->tmrIntro->Enabled = true;
			this->tmrIntro->Tick += gcnew System::EventHandler(this, &frmMenu::anim_intro);
			// 
			// tmrJuegoP2
			// 
			this->tmrJuegoP2->Tick += gcnew System::EventHandler(this, &frmMenu::animar_juegoP2);
			// 
			// tmrfin
			// 
			this->tmrfin->Tick += gcnew System::EventHandler(this, &frmMenu::mostrar_mensaje);
			// 
			// tmrCreditos
			// 
			this->tmrCreditos->Tick += gcnew System::EventHandler(this, &frmMenu::mostrar_creditos);
			// 
			// frmMenu
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::Black;
			this->ClientSize = System::Drawing::Size(624, 321);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Name = L"frmMenu";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"menu principal";
			this->WindowState = System::Windows::Forms::FormWindowState::Maximized;
			this->Load += gcnew System::EventHandler(this, &frmMenu::inicializar);
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &frmMenu::interactuar);
			this->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &frmMenu::accion_form);
			this->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &frmMenu::actualizar_mouse);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void inicializar(System::Object^ sender, System::EventArgs^ e) {
		//INICIALIZANDO EL JUEGO
		this->tc = 28;
		this->juego = gcnew CJuego(tc, this->ClientRectangle);
	}

	private: System::Void anim_intro(System::Object^ sender, System::EventArgs^ e) {
		if (this->juego->get_intro0()->anim_auto(this->buffer->Graphics))
			this->buffer->Render();

		else {
			this->juego->remove_intro0();
			this->tmrIntro->Enabled = false;
			this->tmrMenu->Enabled = true;
		}
	}

	private: System::Void accion_form(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
		if (this->juego->get_cursor()->hay_colision(this->juego->get_btn_cerrar()))
			Application::Exit();

		if (this->juego->get_menu() != nullptr)
		{
			if (this->juego->get_cursor()->hay_colision(this->juego->get_menu()->get_btn_comenzar())) {
				this->tmrMenu->Enabled = false;
				this->juego->set_introjuego();
				this->tmrIntroJugar->Enabled = true;
			}
			else if (this->juego->get_cursor()->hay_colision(this->juego->get_menu()->get_btn_configurar())) {
				frm_configuracion^ frm = gcnew frm_configuracion();
				frm->ShowDialog();
				
				this->juego->get_cursor()->dibujar(this->buffer->Graphics);
				this->buffer->Render();
				this->juego->get_config()->set_aliados_cant(frm->get_cantaliados());
				this->juego->get_config()->set_vidas(frm->get_cantvidas());
				this->juego->get_config()->set_t_to_s(frm->get_cantTiempo());
			}
		}

		if (this->juego->get_introjuego() != nullptr)
		{
			if (this->juego->get_cursor()->hay_colision(this->juego->get_introjuego()->get_btn_dsiguiente()))
			{
				if (this->juego->get_introjuego()->avanzar(this->buffer->Graphics))
					buffer->Render();
				else {
					this->tmrIntroJugar->Enabled = false;
					this->juego->remove_introjuego();
					this->buffer->Graphics->Clear(System::Drawing::Color::Black);
					intro->Stop();
					this->juego->iniciar_juego();
					this->juego->get_laberinto()->pintar_mapa(this->buffer_aux->Graphics);
					buffer_aux->Render();
					this->juego->mover_aliados();
					this->tmrJuegoP1->Enabled = true;
				}
			}
			else if (this->juego->get_cursor()->hay_colision(this->juego->get_introjuego()->get_btn_danterior()))
			{
				if (this->juego->get_introjuego()->retroceder(this->buffer->Graphics))
					buffer->Render();
				else {
					this->tmrIntroJugar->Enabled = false;
					this->juego->remove_introjuego();
					this->tmrMenu->Enabled = true;
				}
			}
		}
		
		if (this->juego->get_cursor()->hay_colision(this->juego->get_btn_reiniciar()))
		{
			this->tmrJuegoP1->Enabled = false;
			this->tmrJuegoP2->Enabled = false;
			this->tmrfin->Enabled = false;
			this->tmrCreditos->Enabled = false;
			this->juego->reiniciar_lab();
			this->juego->get_laberinto()->pintar_mapa(this->buffer_aux->Graphics);
			buffer_aux->Render();
			this->tmrJuegoP1->Enabled = true;
		}

		if (this->juego->get_cursor()->hay_colision(this->juego->get_btn_creditos()))
		{
			this->juego->set_creditos();
			this->tmrJuegoP1->Enabled = false;
			this->tmrJuegoP2->Enabled = false;
			this->tmrfin->Enabled = false;
			this->tmrCreditos->Enabled = true;
		}

		if (this->juego->get_chat_alianza()!= nullptr)
		{
			if (this->juego->get_cursor()->hay_colision(this->juego->get_chat_alianza()->get_btn_dsiguiente()))
			{
				if (this->juego->get_chat_alianza()->avanzar() == false)
				{
					this->tmrChat->Enabled = false;
					this->juego->remove_chat();
					this->juego->set_splash_conspiracion(this->buffer->Graphics);
					buffer->Render();
					System::Threading::Thread::Sleep(1000);
					this->juego->remove_splash_conspiracion();
					this->juego->get_laberinto()->pintar_mapa(this->buffer_aux->Graphics);
					buffer_aux->Render();
					this->tmrJuegoP2->Enabled = true;
				}
			}
			else if (this->juego->get_cursor()->hay_colision(this->juego->get_chat_alianza()->get_btn_danterior()))
				this->juego->get_chat_alianza()->retroceder();
		}
		
	}

	private: System::Void actualizar_mouse(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
		this->juego->get_cursor()->set_ubicacion(e->X, e->Y);
	}

	private: System::Void animar_menu(System::Object^ sender, System::EventArgs^ e) {
		intro->PlayLooping();
		this->juego->get_menu()->menu_principal(buffer->Graphics);
		this->juego->pintar_ui(this->buffer->Graphics);
		this->buffer->Render();
	}

	private: System::Void anim_intro_jugar(System::Object^ sender, System::EventArgs^ e) {
		this->juego->get_introjuego()->anim(this->buffer->Graphics);
		this->juego->pintar_ui(this->buffer->Graphics);
		buffer->Render();
	}

	private: System::Void interactuar(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
		if (tmrJuegoP1->Enabled || tmrJuegoP2->Enabled)
		{
			switch (e->KeyCode) {
			case Keys::Up: this->juego->interactuar(Arriba); break;
			case Keys::Down: this->juego->interactuar(Abajo); break;
			case Keys::Left: this->juego->interactuar(Izquierda); break;
			case Keys::Right: this->juego->interactuar(Derecha); break;
			}
		}
	}

	private: System::Void animar_juegoP1(System::Object^ sender, System::EventArgs^ e) {
		buffer_aux->Render();
		this->juego->pintar_ui(buffer->Graphics);
		this->juego->jugar(buffer->Graphics);
		this->juego->get_btn_reiniciar()->dibujar(this->buffer->Graphics);
		if (this->juego->get_ha_ganado()) {
			this->juego->set_ganar();
			this->tmrJuegoP2->Enabled = false;
			this->tmrfin->Enabled = true;
		}
		this->buffer->Render();
	
		if (this->juego->get_config()->ts_actual == this->juego->get_config()->ts_alianza)
		{
			this->tmrJuegoP1->Enabled = false;
			this->juego->set_chat();
			this->juego->get_chat_alianza()->chat(this->buffer->Graphics);
			this->tmrChat->Enabled = true;
		}
	}

	private: System::Void chat_conspiracion(System::Object^ sender, System::EventArgs^ e) {
		this->juego->get_chat_alianza()->chat(this->buffer->Graphics);
		this->juego->pintar_ui(this->buffer->Graphics);
		buffer->Render();
	}

	private: System::Void animar_juegoP2(System::Object^ sender, System::EventArgs^ e) {
		if (this->juego->get_config()->ts_actual <= this->juego->get_config()->ts_total)
		{
			this->buffer_aux->Render();
			this->juego->jugar(buffer->Graphics);
			this->juego->pintar_ui(buffer->Graphics);
			this->juego->get_btn_reiniciar()->dibujar(this->buffer->Graphics);
			this->buffer->Render();
			if (this->juego->get_ha_ganado()) {
				this->juego->set_ganar();
				this->tmrJuegoP2->Enabled = false;
				this->tmrfin->Enabled = true;
			}
		}
		else {
			this->juego->set_gameover();
			this->tmrJuegoP2->Enabled = false;
			this->tmrfin->Enabled = true;
		}
	}
	private: System::Void mostrar_mensaje(System::Object^ sender, System::EventArgs^ e) {
		this->buffer->Graphics->Clear(System::Drawing::Color::Black);

		if (this->juego->get_ha_ganado())
			this->juego->get_ganar()->dibujar_dialogo(this->buffer->Graphics);
		else
			this->juego->get_gameover()->dibujar_dialogo(this->buffer->Graphics);

		this->juego->get_btn_reiniciar()->dibujar(this->buffer->Graphics);
		this->juego->dibujar_btn_creditos(this->buffer->Graphics);
		this->juego->pintar_ui(this->buffer->Graphics);
		this->buffer->Render();
	}
	private: System::Void mostrar_creditos(System::Object^ sender, System::EventArgs^ e) {
		//this->juego->get_creditos()->dibujar_fondo(this->buffer->Graphics);
		this->juego->dibujar_creditos(this->buffer->Graphics);
		this->buffer->Render();
	}
};
}

