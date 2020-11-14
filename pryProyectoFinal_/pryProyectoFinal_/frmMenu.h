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
	
	private: System::Windows::Forms::Timer^ tmrAnimacion;

	public:
		frmMenu(void)
		{
			InitializeComponent();
			srand(time(NULL));
			this->graficador = this->CreateGraphics();
			this->buffer = BufferedGraphicsManager::Current->Allocate(this->graficador, this->ClientRectangle);
			this->juego = gcnew CJuego(30,20,10);
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
		/// <summary>
		/// Variable del diseñador necesaria.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Método necesario para admitir el Diseñador. No se puede modificar
		/// el contenido de este método con el editor de código.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->tmrAnimacion = (gcnew System::Windows::Forms::Timer(this->components));
			this->SuspendLayout();
			// 
			// tmrAnimacion
			// 
			this->tmrAnimacion->Enabled = true;
			this->tmrAnimacion->Tick += gcnew System::EventHandler(this, &frmMenu::animar);
			// 
			// frmMenu
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(624, 401);
			this->Name = L"frmMenu";
			this->Text = L"menu principal";
			this->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &frmMenu::frmMenu_Paint);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void animar(System::Object^ sender, System::EventArgs^ e) {
		//this->juego->get_laberinto()->pintar_mapa(graficador);
	}
	private: System::Void frmMenu_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
		this->juego->get_laberinto()->pintar_mapa(graficador);
		//string posini = this->juego->get_laberinto()->get_entrada().X + ", ";
	}
	};
}
