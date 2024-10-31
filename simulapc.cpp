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
    std::mutex mtx;                                 //Not you again... Noooooo!!
    std::condition_variable not_full, not_empty;    //Initialize condition variables for the monitor.

    void duplicar_cola() {
        capacidad *= 2;
        buffer.resize(capacidad);
        frente = 0;
        final = elementos;
        log << "La cola ha sido duplicada a capacidad: " << capacidad << "\n";
    }

    void reducir_cola() {
        capacidad /= 2;
        buffer.resize(capacidad);
        frente = 0;
        final = elementos;
        log << "La cola ha sido reducida a capacidad: " << capacidad << "\n";
    }

public:
    ColaCircular(int tam_inicial, const std::string& log_filename) 
        : capacidad(tam_inicial), buffer(tam_inicial), frente(0), final(0), elementos(0), log(log_filename) {
        log << "Inicio del log de la simulación\n";
    }

    void agregar(int item) {            //Method for Productors to add items to the circular queue.
        std::unique_lock<std::mutex> lock(mtx);                         //Acquire lock! >:)
        not_full.wait(lock, [this] { return elementos < capacidad; });  //Wait for the Circular Queue to have space.

        buffer[final] = item;           //We add the item at the end of the queue.
        final = (final+1)%capacidad;    //Move the final index one step to the right.
        elementos++;                    //New item to the queue update.

        if (elementos == capacidad){    // If the queue reaches its limit...
            duplicar_cola();            // Dup its size.
        } 

        log << "Añadido: " << item << ". || Tamaño de cola: " << elementos << " || Capacidad: " << capacidad << "\n";
        not_empty.notify_one();         // Notify the waiting consumers that we've got a new batch of ice cream :)
    }

    void extraer(int &item, int max_wait_seconds) {     // Method for Consumers to extract items from the circular queue.
        std::unique_lock<std::mutex> lock(mtx);         // El mutex es mío, me lo quieren quitar...

        if (!not_empty.wait_for(lock, std::chrono::seconds(max_wait_seconds), [this] { return elementos > 0; })) // Wait for ice cream batches to arrive to the Circular Queue.
            return false; // "bruh, we've been waiting here for [max_wait_seconds], let's get outta here...""

        // If there's an ice cream batch in the Circular Queue...
        item = buffer[frente];          // We extract the ice cream.
        frente = (frente+1)%capacidad;  // Move the front index one step to the left.
        elementos--;                    // Farewell... mint flavour ice cream...

        if (elementos < capacidad / 4 && capacidad > 1){   //If the number of ice cream flavours reaches 25% of the capacity or less...
            reducir_cola(); // Reduce the size of the ice cream truck!! We can't afford these taxes!!
        }
        log << "Consumido: " << item << ". || Tamaño de cola: " << elementos << " || Capacidad: " << capacidad << "\n";
        not_full.notify_one();      //Notify a waiting productor that the queue ain't full anymore.
    }
};

//void productor() {}
//void consumidor() {}

int main(int argc, char *argv[]) {
    if (argc != 9) {
        std::cerr << "Uso: " << argv[0] << " -p <num_productores> -c <num_consumidores> -s <tam_inicial> -t <tiempo_espera>\n";
        return 1;
    }
}
