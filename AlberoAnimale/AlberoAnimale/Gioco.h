#pragma once
#include "Albero.h"
#include "Albero.cpp"
#include <iostream>
#include<string>
#include<fstream>
using namespace std;

class Gioco{
private:
	Albero<string> AlberoGioco;
	NodoAlbero<string>* T;
	bool giaCarico;
	

public:
	Gioco();
	int Menu();
	void Inizializza();
	void RichiestaAnimale(NodoAlbero<string>*);
	void ControlloAnimale(int, NodoAlbero<string>*);
	void ModificaAnimale(string, NodoAlbero<string>*);
	string Converti();
	void Salva();
	NodoAlbero<string>* Carica();
	//int findClosingParen(string, int);
	int indiceVirgola(string);
	//int TrovaIndice(string, int, int);
	//string* DividiStringa(string);
	NodoAlbero<string>* CostruisciAlbero(string);
	~Gioco();
};
