#include "../include/Camera.h"

using namespace std;
using namespace std::filesystem;

Camera::Camera(string hostname)
{
    this->flir = new FLIR_AX8(hostname);
}

Camera::~Camera()
{
    // Destructeur
    delete flir;
}

float Camera::obtenirTempMoy()
{
    int valeur = flir->acquerirTempMoy();
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

string Camera::obtenir_nom_image_IR()
{
    string chemin = "/var/www/html/img/";
    string nom;
    regex pattern("img_.*\\.jpg");  // Regex pattern for img_*.jpg
    filesystem::file_time_type latest_time;

    if (fs::exists(chemin) && fs::is_directory(chemin))
    {
        // Loop through each item (file or subdirectory) in the directory
        for (const auto &entry : fs::directory_iterator(chemin))
        {
            // Check if the entry is a regular file and matches the pattern
            if (fs::is_regular_file(entry.status()))
            {
                string filename = entry.path().filename().string();
                if (regex_match(filename, pattern))
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

string Camera::obtenir_nom_image_VISUAL()
{
    string chemin = "/var/www/html/img/";
    string nom;
    regex pattern("img_.*\\.jpg");  // Regex pattern for img_*.jpg
    filesystem::file_time_type latest_time;

    if (fs::exists(chemin) && fs::is_directory(chemin))
    {
        // Loop through each item (file or subdirectory) in the directory
        for (const auto &entry : fs::directory_iterator(chemin))
        {
            // Check if the entry is a regular file and matches the pattern
            if (fs::is_regular_file(entry.status()))
            {
                string filename = entry.path().filename().string();
                if (regex_match(filename, pattern))
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