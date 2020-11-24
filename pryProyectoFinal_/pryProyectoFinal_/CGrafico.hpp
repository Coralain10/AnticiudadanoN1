#pragma once

using namespace System;
using namespace System::Drawing;

ref class CGrafico
{
private:
	bool imagen_propia;
protected:
	short x, y;
	short ax, ay;
	short ancho, alto;
	System::Drawing::Rectangle area_dibujo;
	Bitmap^ imagen;

public:
	CGrafico(){}
	CGrafico(String^ ruta_imagen) :imagen(gcnew Bitmap(ruta_imagen)) {
		this->ancho = this->imagen->Width;
		this->alto = this->imagen->Height;
		this->area_dibujo = System::Drawing::Rectangle(0,0,this->ancho, this->alto);
	}
	CGrafico(Bitmap^ imagen) :imagen(imagen) {
		this->ancho = this->imagen->Width;
		this->alto = this->imagen->Height;
		this->area_dibujo = System::Drawing::Rectangle(0, 0, this->ancho, this->alto);
	}
	CGrafico(String^ ruta_imagen, short ancho, short alto)
		:ax(0), ay(0), ancho(ancho), alto(alto), imagen(gcnew Bitmap(ruta_imagen)), imagen_propia(true), area_dibujo(System::Drawing::Rectangle(0,0,ancho, alto)) {}
	CGrafico(String^ ruta_imagen, System::Drawing::Rectangle recorte, short ancho, short alto)
		:ax(0), ay(0), ancho(ancho), alto(alto), imagen(gcnew Bitmap(ruta_imagen)), imagen_propia(true), area_dibujo(System::Drawing::Rectangle(0, 0, ancho, alto)) {
		this->imagen = this->imagen->Clone(recorte, imagen->PixelFormat);
	}
	CGrafico(String^ ruta_imagen, short x, short y, short ancho, short alto)
		:x(x), y(y), ax(0), ay(0), ancho(ancho), alto(alto), imagen(gcnew Bitmap(ruta_imagen)), imagen_propia(true), area_dibujo(System::Drawing::Rectangle(x, y, ancho,alto)) {}
	CGrafico(String^ ruta_imagen, short x, short y, short ax, short ay, short ancho, short alto)
		:x(x), y(y), ax(ax), ay(ay), ancho(ancho), alto(alto), imagen(gcnew Bitmap(ruta_imagen)), imagen_propia(true), area_dibujo(System::Drawing::Rectangle(x, y, ancho, alto)) {}
	CGrafico(Bitmap^ imagen, short ancho, short alto)
		:ax(0), ay(0), ancho(ancho), alto(alto), imagen(imagen), imagen_propia(false), area_dibujo(System::Drawing::Rectangle(0, 0, ancho, alto)) {}
	CGrafico(Bitmap^ imagen, System::Drawing::Rectangle recorte, short ancho, short alto)
		:ax(0), ay(0), ancho(ancho), alto(alto), imagen(imagen->Clone(recorte,imagen->PixelFormat)), imagen_propia(false), area_dibujo(System::Drawing::Rectangle(0, 0, ancho, alto)) {
		//delete imagen;
	}
	CGrafico(Bitmap^ imagen, short x, short y, short ancho, short alto)
		:x(x), y(y), ax(0), ay(0), ancho(ancho), alto(alto), imagen(imagen), imagen_propia(false), area_dibujo(System::Drawing::Rectangle(x, y, ancho, alto)) {}
	CGrafico(Bitmap^ imagen, System::Drawing::Rectangle recorte, short x, short y, short ancho, short alto)
		:x(x), y(y), ax(0), ay(0), ancho(ancho), alto(alto), imagen(imagen->Clone(recorte, imagen->PixelFormat)), imagen_propia(false), area_dibujo(System::Drawing::Rectangle(x, y, ancho, alto)) {}
	CGrafico(Bitmap^ imagen, short x, short y, short ax, short ay, short ancho, short alto)
		:x(x), y(y), ax(ax), ay(ay), ancho(ancho), alto(alto), imagen(imagen), imagen_propia(false), area_dibujo(System::Drawing::Rectangle(x, y, ancho, alto)) {}
	~CGrafico() { if(this->imagen_propia) delete this->imagen; }

	virtual void dibujar(Graphics^ graficador) {
		graficador->DrawImage(this->imagen, area_dibujo);
	}

	virtual void dibujar(Graphics^ graficador, short x_pos_img, short y_pos_img, short ancho_img, short alto_img) {
		System::Drawing::Rectangle area_recorte = System::Drawing::Rectangle(x_pos_img, y_pos_img, ancho_img, alto_img);
		graficador->DrawImage(this->imagen, this->area_dibujo, area_recorte, GraphicsUnit::Pixel);
	}

	bool hay_colision(CGrafico^ otro) {
		return this->area_dibujo.IntersectsWith(otro->area_dibujo);
	}

	void hacerTransparente() {
		Color colorTransparente = imagen->GetPixel(0, 0);
		imagen->MakeTransparent(colorTransparente);
	}

	void voltear_horizontal() { this->ancho *= -1; }
	void voltear_vertical() { this->alto *= -1; }

	void escalar_x(float escala_x) { this->ancho *= escala_x; }
	void escalar_y(float escala_y) { this->alto *= escala_y; }
	void escalar(float escala) {
		this->ancho *= escala;
		this->alto *= escala;
	}
	void escalar(float escala_x, float escala_y) {
		this->ancho *= escala_x;
		this->alto *= escala_y;
	}

	void rotar(float angulo) {
		//TODO
	}

	short get_x() { return x; }
	void set_x(short x) {
		this->x = x;
		this->area_dibujo.X = x;
	}
	short get_y() { return y; }
	void set_y(short y) {
		this->y = y;
		this->area_dibujo.Y = y;
	}
	short get_aX() { return ax; }
	void set_ubicacion(short x, short y) {
		this->x = x;
		this->y = y;
		this->area_dibujo.X = x;
		this->area_dibujo.Y = y;
	}
	System::Drawing::Point get_pos_act(){return System::Drawing::Point(this->x,this->y);}
	void set_ax(short ax) { this->ax = ax; }
	short get_ay() { return ay; }
	void set_ay(short ay) { this->ay = ay; }
	short get_ancho() { return ancho; }
	void set_ancho(short ancho) { this->ancho = ancho; }
	short get_alto() { return alto; }
	void set_alto(short alto) { this->alto = alto; }
	void set_imagen (String^ ruta_imagen){ 
		if (this->imagen != nullptr)
			delete this->imagen;
		this->imagen = gcnew Bitmap(ruta_imagen);
	}
	System::Drawing::Rectangle get_area_dibujo() { return this->area_dibujo; }
	void edit_imagen(String^ ruta_imagen, short ancho, short alto) {
		delete this->imagen;
		this->imagen = gcnew Bitmap(ruta_imagen);
		this->area_dibujo.Width = this->ancho = ancho;
		this->area_dibujo.Height = this->alto = alto;
	}
	void edit_imagen(Bitmap^ imagen, short ancho, short alto) {
		//delete this->imagen;
		this->imagen = imagen;
		this->area_dibujo.Width = this->ancho = ancho;
		this->area_dibujo.Height = this->alto = alto;
	}
	/*System::Drawing::Rectangle set_area_dibujo(short x, short y, short ancho, short alto) { this->area_dibujo = System::Drawing::Rectangle(x, y, ancho, alto); }
	System::Drawing::Rectangle set_area_dibujo(System::Drawing::Rectangle area) { this->area_dibujo = area; }*/
};

ref class CGraficoAnimado : public CGrafico {
protected:
	short an_filas, an_columnas;
	short n_subimagenes;
	short indice;
	short pos_anim_x, pos_anim_y;

public:
	CGraficoAnimado() {}
	CGraficoAnimado(String^ ruta_imagen, short x, short y, short ancho, short alto, short nfilas, short ncolumnas, short nsubimagenes) :
		CGrafico(ruta_imagen, x, y, ancho, alto), indice(0),
		an_filas(nfilas), an_columnas(ncolumnas), n_subimagenes(nsubimagenes), pos_anim_x(0), pos_anim_y(0){}
	CGraficoAnimado(String^ ruta_imagen, short x, short y, short ancho, short alto, short nfilas, short ncolumnas) :
		CGrafico(ruta_imagen, x, y, ancho, alto), indice(0),
		an_filas(nfilas), an_columnas(ncolumnas), pos_anim_x(0), pos_anim_y(0) {}
	CGraficoAnimado(String^ ruta_imagen, System::Drawing::Rectangle area_dibujo, short nfilas, short ncolumnas) :
		CGrafico(ruta_imagen, area_dibujo.X, area_dibujo.Y, area_dibujo.Width, area_dibujo.Height), indice(0),
		an_filas(nfilas), an_columnas(ncolumnas), pos_anim_x(0), pos_anim_y(0) {}
	CGraficoAnimado(String^ ruta_imagen, short x, short y, short ax, short ay, short ancho, short alto, short nfilas, short ncolumnas, short nsubimagenes) :
		CGrafico(ruta_imagen, x, y, ax, ay, ancho, alto), indice(0),
		an_filas(nfilas), an_columnas(ncolumnas), n_subimagenes(nsubimagenes), pos_anim_x(0), pos_anim_y(0) {}
	CGraficoAnimado(Bitmap^ imagen, short x, short y, short ancho, short alto, short nfilas, short ncolumnas, short nsubimagenes) :
		CGrafico(imagen, x, y, ancho, alto), indice(0),
		an_filas(nfilas), an_columnas(ncolumnas), n_subimagenes(nsubimagenes), pos_anim_x(0), pos_anim_y(0) {}
	CGraficoAnimado(Bitmap^ imagen, short x, short y, short ax, short ay, short ancho, short alto, short nfilas, short ncolumnas, short nsubimagenes) :
		CGrafico(imagen, x, y, ax, ay, ancho, alto), indice(0),
		an_filas(nfilas), an_columnas(ncolumnas), n_subimagenes(nsubimagenes), pos_anim_x(0), pos_anim_y(0) {}
	CGraficoAnimado(String^ ruta_imagen, System::Drawing::Rectangle recorte_graf, short x,short y, short ancho, short alto, short nfilas, short ncolumnas):
		CGrafico(ruta_imagen, recorte_graf,ancho, alto), indice(0),
		an_filas(nfilas), an_columnas(ncolumnas), pos_anim_x(0), pos_anim_y(0) {}

	~CGraficoAnimado() {}

	void dibujar(Graphics^ graficador) override {
		System::Drawing::Rectangle area_recorte = calcular_area_recorte();
		System::Drawing::Rectangle area_dibujo = System::Drawing::Rectangle(x, y, this->ancho, this->alto);
		graficador->DrawImage(this->imagen, area_dibujo, area_recorte, GraphicsUnit::Pixel);
		//++indice %= n_subimagenes;
	}

	void set_animacion(short pos_animacion_x, short pos_animacion_y) {
		this->pos_anim_x = pos_animacion_x;
		this->pos_anim_y = pos_animacion_y;
	}

private:
	System::Drawing::Rectangle calcular_area_recorte() {
		short ancho_subimagen = this->imagen->Width / this->an_columnas;
		short alto_subimagen = this->imagen->Height / this->an_filas;
		short x = this->indice % this->an_columnas * ancho_subimagen + pos_anim_x;
		short y = this->indice / this->an_columnas * alto_subimagen + pos_anim_y;
		return System::Drawing::Rectangle(x, y, ancho_subimagen, alto_subimagen);
	}

};

//