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
 * Refuel_ship_request.h
 *
 * 
 */

#ifndef MODELS_Refuel_ship_request_H_
#define MODELS_Refuel_ship_request_H_


#include "CppRestOpenAPIClient/ModelBase.h"


namespace models {


/// <summary>
/// 
/// </summary>
class  Refuel_ship_request
    : public ModelBase
{
public:
    Refuel_ship_request();
    virtual ~Refuel_ship_request();

    /////////////////////////////////////////////
    /// ModelBase overrides

    void validate() override;

    web::json::value toJson() const override;
    bool fromJson(const web::json::value& json) override;

    void toMultipart(std::shared_ptr<MultipartFormData> multipart, const utility::string_t& namePrefix) const override;
    bool fromMultiPart(std::shared_ptr<MultipartFormData> multipart, const utility::string_t& namePrefix) override;

    /////////////////////////////////////////////
    /// Refuel_ship_request members

    /// <summary>
    /// The amount of fuel to fill in the ship&#39;s tanks. When not specified, the ship will be refueled to its maximum fuel capacity. If the amount specified is greater than the ship&#39;s remaining capacity, the ship will only be refueled to its maximum fuel capacity. The amount specified is not in market units but in ship fuel units.
    /// </summary>
    int32_t getUnits() const;
    bool unitsIsSet() const;
    void unsetUnits();

    void setUnits(int32_t value);

    /// <summary>
    /// Wether to use the FUEL thats in your cargo or not. Default: false
    /// </summary>
    bool isFromCargo() const;
    bool fromCargoIsSet() const;
    void unsetFromCargo();

    void setFromCargo(bool value);


protected:
    int32_t m_Units;
    bool m_UnitsIsSet;
    bool m_FromCargo;
    bool m_FromCargoIsSet;
};


}

#endif /* MODELS_Refuel_ship_request_H_ */
