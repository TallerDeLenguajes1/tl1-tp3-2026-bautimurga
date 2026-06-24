#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int cantidad_clientes=0; //Un max de 5. La declaro global ya que la usaré en muchas funciones
char *TiposProductos[]={"Galletas", "Snack", "Cigarrillos", "Caramelos", "Bebidas"};
//Este arreglo lo creo para que cada producto tenga un precio determinado
float PrecioProd[]={37.5, 18.2, 99.5, 11.7, 57.3};
//Voy a hacer dos variables para mostrar el total a pagar por producto y el total del cliente
float total_prod=0;
float total_cliente=0;
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

Cliente *clientes; //Este puntero me servirá para almacenar los clientes que pidieron productos

float calcularTotalProducto(Producto prod);
void cargarProductos(int i, int j);
void cargarDatosCliente(int i);
void cargarClientes();
void liberarMemoria();

int main() {
    srand(time(NULL)); //Creo que una semilla con la hora actual
    cargarClientes(); //Cargo todo
    liberarMemoria(); //Libero la memoria reservada de todos los punteros
    return 0;
}

float calcularTotalProducto(Producto prod) {
    return prod.PrecioUnitario*prod.Cantidad;
}

void cargarProductos(int i, int j) {
    clientes[i].Productos[j].ProductoID=j+1; //Mi ID va a ir de 1 en adelante
    printf("\n__Cargando datos de producto %d__\n", clientes[i].Productos[j].ProductoID);
    clientes[i].Productos[j].Cantidad=rand()%10+1; //Entre 1 y 10
    //Voy a generar un entero random entre 0 y 4 para determinar el tipo de producto y su precio
    int tipo=0;
    tipo=rand()%5;
    clientes[i].Productos[j].TipoProducto=TiposProductos[tipo];
    clientes[i].Productos[j].PrecioUnitario=PrecioProd[tipo];
    printf("El cliente pidio %d unidades de %s y el precio por unidad es $%.2f\n", clientes[i].Productos[j].Cantidad, clientes[i].Productos[j].TipoProducto, clientes[i].Productos[j].PrecioUnitario);
    total_prod=calcularTotalProducto(clientes[i].Productos[j]);
    printf("El total del producto es $%.2f\n", total_prod);
}

void cargarDatosCliente(int i) {
    char *buff; //Voy a usar un puntero auxiliar para cargar los nombres
    buff=malloc(sizeof(char)*50); 
    int long_nombre=0;
    clientes[i].ClienteID=i+1; //Mi id va a ser el número que va en interacion +1
    printf("_______Cliente numero: %d_______\n", clientes[i].ClienteID);
    printf("-Ingrese el nombre del cliente: ");
    fflush(stdin); //Limpio el buffer
    gets(buff);
    long_nombre=strlen(buff)+1;
    //Reservo la memoria para el nombre
    clientes[i].NombreCliente=malloc(sizeof(char)*long_nombre);
    strcpy(clientes[i].NombreCliente, buff);
    free(buff); //Libero la memoria utilizada
    printf("El nombre del cliente es %s\n", clientes[i].NombreCliente);
    clientes[i].CantidadProductosAPedir=rand()%5+1; //De uno a 5 productos por cliente
    printf("La cantidad de tipos de productos que pidio el cliente es de %d\n", clientes[i].CantidadProductosAPedir);
    /*Le doy el tamaño que necesito al puntero de productos del cliente*/
    clientes[i].Productos=malloc(sizeof(Producto)*clientes[i].CantidadProductosAPedir);
    for (int j = 0; j < clientes[i].CantidadProductosAPedir; j++) //Aca se  usa clientes[i] porque es el numero de cliente
    {
        cargarProductos(i, j);
        total_cliente+=total_prod;
    }
    printf("\n__________TOTAL A PAGAR: $%.2f__________\n", total_cliente);
    total_cliente=0; //Debo reiniciar para el próximo cliente
}

void cargarClientes() {
    printf("________________INICIADO SISTEMA DE PREVENTISTAS...________________\n\n");
    do //Me aseguro que sea entre 1 y 5
    {
        printf("-Ingrese cuantos clientes va a visitar hoy: ");
        scanf("%d", &cantidad_clientes);
        if (cantidad_clientes>5)
        {
            printf("ERROR: No se puede visitar mas de 5 clientes\n");
        } else if (cantidad_clientes<1)
        {
            printf("ERROR: Debe visitar al menos un cliente\n");
        }
    } while (cantidad_clientes>5||cantidad_clientes<1);
    clientes=malloc(sizeof(Cliente)*cantidad_clientes); //Hago que reserve la memoria que necesito
    for (int i = 0; i <cantidad_clientes; i++)
    {
        printf("\n\n________________Sistema de registro de clientes________________\n\n");
        cargarDatosCliente(i); //Mi ID va ser la i que pase +1, para empezar de 1 en adelante
    }
}

void liberarMemoria() {
    for (int i = 0; i < cantidad_clientes; i++)
    {
        free(clientes[i].NombreCliente);
        free(clientes[i].Productos);
    }
    free(clientes);
}