#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int muestra;
    void *lazo;
}cola_t;

void menu (void){
	system("cls");
	printf("**Menu de Control**");
	printf("\n1-Muestrear");	//Carga de cola
	printf("\n2-Mostrar");
	printf("\n3-Salir\n");
	printf("Opcion:");
}

int opc(void){
	int op;
	scanf("%d", &op);
	return op;
}

int main (void){

	cola_t *p = NULL, *u = NULL, *aux;
	int muestra[8] = {0,64,81,90,97,110,119,127};
	
	while(1){
		menu();
		switch(opc()){

			case 1:

					for(int i = 0; i < 8; i ++)
					{
						printf("\n Muestreando...");
						system("cls");

						aux = (cola_t *)malloc(sizeof(cola_t));

						if(aux)					//Si aux no es NULL
						{
							aux->muestra = muestra[i];

							if(p == NULL)					//Tratamiento especial al ser el primer elemento.
								p=u=aux;
								else
								{
									u->lazo =(void *)aux;		//Engancha el último con el recién creado.
									u = aux;					//Actualiza  el último.
								}
								u->lazo = NULL;					//Final de cola.
							}
							else
									printf("\nMemoria Insuficiente.");
						}

						system("pause");
						break;

			case 2:

				aux = p;
				while(aux)
				{
					printf("%d\t", aux->muestra);
					aux = (cola_t *)aux->lazo;
				}

				system("pause");
				break;

			case 3:
				return 0;
		}

	}

	return 0;
}
