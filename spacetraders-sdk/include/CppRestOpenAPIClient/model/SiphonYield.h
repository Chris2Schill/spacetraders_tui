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
 * SiphonYield.h
 *
 * A yield from the siphon operation.
 */

#ifndef MODELS_SiphonYield_H_
#define MODELS_SiphonYield_H_


#include "CppRestOpenAPIClient/ModelBase.h"

#include "CppRestOpenAPIClient/model/TradeSymbol.h"

namespace models {


/// <summary>
/// A yield from the siphon operation.
/// </summary>
class  SiphonYield
    : public ModelBase
{
public:
    SiphonYield();
    virtual ~SiphonYield();

    /////////////////////////////////////////////
    /// ModelBase overrides

    void validate() override;

    web::json::value toJson() const override;
    bool fromJson(const web::json::value& json) override;

    void toMultipart(std::shared_ptr<MultipartFormData> multipart, const utility::string_t& namePrefix) const override;
    bool fromMultiPart(std::shared_ptr<MultipartFormData> multipart, const utility::string_t& namePrefix) override;

    /////////////////////////////////////////////
    /// SiphonYield members

    /// <summary>
    /// 
    /// </summary>
    std::shared_ptr<TradeSymbol> getSymbol() const;
    bool symbolIsSet() const;
    void unsetSymbol();

    void setSymbol(const std::shared_ptr<TradeSymbol>& value);

    /// <summary>
    /// The number of units siphoned that were placed into the ship&#39;s cargo hold.
    /// </summary>
    int32_t getUnits() const;
    bool unitsIsSet() const;
    void unsetUnits();

    void setUnits(int32_t value);


protected:
    std::shared_ptr<TradeSymbol> m_Symbol;
    bool m_SymbolIsSet;
    int32_t m_Units;
    bool m_UnitsIsSet;
};


}

#endif /* MODELS_SiphonYield_H_ */