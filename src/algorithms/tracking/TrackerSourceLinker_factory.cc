// Created by Dmitry Romanov
// Subject to the terms in the LICENSE file found in the top-level directory.
//

#include "TrackerSourceLinker_factory.h"
#include <services/geometry/acts/ACTSGeo_service.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <services/geometry/dd4hep/JDD4hep_service.h>

#include "JANA/JEvent.h"
#include "services/log/Log_service.h"
#include "extensions/spdlog/SpdlogExtensions.h"

namespace eicrecon {


    void TrackerSourceLinker_factory::Init() {
        // Ask JApplication and parameter managers
        auto app =  this->GetApplication();
        auto pm = app->GetJParameterManager();

        // This prefix will be used for parameters
        std::string param_prefix = "TrackerSourceLinker:" + GetTag();   // Will be something like SiTrkDigi_BarrelTrackerRawHit

        // Now we check that user provided an input names
        pm->SetDefaultParameter(param_prefix + ":input_tags", m_input_tags, "Input data tag name");
        if(m_input_tags.size() == 0) {
            m_input_tags = GetDefaultInputTags();
        }

        // Logger and log level from user parameter or default
        m_log = app->GetService<Log_service>()->logger(param_prefix);
        std::string log_level_str = "info";
        pm->SetDefaultParameter(param_prefix + ":LogLevel", log_level_str, "verbosity: trace, debug, info, warn, err, critical, off");
        m_log->set_level(eicrecon::ParseLogLevel(log_level_str));

        // Get ACTS context from ACTSGeo service
        auto acts_service = GetApplication()->GetService<ACTSGeo_service>();

        auto dd4hp_service = GetApplication()->GetService<JDD4hep_service>();

        // Initialize algorithm
        auto cellid_converter = std::make_shared<const dd4hep::rec::CellIDPositionConverter>(*dd4hp_service->detector());
        m_source_linker.init(cellid_converter, acts_service->acts_context(), m_log);
    }


    void TrackerSourceLinker_factory::ChangeRun(const std::shared_ptr<const JEvent> &event) {

    }

    void TrackerSourceLinker_factory::Process(const std::shared_ptr<const JEvent> &event) {
        // Collect all hits
        std::vector<const eicd::TrackerHit*> total_hits;

        for(auto input_tag: m_input_tags) {
            auto hits = event->Get<eicd::TrackerHit>(input_tag);
            for (const auto hit : hits) {
                total_hits.push_back(hit);
            }
        }
        m_log->debug("TrackerSourceLinker_factory::Process");

        auto result = m_source_linker.produce(total_hits);
        Insert(result);
    }
} // eicrecon