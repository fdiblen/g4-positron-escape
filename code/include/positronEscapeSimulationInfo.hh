
#ifndef positronEscapeSimulationInfo_HH
#define positronEscapeSimulationInfo_HH 1

#include "G4ios.hh"
#include "globals.hh"
#include "G4Polyline.hh"

#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <map>

#include "G4ThreeVector.hh"
#include "G4Track.hh"
#include "G4VProcess.hh"
#include "G4RunManager.hh"

using namespace std;


class positronEscapeSimulationInfo
{

    public:
        positronEscapeSimulationInfo();
        ~positronEscapeSimulationInfo();

        static positronEscapeSimulationInfo* GetInstance();


        //Main Set Methods
        void SetNstopped( G4int n ){nStopped = n;};
        void SetSourceID( G4int n ){sourceID = n;};

        //Main Get Methods
        G4int GetNstopped(){ return nStopped;};
        G4int GetSourceID(){ return sourceID;};


    private:

        static positronEscapeSimulationInfo* instance;

        G4int nStopped;
        G4int sourceID;


};

#endif

