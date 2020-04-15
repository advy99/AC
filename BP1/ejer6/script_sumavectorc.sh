#!/bin/bash
#Todos los scripts que se hagan para atcgrid deben incluir lo siguiente:
#Se asigna al trabajo el nombre SumaVectoresC_vglobales
#PBS -N SumaVectoresC_vglobales
#Se asigna al trabajo la cola ac
#PBS -q ac  
#Se imprime información del trabajo usando variables de entorno de PBS
echo "Id. usuario del trabajo: $PBS_O_LOGNAME"
echo "Id. del trabajo: $PBS_JOBID"
echo "Nombre  del trabajo especificado por usuario: $PBS_JOBNAME"
echo "Nodo que ejecuta qsub: $PBS_O_HOST"
echo "Directorio en el que se ha ejecutado qsub: $PBS_O_WORKDIR"
echo "Cola: $PBS_QUEUE"
echo "Nodos asignados al trabajo:"
cat $PBS_NODEFILE
# FIN del trozo que deben incluir todos los scripts

export OMP_DYNAMIC=FALSE
export OMP_NUM_THREADS=4

time $PBS_O_WORKDIR/SumaVectoresC 10
time $PBS_O_WORKDIR/SumaVectoresC 10000000
