#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
   long partNumber;
   long serialNumber;
   char descripcion[40];
   char ubicacion[100];
   int cantidad;
}repuestos_tt;

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

int main (void)
{

	FILE *file_p;
	FILE *file_p1;
	extraccionRepuestos_t extraccion;
	repuestos_tt repuestoA;
	char *p;

	file_p = fopen("A_Deposito.dat","rb");

	fread(&extraccion,sizeof(extraccionRepuestos_t),1,file_p);
	//printf("Num. de Orden:\tCliente:\tDescripcion de Falla:\tModelo:\tCantidad:\tFecha:\t\tHora:\n");

	while(!feof(file_p))
	{

		p = strstr(extraccion.repuesto.descripciondeFalla, "Luces");
		if(p != NULL)
		{
			file_p1 = fopen("stock.dat","rb+");
			fread(&repuestoA,sizeof(repuestos_tt),1,file_p1);

			while(!feof(file_p1))
			{
				if( strcmp(repuestoA.descripcion,"Luces\0") == 0)
				{
					repuestoA.cantidad = repuestoA.cantidad - extraccion.cantidad;
					fseek(file_p1, (-1L)*sizeof(repuestos_tt), 1);
					fwrite(&repuestoA,sizeof(repuestos_tt),1,file_p1);
					fclose(file_p1);
					break;
				}
				fread(&repuestoA,sizeof(repuestos_tt),1,file_p1);
			}
		}
		system("pause");

		p = strstr(extraccion.repuesto.descripciondeFalla, "Bateria");
		if(p != NULL)
		{
			file_p1 = fopen("stock.dat","rb+");
			fread(&repuestoA,sizeof(repuestos_tt),1,file_p1);

			while(!feof(file_p1))
			{
				if( strcmp(repuestoA.descripcion,"Baterias\0") == 0)
				{
					repuestoA.cantidad = repuestoA.cantidad - extraccion.cantidad;
					fseek(file_p1, (-1L)*sizeof(repuestos_tt), 1);
					fwrite(&repuestoA,sizeof(repuestos_tt),1,file_p1);
					fclose(file_p1);
					break;
				}
				fread(&repuestoA,sizeof(repuestos_tt),1,file_p1);
			}
		}
		system("pause");

		p = strstr(extraccion.repuesto.descripciondeFalla, "Parlante");
		if(p != NULL)
		{
			file_p1 = fopen("stock.dat","rb+");
			fread(&repuestoA,sizeof(repuestos_tt),1,file_p1);

			while(!feof(file_p1))
			{
				if( strcmp(repuestoA.descripcion,"Parlantes\0") == 0)
				{
					repuestoA.cantidad = repuestoA.cantidad - extraccion.cantidad;
					fseek(file_p1, (-1L)*sizeof(repuestos_tt), 1);
					fwrite(&repuestoA,sizeof(repuestos_tt),1,file_p1);
					fclose(file_p1);
					break;
				}
				fread(&repuestoA,sizeof(repuestos_tt),1,file_p1);
			}
		}
		system("pause");
		//printf("%04ld\t\t%-10s\t%-20s\t%-10s\t%d\t%-10s\t%-10s\n",extraccion.repuesto.numeroDeOrden,extraccion.repuesto.cliente,
			//extraccion.repuesto.descripciondeFalla,extraccion.repuesto.modelo,extraccion.cantidad,extraccion.repuesto.fecha,extraccion.repuesto.hora);
		fread(&extraccion,sizeof(extraccionRepuestos_t),1,file_p);
	}
	fclose(file_p);


	return 0;
}
