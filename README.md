# Proyecto-II-SO
## Parte I:
Consiste en un programa que usa multihebras para crear una cola dinámica. \
Para compilar se utiliza el siguiente comando: `g++ simulapc.cpp -o simulapc -pthread` \
Para ejecutar se utiliza el siguiente comando: `./simulapc -p <num_productores> -c <num_consumidores> -s <tam_inicial> -t <tiempo_espera>`\
Donde `<num_productores>` es la cantidad de productores que tendrá el algoritmo, `<num_consumidores>` la cantidad de consumidores, `<tam_inicial>` el tamaño inicial de la cola y `<tiempo_espera>` el tiempo de espera máxima consumidores en segundos.

## Parte II: 
Consiste en un programa que crea un simulador de memoria virtual con paginación y algoritmos de reemplazo de páginas. \
Para compilar se utiliza el siguiente comando: `g++ mvirtual.cpp -o mvirtual` \
Para ejecutar se utiliza el siguiente comando: `./mvirtual -m <num_marcos>-a <algoritmo>-f <archivo_referencias>`\
Donde `<num_marcos>` son los nùmeros de marcos máximo, `<algoritmo>` el algoritmo a utilizar (que puede ser alguno de los siguientes: ``{Optimo, FIFO, LRU, LRURelojSimple}``), y ``<archivo_referencias>`` un archivo de texto de donde se extrae la lista de las páginas referenciadas.
