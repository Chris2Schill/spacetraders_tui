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



#include "CppRestOpenAPIClient/model/ShipCargoItem.h"

namespace models {



ShipCargoItem::ShipCargoItem()
{
    m_SymbolIsSet = false;
    m_Name = utility::conversions::to_string_t("");
    m_NameIsSet = false;
    m_Description = utility::conversions::to_string_t("");
    m_DescriptionIsSet = false;
    m_Units = 0;
    m_UnitsIsSet = false;
}

ShipCargoItem::~ShipCargoItem()
{
}

void ShipCargoItem::validate()
{
    // TODO: implement validation
}

web::json::value ShipCargoItem::toJson() const
{

    web::json::value val = web::json::value::object();
    
    if(m_SymbolIsSet)
    {
        val[utility::conversions::to_string_t(U("symbol"))] = ModelBase::toJson(m_Symbol);
    }
    if(m_NameIsSet)
    {
        val[utility::conversions::to_string_t(U("name"))] = ModelBase::toJson(m_Name);
    }
    if(m_DescriptionIsSet)
    {
        val[utility::conversions::to_string_t(U("description"))] = ModelBase::toJson(m_Description);
    }
    if(m_UnitsIsSet)
    {
        val[utility::conversions::to_string_t(U("units"))] = ModelBase::toJson(m_Units);
    }

    return val;
}

bool ShipCargoItem::fromJson(const web::json::value& val)
{
    bool ok = true;
    
    if(val.has_field(utility::conversions::to_string_t(U("symbol"))))
    {
        const web::json::value& fieldValue = val.at(utility::conversions::to_string_t(U("symbol")));
        if(!fieldValue.is_null())
        {
            std::shared_ptr<TradeSymbol> refVal_setSymbol;
            ok &= ModelBase::fromJson(fieldValue, refVal_setSymbol);
            setSymbol(refVal_setSymbol);
        }
    }
    if(val.has_field(utility::conversions::to_string_t(U("name"))))
    {
        const web::json::value& fieldValue = val.at(utility::conversions::to_string_t(U("name")));
        if(!fieldValue.is_null())
        {
            utility::string_t refVal_setName;
            ok &= ModelBase::fromJson(fieldValue, refVal_setName);
            setName(refVal_setName);
        }
    }
    if(val.has_field(utility::conversions::to_string_t(U("description"))))
    {
        const web::json::value& fieldValue = val.at(utility::conversions::to_string_t(U("description")));
        if(!fieldValue.is_null())
        {
            utility::string_t refVal_setDescription;
            ok &= ModelBase::fromJson(fieldValue, refVal_setDescription);
            setDescription(refVal_setDescription);
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

void ShipCargoItem::toMultipart(std::shared_ptr<MultipartFormData> multipart, const utility::string_t& prefix) const
{
    utility::string_t namePrefix = prefix;
    if(namePrefix.size() > 0 && namePrefix.substr(namePrefix.size() - 1) != utility::conversions::to_string_t(U(".")))
    {
        namePrefix += utility::conversions::to_string_t(U("."));
    }
    if(m_SymbolIsSet)
    {
        multipart->add(ModelBase::toHttpContent(namePrefix + utility::conversions::to_string_t(U("symbol")), m_Symbol));
    }
    if(m_NameIsSet)
    {
        multipart->add(ModelBase::toHttpContent(namePrefix + utility::conversions::to_string_t(U("name")), m_Name));
    }
    if(m_DescriptionIsSet)
    {
        multipart->add(ModelBase::toHttpContent(namePrefix + utility::conversions::to_string_t(U("description")), m_Description));
    }
    if(m_UnitsIsSet)
    {
        multipart->add(ModelBase::toHttpContent(namePrefix + utility::conversions::to_string_t(U("units")), m_Units));
    }
}

bool ShipCargoItem::fromMultiPart(std::shared_ptr<MultipartFormData> multipart, const utility::string_t& prefix)
{
    bool ok = true;
    utility::string_t namePrefix = prefix;
    if(namePrefix.size() > 0 && namePrefix.substr(namePrefix.size() - 1) != utility::conversions::to_string_t(U(".")))
    {
        namePrefix += utility::conversions::to_string_t(U("."));
    }

    if(multipart->hasContent(utility::conversions::to_string_t(U("symbol"))))
    {
        std::shared_ptr<TradeSymbol> refVal_setSymbol;
        ok &= ModelBase::fromHttpContent(multipart->getContent(utility::conversions::to_string_t(U("symbol"))), refVal_setSymbol );
        setSymbol(refVal_setSymbol);
    }
    if(multipart->hasContent(utility::conversions::to_string_t(U("name"))))
    {
        utility::string_t refVal_setName;
        ok &= ModelBase::fromHttpContent(multipart->getContent(utility::conversions::to_string_t(U("name"))), refVal_setName );
        setName(refVal_setName);
    }
    if(multipart->hasContent(utility::conversions::to_string_t(U("description"))))
    {
        utility::string_t refVal_setDescription;
        ok &= ModelBase::fromHttpContent(multipart->getContent(utility::conversions::to_string_t(U("description"))), refVal_setDescription );
        setDescription(refVal_setDescription);
    }
    if(multipart->hasContent(utility::conversions::to_string_t(U("units"))))
    {
        int32_t refVal_setUnits;
        ok &= ModelBase::fromHttpContent(multipart->getContent(utility::conversions::to_string_t(U("units"))), refVal_setUnits );
        setUnits(refVal_setUnits);
    }
    return ok;
}

std::shared_ptr<TradeSymbol> ShipCargoItem::getSymbol() const
{
    return m_Symbol;
}

void ShipCargoItem::setSymbol(const std::shared_ptr<TradeSymbol>& value)
{
    m_Symbol = value;
    m_SymbolIsSet = true;
}

bool ShipCargoItem::symbolIsSet() const
{
    return m_SymbolIsSet;
}

void ShipCargoItem::unsetSymbol()
{
    m_SymbolIsSet = false;
}
utility::string_t ShipCargoItem::getName() const
{
    return m_Name;
}

void ShipCargoItem::setName(const utility::string_t& value)
{
    m_Name = value;
    m_NameIsSet = true;
}

bool ShipCargoItem::nameIsSet() const
{
    return m_NameIsSet;
}

void ShipCargoItem::unsetName()
{
    m_NameIsSet = false;
}
utility::string_t ShipCargoItem::getDescription() const
{
    return m_Description;
}

void ShipCargoItem::setDescription(const utility::string_t& value)
{
    m_Description = value;
    m_DescriptionIsSet = true;
}

bool ShipCargoItem::descriptionIsSet() const
{
    return m_DescriptionIsSet;
}

void ShipCargoItem::unsetDescription()
{
    m_DescriptionIsSet = false;
}
int32_t ShipCargoItem::getUnits() const
{
    return m_Units;
}

void ShipCargoItem::setUnits(int32_t value)
{
    m_Units = value;
    m_UnitsIsSet = true;
}

bool ShipCargoItem::unitsIsSet() const
{
    return m_UnitsIsSet;
}

void ShipCargoItem::unsetUnits()
{
    m_UnitsIsSet = false;
}
}

