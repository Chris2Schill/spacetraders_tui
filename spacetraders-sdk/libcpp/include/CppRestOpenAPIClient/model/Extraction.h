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
 * Extraction.h
 *
 * Extraction details.
 */

#ifndef MODELS_Extraction_H_
#define MODELS_Extraction_H_


#include "CppRestOpenAPIClient/ModelBase.h"

#include <cpprest/details/basic_types.h>
#include "CppRestOpenAPIClient/model/ExtractionYield.h"

namespace models {

class ExtractionYield;

/// <summary>
/// Extraction details.
/// </summary>
class  Extraction
    : public ModelBase
{
public:
    Extraction();
    virtual ~Extraction();

    /////////////////////////////////////////////
    /// ModelBase overrides

    void validate() override;

    web::json::value toJson() const override;
    bool fromJson(const web::json::value& json) override;

    void toMultipart(std::shared_ptr<MultipartFormData> multipart, const utility::string_t& namePrefix) const override;
    bool fromMultiPart(std::shared_ptr<MultipartFormData> multipart, const utility::string_t& namePrefix) override;

    /////////////////////////////////////////////
    /// Extraction members

    /// <summary>
    /// Symbol of the ship that executed the extraction.
    /// </summary>
    utility::string_t getShipSymbol() const;
    bool shipSymbolIsSet() const;
    void unsetShipSymbol();

    void setShipSymbol(const utility::string_t& value);

    /// <summary>
    /// 
    /// </summary>
    std::shared_ptr<ExtractionYield> getYield() const;
    bool yieldIsSet() const;
    void unsetYield();

    void setYield(const std::shared_ptr<ExtractionYield>& value);


protected:
    utility::string_t m_ShipSymbol;
    bool m_ShipSymbolIsSet;
    std::shared_ptr<ExtractionYield> m_Yield;
    bool m_YieldIsSet;
};


}

#endif /* MODELS_Extraction_H_ */
