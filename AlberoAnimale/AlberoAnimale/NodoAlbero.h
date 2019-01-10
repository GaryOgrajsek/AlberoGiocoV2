#pragma once
template<class tipo>
class NodoAlbero {
private:
	tipo info;
	NodoAlbero<tipo>* leftLink, *rightLink;

public:
	NodoAlbero();
	NodoAlbero(tipo);
	tipo GetInfo();
	NodoAlbero<tipo>* GetLeftLink();
	NodoAlbero<tipo>* GetRightLink();
	void SetInfo(tipo);
	void SetLeftLink(NodoAlbero<tipo>*);
	void SetRightLink(NodoAlbero<tipo>*);
	~NodoAlbero();
};
