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



#include "CppRestOpenAPIClient/model/Survey.h"

namespace models {



Survey::Survey()
{
    m_Signature = utility::conversions::to_string_t("");
    m_SignatureIsSet = false;
    m_Symbol = utility::conversions::to_string_t("");
    m_SymbolIsSet = false;
    m_DepositsIsSet = false;
    m_Expiration = utility::datetime();
    m_ExpirationIsSet = false;
    m_Size = utility::conversions::to_string_t("");
    m_SizeIsSet = false;
}

Survey::~Survey()
{
}

void Survey::validate()
{
    // TODO: implement validation
}

web::json::value Survey::toJson() const
{

    web::json::value val = web::json::value::object();
    
    if(m_SignatureIsSet)
    {
        val[utility::conversions::to_string_t(U("signature"))] = ModelBase::toJson(m_Signature);
    }
    if(m_SymbolIsSet)
    {
        val[utility::conversions::to_string_t(U("symbol"))] = ModelBase::toJson(m_Symbol);
    }
    if(m_DepositsIsSet)
    {
        val[utility::conversions::to_string_t(U("deposits"))] = ModelBase::toJson(m_Deposits);
    }
    if(m_ExpirationIsSet)
    {
        val[utility::conversions::to_string_t(U("expiration"))] = ModelBase::toJson(m_Expiration);
    }
    if(m_SizeIsSet)
    {
        val[utility::conversions::to_string_t(U("size"))] = ModelBase::toJson(m_Size);
    }

    return val;
}

bool Survey::fromJson(const web::json::value& val)
{
    bool ok = true;
    
    if(val.has_field(utility::conversions::to_string_t(U("signature"))))
    {
        const web::json::value& fieldValue = val.at(utility::conversions::to_string_t(U("signature")));
        if(!fieldValue.is_null())
        {
            utility::string_t refVal_setSignature;
            ok &= ModelBase::fromJson(fieldValue, refVal_setSignature);
            setSignature(refVal_setSignature);
        }
    }
    if(val.has_field(utility::conversions::to_string_t(U("symbol"))))
    {
        const web::json::value& fieldValue = val.at(utility::conversions::to_string_t(U("symbol")));
        if(!fieldValue.is_null())
        {
            utility::string_t refVal_setSymbol;
            ok &= ModelBase::fromJson(fieldValue, refVal_setSymbol);
            setSymbol(refVal_setSymbol);
        }
    }
    if(val.has_field(utility::conversions::to_string_t(U("deposits"))))
    {
        const web::json::value& fieldValue = val.at(utility::conversions::to_string_t(U("deposits")));
        if(!fieldValue.is_null())
        {
            std::vector<std::shared_ptr<SurveyDeposit>> refVal_setDeposits;
            ok &= ModelBase::fromJson(fieldValue, refVal_setDeposits);
            setDeposits(refVal_setDeposits);
        }
    }
    if(val.has_field(utility::conversions::to_string_t(U("expiration"))))
    {
        const web::json::value& fieldValue = val.at(utility::conversions::to_string_t(U("expiration")));
        if(!fieldValue.is_null())
        {
            utility::datetime refVal_setExpiration;
            ok &= ModelBase::fromJson(fieldValue, refVal_setExpiration);
            setExpiration(refVal_setExpiration);
        }
    }
    if(val.has_field(utility::conversions::to_string_t(U("size"))))
    {
        const web::json::value& fieldValue = val.at(utility::conversions::to_string_t(U("size")));
        if(!fieldValue.is_null())
        {
            utility::string_t refVal_setSize;
            ok &= ModelBase::fromJson(fieldValue, refVal_setSize);
            setSize(refVal_setSize);
        }
    }
    return ok;
}

void Survey::toMultipart(std::shared_ptr<MultipartFormData> multipart, const utility::string_t& prefix) const
{
    utility::string_t namePrefix = prefix;
    if(namePrefix.size() > 0 && namePrefix.substr(namePrefix.size() - 1) != utility::conversions::to_string_t(U(".")))
    {
        namePrefix += utility::conversions::to_string_t(U("."));
    }
    if(m_SignatureIsSet)
    {
        multipart->add(ModelBase::toHttpContent(namePrefix + utility::conversions::to_string_t(U("signature")), m_Signature));
    }
    if(m_SymbolIsSet)
    {
        multipart->add(ModelBase::toHttpContent(namePrefix + utility::conversions::to_string_t(U("symbol")), m_Symbol));
    }
    if(m_DepositsIsSet)
    {
        multipart->add(ModelBase::toHttpContent(namePrefix + utility::conversions::to_string_t(U("deposits")), m_Deposits));
    }
    if(m_ExpirationIsSet)
    {
        multipart->add(ModelBase::toHttpContent(namePrefix + utility::conversions::to_string_t(U("expiration")), m_Expiration));
    }
    if(m_SizeIsSet)
    {
        multipart->add(ModelBase::toHttpContent(namePrefix + utility::conversions::to_string_t(U("size")), m_Size));
    }
}

bool Survey::fromMultiPart(std::shared_ptr<MultipartFormData> multipart, const utility::string_t& prefix)
{
    bool ok = true;
    utility::string_t namePrefix = prefix;
    if(namePrefix.size() > 0 && namePrefix.substr(namePrefix.size() - 1) != utility::conversions::to_string_t(U(".")))
    {
        namePrefix += utility::conversions::to_string_t(U("."));
    }

    if(multipart->hasContent(utility::conversions::to_string_t(U("signature"))))
    {
        utility::string_t refVal_setSignature;
        ok &= ModelBase::fromHttpContent(multipart->getContent(utility::conversions::to_string_t(U("signature"))), refVal_setSignature );
        setSignature(refVal_setSignature);
    }
    if(multipart->hasContent(utility::conversions::to_string_t(U("symbol"))))
    {
        utility::string_t refVal_setSymbol;
        ok &= ModelBase::fromHttpContent(multipart->getContent(utility::conversions::to_string_t(U("symbol"))), refVal_setSymbol );
        setSymbol(refVal_setSymbol);
    }
    if(multipart->hasContent(utility::conversions::to_string_t(U("deposits"))))
    {
        std::vector<std::shared_ptr<SurveyDeposit>> refVal_setDeposits;
        ok &= ModelBase::fromHttpContent(multipart->getContent(utility::conversions::to_string_t(U("deposits"))), refVal_setDeposits );
        setDeposits(refVal_setDeposits);
    }
    if(multipart->hasContent(utility::conversions::to_string_t(U("expiration"))))
    {
        utility::datetime refVal_setExpiration;
        ok &= ModelBase::fromHttpContent(multipart->getContent(utility::conversions::to_string_t(U("expiration"))), refVal_setExpiration );
        setExpiration(refVal_setExpiration);
    }
    if(multipart->hasContent(utility::conversions::to_string_t(U("size"))))
    {
        utility::string_t refVal_setSize;
        ok &= ModelBase::fromHttpContent(multipart->getContent(utility::conversions::to_string_t(U("size"))), refVal_setSize );
        setSize(refVal_setSize);
    }
    return ok;
}

utility::string_t Survey::getSignature() const
{
    return m_Signature;
}

void Survey::setSignature(const utility::string_t& value)
{
    m_Signature = value;
    m_SignatureIsSet = true;
}

bool Survey::signatureIsSet() const
{
    return m_SignatureIsSet;
}

void Survey::unsetSignature()
{
    m_SignatureIsSet = false;
}
utility::string_t Survey::getSymbol() const
{
    return m_Symbol;
}

void Survey::setSymbol(const utility::string_t& value)
{
    m_Symbol = value;
    m_SymbolIsSet = true;
}

bool Survey::symbolIsSet() const
{
    return m_SymbolIsSet;
}

void Survey::unsetSymbol()
{
    m_SymbolIsSet = false;
}
std::vector<std::shared_ptr<SurveyDeposit>>& Survey::getDeposits()
{
    return m_Deposits;
}

void Survey::setDeposits(const std::vector<std::shared_ptr<SurveyDeposit>>& value)
{
    m_Deposits = value;
    m_DepositsIsSet = true;
}

bool Survey::depositsIsSet() const
{
    return m_DepositsIsSet;
}

void Survey::unsetDeposits()
{
    m_DepositsIsSet = false;
}
utility::datetime Survey::getExpiration() const
{
    return m_Expiration;
}

void Survey::setExpiration(const utility::datetime& value)
{
    m_Expiration = value;
    m_ExpirationIsSet = true;
}

bool Survey::expirationIsSet() const
{
    return m_ExpirationIsSet;
}

void Survey::unsetExpiration()
{
    m_ExpirationIsSet = false;
}
utility::string_t Survey::getSize() const
{
    return m_Size;
}

void Survey::setSize(const utility::string_t& value)
{
    m_Size = value;
    m_SizeIsSet = true;
}

bool Survey::sizeIsSet() const
{
    return m_SizeIsSet;
}

void Survey::unsetSize()
{
    m_SizeIsSet = false;
}
}

