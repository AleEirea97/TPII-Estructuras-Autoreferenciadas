#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

typedef struct
{
	long clave;
 	char d[30];
 	unsigned char tipo;
 	char b; //'A':Alta 'B':Baja
 }d_t;

typedef struct
{
	long clave_g;
 	int posicion;
 	void *lazo;
}pila_t;

int stdbit(unsigned char tipo)
{
	int a;
	a = tipo|(1<<4);

	if( (tipo - a) == 0 )
		return 1;
	else
		return 0;

}

 f37(long clave_b, pila_t *p, pila_t *aux)
{
	int pos = 0;
	d_t dat;
	FILE *file_p;


	file_p = fopen("datos.dat","rb");

	fread(&dat,sizeof(d_t),1,file_p);
	while(!feof(file_p))
	{
		pos+=1;
		if(dat.clave == clave_b)
		{
			printf("CLAVE:\tDescripcion:\tTipo:\n");
			printf("%04ld\t%-15s\t%d\n",dat.clave,dat.d,dat.tipo);
			Sleep(1000);
			if(stdbit(dat.tipo) == 1)
			{
				aux = (pila_t *)malloc(sizeof(pila_t));

				aux->clave_g = dat.clave;
				aux->posicion = pos;

				aux->lazo = p;
				p = aux;
			}
			if(p != NULL)
			{
				system("cls");
				printf("Pila Actual:\n");

				aux = p;
				while(1)
				{
					if(!aux)
						break;

					printf("\nClave: %ld",aux->clave_g);
					printf("\nPosicion:%d",aux->posicion);
					Sleep(1000);

					aux = (pila_t *)aux->lazo;
				}
			}
			return;
		}
		fread(&dat,sizeof(d_t),1,file_p);
	}
	printf("Registro no encontrado\n");
	Sleep(1500);

	fclose(file_p);
}

int main (void)
{
	long clave_b;
	pila_t *p,*aux;
	p = aux = NULL;

	while(1)
	{
		system("cls");
		printf("Ingrese la clave a buscar:");
		scanf("%ld", &clave_b);
		f37(clave_b, p, aux);
	}


 return 0;
}
