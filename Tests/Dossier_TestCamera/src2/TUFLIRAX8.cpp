#include "../include/FLIRAX8.h"

#include <iostream>

int main(){
    //Instantiation des objets 
    FLIR_AX8* laFLIR_AX8 = new FLIR_AX8("neco-10655D.local");

    //Lancement de la méthode pour établir une connexion Modbus TCP ou une déconnexion
    cout << "Choisir une option" << endl;
    cout << "Connexion : 1" << endl;
    cout << "Déconnexion : 2" << endl;

    int choix;
    cin >> choix;
    if (choix ==1){
    laFLIR_AX8-> Connection_Modbus();
    cout << "Connexion établie" << endl;
    } else if (choix ==2)
    {
    laFLIR_AX8-> Deconnection_Modbus();
    cout << "Déconnexion" << endl;
    }
    return 0;
}