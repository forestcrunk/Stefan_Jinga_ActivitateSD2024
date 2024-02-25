//task-ul incarcat pe online.ase.ro a fost scris in C++
//deoarece a fost rezolvat inainte de a afla ca materia
//va fi in C
// 
//acesta este task-ul rescris in C

#include <stdio.h>
#include <malloc.h>

//Stefan Jinga -> S J -> SeJur
struct Sejur {
	char* destinatie;
	float pret;
	int nrBileteVandute;
};


//functii
struct Sejur initializareSejur(const char* destinatie, float pret, int nrBileteVandute) {
	struct Sejur s;

	s.destinatie = malloc(strlen(destinatie) + 1);
	strcpy(s.destinatie, destinatie);

	s.pret = pret;
	s.nrBileteVandute = nrBileteVandute;

	return s;
}

void afisareSejur(struct Sejur s) {
	printf("\nDestinatie: ");
	if (s.destinatie != NULL) {
		printf("%s", s.destinatie);
	}
	else printf("-");
	printf("\nPret bilet: %.2f", s.pret);
	printf("\nNumar de bilete vandute: %d", s.nrBileteVandute);
}

float sumaBilete(struct Sejur s) {
	return s.pret * s.nrBileteVandute;
}

void modificaPret(struct Sejur* s, float pret) {
	if (pret > 0) {
		s->pret = pret;
		printf("\nPretul biletului a fost modificat cu succes!");
	}
}

void stergeSejur(struct Sejur* s) {
	if (s->destinatie != NULL) {
		free(s->destinatie);
	}
	s->destinatie = NULL;
}

int main() {
	struct Sejur sejur1 = initializareSejur("Paris", 125.50, 620);

	afisareSejur(sejur1);
	printf("\n");

	float x = sumaBilete(sejur1);
	printf("\nSuma totala a biletelor vandute este: %.2f\n", x);

	modificaPret(&sejur1, 140.25);
	afisareSejur(sejur1);

	stergeSejur(&sejur1);

	return 0;
}