#include <iostream>
#include <fstream>

using namespace std;

int NumElem(char* array);
bool CompArr(char* array1, char* array2);
int Char_Int(char* array);
int ConversionDia(char c);

int main()
{
    ifstream fin;
    char Materias[7][5][20];
    char Horario[12][5][20]={0};
    try{
        fin.open("Materias.txt");
        if(!fin.is_open()){
            throw '1';
        }
        int materia=0, columna=0, indiceC=0;
        //Lectura del archivo materias leyendo informacion por comas y almacenando
        //en matriz Materias con formato Materias[Linea][codigo,nombre,creditos,h.clase,h.autonomas]
        char c;
        while (fin.get(c)) {
            if(c == ',') {
                Materias[materia][columna][indiceC] = '\0';
                columna++;
                indiceC = 0;
            } else if(c == '\n') {
                Materias[materia][columna][indiceC] = '\0';
                materia++;
                columna = 0;
                indiceC = 0;
            } else {
                Materias[materia][columna][indiceC] = c;
                indiceC++;
            }
        }
        fin.close();
        //Verificacion de la informacion guardada

        for(int i = 0; i < materia; i++) {
            for(int j = 0; j < 5; j++) {
                cout << Materias[i][j] << " ";
            }
            cout << endl;
        }

        fin.open("Horario.txt");
        if(!fin.is_open()){
            throw '2';
        }
        char codigo[8]={0},hora[3]={0},dia;
        int aux=1, indice=0;;
        //Lectura de archivo Horario con formato Horario[hora][dia][materia]
        while (fin.get(c)) {
            if(c == ',') {
                aux++;
                indice = 0;
            } else if(c == '\n') {
                for(int i = 0; i < materia; i++) {
                    //Comparo el codigo leido del archivo en la matriz donde guardé las materias
                    //con su informacion para mas claridad a la hora de imprimir (en la matriz
                    //Horario saldra el nombre de la materia en lugar de su codigo)
                    if(CompArr(codigo,Materias[i][0])){
                        for(int k=0; k<NumElem(Materias[i][1]); k++){
                            Horario[Char_Int(hora)-8][ConversionDia(dia)][k]=Materias[i][1][k];
                        }
                        hora[1]='\0';
                        break;
                    }
                }
                aux=1;
                indice = 0;
            } else if(aux==1) {
                codigo[indice] = c;
                indice++;
            }
            else if(aux==2) {
                hora[indice]= c;
                indice++;
            } else if(aux==3) {
                dia = c;
            }

        }
        fin.close();
        //Relleno los espacios vacios con "Disponible" para mas claridad
        char D[11]={"Disponible"};
        for(int i = 0; i < 12; i++) {
            for(int j = 0; j < 5; j++) {
                if(Horario[i][j][0]=='\0'){
                    for(int ñ=0; ñ<10; ñ++){
                        Horario[i][j][ñ]=D[ñ];
                    }
                }

            }

        }
        //Impresion de la matriz Horario para verificar
        char Dias[5][11] = {"Lunes", "Martes", "Miercoles", "Jueves", "Viernes"};
        cout << "       ";
        for(int j = 0; j < 5; j++) {
            printf("%-*s", 20, Dias[j]);
        }
        cout << endl;
        for(int i = 0; i < 12; i++) {
            printf("%2d:00  ", i+8);
            for(int j = 0; j < 5; j++) {
                printf("%-*s", 20, Horario[i][j]);
            }
            cout << endl;
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
int NumElem(char* array)
{
    int cont=0;
    for(int i=0;*(array+i)!='\0';i++)
        cont++;

    return cont;
}

bool CompArr(char* array1, char* array2)
{
    bool b=true;
    if(NumElem(array1)!=NumElem(array2))
        return false;
    else
    {
        for(int i=0; i<NumElem(array1); i++)
        {
            if(*(array1+i)!=*(array2+i))
            {
                b=false;
                break;
            }
        }
    }
    return b;
}

int Char_Int(char* array)
{
    int elem=NumElem(array), aux=1, num=0;
    for(int i=elem-1; i>=0; i--)
    {
        num=num+(*(array+i)-48)*aux;
        aux*=10;
    }
    return num;
}

int ConversionDia(char c){
    if(c=='L'){
        return 0;
    }
    else if(c=='M'){
        return 1;
    }
    else if(c=='W'){
        return 2;
    }
    else if(c=='J'){
        return 3;
    }
    else if(c=='V'){
        return 4;
    }
}
