#include <cstdlib>
#include <iostream>
#include <ctime>
#include <sstream>

using namespace std;

int main() {
    // Obtenir la date/heure actuelle
    time_t t = time(nullptr);
    tm* now = localtime(&t);

    // Créer un nom de fichier : photo_YYYY-MM-DD_HH-MM-SS.jpg
    ostringstream filename;
    filename << "photo_"
             << (now->tm_year + 1900) << "-"
             << (now->tm_mon + 1 < 10 ? "0" : "") << (now->tm_mon + 1) << "-"
             << (now->tm_mday < 10 ? "0" : "") << now->tm_mday << "_"
             << (now->tm_hour < 10 ? "0" : "") << now->tm_hour << "-"
             << (now->tm_min < 10 ? "0" : "") << now->tm_min << "-"
             << (now->tm_sec < 10 ? "0" : "") << now->tm_sec << ".jpg";

    // Construire la commande libcamera-still
    string command = "libcamera-still -o " + filename.str();

    cout << "Exécution de : " << command << endl;

    // Exécuter la commande
    int result = system(command.c_str());

    // Vérification du résultat
    if (result == 0) {
        cout << "Photo capturée avec succès : " << filename.str() << endl;
    } else {
        cout << "Erreur lors de la capture" << endl;
    }

    return result;
}