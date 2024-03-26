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



#include "CppRestOpenAPIClient/model/Supply_construction_201_response_data.h"

namespace models {



Supply_construction_201_response_data::Supply_construction_201_response_data()
{
    m_ConstructionIsSet = false;
    m_CargoIsSet = false;
}

Supply_construction_201_response_data::~Supply_construction_201_response_data()
{
}

void Supply_construction_201_response_data::validate()
{
    // TODO: implement validation
}

web::json::value Supply_construction_201_response_data::toJson() const
{

    web::json::value val = web::json::value::object();
    
    if(m_ConstructionIsSet)
    {
        val[utility::conversions::to_string_t(U("construction"))] = ModelBase::toJson(m_Construction);
    }
    if(m_CargoIsSet)
    {
        val[utility::conversions::to_string_t(U("cargo"))] = ModelBase::toJson(m_Cargo);
    }

    return val;
}

bool Supply_construction_201_response_data::fromJson(const web::json::value& val)
{
    bool ok = true;
    
    if(val.has_field(utility::conversions::to_string_t(U("construction"))))
    {
        const web::json::value& fieldValue = val.at(utility::conversions::to_string_t(U("construction")));
        if(!fieldValue.is_null())
        {
            std::shared_ptr<Construction> refVal_setConstruction;
            ok &= ModelBase::fromJson(fieldValue, refVal_setConstruction);
            setConstruction(refVal_setConstruction);
        }
    }
    if(val.has_field(utility::conversions::to_string_t(U("cargo"))))
    {
        const web::json::value& fieldValue = val.at(utility::conversions::to_string_t(U("cargo")));
        if(!fieldValue.is_null())
        {
            std::shared_ptr<ShipCargo> refVal_setCargo;
            ok &= ModelBase::fromJson(fieldValue, refVal_setCargo);
            setCargo(refVal_setCargo);
        }
    }
    return ok;
}

void Supply_construction_201_response_data::toMultipart(std::shared_ptr<MultipartFormData> multipart, const utility::string_t& prefix) const
{
    utility::string_t namePrefix = prefix;
    if(namePrefix.size() > 0 && namePrefix.substr(namePrefix.size() - 1) != utility::conversions::to_string_t(U(".")))
    {
        namePrefix += utility::conversions::to_string_t(U("."));
    }
    if(m_ConstructionIsSet)
    {
        multipart->add(ModelBase::toHttpContent(namePrefix + utility::conversions::to_string_t(U("construction")), m_Construction));
    }
    if(m_CargoIsSet)
    {
        multipart->add(ModelBase::toHttpContent(namePrefix + utility::conversions::to_string_t(U("cargo")), m_Cargo));
    }
}

bool Supply_construction_201_response_data::fromMultiPart(std::shared_ptr<MultipartFormData> multipart, const utility::string_t& prefix)
{
    bool ok = true;
    utility::string_t namePrefix = prefix;
    if(namePrefix.size() > 0 && namePrefix.substr(namePrefix.size() - 1) != utility::conversions::to_string_t(U(".")))
    {
        namePrefix += utility::conversions::to_string_t(U("."));
    }

    if(multipart->hasContent(utility::conversions::to_string_t(U("construction"))))
    {
        std::shared_ptr<Construction> refVal_setConstruction;
        ok &= ModelBase::fromHttpContent(multipart->getContent(utility::conversions::to_string_t(U("construction"))), refVal_setConstruction );
        setConstruction(refVal_setConstruction);
    }
    if(multipart->hasContent(utility::conversions::to_string_t(U("cargo"))))
    {
        std::shared_ptr<ShipCargo> refVal_setCargo;
        ok &= ModelBase::fromHttpContent(multipart->getContent(utility::conversions::to_string_t(U("cargo"))), refVal_setCargo );
        setCargo(refVal_setCargo);
    }
    return ok;
}

std::shared_ptr<Construction> Supply_construction_201_response_data::getConstruction() const
{
    return m_Construction;
}

void Supply_construction_201_response_data::setConstruction(const std::shared_ptr<Construction>& value)
{
    m_Construction = value;
    m_ConstructionIsSet = true;
}

bool Supply_construction_201_response_data::constructionIsSet() const
{
    return m_ConstructionIsSet;
}

void Supply_construction_201_response_data::unsetConstruction()
{
    m_ConstructionIsSet = false;
}
std::shared_ptr<ShipCargo> Supply_construction_201_response_data::getCargo() const
{
    return m_Cargo;
}

void Supply_construction_201_response_data::setCargo(const std::shared_ptr<ShipCargo>& value)
{
    m_Cargo = value;
    m_CargoIsSet = true;
}

bool Supply_construction_201_response_data::cargoIsSet() const
{
    return m_CargoIsSet;
}

void Supply_construction_201_response_data::unsetCargo()
{
    m_CargoIsSet = false;
}
}

