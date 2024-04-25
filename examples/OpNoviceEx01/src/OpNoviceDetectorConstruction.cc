//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
/// \file OpNovice/src/OpNoviceDetectorConstruction.cc
/// \brief Implementation of the OpNoviceDetectorConstruction class
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "OpNoviceDetectorConstruction.hh"
//#include "OpNoviceDetectorMessenger.hh"

#include "G4Box.hh"
#include "G4Element.hh"
#include "G4GDMLParser.hh"
#include "G4LogicalBorderSurface.hh"
#include "G4LogicalSkinSurface.hh"
#include "G4LogicalVolume.hh"
#include "G4Material.hh"
#include "G4OpticalSurface.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4ThreeVector.hh"

//Added by MK
#include "G4UImanager.hh"
#include "MaterialPropertiesTable.hh"
#include "OpticalSurface.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
OpNoviceDetectorConstruction::OpNoviceDetectorConstruction()
  : G4VUserDetectorConstruction()
{
  fDumpGdmlFileName = "OpNovice_dump.gdml";
  fVerbose          = false;
  fDumpGdml         = false;
  // create a messenger for this class
  //fDetectorMessenger = new OpNoviceDetectorMessenger(this);
  fWorld_x = fWorld_y = fWorld_z = 15.0 * m;
  fExpHall_x = fExpHall_y = fExpHall_z = 10.0 * m;
  fTank_x = fTank_y = fTank_z = 5.0 * m;
  fBubble_x = fBubble_y = fBubble_z = 0.5 * m;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
OpNoviceDetectorConstruction::~OpNoviceDetectorConstruction()
{
  //delete fDetectorMessenger;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
G4VPhysicalVolume* OpNoviceDetectorConstruction::Construct()
{
  G4bool checkOverlaps = true;
  // ------------- Materials -------------
  G4double a, z, density;
  G4int nelements;

  // Air
  G4Element* N = new G4Element("Nitrogen", "N", z = 7, a = 14.01 * g / mole);
  G4Element* O = new G4Element("Oxygen", "O", z = 8, a = 16.00 * g / mole);
  G4Material* air =
    new G4Material("Air", density = 1.29 * mg / cm3, nelements = 2);
  air->AddElement(N, 70. * perCent);
  air->AddElement(O, 30. * perCent);
  //
  // Water
  G4Element* H = new G4Element("Hydrogen", "H", z = 1, a = 1.01 * g / mole);
  G4Material* water =
    new G4Material("Water", density = 1.0 * g / cm3, nelements = 2);
  water->AddElement(H, 2);
  water->AddElement(O, 1);

  //**********Usage of OPSim classes*********************//
  G4UImanager* uImanager = G4UImanager::GetUIpointer(); 
  
  //water
  MaterialPropertiesTable* myMPT1 = new MaterialPropertiesTable("water");
  uImanager->ApplyCommand("/control/execute macros/mpt/water.mac");
  myMPT1->DumpTable();
  
  water->SetMaterialPropertiesTable(myMPT1); // equivalent to myMPT1->AddPropertiesToMaterial(water);
  water->GetIonisation()->SetBirksConstant(0.126 * mm / MeV);
  
  //air
  MaterialPropertiesTable* myMPT2 = new MaterialPropertiesTable("air");
  uImanager->ApplyCommand("/control/execute macros/mpt/"+myMPT2->GetName()+".mac");
  
  myMPT2->AddPropertiesToMaterial(air); // equivalent to air->SetMaterialPropertiesTable(myMPT2);
  //*******************************************************//
  
  
  // ------------- Volumes --------------
  //
  // The world
  G4Box* world_box = new G4Box("World", fWorld_x, fWorld_y, fWorld_z);
  G4LogicalVolume* world_log =
    new G4LogicalVolume(world_box, air, "World", 0, 0, 0);
  G4VPhysicalVolume* world_phys = new G4PVPlacement(
    0, G4ThreeVector(), world_log, "world", 0, false, 0, checkOverlaps);

  // The experimental Hall
  G4Box* expHall_box = new G4Box("expHall", fExpHall_x, fExpHall_y, fExpHall_z);
  G4LogicalVolume* expHall_log =
    new G4LogicalVolume(expHall_box, air, "expHall", 0, 0, 0);
  G4VPhysicalVolume* expHall_phys = new G4PVPlacement(
    0, G4ThreeVector(), expHall_log, "expHall", world_log, false, 0);

  // The Water Tank
  G4Box* waterTank_box = new G4Box("Tank", fTank_x, fTank_y, fTank_z);
  G4LogicalVolume* waterTank_log =
    new G4LogicalVolume(waterTank_box, water, "Tank", 0, 0, 0);
  G4VPhysicalVolume* waterTank_phys = new G4PVPlacement(
    0, G4ThreeVector(), waterTank_log, "Tank", expHall_log, false, 0);

  // The Air Bubble
  G4Box* bubbleAir_box = new G4Box("Bubble", fBubble_x, fBubble_y, fBubble_z);
  G4LogicalVolume* bubbleAir_log =
    new G4LogicalVolume(bubbleAir_box, air, "Bubble", 0, 0, 0);
  new G4PVPlacement(0, G4ThreeVector(0, 2.5 * m, 0), bubbleAir_log, "Bubble",
                    waterTank_log, false, 0);

  // ------------- Surfaces --------------

  //**********Usage of OPSim classes*********************//
  OpticalSurface* opWaterSurface = new OpticalSurface("waterSurface");
  uImanager->ApplyCommand("/control/execute macros/os/waterSurface.mac");
  //********************************************************//
  
  
  G4LogicalBorderSurface* waterSurface = new G4LogicalBorderSurface(
    "WaterSurface", waterTank_phys, expHall_phys, opWaterSurface);

  G4OpticalSurface* opticalSurface = dynamic_cast<G4OpticalSurface*>(
    waterSurface->GetSurface(waterTank_phys, expHall_phys)
      ->GetSurfaceProperty());
  if(opticalSurface)
    opticalSurface->DumpInfo();

  //**********Usage of OPSim classes*********************//
  OpticalSurface* opAirSurface = new OpticalSurface("airSurface");
  uImanager->ApplyCommand("/control/execute macros/os/airSurface.mac");
  //********************************************************//
  
  
  G4LogicalSkinSurface* airSurface =
    new G4LogicalSkinSurface("AirSurface", bubbleAir_log, opAirSurface);

  opticalSurface = dynamic_cast<G4OpticalSurface*>(
    airSurface->GetSurface(bubbleAir_log)->GetSurfaceProperty());
  if(opticalSurface)
    opticalSurface->DumpInfo();


  //**********Usage of OPSim classes*********************//
  MaterialPropertiesTable* myST2 = new MaterialPropertiesTable("optAirSurface");
  uImanager->ApplyCommand("/control/execute macros/mpt/optAirSurface.mac");
  //********************************************************//
    
  if(fVerbose)
  {
    G4cout << "Air Surface G4MaterialPropertiesTable:" << G4endl;
    myST2->DumpTable();
  }
  //opAirSurface->SetMaterialPropertiesTable(myST2);
  myST2->AddPropertiesToSurface(opAirSurface);

  if(fDumpGdml)
  {
    G4GDMLParser* parser = new G4GDMLParser();
    parser->Write(fDumpGdmlFileName, world_phys);
  }

  ////////////////////////////////////////////////////////////////////////////
  // test user-defined properties
  G4String ed;
  if(myMPT1->GetProperty("USERDEFINED") != nullptr)
  {
    ed = "USERDEFINED != nullptr";
    PrintError(ed);
  }
  
  //**********Usage of OPSim classes*********************//
  uImanager->ApplyCommand("/mpt/water/addProperty USERDEFINED data/mpt/water/miegh.txt eV m true true");
  //********************************************************//
  
 
  if(myMPT1->GetProperty("USERDEFINED") == nullptr)
  {
    ed = "USERDEFINED == nullptr";
    PrintError(ed);
  }
  [[maybe_unused]] G4int index_userdefined = -1;
  if(myMPT1->GetProperty("USERDEFINED") != nullptr)
  {
    index_userdefined = myMPT1->GetPropertyIndex("USERDEFINED");
  }
  if(!(index_userdefined >= 0 &&
        index_userdefined <
        (G4int) myMPT1->GetMaterialPropertyNames().size()))
  {
    ed = "USERDEFINED index out of range";
    PrintError(ed);
  }
  myMPT1->RemoveProperty("USERDEFINED");
  if(myMPT1->GetProperty("USERDEFINED") != nullptr)
  {
    ed = "USERDEFINED != nullptr at end";
    PrintError(ed);
  }

  if(myMPT1->ConstPropertyExists("USERDEFINEDCONST") == true)
  {
    ed = "ConstProperty USERDEFINEDCONST already exists.";
    PrintError(ed);
  }
  myMPT1->AddConstProperty("USERDEFINEDCONST", 3.14, true);
  if(myMPT1->ConstPropertyExists("USERDEFINEDCONST") == false)
  {
    ed = "ConstProperty USERDEFINEDCONST doesn't exist.";
    PrintError(ed);
  }
  [[maybe_unused]] G4int index_pi = -1;
  if(myMPT1->ConstPropertyExists("USERDEFINEDCONST") == true)
  {
    index_pi = myMPT1->GetConstPropertyIndex("USERDEFINEDCONST");
  }
  if (!(index_pi >= 0 &&
         index_pi < (G4int) myMPT1->GetMaterialConstPropertyNames().size()))
  {
    ed = "ConstProperty USERDEFINEDCONST index out of range.";
    PrintError(ed);
  }
  myMPT1->RemoveConstProperty("USERDEFINEDCONST");
  if (myMPT1->ConstPropertyExists("USERDEFINEDCONST") == true)
  {
    ed = "ConstProperty USERDEFINEDCONST still exists.";
    PrintError(ed);
  }
  // done testing user-defined properties
  ////////////////////////////////////////////////////////////////////////////

  return world_phys;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void OpNoviceDetectorConstruction::SetDumpGdml(G4bool val) { fDumpGdml = val; }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
G4bool OpNoviceDetectorConstruction::IsDumpGdml() const { return fDumpGdml; }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void OpNoviceDetectorConstruction::SetVerbose(G4bool val) { fVerbose = val; }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
G4bool OpNoviceDetectorConstruction::IsVerbose() const { return fVerbose; }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void OpNoviceDetectorConstruction::SetDumpGdmlFile(G4String filename)
{
  fDumpGdmlFileName = filename;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
G4String OpNoviceDetectorConstruction::GetDumpGdmlFile() const
{
  return fDumpGdmlFileName;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void OpNoviceDetectorConstruction::PrintError(G4String ed)
{
  G4Exception("OpNoviceDetectorConstruction:MaterialProperty test", "op001",
              FatalException, ed);
}
