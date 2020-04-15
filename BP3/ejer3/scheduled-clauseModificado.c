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

   #pragma omp parallel
   {
      #pragma omp for firstprivate(suma) \
                               lastprivate(suma)  \
                               schedule(dynamic, chunck)
      for (i = 0; i < n; i++){
         suma = suma + a[i];
         printf ("thread %d suma a[%d] suma = %d\n",
                  omp_get_thread_num(), i, suma);


      }

      #pragma omp master
      {
         omp_get_schedule(&kind, &modifier);

         printf("Dentro de 'parallel for': \n  \t dyn-var: %d" ,  omp_get_dynamic());
         printf(" \n  \t nthreads-var: %d ", omp_get_max_threads());
         printf("  \n  \t thread-limit-var: %d ",omp_get_thread_limit());
         printf("  \n  \t run-sched-var: %d",  kind  );
      }
   }


   omp_get_schedule(&kind, &modifier);

   printf("\n\nFuera de 'parallel for' suma = %d\n", suma);
   printf("Fuera de 'parallel for': \n  \t dyn-var: %d" ,  omp_get_dynamic());
   printf(" \n  \t nthreads-var: %d ", omp_get_max_threads());
   printf("  \n  \t thread-limit-var: %d ",omp_get_thread_limit());
   printf("  \n  \t run-sched-var: %d \n",  kind  );


   return 0;
}
