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
 * ShipMount.h
 *
 * A mount is installed on the exterier of a ship.
 */

#ifndef MODELS_ShipMount_H_
#define MODELS_ShipMount_H_


#include "CppRestOpenAPIClient/ModelBase.h"

#include <cpprest/details/basic_types.h>
#include "CppRestOpenAPIClient/model/ShipRequirements.h"
#include <vector>

namespace models {

class ShipRequirements;

/// <summary>
/// A mount is installed on the exterier of a ship.
/// </summary>
class  ShipMount
    : public ModelBase
{
public:
    ShipMount();
    virtual ~ShipMount();

    /////////////////////////////////////////////
    /// ModelBase overrides

    void validate() override;

    web::json::value toJson() const override;
    bool fromJson(const web::json::value& json) override;

    void toMultipart(std::shared_ptr<MultipartFormData> multipart, const utility::string_t& namePrefix) const override;
    bool fromMultiPart(std::shared_ptr<MultipartFormData> multipart, const utility::string_t& namePrefix) override;

    /////////////////////////////////////////////
    /// ShipMount members

    /// <summary>
    /// Symbo of this mount.
    /// </summary>
    utility::string_t getSymbol() const;
    bool symbolIsSet() const;
    void unsetSymbol();

    void setSymbol(const utility::string_t& value);

    /// <summary>
    /// Name of this mount.
    /// </summary>
    utility::string_t getName() const;
    bool nameIsSet() const;
    void unsetName();

    void setName(const utility::string_t& value);

    /// <summary>
    /// Description of this mount.
    /// </summary>
    utility::string_t getDescription() const;
    bool descriptionIsSet() const;
    void unsetDescription();

    void setDescription(const utility::string_t& value);

    /// <summary>
    /// Mounts that have this value, such as mining lasers, denote how powerful this mount&#39;s capabilities are.
    /// </summary>
    int32_t getStrength() const;
    bool strengthIsSet() const;
    void unsetStrength();

    void setStrength(int32_t value);

    /// <summary>
    /// Mounts that have this value denote what goods can be produced from using the mount.
    /// </summary>
    std::vector<utility::string_t>& getDeposits();
    bool depositsIsSet() const;
    void unsetDeposits();

    void setDeposits(const std::vector<utility::string_t>& value);

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
    int32_t m_Strength;
    bool m_StrengthIsSet;
    std::vector<utility::string_t> m_Deposits;
    bool m_DepositsIsSet;
    std::shared_ptr<ShipRequirements> m_Requirements;
    bool m_RequirementsIsSet;
};


}

#endif /* MODELS_ShipMount_H_ */