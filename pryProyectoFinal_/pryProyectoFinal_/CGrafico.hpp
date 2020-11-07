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
	Bitmap^ imagen;

public:
	CGrafico();
	CGrafico(String^ ruta_imagen, short x, short y, short ancho, short alto)
		:x(x), y(y), ax(0), ay(0), ancho(ancho), alto(ancho), imagen(gcnew Bitmap(ruta_imagen)), imagen_propia(true) {}
	CGrafico(String^ ruta_imagen, short x, short y, short ax, short ay, short ancho, short alto)
		:x(x), y(y), ax(ax), ay(ay), ancho(ancho), alto(ancho), imagen(gcnew Bitmap(ruta_imagen)), imagen_propia(true) {}
	CGrafico(Bitmap^ imagen, short x, short y, short ancho, short alto)
		:x(x), y(y), ax(0), ay(0), ancho(ancho), alto(ancho), imagen(imagen), imagen_propia(false) {}
	CGrafico(Bitmap^ imagen, short x, short y, short ax, short ay, short ancho, short alto)
		:x(x), y(y), ax(ax), ay(ay), ancho(ancho), alto(ancho), imagen(imagen), imagen_propia(false) {}
	~CGrafico() { if(this->imagen_propia) delete this->imagen; }

	void dibujar(Graphics^ graficador) {
		graficador->DrawImage(this->imagen, x, y, ancho, alto);
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

	short get_X() { return x; }
	void set_x(short x) { this->x = x; }
	short get_y() { return y; }
	void set_y(short y) { this->y = y; }
	short get_aX() { return ax; }
	void set_ubicacion(short x, short y) { this->x = x; this->x = y; }
	void set_ax(short ax) { this->ax = ax; }
	short get_ay() { return ay; }
	void set_ay(short ay) { this->ay = ay; }
	short get_ancho() { return ancho; }
	void set_ancho(short ancho) { this->ancho = ancho; }
	short get_alto() { return alto; }
	void set_alto(short alto) { this->alto = alto; }
};

ref class CGraficoAnimado : public CGrafico {
protected:
	short an_filas, an_columnas;
	short n_subimagenes;
	short indice;

public:
	CGraficoAnimado() {}
	CGraficoAnimado(String^ ruta_imagen, short x, short y, short ancho, short alto, short nfilas, short ncolumnas, short nsubimagenes) :
		CGrafico(ruta_imagen, x, y, ancho, alto), an_filas(nfilas), an_columnas(ncolumnas), n_subimagenes(nsubimagenes) {}
	CGraficoAnimado(String^ ruta_imagen, short x, short y, short ax, short ay, short ancho, short alto, short nfilas, short ncolumnas, short nsubimagenes) :
		CGrafico(ruta_imagen, x, y, ax, ay, ancho, alto), an_filas(nfilas), an_columnas(ncolumnas), n_subimagenes(nsubimagenes) {}
	CGraficoAnimado(Bitmap^ imagen, short x, short y, short ancho, short alto, short nfilas, short ncolumnas, short nsubimagenes) :
		CGrafico(imagen, x, y, ancho, alto), an_filas(nfilas), an_columnas(ncolumnas), n_subimagenes(nsubimagenes) {}
	CGraficoAnimado(Bitmap^ imagen, short x, short y, short ax, short ay, short ancho, short alto, short nfilas, short ncolumnas, short nsubimagenes) :
		CGrafico(imagen, x, y, ax, ay, ancho, alto), an_filas(nfilas), an_columnas(ncolumnas), n_subimagenes(nsubimagenes) {}
	~CGraficoAnimado() {}

	void dibujar(Graphics^ graficador) override {
		System::Drawing::Rectangle area_recorte = calcular_area_recorte();
		System::Drawing::Rectangle area_dibujo = System::Drawing::Rectangle(x, y, this->ancho, this->alto);
		graficador->DrawImage(this->imagen, area_dibujo, area_recorte, GraphicsUnit::Pixel);
		++indice %= n_subimagenes;
	}

private:
	System::Drawing::Rectangle calcular_area_recorte() {
		short ancho_subimagen = this->imagen->Width / this->an_columnas;
		short alto_subimagen = this->imagen->Height / this->an_filas;
		short x = this->indice % this->an_columnas * ancho_subimagen;
		short y = this->indice / this->an_columnas * alto_subimagen;
		return System::Drawing::Rectangle(x, y, ancho_subimagen, alto_subimagen);
	}
};

//