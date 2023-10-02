#pragma once

#include "actions.h"
#include "instrument.h"
#include "messages.h"
#include "types.h"

using namespace RCM::StrategyStudio;
using namespace RCM::StrategyStudio::MarketModels;
using namespace RCM::StrategyStudio::Utilities;
namespace py = pybind11;


namespace bindings {
    PYBIND11_EMBEDDED_MODULE(strategy, m)
    {
        bind_types(m);
        bind_actions(m);
        bind_instrument(m);
        bind_messages(m);
    }

} // namespace bindings