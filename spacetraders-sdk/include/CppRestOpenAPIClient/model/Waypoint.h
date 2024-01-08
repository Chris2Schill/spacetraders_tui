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

/*
 * Waypoint.h
 *
 * A waypoint is a location that ships can travel to such as a Planet, Moon or Space Station.
 */

#ifndef MODELS_Waypoint_H_
#define MODELS_Waypoint_H_


#include "CppRestOpenAPIClient/ModelBase.h"

#include "CppRestOpenAPIClient/model/WaypointTrait.h"
#include "CppRestOpenAPIClient/model/Chart.h"
#include <cpprest/details/basic_types.h>
#include "CppRestOpenAPIClient/model/WaypointModifier.h"
#include "CppRestOpenAPIClient/model/WaypointOrbital.h"
#include "CppRestOpenAPIClient/model/WaypointType.h"
#include "CppRestOpenAPIClient/model/WaypointFaction.h"
#include <vector>

namespace models {

class WaypointOrbital;
class WaypointFaction;
class WaypointTrait;
class WaypointModifier;
class Chart;

/// <summary>
/// A waypoint is a location that ships can travel to such as a Planet, Moon or Space Station.
/// </summary>
class  Waypoint
    : public ModelBase
{
public:
    Waypoint();
    virtual ~Waypoint();

    /////////////////////////////////////////////
    /// ModelBase overrides

    void validate() override;

    web::json::value toJson() const override;
    bool fromJson(const web::json::value& json) override;

    void toMultipart(std::shared_ptr<MultipartFormData> multipart, const utility::string_t& namePrefix) const override;
    bool fromMultiPart(std::shared_ptr<MultipartFormData> multipart, const utility::string_t& namePrefix) override;

    /////////////////////////////////////////////
    /// Waypoint members

    /// <summary>
    /// The symbol of the waypoint.
    /// </summary>
    utility::string_t getSymbol() const;
    bool symbolIsSet() const;
    void unsetSymbol();

    void setSymbol(const utility::string_t& value);

    /// <summary>
    /// 
    /// </summary>
    std::shared_ptr<WaypointType> getType() const;
    bool typeIsSet() const;
    void unsetType();

    void setType(const std::shared_ptr<WaypointType>& value);

    /// <summary>
    /// The symbol of the system.
    /// </summary>
    utility::string_t getSystemSymbol() const;
    bool systemSymbolIsSet() const;
    void unsetSystemSymbol();

    void setSystemSymbol(const utility::string_t& value);

    /// <summary>
    /// Relative position of the waypoint on the system&#39;s x axis. This is not an absolute position in the universe.
    /// </summary>
    int32_t getX() const;
    bool XIsSet() const;
    void unsetx();

    void setX(int32_t value);

    /// <summary>
    /// Relative position of the waypoint on the system&#39;s y axis. This is not an absolute position in the universe.
    /// </summary>
    int32_t getY() const;
    bool YIsSet() const;
    void unsety();

    void setY(int32_t value);

    /// <summary>
    /// Waypoints that orbit this waypoint.
    /// </summary>
    std::vector<std::shared_ptr<WaypointOrbital>>& getOrbitals();
    bool orbitalsIsSet() const;
    void unsetOrbitals();

    void setOrbitals(const std::vector<std::shared_ptr<WaypointOrbital>>& value);

    /// <summary>
    /// The symbol of the parent waypoint, if this waypoint is in orbit around another waypoint. Otherwise this value is undefined.
    /// </summary>
    utility::string_t getOrbits() const;
    bool orbitsIsSet() const;
    void unsetOrbits();

    void setOrbits(const utility::string_t& value);

    /// <summary>
    /// 
    /// </summary>
    std::shared_ptr<WaypointFaction> getFaction() const;
    bool factionIsSet() const;
    void unsetFaction();

    void setFaction(const std::shared_ptr<WaypointFaction>& value);

    /// <summary>
    /// The traits of the waypoint.
    /// </summary>
    std::vector<std::shared_ptr<WaypointTrait>>& getTraits();
    bool traitsIsSet() const;
    void unsetTraits();

    void setTraits(const std::vector<std::shared_ptr<WaypointTrait>>& value);

    /// <summary>
    /// The modifiers of the waypoint.
    /// </summary>
    std::vector<std::shared_ptr<WaypointModifier>>& getModifiers();
    bool modifiersIsSet() const;
    void unsetModifiers();

    void setModifiers(const std::vector<std::shared_ptr<WaypointModifier>>& value);

    /// <summary>
    /// 
    /// </summary>
    std::shared_ptr<Chart> getChart() const;
    bool chartIsSet() const;
    void unsetChart();

    void setChart(const std::shared_ptr<Chart>& value);

    /// <summary>
    /// True if the waypoint is under construction.
    /// </summary>
    bool isIsUnderConstruction() const;
    bool isUnderConstructionIsSet() const;
    void unsetIsUnderConstruction();

    void setIsUnderConstruction(bool value);


protected:
    utility::string_t m_Symbol;
    bool m_SymbolIsSet;
    std::shared_ptr<WaypointType> m_Type;
    bool m_TypeIsSet;
    utility::string_t m_SystemSymbol;
    bool m_SystemSymbolIsSet;
    int32_t m_x;
    bool m_xIsSet;
    int32_t m_y;
    bool m_yIsSet;
    std::vector<std::shared_ptr<WaypointOrbital>> m_Orbitals;
    bool m_OrbitalsIsSet;
    utility::string_t m_Orbits;
    bool m_OrbitsIsSet;
    std::shared_ptr<WaypointFaction> m_Faction;
    bool m_FactionIsSet;
    std::vector<std::shared_ptr<WaypointTrait>> m_Traits;
    bool m_TraitsIsSet;
    std::vector<std::shared_ptr<WaypointModifier>> m_Modifiers;
    bool m_ModifiersIsSet;
    std::shared_ptr<Chart> m_Chart;
    bool m_ChartIsSet;
    bool m_IsUnderConstruction;
    bool m_IsUnderConstructionIsSet;
};


}

#endif /* MODELS_Waypoint_H_ */
