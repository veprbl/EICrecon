// Copyright 2022, David Lawrence
// Subject to the terms in the LICENSE file found in the top-level directory.
//

#ifndef _TruthCluster_factory_HcalEndcapNTruthProtoClusters_h_
#define _TruthCluster_factory_HcalEndcapNTruthProtoClusters_h_

#include <random>

#include <JANA/JFactoryT.h>
#include <services/geometry/dd4hep/JDD4hep_service.h>
#include <algorithms/calorimetry/CalorimeterTruthClustering.h>



class ProtoCluster_factory_HcalEndcapNTruthProtoClusters : public JFactoryT<edm4eic::ProtoCluster>, CalorimeterTruthClustering {

public:
    //------------------------------------------
    // Constructor
    ProtoCluster_factory_HcalEndcapNTruthProtoClusters(){
        SetTag("HcalEndcapNTruthProtoClusters");
    }

    //------------------------------------------
    // Init
    void Init() override{
        auto app = GetApplication();
        m_inputHit_tag="HcalEndcapNRecHits";
        m_inputMCHit_tag="HcalEndcapNHits";

        AlgorithmInit();
    }

    //------------------------------------------
    // ChangeRun
    void ChangeRun(const std::shared_ptr<const JEvent> &event) override{
        AlgorithmChangeRun();
    }

    //------------------------------------------
    // Process
    void Process(const std::shared_ptr<const JEvent> &event) override{
        // Prefill inputs
        m_inputHits = event->Get<edm4eic::CalorimeterHit>(m_inputHit_tag);
        m_mcHits = event->Get<edm4hep::SimCalorimeterHit>(m_inputMCHit_tag);

        // Call Process for generic algorithm
        AlgorithmProcess();

        // Hand owner of algorithm objects over to JANA
        Set(m_outputProtoClusters);
        m_outputProtoClusters.clear(); // not really needed, but better to not leave dangling pointers around
    }
};

#endif // _ProtoCLuster_factory_HcalEndcapNIslandProtoClusters_h_