using namespace RCM::StrategyStudio;
using namespace RCM::StrategyStudio::MarketModels;
using namespace RCM::StrategyStudio::Utilities;
namespace py = pybind11;

namespace bindings {
    void bind_types(py::module_ &m);
    void bind_other_types(py::module_ &m);
    void bind_strategy_param_types(py::module_ &m);
    void bind_execution_types(py::module_ &m);
    void bind_data_types(py::module_ &m);
    void bind_market_center_types(py::module_ &m);
    void bind_event_enums(py::module &m);
    // Do not cast TimeType. Instead, when a return value is TimeType, return it as a string using TimeTypeToString
    // If an enum is created with an important class, e.g. InstrumentType in Instrument.h, then try to bind them together instead of in types.h


    void bind_types(py::module_ &m) {
        bind_other_types(m);
        bind_strategy_param_types(m);
        bind_execution_types(m);
        bind_data_types(m);
        bind_market_center_types(m);
        bind_event_enums(m);
    }
        

    void bind_other_types(py::module_ &m) {
        py::class_<OrderParams>(m, "OrderParams")
            .def(py::init<const Instrument&, int, Price, MarketCenterID, OrderSide, OrderTIF, OrderType>());
        
        py::class_<Order>(m, "Order")
            .def("size_completed", &Order::size_completed)
            .def("size_remaining", &Order::size_remaining)
            .def("trader", &Order::trader)
            .def("account", &Order::account)
            .def("broker_name", &Order::broker_name)
            .def("size_completed", &Order::size_completed)
            .def("size_remaining", &Order::size_remaining)
            .def("avg_fill_price", &Order::avg_fill_price)
            .def("exec_costs", &Order::exec_costs)
            .def("reason", &Order::reason)
            .def("order_quantity", &Order::order_quantity)
            .def("signed_order_quantity", &Order::signed_order_quantity)
            .def("display_quantity", &Order::display_quantity)
            .def("minimum_quantity", &Order::minimum_quantity)
            .def("price", &Order::price)
            .def("stop_price", &Order::stop_price);
        
        py::enum_<OptionType>(m, "OptionType")
            .value("OPTION_TYPE_UNKNOWN", OptionType::OPTION_TYPE_UNKNOWN)
            .value("OPTION_TYPE_CALL", OptionType::OPTION_TYPE_CALL)
            .value("OPTION_TYPE_PUT", OptionType::OPTION_TYPE_PUT)
            .value("OPTION_TYPE_BOTH", OptionType::OPTION_TYPE_BOTH)
            .export_values();

        py::class_<Event>(m, "Event")
            .def("name", &Event::name)
            .def("type", &Event::type);
        
         py::enum_<TradeSide>(m, "TradeSide")
            .value("TRADE_SIDE_SELL", TradeSide::TRADE_SIDE_SELL)
            .value("TRADE_SIDE_UNKNOWN", TradeSide::TRADE_SIDE_UNKNOWN)
            .value("TRADE_SIDE_BUY", TradeSide::TRADE_SIDE_BUY)
            .export_values();
        
        py::enum_<QuoteUpdateType>(m, "QuoteUpdateType")
            .value("QUOTE_UPDATE_TYPE_UNKNOWN", QuoteUpdateType::QUOTE_UPDATE_TYPE_UNKNOWN)
            .value("QUOTE_UPDATE_TYPE_NBBO_AND_MARKET_CENTER", QuoteUpdateType::QUOTE_UPDATE_TYPE_NBBO_AND_MARKET_CENTER)
            .value("QUOTE_UPDATE_TYPE_NBBO_ONLY", QuoteUpdateType::QUOTE_UPDATE_TYPE_NBBO_ONLY)
            .value("QUOTE_UPDATE_TYPE_MARKET_CENTER_ONLY", QuoteUpdateType::QUOTE_UPDATE_TYPE_MARKET_CENTER_ONLY)
            .value("QUOTE_UPDATE_TYPE_MARKET_CENTER_ONLY_BID_SIDE", QuoteUpdateType::QUOTE_UPDATE_TYPE_MARKET_CENTER_ONLY_BID_SIDE)
            .value("QUOTE_UPDATE_TYPE_MARKET_CENTER_ONLY_ASK_SIDE", QuoteUpdateType::QUOTE_UPDATE_TYPE_MARKET_CENTER_ONLY_ASK_SIDE)
            .value("QUOTE_UPDATE_TYPE_TOP_UPDATE", QuoteUpdateType::QUOTE_UPDATE_TYPE_TOP_UPDATE)
            .export_values();
        
    }

    void bind_strategy_param_types(py::module_ &m) {
        py::enum_<StrategyParamType>(m, "StrategyParamType")
            .value("STRATEGY_PARAM_TYPE_UNKNOWN", StrategyParamType::STRATEGY_PARAM_TYPE_UNKNOWN)
            .value("STRATEGY_PARAM_TYPE_STARTUP", StrategyParamType::STRATEGY_PARAM_TYPE_STARTUP)
            .value("STRATEGY_PARAM_TYPE_RUNTIME", StrategyParamType::STRATEGY_PARAM_TYPE_RUNTIME)
            .value("STRATEGY_PARAM_TYPE_READONLY", StrategyParamType::STRATEGY_PARAM_TYPE_READONLY)
            .value("STRATEGY_PARAM_TYPE_SYSTEM", StrategyParamType::STRATEGY_PARAM_TYPE_SYSTEM)
            .export_values();

        py::enum_<StrategyParamRetVal>(m, "StrategyParamRetVal")
            .value("STRATEGY_PARAM_RETVAL_UNKNOWN", StrategyParamRetVal::STRATEGY_PARAM_RETVAL_UNKNOWN)
            .value("STRATEGY_PARAM_RETVAL_SUCCESS", StrategyParamRetVal::STRATEGY_PARAM_RETVAL_SUCCESS)
            .value("STRATEGY_PARAM_RETVAL_INCORRECT_TYPE", StrategyParamRetVal::STRATEGY_PARAM_RETVAL_INCORRECT_TYPE)
            .value("STRATEGY_PARAM_RETVAL_MIN_CONSTRAINT_VIOLATED", StrategyParamRetVal::STRATEGY_PARAM_RETVAL_MIN_CONSTRAINT_VIOLATED)
            .value("STRATEGY_PARAM_RETVAL_MAX_CONSTRAINT_VIOLATED", StrategyParamRetVal::STRATEGY_PARAM_RETVAL_MAX_CONSTRAINT_VIOLATED)
            .value("STRATEGY_PARAM_RETVAL_MAX_PERCENT_CHANGE_CONSTRAINT_VIOLATED", StrategyParamRetVal::STRATEGY_PARAM_RETVAL_MAX_PERCENT_CHANGE_CONSTRAINT_VIOLATED)
            .value("STRATEGY_PARAM_RETVAL_ON_PARAM_VALIDATE_FAILURE", StrategyParamRetVal::STRATEGY_PARAM_RETVAL_ON_PARAM_VALIDATE_FAILURE)
            .export_values();

        py::enum_<ValueType>(m, "ValueType")
            .value("VALUE_TYPE_UNKNOWN", ValueType::VALUE_TYPE_UNKNOWN)
            .value("VALUE_TYPE_INT", ValueType::VALUE_TYPE_INT)
            .value("VALUE_TYPE_DOUBLE", ValueType::VALUE_TYPE_DOUBLE)
            .value("VALUE_TYPE_CHAR", ValueType::VALUE_TYPE_CHAR)
            .value("VALUE_TYPE_STRING", ValueType::VALUE_TYPE_STRING)
            .value("VALUE_TYPE_BOOL", ValueType::VALUE_TYPE_BOOL)
            .export_values();
        
        py::enum_<BarType>(m, "BarType")
            .value("BAR_TYPE_UNKNOWN", BarType::BAR_TYPE_UNKNOWN)
            .value("BAR_TYPE_TIME", BarType::BAR_TYPE_TIME)
            .value("BAR_TYPE_DAILY", BarType::BAR_TYPE_DAILY)
            .value("BAR_TYPE_TICK_COUNT", BarType::BAR_TYPE_TICK_COUNT)
            .value("BAR_TYPE_VOLUME", BarType::BAR_TYPE_VOLUME)
            .value("BAR_TYPE_VARIANCE", BarType::BAR_TYPE_VARIANCE)
            .value("BAR_TYPE_RANGE", BarType::BAR_TYPE_RANGE)
            .export_values();
    }

    void bind_execution_types(py::module_ &m) {
        py::enum_<OrderSide>(m, "OrderSide")
        .value("ORDER_SIDE_UNKNOWN", OrderSide::ORDER_SIDE_UNKNOWN)
        .value("ORDER_SIDE_BUY", OrderSide::ORDER_SIDE_BUY)
        .value("ORDER_SIDE_SELL", OrderSide::ORDER_SIDE_SELL)
        .export_values();

        
        py::enum_<OrderTIF>(m, "OrderTIF")
            .value("ORDER_TIF_UNKNOWN", OrderTIF::ORDER_TIF_UNKNOWN)
            .value("ORDER_TIF_DAY", OrderTIF::ORDER_TIF_DAY)
            .value("ORDER_TIF_GTC", OrderTIF::ORDER_TIF_GTC)
            .export_values();
        
        py::enum_<OrderType>(m, "OrderType")
            .value("ORDER_TYPE_UNKNOWN", OrderType::ORDER_TYPE_UNKNOWN)
            .value("ORDER_TYPE_MARKET", OrderType::ORDER_TYPE_MARKET)
            .value("ORDER_TYPE_LIMIT", OrderType::ORDER_TYPE_LIMIT)
            .export_values();

    }
    
    void bind_data_types(py::module_ &m) {

        py::enum_<TradeActionResult>(m, "TradeActionResult")
            .value("TRADE_ACTION_RESULT_UNKNOWN", TradeActionResult::TRADE_ACTION_RESULT_UNKNOWN)
            .value("TRADE_ACTION_RESULT_SUCCESSFUL", TradeActionResult::TRADE_ACTION_RESULT_SUCCESSFUL)
            .value("TRADE_ACTION_RESULT_FAILED_OMS", TradeActionResult::TRADE_ACTION_RESULT_FAILED_OMS)
            .value("TRADE_ACTION_RESULT_FAILED_INVALID_STRATEGY_STATE", TradeActionResult::TRADE_ACTION_RESULT_FAILED_INVALID_STRATEGY_STATE)
            .value("TRADE_ACTION_RESULT_FAILED_INVALID_SERVER_STATE", TradeActionResult::TRADE_ACTION_RESULT_FAILED_INVALID_SERVER_STATE)
            .value("TRADE_ACTION_RESULT_FAILED_INVALID_MARKET_STATE", TradeActionResult::TRADE_ACTION_RESULT_FAILED_INVALID_MARKET_STATE)
            .value("TRADE_ACTION_RESULT_REJECT_RISK", TradeActionResult::TRADE_ACTION_RESULT_REJECT_RISK)
            .value("TRADE_ACTION_RESULT_FAILED_EXEC_HANDLER_NOT_LOADED", TradeActionResult::TRADE_ACTION_RESULT_FAILED_EXEC_HANDLER_NOT_LOADED)
            .export_values();


        py::enum_<NewsType>(m, "NewsType")
            .value("NEWS_TYPE_CORPORATE", NewsType::NEWS_TYPE_CORPORATE)
            .value("NEWS_TYPE_GOVERNMENT", NewsType::NEWS_TYPE_GOVERNMENT)
            .value("NEWS_TYPE_SPECIFIC_ENTITY", NewsType::NEWS_TYPE_SPECIFIC_ENTITY)
            .export_values();

        py::enum_<SentimentType>(m, "SentimentType")
            .value("SENTIMENT_TYPE_TICKER", SentimentType::SENTIMENT_TYPE_TICKER)
            .value("SENTIMENT_TYPE_ETF", SentimentType::SENTIMENT_TYPE_ETF)
            .value("SENTIMENT_TYPE_INDEX", SentimentType::SENTIMENT_TYPE_INDEX)
            .value("SENTIMENT_TYPE_FOREX", SentimentType::SENTIMENT_TYPE_FOREX)
            .value("SENTIMENT_TYPE_FUTURE", SentimentType::SENTIMENT_TYPE_FUTURE)
            .value("SENTIMENT_TYPE_CRYPTO", SentimentType::SENTIMENT_TYPE_CRYPTO)
            .value("SENTIMENT_TYPE_STOCK_ACTIVITY", SentimentType::SENTIMENT_TYPE_STOCK_ACTIVITY)
            .value("SENTIMENT_TYPE_ETF_ACTIVITY", SentimentType::SENTIMENT_TYPE_ETF_ACTIVITY)
            .value("SENTIMENT_TYPE_FOREX_ACTIVITY", SentimentType::SENTIMENT_TYPE_FOREX_ACTIVITY)
            .value("SENTIMENT_TYPE_FUTURE_ACTIVITY", SentimentType::SENTIMENT_TYPE_FUTURE_ACTIVITY)
            .value("SENTIMENT_TYPE_CRYPTO_ACTIVITY", SentimentType::SENTIMENT_TYPE_CRYPTO_ACTIVITY)
            .export_values();
    }

    void bind_market_center_types(py::module_ &m) {
        py::enum_<MarketCenterID>(m, "MarketCenterID")
            .value("MARKET_CENTER_ID_UNKNOWN", MarketCenterID::MARKET_CENTER_ID_UNKNOWN)
            .value("MARKET_CENTER_ID_AMEX", MarketCenterID::MARKET_CENTER_ID_AMEX)
            .value("MARKET_CENTER_ID_BATS", MarketCenterID::MARKET_CENTER_ID_BATS)
            .value("MARKET_CENTER_ID_BYX", MarketCenterID::MARKET_CENTER_ID_BYX)
            .value("MARKET_CENTER_ID_BSE", MarketCenterID::MARKET_CENTER_ID_BSE)
            .value("MARKET_CENTER_ID_EDGA", MarketCenterID::MARKET_CENTER_ID_EDGA)
            .value("MARKET_CENTER_ID_EDGX", MarketCenterID::MARKET_CENTER_ID_EDGX)
            .value("MARKET_CENTER_ID_NSX", MarketCenterID::MARKET_CENTER_ID_NSX)
            .value("MARKET_CENTER_ID_FINRA", MarketCenterID::MARKET_CENTER_ID_FINRA)
            .value("MARKET_CENTER_ID_ISE", MarketCenterID::MARKET_CENTER_ID_ISE)
            .value("MARKET_CENTER_ID_CHICAGO", MarketCenterID::MARKET_CENTER_ID_CHICAGO)
            .value("MARKET_CENTER_ID_NYSE", MarketCenterID::MARKET_CENTER_ID_NYSE)
            .value("MARKET_CENTER_ID_ARCA", MarketCenterID::MARKET_CENTER_ID_ARCA)
            .value("MARKET_CENTER_ID_NASDAQ", MarketCenterID::MARKET_CENTER_ID_NASDAQ)
            .value("MARKET_CENTER_ID_CONSOLIDATED_CTS", MarketCenterID::MARKET_CENTER_ID_CONSOLIDATED_CTS)
            .value("MARKET_CENTER_ID_CONSOLIDATED_SIP", MarketCenterID::MARKET_CENTER_ID_CONSOLIDATED_SIP)
            .value("MARKET_CENTER_ID_PHLX", MarketCenterID::MARKET_CENTER_ID_PHLX)
            .value("MARKET_CENTER_ID_CBOESTOCK", MarketCenterID::MARKET_CENTER_ID_CBOESTOCK)
            .value("MARKET_CENTER_ID_IEX", MarketCenterID::MARKET_CENTER_ID_IEX)
            .value("MARKET_CENTER_ID_CME_GLOBEX", MarketCenterID::MARKET_CENTER_ID_CME_GLOBEX)
            .value("MARKET_CENTER_ID_ICE_FUTURES", MarketCenterID::MARKET_CENTER_ID_ICE_FUTURES)
            .value("MARKET_CENTER_ID_EUREX", MarketCenterID::MARKET_CENTER_ID_EUREX)
            .value("MARKET_CENTER_ID_CBOE_FUTURES", MarketCenterID::MARKET_CENTER_ID_CBOE_FUTURES)
            .value("MARKET_CENTER_ID_ASX", MarketCenterID::MARKET_CENTER_ID_ASX)
            .value("MARKET_CENTER_ID_MONTREAL", MarketCenterID::MARKET_CENTER_ID_MONTREAL)
            .value("MARKET_CENTER_ID_NASDAQ_FUTURES", MarketCenterID::MARKET_CENTER_ID_NASDAQ_FUTURES)
            .value("MARKET_CENTER_ID_TOCOM", MarketCenterID::MARKET_CENTER_ID_TOCOM)
            .value("MARKET_CENTER_ID_SGX", MarketCenterID::MARKET_CENTER_ID_SGX)
            .value("MARKET_CENTER_ID_BOND_BTEC", MarketCenterID::MARKET_CENTER_ID_BOND_BTEC)
            .value("MARKET_CENTER_ID_BOND_ESPD", MarketCenterID::MARKET_CENTER_ID_BOND_ESPD)
            .value("MARKET_CENTER_ID_AMEX_OPTIONS", MarketCenterID::MARKET_CENTER_ID_AMEX_OPTIONS)
            .value("MARKET_CENTER_ID_ARCA_OPTIONS", MarketCenterID::MARKET_CENTER_ID_ARCA_OPTIONS)
            .value("MARKET_CENTER_ID_BATS_OPTIONS", MarketCenterID::MARKET_CENTER_ID_BATS_OPTIONS)
            .value("MARKET_CENTER_ID_BOX_OPTIONS", MarketCenterID::MARKET_CENTER_ID_BOX_OPTIONS)
            .value("MARKET_CENTER_ID_CBOE_OPTIONS", MarketCenterID::MARKET_CENTER_ID_CBOE_OPTIONS)
            .value("MARKET_CENTER_ID_C2_OPTIONS", MarketCenterID::MARKET_CENTER_ID_C2_OPTIONS)
            .value("MARKET_CENTER_ID_ISE_OPTIONS", MarketCenterID::MARKET_CENTER_ID_ISE_OPTIONS)
            .value("MARKET_CENTER_ID_OPRA_OPTIONS", MarketCenterID::MARKET_CENTER_ID_OPRA_OPTIONS)
            .value("MARKET_CENTER_ID_NASDAQ_OPTIONS", MarketCenterID::MARKET_CENTER_ID_NASDAQ_OPTIONS)
            .value("MARKET_CENTER_ID_PHLX_OPTIONS", MarketCenterID::MARKET_CENTER_ID_PHLX_OPTIONS)
            .value("MARKET_CENTER_ID_GEMINI_OPTIONS", MarketCenterID::MARKET_CENTER_ID_GEMINI_OPTIONS)
            .value("MARKET_CENTER_ID_MIAMI_OPTIONS", MarketCenterID::MARKET_CENTER_ID_MIAMI_OPTIONS)
            .value("MARKET_CENTER_ID_OMX_BX_OPTIONS", MarketCenterID::MARKET_CENTER_ID_OMX_BX_OPTIONS)
            .value("MARKET_CENTER_ID_EDGX_OPTIONS", MarketCenterID::MARKET_CENTER_ID_EDGX_OPTIONS)
            .value("MARKET_CENTER_ID_MERCURY_OPTIONS", MarketCenterID::MARKET_CENTER_ID_MERCURY_OPTIONS)
            .value("MARKET_CENTER_ID_PEARL_OPTIONS", MarketCenterID::MARKET_CENTER_ID_PEARL_OPTIONS)
            .value("MARKET_CENTER_ID_SMART_ROUTER", MarketCenterID::MARKET_CENTER_ID_SMART_ROUTER)
            .value("MARKET_CENTER_ID_ATS_BIDS", MarketCenterID::MARKET_CENTER_ID_ATS_BIDS)
            .value("MARKET_CENTER_ID_ATS_CBX", MarketCenterID::MARKET_CENTER_ID_ATS_CBX)
            .value("MARKET_CENTER_ID_ATS_CRSF", MarketCenterID::MARKET_CENTER_ID_ATS_CRSF)
            .value("MARKET_CENTER_ID_ATS_CSLP", MarketCenterID::MARKET_CENTER_ID_ATS_CSLP)
            .value("MARKET_CENTER_ID_ATS_KLINK", MarketCenterID::MARKET_CENTER_ID_ATS_KLINK)
            .value("MARKET_CENTER_ID_ATS_KMATCH", MarketCenterID::MARKET_CENTER_ID_ATS_KMATCH)
            .value("MARKET_CENTER_ID_ATS_LAVA", MarketCenterID::MARKET_CENTER_ID_ATS_LAVA)
            .value("MARKET_CENTER_ID_ATS_LEVEL", MarketCenterID::MARKET_CENTER_ID_ATS_LEVEL)
            .value("MARKET_CENTER_ID_ATS_LX", MarketCenterID::MARKET_CENTER_ID_ATS_LX)
            .value("MARKET_CENTER_ID_ATS_MILM", MarketCenterID::MARKET_CENTER_ID_ATS_MILM)
            .value("MARKET_CENTER_ID_ATS_MLXN", MarketCenterID::MARKET_CENTER_ID_ATS_MLXN)
            .value("MARKET_CENTER_ID_ATS_POSIT", MarketCenterID::MARKET_CENTER_ID_ATS_POSIT)
            .value("MARKET_CENTER_ID_ATS_SIGMA_X", MarketCenterID::MARKET_CENTER_ID_ATS_SIGMA_X)
            .value("MARKET_CENTER_ID_ATS_VORTX", MarketCenterID::MARKET_CENTER_ID_ATS_VORTX)
            .value("MARKET_CENTER_ID_ATS_CDEL", MarketCenterID::MARKET_CENTER_ID_ATS_CDEL)
            .value("MARKET_CENTER_ID_ATS_DBSX", MarketCenterID::MARKET_CENTER_ID_ATS_DBSX)
            .value("MARKET_CENTER_ID_ATS_GTCO", MarketCenterID::MARKET_CENTER_ID_ATS_GTCO)
            .value("MARKET_CENTER_ID_ATS_JPMX", MarketCenterID::MARKET_CENTER_ID_ATS_JPMX)
            .value("MARKET_CENTER_ID_ATS_PDQ", MarketCenterID::MARKET_CENTER_ID_ATS_PDQ)
            .value("MARKET_CENTER_ID_ATS_UBSA", MarketCenterID::MARKET_CENTER_ID_ATS_UBSA)
            .value("MARKET_CENTER_ID_MM_TWOSIGMA", MarketCenterID::MARKET_CENTER_ID_MM_TWOSIGMA)
            .value("MARKET_CENTER_ID_MM_VIRTU", MarketCenterID::MARKET_CENTER_ID_MM_VIRTU)
            .value("MARKET_CENTER_ID_CA_DARK_ICX", MarketCenterID::MARKET_CENTER_ID_CA_DARK_ICX)
            .value("MARKET_CENTER_ID_CA_DARK_LIQUIDNET", MarketCenterID::MARKET_CENTER_ID_CA_DARK_LIQUIDNET)
            .value("MARKET_CENTER_ID_CA_DARK_MATCHNOW", MarketCenterID::MARKET_CENTER_ID_CA_DARK_MATCHNOW)
            .value("MARKET_CENTER_ID_CA_DARK_NASDAQ_CXD", MarketCenterID::MARKET_CENTER_ID_CA_DARK_NASDAQ_CXD)
            .value("MARKET_CENTER_ID_SMART_ROUTER_OPTIONS", MarketCenterID::MARKET_CENTER_ID_SMART_ROUTER_OPTIONS)
            .value("MARKET_CENTER_ID_FX_CURRENEX", MarketCenterID::MARKET_CENTER_ID_FX_CURRENEX)
            .value("MARKET_CENTER_ID_FX_HOTSPOT", MarketCenterID::MARKET_CENTER_ID_FX_HOTSPOT)
            .value("MARKET_CENTER_ID_FX_EBS", MarketCenterID::MARKET_CENTER_ID_FX_EBS)
            .value("MARKET_CENTER_ID_FX_REUTERS", MarketCenterID::MARKET_CENTER_ID_FX_REUTERS)
            .value("MARKET_CENTER_ID_FX_FXALL", MarketCenterID::MARKET_CENTER_ID_FX_FXALL)
            .value("MARKET_CENTER_ID_FX_LMAX", MarketCenterID::MARKET_CENTER_ID_FX_LMAX)
            .value("MARKET_CENTER_ID_FX_OTC", MarketCenterID::MARKET_CENTER_ID_FX_OTC)
            .value("MARKET_CENTER_ID_CA_AEQUITAS_LIT", MarketCenterID::MARKET_CENTER_ID_CA_AEQUITAS_LIT)
            .value("MARKET_CENTER_ID_CA_AEQUITAS_NEO", MarketCenterID::MARKET_CENTER_ID_CA_AEQUITAS_NEO)
            .value("MARKET_CENTER_ID_CA_ALPHA", MarketCenterID::MARKET_CENTER_ID_CA_ALPHA)
            .value("MARKET_CENTER_ID_CA_CSE", MarketCenterID::MARKET_CENTER_ID_CA_CSE)
            .value("MARKET_CENTER_ID_CA_LYNX", MarketCenterID::MARKET_CENTER_ID_CA_LYNX)
            .value("MARKET_CENTER_ID_CA_NASDAQ_CXC", MarketCenterID::MARKET_CENTER_ID_CA_NASDAQ_CXC)
            .value("MARKET_CENTER_ID_CA_NASDAQ_CX2", MarketCenterID::MARKET_CENTER_ID_CA_NASDAQ_CX2)
            .value("MARKET_CENTER_ID_CA_OMEGA", MarketCenterID::MARKET_CENTER_ID_CA_OMEGA)
            .value("MARKET_CENTER_ID_CA_TSX", MarketCenterID::MARKET_CENTER_ID_CA_TSX)
            .value("MARKET_CENTER_ID_CA_TSXV", MarketCenterID::MARKET_CENTER_ID_CA_TSXV)
            .value("MARKET_CENTER_ID_BOVESPA", MarketCenterID::MARKET_CENTER_ID_BOVESPA)
            .value("MARKET_CENTER_ID_LSE", MarketCenterID::MARKET_CENTER_ID_LSE)
            .value("MARKET_CENTER_ID_EU_XETR", MarketCenterID::MARKET_CENTER_ID_EU_XETR)
            .value("MARKET_CENTER_ID_EU_XPAR", MarketCenterID::MARKET_CENTER_ID_EU_XPAR)
            .value("MARKET_CENTER_ID_EU_XAMS", MarketCenterID::MARKET_CENTER_ID_EU_XAMS)
            .value("MARKET_CENTER_ID_EU_XBRU", MarketCenterID::MARKET_CENTER_ID_EU_XBRU)
            .value("MARKET_CENTER_ID_EU_XLIS", MarketCenterID::MARKET_CENTER_ID_EU_XLIS)
            .value("MARKET_CENTER_ID_EU_MTAA", MarketCenterID::MARKET_CENTER_ID_EU_MTAA)
            .value("MARKET_CENTER_ID_EU_XSWX", MarketCenterID::MARKET_CENTER_ID_EU_XSWX)
            .value("MARKET_CENTER_ID_EU_XVTX", MarketCenterID::MARKET_CENTER_ID_EU_XVTX)
            .value("MARKET_CENTER_ID_EU_XMCE", MarketCenterID::MARKET_CENTER_ID_EU_XMCE)
            .value("MARKET_CENTER_ID_EU_XSTO", MarketCenterID::MARKET_CENTER_ID_EU_XSTO)
            .value("MARKET_CENTER_ID_EU_XHEL", MarketCenterID::MARKET_CENTER_ID_EU_XHEL)
            .value("MARKET_CENTER_ID_EU_XCSE", MarketCenterID::MARKET_CENTER_ID_EU_XCSE)
            .value("MARKET_CENTER_ID_EU_TRQX", MarketCenterID::MARKET_CENTER_ID_EU_TRQX)
            .value("MARKET_CENTER_ID_EU_CHIX", MarketCenterID::MARKET_CENTER_ID_EU_CHIX)
            .value("MARKET_CENTER_ID_EU_BATE", MarketCenterID::MARKET_CENTER_ID_EU_BATE)
            .value("MARKET_CENTER_ID_AP_XIDX", MarketCenterID::MARKET_CENTER_ID_AP_XIDX)
            .value("MARKET_CENTER_ID_AP_XKLS", MarketCenterID::MARKET_CENTER_ID_AP_XKLS)
            .value("MARKET_CENTER_ID_AP_XSES", MarketCenterID::MARKET_CENTER_ID_AP_XSES)
            .export_values();


            py::enum_<FeedType>(m, "FeedType")
                .value("FEED_TYPE_NONE", FeedType::FEED_TYPE_NONE)
                .value("FEED_TYPE_CONSOLIDATED", FeedType::FEED_TYPE_CONSOLIDATED)
                .value("FEED_TYPE_DIRECT", FeedType::FEED_TYPE_DIRECT)
                .value("FEED_TYPE_DEPTH", FeedType::FEED_TYPE_DEPTH)
                .value("FEED_TYPE_TOP", FeedType::FEED_TYPE_TOP)
                .value("FEED_TYPE_BEST", FeedType::FEED_TYPE_BEST)
                .export_values();
        
             py::enum_<MarketType>(m, "MarketType")
                .value("MARKET_TYPE_UNKNOWN", MarketType::MARKET_TYPE_UNKNOWN)
                .value("MARKET_TYPE_US_EQUITIES", MarketType::MARKET_TYPE_US_EQUITIES)
                .value("MARKET_TYPE_GLOBEX", MarketType::MARKET_TYPE_GLOBEX)
                .value("MARKET_TYPE_US_EQUITY_OPTIONS", MarketType::MARKET_TYPE_US_EQUITY_OPTIONS)
                .value("MARKET_TYPE_SPOT_FX", MarketType::MARKET_TYPE_SPOT_FX)
                .value("MARKET_TYPE_BRAZIL", MarketType::MARKET_TYPE_BRAZIL)
                .value("MARKET_TYPE_LONDON", MarketType::MARKET_TYPE_LONDON)
                .value("MARKET_TYPE_FRANKFORT", MarketType::MARKET_TYPE_FRANKFORT)
                .value("MARKET_TYPE_PARIS", MarketType::MARKET_TYPE_PARIS)
                .value("MARKET_TYPE_MILAN", MarketType::MARKET_TYPE_MILAN)
                .value("MARKET_TYPE_ICE", MarketType::MARKET_TYPE_ICE)
                .value("MARKET_TYPE_EUREX", MarketType::MARKET_TYPE_EUREX)
                .value("MARKET_TYPE_CBOE_FUTURES", MarketType::MARKET_TYPE_CBOE_FUTURES)
                .value("MARKET_TYPE_BOND", MarketType::MARKET_TYPE_BOND)
                .value("MARKET_TYPE_INDONESIA", MarketType::MARKET_TYPE_INDONESIA)
                .value("MARKET_TYPE_MALAYSIA", MarketType::MARKET_TYPE_MALAYSIA)
                .value("MARKET_TYPE_SINGAPORE", MarketType::MARKET_TYPE_SINGAPORE)
                .value("MARKET_TYPE_CA_EQUITIES", MarketType::MARKET_TYPE_CA_EQUITIES)
                .value("MARKET_TYPE_ASX", MarketType::MARKET_TYPE_ASX)
                .value("MARKET_TYPE_MONTREAL", MarketType::MARKET_TYPE_MONTREAL)
                .value("MARKET_TYPE_NASDAQ_FUTURES", MarketType::MARKET_TYPE_NASDAQ_FUTURES)
                .value("MARKET_TYPE_TOCOM", MarketType::MARKET_TYPE_TOCOM)
                .value("MARKET_TYPE_SGX", MarketType::MARKET_TYPE_SGX)
                .export_values();
    }

    void bind_event_enums(py::module &m) {
        py::enum_<EventType>(m, "EventType")
            .value("EVENT_TYPE_UNKNOWN", EventType::EVENT_TYPE_UNKNOWN)
            .value("EVENT_TYPE_DATA_SOURCE", EventType::EVENT_TYPE_DATA_SOURCE)
            .value("EVENT_TYPE_ORDER_UPDATE", EventType::EVENT_TYPE_ORDER_UPDATE)
            .value("EVENT_TYPE_CONTROL", EventType::EVENT_TYPE_CONTROL)
            .value("EVENT_TYPE_BROADCAST_CONTROL", EventType::EVENT_TYPE_BROADCAST_CONTROL)
            .value("EVENT_TYPE_BAR", EventType::EVENT_TYPE_BAR)
            // .value("EVENT_TYPE_STRATEGY_STATE_CHANGE", EventType::EVENT_TYPE_STRATEGY_STATE_CHANGE)
            .value("EVENT_TYPE_CORP_ACTION", EventType::EVENT_TYPE_CORP_ACTION)
            .value("EVENT_TYPE_APP_STATE_CHANGE", EventType::EVENT_TYPE_APP_STATE_CHANGE)
            .value("EVENT_TYPE_MARKET_DATA", EventType::EVENT_TYPE_MARKET_DATA)
            .value("EVENT_TYPE_REFERENCE_DATA_SOURCE", EventType::EVENT_TYPE_REFERENCE_DATA_SOURCE)
            .value("EVENT_TYPE_NEWS_SOURCE", EventType::EVENT_TYPE_NEWS_SOURCE)
            .value("EVENT_TYPE_SENTIMENT", EventType::EVENT_TYPE_SENTIMENT)
            .value("EVENT_TYPE_REPLAY", EventType::EVENT_TYPE_REPLAY)
            .value("EVENT_TYPE_ORDER_RESYNC", EventType::EVENT_TYPE_ORDER_RESYNC)
            .value("EVENT_TYPE_SCHEDULED", EventType::EVENT_TYPE_SCHEDULED)
            .value("EVENT_TYPE_STRATEGY_NOTIFY", EventType::EVENT_TYPE_STRATEGY_NOTIFY)
            // .value("EVENT_TYPE_STRATEGY_INSTANCE_STATE_CHANGE", EventType::EVENT_TYPE_STRATEGY_INSTANCE_STATE_CHANGE)
            .value("EVENT_TYPE_STRATEGY_EXTERNAL_FILL_NOTIFY", EventType::EVENT_TYPE_STRATEGY_EXTERNAL_FILL_NOTIFY)
            .value("EVENT_TYPE_EXTERNAL_ORDER", EventType::EVENT_TYPE_EXTERNAL_ORDER)
            .value("EVENT_TYPE_ACCOUNT_FEES_CHANGE", EventType::EVENT_TYPE_ACCOUNT_FEES_CHANGE)
            .value("EVENT_TYPE_TOPIC_SUBSCRIPTION", EventType::EVENT_TYPE_TOPIC_SUBSCRIPTION)
            .value("EVENT_TYPE_INTERNAL_SERVER_NOTIFY", EventType::EVENT_TYPE_INTERNAL_SERVER_NOTIFY)
            // .value("EVENT_TYPE_EVENT_CLOSURE", EventType::EVENT_TYPE_EVENT_CLOSURE)
            .export_values();

        py::enum_<ScheduledEventType>(m, "ScheduledEventType")
            .value("SCHEDULED_EVENT_TYPE_UNKNOWN", ScheduledEventType::SCHEDULED_EVENT_TYPE_UNKNOWN)
            .value("SCHEDULED_EVENT_TYPE_SINGLE", ScheduledEventType::SCHEDULED_EVENT_TYPE_SINGLE)
            .value("SCHEDULED_EVENT_TYPE_RECURRING", ScheduledEventType::SCHEDULED_EVENT_TYPE_RECURRING)
            .export_values();
    }

} // namespace bindings


