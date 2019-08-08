#include <iostream>
#include "ArchivoItem.h"
#include "ContadorTiempo.h"

using namespace std;

int main() {

	struct Item struct_item;
	ArchivoItem ai;
	ContadorTiempo ct;
	int resp = -1;


	do {
		char id1[5];
		char nombre1[9];
		float monto = -1;

		cout << "---------------------" << endl
			<< "Tarea 2" << endl
			<< "1. Agregar registros" << endl
			<< "2. Buscar por nombre (secuencialmente)" << endl
			<< "3. Buscar por nombre (binariamente) " << endl
			<< "4. Salir" << endl
			<< "---------------------" << endl;
		cin >> resp;

		if (resp == 1) {
			int n = -1;
			cout << "cuantos registros quiere ingresar? " << endl;
			cin >> n;
			ai.setNum_Registros(n);

			if (n > 0) {
				for (int i = 0; i < n; i++)
				{
					int codigo;
					char nombre[30];
					char apellidos[30];
					char ciudad[50];

					cout << "Ingrese codigo: " << endl;
					cin >> codigo;
					while ((codigo < 1) || (codigo > 100)) {
						cout << "Codigo solo puede ser del 1 al 100." << endl;
						cout << "Ingrese codigo de nuevo: " << endl;
						cin >> codigo;
					}
					struct_item.codigo = codigo;
					cout << "Ingrese nombre: " << endl;
					cin >> nombre;
					strcpy_s(struct_item.nombres, nombre);
					cout << "Ingrese apellidos: " << endl;
					cin >> apellidos;
					strcpy_s(struct_item.apellidos, apellidos);
					cout << "Ingrese ciudad: " << endl;
					cin >> ciudad;
					strcpy_s(struct_item.ciudad, ciudad);


					//guardar el nuevo cliente en el archivo
					ai.agregarRegistros(struct_item);
					cout << "Registro agregado exitosamente. " << endl;
				}
			}
		}

		if (resp == 2 || resp == 3) {
			char nombres[30];;
			cout << "Ingrese nombre a buscar: " << endl;
			cin >> nombres;

			if (resp == 2) {
				ct.Iniciar();
				ai.buscarNombreS(nombres);
				ct.Terminar();
				ct.duracion();
			}
			else {
				ct.Iniciar();
				ai.buscarNombreB(nombres, 0, 0, 0, 0);
				ct.Terminar();
				ct.duracion();
			}
		}

	} while (resp != 4);



	return 0;
}