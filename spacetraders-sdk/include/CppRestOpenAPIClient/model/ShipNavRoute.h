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
 * ShipNavRoute.h
 *
 * The routing information for the ship&#39;s most recent transit or current location.
 */

#ifndef MODELS_ShipNavRoute_H_
#define MODELS_ShipNavRoute_H_


#include "CppRestOpenAPIClient/ModelBase.h"

#include <cpprest/details/basic_types.h>
#include "CppRestOpenAPIClient/model/ShipNavRouteWaypoint.h"

namespace models {

class ShipNavRouteWaypoint;

/// <summary>
/// The routing information for the ship&#39;s most recent transit or current location.
/// </summary>
class  ShipNavRoute
    : public ModelBase
{
public:
    ShipNavRoute();
    virtual ~ShipNavRoute();

    /////////////////////////////////////////////
    /// ModelBase overrides

    void validate() override;

    web::json::value toJson() const override;
    bool fromJson(const web::json::value& json) override;

    void toMultipart(std::shared_ptr<MultipartFormData> multipart, const utility::string_t& namePrefix) const override;
    bool fromMultiPart(std::shared_ptr<MultipartFormData> multipart, const utility::string_t& namePrefix) override;

    /////////////////////////////////////////////
    /// ShipNavRoute members

    /// <summary>
    /// 
    /// </summary>
    std::shared_ptr<ShipNavRouteWaypoint> getDestination() const;
    bool destinationIsSet() const;
    void unsetDestination();

    void setDestination(const std::shared_ptr<ShipNavRouteWaypoint>& value);

    /// <summary>
    /// 
    /// </summary>
    std::shared_ptr<ShipNavRouteWaypoint> getOrigin() const;
    bool originIsSet() const;
    void unsetOrigin();

    void setOrigin(const std::shared_ptr<ShipNavRouteWaypoint>& value);

    /// <summary>
    /// The date time of the ship&#39;s departure.
    /// </summary>
    utility::datetime getDepartureTime() const;
    bool departureTimeIsSet() const;
    void unsetDepartureTime();

    void setDepartureTime(const utility::datetime& value);

    /// <summary>
    /// The date time of the ship&#39;s arrival. If the ship is in-transit, this is the expected time of arrival.
    /// </summary>
    utility::datetime getArrival() const;
    bool arrivalIsSet() const;
    void unsetArrival();

    void setArrival(const utility::datetime& value);


protected:
    std::shared_ptr<ShipNavRouteWaypoint> m_Destination;
    bool m_DestinationIsSet;
    std::shared_ptr<ShipNavRouteWaypoint> m_Origin;
    bool m_OriginIsSet;
    utility::datetime m_DepartureTime;
    bool m_DepartureTimeIsSet;
    utility::datetime m_Arrival;
    bool m_ArrivalIsSet;
};


}

#endif /* MODELS_ShipNavRoute_H_ */
