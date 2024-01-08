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



#include "CppRestOpenAPIClient/model/ShipRegistration.h"

namespace models {



ShipRegistration::ShipRegistration()
{
    m_Name = utility::conversions::to_string_t("");
    m_NameIsSet = false;
    m_FactionSymbol = utility::conversions::to_string_t("");
    m_FactionSymbolIsSet = false;
    m_RoleIsSet = false;
}

ShipRegistration::~ShipRegistration()
{
}

void ShipRegistration::validate()
{
    // TODO: implement validation
}

web::json::value ShipRegistration::toJson() const
{

    web::json::value val = web::json::value::object();
    
    if(m_NameIsSet)
    {
        val[utility::conversions::to_string_t(U("name"))] = ModelBase::toJson(m_Name);
    }
    if(m_FactionSymbolIsSet)
    {
        val[utility::conversions::to_string_t(U("factionSymbol"))] = ModelBase::toJson(m_FactionSymbol);
    }
    if(m_RoleIsSet)
    {
        val[utility::conversions::to_string_t(U("role"))] = ModelBase::toJson(m_Role);
    }

    return val;
}

bool ShipRegistration::fromJson(const web::json::value& val)
{
    bool ok = true;
    
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
    if(val.has_field(utility::conversions::to_string_t(U("factionSymbol"))))
    {
        const web::json::value& fieldValue = val.at(utility::conversions::to_string_t(U("factionSymbol")));
        if(!fieldValue.is_null())
        {
            utility::string_t refVal_setFactionSymbol;
            ok &= ModelBase::fromJson(fieldValue, refVal_setFactionSymbol);
            setFactionSymbol(refVal_setFactionSymbol);
        }
    }
    if(val.has_field(utility::conversions::to_string_t(U("role"))))
    {
        const web::json::value& fieldValue = val.at(utility::conversions::to_string_t(U("role")));
        if(!fieldValue.is_null())
        {
            std::shared_ptr<ShipRole> refVal_setRole;
            ok &= ModelBase::fromJson(fieldValue, refVal_setRole);
            setRole(refVal_setRole);
        }
    }
    return ok;
}

void ShipRegistration::toMultipart(std::shared_ptr<MultipartFormData> multipart, const utility::string_t& prefix) const
{
    utility::string_t namePrefix = prefix;
    if(namePrefix.size() > 0 && namePrefix.substr(namePrefix.size() - 1) != utility::conversions::to_string_t(U(".")))
    {
        namePrefix += utility::conversions::to_string_t(U("."));
    }
    if(m_NameIsSet)
    {
        multipart->add(ModelBase::toHttpContent(namePrefix + utility::conversions::to_string_t(U("name")), m_Name));
    }
    if(m_FactionSymbolIsSet)
    {
        multipart->add(ModelBase::toHttpContent(namePrefix + utility::conversions::to_string_t(U("factionSymbol")), m_FactionSymbol));
    }
    if(m_RoleIsSet)
    {
        multipart->add(ModelBase::toHttpContent(namePrefix + utility::conversions::to_string_t(U("role")), m_Role));
    }
}

bool ShipRegistration::fromMultiPart(std::shared_ptr<MultipartFormData> multipart, const utility::string_t& prefix)
{
    bool ok = true;
    utility::string_t namePrefix = prefix;
    if(namePrefix.size() > 0 && namePrefix.substr(namePrefix.size() - 1) != utility::conversions::to_string_t(U(".")))
    {
        namePrefix += utility::conversions::to_string_t(U("."));
    }

    if(multipart->hasContent(utility::conversions::to_string_t(U("name"))))
    {
        utility::string_t refVal_setName;
        ok &= ModelBase::fromHttpContent(multipart->getContent(utility::conversions::to_string_t(U("name"))), refVal_setName );
        setName(refVal_setName);
    }
    if(multipart->hasContent(utility::conversions::to_string_t(U("factionSymbol"))))
    {
        utility::string_t refVal_setFactionSymbol;
        ok &= ModelBase::fromHttpContent(multipart->getContent(utility::conversions::to_string_t(U("factionSymbol"))), refVal_setFactionSymbol );
        setFactionSymbol(refVal_setFactionSymbol);
    }
    if(multipart->hasContent(utility::conversions::to_string_t(U("role"))))
    {
        std::shared_ptr<ShipRole> refVal_setRole;
        ok &= ModelBase::fromHttpContent(multipart->getContent(utility::conversions::to_string_t(U("role"))), refVal_setRole );
        setRole(refVal_setRole);
    }
    return ok;
}

utility::string_t ShipRegistration::getName() const
{
    return m_Name;
}

void ShipRegistration::setName(const utility::string_t& value)
{
    m_Name = value;
    m_NameIsSet = true;
}

bool ShipRegistration::nameIsSet() const
{
    return m_NameIsSet;
}

void ShipRegistration::unsetName()
{
    m_NameIsSet = false;
}
utility::string_t ShipRegistration::getFactionSymbol() const
{
    return m_FactionSymbol;
}

void ShipRegistration::setFactionSymbol(const utility::string_t& value)
{
    m_FactionSymbol = value;
    m_FactionSymbolIsSet = true;
}

bool ShipRegistration::factionSymbolIsSet() const
{
    return m_FactionSymbolIsSet;
}

void ShipRegistration::unsetFactionSymbol()
{
    m_FactionSymbolIsSet = false;
}
std::shared_ptr<ShipRole> ShipRegistration::getRole() const
{
    return m_Role;
}

void ShipRegistration::setRole(const std::shared_ptr<ShipRole>& value)
{
    m_Role = value;
    m_RoleIsSet = true;
}

bool ShipRegistration::roleIsSet() const
{
    return m_RoleIsSet;
}

void ShipRegistration::unsetRole()
{
    m_RoleIsSet = false;
}
}


