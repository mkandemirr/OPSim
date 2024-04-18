#include "VMaterialBuilder.hh"
#include "G4Material.hh"
#include "G4NistManager.hh"
#include "MaterialPropertiesTable.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

VMaterialBuilder::VMaterialBuilder(G4bool enableOpticalProperty) : 
pNistManager{G4NistManager::Instance()},
bEnableOpticalProperty{enableOpticalProperty},
pMatPropTable{nullptr}
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

VMaterialBuilder::~VMaterialBuilder()
{ 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

//Template method.
G4Material* VMaterialBuilder::GetProduct()
{
  G4Material* mat = Build();
  
  if(IsOpticalPropertyEnabled())
  {
    mat->SetMaterialPropertiesTable(pMatPropTable);
  }
    
  return mat;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

