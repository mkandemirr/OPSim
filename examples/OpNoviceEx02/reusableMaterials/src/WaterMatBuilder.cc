#include "WaterMatBuilder.hh"

#include "G4Material.hh"
#include "MaterialPropertiesTable.hh"
#include "G4UImanager.hh"
#include "G4NistManager.hh"
//#include "MaterialConstructionStore.hh"
//#include "MaterialManager.hh"
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

WaterMatBuilder::WaterMatBuilder(G4bool enableOpticalProperty):
VMaterialBuilder(enableOpticalProperty) 
{
  if(enableOpticalProperty)
  {
    pMatPropTable = new MaterialPropertiesTable("water"); 
    
    G4UImanager* uImanager = G4UImanager::GetUIpointer();
    uImanager->ApplyCommand("/control/execute reusableMaterials/macros/water.mac");  
  }
  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

WaterMatBuilder::~WaterMatBuilder()
{ 
  if(pMatPropTable) delete pMatPropTable;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4Material* WaterMatBuilder::Build()          
{ 
  G4double a,z,density;
  G4int nelements;
  
  G4Element* H = new G4Element("Hydrogen", "H", z = 1, a = 1.01 * g / mole);
  G4Element* O = new G4Element("Oxygen", "O", z = 8, a = 16.00 * g / mole);
  
  G4Material* water = new G4Material("Water", density = 1.0 * g / cm3, nelements = 2);
  water->AddElement(H, 2);
  water->AddElement(O, 1);
  
  return water;
  
}

