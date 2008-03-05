#ifndef CondTools_L1Trigger_L1CondDBPayloadWriter_h
#define CondTools_L1Trigger_L1CondDBPayloadWriter_h
// -*- C++ -*-
//
// Package:     L1Trigger
// Class  :     L1CondDBPayloadWriter
// 
/**\class L1CondDBPayloadWriter L1CondDBPayloadWriter.h CondTools/L1Trigger/interface/L1CondDBPayloadWriter.h

 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Original Author:  
//         Created:  Sun Mar  2 07:06:56 CET 2008
// $Id$
//

// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "CondTools/L1Trigger/interface/DataWriter.h"

// forward declarations

class L1CondDBPayloadWriter : public edm::EDAnalyzer {
   public:
      explicit L1CondDBPayloadWriter(const edm::ParameterSet&);
      ~L1CondDBPayloadWriter();


   private:
      virtual void beginJob(const edm::EventSetup&) ;
      virtual void analyze(const edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;

      // ----------member data ---------------------------
      l1t::DataWriter m_writer ;
      std::string m_tag ;
};

#endif