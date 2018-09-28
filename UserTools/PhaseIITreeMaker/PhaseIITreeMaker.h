#ifndef PhaseIITreeMaker_H
#define PhaseIITreeMaker_H

#include <string>
#include <iostream>

#include "Tool.h"
// ROOT includes
#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"

class PhaseIITreeMaker: public Tool {


 public:

  PhaseIITreeMaker();
  bool Initialise(std::string configfile,DataModel &data);
  bool Execute();
  bool Finalise();


 private:
 	/// \brief Reset all variables. 
 	void ResetVariables();
 	
 	/// \brief Summary of Reconstructed vertex
 	void RecoSummary();
 	
 	/// \brief ROOT TFile that will be used to store the output from this tool
  TFile* fOutput_tfile = nullptr;

  /// \brief TTree that will be used to store output
  TTree* fRecoTree = nullptr;
  
  
  /// \brief Branch variables
  
  /// \brief MC entry number
  uint64_t fMCEventNum;
  
  /// \brief trigger number
  uint16_t fMCTriggerNum;
  
  /// \brief ANNIE event number
  uint32_t fEventNumber;
  
  // Digits
  int fNhits = 0;
  std::vector<int> fIsFiltered;
  std::vector<double> fDigitX;
  std::vector<double> fDigitY;
  std::vector<double> fDigitZ;
  std::vector<double> fDigitT;
  std::vector<double> fDigitQ;    
  std::vector<int> fDigitType;
  	
  // True muon
  double fTrueVtxX;
  double fTrueVtxY;
  double fTrueVtxZ;
  double fTrueVtxTime;
  double fTrueDirX;
  double fTrueDirY;
  double fTrueDirZ;
  double fTrueTheta;
  double fTruePhi;
  double fTrueEnergy; 

  // Seed vertex
  std::vector<double> fSeedVtxX;
  std::vector<double> fSeedVtxY;
  std::vector<double> fSeedVtxZ;

  // Reco vertex
  // Point Position Vertex
  double fPointPosX;
  double fPointPosY;
  double fPointPosZ;
  double fPointPosTime;
  double fPointPosFOM;
  double fPointDirX;
  double fPointDirY;
  double fPointDirZ;
  double fPointDirTime;
  double fPointDirFOM;
  double fPointVtxFOM;
  
  // Vertex
  double fRecoVtxX;
  double fRecoVtxY;
  double fRecoVtxZ;
  double fRecoVtxTime;
  double fRecoDirX;
  double fRecoDirY;
  double fRecoDirZ;
  double fRecoVtxFOM;
  double fRecoTheta;
  double fRecoPhi;
  int fRecoStatus;
  
  //histograms
  double fDeltaVtxX; 
  double fDeltaVtxY;
  double fDeltaVtxZ;
  double fDeltaVtxR;
  double fDeltaVtxT;
  double fDeltaParallel;
  double fDeltaPerpendicular;
  double fDeltaAzimuth;
  double fDeltaZenith;  
  double fDeltaAngle;
  
  	
  /// \brief Integer that determines the level of logging to perform
  int verbosity = 0;
  int v_error=0;
  int v_warning=1;
  int v_message=2;
  int v_debug=3;
  std::string logmessage;		
  int get_ok;	

  /// \Integer flags that control additional output to the PhaseIITree
  int muonMCTruth_fill = 0; //Output the MC truth information
  int muonRecoDebug_fill = 0; //Outputs results of Reconstruction at each step (best fits, FOMs, etc.)
  int muonTruthRecoDiff_fill = 0; //Output difference in truth and reconstructed values
};


#endif
