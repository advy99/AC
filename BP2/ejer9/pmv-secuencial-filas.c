#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifdef _OPENMP
   #include <omp.h>
#else
   #define omp_get_thread_num() 0
   #define omp_get_num_threads() 1
#endif


int main(int argc, char ** argv){

   if (argc < 2){
      fprintf (stderr, "Falta tam matriz \n");
      exit(-1);
   }

   int n = atoi(argv[1]);

   double ** m = (double **) malloc (n*sizeof(double*));

   for (int i = 0; i < n ; i++){
      m[i] = (double *) malloc (n * sizeof(double) );
   }


   double * v = (double *) malloc (n * sizeof(double));

   double * r = (double *) malloc (n * sizeof(double));

   //velores iniciales
   for (int i = 0; i < n; i++){
      for(int j = 0; j < n; j++){
         m[i][j] = i + j;
      }
      v[i] = i;
   }


   struct timespec cgt1,cgt2; double ncgt; //para tiempo de ejecuci�n

   clock_gettime(CLOCK_REALTIME,&cgt1);

   // multiplicacion
   #pragma omp parallel for
   for (int i = 0; i < n; i++){
      for(int j = 0; j < n; j++){
         r[i] += m[i][j] * v[j];
      }
   }

   clock_gettime(CLOCK_REALTIME,&cgt2);
   ncgt=(double) (cgt2.tv_sec-cgt1.tv_sec)+
     (double) ((cgt2.tv_nsec-cgt1.tv_nsec)/(1.e+9));



    if (n < 10){
     	for (int i = 0; i < n; i++)
     		printf("r[%d]=%f\n", i, r[i]);
    }

  	 else printf("\nTiempo (seg): %11.9f\t Tamaño: %d\tv2[0]=%f\tv[%d]=%f\n", ncgt, n, r[0], n - 1, r[n - 1]);







   for (int i = 0; i < n ; i++){
      free(m[i]);
   }

   free(m);




}
