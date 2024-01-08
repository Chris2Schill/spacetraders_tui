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
 * ShipFuel.h
 *
 * Details of the ship&#39;s fuel tanks including how much fuel was consumed during the last transit or action.
 */

#ifndef MODELS_ShipFuel_H_
#define MODELS_ShipFuel_H_


#include "CppRestOpenAPIClient/ModelBase.h"

#include "CppRestOpenAPIClient/model/ShipFuel_consumed.h"

namespace models {

class ShipFuel_consumed;

/// <summary>
/// Details of the ship&#39;s fuel tanks including how much fuel was consumed during the last transit or action.
/// </summary>
class  ShipFuel
    : public ModelBase
{
public:
    ShipFuel();
    virtual ~ShipFuel();

    /////////////////////////////////////////////
    /// ModelBase overrides

    void validate() override;

    web::json::value toJson() const override;
    bool fromJson(const web::json::value& json) override;

    void toMultipart(std::shared_ptr<MultipartFormData> multipart, const utility::string_t& namePrefix) const override;
    bool fromMultiPart(std::shared_ptr<MultipartFormData> multipart, const utility::string_t& namePrefix) override;

    /////////////////////////////////////////////
    /// ShipFuel members

    /// <summary>
    /// The current amount of fuel in the ship&#39;s tanks.
    /// </summary>
    int32_t getCurrent() const;
    bool currentIsSet() const;
    void unsetCurrent();

    void setCurrent(int32_t value);

    /// <summary>
    /// The maximum amount of fuel the ship&#39;s tanks can hold.
    /// </summary>
    int32_t getCapacity() const;
    bool capacityIsSet() const;
    void unsetCapacity();

    void setCapacity(int32_t value);

    /// <summary>
    /// 
    /// </summary>
    std::shared_ptr<ShipFuel_consumed> getConsumed() const;
    bool consumedIsSet() const;
    void unsetConsumed();

    void setConsumed(const std::shared_ptr<ShipFuel_consumed>& value);


protected:
    int32_t m_Current;
    bool m_CurrentIsSet;
    int32_t m_Capacity;
    bool m_CapacityIsSet;
    std::shared_ptr<ShipFuel_consumed> m_Consumed;
    bool m_ConsumedIsSet;
};


}

#endif /* MODELS_ShipFuel_H_ */
