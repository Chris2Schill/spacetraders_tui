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



#include "CppRestOpenAPIClient/model/ShipNavRoute.h"

namespace models {



ShipNavRoute::ShipNavRoute()
{
    m_DestinationIsSet = false;
    m_OriginIsSet = false;
    m_DepartureTime = utility::datetime();
    m_DepartureTimeIsSet = false;
    m_Arrival = utility::datetime();
    m_ArrivalIsSet = false;
}

ShipNavRoute::~ShipNavRoute()
{
}

void ShipNavRoute::validate()
{
    // TODO: implement validation
}

web::json::value ShipNavRoute::toJson() const
{

    web::json::value val = web::json::value::object();
    
    if(m_DestinationIsSet)
    {
        val[utility::conversions::to_string_t(U("destination"))] = ModelBase::toJson(m_Destination);
    }
    if(m_OriginIsSet)
    {
        val[utility::conversions::to_string_t(U("origin"))] = ModelBase::toJson(m_Origin);
    }
    if(m_DepartureTimeIsSet)
    {
        val[utility::conversions::to_string_t(U("departureTime"))] = ModelBase::toJson(m_DepartureTime);
    }
    if(m_ArrivalIsSet)
    {
        val[utility::conversions::to_string_t(U("arrival"))] = ModelBase::toJson(m_Arrival);
    }

    return val;
}

bool ShipNavRoute::fromJson(const web::json::value& val)
{
    bool ok = true;
    
    if(val.has_field(utility::conversions::to_string_t(U("destination"))))
    {
        const web::json::value& fieldValue = val.at(utility::conversions::to_string_t(U("destination")));
        if(!fieldValue.is_null())
        {
            std::shared_ptr<ShipNavRouteWaypoint> refVal_setDestination;
            ok &= ModelBase::fromJson(fieldValue, refVal_setDestination);
            setDestination(refVal_setDestination);
        }
    }
    if(val.has_field(utility::conversions::to_string_t(U("origin"))))
    {
        const web::json::value& fieldValue = val.at(utility::conversions::to_string_t(U("origin")));
        if(!fieldValue.is_null())
        {
            std::shared_ptr<ShipNavRouteWaypoint> refVal_setOrigin;
            ok &= ModelBase::fromJson(fieldValue, refVal_setOrigin);
            setOrigin(refVal_setOrigin);
        }
    }
    if(val.has_field(utility::conversions::to_string_t(U("departureTime"))))
    {
        const web::json::value& fieldValue = val.at(utility::conversions::to_string_t(U("departureTime")));
        if(!fieldValue.is_null())
        {
            utility::datetime refVal_setDepartureTime;
            ok &= ModelBase::fromJson(fieldValue, refVal_setDepartureTime);
            setDepartureTime(refVal_setDepartureTime);
        }
    }
    if(val.has_field(utility::conversions::to_string_t(U("arrival"))))
    {
        const web::json::value& fieldValue = val.at(utility::conversions::to_string_t(U("arrival")));
        if(!fieldValue.is_null())
        {
            utility::datetime refVal_setArrival;
            ok &= ModelBase::fromJson(fieldValue, refVal_setArrival);
            setArrival(refVal_setArrival);
        }
    }
    return ok;
}

void ShipNavRoute::toMultipart(std::shared_ptr<MultipartFormData> multipart, const utility::string_t& prefix) const
{
    utility::string_t namePrefix = prefix;
    if(namePrefix.size() > 0 && namePrefix.substr(namePrefix.size() - 1) != utility::conversions::to_string_t(U(".")))
    {
        namePrefix += utility::conversions::to_string_t(U("."));
    }
    if(m_DestinationIsSet)
    {
        multipart->add(ModelBase::toHttpContent(namePrefix + utility::conversions::to_string_t(U("destination")), m_Destination));
    }
    if(m_OriginIsSet)
    {
        multipart->add(ModelBase::toHttpContent(namePrefix + utility::conversions::to_string_t(U("origin")), m_Origin));
    }
    if(m_DepartureTimeIsSet)
    {
        multipart->add(ModelBase::toHttpContent(namePrefix + utility::conversions::to_string_t(U("departureTime")), m_DepartureTime));
    }
    if(m_ArrivalIsSet)
    {
        multipart->add(ModelBase::toHttpContent(namePrefix + utility::conversions::to_string_t(U("arrival")), m_Arrival));
    }
}

bool ShipNavRoute::fromMultiPart(std::shared_ptr<MultipartFormData> multipart, const utility::string_t& prefix)
{
    bool ok = true;
    utility::string_t namePrefix = prefix;
    if(namePrefix.size() > 0 && namePrefix.substr(namePrefix.size() - 1) != utility::conversions::to_string_t(U(".")))
    {
        namePrefix += utility::conversions::to_string_t(U("."));
    }

    if(multipart->hasContent(utility::conversions::to_string_t(U("destination"))))
    {
        std::shared_ptr<ShipNavRouteWaypoint> refVal_setDestination;
        ok &= ModelBase::fromHttpContent(multipart->getContent(utility::conversions::to_string_t(U("destination"))), refVal_setDestination );
        setDestination(refVal_setDestination);
    }
    if(multipart->hasContent(utility::conversions::to_string_t(U("origin"))))
    {
        std::shared_ptr<ShipNavRouteWaypoint> refVal_setOrigin;
        ok &= ModelBase::fromHttpContent(multipart->getContent(utility::conversions::to_string_t(U("origin"))), refVal_setOrigin );
        setOrigin(refVal_setOrigin);
    }
    if(multipart->hasContent(utility::conversions::to_string_t(U("departureTime"))))
    {
        utility::datetime refVal_setDepartureTime;
        ok &= ModelBase::fromHttpContent(multipart->getContent(utility::conversions::to_string_t(U("departureTime"))), refVal_setDepartureTime );
        setDepartureTime(refVal_setDepartureTime);
    }
    if(multipart->hasContent(utility::conversions::to_string_t(U("arrival"))))
    {
        utility::datetime refVal_setArrival;
        ok &= ModelBase::fromHttpContent(multipart->getContent(utility::conversions::to_string_t(U("arrival"))), refVal_setArrival );
        setArrival(refVal_setArrival);
    }
    return ok;
}

std::shared_ptr<ShipNavRouteWaypoint> ShipNavRoute::getDestination() const
{
    return m_Destination;
}

void ShipNavRoute::setDestination(const std::shared_ptr<ShipNavRouteWaypoint>& value)
{
    m_Destination = value;
    m_DestinationIsSet = true;
}

bool ShipNavRoute::destinationIsSet() const
{
    return m_DestinationIsSet;
}

void ShipNavRoute::unsetDestination()
{
    m_DestinationIsSet = false;
}
std::shared_ptr<ShipNavRouteWaypoint> ShipNavRoute::getOrigin() const
{
    return m_Origin;
}

void ShipNavRoute::setOrigin(const std::shared_ptr<ShipNavRouteWaypoint>& value)
{
    m_Origin = value;
    m_OriginIsSet = true;
}

bool ShipNavRoute::originIsSet() const
{
    return m_OriginIsSet;
}

void ShipNavRoute::unsetOrigin()
{
    m_OriginIsSet = false;
}
utility::datetime ShipNavRoute::getDepartureTime() const
{
    return m_DepartureTime;
}

void ShipNavRoute::setDepartureTime(const utility::datetime& value)
{
    m_DepartureTime = value;
    m_DepartureTimeIsSet = true;
}

bool ShipNavRoute::departureTimeIsSet() const
{
    return m_DepartureTimeIsSet;
}

void ShipNavRoute::unsetDepartureTime()
{
    m_DepartureTimeIsSet = false;
}
utility::datetime ShipNavRoute::getArrival() const
{
    return m_Arrival;
}

void ShipNavRoute::setArrival(const utility::datetime& value)
{
    m_Arrival = value;
    m_ArrivalIsSet = true;
}

bool ShipNavRoute::arrivalIsSet() const
{
    return m_ArrivalIsSet;
}

void ShipNavRoute::unsetArrival()
{
    m_ArrivalIsSet = false;
}
}

