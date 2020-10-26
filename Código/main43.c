#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
   long numeroDeOrden;
   char cliente[40];
   char descripciondeFalla[200];
   char modelo[65];
   char fecha[10];
   char hora[10];
}repuestos_t;

typedef struct{
	repuestos_t ordenP;
	void *lazo;
}pila_t;

typedef struct{
	long fecha;
	int anno;
	int mes;
	int dia;
}fecha_t;

struct lista{
	fecha_t fechaL;
	repuestos_t ordenL;
	struct lista *lazo;
};

int main (void)
{
	FILE *file_p;
	repuestos_t orden;

	pila_t *pi,*auxp;	//Para la pila.
	pi = auxp = NULL;

	struct lista *p = NULL, *u = NULL, *aux, *r;	//Para la lista.

	file_p = fopen("ordenes.dat","rb");
	fread(&orden,sizeof(repuestos_t),1,file_p);

	printf("Leyendo Ordenes de Trabajo...\n\n");
	while(!feof(file_p))
	{
		aux = (struct lista*)malloc(sizeof(struct lista));

		aux->ordenL = orden;
		aux->fechaL.fecha = atoi(orden.fecha);
		aux->fechaL.dia   = aux->fechaL.fecha / 1000000;
		aux->fechaL.mes    = ( aux->fechaL.fecha - aux->fechaL.dia * 1000000 ) / 10000;
		aux->fechaL.anno  = aux->fechaL.fecha - aux->fechaL.dia * 1000000 - aux->fechaL.mes * 10000;

		if(p == NULL) // Si esta vacía..es el primer elemento.
		{
			p = u = aux;
			u->lazo = NULL;
			//printf("Primer elemento.");
			//system("pause");
		}
		else
		{
			r=p;
			while(1)
			{
				if(r->fechaL.anno < aux->fechaL.anno)
				{
					//printf("\nPrimer lugar.\n");
					//system("pause");
					aux->lazo = p; 	//Rutina de la pila.
					p = aux;
					break;
				}
				if(r->fechaL.anno ==  aux->fechaL.anno)
				{
					if(r->fechaL.mes < aux->fechaL.mes)
					{
						aux->lazo = p; 	//Rutina de la pila.
						p = aux;
						break;
					}
				}
				while(r->lazo) //Ciclo para elemento interno.
				{
					if(r->lazo->fechaL.anno > aux->fechaL.anno)
						r= r->lazo;

					if(r->lazo->fechaL.anno == aux->fechaL.anno)
					{
						if(r->lazo->fechaL.mes > aux->fechaL.mes)
							r = r->lazo;
					}
					else
						break;
				}
				if(r == u)
				{
					//printf("\nUltimo lugar.\n"); //Rutina de la cola.
					//system("pause");
					u->lazo = aux;
					u = aux;
					u->lazo = NULL;
					break;
				}
				//printf("\nOtro lugar.\n");
				//system("pause");
				aux->lazo = r->lazo;
				r->lazo = aux;
				break;
			}
		}

		fread(&orden,sizeof(repuestos_t),1,file_p);
	}
	fclose(file_p);

	//system("cls");
	//Recorrido de la lista apilando:
	aux = p;
	while(aux)
	{
		auxp = (pila_t*)malloc(sizeof(pila_t));
		auxp->ordenP = aux->ordenL;
		auxp->lazo = pi;
		pi = auxp;

		aux = aux->lazo;
	}
	printf("Pila Creada...\n\n");
	//system("pause");

	//Impresión de la pila:
	//system("cls");
	auxp = pi;
	printf("Num. de Orden:\tCliente:\tDescripcion de Falla:\tModelo:\t\tFecha:\t\tHora:\n");
	while(1)
	{
		if(!auxp)
			break;

		printf("%04ld\t\t%-10s\t%-20s\t%-10s\t%-10s\t%-10s\n",auxp->ordenP.numeroDeOrden,auxp->ordenP.cliente,
					auxp->ordenP.descripciondeFalla,auxp->ordenP.modelo,auxp->ordenP.fecha,auxp->ordenP.hora);
		auxp =(pila_t *)auxp->lazo;
	}
	system("pause");

	//Crea un archivo con la pila:
	file_p = fopen("ordenesPila.dat","ab+");
	auxp = pi;
	while(1)
	{
		if(!auxp)
			break;
		orden = auxp->ordenP;
		fwrite(&orden,sizeof(repuestos_t),1,file_p);
		auxp =(pila_t *)auxp->lazo;
	}
	fclose(file_p);

	return 0;
}
