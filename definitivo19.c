///////TRABAJO INFORMÁTICA 2019 
///////JORGE MERCHANTE, ENRIQUE ALEJANDRO RIVAS Y ROBERTO VÁZQUEZ
///////E-100
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Tamaño máximo de las líneas del fichero, con la entrada en español e inglés.
#define MAX_LINEA_SIZE	120

// Opciones de traducción.

// Definición de las entradas del traductor.
typedef struct {
	// No tienen tamaño fijo: se reserva dinámicamente.
 	char *eng;
 	char *esp;
 	int lleno;	
 	
} entrada_traductor_dato;

// Definición de las entradas en el diccionario: son punteros a los datos anteriores.
// Así, el diccionario es una lista de punteros.
typedef entrada_traductor_dato* entrada_traductor;

// inicia_traductor: lee el diccionario:
//	1º lo carga en memoria.
//	2º retorna el número de entradas.
int inicia_traductor(FILE *pf, entrada_traductor **traductor);

// libera_traductor: descarga de memoria
//	y libera todos los punteros a memoria que se han creado.
void libera_traductor(int contador, entrada_traductor *traductor);

// nueva_entrada: crea una nueva entrada en el diccionario.
entrada_traductor nueva_entrada(char *eng, char *esp);

// Pide los datos para añadir datos al diccionario.
int anadir(FILE * pf, int *pcontador, entrada_traductor * traductor);

// Traducción.
int opcion_traducir();
void traducir(int contador, entrada_traductor * traductor, int op);

// Muestra un listado de todas las palabras, con su traducción, que se encuentran en la memoria.  
void listado (int contador, entrada_traductor *traductor);


int main() {

 	int num, op, contador;
	char palabra;
 	FILE * pf;
 	entrada_traductor *traductor;

	// Inicializa varaibles
	traductor = NULL;
	pf = NULL;
 	
 	printf ("TRADUCTOR INGLES-ESPA%cOL DE ENRIQUE ALEJANDRO RIVAS, ROBERTO VAZQUEZ \nY JORGE MERCHANTE\n\n",165);
	system ("pause");
 	
 	contador = inicia_traductor(pf, &traductor);
 
 	do {
 	
  		do {
  		
   			printf ("Elige una opcion:\n");
      		printf ("(1) Anadir palabras al traductor.\n");
      		printf ("(2) Buscar traduccion de la palabra en el traductor.\n");
      		printf ("(3) Listado de palabras.\n");
     		scanf ("\n%i", &num);
     		rewind (stdin);
     	 
  		} while (num < 1 || num > 3);
 
 		switch (num) {
 		
  			case 1:
   				anadir(pf, &contador, traductor);
 			break;
 		
  			case 2:
     			op = opcion_traducir();
     			traducir (contador, traductor, op);
  			break;
  			
  			case 3:
  				listado (contador, traductor);
  			break;
 		}
 		
        do {
        	
			rewind (stdin);
 			printf ("\n\nIntroduce si deseas realizar otra operacion. (S/N)\n");
 			scanf ("\n%c", &palabra);
 			rewind (stdin);
 		
 			if (palabra!='s' && palabra!='S' && palabra!='n' && palabra!='N')  
 				printf("Error, introduce la letra correctamente.\n");
			 
		}while(palabra!='s' && palabra!='S' && palabra!='n' && palabra!='N');
		
 	}while(palabra == 'S'|| palabra == 's');
 
	libera_traductor(contador, traductor);

 	system ("pause");
 	return 0;
}


//------------------------------------------------------------------------------

entrada_traductor nueva_entrada(char *eng, char *esp) {
	entrada_traductor e = (entrada_traductor)malloc(sizeof(entrada_traductor_dato));

	// si 'e' no es NULL, ha ido bien.
	if (e != NULL) {
		// También hay que reservar memoria para los datos de cada entrada,
		// (habrá que comprobar si no son NULL).
		e->eng = (char*)malloc((strlen (eng) + 1)*sizeof(char));
		strcpy(e->eng, eng); 
		e->esp = (char*)malloc((strlen (esp) +1) * sizeof(char));
		strcpy(e->esp, esp); // Se pasa de la variable temporal ,que se recoge del fichero que se ha descrito como parámetro, por ejemplo: char *eng = english 
		e->lleno = 1; // (en la función inicia traductor) a el dato que va a ir en el traductor de verdad, el de la estructura (e->eng).
	}
	return e;
}


//----------------------------------------------------------------------------------

int inicia_traductor(FILE *pf, entrada_traductor **traductor) {
	int contador;
	char temp[MAX_LINEA_SIZE], english[MAX_LINEA_SIZE], spanish[MAX_LINEA_SIZE]; // Variables temporales que recogen la información del fichero.
	char *coma, *end;

	pf = fopen("vocabulario.txt", "r");

	if (pf == NULL) {

		printf("No se ha podido abrir el archivo.\n");
		exit(1);
	}

	contador = 0;

	// cuenta las líneas para poder crear el diccionario.
	while (!feof(pf)) {

		fgets(temp, MAX_LINEA_SIZE, pf);
		contador++;
	}

	// Deja el puntero al principio para procesar las entradas.
	rewind(pf);

	// Crea un array de entradas vacías.
	*traductor = (entrada_traductor*)malloc(contador * sizeof(entrada_traductor*));

	contador = 0;
	
	while (!feof(pf)) {
		// lee de disco una entrada.
		fgets(temp, MAX_LINEA_SIZE, pf);

		// quita el "salto de línea" final.
		if (temp[strlen(temp) - 1] == '\n') temp[strlen(temp) - 1] = '\0';

		// separa los datos, busca la coma con 'strchr'.
		coma = strchr(temp, ',');
		if (coma) {
			// si hay coma, lo de antes es inglés; lo de después, español.
			*coma = 0;
			strcpy(english, temp);
			strcpy(spanish, coma + 1);
		}
		// si la entrada está mal se continúa.
		else continue;

		entrada_traductor e = nueva_entrada(english, spanish);
		if (e == NULL) {
			printf("No se ha podido crear una nueva entrada.\n");
			exit(1);
		}

		(*traductor)[contador++] = e;
	}

	fclose(pf);

	return contador;
}

void libera_traductor(int contador, entrada_traductor *traductor) {
	int i;
	for (i = 0; i < contador; i++) {
		entrada_traductor e = traductor[i];

		// libera los strings con los datos.
		free(e->eng);
		free(e->esp);

		// libera la propia entrada, que también es un puntero.
		free(e);
	}

	// libera el propio traductor, que también es un puntero.
	free(traductor);
}

//------------------------------------------------------------------------------


int anadir(FILE * pf, int *pcontador, entrada_traductor *traductor) {
	
	char english[MAX_LINEA_SIZE], spanish[MAX_LINEA_SIZE]; 
	char respuesta;
	
 	pf = fopen("vocabulario.txt","a");
 
 	if (pf == NULL) {
 	
 		printf("Error al abrir el archivo\n");
 		exit(1);
 	}

do {

	// Pide datos.
	printf("Introduce la palabra en ingles.\n");
	rewind(stdin);
	scanf("%s", english);

	printf("Introduce la palabra en espa%col.\n", 164);
	rewind(stdin);
	scanf("%s", spanish);

	// Crea una nueva entrada y actualiza el número de entradas.
	entrada_traductor e = nueva_entrada(english, spanish);
	if (e == NULL) {
		printf("No se ha podido crear una nueva entrada.\n");
		exit(1);
	}

	traductor[(*pcontador)++] = e;

	// Añade al fichero la nueva palabra con su tradución.
  	fprintf (pf, "%s,%s\n", e->eng, e->esp);
 	
 	do {
 	rewind (stdin);
 	printf ("Desea introducir otra palabra? [S/N]\n");
 	scanf ("\n%c",&respuesta);
 	rewind (stdin);
 	
 	if (respuesta!='s' && respuesta!='S' && respuesta!='n' && respuesta!='N')  {
 		printf("Error, introduce la letra correctamente.\n"); 
	}
 	
} while (respuesta!='s' && respuesta!='S' && respuesta!='n' && respuesta!='N');
 	
} while (respuesta == 'S' || respuesta == 's' );
 	
 	
 	
 	fclose(pf);
 	
 	return 1;
}


//------------------------------------------------------------------------------


int opcion_traducir() {
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


void traducir(int contador, entrada_traductor * traductor, int op) {
 	
	int i, j;
	char temp[MAX_LINEA_SIZE];

 	rewind (stdin);
 	printf ("Introduce la palabra que desea buscar: \n");
 	fscanf (stdin, "%s", temp);
	rewind(stdin);
	 
 	if (op == 1) {
 		// Inglés a español.
  		for (i=0 ; i<contador; i++) {
  			
   			j = strcmp (temp, traductor[i]->eng);
   			
   			if (j == 0) {
   				
   				printf ("La traduccion de %s es: %s\n", traductor[i]->eng, traductor[i]->esp);
   				break;
   				 
  			}
   		}

	}
   		
 	else {
 		// Español a inglés.
		for (i = 0; i<contador; i++) {

			j = strcmp(temp, traductor[i]->esp);

   			if (j == 0) {
   				
				printf("La traduccion de %s es: %s\n", traductor[i]->esp, traductor[i]->eng);
				break;
    			
   			}
  		}
	}

	if (i == contador) {
		// Llegó al final del contador sin encontrar la palabra.
		printf("La palabra buscada no esta registrada\n");
	}
}


//------------------------------------------------------------------------------


void listado (int contador, entrada_traductor *traductor) {
	
	int i;
	
	for (i=0; i<contador; i++) {
		
		printf ("Ingles: %s   Espa%col: %s\n", traductor[i]->eng, 164, traductor[i]->esp);
	}
}



























