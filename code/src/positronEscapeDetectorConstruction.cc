#include "positronEscapeDetectorConstruction.hh"

#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Cons.hh"
#include "G4Orb.hh"
#include "G4Sphere.hh"
#include "G4Trd.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"

#include "G4Tubs.hh"

#include "G4Transform3D.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"

#include "G4RotationMatrix.hh"

#include "G4Element.hh"
#include "G4Material.hh"


positronEscapeDetectorConstruction::positronEscapeDetectorConstruction()
: G4VUserDetectorConstruction(),
  fScoringVolume(0)
{ }

positronEscapeDetectorConstruction::~positronEscapeDetectorConstruction()
{ }

G4VPhysicalVolume* positronEscapeDetectorConstruction::Construct()
{  
  // Get nist material manager
  G4NistManager* nist = G4NistManager::Instance();
  
  // Option to switch on/off checking of volumes overlaps
  //
  G4bool checkOverlaps = true;

  //     
  // World
  //
  G4Material* world_mat = nist->FindOrBuildMaterial("G4_AIR");
  
  G4double worldSize = 4 * m;

  G4Box* solidWorld =    
    new G4Box("World",                       //its name
       worldSize, worldSize, worldSize);     //its size
      
  G4LogicalVolume* logicWorld =                         
    new G4LogicalVolume(solidWorld,          //its solid
                        world_mat,           //its material
                        "World");            //its name
                                   
  G4VPhysicalVolume* physWorld = 
    new G4PVPlacement(0,                     //no rotation
                      G4ThreeVector(),       //at (0,0,0)
                      logicWorld,            //its logical volume
                      "World",               //its name
                      0,                     //its mother  volume
                      false,                 //no boolean operation
                      0,                     //copy number
                      checkOverlaps);        //overlaps checking
                     




  // Target
  //  
  //G4double target_radius = 25 * mm;
  //G4double target_dZ = 70 * mm;


  G4double target_radius = 2 * m;
  G4double target_dZ = 2 * m;

  G4Material* target_mat = nist->FindOrBuildMaterial("G4_WATER");

  //G4String name, symbol;
  //G4double a, z, density;
  //density = 1.72*g/cm3;
  //a = 12.01*g/mole;
  //G4Material* target_mat = new G4Material(name="CarbonKVI", z=6., a, density);



  G4Tubs* solidTarget =
    new G4Tubs("Target", 0., target_radius, 0.5*target_dZ, 0., CLHEP::twopi);

  G4LogicalVolume* logicTarget =
    new G4LogicalVolume(solidTarget,        //its solid
                        target_mat,         //its material
                        "TargetLV");        //its name

    //G4double phi = icrys*dPhi;
    G4RotationMatrix rotm  = G4RotationMatrix();
    rotm.rotateX(90*deg);
    //rotm.rotateY(90*deg);
    //rotm.rotateZ(phi);
    //G4ThreeVector uz = G4ThreeVector(std::cos(phi),  std::sin(phi),0.);
    G4ThreeVector position = G4ThreeVector(0., 0.,0.);
    G4Transform3D transform = G4Transform3D(rotm,position);


new G4PVPlacement(transform,             //rotation,position
                      logicTarget,            //its logical volume
                      "Target",             //its name
                      logicWorld,             //its mother  volume
                      false,                 //no boolean operation
                      0,                 //copy number
                      checkOverlaps);       // checking overlaps



  // visualization
  G4Colour trans_yellow(1.0, 1.0, 0.0, 0.7); // yellow
  G4Colour trans_red(1.0, 0.0, 0.0, 0.8); // red

  G4VisAttributes* PhantomVisAtt = new G4VisAttributes(trans_yellow);
  PhantomVisAtt->SetVisibility(true);
  PhantomVisAtt->SetForceSolid(true);
//PhantomVisAtt->SetForceWireframe(true);
  PhantomVisAtt->SetForceAuxEdgeVisible(false);


  logicTarget->SetVisAttributes(PhantomVisAtt);

  // Print materials
  G4cout << *(G4Material::GetMaterialTable()) << G4endl;
  
  // Set Shape2 as scoring volume
  //
  fScoringVolume = logicTarget;

  //
  //always return the physical World
  //
  return physWorld;
}
