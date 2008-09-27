// -*- C++ -*-
//
// Package:    L1SubsystemKeysOnlineProd
// Class:      L1SubsystemKeysOnlineProd
// 
/**\class L1SubsystemKeysOnlineProd L1SubsystemKeysOnlineProd.h CondTools/L1SubsystemKeysOnlineProd/src/L1SubsystemKeysOnlineProd.cc

 Description: <one line class summary>

 Implementation:
     <Notes on implementation>
*/
//
// Original Author:  Werner Man-Li Sun
//         Created:  Thu Aug 21 20:00:59 CEST 2008
// $Id$
//
//


// system include files

// user include files
#include "FWCore/MessageLogger/interface/MessageLogger.h"

#include "CondTools/L1Trigger/plugins/L1SubsystemKeysOnlineProd.h"

#include "CondTools/L1Trigger/interface/Exception.h"

#include "CondFormats/L1TObjects/interface/L1TriggerKeyList.h"
#include "CondFormats/DataRecord/interface/L1TriggerKeyListRcd.h"

#include "FWCore/Framework/interface/HCTypeTagTemplate.h"
#include "FWCore/Framework/interface/EventSetup.h"

//
// class declaration
//

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//
L1SubsystemKeysOnlineProd::L1SubsystemKeysOnlineProd(const edm::ParameterSet& iConfig)
   : m_tscKey( iConfig.getParameter< std::string >( "tscKey" ) ),
     m_omdsReader(
	iConfig.getParameter< std::string >( "onlineDB" ),
	iConfig.getParameter< std::string >( "onlineAuthentication" ) )
{
   //the following line is needed to tell the framework what
   // data is being produced
  setWhatProduced(this, "SubsystemKeysOnly");

   //now do what ever other initialization is needed
}


L1SubsystemKeysOnlineProd::~L1SubsystemKeysOnlineProd()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called to produce the data  ------------
L1SubsystemKeysOnlineProd::ReturnType
L1SubsystemKeysOnlineProd::produce(const L1TriggerKeyRcd& iRecord)
{
   using namespace edm::es;
   boost::shared_ptr<L1TriggerKey> pL1TriggerKey ;

   // Get L1TriggerKeyList
   const L1TriggerKeyListRcd& keyListRcd =
     iRecord.getRecord< L1TriggerKeyListRcd >() ;
   edm::ESHandle< L1TriggerKeyList > keyList ;
   keyListRcd.get( keyList ) ;

   // If L1TriggerKeyList does not contain TSC key, token is empty
   if( keyList->token( m_tscKey ) == std::string() )
     {
       // Instantiate new L1TriggerKey
       pL1TriggerKey = boost::shared_ptr< L1TriggerKey >(
	 new L1TriggerKey() ) ;
       pL1TriggerKey->setTSCKey( m_tscKey ) ;

       edm::LogVerbatim( "L1-O2O" ) << "TSC KEY " << m_tscKey ;

       // Get subsystem keys from OMDS

       // SELECT CSCTF_KEY, DTTF_KEY, RPC_KEY, GMT_KEY, RCT_KEY, GCT_KEY, GT_KEY FROM TRIGGERSUP_CONF WHERE TRIGGERSUP_CONF.TS_KEY = m_tscKey
       std::vector< std::string > queryStrings ;
       queryStrings.push_back( "CSCTF_KEY" ) ;
       queryStrings.push_back( "DTTF_KEY" ) ;
       queryStrings.push_back( "RPC_KEY" ) ;
       queryStrings.push_back( "GMT_KEY" ) ;
       queryStrings.push_back( "RCT_KEY" ) ;
       queryStrings.push_back( "GCT_KEY" ) ;
       queryStrings.push_back( "GT_KEY" ) ;
       //	  queryStrings.push_back( "TSP0_KEY" ) ;

       l1t::OMDSReader::QueryResults subkeyResults =
	 m_omdsReader.basicQuery( queryStrings,
				  "CMS_TRG_L1_CONF",
				  "TRIGGERSUP_CONF",
				  "TRIGGERSUP_CONF.TS_KEY",
				  m_omdsReader.singleAttribute( m_tscKey ) ) ;
       if( subkeyResults.second.size() != 1 ) // check query successful
	 {
	   edm::LogError( "L1-O2O" ) << "Problem with subsystem keys." ;
	   return pL1TriggerKey ;
	 }

       const coral::AttributeList& row = subkeyResults.second.front() ;

       std::string csctfKey = row[ "CSCTF_KEY" ].data< std::string >() ;
       pL1TriggerKey->setSubsystemKey( L1TriggerKey::kCSCTF, csctfKey ) ;
       edm::LogVerbatim( "L1-O2O" ) << "CSCTF_KEY " << csctfKey ;

       std::string dttfKey = row[ "DTTF_KEY" ].data< std::string >() ;
       pL1TriggerKey->setSubsystemKey( L1TriggerKey::kDTTF, dttfKey ) ;
       edm::LogVerbatim( "L1-O2O" ) << "DTTF_KEY " << dttfKey ;

       std::string rpcKey = row[ "RPC_KEY" ].data< std::string >() ;
       pL1TriggerKey->setSubsystemKey( L1TriggerKey::kRPC, rpcKey ) ;
       edm::LogVerbatim( "L1-O2O" ) << "RPC_KEY " << rpcKey ;

       std::string gmtKey = row[ "GMT_KEY" ].data< std::string >() ;
       pL1TriggerKey->setSubsystemKey( L1TriggerKey::kGMT, gmtKey ) ;
       edm::LogVerbatim( "L1-O2O" ) << "GMT_KEY " << gmtKey ;

       std::string rctKey = row[ "RCT_KEY" ].data< std::string >() ;
       pL1TriggerKey->setSubsystemKey( L1TriggerKey::kRCT, rctKey ) ;
       edm::LogVerbatim( "L1-O2O" ) << "RCT_KEY " << rctKey ;

       std::string gctKey = row[ "GCT_KEY" ].data< std::string >() ;
       pL1TriggerKey->setSubsystemKey( L1TriggerKey::kGCT, gctKey ) ;
       edm::LogVerbatim( "L1-O2O" ) << "GCT_KEY " << gctKey ;

       std::string gtKey = row[ "GT_KEY" ].data< std::string >() ;
       pL1TriggerKey->setSubsystemKey( L1TriggerKey::kGT, gtKey ) ;
       edm::LogVerbatim( "L1-O2O" ) << "GT_KEY " << gtKey ;

//        std::string tsp0Key = row[ "TSP0_KEY" ].data< std::string >() ;
//        pL1TriggerKey->setSubsystemKey( L1TriggerKey::kTSP0, tsp0Key ) ;
//        edm::LogVerbatim( "L1-O2O" ) << "TSP0_KEY " << tsp0Key ;
   }
   else
   {
     throw l1t::DataAlreadyPresentException(
        "L1TriggerKey for TSC key " + m_tscKey + " already in CondDB." ) ;
   }

   return pL1TriggerKey ;
}

//define this as a plug-in
//DEFINE_FWK_EVENTSETUP_MODULE(L1SubsystemKeysOnlineProd);