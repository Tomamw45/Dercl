#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MaxDistribuidoras 1000
#define MaxClientes 50000
#define MaxProductos 50000
#define MaxProductosCompra 5000

struct Derco{
    struct NodoImportadora *Importadora;
    struct NodoDistribuidora *Distribuidora;
    struct NodoCliente *abbClientes;
};

struct NodoImportadora{
    struct Importadora *datosImportadora;
    struct NodoImportadora *sig;
};

struct Importadora{
    char *rutImportadora;
    char *Ubicacion;
    int idImportadora;
    int CapacidadAlmacenamiento;
    struct Distribuidora **Distribuidoras;
    int pLibreDistribuidora;
};

struct NodoDistribuidora{
    struct Distribuidora *datosDistribuidora;
    struct NodoDistribuidora *sig;
};

struct Distribuidora{
    char nombre;
    char direccion;
    int idDistribuidora;
    struct Desplazamiento *Desplazamientos;
    int pLibreDesplazamiento;
};

struct Desplazamiento{
    int TiempoViaje;
    int idImportadora;
};

struct NodoCliente{
    struct Cliente *datosCliente;
    struct NodoCliente *izq, *der;
};

struct Cliente{
    char *nombre;
    char *rut;
    int IdCliente;
    struct NodoCompra ** HeadCompras;
};

struct NodoCompra{
    struct Compras *datosCompra;
    struct NodoCompra *sig;
};

struct Compra{
    int idDistribuidora;
    int idCompra;
    int fechaCompra;
    struct Producto **productosComprados;
    int pLibreProducto;
};

struct Producto{
    char *nombre;
    char *tipo;
    int precio;
    int id;
};

// Fin de definiciones

// Funciones lista circular NodoImportadora

void agregarImportadora(struct NodoImportadora** head, struct Importadora *nueva) {
    struct NodoImportadora* rec = *head;

    struct NodoImportadora* NuevaImp = (struct NodoImportadora*)malloc(sizeof(struct NodoImportadora))
    NuevaImp -> datosImportadora = nueva;

    if (*head == NULL) {
        *head = NuevaImp;
        NuevaImp->sig = NuevaImp;
    } // si esta vacia, hacerla head
    else
    {
        while(rec->sig != *head){
            rec = rec->sig;
        }
        rec->sig = NuevaImp;
        NuevaImp->sig = *head; //agregarla al final de la lista
    }
}

struct Importadora* BuscarImportadora(struct NodoImportadora *head, int id) {
    struct NodoImportadora *rec = head;
    if (head == NULL) {
        return NULL;
    }

    do {
        struct Importadora *datos = rec->datosImportadora;

        do {
            if (datos->idImportadora == id) {
                return datos;
            }
            datos = datos->sig;
        }while (datos != datos->rec);

        rec = rec->sig;
    }while (rec != head);

    return NULL;
}

void EliminarImportadora(struct NodoImportadora **head, int id) {
    if (*head == NULL) {
        return; // si es el head
    }

    struct NodoImportadora* rec = *head;
    struct NodoImportadora* ant = NULL;

    while(rec->datosImportadora->idImportadora != id)
    {
        ant = rec;
        rec = rec->sig;

        if (rec == *head) {
            return; /* si no lo encontramos en la lista */
        }
    }

    if (rec->datosImportadora != NULL && rec->datosImportadora->idImportadora == id) {
        struct NodoImportadora* datosHead->datosImportadora = rec->datosImportadora;
        struct NodoImportadora* datosAnt = datosHead;
        while (datosAnt->sig != datosHead){
            datosAnt = datosAnt->sig;
        }
        rec->datosImportadora = datosHead->sig;
        datosAnt->sig = datosHead->sig;
    }
    if (ant != NULL){
        ant->sig = rec->sig;
    }

    else{
        *head = rec->sig;
    }
}

void mostrarImportadoras(struct NodoImportadora *head)
{
    struct NodoImportadora *rec = head;

    if (head == NULL)
    {
        return;
    }
    rec = head->sig;

    while(rec!=head)
    {
        printf("%s\n",rec->datosImportadora->rutImportadora);
        printf("%s\n",rec->datosImportadora->Ubicacion);
        printf("%d\n",rec->datosImportadora->idImportadora);
        printf("%d\n",rec->datosImportadora->CapacidadAlmacenamiento);
        printf("\n");
        rec = rec->sig;
    }
}

void ModificarImportadora(struct Importadora **importadora, int NuevaId)
{
    (*importadora)->idImportadora = NuevaId;
    return;
}

// Funciones arreglo Distribuidoras con pLibre

void AgregarArrDistribuidora(struct Distribuidora ***distribuidoras, struct Distribuidora *nuevo, int *pLibreDistribuidora)
{
    (*distribuidoras)[*pLibreDistribuidora] = nuevo;
    (*pLibreDistribuidora)++;
    return;
}

struct Distribuidora *BuscarArrDistribuidora(struct Distribuidora **distribuidoras, int id, int pLibreDistribuidora)
{
    int i;

    for(i=0; i<pLibreDistribuidora; i++)
    {
        if(distribuidoras[i]->id == id)
        {
            return distribuidoras[i];
        }
    }
    return NULL; //distribuidora no encontrada
}

void EliminarArrDistribuidora(struct Distribuidora ***distribuidoras, int pLibreDistribuidora, int id)
{
    int i;

    for(i=0; i<pLibreDistribuidora; i++)
    {
        if((*distribuidoras)[i]->idDistribuidora == id)
        {
            (*distribuidoras)[i] = NULL;
            (*distribuidoras)[i]=(*distribuidoras)[(*pLibreDistribuidora)-1];
            (*distribuidoras)[(*pLibreDistribuidora)-1]=NULL;
            (*pLibreDistribuidora)--;
            return;
        }
    }
}

void mostrarArrDistribuidora(struct  Distribuidora **distribuidoras, int pLibreDistribuidora){
    int i;

    for(i=0; i<pLibreDistribuidora; i++){
        printf("%s\n", distribuidoras[i]->nombre);
        printf("%s\n", distribuidoras[i]->direccion);
        printf("%d\n", distribuidoras[i]->idDistribuidora);
        printf("\n");

        mostrarDesplazamiento(distribuidoras[i]->Desplazamientos, distribuidoras[i]->pLibreDesplazamiento);

    }
}

void ModificarArrDistribuidora(struct Distribuidora **distribuidoras, int NuevaId)
{
    (*distribuidoras)->idDistribuidora = NuevaId;
    return;
}

// Funciones lista simplemente enlazada NodoDistribuidora

void AgregarDistribuidora(struct NodoDistribuidora **distribuidoras, struct Distribuidora *nueva)
{

    if((*distribuidoras) == NULL)
    {
        (*distribuidoras) = (struct NodoDistribuidora *)malloc(sizeof (struct NodoDistribuidora));
        (*distribuidoras)->datosDistribuidora = nueva;
        (*distribuidoras)->sig = NULL;
        return;
    }

    struct NodoDistribuidora *rec = *distribuidoras;

    while(rec != NULL)
    {
        if(rec->sig == NULL)
        {
            rec->sig->datosDistribuidora = nueva;
            rec->sig->sig = NULL;
            return;
        }
        rec = rec->sig;
    }
}

struct Distribuidora *BuscarDistribuidora(struct NodoDistribuidora *distribuidoras, int id)
{
    struct NodoDistribuidora *rec = distribuidoras;

    while (rec != NULL) {
        if (rec->datosDistribuidora->idDistribuidora == id)
            return rec->datosDistribuidora;
        rec = rec->sig;
    }
    return NULL;
}

void EliminarDistribuidora(struct NodoDistribuidora **distribuidora, int id)
{
    struct NodoDistribuidora *rec = *distribuidora;

    if ((*distribuidora)->datosDistribuidora->idDistribuidora == id)
    {
        (*distribuidora)->datosDistribuidora = NULL;
        (*distribuidora) = (*distribuidora)->sig;
        return;
    }

    while(rec != NULL)
    {
        if(rec->sig->datosDistribuidora->idDistribuidora == id && rec->sig->sig == NULL)
        {
            rec->sig = NULL;
            return;
        }

        if(rec->sig->datosDistribuidora->idDistribuidora == id)
        {
            rec->sig = rec->sig->sig;
            return;
        }

        rec=rec->sig;
    }
}

void mostrarDistribuidoras(struct NodoDistribuidora *distribuidora){
    struct NodoPlantaDistribucion *rec = distribuidora;

    while (rec!=NULL)
    {
        printf("%s\n",rec->datosDistribuidora->nombre);
        printf("%s\n",rec->datosDistribuidora>direccion);
        printf("%d\n",rec->datosDistribuidora->idDistribuidora);
        printf("\n");

        mostrarDesplazamiento(rec->datosDistribuidora->Desplazamiento, rec->datosDistribuidora->pLibreDistribuidora);

    }
}

void ModificarDistribuidora(struct NodoDistribuidora **distribuidora, int NuevaId)
{
    (*distribuidora)->idDistribuidora = NuevaId;
    return;
}

// Funciones arreglo Desplazamiento con pLibre

void AgregarDesplazamiento(struct Desplazamiento ***desplazamientos, struct Desplazamiento *nuevo, int *pLibreDesplazamiento)
{
    (*desplazamientos)[*pLibreDesplazamiento] = nuevo;
    (*pLibreDesplazamiento)++;
    return;
}

struct Desplazamiento *BuscarDesplazamiento(struct Desplazamiento **desplazamientos, int id, int pLibreDesplazamiento)
{
    int i;

    for(i=0; i<pLibreDesplazamiento; i++)
    {
        if(desplazamientos[i]->idImportadora == id)
        {
            return desplazamientos[i];
        }
    }
    return NULL; //id de importadora no encontrada
}

void EliminarDesplazamiento(struct Desplazamiento ***desplazamientos, int *pLibreDesplazamiento, int id)
{
    int i;

    for(i=0; i<pLibreDesplazamiento; i++)
    {
        if((*desplazamientos)[i]->idImportadora == id) //si se encuentra la id
        {
            (*desplazamientos)[i] = NULL;
            (*desplazamientos)[i]=(*desplazamientos)[(*pLibreDesplazamiento)-1];
            (*desplazamientos)[(*pLibreDesplazamiento)-1]=NULL;
            (*pLibreDesplazamiento)--;
            return;
        }
    }
}

void mostrarDesplazamiento(struct Desplazamiento **desplazamientosTotales, int pLibreDesplazamiento){
    int i;

    for(i = 0; i < pLibreDesplazamiento; i++){
        printf("%d\n", desplazamientosTotales[i]->TiempoViaje);
        printf("%d\n", desplazamientosTotales[i]->idImportadora);
        printf("\n");
    }
}

void ModificarDesplazamiento(struct Desplazamiento **desplazamientos, int NuevaId)
{
    (*desplazamientos)->idImportadora = NuevaId;
    return;
}

// Funciones de arbol binario de Clientes (abb)

void AgregarCliente(struct NodoCliente **abbclientes, struct Cliente *nuevo)
{
    if((*abbclientes) == NULL)
    {
        (*abbclientes) = (struct NodoCliente *)malloc(sizeof(struct NodoCliente));
        (*abbclientes)->datosCliente = nuevo;
        (*abbclientes)->der = (*abbclientes)->izq = NULL;
        return;
    }
    else
    {
        if((*abbclientes)->datosCliente != nuevo)  //pregunta si ya existe
        {
            if((*abbclientes)->datosCliente->IdCliente > nuevo->IdCliente)
                AgregarCliente(&((*abbclientes)->izq),nuevo);
            else
                AgregarCliente(&((*abbclientes)->der),nuevo);
        }
    }
}

struct Cliente *BuscarCliente(struct NodoCliente *AbbClientes, int id)
{
    if(AbbClientes != NULL)
    {
        if (AbbClientes->datosCliente->IdCliente > id)
            BuscarCliente(AbbClientes->izq, id);
        else
        if (AbbClientes->datosCliente->IdCliente < id)
            BuscarCliente(AbbClientes->der, id);

        if(AbbClientes->datosCliente->IdCliente == id)
            return AbbClientes->datosCliente;

    }

    return NULL; //no se encontró al cliente
}

void EliminarCliente (struct NodoCliente **abbClientes, int idClienteEliminar)
{
    struct Cliente *aux = NULL;

    if((*abbClientes) == NULL)
        return;
    if((*abbClientes)->datosCliente->IdCliente < idClienteEliminar)
        EliminarCliente(&(*abbClientes)->der, idClienteEliminar);
    else
    {
        if ((*abbClientes)->datosCliente->IdCliente > idClienteEliminar)
            EliminarCliente(&(*abbClientes)->izq, idClienteEliminar);
        else
        {
            if ((*abbClientes)->datosCliente->IdCliente == idClienteEliminar)
            {
                aux = (*abbClientes)->datosCliente;
                if((*abbClientes)->izq == NULL)
                    (*abbClientes) = (*abbClientes)->der;
                else
                {
                    if ((*abbClientes)->der == NULL)
                        (*abbClientes) = (*abbClientes)->izq;
                    else
                        Reemplazar(&(*abbClientes)->izq, &aux);
                }

                free(aux);
            }
        }
    }

}

void mostrarClientes(struct NodoCliente *abbClientes){

    if(abbClientes != NULL)
    {
        printf("%s\n",abbClientes->datosCliente->nombre);
        printf("%s\n",abbClientes->datosCliente->rut);
        printf("%d\n",abbClientes->datosCliente->IdCliente);
        mostrarCompras(abbClientes->datosCliente->Headcompras);// llamar a funcion que muestra compras

        mostrarClientes(abbClientes->izq);
        mostrarClientes(abbClientes->der);
    }
}

void ModificarCliente(struct Cliente **cliente, int NuevaId)
{
    (*cliente)->IdCliente = NuevaId;
    return;
}

// Funciones lista simplemente enlazada NodoCompras

void AgregarCompra(struct NodoCompra **compras, struct Compra *nueva)
{

    if((*compras) == NULL)
    {
        (*compras) = (struct NodoCompra *)malloc(sizeof(struct NodoCompra));
        (*compras)->datosCompra = nueva;
        (*compras)->sig = NULL;
        return;
    }
    struct NodoCompra *rec = *compras;

    while(rec != NULL)
    {
        if(rec->sig == NULL)
        {
            rec->sig->datosCompra = nueva;
            rec->sig = NULL;
            return;
        }

        rec=rec->sig;
    }
}

struct Compra *BuscarCompra(struct NodoCompra *comprasCliente, int id)
{
    struct NodoCompra *rec = comprasCliente;

    while(rec != NULL)
    {
        if(rec->datosCompra->idCompra == id)
            return rec->datosCompra;
        rec=rec->sig;
    }

    return NULL;
}

void EliminarCompra(struct NodoCompra **compra, int id)
{


    if ((*compra)->datosCompra->idCompra == id)
    {
        (*compra)->datosCompra = NULL;
        (*compra) = (*compra)->sig;
        return;
    }
    struct NodoCompra *rec = *compra;
    while(rec != NULL)
    {
        if(rec->sig->datosCompra->idCompra == id && rec->sig->sig == NULL)
        {
            rec->sig = NULL;
            return;
        }

        if(rec->sig->datosCompra->idCompra == id)
        {
            rec->sig = rec->sig->sig;
            return;
        }

        rec=rec->sig;
    }
}

void mostrarCompras(struct NodoCompra *compras)
{
    struct NodoCompra *rec=compras;

    while(rec!=NULL)
    {
        printf("%s\n",rec->datosCompra->fechaCompra);
        printf("%d\n",rec->datosCompra->pLibreProducto);
        printf("%d\n",rec->datosCompra->idCompra);
        printf("%d\n",rec->datosCompra->totalCompra);
        mostrarProductos(rec->datosCompra->productosComprados,rec->datosCompra->pLibreProducto);
        rec=rec->sig;

    }
}

void ModificarCompra(struct Compra **compra, int NuevaId)
{
    (*compra)->idCompra = NuevaId;
    return;
}

// Funciones arreglo Productos con pLibre

void AgregarProducto(struct Producto ***productos, struct Producto *nuevo, int *pLibreProducto)
{
    (*productos)[*pLibreProducto] = nuevo;
    (*pLibreProducto)++;
    return;
}

struct Producto *BuscarProducto(struct Producto **productos, int id, int pLibreProducto)
{
    int i;

    for(i = 0; i < pLibreProducto; i++)
    {
        if(productos[i]->id == id)
        {
            return productos[i];
        }
    }
    return NULL; //producto no encontrado
}

void EliminarProductoDeUnaCompraDeUnCliente(struct Producto ***productos, int *pLibreProductos, int idProducto)
{
    int i;

    for(i=0; i<pLibreProductos; i++)
    {
        if((*productos)[i]->id == idProducto)
        {
            (*productos)[i] = NULL;
            (*productos)[i]=(*productos)[(*pLibreProductos)-1];
            (*productos)[(*pLibreProductos)-1]=NULL;
            (*pLibreProductos)--;
            return;
        }
    }
}

void mostrarProductos(struct  Producto **productosDisponibles, int pLibreProducto){
    int i;

    for(i=0; i<pLibreProducto; i++){
        printf("%s\n", productosDisponibles[i]->nombre);
        printf("%d\n", productosDisponibles[i]->precio);
        printf("%d\n", productosDisponibles[i]->id);
    }
}

void ModificarProducto(struct Producto **producto, int NuevaId)
{
    (*producto)->id = NuevaId;
    return;
}

// CLIENTE QUE MAS GASTA EN SUS PRODUCTOS

int CalcularCompraCliente(struct NodoCompra *compras)
{
    int suma = 0;
    struct NodoCompra *rec = compras;

    while(rec != NULL)
    {
        suma += rec->datosCompra->totalCompra;
        rec = rec->sig;
    }
    return suma;
}

struct Cliente *clienteMayorGasto(struct NodoCliente *abbClientes)
{
    struct Cliente *mayor = NULL;

    if(abbClientes != NULL)
    {
        if (mayor == NULL || CalcularCompraCliente(abbClientes->datosCliente->Headcompras) > CalcularCompraCliente(mayor->Headcompras))
            mayor = abbClientes->datosCliente;

        clienteMayorGasto(abbClientes->izq);
        clienteMayorGasto(abbClientes->der);

    }
    return mayor;
}

// DISTRIBUIDORA CON MAS VENTAS

int ContarProductosVendidosACliente(struct NodoCompra *compras, int idDistribuidora)
{
    int total=0;
    struct NodoCompra *rec = compras;

    while(rec!=NULL)
    {
        if(rec->datosCompra->idDistribuidora == idDistribuidora)
            total+=rec->datosCompra->pLibreProducto-1;
        rec=rec->sig;
    }

    return total;
}

int ContarProductosVendidosAclientesTotal(struct NodoCliente *Abbclientes, int idDistribuidora)
{
    int total=0;

    if(Abbclientes != NULL)
    {
        total+= ContarProductosVendidosACliente(Abbclientes->datosCliente->Headcompras, idDistribuidora);
        ContarProductosVendidosAclientesTotal(Abbclientes->izq, idDistribuidora);
        ContarProductosVendidosAclientesTotal(Abbclientes->der,idDistribuidora);
    }

    return total;
}

struct Distribuidora *distribuidoraConMasVentas(struct NodoDistribuidora *distribuidora, struct NodoCliente *abb)
{
    struct  NodoDistribuidora *rec = distribuidora;
    struct Distribuidora *mayor = NULL;

    while(rec != NULL)
    {
        if (mayor == NULL || ContarProductosVendidosAclientesTotal(abb, rec->datosDistribuidora->idDistribuidora) >
                             ContarProductosVendidosAclientesTotal(abb, mayor->idDistribuidora))
            mayor = rec->datosDistribuidora;
        rec=rec->sig;
    }

    return mayor;
}

// ORDENAR PRODUCTOS POR ID

void OrdenarProductosPorId(struct Producto **productos, int pLibreProducto){

    int i,j;
    struct Producto *aux = NULL;
    for(i=0; i<pLibreProducto-1; i++)
        for(j=0; j<pLibreProducto-1; j++)
        {
            if(productos[j]->id > productos[j+1]->id)
            {
                aux = productos[j];
                productos[j] = productos[j+1];
                productos[j+1] = aux;
            }
        }
    return;
}

// MENÚ DE TEXTO

int main() {
    char opcion;
    int eleccion;
    int idCliente;
    int idCompra;
    int idProducto;
    int idDistribuidora;
    int idImportadora;
    int nuevaIdImportadora;
    int nuevaIdDistribuidora;
    int nuevaIdCliente;

    struct Derco *EMP = NULL;
    struct Distribuidora *nuevaDistribuidora = NULL;
    struct Importadora *nuevaImportadora = NULL;
    struct Producto *nuevoProducto = NULL;
    struct Cliente *nuevoCliente = NULL;
    struct Compra *nuevaCompra =NULL;

    printf("PRESIONE 'a' PARA AGREGAR ELEMENTOS\n");
    printf("PRESIONE 'e' PARA ELIMINAR ELEMENTOS\n");
    printf("PRESIONE 'b' PARA BUSCAR ELEMENTOS\n");
    printf("PRESIONE 'l' PARA LISTAR ELEMENTOS\n");
    printf("PRESIONE 'm' PARA MODIFICAR ELEMENTOS\n");
    printf("PRESIONE 'o' PARA REALIZAR OTRA ACCIÓN\n");


    scanf("%c", &opcion);
    switch(opcion)
    {
        case 'a':
            printf("PRESIONE '0' PARA AGREGAR UNA IMPORTADORA\n");
            printf("PRESIONE '1' PARA AGREGAR UNA DISTRIBUIDORA\n");
            printf("PRESIONE '2' PARA AGREGAR UN PRODUCTO A LA COMPRA DE UN CLIENTE\n");
            printf("PRESIONE '3' PARA AGREGAR UN CLIENTE\n");
            printf("PRESIONE '4' PARA AGREGAR UNA DISTRIBUIDORA A UNA IMPORTADORA\n");
            printf("PRESIONE '5' PARA AGREGAR UNA COMPRA A UN CLIENTE\n");
            scanf("%d",&eleccion);

            switch (eleccion)
            {
                case '0':

                    if (BuscarImportadora(EMP->Importadora, nuevaImportadora->idImportadora) == NULL)
                    {
                        AgregarImportadora(EMP->Importadora,nuevaImportadora);
                        printf("LA IMPORTADORA SE AGREGO CON EXITO");
                        break;
                    }
                    else
                    {
                        printf("LA IMPORTADORA YA EXISTE");
                        break;
                    }

                case '1':

                    if(BuscarDistribuidora(EMP->Distribuidora, nuevaDistribuidora->idDistribuidora,) == NULL)
                    {
                        AgregarDistribuidora(EMP->Distribuidora, nuevaDistribuidora);
                        printf("LA DISTRIBUIDORA SE AGREGO CORRECTAMENTE");
                        break;
                    }
                    else
                    {
                        printf("LA DISTRIBUIDORA YA EXISTE");
                        break;
                    }

                case '2':

                    printf("INGRESE EL ID DEL CLIENTE");
                    scanf("%d",&idCliente);
                    if(BuscarCliente(EMP->abbClientes,idCliente) != NULL) //cliente existe
                    {
                        printf("INGRESE EL ID DE LA COMPRA");
                        scanf("%d",&idCompra);

                        if(BuscarCompra(BuscarCliente(EMP->abbClientes,idCliente)->Headcompras,idCompra) != NULL) //compra existe
                        {
                            printf("INGRESE EL ID DEL PRODUCTO");
                            scanf("%d",&idProducto);
                            if(BuscarProducto(BuscarCompra(BuscarCliente(EMP->abbClientes,idCliente)->Headcompras,idCompra)->productosComprados,idProducto,BuscarCompra(BuscarCliente(EMP->abbClientes,idCliente)->Headcompras,idCompra)->pLibreProducto) == NULL) //producto no existe, se puede agregar
                            {
                                AgergarProducto(BuscarCompra(BuscarCliente(EMP->abbClientes,idCliente)->Headcompras,idCompra)->productosComprados,nuevoProducto,BuscarCompra(BuscarCliente(EMP->abbClientes,idCliente)->Headcompras,idCompra)->pLibreProducto);
                                printf("EL PRODUCTO SE AGREGO CON EXITO");
                                break;
                            }
                            printf("EL PRODUCTO YA EXISTE EN LA COMPRA DEL CLIENTE");
                            break;
                        }
                        printf("LA COMPRA NO EXISTE, INGRESE UN ID DE COMPRA VALIDO");
                        break;
                    }
                    printf("EL CLIENTE NO EXISTE, INGRESE UN ID DE CIELNTE VALIDO");
                    break;

                case '3':
                    if(BuscarCliente(EMP->abbClientes,nuevoCliente->IdCliente) == NULL) //cliente no existe, se puede agregar
                    {
                        AgregarCliente(EMP->abbClientes,nuevoCliente);
                        printf("CLIENTE SE HA AGREGADO CON EXITO");
                        break;
                    }
                    else
                    {
                        printf("EL CLIENTE YA EXISTE");
                        break;
                    }
                case '4':
                    printf("INGRESE EL ID DE LA IMPORTADORA");
                    scanf("%d",&idImportadora);

                    if(BuscarImportadora(EMP->Importadora, idImportadora) != NULL) //planta productiva existe
                    {
                        if (BuscarImportadora(EMP->Importadora, idImportadora)->pLibreDistribuidora < MaxDistribuidoras &&
                            BuscarArrDistribuidora(BuscarImportadora(EMP->Importadora, idImportadora)->Plantas,BuscarImportadora(EMP->Importadora, idImportadora)->pLibreDistribuidora, nuevaDistribuidora->idPlanta) == NULL) //hay espacio para agregar y la planta de distribucion no existe en el arreglo
                        {
                            AgregarArrDistribuidora(BuscarImportadora(EMP->Importadora, idImportadora)->Plantas,nuevaDistribuidora,
                                                    BuscarImportadora(EMP->Importadora,idImportadora)->pLibreDistribuidora);
                            printf("LA DISTRIBUIDORA SE HA AGREGADO CORRECTAMENTE A LA IMPORTADORA");
                            break;
                        }
                        else
                        {
                            printf("LA DISTRIBUIDORA NO SE PUDO AGREGAR");
                            break;
                        }

                    }
                    else
                    {
                        printf("LA IMPORTADORA NO EXISTE, INGRESA UN ID VALIDO");
                        break;
                    }
                case '5':
                    printf("INGRESA EL ID DEL CLIENTE");
                    scanf("%d",&idCliente);

                    if(BuscarCliente(EMP->abbClientes,idCliente) != NULL && BuscarCompra(BuscarCliente(EMP->abbClientes, idCliente)->Headcompras,nuevaCompra->idCompra)==NULL) //cliente existe y compra no existe asi que se puede agregar
                    {
                        AgregarCompra(BuscarCliente(EMP->abbClientes, idCliente)->Headcompras,nuevaCompra);
                        printf("LA COMPRA SE HA AGREGADO CORRECTAMENTE");
                        break;
                    }
                    else
                    {
                        printf("LA COMPRA NO HA PODIDO SER AGREGADA, POR QUE INGRESASTE UN ID INVALIDO O LA COMPRA YA EXISTE");
                        break;
                    }
                default:
                    break;
            }
        case 'e':

            printf("PRESIONE '0' PARA ELIMINAR UNA IMPORTADORA\n");
            printf("PRESIONE '1' PARA ELIMINAR UNA DISTRIBUIDORA\n");
            printf("PRESIONE '2' PARA ELIMINAR UN PRODUCTO A LA COMPRA DE UN CLIENTE\n");
            printf("PRESIONE '3' PARA ELIMINAR UN CLIENTE\n");
            printf("PRESIONE '4' PARA ELIMINAR UNA DISTRIBUIDORA DE UNA IMPORTADORA\n");
            printf("PRESIONE '5' PARA ELIMINAR UNA COMPRA DE UN CLIENTE\n");
            scanf("%d",&eleccion);

            switch (eleccion)
            {
                case '0' :
                    printf("INGRESE EL ID DE LA IMPORTADORA QUE DESEA ELIMINAR");
                    scanf("%d",&idImportadora);

                    if(BuscarImportadora(EMP->Importadora, idImportadora) != NULL)  //planta existe, se puede eliminar
                    {
                        EliminarImportadora(EMP->Importadora,idImportadora);
                        printf("IMPORTADORA SE HA ELIMINADO CORRECTAMENTE");
                        break;
                    }
                    else{
                        printf("LA IMPORTADORA NO EXISTE, INGRESE UN ID VALIDO");
                        break;
                    }
                case '1' :
                    printf("INGRESE EL ID DE LA DISTRIBUIDORA QUE DESEA ELIMINAR");
                    scanf("%d",&idDistribuidora);

                    if(BuscarDistribuidora(EMP->Distribuidora,idDistribuidora) != NULL)
                    {
                        EliminardDistribuidora(EMP->Distribuidora, idDistribuidora);
                        printf("DISTRIBUIDORA SE HA ELIMINADO CORRECTAMENTE");
                        break;
                    }
                    else{
                        printf("LA DISTRIBUIDORA NO EXISTE, INGRESE UN ID VALIDO");
                        break;
                    }
                case'2':
                    printf("INGRESE EL ID DEL CLIENTE");
                    scanf("%d",&idCliente);

                    if(BuscarCliente(EMP->abbClientes,idCliente) != NULL)   //cliente existe
                    {
                        printf("INGRESE EL ID DE LA COMPRA");
                        scanf("%d",&idCompra);
                        if(BuscarCompra(BuscarCliente(EMP->abbClientes,idCliente)->Headcompras,idCompra) != NULL) //compra existe
                        {
                            printf("INGRESE EL ID DEL PRODUCTO");
                            scanf("%d",&idProducto);
                            if(BuscarProducto(BuscarCompra(BuscarCliente(EMP->abbClientes,idCliente)->Headcompras,idCliente)->productosComprados,idProducto,BuscarCompra(BuscarCliente(EMP->abbClientes,idCliente)->Headcompras,idCliente)->pLibreProducto)!=NULL) //PRODUCTO EXISTE
                            {
                                EliminarProductoDeUnaCompraDeUnCliente(BuscarCompra(BuscarCliente(EMP->abbClientes,idCliente)->Headcompras,idCliente)->productosComprados,BuscarCompra(BuscarCliente(EMP->abbClientes,idCliente)->Headcompras,idCliente)->pLibreProducto,idProducto);
                                printf("EL PRODUCTO SE HA ELIMINADO CORRECTAMENTE DE LA COMPRA DEL CLIENTE");
                                break;
                            }
                            else
                            {
                                printf("EL PRODUCTO NO EXISTE EN LA COMPRA DEL CLIENTE");
                                break;
                            }

                        }
                        else
                        {
                            printf("LA COMPRA NO EXISTE");
                            break;
                        }
                    }
                    else
                    {
                        printf("CLIENTE NO EXISTE");
                        break;
                    }
                case '3':
                    printf("INGRESA EL ID DEL CLIENTE");
                    scanf("%d",&idCliente);
                    if(BuscarCliente(EMP->abbClientes,idCliente) != NULL) //CLIENTE EXISTE
                    {
                        EliminarCliente(EMP->abbClientes,idCliente);
                        printf("CLIENTE ELIMINADO CON EXITO");
                        break;
                    }
                    else
                    {
                        printf("CLIENTE NO EXISTE, INGRESA ID VALIDO");
                        break;
                    }
                case '4': //ELIMINAR UNA DISTRIBUIDORA DE UNA IMPORTADORA
                    printf("INGRESA EL ID DE LA IMPORTADORA Y DE LA DISTRIBUIDORA ");
                    scanf("%d %d",&idImportadora,&idDistribuidora);
                    if(BuscarImportadora(EMP->Importadora,idImportadora) != NULL && BuscarArrDistribuidora(BuscarImportadora(EMP->Importadora,idImportadora)->Plantas,BuscarImportadora(EMP->Importadora,idImportadora)->pLibreDistribuidora,idDistribuidora) != NULL)
                    {
                        EliminarArrDistribuidora(BuscarImportadora(EMP->Importadora,idImportadora)->Plantas,BuscarImportadora(EMP->Importadora,idImportadora)->pLibreDistribuidora, idDistribuidora);
                        printf("LA DISTRIBUIDORA SE HA ELIMINADO CORRECTAMENTE DE LA IMPORTADORA");
                        break;
                    } else{
                        printf("NO SE HA PODIDO ELIMINAR LA DISTRIBUIDORA");
                    }
                case'5': //ELIMINAR UNA COMPRA DE UN CLIENTE
                    printf("INGRESA EL ID DEL CLIENTE Y EL ID DE LA COMPRA A ELIMINAR");
                    scanf("%d %d",&idCliente,&idCompra);
                    if(BuscarCliente(EMP->abbClientes,idCliente) != NULL && BuscarCompra(BuscarCliente(EMP->abbClientes,idCliente)->Headcompras,idCompra) != NULL) //ambos existen
                    {
                        EliminarCompra(BuscarCliente(EMP->abbClientes,idCliente)->Headcompras,idCompra);
                        printf("LA COMPRA SE HA ELIMINADO CORRECTAMENTE DEL CLIENTE");
                        break;
                    }
                    else{
                        printf("LA COMPRA NO SE PUDO ELIMINAR");
                        break;
                    }
                default:
                    break;
            }
        case 'b':

            printf("PRESIONE '0' PARA BUSCAR UNA IMPORTADORA\n");
            printf("PRESIONE '1' PARA BUSCAR UNA DISTRIBUIDORA\n");
            printf("PRESIONE '2' PARA BUSCAR UN PRODUCTO DE LA COMPRA DE UN CLIENTE\n");
            printf("PRESIONE '3' PARA BUSCAR UN CLIENTE\n");
            printf("PRESIONE '4' PARA BUSCAR UNA DISTRIBUIDORA DE UNA IMPORTADORA\n");
            printf("PRESIONE '5' PARA BUSCAR UNA COMPRA DE UN CLIENTE\n");
            scanf("%d",&eleccion);

            switch (eleccion)
            {
                case'0' :
                    printf("INGRESA EL ID DE LA IMPORTADORA QUE DESEAS BUSCAR");
                    scanf("&d",&idImportadora);
                    if(BuscarImportadora(EMP->Importadora,idImportadora) != NULL)
                    {
                        printf("IMPORTADORA ENCONTRADA");
                        break;
                    }
                    else
                    {
                        printf("IMPORTADORA NO ENCONTRADA");
                        break;
                    }
                case'1' : //PARA BUSCAR UNA DISTRIBUIDORA
                    printf("INGRESA EL ID DE LA DISTRIBUIDORA");
                    scanf("%d",&idDistribuidora);
                    if(BuscarDistribuidora(EMP->Distribuidora,idDistribuidora) != NULL)
                    {
                        printf("DISTRIBUIDORA ENCONTRADA");
                        break;
                    }
                    else
                    {
                        printf("DISTRIBUIDORA NO ENCONTRADA");
                        break;
                    }
                case'2' :  //PARA BUSCAR UN PRODUCTO DE LA COMPRA DE UN CLIENTE
                    printf("INGRESA ID DEL CLIENTE, ID DE LA COMPRA Y EL ID DEL PRODUCTO");
                    scanf("%d %d %d",&idCliente,&idCompra,&idProducto);
                    if(BuscarCliente(EMP->abbClientes,idCliente) != NULL && BuscarCompra(BuscarCliente(EMP->abbClientes,idCliente)->Headcompras,idCompra) != NULL &&
                       BuscarProducto(BuscarCompra(BuscarCliente(EMP->abbClientes,idCliente)->Headcompras,idCompra)->productosComprados,idProducto,BuscarCompra(BuscarCliente(EMP->abbClientes,idCliente)->Headcompras,idCompra)->pLibreProducto) != NULL)
                    {
                        EliminarProductoDeUnaCompraDeUnCliente(BuscarCompra(BuscarCliente(EMP->abbClientes,idCliente)->Headcompras,idCompra)->productosComprados,BuscarCompra(BuscarCliente(EMP->abbClientes,idCliente)->Headcompras,idCompra)->pLibreProducto,idProducto);
                        printf("PRODUCTO ELIMINADO CON EXITO");
                        break;
                    }
                    else{
                        printf("NO SE PUDO ELIMINAR EL PRODUCTO");
                        break;
                    }
                case '3':    //PARA BUSCAR UN CLIENTE
                    printf("INGRESA LA ID DEL CLIENTE");
                    scanf("%d",&idCliente);
                    if(BuscarCliente(EMP->abbClientes,idCliente)!=NULL)
                    {
                        printf("CLIENTE ENCONTRADO CON EXITO");
                        break;
                    }
                    else
                    {
                        printf("CLIENTE NO ENCONTRADO");
                        break;
                    }
                case'4' :   //PARA BUSCAR UNA DISTRIBUIDORA DE UNA IMPORTADORA
                    printf("INGRESA ID DE LA IMPORTADORA Y DE LA DISTRIBUIDORA");
                    scanf("%d %d",&idImportadora,&idDistribuidora);

                    if(BuscarImportadora(EMP->Importadora,idImportadora) != NULL &&
                       BuscarArrDistribuidora(BuscarImportadora(EMP->Importadora,idImportadora)->Plantas,BuscarImportadora(EMP->Importadora,idImportadora)->pLibreDistribuidora,idDistribuidora) != NULL)
                    {
                        printf("DISTRIBUIDORA ENCONTRADA");
                        break;
                    }
                    else{
                        printf("DISTRIBUIDORA NO ENCONTRADA");
                        break;
                    }
                case '5':    //BUSCAR UNA COMPRA DE UN CLIENTE
                    printf("INGRESA ID DEL CLIENTE Y DE LA COMPRA");
                    scanf("%d %d",&idCliente,&idCompra );
                    if(BuscarCliente(EMP->abbClientes,idCliente)!=NULL && BuscarCompra(BuscarCliente(EMP->abbClientes,idCliente)->Headcompras,idCompra) != NULL)
                    {
                        printf("COMPRA ENCONTRADA");
                        break;
                    }
                    else{
                        printf("COMPRA NO ENCONTRADA");
                        break;
                    }
                default:
                    break;
            }

        case'm':

            printf("PRESIONE '0' PARA MODIFICAR LA ID DE UNA IMPORTADORA\n");
            printf("PRESIONE '1' PARA MODIFICAR LA ID DE UNA DISTRIBUIDORA\n");
            printf("PRESIONE '2' PARA MODIFICAR LA ID DE UN PRODUCTO DE LA COMPRA DE UN CLIENTE\n");
            printf("PRESIONE '3' PARA MODIFICAR LA ID DE UN CLIENTE\n");
            printf("PRESIONE '4' PARA MODIFICAR LA ID DE UNA DISTRIBUIDORA DE UNA IMPORTADORA\n");
            printf("PRESIONE '5' PARA MODIFICAR LA ID DE LA COMPRA DE UN CLIENTE\n");

            scanf("%d",&eleccion);

            switch (eleccion)
            {
                case'0':
                    printf("INGRESA LA ID DE LA IMPORTADORA Y LA NUEVA ID QUE TENDRA");
                    scanf("%d %d",&idImportadora,&nuevaIdImportadora);
                    if(BuscarImportadora(EMP->Importadora,idImportadora) !=NULL && BuscarImportadora(EMP->Importadora,nuevaIdImportadora) == NULL)
                    {
                        ModificarImportadora(BuscarImportadora(EMP->Importadora,idImportadora),nuevaIdImportadora);
                        printf("LA ID HA SIDO CAMBIADA CORRECTAMENTE");
                        break;
                    }
                    else
                    {
                        printf("LA ID NO SE HA PODIDO MODIFICAR");
                        break;
                    }
                case '1': //PARA MODIFICAR LA ID DE UNA DISTRIBUIDORA
                    printf("INGRESA LA ID DE LA DISTRIBUIDORA Y LA NUEVA ID QUE TENDRA");
                    scanf("%d %d",&idDistribuidora,nuevaIdDistribuidora);
                    if(BuscarDistribuidora(EMP->Distribuidora,idDistribuidora) != NULL &&
                       BuscarDistribuidora(EMP->Distribuidora,nuevaIdDistribuidora) == NULL)
                    {
                        ModificarDistribuidora(BuscarDistribuidora(EMP->Distribuidora,idDistribuidora),nuevaIdDistribuidora);
                        printf("LA ID HA SIDO CAMBIADA CON EXITO");
                        break;
                    }
                    else{
                        printf("LA ID NO SE HA PODIDO CAMBIAR");
                        break;
                    }
                case '2': //PARA MODIFICAR LA ID DE UN PRODUCTO DE LA COMPRA DE UN CLIENTE
                    printf("INGRESA EL ID DEL CLIENTE, DE LA COMPRA, DEL PRODUCTO Y LA NUEVA ID");
                    scanf("%d %d %d %d",&idCliente,&idCompra,&idProducto,&nuevoProducto->id);
                    if(BuscarCliente(EMP->abbClientes,idCliente) != NULL && BuscarCompra(BuscarCliente(EMP->abbClientes,idCliente)->Headcompras,idCompra) != NULL &&
                       BuscarProducto(BuscarCompra(BuscarCliente(EMP->abbClientes,idCliente)->Headcompras,idCompra)->productosComprados,idProducto,BuscarCompra(BuscarCliente(EMP->abbClientes,idCliente)->Headcompras,idCompra)->pLibreProducto) != NULL && BuscarProducto(BuscarCompra(BuscarCliente(EMP->abbClientes,idCliente)->Headcompras,idCompra)->productosComprados,nuevoProducto->id,BuscarCompra(BuscarCliente(EMP->abbClientes,idCliente)->Headcompras,idCompra)->pLibreProducto) == NULL)
                    {
                        ModificarProducto(BuscarCompra(BuscarCliente(EMP->abbClientes,idCliente)->Headcompras,idCompra)->productosComprados,nuevoProducto->id);
                        printf("ID DE PRODUCTO MODIFICADO CON EXITO");
                        break;
                    }
                    else{
                        printf("ID DE PRODUCTO NO SE PUDO MODIFICAR");
                        break;
                    }
                case '3': //PARA MODIFICAR LA ID DE UN CLIENTE
                    printf("INGRESA EL ID DEL CLIENTE Y LA NUEVA ID");
                    scanf("%d %d",&idCliente,&nuevaIdCliente);
                    if(BuscarCliente(EMP->abbClientes,idCliente) != NULL && BuscarCliente(EMP->abbClientes,nuevaIdCliente) == NULL)
                    {
                        ModificarCliente(BuscarCliente(EMP->abbClientes,idCliente),nuevaIdCliente);
                        printf("ID DE CLIENTE HA SIDO CAMBIADA CON EXITO");
                        break;
                    }else
                    {
                        printf("EL ID NO SE HA PODIDO CAMBIAR");
                        break;
                    }
                case '4': //PARA MODIFICAR LA ID DE UNA DISTRIBUIDORA DE UNA IMPORTADORA
                    printf("INGRESA EL ID DE LA IMPORTADORA, DE LA DISTRIBUIDORA A MODIFICAR Y LA NUEVA");
                    scanf("%d %d %d",&idImportadora,&idDistribuidora,&nuevaIdDistribuidora);
                    if(BuscarImportadora(EMP->Importadora,idImportadora) != NULL && BuscarArrDistribuidora(BuscarImportadora(EMP->Importadora,idImportadora)->Plantas,
                                                                                                           BuscarImportadora(EMP->Importadora,idImportadora)->pLibreDistribuidora,idDistribuidora) != NULL && BuscarArrDistribuidora(BuscarImportadora(EMP->Importadora,idImportadora)->Plantas,
                                                                                                                                                                                                                                     BuscarImportadora(EMP->Importadora,idImportadora)->pLibreDistribuidora,nuevaIdDistribuidora )==NULL)
                    {
                        ModificarDistribuidora(BuscarArrDistribuidora(BuscarImportadora(EMP->Importadora,idImportadora)->Plantas,BuscarImportadora(EMP->Importadora,idImportadora)->pLibreDistribuidora,idDistribuidora)->idPlanta,nuevaIdDistribuidora);
                        printf("ID DE LA DISTRIBUIDORA HA SIDO CAMBIADO");
                        break;
                    }
                    else{
                        printf("NO SE HA PODIDO MODIFICAR EL ID DE LA DISTRIBUIDORA");
                        break;
                    }
                case '5': //MODIFICAR LA ID DE LA COMPRA DE UN CLIENTE
                    printf("INGRESA EL ID DEL CLIENTE, DE LA COMPRA Y EL NUEVO ID");
                    scanf("%d %d %d",&idCliente,&idCompra,&nuevaCompra->idCompra);
                    if(BuscarCliente(EMP->abbClientes,idCliente) != NULL && BuscarCompra(BuscarCliente(EMP->abbClientes,idCliente)->Headcompras,idCompra) !=NULL && BuscarCompra(BuscarCliente(EMP->abbClientes,idCliente)->Headcompras,nuevaCompra->idCompra) != NULL)
                    {
                        ModificarCompra(BuscarCompra(BuscarCliente(EMP->abbClientes,idCliente)->Headcompras,idCompra),nuevaCompra->idCompra);
                        printf("ID DE COMPRA SE HA MODIFICADO CON EXITO");
                        break;
                    }
                    else
                    {
                        printf("LA COMPRA NO SE HA PODIDO MODIFICAR");
                        break;
                    }


                default:
                    break;
            }

        case'l':

            printf("PRESIONE '0' PARA LISTAR LAS IMPORTADORAS\n");
            printf("PRESIONE '1' PARA LISTAR LAS DISTRIBUIDORAS\n");
            printf("PRESIONE '2' PARA LISTAR LOS CLIENTES\n");
            scanf("%d",&eleccion);

            switch (eleccion)
            {
                case '0':
                    mostrarImportadoras(EMP->Importadora);
                    break;
                case'1':
                    mostrarDistribuidoras(EMP->Distribuidora);
                    break;
                case '2':
                    mostrarClientes(EMP->abbClientes);
                    break;
                default:
                    break;
            }

        case 'o':
            printf("PRESIONE '0' PARA BUSCAR CLIENTE QUE MAS GASTA EN SUS PRODUCTOS\n");
            printf("PRESIONE '1' PARA BUSCAR LA DISTRIBUIDORA CON MAS VENTAS\n");
            printf("PRESIONE '2' PARA ORDENAR LOS PRODUCTOS DE UNA COMPRA DE UN CLIENTE POR ID\n");
            scanf("%d",&eleccion);

            switch (eleccion)
            {
                case '0':
                    if(clienteMayorGasto(EMP->abbClientes) !=NULL)
                    {
                        printf("EL ID DEL CLIENTE QUE MAS GASTA EN SUS PRODUCTOS ES %d",clienteMayorGasto(EMP->abbClientes)->IdCliente);
                        break;
                    }
                    else{
                        printf("NO EXISTE");
                        break;
                    }

                case '1':
                    if(distribuidoraConMasVentas(EMP->Distribuidora,EMP->abbClientes)!=NULL)
                    {
                        printf("EL ID DE LA DISTRIBUIDORA CON MAYOR VENTAS ES %d",distribuidoraConMasVentas(EMP->Distribuidora,EMP->abbClientes)->idPlanta);
                        break;
                    }
                    else{
                        printf("NO EXISTE");
                    }

                case '2':
                    printf("INGRESA EL ID DE CLIENTE Y EL ID DE LA COMPRA PARA ORDENAR LOS PRODUCTOS");
                    scanf("%d %d",&idCliente,&idCompra);
                    if(BuscarCliente(EMP->abbClientes,idCliente)!=NULL && BuscarCompra(BuscarCliente(EMP->abbClientes,idCliente)->Headcompras,idCompra) != NULL)
                    {
                        OrdenarProductosPorId(BuscarCompra(BuscarCliente(EMP->abbClientes,idCliente)->Headcompras,idCompra)->productosComprados,BuscarCompra(BuscarCliente(EMP->abbClientes,idCliente)->Headcompras,idCompra)->pLibreProducto);
                        printf("PRODUCTOS FUERON ORDENADOS");
                        break;
                    }
                    else{
                        printf("PRODUCTOS NO SE PUDIERON ORDENAR");
                        break;
                    }

                default:
                    break;
            }

        default:
            break;
    }


}
