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
	short tamanho_celda;
	Rectangle area_juego;
	CConfiguracion^ config;
	Bitmap^ fondo_inicio;
	Bitmap^ bg_botones;
	Bitmap^ img_flechasAA;
	Bitmap^ img_aux;
	List<CAliado^>^ aliados;
	List<CCorrupto^>^ corruptos;
	List<CAsesino^>^ asesinos;
	CGrafico^ logo;
	CGrafico^ ui_personaje;
	CGrafico^ btn_cerrar;
	CGrafico^ btn_comenzar;
	CGrafico^ btn_dialogo_sgt;
	CGrafico^ btn_dialogo_ant;
	CGrafico^ btn_configurar;
	CGrafico^ btn_reiniciar;
	CGrafico^ cursor;
	CProtagonista^ protagonista;
	bool inicio_juego;
	Font^ tipografia;
	List<String^>^ dialogos;
	short pos_dialogo_act;

public:
	CJuego(short tamanho_celda, Rectangle area): tamanho_celda(tamanho_celda), area_juego(area) {
		this->inicio_juego = false;
		this->tipografia = gcnew System::Drawing::Font("Courier new",tamanho_celda*0.75),
		this->laberinto = gcnew CLaberinto((short)(area.Width / tamanho_celda), (short)(area.Height / tamanho_celda), tamanho_celda);
		this->config = gcnew CConfiguracion();
		this->bg_botones = gcnew Bitmap("Imagenes\\buttons.png");
		this->img_flechasAA = gcnew Bitmap("Imagenes\\flechasAA.png");
		this->fondo_inicio = gcnew Bitmap("Imagenes\\fondoUI.png");
		this->logo = gcnew CGrafico("Imagenes\\logo.png",360*2,110*2);
		this->logo->escalar(2);
		this->img_aux = gcnew Bitmap("Imagenes\\zion_letrero.png");
		this->ui_personaje = gcnew CGrafico("Imagenes\\protaUI.png", (area.Width - 4 * this->tamanho_celda), 0, 1392, 1080);
		this->btn_cerrar = gcnew CGrafico("Imagenes\\cerrar.png", (short)(area.Width - 2.5 * tamanho_celda), tamanho_celda, (short)(tamanho_celda * 1.5), (short)(tamanho_celda * 1.5));
		this->btn_reiniciar = gcnew CGrafico("Imagenes\\reiniciar.png", (area.Width - 5* tamanho_celda), tamanho_celda, (short)(tamanho_celda * 1.5), (short)(tamanho_celda * 1.5));
		this->btn_comenzar = gcnew CGrafico(bg_botones, Rectangle(0, 0, 160, 160), tamanho_celda *2, area.Height - 8*tamanho_celda, tamanho_celda*10, tamanho_celda*2);
		this->btn_configurar = gcnew CGrafico(bg_botones, Rectangle(0, 160, 160, 160), tamanho_celda * 2, area.Height - 4 * tamanho_celda, tamanho_celda*14, tamanho_celda*2);
		this->btn_dialogo_ant = gcnew CGrafico(img_flechasAA, Rectangle(0, 0, 32, 32), area.Width - 2 * tamanho_celda, tamanho_celda * 6, tamanho_celda, tamanho_celda);
		this->btn_dialogo_sgt = gcnew CGrafico(img_flechasAA, Rectangle(0, 32, 32, 32), area.Width - 2 * tamanho_celda, tamanho_celda * 8, tamanho_celda, tamanho_celda);
		this->cursor = gcnew CGrafico("Imagenes\\mouse.png", 32, 32);
		this->aliados = gcnew List<CAliado^>();
		this->corruptos = gcnew List<CCorrupto^>();
		this->asesinos = gcnew List<CAsesino^>();
		this->protagonista = gcnew CProtagonista("Imagenes\\Protagonista.png",this->laberinto->get_pos_entrada().X*tamanho_celda, this->laberinto->get_pos_entrada().Y * tamanho_celda,System::Drawing::Rectangle(tamanho_celda, tamanho_celda, tamanho_celda, tamanho_celda),System::Drawing::Rectangle(0, 0, 0, 0),4,4);
		//this->protagonista = gcnew CProtagonista(this->laberinto->get_pos_entrada().X, this->laberinto->get_pos_entrada().Y, tamanho_celda, tamanho_celda);
		this->dialogos = gcnew List<String^>();
		set_dialogos();
		pos_dialogo_act = 0;
	}
	~CJuego() {
		delete img_flechasAA;
		delete btn_dialogo_sgt;
		delete btn_dialogo_ant;
		for each (String ^ dialogo in dialogos)
			delete dialogo;
		delete dialogos;
		delete tipografia;
		delete fondo_inicio;
		delete ui_personaje;
		delete bg_botones;
		delete btn_cerrar;
		delete btn_comenzar;
		delete btn_configurar;
		delete btn_reiniciar;
		delete img_aux;
		delete protagonista;
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

	void intro(Graphics^ graficador) {
		graficador->Clear(System::Drawing::Color::Black);
		graficador->DrawString(dialogos[pos_dialogo_act], this->tipografia, Brushes::White, 100, 100);
		pos_dialogo_act++;
	}

	void menu_principal(Graphics^ graficador) {
		graficador->DrawImage(fondo_inicio, this->area_juego);
		this->btn_cerrar->dibujar(graficador);
		this->btn_comenzar->dibujar(graficador);
		graficador->DrawString("¡Jugar!", this->tipografia, Brushes::White, btn_comenzar->get_x() + (btn_comenzar->get_ancho() / 4), btn_comenzar->get_y() + (btn_comenzar->get_alto() / 4));
		this->btn_configurar->dibujar(graficador);
		graficador->DrawString("Configurar", this->tipografia, Brushes::White, btn_configurar->get_x() + (btn_configurar->get_ancho() / 4), btn_configurar->get_y() + (btn_configurar->get_alto() / 4));
		this->logo->dibujar(graficador);
		bool parpadear = rand() % 2;
		if (parpadear == 1)//hacer parpadear ZION
			graficador->DrawImage(img_aux, this->area_juego.Width / 2 - 16, this->area_juego.Height - 180, 32, 120);
		if (this->ui_personaje->get_x() - 40 >= 200) {
			this->ui_personaje->set_x(ui_personaje->get_x() - 40);
		}
		this->ui_personaje->dibujar(graficador);
		this->cursor->dibujar(graficador);
	}

	void pintar_ui(Graphics^ graficador) {
		this->btn_cerrar->dibujar(graficador);
		this->btn_reiniciar->dibujar(graficador);
		this->cursor->dibujar(graficador);
	}

	void iniciar_entrada_juego(Graphics^ graficador) {
		//this->inicio_juego = true;
		graficador->Clear(System::Drawing::Color::Black);
		pos_dialogo_act = 4;
		get_ui_personaje()->edit_imagen("Imagenes\\prota_alliesUI.png", 382 * 2, 258 * 2);
		get_ui_personaje()->set_ubicacion(area_juego.Width / 2 - this->ui_personaje->get_ancho() / 2, area_juego.Height - this->ui_personaje->get_alto());
	}

	bool anim_entrada_juego(Graphics^ graficador) {
		if (this->pos_dialogo_act >= 4 && this->pos_dialogo_act < 7) {
			graficador->Clear(System::Drawing::Color::Black);
			this->ui_personaje->dibujar(graficador);
			graficador->DrawString(dialogos[pos_dialogo_act], this->tipografia, Brushes::White, 50, 50 );
			//if (this->pos_dialogo_act > 4)
				this->btn_dialogo_ant->dibujar(graficador);
			//if (this->pos_dialogo_act < 6)
				this->btn_dialogo_sgt->dibujar(graficador);
			return true;
		}
		else {
			//this->inicio_juego = false;
			this->ui_personaje->edit_imagen("Imagenes\\protaUI.png", 1392, 1080);
			this->ui_personaje->set_ubicacion(area_juego.Width - 4 * this->tamanho_celda, 0);
			return false;
		}
	}

	void iniciar_juego() {
		for (short i = 0; i < this->config->aliados_cant; i++)
			this->aliados->Add(gcnew CAliado);
		/*for (short i = 0; i < this->config->asesinos_cant; i++)
			this->asesinos->Add(gcnew CAsesinos);
		for (short i = 0; i < this->config->asesinos_cant; i++)
			this->asesinos->Add(gcnew CCorruptos);*/
	}
	void interactuar(Direccion direccion) {
		this->protagonista->mover(direccion,this->laberinto->get_mapa());
	}
	void jugar(Graphics ^g) {
		this->protagonista->dibujarSprite(g);
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

	void reiniciar_lab() {
		delete this->laberinto;
		this->laberinto = gcnew CLaberinto((short)(area_juego.Width / tamanho_celda), (short)(area_juego.Height / tamanho_celda), tamanho_celda);
	}

	CLaberinto^ get_laberinto() { return this->laberinto; }
	CGrafico^ get_btn_cerrar() { return this->btn_cerrar; }
	CGrafico^ get_btn_comenzar() { return this->btn_comenzar; }
	CGrafico^ get_btn_configurar() { return this->btn_configurar; }
	CGrafico^ get_btn_reiniciar() { return this->btn_reiniciar; }
	CGrafico^ get_btn_dsiguiente() { return this->btn_dialogo_sgt; }
	CGrafico^ get_btn_danterior() { return this->btn_dialogo_ant; }
	CGrafico^ get_cursor() { return this->cursor; }
	Font^ get_fuente() { return this->tipografia; }
	void set_pos_dialog_act(short pos_dialog) { this->pos_dialogo_act = pos_dialog; }
	short get_pos_dialog_act() { return this->pos_dialogo_act; }
	CGrafico^ get_ui_personaje() { return this->ui_personaje; }
	bool juego_esta_iniciado() { return this->inicio_juego; }

private:
	void set_dialogos() {
		//Introduccion - Descripcion [0-3]
		this->dialogos->Add("Existe un mundo llamado Zion\nque se encuentra regido por un grupo de personas de gran poder,\nquienes han establecido una dictadura total\ndonde ningún ciudadano tiene voz ni voto,\ny son atormentados constantemente\ncon tal de que se mantengan volubles ante la tiranía del grupo.");
		this->dialogos->Add("Pero hay algo que este grupo de dictadores ignora,\nes que durante años,se ha ido formando en silencio una rebelión,\ncon el propósito de liberar a todos los pueblos\ny alcanzar la armonía que una vez existió Zion,\ny que ahora solo vive en la memoria de los más viejos.");
		this->dialogos->Add("El líder de este grupo de rebeldes\nha estado viviendo por mucho tiempo en el grupo privilegiado,\nbuscando alcanzar los altos mandos.\n\nDespués de años de soportar ver maltratos hacia su pueblo,\npor fin está listo para actuar.");
		this->dialogos->Add("Durante su estancia\nrecopiló información acerca de los mundos adyacentes a Zion,\ny encontró uno con el que puede contar\npara la liberación de su pueblo.\n\nPero para ello debe salir de Zion personalmente,\nrenunciando así a su posición como gobernante\ny siendo declarado como\n\"ANITICIUDADANO\"");
		//Advertencias [4-6]
		this->dialogos->Add("¡¡¡CUIDADO!!!\n\nHan sido liberados los \"corruptos\",\nquienes van a ir buscando a tus aliados\ny los irán corrompiendo uno por uno.");
		this->dialogos->Add("Recuerda que mientras más tardes en salir,\nlos \"corruptos\" pueden ir cerrando tratos con los \"asesinos\",\ndespiadados seres que no dudaran ni un segundo en matarte.");
		this->dialogos->Add("Te deseamos suerte en tu viaje,\ny te apoyamos en el camino de Zion hacia la libertad.");
		//Instrucciones Protagonista [7-11]
		this->dialogos->Add("Instrucciones:");
		this->dialogos->Add("Este es tu personaje");
		this->dialogos->Add("Lo controlas usando las teclas direccionales");
		this->dialogos->Add("Esta es tu barra de vida, inicias con *cantidad de vida* de vida");
		this->dialogos->Add("La meta del juego es lograr atravesar el laberinto sin morir");
		//Instrucciones NPC [12-17]
		this->dialogos->Add("A lo largo del laberinto te podrás encontrar con tres tipos de personaje:");
		this->dialogos->Add("ALIADOS:\nSon personajes que te ayudaran en tu viaje\ny te seguirán a lo largo de este dando su vida por la tuya.");
		this->dialogos->Add("CORRUPTOS:\nEstan en tu contra, caminan a lo largo del mapa\ny cuando encuentran un aliado lo corrompen convirtiéndolos en corruptos");
		this->dialogos->Add("ASESINOS:\ncuando encuentran un aliado lo asesinan y lo suplantan\ncambiando su aspecto, siendo iguales a los aliados.");
		this->dialogos->Add("Interacción especial:\nUna vez los assassins son liberados, se generaran portales en distintas partes del laberinto,\nlo que permitirá un escape de cualquier situación de riesgo de forma segura");
		this->dialogos->Add("A lo largo del mapa se han colocado balas, las cuales cargaran tu pistola,\nla que usarás para salir de las situaciones de alto riesgo haciendo frente al peligro.");
		//Final [18-19]
		this->dialogos->Add("Eso es todo lo que debes saber para tu misión");
		this->dialogos->Add("Te deseamos suerte en tu viaje y esperamos que acabes con la injustica de este mundo.");
	}
};

