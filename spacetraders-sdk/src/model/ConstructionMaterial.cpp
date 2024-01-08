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



#include "CppRestOpenAPIClient/model/ConstructionMaterial.h"

namespace models {



ConstructionMaterial::ConstructionMaterial()
{
    m_TradeSymbolIsSet = false;
    m_Required = 0;
    m_RequiredIsSet = false;
    m_Fulfilled = 0;
    m_FulfilledIsSet = false;
}

ConstructionMaterial::~ConstructionMaterial()
{
}

void ConstructionMaterial::validate()
{
    // TODO: implement validation
}

web::json::value ConstructionMaterial::toJson() const
{

    web::json::value val = web::json::value::object();
    
    if(m_TradeSymbolIsSet)
    {
        val[utility::conversions::to_string_t(U("tradeSymbol"))] = ModelBase::toJson(m_TradeSymbol);
    }
    if(m_RequiredIsSet)
    {
        val[utility::conversions::to_string_t(U("required"))] = ModelBase::toJson(m_Required);
    }
    if(m_FulfilledIsSet)
    {
        val[utility::conversions::to_string_t(U("fulfilled"))] = ModelBase::toJson(m_Fulfilled);
    }

    return val;
}

bool ConstructionMaterial::fromJson(const web::json::value& val)
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
    if(val.has_field(utility::conversions::to_string_t(U("required"))))
    {
        const web::json::value& fieldValue = val.at(utility::conversions::to_string_t(U("required")));
        if(!fieldValue.is_null())
        {
            int32_t refVal_setRequired;
            ok &= ModelBase::fromJson(fieldValue, refVal_setRequired);
            setRequired(refVal_setRequired);
        }
    }
    if(val.has_field(utility::conversions::to_string_t(U("fulfilled"))))
    {
        const web::json::value& fieldValue = val.at(utility::conversions::to_string_t(U("fulfilled")));
        if(!fieldValue.is_null())
        {
            int32_t refVal_setFulfilled;
            ok &= ModelBase::fromJson(fieldValue, refVal_setFulfilled);
            setFulfilled(refVal_setFulfilled);
        }
    }
    return ok;
}

void ConstructionMaterial::toMultipart(std::shared_ptr<MultipartFormData> multipart, const utility::string_t& prefix) const
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
    if(m_RequiredIsSet)
    {
        multipart->add(ModelBase::toHttpContent(namePrefix + utility::conversions::to_string_t(U("required")), m_Required));
    }
    if(m_FulfilledIsSet)
    {
        multipart->add(ModelBase::toHttpContent(namePrefix + utility::conversions::to_string_t(U("fulfilled")), m_Fulfilled));
    }
}

bool ConstructionMaterial::fromMultiPart(std::shared_ptr<MultipartFormData> multipart, const utility::string_t& prefix)
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
    if(multipart->hasContent(utility::conversions::to_string_t(U("required"))))
    {
        int32_t refVal_setRequired;
        ok &= ModelBase::fromHttpContent(multipart->getContent(utility::conversions::to_string_t(U("required"))), refVal_setRequired );
        setRequired(refVal_setRequired);
    }
    if(multipart->hasContent(utility::conversions::to_string_t(U("fulfilled"))))
    {
        int32_t refVal_setFulfilled;
        ok &= ModelBase::fromHttpContent(multipart->getContent(utility::conversions::to_string_t(U("fulfilled"))), refVal_setFulfilled );
        setFulfilled(refVal_setFulfilled);
    }
    return ok;
}

std::shared_ptr<TradeSymbol> ConstructionMaterial::getTradeSymbol() const
{
    return m_TradeSymbol;
}

void ConstructionMaterial::setTradeSymbol(const std::shared_ptr<TradeSymbol>& value)
{
    m_TradeSymbol = value;
    m_TradeSymbolIsSet = true;
}

bool ConstructionMaterial::tradeSymbolIsSet() const
{
    return m_TradeSymbolIsSet;
}

void ConstructionMaterial::unsetTradeSymbol()
{
    m_TradeSymbolIsSet = false;
}
int32_t ConstructionMaterial::getRequired() const
{
    return m_Required;
}

void ConstructionMaterial::setRequired(int32_t value)
{
    m_Required = value;
    m_RequiredIsSet = true;
}

bool ConstructionMaterial::requiredIsSet() const
{
    return m_RequiredIsSet;
}

void ConstructionMaterial::unsetRequired()
{
    m_RequiredIsSet = false;
}
int32_t ConstructionMaterial::getFulfilled() const
{
    return m_Fulfilled;
}

void ConstructionMaterial::setFulfilled(int32_t value)
{
    m_Fulfilled = value;
    m_FulfilledIsSet = true;
}

bool ConstructionMaterial::fulfilledIsSet() const
{
    return m_FulfilledIsSet;
}

void ConstructionMaterial::unsetFulfilled()
{
    m_FulfilledIsSet = false;
}
}


