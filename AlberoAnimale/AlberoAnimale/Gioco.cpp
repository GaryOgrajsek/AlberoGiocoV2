#include "Gioco.h"
using namespace std;

/*Queste macro sono necessarie per poter caricare l'albero
Il loro significato è spiegato nella documentazione e, in breve
all'inizio della funzione "Carica"*/
#define primaSx (lastChar + 1)
#define ultimaSx (index-primaSx)
#define primaDx (index+1)
#define ultimaDx ((str.find_last_of(")")-1)-primaDx+1)

/*Costruttore*/
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
	if (!giaCarico) {
		if (file.good()) { //se esiste il file, lo carica, sennò crea l'albero
			T = Carica();
			giaCarico = true;
		}
		else {
			AlberoGioco.InserisciRicorsivo("Vola?");
			T = AlberoGioco.getT();
			NodoAlbero<string>* t1 = new NodoAlbero<string>("Gatto");
			NodoAlbero<string>* t2 = new NodoAlbero<string>("Piccione");
			T->SetLeftLink(t1);
			T->SetRightLink(t2);
			giaCarico = true;
		}
	}
	RichiestaAnimale(T);
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
	cout << "Termine del gioco"<<endl<<endl;
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
			system("CLS");
		}
	}
	return CostruisciAlbero(alberoStringa);
}

/*Costruisce l'albero a partire dalla visualizzazione con le parentesi. Il testo fino alla prima parentesi
aperta è l'elemento del nodo. Da due caratteri dopo la parentesi fino alla virgola è il nodo sx, quello dopo
la virgola fino alla parentesi chiusa finale è la parte dx (il funzionamento è meglio spiegato nella documentazione)*/
NodoAlbero<string>* Gioco::CostruisciAlbero(string str){
	int lastChar = str.find("(");
	NodoAlbero<string>* root = new NodoAlbero<string>(str.substr(0, lastChar));
	if (str[lastChar + 1] != ')') {
		int index = indiceVirgola(str);
		root->SetLeftLink(CostruisciAlbero(str.substr(primaSx, ultimaSx)));
		root->SetRightLink(CostruisciAlbero(str.substr(primaDx, ultimaDx)));
	}
	return root;
}

/*Per poter generare una sottostringa, è necessario sapere la posizione della virgola nella stringa.
Per far ciò, troveremo la posizione della seconda parentesi aperta e la sua corrispondente chiusa*/
int Gioco::indiceVirgola(string str) {
	//Contatore per determinare quando siamo arrivati alla fine
	int i = 1;

	//La posizione di fine sarà maggiore di quella di inizio (ovvero dove si trova la prima "(")
	int fine;
	
	//Per poter iniziare dalla 2^ parentesi, si trova la posizione della prima e poi la successiva
	//partendo da quest'ultima posizione
	int contaparentesi = str.find("(");
	int inizio = fine = (str.find("(", contaparentesi+1)+1);

	//Contatore per non sforare
	int k = 0;

	//Finché i sarà maggiore di zero, allora non siamo arrivati alla parentesi chiusa corrispondente
	while (k<=fine) {
		char c = str[fine++];

		//Se il carattere c è un'altra parentesi aperta, allora dobbiamo aumentare il contatore
		//in modo tale da "escluderla" dalla soluzione. Infatti, se non incrementassimo i, risulterebbe
		//la sua parentesi chiusa quella corretta.
		if (c == '(') {
			i++;
		}
		else if (c == ')') {
			i--;
		}
		if (i == 0) {
			break;
		}
		k++;
	}
	//Fine è ora la nostra posizione desiderata
	return fine;
}

/*Distruttore*/
Gioco::~Gioco(){}
