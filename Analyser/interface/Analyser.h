#ifndef Analyser_h
#define Analyser_h

#include "TTree.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "DataFormats/Common/interface/Handle.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "SimDataFormats/PileupSummaryInfo/interface/PileupSummaryInfo.h"
#include "SimDataFormats/GeneratorProducts/interface/GenEventInfoProduct.h"
#include "SimDataFormats/GeneratorProducts/interface/LHEEventProduct.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/HLTReco/interface/TriggerEvent.h"
#include "DataFormats/PatCandidates/interface/TriggerObjectStandAlone.h"
#include "DataFormats/Common/interface/TriggerResults.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/MET.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Photon.h"
#include "DataFormats/RecoCandidate/interface/RecoEcalCandidate.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/PatCandidates/interface/Tau.h"
#include "CondFormats/JetMETObjects/interface/FactorizedJetCorrector.h"
#include "HiggsAnalysis/HiggsTo2photons/interface/CiCPhotonID.h"
#include "JetMETCorrections/Modules/interface/JetResolution.h"
#include "HLTrigger/HLTcore/interface/HLTPrescaleProvider.h"

using namespace std;

void setbit(UShort_t& x, UShort_t bit);

class Analyser : public edm::EDAnalyzer {
 public:

  explicit Analyser(const edm::ParameterSet&);
  ~Analyser();
  
  //   static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);
  
 private:
  
  //   virtual void beginJob() {};
  virtual void analyze(const edm::Event&, const edm::EventSetup&);
  void branchesPhotons    (TTree*);
  void branchesElectrons  (TTree*);
  void fillPhotons    (const edm::Event&, const edm::EventSetup&);
  void fillElectrons  (const edm::Event&, const edm::EventSetup&);

  bool development_;
  int  year_;

  vector<int> newparticles_;

  edm::EDGetTokenT<edm::View<pat::Electron> >      electronCollection_;
  edm::EDGetTokenT<edm::View<pat::Photon> >        photonCollection_;

  TTree   *tree_;
  TH1F    *hEvents_;
  TH1F    *hPU_;
  TH1F    *hPUTrue_;
  TH1F    *hGenWeight_;
  TH1F    *hSumGenWeight_;

};

#endif
