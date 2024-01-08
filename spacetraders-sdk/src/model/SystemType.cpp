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



#include "CppRestOpenAPIClient/model/SystemType.h"

namespace models {


namespace
{
using EnumUnderlyingType = utility::string_t;

SystemType::eSystemType toEnum(const EnumUnderlyingType& val)
{
    if (val == utility::conversions::to_string_t(U("NEUTRON_STAR")))
        return SystemType::eSystemType::SystemType_NEUTRON_STAR;
    if (val == utility::conversions::to_string_t(U("RED_STAR")))
        return SystemType::eSystemType::SystemType_RED_STAR;
    if (val == utility::conversions::to_string_t(U("ORANGE_STAR")))
        return SystemType::eSystemType::SystemType_ORANGE_STAR;
    if (val == utility::conversions::to_string_t(U("BLUE_STAR")))
        return SystemType::eSystemType::SystemType_BLUE_STAR;
    if (val == utility::conversions::to_string_t(U("YOUNG_STAR")))
        return SystemType::eSystemType::SystemType_YOUNG_STAR;
    if (val == utility::conversions::to_string_t(U("WHITE_DWARF")))
        return SystemType::eSystemType::SystemType_WHITE_DWARF;
    if (val == utility::conversions::to_string_t(U("BLACK_HOLE")))
        return SystemType::eSystemType::SystemType_BLACK_HOLE;
    if (val == utility::conversions::to_string_t(U("HYPERGIANT")))
        return SystemType::eSystemType::SystemType_HYPERGIANT;
    if (val == utility::conversions::to_string_t(U("NEBULA")))
        return SystemType::eSystemType::SystemType_NEBULA;
    if (val == utility::conversions::to_string_t(U("UNSTABLE")))
        return SystemType::eSystemType::SystemType_UNSTABLE;
    return {};
}

EnumUnderlyingType fromEnum(SystemType::eSystemType e)
{
    switch (e)
    {
    case SystemType::eSystemType::SystemType_NEUTRON_STAR:
        return U("NEUTRON_STAR");
    case SystemType::eSystemType::SystemType_RED_STAR:
        return U("RED_STAR");
    case SystemType::eSystemType::SystemType_ORANGE_STAR:
        return U("ORANGE_STAR");
    case SystemType::eSystemType::SystemType_BLUE_STAR:
        return U("BLUE_STAR");
    case SystemType::eSystemType::SystemType_YOUNG_STAR:
        return U("YOUNG_STAR");
    case SystemType::eSystemType::SystemType_WHITE_DWARF:
        return U("WHITE_DWARF");
    case SystemType::eSystemType::SystemType_BLACK_HOLE:
        return U("BLACK_HOLE");
    case SystemType::eSystemType::SystemType_HYPERGIANT:
        return U("HYPERGIANT");
    case SystemType::eSystemType::SystemType_NEBULA:
        return U("NEBULA");
    case SystemType::eSystemType::SystemType_UNSTABLE:
        return U("UNSTABLE");
    default:
        break;
    }
    return {};
}
}

SystemType::SystemType()
{
}

SystemType::~SystemType()
{
}

void SystemType::validate()
{
    // TODO: implement validation
}

web::json::value SystemType::toJson() const
{
    auto val = fromEnum(m_value);
    return web::json::value(val);
}

bool SystemType::fromJson(const web::json::value& val)
{
    m_value = toEnum(val.as_string());
    return true;
}

void SystemType::toMultipart(std::shared_ptr<MultipartFormData> multipart, const utility::string_t& prefix) const
{
    utility::string_t namePrefix = prefix;
    if (!namePrefix.empty() && namePrefix.back() != U('.'))
    {
        namePrefix.push_back(U('.'));
    }

    auto e = fromEnum(m_value);
    multipart->add(ModelBase::toHttpContent(namePrefix, e));
}

bool SystemType::fromMultiPart(std::shared_ptr<MultipartFormData> multipart, const utility::string_t& prefix)
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

SystemType::eSystemType SystemType::getValue() const
{
   return m_value;
}

void SystemType::setValue(SystemType::eSystemType const value)
{
   m_value = value;
}


}


