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
 * MarketTransaction.h
 *
 * Result of a transaction with a market.
 */

#ifndef MODELS_MarketTransaction_H_
#define MODELS_MarketTransaction_H_


#include "CppRestOpenAPIClient/ModelBase.h"

#include <cpprest/details/basic_types.h>

namespace models {


/// <summary>
/// Result of a transaction with a market.
/// </summary>
class  MarketTransaction
    : public ModelBase
{
public:
    MarketTransaction();
    virtual ~MarketTransaction();

    /////////////////////////////////////////////
    /// ModelBase overrides

    void validate() override;

    web::json::value toJson() const override;
    bool fromJson(const web::json::value& json) override;

    void toMultipart(std::shared_ptr<MultipartFormData> multipart, const utility::string_t& namePrefix) const override;
    bool fromMultiPart(std::shared_ptr<MultipartFormData> multipart, const utility::string_t& namePrefix) override;

    /////////////////////////////////////////////
    /// MarketTransaction members

    /// <summary>
    /// The symbol of the waypoint.
    /// </summary>
    utility::string_t getWaypointSymbol() const;
    bool waypointSymbolIsSet() const;
    void unsetWaypointSymbol();

    void setWaypointSymbol(const utility::string_t& value);

    /// <summary>
    /// The symbol of the ship that made the transaction.
    /// </summary>
    utility::string_t getShipSymbol() const;
    bool shipSymbolIsSet() const;
    void unsetShipSymbol();

    void setShipSymbol(const utility::string_t& value);

    /// <summary>
    /// The symbol of the trade good.
    /// </summary>
    utility::string_t getTradeSymbol() const;
    bool tradeSymbolIsSet() const;
    void unsetTradeSymbol();

    void setTradeSymbol(const utility::string_t& value);

    /// <summary>
    /// The type of transaction.
    /// </summary>
    utility::string_t getType() const;
    bool typeIsSet() const;
    void unsetType();

    void setType(const utility::string_t& value);

    /// <summary>
    /// The number of units of the transaction.
    /// </summary>
    int32_t getUnits() const;
    bool unitsIsSet() const;
    void unsetUnits();

    void setUnits(int32_t value);

    /// <summary>
    /// The price per unit of the transaction.
    /// </summary>
    int32_t getPricePerUnit() const;
    bool pricePerUnitIsSet() const;
    void unsetPricePerUnit();

    void setPricePerUnit(int32_t value);

    /// <summary>
    /// The total price of the transaction.
    /// </summary>
    int32_t getTotalPrice() const;
    bool totalPriceIsSet() const;
    void unsetTotalPrice();

    void setTotalPrice(int32_t value);

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
    utility::string_t m_TradeSymbol;
    bool m_TradeSymbolIsSet;
    utility::string_t m_Type;
    bool m_TypeIsSet;
    int32_t m_Units;
    bool m_UnitsIsSet;
    int32_t m_PricePerUnit;
    bool m_PricePerUnitIsSet;
    int32_t m_TotalPrice;
    bool m_TotalPriceIsSet;
    utility::datetime m_Timestamp;
    bool m_TimestampIsSet;
};


}

#endif /* MODELS_MarketTransaction_H_ */
