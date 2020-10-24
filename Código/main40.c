#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
	int id;
	char desc[60];
    unsigned char potencia;
    unsigned int estado;
}dataA_t;

typedef struct
{
	unsigned char potencia;
    void *lazo;
} pila_t;

int stdbits(unsigned int estado)
{
	int a,b;

	a = estado|(1<<0);
	b = estado|(1<<2);

	if( ((estado - a) == 0) && ((estado -b) == 0)  )
		return 1;
	else
		return 0;

}

void strrev_t(char *str1)
{
	char str2[10] = " ";
	int a;
	char *p;

	p = str1;
	while(*p != ' ')
		p++;
	*p = 0;

	p = str1;

	for(int i = strlen(str1); i > -1; i--)
	{
		strcat(str2,p+i);
		*(p+i) = 0;
	}

	printf("Cadena Reversa:%s\n",str2);
}

void f40(int idb)
{
	FILE *file_p;
	FILE *file_p1;
	dataA_t pot;

	pila_t *p,*aux;
	p = aux = NULL;

	file_p = fopen("potencia.dat","rb");

	fseek(file_p, (1L)*sizeof(dataA_t)*(idb-1), 0);
	fread(&pot,sizeof(dataA_t),1,file_p);

	if(pot.id == idb)
	{
		printf("ID:\tDESCRIPCION:\tPotencia.:\tEstado:\n");
		printf("%03d\t%-20s\t%d\t%d\n",pot.id,pot.desc,pot.potencia,pot.estado);

		strrev_t(pot.desc);

		if( stdbits(pot.estado) )
		{
				aux = (pila_t *)malloc(sizeof(pila_t));
				aux->potencia = pot.potencia;
				aux->lazo = p;
				p = aux;
		}
		else
		{
			file_p1 = fopen("salida.dat","ab+");
			fwrite(&pot,sizeof(dataA_t),1,file_p1);
			fclose(file_p1);
		}

	}
	else
		printf("Registro no encontrado.\n");

	fclose(file_p);
}


int main (void){

	int idb;

	printf("Ingrese el ID  a buscar:\n");
	scanf("%d", &idb);

	f40(idb);

	return 0;
}
