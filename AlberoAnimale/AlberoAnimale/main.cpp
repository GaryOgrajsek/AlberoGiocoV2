#include "Gioco.h"
int main() {
	Gioco Albero;
	cout << "INDOVINA L'ANIMALE" << endl;
	int scelta=0;
	do {
		switch (Albero.Menu()) {
		case 1:
			Albero.Inizializza();
			break;
		case 2:
			Albero.Salva();
			return 0;
		case 3:
			return 0;
		}
	} while (true);
}
