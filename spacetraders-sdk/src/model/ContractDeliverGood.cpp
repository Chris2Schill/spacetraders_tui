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



#include "CppRestOpenAPIClient/model/ContractDeliverGood.h"

namespace models {



ContractDeliverGood::ContractDeliverGood()
{
    m_TradeSymbol = utility::conversions::to_string_t("");
    m_TradeSymbolIsSet = false;
    m_DestinationSymbol = utility::conversions::to_string_t("");
    m_DestinationSymbolIsSet = false;
    m_UnitsRequired = 0;
    m_UnitsRequiredIsSet = false;
    m_UnitsFulfilled = 0;
    m_UnitsFulfilledIsSet = false;
}

ContractDeliverGood::~ContractDeliverGood()
{
}

void ContractDeliverGood::validate()
{
    // TODO: implement validation
}

web::json::value ContractDeliverGood::toJson() const
{

    web::json::value val = web::json::value::object();
    
    if(m_TradeSymbolIsSet)
    {
        val[utility::conversions::to_string_t(U("tradeSymbol"))] = ModelBase::toJson(m_TradeSymbol);
    }
    if(m_DestinationSymbolIsSet)
    {
        val[utility::conversions::to_string_t(U("destinationSymbol"))] = ModelBase::toJson(m_DestinationSymbol);
    }
    if(m_UnitsRequiredIsSet)
    {
        val[utility::conversions::to_string_t(U("unitsRequired"))] = ModelBase::toJson(m_UnitsRequired);
    }
    if(m_UnitsFulfilledIsSet)
    {
        val[utility::conversions::to_string_t(U("unitsFulfilled"))] = ModelBase::toJson(m_UnitsFulfilled);
    }

    return val;
}

bool ContractDeliverGood::fromJson(const web::json::value& val)
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
    if(val.has_field(utility::conversions::to_string_t(U("destinationSymbol"))))
    {
        const web::json::value& fieldValue = val.at(utility::conversions::to_string_t(U("destinationSymbol")));
        if(!fieldValue.is_null())
        {
            utility::string_t refVal_setDestinationSymbol;
            ok &= ModelBase::fromJson(fieldValue, refVal_setDestinationSymbol);
            setDestinationSymbol(refVal_setDestinationSymbol);
        }
    }
    if(val.has_field(utility::conversions::to_string_t(U("unitsRequired"))))
    {
        const web::json::value& fieldValue = val.at(utility::conversions::to_string_t(U("unitsRequired")));
        if(!fieldValue.is_null())
        {
            int32_t refVal_setUnitsRequired;
            ok &= ModelBase::fromJson(fieldValue, refVal_setUnitsRequired);
            setUnitsRequired(refVal_setUnitsRequired);
        }
    }
    if(val.has_field(utility::conversions::to_string_t(U("unitsFulfilled"))))
    {
        const web::json::value& fieldValue = val.at(utility::conversions::to_string_t(U("unitsFulfilled")));
        if(!fieldValue.is_null())
        {
            int32_t refVal_setUnitsFulfilled;
            ok &= ModelBase::fromJson(fieldValue, refVal_setUnitsFulfilled);
            setUnitsFulfilled(refVal_setUnitsFulfilled);
        }
    }
    return ok;
}

void ContractDeliverGood::toMultipart(std::shared_ptr<MultipartFormData> multipart, const utility::string_t& prefix) const
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
    if(m_DestinationSymbolIsSet)
    {
        multipart->add(ModelBase::toHttpContent(namePrefix + utility::conversions::to_string_t(U("destinationSymbol")), m_DestinationSymbol));
    }
    if(m_UnitsRequiredIsSet)
    {
        multipart->add(ModelBase::toHttpContent(namePrefix + utility::conversions::to_string_t(U("unitsRequired")), m_UnitsRequired));
    }
    if(m_UnitsFulfilledIsSet)
    {
        multipart->add(ModelBase::toHttpContent(namePrefix + utility::conversions::to_string_t(U("unitsFulfilled")), m_UnitsFulfilled));
    }
}

bool ContractDeliverGood::fromMultiPart(std::shared_ptr<MultipartFormData> multipart, const utility::string_t& prefix)
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
    if(multipart->hasContent(utility::conversions::to_string_t(U("destinationSymbol"))))
    {
        utility::string_t refVal_setDestinationSymbol;
        ok &= ModelBase::fromHttpContent(multipart->getContent(utility::conversions::to_string_t(U("destinationSymbol"))), refVal_setDestinationSymbol );
        setDestinationSymbol(refVal_setDestinationSymbol);
    }
    if(multipart->hasContent(utility::conversions::to_string_t(U("unitsRequired"))))
    {
        int32_t refVal_setUnitsRequired;
        ok &= ModelBase::fromHttpContent(multipart->getContent(utility::conversions::to_string_t(U("unitsRequired"))), refVal_setUnitsRequired );
        setUnitsRequired(refVal_setUnitsRequired);
    }
    if(multipart->hasContent(utility::conversions::to_string_t(U("unitsFulfilled"))))
    {
        int32_t refVal_setUnitsFulfilled;
        ok &= ModelBase::fromHttpContent(multipart->getContent(utility::conversions::to_string_t(U("unitsFulfilled"))), refVal_setUnitsFulfilled );
        setUnitsFulfilled(refVal_setUnitsFulfilled);
    }
    return ok;
}

utility::string_t ContractDeliverGood::getTradeSymbol() const
{
    return m_TradeSymbol;
}

void ContractDeliverGood::setTradeSymbol(const utility::string_t& value)
{
    m_TradeSymbol = value;
    m_TradeSymbolIsSet = true;
}

bool ContractDeliverGood::tradeSymbolIsSet() const
{
    return m_TradeSymbolIsSet;
}

void ContractDeliverGood::unsetTradeSymbol()
{
    m_TradeSymbolIsSet = false;
}
utility::string_t ContractDeliverGood::getDestinationSymbol() const
{
    return m_DestinationSymbol;
}

void ContractDeliverGood::setDestinationSymbol(const utility::string_t& value)
{
    m_DestinationSymbol = value;
    m_DestinationSymbolIsSet = true;
}

bool ContractDeliverGood::destinationSymbolIsSet() const
{
    return m_DestinationSymbolIsSet;
}

void ContractDeliverGood::unsetDestinationSymbol()
{
    m_DestinationSymbolIsSet = false;
}
int32_t ContractDeliverGood::getUnitsRequired() const
{
    return m_UnitsRequired;
}

void ContractDeliverGood::setUnitsRequired(int32_t value)
{
    m_UnitsRequired = value;
    m_UnitsRequiredIsSet = true;
}

bool ContractDeliverGood::unitsRequiredIsSet() const
{
    return m_UnitsRequiredIsSet;
}

void ContractDeliverGood::unsetUnitsRequired()
{
    m_UnitsRequiredIsSet = false;
}
int32_t ContractDeliverGood::getUnitsFulfilled() const
{
    return m_UnitsFulfilled;
}

void ContractDeliverGood::setUnitsFulfilled(int32_t value)
{
    m_UnitsFulfilled = value;
    m_UnitsFulfilledIsSet = true;
}

bool ContractDeliverGood::unitsFulfilledIsSet() const
{
    return m_UnitsFulfilledIsSet;
}

void ContractDeliverGood::unsetUnitsFulfilled()
{
    m_UnitsFulfilledIsSet = false;
}
}

