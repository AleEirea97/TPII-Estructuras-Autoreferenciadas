#include <stdio.h>
#include <stdlib.h>

typedef struct{
   long partNumber;
   long serialNumber;
   char descripcion[40];
   char ubicacion[100];
}repuestos_t;

typedef struct{
    repuestos_t rep_fallados;
    void *lazo;
}cola_t;

int main (void)
{
	FILE *file_p;
	cola_t *p = NULL, *u = NULL, *aux;
	long partNumberb;
	repuestos_t repuestoA;

	partNumberb = 1234;	//Dado por el problema.
	file_p = fopen("stock.dat","rb");

	fread(&repuestoA,sizeof(repuestos_t),1,file_p);
	//printf("PartNumber\tSerialNumber\tDescripcion:\tUbicacion:\n");
	while(!feof(file_p))
	{
		if(repuestoA.partNumber == partNumberb)
		{
			printf("Registro encontrado\n");

			aux = (cola_t *)malloc(sizeof(cola_t));

			aux->rep_fallados = repuestoA;

			if(p == NULL)					//Tratamiento especial al ser el primer elemento.
				p = u = aux;
			else
			{
				u->lazo =(void *)aux;		//Engancha el último con el recién creado.
				u = aux;					//Actualiza  el último.
			}
			u->lazo = NULL;
		}
		//printf("%04ld\t\t%04ld\t\t%-10s\t%-10s\n",repuestoA.partNumber,repuestoA.serialNumber,repuestoA.descripcion,repuestoA.ubicacion);
		fread(&repuestoA,sizeof(repuestos_t),1,file_p);
	}
	fclose(file_p);
	printf("Cola creada con exito..\n");
	system("pause");

	aux = p;
	printf("PartNumber\tSerialNumber\tDescripcion:\tUbicacion:\n");
	while(aux)
	{
		printf("%04ld\t\t%04ld\t\t%-10s\t%-10s\n",aux->rep_fallados.partNumber,aux->rep_fallados.serialNumber,aux->rep_fallados.descripcion,aux->rep_fallados.ubicacion);
		aux = (cola_t *)aux->lazo;
	}
	system("pause");

	return 0;
}
