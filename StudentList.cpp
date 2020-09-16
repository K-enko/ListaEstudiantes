#include <iostream>
#include <fstream>
using namespace std;

struct student
{
	string name;
	string lastname;
	int years;
	long int dni;
	double qualification;
};

void load_data();
void request_save_data();
void delate_student();
void replace_data();
void request_qualification();
void see_students();
void search_q();

student students[50];
int menu;
int contador;
int selec_student;
int qualif, qualif_f, num_student;

int main()
{
	do
	{
		load_data();

		cout << "1. Aniadir alumno." << endl;
		cout << "2. Eliminar alumno." << endl;
		cout << "3. Calificar alumno." << endl;
		cout << "4. Ver lista. Mostrar nota mas alta y el promedio de la clase." << endl;
		cout << endl;
		cout << "0. Salir." << endl;
		cin >> menu;
		cin.ignore();

		switch(menu)
		{
			case 1:

			request_save_data();

			break;
			case 2:

			delate_student();

			break;
			case 3:

			request_qualification();

			break;
			case 4:

			search_q();

			break;
			case 0:

			cout << "El programa se cerrara. Vuelva pronto." << endl;

			break;
			default:

			cout << "No ingreso un valor valido entre las opciones. Intente de nuevo." << endl;
		}
	}while(menu!=0);

	return 0;
}

void load_data()
{
	contador = 0;
	ifstream imp_file;
	imp_file.open("AyEDI.txt", ios::in);
	if(imp_file.is_open())
	{
		while(!imp_file.eof())
		{
			getline(imp_file, students[contador].name);
			getline(imp_file,students[contador].lastname);
			imp_file >> students[contador].years;
			imp_file >> students[contador].dni;
			imp_file >> students[contador].qualification;

			if((!students[contador].name.empty()) && (!students[contador].lastname.empty()) && (students[contador].years != 0) && (students[contador].dni != 0))
			{
				contador++;
			}
		}
	}
	imp_file.close();
}

void request_save_data()
{
	cout << "Ingrese el nombre/s del alumno: ";
	getline(cin, students[contador].name);
	cout << "Ingrese el/los apellido/s del alumno: ";
	getline(cin, students[contador].lastname);
	cout << "Ingrese la edad del alumno: ";
	cin >> students[contador].years;
	cin.ignore();
	cout << "Ingrese el numero de DNI del alumno: ";
	cin >> students[contador].dni;
	cin.ignore();

	ofstream oup_file;
	oup_file.open("AyEDI.txt", ios::out | ios::app);
	if(oup_file.is_open())
	{
		oup_file << students[contador].name << endl;
		oup_file << students[contador].lastname << endl;
		oup_file << students[contador].years << endl;
		oup_file << students[contador].dni << endl;
		oup_file << students[contador].qualification << endl;
	}
	oup_file.close();
	contador++;
}

void delate_student()
{
	see_students();

	cout << "Ingrese el alumno a eliminar: ";
	cin >> selec_student;
	cin.ignore();

	for(int i = contador-1; selec_student<=i; i--)
	{
		students[i-1].name = students[i].name;
		students[i-1].lastname = students[i].lastname;
		students[i-1].years = students[i].years;
		students[i-1].dni = students[i].dni;
		students[i-1].qualification = students[i].qualification;
	}

	--contador;

	replace_data();
}

void replace_data()
{
	ofstream oup_file;
	oup_file.open("AyEDI.txt", ios::out);
	if(oup_file.is_open())
	{
		for(int i=0; i<contador; i++)
		{
			oup_file << students[i].name << endl;
			oup_file << students[i].lastname << endl;
			oup_file << students[i].years << endl;
			oup_file << students[i].dni << endl;
			oup_file << students[i].qualification << endl;
		}
	}
	oup_file.close();
}

void request_qualification()
{
	see_students();

	cout << "Ingrese el alumno a calificar: ";
	cin >> selec_student;
	cin.ignore();

	cout << "Ingrese la calificacion del alumno: ";
	cin >> students[selec_student].qualification;
	cin.ignore();

	replace_data();
}

void see_students()
{
	for(int i=0; i<contador; i++)
	{
		cout << i << ". " << students[i].name << " " << students[i].lastname << endl;
		cout << students[i].years << " anios." << endl;
		cout << students[i].dni << endl;
		cout << "Calificacion: " << students[i].qualification << endl;
		cout << endl;
	}
}

void search_q()
{
	for(int i=0; i<contador; i++)
	{
		if(qualif < students[i].qualification)
		{
			qualif = students[i].qualification;

			num_student = i;
		}

		qualif_f += students[i].qualification;
	}

	cout << "La califiacion mas alta es: " << students[num_student].qualification << endl;
	cout << "Nombre de alumno: " << students[num_student].name << " " << students[num_student].lastname << endl;
	cout << "Edad: " << students[num_student].years << endl;
	cout << "NDI: " << students[num_student].dni << endl;
	cout << endl;
	cout << "el promedio de calificaciones es: " << qualif_f << endl;
	cout << endl;

	see_students();
}