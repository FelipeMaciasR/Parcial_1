#include <iostream>

using namespace std;

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

void modificarHorario(char Horario[][5][20], int d, int h, char materia[]) {
    h -= 8;
    d -= 1;
    char D[11]="Disponible";
    if (CompArr(Horario[h][d], D)) { //Verificacion si la hora esta disponible copio el nombre de la materia a asignar
        for (int i = 0; i < 20 && materia[i] != '\0'; i++) {
            Horario[h][d][i] = materia[i];
        }

    } else {
        cout << "La hora no esta disponible" << endl;
    }
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
