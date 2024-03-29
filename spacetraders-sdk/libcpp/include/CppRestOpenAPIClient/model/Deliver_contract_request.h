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
 * Deliver_contract_request.h
 *
 * 
 */

#ifndef MODELS_Deliver_contract_request_H_
#define MODELS_Deliver_contract_request_H_


#include "CppRestOpenAPIClient/ModelBase.h"

#include <cpprest/details/basic_types.h>

namespace models {


/// <summary>
/// 
/// </summary>
class  Deliver_contract_request
    : public ModelBase
{
public:
    Deliver_contract_request();
    virtual ~Deliver_contract_request();

    /////////////////////////////////////////////
    /// ModelBase overrides

    void validate() override;

    web::json::value toJson() const override;
    bool fromJson(const web::json::value& json) override;

    void toMultipart(std::shared_ptr<MultipartFormData> multipart, const utility::string_t& namePrefix) const override;
    bool fromMultiPart(std::shared_ptr<MultipartFormData> multipart, const utility::string_t& namePrefix) override;

    /////////////////////////////////////////////
    /// Deliver_contract_request members

    /// <summary>
    /// Symbol of a ship located in the destination to deliver a contract and that has a good to deliver in its cargo.
    /// </summary>
    utility::string_t getShipSymbol() const;
    bool shipSymbolIsSet() const;
    void unsetShipSymbol();

    void setShipSymbol(const utility::string_t& value);

    /// <summary>
    /// The symbol of the good to deliver.
    /// </summary>
    utility::string_t getTradeSymbol() const;
    bool tradeSymbolIsSet() const;
    void unsetTradeSymbol();

    void setTradeSymbol(const utility::string_t& value);

    /// <summary>
    /// Amount of units to deliver.
    /// </summary>
    int32_t getUnits() const;
    bool unitsIsSet() const;
    void unsetUnits();

    void setUnits(int32_t value);


protected:
    utility::string_t m_ShipSymbol;
    bool m_ShipSymbolIsSet;
    utility::string_t m_TradeSymbol;
    bool m_TradeSymbolIsSet;
    int32_t m_Units;
    bool m_UnitsIsSet;
};


}

#endif /* MODELS_Deliver_contract_request_H_ */
