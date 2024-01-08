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
 * ShipCrew.h
 *
 * The ship&#39;s crew service and maintain the ship&#39;s systems and equipment.
 */

#ifndef MODELS_ShipCrew_H_
#define MODELS_ShipCrew_H_


#include "CppRestOpenAPIClient/ModelBase.h"

#include <cpprest/details/basic_types.h>

namespace models {


/// <summary>
/// The ship&#39;s crew service and maintain the ship&#39;s systems and equipment.
/// </summary>
class  ShipCrew
    : public ModelBase
{
public:
    ShipCrew();
    virtual ~ShipCrew();

    /////////////////////////////////////////////
    /// ModelBase overrides

    void validate() override;

    web::json::value toJson() const override;
    bool fromJson(const web::json::value& json) override;

    void toMultipart(std::shared_ptr<MultipartFormData> multipart, const utility::string_t& namePrefix) const override;
    bool fromMultiPart(std::shared_ptr<MultipartFormData> multipart, const utility::string_t& namePrefix) override;

    /////////////////////////////////////////////
    /// ShipCrew members

    /// <summary>
    /// The current number of crew members on the ship.
    /// </summary>
    int32_t getCurrent() const;
    bool currentIsSet() const;
    void unsetCurrent();

    void setCurrent(int32_t value);

    /// <summary>
    /// The minimum number of crew members required to maintain the ship.
    /// </summary>
    int32_t getRequired() const;
    bool requiredIsSet() const;
    void unsetRequired();

    void setRequired(int32_t value);

    /// <summary>
    /// The maximum number of crew members the ship can support.
    /// </summary>
    int32_t getCapacity() const;
    bool capacityIsSet() const;
    void unsetCapacity();

    void setCapacity(int32_t value);

    /// <summary>
    /// The rotation of crew shifts. A stricter shift improves the ship&#39;s performance. A more relaxed shift improves the crew&#39;s morale.
    /// </summary>
    utility::string_t getRotation() const;
    bool rotationIsSet() const;
    void unsetRotation();

    void setRotation(const utility::string_t& value);

    /// <summary>
    /// A rough measure of the crew&#39;s morale. A higher morale means the crew is happier and more productive. A lower morale means the ship is more prone to accidents.
    /// </summary>
    int32_t getMorale() const;
    bool moraleIsSet() const;
    void unsetMorale();

    void setMorale(int32_t value);

    /// <summary>
    /// The amount of credits per crew member paid per hour. Wages are paid when a ship docks at a civilized waypoint.
    /// </summary>
    int32_t getWages() const;
    bool wagesIsSet() const;
    void unsetWages();

    void setWages(int32_t value);


protected:
    int32_t m_Current;
    bool m_CurrentIsSet;
    int32_t m_Required;
    bool m_RequiredIsSet;
    int32_t m_Capacity;
    bool m_CapacityIsSet;
    utility::string_t m_Rotation;
    bool m_RotationIsSet;
    int32_t m_Morale;
    bool m_MoraleIsSet;
    int32_t m_Wages;
    bool m_WagesIsSet;
};


}

#endif /* MODELS_ShipCrew_H_ */
