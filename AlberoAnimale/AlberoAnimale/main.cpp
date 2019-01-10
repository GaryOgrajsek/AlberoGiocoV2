#include "Gioco.h"
int main() {
	Gioco Albero;
	Albero.Inizializza();
	int scelta=0;
	do{
		switch (Albero.Menu()) {
		case 1:
			Albero.Inizializza();
			break;
		case 2:
			Albero.Salva();
			break;
		case 0:
			break;
		}
		cout << "Per continuare, digitare 0, altrimenti un altro tasto";
		cin >> scelta;
	}while(scelta==0);
	system("PAUSE");
	return 0;
}
