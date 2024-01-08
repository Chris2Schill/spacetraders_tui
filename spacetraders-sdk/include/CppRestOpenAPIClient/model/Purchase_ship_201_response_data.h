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
 * Purchase_ship_201_response_data.h
 *
 * 
 */

#ifndef MODELS_Purchase_ship_201_response_data_H_
#define MODELS_Purchase_ship_201_response_data_H_


#include "CppRestOpenAPIClient/ModelBase.h"

#include "CppRestOpenAPIClient/model/Ship.h"
#include "CppRestOpenAPIClient/model/ShipyardTransaction.h"
#include "CppRestOpenAPIClient/model/Agent.h"

namespace models {

class Agent;
class Ship;
class ShipyardTransaction;

/// <summary>
/// 
/// </summary>
class  Purchase_ship_201_response_data
    : public ModelBase
{
public:
    Purchase_ship_201_response_data();
    virtual ~Purchase_ship_201_response_data();

    /////////////////////////////////////////////
    /// ModelBase overrides

    void validate() override;

    web::json::value toJson() const override;
    bool fromJson(const web::json::value& json) override;

    void toMultipart(std::shared_ptr<MultipartFormData> multipart, const utility::string_t& namePrefix) const override;
    bool fromMultiPart(std::shared_ptr<MultipartFormData> multipart, const utility::string_t& namePrefix) override;

    /////////////////////////////////////////////
    /// Purchase_ship_201_response_data members

    /// <summary>
    /// 
    /// </summary>
    std::shared_ptr<Agent> getAgent() const;
    bool agentIsSet() const;
    void unsetAgent();

    void setAgent(const std::shared_ptr<Agent>& value);

    /// <summary>
    /// 
    /// </summary>
    std::shared_ptr<Ship> getShip() const;
    bool shipIsSet() const;
    void unsetShip();

    void setShip(const std::shared_ptr<Ship>& value);

    /// <summary>
    /// 
    /// </summary>
    std::shared_ptr<ShipyardTransaction> getTransaction() const;
    bool transactionIsSet() const;
    void unsetTransaction();

    void setTransaction(const std::shared_ptr<ShipyardTransaction>& value);


protected:
    std::shared_ptr<Agent> m_Agent;
    bool m_AgentIsSet;
    std::shared_ptr<Ship> m_Ship;
    bool m_ShipIsSet;
    std::shared_ptr<ShipyardTransaction> m_Transaction;
    bool m_TransactionIsSet;
};


}

#endif /* MODELS_Purchase_ship_201_response_data_H_ */
