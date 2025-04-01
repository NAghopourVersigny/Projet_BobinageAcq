#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>

#define HYT221_ADDR 0x28   // Adresse I2C du capteur HYT221
#define CMD_READ_HUM_TEMP 



// Fonction pour ouvrir la connexion I2C et obtenir un descripteur de fichier
int openI2C(const char *device, int address) {
    int file;
    
    // Ouvrir le périphérique I2C
    if ((file = open(device, O_RDWR)) < 0) {
        perror("Erreur : impossible d'ouvrir le bus I2C");
        exit(1);
    }

    // Configurer l'adresse du périphérique I2C
    if (ioctl(file, I2C_SLAVE, address) < 0) {
        perror("Erreur : impossible de configurer l'adresse du périphérique I2C");
        exit(1);
    }

    return file;
}

// Fonction pour lire les données du capteur
void read_HYT221_data(int file) {
    unsigned char data[4];
    int temp_raw, hum_raw;

    // Envoie de la commande pour lire les données du capteur
    if (write(file, &CMD_READ_HUM_TEMP, 1) != 1) {
        perror("Erreur : impossible d'envoyer la commande de lecture");
        exit(1);
    }

    // Attendre un peu pour que le capteur réponde (50ms)
    usleep(50000);

    // Lire les 4 octets retournés par le capteur (température + humidité)
    if (read(file, data, 4) != 4) {
        perror("Erreur : impossible de lire les données du capteur");
        exit(1);
    }

    // Extraction des valeurs brutes de température et d'humidité
    temp_raw = (data[0] << 8) | data[1];
    hum_raw = (data[2] << 8) | data[3];

    // Conversion des valeurs brutes en température et humidité
    float temperature = -40.0 + (165.0 * temp_raw / 65535.0);
    float humidity = 100.0 * hum_raw / 65535.0;

    // Afficher les résultats
    printf("Température : %.2f °C\n", temperature);
    printf("Humidité : %.2f %%\n", humidity);
}

int main() {
    const char *device = "/dev/i2c-1";  // Le périphérique I2C (généralement /dev/i2c-1 sur la Raspberry Pi)
    int file;

    // Ouvrir la connexion I2C avec l'adresse du capteur
    file = openI2C(device, HYT221_ADDR);

    // Lire les données du capteur toutes les secondes
    while (1) {
        read_HYT221_data(file);
        sleep(1);  // Attendre 1 seconde avant de lire à nouveau
    }

    // Fermer la connexion I2C (bien que cela ne soit pas vraiment nécessaire ici)
    close(file);

    return 0;
}
