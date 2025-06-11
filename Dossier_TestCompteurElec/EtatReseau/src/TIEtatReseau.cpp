#include <iostream>
#include <string>
#include <unistd.h>
#include <cstdint>

#include "../include/EtatReseau.h"
#include "../include/DatabaseManager.h"

using namespace std;

int main()
{
    int id_Machine = 1;
    DatabaseManager *leDatabaseManager = new DatabaseManager();
    int Temperature = 25;
    int Humidite = 50;
    auto now = std::chrono::system_clock::now();
    std::time_t t_c = std::chrono::system_clock::to_time_t(now);
    std::tm tm = *std::localtime(&t_c);

    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y-%m-%d %H:%M");

    string dateHeure = oss.str();
    cout << "dateHeure" << dateHeure << endl;

    string queryRafa = "INSERT INTO Contexte (date,tempAmb, humidite, id_Machine) VALUES (\"" + dateHeure + "\"," + to_string(Temperature) + "," + to_string(Humidite) + "," + to_string(id_Machine) + ");";
    cout << queryRafa << endl;
    leDatabaseManager->executerRequete(queryRafa);
    cout << "queryRafa" << endl;

    // Créer une instance de EtatReseau avec le compteur
    EtatReseau *etatReseau = new EtatReseau();

    cout << "etatReseau" << endl;
    // Appeler la méthode pour acquérir les données
    etatReseau->acquerirEtatReseau();

    cout << "acquerirEtatReseau" << endl;

    // Afficher les valeurs récupérées
    vector<float> tensions = etatReseau->getTension_Reseau();
    vector<float> intensites = etatReseau->getIntensite_Reseau();
    vector<float> cosPhi = etatReseau->getFacteurPuissance_Reseau();

    cout << "Tensions Réseau: ";
    for (float t : tensions)
        cout << t << " V, ";
    cout << endl;

    cout << "Intensites Réseau: ";
    for (float i : intensites)
        cout << i << " A, ";
    cout << endl;

    cout << "Facteurs de Puissance: ";
    for (float f : cosPhi)
        cout << f << ", ";
    cout << endl;

    etatReseau->enregistrerEtatReseau(leDatabaseManager); //, id_Machine);

    return 0;
}
