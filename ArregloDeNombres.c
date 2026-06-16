#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define CANT_NOMBRES 5

void escribirNombres(char *nombres[]);
void MostrarPersonas(char *nombres[]);
void liberarMemoria(char *nombres[]);

int main() {
    char *nombres[CANT_NOMBRES]; //En este arreglo voy a guardar mis 5 nombres
    escribirNombres(nombres);
    MostrarPersonas(nombres);
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

void liberarMemoria(char *nombres[]) {
    for (int i = 0; i < CANT_NOMBRES; i++)
    {
        free(nombres[i]);
    }
}