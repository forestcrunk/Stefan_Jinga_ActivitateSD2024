// binary search tree

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <malloc.h>
#include <string.h>


typedef struct Rezervare Rezervare;
typedef struct Nod Nod;

struct Rezervare {
	int id;
	char* nume_client;
	int nr_pers;
};

struct Nod {
	Rezervare info;
	Nod* fs;
	Nod* fd;
};

Rezervare r_initfromfile(FILE* f) {
	Rezervare r;
	char buffer[50];
	fscanf(f, "%d", &r.id);
	fscanf(f, "%s", &buffer);
	r.nume_client = (char*)malloc(strlen(buffer) + 1);
	strcpy(r.nume_client, buffer);
	fscanf(f, "%d", &r.nr_pers);

	return r;
}

//sem12
int a_calcul_inaltime(Nod* a) {
	if (a) {
		int inaltime_stanga = a_calcul_inaltime(a->fs);
		int inaltime_dreapta = a_calcul_inaltime(a->fd);

		return 1 + (inaltime_stanga > inaltime_dreapta ? inaltime_stanga : inaltime_dreapta);

	}
	return 0;
}

Nod* a_rotire_dreapta(Nod* a) {
	Nod* aux = a->fs;

	if (a) {
		a->fs = aux->fd;
		aux->fd = a;
	}

	return aux;
}

Nod* a_rotire_stanga(Nod* a) {
	Nod* aux = a->fd;

	if (a) {
		a->fd = aux->fs;
		aux->fs = a;
	}

	return aux;
}

int a_calcul_echilibru_nod(Nod* a) {
	if (a) {
		int inaltime_stanga = a_calcul_inaltime(a->fs);
		int inaltime_dreapta = a_calcul_inaltime(a->fd);

		return inaltime_stanga - inaltime_dreapta;
	}
	return 0;
}

Nod* a_insert(Nod* a, Rezervare r) {
	if (a) {
		if (a->info.id < r.id) {
			a->fd = a_insert(a->fd, r);
		}
		else {
			a->fs = a_insert(a->fs, r);
		}
		//sem12
		int grad = a_calcul_echilibru_nod(a);

		if (grad > 1) { //dezechilibru stanga
			// vvvvvvv == 1 e situatie simpla (doar se roteste din radacina)
			if (a_calcul_echilibru_nod(a->fs) == -1) {
				a->fs = a_rotire_stanga(a->fs);
			}

			a = a_rotire_dreapta(a);

		}
		else {
			if (grad < -1) { //dezechilibru dreapta
				// vvvvvvvvvvv == -1 e situatie simpla
				if (a_calcul_echilibru_nod(a->fd) == 1) {
					a->fd = a_rotire_dreapta(a->fd);
				}
				a = a_rotire_stanga(a);
			}
		}
	}
	else {
		Nod* temp = (Nod*)malloc(sizeof(Nod));
		temp->info = r;//shallow copy
		temp->fd = NULL;
		temp->fs = NULL;
		a = temp;
	}
	return a;
}

void a_readfromfile(const char* filename, Nod** a) {
	FILE* f = fopen(filename, "r");
	int nr_rez;
	fscanf(f, "%d", &nr_rez);
	for (int i = 0; i < nr_rez; i++) {

		Rezervare r = r_initfromfile(f);
		*a = a_insert(*a, r);
	}
}

void r_afisare(Rezervare r) {
	printf("Rezervarea cu ID-ul %d a fost facuta de %s pentru %d persoane.\n", r.id, r.nume_client, r.nr_pers);
}

void a_afisare_preordine(Nod* a) {
	if (a != NULL) {
		r_afisare(a->info);
		a_afisare_preordine(a->fs);
		a_afisare_preordine(a->fd);
	}
}
void a_afisare_inordine(Nod* a) {
	if (a != NULL) {
		a_afisare_inordine(a->fs);
		r_afisare(a->info);
		a_afisare_inordine(a->fd);
	}
}
void a_afisare_postordine(Nod* a) {
	if (a != NULL) {
		a_afisare_postordine(a->fs);
		a_afisare_postordine(a->fd);
		r_afisare(a->info);
	}
}

Rezervare a_findByID(Nod* a, int id) {
	if (a) {
		if (a->info.id < id) {
			return a_findByID(a->fd, id);
		}
		else {
			if (a->info.id > id) {
				return a_findByID(a->fs, id);
			}
			else {
				return a->info;
			}
		}
	}
	else {
		Rezervare r;
		r.id = -1;
		r.nume_client = NULL;
		r.nr_pers = -1;
		return r;
	}
}



int a_calcul_nrpers(Nod* a) {
	if (a) {
		int r_pers = a->info.nr_pers;
		int s_pers = a_calcul_nrpers(a->fs);
		int d_pers = a_calcul_nrpers(a->fd);

		return r_pers + s_pers + d_pers;
	}
	return 0;
}

void a_delete(Nod** a) {
	if (*a) {
		//post-ordine
		a_delete(&(*a)->fs);
		a_delete(&(*a)->fd);

		free((*a)->info.nume_client);
		(*a)->info.nume_client = NULL;

		free((*a));
		(*a) = NULL;
	}
}



void main() {
	Nod* arbore = NULL;
	a_readfromfile("Rezervari.txt", &arbore);

	a_afisare_preordine(arbore);
	printf("\n");

	a_delete(&arbore);
	a_afisare_preordine(arbore);
}