#include <TString.h>
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "RecoEcal/EgammaCoreTools/interface/EcalClusterLazyTools.h"
#include "TestAnalyser/Analyser/interface/Analyser.h"

using namespace std;

Int_t          nPho_;
vector<float>  phoE_;
vector<float>  phoSigmaE_;
vector<float>  phoEt_;
vector<float>  phoEta_;
vector<float>  phoPhi_;
vector<float>  phoCalibE_;
vector<float>  phoCalibEt_;
vector<float>  phoSCE_;
vector<float>  phoSCRawE_;
vector<float>  phoESEnP1_;
vector<float>  phoESEnP2_;
vector<float>  phoSCEta_;
vector<float>  phoSCPhi_;
vector<float>  phoSCEtaWidth_;
vector<float>  phoSCPhiWidth_;
vector<float>  phoSCBrem_;
vector<int>    phohasPixelSeed_;
vector<int>    phoEleVeto_;
vector<float>  phoR9_;
vector<float>  phoHoverE_;
vector<float>  phoESEffSigmaRR_;
vector<float>  phoSigmaIEtaIEtaFull5x5_;
vector<float>  phoSigmaIEtaIPhiFull5x5_;
vector<float>  phoSigmaIPhiIPhiFull5x5_;
vector<float>  phoE2x2Full5x5_;
vector<float>  phoE5x5Full5x5_;
vector<float>  phoR9Full5x5_;
vector<float>  phoPFChIso_;
vector<float>  phoPFPhoIso_;
vector<float>  phoPFNeuIso_;
vector<float>  phoPFChWorstIso_;
//vector<float>  phoSeedBCE_;
//vector<float>  phoSeedBCEta_;
vector<float>  phoIDMVA_;
vector<ULong64_t> phoFiredSingleTrgs_;
vector<ULong64_t> phoFiredDoubleTrgs_;
vector<ULong64_t> phoFiredTripleTrgs_;
vector<ULong64_t> phoFiredL1Trgs_;
vector<float>  phoSeedTime_;
vector<float>  phoSeedEnergy_;
//vector<float>  phoSeedTimeFull5x5_;
//vector<float>  phoMIPChi2_;
//vector<float>  phoMIPTotEnergy_;
//vector<float>  phoMIPSlope_;
//vector<float>  phoMIPIntercept_;
//vector<float>  phoMIPNhitCone_;
//vector<float>  phoMIPIsHalo_;
vector<UShort_t> phoxtalBits_;
vector<UShort_t> phoIDbit_;
vector<float>    phoScale_stat_up_;
vector<float>    phoScale_stat_dn_;
vector<float>    phoScale_syst_up_;
vector<float>    phoScale_syst_dn_;
vector<float>    phoScale_gain_up_;
vector<float>    phoScale_gain_dn_;
vector<float>    phoResol_rho_up_;
vector<float>    phoResol_rho_dn_;
vector<float>    phoResol_phi_up_;
vector<float>    phoResol_phi_dn_;

//Necessary for the Photon Footprint removal
template <class T, class U>
bool isInFootprint(const T& thefootprint, const U& theCandidate) {
  for ( auto itr = thefootprint.begin(); itr != thefootprint.end(); ++itr ) {

    if( itr.key() == theCandidate.key() ) return true;
    
  }
  return false;
}

void Analyser::branchesPhotons(TTree* tree) {
  
  tree->Branch("nPho",                    &nPho_);
  tree->Branch("phoE",                    &phoE_);
  tree->Branch("phoSigmaE",               &phoSigmaE_);
  tree->Branch("phoEt",                   &phoEt_);
  tree->Branch("phoEta",                  &phoEta_);
  tree->Branch("phoPhi",                  &phoPhi_);
  tree->Branch("phoCalibE",               &phoCalibE_);
  tree->Branch("phoCalibEt",              &phoCalibEt_);
  tree->Branch("phoSCE",                  &phoSCE_);
  tree->Branch("phoSCRawE",               &phoSCRawE_);
  tree->Branch("phoESEnP1",               &phoESEnP1_);
  tree->Branch("phoESEnP2",               &phoESEnP2_);
  tree->Branch("phoSCEta",                &phoSCEta_);
  tree->Branch("phoSCPhi",                &phoSCPhi_);
  tree->Branch("phoSCEtaWidth",           &phoSCEtaWidth_);
  tree->Branch("phoSCPhiWidth",           &phoSCPhiWidth_);
  tree->Branch("phoSCBrem",               &phoSCBrem_);
  tree->Branch("phohasPixelSeed",         &phohasPixelSeed_);
  tree->Branch("phoEleVeto",              &phoEleVeto_);
  tree->Branch("phoR9",                   &phoR9_);
  tree->Branch("phoHoverE",               &phoHoverE_);
  tree->Branch("phoESEffSigmaRR",         &phoESEffSigmaRR_);
  tree->Branch("phoSigmaIEtaIEtaFull5x5", &phoSigmaIEtaIEtaFull5x5_);
  tree->Branch("phoSigmaIEtaIPhiFull5x5", &phoSigmaIEtaIPhiFull5x5_);
  tree->Branch("phoSigmaIPhiIPhiFull5x5", &phoSigmaIPhiIPhiFull5x5_);
  tree->Branch("phoE2x2Full5x5",          &phoE2x2Full5x5_);
  tree->Branch("phoE5x5Full5x5",          &phoE5x5Full5x5_);
  tree->Branch("phoR9Full5x5",            &phoR9Full5x5_);
  //tree->Branch("phoSeedBCE",              &phoSeedBCE_);
  //tree->Branch("phoSeedBCEta",            &phoSeedBCEta_);
  tree->Branch("phoPFChIso",              &phoPFChIso_);
  tree->Branch("phoPFPhoIso",             &phoPFPhoIso_);
  tree->Branch("phoPFNeuIso",             &phoPFNeuIso_);
  tree->Branch("phoPFChWorstIso",         &phoPFChWorstIso_);
  tree->Branch("phoIDMVA",                &phoIDMVA_);
  tree->Branch("phoFiredSingleTrgs",      &phoFiredSingleTrgs_);
  tree->Branch("phoFiredDoubleTrgs",      &phoFiredDoubleTrgs_);
  tree->Branch("phoFiredTripleTrgs",      &phoFiredTripleTrgs_);
  tree->Branch("phoFiredL1Trgs",          &phoFiredL1Trgs_);
  tree->Branch("phoSeedTime",             &phoSeedTime_);
  tree->Branch("phoSeedEnergy",           &phoSeedEnergy_);
  //tree->Branch("phoSeedTimeFull5x5",              &phoSeedTimeFull5x5_);
  //tree->Branch("phoMIPChi2",                      &phoMIPChi2_);
  //tree->Branch("phoMIPTotEnergy",                 &phoMIPTotEnergy_);
  //tree->Branch("phoMIPSlope",                     &phoMIPSlope_);
  //tree->Branch("phoMIPIntercept",                 &phoMIPIntercept_);
  //tree->Branch("phoMIPNhitCone",                  &phoMIPNhitCone_);
  //tree->Branch("phoMIPIsHalo",                    &phoMIPIsHalo_);

  tree->Branch("phoxtalBits",      &phoxtalBits_);
  tree->Branch("phoIDbit",         &phoIDbit_);
  tree->Branch("phoScale_stat_up", &phoScale_stat_up_);
  tree->Branch("phoScale_stat_dn", &phoScale_stat_dn_);
  tree->Branch("phoScale_syst_up", &phoScale_syst_up_);
  tree->Branch("phoScale_syst_dn", &phoScale_syst_dn_);
  tree->Branch("phoScale_gain_up", &phoScale_gain_up_);
  tree->Branch("phoScale_gain_dn", &phoScale_gain_dn_);
  tree->Branch("phoResol_rho_up",  &phoResol_rho_up_);
  tree->Branch("phoResol_rho_dn",  &phoResol_rho_dn_);
  tree->Branch("phoResol_phi_up",  &phoResol_phi_up_);
  tree->Branch("phoResol_phi_dn",  &phoResol_phi_dn_);

}

void Analyser::fillPhotons(const edm::Event& e, const edm::EventSetup& es) {
  
  // cleanup from previous execution
  phoE_                   .clear();
  phoSigmaE_              .clear();
  phoEt_                  .clear();
  phoEta_                 .clear();
  phoPhi_                 .clear();
  phoCalibE_              .clear();
  phoCalibEt_             .clear();
  phoSCE_                 .clear();
  phoSCRawE_              .clear();
  phoESEnP1_              .clear();
  phoESEnP2_              .clear();
  phoSCEta_               .clear();
  phoSCPhi_               .clear();
  phoSCEtaWidth_          .clear();
  phoSCPhiWidth_          .clear();
  phoSCBrem_              .clear();
  phohasPixelSeed_        .clear();
  phoEleVeto_             .clear();
  phoR9_                  .clear();
  phoHoverE_              .clear();
  phoESEffSigmaRR_        .clear();
  phoSigmaIEtaIEtaFull5x5_.clear();
  phoSigmaIEtaIPhiFull5x5_.clear();
  phoSigmaIPhiIPhiFull5x5_.clear();
  phoE2x2Full5x5_         .clear();
  phoE5x5Full5x5_         .clear();
  phoR9Full5x5_           .clear();
  phoPFChIso_             .clear();
  phoPFPhoIso_            .clear();
  phoPFNeuIso_            .clear();
  phoPFChWorstIso_        .clear();
  //phoSeedBCE_           .clear();
  //phoSeedBCEta_         .clear();
  phoIDMVA_               .clear();
  phoFiredSingleTrgs_     .clear();
  phoFiredDoubleTrgs_     .clear();
  phoFiredTripleTrgs_     .clear();
  phoFiredL1Trgs_         .clear();
  phoxtalBits_            .clear();
  phoSeedTime_            .clear();
  phoSeedEnergy_          .clear();
  /*
  phoSeedTimeFull5x5_   .clear();
  phoMIPChi2_           .clear();
  phoMIPTotEnergy_      .clear();
  phoMIPSlope_          .clear();
  phoMIPIntercept_      .clear();
  phoMIPNhitCone_       .clear();
  phoMIPIsHalo_         .clear();
  */

  phoIDbit_        .clear();
  phoScale_stat_up_.clear();
  phoScale_stat_dn_.clear();
  phoScale_syst_up_.clear();
  phoScale_syst_dn_.clear();
  phoScale_gain_up_.clear();
  phoScale_gain_dn_.clear();
  phoResol_rho_up_ .clear();
  phoResol_rho_dn_ .clear();
  phoResol_phi_up_ .clear();
  phoResol_phi_dn_ .clear();  

  nPho_ = 0;

  edm::Handle<edm::View<pat::Photon> > photonHandle;
  e.getByToken(photonCollection_, photonHandle);

  if (!photonHandle.isValid()) {
    edm::LogWarning("Analyser") << "no pat::Photons in event";
    return;
  }


  for (edm::View<pat::Photon>::const_iterator iPho = photonHandle->begin(); iPho != photonHandle->end(); ++iPho) {

    phoE_             .push_back(iPho->energy());
    //phoCalibE_        .push_back(iPho->userFloat("ecalEnergyPostCorr"));
    phoEt_            .push_back(iPho->et());
    //phoCalibEt_       .push_back(iPho->et()*iPho->userFloat("ecalEnergyPostCorr")/iPho->energy());
    //phoSigmaE_        .push_back(iPho->userFloat("ecalEnergyErrPostCorr"));
    phoEta_           .push_back(iPho->eta());
    phoPhi_           .push_back(iPho->phi());
    phoSCE_           .push_back((*iPho).superCluster()->energy());
    phoSCRawE_        .push_back((*iPho).superCluster()->rawEnergy());
    phoESEnP1_        .push_back((*iPho).superCluster()->preshowerEnergyPlane1());
    phoESEnP2_        .push_back((*iPho).superCluster()->preshowerEnergyPlane2());
    phoSCEta_         .push_back((*iPho).superCluster()->eta());
    phoSCPhi_         .push_back((*iPho).superCluster()->phi());
    phoSCEtaWidth_    .push_back((*iPho).superCluster()->etaWidth());
    phoSCPhiWidth_    .push_back((*iPho).superCluster()->phiWidth());
    phoSCBrem_        .push_back((*iPho).superCluster()->phiWidth()/(*iPho).superCluster()->etaWidth());
    phohasPixelSeed_  .push_back((Int_t)iPho->hasPixelSeed());
    phoEleVeto_       .push_back((Int_t)iPho->passElectronVeto());
    phoR9_            .push_back(iPho->r9());
    phoHoverE_        .push_back(iPho->hadTowOverEm());
    
    nPho_++;
  }

}
