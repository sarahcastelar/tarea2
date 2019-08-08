#include <iostream>
#include <fstream>

using namespace std;

struct Item {
	int codigo;
	char nombres[30];
	char apellidos[30];
	char ciudad[50];
	Item() {

	};
};

class ArchivoItem {

private:
	int num_registros;
	bool first = true;
	int totalRegistros = -1;

public:
	int getNum_Registros() {
		return num_registros;
	}

	void setNum_Registros(int num_registros) {
		this->num_registros = num_registros;
	}


	void agregarRegistros(Item struct_item) {
		ofstream fileC("archivoRegistros1.dat", ios::out | ios::app | ios::binary);
		if (!fileC) {
			cout << "Error de apertura en el archivo. " << endl;
			return;
		}
		else {
			fileC.seekp(0, ios::end);
			fileC.write(reinterpret_cast<const char*>(&struct_item), sizeof(struct_item));
			fileC.close();
		}

	}
	//stcmrp
	//-1 menor 1 mayor

	void buscarNombreS(const char* lookName) {
		bool encontro = false;
		ifstream fileC("archivoRegistros1.dat", ios::in | ios::binary);
		//ifstream fileC("items.dat", ios::in | ios::binary);
		if (!fileC) {
			cout << "Error de aprtura en el archivo!" << endl;
		}

		fileC.seekg(0, ios::beg);
		Item struct_item;
		fileC.read(reinterpret_cast<char*>(&struct_item), sizeof(struct_item));

		while (!fileC.eof()) {
			char nomb[30];
			strcpy_s(nomb, struct_item.nombres);
			if (strcmp(lookName, nomb) == 0) { //si lo encuentra. 
				cout << "Codigo: " << struct_item.codigo << " Nombre: " << struct_item.nombres
					<< " Apellidos: " << struct_item.apellidos
					<< " Ciudad: " << struct_item.ciudad << endl;
				encontro = true;
				break;
			}
			fileC.read(reinterpret_cast<char*>(&struct_item), sizeof(struct_item));
		}

		if (!encontro) {
			cout << "El registro con el nombre: " << lookName << " no existe. " << endl;
		}
		fileC.close();
	}

	void buscarNombreB(const char* lookName, int mitad, int puntero,int left, int right) {
		Item struct_item;
		ifstream fileC("archivoRegistros1.dat", ios::in | ios::binary);
		//ifstream fileC("items.dat", ios::in | ios::binary);
		if (!fileC) {
			cout << "Error de aprtura en el archivo!" << endl;
		}

		if (first) {
			fileC.seekg(0, ios::end);
			int fileSize = fileC.tellg();
			totalRegistros = fileSize / sizeof(struct_item);
			mitad = totalRegistros / 2;
			left = mitad - 1;
			right = mitad + 1;
			puntero = (mitad * sizeof(struct_item));
			first = false;
		}

		fileC.seekg(puntero, ios::beg);
		fileC.read(reinterpret_cast<char*> (&struct_item), sizeof(struct_item));
		int resultado = strcmp(lookName, struct_item.nombres);

		if (left < right) {
			if (resultado == 0) {
				cout << "Codigo: " << struct_item.codigo << " Nombre: " << struct_item.nombres
					<< " Apellidos: " << struct_item.apellidos
					<< " Ciudad: " << struct_item.ciudad << endl;
			}
			else if (resultado < 0) {//izq
				mitad--;
				mitad /= 2;
				puntero = (mitad * sizeof(struct_item));
				left = mitad - 1;
				right = mitad + 1;
				fileC.close();
				buscarNombreB(lookName, mitad, puntero,left,right);
			}
			else { //resultado es > 0 DERECHA
				int countNumbers = totalRegistros - mitad;
				countNumbers /= 2; //se convierte en la mitad. 
				mitad += countNumbers;
				puntero = (mitad * sizeof(struct_item));
				left = mitad - 1;
				right = mitad + 1;
				fileC.close();
				buscarNombreB(lookName, mitad, puntero,left,right);
			}
		} else {
			cout << "El registro con el nombre: " << lookName << " no existe. " << endl;
		}
	}

};
