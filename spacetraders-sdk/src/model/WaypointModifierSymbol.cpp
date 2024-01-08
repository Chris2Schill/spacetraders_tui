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



#include "CppRestOpenAPIClient/model/WaypointModifierSymbol.h"

namespace models {


namespace
{
using EnumUnderlyingType = utility::string_t;

WaypointModifierSymbol::eWaypointModifierSymbol toEnum(const EnumUnderlyingType& val)
{
    if (val == utility::conversions::to_string_t(U("STRIPPED")))
        return WaypointModifierSymbol::eWaypointModifierSymbol::WaypointModifierSymbol_STRIPPED;
    if (val == utility::conversions::to_string_t(U("UNSTABLE")))
        return WaypointModifierSymbol::eWaypointModifierSymbol::WaypointModifierSymbol_UNSTABLE;
    if (val == utility::conversions::to_string_t(U("RADIATION_LEAK")))
        return WaypointModifierSymbol::eWaypointModifierSymbol::WaypointModifierSymbol_RADIATION_LEAK;
    if (val == utility::conversions::to_string_t(U("CRITICAL_LIMIT")))
        return WaypointModifierSymbol::eWaypointModifierSymbol::WaypointModifierSymbol_CRITICAL_LIMIT;
    if (val == utility::conversions::to_string_t(U("CIVIL_UNREST")))
        return WaypointModifierSymbol::eWaypointModifierSymbol::WaypointModifierSymbol_CIVIL_UNREST;
    return {};
}

EnumUnderlyingType fromEnum(WaypointModifierSymbol::eWaypointModifierSymbol e)
{
    switch (e)
    {
    case WaypointModifierSymbol::eWaypointModifierSymbol::WaypointModifierSymbol_STRIPPED:
        return U("STRIPPED");
    case WaypointModifierSymbol::eWaypointModifierSymbol::WaypointModifierSymbol_UNSTABLE:
        return U("UNSTABLE");
    case WaypointModifierSymbol::eWaypointModifierSymbol::WaypointModifierSymbol_RADIATION_LEAK:
        return U("RADIATION_LEAK");
    case WaypointModifierSymbol::eWaypointModifierSymbol::WaypointModifierSymbol_CRITICAL_LIMIT:
        return U("CRITICAL_LIMIT");
    case WaypointModifierSymbol::eWaypointModifierSymbol::WaypointModifierSymbol_CIVIL_UNREST:
        return U("CIVIL_UNREST");
    default:
        break;
    }
    return {};
}
}

WaypointModifierSymbol::WaypointModifierSymbol()
{
}

WaypointModifierSymbol::~WaypointModifierSymbol()
{
}

void WaypointModifierSymbol::validate()
{
    // TODO: implement validation
}

web::json::value WaypointModifierSymbol::toJson() const
{
    auto val = fromEnum(m_value);
    return web::json::value(val);
}

bool WaypointModifierSymbol::fromJson(const web::json::value& val)
{
    m_value = toEnum(val.as_string());
    return true;
}

void WaypointModifierSymbol::toMultipart(std::shared_ptr<MultipartFormData> multipart, const utility::string_t& prefix) const
{
    utility::string_t namePrefix = prefix;
    if (!namePrefix.empty() && namePrefix.back() != U('.'))
    {
        namePrefix.push_back(U('.'));
    }

    auto e = fromEnum(m_value);
    multipart->add(ModelBase::toHttpContent(namePrefix, e));
}

bool WaypointModifierSymbol::fromMultiPart(std::shared_ptr<MultipartFormData> multipart, const utility::string_t& prefix)
{
    bool ok = true;
    utility::string_t namePrefix = prefix;
    if (!namePrefix.empty() && namePrefix.back() != U('.'))
    {
        namePrefix.push_back(U('.'));
    }
    {
        EnumUnderlyingType e;
        ok = ModelBase::fromHttpContent(multipart->getContent(namePrefix), e);
        if (ok)
        {
            auto v = toEnum(e);
            setValue(v);
        }
    }
    return ok;
}

WaypointModifierSymbol::eWaypointModifierSymbol WaypointModifierSymbol::getValue() const
{
   return m_value;
}

void WaypointModifierSymbol::setValue(WaypointModifierSymbol::eWaypointModifierSymbol const value)
{
   m_value = value;
}


}


