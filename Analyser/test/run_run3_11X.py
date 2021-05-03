import FWCore.ParameterSet.Config as cms

process = cms.Process('analysis')

process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.options = cms.untracked.PSet( allowUnscheduled = cms.untracked.bool(True) )

process.load("Configuration.StandardSequences.GeometryDB_cff")
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')

from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, 'auto:phase1_2017_realistic', '')

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
process.MessageLogger.cerr.FwkReport.reportEvery = 1000

process.source = cms.Source("PoolSource",
                            fileNames = cms.untracked.vstring(
                                'file:../../../1325.517_TTbar_13_reminiaod2017UL_INPUT+TTbar_13_reminiaod2017UL_INPUT+REMINIAOD_mc2017UL+HARVESTUP17_REMINIAOD_mc2017UL/step2.root'
        )
                            )

from RecoEgamma.EgammaTools.EgammaPostRecoTools import setupEgammaPostRecoSeq
setupEgammaPostRecoSeq(process,
                       runEnergyCorrections=False,
                       runVID=True,
                       era='2018-Prompt',
                       #era = 'PhaseII',
                       eleIDModules=['RecoEgamma.ElectronIdentification.Identification.cutBasedElectronID_Fall17_94X_V2_cff',
                                     'RecoEgamma.ElectronIdentification.Identification.heepElectronID_HEEPV70_cff',
                                     'RecoEgamma.ElectronIdentification.Identification.mvaElectronID_Fall17_iso_V2_cff',
                                     'RecoEgamma.ElectronIdentification.Identification.mvaElectronID_Fall17_noIso_V2_cff',
                                     #'RecoEgamma.ElectronIdentification.Identification.cutBasedElectronID_Summer20_PhaseII_V0_cff',    
                                     'RecoEgamma.ElectronIdentification.Identification.mvaElectronID_Summer16UL_ID_ISO_cff',
                                     'RecoEgamma.ElectronIdentification.Identification.mvaElectronID_Summer17UL_ID_ISO_cff',
                                     'RecoEgamma.ElectronIdentification.Identification.mvaElectronID_Summer18UL_ID_ISO_cff',
                                     
                                 ],
                       phoIDModules=['RecoEgamma.PhotonIdentification.Identification.mvaPhotonID_Fall17_94X_V2_cff',
                                     'RecoEgamma.PhotonIdentification.Identification.cutBasedPhotonID_Fall17_94X_V2_cff',
                                     #'RecoEgamma.PhotonIdentification.Identification.mvaPhotonID_Summer20_PhaseII_V0_cff'
                                 ]

                       )



from PhysicsTools.PatAlgos.tools.coreTools import *

process.TFileService = cms.Service("TFileService", fileName = cms.string('test.root'))


process.load("TestAnalyser.Analyser.analyser_miniAOD_cfi")
process.Analyser.year=cms.int32(2017)
process.Analyser.electronSrc = cms.InputTag("slimmedElectrons")
process.Analyser.calibelectronSrc = cms.InputTag("slimmedElectrons")
process.Analyser.photonSrc = cms.InputTag("slimmedPhotons")
process.Analyser.calibphotonSrc = cms.InputTag("slimmedPhotons")


process.cleanedMu = cms.EDProducer("PATMuonCleanerBySegments",
                                   src = cms.InputTag("slimmedMuons"),
                                   preselection = cms.string("track.isNonnull"),
                                   passthrough = cms.string("isGlobalMuon && numberOfMatches >= 2"),
                                   fractionOfSharedSegments = cms.double(0.499))





process.p = cms.Path(
    process.egammaPostRecoSeq *
#    process.cleanedMu *
#    process.ggMETFiltersSequence *
    process.Analyser
    )


