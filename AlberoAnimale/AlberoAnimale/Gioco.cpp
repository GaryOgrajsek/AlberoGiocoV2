#include "Gioco.h"
#include <stack>
#include<cstring>
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
	Coda<string> alberoCoda;
	ifstream file("Albero.txt");
	string alberoStringa = "";
	if (file.is_open()) { //apre il file
		while (getline(file, alberoStringa)) {
			cout << "LOADING";
		}
		cout << endl;
	}
	return CostruisciAlbero(DividiStringa(alberoStringa, alberoCoda));
}

Nodo<string>* Gioco::DividiStringa(string vecchiaStringa, Coda<string> alberoCoda) {
	int indice = 0, old;
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
	
	return alberoCoda.getL();
}

/*Costruisce l'albero a partire dalla visualizzazione con le parentesi. AlberoStringa è la visualizzazione
si è l'indice iniziale della stringa o sottostringa presa in considerazione ed ei l'indice finale*/
NodoAlbero<string>* Gioco::CostruisciAlbero(Nodo<string>* L) {
	
	//Se siamo arrivati ad un nodo foglia, si restituisce nullpointer
	if (L==nullptr) {
		return nullptr;
	}

	//Viene creato il nodo a cui viene assegnata 
	NodoAlbero<string>* root = new NodoAlbero<string>(L->getInfo());
	int index = -1;

	// if next char is '(' find the index of 
	// its complement ')' 
	if (L->getPunt() != nullptr && (L->getPunt())->getInfo() == "(");
		index = TrovaIndice(L);

	// if index found 
	if (index != -1) {

		// call for left subtree 
		root->SetLeftLink(CostruisciAlbero(L));

		// call for right subtree 
		root->SetRightLink(CostruisciAlbero(L);
	}
	return root;
}

int Gioco::TrovaIndice(Nodo<string>* L) {
	if (L == nullptr) {
		return -1;
	}

	// Inbuilt stack 
	stack<string> s;

	Nodo<string>* temp = L;
	while(
	for (int i = si; i <= ei; i++) {

		// if open parenthesis, push it 
		if (alberoStringa[i] == '(') {
			s.push(to_string(alberoStringa[i]));
		}

		// if close parenthesis 
		else if (alberoStringa[i] == ')') {
			if (s.top() == to_string('(')) {
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

Gioco::~Gioco(){}
