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
 * MultipartFormData.h
 *
 * This class represents a container for building application/x-multipart-formdata requests.
 */

#ifndef MODELS_MultipartFormData_H_
#define MODELS_MultipartFormData_H_


#include "CppRestOpenAPIClient/IHttpBody.h"
#include "CppRestOpenAPIClient/HttpContent.h"

#include <cpprest/details/basic_types.h>

#include <vector>
#include <map>
#include <memory>

namespace models {

class  MultipartFormData
    : public IHttpBody
{
public:
    MultipartFormData();
    MultipartFormData(const utility::string_t& boundary);
    virtual ~MultipartFormData();

    virtual void add( std::shared_ptr<HttpContent> content );
    virtual utility::string_t getBoundary();
    virtual std::shared_ptr<HttpContent> getContent(const utility::string_t& name) const;
    virtual bool hasContent(const utility::string_t& name) const;
    virtual void writeTo( std::ostream& target );

protected:
    std::vector<std::shared_ptr<HttpContent>> m_Contents;
    utility::string_t m_Boundary;
    std::map<utility::string_t, std::shared_ptr<HttpContent>> m_ContentLookup;
};

}

#endif /* MODELS_MultipartFormData_H_ */
