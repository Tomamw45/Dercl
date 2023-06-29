#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define maxAutos 10000

struct Derco
{
    int id;
    struct NodoRegiones *regiones;
    struct NodoAuto *autos;
};


struct NodoRegiones
{
    struct Region *detalleregion;
    struct NodoRegiones *sig;
};

struct Region
{
    int numero;
    char *nombre;
    struct NodoSucursales *sucursales;
};


struct NodoSucursales
{
    struct Sucursal *detallesucursal;
    struct NodoSucursales *izq, *der;
};

struct Sucursal
{
    int id;
    char *nombre;
    char *direccion;
    struct Auto **autos;
};

struct NodoAuto
{
    struct Auto *detalleauto;
    struct NodoAuto *sig;
};

struct Auto
{
    int id;
    char *marca;
    char *modelo;
    int precio;
    int year;   
};

// FUNCIONES ARREGLO

int buscarVehiculo(int id, struct Auto **autos)
{
    int i;
    for(i = 0; i < maxAutos; i++)
    {
        if (autos[i] != NULL)
        {
            if(autos[i]->id == id)
            {
                return 1;
            }
        }  
    }
    return 0;
}


void mostrarVehiculos(struct Auto **autos, int id)
{
    int i;
    for(i = 0; i < maxAutos; i++)
    {
        if (autos[i] != NULL)
        {
            if(autos[i]->id == id)
            {
                printf("Marca: %s\n", autos[i]->marca);
                printf("Modelo: %s\n", autos[i]->modelo);
                printf("Año: %d\n", autos[i]->year);
                printf("Precio: %d\n", autos[i]->precio);
                
            }
        }  
    }
}


void EliminarVehiculo(struct Auto **autos, int id)
{
    int i;
    for(i = 0; i < maxAutos; i++)
    {
        if (autos[i] != NULL)
        {
            if(autos[i]->id == id)
            {
                autos[i] = NULL;
            }
        }  
    }
}


void modificarVehiculo(struct Auto **autos, int id, char *marca, char *modelo, int year, int precio)
{
    int i;
    for(i = 0; i < maxAutos; i++)
    {
        if (autos[i] != NULL)
        {
            if(autos[i]->id == id)
            {
                autos[i]->marca = marca;
                autos[i]->modelo = modelo;
                autos[i]->year = year;
                autos[i]->precio = precio;
            }
        }  
    }
}

struct Auto *crearNodoAuto()
{
    struct Auto *nuevo = (struct Auto *)malloc(sizeof(struct Auto));
    
    printf("Ingrese el id del auto: "); 
    scanf("%d", &nuevo->id);
    printf("Ingrese la marca del auto: ");
    scanf("%s", &nuevo->marca);
    printf("Ingrese el modelo del auto: ");
    scanf("%s", &nuevo->modelo);
    printf("Ingrese el año del auto: ");
    scanf("%d", &nuevo->year);
    printf("Ingrese el precio del auto: ");
    scanf("%d", &nuevo->precio);
    return nuevo;
}

void agregarVehiculo(struct Auto **autos,struct Auto * nuevo)
{
    int i;
    for(i = 0; i < maxAutos; i++)
    {
        if(buscarAuto(autos[i]->id, nuevo->id ) == 0)
        {
            if (autos[i] == NULL)
            {
                autos[i] = crearNodoAuto();
                return;
            }  
        }
        
    }
}

// FUNCIONES LISTA

int buscarRegion(struct NodoRegiones **head, int numero)
{
    struct NodoRegiones *rec = *head;
    while(rec != NULL)
    {
        if(rec->detalleregion->numero == numero)
        {
            return 1;
        }
        rec = rec->sig;
    }
    return 0;
}

struct NodoRegiones *crearNodoRegion()
{
    struct NodoRegiones *nuevo = (struct NodoRegiones *)malloc(sizeof(struct NodoRegiones));
    printf("INGRESE EL NUMERO DE LA REGION: ");
    scanf("%d", &nuevo->detalleregion->numero);
    printf("INGRESE EL NOMBRE DE LA REGION  : ");
    scanf("%s", &nuevo->detalleregion->nombre);
    nuevo->sig = NULL;
    return nuevo;
}

void agregarRegion(struct NodoRegiones **head)
{
    struct NodoRegiones *rec = *head;
    struct NodoRegiones *nuevo;
    while(rec != NULL)
    {
        if(buscarRegion(head, rec->detalleregion->numero) == 0)
        {
            if(rec->sig == NULL)
            {
                nuevo = crearNodoRegion();
                rec->sig = nuevo;
                return;
            }
            
        }
        
    }
}

void mostrarRegiones(struct NodoRegiones **head, int numero)
{
    struct NodoRegiones *rec = *head;
    while(rec != NULL)
    {
        if(rec->detalleregion->numero == numero)
        {
            printf("Numero: %d\n", rec->detalleregion->numero);
            printf("Nombre: %s\n", rec->detalleregion->nombre);
            return;
        }
        rec = rec->sig;
    }
}

void eliminarRegion(struct NodoRegiones **head, int numero)
{
    struct NodoRegiones *rec = *head;
    while(rec != NULL)
    {
        if(rec->sig->detalleregion->numero == numero)
        {
            rec->sig = rec->sig->sig;
            free(rec->sig);
            return;
        }
        rec = rec->sig;
    }

}

void modificarRegion(struct NodoRegiones **head, int numero, char *nombre)
{
    struct NodoRegiones *rec = *head;
    while(rec != NULL)
    {
        if(rec->detalleregion->numero == numero)
        {
            rec->detalleregion->nombre = nombre;
            return;
        }
        rec = rec->sig;
    }
}

// FUNCIONES ARBOL

int buscarSucursal(struct NodoSucursales *abb,int id)
{
    if (!abb || abb->detallesucursal->id == id)
    {
        return 1;
    }
    else
    {
        if (abb->detallesucursal->id > id)
        {
            return buscarSucursal(abb->izq, id);
        }
        else
        {
            return buscarSucursal(abb->der, id);
        }
    }
}


void mostrarSucursales(struct NodoSucursales *abb, int id)
{
    if (!abb)
    {
        return;
    }
    else
    {
        if (abb->detallesucursal->id == id)
        {
            printf("Id: %d\n", abb->detallesucursal->id);
            printf("Nombre: %s\n", abb->detallesucursal->nombre);
            printf("Direccion: %s\n", abb->detallesucursal->direccion);
            return;
        }
        else
        {
            if (abb->detallesucursal->id > id)
            {
                return mostrarSucursales(abb->izq, id);
            }
            else
            {
                return mostrarSucursales(abb->der, id);
            }
        }
    }
}

struct NodoSucursales *crearNodoSucursal()
{
    struct NodoSucursales *nuevo = (struct NodoSucursales *)malloc(sizeof(struct NodoSucursales));
    printf("INGRESE EL ID DE LA SUCURSAL: ");
    scanf("%d", &nuevo->detallesucursal->id);
    printf("INGRESE EL NOMBRE DE LA SUCURSAL: ");
    scanf("%s", &nuevo->detallesucursal->nombre);
    printf("INGRESE LA DIRECCION DE LA SUCURSAL: ");
    scanf("%s", &nuevo->detallesucursal->direccion);
    nuevo->izq = NULL;
    nuevo->der = NULL;
    return nuevo;
}

void agregarSucursal(struct NodoSucursales **abb, int id, char *nombre, char *direccion )
{
    if (!*abb)
    {
        (*abb) = crearNodoSucursal();
        return;
    }
    else
    {
        if ((*abb)->detallesucursal->id > id)
        {
            return agregarSucursal(&(*abb)->izq, id, nombre, direccion);
        }
        else
        {
            return agregarSucursal(&(*abb)->der, id, nombre, direccion);
        }
    }
}

void Reemplazar(struct NodoSucursales **abb, struct Sucursal **aux)
{
    if ((*abb)->der == NULL)
    {
        (*aux)->id = (*abb)->detallesucursal->id;
        (*aux)->autos = (*abb)->detallesucursal->autos;
        strcpy((*aux)->nombre,(*abb)->detallesucursal->nombre);
        strcpy((*aux)->direccion,(*abb)->detallesucursal->direccion);
    }
    else
        Reemplazar((*abb)->der, &(*aux));
}

void EliminarSucursal(struct NodoSucursales **abb, int idSucursalEliminar)
{
    struct Cliente *aux = NULL;

    if((*abb) == NULL)
        return;
    if((*abb)->detallesucursal->id < idSucursalEliminar)
        EliminarSucursal(&(*abb)->der, idSucursalEliminar);
    else
    {
        if ((*abb)->detallesucursal->id > idSucursalEliminar)
            EliminarSucursal(&(*abb)->izq, idSucursalEliminar);
        else
        {
            if ((*abb)->detallesucursal->id == idSucursalEliminar)
            {
                aux = (*abb)->detallesucursal;
                if((*abb)->izq == NULL)
                    (*abb) = (*abb)->der;
                else
                {
                    if ((*abb)->der == NULL)
                        (*abb) = (*abb)->izq;
                    else
                        Reemplazar(&(*abb)->izq, &aux);
                }

                free(aux);
            }
        }
    }

}

void ModificarSucursal(struct Sucursal **sucursal, int NuevaId)
{
    (*sucursal)->id = NuevaId;
    return;
}

// FUNCIONES LISTA CIRCULAR

void agregarAuto(struct NodoAuto** head, struct Auto *nueva) {
    struct NodoAuto* rec = *head;
    
    struct NodoAuto* Nuevoauto = (struct NodoAuto*)malloc(sizeof(struct NodoAuto));
    Nuevoauto -> detalleauto = nueva;
            
    if (*head == NULL) {
        *head = Nuevoauto;
        Nuevoauto->sig = Nuevoauto;
    } // si esta vacia, hacerla head
    else
    {
        while(rec->sig != *head){
            rec = rec->sig;
        }
        rec->sig = Nuevoauto;
        Nuevoauto->sig = *head; //agregarla al final de la lista
    }
}

struct Auto* BuscarAuto(struct NodoAuto *head, int id) {
    struct NodoAuto *rec = head;
    if (head == NULL) {
        return NULL;
    }

    do {
        struct Auto *datos = rec->detalleauto;

        do {
            if (datos->id == id) {
                return datos;
            }
            datos = datos->sig;
        }while (datos != datos->rec);

        rec = rec->sig;
    }while (rec != head);

    return NULL;
}

void EliminarAuto(struct NodoAuto **head, int id) {
    if (*head == NULL) {
        return; // si es el head
    }

    struct NodoAuto* rec = *head;
    struct NodoAuto* ant = NULL;

    while(rec->detalleauto->id != id)
    {
        ant = rec;
        rec = rec->sig;

        if (rec == *head) {
            return; /* si no lo encontramos en la lista */
        }
    }

    if (rec->detalleauto != NULL && rec->detalleauto->id == id) {
        struct NodoAuto* datosHead->detalleauto = rec->detalleauto;
        struct NodoAuto* datosAnt = datosHead;
        while (datosAnt->sig != datosHead){
            datosAnt = datosAnt->sig;
        }
        rec->detalleauto = datosHead->sig;
        datosAnt->sig = datosHead->sig;
    }
    if (ant != NULL){
        ant->sig = rec->sig;
    }

    else{
        *head = rec->sig;
    }
}

void mostrarAutos(struct NodoAuto *head)
{
    struct NodoAuto *rec = head;

    if (head == NULL)
    {
        return;
    }
    rec = head->sig;

    while(rec!=head)
    {
        printf("%d\n",rec->detalleauto->id);
        printf("%s\n",rec->detalleauto->marca);
        printf("%s\n",rec->detalleauto->modelo);
        printf("%d\n",rec->detalleauto->precio);
        printf("%d\n",rec->detalleauto->year);
        printf("\n");
        rec = rec->sig;
    }
}

void ModificarAuto(struct Auto ** Auto, int NuevaId)
{
    (*Auto)->id = NuevaId;
    return;
}

// FUNCION PROMEDIO SUCURSALES

int totalSucursales(struct NodoSucursales *abb)
{
    if (!abb)
    {
        return 0;
    }
    else
    {
        return 1 + totalSucursales(abb->izq) + totalSucursales(abb->der);
    }
}


float promedioSucursalesPorRegion(struct NodoRegiones *head, struct NodoSucursales *abb)
{
    int contador = 0;
    struct NodoRegiones *rec;
    float total = totalSucursales(abb);
    if head != NULL
    {
        rec = head;
        while(rec != NULL)
        {
            contador++;
            rec = rec->sig;
        }
    }
    return total/contador;
}

// ORDENAR VEHICULOS POR ID

void OrdenarVehiculosPorId(struct Autos **autos){

    int i,j;
    int temp = maxAutos;
    struct Autos *aux = NULL;
    for(i=0; i<temp-1; i++)
        for(j=0; j<temp-1; j++)
        {
            if(autos[j]->id > autos[j+1]->id)
            {
                aux = autos[j];
                autos[j] = autos[j+1];
                autos[j+1] = aux;
            }
        }
    return;
}

// SUCURSAL CON VEHÍCULOS MÁS CAROS

float promedioVehiculosSucursal(struct Auto ** autos){
  int cont = 0, suma = 0,i;
  float promedio = 0;

  for(i=0;i<maxAutos;i++)
  {
    if(autos[i] != NULL)
    {
      suma += autos[i]->precio;
      cont++;
    }
      
  }
  promedio = suma/cont;

  return promedio;
}

struct NodoSucursales sucursalVehiculosMasCarosRegion(struct NodoSucursales * abb)
{

  float promedioMasAlto = 0;
  struct NodoSucursales *nuevo = (struct NodoSucursales *)malloc(sizeof(struct NodoSucursales));
  
  if (!abb)
    {
        return 0;
    }
    else
    {
      if (promedioVehiculosSucursal(abb->detallesucursal->autos) > promedioMasAlto)
      {
        promedioMasAlto = promedioVehiculosSucursal(abb->detallesucursal->autos);
        nuevo -> detallesucursal = abb->detallesucursal;
      }
    
    sucursalVehiculosMasCarosRegion(abb->izq);
    sucursalVehiculosMasCarosRegion(abb->der);
    }

  return *nuevo;
}

int sucursalPromedioVehiculosMasCaros(struct NodoRegiones **head)
{
  float promedioMasAlto = 0;
  int idSucursalGanadora;
  struct NodoRegiones *rec = *head;

  while(rec != NULL)
  {
      if(sucursalPromedioVehiculosMasCaros(rec->detalleregion->sucursales) > promedioMasAlto)
      {
        promedioMasAlto = sucursalPromedioVehiculosMasCaros(rec->detalleregion->sucursales);
        idSucursalGanadora = rec->detalleregion->sucursales->detallesucursal->id;
      }
      rec = rec->sig;
  }
  return idSucursalGanadora;
}


// MENÚ DE TEXTO

int main()
{
    char opcion;
    int eleccion;
    int idAuto;
    int idSucursal;
    char nombreSucursal;
    char direccionSucursal;
  
    struct NodoSucursales *nuevaSucursal = NULL;
    struct NodoRegiones *nuevaRegion = NULL;
    struct NodoAuto *autoNuevo = NULL;
    struct Derco *EMP = NULL;

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
            printf("PRESIONE '0' PARA AGREGAR UN AUTO\n");
            printf("PRESIONE '1' PARA AGREGAR UNA REGION\n");
            printf("PRESIONE '2' PARA AGREGAR UNA SUCURSAL\n");
            printf("PRESIONE '3' PARA AGREGAR UN VEHICULO A UNA SUCURSAL\n");
            scanf("%d",&eleccion);

            switch (eleccion)
            {
                case '0':

                    if (BuscarAuto(EMP->autos, autoNuevo->detalleauto->id) == NULL)
                    {
                        agregarAuto(EMP->autos*,autoNuevo->detalleauto);
                        printf("EL AUTO SE AGREGO CON EXITO");
                        break;
                    }
                    else
                    {
                        printf("EL AUTO YA EXISTE");
                        break;
                    }

                case '1':

                    if(buscarRegion(EMP->regiones*, nuevaRegion->detalleregion->numero) == NULL)
                    {
                        agregarRegion(EMP->regiones*, nuevaRegion);
                        printf("LA REGION SE AGREGO CORRECTAMENTE");
                        break;
                    }
                    else
                    {
                        printf("LA REGION YA EXISTE");
                        break;
                    }

                case '2':
                    if(buscarSucursal(EMP->regiones->detalleregion->sucursales, idSucursal) == NULL) //cliente no existe, se puede agregar
                    {
                        agregarSucursal(EMP->regiones->detalleregion->sucursales,idSucursal,nombreSucursal,direccionSucursal);
                        printf("SUCURSAL SE HA AGREGADO CON EXITO");
                        break;
                    }
                    else
                    {
                        printf("LA SUCURSAL YA EXISTE");
                        break;
                    }
            }
    }