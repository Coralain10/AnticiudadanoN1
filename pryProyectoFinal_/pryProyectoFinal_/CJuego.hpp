#pragma once
#include "CGrafico.hpp"
#include "CDialogos.hpp"
#include "CLaberinto.hpp"
#include "CEntidad.hpp"
#include "CProtagonista.hpp"
#include "CNPC.hpp"
#include <string>
#include <time.h>

using namespace System::Collections::Generic;
using namespace std;

ref class CConfiguracion {
private:
	short aliados_cant, asesinos_cant, corruptos_cant, cant_vidas,portales_cant;

public:
	unsigned int ts_total, ts_actual, ts_alianza;
	short aliados_rvision, asesinos_rvision, corruptos_rvision;
	int t_aliados_seguir, t_asesinos_ataque, t_corruptos_corrupcion;

	CConfiguracion() {
		//cargando valores por default
		this->ts_total = 200; //Son 20 segundos
		this->ts_actual = 0;
		this->ts_alianza =100; //son 10 segundos
		this->aliados_cant = 4;
		this->asesinos_cant = (short)(aliados_cant * 0.6);
		this->corruptos_cant = (short)(aliados_cant * 0.4);
		this->aliados_rvision = this->asesinos_rvision = this->corruptos_rvision = 2;
		this->t_aliados_seguir = t_asesinos_ataque = t_corruptos_corrupcion;
		this->cant_vidas =3;
		this->portales_cant = 4;
	}
	~CConfiguracion() {}
	void set_vidas(int value) { this->cant_vidas = value; }
	void set_cant_vidas(int value) { this->cant_vidas += value; } //para restar vidas en la colision
	short get_cant_vidas() { return this->cant_vidas; }
	void set_aliados_cant(short cantidad) {
		this->aliados_cant = cantidad;
		this->asesinos_cant = (short)(cantidad * 0.6);
		this->corruptos_cant = (short)(cantidad * 0.4);
	}
	short get_aliados_cant() { return this->aliados_cant; }
	short get_corruptos_cant() { return this->corruptos_cant; }
	short get_asesinos_cant() { return this->asesinos_cant; }
	short get_portales_cant() { return this->portales_cant; }
	short set_t_to_s(unsigned int t) { return t * 10; }

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
	System::Drawing::Rectangle area;
public:
	CMenu(short tamanho_celda, System::Drawing::Rectangle area, Font^ tipografia): tipografia(tipografia), area(area){
		this->bg_botones = gcnew Bitmap("Imagenes\\buttons.png");
		this->fondo = gcnew Bitmap("Imagenes\\fondoUI.png");
		this->logo = gcnew CGrafico("Imagenes\\logo.png", 360 * 2, 110 * 2);
		this->logo->escalar(2);
		this->letrero = gcnew Bitmap("Imagenes\\zion_letrero.png");
		this->ui_personaje = gcnew CGrafico("Imagenes\\protaUI.png", (area.Width - 4 * tamanho_celda), 0, 1392, 1080);
		this->btn_comenzar = gcnew CGrafico(bg_botones, System::Drawing::Rectangle(0, 0, 160, 160), tamanho_celda * 2, area.Height - 8 * tamanho_celda, tamanho_celda * 10, tamanho_celda * 2);
		this->btn_configurar = gcnew CGrafico(bg_botones, System::Drawing::Rectangle(0, 160, 160, 160), tamanho_celda * 2, area.Height - 4 * tamanho_celda, tamanho_celda * 14, tamanho_celda * 2);
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
	System::Drawing::Rectangle area_juego;
	Font^ tipografia;

	CMenu^ menu;
	CConfiguracion^ config;
	
	CDialogos^ intro0;
	CDialogos^ introjuego;
	CChat^ chat_alianza;
	CDialogo^ splash_conspiracion;
	CDialogo^ gameover;
	CDialogo^ ganar;
	CDialogo^ creditos;

	CGrafico^ cursor;
	CGrafico^ btn_cerrar;

	CGrafico^ btn_creditos;
	CGrafico^ btn_reiniciar;
	CLaberinto^ laberinto;
	List<CAliado^>^ aliados;
	List<CCorrupto^>^ corruptos;
	List<CAsesino^>^ asesinos;
	List<CPortal^>^ portales;
	CProtagonista^ protagonista;

	bool inicio_juego;
	bool ha_ganado;
	bool ha_perdido;

	int cooldown;
public:
	CJuego(short tamanho_celda, System::Drawing::Rectangle area): tamanho_celda(tamanho_celda), area_juego(area) {
		this->tipografia = gcnew System::Drawing::Font("Courier new", tamanho_celda * 0.75);
		this->menu = gcnew CMenu(this->tamanho_celda, this->area_juego, this->tipografia);
		this->config = gcnew CConfiguracion();
		set_intro0();
		this->cursor = gcnew CGrafico("Imagenes\\mouse.png", 32, 32);
		this->btn_cerrar = gcnew CGrafico("Imagenes\\cerrar.png", (short)(area.Width - 2.5 * tamanho_celda), tamanho_celda, (short)(tamanho_celda * 1.5), (short)(tamanho_celda * 1.5));
		this->btn_creditos = gcnew CGrafico("Imagenes\\buttons.png", System::Drawing::Rectangle(160, 160, 160, 160), tamanho_celda * 8, tamanho_celda*2);
		this->btn_creditos->set_ubicacion(area.Width/2 - tamanho_celda*2, area.Height - (4*tamanho_celda));
		this->btn_reiniciar = gcnew CGrafico("Imagenes\\reiniciar.png", (area.Width - 5 * tamanho_celda), tamanho_celda, (short)(tamanho_celda * 1.5), (short)(tamanho_celda * 1.5));
		this->laberinto = gcnew CLaberinto((short)(area.Width / tamanho_celda), (short)(area.Height / tamanho_celda), tamanho_celda);
		this->aliados = gcnew List<CAliado^>();
		this->corruptos = gcnew List<CCorrupto^>();
		this->asesinos = gcnew List<CAsesino^>();
		this->portales = gcnew List<CPortal^>();
		this->protagonista = gcnew CProtagonista(System::Drawing::Rectangle(this->laberinto->get_pos_entrada().X * tamanho_celda, this->laberinto->get_pos_entrada().Y * tamanho_celda, tamanho_celda*0.75, tamanho_celda), System::Drawing::Rectangle(0, 0, 0, 0), 4, 4,tamanho_celda);
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
		this->config->ts_actual = 0;
		this->inicio_juego = true;
		for (short i = 0; i < this->config->get_aliados_cant(); i++) {
			Point aux;
			if (i < 2) {
				aux= this->laberinto->pos_cerca(Point(this->protagonista->get_x()/tamanho_celda, this->protagonista->get_y() / tamanho_celda), 5);
			}
			else{
				aux = this->laberinto->pos_lejos(Point(this->protagonista->get_x() / tamanho_celda, this->protagonista->get_y() / tamanho_celda), 5);
			}
			aux.X *= tamanho_celda ;
			aux.Y *= tamanho_celda ;
			this->aliados->Add(gcnew CAliado(System::Drawing::Rectangle(aux.X, aux.Y, tamanho_celda, tamanho_celda), System::Drawing::Rectangle(0, 0, 0, 0), 4, 4,tamanho_celda));
			
		}
		for (short i = 0; i < this->config->get_corruptos_cant(); i++) {
			this->corruptos->Add(gcnew CCorrupto("Imagenes\\policia.png", System::Drawing::Rectangle(rand()%500, rand()%500, tamanho_celda, tamanho_celda), 
				System::Drawing::Rectangle(0, 0, 0, 0), 4, 4,tamanho_celda, rand() % 2, rand() % 2));
		}

		for (short i = 0; i < this->config->get_asesinos_cant(); i++) {
			Point aux;
			if (i < 2) {
				aux = this->laberinto->pos_cerca(Point(this->protagonista->get_x() / tamanho_celda, this->protagonista->get_y() / tamanho_celda), 5);
			}
			else {
				aux = this->laberinto->pos_lejos(Point(this->protagonista->get_x() / tamanho_celda, this->protagonista->get_y() / tamanho_celda), 5);
			}
			aux.X *= tamanho_celda;
			aux.Y *= tamanho_celda;
			this->asesinos->Add(gcnew CAsesino(System::Drawing::Rectangle(aux.X, aux.Y, tamanho_celda, tamanho_celda), System::Drawing::Rectangle(0, 0, 0, 0), 4, 4, tamanho_celda));

		}
		for (short i = 0; i < this->config->get_portales_cant(); i++) {
			this->portales->Add(gcnew CPortal(System::Drawing::Rectangle(rand() % 500, rand() % 500, tamanho_celda, tamanho_celda), System::Drawing::Rectangle(0, 0, 0, 0), 4, 4, tamanho_celda));
		}
	}
	void interactuar(Direccion direccion) {
		this->ha_ganado = this->protagonista->gano(direccion, this->laberinto);
	}
	void jugar(Graphics ^g) {
		this->config->ts_actual++;
		this->protagonista->MostrarVidas(this->config->get_cant_vidas(),g);
		this->protagonista->dibujarSprite(g);
		mover_aliados();
		for each (CAliado ^ aliado in aliados) {
			aliado->dibujarSprite(g);
		}

		for each (CCorrupto ^ corrupt in corruptos) {
			corrupt->mover_auto((short)this->config->ts_actual % 35 / 10, this->laberinto);
			corrupt->dibujarSprite(g);
			if (protagonista->hay_colision(corrupt)&&clock()-cooldown>=2000) {
						this->config->set_cant_vidas(-1);
						cooldown = clock();
			}
		}

		if (this->aumentar_dificultad() == true) {
			mover_asesinos();
			for each (CAsesino ^ asesino in asesinos) {
				asesino->dibujarSprite(g);
			}
			for each (CPortal ^ portal in portales) {
				portal->dibujarSprite(g);
			}
		}
		
	}
	
	void reiniciar_lab() {
		delete this->laberinto;
		this->laberinto = gcnew CLaberinto((short)(area_juego.Width / tamanho_celda), (short)(area_juego.Height / tamanho_celda), tamanho_celda);

		if (this->ganar != nullptr)
			remove_ganar();
		if (this->gameover != nullptr)
			remove_ganar();
		if (this->creditos != nullptr)
			remove_creditos();
		for (short i = this->config->get_aliados_cant()-1; i > 0; i--){
			aliados->RemoveAt(i);
		}
		for (short i = this->config->get_corruptos_cant() - 1; i > 0; i--) {
			corruptos->RemoveAt(i);
		}	
		
		iniciar_juego();

	}

	bool aumentar_dificultad() {
		if (this->config->ts_actual >= this->config->ts_alianza)
			return true;
	}
	void mover_aliados() {
		for each (CAliado ^ aliado in aliados) {
			if (aliado->get_x() > protagonista->get_x())
			     aliado->mover(Direccion::Izquierda,laberinto);
			else if (aliado->get_x() < protagonista->get_x())
				aliado->mover(Direccion::Derecha, laberinto);

			if (aliado->get_y() > protagonista->get_y())
				aliado->mover(Direccion::Arriba, laberinto);
			else if (aliado->get_y() < protagonista->get_y())
				aliado->mover(Direccion::Abajo, laberinto);
		}
	}
	void mover_asesinos() {
		for each (CAsesino ^ asesino in asesinos) {
			if (asesino->get_x() > protagonista->get_x())
				asesino->mover(Direccion::Izquierda, laberinto);
			else if (asesino->get_x() < protagonista->get_x())
				asesino->mover(Direccion::Derecha, laberinto);

			if (asesino->get_y() > protagonista->get_y())
				asesino->mover(Direccion::Arriba, laberinto);
			else if (asesino->get_y() < protagonista->get_y())
				asesino->mover(Direccion::Abajo, laberinto);
		}

	}
	bool es_fin_juego() {
		if (this->config->ts_actual == this->config->ts_total)
			return true;
	}

	CConfiguracion^ get_config() { return this->config; }
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
	CGrafico^ get_btn_creditos() { return this->btn_creditos; }
	CGrafico^ get_cursor() { return this->cursor; }
	Font^ get_fuente() { return this->tipografia; }
	bool juego_esta_iniciado() { return this->inicio_juego; }
	bool get_ha_ganado() { return this->ha_ganado; }

	//DIALOGOS

	void set_introjuego() {
		List<CDialogo^>^ intro_juego = gcnew List<CDialogo^>();
		intro_juego->Add(gcnew CDialogo("¡¡¡CUIDADO!!!\n\nHan sido liberados los \"corruptos\",\nquienes van a ir buscando a tus aliados\ny los irán corrompiendo uno por uno.", this->area_juego));
		intro_juego->Add(gcnew CDialogo("Recuerda que mientras más tardes en salir,\nlos \"corruptos\" pueden ir cerrando tratos con los \"asesinos\",\ndespiadados seres que no dudaran ni un segundo en matarte.", this->area_juego));
		intro_juego->Add(gcnew CDialogo("Te deseamos suerte en tu viaje,\ny te apoyamos en el camino de Zion hacia la libertad.", this->area_juego));
		this->introjuego = gcnew CDialogos(intro_juego, gcnew CGrafico("Imagenes\\prota_alliesUI.png", 382 * 2, 258 * 2), this->area_juego, this->tamanho_celda);
	}

	void set_chat() {
		List<String^>^ chat_corrupt = gcnew List<String^>();
		List<String^>^ chat_assassin = gcnew List<String^>();
		chat_corrupt->Add("Corrupt:\nHemos fallado en detener al anticiudadano,\nnecesitamos su ayuda.");
		chat_assassin->Add("Assassin:\nEsta bien, aniquilaré al rebelde,\npero les saldrá caro.");
		chat_corrupt->Add("Corrupt:\nTodo sea para eliminar a esa escoria.");
		chat_assassin->Add("Assassin:\nHecho.");
		chat_alianza = gcnew CChat(gcnew CGrafico("Imagenes\\policia.png", System::Drawing::Rectangle(10, 36, 40, 40), this->tamanho_celda, this->tamanho_celda),
			gcnew CGrafico("Imagenes\\asesino.png", System::Drawing::Rectangle(10, 50, 40, 40), this->tamanho_celda, this->tamanho_celda),
			chat_corrupt, chat_assassin, this->area_juego, this->tamanho_celda);
	}
	void set_splash_conspiracion(Graphics^ graficador) {
		CGrafico^ img_conspiracion = gcnew CGrafico("Imagenes\\corrupt_assasinUI.png", 416 * 2, 259 * 2);
		splash_conspiracion = gcnew CDialogo("Conspiracion realizada", this->area_juego, img_conspiracion);
		this->splash_conspiracion->dibujar_fondo(graficador);
		this->splash_conspiracion->dibujar_dialogo(graficador);
	}

	void set_gameover() {
		gameover = gcnew CDialogo("No nos privaran de la libertad\nVAMOS OTRA VEZ", this->area_juego);
	}

	void set_ganar() {
		ganar = gcnew CDialogo("FELICIDADES\nPero este es solo el primer paso hacia la libertad", this->area_juego);
	}
	void dibujar_btn_creditos(Graphics^ graficador) {
		this->btn_creditos->dibujar(graficador);
		graficador->DrawString("Creditos", this->tipografia, Brushes::White, btn_creditos->get_x() + (btn_creditos->get_ancho() / 4), btn_creditos->get_y() + (btn_creditos->get_alto() / 4));
	}
	void dibujar_creditos(Graphics^ graficador) {
		graficador->Clear(System::Drawing::Color::Black);
		//this->creditos->dibujar_fondo(graficador);
		this->creditos->dibujar_dialogo(graficador);
		this->btn_reiniciar->dibujar(graficador);
		pintar_ui(graficador);
	}
	void set_creditos() {
		std::string creditos_txt = "CRÉDITOS:\n\nDesarrollado por:\n";
		creditos_txt+= "Arte & Programación | Carolain Anto Chávez\n";
		creditos_txt += "Arte & Programación | Julio Arturo Morón Campos\n";
		creditos_txt += "Producción & Programación | Santiago Sebastian Heredia Orejuela\n";
		creditos_txt += "Producción & Programación | Gabriel Omar Quispe Kobashikawa\n";
		creditos_txt += "\nMÚSICA UTILIZADA : \n1.Halo 3: ODST - Rain (8Bit Remix)(https:\//www.youtube.com/watch?v=1s0VviYG_GU)\n2.Mega Man (NES) Music - Ice Man Stage(https:\//www.youtube.com/watch?v=CUZlDht8iro&list=PL7EF_qp0zBDmKNoUhxqH7qwDOg_mcmLR4&index=5)\n";
		creditos_txt += "\nCURSO:\nProgramación II\n";
		creditos_txt += "\nGracias especiales al profesor Ricardo Gonzales Valenzuela";
		creditos = gcnew CDialogo(gcnew String(creditos_txt.c_str()), this->area_juego);
	}

	void remove_intro0() { delete this->intro0; this->intro0 = nullptr; }
	void remove_introjuego() { delete this->introjuego; this->introjuego = nullptr; }
	void remove_chat() { delete this->chat_alianza; this->chat_alianza = nullptr; }
	void remove_splash_conspiracion() { delete this->splash_conspiracion; this->splash_conspiracion = nullptr;}
	void remove_gameover() { delete this->gameover; this->gameover = nullptr; }
	void remove_ganar() { delete this->ganar; this->ganar = nullptr; }
	void remove_creditos() { delete this->creditos; this->creditos = nullptr; }

private:
	void set_intro0() {
		List<CDialogo^>^ intro_descrip = gcnew List<CDialogo^>();
		intro_descrip->Add(gcnew CDialogo("Existe un mundo llamado Zion\nque se encuentra regido por un grupo de personas de gran poder,\nquienes han establecido una dictadura total\ndonde ningún ciudadano tiene voz ni voto,\ny son atormentados constantemente\ncon tal de que se mantengan volubles ante la tiranía del grupo.", this->area_juego));
		intro_descrip->Add(gcnew CDialogo("Pero hay algo que este grupo de dictadores ignora,\nes que durante años,se ha ido formando en silencio una rebelión,\ncon el propósito de liberar a todos los pueblos\ny alcanzar la armonía que una vez existió Zion,\ny que ahora solo vive en la memoria de los más viejos.", this->area_juego));
		intro_descrip->Add(gcnew CDialogo("El líder de este grupo de rebeldes\nha estado viviendo por mucho tiempo en el grupo privilegiado,\nbuscando alcanzar los altos mandos.\n\nDespués de años de soportar ver maltratos hacia su pueblo,\npor fin está listo para actuar.", this->area_juego));
		intro_descrip->Add(gcnew CDialogo("Durante su estancia\nrecopiló información acerca de los mundos adyacentes a Zion,\ny encontró uno con el que puede contar\npara la liberación de su pueblo.\n\nPero para ello debe salir de Zion personalmente,\nrenunciando así a su posición como gobernante\ny siendo declarado como\n\"ANITICIUDADANO\"", this->area_juego));
		intro0 = gcnew CDialogos(intro_descrip, this->area_juego);
	}

	/*void set_instrucciones() {
		List<String^ >^ instrucciones = gcnew List<String^>();
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
		
	}*/
};

