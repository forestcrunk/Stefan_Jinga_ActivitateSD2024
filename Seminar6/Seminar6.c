//toate functiile sunt facute recursiv

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <malloc.h>
#include <string.h>

typedef struct Santier Santier;
typedef struct NodLd NodLd;

struct Santier {
	char* nume_proiect;
	int nr_muncitori;
	float suprafata;
};

struct NodLd {
	Santier santier;
	NodLd* next;
	NodLd* prev;
};

typedef struct ListaDubla ListaDubla;
struct ListaDubla {
	NodLd* prim;
	NodLd* ultim;
};

Santier init_santier(const char* nume_proiect, int nr_muncitori, float suprafata) {
	Santier s;
	s.nume_proiect = (char*)malloc(strlen(nume_proiect) + 1);
	strcpy(s.nume_proiect, nume_proiect);
	s.nr_muncitori = nr_muncitori;
	s.suprafata = suprafata;

	return s;
}

void afisare_santier(Santier s) {
	/*if (s.nume_proiect != NULL) {
		printf("Denumire: %s\n", s.nume_proiect);
	}
	else printf("Denumire: -\n");
	printf("Numar muncitori: %d\n", s.nr_muncitori);
	printf("Suprafata: %.2f\n", s.suprafata);
	printf("\n");*/

	printf("Santierul \'%s\' are %d muncitori si %.2fmp suprafata.\n", s.nume_proiect, s.nr_muncitori, s.suprafata);
}



void stergere_santier(Santier* santier) {
	if (santier->nume_proiect != NULL) {
		free(santier->nume_proiect);
		santier->nume_proiect = NULL;
	}
}

float densitate_muncitori(Santier santier) {
	if (santier.suprafata > 0) 
		return santier.nr_muncitori / santier.suprafata;
	return 0;
}

void inserare_inceput(ListaDubla* lista, Santier s) {
	NodLd* aux = (NodLd*) malloc(sizeof(NodLd));
	aux->santier = s;
	aux->next = lista->prim;
	aux->prev = NULL;
	if (lista->prim != NULL) {
		lista->prim->prev = aux;
		//lista->prim = aux;
	}
	else {
		//lista->prim = aux;
		lista->ultim = aux;
	}
	lista->prim = aux;
}

void afisare_lista_first_to_last(ListaDubla lista) {
	for (NodLd* nod = lista.prim; nod != NULL; nod = nod->next) {
		afisare_santier(nod->santier);
	}
	printf("\n");
}

//stergere santier ce contine un nume dat
void lista_stergere_santier_nume(ListaDubla* lista, const char* nume) {
	NodLd* nod = lista->prim;
	
	while(nod!=NULL) {
		if (strcmp(nod->santier.nume_proiect, nume) == 0) {
			if (nod->prev == NULL) { //primul nod
				if (nod->next == NULL) {
					lista->prim = NULL;
					lista->ultim = NULL;
				}
				else {
					nod->next->prev = NULL;
					lista->prim = nod->next;
				}
			
			}
			else {
				if (nod->next == NULL) { //ultimul nod
					nod->prev->next = NULL;
					lista->ultim = nod->prev;
				}
				else {
					nod->prev->next = nod->next;
					nod->next->prev = nod->prev;
				}
			}

			//undeva in mijloc


			stergere_santier(&(nod->santier));
			free(nod);
			nod = NULL;
			break;
		}

		nod = nod->next;

	}
}

int lista_total_muncitori(ListaDubla lista) {
	int suma = 0;
	for (NodLd* nod = lista.prim; nod != NULL; nod = nod->next) {
		suma += nod->santier.nr_muncitori;
	}

	return suma;
}

int lista_total_muncitori_sup(ListaDubla lista, float suprafata) {
	int suma = 0;
	for (NodLd* nod = lista.prim; nod != NULL; nod = nod->next) {
		if (nod->santier.suprafata < suprafata) {
			suma += nod->santier.nr_muncitori;
		}
	}

	return suma;
}

void stergere_lista(ListaDubla* lista) {
	if (lista != NULL) {
		NodLd* nod = lista->prim;
		while(nod != NULL) {
			stergere_santier(&(nod->santier));
			
			NodLd* temp = nod->next;
			free(nod);
			nod = temp;
		}

		free(lista->prim);
		lista->prim = NULL;
		free(lista->ultim);
		lista->ultim = NULL;
	}


	
}

int main() {
	Santier s1 = init_santier("Santier 1", 3, 7.5);
	Santier s2 = init_santier("Santier 2", 7, 24.77);
	Santier s3 = init_santier("Santier 3", 15, 44.37);
	Santier s4 = init_santier("Santier 4", 22, 83.10);

	ListaDubla lista;
	lista.prim = NULL;
	lista.ultim = NULL;

	inserare_inceput(&lista, s1);
	inserare_inceput(&lista, s3);
	inserare_inceput(&lista, s2);
	inserare_inceput(&lista, s4);
	afisare_lista_first_to_last(lista);

	printf("Total munctori: %d\n", lista_total_muncitori(lista));
	float sup = 25;
	printf("Total munctiori snatiere cu sup mai mica de %.2fmp: %d\n\n", sup, lista_total_muncitori_sup(lista, sup));
	

	lista_stergere_santier_nume(&lista, "Santier 3");
	afisare_lista_first_to_last(lista);
	lista_stergere_santier_nume(&lista, "Santier 2");
	afisare_lista_first_to_last(lista);
	lista_stergere_santier_nume(&lista, "Santier 4");
	afisare_lista_first_to_last(lista);
	lista_stergere_santier_nume(&lista, "Santier 1");
	afisare_lista_first_to_last(lista);

	stergere_lista(&lista);
	afisare_lista_first_to_last(lista);

}