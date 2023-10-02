#include "../PybindStrat.h"

using namespace std;
using namespace RCM::StrategyStudio;
using namespace RCM::StrategyStudio::MarketModels;
using namespace RCM::StrategyStudio::Utilities;
namespace py = pybind11;

// C++11 compatible py::overload_cast implementation
template <typename... Args>
using overload_cast_ = pybind11::detail::overload_cast_impl<Args...>;

namespace bindings {
    void bind_actions(py::module_ &m);
    void bind_strategy_actions(py::module_ &m);
    // void bind_params(py::module_ &m);
    void bind_portfolio(py::module_ &m);
    void bind_orders(py::module_ &m);
    // void bind_fills(py::module_ &m);
    void bind_trades(py::module_ &m);
    // void bind_risk_profile(py::module_ &m);
    void bind_account_fees(py::module_ &m);
    void bind_trade_actions(py::module_ &m);

    // Not in Strategy.h
    void bind_strategy_event_register(py::module_ &m);

    void bind_actions(py::module_ &m) {
        bind_strategy_actions(m);
        // bind_params(m);
        bind_portfolio(m);
        bind_orders(m);
        // bind_fills(m);
        bind_trades(m);
        // bind_risk_profile(m);
        bind_account_fees(m);
        bind_trade_actions(m);
        bind_strategy_event_register(m);
    }

    void bind_strategy_actions(py::module_ &m) {
        py::class_<PybindStrategy>(m, "PybindStrategy");
        
        py::class_<PybindStrategy::StrategyActions>(m, "StrategyActions")
            // .def("params", &PybindStrategy::StrategyActions::params, py::return_value_policy::reference)
            .def("portfolio", &PybindStrategy::StrategyActions::portfolio, py::return_value_policy::reference)
            .def("orders", &PybindStrategy::StrategyActions::orders, py::return_value_policy::reference)
            // .def("fills", &PybindStrategy::StrategyActions::fills, py::return_value_policy::reference)
            .def("trades", &PybindStrategy::StrategyActions::trades, py::return_value_policy::reference)
            // .def("risk_profile", &PybindStrategy::StrategyActions::risk_profile, py::return_value_policy::reference)
            .def("account_fees", &PybindStrategy::StrategyActions::account_fees, py::return_value_policy::reference)
            .def("trade_actions", &PybindStrategy::StrategyActions::trade_actions, py::return_value_policy::reference)
            .def("SymbolCount", &PybindStrategy::StrategyActions::SymbolCount)
            .def("symbols", &PybindStrategy::StrategyActions::symbols, py::keep_alive<0, 1>())
            .def("instruments", &PybindStrategy::StrategyActions::instruments, py::keep_alive<0, 1>())
            .def("instrument_find", &PybindStrategy::StrategyActions::instrument_find, py::keep_alive<0, 1>())
            .def("CheckEnabledTradingForMarketState", &PybindStrategy::StrategyActions::CheckEnabledTradingForMarketState)
            .def("enabled_post_close_data_flag", &PybindStrategy::StrategyActions::enabled_post_close_data_flag)
            .def("set_enabled_post_close_data_flag", &PybindStrategy::StrategyActions::set_enabled_post_close_data_flag)
            .def("enabled_post_close_trade_flag", &PybindStrategy::StrategyActions::enabled_post_close_trade_flag)
            .def("set_enabled_post_close_trade_flag", &PybindStrategy::StrategyActions::set_enabled_post_close_trade_flag)
            .def("enabled_pre_open_data_flag", &PybindStrategy::StrategyActions::enabled_pre_open_data_flag)
            .def("set_enabled_pre_open_data_flag", &PybindStrategy::StrategyActions::set_enabled_pre_open_data_flag)
            .def("enabled_pre_open_trade_flag", &PybindStrategy::StrategyActions::enabled_pre_open_trade_flag)
            .def("set_enabled_pre_open_trade_flag", &PybindStrategy::StrategyActions::set_enabled_pre_open_trade_flag)
            .def("enabled_cancel_on_stop_flag", &PybindStrategy::StrategyActions::enabled_cancel_on_stop_flag)
            .def("set_enabled_cancel_on_stop_flag", &PybindStrategy::StrategyActions::set_enabled_cancel_on_stop_flag);
    }

    /*
    void bind_params(py::module_ &m) {
        // StrategyParamCollection
        py::class_<StrategyParamCollection>(m, "StrategyParamCollection")
            .def("CreateParam", &StrategyParamCollection::CreateParam, py::return_value_policy::reference);

        py::class_<StrategyParam>(m, "StrategyParam")
            .def("param_name", &StrategyParam::param_name)
            .def("param_type", &StrategyParam::param_type)
            .def("value_type", &StrategyParam::value_type)
            .def("min_constraint", &StrategyParam::min_constraint)
            .def("max_constraint", &StrategyParam::max_constraint)
            .def("max_allowed_percent_change", &StrategyParam::max_allowed_percent_change);


        py::class_<CreateStrategyParamArgs>(m, "CreateStrategyParamArgs")
            .def(py::init<const std::string&, StrategyParamType, ValueType>())

            .def_readwrite("param_name", &CreateStrategyParamArgs::param_name)
            .def_readwrite("param_type", &CreateStrategyParamArgs::param_type)
            .def_readwrite("value_type", &CreateStrategyParamArgs::value_type)
            .def_readwrite("default_value", &CreateStrategyParamArgs::default_value)
            .def_readwrite("min", &CreateStrategyParamArgs::min)
            .def_readwrite("max", &CreateStrategyParamArgs::max)
            .def_readwrite("max_percent_change", &CreateStrategyParamArgs::max_percent_change);
    }
    */

    // TODO
    void bind_portfolio(py::module_ &m) {
    // Implement the bindings for the portfolio class and functions here
        py::class_<IPortfolioTracker>(m, "IPortfolioTracker")
                .def("total_pnl", overload_cast_<>()(&IPortfolioTracker::total_pnl, py::const_))
                .def("total_pnl", overload_cast_<const Instrument*>()(&IPortfolioTracker::total_pnl, py::const_))
                .def("unrealized_pnl", overload_cast_<>()(&IPortfolioTracker::unrealized_pnl, py::const_))
                .def("unrealized_pnl", overload_cast_<const Instrument*>()(&IPortfolioTracker::unrealized_pnl, py::const_))
                .def("realized_pnl", overload_cast_<>()(&IPortfolioTracker::realized_pnl, py::const_))
                .def("realized_pnl", overload_cast_<const Instrument*>()(&IPortfolioTracker::realized_pnl, py::const_))
                .def("day_pnl", &IPortfolioTracker::day_pnl)
                .def("opening_cumulative_pnl", &IPortfolioTracker::opening_cumulative_pnl)
                .def("execution_costs", &IPortfolioTracker::execution_costs)
                .def("initial_equity", &IPortfolioTracker::initial_equity)
                .def("initial_cash", &IPortfolioTracker::initial_cash)
                .def("account_equity", &IPortfolioTracker::account_equity)
                .def("cash_balance", &IPortfolioTracker::cash_balance)
                .def("borrow_balance", &IPortfolioTracker::borrow_balance)
                .def("rebate_balance", &IPortfolioTracker::rebate_balance)
                .def("notional", overload_cast_<>()(&IPortfolioTracker::notional, py::const_))
                .def("notional", overload_cast_<const Instrument*>()(&IPortfolioTracker::notional, py::const_))
                .def("long_notional", overload_cast_<>()(&IPortfolioTracker::long_notional, py::const_))
                .def("long_notional",overload_cast_<const Instrument*>()(&IPortfolioTracker::long_notional, py::const_))
                .def("short_notional", overload_cast_<>()(&IPortfolioTracker::short_notional, py::const_))
                .def("short_notional", overload_cast_<const Instrument*>()(&IPortfolioTracker::short_notional, py::const_))
                .def("leverage", &IPortfolioTracker::leverage)
                .def("leverage_numerator", &IPortfolioTracker::leverage_numerator)
                .def("position", overload_cast_<const Instrument*>()(&IPortfolioTracker::position, py::const_));

    }

    void bind_orders(py::module_ &m) {
        py::class_<IOrderTracker>(m, "IOrderTracker")
            .def("num_working_orders", overload_cast_<>()(&IOrderTracker::num_working_orders, py::const_))
            .def("num_working_orders", overload_cast_<const Instrument*>()(&IOrderTracker::num_working_orders, py::const_))
            .def("num_tracked_orders", &IOrderTracker::num_tracked_orders)
            .def("stats", overload_cast_<>()(&IOrderTracker::stats, py::const_), py::return_value_policy::reference)
            .def("working_orders", [](const IOrderTracker &ot) {
                return py::make_iterator(ot.working_orders_begin(), ot.working_orders_end());
            }, py::keep_alive<0, 1>());
            // overloads TBD
            // currently unable to bind boost iterators
            // .def("tracked_orders", [](const IOrderTracker &ot) {
            //     return py::make_iterator(ot.tracked_orders_begin(), ot.tracked_orders_end());
            // }, py::keep_alive<0, 1>());
            
        

        py::class_<IOrderStatistics>(m, "IOrderStatistics")
            .def("num_orders_sent", &IOrderStatistics::num_orders_sent)
            .def("num_orders_filled", &IOrderStatistics::num_orders_filled)
            .def("num_orders_rejected", &IOrderStatistics::num_orders_rejected)
            .def("num_orders_cancelled", &IOrderStatistics::num_orders_cancelled)
            .def("num_orders_open_pending", &IOrderStatistics::num_orders_open_pending)
            .def("num_orders_cancel_pending", &IOrderStatistics::num_orders_cancel_pending)
            .def("num_orders_replace_pending", &IOrderStatistics::num_orders_replace_pending)
            .def("long_working_order_size", &IOrderStatistics::long_working_order_size)
            .def("short_working_order_size", &IOrderStatistics::short_working_order_size)
            .def("net_working_order_size", &IOrderStatistics::net_working_order_size)
            .def("long_working_notional", &IOrderStatistics::long_working_notional)
            .def("short_working_notional", &IOrderStatistics::short_working_notional)
            .def("net_working_notional", &IOrderStatistics::net_working_notional);
    }

    // void bind_fills(py::module_ &m) {
    // // Implement the bindings for the fills class and functions here
    // }

    void bind_trades(py::module_ &m) {
    // Implement the bindings for the trades class and functions here
        py::class_<ITradeTracker>(m, "ITradeTracker")
            .def("num_open_trades", overload_cast_<>()(&ITradeTracker::num_open_trades, py::const_))
            .def("num_open_trades", overload_cast_<const Instrument*>()(&ITradeTracker::num_open_trades, py::const_))
            .def("num_closed_trades", overload_cast_<>()(&ITradeTracker::num_closed_trades, py::const_))
            .def("num_closed_trades", overload_cast_<const Instrument*>()(&ITradeTracker::num_closed_trades, py::const_))
            .def("curr_trade_id", &ITradeTracker::curr_trade_id)
            .def("save_history_flag", &ITradeTracker::save_history_flag);
    }

    // void bind_risk_profile(py::module_ &m) {
    // // Implement the bindings for the risk_profile class and functions here
    // }

    void bind_account_fees(py::module_ &m) {
    // Implement the bindings for the account_fees class and functions here
        py::class_<AccountFees>(m, "AccountFees")
            .def_readwrite("fees_per_order", &AccountFees::fees_per_order)
            .def_readwrite("fees_per_contract", &AccountFees::fees_per_contract)
            .def_readwrite("fees_percentage_of_notional", &AccountFees::fees_percentage_of_notional)
            .def_readwrite("sales_fees_percentage_of_notional", &AccountFees::sales_fees_percentage_of_notional)
            .def_readwrite("sales_fees_per_share", &AccountFees::sales_fees_per_share)
            .def_readwrite("passes_through_exchange_fees", &AccountFees::passes_through_exchange_fees);
    }

    void bind_trade_actions(py::module_ &m) {
        py::class_<StrategyTradeActions>(m, "StrategyTradeActions")
            .def("SendNewOrder", overload_cast_<OrderParams &>()(&StrategyTradeActions::SendNewOrder))
            .def("SendCancelAll", overload_cast_<>()(&StrategyTradeActions::SendCancelAll))
            .def("SendCancelAll", overload_cast_<const Instrument *>()(&StrategyTradeActions::SendCancelAll));
    }

    void bind_strategy_event_register(py::module_ &m) {
        py::class_<StrategyEventRegister>(m, "StrategyEventRegister")
            .def("RegisterForMarketData", &StrategyEventRegister::RegisterForMarketData, py::arg("symbol"), py::arg("data_source") = "", py::return_value_policy::reference)
            // .def("RegisterForBars", &StrategyEventRegister::RegisterForBars, py::arg("symbol"), py::arg("type"), py::arg("interval"), py::arg("p_value") = 2.0, py::arg("alignment_time") = 0, py::arg("data_source") = "", py::return_value_policy::reference)
            .def("RegisterForBars", [](StrategyEventRegister& eventRegister, const std::string& symbol, BarType type, double interval) {
                return eventRegister.RegisterForBars(symbol, type, interval);
            })
            .def("RegisterForOptions", &StrategyEventRegister::RegisterForOptions, py::arg("underlierSymbol"), py::arg("optionType") = MarketModels::OPTION_TYPE_BOTH, py::arg("minStrike") = 0, py::arg("maxStrike") = 0, py::arg("minExpiry") = 0, py::arg("maxExpiry") = 0, py::arg("includeAdjustedContracts") = true, py::arg("data_source") = "", py::return_value_policy::reference)
            .def("RegisterForFutures", &StrategyEventRegister::RegisterForFutures, py::arg("baseSymbol"), py::arg("minMaturity") = 0, py::arg("maxMaturity") = 0, py::arg("includeSpreads") = false, py::arg("data_source") = "", py::return_value_policy::reference)
            .def("RegisterForNews", &StrategyEventRegister::RegisterForNews, py::arg("entity"), py::arg("type") = NewsType::NEWS_TYPE_SPECIFIC_ENTITY, py::arg("data_source") = "", py::return_value_policy::reference)
            .def("RegisterForSentiment", &StrategyEventRegister::RegisterForSentiment, py::arg("entity"), py::arg("type") = SentimentType::SENTIMENT_TYPE_TICKER, py::arg("data_source") = "", py::return_value_policy::reference)
            .def("RegisterForSingleScheduledEvent", &StrategyEventRegister::RegisterForSingleScheduledEvent, py::arg("name"), py::arg("fireTime"), py::arg("fireIfPast") = false, py::return_value_policy::reference)
            .def("RegisterForRecurringScheduledEvents", &StrategyEventRegister::RegisterForRecurringScheduledEvents, py::arg("name"), py::arg("firstFireTime"), py::arg("endFireTime"), py::arg("interval"), py::arg("fireIfPast") = false, py::return_value_policy::reference)
            .def("RegisterForTopicSubscription", &StrategyEventRegister::RegisterForTopicSubscription, py::arg("topic"), py::return_value_policy::reference)
            .def("RegisterForClosureEvent", &StrategyEventRegister::RegisterForClosureEvent, py::arg("closureObject"), py::arg("parentEvent"), py::return_value_policy::reference)
            .def("RegisterForExternalOrders", &StrategyEventRegister::RegisterForExternalOrders, py::arg("symbol"), py::arg("order_source") = "", py::return_value_policy::reference);
    }

} // namespace bindings
