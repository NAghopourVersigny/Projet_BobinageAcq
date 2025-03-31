#include "../include/Camera.h"

#include <iostream>

int main(){
    //Instantiation des objets 
    Camera* laCamera = new Camera("neco-10655D.local");

    //Lancement de la méthode pour capturer une image
    laCamera->capturer_Image();

    return 0;
}