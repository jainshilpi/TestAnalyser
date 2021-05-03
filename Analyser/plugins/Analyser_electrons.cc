#include "DataFormats/EgammaCandidates/interface/GsfElectron.h"
#include "DataFormats/GsfTrackReco/interface/GsfTrackFwd.h"
#include "DataFormats/EcalDetId/interface/ESDetId.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "RecoEcal/EgammaCoreTools/interface/EcalClusterLazyTools.h"
#include "RecoEgamma/EgammaTools/interface/ConversionTools.h"

#include "TestAnalyser/Analyser/interface/Analyser.h"

using namespace std;
using namespace reco;

// (local) variables associated with tree branches
Int_t          nEle_;
vector<int>    eleCharge_;
vector<int>    eleChargeConsistent_;
vector<float>  eleEn_;

vector<float>  eleEta_;
vector<float>  elePt_;
vector<float>  elePhi_;
vector<float>  eleR9_;
vector<UShort_t>  eleIDbit_;


void Analyser::branchesElectrons(TTree* tree) {

  tree->Branch("nEle",                    &nEle_);
  tree->Branch("eleEn",                   &eleEn_);
  tree->Branch("elePt",                   &elePt_);

  tree->Branch("eleEta",                  &eleEta_);
  tree->Branch("elePhi",                  &elePhi_);
  tree->Branch("eleR9",                   &eleR9_);
  tree->Branch("eleIDbit",                    &eleIDbit_);
  
}

void Analyser::fillElectrons(const edm::Event &e, const edm::EventSetup &es) {
    
  //bool debug = true;
  bool debug = false;
  // cleanup from previous execution
  eleCharge_                  .clear();
  eleEn_                      .clear();
  elePt_                      .clear();
  eleEta_                     .clear();
  elePhi_                     .clear();
  eleR9_                      .clear();
  eleIDbit_                   .clear();
  
  nEle_ = 0;

  if(debug) std::cout<<"gettign electron handle"<<std::endl;


  edm::Handle<edm::View<pat::Electron> > electronHandle;
  e.getByToken(electronCollection_, electronHandle);

  if (!electronHandle.isValid()) {
    edm::LogWarning("Analyser") << "no pat::Electrons in event";
    return;
  }



  for (edm::View<pat::Electron>::const_iterator iEle = electronHandle->begin(); iEle != electronHandle->end(); ++iEle) {

    eleCharge_          .push_back(iEle->charge());
    eleEn_              .push_back(iEle->energy());
    elePt_              .push_back(iEle->pt());
    eleEta_             .push_back(iEle->eta());
    elePhi_             .push_back(iEle->phi());
    eleR9_              .push_back(iEle->r9());
    // VID decisions 
    UShort_t tmpeleIDbit = 0;   
    bool isPassVeto   = iEle->electronID("cutBasedElectronID-Fall17-94X-V2-veto");
    if (isPassVeto)   setbit(tmpeleIDbit, 0);    
    bool isPassLoose  = iEle->electronID("cutBasedElectronID-Fall17-94X-V2-loose");
    if (isPassLoose)  setbit(tmpeleIDbit, 1);   
    bool isPassMedium = iEle->electronID("cutBasedElectronID-Fall17-94X-V2-medium");
    if (isPassMedium) setbit(tmpeleIDbit, 2);    
    bool isPassTight  = iEle->electronID("cutBasedElectronID-Fall17-94X-V2-tight");
    if (isPassTight)  setbit(tmpeleIDbit, 3);    
    bool isPassHEEP   = iEle->electronID("heepElectronID-HEEPV70");
    if (isPassHEEP)   setbit(tmpeleIDbit, 4);

    
    eleIDbit_.push_back(tmpeleIDbit);

    
    ///other IDs
    std::cout<<"========New electron IDs======="<<std::endl;

    cout<<"Ele HtoZZ 16 id "<<iEle->electronID("mvaEleID-Summer16UL-ID-ISO-HZZ")<<endl;
    cout<<"Ele HtoZZ 17 id "<<iEle->electronID("mvaEleID-Summer17UL-ID-ISO-HZZ")<<endl;
    cout<<"Ele HtoZZ 18 id "<<iEle->electronID("mvaEleID-Summer18UL-ID-ISO-HZZ")<<endl;
    nEle_++;
  }

  if(debug) std::cout<<"Done with electron handle"<<std::endl;

    
}
