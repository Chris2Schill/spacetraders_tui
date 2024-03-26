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



#include "CppRestOpenAPIClient/model/Navigate_ship_200_response_data.h"

namespace models {



Navigate_ship_200_response_data::Navigate_ship_200_response_data()
{
    m_FuelIsSet = false;
    m_NavIsSet = false;
}

Navigate_ship_200_response_data::~Navigate_ship_200_response_data()
{
}

void Navigate_ship_200_response_data::validate()
{
    // TODO: implement validation
}

web::json::value Navigate_ship_200_response_data::toJson() const
{

    web::json::value val = web::json::value::object();
    
    if(m_FuelIsSet)
    {
        val[utility::conversions::to_string_t(U("fuel"))] = ModelBase::toJson(m_Fuel);
    }
    if(m_NavIsSet)
    {
        val[utility::conversions::to_string_t(U("nav"))] = ModelBase::toJson(m_Nav);
    }

    return val;
}

bool Navigate_ship_200_response_data::fromJson(const web::json::value& val)
{
    bool ok = true;
    
    if(val.has_field(utility::conversions::to_string_t(U("fuel"))))
    {
        const web::json::value& fieldValue = val.at(utility::conversions::to_string_t(U("fuel")));
        if(!fieldValue.is_null())
        {
            std::shared_ptr<ShipFuel> refVal_setFuel;
            ok &= ModelBase::fromJson(fieldValue, refVal_setFuel);
            setFuel(refVal_setFuel);
        }
    }
    if(val.has_field(utility::conversions::to_string_t(U("nav"))))
    {
        const web::json::value& fieldValue = val.at(utility::conversions::to_string_t(U("nav")));
        if(!fieldValue.is_null())
        {
            std::shared_ptr<ShipNav> refVal_setNav;
            ok &= ModelBase::fromJson(fieldValue, refVal_setNav);
            setNav(refVal_setNav);
        }
    }
    return ok;
}

void Navigate_ship_200_response_data::toMultipart(std::shared_ptr<MultipartFormData> multipart, const utility::string_t& prefix) const
{
    utility::string_t namePrefix = prefix;
    if(namePrefix.size() > 0 && namePrefix.substr(namePrefix.size() - 1) != utility::conversions::to_string_t(U(".")))
    {
        namePrefix += utility::conversions::to_string_t(U("."));
    }
    if(m_FuelIsSet)
    {
        multipart->add(ModelBase::toHttpContent(namePrefix + utility::conversions::to_string_t(U("fuel")), m_Fuel));
    }
    if(m_NavIsSet)
    {
        multipart->add(ModelBase::toHttpContent(namePrefix + utility::conversions::to_string_t(U("nav")), m_Nav));
    }
}

bool Navigate_ship_200_response_data::fromMultiPart(std::shared_ptr<MultipartFormData> multipart, const utility::string_t& prefix)
{
    bool ok = true;
    utility::string_t namePrefix = prefix;
    if(namePrefix.size() > 0 && namePrefix.substr(namePrefix.size() - 1) != utility::conversions::to_string_t(U(".")))
    {
        namePrefix += utility::conversions::to_string_t(U("."));
    }

    if(multipart->hasContent(utility::conversions::to_string_t(U("fuel"))))
    {
        std::shared_ptr<ShipFuel> refVal_setFuel;
        ok &= ModelBase::fromHttpContent(multipart->getContent(utility::conversions::to_string_t(U("fuel"))), refVal_setFuel );
        setFuel(refVal_setFuel);
    }
    if(multipart->hasContent(utility::conversions::to_string_t(U("nav"))))
    {
        std::shared_ptr<ShipNav> refVal_setNav;
        ok &= ModelBase::fromHttpContent(multipart->getContent(utility::conversions::to_string_t(U("nav"))), refVal_setNav );
        setNav(refVal_setNav);
    }
    return ok;
}

std::shared_ptr<ShipFuel> Navigate_ship_200_response_data::getFuel() const
{
    return m_Fuel;
}

void Navigate_ship_200_response_data::setFuel(const std::shared_ptr<ShipFuel>& value)
{
    m_Fuel = value;
    m_FuelIsSet = true;
}

bool Navigate_ship_200_response_data::fuelIsSet() const
{
    return m_FuelIsSet;
}

void Navigate_ship_200_response_data::unsetFuel()
{
    m_FuelIsSet = false;
}
std::shared_ptr<ShipNav> Navigate_ship_200_response_data::getNav() const
{
    return m_Nav;
}

void Navigate_ship_200_response_data::setNav(const std::shared_ptr<ShipNav>& value)
{
    m_Nav = value;
    m_NavIsSet = true;
}

bool Navigate_ship_200_response_data::navIsSet() const
{
    return m_NavIsSet;
}

void Navigate_ship_200_response_data::unsetNav()
{
    m_NavIsSet = false;
}
}

