#pragma once
#include "CGrafico.hpp"
#include "CDialogos.hpp"
#include "CLaberinto.hpp"
#include "CEntidad.hpp"
#include "CProtagonista.hpp"
#include "CNPC.hpp"

using namespace System::Collections::Generic;

ref class CConfiguracion {
private:
	short aliados_cant, asesinos_cant, corruptos_cant;

public:
	unsigned int ts_total, ts_actual, ts_alianza;
	short aliados_rvision, asesinos_rvision, corruptos_rvision;
	int t_aliados_seguir, t_asesinos_ataque, t_corruptos_corrupcion;

	CConfiguracion() {
		//cargando valores por default
		this->ts_total = 12000;
		this->ts_actual = 0;
		this->ts_alianza = 6000;
		this->aliados_cant = 10;
		this->asesinos_cant = (short)(aliados_cant * 0.6);
		this->corruptos_cant = (short)(aliados_cant * 0.4);
		this->aliados_rvision = this->asesinos_rvision = this->corruptos_rvision = 2;
		this->t_aliados_seguir = t_asesinos_ataque = t_corruptos_corrupcion;
	}
	~CConfiguracion() {}
	
	void set_aliados_cant(short cantidad) {
		this->aliados_cant = cantidad;
		this->asesinos_cant = (short)(cantidad * 0.6);
		this->corruptos_cant = (short)(cantidad * 0.4);
	}
	short get_aliados_cant() { return this->aliados_cant; }
	short get_corruptos_cant() { return this->corruptos_cant; }
	short get_asesinos_cant() { return this->asesinos_cant; }
};

ref class CMenu {
private:
	Bitmap^ fondo;
	Bitmap^ bg_botones;
	Bitmap^ letrero;
	CGrafico^ logo;
	CGrafico^ ui_personaje;
	CGrafico^ btn_comenzar;
	CGrafico^ btn_configurar;
	Font^ tipografia;
	Rectangle area;
public:
	CMenu(short tamanho_celda, Rectangle area, Font^ tipografia): tipografia(tipografia), area(area){
		this->bg_botones = gcnew Bitmap("Imagenes\\buttons.png");
		this->fondo = gcnew Bitmap("Imagenes\\fondoUI.png");
		this->logo = gcnew CGrafico("Imagenes\\logo.png", 360 * 2, 110 * 2);
		this->logo->escalar(2);
		this->letrero = gcnew Bitmap("Imagenes\\zion_letrero.png");
		this->ui_personaje = gcnew CGrafico("Imagenes\\protaUI.png", (area.Width - 4 * tamanho_celda), 0, 1392, 1080);
		this->btn_comenzar = gcnew CGrafico(bg_botones, Rectangle(0, 0, 160, 160), tamanho_celda * 2, area.Height - 8 * tamanho_celda, tamanho_celda * 10, tamanho_celda * 2);
		this->btn_configurar = gcnew CGrafico(bg_botones, Rectangle(0, 160, 160, 160), tamanho_celda * 2, area.Height - 4 * tamanho_celda, tamanho_celda * 14, tamanho_celda * 2);
	}
	~CMenu() {
		delete fondo;
		delete bg_botones;
		delete tipografia;
		delete ui_personaje;
		delete bg_botones;
		delete btn_comenzar;
		delete btn_configurar;
		delete letrero;
	}

	void menu_principal(Graphics^ graficador) {
		graficador->DrawImage(fondo, this->area);
		this->btn_comenzar->dibujar(graficador);
		graficador->DrawString("¡Jugar!", this->tipografia, Brushes::White, btn_comenzar->get_x() + (btn_comenzar->get_ancho() / 4), btn_comenzar->get_y() + (btn_comenzar->get_alto() / 4));
		this->btn_configurar->dibujar(graficador);
		graficador->DrawString("Configurar", this->tipografia, Brushes::White, btn_configurar->get_x() + (btn_configurar->get_ancho() / 4), btn_configurar->get_y() + (btn_configurar->get_alto() / 4));
		this->logo->dibujar(graficador);
		bool parpadear = rand() % 2;
		if (parpadear == 1)//hacer parpadear ZION
			graficador->DrawImage(this->letrero, this->area.Width / 2 - 16, this->area.Height - 180, 32, 120);
		if (this->ui_personaje->get_x() - 40 >= 200) {
			this->ui_personaje->set_x(ui_personaje->get_x() - 40);
		}
		this->ui_personaje->dibujar(graficador);
	}

	CGrafico^ get_btn_comenzar() { return this->btn_comenzar; }
	CGrafico^ get_btn_configurar() { return this->btn_configurar; }
	CGrafico^ get_ui_personaje() { return this->ui_personaje; }
};

ref class CJuego {
private:
	short tamanho_celda;
	Rectangle area_juego;
	Font^ tipografia;

	CMenu^ menu;
	CConfiguracion^ config;
	
	CDialogos^ intro0;
	CDialogos^ introjuego;
	CChat^ chat_alianza;
	CDialogo^ gameover;
	CDialogo^ ganar;
	CDialogo^ creditos;

	CGrafico^ cursor;
	CGrafico^ btn_cerrar;

	CGrafico^ btn_reiniciar;
	CLaberinto^ laberinto;
	List<CAliado^>^ aliados;
	List<CCorrupto^>^ corruptos;
	List<CAsesino^>^ asesinos;
	CProtagonista^ protagonista;
	bool inicio_juego;

public:
	CJuego(short tamanho_celda, Rectangle area): tamanho_celda(tamanho_celda), area_juego(area) {
		this->tipografia = gcnew System::Drawing::Font("Courier new", tamanho_celda * 0.75);
		this->menu = gcnew CMenu(this->tamanho_celda, this->area_juego, this->tipografia);
		this->config = gcnew CConfiguracion();
		set_dialogos();
		this->cursor = gcnew CGrafico("Imagenes\\mouse.png", 32, 32);
		this->btn_cerrar = gcnew CGrafico("Imagenes\\cerrar.png", (short)(area.Width - 2.5 * tamanho_celda), tamanho_celda, (short)(tamanho_celda * 1.5), (short)(tamanho_celda * 1.5));
		this->btn_reiniciar = gcnew CGrafico("Imagenes\\reiniciar.png", (area.Width - 5 * tamanho_celda), tamanho_celda, (short)(tamanho_celda * 1.5), (short)(tamanho_celda * 1.5));
		this->laberinto = gcnew CLaberinto((short)(area.Width / tamanho_celda), (short)(area.Height / tamanho_celda), tamanho_celda);
		this->aliados = gcnew List<CAliado^>();
		this->corruptos = gcnew List<CCorrupto^>();
		this->asesinos = gcnew List<CAsesino^>();
		this->protagonista = gcnew CProtagonista("Imagenes\\Protagonista.png", System::Drawing::Rectangle(this->laberinto->get_pos_entrada().X * tamanho_celda, this->laberinto->get_pos_entrada().Y * tamanho_celda, tamanho_celda, tamanho_celda), System::Drawing::Rectangle(0, 0, 0, 0), 4, 4);
		this->inicio_juego = false;
	}
	~CJuego() {
		delete tipografia;
		delete cursor;
		delete btn_cerrar;
		delete config;
		delete menu;

		delete intro0;
		delete introjuego;
		delete chat_alianza;
		delete gameover;
		delete ganar;
		delete creditos;

		delete laberinto;
		delete btn_reiniciar;
		delete protagonista;
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

	void pintar_ui(Graphics^ graficador) {
		this->btn_cerrar->dibujar(graficador);
		this->cursor->dibujar(graficador);
	}

	void iniciar_juego() {
		for (short i = 0; i < this->config->get_aliados_cant(); i++)
			this->aliados->Add(gcnew CAliado);
		/*for (short i = 0; i < this->config->asesinos_cant; i++)
			this->asesinos->Add(gcnew CAsesinos);
		for (short i = 0; i < this->config->asesinos_cant; i++)
			this->asesinos->Add(gcnew CCorruptos);*/
	}
	void interactuar(Direccion direccion) {
		this->protagonista->mover(direccion,this->laberinto);
	}
	void jugar(Graphics ^g) {
		this->protagonista->dibujarSprite(g);
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

	bool aumentar_dificultad() {
		if (this->config->ts_actual == this->config->ts_alianza)
			return true;
	}
	bool es_fin_juego() {
		if (this->config->ts_actual == this->config->ts_total)
			return true;
	}

	CConfiguracion^ get_configuracion() { return this->config; }
	CMenu^ get_menu() { return this->menu; }
	CDialogos^ get_intro0() { return this->intro0; };
	CDialogos^ get_introjuego() { return this->introjuego; }
	CChat^ get_chat_alianza() { return this->chat_alianza; }
	CDialogo^ get_gameover() { return this->gameover; }
	CDialogo^ get_ganar() { return this->ganar; }
	CDialogo^ get_creditos() { return this->creditos; }
	CLaberinto^ get_laberinto() { return this->laberinto; }
	CGrafico^ get_btn_cerrar() { return this->btn_cerrar; }
	CGrafico^ get_btn_reiniciar() { return this->btn_reiniciar; }
	CGrafico^ get_cursor() { return this->cursor; }
	Font^ get_fuente() { return this->tipografia; }
	bool juego_esta_iniciado() { return this->inicio_juego; }

private:
	void set_dialogos() {
		List<CDialogo^>^ intro_descrip = gcnew List<CDialogo^>();
		intro_descrip->Add(gcnew CDialogo("Existe un mundo llamado Zion\nque se encuentra regido por un grupo de personas de gran poder,\nquienes han establecido una dictadura total\ndonde ningún ciudadano tiene voz ni voto,\ny son atormentados constantemente\ncon tal de que se mantengan volubles ante la tiranía del grupo.",this->area_juego));
		intro_descrip->Add(gcnew CDialogo("Pero hay algo que este grupo de dictadores ignora,\nes que durante años,se ha ido formando en silencio una rebelión,\ncon el propósito de liberar a todos los pueblos\ny alcanzar la armonía que una vez existió Zion,\ny que ahora solo vive en la memoria de los más viejos.", this->area_juego));
		intro_descrip->Add(gcnew CDialogo("El líder de este grupo de rebeldes\nha estado viviendo por mucho tiempo en el grupo privilegiado,\nbuscando alcanzar los altos mandos.\n\nDespués de años de soportar ver maltratos hacia su pueblo,\npor fin está listo para actuar.", this->area_juego));
		intro_descrip->Add(gcnew CDialogo("Durante su estancia\nrecopiló información acerca de los mundos adyacentes a Zion,\ny encontró uno con el que puede contar\npara la liberación de su pueblo.\n\nPero para ello debe salir de Zion personalmente,\nrenunciando así a su posición como gobernante\ny siendo declarado como\n\"ANITICIUDADANO\"", this->area_juego));
		intro0 = gcnew CDialogos(intro_descrip, this->area_juego);

		List<CDialogo^>^ intro_juego = gcnew List<CDialogo^>();
		intro_juego->Add(gcnew CDialogo("¡¡¡CUIDADO!!!\n\nHan sido liberados los \"corruptos\",\nquienes van a ir buscando a tus aliados\ny los irán corrompiendo uno por uno.", this->area_juego));
		intro_juego->Add(gcnew CDialogo("Recuerda que mientras más tardes en salir,\nlos \"corruptos\" pueden ir cerrando tratos con los \"asesinos\",\ndespiadados seres que no dudaran ni un segundo en matarte.", this->area_juego));
		intro_juego->Add(gcnew CDialogo("Te deseamos suerte en tu viaje,\ny te apoyamos en el camino de Zion hacia la libertad.", this->area_juego));
		this->introjuego = gcnew CDialogos(intro_juego, gcnew CGrafico("Imagenes\\prota_alliesUI.png", 382 * 2, 258 * 2),this->area_juego, this->tamanho_celda);

		/*List<String^ >^ instrucciones = gcnew List<String^>();
		instrucciones->Add("Instrucciones:");
		instrucciones->Add("Este es tu personaje");
		instrucciones->Add("Lo controlas usando las teclas direccionales");
		instrucciones->Add("Esta es tu barra de vida, inicias con *cantidad de vida* de vida");
		instrucciones->Add("La meta del juego es lograr atravesar el laberinto sin morir");
		instrucciones->Add("A lo largo del laberinto te podrás encontrar con tres tipos de personaje:");
		instrucciones->Add("ALIADOS:\nSon personajes que te ayudaran en tu viaje\ny te seguirán a lo largo de este dando su vida por la tuya.");
		instrucciones->Add("CORRUPTOS:\nEstan en tu contra, caminan a lo largo del mapa\ny cuando encuentran un aliado lo corrompen convirtiéndolos en corruptos");
		instrucciones->Add("ASESINOS:\ncuando encuentran un aliado lo asesinan y lo suplantan\ncambiando su aspecto, siendo iguales a los aliados.");
		instrucciones->Add("Interacción especial:\nUna vez los assassins son liberados, se generaran portales en distintas partes del laberinto,\nlo que permitirá un escape de cualquier situación de riesgo de forma segura");
		instrucciones->Add("A lo largo del mapa se han colocado balas, las cuales cargaran tu pistola,\nla que usarás para salir de las situaciones de alto riesgo haciendo frente al peligro.");
		instrucciones->Add("Eso es todo lo que debes saber para tu misión");
		instrucciones->Add("Te deseamos suerte en tu viaje y esperamos que acabes con la injustica de este mundo.");
		*/
		
		List<String^>^ chat_corrupt = gcnew List<String^>();
		List<String^>^ chat_assassin = gcnew List<String^>();
		chat_corrupt->Add("Corrupt:\nHemos fallado en detener al anticiudadano, necesitamos su ayuda.");
		chat_assassin->Add("Assassin:\nEsta bien, aniquilará al rebelde, pero les saldrá caro.");
		chat_corrupt->Add("Corrupt:\nTodo sea para eliminar a esa escoria.");
		chat_assassin->Add("Assassin:\nHecho.");
		chat_alianza = gcnew CChat(gcnew CGrafico("Imagenes\\policia.png", Rectangle(10, 36, 40, 40), this->tamanho_celda, this->tamanho_celda),
			gcnew CGrafico("Imagenes\\asesino.png", Rectangle(10, 50, 40, 40), this->tamanho_celda, this->tamanho_celda),
			chat_corrupt, chat_assassin, this->area_juego,this->tamanho_celda);

		gameover = gcnew CDialogo("No nos privaran de la libertad\nVAMOS OTRA VEZ", this->area_juego);
		ganar = gcnew CDialogo("FELICIDADES\nPero este es solo el primer paso hacia la libertad", this->area_juego);

		String^ creditos_txt = "CRÉDITOS:\n\nDesarrollado por:\n";
		creditos_txt->Concat("Arte & Programación | Carolain Anto Chávez\n");
		creditos_txt->Concat("Arte & Programación | Julio Arturo Morón Campos\n");
		creditos_txt->Concat("Producción & Programación | Santiago Sebastian Heredia Orejuela\n");
		creditos_txt->Concat("Producción & Programación | Gabriel Omar Quispe Kobashikawa\n");
		creditos_txt->Concat("\nMÚSICA UTILIZADA : \n1.\n2.\n3.\n");
		creditos_txt->Concat("\nCURSO:\nProgramación II\n");
		creditos_txt->Concat("\nGracias especiales al profesor Ricardo Gonzales Valenzuela");
		creditos = gcnew CDialogo(creditos_txt, this->area_juego);
	}
};

