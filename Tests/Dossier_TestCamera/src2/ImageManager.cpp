#include <iostream>
#include <filesystem>
#include <string>
#include <chrono>
#include "../include/ImageManager.h"

using namespace std;
namespace fs = std::filesystem;

void ImageManager::trierImage() {
    string dossier = "";  // Mettre le chemin vers le dossier à trier

    if (!fs::exists(dossier) || !fs::is_directory(dossier)) {
        cout << "Erreur : le dossier spécifié est introuvable ou invalide." << endl;
        return;
    }

    fs::path dernierFichier;
    fs::file_time_type dernierTemps;

    // Première phase : trouver le fichier le plus récent
    for (const auto& entry : fs::directory_iterator(dossier)) {
        if (fs::is_regular_file(entry)) {
            auto temps = fs::last_write_time(entry);
            if (dernierFichier.empty() || temps > dernierTemps) {
                dernierTemps = temps;
                dernierFichier = entry.path();
            }
        }
    }

    if (dernierFichier.empty()) {
        cout << "Aucun fichier trouvé dans le dossier." << endl;
        return;
    }

    cout << "Dernier fichier conservé : " << dernierFichier.filename() << endl;

    // Deuxième phase : supprimer les autres fichiers
    for (const auto& entry : fs::directory_iterator(dossier)) {
        if (fs::is_regular_file(entry) && entry.path() != dernierFichier) {
            try {
                fs::remove(entry);
                cout << "Supprimé : " << entry.path().filename() << endl;
            } catch (const fs::filesystem_error& e) {
                cout << "Erreur lors de la suppression de " << entry.path() << " : " << e.what() << endl;
            }
        }
    }
}