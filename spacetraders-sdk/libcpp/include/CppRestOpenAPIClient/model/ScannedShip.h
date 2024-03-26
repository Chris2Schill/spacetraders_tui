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
 * ScannedShip.h
 *
 * The ship that was scanned. Details include information about the ship that could be detected by the scanner.
 */

#ifndef MODELS_ScannedShip_H_
#define MODELS_ScannedShip_H_


#include "CppRestOpenAPIClient/ModelBase.h"

#include "CppRestOpenAPIClient/model/ScannedShip_reactor.h"
#include "CppRestOpenAPIClient/model/ScannedShip_frame.h"
#include "CppRestOpenAPIClient/model/ShipRegistration.h"
#include <cpprest/details/basic_types.h>
#include "CppRestOpenAPIClient/model/ScannedShip_engine.h"
#include <vector>
#include "CppRestOpenAPIClient/model/ScannedShip_mounts_inner.h"
#include "CppRestOpenAPIClient/model/ShipNav.h"

namespace models {

class ShipRegistration;
class ShipNav;
class ScannedShip_frame;
class ScannedShip_reactor;
class ScannedShip_engine;
class ScannedShip_mounts_inner;

/// <summary>
/// The ship that was scanned. Details include information about the ship that could be detected by the scanner.
/// </summary>
class  ScannedShip
    : public ModelBase
{
public:
    ScannedShip();
    virtual ~ScannedShip();

    /////////////////////////////////////////////
    /// ModelBase overrides

    void validate() override;

    web::json::value toJson() const override;
    bool fromJson(const web::json::value& json) override;

    void toMultipart(std::shared_ptr<MultipartFormData> multipart, const utility::string_t& namePrefix) const override;
    bool fromMultiPart(std::shared_ptr<MultipartFormData> multipart, const utility::string_t& namePrefix) override;

    /////////////////////////////////////////////
    /// ScannedShip members

    /// <summary>
    /// The globally unique identifier of the ship.
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
    std::shared_ptr<ScannedShip_frame> getFrame() const;
    bool frameIsSet() const;
    void unsetFrame();

    void setFrame(const std::shared_ptr<ScannedShip_frame>& value);

    /// <summary>
    /// 
    /// </summary>
    std::shared_ptr<ScannedShip_reactor> getReactor() const;
    bool reactorIsSet() const;
    void unsetReactor();

    void setReactor(const std::shared_ptr<ScannedShip_reactor>& value);

    /// <summary>
    /// 
    /// </summary>
    std::shared_ptr<ScannedShip_engine> getEngine() const;
    bool engineIsSet() const;
    void unsetEngine();

    void setEngine(const std::shared_ptr<ScannedShip_engine>& value);

    /// <summary>
    /// List of mounts installed in the ship.
    /// </summary>
    std::vector<std::shared_ptr<ScannedShip_mounts_inner>>& getMounts();
    bool mountsIsSet() const;
    void unsetMounts();

    void setMounts(const std::vector<std::shared_ptr<ScannedShip_mounts_inner>>& value);


protected:
    utility::string_t m_Symbol;
    bool m_SymbolIsSet;
    std::shared_ptr<ShipRegistration> m_Registration;
    bool m_RegistrationIsSet;
    std::shared_ptr<ShipNav> m_Nav;
    bool m_NavIsSet;
    std::shared_ptr<ScannedShip_frame> m_Frame;
    bool m_FrameIsSet;
    std::shared_ptr<ScannedShip_reactor> m_Reactor;
    bool m_ReactorIsSet;
    std::shared_ptr<ScannedShip_engine> m_Engine;
    bool m_EngineIsSet;
    std::vector<std::shared_ptr<ScannedShip_mounts_inner>> m_Mounts;
    bool m_MountsIsSet;
};


}

#endif /* MODELS_ScannedShip_H_ */