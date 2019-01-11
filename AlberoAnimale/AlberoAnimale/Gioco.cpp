#include "Gioco.h"
using namespace std;

Gioco::Gioco(){}

/*Quando l'utente avvia il programma, viene mostrato il menù che permette
di giocare o uscire salvando, o non, l'albero*/
int Gioco::Menu() {
	int scelta;
	cout << "1) Gioca" << endl;
	cout << "2) Esci salvando l'albero" << endl;
	cout << "3) Esci senza salvare" << endl;
	cout << endl;
	do {
		cin >> scelta;
	} while (scelta < 1 || scelta > 3); //controllo scelta

	return scelta;
}

/*Crea un albero base che chiede se l'animale vola. Se sì, restituisce piccione,
altrimenti restituisce gatto*/
void Gioco::Inizializza() {
	ifstream file("Albero.txt");
	if (file.good()) { //se esiste il file, lo carica, sennò crea l'albero
		T=Carica();
		RichiestaAnimale(T);
	}
	else {
		if (!giaCarico) {
			AlberoGioco.InserisciRicorsivo("Vola?");
			T = AlberoGioco.getT();
			NodoAlbero<string>* t1 = new NodoAlbero<string>("Gatto");
			NodoAlbero<string>* t2 = new NodoAlbero<string>("Piccione");
			T->SetLeftLink(t1);
			T->SetRightLink(t2);
			giaCarico = true;
		}
		RichiestaAnimale(T);
	}
}

/*Funzione per richiedere l'animale */
void Gioco::RichiestaAnimale(NodoAlbero<string>* T) {
	int risposta; //contiene il codice numerico 1 o 2
	cout << T->GetInfo() << endl;
	cout << "1) SI 2) NO ";
	do {
		cin >> risposta;
	} while (risposta < 1 || risposta>2); //controllo risposta

	//Se siamo ad un nodo foglia, dobbiamo visualizzare l'animale e controllare se è giusto.
	if (T->GetLeftLink() == T->GetRightLink()) {
		ControlloAnimale(risposta, T);
	}
	else { //Se NON siamo ad un nodo foglia dobbiamo andare a sinistra se la risposta alla domanda è no,
		   //altrimenti a destra 
		if (risposta == 1) {
			RichiestaAnimale(T->GetRightLink());
		}
		else {
			RichiestaAnimale(T->GetLeftLink());
		}
	}
}

/*In questa funzione viene inserito il nuovo animale*/
void Gioco::ModificaAnimale(string diverso, NodoAlbero<string>* T) {
	string temp = T->GetInfo(); //stringa che contiene l'animale precedentemente nel nodo foglia
	string newAnimale; //contiene il nuovo animale chiesto successivamente
	cout << "Quale e' l'animale nuovo? ";
	cin >> newAnimale;
	NodoAlbero<string>* t1 = new NodoAlbero<string>(temp); //Nodo con il "vecchio" animale
	NodoAlbero<string>* t2 = new NodoAlbero<string>(newAnimale); //Nodo con il "nuovo" animale
	T->SetInfo(diverso); //settato nel nodo foglia la nuova domanda
	T->SetLeftLink(t1); //settato a sinistra il vecchio animale
	T->SetRightLink(t2); //settato a destra il nuovo animale
}

/*Arrivati al nodo foglia, l'utente ha deciso se l'animale mostrato è quello che voleva o no.
Se è quello corretto, verrà solamente mostrata la scritta che annuncia la fine del gioco, altrimenti
viene richiesta la nuova domanda da fare. In un'altra funzione, viene definito anche l'animale.*/
void Gioco::ControlloAnimale(int risposta, NodoAlbero<string>* T) {
	if (risposta == 2) {
		string diverso;
		cout << "Che domanda bisogna fare, allora? ";
		cin.ignore();
		getline(cin, diverso);
		ModificaAnimale(diverso, T);
	}
	cout << "Termine del gioco"<<endl;
}

/*Avvia la funzione dell'albero converti per avere l'albero con le parentesi*/
string Gioco::Converti() {
	return AlberoGioco.Converti();
}

/*Salva in un file la conversione dell'albero con le parentesi*/
void Gioco::Salva() {
	ofstream file("Albero.txt");
	file << AlberoGioco.Converti();
	file.close();
}

/*Inserisce in una stringa il file, poi ottiene l'indice del nodo madre
e infine costruisce l'albero*/
NodoAlbero<string>* Gioco::Carica() {
	ifstream file("Albero.txt");
	string alberoStringa = "";
	if (file.is_open()) { //apre il file
		while (getline(file, alberoStringa)) {
			cout << "LOADING";
		}
		cout << endl;
	}
	return CostruisciAlbero(alberoStringa);
}

/*string Gioco::DividiStringa(string vecchiaStringa) {
	int indice = 0, old;
	Coda<string> alberoCoda;
	string ciao[1000];
	while (indice < vecchiaStringa.length()) {
		if (to_string(vecchiaStringa[indice]) == "(" || to_string(vecchiaStringa[indice]) == ")") {
			alberoCoda.Inserisci(to_string(vecchiaStringa[indice]));
			indice++;
		}
		else {
			old = indice;
			while (to_string(vecchiaStringa[indice]) != "?") {
				indice++;
			}
			alberoCoda.Inserisci(vecchiaStringa.substr(old, ++indice));
		}
	}
	Nodo<string>* L = alberoCoda.getL();
	int indice = 0;
	while(L!=0) {
		ciao[indice] = L->getInfo();
		L = L->getPunt();
	}
	return ciao;
}*/

/*Costruisce l'albero a partire dalla visualizzazione con le parentesi. AlberoStringa è la visualizzazione
si è l'indice iniziale della stringa o sottostringa presa in considerazione ed ei l'indice finale*/
NodoAlbero<string>* Gioco::CostruisciAlbero(string str){
	int lastChar = str.find("(");
	NodoAlbero<string>* root = new NodoAlbero<string>(str.substr(0, lastChar));
	int posizionevirgola=str.find_last_of(",");
	if (to_string(str[lastChar + 2]) != ")") {
		int index = indiceVirgola(str);

		root->SetLeftLink(CostruisciAlbero(str.substr((lastChar + 2), index-1)));
		root->SetRightLink(CostruisciAlbero(str.substr((posizionevirgola + 1), (str.find_last_of(")")))));
	}
	return root;
}

int Gioco::indiceVirgola(string str) {
	int counter = 0;
	for (int i = 0; i < str.length(); i++) {
		if (str[i] == ',') {
			counter++;
		}
	}
	counter = counter / 2;
	int mine = 0;
	for (int i = 0; i < str.length(); i++) {
		if (str[i] == ',') {
			mine++;
			if (mine == counter) {
				return i;
			}
		}
	}
}

/*
int Gioco::findClosingParen(string text, int openPos) {
	int closePos = openPos;
	int counter = 1;
	while (counter > 0) {
		char c = text[++closePos];
		if (c == '(') {
			counter++;
		}
		else if (c == ')') {
			counter--;
		}
	}
	return closePos;
}

int Gioco::TrovaIndice(string str, int si, int ei) {
	if (si > ei) {
		return -1;
	}

	// Inbuilt stack 
	stack<char> s;

	for (int i = si; i <= ei; i++) {

		// if open parenthesis, push it 
		if (str[i] == '(')
			s.push(str[i]);

		// if close parenthesis 
		else if (str[i] == ')') {
			if (s.top() == '(') {
				s.pop();

				// if stack is empty, this is  
				// the required index 
				if (s.empty())
					return i;
			}
		}
	}
	// if not found return -1 
	return -1;
}
*/
Gioco::~Gioco(){}
