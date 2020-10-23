#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

typedef struct{
	char desc[60];
    unsigned char potencia;
    unsigned int estado;
}data_t;

typedef struct{
	int id;
	char desc[60];
    unsigned char potencia;
    unsigned int estado;
}dataA_t;

struct lista{
	data_t pot;
 	struct lista *lazo;
};

void menu (void){
	system("cls");
	printf("**MENU DE CONTROL**");
	printf("\n1. Cargar datos.");
	printf("\n2. Guardar en Archivo.");		//potencia.dat
	printf("\n3. SALIR.");
	printf("\nOPCION:");
}

int opc(void){
	int op;
	scanf("%d", &op);
	fflush(stdin);
	return op;
}

void genA(dataA_t pot){
	FILE *file_p;
	file_p = fopen("potencia.dat","wb");

	pot.id = 1;
	strcpy(pot.desc," ");
	pot.potencia = 0;
	pot.estado = 0;
	fwrite(&pot,sizeof(dataA_t),1,file_p);
	fclose(file_p);
}

int main (void){

	FILE *file_p;
	struct lista *p=NULL, *u= NULL, *aux, *r;

	dataA_t pot;
	genA(pot);

	while(1){
		menu();

		switch(opc()){

			case 1:

				aux = (struct lista*)malloc(sizeof(struct lista));

				//Ingreso de datos:
				printf("Ingrese Descripcion.");
				gets(aux->pot.desc);
				printf("Ingrese la potencia.");
				scanf("%d",&aux->pot.potencia);

				aux->pot.estado = aux->pot.desc[0]*aux->pot.potencia;
				//Fin ingreso de datos.

				if(p == NULL) // Si esta vacia..es el primer elemento.
				{
					p = u = aux;
					u->lazo = NULL;
					printf("Primer elemento.");
					Sleep(1000);
				}
				else
				{
					r=p;
					while(1)
					{
						if(r->pot.potencia < aux->pot.potencia)
						{
							printf("\nPrimer lugar.\n");
							system("pause");
							aux->lazo = p;	//Rutina de la pila.
							p = aux;
							break;
						}
						while(r->lazo)		//Ciclo para elemento interno.
						{
							if(r->lazo->pot.potencia > aux->pot.potencia)
								r= r->lazo;
							else
								break;
						}
						if(r == u)
						{
							printf("\nUltimo lugar.\n");	//Rutina de la cola.
							system("pause");
							u->lazo = aux;
							u=aux;
							u->lazo= NULL;
							break;
						}
						printf("\nOtro lugar.\n");
						system("pause");
						aux->lazo = r->lazo;
						r->lazo = aux;
						break;
					}
				}
			break;

			case 2:

				file_p = fopen("potencia.dat","rb+");	//El archivo ya tiene que estar creado.

				aux = p;
				while(aux)
				{
					printf("\nDescripcion:%s", aux->pot.desc);
					printf("\nPotencia:%d", aux->pot.potencia);
					printf("\nEstado:%d\n",aux->pot.estado);

					fseek(file_p, (-1L)*sizeof(dataA_t), 2);
					fread(&pot,sizeof(dataA_t),1,file_p);

					pot.id++;
					fseek(file_p, 0L, 2);

					strcpy(pot.desc,aux->pot.desc);
					pot.potencia = aux->pot.potencia;
					pot.estado = aux->pot.estado;

					fwrite(&pot,sizeof(dataA_t),1,file_p);

					aux = aux->lazo;
				}
				fclose(file_p);
			system("pause");
			break;

			case 3:
				return 0;

			case 4://Mostrar LISTA.
				aux = p;
				while(aux)
				{
					printf("\nDescripcion:%s", aux->pot.desc);
					printf("\nPotencia:%d", aux->pot.potencia);
					printf("\nEstado:%d\n",aux->pot.estado);

					aux = aux->lazo;
				}
			system("pause");
			break;

			case 5:
				system("cls");

				file_p = fopen("potencia.dat","rb");

				fread(&pot,sizeof(dataA_t),1,file_p);
				printf("ID:\tDESCRIPCION:\tPotencia.:\tEstado:\n");

				while(!feof(file_p))
				{

					printf("%03d\t%-20s\t%d\t%d\n",pot.id,pot.desc,pot.potencia,pot.estado);

					fread(&pot,sizeof(dataA_t),1,file_p);
				}

				fclose(file_p);
				system("pause");
			break;
		}
	}

	return 0;
}
