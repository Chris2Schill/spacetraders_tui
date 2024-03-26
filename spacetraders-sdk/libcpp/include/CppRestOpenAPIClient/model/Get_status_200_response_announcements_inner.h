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
 * Get_status_200_response_announcements_inner.h
 *
 * 
 */

#ifndef MODELS_Get_status_200_response_announcements_inner_H_
#define MODELS_Get_status_200_response_announcements_inner_H_


#include "CppRestOpenAPIClient/ModelBase.h"

#include <cpprest/details/basic_types.h>

namespace models {


/// <summary>
/// 
/// </summary>
class  Get_status_200_response_announcements_inner
    : public ModelBase
{
public:
    Get_status_200_response_announcements_inner();
    virtual ~Get_status_200_response_announcements_inner();

    /////////////////////////////////////////////
    /// ModelBase overrides

    void validate() override;

    web::json::value toJson() const override;
    bool fromJson(const web::json::value& json) override;

    void toMultipart(std::shared_ptr<MultipartFormData> multipart, const utility::string_t& namePrefix) const override;
    bool fromMultiPart(std::shared_ptr<MultipartFormData> multipart, const utility::string_t& namePrefix) override;

    /////////////////////////////////////////////
    /// Get_status_200_response_announcements_inner members

    /// <summary>
    /// 
    /// </summary>
    utility::string_t getTitle() const;
    bool titleIsSet() const;
    void unsetTitle();

    void setTitle(const utility::string_t& value);

    /// <summary>
    /// 
    /// </summary>
    utility::string_t getBody() const;
    bool bodyIsSet() const;
    void unsetBody();

    void setBody(const utility::string_t& value);


protected:
    utility::string_t m_Title;
    bool m_TitleIsSet;
    utility::string_t m_Body;
    bool m_BodyIsSet;
};


}

#endif /* MODELS_Get_status_200_response_announcements_inner_H_ */