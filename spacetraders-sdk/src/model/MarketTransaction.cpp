/**
 * SpaceTraders API
 * SpaceTraders is an open-universe game and learning platform that offers a set of HTTP endpoints to control a fleet of ships and explore a multiplayer universe.  The API is documented using [OpenAPI](https://github.com/SpaceTradersAPI/api-docs). You can send your first request right here in your browser to check the status of the game server.  ```json http {   \"method\": \"GET\",   \"url\": \"https://api.spacetraders.io/v2\", } ```  Unlike a traditional game, SpaceTraders does not have a first-party client or app to play the game. Instead, you can use the API to build your own client, write a script to automate your ships, or try an app built by the community.  We have a [Discord channel](https://discord.com/invite/jh6zurdWk5) where you can share your projects, ask questions, and get help from other players.   
 *
 * The version of the OpenAPI document: 2.0.0
 * Contact: joel@spacetraders.io
 *
 * NOTE: This class is auto generated by OpenAPI-Generator 7.2.0.
 * https://openapi-generator.tech
 * Do not edit the class manually.
 */



#include "CppRestOpenAPIClient/model/MarketTransaction.h"

namespace models {



MarketTransaction::MarketTransaction()
{
    m_WaypointSymbol = utility::conversions::to_string_t("");
    m_WaypointSymbolIsSet = false;
    m_ShipSymbol = utility::conversions::to_string_t("");
    m_ShipSymbolIsSet = false;
    m_TradeSymbol = utility::conversions::to_string_t("");
    m_TradeSymbolIsSet = false;
    m_Type = utility::conversions::to_string_t("");
    m_TypeIsSet = false;
    m_Units = 0;
    m_UnitsIsSet = false;
    m_PricePerUnit = 0;
    m_PricePerUnitIsSet = false;
    m_TotalPrice = 0;
    m_TotalPriceIsSet = false;
    m_Timestamp = utility::datetime();
    m_TimestampIsSet = false;
}

MarketTransaction::~MarketTransaction()
{
}

void MarketTransaction::validate()
{
    // TODO: implement validation
}

web::json::value MarketTransaction::toJson() const
{

    web::json::value val = web::json::value::object();
    
    if(m_WaypointSymbolIsSet)
    {
        val[utility::conversions::to_string_t(U("waypointSymbol"))] = ModelBase::toJson(m_WaypointSymbol);
    }
    if(m_ShipSymbolIsSet)
    {
        val[utility::conversions::to_string_t(U("shipSymbol"))] = ModelBase::toJson(m_ShipSymbol);
    }
    if(m_TradeSymbolIsSet)
    {
        val[utility::conversions::to_string_t(U("tradeSymbol"))] = ModelBase::toJson(m_TradeSymbol);
    }
    if(m_TypeIsSet)
    {
        val[utility::conversions::to_string_t(U("type"))] = ModelBase::toJson(m_Type);
    }
    if(m_UnitsIsSet)
    {
        val[utility::conversions::to_string_t(U("units"))] = ModelBase::toJson(m_Units);
    }
    if(m_PricePerUnitIsSet)
    {
        val[utility::conversions::to_string_t(U("pricePerUnit"))] = ModelBase::toJson(m_PricePerUnit);
    }
    if(m_TotalPriceIsSet)
    {
        val[utility::conversions::to_string_t(U("totalPrice"))] = ModelBase::toJson(m_TotalPrice);
    }
    if(m_TimestampIsSet)
    {
        val[utility::conversions::to_string_t(U("timestamp"))] = ModelBase::toJson(m_Timestamp);
    }

    return val;
}

bool MarketTransaction::fromJson(const web::json::value& val)
{
    bool ok = true;
    
    if(val.has_field(utility::conversions::to_string_t(U("waypointSymbol"))))
    {
        const web::json::value& fieldValue = val.at(utility::conversions::to_string_t(U("waypointSymbol")));
        if(!fieldValue.is_null())
        {
            utility::string_t refVal_setWaypointSymbol;
            ok &= ModelBase::fromJson(fieldValue, refVal_setWaypointSymbol);
            setWaypointSymbol(refVal_setWaypointSymbol);
        }
    }
    if(val.has_field(utility::conversions::to_string_t(U("shipSymbol"))))
    {
        const web::json::value& fieldValue = val.at(utility::conversions::to_string_t(U("shipSymbol")));
        if(!fieldValue.is_null())
        {
            utility::string_t refVal_setShipSymbol;
            ok &= ModelBase::fromJson(fieldValue, refVal_setShipSymbol);
            setShipSymbol(refVal_setShipSymbol);
        }
    }
    if(val.has_field(utility::conversions::to_string_t(U("tradeSymbol"))))
    {
        const web::json::value& fieldValue = val.at(utility::conversions::to_string_t(U("tradeSymbol")));
        if(!fieldValue.is_null())
        {
            utility::string_t refVal_setTradeSymbol;
            ok &= ModelBase::fromJson(fieldValue, refVal_setTradeSymbol);
            setTradeSymbol(refVal_setTradeSymbol);
        }
    }
    if(val.has_field(utility::conversions::to_string_t(U("type"))))
    {
        const web::json::value& fieldValue = val.at(utility::conversions::to_string_t(U("type")));
        if(!fieldValue.is_null())
        {
            utility::string_t refVal_setType;
            ok &= ModelBase::fromJson(fieldValue, refVal_setType);
            setType(refVal_setType);
        }
    }
    if(val.has_field(utility::conversions::to_string_t(U("units"))))
    {
        const web::json::value& fieldValue = val.at(utility::conversions::to_string_t(U("units")));
        if(!fieldValue.is_null())
        {
            int32_t refVal_setUnits;
            ok &= ModelBase::fromJson(fieldValue, refVal_setUnits);
            setUnits(refVal_setUnits);
        }
    }
    if(val.has_field(utility::conversions::to_string_t(U("pricePerUnit"))))
    {
        const web::json::value& fieldValue = val.at(utility::conversions::to_string_t(U("pricePerUnit")));
        if(!fieldValue.is_null())
        {
            int32_t refVal_setPricePerUnit;
            ok &= ModelBase::fromJson(fieldValue, refVal_setPricePerUnit);
            setPricePerUnit(refVal_setPricePerUnit);
        }
    }
    if(val.has_field(utility::conversions::to_string_t(U("totalPrice"))))
    {
        const web::json::value& fieldValue = val.at(utility::conversions::to_string_t(U("totalPrice")));
        if(!fieldValue.is_null())
        {
            int32_t refVal_setTotalPrice;
            ok &= ModelBase::fromJson(fieldValue, refVal_setTotalPrice);
            setTotalPrice(refVal_setTotalPrice);
        }
    }
    if(val.has_field(utility::conversions::to_string_t(U("timestamp"))))
    {
        const web::json::value& fieldValue = val.at(utility::conversions::to_string_t(U("timestamp")));
        if(!fieldValue.is_null())
        {
            utility::datetime refVal_setTimestamp;
            ok &= ModelBase::fromJson(fieldValue, refVal_setTimestamp);
            setTimestamp(refVal_setTimestamp);
        }
    }
    return ok;
}

void MarketTransaction::toMultipart(std::shared_ptr<MultipartFormData> multipart, const utility::string_t& prefix) const
{
    utility::string_t namePrefix = prefix;
    if(namePrefix.size() > 0 && namePrefix.substr(namePrefix.size() - 1) != utility::conversions::to_string_t(U(".")))
    {
        namePrefix += utility::conversions::to_string_t(U("."));
    }
    if(m_WaypointSymbolIsSet)
    {
        multipart->add(ModelBase::toHttpContent(namePrefix + utility::conversions::to_string_t(U("waypointSymbol")), m_WaypointSymbol));
    }
    if(m_ShipSymbolIsSet)
    {
        multipart->add(ModelBase::toHttpContent(namePrefix + utility::conversions::to_string_t(U("shipSymbol")), m_ShipSymbol));
    }
    if(m_TradeSymbolIsSet)
    {
        multipart->add(ModelBase::toHttpContent(namePrefix + utility::conversions::to_string_t(U("tradeSymbol")), m_TradeSymbol));
    }
    if(m_TypeIsSet)
    {
        multipart->add(ModelBase::toHttpContent(namePrefix + utility::conversions::to_string_t(U("type")), m_Type));
    }
    if(m_UnitsIsSet)
    {
        multipart->add(ModelBase::toHttpContent(namePrefix + utility::conversions::to_string_t(U("units")), m_Units));
    }
    if(m_PricePerUnitIsSet)
    {
        multipart->add(ModelBase::toHttpContent(namePrefix + utility::conversions::to_string_t(U("pricePerUnit")), m_PricePerUnit));
    }
    if(m_TotalPriceIsSet)
    {
        multipart->add(ModelBase::toHttpContent(namePrefix + utility::conversions::to_string_t(U("totalPrice")), m_TotalPrice));
    }
    if(m_TimestampIsSet)
    {
        multipart->add(ModelBase::toHttpContent(namePrefix + utility::conversions::to_string_t(U("timestamp")), m_Timestamp));
    }
}

bool MarketTransaction::fromMultiPart(std::shared_ptr<MultipartFormData> multipart, const utility::string_t& prefix)
{
    bool ok = true;
    utility::string_t namePrefix = prefix;
    if(namePrefix.size() > 0 && namePrefix.substr(namePrefix.size() - 1) != utility::conversions::to_string_t(U(".")))
    {
        namePrefix += utility::conversions::to_string_t(U("."));
    }

    if(multipart->hasContent(utility::conversions::to_string_t(U("waypointSymbol"))))
    {
        utility::string_t refVal_setWaypointSymbol;
        ok &= ModelBase::fromHttpContent(multipart->getContent(utility::conversions::to_string_t(U("waypointSymbol"))), refVal_setWaypointSymbol );
        setWaypointSymbol(refVal_setWaypointSymbol);
    }
    if(multipart->hasContent(utility::conversions::to_string_t(U("shipSymbol"))))
    {
        utility::string_t refVal_setShipSymbol;
        ok &= ModelBase::fromHttpContent(multipart->getContent(utility::conversions::to_string_t(U("shipSymbol"))), refVal_setShipSymbol );
        setShipSymbol(refVal_setShipSymbol);
    }
    if(multipart->hasContent(utility::conversions::to_string_t(U("tradeSymbol"))))
    {
        utility::string_t refVal_setTradeSymbol;
        ok &= ModelBase::fromHttpContent(multipart->getContent(utility::conversions::to_string_t(U("tradeSymbol"))), refVal_setTradeSymbol );
        setTradeSymbol(refVal_setTradeSymbol);
    }
    if(multipart->hasContent(utility::conversions::to_string_t(U("type"))))
    {
        utility::string_t refVal_setType;
        ok &= ModelBase::fromHttpContent(multipart->getContent(utility::conversions::to_string_t(U("type"))), refVal_setType );
        setType(refVal_setType);
    }
    if(multipart->hasContent(utility::conversions::to_string_t(U("units"))))
    {
        int32_t refVal_setUnits;
        ok &= ModelBase::fromHttpContent(multipart->getContent(utility::conversions::to_string_t(U("units"))), refVal_setUnits );
        setUnits(refVal_setUnits);
    }
    if(multipart->hasContent(utility::conversions::to_string_t(U("pricePerUnit"))))
    {
        int32_t refVal_setPricePerUnit;
        ok &= ModelBase::fromHttpContent(multipart->getContent(utility::conversions::to_string_t(U("pricePerUnit"))), refVal_setPricePerUnit );
        setPricePerUnit(refVal_setPricePerUnit);
    }
    if(multipart->hasContent(utility::conversions::to_string_t(U("totalPrice"))))
    {
        int32_t refVal_setTotalPrice;
        ok &= ModelBase::fromHttpContent(multipart->getContent(utility::conversions::to_string_t(U("totalPrice"))), refVal_setTotalPrice );
        setTotalPrice(refVal_setTotalPrice);
    }
    if(multipart->hasContent(utility::conversions::to_string_t(U("timestamp"))))
    {
        utility::datetime refVal_setTimestamp;
        ok &= ModelBase::fromHttpContent(multipart->getContent(utility::conversions::to_string_t(U("timestamp"))), refVal_setTimestamp );
        setTimestamp(refVal_setTimestamp);
    }
    return ok;
}

utility::string_t MarketTransaction::getWaypointSymbol() const
{
    return m_WaypointSymbol;
}

void MarketTransaction::setWaypointSymbol(const utility::string_t& value)
{
    m_WaypointSymbol = value;
    m_WaypointSymbolIsSet = true;
}

bool MarketTransaction::waypointSymbolIsSet() const
{
    return m_WaypointSymbolIsSet;
}

void MarketTransaction::unsetWaypointSymbol()
{
    m_WaypointSymbolIsSet = false;
}
utility::string_t MarketTransaction::getShipSymbol() const
{
    return m_ShipSymbol;
}

void MarketTransaction::setShipSymbol(const utility::string_t& value)
{
    m_ShipSymbol = value;
    m_ShipSymbolIsSet = true;
}

bool MarketTransaction::shipSymbolIsSet() const
{
    return m_ShipSymbolIsSet;
}

void MarketTransaction::unsetShipSymbol()
{
    m_ShipSymbolIsSet = false;
}
utility::string_t MarketTransaction::getTradeSymbol() const
{
    return m_TradeSymbol;
}

void MarketTransaction::setTradeSymbol(const utility::string_t& value)
{
    m_TradeSymbol = value;
    m_TradeSymbolIsSet = true;
}

bool MarketTransaction::tradeSymbolIsSet() const
{
    return m_TradeSymbolIsSet;
}

void MarketTransaction::unsetTradeSymbol()
{
    m_TradeSymbolIsSet = false;
}
utility::string_t MarketTransaction::getType() const
{
    return m_Type;
}

void MarketTransaction::setType(const utility::string_t& value)
{
    m_Type = value;
    m_TypeIsSet = true;
}

bool MarketTransaction::typeIsSet() const
{
    return m_TypeIsSet;
}

void MarketTransaction::unsetType()
{
    m_TypeIsSet = false;
}
int32_t MarketTransaction::getUnits() const
{
    return m_Units;
}

void MarketTransaction::setUnits(int32_t value)
{
    m_Units = value;
    m_UnitsIsSet = true;
}

bool MarketTransaction::unitsIsSet() const
{
    return m_UnitsIsSet;
}

void MarketTransaction::unsetUnits()
{
    m_UnitsIsSet = false;
}
int32_t MarketTransaction::getPricePerUnit() const
{
    return m_PricePerUnit;
}

void MarketTransaction::setPricePerUnit(int32_t value)
{
    m_PricePerUnit = value;
    m_PricePerUnitIsSet = true;
}

bool MarketTransaction::pricePerUnitIsSet() const
{
    return m_PricePerUnitIsSet;
}

void MarketTransaction::unsetPricePerUnit()
{
    m_PricePerUnitIsSet = false;
}
int32_t MarketTransaction::getTotalPrice() const
{
    return m_TotalPrice;
}

void MarketTransaction::setTotalPrice(int32_t value)
{
    m_TotalPrice = value;
    m_TotalPriceIsSet = true;
}

bool MarketTransaction::totalPriceIsSet() const
{
    return m_TotalPriceIsSet;
}

void MarketTransaction::unsetTotalPrice()
{
    m_TotalPriceIsSet = false;
}
utility::datetime MarketTransaction::getTimestamp() const
{
    return m_Timestamp;
}

void MarketTransaction::setTimestamp(const utility::datetime& value)
{
    m_Timestamp = value;
    m_TimestampIsSet = true;
}

bool MarketTransaction::timestampIsSet() const
{
    return m_TimestampIsSet;
}

void MarketTransaction::unsetTimestamp()
{
    m_TimestampIsSet = false;
}
}


