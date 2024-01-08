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
 * Contract.h
 *
 * Contract details.
 */

#ifndef MODELS_Contract_H_
#define MODELS_Contract_H_


#include "CppRestOpenAPIClient/ModelBase.h"

#include <cpprest/details/basic_types.h>
#include "CppRestOpenAPIClient/model/ContractTerms.h"

namespace models {

class ContractTerms;

/// <summary>
/// Contract details.
/// </summary>
class  Contract
    : public ModelBase
{
public:
    Contract();
    virtual ~Contract();

    /////////////////////////////////////////////
    /// ModelBase overrides

    void validate() override;

    web::json::value toJson() const override;
    bool fromJson(const web::json::value& json) override;

    void toMultipart(std::shared_ptr<MultipartFormData> multipart, const utility::string_t& namePrefix) const override;
    bool fromMultiPart(std::shared_ptr<MultipartFormData> multipart, const utility::string_t& namePrefix) override;

    /////////////////////////////////////////////
    /// Contract members

    /// <summary>
    /// ID of the contract.
    /// </summary>
    utility::string_t getId() const;
    bool idIsSet() const;
    void unsetId();

    void setId(const utility::string_t& value);

    /// <summary>
    /// The symbol of the faction that this contract is for.
    /// </summary>
    utility::string_t getFactionSymbol() const;
    bool factionSymbolIsSet() const;
    void unsetFactionSymbol();

    void setFactionSymbol(const utility::string_t& value);

    /// <summary>
    /// Type of contract.
    /// </summary>
    utility::string_t getType() const;
    bool typeIsSet() const;
    void unsetType();

    void setType(const utility::string_t& value);

    /// <summary>
    /// 
    /// </summary>
    std::shared_ptr<ContractTerms> getTerms() const;
    bool termsIsSet() const;
    void unsetTerms();

    void setTerms(const std::shared_ptr<ContractTerms>& value);

    /// <summary>
    /// Whether the contract has been accepted by the agent
    /// </summary>
    bool isAccepted() const;
    bool acceptedIsSet() const;
    void unsetAccepted();

    void setAccepted(bool value);

    /// <summary>
    /// Whether the contract has been fulfilled
    /// </summary>
    bool isFulfilled() const;
    bool fulfilledIsSet() const;
    void unsetFulfilled();

    void setFulfilled(bool value);

    /// <summary>
    /// Deprecated in favor of deadlineToAccept
    /// </summary>
    utility::datetime getExpiration() const;
    bool expirationIsSet() const;
    void unsetExpiration();

    void setExpiration(const utility::datetime& value);

    /// <summary>
    /// The time at which the contract is no longer available to be accepted
    /// </summary>
    utility::datetime getDeadlineToAccept() const;
    bool deadlineToAcceptIsSet() const;
    void unsetDeadlineToAccept();

    void setDeadlineToAccept(const utility::datetime& value);


protected:
    utility::string_t m_Id;
    bool m_IdIsSet;
    utility::string_t m_FactionSymbol;
    bool m_FactionSymbolIsSet;
    utility::string_t m_Type;
    bool m_TypeIsSet;
    std::shared_ptr<ContractTerms> m_Terms;
    bool m_TermsIsSet;
    bool m_Accepted;
    bool m_AcceptedIsSet;
    bool m_Fulfilled;
    bool m_FulfilledIsSet;
    utility::datetime m_Expiration;
    bool m_ExpirationIsSet;
    utility::datetime m_DeadlineToAccept;
    bool m_DeadlineToAcceptIsSet;
};


}

#endif /* MODELS_Contract_H_ */
