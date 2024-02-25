#include <stdio.h>
#include <malloc.h>

//Stefan Jinga -> S J -> SeJur
struct Sejur {
	char* destinatie;
	float pret;
	int nrBileteVandute;
};


//functii task 1
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

//functii task 2
void afisareVector(struct Sejur* v, int nrElem) {
	if (v != NULL && nrElem > 0) {
		printf("\nNumar de elemente in vector: %d", nrElem);

		for (int i = 0; i < nrElem; i++) {
			printf("\n//Elementul %d:", i + 1);
			afisareSejur(v[i]);
			printf("\n");
		}
	}
	else {
		printf("\nVectorul nu contine elemente.");
	}
}

struct Sejur* f1(struct Sejur* v, int nrElem, int* dimNou) {
	//f1 : pret > 200

	if (v != NULL && nrElem > 0) {
		*dimNou = 0;
		struct Sejur* v_nou;
		for (int i = 0; i < nrElem; i++) {
			if (v[i].pret > 200)(*dimNou)++;
		}

		if (*dimNou > 0) {
			v_nou = (struct Sejur*) malloc(sizeof(struct Sejur) * (*dimNou));

			int k = 0;
			for (int i = 0; i < nrElem; i++) {
				if (v[i].pret > 200) {
					v_nou[k++] = v[i];
				}
			}

			return v_nou;
		}
		else {
			printf("\nNu exista sejururi in vector al caror pret pentru bilet sa fie mai mare de 200.");
			return NULL; //pentru ca vectorul sa nu ramana neinitializat; cauza erori la free()
		}
	}
}

struct Sejur* f2(struct Sejur* v, int nrElem, int* dimNou) {
	//f2 : nr bilete <250

	if (v != NULL && nrElem > 0) {
		*dimNou = 0;
		struct Sejur* v_nou;
		for (int i = 0; i < nrElem; i++) {
			if (v[i].nrBileteVandute < 250)(*dimNou)++;
		}

		if (*dimNou > 0) {
			v_nou = (struct Sejur*) malloc(sizeof(struct Sejur) * (*dimNou));

			int k = 0;
			for (int i = 0; i < nrElem; i++) {
				if (v[i].nrBileteVandute < 250) {
					v_nou[k++] = v[i];
				}
			}

			return v_nou;
		}
		else {
			printf("\nNu exista sejururi in vector pentru care sa se fi vandut mai putin de 250 de bilete.");
			return NULL;
		}
	}
}

struct Sejur* concatVectori(struct Sejur* v1, int dim1, struct Sejur* v2, int dim2, int* dimNou) {
	if (v1 != NULL && dim1 > 0 && v2 != NULL && dim2 > 0) {
		*dimNou = dim1 + dim2;
		struct Sejur* v_nou= (struct Sejur*) malloc(sizeof(struct Sejur) * (*dimNou));

		for (int i = 0; i < dim1; i++) {
			v_nou[i] = v1[i];
		}

		for (int i = dim1; i < (*dimNou) /* dim1 + dim2 */; i++) {
			v_nou[i] = v2[i - dim1];
		}
		
		return v_nou;
	}
	else {
		printf("\nCel putin unul din vectori nu contine elemente.");
		return NULL;
	}
}

void stergeVector(struct Sejur* v) {
	if (v != NULL) {
		free(v);
	}
	v = NULL;
}

int main() {
	struct Sejur* vec1;

	struct Sejur s1 = initializareSejur("Paris", 125.50, 620);
	struct Sejur s2 = initializareSejur("Hawaii", 285.75, 300);
	struct Sejur s3 = initializareSejur("Constanta", 75, 125);
	struct Sejur s4 = initializareSejur("Roma", 175.15, 420);
	struct Sejur s5 = initializareSejur("Venetia", 195.35, 140);
	struct Sejur s6 = initializareSejur("Kuala Lumpur", 215.21, 369);

	
	
	int dim1 = 6;
	vec1 = (struct Sejur*) malloc(sizeof(struct Sejur) * dim1);
	vec1[0] = s1;
	vec1[1] = s2;
	vec1[2] = s3;
	vec1[3] = s4;
	vec1[4] = s5;
	vec1[5] = s6;

	printf("\n~~~~Testare afisare~~~~\n");
	afisareVector(vec1, dim1);

	printf("\n~~~~Testare f1~~~~\n");
	int dim2 = 0;
	struct Sejur* vec2 = f1(vec1, dim1, &dim2);
	afisareVector(vec2, dim2);
	
	printf("\n~~~Testare f2~~~~\n");
	int dim3 = 0;
	struct Sejur* vec3 = f2(vec1, dim1, &dim3);
	afisareVector(vec3, dim3);

	printf("\n~~~~Testare concatenare~~~~\n");
	int dim4 = 0;
	struct Sejur* vec4 = concatVectori(vec2, dim2, vec3, dim3, &dim4);
	afisareVector(vec4, dim4);


	
	//frees
	stergeVector(vec1);
	stergeVector(vec2);
	stergeVector(vec3);
	stergeVector(vec4);
	
	stergeSejur(&s1);
	stergeSejur(&s2);
	stergeSejur(&s3);
	stergeSejur(&s4);
	stergeSejur(&s5);
	stergeSejur(&s6);
	
	return 0;
}