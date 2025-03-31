#include "../include/FLIRAX8.h"

#include <iostream>

int main(){
    //Instantiation des objets 
    FLIR_AX8* laFLIR_AX8 = new FLIR_AX8("neco-10655D.local");

    //Lancement de la méthode pour établir une connexion Modbus TCP
    laFLIR_AX8-> ConnectionFLIR_AX8();

    return 0;
}