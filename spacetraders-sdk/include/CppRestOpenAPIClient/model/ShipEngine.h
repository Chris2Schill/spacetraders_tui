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
 * ShipEngine.h
 *
 * The engine determines how quickly a ship travels between waypoints.
 */

#ifndef MODELS_ShipEngine_H_
#define MODELS_ShipEngine_H_


#include "CppRestOpenAPIClient/ModelBase.h"

#include <cpprest/details/basic_types.h>
#include "CppRestOpenAPIClient/model/ShipRequirements.h"

namespace models {

class ShipRequirements;

/// <summary>
/// The engine determines how quickly a ship travels between waypoints.
/// </summary>
class  ShipEngine
    : public ModelBase
{
public:
    ShipEngine();
    virtual ~ShipEngine();

    /////////////////////////////////////////////
    /// ModelBase overrides

    void validate() override;

    web::json::value toJson() const override;
    bool fromJson(const web::json::value& json) override;

    void toMultipart(std::shared_ptr<MultipartFormData> multipart, const utility::string_t& namePrefix) const override;
    bool fromMultiPart(std::shared_ptr<MultipartFormData> multipart, const utility::string_t& namePrefix) override;

    /////////////////////////////////////////////
    /// ShipEngine members

    /// <summary>
    /// The symbol of the engine.
    /// </summary>
    utility::string_t getSymbol() const;
    bool symbolIsSet() const;
    void unsetSymbol();

    void setSymbol(const utility::string_t& value);

    /// <summary>
    /// The name of the engine.
    /// </summary>
    utility::string_t getName() const;
    bool nameIsSet() const;
    void unsetName();

    void setName(const utility::string_t& value);

    /// <summary>
    /// The description of the engine.
    /// </summary>
    utility::string_t getDescription() const;
    bool descriptionIsSet() const;
    void unsetDescription();

    void setDescription(const utility::string_t& value);

    /// <summary>
    /// Condition is a range of 0 to 100 where 0 is completely worn out and 100 is brand new.
    /// </summary>
    int32_t getCondition() const;
    bool conditionIsSet() const;
    void unsetCondition();

    void setCondition(int32_t value);

    /// <summary>
    /// The speed stat of this engine. The higher the speed, the faster a ship can travel from one point to another. Reduces the time of arrival when navigating the ship.
    /// </summary>
    int32_t getSpeed() const;
    bool speedIsSet() const;
    void unsetSpeed();

    void setSpeed(int32_t value);

    /// <summary>
    /// 
    /// </summary>
    std::shared_ptr<ShipRequirements> getRequirements() const;
    bool requirementsIsSet() const;
    void unsetRequirements();

    void setRequirements(const std::shared_ptr<ShipRequirements>& value);


protected:
    utility::string_t m_Symbol;
    bool m_SymbolIsSet;
    utility::string_t m_Name;
    bool m_NameIsSet;
    utility::string_t m_Description;
    bool m_DescriptionIsSet;
    int32_t m_Condition;
    bool m_ConditionIsSet;
    int32_t m_Speed;
    bool m_SpeedIsSet;
    std::shared_ptr<ShipRequirements> m_Requirements;
    bool m_RequirementsIsSet;
};


}

#endif /* MODELS_ShipEngine_H_ */
