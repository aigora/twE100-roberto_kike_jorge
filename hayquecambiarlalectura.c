///////TRABAJO INFOR

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define N 50

typedef struct {

 	char eng[N];
 	char esp[N];
 	int lleno;	
 	
}traductor;


void vacio(traductor * trad);
int anadir(FILE * pf, traductor * trad);
int traducir();
void tradu(traductor * trad, FILE * pf, int op);

int main() {

 	int num, op;
	char palabra;
 	FILE * pf;
 	traductor trad[N];
 	
 	printf ("TRADUCTOR INGLES-ESPA%cOL DE ENRIQUE ALEJANDRO RIVAS, ROBERTO VAZQUEZ Y JORGE MERCHANTE\n\n",165);
	printf ("pulse cualquier boton para empezar");
	scanf ("%c", &palabra);
 	
 	vacio(trad);
 
 	do {
 	
  		do {
  		
   			printf ("Elige una opcion:\n");
      		printf ("(1) Anadir palabras al traductor.\n");
      		printf ("(2) Buscar traduccion de la palabra en el traductor.\n");
     		scanf ("\n%i", &num);
     		rewind (stdin);
     	 
  		} while (num < 1 || num > 2);
 
 		switch (num) {
 		
  			case 1:
   				anadir(pf, trad);
 			break;
 		
  			case 2:
     			op = traducir();
     			tradu (trad, pf, op);
  			break;
  			
 		}
 		
        do {
        	
			rewind (stdin);
 			printf ("Introduce si deseas realizar otra operacion. (S/N)\n");
 			scanf ("\n%c", &palabra);
 			rewind (stdin);
 		
 			if (palabra!='s' && palabra!='S' && palabra!='n' && palabra!='N')  
 				printf("Error, introduce la letra correctamente.\n");
			 
		}while(palabra!='s' && palabra!='S' && palabra!='n' && palabra!='N');
		
 	}while(palabra == 'S'|| palabra == 's');
 
 	system ("pause");
 	return 0;
}


//------------------------------------------------------------------------------


void vacio(traductor trad[]) {
 	int i;
 	for (i=0 ; i<N ; i++) {
  		trad[i].lleno = 0;
 	}
} 


//------------------------------------------------------------------------------


int anadir(FILE * pf,traductor trad[]) {
	
 	int i, aux;
 	aux = 0;
 
 	pf = fopen("vocabulario.txt","a");
 
 	if(pf == NULL) {
 	
 		printf("Error al abrir el archivo\n");
 		return -1;
 	}
 
 	for (i=0 ; i<N && aux == 0 ; i++) {
 	
  		if (trad[i].lleno == 0) {
  	
   			printf ("Introduce la palabra en ingles.\n");
   			rewind(stdin);
   			scanf ("%s",trad[i].eng);
   
 			printf ("Introduce la palabra en espa%col.\n",164);
  			rewind(stdin);
  			scanf ("%s",trad[i].esp);
  		
  			fprintf (pf, "%s %s \n",trad[i].eng, trad[i].esp);
			  	 
 			trad[i].lleno = 1;
 			aux = 1;
 		}
 	}
 	
 	fclose(pf);
 	
 	return 1;
}


//------------------------------------------------------------------------------


int traducir() {
 	int op;
 
 	do {
 		
   		printf ("Elige que deseas hacer:\n");
      	printf ("(1) Traducir de Ingles a Espa%col.\n",164);
      	printf ("(2) Traducir de Espa%col a Ingles.\n",164);
      	scanf ("\n%i", &op);
      	
  		} while (op < 1 || op > 2);
 
 	return op;
}


//------------------------------------------------------------------------------


void tradu (traductor trad[], FILE * pf, int op) {
 	
	int i, j, temp;
 	char aux[N], basura[N];
 	
 	pf = fopen("vocabulario.txt","r");
 
 
 	temp = 0;
 
 	printf ("Introduce la palabra que desea buscar: \n");
 	rewind(stdin);
 	fscanf (stdin, "%s", aux);
 
 	if (op == 1) {
 		
  		for (i=0 ; i<N && temp==0 ; i++) {
  			
   			j = strcmp (aux, trad[i].eng);
   			
   			if (j == 0) {
   				
   				printf ("La traduccion de %s es:", trad[i].eng);
   				fscanf(pf, "%s",trad[i].esp);
   				rewind(stdin);
   				printf ("%s",trad[i].esp);
   				
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
    			fscanf(pf,"%s",trad[i].eng);
    			rewind(stdin);
    			printf ("%s",trad[i].eng);
    			
    			temp = 1;
    			break;
    			
   			} else{
   				
   				printf("La palabra buscada no esta registrada\n");
   				break;
   	
   			}
  		}
	}
	
	fclose(pf);
}


