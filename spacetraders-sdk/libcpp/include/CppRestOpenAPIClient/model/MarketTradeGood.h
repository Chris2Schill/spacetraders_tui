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
 * MarketTradeGood.h
 *
 * 
 */

#ifndef MODELS_MarketTradeGood_H_
#define MODELS_MarketTradeGood_H_


#include "CppRestOpenAPIClient/ModelBase.h"

#include "CppRestOpenAPIClient/model/TradeSymbol.h"
#include "CppRestOpenAPIClient/model/SupplyLevel.h"
#include <cpprest/details/basic_types.h>
#include "CppRestOpenAPIClient/model/ActivityLevel.h"

namespace models {


/// <summary>
/// 
/// </summary>
class  MarketTradeGood
    : public ModelBase
{
public:
    MarketTradeGood();
    virtual ~MarketTradeGood();

    /////////////////////////////////////////////
    /// ModelBase overrides

    void validate() override;

    web::json::value toJson() const override;
    bool fromJson(const web::json::value& json) override;

    void toMultipart(std::shared_ptr<MultipartFormData> multipart, const utility::string_t& namePrefix) const override;
    bool fromMultiPart(std::shared_ptr<MultipartFormData> multipart, const utility::string_t& namePrefix) override;

    /////////////////////////////////////////////
    /// MarketTradeGood members

    /// <summary>
    /// 
    /// </summary>
    std::shared_ptr<TradeSymbol> getSymbol() const;
    bool symbolIsSet() const;
    void unsetSymbol();

    void setSymbol(const std::shared_ptr<TradeSymbol>& value);

    /// <summary>
    /// The type of trade good (export, import, or exchange).
    /// </summary>
    utility::string_t getType() const;
    bool typeIsSet() const;
    void unsetType();

    void setType(const utility::string_t& value);

    /// <summary>
    /// This is the maximum number of units that can be purchased or sold at this market in a single trade for this good. Trade volume also gives an indication of price volatility. A market with a low trade volume will have large price swings, while high trade volume will be more resilient to price changes.
    /// </summary>
    int32_t getTradeVolume() const;
    bool tradeVolumeIsSet() const;
    void unsetTradeVolume();

    void setTradeVolume(int32_t value);

    /// <summary>
    /// 
    /// </summary>
    std::shared_ptr<SupplyLevel> getSupply() const;
    bool supplyIsSet() const;
    void unsetSupply();

    void setSupply(const std::shared_ptr<SupplyLevel>& value);

    /// <summary>
    /// 
    /// </summary>
    std::shared_ptr<ActivityLevel> getActivity() const;
    bool activityIsSet() const;
    void unsetActivity();

    void setActivity(const std::shared_ptr<ActivityLevel>& value);

    /// <summary>
    /// The price at which this good can be purchased from the market.
    /// </summary>
    int32_t getPurchasePrice() const;
    bool purchasePriceIsSet() const;
    void unsetPurchasePrice();

    void setPurchasePrice(int32_t value);

    /// <summary>
    /// The price at which this good can be sold to the market.
    /// </summary>
    int32_t getSellPrice() const;
    bool sellPriceIsSet() const;
    void unsetSellPrice();

    void setSellPrice(int32_t value);


protected:
    std::shared_ptr<TradeSymbol> m_Symbol;
    bool m_SymbolIsSet;
    utility::string_t m_Type;
    bool m_TypeIsSet;
    int32_t m_TradeVolume;
    bool m_TradeVolumeIsSet;
    std::shared_ptr<SupplyLevel> m_Supply;
    bool m_SupplyIsSet;
    std::shared_ptr<ActivityLevel> m_Activity;
    bool m_ActivityIsSet;
    int32_t m_PurchasePrice;
    bool m_PurchasePriceIsSet;
    int32_t m_SellPrice;
    bool m_SellPriceIsSet;
};


}

#endif /* MODELS_MarketTradeGood_H_ */
