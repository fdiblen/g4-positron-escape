
#include "positronEscapeSimulationInfo.hh"

#include "G4UIcommand.hh"

#include "G4Run.hh"
#include "G4RunManager.hh"

positronEscapeSimulationInfo* positronEscapeSimulationInfo::instance = 0;

positronEscapeSimulationInfo::positronEscapeSimulationInfo():nStopped(0)
{

}

positronEscapeSimulationInfo::~positronEscapeSimulationInfo()
{

}

positronEscapeSimulationInfo* positronEscapeSimulationInfo::GetInstance()
{
	if (instance == 0) instance = new positronEscapeSimulationInfo;
	return instance;
}





