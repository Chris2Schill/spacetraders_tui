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



#include "CppRestOpenAPIClient/model/Remove_Mount_201_Response_data.h"

namespace models {



Remove_Mount_201_Response_data::Remove_Mount_201_Response_data()
{
    m_AgentIsSet = false;
    m_MountsIsSet = false;
    m_CargoIsSet = false;
    m_TransactionIsSet = false;
}

Remove_Mount_201_Response_data::~Remove_Mount_201_Response_data()
{
}

void Remove_Mount_201_Response_data::validate()
{
    // TODO: implement validation
}

web::json::value Remove_Mount_201_Response_data::toJson() const
{

    web::json::value val = web::json::value::object();
    
    if(m_AgentIsSet)
    {
        val[utility::conversions::to_string_t(U("agent"))] = ModelBase::toJson(m_Agent);
    }
    if(m_MountsIsSet)
    {
        val[utility::conversions::to_string_t(U("mounts"))] = ModelBase::toJson(m_Mounts);
    }
    if(m_CargoIsSet)
    {
        val[utility::conversions::to_string_t(U("cargo"))] = ModelBase::toJson(m_Cargo);
    }
    if(m_TransactionIsSet)
    {
        val[utility::conversions::to_string_t(U("transaction"))] = ModelBase::toJson(m_Transaction);
    }

    return val;
}

bool Remove_Mount_201_Response_data::fromJson(const web::json::value& val)
{
    bool ok = true;
    
    if(val.has_field(utility::conversions::to_string_t(U("agent"))))
    {
        const web::json::value& fieldValue = val.at(utility::conversions::to_string_t(U("agent")));
        if(!fieldValue.is_null())
        {
            std::shared_ptr<Agent> refVal_setAgent;
            ok &= ModelBase::fromJson(fieldValue, refVal_setAgent);
            setAgent(refVal_setAgent);
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
    if(val.has_field(utility::conversions::to_string_t(U("transaction"))))
    {
        const web::json::value& fieldValue = val.at(utility::conversions::to_string_t(U("transaction")));
        if(!fieldValue.is_null())
        {
            std::shared_ptr<ShipModificationTransaction> refVal_setTransaction;
            ok &= ModelBase::fromJson(fieldValue, refVal_setTransaction);
            setTransaction(refVal_setTransaction);
        }
    }
    return ok;
}

void Remove_Mount_201_Response_data::toMultipart(std::shared_ptr<MultipartFormData> multipart, const utility::string_t& prefix) const
{
    utility::string_t namePrefix = prefix;
    if(namePrefix.size() > 0 && namePrefix.substr(namePrefix.size() - 1) != utility::conversions::to_string_t(U(".")))
    {
        namePrefix += utility::conversions::to_string_t(U("."));
    }
    if(m_AgentIsSet)
    {
        multipart->add(ModelBase::toHttpContent(namePrefix + utility::conversions::to_string_t(U("agent")), m_Agent));
    }
    if(m_MountsIsSet)
    {
        multipart->add(ModelBase::toHttpContent(namePrefix + utility::conversions::to_string_t(U("mounts")), m_Mounts));
    }
    if(m_CargoIsSet)
    {
        multipart->add(ModelBase::toHttpContent(namePrefix + utility::conversions::to_string_t(U("cargo")), m_Cargo));
    }
    if(m_TransactionIsSet)
    {
        multipart->add(ModelBase::toHttpContent(namePrefix + utility::conversions::to_string_t(U("transaction")), m_Transaction));
    }
}

bool Remove_Mount_201_Response_data::fromMultiPart(std::shared_ptr<MultipartFormData> multipart, const utility::string_t& prefix)
{
    bool ok = true;
    utility::string_t namePrefix = prefix;
    if(namePrefix.size() > 0 && namePrefix.substr(namePrefix.size() - 1) != utility::conversions::to_string_t(U(".")))
    {
        namePrefix += utility::conversions::to_string_t(U("."));
    }

    if(multipart->hasContent(utility::conversions::to_string_t(U("agent"))))
    {
        std::shared_ptr<Agent> refVal_setAgent;
        ok &= ModelBase::fromHttpContent(multipart->getContent(utility::conversions::to_string_t(U("agent"))), refVal_setAgent );
        setAgent(refVal_setAgent);
    }
    if(multipart->hasContent(utility::conversions::to_string_t(U("mounts"))))
    {
        std::vector<std::shared_ptr<ShipMount>> refVal_setMounts;
        ok &= ModelBase::fromHttpContent(multipart->getContent(utility::conversions::to_string_t(U("mounts"))), refVal_setMounts );
        setMounts(refVal_setMounts);
    }
    if(multipart->hasContent(utility::conversions::to_string_t(U("cargo"))))
    {
        std::shared_ptr<ShipCargo> refVal_setCargo;
        ok &= ModelBase::fromHttpContent(multipart->getContent(utility::conversions::to_string_t(U("cargo"))), refVal_setCargo );
        setCargo(refVal_setCargo);
    }
    if(multipart->hasContent(utility::conversions::to_string_t(U("transaction"))))
    {
        std::shared_ptr<ShipModificationTransaction> refVal_setTransaction;
        ok &= ModelBase::fromHttpContent(multipart->getContent(utility::conversions::to_string_t(U("transaction"))), refVal_setTransaction );
        setTransaction(refVal_setTransaction);
    }
    return ok;
}

std::shared_ptr<Agent> Remove_Mount_201_Response_data::getAgent() const
{
    return m_Agent;
}

void Remove_Mount_201_Response_data::setAgent(const std::shared_ptr<Agent>& value)
{
    m_Agent = value;
    m_AgentIsSet = true;
}

bool Remove_Mount_201_Response_data::agentIsSet() const
{
    return m_AgentIsSet;
}

void Remove_Mount_201_Response_data::unsetAgent()
{
    m_AgentIsSet = false;
}
std::vector<std::shared_ptr<ShipMount>>& Remove_Mount_201_Response_data::getMounts()
{
    return m_Mounts;
}

void Remove_Mount_201_Response_data::setMounts(const std::vector<std::shared_ptr<ShipMount>>& value)
{
    m_Mounts = value;
    m_MountsIsSet = true;
}

bool Remove_Mount_201_Response_data::mountsIsSet() const
{
    return m_MountsIsSet;
}

void Remove_Mount_201_Response_data::unsetMounts()
{
    m_MountsIsSet = false;
}
std::shared_ptr<ShipCargo> Remove_Mount_201_Response_data::getCargo() const
{
    return m_Cargo;
}

void Remove_Mount_201_Response_data::setCargo(const std::shared_ptr<ShipCargo>& value)
{
    m_Cargo = value;
    m_CargoIsSet = true;
}

bool Remove_Mount_201_Response_data::cargoIsSet() const
{
    return m_CargoIsSet;
}

void Remove_Mount_201_Response_data::unsetCargo()
{
    m_CargoIsSet = false;
}
std::shared_ptr<ShipModificationTransaction> Remove_Mount_201_Response_data::getTransaction() const
{
    return m_Transaction;
}

void Remove_Mount_201_Response_data::setTransaction(const std::shared_ptr<ShipModificationTransaction>& value)
{
    m_Transaction = value;
    m_TransactionIsSet = true;
}

bool Remove_Mount_201_Response_data::transactionIsSet() const
{
    return m_TransactionIsSet;
}

void Remove_Mount_201_Response_data::unsetTransaction()
{
    m_TransactionIsSet = false;
}
}

