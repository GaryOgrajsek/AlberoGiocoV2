#pragma once
template <class tipo>
class Nodo {
private:
	tipo info;
	Nodo<tipo>* punt;

public:
	Nodo();
	Nodo(tipo);
	tipo getInfo();
	void setInfo(tipo);
	Nodo<tipo>* getPunt();
	void setPunt(Nodo<tipo>*);
	~Nodo();
};