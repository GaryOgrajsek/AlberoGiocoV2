#pragma once
#include "NodoAlbero.h"
#include "NodoAlbero.cpp"
#include<string>
using namespace std;
//postorder F D E B G C A  INORDER D F B E A G C
template <class tipo>
class Albero{
	friend bool AlberoUguale(Albero<tipo>, Albero<tipo>);
private:
	NodoAlbero<tipo>* T;
	NodoAlbero<tipo>* InserisciRicorsivo(tipo, NodoAlbero<tipo>*);
	void Preorder(NodoAlbero<tipo>*);
	void Inorder(NodoAlbero<tipo>*);
	void Postorder(NodoAlbero<tipo>*);
	int ContaNodi(int&, NodoAlbero<tipo>*);
	int ContaNodiFoglia(int&, NodoAlbero<tipo>*);
	bool Cerca(tipo, NodoAlbero<tipo>*);
	string Converti(string&, NodoAlbero<tipo>*);
	int ContaProfondita(NodoAlbero<tipo>*);
	void Uguale(NodoAlbero<tipo>*);

public:
	Albero();
	void Preorder();
	void Inorder();
	void Postorder();
	void InserisciIterativo(tipo);
	void InserisciRicorsivo(tipo);
	int ContaNodi();
	int ContaNodiFoglia();
	bool Cerca(tipo);
	void InserisciNnodi(int);
	string Converti();
	void operator =(Albero<tipo>);
	int ContaProfondita();
	NodoAlbero<tipo>* getT();
	~Albero();
};
