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



#include "CppRestOpenAPIClient/model/Create_survey_201_response_data.h"

namespace models {



Create_survey_201_response_data::Create_survey_201_response_data()
{
    m_CooldownIsSet = false;
    m_SurveysIsSet = false;
}

Create_survey_201_response_data::~Create_survey_201_response_data()
{
}

void Create_survey_201_response_data::validate()
{
    // TODO: implement validation
}

web::json::value Create_survey_201_response_data::toJson() const
{

    web::json::value val = web::json::value::object();
    
    if(m_CooldownIsSet)
    {
        val[utility::conversions::to_string_t(U("cooldown"))] = ModelBase::toJson(m_Cooldown);
    }
    if(m_SurveysIsSet)
    {
        val[utility::conversions::to_string_t(U("surveys"))] = ModelBase::toJson(m_Surveys);
    }

    return val;
}

bool Create_survey_201_response_data::fromJson(const web::json::value& val)
{
    bool ok = true;
    
    if(val.has_field(utility::conversions::to_string_t(U("cooldown"))))
    {
        const web::json::value& fieldValue = val.at(utility::conversions::to_string_t(U("cooldown")));
        if(!fieldValue.is_null())
        {
            std::shared_ptr<Cooldown> refVal_setCooldown;
            ok &= ModelBase::fromJson(fieldValue, refVal_setCooldown);
            setCooldown(refVal_setCooldown);
        }
    }
    if(val.has_field(utility::conversions::to_string_t(U("surveys"))))
    {
        const web::json::value& fieldValue = val.at(utility::conversions::to_string_t(U("surveys")));
        if(!fieldValue.is_null())
        {
            std::vector<std::shared_ptr<Survey>> refVal_setSurveys;
            ok &= ModelBase::fromJson(fieldValue, refVal_setSurveys);
            setSurveys(refVal_setSurveys);
        }
    }
    return ok;
}

void Create_survey_201_response_data::toMultipart(std::shared_ptr<MultipartFormData> multipart, const utility::string_t& prefix) const
{
    utility::string_t namePrefix = prefix;
    if(namePrefix.size() > 0 && namePrefix.substr(namePrefix.size() - 1) != utility::conversions::to_string_t(U(".")))
    {
        namePrefix += utility::conversions::to_string_t(U("."));
    }
    if(m_CooldownIsSet)
    {
        multipart->add(ModelBase::toHttpContent(namePrefix + utility::conversions::to_string_t(U("cooldown")), m_Cooldown));
    }
    if(m_SurveysIsSet)
    {
        multipart->add(ModelBase::toHttpContent(namePrefix + utility::conversions::to_string_t(U("surveys")), m_Surveys));
    }
}

bool Create_survey_201_response_data::fromMultiPart(std::shared_ptr<MultipartFormData> multipart, const utility::string_t& prefix)
{
    bool ok = true;
    utility::string_t namePrefix = prefix;
    if(namePrefix.size() > 0 && namePrefix.substr(namePrefix.size() - 1) != utility::conversions::to_string_t(U(".")))
    {
        namePrefix += utility::conversions::to_string_t(U("."));
    }

    if(multipart->hasContent(utility::conversions::to_string_t(U("cooldown"))))
    {
        std::shared_ptr<Cooldown> refVal_setCooldown;
        ok &= ModelBase::fromHttpContent(multipart->getContent(utility::conversions::to_string_t(U("cooldown"))), refVal_setCooldown );
        setCooldown(refVal_setCooldown);
    }
    if(multipart->hasContent(utility::conversions::to_string_t(U("surveys"))))
    {
        std::vector<std::shared_ptr<Survey>> refVal_setSurveys;
        ok &= ModelBase::fromHttpContent(multipart->getContent(utility::conversions::to_string_t(U("surveys"))), refVal_setSurveys );
        setSurveys(refVal_setSurveys);
    }
    return ok;
}

std::shared_ptr<Cooldown> Create_survey_201_response_data::getCooldown() const
{
    return m_Cooldown;
}

void Create_survey_201_response_data::setCooldown(const std::shared_ptr<Cooldown>& value)
{
    m_Cooldown = value;
    m_CooldownIsSet = true;
}

bool Create_survey_201_response_data::cooldownIsSet() const
{
    return m_CooldownIsSet;
}

void Create_survey_201_response_data::unsetCooldown()
{
    m_CooldownIsSet = false;
}
std::vector<std::shared_ptr<Survey>>& Create_survey_201_response_data::getSurveys()
{
    return m_Surveys;
}

void Create_survey_201_response_data::setSurveys(const std::vector<std::shared_ptr<Survey>>& value)
{
    m_Surveys = value;
    m_SurveysIsSet = true;
}

bool Create_survey_201_response_data::surveysIsSet() const
{
    return m_SurveysIsSet;
}

void Create_survey_201_response_data::unsetSurveys()
{
    m_SurveysIsSet = false;
}
}


