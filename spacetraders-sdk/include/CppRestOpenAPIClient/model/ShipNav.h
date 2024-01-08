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
 * ShipNav.h
 *
 * The navigation information of the ship.
 */

#ifndef MODELS_ShipNav_H_
#define MODELS_ShipNav_H_


#include "CppRestOpenAPIClient/ModelBase.h"

#include "CppRestOpenAPIClient/model/ShipNavRoute.h"
#include "CppRestOpenAPIClient/model/ShipNavStatus.h"
#include <cpprest/details/basic_types.h>
#include "CppRestOpenAPIClient/model/ShipNavFlightMode.h"

namespace models {

class ShipNavRoute;

/// <summary>
/// The navigation information of the ship.
/// </summary>
class  ShipNav
    : public ModelBase
{
public:
    ShipNav();
    virtual ~ShipNav();

    /////////////////////////////////////////////
    /// ModelBase overrides

    void validate() override;

    web::json::value toJson() const override;
    bool fromJson(const web::json::value& json) override;

    void toMultipart(std::shared_ptr<MultipartFormData> multipart, const utility::string_t& namePrefix) const override;
    bool fromMultiPart(std::shared_ptr<MultipartFormData> multipart, const utility::string_t& namePrefix) override;

    /////////////////////////////////////////////
    /// ShipNav members

    /// <summary>
    /// The symbol of the system.
    /// </summary>
    utility::string_t getSystemSymbol() const;
    bool systemSymbolIsSet() const;
    void unsetSystemSymbol();

    void setSystemSymbol(const utility::string_t& value);

    /// <summary>
    /// The symbol of the waypoint.
    /// </summary>
    utility::string_t getWaypointSymbol() const;
    bool waypointSymbolIsSet() const;
    void unsetWaypointSymbol();

    void setWaypointSymbol(const utility::string_t& value);

    /// <summary>
    /// 
    /// </summary>
    std::shared_ptr<ShipNavRoute> getRoute() const;
    bool routeIsSet() const;
    void unsetRoute();

    void setRoute(const std::shared_ptr<ShipNavRoute>& value);

    /// <summary>
    /// 
    /// </summary>
    std::shared_ptr<ShipNavStatus> getStatus() const;
    bool statusIsSet() const;
    void unsetStatus();

    void setStatus(const std::shared_ptr<ShipNavStatus>& value);

    /// <summary>
    /// 
    /// </summary>
    std::shared_ptr<ShipNavFlightMode> getFlightMode() const;
    bool flightModeIsSet() const;
    void unsetFlightMode();

    void setFlightMode(const std::shared_ptr<ShipNavFlightMode>& value);


protected:
    utility::string_t m_SystemSymbol;
    bool m_SystemSymbolIsSet;
    utility::string_t m_WaypointSymbol;
    bool m_WaypointSymbolIsSet;
    std::shared_ptr<ShipNavRoute> m_Route;
    bool m_RouteIsSet;
    std::shared_ptr<ShipNavStatus> m_Status;
    bool m_StatusIsSet;
    std::shared_ptr<ShipNavFlightMode> m_FlightMode;
    bool m_FlightModeIsSet;
};


}

#endif /* MODELS_ShipNav_H_ */
