#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <condition_variable>
#include <fstream>
#include <chrono>
#include <cstdlib>

#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <condition_variable>
#include <fstream>
#include <chrono>
#include <cstdlib>

class ColaCircular {
private:
    std::vector<int> buffer;
    int capacidad;
    int frente, final, elementos;
    std::ofstream log;

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
    ColaCircular(int tam_inicial, const std::string& log_filename) 
        : capacidad(tam_inicial), buffer(tam_inicial), frente(0), final(0), elementos(0), log(log_filename) {
        log << "Inicio del log de la simulación\n";
    }

    //void agregar() {}

    //bool extraer() {}
};

//void productor() {}
//void consumidor() {}

int main(int argc, char *argv[]) {
    if (argc != 9) {
        std::cerr << "Uso: " << argv[0] << " -p <num_productores> -c <num_consumidores> -s <tam_inicial> -t <tiempo_espera>\n";
        return 1;
    }
}
