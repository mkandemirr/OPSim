#ifndef AirMatBuilder_h
#define AirMatBuilder_h 1

#include "VMaterialBuilder.hh"

class G4Material;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class AirMatBuilder: public VMaterialBuilder{

  public:
    AirMatBuilder(G4bool enableOpticalProperty=false); 
    virtual ~AirMatBuilder();

    virtual G4Material* Build() override;
       
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

