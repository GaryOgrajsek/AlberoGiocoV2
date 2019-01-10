#pragma once
#include"Nodo.h"
template<class tipo>
class Coda {
private:
	Nodo<tipo> * L;
public:
	Coda();
	void Inserisci(tipo);
	void Modifica(tipo, tipo);
	Nodo<tipo> * Ricerca(tipo); //	ricerca un dato e restituisce il puntatore al nodo precedente quello che contiene il dato cercato
	void Visualizza();
	void Elimina();
	void Inverti();
	Nodo<tipo>* getL();
	~Coda();
};