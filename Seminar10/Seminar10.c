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

Nod* a_insert(Nod* a, Rezervare r) {
	if (a) {
		if (a->info.id < r.id) {
			a->fd = a_insert(a->fd, r);
		}
		else {
			a->fs = a_insert(a->fs, r);
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

int a_calculnrpers(Nod* a) {
	if (a) {
		int r_pers = a->info.nr_pers;
		int s_pers = a_calculnrpers(a->fs);
		int d_pers = a_calculnrpers(a->fd);

		return r_pers + s_pers + d_pers;
	}
	return 0;


}

void main() {
	Nod* arbore = NULL;
	a_readfromfile("Rezervari.txt", &arbore);
	
	a_afisare_preordine(arbore);
	printf("\n");
	r_afisare(a_findByID(arbore, 10));

	printf("\n");
	printf("%d persoane in total\n", a_calculnrpers(arbore));
}