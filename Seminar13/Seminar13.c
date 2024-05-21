#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <malloc.h>

typedef struct Autobuz Autobuz;
struct Autobuz {
	int linie; //unic
	char* capat_linie;
};

typedef struct NodSecundar NodSecundar;


typedef struct NodPrincipal NodPrincipal;
struct NodPrincipal {
	Autobuz info;
	NodPrincipal* next;
	NodSecundar* vecini;
};

struct NodSecundar {
	NodPrincipal* nod;
	NodSecundar* next;
};

Autobuz autobuz_init(int linie, const char* capat_linie) {
	Autobuz a;

	a.linie = linie;
	a.capat_linie = (char*)malloc( sizeof(char) * (strlen(capat_linie) + 1) );
	strcpy(a.capat_linie, capat_linie);

	return a;
}

//fct inserare sfarsit in NodPrincipal
void graf_inserare_nod(NodPrincipal** graf, Autobuz autobuz) {
	NodPrincipal* nod = (NodPrincipal*)malloc(sizeof(NodPrincipal));
	nod->info = autobuz; //shallow
	nod->next = NULL;
	nod->vecini = NULL;


	if ((*graf)) {
		NodPrincipal* temp = *graf;
		while (temp->next) {
			temp = temp->next;
		}
		temp->next = nod;
	}
	else {
		*graf = nod;
	}
	

}


//fct cautare dupa linii in NodPrincipal
NodPrincipal* graf_cautare(NodPrincipal* graf, int linie) {
	while (graf && graf->info.linie != linie) {
		graf = graf->next;
	}
	return graf;
}

//fct inserare sfarsit in NodSecundar
NodSecundar* vecini_inserare(NodSecundar* cap, NodPrincipal* info) {
	NodSecundar* nou = (NodSecundar*)malloc(sizeof(NodSecundar));
	nou->next = NULL;
	nou->nod = info;

	if (cap) {
		NodSecundar* temp = cap;
		while (temp->next) {
			temp = temp->next;
		}
		temp->next = nou;
		return cap;
	}
	else {
		return nou;
	}
}

//fct inserare muchie (va insera adresa lui 2 in 1 si vice versa)
void graf_inserare_muchie(NodPrincipal* graf, int linie_start, int linie_stop) {
	NodPrincipal* nod_start = graf_cautare(graf, linie_start);
	NodPrincipal* nod_stop = graf_cautare(graf, linie_stop);

	nod_start->vecini = vecini_inserare(nod_start->vecini, nod_stop);
	nod_stop->vecini = vecini_inserare(nod_stop->vecini, nod_start);
}


void main() {
	NodPrincipal* graf = NULL;
	graf_inserare_nod(&graf, autobuz_init(0, "Romana"));
	graf_inserare_nod(&graf, autobuz_init(1, "Universitate"));
	graf_inserare_nod(&graf, autobuz_init(2, "Unirii"));
	graf_inserare_nod(&graf, autobuz_init(3, "Victoriei"));
	graf_inserare_nod(&graf, autobuz_init(4, "Militari"));

	//muchii
	graf_inserare_muchie(graf, 0, 1);
	graf_inserare_muchie(graf, 0, 4);
	graf_inserare_muchie(graf, 1, 2);
	graf_inserare_muchie(graf, 2, 4);
	graf_inserare_muchie(graf, 3, 4);
}