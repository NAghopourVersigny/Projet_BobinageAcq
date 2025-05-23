/* Attention ! Classe de test*/
#include "../include/ina219.h"

#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>
#include <bitset>
#include <math.h>
#include <iostream>

using namespace std;

INA219::INA219(float shunt_resistance, float max_expected_amps)
{
	init_i2c(__ADDRESS);
	_shunt_ohms = shunt_resistance;
	_max_expected_amps = max_expected_amps;
	_min_device_current_lsb = __CALIBRATION_FACTOR / (_shunt_ohms * __MAX_CALIBRATION_VALUE);
}
INA219::INA219(float shunt_resistance, float max_expected_amps, uint8_t address)
{
	cout << " L'adresse configurée est : " << hex << (int)address << endl;
	init_i2c(address);
	_shunt_ohms = shunt_resistance;
	_max_expected_amps = max_expected_amps;
	_min_device_current_lsb = __CALIBRATION_FACTOR / (_shunt_ohms * __MAX_CALIBRATION_VALUE);
}
INA219::~INA219()
{
	cout << " Fermeture accès " << endl;
}

void INA219::init_i2c(uint8_t address)
{
	cout << "test appel méthode INA219 et conversion courant" << endl;
	cout << " Ouverture accès " << endl;

}

uint16_t INA219::read_register(uint8_t register_address)
{

	cout << " Lecture de l'adresse " << register_address << endl;
	return 256;
}
bool INA219::write_register(uint8_t register_address, uint16_t register_value)
{
	return true;
}

bool INA219::configure(int voltage_range, int gain, int bus_adc, int shunt_adc)
{
	cout << " Configuration de INA219 avec " << voltage_range << " " << gain << " " << bus_adc << " " << shunt_adc << "" << endl;
	return true;
}

void INA219::calibrate(int bus_volts_max, float shunt_volts_max, float max_expected_amps)
{
}
float INA219::determine_current_lsb(float max_expected_amps, float max_possible_amps)
{
	return 0;
}
void INA219::sleep()
{
}
void INA219::wake()
{
}
void INA219::reset()
{
}
float INA219::voltage()
{

	return 0;
}
float INA219::shunt_voltage()
{
	uint16_t shunt_voltage;

	return 0;
}
float INA219::supply_voltage()
{
	return voltage() + (shunt_voltage() / 1000.0);
}
float INA219::current()
{
	float current_mA;
	cout << "Saisissez un courant compris entre 4mA et 20mA." << endl;
	cout << "Veuillez saisir le courant en mA : 4 pour 4mA et 20 pour 20mA." << endl;
	cin >> current_mA;

	return current_mA;
}
float INA219::power()
{

	return 0;
}
