#include <stdio.h>
#include <stdlib.h>

typedef struct{
	char nombre[15];
	char apellido[15];
	int edad;
	long tel;
	char mail[30];
}datos_t;

typedef struct {
    datos_t info;
    void *lazo;
} pila_t;

void menu (void){
	system("cls");
	printf("**MENU DE CONTROL**");
	printf("\n1. Cargar Datos.");		//Carga en pila.
	printf("\n2. Cargar Datos en Archivo.");
	printf("\n3. Mostrar Archivo.");	//Contactos.dat
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
	pila_t *p,*aux;
	p = aux = NULL;
	datos_t info_A;

	while(1){

		menu();

		switch(opc()){

			case 1:
				fflush(stdin);
				system("cls");

				aux = (pila_t *)malloc(sizeof(pila_t));

				printf("Ingrese su nombre:");
				gets(aux->info.nombre);

				printf("Ingrese su apellido:");
				gets(aux->info.apellido);

				fflush(stdin);

				printf("Ingrese su edad:");
				scanf("%d", &aux->info.edad);

				printf("Ingrese su telefono:");
				scanf("%ld", &aux->info.tel);

				fflush(stdin);

				printf("Ingrese su direccion de e-mail:");
				gets(aux->info.mail);

				aux->lazo = p;

				p = aux;

				system("pause");
			break;

			case 2:
				system("cls");

				file_p = fopen("contactos.dat","ab");

				aux = p;

				while(1)
				{
					if(!aux)
						break;

					if (aux->info.edad > 21)
					{
						printf("\nApellido: %s",aux->info.apellido);
						printf("\nNombre: %s", aux->info.nombre);
						printf("\nEdad: %d",aux->info.edad);
						printf("\nTelefono: %ld", aux->info.tel);
						printf("\nE-Mail: %s", aux->info.mail);

						fwrite(&aux->info,sizeof(datos_t),1,file_p);
					}
					aux = (pila_t *)aux->lazo;
				}
				fclose(file_p);

				system("pause");
			break;

			case 3:
				system("cls");

				file_p = fopen("contactos.dat","rb");

				fread(&info_A,sizeof(datos_t),1,file_p);

				while(!feof(file_p)){
					printf("\nApellido: %s",info_A.apellido);
					printf("\nNombre: %s", info_A.nombre);
					printf("\nEdad: %d", info_A.edad);
					printf("\nTelefono: %ld", info_A.tel);
					printf("\nE-Mail: %s", info_A.mail);
					fread(&info_A,sizeof(datos_t),1,file_p);

					printf("\n\n");
				}
				fclose(file_p);

				system("pause");
			break;

			case 4:
				return 0;

			case 5://Borra el contenido del archivo al pisarlo con uno nuevo.
				file_p = fopen("contactos.dat", "wb");
			break;
		}
	}

	return 0;
}
