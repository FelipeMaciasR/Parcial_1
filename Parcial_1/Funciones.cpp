#include <iostream>

using namespace std;

//Numero de caracteres en una cadena
int NumElem(char* array)
{
    int cont=0;
    for(int i=0;*(array+i)!='\0';i++)
        cont++;

    return cont;
}

//Comparar dos cadenas de caracteres
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

//Conversion de un char a int
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

//Ayuda a la hora de leer el archivo Horario
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

bool modificarHorario(char Horario[][5][20], int d, int h, char materia[]) {
    h -= 8;
    d -= 1;
    bool V;
    char D[11]="Disponible";
    if (CompArr(Horario[h][d], D)) { //Verificacion si la hora esta disponible copio el nombre de la materia a asignar
        for (int i = 0; i < 20 && materia[i] != '\0'; i++) {//Copio el nombre de la materia en el espacio
            Horario[h][d][i] = materia[i];
        }
        V=true;

    } else {
        cout << "La hora no esta disponible" << endl;
        V=false;
    }
    return V;
}

void cambiarHoraAutonoma(char Horario[][5][20], int d, int h, int nd, int nh) {
    h -= 8;
    d -= 1;
    //Verificacion si la hora seleccionada es de estudio autonomo
    if (Horario[h][d][NumElem(Horario[h][d])-1] != '*') {
        cout << "La hora seleccionada no es una hora autonoma." << endl;
    }
    else{
        modificarHorario(Horario, nd, nh, Horario[h][d]);//Hago el cambio de hora indicado por el usuario
        char D[11]={"Disponible"};
        for(int ñ=0; ñ<10; ñ++){//Libero la hora que estaba, dejandola disponible
            Horario[h][d][ñ]=D[ñ];
        }
        Horario[h][d][10]='\0';
    }
}

//Verifico si faltan horas de estudio autonomo por asignar
bool VerificacionHA(char Materias[][5][20], int materia){
    bool V=true;
    for(int i=0; i<materia; i++){
        if(Char_Int(Materias[i][4])>0){
            V=false;
            break;
        }
    }
    return V;
}
