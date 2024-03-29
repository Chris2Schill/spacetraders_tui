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
 * ShipFrame.h
 *
 * The frame of the ship. The frame determines the number of modules and mounting points of the ship, as well as base fuel capacity. As the condition of the frame takes more wear, the ship will become more sluggish and less maneuverable.
 */

#ifndef MODELS_ShipFrame_H_
#define MODELS_ShipFrame_H_


#include "CppRestOpenAPIClient/ModelBase.h"

#include <cpprest/details/basic_types.h>
#include "CppRestOpenAPIClient/model/ShipRequirements.h"

namespace models {

class ShipRequirements;

/// <summary>
/// The frame of the ship. The frame determines the number of modules and mounting points of the ship, as well as base fuel capacity. As the condition of the frame takes more wear, the ship will become more sluggish and less maneuverable.
/// </summary>
class  ShipFrame
    : public ModelBase
{
public:
    ShipFrame();
    virtual ~ShipFrame();

    /////////////////////////////////////////////
    /// ModelBase overrides

    void validate() override;

    web::json::value toJson() const override;
    bool fromJson(const web::json::value& json) override;

    void toMultipart(std::shared_ptr<MultipartFormData> multipart, const utility::string_t& namePrefix) const override;
    bool fromMultiPart(std::shared_ptr<MultipartFormData> multipart, const utility::string_t& namePrefix) override;

    /////////////////////////////////////////////
    /// ShipFrame members

    /// <summary>
    /// Symbol of the frame.
    /// </summary>
    utility::string_t getSymbol() const;
    bool symbolIsSet() const;
    void unsetSymbol();

    void setSymbol(const utility::string_t& value);

    /// <summary>
    /// Name of the frame.
    /// </summary>
    utility::string_t getName() const;
    bool nameIsSet() const;
    void unsetName();

    void setName(const utility::string_t& value);

    /// <summary>
    /// Description of the frame.
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
    /// The amount of slots that can be dedicated to modules installed in the ship. Each installed module take up a number of slots, and once there are no more slots, no new modules can be installed.
    /// </summary>
    int32_t getModuleSlots() const;
    bool moduleSlotsIsSet() const;
    void unsetModuleSlots();

    void setModuleSlots(int32_t value);

    /// <summary>
    /// The amount of slots that can be dedicated to mounts installed in the ship. Each installed mount takes up a number of points, and once there are no more points remaining, no new mounts can be installed.
    /// </summary>
    int32_t getMountingPoints() const;
    bool mountingPointsIsSet() const;
    void unsetMountingPoints();

    void setMountingPoints(int32_t value);

    /// <summary>
    /// The maximum amount of fuel that can be stored in this ship. When refueling, the ship will be refueled to this amount.
    /// </summary>
    int32_t getFuelCapacity() const;
    bool fuelCapacityIsSet() const;
    void unsetFuelCapacity();

    void setFuelCapacity(int32_t value);

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
    int32_t m_ModuleSlots;
    bool m_ModuleSlotsIsSet;
    int32_t m_MountingPoints;
    bool m_MountingPointsIsSet;
    int32_t m_FuelCapacity;
    bool m_FuelCapacityIsSet;
    std::shared_ptr<ShipRequirements> m_Requirements;
    bool m_RequirementsIsSet;
};


}

#endif /* MODELS_ShipFrame_H_ */
