#include "Coda.h"
#include<iostream>
using namespace std;

template <class tipo>
Coda<tipo>::Coda() {
	L = 0; //se la lista è nuova, L non punta a niente.
}

template <class tipo>
void Coda<tipo>::Inserisci(tipo x) { //in coda
	Nodo<tipo> *p = L;
	Nodo<tipo> *temp = new Nodo<tipo>(x);

	if (L != 0) {
		while (p->getPunt() != 0) {
			p = p->getPunt();
		}

		p->setPunt(temp);
		temp->setPunt(0);
	}
	else
		L = temp;
}

template <class tipo>
void Coda<tipo>::Visualizza() {
	Nodo<tipo> *P = L;
	while (P != 0) { //così sennò non visualizza l'ultimo. E supera l'ultimo.
		cout << P->getInfo();
		P = P->getPunt();
	}
}

template <class tipo>
void Coda<tipo>::Elimina() {
	Nodo<tipo> *P = L;
	if (P->getPunt() != 0) {
		L = P->getPunt();
		delete P;
	}
}

template <class tipo>
void Coda<tipo>::Modifica(tipo prima, tipo dopo) {
	Nodo<tipo> *p;
	p = L;
	if (L != 0) {
		while (p != 0) {
			if (p->getInfo() == prima) {
				p->setInfo(dopo);
				break;
			}
			else {
				p = p->getPunt();
			}
		}
	}
}

template <class tipo>
Nodo<tipo>* Coda<tipo>::Ricerca(tipo x) {
	Nodo<tipo> *succ, *prec;
	succ = L;
	prec = NULL;
	if (L == 0) {
		cout << "Coda vuota.";
	}
	else {
		while (succ != 0 && succ->getInfo() != x) {
			prec = succ;
			succ = succ->getPunt();
		}
		return prec;
	}
}

template <class tipo>
void Coda<tipo>::Inverti() {
	Nodo<tipo> *succ = L;
	Nodo<tipo> *prec = 0;
	Nodo<tipo> *tmp = NULL;
	while (succ != 0) {
		tmp = succ->getPunt();
		succ->setPunt(prec);
		L = succ;
		prec = succ;
		succ = tmp;
	}
}

template <class tipo>
Nodo<tipo>* Coda<tipo>::getL() {
	return L;
}

template <class tipo>
Coda<tipo>::~Coda() {
}