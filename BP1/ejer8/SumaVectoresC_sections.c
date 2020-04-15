/* SumaVectoresC.c
 Suma de dos vectores: v3 = v1 + v2

 Para compilar usar (-lrt: real time library, es posible que no sea necesario usar -lrt):
	gcc  -O2  SumaVectores.c -o SumaVectores -lrt
	gcc  -O2 -S SumaVectores.c -lrt

 Para ejecutar use: SumaVectoresC longitud

*/

#include <stdlib.h>	// biblioteca con funciones atoi(), malloc() y free()
#include <stdio.h>	// biblioteca donde se encuentra la funci�n printf()
#include <time.h>	// biblioteca donde se encuentra la funci�n clock_gettime()

#ifdef _OPENMP
   #include <omp.h>
#else
   #define omp_get_thread_num() 0
   #define omp_get_num_threads() 1
#endif

//S�lo puede estar definida una de las tres constantes VECTOR_ (s�lo uno de los ...
//tres defines siguientes puede estar descomentado):
//#define VECTOR_LOCAL	// descomentar para que los vectores sean variables ...
			// locales (si se supera el tama�o de la pila se ...
			// generar� el error "Violaci�n de Segmento")
//#define VECTOR_GLOBAL // descomentar para que los vectores sean variables ...
			// globales (su longitud no estar� limitada por el ...
			// tama�o de la pila del programa)
#define VECTOR_DYNAMIC	// descomentar para que los vectores sean variables ...
			// din�micas (memoria reutilizable durante la ejecuci�n)

#ifdef VECTOR_GLOBAL
#define MAX 33554432	//=2^25

double v1[MAX], v2[MAX], v3[MAX];
#endif
int main(int argc, char** argv){

  struct timespec cgt1,cgt2; double ncgt; //para tiempo de ejecuci�n

  //Leer argumento de entrada (n� de componentes del vector)
  if (argc<2){
    printf("Faltan n� componentes del vector\n");
    exit(-1);
  }

  unsigned int N = atoi(argv[1]);	// M�ximo N =2^32-1=4294967295 (sizeof(unsigned int) = 4 B)
  printf("Tama�o Vectores:%u (%u B)\n",N, sizeof(unsigned int));


  #ifdef VECTOR_DYNAMIC
  double *v1, *v2, *v3;
  v1 = (double*) malloc(N*sizeof(double));// malloc necesita el tama�o en bytes
  v2 = (double*) malloc(N*sizeof(double));
  v3 = (double*) malloc(N*sizeof(double));
  if ((v1 == NULL) || (v2 == NULL) || (v3 == NULL)) {
    printf("No hay suficiente espacio para los vectores \n");
    exit(-2);
  }
  #endif


  //Inicializar vectores
  #pragma omp parallel sections
  {
     #pragma omp section
        for(int i=0; i<N/4; i++){
         v1[i] = N*0.1+i*0.1; v2[i] = N*0.1-i*0.1;
        }

     #pragma omp section
       for(int i=N/4; i<N/2; i++){
        v1[i] = N*0.1+i*0.1; v2[i] = N*0.1-i*0.1;
       }

     #pragma omp section
       for(int i=N/2; i<3*N/4; i++){
        v1[i] = N*0.1+i*0.1; v2[i] = N*0.1-i*0.1;
       }
     #pragma omp section
       for(int i=3*N/4; i<N; i++){
         v1[i] = N*0.1+i*0.1; v2[i] = N*0.1-i*0.1;
       }
  }


  double start = omp_get_wtime();
  //Calcular suma de vectores

  #pragma omp parallel sections
  {
     #pragma omp section
        for(int i=0; i<N/4; i++){
         v3[i] = v1[i] + v2[i];
        }

     #pragma omp section
       for(int i=N/4; i<N/2; i++){
        v3[i] = v1[i] + v2[i];
       }

     #pragma omp section
       for(int i=N/2; i<3*N/4; i++){
        v3[i] = v1[i] + v2[i];
       }
     #pragma omp section
       for(int i=3*N/4; i<N; i++){
         v3[i] = v1[i] + v2[i];
       }
  }


  double end = omp_get_wtime();

  double time = end - start;

  //Imprimir resultado de la suma y el tiempo de ejecuci�n
  if (N<10) {
  printf("Tiempo:%11.9f\t / Tama�o Vectores:%u\n",time,N);
  for(int i=0; i<N; i++)
    printf("/ V1[%d]+V2[%d]=V3[%d](%8.6f+%8.6f=%8.6f) /\n",
           i,i,i,v1[i],v2[i],v3[i]);
  }
  else
    printf("Tiempo:%11.9f\t / Tama�o Vectores:%u\t/ V1[0]+V2[0]=V3[0](%8.6f+%8.6f=%8.6f) / / V1[%d]+V2[%d]=V3[%d](%8.6f+%8.6f=%8.6f) /\n",
           time,N,v1[0],v2[0],v3[0],N-1,N-1,N-1,v1[N-1],v2[N-1],v3[N-1]);


  #ifdef VECTOR_DYNAMIC
  free(v1); // libera el espacio reservado para v1
  free(v2); // libera el espacio reservado para v2
  free(v3); // libera el espacio reservado para v3
  #endif
  return 0;
}
