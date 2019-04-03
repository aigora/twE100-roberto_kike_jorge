///////TRABAJO INFOR

#include <stdio.h>
#include <string.h>
#include<stdlib.h>
#define N 50

typedef struct {
 	char eng[N];
 	char esp[N];
 	int lleno;	
	}traductor;


	void vacio(traductor*trad);
	int anadir(FILE**palabras,traductor*trad);
	int traducir();
	void tradu(int op,traductor*trad,FILE**palabras);

int main() {
 	int num, op;
	char palabra;
 	FILE *palabras;
 	traductor trad[N];
 	
 	printf("TRADUCTOR INGLES-ESPA%cOL DE ENRIQUE ALEJANDRO RIVAS, ROBERTO VAZQUEZ Y JORGE MERCHANTE\n\n",165);
 	
 	vacio(trad);
 	if (anadir(&palabras,trad) == -1) exit(1);
 
 do {
 	
  	do {
  		
   		printf ("Elige una opcion:\n");
      	printf ("(1) Anadir palabras al traductor.\n");
      	printf ("(2) Buscar traduccion de la palabra en el traductor.\n");
     	scanf ("%i", &num);
     	
     	 
  		} while (num < 1 || num > 2);
 
 	switch (num) {
 		
  		case 1:
   			anadir(&palabras, trad);
 		break;
 		
  		case 2:
     		op = traducir();
     		tradu (op ,trad,&palabras);
  		break;
 }
        do{
		
 		printf ("Introduce si deseas realizar otra operacion. (S/N)\n");
 		scanf ("%c", &palabra);
 		
 		if (palabra!='s' && palabra!='S' && palabra!='n' && palabra!='N')  {
 			
 			printf("Error la respuesta no es valida\n");
 			break;
		 }
		}while(palabra!='s' && palabra!='S' && palabra!='n' && palabra!='N');
		
 		}while(palabra != 'S'|| palabra != 's');
 
 	system ("pause");
 	return 0;
}
/////////
void vacio(traductor trad[]) {
 	int i;
 	for (i=0 ; i<N ; i++) {
  		trad[i].lleno = 0;
 	}
} 
//////
int anadir(FILE **palabras,traductor trad[]) {
	
 	int i, aux;
 	aux = 0;
 
 	*palabras=fopen("vocabulario.txt","a");
 
 	if(*palabras==NULL){
 	
 		printf("Error al abrir el archivo\n");
 		return -1;
 	}
 
 	for (i=0 ; i<N && aux == 0 ; i++) {
 	
  		if (trad[i].lleno == 0) {
  	
   			printf ("Introduce la palabra en ingles.\n");
   			rewind(stdin);
   			fgets (trad[i].eng,N,stdin);
   
 			printf ("Introduce la palabra en espa%col.\n",164);
  			rewind(stdin);
  			fgets (trad[i].esp,N,stdin);
  		
  		
  			fprintf(*palabras,"%s",trad[i].esp);
  	 
 			trad[i].lleno = 1;
 			aux = 1;
 		}
 	}
 	fclose(*palabras);
 	
 	return 1;
}
///////////
int traducir() {
 	int op;
 
 	do {
 		
   		printf ("Elige que deseas hacer:\n");
      	printf ("(1) Traducir de Ingles a Espa%col.\n",164);
      	printf ("(2) Traducir de Espa%col a Ingles.\n",164);
      	scanf ("%i", &op);
      	
  		} while (op < 1 || op > 2);
 
 	return op;
}

//////////
void tradu(int op,traductor trad[],FILE **palabras) {
 	
	int i, j, temp;
 	char aux[N];
 	
 	*palabras=fopen("vocabulario.txt","r");
 
 
 	temp = 0;
 
 	printf ("Introduce la palabra que desea buscar: \n");
 	rewind(stdin);
 	fgets (aux,N,stdin);
 	aux[strlen(aux)-1] = '\0';
 
 	if (op == 1) {
 		
  		for (i=0 ; i<N && temp==0 ; i++) {
  			
   			j = strcmp (aux, trad[i].eng);
   			
   			if (j == 0) {
   				
   				printf ("La traduccion de %s es:\n", trad[i].eng);
   				fscanf(*palabras,"%c",trad[i].esp);
   				rewind(stdin);
   				
   				
   				temp = 1;
   				break;
   				 
  			} else{
  				
   				printf("La palabra buscada no esta registrada\n");
   				break;
   				
   			}
   		}
   	}

 	else {
 		
   		for (i=0 ; i<N && temp==0 ; i++) {
   			
   			j = strcmp (aux, trad[i].esp);
   			
   			if (j == 0) {
   				
    			printf ("La traduccion de %s es:\n", trad[i].esp);
    			fscanf(*palabras,"%c",trad[i].eng);
    			rewind(stdin);
    			
    			
    			temp = 1;
    			break;
    			
   			} else{
   				
   				printf("La palabra buscada no esta registrada\n");
   				break;
   	
   			}
  		}
	}
	
	fclose(*palabras);
}

///////////

