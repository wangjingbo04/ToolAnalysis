#include "VtxPointPositionFinder.h"

VtxPointPositionFinder::VtxPointPositionFinder():Tool(){}


bool VtxPointPositionFinder::Initialise(std::string configfile, DataModel &data){

  /////////////////// Usefull header ///////////////////////
  if(configfile!="")  m_variables.Initialise(configfile); //loading config file
  //m_variables.Print();

  m_data= &data; //assigning transient data pointer
  /////////////////////////////////////////////////////////////////
  
  /// Get the Tool configuration variables
	m_variables.Get("UseTrueVertexAsSeed",fUseTrueVertexAsSeed);


  fUseTrueVertexAsSeed = false;
  return true;
}

bool VtxPointPositionFinder::Execute(){
	Log("Executing tool VtxPointPositionFinder with MC entry ", v_message, verbosity);
	// Retrive digits from RecoEvent
	get_ok = m_data->Stores.at("RecoEvent")->Get("RecoDigit",fDigitList);  ///> Get digits from "RecoEvent" 
  if(not get_ok){
  	Log("VtxSeedGenerator  Tool: Error retrieving RecoDigits,no digit from the RecoEvent!",v_error,verbosity); 
  	return false;
  }
  
  // Load digits to VertexGeometry
  VertexGeometry* myvtxgeo = VertexGeometry::Instance();
  myvtxgeo->LoadDigits(fDigitList);
  
	// Do point position reconstruction using MC truth information
  if( fUseTrueVertexAsSeed ){
    Log("VtxPointPositionFinder Tool: Run vertex reconstruction using MC truth information",v_message,verbosity);
    // get truth vertex information 
    get_ok = m_data->Stores.at("RecoEvent")->Get("TrueVertex", fTrueVertex);
	  if(not get_ok){ 
		  Log("VtxPointPositionFinder Tool: Error retrieving TrueVertex from RecoEvent!",v_error,verbosity); 
		return false; 
	  }
	  Position vtxPos = fTrueVertex->GetPosition();
	  Direction vtxDir = fTrueVertex->GetDirection();
	  double vtxTime = fTrueVertex->GetTime();
	  //Set vertex seed
    RecoVertex* vtx = new RecoVertex();
	  vtx->SetVertex(vtxPos, vtxTime);
    vtx->SetDirection(vtxDir);
    // return vertex
    RecoVertex* myvertex  = (RecoVertex*)(this->FitPointVertex(vtx)); 
  }

  return true;
}


bool VtxPointPositionFinder::Finalise(){

  return true;
}

RecoVertex* VtxPointPositionFinder::FitPointVertex(RecoVertex* myvertex) {
	Log("VtxPointPositionFinder::FitPointVertex: Fit point vertex",v_message,verbosity);
	//fit with Minuit
  MinuitOptimizer* myOptimizer = new MinuitOptimizer();
  myOptimizer->SetPrintLevel(1);
  VertexGeometry* myvtxgeo = VertexGeometry::Instance();
  myOptimizer->LoadVertexGeometry(myvtxgeo); //Load vertex geometry
  myOptimizer->LoadVertex(myvertex); //Load vertex seed
  myOptimizer->FitPointVertexWithMinuit();
//  RecoVertex* newVertex = (RecoVertex*)(this->FixPointVertex(myOptimizer->GetFittedVertex())); 
  delete myOptimizer; myOptimizer = 0;
//  return newVertex;
  return 0;
}
