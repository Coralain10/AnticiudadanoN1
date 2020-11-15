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
	using namespace std;


	public ref class frmMenu : public System::Windows::Forms::Form
	{
		Graphics^ graficador;
		BufferedGraphics^ buffer;
		CJuego^ juego;
	private: System::Windows::Forms::Timer^ tmrMenu;

	private: System::Windows::Forms::Timer^ tmrAnimacion;

	public:
		frmMenu(void)
		{
			InitializeComponent();
			srand(time(NULL));
			this->graficador = this->CreateGraphics();
			this->buffer = BufferedGraphicsManager::Current->Allocate(this->graficador, this->ClientRectangle);
			this->DoubleBuffered == true;
			this->juego = gcnew CJuego(this->ClientRectangle.Width / 28, this->ClientRectangle.Height / 28, 28);
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
			this->tmrAnimacion = (gcnew System::Windows::Forms::Timer(this->components));
			this->tmrMenu = (gcnew System::Windows::Forms::Timer(this->components));
			this->SuspendLayout();
			// 
			// tmrAnimacion
			// 
			this->tmrAnimacion->Tick += gcnew System::EventHandler(this, &frmMenu::animar);
			// 
			// tmrMenu
			// 
			this->tmrMenu->Enabled = true;
			this->tmrMenu->Tick += gcnew System::EventHandler(this, &frmMenu::animar_menu);
			// 
			// frmMenu
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(624, 321);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Name = L"frmMenu";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"menu principal";
			this->WindowState = System::Windows::Forms::FormWindowState::Maximized;
			this->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &frmMenu::frmMenu_Paint);
			this->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &frmMenu::accion_form);
			this->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &frmMenu::actualizar_mouse);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void animar(System::Object^ sender, System::EventArgs^ e) {
		//this->graficador->
		this->juego->get_laberinto()->pintar_mapa(buffer->Graphics);
		this->juego->pintar_ui(buffer->Graphics);
		this->buffer->Render();
	}
	private: System::Void frmMenu_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
		//this->juego->pintar_ui(graficador);
	}

	private: System::Void accion_form(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
		if (this->juego->get_cursor()->hay_colision(this->juego->get_btn_cerrar()))
			Application::Exit();
		if (this->juego->get_cursor()->hay_colision(this->juego->get_btn_comenzar()))
		{
			this->juego->iniciar_juego(buffer->Graphics);
			this->tmrMenu->Enabled = false;
			this->tmrAnimacion->Enabled = true;
		}
	}
	private: System::Void actualizar_mouse(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
		this->juego->get_cursor()->set_ubicacion(e->X, e->Y);
	}
	private: System::Void animar_menu(System::Object^ sender, System::EventArgs^ e) {
		this->juego->menu_principal(buffer->Graphics, this->ClientRectangle);
		this->buffer->Render();
	}
	};
}
