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
 * ShipRequirements.h
 *
 * The requirements for installation on a ship
 */

#ifndef MODELS_ShipRequirements_H_
#define MODELS_ShipRequirements_H_


#include "CppRestOpenAPIClient/ModelBase.h"


namespace models {


/// <summary>
/// The requirements for installation on a ship
/// </summary>
class  ShipRequirements
    : public ModelBase
{
public:
    ShipRequirements();
    virtual ~ShipRequirements();

    /////////////////////////////////////////////
    /// ModelBase overrides

    void validate() override;

    web::json::value toJson() const override;
    bool fromJson(const web::json::value& json) override;

    void toMultipart(std::shared_ptr<MultipartFormData> multipart, const utility::string_t& namePrefix) const override;
    bool fromMultiPart(std::shared_ptr<MultipartFormData> multipart, const utility::string_t& namePrefix) override;

    /////////////////////////////////////////////
    /// ShipRequirements members

    /// <summary>
    /// The amount of power required from the reactor.
    /// </summary>
    int32_t getPower() const;
    bool powerIsSet() const;
    void unsetPower();

    void setPower(int32_t value);

    /// <summary>
    /// The number of crew required for operation.
    /// </summary>
    int32_t getCrew() const;
    bool crewIsSet() const;
    void unsetCrew();

    void setCrew(int32_t value);

    /// <summary>
    /// The number of module slots required for installation.
    /// </summary>
    int32_t getSlots() const;
    bool slotsIsSet() const;
    void unsetSlots();

    void setSlots(int32_t value);


protected:
    int32_t m_Power;
    bool m_PowerIsSet;
    int32_t m_Crew;
    bool m_CrewIsSet;
    int32_t m_Slots;
    bool m_SlotsIsSet;
};


}

#endif /* MODELS_ShipRequirements_H_ */