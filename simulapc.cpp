#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <condition_variable>
#include <fstream>
#include <chrono>
#include <cstdlib>

using namespace std;

class ColaCircular {
private:
    vector<int> buffer;
    int capacidad;
    int frente, final, elementos;
    ofstream log;

    void duplicar_cola() {
        capacidad *= 2;
        buffer.resize(capacidad);
        log << "La cola ha sido duplicada a capacidad: " << capacidad << "\n";
    }

    void reducir_cola() {
        capacidad /= 2;
        buffer.resize(capacidad);
        log << "La cola ha sido reducida a capacidad: " << capacidad << "\n";
    }

public:
    ColaCircular(int tam_inicial, const string& log_filename) 
        : capacidad(tam_inicial), buffer(tam_inicial), frente(0), final(0), elementos(0), log(log_filename) {
        log << "Inicio del log de la simulación\n";
    }

    //void agregar() {}

    //bool extraer() {}
};

void productor(ColaCircular &cola, int id, int cantidad_items) {}
void consumidor(ColaCircular &cola, int id, int tiempo_espera) {}

int main(int argc, char *argv[]) {
    if (argc != 9) {
        cerr << "Uso: " << argv[0] << " -p <num_productores> -c <num_consumidores> -s <tam_inicial> -t <tiempo_espera>\n";
        return 1;
    }

    int num_productores, num_consumidores, tam_inicial, tiempo_espera;
    for (int i = 1; i < argc; i += 2) {
        if (string(argv[i]) == "-p") 
            num_productores = atoi(argv[i + 1]);
        else if (string(argv[i]) == "-c") 
            num_consumidores = atoi(argv[i + 1]);
        else if (string(argv[i]) == "-s") 
            tam_inicial = atoi(argv[i + 1]);
        else if (string(argv[i]) == "-t") 
            tiempo_espera = atoi(argv[i + 1]);
    }

    ColaCircular cola(tam_inicial, "log.txt");
    std::vector<std::thread> productores, consumidores;
    
    int items = 10; // Cantidad de items que añade un productor
    
    for(int i = 0; i < num_productores; i++) {
        productores.emplace_back(productor, ref(cola), i, items);
    }

    for(int i = 0; i < num_consumidores; i++) {
        productores.emplace_back(consumidor, ref(cola), i, tiempo_espera);
    }

}
