#include "MyPrimaryGenerator.hh"

MyPrimaryGenerator::MyPrimaryGenerator() :G4VUserPrimaryGeneratorAction(), fParticleGun(0)
{
	fParticleGun = new G4ParticleGun();
}

MyPrimaryGenerator::~MyPrimaryGenerator()
{
	delete fParticleGun;
}

void MyPrimaryGenerator::GeneratePrimaries(G4Event *event)
{
	G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
  fParticleGun->SetParticleDefinition(particleTable->FindParticle("gamma"));

	G4ThreeVector pos1(0., -1.5*cm, -5.3*cm); // source position
	fParticleGun->SetParticlePosition(pos1);

	G4double random = G4UniformRand();

  G4double cosTheta = 2*G4UniformRand() - 1., phi = twopi*G4UniformRand();
  G4double sinTheta = std::sqrt(1. - cosTheta*cosTheta);
  G4double ux = sinTheta*std::cos(phi),
  uy = sinTheta*std::sin(phi),
  uz = cosTheta;

	//fParticleGun->SetParticleEnergy(.6616553*MeV);
	//fParticleGun->SetParticleEnergy(1.*MeV);
	
  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(ux,uy,uz));
  //fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0.,0.,1.));
	
	double odds = G4UniformRand();
	
  fParticleGun->SetParticleEnergy(511.*keV);
  fParticleGun->GeneratePrimaryVertex(event);
  
  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(-ux, -uy, -uz));
  fParticleGun->SetParticleEnergy(511.*keV);
  fParticleGun->GeneratePrimaryVertex(event);
	
	if (odds < 130./180.)
	{
	  
    G4double cosTheta1 = 2*G4UniformRand() - 1., phi1 = twopi*G4UniformRand();
    G4double sinTheta1 = std::sqrt(1. - cosTheta1*cosTheta1);
    G4double ux1 = sinTheta1*std::cos(phi1),
    uy1 = sinTheta1*std::sin(phi1),
    uz1 = cosTheta1;
  
	  fParticleGun->SetParticleEnergy(1274.577*keV);
    fParticleGun->SetParticleMomentumDirection(G4ThreeVector(ux1,uy1,uz1));
    fParticleGun->GeneratePrimaryVertex(event);
	}
	
}
