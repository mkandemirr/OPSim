#ifndef WaterMatBuilder_h
#define WaterMatBuilder_h 1

#include "VMaterialBuilder.hh"

class G4Material;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class WaterMatBuilder: public VMaterialBuilder{

  public:
    WaterMatBuilder(G4bool enableMPT = false); 
    virtual ~WaterMatBuilder();

    virtual G4Material* Build() override;
       
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

