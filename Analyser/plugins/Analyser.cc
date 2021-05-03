#include "TestAnalyser/Analyser/interface/Analyser.h"

using namespace std;
using namespace edm;

void setbit(UShort_t& x, UShort_t bit) {
  UShort_t a = 1;
  x |= (a << bit);
}

Analyser::Analyser(const edm::ParameterSet& ps)
{

  development_               = ps.getParameter<bool>("development");
  year_                      = ps.getParameter<int>("year");

  electronCollection_        = consumes<View<pat::Electron> >          (ps.getParameter<InputTag>("electronSrc"));
  photonCollection_          = consumes<View<pat::Photon> >            (ps.getParameter<InputTag>("photonSrc"));

  Service<TFileService> fs;
  tree_    = fs->make<TTree>("EventTree", "Event data (tag V10_02_10_04)");
  hEvents_ = fs->make<TH1F>("hEvents",    "total processed and skimmed events",   2,  0,   2);

  branchesPhotons(tree_);
  branchesElectrons(tree_);
}

Analyser::~Analyser() {

}

void Analyser::analyze(const edm::Event& e, const edm::EventSetup& es) {

  hEvents_->Fill(0.5);


  fillElectrons(e, es);
  fillPhotons(e, es); 

  hEvents_->Fill(1.5);
  tree_->Fill();

}

DEFINE_FWK_MODULE(Analyser);
