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



#include "CppRestOpenAPIClient/model/Ship_Refine_201_Response_data_produced_inner.h"

namespace models {



Ship_Refine_201_Response_data_produced_inner::Ship_Refine_201_Response_data_produced_inner()
{
    m_TradeSymbol = utility::conversions::to_string_t("");
    m_TradeSymbolIsSet = false;
    m_Units = 0;
    m_UnitsIsSet = false;
}

Ship_Refine_201_Response_data_produced_inner::~Ship_Refine_201_Response_data_produced_inner()
{
}

void Ship_Refine_201_Response_data_produced_inner::validate()
{
    // TODO: implement validation
}

web::json::value Ship_Refine_201_Response_data_produced_inner::toJson() const
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

    return val;
}

bool Ship_Refine_201_Response_data_produced_inner::fromJson(const web::json::value& val)
{
    bool ok = true;
    
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
    return ok;
}

void Ship_Refine_201_Response_data_produced_inner::toMultipart(std::shared_ptr<MultipartFormData> multipart, const utility::string_t& prefix) const
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
}

bool Ship_Refine_201_Response_data_produced_inner::fromMultiPart(std::shared_ptr<MultipartFormData> multipart, const utility::string_t& prefix)
{
    bool ok = true;
    utility::string_t namePrefix = prefix;
    if(namePrefix.size() > 0 && namePrefix.substr(namePrefix.size() - 1) != utility::conversions::to_string_t(U(".")))
    {
        namePrefix += utility::conversions::to_string_t(U("."));
    }

    if(multipart->hasContent(utility::conversions::to_string_t(U("tradeSymbol"))))
    {
        utility::string_t refVal_setTradeSymbol;
        ok &= ModelBase::fromHttpContent(multipart->getContent(utility::conversions::to_string_t(U("tradeSymbol"))), refVal_setTradeSymbol );
        setTradeSymbol(refVal_setTradeSymbol);
    }
    if(multipart->hasContent(utility::conversions::to_string_t(U("units"))))
    {
        int32_t refVal_setUnits;
        ok &= ModelBase::fromHttpContent(multipart->getContent(utility::conversions::to_string_t(U("units"))), refVal_setUnits );
        setUnits(refVal_setUnits);
    }
    return ok;
}

utility::string_t Ship_Refine_201_Response_data_produced_inner::getTradeSymbol() const
{
    return m_TradeSymbol;
}

void Ship_Refine_201_Response_data_produced_inner::setTradeSymbol(const utility::string_t& value)
{
    m_TradeSymbol = value;
    m_TradeSymbolIsSet = true;
}

bool Ship_Refine_201_Response_data_produced_inner::tradeSymbolIsSet() const
{
    return m_TradeSymbolIsSet;
}

void Ship_Refine_201_Response_data_produced_inner::unsetTradeSymbol()
{
    m_TradeSymbolIsSet = false;
}
int32_t Ship_Refine_201_Response_data_produced_inner::getUnits() const
{
    return m_Units;
}

void Ship_Refine_201_Response_data_produced_inner::setUnits(int32_t value)
{
    m_Units = value;
    m_UnitsIsSet = true;
}

bool Ship_Refine_201_Response_data_produced_inner::unitsIsSet() const
{
    return m_UnitsIsSet;
}

void Ship_Refine_201_Response_data_produced_inner::unsetUnits()
{
    m_UnitsIsSet = false;
}
}

