#include <stdlib.h>
#include <stdio.h>
#include <time.h>

/******************************************  FUNCIONES EXTRAS IMPLEMENTADAS PARA AYUDAR AL ALGORITMO *************************************************/
void Guardar_fila(int n){
    FILE* fichero;
    fichero = fopen("fila.txt", "wt");
    fprintf (fichero, "%d",n);
    fclose(fichero);
}

int Leer_fila(){
    FILE* fichero;
    char cadena[100];//soporta hasta 1000000000- 9 ceros
    int n;
    fichero=fopen("fila.txt","r");
    while(!(feof(fichero))){
        fgets(cadena,100,fichero);//puede leer 1000000000 hasta lo que el array le permite.
        n= atoi(cadena);
    }
    fclose(fichero);
    return n;
}

void Guardar_columna(int n){
    FILE* fichero;
    fichero = fopen("columna.txt", "wt");
    fprintf (fichero, "%d",n);
    fclose(fichero);
}

int Leer_columna(){
    FILE* fichero;
    char cadena[100];//soporta hasta 1000000000- 9 ceros
    int n;
    fichero=fopen("columna.txt","r");
    while(!(feof(fichero))){
        fgets(cadena,100,fichero);//puede leer 1000000000 hasta lo que el array le permite.
        n= atoi(cadena);
    }
    fclose(fichero);
    return n;
}


int estaVacia(int *vector){
    //if(vector==NULL){
        //return 0;
    //}
    //else{
        //return 1;
    //}
    return 0;
}


int *AhoradorTamanoVValores(int *EntradaVector){
    int i=0;
    while(EntradaVector[i]!=estaVacia(EntradaVector)){
        i++;
    }
    EntradaVector = (int *)realloc(EntradaVector, sizeof(int)*i);
    return EntradaVector;
}

int *AhoradorTamano(int *EntradaVector,int tam){
    EntradaVector = (int *)realloc(EntradaVector, sizeof(int)*tam);
    return EntradaVector;
}
/////////////////////////////
void ImprimirVector(int *EntradaVector){
    int i=0;
    while(EntradaVector[i]!=estaVacia(EntradaVector)){
        printf("%d-",EntradaVector[i]);
        i++;
    }
}
void ImprimirVectorFYC(int *EntradaVector,int tam){
    int i=0;
    while(i<tam){
        printf("%d-",EntradaVector[i]);
        i++;
    }
}
////////////////////
int *LLenarConCeros(int *EntradaVector,int Tam){//esta funcion solo seria para compiladores que no identifiquen el null y por el uso del realloc
    int i=0;
    while(i<Tam){
        EntradaVector[i]=0;
        i++;
    }
    return EntradaVector;
}


/*********************************************FUNCIONES PARA EL TAD****************************************************************/


int longVector(int *EntradaVector){
    int contador=0;
    while(EntradaVector[contador]!=estaVacia(EntradaVector)){
        contador++;
    }
    return contador;
}


int *crearVector(){
  int FilasEntrada=Leer_fila();
  int ColumnasEntrada=Leer_columna();

  int *Vector=((int *)malloc((FilasEntrada*ColumnasEntrada) * sizeof(int)));
  return Vector;
}


/*************************************************************************************************************/
///////////////////////////////
//PARA HACER LUEGO ; UNA ESTRUCTURA DONDE GUARDE DATOS COMO FILAS Y COLUMNAS Y ASI EVITAR LA MEMORIA EXTRA DEL PROGRAMA.

///////////////////////////////
typedef struct MATRIZ{// Estructura tipo Matriz(int,int,int).\nHecho por Jeison Fernando Garces Castañeda\n
    int *Valores;
    int *Filas;
    int *Columnas;
}Tipo_Matriz;
///////////////////////////////


//////////////////////////////////////////ESTO ES PARA CREAR LA MATRIZ DE ENTRADA///////////// ES EXTERNO AL PROYECTO
int **CrearMatriz(int filas,int columnas){
    int **matriz=(int **)malloc((filas) * sizeof(int*));//tamaño de filas
    //////////////////le doy espacio a las columas respecto al numero de filas.
    int n;//numero de filas
    for(n=0;n<filas;n++){
        matriz[n]=((int *)malloc((columnas) * sizeof(int)));
    }
    //Respecto al numero de filas y columnas se le asigna un valor.
    int i;
    for(i=0;i<filas;i++){//recorre las filas
        int j;
        for(j=0;j<columnas;j++){//recorre las columnas
          matriz[i][j]=rand()% 3;//colocar valores mayores a cero y menores e iguales a 3.
        }
    }
    return matriz;//retorna la matriz
}
///////////////////////////////////////////////CON LA FUNCION DE IMPRIMIR PUEDO VISUALIZAR LA MATRIZ

void imprimir_tablero(int **matriz){
    int filas=Leer_fila();
    int columnas=Leer_columna();
    int i;
    for(i=0;i<filas;i++){//recorre las filas
        int j;
        printf("\n");
        for(j=0;j<columnas;j++){//recorre las columnas
            printf("| %c ",matriz[i][j] + '0');//colocar valores mayores a cero y menores e iguales a 3.
        }
        printf("|");
        printf("\n");
    }
}
//////////////////////////////////////////////////

//////////////////////////CREACION DE LA MATRIZ DISPERSA////////////////////////
Tipo_Matriz Crear_De_Matriz_Completa(int **matrizEntrada){
    Tipo_Matriz Formato_Coordenado;
    int FilasEntrada=Leer_fila();
    int ColumnasEntrada=Leer_columna();
    int n=0,m;//filas, columnas
    Formato_Coordenado.Valores =crearVector();//valores , puede que toda la matriz los tenga.//crearvector();//me de vuelve un vector con un tamaño , piensalo despues
    Formato_Coordenado.Filas=crearVector();//tamaño del vector filas.
    Formato_Coordenado.Columnas=crearVector();//tamaño del vector columnas.

    Formato_Coordenado.Valores=LLenarConCeros(Formato_Coordenado.Valores,(FilasEntrada*ColumnasEntrada));//llena el vector con ceros porque algunos compiladores no observan el null
    Formato_Coordenado.Filas=LLenarConCeros(Formato_Coordenado.Filas,(FilasEntrada*ColumnasEntrada));//llena el vector con ceros para precau
    Formato_Coordenado.Columnas=LLenarConCeros(Formato_Coordenado.Columnas,(FilasEntrada*ColumnasEntrada));

    int T = 0;//Para llenar los vectorres Valores,Filas y Columnas. Tambien Guarda el Tamaño de estos por si algo
    while(n<FilasEntrada){
        for(m=0;m<ColumnasEntrada;m++){
                if(matrizEntrada[n][m] != 0){
                  Formato_Coordenado.Valores[T]= matrizEntrada[n][m];
                  Formato_Coordenado.Filas[T]= n;
                  Formato_Coordenado.Columnas[T]= m;
                  T++;
                }
        }
        n++;
    }
    Formato_Coordenado.Valores=AhoradorTamanoVValores(Formato_Coordenado.Valores);
    Formato_Coordenado.Filas=AhoradorTamano(Formato_Coordenado.Filas,T);
    Formato_Coordenado.Columnas=AhoradorTamano(Formato_Coordenado.Columnas,T);

    /*printf(" Valores\n");
    ImprimirVector(Formato_Coordenado.Valores);
    printf("\nfila\n");
    ImprimirVectorFYC(Formato_Coordenado.Filas,T);
    printf("\ncolumna\n");
    ImprimirVectorFYC(Formato_Coordenado.Columnas,T);
    printf("\n");
    */
    return Formato_Coordenado;
}//USA LAS FUNCIONES: leer fila y columna - llenar con ceros - ahorador de tamaño.
//////////////////////////////////////////////////

int **LLenarConCerosmatriz(int **matriz){
    int filas=Leer_fila();
    int columnas=Leer_columna();
    int f;
    for(f=0;f<filas;f++){//recorre las filas
        int c;
        for(c=0;c<columnas;c++){//recorre las columnas
          matriz[f][c]=0;
        }
    }
    return matriz;
}
int **Obtener_Matriz_Completa(Tipo_Matriz matriz_dispersa_Entrada){
    int filas=Leer_fila();
    int columnas=Leer_columna();
    int Tam=longVector(matriz_dispersa_Entrada.Valores);

    int **matriz=(int **)malloc((filas) * sizeof(int*));//tamaño de filas
    //////////////////le doy espacio a las columas respecto al numero de filas.
    int n;//numero de filas
    for(n=0;n<filas;n++){
        matriz[n]=((int *)malloc((columnas) * sizeof(int)));
    }
    //llenar de ceros la matriz
    matriz=LLenarConCerosmatriz(matriz);
    //llenar la matriz con los valores pertenecientes
    int i=0;
    while(i<Tam){
        matriz[matriz_dispersa_Entrada.Filas[i]][matriz_dispersa_Entrada.Columnas[i]]=matriz_dispersa_Entrada.Valores[i];
        i++;
    }
    //printf("\n");
    //imprimir_tablero(matriz);
    return matriz;
}//USA LAS FUNCIONES : leer fila y columna - longVector -imprimir_tablero




int Obtener_Elemento(Tipo_Matriz matriz_dispersa_entrada){//De esta manera solo necesito de entrada la matriz dispersa.
    int i,j;
    printf("Ingrese el elemento en n(fila) que desea obtener: ");
    scanf("%d",&i);
    printf("Ingrese el elemento en m(columna) que desea obtener: ");
    scanf("%d",&j);
    int elemento=0;
    int c=0;//contador
    while(c<longVector(matriz_dispersa_entrada.Valores)){
        if(matriz_dispersa_entrada.Filas[c]==i && matriz_dispersa_entrada.Columnas[c]==j){
            elemento=matriz_dispersa_entrada.Valores[c];
        }
        c++;
    }
    printf("%d",elemento);
    return elemento;
}//USA LAS FUNCIONES: longVector



int *Obtener_Fila(Tipo_Matriz matriz_dispersa_entrada){
    int Tam=longVector(matriz_dispersa_entrada.Valores);

    int i;
    printf("Ingrese el n(fila) que desea obtener: ");
    scanf("%d",&i);

    int *fila=(int *)malloc((Tam) * sizeof(int));
    int c=0,aux=0;
    while(c<Tam){
        if(matriz_dispersa_entrada.Filas[c]==i){
            fila[aux]=matriz_dispersa_entrada.Valores[c];//para obtener los valores d ea fila que me piden
            aux++;
        }
        c++;
    }
    ImprimirVectorFYC(fila,aux);

    return fila;
}//USA LAS FUNCIONES: long Vector - ImprimirVectorFyC .


int *Obtener_Columna(Tipo_Matriz matriz_dispersa_entrada){
    int Tam=longVector(matriz_dispersa_entrada.Valores);

    int i;
    printf("Ingrese el n(Columna) que desea obtener: ");
    scanf("%d",&i);

    int *columna=(int *)malloc((Tam) * sizeof(int));
    int c=0,aux=0;
    while(c<Tam){
        if(matriz_dispersa_entrada.Columnas[c]==i){
            columna[aux]=matriz_dispersa_entrada.Valores[c];//para obtener los valores de la columna que me piden
            aux++;
        }
        c++;
    }
    ImprimirVectorFYC(columna,aux);

    return columna;
}//USA LAS FUNCIONES: longVector - ImprimirVectorFyC



int Obtener_numero_de_elementos(Tipo_Matriz matriz_dispersa){
    int numero_elem=longVector(matriz_dispersa.Valores);
    /*
    int contador=0;

    while(contador < numero_elem)){
        matriz_dispersa.Valores[contador]];
        contador++;
    }
    printf("%d",contador);
    */
    return numero_elem;

}


Tipo_Matriz Matriz_Transpuesta(Tipo_Matriz matriz_dispersa_entrada){
    int Tam=longVector(matriz_dispersa_entrada.Valores);
    Tipo_Matriz Matriz_Dispersa_Transpuesta;
    //recorrer la matriz y asignar a las listas o vectores sus elementos e indices de dirreción.
    int **matriz_completa_nueva;
    int filas=Leer_fila();
    int columnas=Leer_columna();
    printf("\n");
    matriz_completa_nueva=Obtener_Matriz_Completa(matriz_dispersa_entrada);//hacer que funcione sin filas y columnas
    int **matriz_completa_nueva_temp=CrearMatriz(filas,columnas); //para evitar que se pierdan valores de la matriz
    ///////////// AHORA TRANSPONEMOS LOS VALORES DE LA MATRIZ/////////////
    int i2=0;
    while(i2<filas){
        int j2=0;
        while(j2<columnas){
            matriz_completa_nueva_temp[j2][i2]=matriz_completa_nueva[i2][j2];
            j2++;
        }
        i2++;
    }
    //imprimir_tablero(matriz_completa_nueva);
    //printf("\n");
    //imprimir_tablero(matriz_completa_nueva_temp);

    //////ahora armo otra vez la matriz dispers para retornarla//
    Matriz_Dispersa_Transpuesta=Crear_De_Matriz_Completa(matriz_completa_nueva);
    //ImprimirVector(Matriz_Dispersa_Transpuesta.Valores);
    return Matriz_Dispersa_Transpuesta;
}//USA LAS FUNCIONES: longVector - Leer fila y columna - Obtener_Matriz_Completa - CrearMatriz -Crear_De_Matriz_Completa

int *crearVectorColumna(){
    int ColumnasEntrada=Leer_columna();
    int *Vector=((int *)malloc((ColumnasEntrada) * sizeof(int)));
    int j;
    for(j=0;j<ColumnasEntrada;j++){//recorre las columnas
      Vector[j]= rand()% 3;//colocar valores mayores a cero y menores e iguales a 3.
      //printf("%d",Vector[j]);
    }
    return Vector;
}


Tipo_Matriz Suma_De_Matrices(Tipo_Matriz matriz_dispersa_1,Tipo_Matriz matriz_dispersa_2){
    int **matriz_1;
    int **matriz_2;
    matriz_1=Obtener_Matriz_Completa(matriz_dispersa_1);
    matriz_2=Obtener_Matriz_Completa(matriz_dispersa_2);
    ///////////////////////////////////////////
    int tam_fila=Leer_fila();
    int tam_Columna=Leer_columna();

    int **matriz_suma=CrearMatriz(tam_fila,tam_Columna);
    matriz_suma=LLenarConCerosmatriz(matriz_suma);

    int i;

    for(i=0;i<tam_fila;i++){
        int j=0;
        int x;
        int suma;
        while(j<tam_Columna){
            x=matriz_1[i][j];
            suma=matriz_2[i][j];
            matriz_suma[i][j]=suma+x;
            j++;
        }
    }
    printf("matriz suma\n");
    imprimir_tablero(matriz_suma);

    Tipo_Matriz suma_matriz=Crear_De_Matriz_Completa(matriz_suma);
    return suma_matriz;
}


Tipo_Matriz Producto_Matriz_Vector(Tipo_Matriz matriz_dispersa, int *Vector_col_producto){

    int **matriz_Completa = Obtener_Matriz_Completa(matriz_dispersa);
    int tam1=Leer_columna();
    int tam2=Leer_fila();

    int **nueva_matriz=CrearMatriz(tam2,tam1);
    nueva_matriz=LLenarConCerosmatriz(nueva_matriz);

    int i;
    for(i=0; i<tam2; i++){
        int j;
        int x;
        int y;
        for(j=0; j<tam1;j++){
            x=matriz_Completa[i][j];
            y=Vector_col_producto[j];
            nueva_matriz[i][j]=x*y;
        }
    }

    printf("matriz producto \n");
    imprimir_tablero(nueva_matriz);

    Tipo_Matriz matriz_Producto;
    matriz_Producto=Crear_De_Matriz_Completa(nueva_matriz);
    return matriz_Producto;
}





int main(){

    int filas=8;
    Guardar_fila(filas);
    int columnas=8;
    Guardar_columna(columnas);

    int **matriz;
    /***************************************************************************/
    matriz=CrearMatriz(filas,columnas);
    imprimir_tablero(matriz);
    /***************************************************************************/

    /***************************************************************************/
    Tipo_Matriz matriz_dispersa;
    matriz_dispersa=Crear_De_Matriz_Completa(matriz);
    /***************************************************************************/
    //int **matriz_completa;
    //matriz_completa=Obtener_Matriz_Completa(matriz_dispersa);//hacer que funcione sin filas y columnas
    /***************************************************************************/
    int elemento;
    //elemento =Obtener_Elemento(matriz_dispersa);//esta es la segunda de obtener elemento pero solo con una entrada.
    /***************************************************************************/
    int *Fila;
    //Fila=Obtener_Fila(matriz_dispersa);
    /***************************************************************************/
    int *Columna;
    //Columna=Obtener_Columna(matriz_dispersa);
    /***************************************************************************/

    //Obtener_Fila_Dispersa();
    //Obtener_Columna_Dispersa();
    /***************************************************************************/
    int num_elementos;
    num_elementos=Obtener_numero_de_elementos(matriz_dispersa);
    /***************************************************************************/
    //Modiﬁcar_Posicion();

    /***************************************************************************/
    srand(time(NULL));//FALTA ARREGLAR ESO DE LA SUMA
    int **Matriz_2=CrearMatriz(filas,columnas);
    //printf("matriz 2\n");
    //imprimir_tablero(Matriz_2);

    Tipo_Matriz matriz_dispersa2;
    matriz_dispersa2=Crear_De_Matriz_Completa(Matriz_2);
    ////////////////////////////////////////////////////
    Tipo_Matriz nueva_matriz_Dispersa;
    //nueva_matriz_Dispersa=Suma_De_Matrices(matriz_dispersa,matriz_dispersa2);

    /***************************************************************************/
    int *Vector_col_producto=crearVectorColumna();
    Tipo_Matriz nueva_matriz_Dispersa_producto;
    nueva_matriz_Dispersa_producto=Producto_Matriz_Vector(matriz_dispersa,Vector_col_producto);
    /***************************************************************************/
    Tipo_Matriz matriz_dispersa_Transpuesta;
    //matriz_dispersa_Transpuesta=Matriz_Transpuesta(matriz_dispersa);//listo pero hay que hacerle lo de filas y columnas

    crearVectorColumna();
}


