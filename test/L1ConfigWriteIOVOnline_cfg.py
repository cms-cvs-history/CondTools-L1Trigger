import FWCore.ParameterSet.Config as cms

process = cms.Process("L1ConfigWriteIOVOnline")
process.load("FWCore.MessageLogger.MessageLogger_cfi")

# Get L1TriggerKeyList from DB
process.load("CondCore.DBCommon.CondDBCommon_cfi")

# Generate TSC key
process.load("CondTools.L1Trigger.L1TriggerKeyOnline_cfi")

# writer modules
process.load("CondTools.L1Trigger.L1CondDBIOVWriter_cfi")

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(1)
)
process.source = cms.Source("EmptyIOVSource",
    firstValue = cms.uint64(1),
    lastValue = cms.uint64(1),
    timetype = cms.string('runnumber'),
    interval = cms.uint64(1)
)

process.orcon = cms.ESSource("PoolDBESSource",
    process.CondDBCommon,
    toGet = cms.VPSet(cms.PSet(
        record = cms.string('L1TriggerKeyListRcd'),
        tag = cms.string('L1TriggerKeyList_CRUZET_hlt')
    ))
)

process.p = cms.Path(process.L1CondDBIOVWriter)
process.orcon.connect = cms.string('oracle://cms_orcon_prod/CMS_COND_20X_L1T')
process.orcon.DBParameters.authenticationPath = '/nfshome0/onlinedbadm/conddb'
process.L1TriggerKeyOnline.forceGeneration = True
process.L1CondDBIOVWriter.offlineDB = cms.string('oracle://cms_orcon_prod/CMS_COND_20X_L1T')
process.L1CondDBIOVWriter.offlineAuthentication = '/nfshome0/onlinedbadm/conddb'

