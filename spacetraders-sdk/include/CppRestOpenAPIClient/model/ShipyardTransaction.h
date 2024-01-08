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
 * ShipyardTransaction.h
 *
 * Results of a transaction with a shipyard.
 */

#ifndef MODELS_ShipyardTransaction_H_
#define MODELS_ShipyardTransaction_H_


#include "CppRestOpenAPIClient/ModelBase.h"

#include <cpprest/details/basic_types.h>

namespace models {


/// <summary>
/// Results of a transaction with a shipyard.
/// </summary>
class  ShipyardTransaction
    : public ModelBase
{
public:
    ShipyardTransaction();
    virtual ~ShipyardTransaction();

    /////////////////////////////////////////////
    /// ModelBase overrides

    void validate() override;

    web::json::value toJson() const override;
    bool fromJson(const web::json::value& json) override;

    void toMultipart(std::shared_ptr<MultipartFormData> multipart, const utility::string_t& namePrefix) const override;
    bool fromMultiPart(std::shared_ptr<MultipartFormData> multipart, const utility::string_t& namePrefix) override;

    /////////////////////////////////////////////
    /// ShipyardTransaction members

    /// <summary>
    /// The symbol of the waypoint.
    /// </summary>
    utility::string_t getWaypointSymbol() const;
    bool waypointSymbolIsSet() const;
    void unsetWaypointSymbol();

    void setWaypointSymbol(const utility::string_t& value);

    /// <summary>
    /// The symbol of the ship that was the subject of the transaction.
    /// </summary>
    utility::string_t getShipSymbol() const;
    bool shipSymbolIsSet() const;
    void unsetShipSymbol();

    void setShipSymbol(const utility::string_t& value);

    /// <summary>
    /// The symbol of the ship that was the subject of the transaction.
    /// </summary>
    utility::string_t getShipType() const;
    bool shipTypeIsSet() const;
    void unsetShipType();

    void setShipType(const utility::string_t& value);

    /// <summary>
    /// The price of the transaction.
    /// </summary>
    int32_t getPrice() const;
    bool priceIsSet() const;
    void unsetPrice();

    void setPrice(int32_t value);

    /// <summary>
    /// The symbol of the agent that made the transaction.
    /// </summary>
    utility::string_t getAgentSymbol() const;
    bool agentSymbolIsSet() const;
    void unsetAgentSymbol();

    void setAgentSymbol(const utility::string_t& value);

    /// <summary>
    /// The timestamp of the transaction.
    /// </summary>
    utility::datetime getTimestamp() const;
    bool timestampIsSet() const;
    void unsetTimestamp();

    void setTimestamp(const utility::datetime& value);


protected:
    utility::string_t m_WaypointSymbol;
    bool m_WaypointSymbolIsSet;
    utility::string_t m_ShipSymbol;
    bool m_ShipSymbolIsSet;
    utility::string_t m_ShipType;
    bool m_ShipTypeIsSet;
    int32_t m_Price;
    bool m_PriceIsSet;
    utility::string_t m_AgentSymbol;
    bool m_AgentSymbolIsSet;
    utility::datetime m_Timestamp;
    bool m_TimestampIsSet;
};


}

#endif /* MODELS_ShipyardTransaction_H_ */
