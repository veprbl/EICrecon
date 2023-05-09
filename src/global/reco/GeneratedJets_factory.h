// SPDX-License-Identifier: LGPL-3.0-or-later
// Copyright (C) 2023 Zhongling Ji, Derek Anderson

#pragma once

#include <edm4eic/ReconstructedParticleCollection.h>
#include <spdlog/logger.h>

#include <extensions/jana/JChainFactoryT.h>
#include <extensions/spdlog/SpdlogMixin.h>
#include <algorithms/reco/JetReconstruction.h>


namespace eicrecon {

    class GeneratedJets_factory :
            public JChainFactoryT<edm4eic::ReconstructedParticle>,
            public SpdlogMixin<GeneratedJets_factory> {

    public:
        explicit GeneratedJets_factory(std::vector<std::string> default_input_tags):
            JChainFactoryT<edm4eic::ReconstructedParticle>(std::move(default_input_tags)) {
        }

        /** One time initialization **/
        void Init() override;

        /** On run change preparations **/
        void ChangeRun(const std::shared_ptr<const JEvent> &event) override;

        /** Event by event processing **/
        void Process(const std::shared_ptr<const JEvent> &event) override;

    protected:
        JetReconstruction m_jet_algo;

    };

} // eicrecon