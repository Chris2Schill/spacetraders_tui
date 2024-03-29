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



#include "CppRestOpenAPIClient/model/Transfer_Cargo_Request.h"

namespace models {



Transfer_Cargo_Request::Transfer_Cargo_Request()
{
    m_TradeSymbolIsSet = false;
    m_Units = 0;
    m_UnitsIsSet = false;
    m_ShipSymbol = utility::conversions::to_string_t("");
    m_ShipSymbolIsSet = false;
}

Transfer_Cargo_Request::~Transfer_Cargo_Request()
{
}

void Transfer_Cargo_Request::validate()
{
    // TODO: implement validation
}

web::json::value Transfer_Cargo_Request::toJson() const
{

    web::json::value val = web::json::value::object();
    
    if(m_TradeSymbolIsSet)
    {
        val[utility::conversions::to_string_t(U("tradeSymbol"))] = ModelBase::toJson(m_TradeSymbol);
    }
    if(m_UnitsIsSet)
    {
        val[utility::conversions::to_string_t(U("units"))] = ModelBase::toJson(m_Units);
    }
    if(m_ShipSymbolIsSet)
    {
        val[utility::conversions::to_string_t(U("shipSymbol"))] = ModelBase::toJson(m_ShipSymbol);
    }

    return val;
}

bool Transfer_Cargo_Request::fromJson(const web::json::value& val)
{
    bool ok = true;
    
    if(val.has_field(utility::conversions::to_string_t(U("tradeSymbol"))))
    {
        const web::json::value& fieldValue = val.at(utility::conversions::to_string_t(U("tradeSymbol")));
        if(!fieldValue.is_null())
        {
            std::shared_ptr<TradeSymbol> refVal_setTradeSymbol;
            ok &= ModelBase::fromJson(fieldValue, refVal_setTradeSymbol);
            setTradeSymbol(refVal_setTradeSymbol);
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
    return ok;
}

void Transfer_Cargo_Request::toMultipart(std::shared_ptr<MultipartFormData> multipart, const utility::string_t& prefix) const
{
    utility::string_t namePrefix = prefix;
    if(namePrefix.size() > 0 && namePrefix.substr(namePrefix.size() - 1) != utility::conversions::to_string_t(U(".")))
    {
        namePrefix += utility::conversions::to_string_t(U("."));
    }
    if(m_TradeSymbolIsSet)
    {
        multipart->add(ModelBase::toHttpContent(namePrefix + utility::conversions::to_string_t(U("tradeSymbol")), m_TradeSymbol));
    }
    if(m_UnitsIsSet)
    {
        multipart->add(ModelBase::toHttpContent(namePrefix + utility::conversions::to_string_t(U("units")), m_Units));
    }
    if(m_ShipSymbolIsSet)
    {
        multipart->add(ModelBase::toHttpContent(namePrefix + utility::conversions::to_string_t(U("shipSymbol")), m_ShipSymbol));
    }
}

bool Transfer_Cargo_Request::fromMultiPart(std::shared_ptr<MultipartFormData> multipart, const utility::string_t& prefix)
{
    bool ok = true;
    utility::string_t namePrefix = prefix;
    if(namePrefix.size() > 0 && namePrefix.substr(namePrefix.size() - 1) != utility::conversions::to_string_t(U(".")))
    {
        namePrefix += utility::conversions::to_string_t(U("."));
    }

    if(multipart->hasContent(utility::conversions::to_string_t(U("tradeSymbol"))))
    {
        std::shared_ptr<TradeSymbol> refVal_setTradeSymbol;
        ok &= ModelBase::fromHttpContent(multipart->getContent(utility::conversions::to_string_t(U("tradeSymbol"))), refVal_setTradeSymbol );
        setTradeSymbol(refVal_setTradeSymbol);
    }
    if(multipart->hasContent(utility::conversions::to_string_t(U("units"))))
    {
        int32_t refVal_setUnits;
        ok &= ModelBase::fromHttpContent(multipart->getContent(utility::conversions::to_string_t(U("units"))), refVal_setUnits );
        setUnits(refVal_setUnits);
    }
    if(multipart->hasContent(utility::conversions::to_string_t(U("shipSymbol"))))
    {
        utility::string_t refVal_setShipSymbol;
        ok &= ModelBase::fromHttpContent(multipart->getContent(utility::conversions::to_string_t(U("shipSymbol"))), refVal_setShipSymbol );
        setShipSymbol(refVal_setShipSymbol);
    }
    return ok;
}

std::shared_ptr<TradeSymbol> Transfer_Cargo_Request::getTradeSymbol() const
{
    return m_TradeSymbol;
}

void Transfer_Cargo_Request::setTradeSymbol(const std::shared_ptr<TradeSymbol>& value)
{
    m_TradeSymbol = value;
    m_TradeSymbolIsSet = true;
}

bool Transfer_Cargo_Request::tradeSymbolIsSet() const
{
    return m_TradeSymbolIsSet;
}

void Transfer_Cargo_Request::unsetTradeSymbol()
{
    m_TradeSymbolIsSet = false;
}
int32_t Transfer_Cargo_Request::getUnits() const
{
    return m_Units;
}

void Transfer_Cargo_Request::setUnits(int32_t value)
{
    m_Units = value;
    m_UnitsIsSet = true;
}

bool Transfer_Cargo_Request::unitsIsSet() const
{
    return m_UnitsIsSet;
}

void Transfer_Cargo_Request::unsetUnits()
{
    m_UnitsIsSet = false;
}
utility::string_t Transfer_Cargo_Request::getShipSymbol() const
{
    return m_ShipSymbol;
}

void Transfer_Cargo_Request::setShipSymbol(const utility::string_t& value)
{
    m_ShipSymbol = value;
    m_ShipSymbolIsSet = true;
}

bool Transfer_Cargo_Request::shipSymbolIsSet() const
{
    return m_ShipSymbolIsSet;
}

void Transfer_Cargo_Request::unsetShipSymbol()
{
    m_ShipSymbolIsSet = false;
}
}


