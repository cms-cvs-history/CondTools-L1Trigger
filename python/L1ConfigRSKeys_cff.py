# Generate dummy L1TriggerKey with "SubsystemKeysOnly" label
from CondTools.L1Trigger.L1TriggerKeyDummy_cff import *
L1TriggerKeyDummy.objectKeys = cms.VPSet()
L1TriggerKeyDummy.label = "SubsystemKeysOnly"

# Generate object keys for each subsystem
from L1TriggerConfig.L1GtConfigProducers.l1GtRsObjectKeysOnline_cfi import *
l1GtRsObjectKeysOnline.EnableL1GtPrescaleFactorsAlgoTrig = False
l1GtRsObjectKeysOnline.EnableL1GtPrescaleFactorsTechTrig = False
l1GtRsObjectKeysOnline.EnableL1GtTriggerMaskAlgoTrig = True
l1GtRsObjectKeysOnline.EnableL1GtTriggerMaskTechTrig = False
l1GtRsObjectKeysOnline.EnableL1GtTriggerMaskVetoTechTrig = False
l1GtRsObjectKeysOnline.subsystemLabel = "GT"

# Collate subsystem object keys
from CondTools.L1Trigger.L1TriggerKeyOnline_cfi import *
L1TriggerKeyOnline.subsystemLabels = cms.vstring( 'GT' )