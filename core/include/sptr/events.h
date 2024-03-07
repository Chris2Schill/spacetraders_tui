#pragma once

#include <string>

namespace sptr {
    class User;
    
namespace event {


    struct UserSelected {
      const sptr::User *user;
    };

    struct LogEvent {
        std::string msg;
    };
}

}
