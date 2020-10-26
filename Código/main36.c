#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

typedef struct{
	char nombre_apellido[30];
 	int edad;
 	long tel;
 	char mail[30];
}datos_t;

typedef struct{
	int id;
	char nombre_apellido[30];
 	int edad;
 	long tel;
 	char mail[30];
}datosA_t;

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

void genA(datosA_t infoA){
	FILE *file_p;
	file_p = fopen("contactos_ordenados.dat","ab");

	infoA.id = 1;
	strcpy(infoA.nombre_apellido," ");
	infoA.edad = 0;
	infoA.tel = 0;
	strcpy(infoA.mail," ");

	fwrite(&infoA,sizeof(datosA_t),1,file_p);
	fclose(file_p);
}

int main (void){

	FILE *file_p;
	struct lista *p=NULL, *u= NULL, *aux, *r;
	datos_t a;

	datosA_t infoA;
	//genA(infoA);

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
						//printf("Primer elemento.");
					}
					else
					{
						r=p;
						while(1)
						{
							if( strcmp( aux->info.nombre_apellido, r->info.nombre_apellido ) == -1 )
							{
								//printf("\nPrimer lugar.\n");
								aux->lazo = p;	//Rutina de la pila.
								p = aux;
								break;
							}
							while(r->lazo)		//Ciclo para elemento interno.
							{
								if( strcmp( r->lazo->info.nombre_apellido, aux->info.nombre_apellido ) == -1 )
									r = r->lazo;
								else
									break;
							}
							if(r == u)
							{
								//printf("\nUltimo lugar.\n");	//Rutina de la cola.
								u->lazo = aux;
								u=aux;
								u->lazo= NULL;
								break;
							}
							//printf("\nOtro lugar.\n");
							aux->lazo = r->lazo;
							r->lazo = aux;
							break;
						}
					}

					fread(&a,sizeof(datos_t),1,file_p);
 				}
				fclose(file_p);
				printf("Lista creada con exito..\n");
				system("pause");
			break;

			case 2:
				file_p = fopen("potencia.dat","rb+");

				aux = p;
				while(aux)
				{
					printf("\nNombre y Apellido:%s", aux->info.nombre_apellido);
					printf("\nEdad:%d", aux->info.edad);
					printf("\nTelefono:%ld",aux->info.tel);
					printf("\nE - Mail:%s",aux->info.mail);

					fseek(file_p, (-1L)*sizeof(datosA_t), 2);
					fread(&infoA,sizeof(datosA_t),1,file_p);

					infoA.id++;
					fseek(file_p, 0L, 2);

					strcpy(infoA.nombre_apellido,aux->info.nombre_apellido);
					infoA.edad = aux->info.edad;
					infoA.tel = aux->info.tel;
					strcpy(infoA.mail,aux->info.mail);

					fwrite(&infoA,sizeof(datosA_t),1,file_p);

					aux = aux->lazo;
				}
				fclose(file_p);
				system("pause");

			break;

			case 3:	//Mostrar Lista.

				aux = p;
				printf("Nombre y Apellido:\tEdad:\tTelefono:\tE-mail:\n");
				while(aux)
				{
					printf("\n%-10s\t\t%d\t%ld\t%-10s\n",aux->info.nombre_apellido, aux->info.edad, aux->info.tel, aux->info.mail);

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
