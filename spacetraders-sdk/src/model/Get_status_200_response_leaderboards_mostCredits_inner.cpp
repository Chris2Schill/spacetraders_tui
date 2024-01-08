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



#include "CppRestOpenAPIClient/model/Get_status_200_response_leaderboards_mostCredits_inner.h"

namespace models {



Get_status_200_response_leaderboards_mostCredits_inner::Get_status_200_response_leaderboards_mostCredits_inner()
{
    m_AgentSymbol = utility::conversions::to_string_t("");
    m_AgentSymbolIsSet = false;
    m_Credits = 0L;
    m_CreditsIsSet = false;
}

Get_status_200_response_leaderboards_mostCredits_inner::~Get_status_200_response_leaderboards_mostCredits_inner()
{
}

void Get_status_200_response_leaderboards_mostCredits_inner::validate()
{
    // TODO: implement validation
}

web::json::value Get_status_200_response_leaderboards_mostCredits_inner::toJson() const
{

    web::json::value val = web::json::value::object();
    
    if(m_AgentSymbolIsSet)
    {
        val[utility::conversions::to_string_t(U("agentSymbol"))] = ModelBase::toJson(m_AgentSymbol);
    }
    if(m_CreditsIsSet)
    {
        val[utility::conversions::to_string_t(U("credits"))] = ModelBase::toJson(m_Credits);
    }

    return val;
}

bool Get_status_200_response_leaderboards_mostCredits_inner::fromJson(const web::json::value& val)
{
    bool ok = true;
    
    if(val.has_field(utility::conversions::to_string_t(U("agentSymbol"))))
    {
        const web::json::value& fieldValue = val.at(utility::conversions::to_string_t(U("agentSymbol")));
        if(!fieldValue.is_null())
        {
            utility::string_t refVal_setAgentSymbol;
            ok &= ModelBase::fromJson(fieldValue, refVal_setAgentSymbol);
            setAgentSymbol(refVal_setAgentSymbol);
        }
    }
    if(val.has_field(utility::conversions::to_string_t(U("credits"))))
    {
        const web::json::value& fieldValue = val.at(utility::conversions::to_string_t(U("credits")));
        if(!fieldValue.is_null())
        {
            int64_t refVal_setCredits;
            ok &= ModelBase::fromJson(fieldValue, refVal_setCredits);
            setCredits(refVal_setCredits);
        }
    }
    return ok;
}

void Get_status_200_response_leaderboards_mostCredits_inner::toMultipart(std::shared_ptr<MultipartFormData> multipart, const utility::string_t& prefix) const
{
    utility::string_t namePrefix = prefix;
    if(namePrefix.size() > 0 && namePrefix.substr(namePrefix.size() - 1) != utility::conversions::to_string_t(U(".")))
    {
        namePrefix += utility::conversions::to_string_t(U("."));
    }
    if(m_AgentSymbolIsSet)
    {
        multipart->add(ModelBase::toHttpContent(namePrefix + utility::conversions::to_string_t(U("agentSymbol")), m_AgentSymbol));
    }
    if(m_CreditsIsSet)
    {
        multipart->add(ModelBase::toHttpContent(namePrefix + utility::conversions::to_string_t(U("credits")), m_Credits));
    }
}

bool Get_status_200_response_leaderboards_mostCredits_inner::fromMultiPart(std::shared_ptr<MultipartFormData> multipart, const utility::string_t& prefix)
{
    bool ok = true;
    utility::string_t namePrefix = prefix;
    if(namePrefix.size() > 0 && namePrefix.substr(namePrefix.size() - 1) != utility::conversions::to_string_t(U(".")))
    {
        namePrefix += utility::conversions::to_string_t(U("."));
    }

    if(multipart->hasContent(utility::conversions::to_string_t(U("agentSymbol"))))
    {
        utility::string_t refVal_setAgentSymbol;
        ok &= ModelBase::fromHttpContent(multipart->getContent(utility::conversions::to_string_t(U("agentSymbol"))), refVal_setAgentSymbol );
        setAgentSymbol(refVal_setAgentSymbol);
    }
    if(multipart->hasContent(utility::conversions::to_string_t(U("credits"))))
    {
        int64_t refVal_setCredits;
        ok &= ModelBase::fromHttpContent(multipart->getContent(utility::conversions::to_string_t(U("credits"))), refVal_setCredits );
        setCredits(refVal_setCredits);
    }
    return ok;
}

utility::string_t Get_status_200_response_leaderboards_mostCredits_inner::getAgentSymbol() const
{
    return m_AgentSymbol;
}

void Get_status_200_response_leaderboards_mostCredits_inner::setAgentSymbol(const utility::string_t& value)
{
    m_AgentSymbol = value;
    m_AgentSymbolIsSet = true;
}

bool Get_status_200_response_leaderboards_mostCredits_inner::agentSymbolIsSet() const
{
    return m_AgentSymbolIsSet;
}

void Get_status_200_response_leaderboards_mostCredits_inner::unsetAgentSymbol()
{
    m_AgentSymbolIsSet = false;
}
int64_t Get_status_200_response_leaderboards_mostCredits_inner::getCredits() const
{
    return m_Credits;
}

void Get_status_200_response_leaderboards_mostCredits_inner::setCredits(int64_t value)
{
    m_Credits = value;
    m_CreditsIsSet = true;
}

bool Get_status_200_response_leaderboards_mostCredits_inner::creditsIsSet() const
{
    return m_CreditsIsSet;
}

void Get_status_200_response_leaderboards_mostCredits_inner::unsetCredits()
{
    m_CreditsIsSet = false;
}
}


