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



#include "CppRestOpenAPIClient/model/Negotiate_Contract_200_Response_data.h"

namespace models {



Negotiate_Contract_200_Response_data::Negotiate_Contract_200_Response_data()
{
    m_ContractIsSet = false;
}

Negotiate_Contract_200_Response_data::~Negotiate_Contract_200_Response_data()
{
}

void Negotiate_Contract_200_Response_data::validate()
{
    // TODO: implement validation
}

web::json::value Negotiate_Contract_200_Response_data::toJson() const
{

    web::json::value val = web::json::value::object();
    
    if(m_ContractIsSet)
    {
        val[utility::conversions::to_string_t(U("contract"))] = ModelBase::toJson(m_Contract);
    }

    return val;
}

bool Negotiate_Contract_200_Response_data::fromJson(const web::json::value& val)
{
    bool ok = true;
    
    if(val.has_field(utility::conversions::to_string_t(U("contract"))))
    {
        const web::json::value& fieldValue = val.at(utility::conversions::to_string_t(U("contract")));
        if(!fieldValue.is_null())
        {
            std::shared_ptr<Contract> refVal_setContract;
            ok &= ModelBase::fromJson(fieldValue, refVal_setContract);
            setContract(refVal_setContract);
        }
    }
    return ok;
}

void Negotiate_Contract_200_Response_data::toMultipart(std::shared_ptr<MultipartFormData> multipart, const utility::string_t& prefix) const
{
    utility::string_t namePrefix = prefix;
    if(namePrefix.size() > 0 && namePrefix.substr(namePrefix.size() - 1) != utility::conversions::to_string_t(U(".")))
    {
        namePrefix += utility::conversions::to_string_t(U("."));
    }
    if(m_ContractIsSet)
    {
        multipart->add(ModelBase::toHttpContent(namePrefix + utility::conversions::to_string_t(U("contract")), m_Contract));
    }
}

bool Negotiate_Contract_200_Response_data::fromMultiPart(std::shared_ptr<MultipartFormData> multipart, const utility::string_t& prefix)
{
    bool ok = true;
    utility::string_t namePrefix = prefix;
    if(namePrefix.size() > 0 && namePrefix.substr(namePrefix.size() - 1) != utility::conversions::to_string_t(U(".")))
    {
        namePrefix += utility::conversions::to_string_t(U("."));
    }

    if(multipart->hasContent(utility::conversions::to_string_t(U("contract"))))
    {
        std::shared_ptr<Contract> refVal_setContract;
        ok &= ModelBase::fromHttpContent(multipart->getContent(utility::conversions::to_string_t(U("contract"))), refVal_setContract );
        setContract(refVal_setContract);
    }
    return ok;
}

std::shared_ptr<Contract> Negotiate_Contract_200_Response_data::getContract() const
{
    return m_Contract;
}

void Negotiate_Contract_200_Response_data::setContract(const std::shared_ptr<Contract>& value)
{
    m_Contract = value;
    m_ContractIsSet = true;
}

bool Negotiate_Contract_200_Response_data::contractIsSet() const
{
    return m_ContractIsSet;
}

void Negotiate_Contract_200_Response_data::unsetContract()
{
    m_ContractIsSet = false;
}
}


