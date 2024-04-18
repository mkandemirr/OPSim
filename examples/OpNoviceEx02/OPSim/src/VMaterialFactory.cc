#include "VMaterialFactory.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

VMaterialFactory::VMaterialFactory()
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

VMaterialFactory::~VMaterialFactory()
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4Material* VMaterialFactory::GetMaterial
(
  const G4String& name, 
  G4bool enableOpticalProperty
)
{
  //user-defined material
  G4Material* mat = CreateMaterial(name,enableOpticalProperty);
  //-----------
  if (!mat) 
  {
    std::ostringstream o;
    o << "Material " << name << " not found!";
    G4Exception("VMaterialFactory::GetMaterial()",
                "",
                FatalException,
                o.str().c_str()
                );
  }

  return mat;
}
