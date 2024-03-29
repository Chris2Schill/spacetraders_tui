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
 * Meta.h
 *
 * Meta details for pagination.
 */

#ifndef MODELS_Meta_H_
#define MODELS_Meta_H_


#include "CppRestOpenAPIClient/ModelBase.h"


namespace models {


/// <summary>
/// Meta details for pagination.
/// </summary>
class  Meta
    : public ModelBase
{
public:
    Meta();
    virtual ~Meta();

    /////////////////////////////////////////////
    /// ModelBase overrides

    void validate() override;

    web::json::value toJson() const override;
    bool fromJson(const web::json::value& json) override;

    void toMultipart(std::shared_ptr<MultipartFormData> multipart, const utility::string_t& namePrefix) const override;
    bool fromMultiPart(std::shared_ptr<MultipartFormData> multipart, const utility::string_t& namePrefix) override;

    /////////////////////////////////////////////
    /// Meta members

    /// <summary>
    /// Shows the total amount of items of this kind that exist.
    /// </summary>
    int32_t getTotal() const;
    bool totalIsSet() const;
    void unsetTotal();

    void setTotal(int32_t value);

    /// <summary>
    /// A page denotes an amount of items, offset from the first item. Each page holds an amount of items equal to the &#x60;limit&#x60;.
    /// </summary>
    int32_t getPage() const;
    bool pageIsSet() const;
    void unsetPage();

    void setPage(int32_t value);

    /// <summary>
    /// The amount of items in each page. Limits how many items can be fetched at once.
    /// </summary>
    int32_t getLimit() const;
    bool limitIsSet() const;
    void unsetLimit();

    void setLimit(int32_t value);


protected:
    int32_t m_Total;
    bool m_TotalIsSet;
    int32_t m_Page;
    bool m_PageIsSet;
    int32_t m_Limit;
    bool m_LimitIsSet;
};


}

#endif /* MODELS_Meta_H_ */
