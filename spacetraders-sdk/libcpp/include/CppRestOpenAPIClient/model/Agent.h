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
 * Agent.h
 *
 * Agent details.
 */

#ifndef MODELS_Agent_H_
#define MODELS_Agent_H_


#include "CppRestOpenAPIClient/ModelBase.h"

#include <cpprest/details/basic_types.h>

namespace models {


/// <summary>
/// Agent details.
/// </summary>
class  Agent
    : public ModelBase
{
public:
    Agent();
    virtual ~Agent();

    /////////////////////////////////////////////
    /// ModelBase overrides

    void validate() override;

    web::json::value toJson() const override;
    bool fromJson(const web::json::value& json) override;

    void toMultipart(std::shared_ptr<MultipartFormData> multipart, const utility::string_t& namePrefix) const override;
    bool fromMultiPart(std::shared_ptr<MultipartFormData> multipart, const utility::string_t& namePrefix) override;

    /////////////////////////////////////////////
    /// Agent members

    /// <summary>
    /// Account ID that is tied to this agent. Only included on your own agent.
    /// </summary>
    utility::string_t getAccountId() const;
    bool accountIdIsSet() const;
    void unsetAccountId();

    void setAccountId(const utility::string_t& value);

    /// <summary>
    /// Symbol of the agent.
    /// </summary>
    utility::string_t getSymbol() const;
    bool symbolIsSet() const;
    void unsetSymbol();

    void setSymbol(const utility::string_t& value);

    /// <summary>
    /// The headquarters of the agent.
    /// </summary>
    utility::string_t getHeadquarters() const;
    bool headquartersIsSet() const;
    void unsetHeadquarters();

    void setHeadquarters(const utility::string_t& value);

    /// <summary>
    /// The number of credits the agent has available. Credits can be negative if funds have been overdrawn.
    /// </summary>
    int64_t getCredits() const;
    bool creditsIsSet() const;
    void unsetCredits();

    void setCredits(int64_t value);

    /// <summary>
    /// The faction the agent started with.
    /// </summary>
    utility::string_t getStartingFaction() const;
    bool startingFactionIsSet() const;
    void unsetStartingFaction();

    void setStartingFaction(const utility::string_t& value);

    /// <summary>
    /// How many ships are owned by the agent.
    /// </summary>
    int32_t getShipCount() const;
    bool shipCountIsSet() const;
    void unsetShipCount();

    void setShipCount(int32_t value);


protected:
    utility::string_t m_AccountId;
    bool m_AccountIdIsSet;
    utility::string_t m_Symbol;
    bool m_SymbolIsSet;
    utility::string_t m_Headquarters;
    bool m_HeadquartersIsSet;
    int64_t m_Credits;
    bool m_CreditsIsSet;
    utility::string_t m_StartingFaction;
    bool m_StartingFactionIsSet;
    int32_t m_ShipCount;
    bool m_ShipCountIsSet;
};


}

#endif /* MODELS_Agent_H_ */
