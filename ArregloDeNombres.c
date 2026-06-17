#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define CANT_NOMBRES 5

void escribirNombres(char *nombres[]);
void MostrarPersonas(char *nombres[]);
int BuscarNombre(char *nombres[]);
void mostrarBuscado(char *nombres[], int buscado);
void liberarMemoria(char *nombres[]);

int main() {
    char *nombres[CANT_NOMBRES]; //En este arreglo voy a guardar mis 5 nombres
    escribirNombres(nombres);
    MostrarPersonas(nombres);
    mostrarBuscado(nombres, BuscarNombre(nombres));
    liberarMemoria(nombres);
    return 0;
}

void escribirNombres(char *nombres[]) {
    printf("________________Sistema de registro________________\n\n");
    char *buff; //Variable auxiliar en las que escribo las cadenas
    buff=(char *)malloc(sizeof(char)*50); //Le asigno un tamaño de 50 caracteres
    int longitud; //Guardo la longitud de cada cadena ingresada en esta variable, para darle tamanio
    for (int i = 0; i < CANT_NOMBRES; i++)
    {
        printf("-El ingrese el nombre numero %d\n", i+1);
        gets(buff);
        longitud=strlen(buff)+1; //Debo sumar uno para guardar la marca final \0
        nombres[i]=(char *)malloc(sizeof(char)*longitud); //Doy un tamanio variable a cada puntero según la longitud de la cadena ingresada
        strcpy(nombres[i], buff);
    }
    free(buff);
}

void MostrarPersonas(char *nombres[]) {
    printf("\n________________Nombres ingresados al sistema________________\n\n");
    for (int i = 0; i < CANT_NOMBRES; i++)
    {
        printf("-El nombre numero %d es\n", i+1);
        puts(nombres[i]);
        printf("\n");
    }
}

int BuscarNombre(char *nombres[]) {
    char *buff;
    buff=(char *)malloc(sizeof(char)*50);
    int find=-1; //Esta variable es para confirmar si se encontró algo
    printf("\n________________Sistema de busqueda de nombres________________\n\n");
    printf("-Ingrese la busqueda: ");
    gets(buff);
    for (int i = 0; i < CANT_NOMBRES && find==-1; i++) //Agrego cómo condición find==-1 para que con la primera coincidencia salga
    {
        if (strstr(nombres[i], buff)!=NULL)
        {
            find=i;
        }
    }
    free(buff);
    return find; //Devuelve el encontrado o -1 si no encontró nada
}

void mostrarBuscado(char *nombres[], int buscado) {
    if (buscado!=-1)
    {
        printf("-El nombre que coincide con la busqueda es: ");
        puts(nombres[buscado]);
    } else {
        printf("-ERROR en la busqueda, no se hallaron coincidencias...\n");
    }
}

void liberarMemoria(char *nombres[]) {
    for (int i = 0; i < CANT_NOMBRES; i++)
    {
        free(nombres[i]);
    }
}