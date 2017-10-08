#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
using namespace std;

typedef enum { NADIE, MAQUINA, JUGADOR } tGanador; // DEFINE COMO 0, 1, 2 RESPECTIVAMENTE.

//prototipos

bool mostrar_reglas(string nombrearchivo); // OPCION 3
void juego(int numMonedas, int maxEleccion, int marcador);// OPCION 4.
int monedasHumano(int numMonedas); // MONEDAS QUE SACA EL JUGADOR.
int apuestaHumano(int apuestasMaquina, int monedasHumano, int maxEleccion); // APUESTA QUE SACA EL JUGADOR.
int monedasMaquina(int numMonedas); // MONEDAS QUE SACA LA MAQUINA.
int apuestaMaquina(int monedasMaquina, int numMonedas); // APUESTA QUE SACA LA MAQUINA.
int quienGana(int monedaMaquina, int monedaHumano, int apuestaMaquina, int apuestaHumano, int &marcadorJ, int &marcadorM);
int menu(); // MENU
int leer_entero(); // CONTROLA EL FLUJO DE ENTRADA DE DATOS, ASEGURA UN VALOR INTEGRO.
void pausa();


int main() {
		
	srand(time(NULL));
	int marcador = 2;
	int numMonedas = 3;
	{
		ifstream configuracion;
		configuracion.open("configP1.txt");
		if (configuracion.is_open()){
		configuracion >> marcador >> numMonedas;
		configuracion.close();
	}
		else cout << "No existe archivos de configuracion, se utilizaran los valores predeterminados" << endl << endl;
	}
	int maxEleccion = numMonedas * 2;
	int opcion = menu();
	while(opcion != 0){
	
		switch (opcion) {

		case 1: cout << "¿Cuantas partidas debe ganar el Vencedor?: ";
				marcador = leer_entero();
				while(marcador <= 0) {
					cout << "No seas gallina, ahora enserio, cuantas: ";
					marcador = leer_entero();
				
				}
				break;

		case 2: cout << "¿Cual es el maximo numero de monedas?: ";
				numMonedas = leer_entero();
				while (numMonedas <= 0) {
					cout << "No puedes jugar con tan pocas monedas, cuantas: ";
					numMonedas = leer_entero();
				}
				maxEleccion = numMonedas * 2;

				break;

		case 3: mostrar_reglas("reglas.txt");
				break;

		case 4:	juego(numMonedas,maxEleccion,marcador);
				break;
				
		}
		opcion = menu();
	}
	{
		ofstream configuracion;
		configuracion.open("configP1.txt");
		configuracion << marcador << endl << numMonedas;
	}
}

bool mostrar_reglas(string nombrearchivo) {

	bool existe = false;
	char c;
	ifstream archivo;
	archivo.open("reglas.txt");
	if (archivo.is_open()) {
		existe = true;
		archivo.get(c);
		while (!archivo.eof()) {
			cout << c;
			archivo.get(c);
		}
		archivo.close();
	}
	else {
		cout << "Error: Archivo reglas.txt no encontraado." << endl;
	}
	return existe;
	
}

void juego(int numMonedas, int maxEleccion, int marcador) {


	int marcadorJ = 0, marcadorM = 0;
	
	while (marcadorJ != marcador && marcadorM != marcador) {
		cout << endl << "BIENVENIDO AL JUEGO DE LOS CHINOS" << endl << endl;
		cout << "Recoge tus monedas: ";
		int monedaHumano = monedasHumano(numMonedas);
		cout << "Me TOCA!" << endl;
		int monedaMaquina = monedasMaquina(numMonedas);
		int apuestasMaquina = apuestaMaquina(monedaMaquina, numMonedas);
		cout << "Mi apuesta es: " << apuestaMaquina(monedaMaquina, numMonedas) << endl;
		cout << "Ahora realiza tu apuesta: ";
		int apuestasHumano = apuestaHumano(apuestasMaquina, monedaHumano, maxEleccion);
		quienGana(monedaMaquina, monedaHumano, apuestasMaquina, apuestasHumano, marcadorJ, marcadorM);
		pausa();
		system("cls");
	}
}

int monedasHumano(int numMonedas) {

	int numMonedasH = leer_entero() ;

	while (numMonedasH > numMonedas) {
		cout << "introduzca el numero de monedas [0-3]: ";
		numMonedasH = leer_entero();
	}

	return numMonedasH;
}

int apuestaHumano(int apuestasMaquina, int monedasHumano, int maxEleccion) {

	cout << "introduzca la apuesta: ";
	int apuestaHumano = leer_entero();

	while (apuestaHumano == apuestasMaquina || apuestaHumano > maxEleccion) {
		cout << "no se puede introducir el mismo numero que la maquina o un valor erroneo ,repite: ";
		apuestaHumano = leer_entero();
	}

	return apuestaHumano;

}

int monedasMaquina(int numMonedas) {

	
	int monedasMaquina = rand() % ( numMonedas + 1);
	
	return monedasMaquina;
}

int apuestaMaquina(int monedasMaquina, int numMonedas) { 

	
	int  apuestaMaquina = monedasMaquina + rand() % (numMonedas + 1 - monedasMaquina);

	return apuestaMaquina;
}

int quienGana(int monedaMaquina, int monedaHumano, int apuestaMaquina, int apuestaHumano, int &marcadorJ, int &marcadorM) {

	int	numMonedasT = monedaHumano + monedaMaquina;
	int ganador;

	if (apuestaMaquina == numMonedasT) {

		cout << "Ha ganado la maquina!" << endl;
		ganador = MAQUINA;
		marcadorM++;

	}
	else if (apuestaHumano == numMonedasT) {

		cout << "Has ganado ser humano!" << endl;
		ganador = JUGADOR;
		marcadorJ++;
	}
	else {
		cout << "No ha ganado nadie";
		ganador = NADIE;

	}
	return ganador;
}

int menu() {
	cout << "JUEGO DE LOS CHINOS!!!!!" << endl << endl;
	cout << endl << "1 - Cambiar el marcador" << endl;
	cout << "2 - Cambiar el numero de monedas" << endl;
	cout << "3 - Acerca del juego de los chinos" << endl;
	cout << "4 - Jugar una partida" << endl;
	cout << "5 - Jugar una partida automatica" << endl << endl;
	cout << "0 - Salir" << endl << endl;

	cout << "Opcion: ";
	return  leer_entero();
}

int leer_entero() {

	int n;
	cin >> n;

	while (cin.fail()) {

		cin.clear();
		cin.sync();
		cout << "introduce un valor entero: " << endl;
		cin >> n;

	}

	return n;
}

void pausa(){

	cin.sync();
	cout << endl << "pulsa intro para continuar";
	cin.get();

}




