#include <iostream>
#include <fstream>
#include <Funciones.h>

using namespace std;

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
        /*
        for(int i = 0; i < materia; i++) {
            for(int j = 0; j < 5; j++) {
                cout << Materias[i][j] << " ";
            }
            cout << endl;
        }
        */
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
        /*
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
        */
        //Menu para asignacion de horas autonomas
        int opcion, h, d, nd, nh;
        char materiaHA[20]={0};
        bool Verificacion, Verificacion2;
        char V[3]={0}, Si[3]={"Si"}, No[3]={"No"};
        do {
                cout << "Menu:" << endl;
                cout << "1. Visualizar horario" << endl;
                cout << "2. Asignar horas de estudio autonomo" << endl;
                cout << "3. Cambiar horas de estudio autonomo" << endl;
                cout << "4. Salir" << endl;
                cout << "Selecciona una opcion: ";
                cin >> opcion;

                switch (opcion) {
                    case 1:
                    //Impresion de horario
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
                        break;
                    case 2:
                    //Asignacion de horas autonomas a las horas disponibles
                    cout<<"Tienes las siguientes materias matriculadas: "<<endl;
                    for(int i = 0; i < materia; i++) {
                        cout <<"-"<< Materias[i][1] << " con "<<Materias[i][4]<< " horas de estudio autonomo por asignar"<< endl;
                    }
                    cout<<"A que materia le vas a asignar hora de estudio autonomo? ";
                    cin>>materiaHA;
                    Verificacion=false;
                    for(int i = 0; i < materia; i++) {
                        if(CompArr(materiaHA,Materias[i][1])){
                            if(Char_Int(Materias[i][4])>0){
                                cout<<"En que dia quieres asignar la hora? ";
                                cin>>d;
                                cout<<"A que hora? ";
                                cin>>h;
                                if((d>=1 && d<=5)&&( h>=8 && h<=19)){ //Validacion de los datos ingresados
                                    Verificacion2=modificarHorario(Horario, d, h, materiaHA);
                                    if(Verificacion2==true){
                                        Horario[h-8][d-1][NumElem(materiaHA)] = '*'; //Indica hora autonoma, diferente de hora de clase
                                        Materias[i][4][0]=(Char_Int(Materias[i][4])-1)+48;//Resto uno a las horas autonomas por asignar
                                        cout<<"La hora ha sido asignada"<<endl;
                                    }
                                }
                                else{
                                    cout<<"Dia u hora invalida"<<endl;
                                }
                            }
                            else{
                                cout<<"No tienes horas de estudio autonomo por asignar en "<<Materias[i][1]<<endl;
                            }
                            Verificacion=true;
                            break;
                        }
                    }
                    if(Verificacion==false){
                        cout<<"No tienes matriculada esa materia"<<endl;
                    }
                        break;
                    case 3:
                    //Cambio de una hora asignada a otra disponible
                    cout<<"Que dia vas a modificar? ";
                    cin>>d;
                    cout<<"Que hora? ";
                    cin>>h;
                    cout<<"A que dia lo vas a cambiar? ";
                    cin>>nd;
                    cout<<"A que hora? ";
                    cin>>nh;
                    if((d>=1 && d<=5)&&( h>=8 && h<=19) && (nd>=1 && nd<=5) &&( nh>=8 && nh<=19)){//Validacion de los datos ingresados
                        cambiarHoraAutonoma(Horario, d, h, nd, nh);
                    }
                    else{
                        cout<<"Dia u hora invalida"<<endl;
                    }
                        break;
                    case 4:
                    if(VerificacionHA(Materias, materia)==false){
                        //Si aun faltan horas por asignar, se lo hago saber al usuario
                        cout<<"Aun tienes horas de estudio autonomo por asignar, seguro que quieres salir? (Si o No) ";
                        cin>>V;
                        if(CompArr(V, Si)){
                            //Si desea salir, imprimo una ultima vez el horario
                            cout << "Asi quedo su horario" << endl;
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
                            cout << "Hasta luego" << endl;
                            break;
                        }
                        else if(CompArr(V, No)){
                            opcion=0;
                            break;
                        }
                        else{
                            cout<<"Opcion invalida"<<endl;
                            opcion=0;
                            break;
                        }
                    }
                    else{
                        //Una vez no tenga horas para asignar y y el usuario desee salir
                        //imprimo una ultima vez el horario
                        cout << "Asi quedo su horario" << endl;
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
                        cout << "Hasta luego" << endl;

                        break;
                    }
                    default:
                        cout << "Ingrese una opcion valida" << endl;
                        break;
                }
            } while (opcion != 4);

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


