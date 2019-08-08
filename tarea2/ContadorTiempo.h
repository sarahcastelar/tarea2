#include <iostream>
#include <chrono> 
#include <ctime> 

using namespace std;

class ContadorTiempo {
private:
		std::chrono::time_point<std::chrono::system_clock> start, end;
public:

	void Iniciar() {
		 start = std::chrono::system_clock::now();
	}

	void Terminar() {
		 end = std::chrono::system_clock::now();
	}

	void Resetear() {

	}

	void duracion() {
		std::chrono::duration<double> elapsed_seconds = end - start;
		cout << "Tiempo ejecucion: " << elapsed_seconds.count() << "s\n";
	}


};