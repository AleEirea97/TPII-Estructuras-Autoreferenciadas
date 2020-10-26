#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
   long partNumber;
   long serialNumber;
   char descripcion[40];
   char ubicacion[100];
   int cantidad;
}repuestos_t;

struct lista{
	repuestos_t repuesto;
	struct lista *lazo;
};

void menu(void)
{
	system("cls");
	printf("\n1. Insertar Repuestos.");
	printf("\n2. Cargar en Stock.");
	printf("\n3. Salir..");
	printf("\nOpcion:");
}

int opc(void)
{
	int op;
	scanf("%d",&op);
	return op;
}

int main(void)
{
	FILE *file_p;
	repuestos_t repuestoA;
	struct lista *p = NULL, *u = NULL, *aux, *r;

	while(1)
	{
		menu();
		switch(opc())
		{
			case 1://Insertar en la lista..
				aux = (struct lista*)malloc(sizeof(struct lista));

				printf("\nIngrese Numero de Parte:");
				scanf("%ld", &aux->repuesto.partNumber);
				printf("\nIngrese Numero de Serie:");
				scanf("%ld", &aux->repuesto.serialNumber);
				fflush(stdin);
				printf("\nIngrese Descripcion:");
				gets(aux->repuesto.descripcion);
				printf("\nIngrese Ubicacion:");
				gets(aux->repuesto.ubicacion);
				fflush(stdin);
				printf("\nIngrese la cantidad:");
				scanf("%d",&aux->repuesto.cantidad);

				if(p == NULL) // Si esta vacía..es el primer elemento.
				{
					p = u = aux;
					u->lazo = NULL;
				}
				else
				{
					r = p;
					while(1)
					{
						if( strcmp(aux->repuesto.descripcion, r->repuesto.descripcion) == -1 )
						{
							aux->lazo = p;	//Rutina de la pila.
							p = aux;
							break;
						}
						while(r->lazo) //Ciclo para elemento interno.
						{
							if( strcmp(r->lazo->repuesto.descripcion, aux->repuesto.descripcion) == -1 )
								r= r->lazo;
							else
								break;
						}
						if(r == u)
						{
							u->lazo = aux;
							u=aux;
							u->lazo= NULL;
							break;
						}
						aux->lazo = r->lazo;
						r->lazo = aux;
						break;
					}
				}

				//Imprimir la lista:
				aux = p;
				printf("\nLista Actual:");
				printf("\nPartNumber\tSerialNumber\tDescripcion:\t\tUbicacion:\tCantidad\n");
				while(aux)
				{
					printf("%04ld\t\t%04ld\t\t%-10s\t%-10s\t%04d\n",aux->repuesto.partNumber,aux->repuesto.serialNumber,
						aux->repuesto.descripcion,aux->repuesto.ubicacion,aux->repuesto.cantidad);
					aux = aux->lazo;
				}
				system("pause");
				break;

			case 2://Cargar el Archivo..

				file_p = fopen("stock.dat","ab+");

				aux = p;
				while(aux)
				{
					repuestoA = aux->repuesto;
					fwrite(&repuestoA,sizeof(repuestos_t),1,file_p);
					aux = aux->lazo;
				}
				fclose(file_p);
				printf("Stock creado con exito.\n");
				system("pause");

				break;

			case 3:
				return 0;

			case 4://Lee archivo Stock..

				file_p = fopen("stock.dat","rb");

				fread(&repuestoA,sizeof(repuestos_t),1,file_p);
				printf("\nPartNumber\tSerialNumber\tDescripcion:\t\tUbicacion:\tCantidad:\n");
				while(!feof(file_p))
				{
					printf("%04ld\t\t%04ld\t\t%-10s\t\t%-10s\t%04d\n",repuestoA.partNumber,repuestoA.serialNumber,
						repuestoA.descripcion,repuestoA.ubicacion,repuestoA.cantidad);

					fread(&repuestoA,sizeof(repuestos_t),1,file_p);
				}
				fclose(file_p);
				system("pause");

				break;
		}
	}

	return 0;
}
