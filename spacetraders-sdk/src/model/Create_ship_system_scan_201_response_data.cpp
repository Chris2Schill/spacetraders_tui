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



#include "CppRestOpenAPIClient/model/Create_ship_system_scan_201_response_data.h"

namespace models {



Create_ship_system_scan_201_response_data::Create_ship_system_scan_201_response_data()
{
    m_CooldownIsSet = false;
    m_SystemsIsSet = false;
}

Create_ship_system_scan_201_response_data::~Create_ship_system_scan_201_response_data()
{
}

void Create_ship_system_scan_201_response_data::validate()
{
    // TODO: implement validation
}

web::json::value Create_ship_system_scan_201_response_data::toJson() const
{

    web::json::value val = web::json::value::object();
    
    if(m_CooldownIsSet)
    {
        val[utility::conversions::to_string_t(U("cooldown"))] = ModelBase::toJson(m_Cooldown);
    }
    if(m_SystemsIsSet)
    {
        val[utility::conversions::to_string_t(U("systems"))] = ModelBase::toJson(m_Systems);
    }

    return val;
}

bool Create_ship_system_scan_201_response_data::fromJson(const web::json::value& val)
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
    if(val.has_field(utility::conversions::to_string_t(U("systems"))))
    {
        const web::json::value& fieldValue = val.at(utility::conversions::to_string_t(U("systems")));
        if(!fieldValue.is_null())
        {
            std::vector<std::shared_ptr<ScannedSystem>> refVal_setSystems;
            ok &= ModelBase::fromJson(fieldValue, refVal_setSystems);
            setSystems(refVal_setSystems);
        }
    }
    return ok;
}

void Create_ship_system_scan_201_response_data::toMultipart(std::shared_ptr<MultipartFormData> multipart, const utility::string_t& prefix) const
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
    if(m_SystemsIsSet)
    {
        multipart->add(ModelBase::toHttpContent(namePrefix + utility::conversions::to_string_t(U("systems")), m_Systems));
    }
}

bool Create_ship_system_scan_201_response_data::fromMultiPart(std::shared_ptr<MultipartFormData> multipart, const utility::string_t& prefix)
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
    if(multipart->hasContent(utility::conversions::to_string_t(U("systems"))))
    {
        std::vector<std::shared_ptr<ScannedSystem>> refVal_setSystems;
        ok &= ModelBase::fromHttpContent(multipart->getContent(utility::conversions::to_string_t(U("systems"))), refVal_setSystems );
        setSystems(refVal_setSystems);
    }
    return ok;
}

std::shared_ptr<Cooldown> Create_ship_system_scan_201_response_data::getCooldown() const
{
    return m_Cooldown;
}

void Create_ship_system_scan_201_response_data::setCooldown(const std::shared_ptr<Cooldown>& value)
{
    m_Cooldown = value;
    m_CooldownIsSet = true;
}

bool Create_ship_system_scan_201_response_data::cooldownIsSet() const
{
    return m_CooldownIsSet;
}

void Create_ship_system_scan_201_response_data::unsetCooldown()
{
    m_CooldownIsSet = false;
}
std::vector<std::shared_ptr<ScannedSystem>>& Create_ship_system_scan_201_response_data::getSystems()
{
    return m_Systems;
}

void Create_ship_system_scan_201_response_data::setSystems(const std::vector<std::shared_ptr<ScannedSystem>>& value)
{
    m_Systems = value;
    m_SystemsIsSet = true;
}

bool Create_ship_system_scan_201_response_data::systemsIsSet() const
{
    return m_SystemsIsSet;
}

void Create_ship_system_scan_201_response_data::unsetSystems()
{
    m_SystemsIsSet = false;
}
}


