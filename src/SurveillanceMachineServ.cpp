#include "../include/SurveillanceMachineServ.h"

using namespace std;

SurveillanceMachine::SurveillanceMachine()
{
}

SurveillanceMachine::~SurveillanceMachine()
{
}

void SurveillanceMachine::gererReceptionTemperature()
{
}

void SurveillanceMachine::gererReceptionSeuils()
{
}

void SurveillanceMachine::gererEtatApprentissage()
{
}

void SurveillanceMachine::enregistrerAmbiance(DatabaseManager *base)
{
}

void SurveillanceMachine::enregistrerEvenement(DatabaseManager *base)
{
}

void SurveillanceMachine::setEtatReseau(EtatReseau etatReseau)
{
}

void SurveillanceMachine::publierSeuils(int machineId, float seuils)
{
}

void SurveillanceMachine::publierApprentissage()
{
}

void SurveillanceMachine::modifierTemperature(int numMachine)
{
}

string SurveillanceMachine::releverDateTime()
{
}

void SurveillanceMachine::reprendreDerniereDonneesTemp()
{
}

void SurveillanceMachine::modifierEvenement(int numMachine)
{
}