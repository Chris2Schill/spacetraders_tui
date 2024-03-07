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
 * SystemsApi.h
 *
 * 
 */

#ifndef API_SystemsApi_H_
#define API_SystemsApi_H_



#include "CppRestOpenAPIClient/ApiClient.h"

#include "CppRestOpenAPIClient/model/Get_construction_200_response.h"
#include "CppRestOpenAPIClient/model/Get_jump_gate_200_response.h"
#include "CppRestOpenAPIClient/model/Get_market_200_response.h"
#include "CppRestOpenAPIClient/model/Get_shipyard_200_response.h"
#include "CppRestOpenAPIClient/model/Get_system_200_response.h"
#include "CppRestOpenAPIClient/model/Get_system_waypoints_200_response.h"
#include "CppRestOpenAPIClient/model/Get_system_waypoints_traits_parameter.h"
#include "CppRestOpenAPIClient/model/Get_systems_200_response.h"
#include "CppRestOpenAPIClient/model/Get_waypoint_200_response.h"
#include "CppRestOpenAPIClient/model/Supply_construction_201_response.h"
#include "CppRestOpenAPIClient/model/Supply_construction_request.h"
#include "CppRestOpenAPIClient/model/WaypointType.h"
#include <cpprest/details/basic_types.h>
#include <boost/optional.hpp>

namespace api {

using namespace models;



class  SystemsApi 
{
public:

    explicit SystemsApi( std::shared_ptr<const ApiClient> apiClient );

    virtual ~SystemsApi();

    /// <summary>
    /// Get Construction Site
    /// </summary>
    /// <remarks>
    /// Get construction details for a waypoint. Requires a waypoint with a property of &#x60;isUnderConstruction&#x60; to be true.
    /// </remarks>
    /// <param name="systemSymbol">The system symbol</param>
    /// <param name="waypointSymbol">The waypoint symbol</param>
    pplx::task<std::shared_ptr<Get_construction_200_response>> getConstruction(
        utility::string_t systemSymbol,
        utility::string_t waypointSymbol
    ) const;
    /// <summary>
    /// Get Jump Gate
    /// </summary>
    /// <remarks>
    /// Get jump gate details for a waypoint. Requires a waypoint of type &#x60;JUMP_GATE&#x60; to use.  Waypoints connected to this jump gate can be 
    /// </remarks>
    /// <param name="systemSymbol">The system symbol</param>
    /// <param name="waypointSymbol">The waypoint symbol</param>
    pplx::task<std::shared_ptr<Get_jump_gate_200_response>> getJumpGate(
        utility::string_t systemSymbol,
        utility::string_t waypointSymbol
    ) const;
    /// <summary>
    /// Get Market
    /// </summary>
    /// <remarks>
    /// Retrieve imports, exports and exchange data from a marketplace. Requires a waypoint that has the &#x60;Marketplace&#x60; trait to use.  Send a ship to the waypoint to access trade good prices and recent transactions. Refer to the [Market Overview page](https://docs.spacetraders.io/game-concepts/markets) to gain better a understanding of the market in the game.
    /// </remarks>
    /// <param name="systemSymbol">The system symbol</param>
    /// <param name="waypointSymbol">The waypoint symbol</param>
    pplx::task<std::shared_ptr<Get_market_200_response>> getMarket(
        utility::string_t systemSymbol,
        utility::string_t waypointSymbol
    ) const;
    /// <summary>
    /// Get Shipyard
    /// </summary>
    /// <remarks>
    /// Get the shipyard for a waypoint. Requires a waypoint that has the &#x60;Shipyard&#x60; trait to use. Send a ship to the waypoint to access data on ships that are currently available for purchase and recent transactions.
    /// </remarks>
    /// <param name="systemSymbol">The system symbol</param>
    /// <param name="waypointSymbol">The waypoint symbol</param>
    pplx::task<std::shared_ptr<Get_shipyard_200_response>> getShipyard(
        utility::string_t systemSymbol,
        utility::string_t waypointSymbol
    ) const;
    /// <summary>
    /// Get System
    /// </summary>
    /// <remarks>
    /// Get the details of a system.
    /// </remarks>
    /// <param name="systemSymbol">The system symbol</param>
    pplx::task<std::shared_ptr<Get_system_200_response>> getSystem(
        utility::string_t systemSymbol
    ) const;
    /// <summary>
    /// List Waypoints in System
    /// </summary>
    /// <remarks>
    /// Return a paginated list of all of the waypoints for a given system.  If a waypoint is uncharted, it will return the &#x60;Uncharted&#x60; trait instead of its actual traits.
    /// </remarks>
    /// <param name="systemSymbol">The system symbol</param>
    /// <param name="page">What entry offset to request (optional, default to 0)</param>
    /// <param name="limit">How many entries to return per page (optional, default to 0)</param>
    /// <param name="type">Filter waypoints by type. (optional, default to new WaypointType())</param>
    /// <param name="traits">Filter waypoints by one or more traits. (optional, default to nullptr)</param>
    pplx::task<std::shared_ptr<Get_system_waypoints_200_response>> getSystemWaypoints(
        utility::string_t systemSymbol,
        boost::optional<int32_t> page,
        boost::optional<int32_t> limit,
        boost::optional<std::shared_ptr<WaypointType>> type,
        boost::optional<std::shared_ptr<WaypointTraitSymbol>> traits
    ) const;
    /// <summary>
    /// List Systems
    /// </summary>
    /// <remarks>
    /// Return a paginated list of all systems.
    /// </remarks>
    /// <param name="page">What entry offset to request (optional, default to 0)</param>
    /// <param name="limit">How many entries to return per page (optional, default to 0)</param>
    pplx::task<std::shared_ptr<Get_systems_200_response>> getSystems(
        boost::optional<int32_t> page,
        boost::optional<int32_t> limit
    ) const;
    /// <summary>
    /// Get Waypoint
    /// </summary>
    /// <remarks>
    /// View the details of a waypoint.  If the waypoint is uncharted, it will return the &#39;Uncharted&#39; trait instead of its actual traits.
    /// </remarks>
    /// <param name="systemSymbol">The system symbol</param>
    /// <param name="waypointSymbol">The waypoint symbol</param>
    pplx::task<std::shared_ptr<Get_waypoint_200_response>> getWaypoint(
        utility::string_t systemSymbol,
        utility::string_t waypointSymbol
    ) const;
    /// <summary>
    /// Supply Construction Site
    /// </summary>
    /// <remarks>
    /// Supply a construction site with the specified good. Requires a waypoint with a property of &#x60;isUnderConstruction&#x60; to be true.  The good must be in your ship&#39;s cargo. The good will be removed from your ship&#39;s cargo and added to the construction site&#39;s materials.
    /// </remarks>
    /// <param name="systemSymbol">The system symbol</param>
    /// <param name="waypointSymbol">The waypoint symbol</param>
    /// <param name="supplyConstructionRequest"> (optional)</param>
    pplx::task<std::shared_ptr<Supply_construction_201_response>> supplyConstruction(
        utility::string_t systemSymbol,
        utility::string_t waypointSymbol,
        boost::optional<std::shared_ptr<Supply_construction_request>> supplyConstructionRequest
    ) const;

protected:
    std::shared_ptr<const ApiClient> m_ApiClient;
};

}

#endif /* API_SystemsApi_H_ */

