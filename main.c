#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#include <Windows.h>


/// ARCHIVOS ///

#define arCliente "clientes.dat"
#define arPedidos "pedidos.dat"
#define arProductos "productos.dat"



///ESTRUCTURA DIRECCION - VA DENTRO DE ESTRUCTURA CLIENTE///
struct stDireccion
{
    char calle [30];
    int numero;
    int piso;
    char departamento [4];
};


///ESTRUCTURA CLIENTE///
typedef struct
{
    int id;          ///unico y todos consecutivos
    int dni;
    char nombre[30];
    char apellido[30];
    int movil;
    char mail[30];
    struct stDireccion dir;
    int baja;       ///       0= alta    /    1= baja
} stCliente;


///ESTRCUTURA PRODUCTO///
typedef struct
{
    int categoria;  ///1-Helado 2-tortas 3-bombones
    int codigoProducto;
    char descripcion[100];
    float precio;
    int baja;                    /// 0= alta    /    1= baja
} stProducto;


///ESTRUCTURA DE CADA COMPRA QUE VA DENTRO DE UN PEDIDO - DE ESTRCUTURA PEDIDO///
typedef struct
{
    int codigoProducto;
    int cantidad;
    int valorCompra;  ///$producto x cantidad

} stDescripcionCompra;


///ESTRUCTURA PEDIDO///
typedef struct
{
    int idPedido;
    char fechaPedido [30];
    stDescripcionCompra descripcionPedido [50];  ///arreglo de estructura stDescripcionCompra - cada producto y cant se alojan en un subindice///
    int validos;  ///validos del arreglo stDescripcionCompra p/ poder manejar el arreglo posteriormente///
    int costoPedido; ///costo total del pedido --- suma de cada subindice del arreglo///
    int idCliente;   ///se extrae de la estructura cliente///
    int pedidoAnulado;     ///1= si  0= no
} stPedido;


///ESTRUCTURA ESTADISTICA P/ CLIENTES///
typedef struct
{
    int idCliente;  ///id del cliente///
    int totalPedidos;  ///total de pedidos por id///
} stEstadistica;


///ESTRCUTURA ESTADISTICA P/RANKING DE PRODUCTOS///
typedef struct
{
    int codigo; ///codigo del producto///
    int totalVendidos;  ///cant vendidos por código///
} stVentaProducto;



///PROTOTIPADO FUNCIONES MENU///
void menuUsProg ();
void menuClientesPedidosUs();
void menuClientesPedidosProg();
void menuClientesUs();
void menuPedidosUs();
void menuClientesProg();
void menuPedidosProg();


///PROTOTIPADO FUNCIONES MENU - PRINTF///
void menuUsuarioProgramador();
void menuClientesOPedidos();
void menuClientesPedidosProductoAdm();
void menuClientesUsuario();
void menuClientesProgramador();
void menuPedidosUsuario();
void menuPedidosProgramador();
void menuProductosProgramador();


///PROTOTIPADO FUNCIONES CLIENTE///
void guardaUnCliente (stCliente clientes);
stCliente cargaUnCliente();
void cargaClientes();
int buscarClienteDNIArchivo(int dni);
int buscarUltimoId();
void muestraUnCliente (stCliente cliente);
void muestraClientes();
int buscaPosicion(char archivo[], int dni);
void modificarRegistro(char archivo[], int dni);
void menuModificacionRegistro ();
void bajaCliente (char archivo[], int dni);
void altaCliente (char archivo[], int dni);
int estadoBajaAltaCliente(char archivo [], int DNI);
void funcionCompletaAltaDeCliente ();
int pasarArchivoClientesToArreglo (char archivo [], stCliente arreglo [], int dimension);
int pasarArchivoToArregloFiltradoAltas (char archivo [], stCliente arreglo [], int dimension);
int pasarArchivoToArregloFiltradoBajas (char archivo [], stCliente arreglo [], int dimension);
void mostrarArregloDeClientes(stCliente arreglo[], int validos);
void muestraUnClientePorDni (char archivoCliente[], int dni);
int arregloPedidosPorCliente (char archivoClientes [], char archivoPedidos[], stEstadistica arregloEstadistica[], int dimension);
int buscarPosClienteMayorPedido (stEstadistica estadistica[ ], int pos, int validos);
void ordenacionSeleccionClientesPorPedidos(stEstadistica estadistica[ ], int validos);
void mostrarArregloDeEstadistica(stEstadistica arregloEst[], int validos);


///PROTOTIPADO FUNCIONES PRODUCTO///
void guardaUnProducto (stProducto producto);
stProducto cargaUnProducto();
void muestraUnProducto (stProducto producto);
void mostrarProductosArchivo (char archivo []);
int buscaPosicionProducto(char archivo[], int codigo);
void modificarRegistroProducto(char archivo[], int codigo);
void menuModificacionRegistroProducto ();
void bajaProducto (char archivo[], int codigo);
void altaProducto (char archivo[], int codigo);
int pasarArchivoToArregloFiltradoCategoriaProducto (char archivo [], stProducto arreglo [], int dimension, int categoria);
int pasarArchivoToArregloFiltradoProductosAlta (char archivo [], stProducto arreglo [], int dimension);
int pasarArchivoToArregloFiltradoProductosBaja (char archivo [], stProducto arreglo [], int dimension);
int buscarMenorProducto (stProducto producto[ ], int pos, int validos);
void ordenacionSeleccionProductos(stProducto producto[ ], int validos);
int buscarProductoActivoMenu(int codigo);
void mostrarArregloDeProductos(stProducto arreglo[], int validos);
void menuProductosProg();
int contarCantProductosVendidosPorCodigo(char archivoPedidos [], char archivoProductos[], stVentaProducto venta[], int dimension);
int recorrerArregloPedidoSumaCodigos (stDescripcionCompra compras [], int validos, int codigo);
int buscarPosProductoMasVendido (stVentaProducto ventaP[ ], int pos, int validos);
void ordenacionSeleccionProductoMasVendido(stVentaProducto ventaP[ ], int validos);
void mostrarArregloProductosMasVendidos(stVentaProducto arregloVendidos[], int validos);


///PROTOTIPADO FUNCIONES PEDIDO///
void guardaPedidoClienteArchivo (stPedido pedido);
stPedido cargaUnPedido(char archivoCliente[], char archivoProducto[], stDescripcionCompra compras [], int validos, int dni);
stDescripcionCompra cargaCompra (char archivoProducto []);
int precioProducto (char archivoProducto [], int codigo);
int cargaComprasEnArreglo (stDescripcionCompra compras [], int dimension, char archivoProducto[]);
int ultimoIdPedido();
int sumaArregloCompras (stDescripcionCompra arregloCompras [], int validos);
int buscaIdCliente (char archivoCliente [], int dni);
void muestraUnaCompra (stDescripcionCompra compra, char archivoProducto[]);
void mostrarArregloCompras (stDescripcionCompra compra [], int validos, char archivoProducto []);
void muestraUnPedido (stPedido pedido, char archivoProducto [], stDescripcionCompra compras []);
void funcionCompletaAltaPedido ();
void mostrarArchivoPedidosActivos (char archivoPedidos [], char archivoProductos[]);
void mostrarArchivoPedidosFiltradoPorCliente (char archivoClientes [], char archivoPedidos [], char archivoProductos[], int dni);
int buscaPosicionPedido(char archivoPedidos[], int id);
void bajaPedido (char archivoPedidos[], int id);
void mostrarArchivoPedidosFiltradoPorClienteYAlta (char archivoClientes [], char archivoPedidos [], char archivoProductos[], int dni);
int buscarPosicionPedido(char archivoPedido[], int id);
int recorrerArregloPedido (stDescripcionCompra compras [], int validos, int codigo);
int buscaPosicionPedidoArregloInterno(char archivoPedido[], int codigo, int posPedido);
void modificarRegistroPedido(char archivoPedido[], int id, char archivoProducto[]);
void menuModificacionRegistroPedido ();

///colores///
void Color(int Background, int Text); // Prototipo de función


int main()
{


    menuUsProg();  ///menú que despliega los demás///
    return 0;
}

///funcion cambio de colores///

enum Colors {
 BLACK = 0,
 BLUE = 1,
 GREEN = 2,
 CYAN = 3,
 RED = 4,
 MAGENTA = 5,
 BROWN = 6,
 LGREY = 7,
 DGREY = 8,
 LBLUE = 9,
 LGREEN = 10,
 LCYAN = 11,
 LRED = 12,
 LMAGENTA = 13,
 YELLOW = 14,
 WHITE = 15
};

void Color(int Background, int Text){ // Función para cambiar el color del fondo y/o pantalla

 HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE);


 int    New_Color= Text + (Background * 16);

 SetConsoleTextAttribute(Console, New_Color);

}


//////////////////////MENU OPCION USUARIO O ADMINISTRADOR///////////
void menuUsProg ()
{

    int menuUP; // menu usuario / administrador
    char controlUP; // control menu usuario / administrador

    int clave = 0;
    int claveValida = 123;

    do
    {
        system("cls");
        menuUsuarioProgramador();  //// OPCION DE USUARIO O ADMINISTRADOR
        scanf("%i", &menuUP);
        system("cls");
        switch(menuUP)
        {
        case 1:
            menuClientesPedidosUs();  ///opcion clientes o pedidos para el usuario
            break;

        case 2:
            Color (BLACK, WHITE);
            printf ("Ingrese su contrase%ca   --contrase%ca por defecto: 123--\n\n", 164, 164);
            Color (BLACK, LMAGENTA);
            scanf("%d", &clave);
            if (clave==claveValida)  ///opcion clientes / productos /  pedidos  para el administrador
            {
                menuClientesPedidosProg();
            }
            else
            {
                Color (BLACK, WHITE);
                printf("\nContrase%ca incorrecta", 164);
                Color (BLACK, LMAGENTA);
            }


            break;


        default:
            Color (BLACK, WHITE);
            printf("\nEl n%cmero de men%c ingresado no existe \n", 163,163);
            Color (BLACK, LMAGENTA);
        }

        printf("\n\nQuiere ver otra funci%cn? s/n\n", 162);
        fflush(stdin);
        printf("%c\n", controlUP = getch());
    }
    while(controlUP == 's');

}


/////////////////////MENU OPCION CLIENTES O PEDIDOS PARA EL USUARIO////////////
void menuClientesPedidosUs()
{
    int menuElegido; //menu clientes / pedidos
    char controlMenuCP; //control menu clientes / pedidos

    do
    {

        menuClientesOPedidos();
        scanf("%i", &menuElegido);
        system("cls");
        switch(menuElegido)
        {

        case 1:
            menuClientesUs();  ///menu de clientes para el usuario
            break;

        case 2:
            menuPedidosUs();  ///menu de pedidos para el usuario
            break;

        case 99:
            menuUsProg();  ///volver al menú ppal
            break;


        default:
            Color (BLACK, WHITE);
            printf("\nEl n%cmero de men%c ingresado no existe \n", 163,163);
            Color (BLACK, LMAGENTA);

        }


        printf("\n\nQuiere ver otra funci%cn? s/n\n", 162);
        fflush(stdin);
        printf("%c\n", controlMenuCP = getch());
    }
    while(controlMenuCP == 's');

    system("cls");
    menuUsProg();

}
///////////////////////OPCION CLIENTES O PEDIDOS PARA EL ADMINISTRADOR////////////
void menuClientesPedidosProg()
{
    int menuElegido; //menu clientes / pedidos
    char controlMenuCP; //control menu clientes / productos / pedidos

    do
    {
        system("cls");
        menuClientesPedidosProductoAdm();
        scanf("%i", &menuElegido);
        system("cls");
        switch(menuElegido)
        {

        case 1:
            menuClientesProg();   ///menu de clientes para el administrador
            break;

        case 2:
            menuProductosProg();   ///menu de productos para el administrador
            break;

        case 3:
            menuPedidosProg();   ///menu de pedidos para el administrador
            break;

        case 99:
            menuUsProg();  ///volver al menú ppal
            break;

        default:
            Color (BLACK,   WHITE);
            printf("\nEl n%cmero de men%c ingresado no existe \n", 163,163);
            Color (BLACK, LMAGENTA);

        }


        printf("\n\nQuiere ver otra funci%cn? s/n\n", 162);
        fflush(stdin);
        printf("%c\n", controlMenuCP = getch());
    }
    while(controlMenuCP == 's');

    system("cls");
    menuUsProg();



}
/////////////////////////////MENU CLIENTES PARA EL USUARIO///////////////////////////////
void menuClientesUs()
{
    int menuC;  //menu clientes
    char controlClientes;  //control menu clientes


    int dni = 0;

    do
    {
        system("cls");
        menuClientesUsuario();
        scanf("%i", &menuC);
        system("cls");
        switch(menuC)
        {

        case 1:
            funcionCompletaAltaDeCliente();
            break;

        case 2:
            Color (BLACK, WHITE);
            printf("Ingrese su DNI\n\n");
            Color (BLACK, LMAGENTA);
            scanf("%d", &dni);
            muestraUnClientePorDni(arCliente, dni);
            break;

        case 3:
            Color (BLACK, WHITE);
            printf("Ingrese su DNI\n\n");
            Color (BLACK, LMAGENTA);
            scanf("%d", &dni);
            modificarRegistro (arCliente, dni);
            break;

        case 4:
            Color (BLACK, WHITE);
            printf("Ingrese su DNI\n\n");
            Color (BLACK, LMAGENTA);
            scanf("%d", &dni);
            bajaCliente (arCliente, dni);
            break;

        case 98:
            menuClientesPedidosUs();
            break;


        case 99:
            menuUsProg();
            break;

        default:
            Color (BLACK, WHITE);
            printf("La opci%cn ingresada no existe \n", 162);
            Color (BLACK, LMAGENTA);

        }

        printf("\n\nQuiere ver otra opci%cn? s/n\n", 162);
        fflush(stdin);
        printf("%c\n", controlClientes = getch());

    }
    while(controlClientes == 's');

    system("cls");
    menuClientesPedidosUs();
}
///////////////////////////////////////MENU PEDIDOS PARA EL USUARIO/////////////////////////////////
void menuPedidosUs()
{
    int menuP;  //menu pedidos
    char controlPedidos;  //control menu pedidos

    int dni = 0;
    int id = 0;
    int dimension = 100;
    stProducto arregloProductos [dimension];
    int validos = 0;


    do
    {
        system("cls");
        menuPedidosUsuario();
        scanf("%i", &menuP);
        system("cls");
        switch(menuP)
        {

        case 1:
            Color (BLACK, WHITE);
            printf ("\n                   #define dulC - Una constante de dulzura-                    \n");
            printf ("\n\n                       ...Nuestros productos...\n\n");
            Color (BLACK, LMAGENTA);
            validos = pasarArchivoToArregloFiltradoProductosAlta (arProductos, arregloProductos, dimension);
            ordenacionSeleccionProductos (arregloProductos, validos);
            mostrarArregloDeProductos (arregloProductos, validos);
            break;

        case 2:

            funcionCompletaAltaPedido ();
            break;

        case 3:
            Color (BLACK, WHITE);
            printf("Ingrese el ID del pedido que desea modificar\n\n");
            Color (BLACK, LMAGENTA);
            scanf("%d", &id);
            modificarRegistroPedido (arPedidos, id, arProductos);
            break;

        case 4:
            Color (BLACK, WHITE);
            printf("Ingrese su DNI\n\n");
            Color (BLACK, LMAGENTA);
            scanf("%d", &dni);
            mostrarArchivoPedidosFiltradoPorCliente (arCliente, arPedidos, arProductos, dni);
            break;

        case 5:
            Color (BLACK, WHITE);
            printf("Ingrese su DNI\n\n");
            Color (BLACK, LMAGENTA);
            scanf("%d", &dni);
            mostrarArchivoPedidosFiltradoPorClienteYAlta (arCliente, arPedidos, arProductos, dni);
            break;

        case 6:
            Color (BLACK, WHITE);
            printf("Ingrese el ID del pedido que desea anular\n\n");
            Color (BLACK, LMAGENTA);
            scanf("%d", &id);
            bajaPedido (arPedidos, id);
            break;

        case 98:
            menuClientesPedidosUs();
            break;

        case 99:
            menuUsProg();
            break;


        default:
            Color (BLACK, WHITE);
            printf("La opci%cn ingresada no existe \n", 162);
            Color (BLACK, LMAGENTA);

        }

        printf("\n\nQuiere ver otra opci%cn? s/n\n", 162);
        fflush(stdin);
        printf("%c\n", controlPedidos = getch());

    }
    while(controlPedidos == 's');

    system("cls");
    menuClientesPedidosUs();


}
////////////////////////////MENU CLIENTES PARA EL ADMINISTRADOR////////////////////////////////
void menuClientesProg()
{
    int menuC;  //menu clientes
    char controlClientes;  //control menu clientes

    int dni = 0;
    int dimension = 200;
    stCliente arregloClientes [dimension];
    int validosArreglo = 0;
    stEstadistica arregloPedidosCliente[dimension];



    do
    {
        system("cls");
        menuClientesProgramador();
        scanf("%i", &menuC);
        system("cls");
        switch(menuC)
        {

        case 1:
            funcionCompletaAltaDeCliente();
            break;

        case 2:
            Color (BLACK, WHITE);
            printf("Ingrese el DNI del cliente que desea ver\n\n");
            Color (BLACK, LMAGENTA);
            scanf("%d", &dni);
            muestraUnClientePorDni(arCliente, dni);
            break;

        case 3:
            Color (BLACK, WHITE);
            printf("Ingrese el DNI del cliente a modificar\n\n");
            Color (BLACK, LMAGENTA);
            scanf("%d", &dni);
            modificarRegistro (arCliente, dni);
            break;

        case 4:
            Color (BLACK, WHITE);
            printf("Ingrese  DNI\n\n");
            Color (BLACK, LMAGENTA);
            scanf("%d", &dni);
            bajaCliente (arCliente, dni);
            break;

        case 5:
            Color (BLACK, WHITE);
            printf("\nListado de clientes activos\n\n");
            Color (BLACK, LMAGENTA);
            validosArreglo = pasarArchivoToArregloFiltradoAltas (arCliente, arregloClientes, dimension);
            mostrarArregloDeClientes (arregloClientes, validosArreglo);
            break;

        case 6:
            Color (BLACK, WHITE);
            printf("\nListado de clientes inactivos\n\n");
            Color (BLACK, LMAGENTA);
            validosArreglo = pasarArchivoToArregloFiltradoBajas (arCliente, arregloClientes, dimension);
            mostrarArregloDeClientes (arregloClientes, validosArreglo);
            break;

        case 7:
            Color (BLACK, WHITE);
            printf("\nListado de los mejores clientes\n\n");
            Color (BLACK, LMAGENTA);
            validosArreglo = arregloPedidosPorCliente (arCliente, arPedidos, arregloPedidosCliente, dimension);
            ordenacionSeleccionClientesPorPedidos (arregloPedidosCliente, validosArreglo);
            mostrarArregloDeEstadistica (arregloPedidosCliente, validosArreglo);
            break;


        case 98:
            menuClientesPedidosProg();
            break;

        case 99:
            menuUsProg();
            break;


        default:
            Color (BLACK, WHITE);
            printf("La opci%cn ingresada no existe \n", 162);
            Color (BLACK, LMAGENTA);

        }

        printf("\n\nQuiere ver otra opci%cn? s/n\n", 162);
        fflush(stdin);
        printf("%c\n", controlClientes = getch());

    }
    while(controlClientes == 's');

    system("cls");
    menuClientesPedidosProg();

}
//////////////////////////////////MENU PEDIDOS PARA EL ADMINISTRADOR////////////////////////////////////
void menuPedidosProg()
{
    int menuP;  //menu pedidos
    char controlPedidos;  //control menu pedidos


    int dni = 0;
    int id = 0;
    int dimension = 100;
    stProducto arregloProductos [dimension];
    int validos = 0;


    do
    {
        system("cls");
        menuPedidosProgramador();
        scanf("%i", &menuP);
        system("cls");
        switch(menuP)
        {

        case 1:
            Color (BLACK, WHITE);
            printf ("\n  -------- #define dulC, -Una constante de dulzura- --------  \n");
            printf ("\n\n                       ...Nuestros productos...\n\n");
            Color (BLACK, LMAGENTA);
            validos = pasarArchivoToArregloFiltradoProductosAlta (arProductos, arregloProductos, dimension);
            ordenacionSeleccionProductos (arregloProductos, validos);
            mostrarArregloDeProductos (arregloProductos, validos);
            break;

        case 2:
            funcionCompletaAltaPedido ();
            break;

        case 3:
            Color (BLACK, WHITE);
            printf("Ingrese el ID del pedido que desea modificar\n\n");
            Color (BLACK, LMAGENTA);
            scanf("%d", &id);
            modificarRegistroPedido (arPedidos, id, arProductos);
            break;

        case 4:
            Color (BLACK, WHITE);
            printf("Listado de pedidos activos\n\n");
            Color (BLACK, LMAGENTA);
            mostrarArchivoPedidosActivos (arPedidos, arProductos);
            break;

        case 5:
            Color (BLACK, WHITE);
            printf("Ingrese su DNI\n\n");
            Color (BLACK, LMAGENTA);
            scanf("%d", &dni);
            mostrarArchivoPedidosFiltradoPorCliente (arCliente, arPedidos, arProductos, dni);
            break;

        case 6:
            Color (BLACK, WHITE);
            printf("Ingrese su DNI\n\n");
            Color (BLACK, LMAGENTA);
            scanf("%d", &dni);
            mostrarArchivoPedidosFiltradoPorClienteYAlta (arCliente, arPedidos, arProductos, dni);
            break;

        case 7:
            Color (BLACK, WHITE);
            printf("Ingrese el ID del pedido que desea anular\n\n");
            Color (BLACK, LMAGENTA);
            scanf("%d", &id);
            bajaPedido (arPedidos, id);
            break;






        case 98:
            menuClientesPedidosProg();
            break;

        case 99:
            menuUsProg();
            break;




        default:
            Color (BLACK, WHITE);
            printf("La opci%cn ingresada no existe \n", 162);
            Color (BLACK, LMAGENTA);

        }

        printf("\n\nQuiere ver otra opci%cn? s/n\n", 162);
        fflush(stdin);
        printf("%c\n", controlPedidos = getch());

    }
    while(controlPedidos == 's');

    system("cls");
    menuClientesPedidosProg();

}

//////////////////////////////////MENU PRODUCTOS PARA EL ADMINISTRADOR/////////////////////////////////////
void menuProductosProg()
{
    int menuP;  //menu pedidos
    char controlProductos;  //control menu producto


    int categoria = 0;
    stProducto prod;
    int codigo = 0;
    int dimension = 100;
    stProducto arregloProductos [dimension];
    int validos = 0;
    stVentaProducto ventas [dimension];

    do
    {
        system("cls");
        menuProductosProgramador();
        scanf("%i", &menuP);
        system("cls");
        switch(menuP)
        {

        case 1:
            prod = cargaUnProducto();
            guardaUnProducto(prod);
            muestraUnProducto(prod);
            break;

        case 2:
            Color (BLACK, WHITE);
            printf("Listado general de productos:\n\n", 161);
            Color (BLACK, LMAGENTA);
            mostrarProductosArchivo(arProductos);
            break;

        case 3:
            Color (BLACK, WHITE);
            printf("Ingrese la categor%ca que desea ver (1-Helados 2-Tortas 3-Bombones):\n\n", 161);
            Color (BLACK, LMAGENTA);
            scanf("%d", &categoria);
            validos = pasarArchivoToArregloFiltradoCategoriaProducto (arProductos, arregloProductos, dimension, categoria);
            system("cls");
            if (categoria==1)
            {   Color (BLACK, WHITE);
                printf("Listado de Helados\n\n");
                Color (BLACK, LMAGENTA);

            }
            else if (categoria==2)
            {
                Color (BLACK, WHITE);
                printf("Listado de Tortas\n\n");
                Color (BLACK, LMAGENTA);
            }
            else
            {
                Color (BLACK, WHITE);
                printf("Listado de Bombones\n\n");
                Color (BLACK, LMAGENTA);
            }
            ordenacionSeleccionProductos (arregloProductos, validos);
            mostrarArregloDeProductos (arregloProductos, validos);
            break;

        case 4:
            Color (BLACK, WHITE);
            printf("Productos activos\n\n");
            Color (BLACK, LMAGENTA);
            validos = pasarArchivoToArregloFiltradoProductosAlta (arProductos, arregloProductos, dimension);
            ordenacionSeleccionProductos (arregloProductos, validos);
            mostrarArregloDeProductos (arregloProductos, validos);
            break;

        case 5:
            Color (BLACK, WHITE);
            printf("Productos inactivos\n\n");
            Color (BLACK, LMAGENTA);
            validos = pasarArchivoToArregloFiltradoProductosBaja (arProductos, arregloProductos, dimension);
            ordenacionSeleccionProductos (arregloProductos, validos);
            mostrarArregloDeProductos (arregloProductos, validos);
            break;

        case 6:
            Color (BLACK, WHITE);
            printf("Ranking productos m%cs vendidos\n\n", 160);
            Color (BLACK, LMAGENTA);
            validos = contarCantProductosVendidosPorCodigo (arPedidos, arProductos, ventas, dimension);
            ordenacionSeleccionProductoMasVendido (ventas, validos);
            mostrarArregloProductosMasVendidos (ventas, validos);
            break;


        case 7:
            Color (BLACK, WHITE);
            printf("Ingrese el c%cdigo del producto que desea modificar\n\n", 162);
            Color (BLACK, LMAGENTA);
            scanf("%d", &codigo);
            modificarRegistroProducto (arProductos, codigo);
            break;

        case 8:
            Color (BLACK, WHITE);
            printf("Ingrese el c%cdigo del producto que desea dar de baja\n\n", 162);
            Color (BLACK, LMAGENTA);
            scanf("%d", &codigo);
            bajaProducto (arProductos, codigo);
            break;

        case 9:
            Color (BLACK, WHITE);
            printf("Ingrese el c%cdigo del producto que desea volver a dar de alta\n\n", 162);
            Color (BLACK, LMAGENTA);
            scanf("%d", &codigo);
            altaProducto (arProductos, codigo);
            break;

        case 98:
            menuClientesPedidosProductoAdm();
            break;

        case 99:
            menuUsProg();
            break;






        default:
            Color (BLACK, WHITE);
            printf("La opci%cn ingresada no existe \n", 162);
            Color (BLACK, LMAGENTA);

        }

        printf("\n\nQuiere ver otra opci%cn? s/n\n", 162);
        fflush(stdin);
        printf("%c\n", controlProductos = getch());

    }
    while(controlProductos == 's');

    system("cls");
    menuClientesPedidosProg();

}

////FUNCIONES///

///GUARDA UN CLIENTE///

void guardaUnCliente (stCliente clientes)
{
    FILE * pArchCliente= fopen(arCliente, "ab");

    if (pArchCliente != NULL)
    {
        fwrite (&clientes, sizeof(stCliente), 1, pArchCliente);

        fclose(pArchCliente);
    }
}

///CARGA UN CLIENTE///

stCliente cargaUnCliente()  /// pedir dni primero para verificar si existe - IF / else
{
    stCliente cliente;
    int ultimoID;


    ultimoID = buscarUltimoId();

    cliente.id = ultimoID+1;
    Color (BLACK, WHITE);
    printf("Nombre:");
    Color (BLACK, LMAGENTA);
    fflush(stdin);
    gets(cliente.nombre);
    Color (BLACK, WHITE);
    printf("Apellido:");
    Color (BLACK, LMAGENTA);
    fflush(stdin);
    gets(cliente.apellido);
    Color (BLACK, WHITE);
    printf("Confirmar DNI:");
    Color (BLACK, LMAGENTA);
    scanf("%d", &cliente.dni);
    Color (BLACK, WHITE);
    printf("Tel%cfono:", 130);
    Color (BLACK, LMAGENTA);
    scanf("%d", &cliente.movil);
    Color (BLACK, WHITE);
    printf("Mail:");
    Color (BLACK, LMAGENTA);
    fflush(stdin);
    gets(cliente.mail);
    Color (BLACK, WHITE);
    printf("Domicilio:\n");
    printf("Calle:");
    Color (BLACK, LMAGENTA);
    fflush(stdin);
    gets(cliente.dir.calle);
    Color (BLACK, WHITE);
    printf("N%cmero:", 163);
    Color (BLACK, LMAGENTA);
    scanf ("%d", &cliente.dir.numero);
    Color (BLACK, WHITE);
    printf("Piso:");
    Color (BLACK, LMAGENTA);
    scanf ("%d", &cliente.dir.piso);
    Color (BLACK, WHITE);
    printf("Departamento:");
    Color (BLACK, LMAGENTA);
    fflush(stdin);
    gets(cliente.dir.departamento);

    cliente.baja = 0;

    return cliente;

}

///BUSCAR SI EXISTE EL DNI///

int buscarClienteDNIArchivo(int dni)
{
    int flag = 0;
    stCliente c;
    FILE *pArchCliente = fopen(arCliente, "rb");
    if(pArchCliente)
    {
        while(fread(&c, sizeof(stCliente),1,pArchCliente) > 0 && flag == 0)
        {
            if(c.dni==dni)
            {
                flag=1;
            }
        }
        fclose(pArchCliente);
    }
    return flag;
}

///BUSCAR ULTIMO ID///

int buscarUltimoId()
{
    stCliente c;
    int id=-1;
    FILE *pArchCliente = fopen(arCliente,"rb");
    if(pArchCliente)
    {
        fseek(pArchCliente, -1* sizeof(stCliente),SEEK_END);
        if(fread(&c,sizeof(stCliente),1,pArchCliente) > 0)
        {
            id=c.id;
        }
        fclose(pArchCliente);
    }
    return id;
}

///MUESTRA UN CLIENTE//

void muestraUnCliente (stCliente cliente)
{
    Color (BLACK, WHITE);
    printf("--------------------------\n");
    printf("\n");
    Color (BLACK, LMAGENTA);
    printf("ID:");
    Color (BLACK, WHITE);
    printf("        %d \n", cliente.id);
    Color (BLACK, LMAGENTA);
    printf("Nombre:");
    Color (BLACK, WHITE);
    printf("    %s %s \n", cliente.nombre, cliente.apellido);
    Color (BLACK, LMAGENTA);
    printf("DNI:");
    Color (BLACK, WHITE);
    printf("       %d \n", cliente.dni);
    Color (BLACK, LMAGENTA);
    printf("Tel%cfono:", 130);
    Color (BLACK, WHITE);
    printf("  %d \n", cliente.movil);
    Color (BLACK, LMAGENTA);
    printf("Mail:");
    Color (BLACK, WHITE);
    printf("      %s \n", cliente.mail);
    Color (BLACK, LMAGENTA);
    printf("Domicilio:");
    Color (BLACK, WHITE);
    printf(" %s %d %d %s\n", cliente.dir.calle, cliente.dir.numero, cliente.dir.piso, cliente.dir.departamento);
     Color (BLACK, WHITE);
    printf("\n");
    printf("--------------------------\n");
     Color (BLACK, LMAGENTA);

}

///MUESTRA CLIENTES///

void muestraClientes()
{
    stCliente cliente;

    FILE *pArchCliente = fopen(arCliente, "rb");

    if(pArchCliente)
    {
        while ( fread(&cliente, sizeof(stCliente), 1, pArchCliente) > 0)
        {

            muestraUnCliente(cliente);

        }
        fclose(pArchCliente);
    }
    printf("\n");
}

///BUSCAR POSICION EN ARCHIVO DE CLIENTES///

int buscaPosicion(char archivo[], int dni)
{
    int pos=-1;
    stCliente c;
    FILE *pArch = fopen(archivo,"rb");
    if(pArch)
    {
        while(pos == -1 && fread(&c, sizeof(stCliente), 1, pArch) > 0)
        {
            if(c.dni == dni)
            {
                pos = ftell(pArch)/sizeof(stCliente)-1;
            }
        }
        fclose(pArch);
    }

    return pos;
}
///MUESTRA UN CTE POR DNI///
void muestraUnClientePorDni (char archivoCliente[], int dni)
{
    int pos= buscaPosicion(archivoCliente,dni);
    stCliente c;

    FILE *pArchCliente = fopen(arCliente,"rb");

    if(pArchCliente)
    {
        fseek(pArchCliente, pos* sizeof(stCliente),SEEK_SET);
        fread(&c,sizeof(stCliente),1,pArchCliente);

        muestraUnCliente(c);

        fclose(pArchCliente);
    }

}




///MODIFICAR REGISTRO DE CLIENTE///
void modificarRegistro(char archivo[], int dni)
{
    char control;
    int funcion = 0;
    int pos=0;
    char nombre [30];
    char apellido [30];
    char mail [30];
    char calle [30];
    char dpto [10];
    stCliente cliente;

    pos = buscaPosicion (archivo, dni);

    if (pos>-1)
    {
        FILE *pArch = fopen(archivo, "r+b");
        if(pArch)
        {

            fseek(pArch, sizeof(stCliente)*pos, SEEK_SET);
            fread(&cliente, sizeof(stCliente),1,pArch);

            do
            {
                system ("cls");
                menuModificacionRegistro();
                scanf("%i", &funcion);
                system("cls");

                switch(funcion)
                {
                case 1:
                    Color (BLACK, WHITE);
                    printf("Ingrese su nombre nuevamente\n");
                    Color (BLACK, LMAGENTA);
                    fflush (stdin);
                    gets (nombre);
                    strcpy(cliente.nombre, nombre);
                    break;


                case 2:
                    Color (BLACK, WHITE);
                    printf("Ingrese su apellido nuevamente\n");
                    Color (BLACK, LMAGENTA);
                    fflush (stdin);
                    gets (apellido);
                    strcpy(cliente.apellido, apellido);
                    break;

                case 3:
                    Color (BLACK, WHITE);
                    printf("Ingrese nuevamente su tel%cfono\n", 130);
                    Color (BLACK, LMAGENTA);
                    scanf("%d", &cliente.movil);
                    break;

                case 4:
                    Color (BLACK, WHITE);
                    printf("Ingrese nuevamente su correo electr%cnico\n", 162);
                    Color (BLACK, LMAGENTA);
                    fflush (stdin);
                    gets (mail);
                    strcpy(cliente.mail, mail);
                    break;

                case 5:
                    Color (BLACK, WHITE);
                    printf("Ingrese nuevamente su domicilio\n");
                    printf("Calle:");
                    Color (BLACK, LMAGENTA);
                    fflush(stdin);
                    gets(calle);
                    strcpy(cliente.dir.calle, calle);
                    Color (BLACK, WHITE);
                    printf("N%cmero:", 163);
                    Color (BLACK, LMAGENTA);
                    scanf ("%d", &cliente.dir.numero);
                    Color (BLACK, WHITE);
                    printf("Piso:");
                    Color (BLACK, LMAGENTA);
                    scanf ("%d", &cliente.dir.piso);
                    Color (BLACK, WHITE);
                    printf("Departamento:");
                    Color (BLACK, LMAGENTA);
                    fflush(stdin);
                    gets(dpto);
                    strcpy(cliente.dir.departamento, dpto);
                    break;

                default:
                    Color (BLACK, WHITE);
                    printf("La funci%cn no existe \n", 162);
                    Color (BLACK, LMAGENTA);

                }

                fseek(pArch, sizeof(stCliente)*(-1), SEEK_CUR);
                fwrite(&cliente, sizeof(stCliente), 1, pArch);

                printf("\n\nQuiere modificar otro dato? s/n\n");
                fflush(stdin);
                printf("%c\n", control = getch());

            }
            while(control == 's');

            fclose(pArch);
        }
    }
    else
    {
        Color (BLACK, WHITE);
        printf("No tenemos registrado un cliente con ese DNI\n");
        Color (BLACK, LMAGENTA);
    }
}

///MENU PARA MODIFICAR DATOS CLIENTE///
void menuModificacionRegistro ()
{
    Color (BLACK, WHITE);
    printf("Qu%c dato desea modificar?\n", 130);
    Color (BLACK, LMAGENTA);
    printf("1- Nombre\n");
    printf("2- Apellido\n");
    printf("3- Tel%cfono\n", 130);
    printf("4- Correo electr%cnico\n", 162);
    printf("5- Domicilio\n");

}
///DAR DE BAJA UN CLIENTE///
void bajaCliente (char archivo[], int dni)
{
    int pos=0;
    stCliente cliente;

    pos = buscaPosicion (archivo, dni);

    if (pos>-1)
    {
        FILE *pArch = fopen(archivo, "r+b");
        if(pArch)
        {

            fseek(pArch, sizeof(stCliente)*pos, SEEK_SET);
            fread(&cliente, sizeof(stCliente),1,pArch);
            cliente.baja=1;
            fseek(pArch, sizeof(stCliente)*(-1), SEEK_CUR);
            fwrite(&cliente, sizeof(stCliente), 1, pArch);
            fclose(pArch);
            Color (BLACK, WHITE);
            printf("\nYa fue dado de baja de #define dulC, esperamos volver a verlo pronto!\n");
            Color (BLACK, LMAGENTA);
        }

    }
    else
    {
        Color (BLACK, WHITE);
        printf ("\nUsted no es cliente de #define dulC, lo invitamos a conocernos!");
        Color (BLACK, LMAGENTA);
    }
}

///DAR DE ALTA UN CLIENTE///
void altaCliente (char archivo[], int dni)
{
    int pos=0;
    stCliente cliente;

    pos = buscaPosicion (archivo, dni);

    if (pos>-1)
    {
        FILE *pArch = fopen(archivo, "r+b");
        if(pArch)
        {

            fseek(pArch, sizeof(stCliente)*pos, SEEK_SET);
            fread(&cliente, sizeof(stCliente),1,pArch);
            cliente.baja=0;
            fseek(pArch, sizeof(stCliente)*(-1), SEEK_CUR);
            fwrite(&cliente, sizeof(stCliente), 1, pArch);
            fclose(pArch);
        }

    }
}

///VER ESTADO ALTA/BAJA DE CLIENTE///
int estadoBajaAltaCliente(char archivo [], int dni)
{
    int pos=0;
    int flag = 0;
    stCliente cliente;

    pos = buscaPosicion (archivo, dni);

    if (pos>-1)
    {
        FILE *pArch = fopen(archivo, "rb");
        if(pArch)
        {

            fseek(pArch, sizeof(stCliente)*pos, SEEK_SET);
            fread(&cliente, sizeof(stCliente),1,pArch);
            if(cliente.baja==0)
            {
                flag=1;
            }
        }
        fclose(pArch);
    }

    return flag;
}

///FUNCION COMPLETA DE ALTA DE CLIENTE -> ALTA, CAMBIAR ESTADO, CTE YA REGISTRADO///
void funcionCompletaAltaDeCliente ()
{

    int dni = 0;
    stCliente cli;
    int estado = 0;
    Color (BLACK, WHITE);
    printf("Ingrese sus datos:\n\n");
    printf("DNI:");
    Color (BLACK, LMAGENTA);
    scanf("%d", &dni);
    if (buscarClienteDNIArchivo(dni) != 1)
    {
        cli = cargaUnCliente();
        guardaUnCliente(cli);
        muestraUnCliente(cli);

    }
    else if ((estado = estadoBajaAltaCliente (arCliente, dni))== 0)
    {
        Color (BLACK, WHITE);
        printf ("\nUd. fue cliente de #define dulC tiempo atr%cs, bienvenido nuevamente\n", 160);
        Color (BLACK, LMAGENTA);
        altaCliente (arCliente, dni);
    }
    else
    {
        Color (BLACK, WHITE);
        printf ("\nUd. ya es cliente de #define dulC\n");
        Color (BLACK, LMAGENTA);
    }
}

///CUENTA REGISTROS DE CUALQUIER TIPO DE DATO///
int contarRegistrosArchivo (char archivo[], int dato)
{
    int total=0;

    FILE *pArch = fopen(archivo,"rb");
    if(pArch)
    {
        fseek(pArch,0,SEEK_END);
        total=ftell(pArch)/dato;
        fclose(pArch);
    }

    return total;
}

///PASAR TODOS LOS CLIENTES A UN ARREGLO///
int pasarArchivoClientesToArreglo (char archivo [], stCliente arreglo [], int dimension)
{
    FILE *parchivo = NULL;
    int i = 0;
    stCliente cliente;

    if (contarRegistrosArchivo(archivo, sizeof(stCliente))>0)
    {
        parchivo = fopen(archivo,"rb");

        if(parchivo)
        {
            while ((fread(&cliente, sizeof(stCliente),1,parchivo) > 0 ) && i<dimension)
            {
                arreglo[i] = cliente;
                i++;
            }

        }
        fclose(parchivo);
    }
    else
    {
        Color (BLACK, WHITE);
        printf("\nTodavía no tiene clientes cargados\n");
        Color (BLACK, LMAGENTA);
    }
    return i;
}

///PASA A UN ARREGLO SOLO LOS CLIENTES ACTIVOS///
int pasarArchivoToArregloFiltradoAltas (char archivo [], stCliente arreglo [], int dimension)
{
    FILE *parchivo = NULL;
    int i = 0;
    stCliente cliente;

    if (contarRegistrosArchivo(archivo, sizeof(stCliente))>0)
    {
        parchivo = fopen(archivo,"rb");

        if(parchivo)
        {
            while ((fread(&cliente, sizeof(stCliente),1,parchivo) > 0 ) && i<dimension)
            {
                if (cliente.baja==0)
                {
                    arreglo[i]=cliente;
                    i++;
                }
            }

        }
        fclose(parchivo);
    }
    else
    {
        Color (BLACK, WHITE);
        printf("\nTodavía no tiene clientes cargados\n");
        Color (BLACK, LMAGENTA);
    }
    return i;
}

///PASA A UN ARREGLO TODOS LOS CLIENTES INACTIVOS///
int pasarArchivoToArregloFiltradoBajas (char archivo [], stCliente arreglo [], int dimension)
{
    FILE *parchivo = NULL;
    int i = 0;
    stCliente cliente;

    if (contarRegistrosArchivo(archivo, sizeof(stCliente))>0)
    {
        parchivo = fopen(archivo,"rb");

        if(parchivo)
        {
            while ((fread(&cliente, sizeof(stCliente),1,parchivo) > 0 ) && i<dimension)
            {
                if (cliente.baja==1)
                {
                    arreglo[i]=cliente;
                    i++;
                }
            }

        }
        fclose(parchivo);
    }
    else
    {
        Color (BLACK, WHITE);
        printf("\nTodavía no tiene clientes cargados\n");
        Color (BLACK, LMAGENTA);
    }
    return i;
}


///MUESTRA CUALQUIER ARREGLO DE CLIENTES///
void mostrarArregloDeClientes(stCliente arreglo[], int validos)
{


    for (int i=0; i<validos; i++)
    {
        muestraUnCliente(arreglo[i]);
    }
}


///GUARDA UN PRODUCTO///

void guardaUnProducto (stProducto producto)
{
    FILE * pArch= fopen(arProductos, "ab");

    if (pArch)
    {
        fwrite (&producto, sizeof(stProducto), 1, pArch);

        fclose(pArch);
    }
}

///CARGA UN PRODUCTO///

stProducto cargaUnProducto()
{
    stProducto producto;
    Color (BLACK, WHITE);
    printf("Categor%ca (1-Helados 2-Tortas 3-Bombones): ", 161);
    Color (BLACK, LMAGENTA);
    scanf("%d", &producto.categoria);
    Color (BLACK, WHITE);
    printf("Descripci%cn: ", 162);
    Color (BLACK, LMAGENTA);
    fflush(stdin);
    gets(producto.descripcion);
    Color (BLACK, WHITE);
    printf("Precio: ");
    Color (BLACK, LMAGENTA);
    scanf("%f", &producto.precio);
    Color (BLACK, WHITE);
    printf("C%cdigo del producto: ", 162);
    Color (BLACK, LMAGENTA);
    scanf ("%d", &producto.codigoProducto);

    producto.baja = 0;

    return producto;

}

///MUESTRA UN PRODUCTO P/ EL USUARIO//

void muestraUnProducto (stProducto producto)
{
    Color (BLACK, WHITE);
    printf("-----------------------------------------------------------------------------\n");
    Color (BLACK, LMAGENTA);

    printf(" %d ", producto.codigoProducto);
    printf("- %s - $%.2f\n", producto.descripcion, producto.precio);
    Color (BLACK, WHITE);
    printf("-----------------------------------------------------------------------------\n");
    Color (BLACK, LMAGENTA);

}

///MUESTRA PRODUCTOS//

void mostrarProductosArchivo (char archivo [])
{
    FILE *parchivo =fopen(archivo,"rb");
    stProducto p;

    if(parchivo!=NULL)
    {

        while(fread(&p, sizeof(stProducto),1,parchivo)>0)
        {
            muestraUnProducto (p);

        }

    }
    fclose(parchivo);
}



///BUSCAR POSICION EN ARCHIVO DE PRODUCTOS///
int buscaPosicionProducto(char archivo[], int codigo)
{
    int pos=-1;
    stProducto p;
    FILE *pArch = fopen(archivo,"rb");
    if(pArch)
    {
        while(pos == -1 && fread(&p, sizeof(stProducto), 1, pArch) > 0)
        {
            if(p.codigoProducto == codigo)
            {
                pos = ftell(pArch)/sizeof(stProducto)-1;
            }
        }
        fclose(pArch);
    }

    return pos;
}

///MODIFICAR REGISTRO DE PRODUCTO///
void modificarRegistroProducto(char archivo[], int codigo)
{
    char control;
    int funcion = 0;
    int pos=0;
    char descripcion [100];
    stProducto producto;

    pos = buscaPosicionProducto (archivo, codigo);

    if (pos>-1)
    {
        FILE *pArch = fopen(archivo, "r+b");
        if(pArch)
        {

            fseek(pArch, sizeof(stProducto)*pos, SEEK_SET);
            fread(&producto, sizeof(stProducto),1,pArch);

            do
            {
                system ("cls");
                menuModificacionRegistroProducto();
                scanf("%i", &funcion);
                system("cls");

                switch(funcion)
                {

                case 1:
                    Color (BLACK, WHITE);
                    printf("Ingrese nuevamente la categor%ca del producto\n", 161);
                    Color (BLACK, LMAGENTA);
                    scanf ("%d", &producto.categoria);
                    break;

                case 2:
                    Color (BLACK, WHITE);
                    printf("Ingrese nuevamente el c%cdigo del producto\n", 162);
                    Color (BLACK, LMAGENTA);
                    scanf ("%d", &producto.codigoProducto);
                    break;


                case 3:
                    Color (BLACK, WHITE);
                    printf("Ingrese nuevamente la descripci%cn\n", 162);
                    Color (BLACK, LMAGENTA);
                    fflush (stdin);
                    gets (descripcion);
                    strcpy(producto.descripcion, descripcion);
                    break;

                case 4:
                    Color (BLACK, WHITE);
                    printf("Ingrese nuevamente el precio");
                    Color (BLACK, LMAGENTA);
                    scanf("%f", &producto.precio);
                    break;

                default:
                    Color (BLACK, WHITE);
                    printf("La funci%cn no existe \n", 162);
                    Color (BLACK, LMAGENTA);

                }

                fseek(pArch, sizeof(stProducto)*(-1), SEEK_CUR);
                fwrite(&producto, sizeof(stProducto), 1, pArch);

                printf("\n\nQuiere modificar otro dato? s/n\n");
                fflush(stdin);
                printf("%c\n", control = getch());

            }
            while(control == 's');

            fclose(pArch);
        }
    }
    else
    {
        Color (BLACK, WHITE);
        printf ("\nNo existe un producto con ese c%cdigo", 162);
        Color (BLACK, LMAGENTA);
    }
}

///MENU PARA MODIFICAR DATOS CLIENTE///
void menuModificacionRegistroProducto ()
{
    Color (BLACK, WHITE);
    printf("Qu%c dato desea modificar?\n\n", 130);
    Color (BLACK, LMAGENTA);
    printf("1- Categor%ca\n", 161);
    printf("2- C%cdigo\n", 162);
    printf("3- Descripci%cn\n", 162);
    printf("4- Precio\n");
}

///MUESTRA CUALQUIER ARREGLO DE PRODUCTOS///
void mostrarArregloDeProductos(stProducto arreglo[], int validos)
{


    for (int i=0; i<validos; i++)
    {
        muestraUnProducto(arreglo[i]);
    }
}

///DAR DE BAJA UN PRODUCTO///
void bajaProducto (char archivo[], int codigo)
{
    int pos=0;
    stProducto producto;

    pos = buscaPosicionProducto (archivo, codigo);

    if (pos>-1)
    {
        FILE *pArch = fopen(archivo, "r+b");
        if(pArch)
        {

            fseek(pArch, sizeof(stProducto)*pos, SEEK_SET);
            fread(&producto, sizeof(stProducto),1,pArch);
            producto.baja=1;
            fseek(pArch, sizeof(stProducto)*(-1), SEEK_CUR);
            fwrite(&producto, sizeof(stProducto), 1, pArch);
            fclose(pArch);
            printf("\nEl producto fue dado de baja\n");
        }

    }
    else
    {
        Color (BLACK, WHITE);
        printf ("\nNo existe un producto con ese c%cdigo", 162);
        Color (BLACK, LMAGENTA);
    }
}

///DAR DE ALTA UN PRODUCTO///
void altaProducto (char archivo[], int codigo)
{
    int pos=0;
    stProducto producto;

    pos = buscaPosicionProducto (archivo, codigo);

    if (pos>-1)
    {
        FILE *pArch = fopen(archivo, "r+b");
        if(pArch)
        {

            fseek(pArch, sizeof(stProducto)*pos, SEEK_SET);
            fread(&producto, sizeof(stProducto),1,pArch);
            producto.baja=0;
            fseek(pArch, sizeof(stProducto)*(-1), SEEK_CUR);
            fwrite(&producto, sizeof(stProducto), 1, pArch);
            fclose(pArch);
            Color (BLACK, WHITE);
            printf("\nEl producto fue dado de alta nuevamente\n");
            Color (BLACK, LMAGENTA);
        }

    }
    else
    {
        Color (BLACK, WHITE);
        printf ("\nNo existe un producto con ese c%cdigo", 162);
        Color (BLACK, LMAGENTA);
    }
}

///PASA A UN ARREGLO PRODUCTOS POR CATEGORIA//
int pasarArchivoToArregloFiltradoCategoriaProducto (char archivo [], stProducto arreglo [], int dimension, int categoria)
{
    FILE *parchivo = NULL;
    int i = 0;
    stProducto p;

    if (contarRegistrosArchivo(archivo, sizeof(stProducto))>0)
    {
        parchivo = fopen(archivo,"rb");

        if(parchivo)
        {
            while ((fread(&p, sizeof(stProducto),1,parchivo) > 0 ) && i<dimension)
            {
                if (p.categoria==categoria)
                {
                    arreglo[i]=p;
                    i++;
                }
            }

        }
        fclose(parchivo);
    }
    else
    {
        Color (BLACK, WHITE);
        printf("\nNo tiene productos cargados en esa categor%ca\n", 161);
        Color (BLACK, LMAGENTA);
    }
    return i;
}

///PASA A UN ARREGLO PRODUCTOS POR CATEGORIA//
int pasarArchivoToArregloFiltradoProductosAlta (char archivo [], stProducto arreglo [], int dimension)
{
    FILE *parchivo = NULL;
    int i = 0;
    stProducto p;

    if (contarRegistrosArchivo(archivo, sizeof(stProducto))>0)
    {
        parchivo = fopen(archivo,"rb");

        if(parchivo)
        {
            while ((fread(&p, sizeof(stProducto),1,parchivo) > 0 ) && i<dimension)
            {
                if (p.baja==0)
                {
                    arreglo[i]=p;
                    i++;
                }
            }

        }
        fclose(parchivo);
    }
    else
    {
        Color (BLACK, WHITE);
        printf("\nNo tiene productos activos en este momento\n");
        Color (BLACK, LMAGENTA);
    }
    return i;
}

///PASA A UN ARREGLO PRODUCTOS POR CATEGORIA//
int pasarArchivoToArregloFiltradoProductosBaja (char archivo [], stProducto arreglo [], int dimension)
{
    FILE *parchivo = NULL;
    int i = 0;
    stProducto p;

    if (contarRegistrosArchivo(archivo, sizeof(stProducto))>0)
    {
        parchivo = fopen(archivo,"rb");

        if(parchivo)
        {
            while ((fread(&p, sizeof(stProducto),1,parchivo) > 0 ) && i<dimension)
            {
                if (p.baja==1)
                {
                    arreglo[i]=p;
                    i++;
                }
            }

        }
        fclose(parchivo);
    }
    else
    {
        Color (BLACK, WHITE);
        printf("\nNo tiene productos inactivos en este momento\n");
        Color (BLACK, LMAGENTA);
    }
    return i;
}
///ORDENACION POR SELECCION PRODUCTOS////
int buscarMenorProducto (stProducto producto[ ], int pos, int validos)
{
    int i=0;
    int posMenor = pos;
    stProducto menor = producto[pos];

    for(i=pos+1; i<validos; i++)
    {
        if( producto[i].codigoProducto< menor.codigoProducto)
        {
            posMenor = i;
            menor = producto[i];
        }
    }
    return posMenor;
}

void ordenacionSeleccionProductos(stProducto producto[ ], int validos)
{
    int posMenor;
    int i = 0;
    stProducto aux;
    while(i<validos - 1)
    {
        posMenor = buscarMenorProducto(producto, i, validos);
        aux = producto[posMenor];
        producto[posMenor] = producto[i];
        producto[i] = aux;
        i++;
    }
}

////////////////////////// FUNCIONES PEDIDOS ///////////////////////////////////////////////////////////////////////////////

///GUARDA UN PEDIDO EN EL ARCHIVO///

void guardaPedidoClienteArchivo (stPedido pedido)
{
    FILE * pArchPedido= fopen(arPedidos, "ab");

    if (pArchPedido != NULL)
    {
        fwrite (&pedido, sizeof(stPedido), 1, pArchPedido);

        fclose(pArchPedido);
    }
}

///CARGA UNA ESTRUCTURA COMPRA  -  PEDIDO PARCIAL///

stDescripcionCompra cargaCompra (char archivoProducto [])
{
    stDescripcionCompra compra;
    int precio = 0;
    int codigo = 0;
    int flag = 0;
    int validos=0;
    int dimension = 100;
    stProducto arregloProductos [dimension];

    do
    {
        Color (BLACK, WHITE);
        printf ("\n                 #define dulC - Una constante de dulzura-                    \n");
        printf ("\n\n                       ...Nuestros productos...\n\n");
        Color (BLACK, LMAGENTA);
        validos = pasarArchivoToArregloFiltradoProductosAlta (arProductos, arregloProductos, dimension);
        ordenacionSeleccionProductos (arregloProductos, validos);
        mostrarArregloDeProductos (arregloProductos, validos);

        Color (BLACK, WHITE);
        printf("\nIngrese el c%cdigo del producto que desea pedir:\n\n", 162);
        Color (BLACK, LMAGENTA);
        scanf("%d", &codigo);
        flag = buscarProductoActivoMenu (codigo);
        if (flag==0)
        {
            Color (BLACK, WHITE);
            printf("\nEl c%cdigo ingresado no se encuentra activo en nuestro men%c\n", 162, 163);
            printf("\nIntente nuevamente\n\n");
            Color (BLACK, LMAGENTA);
            system("pause");
            system("cls");
        }
    }
    while (flag==0);

    compra.codigoProducto=codigo;
    Color (BLACK, WHITE);
    printf("\nQu%c cantidad desea pedir?\n\n", 130);
    Color (BLACK, LMAGENTA);
    scanf("%d", &compra.cantidad);

    precio = precioProducto(archivoProducto, compra.codigoProducto);

    compra.valorCompra=precio*compra.cantidad;

    return compra;
}
///BUSCA SI EXISTE PRODUCTO ACTIVO EN EL MENU///
int buscarProductoActivoMenu(int codigo)
{
    int flag = 0;
    stProducto p;
    FILE *pArch= fopen(arProductos, "rb");
    if(pArch)
    {
        while(fread(&p, sizeof(stProducto),1,pArch) > 0 && flag == 0)
        {
            if(p.codigoProducto==codigo && p.baja==0)
            {
                flag=1;
            }
        }
        fclose(pArch);
    }
    return flag;
}

///BUSCA PRECIO POR CODIGO EN EL ARCHIVO DE PRODUCTOS///

int precioProducto (char archivoProducto [], int codigo)
{
    stProducto producto;

    int precio=0;

    int pos= buscaPosicionProducto(archivoProducto, codigo);

    FILE*pArchi= fopen(archivoProducto, "rb");

    if(pArchi)
    {

        fseek(pArchi, pos*sizeof(stProducto), SEEK_SET);
        fread(&producto, sizeof(stProducto),1,pArchi);
        precio  = producto.precio;
        fclose(pArchi);
    }


    return precio;
}

///CARGAR ARREGLO DE COMPRAS///

int cargaComprasEnArreglo (stDescripcionCompra compras [], int dimension, char archivoProducto[])
{

    char control='s';
    int validos = 0;

    printf("\nComience a realizar su pedido:\n\n");

    while (control=='s'  && validos<dimension)
    {

        compras[validos]=cargaCompra(archivoProducto);
        printf("\nDesea pedir algo m%cs? s/n \n", 160);
        fflush(stdin);
        scanf("%c", &control);


        validos++;
        system("cls");

    }
    return validos;
}

///BUSCAR ULTIMO ID PEDIDO///
int ultimoIdPedido()
{
    stPedido pedido;
    int ultimoID=-1;

    FILE*pArchi = fopen(arPedidos,"rb");

    if(pArchi)
    {
        fseek(pArchi,(-1)*sizeof(stPedido),SEEK_END);

        if(fread(&pedido,sizeof(stPedido),1,pArchi) > 0)
        {
            ultimoID=pedido.idPedido;
        }

        fclose(pArchi);
    }

    return ultimoID;
}

///SUMA ARREGLO DE COMPRAS - SUMA TOTAL DEL PEDIDO///

int sumaArregloCompras (stDescripcionCompra arregloCompras [], int validos)
{
    int total=0;
    int i=0;

    while(i<validos)
    {

        total=total + arregloCompras[i].valorCompra;
        i++;

    }
    return total;
}
///BUSCA ID DE CLIENTE POR DNI///

int buscaIdCliente (char archivoCliente [], int dni)
{
    stCliente cliente;

    int id=-1;

    int pos= buscaPosicion (archivoCliente, dni);

    if(pos>-1)
    {
        FILE*pArchi= fopen(archivoCliente, "rb");

        if(pArchi)
        {
            fseek(pArchi, pos*sizeof(stCliente), SEEK_SET);
            fread(&cliente, sizeof(stCliente),1,pArchi);
            id  = cliente.id;
            fclose(pArchi);

        }
    }


    return id;
}


///CARGA UN PEDIDO

stPedido cargaUnPedido(char archivoCliente[], char archivoProducto[], stDescripcionCompra compras [], int validos, int dni)
{
    stPedido pedido;

    int i=0;

    Color (BLACK, WHITE);
    printf("\nIngrese la fecha de su pedido (dd/mm/aaaa):\n");
    fflush(stdin);
    gets(pedido.fechaPedido);

    pedido.idPedido= ultimoIdPedido() +1;

    pedido.validos=validos;  ///PARA PODER MANEJAR EL ARREGLO DE COMPRAS///

    pedido.costoPedido = sumaArregloCompras (compras, validos);  ///VALOR TOTAL DEL PEDIDO

    while (i<validos)   ///CARGA ESTRCUTURA DE COMPRAS///
    {
        pedido.descripcionPedido[i]=compras[i];
        i++;
    }

    pedido.idCliente=buscaIdCliente(archivoCliente, dni);

    pedido.pedidoAnulado=0;

    return pedido;
}


///muestra una estrucrura compra

void muestraUnaCompra (stDescripcionCompra compra, char archivoProducto[])
{

    FILE *pArch = NULL;

    stProducto p;
    int pos = buscaPosicionProducto (archivoProducto, compra.codigoProducto);

    pArch=fopen(archivoProducto, "rb");
    fseek(pArch, sizeof(stProducto)*pos, SEEK_SET);
    fread(&p, sizeof(stProducto),1,pArch);


    printf("\n%d - %du. - %s - $%d\n", compra.codigoProducto, compra.cantidad, p.descripcion, compra.valorCompra);



}

///MUESTRA EL ARREGLO DE COMPRAS POR PEDIDO///
void mostrarArregloCompras (stDescripcionCompra compra [], int validos, char archivoProducto [])
{
    int i=0;

    for ( i=0; i<validos; i++)
    {
        muestraUnaCompra (compra[i], archivoProducto);
    }
}

///MUESTRA EL PEDIDO///
void muestraUnPedido (stPedido pedido, char archivoProducto [], stDescripcionCompra compras [])
{

    Color (BLACK, LMAGENTA);
    printf("\nID Cliente: %d \n", pedido.idCliente);

    printf("\nID Pedido:  %d \n", pedido.idPedido );

    printf("\nFecha: %s \n", pedido.fechaPedido);

    printf("\n");
    Color (BLACK, WHITE);

    mostrarArregloCompras (compras, pedido.validos, archivoProducto);

    printf("\n\nTotal de su pedido: $%d \n\n", pedido.costoPedido);
    Color (BLACK, LMAGENTA);


}

///FUNCION COMPLETA DE ALTA DE PEDIDO -> ALTA - MOSTRAR///
void funcionCompletaAltaPedido ()
{
    int dimension = 100;
    stDescripcionCompra arregloCompras [dimension];
    int validosCompra = 0;
    stPedido pedido;
    int dni = 0;


    printf("Ingrese su DNI:\n");
    scanf("%d", &dni);
    if (buscarClienteDNIArchivo(dni) == 1)
    {
        system("cls");
        validosCompra = cargaComprasEnArreglo (arregloCompras, dimension, arProductos);
        pedido = cargaUnPedido (arCliente, arProductos, arregloCompras, validosCompra, dni);
        guardaPedidoClienteArchivo (pedido);
        system("cls");
        muestraUnPedido (pedido, arProductos, arregloCompras);
        printf("\n");
        printf("\nMuchas gracias por su compra!\n");


    }
    else
    {
        Color (BLACK, WHITE);
        printf ("\nUd. a%cn no es cliente de #define dulC, lo invitamos a registrarse", 163);
        Color (BLACK, LMAGENTA);
    }
}

///MUESTRA PEDIDOS ACTIVOS///
void mostrarArchivoPedidosActivos (char archivoPedidos [], char archivoProductos[])
{
    FILE *parchivo = NULL;

    stPedido pedido;

    if (contarRegistrosArchivo(archivoPedidos, sizeof(stPedido))>0)
    {
        parchivo = fopen(archivoPedidos,"rb");

        if(parchivo!=NULL)
        {
            printf("\nListado de pedidos:\n\n");

            while(fread(&pedido, sizeof(stPedido),1,parchivo)>0)
            {
                if (pedido.pedidoAnulado==0)
                {
                    printf("-----------------------------------------------------------------------\n");
                    muestraUnPedido (pedido, archivoProductos, pedido.descripcionPedido);
                    printf("-----------------------------------------------------------------------\n");
                }

            }
            fclose(parchivo);
        }
    }
    else
    {
        Color (BLACK, WHITE);
        printf("\nNo tiene pedidos activos cargados");
        Color (BLACK, LMAGENTA);
    }

}
///MUESTRA PEDIDOS POR CLIENTE///
void mostrarArchivoPedidosFiltradoPorCliente (char archivoClientes [], char archivoPedidos [], char archivoProductos[], int dni)
{
    int id  = buscaIdCliente (archivoClientes, dni);
    stPedido pedido;

    if (id>-1)
    {
        FILE *parchivo = NULL;
        if (contarRegistrosArchivo(archivoPedidos, sizeof(stPedido))>0)
        {
            parchivo = fopen(archivoPedidos,"rb");


            if(parchivo!=NULL)
            {
                printf("\nListado de pedidos:\n\n");

                while(fread(&pedido, sizeof(stPedido),1,parchivo)>0)
                {
                    if (pedido.idCliente==id)
                    {
                        printf("----------------------------------------------------------------------\n");
                        muestraUnPedido (pedido, archivoProductos, pedido.descripcionPedido);
                        printf("----------------------------------------------------------------------\n");
                    }

                }
                fclose(parchivo);
            }
        }
        else
        {
            Color (BLACK, WHITE);
            printf("\nNo tiene pedidos realizados");
            Color (BLACK, LMAGENTA);
        }

    }
    else
    {
        Color (BLACK, WHITE);
        printf("\nUd. no es cliente de #define dulC, lo invitamos a registrarse\n");
        Color (BLACK, LMAGENTA);
    }


}

///BUSCAR POSICION EN ARCHIVO DE PEDIDOS///
int buscaPosicionPedido(char archivoPedidos[], int id)
{
    int pos=-1;
    stPedido p;
    FILE *pArch = fopen(archivoPedidos,"rb");
    if(pArch)
    {
        while(pos == -1 && fread(&p, sizeof(stPedido), 1, pArch) > 0)
        {
            if(p.idPedido == id)
            {
                pos = ftell(pArch)/sizeof(stPedido)-1;
            }
        }
        fclose(pArch);
    }

    return pos;
}

///DAR DE BAJA UN PEDIDO///
void bajaPedido (char archivoPedidos[], int id)
{
    int pos=0;
    stPedido p;

    pos = buscaPosicionPedido (archivoPedidos, id);

    if (pos>-1)
    {
        FILE *pArch = fopen(archivoPedidos, "r+b");
        if(pArch)
        {

            fseek(pArch, sizeof(stPedido)*pos, SEEK_SET);
            fread(&p, sizeof(stPedido),1,pArch);
            p.pedidoAnulado=1;
            fseek(pArch, sizeof(stPedido)*(-1), SEEK_CUR);
            fwrite(&p, sizeof(stPedido), 1, pArch);
            fclose(pArch);
            printf("\nEl pedido fue dado de baja\n");
        }

    }
    else
    {
        Color (BLACK, WHITE);
        printf ("\nNo existe un pedido con ese ID");
        Color (BLACK, LMAGENTA);
    }
}

void mostrarArchivoPedidosFiltradoPorClienteYAlta (char archivoClientes [], char archivoPedidos [], char archivoProductos[], int dni)
{
    int id  = buscaIdCliente (archivoClientes, dni);
    stPedido pedido;

    if (id>-1)
    {
        FILE *parchivo = NULL;
        if (contarRegistrosArchivo(archivoPedidos, sizeof(stPedido))>0)
        {
            parchivo = fopen(archivoPedidos,"rb");


            if(parchivo!=NULL)
            {
                printf("\nListado de pedidos:\n\n");

                while(fread(&pedido, sizeof(stPedido),1,parchivo)>0)
                {
                    if (pedido.idCliente==id && pedido.pedidoAnulado==0)
                    {
                        printf("--------------------------------------------------------------------------------\n");
                        muestraUnPedido (pedido, archivoProductos, pedido.descripcionPedido);
                        printf("--------------------------------------------------------------------------------\n");
                    }

                }
                fclose(parchivo);
            }
        }
        else
        {
            Color (BLACK, WHITE);
            printf("\nNo tiene pedidos activos en este momento");
            Color (BLACK, LMAGENTA);
        }

    }
    else
    {
        Color (BLACK, WHITE);
        printf("\nUd. no es cliente de #define dulC, lo invitamos a registrarse\n");
        Color (BLACK, LMAGENTA);
    }


}
///BUSCAR POSICION DEL PEDIDO EN EL ARCHIVO///
int buscarPosicionPedido(char archivoPedido[], int id)
{
    int pos=-1;
    stPedido p;
    FILE *pArch = fopen(archivoPedido,"rb");
    if(pArch)
    {
        while(pos == -1 && fread(&p, sizeof(stPedido), 1, pArch) > 0)
        {
            if(p.idPedido == id)
            {
                pos = ftell(pArch)/sizeof(stPedido)-1;
            }
        }
        fclose(pArch);
    }

    return pos;
}
///BUSCA LA POSICION DEL CODIGO DEL PRODUCTO DENTRO DEL ARREGLO DEL PEDIDO///
int recorrerArregloPedido (stDescripcionCompra compras [], int validos, int codigo)
{
    int i = 0;
    int pos = -1;

    for (i=0; i<validos; i++)
    {
        if (compras[i].codigoProducto == codigo) ///RECORRO EL ARREGLO P/ ENCONTRAR LA POS DEL CODIGO A MODIFICAR
        {
            pos = i;
        }
    }
    return pos;
}

int buscaPosicionPedidoArregloInterno(char archivoPedido[], int codigo, int posPedido)
{
    int pos=-1;
    stPedido p;

    FILE *pArch = fopen(archivoPedido,"rb");


    if(pArch)
    {
        fseek(pArch, sizeof(stPedido)*posPedido, SEEK_SET);
        fread(&p, sizeof(stPedido),1,pArch);  /// ME PARO EN POS DEL PEDIDO

        pos = recorrerArregloPedido (p.descripcionPedido, p.validos, codigo);


    }

    return pos;
}

///MODIFICAR REGISTRO DE PEDIDO///
void modificarRegistroPedido(char archivoPedido[], int id, char archivoProducto[])
{
    char control;
    int funcion = 0;
    int pos=0;
    char fecha[30];
    int codigo=0;
    stPedido pedido;
    int posCompra = 0;
    int flagCodigo =0;

    pos = buscarPosicionPedido (archivoPedido, id);

    if (pos>-1)
    {
        FILE *pArch = fopen(archivoPedido, "r+b");
        if(pArch)
        {

            fseek(pArch, sizeof(stPedido)*pos, SEEK_SET);
            fread(&pedido, sizeof(stPedido),1,pArch);

            do
            {
                system ("cls");
                menuModificacionRegistroPedido();
                scanf("%i", &funcion);
                system("cls");

                switch(funcion)
                {
                case 1:
                    Color (BLACK, WHITE);
                    printf("Ingrese la nuevamente la fecha\n");
                    Color (BLACK, LMAGENTA);
                    fflush (stdin);
                    gets (fecha);
                    strcpy(pedido.fechaPedido, fecha);
                    break;


                case 2:
                    Color (BLACK, WHITE);   ///MODIFICA CANT DE UN PRODUCTO///
                    printf("Ingrese el c%cdigo del producto que desea modificar\n", 162);
                    Color (BLACK, LMAGENTA);
                    scanf("%d", &codigo);
                    flagCodigo = recorrerArregloPedido (pedido.descripcionPedido, pedido.validos, codigo); ///SE FIJA SI EL CODIGO ESTA EN EL ARREGLO COMPRA
                    if (flagCodigo>-1)
                    {
                        posCompra = buscaPosicionPedidoArregloInterno (archivoPedido, codigo, pos); ///BUSCO POS EN ARREGLO
                        Color (BLACK, WHITE);
                        printf("Ingrese nuevamente la cantidad que desea pedir\n");
                        Color (BLACK, LMAGENTA);
                        scanf("%d", &pedido.descripcionPedido[posCompra].cantidad); /// GUARDA LA NUEVA CANT EN ESA COMPRA
                        pedido.descripcionPedido[posCompra].valorCompra = precioProducto (archivoProducto, codigo)*pedido.descripcionPedido[posCompra].cantidad;  //VUELVE A CALCULAR PRECIO DE LA COMPRA
                        pedido.costoPedido  = sumaArregloCompras (pedido.descripcionPedido, pedido.validos); /// VUELVE A CALCULAR PRECIO TOTAL DEL PEDIDO
                    }
                    else
                    {
                        Color (BLACK, WHITE);
                        printf ("\nEl c%cdigo de producto ingresado no se encuentra dentro de su pedido", 162);
                        Color (BLACK, LMAGENTA);
                    }

                    break;

                case 3:
                    pedido.descripcionPedido[pedido.validos]= cargaCompra (archivoProducto);  //AGREGAR PRODUCTO
                    pedido.validos=pedido.validos+1; // SE SUMA UN POS AL ARREGLO
                    pedido.costoPedido  = sumaArregloCompras (pedido.descripcionPedido, pedido.validos); ///VUELVE A CALCULAR TOTAL
                    break;

                case 4:
                    Color (BLACK, WHITE);  /// ELIMINA UN PRODUCTO
                    printf("Ingrese el c%cdigo del producto que desea eliminar de su pedido\n", 162);
                    Color (BLACK, LMAGENTA);
                    scanf("%d", &codigo);
                    flagCodigo = recorrerArregloPedido (pedido.descripcionPedido, pedido.validos, codigo);
                    if (flagCodigo>-1)
                    {
                        posCompra = buscaPosicionPedidoArregloInterno (archivoPedido, codigo, pos);
                        pedido.descripcionPedido[posCompra].cantidad = 0;
                        pedido.descripcionPedido[posCompra].valorCompra = precioProducto (archivoProducto, codigo)*pedido.descripcionPedido[posCompra].cantidad;
                        pedido.costoPedido  = sumaArregloCompras (pedido.descripcionPedido, pedido.validos);
                    }
                    else
                    {
                        Color (BLACK, WHITE);
                        printf ("\nEl c%cdigo de producto ingresado no se encuentra dentro de su pedido", 162);
                        Color (BLACK, LMAGENTA);
                    }

                    break;


                default:
                    Color (BLACK, WHITE);
                    printf("La funci%cn no existe \n", 162);
                    Color (BLACK, LMAGENTA);

                }

                fseek(pArch, sizeof(stPedido)*(-1), SEEK_CUR);
                fwrite(&pedido, sizeof(stPedido), 1, pArch);

                printf("\n\nQuiere modificar otro dato? s/n\n");
                fflush(stdin);
                printf("%c\n", control = getch());

            }
            while(control == 's');

            fclose(pArch);
        }
    }
    else
    {
        Color (BLACK, WHITE);
        printf("No tenemos registrado un pedido con ese ID\n");
        Color (BLACK, LMAGENTA);
    }
}

///MENU PARA MODIFICAR EL PEDIDO//
void menuModificacionRegistroPedido ()
{
    Color (BLACK, WHITE);
    printf("Qu%c dato desea modificar?\n", 130);
    Color (BLACK, LMAGENTA);
    printf("1- Fecha del pedido\n");
    printf("2- Modificar cantidad de un producto pedido\n");
    printf("3- Agregar un producto al pedido\n");
    printf("4- Eliminar un producto del pedido\n");

}
//////////////////ESTADISTICAS  --- RANKING DE PRODUCTOS//////////////////
int contarCantProductosVendidosPorCodigo(char archivoPedidos [], char archivoProductos[], stVentaProducto venta[], int dimension)
{
    FILE *parchivoPed = fopen(archivoPedidos,"rb");
    FILE *parchivoProd = fopen(archivoProductos,"rb");
    stPedido pedido;
    stProducto prod;
    int totalParcial=0;
    int totalFinal =0;
    int i=0;

    if(parchivoPed && parchivoProd)
    {
        while((fread(&prod, sizeof(stProducto), 1, parchivoProd) > 0) && i<dimension) ///LEE LOS CODIGOS DEL ARCHIVO DE PRODUCTOS
        {
            fseek(parchivoPed, 0, SEEK_SET);
            totalFinal = 0;

            while(fread(&pedido, sizeof(stPedido),1,parchivoPed)>0)  ///LEE LOS CODIGOS DEL ARCHIVO DE PEDIDO
            {
                totalParcial = recorrerArregloPedidoSumaCodigos (pedido.descripcionPedido, pedido.validos, prod.codigoProducto);
                totalFinal = totalFinal + totalParcial; ///ACUMULADOR P/ CANT DE COMPRAS POR CODIGO

            }
             venta[i].codigo=prod.codigoProducto;
             venta[i].totalVendidos=totalFinal;

            i++;
        }

        fclose(parchivoPed);
        fclose(parchivoProd);
    }
    return i;
}

///SUMAR CANT. DE UN PRODUCTO EN CADA PEDIDO///
int recorrerArregloPedidoSumaCodigos (stDescripcionCompra compras [], int validos, int codigo)
{
    int i = 0;
    int total = 0;

    for (i=0; i<validos; i++)
    {
        if (compras[i].codigoProducto == codigo)
        {
            total++;
        }
    }
    return total;
}

int buscarPosProductoMasVendido (stVentaProducto ventaP[ ], int pos, int validos)
{
    int i=0;
    int posMayor = pos;
    stVentaProducto mayor = ventaP[pos];

    for(i=pos+1; i<validos; i++)
    {
        if( ventaP[i].totalVendidos> mayor.totalVendidos)
        {
            posMayor = i;
            mayor = ventaP[i];
        }
    }
    return posMayor;
}

void ordenacionSeleccionProductoMasVendido(stVentaProducto ventaP[ ], int validos)
{
    int posMayor;
    int i = 0;
    stVentaProducto aux;
    while(i<validos - 1)
    {
        posMayor = buscarPosProductoMasVendido(ventaP, i, validos);
        aux = ventaP[posMayor];
        ventaP[posMayor] = ventaP[i];
        ventaP[i] = aux;
        i++;
    }
}

void mostrarArregloProductosMasVendidos(stVentaProducto arregloVendidos[], int validos)
{


    for (int i=0; i<validos; i++)
    {
        Color (BLACK, WHITE);
        printf("-----------------------------------------\n");

        printf ("ID Producto:");
        Color (BLACK, LMAGENTA);
        printf (" %d", arregloVendidos[i].codigo);
        printf("  ");
        Color (BLACK, WHITE);
        printf ("Total vendidos:");
        Color (BLACK, LMAGENTA);
        printf (" %d\n", arregloVendidos[i].totalVendidos);

         Color (BLACK, WHITE);
        printf("-----------------------------------------\n");
        Color (BLACK, LMAGENTA);
    }
}


///ESTADISTICAS  --- MEJOR CLIENTE///
int arregloPedidosPorCliente (char archivoClientes [], char archivoPedidos[], stEstadistica arregloEstadistica[], int dimension)
{
    stCliente c;
    stPedido p;
    int i=0;
    int totalP = 0;
    FILE *parchivoPed = fopen(archivoPedidos,"rb");
    FILE *parchivoCli = fopen(archivoClientes,"rb");

    if (parchivoCli && parchivoPed)
    {


        while((fread(&c, sizeof(stCliente), 1, parchivoCli) > 0) && i<dimension)  ///LEE CADA CLIENTE
        {
            fseek(parchivoPed, 0, SEEK_SET);
            totalP = 0;
            while(fread(&p, sizeof(stPedido), 1, parchivoPed) > 0)  ///LEE UN PEDIDO
            {
                if (c.id ==p.idCliente)
                {
                    totalP++;
                }
                arregloEstadistica[i].idCliente=c.id;
                arregloEstadistica[i].totalPedidos=totalP;

            }
            i++;
        }


        fclose(parchivoCli);
        fclose(parchivoPed);
    }
    return i;
}


int buscarPosClienteMayorPedido (stEstadistica estadistica[ ], int pos, int validos)
{
    int i=0;
    int posMayor = pos;
    stEstadistica mayor = estadistica[pos];

    for(i=pos+1; i<validos; i++)
    {
        if( estadistica[i].totalPedidos> mayor.totalPedidos)
        {
            posMayor = i;
            mayor = estadistica[i];
        }
    }
    return posMayor;
}

void ordenacionSeleccionClientesPorPedidos(stEstadistica estadistica[ ], int validos)
{
    int posMayor;
    int i = 0;
    stEstadistica aux;
    while(i<validos - 1)
    {
        posMayor = buscarPosClienteMayorPedido(estadistica, i, validos);
        aux = estadistica[posMayor];
        estadistica[posMayor] = estadistica[i];
        estadistica[i] = aux;
        i++;
    }
}

///MOSTRAR ARREGLO ESTADISTICA///
void mostrarArregloDeEstadistica(stEstadistica arregloEst[], int validos)
{


    for (int i=0; i<validos; i++)
    {
        Color (BLACK, WHITE);
        printf("-----------------------------------------\n");

        printf ("ID Cliente:");
        Color (BLACK, LMAGENTA);
        printf (" %d   ", arregloEst[i].idCliente);
        Color (BLACK, WHITE);
        printf ("Total de pedidos:");
        Color (BLACK, LMAGENTA);
        printf (" %d\n", arregloEst[i].totalPedidos);
        Color (BLACK, WHITE);
        printf("-----------------------------------------\n");
        Color (BLACK, LMAGENTA);
    }
}


///////////////////////////////////////////////////MENU/////////////////////////////////////////////////////////
void menuUsuarioProgramador()
{
    system ("Color 011");
    printf("\n");
    Color (BLACK, LGREY);
    printf("             ------------------- BIENVENIDOS -------------------    \n");
    printf("\n");
    Color (BLACK, LMAGENTA);
    printf("                   #define dulC, -Una constante de dulzura-        \n" );
    printf("\n");
    printf("\n");
    Color (BLACK, WHITE);
    printf("Escriba el n%cmero de men%c al que se quiera dirigir:", 163, 163);
    printf("\n");
    printf("\n");
    Color (BLACK, LMAGENTA);
    printf(" 1- CLIENTE\n");
    printf("\n");
    Color (BLACK, LMAGENTA);
    printf(" 2- ADMINISTRADOR");
    printf("\n");
    printf("\n");
}

void menuClientesOPedidos()
{

    printf("\n");
    Color (BLACK, LMAGENTA);
    printf("                #define dulC, -Una constante de dulzura-   \n");
    printf("\n");
    printf("\n");
    Color (BLACK, WHITE);
    printf("Escriba el n%cmero de men%c al que se quiera dirigir:", 163, 163);
    printf("\n");
    printf("\n");
    Color (BLACK, LMAGENTA);
    printf(" 1- CLIENTES\n");
    printf("\n");
    Color (BLACK, LMAGENTA);
    printf(" 2- PEDIDOS");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    Color (BLACK, LMAGENTA);
    printf("99- Volver al men%c principal\n", 163);
    printf("\n");
    printf("\n");
}

void menuClientesPedidosProductoAdm()
{

    printf("\n");
    Color (BLACK, LMAGENTA);
    printf("                 #define dulC, -Una constante de dulzura-  \n");
    printf("\n");
    printf("\n");
    Color (BLACK, WHITE);
    printf("Escriba el n%cmero de men%c al que se quiera dirigir:", 163, 163);
    printf("\n");
    printf("\n");
    Color (BLACK, LMAGENTA);
    printf(" 1- CLIENTES\n");
    printf("\n");
    Color (BLACK, LMAGENTA);
    printf(" 2- PRODUCTOS\n");
    printf("\n");
    Color (BLACK, LMAGENTA);
    printf(" 3- PEDIDOS");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    Color (BLACK, LMAGENTA);
    printf("99- Volver al men%c principal\n", 163);
    printf("\n");
    printf("\n");
}

void menuClientesUsuario()
{
    printf("\n");
    Color (BLACK,LGREY);
    printf("CLIENTES");
    printf("\n");
    printf("\n");
    printf("\n");
    Color (BLACK, WHITE);
    printf("Ingrese la opci%cn a la que desea dirigirse:\n", 162);
    printf("\n");
    Color (BLACK, LMAGENTA);
    printf(" 1- Nuevo Cliente dulC\n");
    printf("\n");
    Color (BLACK, LMAGENTA);
    printf(" 2- Ver mis datos\n");
    printf("\n");
    Color (BLACK, LMAGENTA);
    printf(" 3- Modificar mis datos\n");
    printf("\n");
    Color (BLACK, LMAGENTA);
    printf(" 4- Darme de baja\n");
    printf("\n");
    printf("\n");
    printf("\n");
    Color (BLACK, LMAGENTA);
    printf("98- Volver al men%c Clientes/Pedidos\n", 163);
    Color (BLACK, LMAGENTA);
    printf("99- Volver al men%c principal\n", 163);
    printf("\n");
    printf("\n");
}

void menuClientesProgramador()
{
    printf("\n");
    Color (BLACK,LGREY);
    printf("CLIENTES");
    printf("\n");
    printf("\n");
    Color (BLACK, WHITE);
    printf("Ingrese la opci%cn a la que desea dirigirse:\n", 162);
    printf("\n");
    Color (BLACK, LMAGENTA);
    printf(" 1- Nuevo Cliente dulC\n");
    printf("\n");
    Color (BLACK, LMAGENTA);
    printf(" 2- Ver Cliente por DNI\n");
    printf("\n");
    Color (BLACK, LMAGENTA);
    printf(" 3- Modificar datos de un cliente\n");
    printf("\n");
    Color (BLACK, LMAGENTA);
    printf(" 4- Dar de baja un cliente\n");
    printf("\n");
    Color (BLACK, LMAGENTA);
    printf(" 5- Listado de clientes activos\n");
    printf("\n");
    Color (BLACK, LMAGENTA);
    printf(" 6- Listado de clientes inactivos\n");
    printf("\n");
    Color (BLACK, LMAGENTA);
    printf(" 7- Listado de los mejores clientes\n");
    printf("\n");
    printf("\n");
    printf("\n");
    Color (BLACK, LMAGENTA);
    printf("98- Volver al men%c Clientes/Productos/Pedidos\n", 163);
    Color (BLACK, LMAGENTA);
    printf("99- Volver al men%c principal\n", 163);
    printf("\n");
    printf("\n");
}

void menuPedidosUsuario()
{
    printf("\n");
    Color (BLACK,LGREY);
    printf("PEDIDOS");
    printf("\n");
    printf("\n");
    Color (BLACK, WHITE);
    printf("Ingrese la opci%cn a la que desea dirigirse:\n", 162);
    printf("\n");
    Color (BLACK, LMAGENTA);
    printf(" 1- Ver men%c\n", 163);
    printf("\n");
    Color (BLACK, LMAGENTA);
    printf(" 2- Hacer un pedido\n");
    printf("\n");
    Color (BLACK, LMAGENTA);
    printf(" 3- Modificar mi pedido\n");
    printf("\n");
    Color (BLACK, LMAGENTA);
    printf(" 4- Ver mis pedidos\n");
    printf("\n");
    Color (BLACK, LMAGENTA);
    printf(" 5- Ver mis pedidos activos\n");
    printf("\n");
    Color (BLACK, LMAGENTA);
    printf(" 6- Anular pedido\n");
    printf("\n");
    printf("\n");
    printf("\n");
    Color (BLACK, LMAGENTA);
    printf("98- Volver al men%c Clientes/Pedidos\n", 163);
    Color (BLACK, LMAGENTA);
    printf("99- Volver al men%c principal\n", 163);
    printf("\n");
    printf("\n");
}

void menuPedidosProgramador()
{
    printf("\n");
    Color (BLACK,LGREY);
    printf("PEDIDOS");
    printf("\n");
    printf("\n");
    Color (BLACK, WHITE);
    printf("Ingrese la opci%cn a la que desea dirigirse:\n", 162);
    printf("\n");
    Color (BLACK, LMAGENTA);
    printf(" 1- Ver men%c\n", 163);
    printf("\n");
    Color (BLACK, LMAGENTA);
    printf(" 2- Hacer un pedido\n");
    printf("\n");
    Color (BLACK, LMAGENTA);
    printf(" 3- Modificar un pedido\n");
    printf("\n");
    Color (BLACK, LMAGENTA);
    printf(" 4- Ver pedidos activos\n");
    printf("\n");
    Color (BLACK, LMAGENTA);
    printf(" 5- Ver pedidos por cliente\n");
    printf("\n");
    Color (BLACK, LMAGENTA);
    printf(" 6- Ver pedidos activos por cliente\n");
    printf("\n");
    Color (BLACK, LMAGENTA);
    printf(" 7- Anular un pedido\n");
    printf("\n");
    printf("\n");
    printf("\n");
    Color (BLACK, LMAGENTA);
    printf("98- Volver al men%c Clientes/Productos/Pedidos\n", 163);
    Color (BLACK, LMAGENTA);
    printf("99- Volver al men%c principal\n", 163);
    printf("\n");
    printf("\n");
}

void menuProductosProgramador()
{
    printf("\n");
    Color (BLACK,LGREY);
    printf("PRODUCTOS");
    printf("\n");
    printf("\n");
    Color (BLACK, WHITE);
    printf("Ingrese la opci%cn a la que desea dirigirse:\n", 162);
    printf("\n");
    Color (BLACK, LMAGENTA);
    printf(" 1- Cargar nuevo producto\n");
    printf("\n");
    Color (BLACK, LMAGENTA);
    printf(" 2- Ver listado  completo de productos activos e inactivos\n");
    printf("\n");
    Color (BLACK, LMAGENTA);
    printf(" 3- Ver listado de productos por categor%ca\n", 161);
    printf("\n");
    Color (BLACK, LMAGENTA);
    printf(" 4- Ver listado de productos activos\n");
    printf("\n");
    Color (BLACK, LMAGENTA);
    printf(" 5- Ver listado de productos inactivos\n");
    printf("\n");
    Color (BLACK, LMAGENTA);
    printf(" 6- Ver productos m%cs vendidos\n", 160);
    printf("\n");
    Color (BLACK, LMAGENTA);
    printf(" 7- Modificar un producto\n");
    printf("\n");
    Color (BLACK, LMAGENTA);
    printf(" 8- Dar de baja un producto\n");
    printf("\n");
    Color (BLACK, LMAGENTA);
    printf(" 9- Dar de alta un producto\n");
    printf("\n");
    printf("\n");
    printf("\n");
    Color (BLACK, LMAGENTA);
    printf("98- Volver al men%c Clientes/Productos/Pedidos\n", 163);
    Color (BLACK, LMAGENTA);
    printf("99- Volver al men%c principal\n", 163);
    printf("\n");
    printf("\n");
}
