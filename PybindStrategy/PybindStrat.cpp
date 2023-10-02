#ifdef _WIN32
    #include "stdafx.h"
#endif

#include <unistd.h>

#include "PybindStrat.h"
#include <bindings.h>

using namespace RCM::StrategyStudio;
using namespace RCM::StrategyStudio::MarketModels;
using namespace RCM::StrategyStudio::Utilities;

using namespace std;

// C++11 compatible py::overload_cast implementation
template <typename... Args>
using overload_cast_ = pybind11::detail::overload_cast_impl<Args...>;

std::function<void(pybind11::object)> PybindStrategy::saved_register_call;
std::function<void(py::object)> PybindStrategy::saved_define_params_call; 
std::function<void(py::object)> PybindStrategy::saved_define_commands_call; 

PybindStrategy::PybindStrategy(StrategyID strategyID, const std::string& strategyName, const std::string& groupName)
    : Strategy(strategyID, strategyName, groupName) {

    py::scoped_interpreter guard{};     

    try {
        py::module_ Strategy = py::module_::import("MyStrategy");
        py::object Pybind = Strategy.attr("MyStrategy")(StrategyActions(this));

        Pybind.attr("SetFlags")();

    }
    catch (const std::exception& e) {
        std::cout << "SetFlags fail" << std::endl;
        std::cout << e.what() << std::endl;
    }
}

PybindStrategy::~PybindStrategy() {
    std::cout << "Destructor\n" << std::endl;
    py::finalize_interpreter(); 
}

void PybindStrategy::OnTrade(const TradeDataEventMsg& msg) {
   
    try {      
    
        run_init();

        PybindStrat.attr("OnTrade")(msg);

    }

    catch (const std::exception& e) { 
        std::cout << e.what() << std::endl;
    }
    
}

void PybindStrategy::OnTopQuote(const QuoteEventMsg& msg) {
    
   
    
    try {
       
        run_init();

        PybindStrat.attr("OnTopQuote")(msg);
    }
    catch (const std::exception& e) { 
        std::cout << e.what() << std::endl;
    }
    
   

}


void PybindStrategy::OnQuote(const QuoteEventMsg& msg) {

   
    
    try {
        
        run_init();

        PybindStrat.attr("OnQuote")(msg);
        
    }
    catch (const std::exception& e) {
        std::cout << "OnQuote fail" << std::endl;
        std::cout << e.what() << std::endl;
    }



}

void PybindStrategy::OnDepth(const MarketDepthEventMsg& msg) {

   
    try {
        
        run_init();

        PybindStrat.attr("OnDepth")(msg);

    }
    catch (const std::exception& e) {
        std::cout << "OnDepth fail" << std::endl;
        std::cout << e.what() << std::endl;
    }

   

}

void PybindStrategy::OnBar(const BarEventMsg& msg) {

   
    try {
        
        run_init();

        PybindStrat.attr("OnBar")(msg);

    }
    catch (const std::exception& e) {
        std::cout << "OnBar fail" << std::endl;
        std::cout << e.what() << std::endl;
    }

  

}

void PybindStrategy::OnOrderUpdate(const OrderUpdateEventMsg& msg) {
    try {
        
        run_init(); 

        PybindStrat.attr("OnOrderUpdate")(msg);

    }
    catch (const std::exception& e) {
        std::cout << "OnOrderUpdate fail" << std::endl;
        std::cout << e.what() << std::endl;
    }
}

void PybindStrategy::OnStrategyCommand(const StrategyCommandEventMsg& msg) {
    try {
        
        run_init();
        
        PybindStrat.attr("OnStrategyCommand")(msg);

    }
        
    catch (const std::exception& e) {
        std::cout << "OnStrategyCommand fail" << std::endl;
        std::cout << e.what() << std::endl;
    }


}

void PybindStrategy::OnParamChanged(StrategyParam& param) {
     try {
        
        run_init();
        
        PybindStrat.attr("OnParamChanged")(param);

    }
    catch (const std::exception& e) {
        std::cout << "OnParamChanged fail" << std::endl;
        std::cout << e.what() << std::endl;
    }

    
}

void PybindStrategy::OnResetStrategyState() {
    
    try {
        
        run_init();
        
        PybindStrat.attr("OnResetStrategyState")();

    }
    catch (const std::exception& e) {
        std::cout << "OnResetStrategyState fail" << std::endl;
        std::cout << e.what() << std::endl;
    }
    
}

void PybindStrategy::RegisterForStrategyEvents(StrategyEventRegister* eventRegister, DateType currDate)
{       
    // std::function<void(py::object)> save = [eventRegister, currDate](py::object strat) {
    //     strat.attr("RegisterForStrategyEvents")(eventRegister, boost::gregorian::to_simple_string(currDate));
    // };
    
    // saved_register_call = save; 
    // py::scoped_interpreter guard{}; 
    // py::module_ MyStrategy = py::module_::import("MyStrategy");
    // py::object PybindStrat = MyStrategy.attr("MyStrategy")(StrategyActions(this)); 
    // PybindStrat.attr("RegisterForStrategyEvents")(eventRegister, boost::gregorian::to_simple_string(currDate));
    // std::cout << "Made it????" << std::endl;

}

void PybindStrategy::DefineStrategyParams()
{   

    std::function<void(py::object)> save = [](py::object strat) {
        strat.attr("DefineStrategyParams")();
    };

    saved_define_params_call = save; 
    
}

void PybindStrategy::DefineStrategyCommands()
{   

    std::function<void(py::object)> save = [](py::object strat) {
        strat.attr("DefineStrategyCommands")();
    };

    saved_define_commands_call = save; 
}

void PybindStrategy::OnNews(const NewsEventMsg& msg) {
        py::scoped_interpreter guard{};    

    try {
        py::module_ Strategy = py::module_::import("MyStrategy");
        py::object Pybind = Strategy.attr("MyStrategy")(StrategyActions(this));

        Pybind.attr("OnNews")();

    }
    catch (const std::exception& e) {
        std::cout << "OnNews fail" << std::endl;
        std::cout << e.what() << std::endl;
    }
}

void PybindStrategy::run_init() { 
    if(!Py_IsInitialized()) {
            
            py::initialize_interpreter(); 
            MyStrategy = py::module_::import("MyStrategy");
            PybindStrat = MyStrategy.attr("MyStrategy")(StrategyActions(this)); 
        
            // saved_define_params_call(PybindStrat);
            // saved_define_commands_call(PybindStrat);
            // saved_register_call(PybindStrat);
    }
}

