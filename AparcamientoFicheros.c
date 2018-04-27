#define _CRT_SECURE_NO_WARNINGS
#define NUM_PLAZAS 10
#define NUM_USU 5
#include <stdio.h>
#include <time.h>
#include <string.h>
struct acceso {
	char usuario[50];
	char contras[50];
};
struct plazas {
	int est;
	char tipo;
	char Mat[8];
};

void recuento(struct plazas plaza[], int *nLibresCoches, int *nLibresMotos);
//void inicio(struct plazas plaza[]);
int esMatriculaValida(char *Mat);
char menu();
int BuscaVehiculo(struct plazas plaza[]);
int buscarPlazaLibre(struct plazas plaza[], char tipo);
void leerFichero(char nombreFichero[], struct plazas plaza[], int *dim);
void salvarFichero(char nombreFichero[], struct plazas plaza[], int dim);
void main() {
	struct acceso admins[NUM_USU] = { { "admin", "1234" },{ "administrador", "9876" },{ "todopoderoso", "ornitorrinco" },{ "user1", "contra1234" },{ "user2", "5678" } };
	struct plazas plaza[NUM_PLAZAS];
	int l = 0, i, j = 4, k = 0, p = 0, NLCoches = 0, NLMotos = 0, busca, nPlazas = NUM_PLAZAS;
	char op, numMat[8], op2, op3, usu[50], contra[50], opcion;
	//inicio(plaza);
	leerFichero("lab.txt", plaza, &nPlazas);
	while (l < 4) {
		system("cls");
		l++;
		if (l == 4) {
			printf("Numero de intentos agotados.\nSaliendo del programa...\n");
			return 0;
		}
		printf("BIENVENIDO\n\n");
		printf("Numero de intentos restantes: %d\n", j - l);
		printf("Introduzca usuario y contrasena para obtener acceso al sistema.\n");
		printf("Usuario: ");
		scanf("%s", usu);
		printf("Contrasena: ");
		scanf("%s", contra);
		for (i = 0; i < NUM_USU; i++) {
			if (strcmp(admins[i].usuario, usu) == 0) {
				if (strcmp(admins[i].contras, contra) == 0) {
					l = 5;
					break;
				}
			}
		}
		getchar();
	}

	while (1) {
		system("cls");
		printf("%s bienvenido/a al sistema de aparcamiento.\n\n", usu);
		op = menu();
		switch (op) {
		case 'R':
			printf("Seleccione el tipo de su vehiculo(M-moto)o(C-coche):\n");
			getchar();
			scanf("%c", &op3);
			if (op3 == 'M') {
				p = buscarPlazaLibre(plaza, 'M');
				plaza[p].est = 1;
				do {
					printf("Introduzca la matricula de su moto:\n");
					getchar();
					scanf("%s", plaza[i].Mat);
					k = esMatriculaValida(&plaza[i].Mat);
				} while (k != 0);
				printf("Su moto se encuentra estacionada en la plaza %d\n", i + 1);
				system("pause");
				break;
			}
			else if (i == NUM_PLAZAS - 1) {
				printf("Lo sentimos, No hay plazas libres en este momento.\n");
			}
			if (op3 == 'C') {
				if (plaza[i].tipo == 'C') {
					p = buscarPlazaLibre(plaza, 'C');
					plaza[p].est = 1;
					do {
						printf("Introduzca la matricula de su coche:\n");
						getchar();
						scanf("%s", plaza[i].Mat);
						k = esMatriculaValida(&plaza[i].Mat);
					} while (k != 0);
					printf("Su coche se encuentra estacionada en la plaza %d\n", i + 1);
					system("pause");
					break;
				}
				else if (i == NUM_PLAZAS - 1) {
					printf("Lo sentimos, No hay plazas libres en este momento.\n");
					system("pause");
					break;
				}
			}
			break;
		case 'A':
			printf("Introduzca su numero de matricula:\n");
			scanf("%s", numMat);
			for (i = 0; i < NUM_PLAZAS; i++) {
				if (strcmp(numMat, plaza[i].Mat) == 0) {
					plaza[i].est = 0;
					printf("Su coche con matricula %s ha abandonado el parking satisfactoriamente.\n", numMat);
					system("pause");
					break;
				}
			}
			if (i == NUM_PLAZAS) {
				printf("Su vehiculo no se encuentra en el parking en este momento.\n");
			}
			system("pause");
			break;
		case 'E':
			recuento(plaza, &NLCoches, &NLMotos);
			printf("Hay %d plazas de coches libres y %d plazas de motos libres.\n", NLCoches, NLMotos);
			printf("El estado actual del parking es:\n");
			for (i = 0; i < NUM_PLAZAS; i++) {
				if (i % 2 == 0) printf("\n");
				if (plaza[i].est == 0) {
					if (plaza[i].tipo == 'M') {
						printf("La plaza %d de moto esta LIBRE.\t", i + 1);
					}
					else if (plaza[i].tipo == 'C') {
						printf("La plaza %d de coche esta LIBRE.\t", i + 1);
					}
				}
				else if (plaza[i].est == 1) {
					if (plaza[i].tipo == 'M') {
						printf("La plaza %d de moto esta OCUPADA.\t", i + 1);
					}
					else if (plaza[i].tipo == 'C') {
						printf("La plaza %d de coche esta OCUPADA.\t", i + 1);
					}
				}

			}

			system("pause");
			break;
		case 'B':
			BuscaVehiculo(plaza);
			break;
		case 'S': printf("Saliendo del programa...\n");
			salvarFichero("lab.txt", plaza, nPlazas);
			return 0;
			system("pause");
			break;

		default: printf("Opcion no valida....\n");
			system("pause");
			break;
		}
		getchar();
	}
}
void recuento(struct plazas plaza[], int *nLibresCoches, int *nLibresMotos) {
	int i;
	*nLibresCoches = 0;
	*nLibresMotos = 0;
	for (i = 0; i < NUM_PLAZAS; i++) {
		if (plaza[i].tipo == 'C' && plaza[i].est == 0) {
			(*nLibresCoches)++;
		}
		else if (plaza[i].tipo == 'M' && plaza[i].est == 0) {
			(*nLibresMotos)++;
		}
	}
}
void inicio(struct plazas plaza[]) {
	int i;
	for (i = 0; i < NUM_PLAZAS; i++) {
		plaza[i].est = 0;
		if (i >= NUM_PLAZAS / 2) {
			plaza[i].tipo = 'M';
		}
		else {
			plaza[i].tipo = 'C';
		}
	}
}
char menu() {
	char opcion;
	printf("Seleccione una de estas opciones:\n");
	printf("\nR-Reserva de plaza.\n");
	printf("\n----------------------------------------------------------------------------------------\n");
	printf("\nA-Abandonar plaza.\n");
	printf("\n----------------------------------------------------------------------------------------\n");
	printf("\nE-Estado del aparcamiento\n");
	printf("\n----------------------------------------------------------------------------------------\n");
	printf("\nB-Buscar vehiculo por matricula.\n");
	printf("\n----------------------------------------------------------------------------------------\n");
	printf("\nS-Salir del programa.\n");
	printf("\n----------------------------------------------------------------------------------------\n");
	scanf("%c", &opcion);
	return opcion;
}
int esMatriculaValida(char *Mat) {
	int k, l = 0;
	for (k = 0; k < 7; k++) {
		if (k < 4) {
			if (*(Mat + k) < 0 && *(Mat + k) > 9) {
				printf("Matricula no valida por el numero.\n");
				l++;
				break;
			}
		}
		if (k >= 4) {
			if ((*(Mat + k) < 'B' && *(Mat + k) > 'Z') || *(Mat + k) == 'E' || *(Mat + k) == 'I' || *(Mat + k) == 'O' || *(Mat + k) == 'U') {
				printf("Matricula no valida por la letra.\n");
				l++;
				break;
			}
		}
	}
	if (l == 0) printf("La matricula introducida es valida.\n");
	else printf("La matricula introducida no es valida.\n");
	return l;
}
BuscaVehiculo(struct plazas plaza[]) {
	int i;
	char BusMat[8];
	printf("Introduzca numero de matricula para localizar su vehiculo.\t");
	scanf("%s", BusMat);
	for (i = 0; i < NUM_PLAZAS; i++) {
		if (strcmp(BusMat, plaza[i].Mat) == 0) {
			printf("Su vehiculo se encuentra en la plaza %d.\n", i + 1);
			system("pause");
		}
	}
	if (i == NUM_PLAZAS) {
		printf("Su vehiculo no se encuentra estacionado en este aparcamiento.\n");
		system("pause");
	}
}
int buscarPlazaLibre(struct plazas plaza[], char tipo) {
	int k;
	if (tipo == 'M') {
		for (k = 0; k < NUM_PLAZAS / 2; k++) {
			if (plaza[k].est == 0)
				break;
		}
	}
	else if (tipo == 'C') {
		for (k = NUM_PLAZAS / 2; k < NUM_PLAZAS / 2; k++) {
			if (plaza[k].est == 0)
				break;
		}
	}
	return k;
}
void leerFichero(char nombreFichero[], struct plazas plaza[], int *dim) {
	FILE *pf;
	int k;
	pf = fopen("lab.txt", "r");
	for (k = 0; k < *dim; k++) {
		fscanf(pf, "%d %c %s\n", &plaza[k].est, &plaza[k].tipo, &plaza[k].Mat);
	}
	fclose(pf);
}
void salvarFichero(char nombreFichero[], struct plazas plaza[], int dim) {
	FILE *pf;
	int k;
	pf = fopen("lab.txt", "w");
	for (k = 0; k < dim; k++) {
		fprintf(pf, "%d %c %s\n", plaza[k].est, plaza[k].tipo, plaza[k].Mat);
	}
	fclose(pf);

}