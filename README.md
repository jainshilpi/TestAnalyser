# TestAnalyser
Analyser for small tests

cmsrel CMSSW_12_0_X_2021-05-02-2300

cmsenv

git cms-init 

git clone https://github.com/jainshilpi/TestAnalyser.git

git cms-addpkg RecoEgamma/EgammaTools  ### essentially just checkout the package from CMSSW

git clone https://github.com/cms-egamma/EgammaPostRecoTools.git

mv EgammaPostRecoTools/python/EgammaPostRecoTools.py RecoEgamma/EgammaTools/python/.

scram b -j 3