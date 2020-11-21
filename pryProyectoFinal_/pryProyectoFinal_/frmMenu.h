#pragma once
#include <stdlib.h>
#include <time.h>
#include "CJuego.hpp"
#include <string>

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

	private:


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
			// tmrIntroJugar
			// 
			this->tmrIntroJugar->Tick += gcnew System::EventHandler(this, &frmMenu::anim_intro_jugar);
			// 
			// tmrIntro
			// 
			this->tmrIntro->Enabled = true;
			this->tmrIntro->Interval = 2000;
			this->tmrIntro->Tick += gcnew System::EventHandler(this, &frmMenu::anim_intro);
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
			this->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &frmMenu::frmMenu_Paint);
			this->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &frmMenu::accion_form);
			this->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &frmMenu::actualizar_mouse);
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &frmMenu::interactuar);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void inicializar(System::Object^ sender, System::EventArgs^ e) {
		//INICIALIZANDO EL JUEGO
		this->tc = 28;
		this->juego = gcnew CJuego(tc, this->ClientRectangle);
	}
	private: System::Void frmMenu_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
		//this->juego->pintar_ui(graficador);
	}
	private: System::Void anim_intro(System::Object^ sender, System::EventArgs^ e) {
		
		if (this->juego->get_pos_dialog_act() <= 3) {
			this->juego->intro(this->buffer->Graphics);
			this->buffer->Render();
		}
		else {
			this->tmrIntro->Enabled = false;
			this->tmrMenu->Enabled = true;
		}
		
	}

	private: System::Void accion_form(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
		if (this->juego->get_cursor()->hay_colision(this->juego->get_btn_cerrar()))
			Application::Exit();

		if (this->juego->get_cursor()->hay_colision(this->juego->get_btn_comenzar()))
		{
			//this->juego->iniciar_juego(buffer->Graphics);
			this->tmrMenu->Enabled = false;
			this->juego->iniciar_entrada_juego(buffer->Graphics);
			buffer->Render();
			this->tmrIntroJugar->Enabled = true;
		}

		if (this->juego->get_cursor()->hay_colision(this->juego->get_btn_dsiguiente()))
		{
			this->juego->set_pos_dialog_act(this->juego->get_pos_dialog_act() + 1);
			if (this->juego->anim_entrada_juego(buffer->Graphics) == false)
			{
				this->juego->get_laberinto()->pintar_mapa(this->buffer_aux->Graphics);
					buffer_aux->Render();
					
					this->tmrIntroJugar->Enabled = false;
					this->tmrJuegoP1->Enabled = true;
			}
		}

		if (this->juego->get_cursor()->hay_colision(this->juego->get_btn_danterior()))
		{
			this->juego->set_pos_dialog_act(this->juego->get_pos_dialog_act() - 1);
			if (this->juego->anim_entrada_juego(buffer->Graphics)==false)
			{
				this->tmrMenu->Enabled = true;
				this->tmrIntroJugar->Enabled = false;
			}
		}

		if (this->juego->get_cursor()->hay_colision(this->juego->get_btn_reiniciar()))
		{
			//this->juego->iniciar_juego();
			this->tmrJuegoP1->Enabled = false;
			this->juego->reiniciar_lab();
			this->juego->get_laberinto()->pintar_mapa(this->buffer_aux->Graphics);
			buffer_aux->Render();
			this->tmrJuegoP1->Enabled = true;
		}
	}

	private: System::Void actualizar_mouse(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
		this->juego->get_cursor()->set_ubicacion(e->X, e->Y);
	}

	private: System::Void animar_menu(System::Object^ sender, System::EventArgs^ e) {
		intro->PlayLooping();
		this->juego->menu_principal(buffer->Graphics);
		this->buffer->Render();
	}

	private: System::Void anim_intro_jugar(System::Object^ sender, System::EventArgs^ e) {
		this->juego->anim_entrada_juego(buffer->Graphics);
		this->juego->get_cursor()->dibujar(buffer->Graphics);
		buffer->Render();
	}
	private: System::Void animar_juegoP1(System::Object^ sender, System::EventArgs^ e) {
		intro->Stop();
		buffer_aux->Render();
		this->juego->pintar_ui(buffer->Graphics);
		this->juego->jugar(buffer->Graphics);
		this->buffer->Render();
	}
	 private: System::Void interactuar(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
			   switch (e->KeyCode) {
			   case Keys::Up: this->juego->interactuar(Arriba); break;
			   case Keys::Down: this->juego->interactuar(Abajo); break;
			   case Keys::Left: this->juego->interactuar(Izquierda); break;
			   case Keys::Right: this->juego->interactuar(Derecha); break;
			   }
		   }

};
}
