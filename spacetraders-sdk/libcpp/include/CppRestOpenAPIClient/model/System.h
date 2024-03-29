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
 * System.h
 *
 * 
 */

#ifndef MODELS_System_H_
#define MODELS_System_H_


#include "CppRestOpenAPIClient/ModelBase.h"

#include "CppRestOpenAPIClient/model/SystemFaction.h"
#include "CppRestOpenAPIClient/model/SystemWaypoint.h"
#include <cpprest/details/basic_types.h>
#include "CppRestOpenAPIClient/model/SystemType.h"
#include <vector>

namespace models {

class SystemWaypoint;
class SystemFaction;

/// <summary>
/// 
/// </summary>
class  System
    : public ModelBase
{
public:
    System();
    virtual ~System();

    /////////////////////////////////////////////
    /// ModelBase overrides

    void validate() override;

    web::json::value toJson() const override;
    bool fromJson(const web::json::value& json) override;

    void toMultipart(std::shared_ptr<MultipartFormData> multipart, const utility::string_t& namePrefix) const override;
    bool fromMultiPart(std::shared_ptr<MultipartFormData> multipart, const utility::string_t& namePrefix) override;

    /////////////////////////////////////////////
    /// System members

    /// <summary>
    /// The symbol of the system.
    /// </summary>
    utility::string_t getSymbol() const;
    bool symbolIsSet() const;
    void unsetSymbol();

    void setSymbol(const utility::string_t& value);

    /// <summary>
    /// The symbol of the sector.
    /// </summary>
    utility::string_t getSectorSymbol() const;
    bool sectorSymbolIsSet() const;
    void unsetSectorSymbol();

    void setSectorSymbol(const utility::string_t& value);

    /// <summary>
    /// 
    /// </summary>
    std::shared_ptr<SystemType> getType() const;
    bool typeIsSet() const;
    void unsetType();

    void setType(const std::shared_ptr<SystemType>& value);

    /// <summary>
    /// Relative position of the system in the sector in the x axis.
    /// </summary>
    int32_t getX() const;
    bool XIsSet() const;
    void unsetx();

    void setX(int32_t value);

    /// <summary>
    /// Relative position of the system in the sector in the y axis.
    /// </summary>
    int32_t getY() const;
    bool YIsSet() const;
    void unsety();

    void setY(int32_t value);

    /// <summary>
    /// Waypoints in this system.
    /// </summary>
    std::vector<std::shared_ptr<SystemWaypoint>>& getWaypoints();
    bool waypointsIsSet() const;
    void unsetWaypoints();

    void setWaypoints(const std::vector<std::shared_ptr<SystemWaypoint>>& value);

    /// <summary>
    /// Factions that control this system.
    /// </summary>
    std::vector<std::shared_ptr<SystemFaction>>& getFactions();
    bool factionsIsSet() const;
    void unsetFactions();

    void setFactions(const std::vector<std::shared_ptr<SystemFaction>>& value);


protected:
    utility::string_t m_Symbol;
    bool m_SymbolIsSet;
    utility::string_t m_SectorSymbol;
    bool m_SectorSymbolIsSet;
    std::shared_ptr<SystemType> m_Type;
    bool m_TypeIsSet;
    int32_t m_x;
    bool m_xIsSet;
    int32_t m_y;
    bool m_yIsSet;
    std::vector<std::shared_ptr<SystemWaypoint>> m_Waypoints;
    bool m_WaypointsIsSet;
    std::vector<std::shared_ptr<SystemFaction>> m_Factions;
    bool m_FactionsIsSet;
};


}

#endif /* MODELS_System_H_ */
