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
 * AgentsApi.h
 *
 * 
 */

#ifndef API_AgentsApi_H_
#define API_AgentsApi_H_



#include "CppRestOpenAPIClient/ApiClient.h"

#include "CppRestOpenAPIClient/model/Get_agents_200_response.h"
#include "CppRestOpenAPIClient/model/Get_my_agent_200_response.h"
#include <cpprest/details/basic_types.h>
#include <boost/optional.hpp>

namespace api {

using namespace models;



class  AgentsApi 
{
public:

    explicit AgentsApi( std::shared_ptr<const ApiClient> apiClient );

    virtual ~AgentsApi();

    /// <summary>
    /// Get Public Agent
    /// </summary>
    /// <remarks>
    /// Fetch agent details.
    /// </remarks>
    /// <param name="agentSymbol">The agent symbol</param>
    pplx::task<std::shared_ptr<Get_my_agent_200_response>> getAgent(
        utility::string_t agentSymbol
    ) const;
    /// <summary>
    /// List Agents
    /// </summary>
    /// <remarks>
    /// Fetch agents details.
    /// </remarks>
    /// <param name="page">What entry offset to request (optional, default to 0)</param>
    /// <param name="limit">How many entries to return per page (optional, default to 0)</param>
    pplx::task<std::shared_ptr<Get_agents_200_response>> getAgents(
        boost::optional<int32_t> page,
        boost::optional<int32_t> limit
    ) const;
    /// <summary>
    /// Get Agent
    /// </summary>
    /// <remarks>
    /// Fetch your agent&#39;s details.
    /// </remarks>
    pplx::task<std::shared_ptr<Get_my_agent_200_response>> getMyAgent(
    ) const;

protected:
    std::shared_ptr<const ApiClient> m_ApiClient;
};

}

#endif /* API_AgentsApi_H_ */

