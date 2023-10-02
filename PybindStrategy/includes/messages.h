using namespace RCM::StrategyStudio;
using namespace RCM::StrategyStudio::MarketModels;
using namespace RCM::StrategyStudio::Utilities;
namespace py = pybind11;

namespace bindings {
    void bind_messages(py::module_ &m);
    void bind_trade_data_event_msg(py::module_ &m);
    void bind_quote_event_msg(py::module_ &m);
    void bind_market_depth_event_msg(py::module_ &m); 
    void bind_bar_event_msg(py::module_ &m);
    void bind_order_update_event_msg(py::module_ &m);
    void bind_news_event_msg(py::module_ &m);

    void bind_messages(py::module_ &m) {
        bind_trade_data_event_msg(m);
        bind_quote_event_msg(m);
        bind_market_depth_event_msg(m);
        bind_bar_event_msg(m);
        bind_order_update_event_msg(m); 
        bind_news_event_msg(m);
    }

    void bind_trade_data_event_msg(py::module_ &m) {
        py::class_<TradeDataEventMsg>(m, "TradeDataEventMsg")
            .def("name", &TradeDataEventMsg::name)
            .def("instrument", &TradeDataEventMsg::instrument, py::return_value_policy::reference)
            .def("trade", &TradeDataEventMsg::trade, py::return_value_policy::reference)
            .def("side", &TradeDataEventMsg::side)
            .def("IsConsolidated", &TradeDataEventMsg::IsConsolidated)
            .def("IsDirect", &TradeDataEventMsg::IsDirect)
            .def("IsFromDepth", &TradeDataEventMsg::IsFromDepth)
            .def("source_time", 
                [](const TradeDataEventMsg &msg) {
                    return TimeTypeToString(msg.source_time());
                }
            )
            .def("adapter_time", 
                [](const TradeDataEventMsg &msg) {
                    return TimeTypeToString(msg.adapter_time());
                }
            );
    }

    void bind_quote_event_msg(py::module_ &m) {
        py::class_<QuoteEventMsg>(m, "QuoteEventMsg")
            .def("name", &QuoteEventMsg::name)
            .def("instrument", &QuoteEventMsg::instrument, py::return_value_policy::reference)
            .def("adapter_time", [](const QuoteEventMsg &msg) {
                return TimeTypeToString(msg.adapter_time());
            })
            .def("quote_feed_type", &QuoteEventMsg::quote_feed_type)
            .def("source_time", [](const QuoteEventMsg &msg) {
                return TimeTypeToString(msg.source_time());
            })
            .def("feed_handler_time", [](const QuoteEventMsg &msg) {
                return TimeTypeToString(msg.feed_handler_time());
            })
            .def("quote", &QuoteEventMsg::quote, py::return_value_policy::reference)
            .def("updates_nbbo", &QuoteEventMsg::updates_nbbo)
            .def("nbbo", &QuoteEventMsg::nbbo, py::return_value_policy::reference)
            .def("update_type", &QuoteEventMsg::update_type)
            .def("updates_top", &QuoteEventMsg::updates_top)
            .def("IsTopQuote", &QuoteEventMsg::IsTopQuote)
            .def("IsConsolidated", &QuoteEventMsg::IsConsolidated)
            .def("IsDirect", &QuoteEventMsg::IsDirect)
            .def("IsFromDepth", &QuoteEventMsg::IsFromDepth)
            .def("FeedOnlyHasNBBOQuotes", &QuoteEventMsg::FeedOnlyHasNBBOQuotes)
            .def("market_center_id", &QuoteEventMsg::market_center_id);
    }

    void bind_market_depth_event_msg(py::module_ &m) {
        py::class_<MarketDepthEventMsg>(m, "MarketDepthEventMsg")
            .def("name", &MarketDepthEventMsg::name)
            .def("instrument", &MarketDepthEventMsg::instrument, py::return_value_policy::reference)
            .def("adapter_time", 
                [](const MarketDepthEventMsg &msg) {
                    return TimeTypeToString(msg.adapter_time());
                }
            )
            .def("updated_order_book", &MarketDepthEventMsg::updated_order_book)
            .def("updated_top_quote", &MarketDepthEventMsg::updated_top_quote)
            .def("updated_market_center_best", &MarketDepthEventMsg::updated_market_center_best)
            .def("source_time", 
                [](const MarketDepthEventMsg &msg) {
                    return TimeTypeToString(msg.source_time());
                }
            )
            .def("feed_handler_time", 
                [](const MarketDepthEventMsg &msg) {
                    return TimeTypeToString(msg.feed_handler_time());
                }
            );
    }


    void bind_bar_event_msg(py::module_ &m) {
        py::class_<BarEventMsg>(m, "BarEventMsg")
            .def("name", &BarEventMsg::name)
            .def("instrument", &BarEventMsg::instrument, py::return_value_policy::reference)
            .def("interval", &BarEventMsg::interval, py::return_value_policy::reference)
            .def("p_value",&BarEventMsg::p_value, py::return_value_policy::reference)
            .def("alignment_time", 
                [](const BarEventMsg &msg) {
                    return TimeTypeToString(msg.alignment_time());
                }
            )
            .def("bar_time", 
                [](const BarEventMsg &msg) {
                    return TimeTypeToString(msg.bar_time());
                }
            );
        
        py::class_<Bar>(m, "Bar")
            .def("open", &Bar::open)
            .def("high", &Bar::high, py::return_value_policy::reference)
            .def("low", &Bar::low, py::return_value_policy::reference)
            .def("close",&Bar::close, py::return_value_policy::reference)
            .def("volume",&Bar::volume, py::return_value_policy::reference)
            .def("multiplier",&Bar::multiplier, py::return_value_policy::reference)
            .def("remainder",&Bar::remainder, py::return_value_policy::reference)
            .def("realized_variance",&Bar::realized_variance, py::return_value_policy::reference);
    }

    void bind_order_update_event_msg(py::module &m) {
        py::class_<OrderUpdateEventMsg>(m, "OrderUpdateEventMsg")
            .def("name", &OrderUpdateEventMsg::name)
            .def("order", &OrderUpdateEventMsg::order)
            .def("reason", &OrderUpdateEventMsg::reason)
            .def("completes_order", &OrderUpdateEventMsg::completes_order);
    }

    void bind_news_event_msg(py::module &m)
    {
        py::class_<NewsEventMsg>(m, "NewsEventMsg")
            .def("is_min_valid", &NewsEventMsg::is_min_valid)
            .def("is_mid_valid", &NewsEventMsg::is_mid_valid)
            .def("is_max_valid", &NewsEventMsg::is_max_valid)
            .def("is_min_exclusive", &NewsEventMsg::is_min_exclusive)
            .def("is_max_exclusive", &NewsEventMsg::is_max_exclusive)
            .def("is_approximate", &NewsEventMsg::is_approximate)
            .def("lower_bound", &NewsEventMsg::lower_bound)
            .def("mid", &NewsEventMsg::mid)
            .def("upper_bound", &NewsEventMsg::upper_bound)
            .def("IsValid", &NewsEventMsg::IsValid)
            .def("measurement_type", &NewsEventMsg::measurement_type,  py::return_value_policy::reference)
            .def("entity", &NewsEventMsg::entity,  py::return_value_policy::reference)
            .def("measure", &NewsEventMsg::measure,  py::return_value_policy::reference)
            .def("period", &NewsEventMsg::period, py::return_value_policy::reference);
    }
 
} // namespace bindings
