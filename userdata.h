#pragma once

#include <vector>
#include <string>

namespace dm {

namespace fields {
    inline static constexpr char* TOKEN = "token";
    inline static constexpr char* AGENT = "agent";
    inline static constexpr char* CONTRACT = "contract";
    inline static constexpr char* FACTION = "faction";
}

  // struct Player {
  //     std::string token = "eyJhbGciOiJSUzI1NiIsInR5cCI6IkpXVCJ9.eyJpZGVudGlmaWVyIjoiRkFUSE9SU0VOSVBTIiwidmVyc2lvbiI6InYyLjEuNCIsInJlc2V0X2RhdGUiOiIyMDIzLTEyLTE2IiwiaWF0IjoxNzAzNzEwOTIyLCJzdWIiOiJhZ2VudC10b2tlbiJ9.dd7Je0n4cFDQdfjmXVZcbNr0lhEBAWDKp-eWINh1ppXIYUdFOgXd4lKBELYk_9ksgmwYI9vKV9HtnPxLBt77S6hCHfZW4QM52o5XR57_fYRPPyvgipdUmuJlmSzOw2eEOiI3dkv613CGHuEZp7aQ5knejfzDySSmFiNBzmFPwtIbDtwwP-BylUlchkJfTefoDsX9oCFtEO-_aGJoF9aTutMduU3ggXT1umK0D_BGbfWL7ZD_3TN_AfrE8ndQdrkm_D455Dx3wplwfvQyrCTZedu94KP37kNxzqMza4qzvm4IuUBO83bvVm51Bzv_f93mmIAZDY36iuiMdw0A4unx6A";
  //   "agent": {
  //     "accountId": "clqo9ht5duazms60c0ng4nyk0",
  //     "symbol": "FATHORSENIPS",
  //     "headquarters": "X1-MT7-A1",
  //     "credits": 175000,
  //     "startingFaction": "COSMIC",
  //     "shipCount": 0
  //   },
  //   "contract": {
  //     "id": "clqo9ht6zuazos60cet5t33k0",
  //     "factionSymbol": "COSMIC",
  //     "type": "PROCUREMENT",
  //     "terms": {
  //       "deadline": "2024-01-03T21:02:02.489Z",
  //       "payment": {
  //         "onAccepted": 1368,
  //         "onFulfilled": 8662
  //       },
  //       "deliver": [
  //         {
  //           "tradeSymbol": "COPPER_ORE",
  //           "destinationSymbol": "X1-MT7-H50",
  //           "unitsRequired": 139,
  //           "unitsFulfilled": 0
  //         }
  //       ]
  //     },
  //     "accepted": false,
  //     "fulfilled": false,
  //     "expiration": "2023-12-28T21:02:02.489Z",
  //     "deadlineToAccept": "2023-12-28T21:02:02.489Z"
  //   },
  //   "faction": {
  //     "symbol": "COSMIC",
  //     "name": "Cosmic Engineers",
  //     "description": "The Cosmic Engineers are a group of highly advanced scientists and engineers who seek to terraform and colonize new worlds, pushing the boundaries of technology and exploration.",
  //     "headquarters": "X1-MY18",
  //     "traits": [
  //       {
  //         "symbol": "INNOVATIVE",
  //         "name": "Innovative",
  //         "description": "Willing to try new and untested ideas. Sometimes able to come up with creative and original solutions to problems, and may be able to think outside the box. Sometimes at the forefront of technological or social change, and may be willing to take risks in order to advance the boundaries of human knowledge and understanding."
  //       },
  //       {
  //         "symbol": "BOLD",
  //         "name": "Bold",
  //         "description": "Unafraid to take risks and challenge the status quo. Sometimes willing to do things that others would not dare, and may be able to overcome obstacles and challenges that would be insurmountable for others. Sometimes able to inspire and motivate others to take bold action as well."
  //       },
  //       {
  //         "symbol": "VISIONARY",
  //         "name": "Visionary",
  //         "description": "Possessing a clear and compelling vision for the future. Sometimes able to see beyond the present and anticipate the needs and challenges of tomorrow. Sometimes able to inspire and guide others towards a better and brighter future, and may be willing to take bold and decisive action to make their vision a reality."
  //       },
  //       {
  //         "symbol": "CURIOUS",
  //         "name": "Curious",
  //         "description": "Possessing a strong desire to learn and explore. Sometimes interested in a wide range of topics and may be willing to take risks in order to satisfy their curiosity. Sometimes able to think outside the box and come up with creative solutions to challenges."
  //       }
  //     ],
  //     "isRecruiting": true
  //   },
  //   "ship": {
  //     "symbol": "FATHORSENIPS-1",
  //     "nav": {
  //       "systemSymbol": "X1-MT7",
  //       "waypointSymbol": "X1-MT7-A1",
  //       "route": {
  //         "departure": {
  //           "symbol": "X1-MT7-A1",
  //           "type": "PLANET",
  //           "systemSymbol": "X1-MT7",
  //           "x": -18,
  //           "y": 17
  //         },
  //         "origin": {
  //           "symbol": "X1-MT7-A1",
  //           "type": "PLANET",
  //           "systemSymbol": "X1-MT7",
  //           "x": -18,
  //           "y": 17
  //         },
  //         "destination": {
  //           "symbol": "X1-MT7-A1",
  //           "type": "PLANET",
  //           "systemSymbol": "X1-MT7",
  //           "x": -18,
  //           "y": 17
  //         },
  //         "arrival": "2023-12-27T21:02:02.545Z",
  //         "departureTime": "2023-12-27T21:02:02.545Z"
  //       },
  //       "status": "DOCKED",
  //       "flightMode": "CRUISE"
  //     },
  //     "crew": {
  //       "current": 57,
  //       "capacity": 80,
  //       "required": 57,
  //       "rotation": "STRICT",
  //       "morale": 100,
  //       "wages": 0
  //     },
  //     "fuel": {
  //       "current": 400,
  //       "capacity": 400,
  //       "consumed": {
  //         "amount": 0,
  //         "timestamp": "2023-12-27T21:02:02.545Z"
  //       }
  //     },
  //     "cooldown": {
  //       "shipSymbol": "FATHORSENIPS-1",
  //       "totalSeconds": 0,
  //       "remainingSeconds": 0
  //     },
  //     "frame": {
  //       "symbol": "FRAME_FRIGATE",
  //       "name": "Frigate",
  //       "description": "A medium-sized, multi-purpose spacecraft, often used for combat, transport, or support operations.",
  //       "moduleSlots": 8,
  //       "mountingPoints": 5,
  //       "fuelCapacity": 400,
  //       "condition": 100,
  //       "requirements": {
  //         "power": 8,
  //         "crew": 25
  //       }
  //     },
  //     "reactor": {
  //       "symbol": "REACTOR_FISSION_I",
  //       "name": "Fission Reactor I",
  //       "description": "A basic fission power reactor, used to generate electricity from nuclear fission reactions.",
  //       "condition": 100,
  //       "powerOutput": 31,
  //       "requirements": {
  //         "crew": 8
  //       }
  //     },
  //     "engine": {
  //       "symbol": "ENGINE_ION_DRIVE_II",
  //       "name": "Ion Drive II",
  //       "description": "An advanced propulsion system that uses ionized particles to generate high-speed, low-thrust acceleration, with improved efficiency and performance.",
  //       "condition": 100,
  //       "speed": 30,
  //       "requirements": {
  //         "power": 6,
  //         "crew": 8
  //       }
  //     },
  //     "modules": [
  //       {
  //         "symbol": "MODULE_CARGO_HOLD_II",
  //         "name": "Expanded Cargo Hold",
  //         "description": "An expanded cargo hold module that provides more efficient storage space for a ship's cargo.",
  //         "capacity": 40,
  //         "requirements": {
  //           "crew": 2,
  //           "power": 2,
  //           "slots": 2
  //         }
  //       },
  //       {
  //         "symbol": "MODULE_CREW_QUARTERS_I",
  //         "name": "Crew Quarters",
  //         "description": "A module that provides living space and amenities for the crew.",
  //         "capacity": 40,
  //         "requirements": {
  //           "crew": 2,
  //           "power": 1,
  //           "slots": 1
  //         }
  //       },
  //       {
  //         "symbol": "MODULE_CREW_QUARTERS_I",
  //         "name": "Crew Quarters",
  //         "description": "A module that provides living space and amenities for the crew.",
  //         "capacity": 40,
  //         "requirements": {
  //           "crew": 2,
  //           "power": 1,
  //           "slots": 1
  //         }
  //       },
  //       {
  //         "symbol": "MODULE_MINERAL_PROCESSOR_I",
  //         "name": "Mineral Processor",
  //         "description": "Crushes and processes extracted minerals and ores into their component parts, filters out impurities, and containerizes them into raw storage units.",
  //         "requirements": {
  //           "crew": 0,
  //           "power": 1,
  //           "slots": 2
  //         }
  //       },
  //       {
  //         "symbol": "MODULE_GAS_PROCESSOR_I",
  //         "name": "Gas Processor",
  //         "description": "Filters and processes extracted gases into their component parts, filters out impurities, and containerizes them into raw storage units.",
  //         "requirements": {
  //           "crew": 0,
  //           "power": 1,
  //           "slots": 2
  //         }
  //       }
  //     ],
  //     "mounts": [
  //       {
  //         "symbol": "MOUNT_SENSOR_ARRAY_II",
  //         "name": "Sensor Array II",
  //         "description": "An advanced sensor array that improves a ship's ability to detect and track other objects in space with greater accuracy and range.",
  //         "strength": 4,
  //         "requirements": {
  //           "crew": 2,
  //           "power": 2
  //         }
  //       },
  //       {
  //         "symbol": "MOUNT_GAS_SIPHON_II",
  //         "name": "Gas Siphon II",
  //         "description": "An advanced gas siphon that can extract gas from gas giants and other gas-rich bodies more efficiently and at a higher rate.",
  //         "strength": 20,
  //         "requirements": {
  //           "crew": 2,
  //           "power": 2
  //         }
  //       },
  //       {
  //         "symbol": "MOUNT_MINING_LASER_II",
  //         "name": "Mining Laser II",
  //         "description": "An advanced mining laser that is more efficient and effective at extracting valuable minerals from asteroids and other space objects.",
  //         "strength": 5,
  //         "requirements": {
  //           "crew": 2,
  //           "power": 2
  //         }
  //       },
  //       {
  //         "symbol": "MOUNT_SURVEYOR_II",
  //         "name": "Surveyor II",
  //         "description": "An advanced survey probe that can be used to gather information about a mineral deposit with greater accuracy.",
  //         "strength": 2,
  //         "deposits": [
  //           "QUARTZ_SAND",
  //           "SILICON_CRYSTALS",
  //           "PRECIOUS_STONES",
  //           "ICE_WATER",
  //           "AMMONIA_ICE",
  //           "IRON_ORE",
  //           "COPPER_ORE",
  //           "SILVER_ORE",
  //           "ALUMINUM_ORE",
  //           "GOLD_ORE",
  //           "PLATINUM_ORE",
  //           "DIAMONDS",
  //           "URANITE_ORE"
  //         ],
  //         "requirements": {
  //           "crew": 4,
  //           "power": 3
  //         }
  //       }
  //     ],
  //     "registration": {
  //       "name": "FATHORSENIPS-1",
  //       "factionSymbol": "COSMIC",
  //       "role": "COMMAND"
  //     },
  //     "cargo": {
  //       "capacity": 40,
  //       "units": 0,
  //       "inventory": []
  //     }
  //   }
  // }


struct Requirements {
    int crew;
    int power;
    int slots;
};

struct Consumed {
    
};

struct Fuel {
    int current;
    int capacity;
};

struct Cooldown {
    std::string shipSymbol;
    int totalSeconds;
    int remainingSeconds;
};

struct Frame {
    std::string symbol;
    std::string name;
    std::string description;
    int modulesSlots;
    int mountingPoints;
    int fuelCapacity;
    int condition;
    Requirements requirements;
};

struct Reactor {
    std::string symbol;
    std::string name;
    std::string description;
    int condition;
    int powerOutput;
    Requirements requirements;
};

struct Engine {
    std::string symbol;
    std::string name;
    std::string description;
    int condition;
    int speed;
    Requirements requirements;
};

struct Modules {
    std::string symbol;
    std::string name;
    std::string description;
    int capacity;
    Requirements requirements;
};

struct Mount {
    std::string symbol;
    std::string name;
    std::string description;
    int strength;
    Requirements requirement;
};

struct Registration {
    std::string name;
    std::string factionSymbol;
    std::string role;
};

struct Cargo {
    int capacity;
    int units;
    std::vector<std::string> inventory;
};

} // end namespace dm
