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
 * Survey.h
 *
 * A resource survey of a waypoint, detailing a specific extraction location and the types of resources that can be found there.
 */

#ifndef MODELS_Survey_H_
#define MODELS_Survey_H_


#include "CppRestOpenAPIClient/ModelBase.h"

#include <cpprest/details/basic_types.h>
#include "CppRestOpenAPIClient/model/SurveyDeposit.h"
#include <vector>

namespace models {

class SurveyDeposit;

/// <summary>
/// A resource survey of a waypoint, detailing a specific extraction location and the types of resources that can be found there.
/// </summary>
class  Survey
    : public ModelBase
{
public:
    Survey();
    virtual ~Survey();

    /////////////////////////////////////////////
    /// ModelBase overrides

    void validate() override;

    web::json::value toJson() const override;
    bool fromJson(const web::json::value& json) override;

    void toMultipart(std::shared_ptr<MultipartFormData> multipart, const utility::string_t& namePrefix) const override;
    bool fromMultiPart(std::shared_ptr<MultipartFormData> multipart, const utility::string_t& namePrefix) override;

    /////////////////////////////////////////////
    /// Survey members

    /// <summary>
    /// A unique signature for the location of this survey. This signature is verified when attempting an extraction using this survey.
    /// </summary>
    utility::string_t getSignature() const;
    bool signatureIsSet() const;
    void unsetSignature();

    void setSignature(const utility::string_t& value);

    /// <summary>
    /// The symbol of the waypoint that this survey is for.
    /// </summary>
    utility::string_t getSymbol() const;
    bool symbolIsSet() const;
    void unsetSymbol();

    void setSymbol(const utility::string_t& value);

    /// <summary>
    /// A list of deposits that can be found at this location. A ship will extract one of these deposits when using this survey in an extraction request. If multiple deposits of the same type are present, the chance of extracting that deposit is increased.
    /// </summary>
    std::vector<std::shared_ptr<SurveyDeposit>>& getDeposits();
    bool depositsIsSet() const;
    void unsetDeposits();

    void setDeposits(const std::vector<std::shared_ptr<SurveyDeposit>>& value);

    /// <summary>
    /// The date and time when the survey expires. After this date and time, the survey will no longer be available for extraction.
    /// </summary>
    utility::datetime getExpiration() const;
    bool expirationIsSet() const;
    void unsetExpiration();

    void setExpiration(const utility::datetime& value);

    /// <summary>
    /// The size of the deposit. This value indicates how much can be extracted from the survey before it is exhausted.
    /// </summary>
    utility::string_t getSize() const;
    bool sizeIsSet() const;
    void unsetSize();

    void setSize(const utility::string_t& value);


protected:
    utility::string_t m_Signature;
    bool m_SignatureIsSet;
    utility::string_t m_Symbol;
    bool m_SymbolIsSet;
    std::vector<std::shared_ptr<SurveyDeposit>> m_Deposits;
    bool m_DepositsIsSet;
    utility::datetime m_Expiration;
    bool m_ExpirationIsSet;
    utility::string_t m_Size;
    bool m_SizeIsSet;
};


}

#endif /* MODELS_Survey_H_ */
