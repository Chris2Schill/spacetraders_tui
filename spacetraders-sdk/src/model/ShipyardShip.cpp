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



#include "CppRestOpenAPIClient/model/ShipyardShip.h"

namespace models {



ShipyardShip::ShipyardShip()
{
    m_TypeIsSet = false;
    m_Name = utility::conversions::to_string_t("");
    m_NameIsSet = false;
    m_Description = utility::conversions::to_string_t("");
    m_DescriptionIsSet = false;
    m_SupplyIsSet = false;
    m_ActivityIsSet = false;
    m_PurchasePrice = 0;
    m_PurchasePriceIsSet = false;
    m_FrameIsSet = false;
    m_ReactorIsSet = false;
    m_EngineIsSet = false;
    m_ModulesIsSet = false;
    m_MountsIsSet = false;
    m_CrewIsSet = false;
}

ShipyardShip::~ShipyardShip()
{
}

void ShipyardShip::validate()
{
    // TODO: implement validation
}

web::json::value ShipyardShip::toJson() const
{

    web::json::value val = web::json::value::object();
    
    if(m_TypeIsSet)
    {
        val[utility::conversions::to_string_t(U("type"))] = ModelBase::toJson(m_Type);
    }
    if(m_NameIsSet)
    {
        val[utility::conversions::to_string_t(U("name"))] = ModelBase::toJson(m_Name);
    }
    if(m_DescriptionIsSet)
    {
        val[utility::conversions::to_string_t(U("description"))] = ModelBase::toJson(m_Description);
    }
    if(m_SupplyIsSet)
    {
        val[utility::conversions::to_string_t(U("supply"))] = ModelBase::toJson(m_Supply);
    }
    if(m_ActivityIsSet)
    {
        val[utility::conversions::to_string_t(U("activity"))] = ModelBase::toJson(m_Activity);
    }
    if(m_PurchasePriceIsSet)
    {
        val[utility::conversions::to_string_t(U("purchasePrice"))] = ModelBase::toJson(m_PurchasePrice);
    }
    if(m_FrameIsSet)
    {
        val[utility::conversions::to_string_t(U("frame"))] = ModelBase::toJson(m_Frame);
    }
    if(m_ReactorIsSet)
    {
        val[utility::conversions::to_string_t(U("reactor"))] = ModelBase::toJson(m_Reactor);
    }
    if(m_EngineIsSet)
    {
        val[utility::conversions::to_string_t(U("engine"))] = ModelBase::toJson(m_Engine);
    }
    if(m_ModulesIsSet)
    {
        val[utility::conversions::to_string_t(U("modules"))] = ModelBase::toJson(m_Modules);
    }
    if(m_MountsIsSet)
    {
        val[utility::conversions::to_string_t(U("mounts"))] = ModelBase::toJson(m_Mounts);
    }
    if(m_CrewIsSet)
    {
        val[utility::conversions::to_string_t(U("crew"))] = ModelBase::toJson(m_Crew);
    }

    return val;
}

bool ShipyardShip::fromJson(const web::json::value& val)
{
    bool ok = true;
    
    if(val.has_field(utility::conversions::to_string_t(U("type"))))
    {
        const web::json::value& fieldValue = val.at(utility::conversions::to_string_t(U("type")));
        if(!fieldValue.is_null())
        {
            std::shared_ptr<ShipType> refVal_setType;
            ok &= ModelBase::fromJson(fieldValue, refVal_setType);
            setType(refVal_setType);
        }
    }
    if(val.has_field(utility::conversions::to_string_t(U("name"))))
    {
        const web::json::value& fieldValue = val.at(utility::conversions::to_string_t(U("name")));
        if(!fieldValue.is_null())
        {
            utility::string_t refVal_setName;
            ok &= ModelBase::fromJson(fieldValue, refVal_setName);
            setName(refVal_setName);
        }
    }
    if(val.has_field(utility::conversions::to_string_t(U("description"))))
    {
        const web::json::value& fieldValue = val.at(utility::conversions::to_string_t(U("description")));
        if(!fieldValue.is_null())
        {
            utility::string_t refVal_setDescription;
            ok &= ModelBase::fromJson(fieldValue, refVal_setDescription);
            setDescription(refVal_setDescription);
        }
    }
    if(val.has_field(utility::conversions::to_string_t(U("supply"))))
    {
        const web::json::value& fieldValue = val.at(utility::conversions::to_string_t(U("supply")));
        if(!fieldValue.is_null())
        {
            std::shared_ptr<SupplyLevel> refVal_setSupply;
            ok &= ModelBase::fromJson(fieldValue, refVal_setSupply);
            setSupply(refVal_setSupply);
        }
    }
    if(val.has_field(utility::conversions::to_string_t(U("activity"))))
    {
        const web::json::value& fieldValue = val.at(utility::conversions::to_string_t(U("activity")));
        if(!fieldValue.is_null())
        {
            std::shared_ptr<ActivityLevel> refVal_setActivity;
            ok &= ModelBase::fromJson(fieldValue, refVal_setActivity);
            setActivity(refVal_setActivity);
        }
    }
    if(val.has_field(utility::conversions::to_string_t(U("purchasePrice"))))
    {
        const web::json::value& fieldValue = val.at(utility::conversions::to_string_t(U("purchasePrice")));
        if(!fieldValue.is_null())
        {
            int32_t refVal_setPurchasePrice;
            ok &= ModelBase::fromJson(fieldValue, refVal_setPurchasePrice);
            setPurchasePrice(refVal_setPurchasePrice);
        }
    }
    if(val.has_field(utility::conversions::to_string_t(U("frame"))))
    {
        const web::json::value& fieldValue = val.at(utility::conversions::to_string_t(U("frame")));
        if(!fieldValue.is_null())
        {
            std::shared_ptr<ShipFrame> refVal_setFrame;
            ok &= ModelBase::fromJson(fieldValue, refVal_setFrame);
            setFrame(refVal_setFrame);
        }
    }
    if(val.has_field(utility::conversions::to_string_t(U("reactor"))))
    {
        const web::json::value& fieldValue = val.at(utility::conversions::to_string_t(U("reactor")));
        if(!fieldValue.is_null())
        {
            std::shared_ptr<ShipReactor> refVal_setReactor;
            ok &= ModelBase::fromJson(fieldValue, refVal_setReactor);
            setReactor(refVal_setReactor);
        }
    }
    if(val.has_field(utility::conversions::to_string_t(U("engine"))))
    {
        const web::json::value& fieldValue = val.at(utility::conversions::to_string_t(U("engine")));
        if(!fieldValue.is_null())
        {
            std::shared_ptr<ShipEngine> refVal_setEngine;
            ok &= ModelBase::fromJson(fieldValue, refVal_setEngine);
            setEngine(refVal_setEngine);
        }
    }
    if(val.has_field(utility::conversions::to_string_t(U("modules"))))
    {
        const web::json::value& fieldValue = val.at(utility::conversions::to_string_t(U("modules")));
        if(!fieldValue.is_null())
        {
            std::vector<std::shared_ptr<ShipModule>> refVal_setModules;
            ok &= ModelBase::fromJson(fieldValue, refVal_setModules);
            setModules(refVal_setModules);
        }
    }
    if(val.has_field(utility::conversions::to_string_t(U("mounts"))))
    {
        const web::json::value& fieldValue = val.at(utility::conversions::to_string_t(U("mounts")));
        if(!fieldValue.is_null())
        {
            std::vector<std::shared_ptr<ShipMount>> refVal_setMounts;
            ok &= ModelBase::fromJson(fieldValue, refVal_setMounts);
            setMounts(refVal_setMounts);
        }
    }
    if(val.has_field(utility::conversions::to_string_t(U("crew"))))
    {
        const web::json::value& fieldValue = val.at(utility::conversions::to_string_t(U("crew")));
        if(!fieldValue.is_null())
        {
            std::shared_ptr<ShipyardShip_crew> refVal_setCrew;
            ok &= ModelBase::fromJson(fieldValue, refVal_setCrew);
            setCrew(refVal_setCrew);
        }
    }
    return ok;
}

void ShipyardShip::toMultipart(std::shared_ptr<MultipartFormData> multipart, const utility::string_t& prefix) const
{
    utility::string_t namePrefix = prefix;
    if(namePrefix.size() > 0 && namePrefix.substr(namePrefix.size() - 1) != utility::conversions::to_string_t(U(".")))
    {
        namePrefix += utility::conversions::to_string_t(U("."));
    }
    if(m_TypeIsSet)
    {
        multipart->add(ModelBase::toHttpContent(namePrefix + utility::conversions::to_string_t(U("type")), m_Type));
    }
    if(m_NameIsSet)
    {
        multipart->add(ModelBase::toHttpContent(namePrefix + utility::conversions::to_string_t(U("name")), m_Name));
    }
    if(m_DescriptionIsSet)
    {
        multipart->add(ModelBase::toHttpContent(namePrefix + utility::conversions::to_string_t(U("description")), m_Description));
    }
    if(m_SupplyIsSet)
    {
        multipart->add(ModelBase::toHttpContent(namePrefix + utility::conversions::to_string_t(U("supply")), m_Supply));
    }
    if(m_ActivityIsSet)
    {
        multipart->add(ModelBase::toHttpContent(namePrefix + utility::conversions::to_string_t(U("activity")), m_Activity));
    }
    if(m_PurchasePriceIsSet)
    {
        multipart->add(ModelBase::toHttpContent(namePrefix + utility::conversions::to_string_t(U("purchasePrice")), m_PurchasePrice));
    }
    if(m_FrameIsSet)
    {
        multipart->add(ModelBase::toHttpContent(namePrefix + utility::conversions::to_string_t(U("frame")), m_Frame));
    }
    if(m_ReactorIsSet)
    {
        multipart->add(ModelBase::toHttpContent(namePrefix + utility::conversions::to_string_t(U("reactor")), m_Reactor));
    }
    if(m_EngineIsSet)
    {
        multipart->add(ModelBase::toHttpContent(namePrefix + utility::conversions::to_string_t(U("engine")), m_Engine));
    }
    if(m_ModulesIsSet)
    {
        multipart->add(ModelBase::toHttpContent(namePrefix + utility::conversions::to_string_t(U("modules")), m_Modules));
    }
    if(m_MountsIsSet)
    {
        multipart->add(ModelBase::toHttpContent(namePrefix + utility::conversions::to_string_t(U("mounts")), m_Mounts));
    }
    if(m_CrewIsSet)
    {
        multipart->add(ModelBase::toHttpContent(namePrefix + utility::conversions::to_string_t(U("crew")), m_Crew));
    }
}

bool ShipyardShip::fromMultiPart(std::shared_ptr<MultipartFormData> multipart, const utility::string_t& prefix)
{
    bool ok = true;
    utility::string_t namePrefix = prefix;
    if(namePrefix.size() > 0 && namePrefix.substr(namePrefix.size() - 1) != utility::conversions::to_string_t(U(".")))
    {
        namePrefix += utility::conversions::to_string_t(U("."));
    }

    if(multipart->hasContent(utility::conversions::to_string_t(U("type"))))
    {
        std::shared_ptr<ShipType> refVal_setType;
        ok &= ModelBase::fromHttpContent(multipart->getContent(utility::conversions::to_string_t(U("type"))), refVal_setType );
        setType(refVal_setType);
    }
    if(multipart->hasContent(utility::conversions::to_string_t(U("name"))))
    {
        utility::string_t refVal_setName;
        ok &= ModelBase::fromHttpContent(multipart->getContent(utility::conversions::to_string_t(U("name"))), refVal_setName );
        setName(refVal_setName);
    }
    if(multipart->hasContent(utility::conversions::to_string_t(U("description"))))
    {
        utility::string_t refVal_setDescription;
        ok &= ModelBase::fromHttpContent(multipart->getContent(utility::conversions::to_string_t(U("description"))), refVal_setDescription );
        setDescription(refVal_setDescription);
    }
    if(multipart->hasContent(utility::conversions::to_string_t(U("supply"))))
    {
        std::shared_ptr<SupplyLevel> refVal_setSupply;
        ok &= ModelBase::fromHttpContent(multipart->getContent(utility::conversions::to_string_t(U("supply"))), refVal_setSupply );
        setSupply(refVal_setSupply);
    }
    if(multipart->hasContent(utility::conversions::to_string_t(U("activity"))))
    {
        std::shared_ptr<ActivityLevel> refVal_setActivity;
        ok &= ModelBase::fromHttpContent(multipart->getContent(utility::conversions::to_string_t(U("activity"))), refVal_setActivity );
        setActivity(refVal_setActivity);
    }
    if(multipart->hasContent(utility::conversions::to_string_t(U("purchasePrice"))))
    {
        int32_t refVal_setPurchasePrice;
        ok &= ModelBase::fromHttpContent(multipart->getContent(utility::conversions::to_string_t(U("purchasePrice"))), refVal_setPurchasePrice );
        setPurchasePrice(refVal_setPurchasePrice);
    }
    if(multipart->hasContent(utility::conversions::to_string_t(U("frame"))))
    {
        std::shared_ptr<ShipFrame> refVal_setFrame;
        ok &= ModelBase::fromHttpContent(multipart->getContent(utility::conversions::to_string_t(U("frame"))), refVal_setFrame );
        setFrame(refVal_setFrame);
    }
    if(multipart->hasContent(utility::conversions::to_string_t(U("reactor"))))
    {
        std::shared_ptr<ShipReactor> refVal_setReactor;
        ok &= ModelBase::fromHttpContent(multipart->getContent(utility::conversions::to_string_t(U("reactor"))), refVal_setReactor );
        setReactor(refVal_setReactor);
    }
    if(multipart->hasContent(utility::conversions::to_string_t(U("engine"))))
    {
        std::shared_ptr<ShipEngine> refVal_setEngine;
        ok &= ModelBase::fromHttpContent(multipart->getContent(utility::conversions::to_string_t(U("engine"))), refVal_setEngine );
        setEngine(refVal_setEngine);
    }
    if(multipart->hasContent(utility::conversions::to_string_t(U("modules"))))
    {
        std::vector<std::shared_ptr<ShipModule>> refVal_setModules;
        ok &= ModelBase::fromHttpContent(multipart->getContent(utility::conversions::to_string_t(U("modules"))), refVal_setModules );
        setModules(refVal_setModules);
    }
    if(multipart->hasContent(utility::conversions::to_string_t(U("mounts"))))
    {
        std::vector<std::shared_ptr<ShipMount>> refVal_setMounts;
        ok &= ModelBase::fromHttpContent(multipart->getContent(utility::conversions::to_string_t(U("mounts"))), refVal_setMounts );
        setMounts(refVal_setMounts);
    }
    if(multipart->hasContent(utility::conversions::to_string_t(U("crew"))))
    {
        std::shared_ptr<ShipyardShip_crew> refVal_setCrew;
        ok &= ModelBase::fromHttpContent(multipart->getContent(utility::conversions::to_string_t(U("crew"))), refVal_setCrew );
        setCrew(refVal_setCrew);
    }
    return ok;
}

std::shared_ptr<ShipType> ShipyardShip::getType() const
{
    return m_Type;
}

void ShipyardShip::setType(const std::shared_ptr<ShipType>& value)
{
    m_Type = value;
    m_TypeIsSet = true;
}

bool ShipyardShip::typeIsSet() const
{
    return m_TypeIsSet;
}

void ShipyardShip::unsetType()
{
    m_TypeIsSet = false;
}
utility::string_t ShipyardShip::getName() const
{
    return m_Name;
}

void ShipyardShip::setName(const utility::string_t& value)
{
    m_Name = value;
    m_NameIsSet = true;
}

bool ShipyardShip::nameIsSet() const
{
    return m_NameIsSet;
}

void ShipyardShip::unsetName()
{
    m_NameIsSet = false;
}
utility::string_t ShipyardShip::getDescription() const
{
    return m_Description;
}

void ShipyardShip::setDescription(const utility::string_t& value)
{
    m_Description = value;
    m_DescriptionIsSet = true;
}

bool ShipyardShip::descriptionIsSet() const
{
    return m_DescriptionIsSet;
}

void ShipyardShip::unsetDescription()
{
    m_DescriptionIsSet = false;
}
std::shared_ptr<SupplyLevel> ShipyardShip::getSupply() const
{
    return m_Supply;
}

void ShipyardShip::setSupply(const std::shared_ptr<SupplyLevel>& value)
{
    m_Supply = value;
    m_SupplyIsSet = true;
}

bool ShipyardShip::supplyIsSet() const
{
    return m_SupplyIsSet;
}

void ShipyardShip::unsetSupply()
{
    m_SupplyIsSet = false;
}
std::shared_ptr<ActivityLevel> ShipyardShip::getActivity() const
{
    return m_Activity;
}

void ShipyardShip::setActivity(const std::shared_ptr<ActivityLevel>& value)
{
    m_Activity = value;
    m_ActivityIsSet = true;
}

bool ShipyardShip::activityIsSet() const
{
    return m_ActivityIsSet;
}

void ShipyardShip::unsetActivity()
{
    m_ActivityIsSet = false;
}
int32_t ShipyardShip::getPurchasePrice() const
{
    return m_PurchasePrice;
}

void ShipyardShip::setPurchasePrice(int32_t value)
{
    m_PurchasePrice = value;
    m_PurchasePriceIsSet = true;
}

bool ShipyardShip::purchasePriceIsSet() const
{
    return m_PurchasePriceIsSet;
}

void ShipyardShip::unsetPurchasePrice()
{
    m_PurchasePriceIsSet = false;
}
std::shared_ptr<ShipFrame> ShipyardShip::getFrame() const
{
    return m_Frame;
}

void ShipyardShip::setFrame(const std::shared_ptr<ShipFrame>& value)
{
    m_Frame = value;
    m_FrameIsSet = true;
}

bool ShipyardShip::frameIsSet() const
{
    return m_FrameIsSet;
}

void ShipyardShip::unsetFrame()
{
    m_FrameIsSet = false;
}
std::shared_ptr<ShipReactor> ShipyardShip::getReactor() const
{
    return m_Reactor;
}

void ShipyardShip::setReactor(const std::shared_ptr<ShipReactor>& value)
{
    m_Reactor = value;
    m_ReactorIsSet = true;
}

bool ShipyardShip::reactorIsSet() const
{
    return m_ReactorIsSet;
}

void ShipyardShip::unsetReactor()
{
    m_ReactorIsSet = false;
}
std::shared_ptr<ShipEngine> ShipyardShip::getEngine() const
{
    return m_Engine;
}

void ShipyardShip::setEngine(const std::shared_ptr<ShipEngine>& value)
{
    m_Engine = value;
    m_EngineIsSet = true;
}

bool ShipyardShip::engineIsSet() const
{
    return m_EngineIsSet;
}

void ShipyardShip::unsetEngine()
{
    m_EngineIsSet = false;
}
std::vector<std::shared_ptr<ShipModule>>& ShipyardShip::getModules()
{
    return m_Modules;
}

void ShipyardShip::setModules(const std::vector<std::shared_ptr<ShipModule>>& value)
{
    m_Modules = value;
    m_ModulesIsSet = true;
}

bool ShipyardShip::modulesIsSet() const
{
    return m_ModulesIsSet;
}

void ShipyardShip::unsetModules()
{
    m_ModulesIsSet = false;
}
std::vector<std::shared_ptr<ShipMount>>& ShipyardShip::getMounts()
{
    return m_Mounts;
}

void ShipyardShip::setMounts(const std::vector<std::shared_ptr<ShipMount>>& value)
{
    m_Mounts = value;
    m_MountsIsSet = true;
}

bool ShipyardShip::mountsIsSet() const
{
    return m_MountsIsSet;
}

void ShipyardShip::unsetMounts()
{
    m_MountsIsSet = false;
}
std::shared_ptr<ShipyardShip_crew> ShipyardShip::getCrew() const
{
    return m_Crew;
}

void ShipyardShip::setCrew(const std::shared_ptr<ShipyardShip_crew>& value)
{
    m_Crew = value;
    m_CrewIsSet = true;
}

bool ShipyardShip::crewIsSet() const
{
    return m_CrewIsSet;
}

void ShipyardShip::unsetCrew()
{
    m_CrewIsSet = false;
}
}


