#include "MyDetectorConstruction.hh"

MyDetectorConstruction::MyDetectorConstruction()
{	
	G4NistManager *nist = G4NistManager::Instance();

// Material for World (vacuum)
	G4Material *worldMat = nist->FindOrBuildMaterial("G4_Galactic");

// Material for Scintillator
	G4Material *matScint = nist->FindOrBuildMaterial("G4_CESIUM_IODIDE");

// Cell_World
	G4double dWorld = 40.*cm;

	solidWorld = new G4Box("solidWorld", dWorld, dWorld, dWorld);
	G4LogicalVolume *logicWorld = new G4LogicalVolume(solidWorld, worldMat, "logicWorld");
	physWorld = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicWorld, "physWorld", 0, false, 0, true); 

// Scintillator

  double x_length = 2.4*cm;
  double y_length = 2.4*cm;
  double z_length = 4.7*cm;
  
	// Scoring Scintillator
	G4Box* solidScint = new G4Box("solidScint", x_length/2, y_length/2, z_length/2);
	G4LogicalVolume *logicScint = new G4LogicalVolume(solidScint, matScint, "logicScint");
	G4VPhysicalVolume *physScint = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicScint, "physScint", logicWorld, false, 0, true);

// Select scoring volume
	fDEScoringVolume = logicScint;
}

MyDetectorConstruction::~MyDetectorConstruction()
{}

G4VPhysicalVolume *MyDetectorConstruction::Construct() 
{
	return physWorld;
}
