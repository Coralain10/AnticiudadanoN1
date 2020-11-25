#pragma once
namespace pryProyectoFinal {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Resumen de frm_configuracion
	/// </summary>
	public ref class frm_configuracion : public System::Windows::Forms::Form
	{
	public:
		frm_configuracion(void)
		{
			InitializeComponent();
			Cursor->Show();
		}

	protected:
		/// <summary>
		/// Limpiar los recursos que se estén usando.
		/// </summary>
		~frm_configuracion()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::NumericUpDown^ Nud_cant_aliados;
	protected:

	protected:
	private: System::Windows::Forms::NumericUpDown^ Nud_cant_vidas;
	private: System::Windows::Forms::Button^ btn_aceptar;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ lbl_cant_aliados;

	private: System::Windows::Forms::Label^ lbl_cant_vidas;
	private: System::Windows::Forms::PictureBox^ pictureBox1;
	private: System::Windows::Forms::NumericUpDown^ Nud_cant_tiempojuego;
	private: System::Windows::Forms::Label^ lbl_tiempo_total;

	private:
		/// <summary>
		/// Variable del diseñador necesaria.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Método necesario para admitir el Diseñador. No se puede modificar
		/// el contenido de este método con el editor de código.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(frm_configuracion::typeid));
			this->Nud_cant_aliados = (gcnew System::Windows::Forms::NumericUpDown());
			this->Nud_cant_vidas = (gcnew System::Windows::Forms::NumericUpDown());
			this->btn_aceptar = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->lbl_cant_aliados = (gcnew System::Windows::Forms::Label());
			this->lbl_cant_vidas = (gcnew System::Windows::Forms::Label());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->Nud_cant_tiempojuego = (gcnew System::Windows::Forms::NumericUpDown());
			this->lbl_tiempo_total = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->Nud_cant_aliados))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->Nud_cant_vidas))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->Nud_cant_tiempojuego))->BeginInit();
			this->SuspendLayout();
			// 
			// Nud_cant_aliados
			// 
			this->Nud_cant_aliados->BackColor = System::Drawing::Color::Black;
			this->Nud_cant_aliados->ForeColor = System::Drawing::Color::White;
			this->Nud_cant_aliados->Location = System::Drawing::Point(256, 208);
			this->Nud_cant_aliados->Name = L"Nud_cant_aliados";
			this->Nud_cant_aliados->Size = System::Drawing::Size(120, 20);
			this->Nud_cant_aliados->TabIndex = 0;
			// 
			// Nud_cant_vidas
			// 
			this->Nud_cant_vidas->BackColor = System::Drawing::Color::Black;
			this->Nud_cant_vidas->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->Nud_cant_vidas->Font = (gcnew System::Drawing::Font(L"Courier New", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Nud_cant_vidas->ForeColor = System::Drawing::Color::White;
			this->Nud_cant_vidas->Location = System::Drawing::Point(62, 208);
			this->Nud_cant_vidas->Name = L"Nud_cant_vidas";
			this->Nud_cant_vidas->Size = System::Drawing::Size(120, 20);
			this->Nud_cant_vidas->TabIndex = 0;
			// 
			// btn_aceptar
			// 
			this->btn_aceptar->BackColor = System::Drawing::Color::Black;
			this->btn_aceptar->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
			this->btn_aceptar->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->btn_aceptar->FlatAppearance->BorderSize = 0;
			this->btn_aceptar->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btn_aceptar->Font = (gcnew System::Drawing::Font(L"Courier New", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btn_aceptar->ForeColor = System::Drawing::Color::White;
			this->btn_aceptar->Location = System::Drawing::Point(0, 343);
			this->btn_aceptar->Name = L"btn_aceptar";
			this->btn_aceptar->Size = System::Drawing::Size(662, 89);
			this->btn_aceptar->TabIndex = 1;
			this->btn_aceptar->Text = L"ACEPTAR";
			this->btn_aceptar->UseVisualStyleBackColor = false;
			this->btn_aceptar->Click += gcnew System::EventHandler(this, &frm_configuracion::btn_aceptar_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(59, 129);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(35, 13);
			this->label1->TabIndex = 2;
			this->label1->Text = L"label1";
			// 
			// lbl_cant_aliados
			// 
			this->lbl_cant_aliados->AutoSize = true;
			this->lbl_cant_aliados->BackColor = System::Drawing::Color::Transparent;
			this->lbl_cant_aliados->Font = (gcnew System::Drawing::Font(L"Courier New", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lbl_cant_aliados->ForeColor = System::Drawing::SystemColors::Info;
			this->lbl_cant_aliados->Location = System::Drawing::Point(253, 174);
			this->lbl_cant_aliados->Name = L"lbl_cant_aliados";
			this->lbl_cant_aliados->Size = System::Drawing::Size(140, 14);
			this->lbl_cant_aliados->TabIndex = 2;
			this->lbl_cant_aliados->Text = L"Cantidad de Aliados";
			// 
			// lbl_cant_vidas
			// 
			this->lbl_cant_vidas->AutoSize = true;
			this->lbl_cant_vidas->BackColor = System::Drawing::Color::Transparent;
			this->lbl_cant_vidas->Font = (gcnew System::Drawing::Font(L"Courier New", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lbl_cant_vidas->ForeColor = System::Drawing::SystemColors::MenuBar;
			this->lbl_cant_vidas->Location = System::Drawing::Point(59, 174);
			this->lbl_cant_vidas->Name = L"lbl_cant_vidas";
			this->lbl_cant_vidas->Size = System::Drawing::Size(126, 14);
			this->lbl_cant_vidas->TabIndex = 3;
			this->lbl_cant_vidas->Text = L"Cantidad de vidas";
			// 
			// pictureBox1
			// 
			this->pictureBox1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->pictureBox1->BackColor = System::Drawing::Color::Transparent;
			this->pictureBox1->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox1.Image")));
			this->pictureBox1->Location = System::Drawing::Point(601, 29);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(39, 34);
			this->pictureBox1->TabIndex = 4;
			this->pictureBox1->TabStop = false;
			this->pictureBox1->Click += gcnew System::EventHandler(this, &frm_configuracion::pictureBox1_Click);
			// 
			// Nud_cant_tiempojuego
			// 
			this->Nud_cant_tiempojuego->BackColor = System::Drawing::Color::Black;
			this->Nud_cant_tiempojuego->ForeColor = System::Drawing::Color::White;
			this->Nud_cant_tiempojuego->Location = System::Drawing::Point(449, 208);
			this->Nud_cant_tiempojuego->Name = L"Nud_cant_tiempojuego";
			this->Nud_cant_tiempojuego->Size = System::Drawing::Size(120, 20);
			this->Nud_cant_tiempojuego->TabIndex = 5;
			// 
			// lbl_tiempo_total
			// 
			this->lbl_tiempo_total->AutoSize = true;
			this->lbl_tiempo_total->BackColor = System::Drawing::Color::Transparent;
			this->lbl_tiempo_total->Font = (gcnew System::Drawing::Font(L"Courier New", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lbl_tiempo_total->ForeColor = System::Drawing::SystemColors::Info;
			this->lbl_tiempo_total->Location = System::Drawing::Point(422, 174);
			this->lbl_tiempo_total->Name = L"lbl_tiempo_total";
			this->lbl_tiempo_total->Size = System::Drawing::Size(203, 14);
			this->lbl_tiempo_total->TabIndex = 6;
			this->lbl_tiempo_total->Text = L"Cantidad del tiempo de juego";
			// 
			// frm_configuracion
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"$this.BackgroundImage")));
			this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->ClientSize = System::Drawing::Size(662, 432);
			this->Controls->Add(this->lbl_tiempo_total);
			this->Controls->Add(this->Nud_cant_tiempojuego);
			this->Controls->Add(this->pictureBox1);
			this->Controls->Add(this->lbl_cant_vidas);
			this->Controls->Add(this->lbl_cant_aliados);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->btn_aceptar);
			this->Controls->Add(this->Nud_cant_vidas);
			this->Controls->Add(this->Nud_cant_aliados);
			this->DoubleBuffered = true;
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Name = L"frm_configuracion";
			this->ShowInTaskbar = false;
			this->SizeGripStyle = System::Windows::Forms::SizeGripStyle::Hide;
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Configuracion";
			this->WindowState = System::Windows::Forms::FormWindowState::Maximized;
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->Nud_cant_aliados))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->Nud_cant_vidas))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->Nud_cant_tiempojuego))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void btn_aceptar_Click(System::Object^ sender, System::EventArgs^ e) {
		
		Cursor->Hide();
		this->Close();
		
	}
private: System::Void pictureBox1_Click(System::Object^ sender, System::EventArgs^ e) {
		Cursor->Hide();
		this->Close();
}
public:
	short get_cantvidas() { return Int16::Parse(this->Nud_cant_vidas->Text); }
	short get_cantaliados() { return Int16::Parse(this->Nud_cant_aliados->Text); }
	short get_cantTiempo() { return Int16::Parse(this->Nud_cant_tiempojuego->Text); }
};
}
