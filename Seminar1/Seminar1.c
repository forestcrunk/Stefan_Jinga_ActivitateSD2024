#include <stdio.h>
#include <malloc.h>

struct Cofetarie {
	char* nume;
	int nrAngajati;
	float* salarii;
};


struct Cofetarie initCofetarie(const char* nume, int nrAngajati, const float* salarii) {
	struct Cofetarie c;

	c.nume = (char*)malloc(strlen(nume) + 1);
	strcpy(c.nume, nume);

	c.nrAngajati = nrAngajati;
	c.salarii = (float*)malloc(sizeof(float) * nrAngajati);

	for (int i = 0; i < nrAngajati; i++) {
		c.salarii[i] = salarii[i];
	}

	return c;
}

void afisareCofetarie(struct Cofetarie c) {
	if (c.nume != NULL) {
		printf("Nume: %s\n", c.nume);
	}
	printf("Numar angajati: %d\n", c.nrAngajati);

	if (c.salarii != NULL) {
		printf("Salarii: ");
		for (int i = 0; i < c.nrAngajati; i++) {
			printf("%5.2f, ", c.salarii[i]);
		}
	}

	printf("\n");
}

void stergeCofetarie(struct Cofetarie* c) {
	if (c->nume != NULL) {
		free(c->nume);
	}
	free(c->salarii);

	c->nume = NULL;
	c->salarii = NULL;
}

int main() {
	struct Cofetarie cofetarie1;
	cofetarie1.nume = (char*)malloc(strlen("Dulce") + 1);
	strcpy(cofetarie1.nume, "Dulce");

	cofetarie1.nrAngajati = 3;
	cofetarie1.salarii = (float*)malloc(sizeof(float) * cofetarie1.nrAngajati);

	for (int i = 0; i < cofetarie1.nrAngajati; i++) {
		cofetarie1.salarii[i] = (i + 1) * 1000;
	}



	afisareCofetarie(cofetarie1);


	float* vec = malloc(sizeof(float) * 2);
	vec[0] = 4567;
	vec[1] = 473.15;
	struct Cofetarie cofetarie2 = initCofetarie("Mara", 2, vec);
	afisareCofetarie(cofetarie2);
	free(vec);

	stergeCofetarie(&cofetarie1);
	stergeCofetarie(&cofetarie2);

	return 0;
}