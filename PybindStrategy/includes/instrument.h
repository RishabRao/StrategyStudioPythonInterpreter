#include <MarketModels/Trade.h>
#include <MarketModels/Markets.h>
#include <MarketModels/NBBOQuote.h>
#include <MarketModels/IAggrOrderBook.h>

using namespace RCM::StrategyStudio;
using namespace RCM::StrategyStudio::MarketModels;
using namespace RCM::StrategyStudio::Utilities;
namespace py = pybind11;

namespace bindings {
    void bind_instrument(py::module_ &m) {
        py::class_ <Trade>(m, "Trade")
                .def("price", &Trade::price)
                .def("set_price", &Trade::set_price)
                .def("size", &Trade::size)
                .def("set_size", &Trade::set_size)
                .def(py::init<double, int, MarketCenterID>(), "Base Constructor");

        py::class_ <NBBOQuote>(m, "NBBOQuote")
            .def("bid_exchange", &NBBOQuote::bid_exchange)
            .def("set_bid_exchange", &NBBOQuote::set_bid_exchange)
            .def("ask_exchange", &NBBOQuote::ask_exchange)
            .def("set_ask_exchange", &NBBOQuote::set_ask_exchange)
            .def(py::init<double, int, MarketCenterID, double, int, MarketCenterID>(), "Base Constructor");

        py::class_ <Markets>(m, "Markets")
            .def("aggregate_order_book", overload_cast_<>()(&Markets::aggregate_order_book, py::const_), py::return_value_policy::reference)
            .def("top_quote", &Markets::top_quote, py::return_value_policy::reference)
            .def("last_trade", &Markets::last_trade, py::return_value_policy::reference)
            .def("num_depth_updates_processed", &Markets::num_depth_updates_processed)
            .def("set_top_quote", &Markets::set_top_quote)
            .def("MinExchangeBidSize", &Markets::MinExchangeBidSize)
            .def("MinExchangeAskSize", &Markets::MinExchangeAskSize)
            .def("UpdateTopQuoteFromNBBO", &Markets::UpdateTopQuoteFromNBBO);


        py::class_ <IAggrOrderBook>(m, "IAggrOrderBook")
            .def("BestBidLevel", &IAggrOrderBook::BestBidLevel, py::return_value_policy::take_ownership)
            .def("BestAskLevel", &IAggrOrderBook::BestAskLevel, py::return_value_policy::take_ownership)
            .def("WorstBidLevel", &IAggrOrderBook::WorstBidLevel, py::return_value_policy::take_ownership)
            .def("WorstAskLevel", &IAggrOrderBook::WorstAskLevel, py::return_value_policy::take_ownership)
            .def("NumBidMarketCentersAtPrice", &IAggrOrderBook::NumBidMarketCentersAtPrice, py::return_value_policy::reference)
            .def("NumAskMarketCentersAtPrice", &IAggrOrderBook::NumAskMarketCentersAtPrice, py::return_value_policy::reference)
            .def("NumBidMarketCentersAtLevel", &IAggrOrderBook::NumBidMarketCentersAtLevel, py::return_value_policy::reference)
            .def("NumAskMarketCentersAtLevel", &IAggrOrderBook::NumAskMarketCentersAtLevel, py::return_value_policy::reference);

        py::class_<Instrument>(m, "Instrument")
            .def("symbol", &Instrument::symbol)
            .def("underlier", &Instrument::underlier, py::return_value_policy::take_ownership) // Returns a Pointer -> Please Delete
            .def("aggregate_order_book", overload_cast_<>()(&Instrument::aggregate_order_book, py::const_), py::return_value_policy::reference) // Returns a Pointer -> Please Delete
            .def("markets", overload_cast_<>()(&Instrument::markets, py::const_), py::return_value_policy::reference) // Do this
            .def("nbbo", overload_cast_<>()(&Instrument::nbbo, py::const_), py::return_value_policy::reference) // Do this
            .def("last_trade", overload_cast_<>()(&Instrument::last_trade, py::const_), py::return_value_policy::reference)// Do this
            .def("is_first_trade_received", &Instrument::is_first_trade_received)
            .def("AddChildInstrument", &Instrument::AddChildInstrument) // Takes in a parameter of Instrument -> pointer
            .def("HasChildInstrument", &Instrument::HasChildInstrument)
            .def("IsCalcTopQuoteBetter", &Instrument::IsCalcTopQuoteBetter)
            .def("top_quote", &Instrument::top_quote, py::return_value_policy::reference);
            
        py::class_<Quote>(m, "Quote")
            .def("bid", &Quote::bid)
            .def("ask", &Quote::ask)
            .def("bid_size", &Quote::bid_size)
            .def("ask_size", &Quote::ask_size);
        
        // NBBOQuote 
        // InstrumentType
        // IAggrOrderBook
        // Markets
        // Trade, TradeStats
        
    }

} // namespace bindings


