// Proyecto 2.cpp: define el punto de entrada de la aplicación de consola.
//

#include "stdafx.h"
#include <iostream>
#include <conio.h>		
#include <math.h>
#include <stdio.h>
#include <time.h>	
#include <Windows.h>

using namespace std;

int tombola[99], num, Opcion, Num, Bingo = 0, h = 0;
char nombres[20][20] = { "Jesus", "Kevin", "Kevin G", "Alfonso", "Zarate", "Jose", "Frida", "Mauricio", "Isaac", "Jessica", "Marcelo", "Emmanuel", "Alan", "Franco", "Manuel", "Oscar", "Felipe", "Andres", "Isai", "Missa" };

struct Jugadores {
	char Nombre[20];
	int tabla[4][4];
	Jugadores *sig;
}*tab, *aux, *aux2;

void RegSt() {
	for (int i = 0; i <= 99; i++) {
		tombola[i] = i + 1;
	}
}
void Tombola() {
	srand(time(NULL));
	do {
		num = rand() % 99 + 1;
	} while (tombola[num - 1] == -1);
	tombola[num - 1] = -1;
}
void Cambio() {
	aux = tab;
	while (aux != NULL) {
		for (int y = 0; y < 4; y++) {
			for (int x = 0; x < 4; x++) {
				if (num == aux->tabla[x][y]) {
					aux->tabla[x][y] = -1;
				}
			}
		}
		aux = aux->sig;
	}
}
int Vacia() {
	if (tab == NULL) {
		return 1;
	}
	else {
		return 0;
	}
}
void Crear(char nombre[20]) {
	if (Vacia() == 1) {
		tab = new Jugadores;
		tab->sig = NULL;
		strcpy_s(tab->Nombre, nombre);
		//strcpy(tab->Nombre, nombre);
	}
	else {
		aux = new Jugadores;
		aux2 = tab;
		strcpy_s(aux->Nombre, nombre);
		//strcpy(tab->Nombre, nombre);
		while (aux2->sig != NULL) {
			aux2 = aux2->sig;
		}
		aux->sig = aux2->sig;
		aux2->sig = aux;
	}
}
void Check(int x, int y) {
	for (int z = 0; z <= y; z++) {
		for (int c = 0; c <= x; c++) {
			if (aux->tabla[x][y] == aux->tabla[c][z]) {
				aux->tabla[x][y] = 1 + rand() % (100 - 1);
			}
		}
	}
}
void Llenar() {
	aux = tab;
	srand(time(NULL));
	while (aux != NULL) {
		for (int y = 0; y < 4; y++) {
			for (int x = 0; x < 4; x++) {
				aux->tabla[x][y] = rand() % 99 + 1;
				Check(x, y);
			}
		}
		aux = aux->sig;
	}
}
void Imprimir() {
	aux = tab;
	while (aux != NULL) {
		cout << "Jugador: " << aux->Nombre << "" << endl;
		for (int y = 0; y < 4; y++) {
			for (int x = 0; x < 4; x++) {
				cout << aux->tabla[x][y] << " ";
				cout << " ";
				if (x == 3) cout << endl;
			}
		}
		aux = aux->sig;
	}
}
void bingo_horizontal() {
	for (int y = 0; y < 4; y++) {
		if ((aux2->tabla[0][y] == -1) && (aux2->tabla[1][y] == -1) && (aux2->tabla[2][y] == -1) && (aux2->tabla[3][y] == -1)) {
			Bingo = 1;
		}
	}
}
void bingo_diagonal() {
	if (((aux2->tabla[0][0] == -1) && (aux2->tabla[1][1] == -1) && (aux2->tabla[2][2] == -1) && (aux2->tabla[3][3] == -1)) || ((aux2->tabla[3][0] == -1) && (aux2->tabla[2][1] == -1) && (aux2->tabla[1][2] == -1) && (aux2->tabla[0][3] == -1))) {
		Bingo = 1;
	}
}
void bingo_vertical() {
	for (int x = 0; x < 4; x++) {
		if ((aux2->tabla[x][0] == -1) && (aux2->tabla[x][1] == -1) && (aux2->tabla[x][2] == -1) && (aux2->tabla[x][3] == -1)) {
			Bingo = 1;
		}
	}
}
void Reinicio() {
	if (tab->sig == NULL)
	{
		delete tab;
		tab = NULL;
	}
	else
	{
		aux = tab;
		while (aux != NULL) {
			aux = aux->sig;
			delete tab;
			tab = aux;
		}
	}
	tab = NULL;
}

int main() {
	char nombre[20];
	tab = NULL;
	do {
		num = 0;
		h = 0;
		Bingo = 0;
		system("cls");
		cout << "Elija la opcion que desee\n";
		cout << "\n\t1.-Jugar.\n\t2.-Salir.\n";
		cin >> Opcion;
		switch (Opcion) {
		case 1:
			system("cls");
			cout << "Elige la cantidad de jugadores: (entre 2 y 20)\n";
			cin >> Num;
			while (Num < 2 || Num > 20) {
				system("cls");
				cout << "Opcion invalida, porfavor elige de nuevo: ";
				cin >> Num;
			}
			for (int i = 1; i <= Num; i++) {
				strcpy_s(nombre, nombres[i - 1]);
				//strcpy(nombre, nombres[i - 1]);
				Crear(nombre);
				Llenar();
			}
			Imprimir();
			_getch();
			do {
				system("cls");
				aux2 = tab;
				RegSt();
				Tombola();
				cout << "Presiona una tecla para obtener el siguiente numero\n";
				cout << "Numero: [" << num << "]\n\n";
				Cambio();
				Imprimir();
				_getch();
				while (aux2 != NULL && Bingo != 1) {
					bingo_diagonal();
					bingo_horizontal();
					bingo_vertical();
					if (Bingo != 1) {
						aux2 = aux2->sig;
					}
				}
			} while (Bingo != 1);
			system("cls");
			cout << "\t!BINGO!\n\n";
			cout << "\tEl ganador es: " << aux2->Nombre;
			Reinicio();
			_getch();
			break;

		case 2:
			system("cls");
			cout << "Gracias por jugar.";
			_getch();
			break;

		default:
			system("cls");
			cout << "Opcion invalida";
			_getch();
			break;
		}
	} while (Opcion != 2);
	return 0;
}