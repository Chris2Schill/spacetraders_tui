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
 * Navigate_ship_200_response_data.h
 *
 * 
 */

#ifndef MODELS_Navigate_ship_200_response_data_H_
#define MODELS_Navigate_ship_200_response_data_H_


#include "CppRestOpenAPIClient/ModelBase.h"

#include "CppRestOpenAPIClient/model/ShipFuel.h"
#include "CppRestOpenAPIClient/model/ShipNav.h"

namespace models {

class ShipFuel;
class ShipNav;

/// <summary>
/// 
/// </summary>
class  Navigate_ship_200_response_data
    : public ModelBase
{
public:
    Navigate_ship_200_response_data();
    virtual ~Navigate_ship_200_response_data();

    /////////////////////////////////////////////
    /// ModelBase overrides

    void validate() override;

    web::json::value toJson() const override;
    bool fromJson(const web::json::value& json) override;

    void toMultipart(std::shared_ptr<MultipartFormData> multipart, const utility::string_t& namePrefix) const override;
    bool fromMultiPart(std::shared_ptr<MultipartFormData> multipart, const utility::string_t& namePrefix) override;

    /////////////////////////////////////////////
    /// Navigate_ship_200_response_data members

    /// <summary>
    /// 
    /// </summary>
    std::shared_ptr<ShipFuel> getFuel() const;
    bool fuelIsSet() const;
    void unsetFuel();

    void setFuel(const std::shared_ptr<ShipFuel>& value);

    /// <summary>
    /// 
    /// </summary>
    std::shared_ptr<ShipNav> getNav() const;
    bool navIsSet() const;
    void unsetNav();

    void setNav(const std::shared_ptr<ShipNav>& value);


protected:
    std::shared_ptr<ShipFuel> m_Fuel;
    bool m_FuelIsSet;
    std::shared_ptr<ShipNav> m_Nav;
    bool m_NavIsSet;
};


}

#endif /* MODELS_Navigate_ship_200_response_data_H_ */
