#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int cantidad_clientes=0; //Un max de 5. La declaro global ya que la usaré en muchas funciones
char *TiposProductos[]={"Galletas", "Snack", "Cigarrillos", "Caramelos", "Bebidas"};  
typedef struct{ 
    int ProductoID;    //Numerado en ciclo iterativo   
    int Cantidad;    // entre 1 y 10
    char *TipoProducto;    // Algún valor del arreglo TiposProductos
    float PrecioUnitario;    // entre 10 - 100
} Producto;

typedef struct{   
    int ClienteID;    // Numerado en el ciclo iterativo            
    char *NombreCliente;    // Ingresado por usuario
    int CantidadProductosAPedir;    // (aleatorio entre 1 y 5) 
    Producto *Productos;    //El tamaño de este arreglo depende de la variable “CantidadProductosAPedir”  
} Cliente;

// void cargarProductos(Cliente *clientes, int j);
void cargarDatosCliente(Cliente *clientes, int i);
void cargarClientes(Cliente *clientes);
void liberarMemoria(Cliente *clientes);

int main() {
    srand(time(NULL)); //Creo que una semilla con la hora actual
    Cliente *clientes; //Este puntero me servirá para almacenar los clientes que pidieron productos
    cargarClientes(clientes); //Cargo todo
    liberarMemoria(clientes); //Libero la memoria reservada de todos los punteros
    return 0;
}

// void cargarProductos(Cliente *clientes, int j);

void cargarDatosCliente(Cliente *clientes, int i) {
    char *buff; //Voy a usar un puntero auxiliar para cargar los nombres
    buff=malloc(sizeof(char)*50); 
    int long_nombre=0;
    clientes[i].ClienteID=i+1; //Mi id va a ser el número que va en interacion +1
    printf("__Cliente numero: %d__\n", clientes[i].ClienteID);
    printf("-Ingrese el nombre del cliente: ");
    fflush(stdin); //Limpio el buffer
    gets(buff);
    long_nombre=strlen(buff)+1;
    //Reservo la memoria para el nombre
    clientes[i].NombreCliente=malloc(sizeof(char)*long_nombre);
    strcpy(clientes[i].NombreCliente, buff);
    free(buff); //Libero la memoria utilizada
    clientes[i].CantidadProductosAPedir=rand()%5+1; //De uno a 5 productos por cliente
    for (int j = 0; j < clientes[i].CantidadProductosAPedir; j++) //Aca se  usa clientes[i] porque es el numero de cliente
    {
        // cargarProductos(clientes, j);
    }
}

void cargarClientes(Cliente *clientes) {
    printf("________________INICIADO SISTEMA DE PREVENTISTAS...________________\n\n");
    do //Me aseguro que sea entre 1 y 5
    {
        printf("-Ingrese cuantos clientes va a visitar hoy: ");
        scanf("%d", &cantidad_clientes);
        if (cantidad_clientes>6)
        {
            printf("ERROR: No se puede visitar mas de 5 clientes\n");
        } else if (cantidad_clientes<1)
        {
            printf("ERROR: Debe visitar al menos un cliente\n");
        }
    } while (cantidad_clientes>6||cantidad_clientes<1);
    clientes=malloc(sizeof(Cliente)*cantidad_clientes); //Hago que reserve la memoria que necesito
    for (int i = 0; i <cantidad_clientes; i++)
    {
        printf("\n\n________________Sistema de registro de clientes________________\n\n");
        cargarDatosCliente(clientes, i); //Mi ID va ser la i que pase +1, para empezar de 1 en adelante
    }
}

void liberarMemoria(Cliente *clientes) {
    for (int i = 0; i < cantidad_clientes; i++)
    {
        free(clientes[i].NombreCliente);
        free(clientes[i].Productos);
    }
    free(clientes);
}