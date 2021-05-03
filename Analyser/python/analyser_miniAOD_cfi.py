import FWCore.ParameterSet.Config as cms

Analyser = cms.EDAnalyzer("Analyser",
                             development          = cms.bool(False),
                             year                 = cms.int32(2017), 

                             electronSrc          = cms.InputTag("slimmedElectrons"),
                             calibelectronSrc     = cms.InputTag("slimmedElectrons"),
                             photonSrc            = cms.InputTag("slimmedPhotons"),
                             calibphotonSrc       = cms.InputTag("slimmedPhotons"),
                             )
