#ifndef VMaterialFactory_h
#define VMaterialFactory_h 1

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "globals.hh"
#include "G4Material.hh"

class VMaterialFactory
{
  public:
    VMaterialFactory();
    virtual ~VMaterialFactory();
     
  public:     
    //This method internally invokes the factory method.                          
    G4Material* GetMaterial(const G4String& name, 
                            G4bool enableOpticalProperty = false
                            );
                            
  protected: 
    virtual G4Material* CreateMaterial(const G4String& name, 
                                       G4bool enableOpticalProperty
                                       ) = 0;               
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif 
