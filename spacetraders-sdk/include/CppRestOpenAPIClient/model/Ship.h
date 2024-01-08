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
 * Ship.h
 *
 * Ship details.
 */

#ifndef MODELS_Ship_H_
#define MODELS_Ship_H_


#include "CppRestOpenAPIClient/ModelBase.h"

#include "CppRestOpenAPIClient/model/Cooldown.h"
#include "CppRestOpenAPIClient/model/ShipFuel.h"
#include "CppRestOpenAPIClient/model/ShipCargo.h"
#include <vector>
#include "CppRestOpenAPIClient/model/ShipNav.h"
#include "CppRestOpenAPIClient/model/ShipFrame.h"
#include "CppRestOpenAPIClient/model/ShipMount.h"
#include "CppRestOpenAPIClient/model/ShipRegistration.h"
#include "CppRestOpenAPIClient/model/ShipModule.h"
#include "CppRestOpenAPIClient/model/ShipReactor.h"
#include <cpprest/details/basic_types.h>
#include "CppRestOpenAPIClient/model/ShipCrew.h"
#include "CppRestOpenAPIClient/model/ShipEngine.h"

namespace models {

class ShipRegistration;
class ShipNav;
class ShipCrew;
class ShipFrame;
class ShipReactor;
class ShipEngine;
class Cooldown;
class ShipModule;
class ShipMount;
class ShipCargo;
class ShipFuel;

/// <summary>
/// Ship details.
/// </summary>
class  Ship
    : public ModelBase
{
public:
    Ship();
    virtual ~Ship();

    /////////////////////////////////////////////
    /// ModelBase overrides

    void validate() override;

    web::json::value toJson() const override;
    bool fromJson(const web::json::value& json) override;

    void toMultipart(std::shared_ptr<MultipartFormData> multipart, const utility::string_t& namePrefix) const override;
    bool fromMultiPart(std::shared_ptr<MultipartFormData> multipart, const utility::string_t& namePrefix) override;

    /////////////////////////////////////////////
    /// Ship members

    /// <summary>
    /// The globally unique identifier of the ship in the following format: &#x60;[AGENT_SYMBOL]-[HEX_ID]&#x60;
    /// </summary>
    utility::string_t getSymbol() const;
    bool symbolIsSet() const;
    void unsetSymbol();

    void setSymbol(const utility::string_t& value);

    /// <summary>
    /// 
    /// </summary>
    std::shared_ptr<ShipRegistration> getRegistration() const;
    bool registrationIsSet() const;
    void unsetRegistration();

    void setRegistration(const std::shared_ptr<ShipRegistration>& value);

    /// <summary>
    /// 
    /// </summary>
    std::shared_ptr<ShipNav> getNav() const;
    bool navIsSet() const;
    void unsetNav();

    void setNav(const std::shared_ptr<ShipNav>& value);

    /// <summary>
    /// 
    /// </summary>
    std::shared_ptr<ShipCrew> getCrew() const;
    bool crewIsSet() const;
    void unsetCrew();

    void setCrew(const std::shared_ptr<ShipCrew>& value);

    /// <summary>
    /// 
    /// </summary>
    std::shared_ptr<ShipFrame> getFrame() const;
    bool frameIsSet() const;
    void unsetFrame();

    void setFrame(const std::shared_ptr<ShipFrame>& value);

    /// <summary>
    /// 
    /// </summary>
    std::shared_ptr<ShipReactor> getReactor() const;
    bool reactorIsSet() const;
    void unsetReactor();

    void setReactor(const std::shared_ptr<ShipReactor>& value);

    /// <summary>
    /// 
    /// </summary>
    std::shared_ptr<ShipEngine> getEngine() const;
    bool engineIsSet() const;
    void unsetEngine();

    void setEngine(const std::shared_ptr<ShipEngine>& value);

    /// <summary>
    /// 
    /// </summary>
    std::shared_ptr<Cooldown> getCooldown() const;
    bool cooldownIsSet() const;
    void unsetCooldown();

    void setCooldown(const std::shared_ptr<Cooldown>& value);

    /// <summary>
    /// Modules installed in this ship.
    /// </summary>
    std::vector<std::shared_ptr<ShipModule>>& getModules();
    bool modulesIsSet() const;
    void unsetModules();

    void setModules(const std::vector<std::shared_ptr<ShipModule>>& value);

    /// <summary>
    /// Mounts installed in this ship.
    /// </summary>
    std::vector<std::shared_ptr<ShipMount>>& getMounts();
    bool mountsIsSet() const;
    void unsetMounts();

    void setMounts(const std::vector<std::shared_ptr<ShipMount>>& value);

    /// <summary>
    /// 
    /// </summary>
    std::shared_ptr<ShipCargo> getCargo() const;
    bool cargoIsSet() const;
    void unsetCargo();

    void setCargo(const std::shared_ptr<ShipCargo>& value);

    /// <summary>
    /// 
    /// </summary>
    std::shared_ptr<ShipFuel> getFuel() const;
    bool fuelIsSet() const;
    void unsetFuel();

    void setFuel(const std::shared_ptr<ShipFuel>& value);


protected:
    utility::string_t m_Symbol;
    bool m_SymbolIsSet;
    std::shared_ptr<ShipRegistration> m_Registration;
    bool m_RegistrationIsSet;
    std::shared_ptr<ShipNav> m_Nav;
    bool m_NavIsSet;
    std::shared_ptr<ShipCrew> m_Crew;
    bool m_CrewIsSet;
    std::shared_ptr<ShipFrame> m_Frame;
    bool m_FrameIsSet;
    std::shared_ptr<ShipReactor> m_Reactor;
    bool m_ReactorIsSet;
    std::shared_ptr<ShipEngine> m_Engine;
    bool m_EngineIsSet;
    std::shared_ptr<Cooldown> m_Cooldown;
    bool m_CooldownIsSet;
    std::vector<std::shared_ptr<ShipModule>> m_Modules;
    bool m_ModulesIsSet;
    std::vector<std::shared_ptr<ShipMount>> m_Mounts;
    bool m_MountsIsSet;
    std::shared_ptr<ShipCargo> m_Cargo;
    bool m_CargoIsSet;
    std::shared_ptr<ShipFuel> m_Fuel;
    bool m_FuelIsSet;
};


}

#endif /* MODELS_Ship_H_ */
