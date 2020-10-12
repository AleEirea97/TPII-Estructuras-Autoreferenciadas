#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

typedef struct{
	char apellido[15];
 	char nombre[15];
 	int edad;
 	long tel;
 	char mail[30];
}datos_t;

struct lista{
	datos_t info;
 	struct lista *lazo;
};

void menu (void){
	system("cls");
	printf("**MENU DE CONTROL**");
	printf("\n1. Crear Lista.");
	printf("\n2. Cargar en Archivo.");
	printf("\n3. Mostrar Lista.");	//contactos_ordenados.dat
	printf("\n4. SALIR.");
	printf("\nOPCION:");
}

int opc(void){
	int op;
	scanf("%d", &op);
	return op;
}

int main (void){

	FILE *file_p;
	struct lista *p=NULL, *u= NULL, *aux, *r;
	datos_t a;

	while(1)
	{
		menu();

		switch(opc())
		{
			case 1:

				file_p = fopen("contactos.dat","rb");

				fread(&a,sizeof(datos_t),1,file_p);
				while(!feof(file_p))
				{
				 	aux = (struct lista*)malloc(sizeof(struct lista));

					aux->info = a;

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
							if( strcmp(aux->info.apellido,r->info.apellido) == -1 )
							{
								printf("%s",aux->info.apellido );
								printf("\nPrimer lugar.\n");
								Sleep(1000);
								aux->lazo = p;	//Rutina de la pila.
								p = aux;
								break;
							}
							while(r->lazo)		//Ciclo para elemento interno.
							{
								if( strcmp( r->lazo->info.apellido, aux->info.apellido) == -1 )	{

									printf("%s",aux->info.apellido );
									r = r->lazo;}
								else
									break;
							}
							if(r == u)
							{
								printf("%s",aux->info.apellido );
								printf("\nUltimo lugar.\n");	//Rutina de la cola.
								Sleep(1000);
								u->lazo = aux;
								u=aux;
								u->lazo= NULL;
								break;
							}
							printf("%s",aux->info.apellido );
							printf("\nOtro lugar.\n");
							Sleep(1000);
							aux->lazo = r->lazo;
							r->lazo = aux;
							break;
						}
					}

					fread(&a,sizeof(datos_t),1,file_p);
 				}
				fclose(file_p);
			break;

			case 3:	//Mostrar Lista.

				aux = p;
				while(aux)
				{
					printf("\nApellido: %s",aux->info.apellido);
					printf("\nNombre: %s", aux->info.nombre);
					printf("\nEdad: %d", aux->info.edad);
					printf("\nTelefono: %ld", aux->info.tel);
					printf("\nE-Mail: %s", aux->info.mail);

					aux = aux->lazo;
				}
				system("pause");
			break;

			case 4:
				return 0;
		}
	}

	return 0;
}
