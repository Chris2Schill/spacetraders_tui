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
 * Get_agents_200_response.h
 *
 * 
 */

#ifndef MODELS_Get_agents_200_response_H_
#define MODELS_Get_agents_200_response_H_


#include "CppRestOpenAPIClient/ModelBase.h"

#include "CppRestOpenAPIClient/model/Agent.h"
#include <vector>
#include "CppRestOpenAPIClient/model/Meta.h"

namespace models {

class Agent;
class Meta;

/// <summary>
/// 
/// </summary>
class  Get_agents_200_response
    : public ModelBase
{
public:
    Get_agents_200_response();
    virtual ~Get_agents_200_response();

    /////////////////////////////////////////////
    /// ModelBase overrides

    void validate() override;

    web::json::value toJson() const override;
    bool fromJson(const web::json::value& json) override;

    void toMultipart(std::shared_ptr<MultipartFormData> multipart, const utility::string_t& namePrefix) const override;
    bool fromMultiPart(std::shared_ptr<MultipartFormData> multipart, const utility::string_t& namePrefix) override;

    /////////////////////////////////////////////
    /// Get_agents_200_response members

    /// <summary>
    /// 
    /// </summary>
    std::vector<std::shared_ptr<Agent>>& getData();
    bool dataIsSet() const;
    void unsetData();

    void setData(const std::vector<std::shared_ptr<Agent>>& value);

    /// <summary>
    /// 
    /// </summary>
    std::shared_ptr<Meta> getMeta() const;
    bool metaIsSet() const;
    void unsetMeta();

    void setMeta(const std::shared_ptr<Meta>& value);


protected:
    std::vector<std::shared_ptr<Agent>> m_Data;
    bool m_DataIsSet;
    std::shared_ptr<Meta> m_Meta;
    bool m_MetaIsSet;
};


}

#endif /* MODELS_Get_agents_200_response_H_ */
