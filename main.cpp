#include <iostream>
#include <windows.h>


using namespace std;
int entrada;
HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

string palabrasSecretas[15] = {"rojos", "abeto", "bache", "cabra", "dados"
                                "enojo", "fallo", "gales", "hacer", "mania"
                               "nacer", "opera", "paris", "reloj", "sabio"};
string palabraSecreta;
bool incorrecta = false;
string palabra;
int largo, ciclos, victoria;

bool esLetra(char c){
    if(c > 0x40 && c < 0x5b)
        return true;
    if(c > 0x60 && c < 0x7b)
        return true;

    return false;
}

void menuPrincipal(){
    palabraSecreta = palabrasSecretas[(rand() % 15) + 1];
    //cout << palabraSecreta << endl;
    ciclos = victoria = 0;
    cout<<"Ingrese una opcion" << endl;
    cout<<"1) Mostrar Instrucciones" << endl;
    cout<<"2) Tutorial" << endl;
    cout<<"3) Jugar" << endl;
    cout<<"4) Cerrar el Programa" << endl;
    cin>>entrada;
}

void juego(){
    while(ciclos < 5){
        ciclos ++;
        if(victoria != 5){
            victoria = 0;
            cout << "\nEs tu " << ciclos << "/5 intentos" << endl;
            cout << "Ingresa una palabra de 5 letras: " << endl;
            cin >> palabra;
            largo = palabra.length();
        }else
            largo = 113;
        switch (largo) {
        case 5:
            for (int i = 0; i < largo; ++i)
                if(esLetra(palabra.at(i))){
                    incorrecta = false;
                    if(palabra.at(i) == palabraSecreta.at(i)){
                        SetConsoleTextAttribute(h, FOREGROUND_GREEN);
                        cout << palabra.at(i) << endl;
                        victoria ++;
                    }else{
                        for (int j = 0; j < largo; ++j)
                            if(palabra.at(i) == palabraSecreta.at(j) && i != j){
                                victoria = 0;
                                SetConsoleTextAttribute(h, 6);
                                cout << palabra.at(i) << endl;
                                incorrecta = false;
                                j = largo;
                            }else
                                incorrecta = true;
                        if(incorrecta){
                            victoria = 0;
                            SetConsoleTextAttribute(h, FOREGROUND_RED);
                            cout << palabra.at(i) << endl;
                        }
                    }
                }else{
                    victoria = 0;
                    cout << palabra.at(i) << " No es valido" << endl;
                    cout << "Ingresa solo Letras" << endl;
                }
            SetConsoleTextAttribute(h, 7);
            break;
        case 113:
            ciclos = 6;
            cout << palabra << " ES la palabra secreta, has ganado, FELICIDADES :)\n" << endl;
            break;
        default:
            cout << "Ingresa una palabra valida de 5 Letras" << endl;
            break;
        }
    }

    if(victoria != 5)
        cout << palabraSecreta << " Era la palabra secreta, has perdido :(, Vuelve a intentarlo\n" << endl;
}

void instrucciones(){
    cout << "\nBienvenido, te enseñare a jugar a adivina la palabra" << endl;
    cout << "El objetivo es adivinar la palabra de 5 letras en 5 o menos oportunidades" << endl;
    cout << "para empezar deberas ingresar una palabra de 5 letras" << endl;
    cout << "justo despues recibiras las letras de la palabra que ingresaste" << endl;
    cout << "dependiendo del color que este pintada significa lo siguiente" << endl;
    SetConsoleTextAttribute(h, FOREGROUND_GREEN);
    cout << "VERDE = Significa que la palabra contiene esa letra y esa ES su posicion, entonces ya no la cambies ni la muevas" << endl;
    SetConsoleTextAttribute(h, 6);
    cout << "AMARILLO = Significa que la palabra contiene esa letra, pero esa NO es su posicion, asi que encuentrala" << endl;
    SetConsoleTextAttribute(h, FOREGROUND_RED);
    cout << "ROJO = Significa que la palabra secreta no contiene esa letra, asi que ya no la uses" << endl;
    SetConsoleTextAttribute(h, 7);
    cout << "Al obtener las 5 letras en verde entonces habras ganado" << endl;
    cout << "si no lo logras en 5 opotunidades, perderas, pero no te rindas, puedes volver a tratar" << endl;
    cout << "Ya conoces como jugar a adivina la palabra, mucha suerte\n" << endl;
}

void tutorial(){
    palabraSecreta = "arbol";
    ciclos = 1;
    cout << "\nBienvenido al tutorial, esta es una partida de prueba" << endl;
    cout << "para que logres entender el juego practicando: " << endl;
    cout << "Es tu " << ciclos << "/5 intento" << endl;
    cout << "Ingresa una palabra de 5 letras: " << endl;
    SetConsoleTextAttribute(h, FOREGROUND_GREEN);
    cout << "a" << endl;
    cout << "r" << endl;
    cout << "b" << endl;
    SetConsoleTextAttribute(h, FOREGROUND_RED);
    cout << "x" << endl;
    SetConsoleTextAttribute(h, FOREGROUND_GREEN);
    cout << "l" << endl;
    SetConsoleTextAttribute(h, 7);
    cout << "en este caso tienes ya casi la palabra adivinada" << endl;
    cout << "solo ingresa la letra que falta para ganar, o prueba como se ve una letra incorrecta" << endl;
    juego();
}

void menu(){
    do{
        menuPrincipal();

        switch (entrada) {
        case 1:
            instrucciones();
            break;
        case 2:
            tutorial();
            break;
        case 3:
            juego();
            break;
        case 4:
            cout<<"Programa Finalizado" << endl;
            abort();
            break;
        default:
            SetConsoleTextAttribute(h, FOREGROUND_RED);
            cout <<"\nIngresa una opcion valida, " << entrada << " NO lo es\n"<< endl;
            SetConsoleTextAttribute(h, 7);
            menu();
            break;
        }
    } while(entrada != 4);
}


int main()
{
    cout << "Bienvenido a Adivina la Palabra" << endl;
    menu();

    return 0;

}
