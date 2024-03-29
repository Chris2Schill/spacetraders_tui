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



#include "CppRestOpenAPIClient/model/Waypoint.h"

namespace models {



Waypoint::Waypoint()
{
    m_Symbol = utility::conversions::to_string_t("");
    m_SymbolIsSet = false;
    m_TypeIsSet = false;
    m_SystemSymbol = utility::conversions::to_string_t("");
    m_SystemSymbolIsSet = false;
    m_x = 0;
    m_xIsSet = false;
    m_y = 0;
    m_yIsSet = false;
    m_OrbitalsIsSet = false;
    m_Orbits = utility::conversions::to_string_t("");
    m_OrbitsIsSet = false;
    m_FactionIsSet = false;
    m_TraitsIsSet = false;
    m_ModifiersIsSet = false;
    m_ChartIsSet = false;
    m_IsUnderConstruction = false;
    m_IsUnderConstructionIsSet = false;
}

Waypoint::~Waypoint()
{
}

void Waypoint::validate()
{
    // TODO: implement validation
}

web::json::value Waypoint::toJson() const
{

    web::json::value val = web::json::value::object();
    
    if(m_SymbolIsSet)
    {
        val[utility::conversions::to_string_t(U("symbol"))] = ModelBase::toJson(m_Symbol);
    }
    if(m_TypeIsSet)
    {
        val[utility::conversions::to_string_t(U("type"))] = ModelBase::toJson(m_Type);
    }
    if(m_SystemSymbolIsSet)
    {
        val[utility::conversions::to_string_t(U("systemSymbol"))] = ModelBase::toJson(m_SystemSymbol);
    }
    if(m_xIsSet)
    {
        val[utility::conversions::to_string_t(U("x"))] = ModelBase::toJson(m_x);
    }
    if(m_yIsSet)
    {
        val[utility::conversions::to_string_t(U("y"))] = ModelBase::toJson(m_y);
    }
    if(m_OrbitalsIsSet)
    {
        val[utility::conversions::to_string_t(U("orbitals"))] = ModelBase::toJson(m_Orbitals);
    }
    if(m_OrbitsIsSet)
    {
        val[utility::conversions::to_string_t(U("orbits"))] = ModelBase::toJson(m_Orbits);
    }
    if(m_FactionIsSet)
    {
        val[utility::conversions::to_string_t(U("faction"))] = ModelBase::toJson(m_Faction);
    }
    if(m_TraitsIsSet)
    {
        val[utility::conversions::to_string_t(U("traits"))] = ModelBase::toJson(m_Traits);
    }
    if(m_ModifiersIsSet)
    {
        val[utility::conversions::to_string_t(U("modifiers"))] = ModelBase::toJson(m_Modifiers);
    }
    if(m_ChartIsSet)
    {
        val[utility::conversions::to_string_t(U("chart"))] = ModelBase::toJson(m_Chart);
    }
    if(m_IsUnderConstructionIsSet)
    {
        val[utility::conversions::to_string_t(U("isUnderConstruction"))] = ModelBase::toJson(m_IsUnderConstruction);
    }

    return val;
}

bool Waypoint::fromJson(const web::json::value& val)
{
    bool ok = true;
    
    if(val.has_field(utility::conversions::to_string_t(U("symbol"))))
    {
        const web::json::value& fieldValue = val.at(utility::conversions::to_string_t(U("symbol")));
        if(!fieldValue.is_null())
        {
            utility::string_t refVal_setSymbol;
            ok &= ModelBase::fromJson(fieldValue, refVal_setSymbol);
            setSymbol(refVal_setSymbol);
        }
    }
    if(val.has_field(utility::conversions::to_string_t(U("type"))))
    {
        const web::json::value& fieldValue = val.at(utility::conversions::to_string_t(U("type")));
        if(!fieldValue.is_null())
        {
            std::shared_ptr<WaypointType> refVal_setType;
            ok &= ModelBase::fromJson(fieldValue, refVal_setType);
            setType(refVal_setType);
        }
    }
    if(val.has_field(utility::conversions::to_string_t(U("systemSymbol"))))
    {
        const web::json::value& fieldValue = val.at(utility::conversions::to_string_t(U("systemSymbol")));
        if(!fieldValue.is_null())
        {
            utility::string_t refVal_setSystemSymbol;
            ok &= ModelBase::fromJson(fieldValue, refVal_setSystemSymbol);
            setSystemSymbol(refVal_setSystemSymbol);
        }
    }
    if(val.has_field(utility::conversions::to_string_t(U("x"))))
    {
        const web::json::value& fieldValue = val.at(utility::conversions::to_string_t(U("x")));
        if(!fieldValue.is_null())
        {
            int32_t refVal_setX;
            ok &= ModelBase::fromJson(fieldValue, refVal_setX);
            setX(refVal_setX);
        }
    }
    if(val.has_field(utility::conversions::to_string_t(U("y"))))
    {
        const web::json::value& fieldValue = val.at(utility::conversions::to_string_t(U("y")));
        if(!fieldValue.is_null())
        {
            int32_t refVal_setY;
            ok &= ModelBase::fromJson(fieldValue, refVal_setY);
            setY(refVal_setY);
        }
    }
    if(val.has_field(utility::conversions::to_string_t(U("orbitals"))))
    {
        const web::json::value& fieldValue = val.at(utility::conversions::to_string_t(U("orbitals")));
        if(!fieldValue.is_null())
        {
            std::vector<std::shared_ptr<WaypointOrbital>> refVal_setOrbitals;
            ok &= ModelBase::fromJson(fieldValue, refVal_setOrbitals);
            setOrbitals(refVal_setOrbitals);
        }
    }
    if(val.has_field(utility::conversions::to_string_t(U("orbits"))))
    {
        const web::json::value& fieldValue = val.at(utility::conversions::to_string_t(U("orbits")));
        if(!fieldValue.is_null())
        {
            utility::string_t refVal_setOrbits;
            ok &= ModelBase::fromJson(fieldValue, refVal_setOrbits);
            setOrbits(refVal_setOrbits);
        }
    }
    if(val.has_field(utility::conversions::to_string_t(U("faction"))))
    {
        const web::json::value& fieldValue = val.at(utility::conversions::to_string_t(U("faction")));
        if(!fieldValue.is_null())
        {
            std::shared_ptr<WaypointFaction> refVal_setFaction;
            ok &= ModelBase::fromJson(fieldValue, refVal_setFaction);
            setFaction(refVal_setFaction);
        }
    }
    if(val.has_field(utility::conversions::to_string_t(U("traits"))))
    {
        const web::json::value& fieldValue = val.at(utility::conversions::to_string_t(U("traits")));
        if(!fieldValue.is_null())
        {
            std::vector<std::shared_ptr<WaypointTrait>> refVal_setTraits;
            ok &= ModelBase::fromJson(fieldValue, refVal_setTraits);
            setTraits(refVal_setTraits);
        }
    }
    if(val.has_field(utility::conversions::to_string_t(U("modifiers"))))
    {
        const web::json::value& fieldValue = val.at(utility::conversions::to_string_t(U("modifiers")));
        if(!fieldValue.is_null())
        {
            std::vector<std::shared_ptr<WaypointModifier>> refVal_setModifiers;
            ok &= ModelBase::fromJson(fieldValue, refVal_setModifiers);
            setModifiers(refVal_setModifiers);
        }
    }
    if(val.has_field(utility::conversions::to_string_t(U("chart"))))
    {
        const web::json::value& fieldValue = val.at(utility::conversions::to_string_t(U("chart")));
        if(!fieldValue.is_null())
        {
            std::shared_ptr<Chart> refVal_setChart;
            ok &= ModelBase::fromJson(fieldValue, refVal_setChart);
            setChart(refVal_setChart);
        }
    }
    if(val.has_field(utility::conversions::to_string_t(U("isUnderConstruction"))))
    {
        const web::json::value& fieldValue = val.at(utility::conversions::to_string_t(U("isUnderConstruction")));
        if(!fieldValue.is_null())
        {
            bool refVal_setIsUnderConstruction;
            ok &= ModelBase::fromJson(fieldValue, refVal_setIsUnderConstruction);
            setIsUnderConstruction(refVal_setIsUnderConstruction);
        }
    }
    return ok;
}

void Waypoint::toMultipart(std::shared_ptr<MultipartFormData> multipart, const utility::string_t& prefix) const
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
    if(m_TypeIsSet)
    {
        multipart->add(ModelBase::toHttpContent(namePrefix + utility::conversions::to_string_t(U("type")), m_Type));
    }
    if(m_SystemSymbolIsSet)
    {
        multipart->add(ModelBase::toHttpContent(namePrefix + utility::conversions::to_string_t(U("systemSymbol")), m_SystemSymbol));
    }
    if(m_xIsSet)
    {
        multipart->add(ModelBase::toHttpContent(namePrefix + utility::conversions::to_string_t(U("x")), m_x));
    }
    if(m_yIsSet)
    {
        multipart->add(ModelBase::toHttpContent(namePrefix + utility::conversions::to_string_t(U("y")), m_y));
    }
    if(m_OrbitalsIsSet)
    {
        multipart->add(ModelBase::toHttpContent(namePrefix + utility::conversions::to_string_t(U("orbitals")), m_Orbitals));
    }
    if(m_OrbitsIsSet)
    {
        multipart->add(ModelBase::toHttpContent(namePrefix + utility::conversions::to_string_t(U("orbits")), m_Orbits));
    }
    if(m_FactionIsSet)
    {
        multipart->add(ModelBase::toHttpContent(namePrefix + utility::conversions::to_string_t(U("faction")), m_Faction));
    }
    if(m_TraitsIsSet)
    {
        multipart->add(ModelBase::toHttpContent(namePrefix + utility::conversions::to_string_t(U("traits")), m_Traits));
    }
    if(m_ModifiersIsSet)
    {
        multipart->add(ModelBase::toHttpContent(namePrefix + utility::conversions::to_string_t(U("modifiers")), m_Modifiers));
    }
    if(m_ChartIsSet)
    {
        multipart->add(ModelBase::toHttpContent(namePrefix + utility::conversions::to_string_t(U("chart")), m_Chart));
    }
    if(m_IsUnderConstructionIsSet)
    {
        multipart->add(ModelBase::toHttpContent(namePrefix + utility::conversions::to_string_t(U("isUnderConstruction")), m_IsUnderConstruction));
    }
}

bool Waypoint::fromMultiPart(std::shared_ptr<MultipartFormData> multipart, const utility::string_t& prefix)
{
    bool ok = true;
    utility::string_t namePrefix = prefix;
    if(namePrefix.size() > 0 && namePrefix.substr(namePrefix.size() - 1) != utility::conversions::to_string_t(U(".")))
    {
        namePrefix += utility::conversions::to_string_t(U("."));
    }

    if(multipart->hasContent(utility::conversions::to_string_t(U("symbol"))))
    {
        utility::string_t refVal_setSymbol;
        ok &= ModelBase::fromHttpContent(multipart->getContent(utility::conversions::to_string_t(U("symbol"))), refVal_setSymbol );
        setSymbol(refVal_setSymbol);
    }
    if(multipart->hasContent(utility::conversions::to_string_t(U("type"))))
    {
        std::shared_ptr<WaypointType> refVal_setType;
        ok &= ModelBase::fromHttpContent(multipart->getContent(utility::conversions::to_string_t(U("type"))), refVal_setType );
        setType(refVal_setType);
    }
    if(multipart->hasContent(utility::conversions::to_string_t(U("systemSymbol"))))
    {
        utility::string_t refVal_setSystemSymbol;
        ok &= ModelBase::fromHttpContent(multipart->getContent(utility::conversions::to_string_t(U("systemSymbol"))), refVal_setSystemSymbol );
        setSystemSymbol(refVal_setSystemSymbol);
    }
    if(multipart->hasContent(utility::conversions::to_string_t(U("x"))))
    {
        int32_t refVal_setX;
        ok &= ModelBase::fromHttpContent(multipart->getContent(utility::conversions::to_string_t(U("x"))), refVal_setX );
        setX(refVal_setX);
    }
    if(multipart->hasContent(utility::conversions::to_string_t(U("y"))))
    {
        int32_t refVal_setY;
        ok &= ModelBase::fromHttpContent(multipart->getContent(utility::conversions::to_string_t(U("y"))), refVal_setY );
        setY(refVal_setY);
    }
    if(multipart->hasContent(utility::conversions::to_string_t(U("orbitals"))))
    {
        std::vector<std::shared_ptr<WaypointOrbital>> refVal_setOrbitals;
        ok &= ModelBase::fromHttpContent(multipart->getContent(utility::conversions::to_string_t(U("orbitals"))), refVal_setOrbitals );
        setOrbitals(refVal_setOrbitals);
    }
    if(multipart->hasContent(utility::conversions::to_string_t(U("orbits"))))
    {
        utility::string_t refVal_setOrbits;
        ok &= ModelBase::fromHttpContent(multipart->getContent(utility::conversions::to_string_t(U("orbits"))), refVal_setOrbits );
        setOrbits(refVal_setOrbits);
    }
    if(multipart->hasContent(utility::conversions::to_string_t(U("faction"))))
    {
        std::shared_ptr<WaypointFaction> refVal_setFaction;
        ok &= ModelBase::fromHttpContent(multipart->getContent(utility::conversions::to_string_t(U("faction"))), refVal_setFaction );
        setFaction(refVal_setFaction);
    }
    if(multipart->hasContent(utility::conversions::to_string_t(U("traits"))))
    {
        std::vector<std::shared_ptr<WaypointTrait>> refVal_setTraits;
        ok &= ModelBase::fromHttpContent(multipart->getContent(utility::conversions::to_string_t(U("traits"))), refVal_setTraits );
        setTraits(refVal_setTraits);
    }
    if(multipart->hasContent(utility::conversions::to_string_t(U("modifiers"))))
    {
        std::vector<std::shared_ptr<WaypointModifier>> refVal_setModifiers;
        ok &= ModelBase::fromHttpContent(multipart->getContent(utility::conversions::to_string_t(U("modifiers"))), refVal_setModifiers );
        setModifiers(refVal_setModifiers);
    }
    if(multipart->hasContent(utility::conversions::to_string_t(U("chart"))))
    {
        std::shared_ptr<Chart> refVal_setChart;
        ok &= ModelBase::fromHttpContent(multipart->getContent(utility::conversions::to_string_t(U("chart"))), refVal_setChart );
        setChart(refVal_setChart);
    }
    if(multipart->hasContent(utility::conversions::to_string_t(U("isUnderConstruction"))))
    {
        bool refVal_setIsUnderConstruction;
        ok &= ModelBase::fromHttpContent(multipart->getContent(utility::conversions::to_string_t(U("isUnderConstruction"))), refVal_setIsUnderConstruction );
        setIsUnderConstruction(refVal_setIsUnderConstruction);
    }
    return ok;
}

utility::string_t Waypoint::getSymbol() const
{
    return m_Symbol;
}

void Waypoint::setSymbol(const utility::string_t& value)
{
    m_Symbol = value;
    m_SymbolIsSet = true;
}

bool Waypoint::symbolIsSet() const
{
    return m_SymbolIsSet;
}

void Waypoint::unsetSymbol()
{
    m_SymbolIsSet = false;
}
std::shared_ptr<WaypointType> Waypoint::getType() const
{
    return m_Type;
}

void Waypoint::setType(const std::shared_ptr<WaypointType>& value)
{
    m_Type = value;
    m_TypeIsSet = true;
}

bool Waypoint::typeIsSet() const
{
    return m_TypeIsSet;
}

void Waypoint::unsetType()
{
    m_TypeIsSet = false;
}
utility::string_t Waypoint::getSystemSymbol() const
{
    return m_SystemSymbol;
}

void Waypoint::setSystemSymbol(const utility::string_t& value)
{
    m_SystemSymbol = value;
    m_SystemSymbolIsSet = true;
}

bool Waypoint::systemSymbolIsSet() const
{
    return m_SystemSymbolIsSet;
}

void Waypoint::unsetSystemSymbol()
{
    m_SystemSymbolIsSet = false;
}
int32_t Waypoint::getX() const
{
    return m_x;
}

void Waypoint::setX(int32_t value)
{
    m_x = value;
    m_xIsSet = true;
}

bool Waypoint::XIsSet() const
{
    return m_xIsSet;
}

void Waypoint::unsetx()
{
    m_xIsSet = false;
}
int32_t Waypoint::getY() const
{
    return m_y;
}

void Waypoint::setY(int32_t value)
{
    m_y = value;
    m_yIsSet = true;
}

bool Waypoint::YIsSet() const
{
    return m_yIsSet;
}

void Waypoint::unsety()
{
    m_yIsSet = false;
}
std::vector<std::shared_ptr<WaypointOrbital>>& Waypoint::getOrbitals()
{
    return m_Orbitals;
}

void Waypoint::setOrbitals(const std::vector<std::shared_ptr<WaypointOrbital>>& value)
{
    m_Orbitals = value;
    m_OrbitalsIsSet = true;
}

bool Waypoint::orbitalsIsSet() const
{
    return m_OrbitalsIsSet;
}

void Waypoint::unsetOrbitals()
{
    m_OrbitalsIsSet = false;
}
utility::string_t Waypoint::getOrbits() const
{
    return m_Orbits;
}

void Waypoint::setOrbits(const utility::string_t& value)
{
    m_Orbits = value;
    m_OrbitsIsSet = true;
}

bool Waypoint::orbitsIsSet() const
{
    return m_OrbitsIsSet;
}

void Waypoint::unsetOrbits()
{
    m_OrbitsIsSet = false;
}
std::shared_ptr<WaypointFaction> Waypoint::getFaction() const
{
    return m_Faction;
}

void Waypoint::setFaction(const std::shared_ptr<WaypointFaction>& value)
{
    m_Faction = value;
    m_FactionIsSet = true;
}

bool Waypoint::factionIsSet() const
{
    return m_FactionIsSet;
}

void Waypoint::unsetFaction()
{
    m_FactionIsSet = false;
}
std::vector<std::shared_ptr<WaypointTrait>>& Waypoint::getTraits()
{
    return m_Traits;
}

void Waypoint::setTraits(const std::vector<std::shared_ptr<WaypointTrait>>& value)
{
    m_Traits = value;
    m_TraitsIsSet = true;
}

bool Waypoint::traitsIsSet() const
{
    return m_TraitsIsSet;
}

void Waypoint::unsetTraits()
{
    m_TraitsIsSet = false;
}
std::vector<std::shared_ptr<WaypointModifier>>& Waypoint::getModifiers()
{
    return m_Modifiers;
}

void Waypoint::setModifiers(const std::vector<std::shared_ptr<WaypointModifier>>& value)
{
    m_Modifiers = value;
    m_ModifiersIsSet = true;
}

bool Waypoint::modifiersIsSet() const
{
    return m_ModifiersIsSet;
}

void Waypoint::unsetModifiers()
{
    m_ModifiersIsSet = false;
}
std::shared_ptr<Chart> Waypoint::getChart() const
{
    return m_Chart;
}

void Waypoint::setChart(const std::shared_ptr<Chart>& value)
{
    m_Chart = value;
    m_ChartIsSet = true;
}

bool Waypoint::chartIsSet() const
{
    return m_ChartIsSet;
}

void Waypoint::unsetChart()
{
    m_ChartIsSet = false;
}
bool Waypoint::isIsUnderConstruction() const
{
    return m_IsUnderConstruction;
}

void Waypoint::setIsUnderConstruction(bool value)
{
    m_IsUnderConstruction = value;
    m_IsUnderConstructionIsSet = true;
}

bool Waypoint::isUnderConstructionIsSet() const
{
    return m_IsUnderConstructionIsSet;
}

void Waypoint::unsetIsUnderConstruction()
{
    m_IsUnderConstructionIsSet = false;
}
}


