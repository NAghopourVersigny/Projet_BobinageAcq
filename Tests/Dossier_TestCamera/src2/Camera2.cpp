#include "../include/Camera.h"

using namespace std;
using namespace std::filesystem;

Camera::Camera(string hostname)
{
    this->flir = new FLIR_AX8(hostname);
    cout << hostname << endl;
}

Camera::~Camera()
{
    // Destructeur
    delete flir;
}

float Camera::obtenirTempMoy()
{
    int valeur = flir->acquerirTempMoy();
    cout << valeur << endl;
    float mantisse, exposant, kelvin;
    int sign = valeur >> 31;
    mantisse = (valeur & 0x7FFFFF) | 0X800000;
    exposant = ((valeur >> 23) & 0xFF) - 127 - 23;
    kelvin = mantisse * pow(2.0, exposant);
    float degree = kelvin - 273.15;
    temperatureMoyImage = degree;
    return degree;
}

float Camera::obtenirTempMin()
{
    float mantisse, exposant, kelvin;
    int valeur = flir->acquerirTempMin();
    int sign = valeur >> 31;
    mantisse = (valeur & 0x7FFFFF) | 0X800000;
    exposant = ((valeur >> 23) & 0xFF) - 127 - 23;
    kelvin = mantisse * pow(2.0, exposant);
    float degree = kelvin - 273.15;
    return degree;
}

float Camera::obtenirTempMax()
{
    float mantisse, exposant, kelvin;
    int valeur = flir->acquerirTempMax();
    int sign = valeur >> 31;
    mantisse = (valeur & 0x7FFFFF) | 0X800000;
    exposant = ((valeur >> 23) & 0xFF) - 127 - 23;
    kelvin = mantisse * pow(2.0, exposant);
    float degree = kelvin - 273.15;
    temperatureMaxImage = degree;
    return degree;
}

string Camera::obtenir_nom_image()
{
    /*string chemin = "/var/www/html/img/";
    string nom;
    if (std::filesystem::exists(chemin) && std::filesystem::is_directory(chemin))
    {
        // Loop through each item (file or subdirectory) in
        // the directory
        for (const auto &entry :
            std::filesystem::__cxx11::directory_iterator(chemin))
        {
            // Output the path of the file or subdirectory
             nom = entry.path() ;
        }
    }
    return nom;*/
    /*std::string chemin = "/var/www/html/img/";
    std::string nom;
    std::regex pattern("img_.*\\.jpg");  // Regex pattern for img_*.jpg

    if (fs::exists(chemin) && fs::is_directory(chemin))
    {
        // Loop through each item (file or subdirectory) in the directory
        for (const auto &entry : fs::directory_iterator(chemin))
        {
            // Check if the entry is a regular file and matches the pattern
            if (fs::is_regular_file(entry.status()))
            {
                std::string filename = entry.path().filename().string();
                if (std::regex_match(filename, pattern))
                {
                    nom = filename;  // or entry.path().string() if full path is needed
                    //break;  // Stop after finding the first match
                
            }
        }
    }
    return nom;*/
    std::string chemin = "/var/www/html/img/";
    std::string nom;
    std::regex pattern("img_.*\\.jpg");  // Regex pattern for img_*.jpg
    std::filesystem::file_time_type latest_time;

    if (fs::exists(chemin) && fs::is_directory(chemin))
    {
        // Loop through each item (file or subdirectory) in the directory
        for (const auto &entry : fs::directory_iterator(chemin))
        {
            // Check if the entry is a regular file and matches the pattern
            if (fs::is_regular_file(entry.status()))
            {
                std::string filename = entry.path().filename().string();
                if (std::regex_match(filename, pattern))
                {
                    auto ftime = fs::last_write_time(entry);
                    if (nom.empty() || ftime > latest_time)
                    {
                        latest_time = ftime;
                        nom = filename;  // or entry.path().string() if full path is needed
                    }
                }
            }
        }
    }
    return nom;
}

void Camera::capturer_Image()
{
    flir->store_Image();
}

void Camera::recuperer_Image()
{
    flir->requerir_Image();
}
