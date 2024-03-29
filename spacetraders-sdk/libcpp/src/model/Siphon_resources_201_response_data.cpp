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



#include "CppRestOpenAPIClient/model/Siphon_resources_201_response_data.h"

namespace models {



Siphon_resources_201_response_data::Siphon_resources_201_response_data()
{
    m_CooldownIsSet = false;
    m_SiphonIsSet = false;
    m_CargoIsSet = false;
}

Siphon_resources_201_response_data::~Siphon_resources_201_response_data()
{
}

void Siphon_resources_201_response_data::validate()
{
    // TODO: implement validation
}

web::json::value Siphon_resources_201_response_data::toJson() const
{

    web::json::value val = web::json::value::object();
    
    if(m_CooldownIsSet)
    {
        val[utility::conversions::to_string_t(U("cooldown"))] = ModelBase::toJson(m_Cooldown);
    }
    if(m_SiphonIsSet)
    {
        val[utility::conversions::to_string_t(U("siphon"))] = ModelBase::toJson(m_Siphon);
    }
    if(m_CargoIsSet)
    {
        val[utility::conversions::to_string_t(U("cargo"))] = ModelBase::toJson(m_Cargo);
    }

    return val;
}

bool Siphon_resources_201_response_data::fromJson(const web::json::value& val)
{
    bool ok = true;
    
    if(val.has_field(utility::conversions::to_string_t(U("cooldown"))))
    {
        const web::json::value& fieldValue = val.at(utility::conversions::to_string_t(U("cooldown")));
        if(!fieldValue.is_null())
        {
            std::shared_ptr<Cooldown> refVal_setCooldown;
            ok &= ModelBase::fromJson(fieldValue, refVal_setCooldown);
            setCooldown(refVal_setCooldown);
        }
    }
    if(val.has_field(utility::conversions::to_string_t(U("siphon"))))
    {
        const web::json::value& fieldValue = val.at(utility::conversions::to_string_t(U("siphon")));
        if(!fieldValue.is_null())
        {
            std::shared_ptr<Siphon> refVal_setSiphon;
            ok &= ModelBase::fromJson(fieldValue, refVal_setSiphon);
            setSiphon(refVal_setSiphon);
        }
    }
    if(val.has_field(utility::conversions::to_string_t(U("cargo"))))
    {
        const web::json::value& fieldValue = val.at(utility::conversions::to_string_t(U("cargo")));
        if(!fieldValue.is_null())
        {
            std::shared_ptr<ShipCargo> refVal_setCargo;
            ok &= ModelBase::fromJson(fieldValue, refVal_setCargo);
            setCargo(refVal_setCargo);
        }
    }
    return ok;
}

void Siphon_resources_201_response_data::toMultipart(std::shared_ptr<MultipartFormData> multipart, const utility::string_t& prefix) const
{
    utility::string_t namePrefix = prefix;
    if(namePrefix.size() > 0 && namePrefix.substr(namePrefix.size() - 1) != utility::conversions::to_string_t(U(".")))
    {
        namePrefix += utility::conversions::to_string_t(U("."));
    }
    if(m_CooldownIsSet)
    {
        multipart->add(ModelBase::toHttpContent(namePrefix + utility::conversions::to_string_t(U("cooldown")), m_Cooldown));
    }
    if(m_SiphonIsSet)
    {
        multipart->add(ModelBase::toHttpContent(namePrefix + utility::conversions::to_string_t(U("siphon")), m_Siphon));
    }
    if(m_CargoIsSet)
    {
        multipart->add(ModelBase::toHttpContent(namePrefix + utility::conversions::to_string_t(U("cargo")), m_Cargo));
    }
}

bool Siphon_resources_201_response_data::fromMultiPart(std::shared_ptr<MultipartFormData> multipart, const utility::string_t& prefix)
{
    bool ok = true;
    utility::string_t namePrefix = prefix;
    if(namePrefix.size() > 0 && namePrefix.substr(namePrefix.size() - 1) != utility::conversions::to_string_t(U(".")))
    {
        namePrefix += utility::conversions::to_string_t(U("."));
    }

    if(multipart->hasContent(utility::conversions::to_string_t(U("cooldown"))))
    {
        std::shared_ptr<Cooldown> refVal_setCooldown;
        ok &= ModelBase::fromHttpContent(multipart->getContent(utility::conversions::to_string_t(U("cooldown"))), refVal_setCooldown );
        setCooldown(refVal_setCooldown);
    }
    if(multipart->hasContent(utility::conversions::to_string_t(U("siphon"))))
    {
        std::shared_ptr<Siphon> refVal_setSiphon;
        ok &= ModelBase::fromHttpContent(multipart->getContent(utility::conversions::to_string_t(U("siphon"))), refVal_setSiphon );
        setSiphon(refVal_setSiphon);
    }
    if(multipart->hasContent(utility::conversions::to_string_t(U("cargo"))))
    {
        std::shared_ptr<ShipCargo> refVal_setCargo;
        ok &= ModelBase::fromHttpContent(multipart->getContent(utility::conversions::to_string_t(U("cargo"))), refVal_setCargo );
        setCargo(refVal_setCargo);
    }
    return ok;
}

std::shared_ptr<Cooldown> Siphon_resources_201_response_data::getCooldown() const
{
    return m_Cooldown;
}

void Siphon_resources_201_response_data::setCooldown(const std::shared_ptr<Cooldown>& value)
{
    m_Cooldown = value;
    m_CooldownIsSet = true;
}

bool Siphon_resources_201_response_data::cooldownIsSet() const
{
    return m_CooldownIsSet;
}

void Siphon_resources_201_response_data::unsetCooldown()
{
    m_CooldownIsSet = false;
}
std::shared_ptr<Siphon> Siphon_resources_201_response_data::getSiphon() const
{
    return m_Siphon;
}

void Siphon_resources_201_response_data::setSiphon(const std::shared_ptr<Siphon>& value)
{
    m_Siphon = value;
    m_SiphonIsSet = true;
}

bool Siphon_resources_201_response_data::siphonIsSet() const
{
    return m_SiphonIsSet;
}

void Siphon_resources_201_response_data::unsetSiphon()
{
    m_SiphonIsSet = false;
}
std::shared_ptr<ShipCargo> Siphon_resources_201_response_data::getCargo() const
{
    return m_Cargo;
}

void Siphon_resources_201_response_data::setCargo(const std::shared_ptr<ShipCargo>& value)
{
    m_Cargo = value;
    m_CargoIsSet = true;
}

bool Siphon_resources_201_response_data::cargoIsSet() const
{
    return m_CargoIsSet;
}

void Siphon_resources_201_response_data::unsetCargo()
{
    m_CargoIsSet = false;
}
}


