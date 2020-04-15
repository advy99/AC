#include <stdio.h>
#include <stdlib.h>

#ifdef _OPENMP
   #include <omp.h>
#else
   #define omp_get_thread_num() 0
#endif

int main (int argc, char ** argv){
   int i, n = 200, chunck, a[n], suma = 0;

   omp_sched_t kind;
   int modifier;

   if (argc < 3){
      fprintf(stderr, "\nFalta iteraciones o chunck\n");
      exit(-1);
   }
   n = atoi(argv[1]); if (n > 200) n = 200; chunck = atoi(argv[2]);

   for (i = 0; i < n; i++) a[i] = i;

   omp_get_schedule(&kind, &modifier);

   printf("Fuera de parallel antes de modificar: \n");
   printf("\t\t dyn-ver: %d\n", omp_get_dynamic());
   printf("\t\t nthreads-var: %d\n", omp_get_max_threads());
   printf("\t\t run-sched-var: %d\n", kind);

   kind = 3;

   omp_set_dynamic(1);
   omp_set_num_threads(2);
   omp_set_schedule(kind, modifier);

   printf("Fuera de parallel despues de modificar: \n");
   printf("\t\t dyn-ver: %d\n", omp_get_dynamic());
   printf("\t\t nthreads-var: %d\n", omp_get_max_threads());
   printf("\t\t run-sched-var: %d\n", kind);


   #pragma omp parallel for firstprivate(suma) \
                            lastprivate(suma)  \
                            schedule(dynamic, chunck)
   for (i = 0; i < n; i++){
      suma = suma + a[i];
      printf ("thread %d suma a[%d] suma = %d\n",
               omp_get_thread_num(), i, suma);
   }

   printf("Fuera de 'parallel for' suma = %d\n", suma);


   return 0;
}
