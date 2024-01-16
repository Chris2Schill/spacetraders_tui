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



#include "CppRestOpenAPIClient/model/System.h"

namespace models {



System::System()
{
    m_Symbol = utility::conversions::to_string_t("");
    m_SymbolIsSet = false;
    m_SectorSymbol = utility::conversions::to_string_t("");
    m_SectorSymbolIsSet = false;
    m_TypeIsSet = false;
    m_x = 0;
    m_xIsSet = false;
    m_y = 0;
    m_yIsSet = false;
    m_WaypointsIsSet = false;
    m_FactionsIsSet = false;
}

System::~System()
{
}

void System::validate()
{
    // TODO: implement validation
}

web::json::value System::toJson() const
{

    web::json::value val = web::json::value::object();
    
    if(m_SymbolIsSet)
    {
        val[utility::conversions::to_string_t(U("symbol"))] = ModelBase::toJson(m_Symbol);
    }
    if(m_SectorSymbolIsSet)
    {
        val[utility::conversions::to_string_t(U("sectorSymbol"))] = ModelBase::toJson(m_SectorSymbol);
    }
    if(m_TypeIsSet)
    {
        val[utility::conversions::to_string_t(U("type"))] = ModelBase::toJson(m_Type);
    }
    if(m_xIsSet)
    {
        val[utility::conversions::to_string_t(U("x"))] = ModelBase::toJson(m_x);
    }
    if(m_yIsSet)
    {
        val[utility::conversions::to_string_t(U("y"))] = ModelBase::toJson(m_y);
    }
    if(m_WaypointsIsSet)
    {
        val[utility::conversions::to_string_t(U("waypoints"))] = ModelBase::toJson(m_Waypoints);
    }
    if(m_FactionsIsSet)
    {
        val[utility::conversions::to_string_t(U("factions"))] = ModelBase::toJson(m_Factions);
    }

    return val;
}

bool System::fromJson(const web::json::value& val)
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
    if(val.has_field(utility::conversions::to_string_t(U("sectorSymbol"))))
    {
        const web::json::value& fieldValue = val.at(utility::conversions::to_string_t(U("sectorSymbol")));
        if(!fieldValue.is_null())
        {
            utility::string_t refVal_setSectorSymbol;
            ok &= ModelBase::fromJson(fieldValue, refVal_setSectorSymbol);
            setSectorSymbol(refVal_setSectorSymbol);
        }
    }
    if(val.has_field(utility::conversions::to_string_t(U("type"))))
    {
        const web::json::value& fieldValue = val.at(utility::conversions::to_string_t(U("type")));
        if(!fieldValue.is_null())
        {
            std::shared_ptr<SystemType> refVal_setType;
            ok &= ModelBase::fromJson(fieldValue, refVal_setType);
            setType(refVal_setType);
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
    if(val.has_field(utility::conversions::to_string_t(U("waypoints"))))
    {
        const web::json::value& fieldValue = val.at(utility::conversions::to_string_t(U("waypoints")));
        if(!fieldValue.is_null())
        {
            std::vector<std::shared_ptr<SystemWaypoint>> refVal_setWaypoints;
            ok &= ModelBase::fromJson(fieldValue, refVal_setWaypoints);
            setWaypoints(refVal_setWaypoints);
        }
    }
    if(val.has_field(utility::conversions::to_string_t(U("factions"))))
    {
        const web::json::value& fieldValue = val.at(utility::conversions::to_string_t(U("factions")));
        if(!fieldValue.is_null())
        {
            std::vector<std::shared_ptr<SystemFaction>> refVal_setFactions;
            ok &= ModelBase::fromJson(fieldValue, refVal_setFactions);
            setFactions(refVal_setFactions);
        }
    }
    return ok;
}

void System::toMultipart(std::shared_ptr<MultipartFormData> multipart, const utility::string_t& prefix) const
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
    if(m_SectorSymbolIsSet)
    {
        multipart->add(ModelBase::toHttpContent(namePrefix + utility::conversions::to_string_t(U("sectorSymbol")), m_SectorSymbol));
    }
    if(m_TypeIsSet)
    {
        multipart->add(ModelBase::toHttpContent(namePrefix + utility::conversions::to_string_t(U("type")), m_Type));
    }
    if(m_xIsSet)
    {
        multipart->add(ModelBase::toHttpContent(namePrefix + utility::conversions::to_string_t(U("x")), m_x));
    }
    if(m_yIsSet)
    {
        multipart->add(ModelBase::toHttpContent(namePrefix + utility::conversions::to_string_t(U("y")), m_y));
    }
    if(m_WaypointsIsSet)
    {
        multipart->add(ModelBase::toHttpContent(namePrefix + utility::conversions::to_string_t(U("waypoints")), m_Waypoints));
    }
    if(m_FactionsIsSet)
    {
        multipart->add(ModelBase::toHttpContent(namePrefix + utility::conversions::to_string_t(U("factions")), m_Factions));
    }
}

bool System::fromMultiPart(std::shared_ptr<MultipartFormData> multipart, const utility::string_t& prefix)
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
    if(multipart->hasContent(utility::conversions::to_string_t(U("sectorSymbol"))))
    {
        utility::string_t refVal_setSectorSymbol;
        ok &= ModelBase::fromHttpContent(multipart->getContent(utility::conversions::to_string_t(U("sectorSymbol"))), refVal_setSectorSymbol );
        setSectorSymbol(refVal_setSectorSymbol);
    }
    if(multipart->hasContent(utility::conversions::to_string_t(U("type"))))
    {
        std::shared_ptr<SystemType> refVal_setType;
        ok &= ModelBase::fromHttpContent(multipart->getContent(utility::conversions::to_string_t(U("type"))), refVal_setType );
        setType(refVal_setType);
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
    if(multipart->hasContent(utility::conversions::to_string_t(U("waypoints"))))
    {
        std::vector<std::shared_ptr<SystemWaypoint>> refVal_setWaypoints;
        ok &= ModelBase::fromHttpContent(multipart->getContent(utility::conversions::to_string_t(U("waypoints"))), refVal_setWaypoints );
        setWaypoints(refVal_setWaypoints);
    }
    if(multipart->hasContent(utility::conversions::to_string_t(U("factions"))))
    {
        std::vector<std::shared_ptr<SystemFaction>> refVal_setFactions;
        ok &= ModelBase::fromHttpContent(multipart->getContent(utility::conversions::to_string_t(U("factions"))), refVal_setFactions );
        setFactions(refVal_setFactions);
    }
    return ok;
}

utility::string_t System::getSymbol() const
{
    return m_Symbol;
}

void System::setSymbol(const utility::string_t& value)
{
    m_Symbol = value;
    m_SymbolIsSet = true;
}

bool System::symbolIsSet() const
{
    return m_SymbolIsSet;
}

void System::unsetSymbol()
{
    m_SymbolIsSet = false;
}
utility::string_t System::getSectorSymbol() const
{
    return m_SectorSymbol;
}

void System::setSectorSymbol(const utility::string_t& value)
{
    m_SectorSymbol = value;
    m_SectorSymbolIsSet = true;
}

bool System::sectorSymbolIsSet() const
{
    return m_SectorSymbolIsSet;
}

void System::unsetSectorSymbol()
{
    m_SectorSymbolIsSet = false;
}
std::shared_ptr<SystemType> System::getType() const
{
    return m_Type;
}

void System::setType(const std::shared_ptr<SystemType>& value)
{
    m_Type = value;
    m_TypeIsSet = true;
}

bool System::typeIsSet() const
{
    return m_TypeIsSet;
}

void System::unsetType()
{
    m_TypeIsSet = false;
}
int32_t System::getX() const
{
    return m_x;
}

void System::setX(int32_t value)
{
    m_x = value;
    m_xIsSet = true;
}

bool System::XIsSet() const
{
    return m_xIsSet;
}

void System::unsetx()
{
    m_xIsSet = false;
}
int32_t System::getY() const
{
    return m_y;
}

void System::setY(int32_t value)
{
    m_y = value;
    m_yIsSet = true;
}

bool System::YIsSet() const
{
    return m_yIsSet;
}

void System::unsety()
{
    m_yIsSet = false;
}
std::vector<std::shared_ptr<SystemWaypoint>>& System::getWaypoints()
{
    return m_Waypoints;
}

void System::setWaypoints(const std::vector<std::shared_ptr<SystemWaypoint>>& value)
{
    m_Waypoints = value;
    m_WaypointsIsSet = true;
}

bool System::waypointsIsSet() const
{
    return m_WaypointsIsSet;
}

void System::unsetWaypoints()
{
    m_WaypointsIsSet = false;
}
std::vector<std::shared_ptr<SystemFaction>>& System::getFactions()
{
    return m_Factions;
}

void System::setFactions(const std::vector<std::shared_ptr<SystemFaction>>& value)
{
    m_Factions = value;
    m_FactionsIsSet = true;
}

bool System::factionsIsSet() const
{
    return m_FactionsIsSet;
}

void System::unsetFactions()
{
    m_FactionsIsSet = false;
}
}

