#include <stdio.h>
#include <stdlib.h>

typedef struct{
   long partNumber;
   long serialNumber;
   char descripcion[40];
   char ubicacion[100];
   int cantidad;
}repuestos_t;

typedef struct{
    repuestos_t rep_fallados;
    void *lazo;
}cola_t;

typedef struct{
	repuestos_t rep_fallados;
	void *lazo;
}pila_t;

int main (void)
{
	FILE *file_p;
	FILE *file_p1;
	FILE *file_p2;

	cola_t *p = NULL, *u = NULL, *aux;
	pila_t *pi,*auxp;
	pi = auxp = NULL;

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
			system("pause");

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
		else
		{
			file_p1 = fopen("n_stock.dat","ab");

			fwrite(&repuestoA,sizeof(repuestos_t),1,file_p1);
			fclose(file_p1);
		}
		//printf("%04ld\t\t%04ld\t\t%-10s\t%-10s\n",repuestoA.partNumber,repuestoA.serialNumber,repuestoA.descripcion,repuestoA.ubicacion);
		fread(&repuestoA,sizeof(repuestos_t),1,file_p);
	}
	fclose(file_p);

	remove("stock.dat");
	rename("n_stock.dat","stock.dat");


	printf("Cola creada con exito..\n");
	system("pause");

	//Impresión de Cola.
	aux = p;
	printf("PartNumber\tSerialNumber\tDescripcion:\tUbicacion:\n");
	while(aux)
	{
		auxp = (pila_t *)malloc(sizeof(pila_t));
		auxp->rep_fallados = aux->rep_fallados;
		auxp->lazo = pi;
		pi = auxp;

		printf("%04ld\t\t%04ld\t\t%-10s\t%-10s\n",aux->rep_fallados.partNumber,aux->rep_fallados.serialNumber,aux->rep_fallados.descripcion,aux->rep_fallados.ubicacion);
		aux = (cola_t *)aux->lazo;
	}
	system("pause");

	file_p2 = fopen("ColaInversa.dat","ab");
	auxp = pi;
	while(auxp)
	{
		repuestoA = auxp->rep_fallados;
		fwrite(&repuestoA,sizeof(repuestos_t),1,file_p2);

		auxp = (pila_t *)auxp->lazo;
	}
	fclose(file_p2);

	return 0;
}
