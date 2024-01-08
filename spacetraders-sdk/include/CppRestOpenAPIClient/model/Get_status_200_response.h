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
 * Get_status_200_response.h
 *
 * 
 */

#ifndef MODELS_Get_status_200_response_H_
#define MODELS_Get_status_200_response_H_


#include "CppRestOpenAPIClient/ModelBase.h"

#include "CppRestOpenAPIClient/model/Get_status_200_response_leaderboards.h"
#include "CppRestOpenAPIClient/model/Get_status_200_response_serverResets.h"
#include "CppRestOpenAPIClient/model/Get_status_200_response_announcements_inner.h"
#include "CppRestOpenAPIClient/model/Get_status_200_response_links_inner.h"
#include <cpprest/details/basic_types.h>
#include "CppRestOpenAPIClient/model/Get_status_200_response_stats.h"
#include <vector>

namespace models {

class Get_status_200_response_stats;
class Get_status_200_response_leaderboards;
class Get_status_200_response_serverResets;
class Get_status_200_response_announcements_inner;
class Get_status_200_response_links_inner;

/// <summary>
/// 
/// </summary>
class  Get_status_200_response
    : public ModelBase
{
public:
    Get_status_200_response();
    virtual ~Get_status_200_response();

    /////////////////////////////////////////////
    /// ModelBase overrides

    void validate() override;

    web::json::value toJson() const override;
    bool fromJson(const web::json::value& json) override;

    void toMultipart(std::shared_ptr<MultipartFormData> multipart, const utility::string_t& namePrefix) const override;
    bool fromMultiPart(std::shared_ptr<MultipartFormData> multipart, const utility::string_t& namePrefix) override;

    /////////////////////////////////////////////
    /// Get_status_200_response members

    /// <summary>
    /// The current status of the game server.
    /// </summary>
    utility::string_t getStatus() const;
    bool statusIsSet() const;
    void unsetStatus();

    void setStatus(const utility::string_t& value);

    /// <summary>
    /// The current version of the API.
    /// </summary>
    utility::string_t getVersion() const;
    bool versionIsSet() const;
    void unsetVersion();

    void setVersion(const utility::string_t& value);

    /// <summary>
    /// The date when the game server was last reset.
    /// </summary>
    utility::string_t getResetDate() const;
    bool resetDateIsSet() const;
    void unsetResetDate();

    void setResetDate(const utility::string_t& value);

    /// <summary>
    /// 
    /// </summary>
    utility::string_t getDescription() const;
    bool descriptionIsSet() const;
    void unsetDescription();

    void setDescription(const utility::string_t& value);

    /// <summary>
    /// 
    /// </summary>
    std::shared_ptr<Get_status_200_response_stats> getStats() const;
    bool statsIsSet() const;
    void unsetStats();

    void setStats(const std::shared_ptr<Get_status_200_response_stats>& value);

    /// <summary>
    /// 
    /// </summary>
    std::shared_ptr<Get_status_200_response_leaderboards> getLeaderboards() const;
    bool leaderboardsIsSet() const;
    void unsetLeaderboards();

    void setLeaderboards(const std::shared_ptr<Get_status_200_response_leaderboards>& value);

    /// <summary>
    /// 
    /// </summary>
    std::shared_ptr<Get_status_200_response_serverResets> getServerResets() const;
    bool serverResetsIsSet() const;
    void unsetServerResets();

    void setServerResets(const std::shared_ptr<Get_status_200_response_serverResets>& value);

    /// <summary>
    /// 
    /// </summary>
    std::vector<std::shared_ptr<Get_status_200_response_announcements_inner>>& getAnnouncements();
    bool announcementsIsSet() const;
    void unsetAnnouncements();

    void setAnnouncements(const std::vector<std::shared_ptr<Get_status_200_response_announcements_inner>>& value);

    /// <summary>
    /// 
    /// </summary>
    std::vector<std::shared_ptr<Get_status_200_response_links_inner>>& getLinks();
    bool linksIsSet() const;
    void unsetLinks();

    void setLinks(const std::vector<std::shared_ptr<Get_status_200_response_links_inner>>& value);


protected:
    utility::string_t m_Status;
    bool m_StatusIsSet;
    utility::string_t m_Version;
    bool m_VersionIsSet;
    utility::string_t m_ResetDate;
    bool m_ResetDateIsSet;
    utility::string_t m_Description;
    bool m_DescriptionIsSet;
    std::shared_ptr<Get_status_200_response_stats> m_Stats;
    bool m_StatsIsSet;
    std::shared_ptr<Get_status_200_response_leaderboards> m_Leaderboards;
    bool m_LeaderboardsIsSet;
    std::shared_ptr<Get_status_200_response_serverResets> m_ServerResets;
    bool m_ServerResetsIsSet;
    std::vector<std::shared_ptr<Get_status_200_response_announcements_inner>> m_Announcements;
    bool m_AnnouncementsIsSet;
    std::vector<std::shared_ptr<Get_status_200_response_links_inner>> m_Links;
    bool m_LinksIsSet;
};


}

#endif /* MODELS_Get_status_200_response_H_ */
