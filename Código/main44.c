#include <stdio.h>
#include <stdlib.h>

typedef struct{
   long numeroDeOrden;
   char cliente[40];
   char descripciondeFalla[200];
   char modelo[65];
   char fecha[10];
   char hora[10];
}repuestos_t;

typedef struct{
    repuestos_t repuesto;
    int cantidad;
}extraccionRepuestos_t;

struct lista{
	extraccionRepuestos_t extraccionL;
	struct lista *lazo;
};

int main (void)
{
	FILE *file_p;
	struct lista *p = NULL, *u = NULL, *aux, *r;
	repuestos_t orden;
	extraccionRepuestos_t extraccion;

	file_p = fopen("ordenesPila.dat","rb");
	fread(&orden, sizeof(repuestos_t),1,file_p);

	while(!feof(file_p))
	{
		printf("Num. de Orden:\tCliente:\tDescripcion de Falla:\tModelo:\t\tFecha:\t\tHora:\n");
		printf("%04ld\t\t%-10s\t%-20s\t%-10s\t%-10s\t%-10s\n",orden.numeroDeOrden,orden.cliente,orden.descripciondeFalla,orden.modelo,orden.fecha,orden.hora);
		aux = (struct lista*)malloc(sizeof(struct lista));

		aux->extraccionL.repuesto = orden;
		printf("Ingrese la cantidad para la orden actual:");
		scanf("%d",&aux->extraccionL.cantidad);

		printf("\n\n");
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
				if(r->extraccionL.repuesto.numeroDeOrden < aux->extraccionL.repuesto.numeroDeOrden)
				{
					//printf("\nPrimer lugar.\n");
					//system("pause");
					aux->lazo = p; 	//Rutina de la pila.
					p = aux;
					break;
				}
				while(r->lazo) //Ciclo para elemento interno.
				{
					if(r->lazo->extraccionL.repuesto.numeroDeOrden > aux->extraccionL.repuesto.numeroDeOrden)
						r= r->lazo;
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

		fread(&orden, sizeof(repuestos_t),1,file_p);
	}
	fclose(file_p);

	file_p = fopen("A_Deposito.dat","ab");

	//Impresión de la lista:
	aux = p;
	printf("Num. de Orden:\tCliente:\tDescripcion de Falla:\tModelo:\tCantidad:\tFecha:\t\tHora:\n");
	while(aux)
	{
		printf("%04ld\t\t%-10s\t%-20s\t%-10s\t%02d\t%-10s\t%-10s\n",aux->extraccionL.repuesto.numeroDeOrden,
			aux->extraccionL.repuesto.cliente,aux->extraccionL.repuesto.descripciondeFalla,aux->extraccionL.repuesto.modelo,
			aux->extraccionL.cantidad,aux->extraccionL.repuesto.fecha,aux->extraccionL.repuesto.hora);

		extraccion.repuesto = aux->extraccionL.repuesto;
		extraccion.cantidad = aux->extraccionL.cantidad;
		fwrite(&extraccion,sizeof(extraccionRepuestos_t),1,file_p);

		aux = aux->lazo;
	}
	printf("Archivo para deposito creado con exito...");
	fclose(file_p);

	return 0;
}
