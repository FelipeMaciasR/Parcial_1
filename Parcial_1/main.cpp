#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    cout << "Hello World!" << endl;
    ifstream fin;
    char codigo[15],nombre[15],creditos[15],h_docente[15],h_autonomas[15];
    char Materias[12][5];
    try{
        fin.open("Materias.txt");
        if(!fin.is_open()){
            throw '1';
        }
        while (getline(fin, codigo, ',') && getline(fin, nombre, ',') && getline(fin, creditos, ',')&& getline(fin, h_docente, ',')&& getline(fin, h_autonomas, ',')){

        }
    }catch(char c){
        cout<<"Error # "<<c<<": ";
        if(c=='1')
            cout<<"Error al abrir el archivo Materias.\n";
        else if(c=='2'){
            cout<<"Error al abrir el archivo para Horario.\n";
        }
    }catch (...){
        cout<<"Error no definido\n";
    }
    return 0;
}
