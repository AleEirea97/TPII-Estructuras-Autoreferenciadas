#include <stdio.h>
#include <stdlib.h>

typedef struct{
	unsigned char b0:1;
	unsigned char b1:1;
	unsigned char b2:1;
	unsigned char b3:1;
	unsigned char b4:1;
	unsigned char b5:1;
	unsigned char b6:1;
	unsigned char b7:1;
}fbit_t;

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

	while(1){
		menu();
		switch(opc()){

			case 1:

				aux = (cola_t *)malloc(sizeof(cola_t));
				if(aux)					//Si aux no es NULL
				{
					printf("\n Muestra:");
					scanf("%d",&aux->muestra);

					if(p == NULL)		//Tratamiento especial al ser el primer elemento.
						p=u=aux;
					else
					{
						u->lazo =(void *)aux;	//Engancha el último con el recién creado.
						u = aux;					//Actualiza  el último.
					}
					u->lazo = NULL;		//Final de cola.
				}
				else
					printf("\nMemoria Insuficiente.");

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
