#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define N 2

typedef struct
{
	char matricula[8];
	int ocupado;
}Tplaza;

void main()
{
	
	static Tplaza aparcamiento[N];
	int i;
	char opcion, matriculaB[8];
	while (1)
	{
		printf("MENU DE ADMINISTRACION PRINCIPAL\n");
		printf("Pulse R para reservar una plaza\n");
		printf("Pulse A para abandonar una plaza\n");
		printf("Pulse E para visualizar el estado del aparcamiento\n");
		printf("Pulse B para buscar vehiculo por matricula\n");
		printf("Pulse S para salir del programa\n");
		scanf("%s", &opcion);
		while (getchar() != '\n');


		switch (opcion)
		{
		case 'R':
		case 'r':
			for (i = 0; i<N; i++)
			{
				if (aparcamiento[i].ocupado == 0)
				{
					aparcamiento[i].ocupado = 1;
					printf("Se ha ocupado la plaza %d\n", i + 1);
					printf("Indique el numero de matricula: ");
					gets(aparcamiento[i].matricula);
					if (aparcamiento[i].ocupado) i = N;
					puts("Pulse INTRO para continuar\n");
					while (getchar() != '\n');
				}
			}
			if (i == N)
			{
				puts("No hay plazas libres\n");
				puts("Pulse INTRO para continuar\n");
				while (getchar() != '\n');
			}
			break;
		case 'A':
		case 'a':
			printf("Indique que plaza desea desocupar: \n");
			scanf("%d", &i);
			while (getchar() != '\n');

			if (i>N || i<1)
			{
				printf("Esa plaza no existe\n");
			}
			else if (aparcamiento[i - 1].ocupado)
			{
				aparcamiento[i - 1].ocupado = 0;
				printf("Se ha desocupado la plaza\n");
			}
			else
			{
				printf("La plaza %d esta libre\n", i);
			}
			puts("Pulse INTRO para continuar\n");
			while (getchar() != '\n');
			break;
		case 'E':
		case 'e':
			for (i = 0; i<N; i++)
			{
				if (aparcamiento[i].ocupado)
				{
					printf("Plaza %d: ocupado\n", i + 1);
					printf("Matricula: %s\n", aparcamiento[i].matricula);
				}
				else
				{
					printf("Plaza %d: libre\n", i + 1);
				}
			}
			puts("Pulse INTRO para continuar\n");
			while (getchar() != '\n');
			break;
		case 'B':
		case'b':
			printf("Indique el numero de matricula del vehiculo: \n");
			gets(matriculaB);
			for (i = 0; i<N; i++)
			{
				if (strcmp(matriculaB, aparcamiento[i].matricula) == 0)
				{
					printf("El vehiculo con matricula %s esta en la plaza %d\n", matriculaB, i + 1);

					i = N;
				}

			}
			if (i == N)
			{
				printf("El vehiculo con matricula %s no esta en el aparcamiento\n", matriculaB);

			}

			break;
		case 'S':
		case's':

			break;

		default:
			printf("Opcion no encontrada, pruebe otra vez\n");
			puts("Pulse INTRO para continuar\n");
			while (getchar() != '\n');

		} 

		if (opcion == 's' || opcion == 'S') break;

	}

	puts("Pulse INTRO para finalizar\n");
	while (getchar() != '\n');
}
