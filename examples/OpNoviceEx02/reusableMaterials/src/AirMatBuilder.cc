#include "AirMatBuilder.hh"

#include "G4Material.hh"
#include "MaterialPropertiesTable.hh"
#include "G4UImanager.hh"
#include "G4NistManager.hh"
//#include "MaterialConstructionStore.hh"
//#include "MaterialManager.hh"
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

AirMatBuilder::AirMatBuilder(G4bool enableMPT):
VMaterialBuilder(enableMPT) 
{
  if(enableMPT)
  {
    pMPT = new MaterialPropertiesTable("air"); 
    
    G4UImanager* uImanager = G4UImanager::GetUIpointer();
    uImanager->ApplyCommand("/control/execute reusableMaterials/macros/air.mac");  
  }
  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

AirMatBuilder::~AirMatBuilder()
{ 
  if(pMPT) delete pMPT;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4Material* AirMatBuilder::Build()          
{ 
  G4double a,z,density;
  G4int nElements;
  
  G4Element* N = new G4Element("Nitrogen", "N", z = 7, a = 14.01 * g / mole);
  G4Element* O = new G4Element("Oxygen", "O", z = 8, a = 16.00 * g / mole);
  
  G4Material* air = new G4Material("Air", density = 1.29 * mg / cm3, nElements = 2);
  air->AddElement(N, 70. * perCent);
  air->AddElement(O, 30. * perCent);
  
  return air;
  
}

