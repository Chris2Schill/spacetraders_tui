{
    "openapi": "3.0.0",
    "info": {
        "contact": {
            "email": "joel@spacetraders.io",
            "name": "Joel Brubaker"
        },
        "description": "SpaceTraders is an open-universe game and learning platform that offers a set of HTTP endpoints to control a fleet of ships and explore a multiplayer universe.\n\nThe API is documented using [OpenAPI](https://github.com/SpaceTradersAPI/api-docs). You can send your first request right here in your browser to check the status of the game server.\n\n```json http\n{\n  \"method\": \"GET\",\n  \"url\": \"https://api.spacetraders.io/v2\",\n}\n```\n\nUnlike a traditional game, SpaceTraders does not have a first-party client or app to play the game. Instead, you can use the API to build your own client, write a script to automate your ships, or try an app built by the community.\n\nWe have a [Discord channel](https://discord.com/invite/jh6zurdWk5) where you can share your projects, ask questions, and get help from other players.\n\n\n",
        "license": {
            "name": "No Permission",
            "url": "https://choosealicense.com/no-permission/"
        },
        "title": "SpaceTraders API",
        "version": "2.0.0"
    },
    "security": [
        {
            "AgentToken": []
        }
    ],
    "servers": [
        {
            "description": "v2",
            "url": "https://api.spacetraders.io/v2"
        }
    ],
    "tags": [
        {
            "description": "Agents",
            "name": "Agents"
        },
        {
            "description": "Contracts",
            "name": "Contracts"
        },
        {
            "description": "Factions",
            "name": "Factions"
        },
        {
            "description": "Fleet",
            "name": "Fleet"
        },
        {
            "description": "Systems",
            "name": "Systems"
        }
    ],
    "components": {
        "requestBodies": {},
        "schemas": {
            "ActivityLevel": {
                "type": "string",
                "description": "The activity level of a trade good. If the good is an import, this represents how strong consumption is. If the good is an export, this represents how strong the production is for the good. When activity is strong, consumption or production is near maximum capacity. When activity is weak, consumption or production is near minimum capacity.",
                "enum": [
                    "WEAK",
                    "GROWING",
                    "STRONG",
                    "RESTRICTED"
                ],
                "x-enumDescriptions": {
                    "WEAK": "Indicates very low production or consumption activity. This may suggest a surplus in supply or a lack of demand.",
                    "GROWING": "Represents increasing activity in production or consumption, suggesting a developing market.",
                    "STRONG": "Signifies high levels of production or consumption. Indicates a healthy and active market with high demand or supply.",
                    "RESTRICTED": "Reflects a bottleneck in production or consumption, possibly due to a lack of supply or demand in related goods."
                }
            },
            "Agent": {
                "description": "Agent details.",
                "type": "object",
                "properties": {
                    "accountId": {
                        "type": "string",
                        "minLength": 1,
                        "description": "Account ID that is tied to this agent. Only included on your own agent."
                    },
                    "symbol": {
                        "type": "string",
                        "minLength": 3,
                        "maxLength": 14,
                        "description": "Symbol of the agent."
                    },
                    "headquarters": {
                        "type": "string",
                        "minLength": 1,
                        "description": "The headquarters of the agent."
                    },
                    "credits": {
                        "type": "integer",
                        "format": "int64",
                        "description": "The number of credits the agent has available. Credits can be negative if funds have been overdrawn."
                    },
                    "startingFaction": {
                        "type": "string",
                        "minLength": 1,
                        "description": "The faction the agent started with."
                    },
                    "shipCount": {
                        "type": "integer",
                        "description": "How many ships are owned by the agent."
                    }
                },
                "required": [
                    "symbol",
                    "headquarters",
                    "credits",
                    "startingFaction",
                    "shipCount"
                ]
            },
            "Chart": {
                "type": "object",
                "description": "The chart of a system or waypoint, which makes the location visible to other agents.",
                "properties": {
                    "waypointSymbol": {
                        "$ref": "#/components/schemas/WaypointSymbol"
                    },
                    "submittedBy": {
                        "type": "string",
                        "description": "The agent that submitted the chart for this waypoint."
                    },
                    "submittedOn": {
                        "type": "string",
                        "format": "date-time",
                        "description": "The time the chart for this waypoint was submitted."
                    }
                }
            },
            "Construction": {
                "type": "object",
                "description": "The construction details of a waypoint.",
                "properties": {
                    "symbol": {
                        "type": "string",
                        "description": "The symbol of the waypoint."
                    },
                    "materials": {
                        "type": "array",
                        "description": "The materials required to construct the waypoint.",
                        "items": {
                            "$ref": "#/components/schemas/ConstructionMaterial"
                        }
                    },
                    "isComplete": {
                        "type": "boolean",
                        "description": "Whether the waypoint has been constructed."
                    }
                },
                "required": [
                    "symbol",
                    "materials",
                    "isComplete"
                ]
            },
            "ConstructionMaterial": {
                "description": "The details of the required construction materials for a given waypoint under construction.",
                "type": "object",
                "properties": {
                    "tradeSymbol": {
                        "$ref": "#/components/schemas/TradeSymbol"
                    },
                    "required": {
                        "type": "integer",
                        "description": "The number of units required."
                    },
                    "fulfilled": {
                        "type": "integer",
                        "description": "The number of units fulfilled toward the required amount."
                    }
                },
                "required": [
                    "tradeSymbol",
                    "required",
                    "fulfilled"
                ]
            },
            "Contract": {
                "description": "Contract details.",
                "type": "object",
                "properties": {
                    "id": {
                        "type": "string",
                        "minLength": 1,
                        "description": "ID of the contract."
                    },
                    "factionSymbol": {
                        "type": "string",
                        "minLength": 1,
                        "description": "The symbol of the faction that this contract is for."
                    },
                    "type": {
                        "type": "string",
                        "enum": [
                            "PROCUREMENT",
                            "TRANSPORT",
                            "SHUTTLE"
                        ],
                        "description": "Type of contract."
                    },
                    "terms": {
                        "$ref": "#/components/schemas/ContractTerms"
                    },
                    "accepted": {
                        "type": "boolean",
                        "default": false,
                        "description": "Whether the contract has been accepted by the agent"
                    },
                    "fulfilled": {
                        "type": "boolean",
                        "default": false,
                        "description": "Whether the contract has been fulfilled"
                    },
                    "expiration": {
                        "type": "string",
                        "format": "date-time",
                        "description": "Deprecated in favor of deadlineToAccept",
                        "deprecated": true
                    },
                    "deadlineToAccept": {
                        "type": "string",
                        "format": "date-time",
                        "description": "The time at which the contract is no longer available to be accepted"
                    }
                },
                "required": [
                    "id",
                    "factionSymbol",
                    "type",
                    "terms",
                    "accepted",
                    "fulfilled",
                    "expiration"
                ]
            },
            "ContractDeliverGood": {
                "description": "The details of a delivery contract. Includes the type of good, units needed, and the destination.",
                "type": "object",
                "properties": {
                    "tradeSymbol": {
                        "type": "string",
                        "description": "The symbol of the trade good to deliver.",
                        "minLength": 1
                    },
                    "destinationSymbol": {
                        "type": "string",
                        "description": "The destination where goods need to be delivered.",
                        "minLength": 1
                    },
                    "unitsRequired": {
                        "type": "integer",
                        "description": "The number of units that need to be delivered on this contract."
                    },
                    "unitsFulfilled": {
                        "type": "integer",
                        "description": "The number of units fulfilled on this contract."
                    }
                },
                "required": [
                    "tradeSymbol",
                    "destinationSymbol",
                    "unitsRequired",
                    "unitsFulfilled"
                ]
            },
            "ContractPayment": {
                "type": "object",
                "description": "Payments for the contract.",
                "properties": {
                    "onAccepted": {
                        "type": "integer",
                        "description": "The amount of credits received up front for accepting the contract."
                    },
                    "onFulfilled": {
                        "type": "integer",
                        "description": "The amount of credits received when the contract is fulfilled."
                    }
                },
                "required": [
                    "onAccepted",
                    "onFulfilled"
                ]
            },
            "ContractTerms": {
                "type": "object",
                "description": "The terms to fulfill the contract.",
                "properties": {
                    "deadline": {
                        "type": "string",
                        "format": "date-time",
                        "description": "The deadline for the contract."
                    },
                    "payment": {
                        "$ref": "#/components/schemas/ContractPayment"
                    },
                    "deliver": {
                        "type": "array",
                        "description": "The cargo that needs to be delivered to fulfill the contract.",
                        "items": {
                            "$ref": "#/components/schemas/ContractDeliverGood"
                        }
                    }
                },
                "required": [
                    "deadline",
                    "payment"
                ]
            },
            "Cooldown": {
                "type": "object",
                "description": "A cooldown is a period of time in which a ship cannot perform certain actions.",
                "properties": {
                    "shipSymbol": {
                        "type": "string",
                        "description": "The symbol of the ship that is on cooldown",
                        "minLength": 1
                    },
                    "totalSeconds": {
                        "type": "integer",
                        "description": "The total duration of the cooldown in seconds",
                        "minimum": 0
                    },
                    "remainingSeconds": {
                        "type": "integer",
                        "description": "The remaining duration of the cooldown in seconds",
                        "minimum": 0
                    },
                    "expiration": {
                        "type": "string",
                        "format": "date-time",
                        "description": "The date and time when the cooldown expires in ISO 8601 format"
                    }
                },
                "required": [
                    "shipSymbol",
                    "totalSeconds",
                    "remainingSeconds"
                ]
            },
            "Extraction": {
                "description": "Extraction details.",
                "type": "object",
                "properties": {
                    "shipSymbol": {
                        "type": "string",
                        "minLength": 1,
                        "description": "Symbol of the ship that executed the extraction."
                    },
                    "yield": {
                        "$ref": "#/components/schemas/ExtractionYield"
                    }
                },
                "required": [
                    "shipSymbol",
                    "yield"
                ]
            },
            "ExtractionYield": {
                "type": "object",
                "description": "A yield from the extraction operation.",
                "properties": {
                    "symbol": {
                        "$ref": "#/components/schemas/TradeSymbol"
                    },
                    "units": {
                        "type": "integer",
                        "description": "The number of units extracted that were placed into the ship's cargo hold."
                    }
                },
                "required": [
                    "symbol",
                    "units"
                ]
            },
            "Faction": {
                "description": "Faction details.",
                "type": "object",
                "properties": {
                    "symbol": {
                        "$ref": "#/components/schemas/FactionSymbol"
                    },
                    "name": {
                        "type": "string",
                        "minLength": 1,
                        "description": "Name of the faction."
                    },
                    "description": {
                        "type": "string",
                        "minLength": 1,
                        "description": "Description of the faction."
                    },
                    "headquarters": {
                        "type": "string",
                        "minLength": 1,
                        "description": "The waypoint in which the faction's HQ is located in."
                    },
                    "traits": {
                        "type": "array",
                        "description": "List of traits that define this faction.",
                        "items": {
                            "$ref": "#/components/schemas/FactionTrait"
                        }
                    },
                    "isRecruiting": {
                        "type": "boolean",
                        "description": "Whether or not the faction is currently recruiting new agents."
                    }
                },
                "required": [
                    "symbol",
                    "name",
                    "description",
                    "headquarters",
                    "traits",
                    "isRecruiting"
                ]
            },
            "FactionSymbol": {
                "type": "string",
                "description": "The symbol of the faction.",
                "minLength": 1,
                "enum": [
                    "COSMIC",
                    "VOID",
                    "GALACTIC",
                    "QUANTUM",
                    "DOMINION",
                    "ASTRO",
                    "CORSAIRS",
                    "OBSIDIAN",
                    "AEGIS",
                    "UNITED",
                    "SOLITARY",
                    "COBALT",
                    "OMEGA",
                    "ECHO",
                    "LORDS",
                    "CULT",
                    "ANCIENTS",
                    "SHADOW",
                    "ETHEREAL"
                ]
            },
            "FactionTrait": {
                "type": "object",
                "properties": {
                    "symbol": {
                        "$ref": "#/components/schemas/FactionTraitSymbol"
                    },
                    "name": {
                        "type": "string",
                        "description": "The name of the trait."
                    },
                    "description": {
                        "type": "string",
                        "description": "A description of the trait."
                    }
                },
                "required": [
                    "symbol",
                    "name",
                    "description"
                ]
            },
            "FactionTraitSymbol": {
                "type": "string",
                "description": "The unique identifier of the trait.",
                "enum": [
                    "BUREAUCRATIC",
                    "SECRETIVE",
                    "CAPITALISTIC",
                    "INDUSTRIOUS",
                    "PEACEFUL",
                    "DISTRUSTFUL",
                    "WELCOMING",
                    "SMUGGLERS",
                    "SCAVENGERS",
                    "REBELLIOUS",
                    "EXILES",
                    "PIRATES",
                    "RAIDERS",
                    "CLAN",
                    "GUILD",
                    "DOMINION",
                    "FRINGE",
                    "FORSAKEN",
                    "ISOLATED",
                    "LOCALIZED",
                    "ESTABLISHED",
                    "NOTABLE",
                    "DOMINANT",
                    "INESCAPABLE",
                    "INNOVATIVE",
                    "BOLD",
                    "VISIONARY",
                    "CURIOUS",
                    "DARING",
                    "EXPLORATORY",
                    "RESOURCEFUL",
                    "FLEXIBLE",
                    "COOPERATIVE",
                    "UNITED",
                    "STRATEGIC",
                    "INTELLIGENT",
                    "RESEARCH_FOCUSED",
                    "COLLABORATIVE",
                    "PROGRESSIVE",
                    "MILITARISTIC",
                    "TECHNOLOGICALLY_ADVANCED",
                    "AGGRESSIVE",
                    "IMPERIALISTIC",
                    "TREASURE_HUNTERS",
                    "DEXTEROUS",
                    "UNPREDICTABLE",
                    "BRUTAL",
                    "FLEETING",
                    "ADAPTABLE",
                    "SELF_SUFFICIENT",
                    "DEFENSIVE",
                    "PROUD",
                    "DIVERSE",
                    "INDEPENDENT",
                    "SELF_INTERESTED",
                    "FRAGMENTED",
                    "COMMERCIAL",
                    "FREE_MARKETS",
                    "ENTREPRENEURIAL"
                ]
            },
            "JumpGate": {
                "type": "object",
                "description": "",
                "properties": {
                    "symbol": {
                        "$ref": "#/components/schemas/WaypointSymbol"
                    },
                    "connections": {
                        "type": "array",
                        "description": "All the gates that are connected to this waypoint.",
                        "items": {
                            "type": "string",
                            "description": "The symbol of the waypoint that has a corresponding gate."
                        }
                    }
                },
                "required": [
                    "symbol",
                    "connections"
                ]
            },
            "Market": {
                "description": "",
                "type": "object",
                "properties": {
                    "symbol": {
                        "type": "string",
                        "description": "The symbol of the market. The symbol is the same as the waypoint where the market is located."
                    },
                    "exports": {
                        "type": "array",
                        "description": "The list of goods that are exported from this market.",
                        "items": {
                            "$ref": "#/components/schemas/TradeGood"
                        }
                    },
                    "imports": {
                        "type": "array",
                        "description": "The list of goods that are sought as imports in this market.",
                        "items": {
                            "$ref": "#/components/schemas/TradeGood"
                        }
                    },
                    "exchange": {
                        "type": "array",
                        "description": "The list of goods that are bought and sold between agents at this market.",
                        "items": {
                            "$ref": "#/components/schemas/TradeGood"
                        }
                    },
                    "transactions": {
                        "type": "array",
                        "description": "The list of recent transactions at this market. Visible only when a ship is present at the market.",
                        "items": {
                            "$ref": "#/components/schemas/MarketTransaction"
                        }
                    },
                    "tradeGoods": {
                        "type": "array",
                        "description": "The list of goods that are traded at this market. Visible only when a ship is present at the market.",
                        "items": {
                            "$ref": "#/components/schemas/MarketTradeGood"
                        }
                    }
                },
                "required": [
                    "symbol",
                    "exports",
                    "imports",
                    "exchange"
                ]
            },
            "MarketTradeGood": {
                "type": "object",
                "properties": {
                    "symbol": {
                        "$ref": "#/components/schemas/TradeSymbol"
                    },
                    "type": {
                        "type": "string",
                        "description": "The type of trade good (export, import, or exchange).",
                        "enum": [
                            "EXPORT",
                            "IMPORT",
                            "EXCHANGE"
                        ]
                    },
                    "tradeVolume": {
                        "type": "integer",
                        "description": "This is the maximum number of units that can be purchased or sold at this market in a single trade for this good. Trade volume also gives an indication of price volatility. A market with a low trade volume will have large price swings, while high trade volume will be more resilient to price changes.",
                        "minimum": 1
                    },
                    "supply": {
                        "$ref": "#/components/schemas/SupplyLevel"
                    },
                    "activity": {
                        "$ref": "#/components/schemas/ActivityLevel"
                    },
                    "purchasePrice": {
                        "type": "integer",
                        "description": "The price at which this good can be purchased from the market.",
                        "minimum": 0
                    },
                    "sellPrice": {
                        "type": "integer",
                        "description": "The price at which this good can be sold to the market.",
                        "minimum": 0
                    }
                },
                "required": [
                    "symbol",
                    "type",
                    "tradeVolume",
                    "supply",
                    "purchasePrice",
                    "sellPrice"
                ]
            },
            "MarketTransaction": {
                "type": "object",
                "properties": {
                    "waypointSymbol": {
                        "$ref": "#/components/schemas/WaypointSymbol"
                    },
                    "shipSymbol": {
                        "type": "string",
                        "description": "The symbol of the ship that made the transaction."
                    },
                    "tradeSymbol": {
                        "type": "string",
                        "description": "The symbol of the trade good."
                    },
                    "type": {
                        "type": "string",
                        "description": "The type of transaction.",
                        "enum": [
                            "PURCHASE",
                            "SELL"
                        ]
                    },
                    "units": {
                        "type": "integer",
                        "description": "The number of units of the transaction.",
                        "minimum": 0
                    },
                    "pricePerUnit": {
                        "type": "integer",
                        "description": "The price per unit of the transaction.",
                        "minimum": 0
                    },
                    "totalPrice": {
                        "type": "integer",
                        "description": "The total price of the transaction.",
                        "minimum": 0
                    },
                    "timestamp": {
                        "type": "string",
                        "format": "date-time",
                        "description": "The timestamp of the transaction."
                    }
                },
                "required": [
                    "waypointSymbol",
                    "shipSymbol",
                    "tradeSymbol",
                    "type",
                    "units",
                    "pricePerUnit",
                    "totalPrice",
                    "timestamp"
                ],
                "description": "Result of a transaction with a market."
            },
            "Meta": {
                "description": "Meta details for pagination.",
                "type": "object",
                "x-examples": {
                    "example-1": {
                        "total": 6,
                        "page": 1,
                        "limit": 20
                    }
                },
                "properties": {
                    "total": {
                        "type": "integer",
                        "description": "Shows the total amount of items of this kind that exist.",
                        "minimum": 0
                    },
                    "page": {
                        "type": "integer",
                        "default": 1,
                        "description": "A page denotes an amount of items, offset from the first item. Each page holds an amount of items equal to the `limit`.",
                        "minimum": 1
                    },
                    "limit": {
                        "type": "integer",
                        "default": 10,
                        "description": "The amount of items in each page. Limits how many items can be fetched at once.",
                        "minimum": 1,
                        "maximum": 20
                    }
                },
                "required": [
                    "total",
                    "page",
                    "limit"
                ]
            },
            "RepairTransaction": {
                "type": "object",
                "properties": {
                    "waypointSymbol": {
                        "$ref": "#/components/schemas/WaypointSymbol"
                    },
                    "shipSymbol": {
                        "type": "string",
                        "description": "The symbol of the ship."
                    },
                    "totalPrice": {
                        "type": "integer",
                        "description": "The total price of the transaction.",
                        "minimum": 0
                    },
                    "timestamp": {
                        "type": "string",
                        "format": "date-time",
                        "description": "The timestamp of the transaction."
                    }
                },
                "required": [
                    "waypointSymbol",
                    "shipSymbol",
                    "totalPrice",
                    "timestamp"
                ],
                "description": "Result of a repair transaction."
            },
            "ScannedShip": {
                "description": "The ship that was scanned. Details include information about the ship that could be detected by the scanner.",
                "type": "object",
                "properties": {
                    "symbol": {
                        "type": "string",
                        "description": "The globally unique identifier of the ship."
                    },
                    "registration": {
                        "$ref": "#/components/schemas/ShipRegistration"
                    },
                    "nav": {
                        "$ref": "#/components/schemas/ShipNav"
                    },
                    "frame": {
                        "type": "object",
                        "description": "The frame of the ship.",
                        "properties": {
                            "symbol": {
                                "type": "string",
                                "description": "The symbol of the frame."
                            }
                        },
                        "required": [
                            "symbol"
                        ]
                    },
                    "reactor": {
                        "type": "object",
                        "description": "The reactor of the ship.",
                        "properties": {
                            "symbol": {
                                "type": "string",
                                "description": "The symbol of the reactor."
                            }
                        },
                        "required": [
                            "symbol"
                        ]
                    },
                    "engine": {
                        "type": "object",
                        "description": "The engine of the ship.",
                        "required": [
                            "symbol"
                        ],
                        "properties": {
                            "symbol": {
                                "type": "string",
                                "description": "The symbol of the engine."
                            }
                        }
                    },
                    "mounts": {
                        "type": "array",
                        "description": "List of mounts installed in the ship.",
                        "items": {
                            "type": "object",
                            "description": "A mount on the ship.",
                            "properties": {
                                "symbol": {
                                    "type": "string",
                                    "description": "The symbol of the mount."
                                }
                            },
                            "required": [
                                "symbol"
                            ]
                        }
                    }
                },
                "required": [
                    "symbol",
                    "registration",
                    "nav",
                    "engine"
                ]
            },
            "ScannedSystem": {
                "description": "Details of a system was that scanned.",
                "type": "object",
                "properties": {
                    "symbol": {
                        "type": "string",
                        "minLength": 1,
                        "description": "Symbol of the system."
                    },
                    "sectorSymbol": {
                        "type": "string",
                        "minLength": 1,
                        "description": "Symbol of the system's sector."
                    },
                    "type": {
                        "$ref": "#/components/schemas/SystemType"
                    },
                    "x": {
                        "type": "integer",
                        "description": "Position in the universe in the x axis."
                    },
                    "y": {
                        "type": "integer",
                        "description": "Position in the universe in the y axis."
                    },
                    "distance": {
                        "type": "integer",
                        "description": "The system's distance from the scanning ship."
                    }
                },
                "required": [
                    "symbol",
                    "sectorSymbol",
                    "type",
                    "x",
                    "y",
                    "distance"
                ]
            },
            "ScannedWaypoint": {
                "description": "A waypoint that was scanned by a ship.",
                "type": "object",
                "properties": {
                    "symbol": {
                        "$ref": "#/components/schemas/WaypointSymbol"
                    },
                    "type": {
                        "$ref": "#/components/schemas/WaypointType"
                    },
                    "systemSymbol": {
                        "$ref": "#/components/schemas/SystemSymbol"
                    },
                    "x": {
                        "type": "integer",
                        "description": "Position in the universe in the x axis."
                    },
                    "y": {
                        "type": "integer",
                        "description": "Position in the universe in the y axis."
                    },
                    "orbitals": {
                        "type": "array",
                        "description": "List of waypoints that orbit this waypoint.",
                        "items": {
                            "$ref": "#/components/schemas/WaypointOrbital"
                        }
                    },
                    "faction": {
                        "$ref": "#/components/schemas/WaypointFaction"
                    },
                    "traits": {
                        "type": "array",
                        "description": "The traits of the waypoint.",
                        "items": {
                            "$ref": "#/components/schemas/WaypointTrait"
                        }
                    },
                    "chart": {
                        "$ref": "#/components/schemas/Chart"
                    }
                },
                "required": [
                    "symbol",
                    "type",
                    "systemSymbol",
                    "x",
                    "y",
                    "orbitals",
                    "traits"
                ]
            },
            "ScrapTransaction": {
                "type": "object",
                "properties": {
                    "waypointSymbol": {
                        "$ref": "#/components/schemas/WaypointSymbol"
                    },
                    "shipSymbol": {
                        "type": "string",
                        "description": "The symbol of the ship."
                    },
                    "totalPrice": {
                        "type": "integer",
                        "description": "The total price of the transaction.",
                        "minimum": 0
                    },
                    "timestamp": {
                        "type": "string",
                        "format": "date-time",
                        "description": "The timestamp of the transaction."
                    }
                },
                "required": [
                    "waypointSymbol",
                    "shipSymbol",
                    "totalPrice",
                    "timestamp"
                ],
                "description": "Result of a scrap transaction."
            },
            "Ship": {
                "description": "Ship details.",
                "type": "object",
                "properties": {
                    "symbol": {
                        "type": "string",
                        "description": "The globally unique identifier of the ship in the following format: `[AGENT_SYMBOL]-[HEX_ID]`"
                    },
                    "registration": {
                        "$ref": "#/components/schemas/ShipRegistration"
                    },
                    "nav": {
                        "$ref": "#/components/schemas/ShipNav"
                    },
                    "crew": {
                        "$ref": "#/components/schemas/ShipCrew"
                    },
                    "frame": {
                        "$ref": "#/components/schemas/ShipFrame"
                    },
                    "reactor": {
                        "$ref": "#/components/schemas/ShipReactor"
                    },
                    "engine": {
                        "$ref": "#/components/schemas/ShipEngine"
                    },
                    "cooldown": {
                        "$ref": "#/components/schemas/Cooldown"
                    },
                    "modules": {
                        "type": "array",
                        "description": "Modules installed in this ship.",
                        "items": {
                            "$ref": "#/components/schemas/ShipModule"
                        }
                    },
                    "mounts": {
                        "type": "array",
                        "description": "Mounts installed in this ship.",
                        "items": {
                            "$ref": "#/components/schemas/ShipMount"
                        }
                    },
                    "cargo": {
                        "$ref": "#/components/schemas/ShipCargo"
                    },
                    "fuel": {
                        "$ref": "#/components/schemas/ShipFuel"
                    }
                },
                "required": [
                    "symbol",
                    "registration",
                    "nav",
                    "crew",
                    "frame",
                    "reactor",
                    "engine",
                    "modules",
                    "mounts",
                    "cargo",
                    "fuel",
                    "cooldown"
                ]
            },
            "ShipCargo": {
                "type": "object",
                "properties": {
                    "capacity": {
                        "type": "integer",
                        "description": "The max number of items that can be stored in the cargo hold.",
                        "minimum": 0
                    },
                    "units": {
                        "type": "integer",
                        "description": "The number of items currently stored in the cargo hold.",
                        "minimum": 0
                    },
                    "inventory": {
                        "type": "array",
                        "description": "The items currently in the cargo hold.",
                        "items": {
                            "$ref": "#/components/schemas/ShipCargoItem"
                        }
                    }
                },
                "required": [
                    "capacity",
                    "units",
                    "inventory"
                ],
                "description": "Ship cargo details."
            },
            "ShipCargoItem": {
                "type": "object",
                "description": "The type of cargo item and the number of units.",
                "properties": {
                    "symbol": {
                        "$ref": "#/components/schemas/TradeSymbol"
                    },
                    "name": {
                        "type": "string",
                        "description": "The name of the cargo item type."
                    },
                    "description": {
                        "type": "string",
                        "description": "The description of the cargo item type."
                    },
                    "units": {
                        "type": "integer",
                        "description": "The number of units of the cargo item.",
                        "minimum": 1
                    }
                },
                "required": [
                    "symbol",
                    "name",
                    "description",
                    "units"
                ]
            },
            "ShipComponentCondition": {
                "type": "number",
                "format": "double",
                "description": "The repairable condition of a component. A value of 0 indicates the component needs significant repairs, while a value of 1 indicates the component is in near perfect condition. As the condition of a component is repaired, the overall integrity of the component decreases.",
                "minimum": 0,
                "maximum": 1
            },
            "ShipComponentIntegrity": {
                "type": "number",
                "format": "double",
                "description": "The overall integrity of the component, which determines the performance of the component. A value of 0 indicates that the component is almost completely degraded, while a value of 1 indicates that the component is in near perfect condition. The integrity of the component is non-repairable, and represents permanent wear over time.",
                "minimum": 0,
                "maximum": 1
            },
            "ShipConditionEvent": {
                "type": "object",
                "description": "An event that represents damage or wear to a ship's reactor, frame, or engine, reducing the condition of the ship.",
                "properties": {
                    "symbol": {
                        "type": "string",
                        "enum": [
                            "REACTOR_OVERLOAD",
                            "ENERGY_SPIKE_FROM_MINERAL",
                            "SOLAR_FLARE_INTERFERENCE",
                            "COOLANT_LEAK",
                            "POWER_DISTRIBUTION_FLUCTUATION",
                            "MAGNETIC_FIELD_DISRUPTION",
                            "HULL_MICROMETEORITE_STRIKES",
                            "STRUCTURAL_STRESS_FRACTURES",
                            "CORROSIVE_MINERAL_CONTAMINATION",
                            "THERMAL_EXPANSION_MISMATCH",
                            "VIBRATION_DAMAGE_FROM_DRILLING",
                            "ELECTROMAGNETIC_FIELD_INTERFERENCE",
                            "IMPACT_WITH_EXTRACTED_DEBRIS",
                            "FUEL_EFFICIENCY_DEGRADATION",
                            "COOLANT_SYSTEM_AGEING",
                            "DUST_MICROABRASIONS",
                            "THRUSTER_NOZZLE_WEAR",
                            "EXHAUST_PORT_CLOGGING",
                            "BEARING_LUBRICATION_FADE",
                            "SENSOR_CALIBRATION_DRIFT",
                            "HULL_MICROMETEORITE_DAMAGE",
                            "SPACE_DEBRIS_COLLISION",
                            "THERMAL_STRESS",
                            "VIBRATION_OVERLOAD",
                            "PRESSURE_DIFFERENTIAL_STRESS",
                            "ELECTROMAGNETIC_SURGE_EFFECTS",
                            "ATMOSPHERIC_ENTRY_HEAT"
                        ]
                    },
                    "component": {
                        "type": "string",
                        "enum": [
                            "FRAME",
                            "REACTOR",
                            "ENGINE"
                        ]
                    },
                    "name": {
                        "type": "string",
                        "description": "The name of the event."
                    },
                    "description": {
                        "type": "string",
                        "description": "A description of the event."
                    }
                },
                "required": [
                    "symbol",
                    "component",
                    "name",
                    "description"
                ]
            },
            "ShipCrew": {
                "type": "object",
                "description": "The ship's crew service and maintain the ship's systems and equipment.",
                "properties": {
                    "current": {
                        "type": "integer",
                        "description": "The current number of crew members on the ship."
                    },
                    "required": {
                        "type": "integer",
                        "description": "The minimum number of crew members required to maintain the ship."
                    },
                    "capacity": {
                        "type": "integer",
                        "description": "The maximum number of crew members the ship can support."
                    },
                    "rotation": {
                        "type": "string",
                        "description": "The rotation of crew shifts. A stricter shift improves the ship's performance. A more relaxed shift improves the crew's morale.",
                        "enum": [
                            "STRICT",
                            "RELAXED"
                        ],
                        "default": "STRICT"
                    },
                    "morale": {
                        "type": "integer",
                        "description": "A rough measure of the crew's morale. A higher morale means the crew is happier and more productive. A lower morale means the ship is more prone to accidents.",
                        "minimum": 0,
                        "maximum": 100
                    },
                    "wages": {
                        "type": "integer",
                        "description": "The amount of credits per crew member paid per hour. Wages are paid when a ship docks at a civilized waypoint.",
                        "minimum": 0
                    }
                },
                "required": [
                    "current",
                    "required",
                    "capacity",
                    "rotation",
                    "morale",
                    "wages"
                ]
            },
            "ShipEngine": {
                "type": "object",
                "description": "The engine determines how quickly a ship travels between waypoints.",
                "properties": {
                    "symbol": {
                        "type": "string",
                        "enum": [
                            "ENGINE_IMPULSE_DRIVE_I",
                            "ENGINE_ION_DRIVE_I",
                            "ENGINE_ION_DRIVE_II",
                            "ENGINE_HYPER_DRIVE_I"
                        ],
                        "description": "The symbol of the engine."
                    },
                    "name": {
                        "type": "string",
                        "description": "The name of the engine."
                    },
                    "description": {
                        "type": "string",
                        "description": "The description of the engine."
                    },
                    "condition": {
                        "$ref": "#/components/schemas/ShipComponentCondition"
                    },
                    "integrity": {
                        "$ref": "#/components/schemas/ShipComponentIntegrity"
                    },
                    "speed": {
                        "type": "integer",
                        "minimum": 1,
                        "description": "The speed stat of this engine. The higher the speed, the faster a ship can travel from one point to another. Reduces the time of arrival when navigating the ship."
                    },
                    "requirements": {
                        "$ref": "#/components/schemas/ShipRequirements"
                    }
                },
                "required": [
                    "symbol",
                    "name",
                    "condition",
                    "integrity",
                    "description",
                    "speed",
                    "requirements"
                ]
            },
            "ShipFrame": {
                "type": "object",
                "description": "The frame of the ship. The frame determines the number of modules and mounting points of the ship, as well as base fuel capacity. As the condition of the frame takes more wear, the ship will become more sluggish and less maneuverable.",
                "properties": {
                    "symbol": {
                        "type": "string",
                        "enum": [
                            "FRAME_PROBE",
                            "FRAME_DRONE",
                            "FRAME_INTERCEPTOR",
                            "FRAME_RACER",
                            "FRAME_FIGHTER",
                            "FRAME_FRIGATE",
                            "FRAME_SHUTTLE",
                            "FRAME_EXPLORER",
                            "FRAME_MINER",
                            "FRAME_LIGHT_FREIGHTER",
                            "FRAME_HEAVY_FREIGHTER",
                            "FRAME_TRANSPORT",
                            "FRAME_DESTROYER",
                            "FRAME_CRUISER",
                            "FRAME_CARRIER"
                        ],
                        "description": "Symbol of the frame."
                    },
                    "name": {
                        "type": "string",
                        "description": "Name of the frame."
                    },
                    "description": {
                        "type": "string",
                        "description": "Description of the frame."
                    },
                    "condition": {
                        "$ref": "#/components/schemas/ShipComponentCondition"
                    },
                    "integrity": {
                        "$ref": "#/components/schemas/ShipComponentIntegrity"
                    },
                    "moduleSlots": {
                        "type": "integer",
                        "minimum": 0,
                        "description": "The amount of slots that can be dedicated to modules installed in the ship. Each installed module take up a number of slots, and once there are no more slots, no new modules can be installed."
                    },
                    "mountingPoints": {
                        "type": "integer",
                        "minimum": 0,
                        "description": "The amount of slots that can be dedicated to mounts installed in the ship. Each installed mount takes up a number of points, and once there are no more points remaining, no new mounts can be installed."
                    },
                    "fuelCapacity": {
                        "type": "integer",
                        "minimum": 0,
                        "description": "The maximum amount of fuel that can be stored in this ship. When refueling, the ship will be refueled to this amount."
                    },
                    "requirements": {
                        "$ref": "#/components/schemas/ShipRequirements"
                    }
                },
                "required": [
                    "symbol",
                    "name",
                    "condition",
                    "integrity",
                    "description",
                    "moduleSlots",
                    "mountingPoints",
                    "fuelCapacity",
                    "requirements"
                ]
            },
            "ShipFuel": {
                "type": "object",
                "description": "Details of the ship's fuel tanks including how much fuel was consumed during the last transit or action.",
                "properties": {
                    "current": {
                        "type": "integer",
                        "description": "The current amount of fuel in the ship's tanks.",
                        "minimum": 0
                    },
                    "capacity": {
                        "type": "integer",
                        "description": "The maximum amount of fuel the ship's tanks can hold.",
                        "minimum": 0
                    },
                    "consumed": {
                        "type": "object",
                        "description": "An object that only shows up when an action has consumed fuel in the process. Shows the fuel consumption data.",
                        "properties": {
                            "amount": {
                                "type": "integer",
                                "description": "The amount of fuel consumed by the most recent transit or action.",
                                "minimum": 0
                            },
                            "timestamp": {
                                "type": "string",
                                "format": "date-time",
                                "description": "The time at which the fuel was consumed."
                            }
                        },
                        "required": [
                            "amount",
                            "timestamp"
                        ]
                    }
                },
                "required": [
                    "current",
                    "capacity"
                ]
            },
            "ShipModificationTransaction": {
                "type": "object",
                "properties": {
                    "waypointSymbol": {
                        "type": "string",
                        "description": "The symbol of the waypoint where the transaction took place."
                    },
                    "shipSymbol": {
                        "type": "string",
                        "description": "The symbol of the ship that made the transaction."
                    },
                    "tradeSymbol": {
                        "type": "string",
                        "description": "The symbol of the trade good."
                    },
                    "totalPrice": {
                        "type": "integer",
                        "description": "The total price of the transaction.",
                        "minimum": 0
                    },
                    "timestamp": {
                        "type": "string",
                        "format": "date-time",
                        "description": "The timestamp of the transaction."
                    }
                },
                "required": [
                    "waypointSymbol",
                    "shipSymbol",
                    "tradeSymbol",
                    "totalPrice",
                    "timestamp"
                ],
                "description": "Result of a transaction for a ship modification, such as installing a mount or a module."
            },
            "ShipModule": {
                "type": "object",
                "description": "A module can be installed in a ship and provides a set of capabilities such as storage space or quarters for crew. Module installations are permanent.",
                "properties": {
                    "symbol": {
                        "type": "string",
                        "enum": [
                            "MODULE_MINERAL_PROCESSOR_I",
                            "MODULE_GAS_PROCESSOR_I",
                            "MODULE_CARGO_HOLD_I",
                            "MODULE_CARGO_HOLD_II",
                            "MODULE_CARGO_HOLD_III",
                            "MODULE_CREW_QUARTERS_I",
                            "MODULE_ENVOY_QUARTERS_I",
                            "MODULE_PASSENGER_CABIN_I",
                            "MODULE_MICRO_REFINERY_I",
                            "MODULE_ORE_REFINERY_I",
                            "MODULE_FUEL_REFINERY_I",
                            "MODULE_SCIENCE_LAB_I",
                            "MODULE_JUMP_DRIVE_I",
                            "MODULE_JUMP_DRIVE_II",
                            "MODULE_JUMP_DRIVE_III",
                            "MODULE_WARP_DRIVE_I",
                            "MODULE_WARP_DRIVE_II",
                            "MODULE_WARP_DRIVE_III",
                            "MODULE_SHIELD_GENERATOR_I",
                            "MODULE_SHIELD_GENERATOR_II"
                        ],
                        "description": "The symbol of the module."
                    },
                    "capacity": {
                        "type": "integer",
                        "minimum": 0,
                        "description": "Modules that provide capacity, such as cargo hold or crew quarters will show this value to denote how much of a bonus the module grants."
                    },
                    "range": {
                        "type": "integer",
                        "minimum": 0,
                        "description": "Modules that have a range will such as a sensor array show this value to denote how far can the module reach with its capabilities."
                    },
                    "name": {
                        "type": "string",
                        "description": "Name of this module."
                    },
                    "description": {
                        "type": "string",
                        "description": "Description of this module."
                    },
                    "requirements": {
                        "$ref": "#/components/schemas/ShipRequirements"
                    }
                },
                "required": [
                    "symbol",
                    "name",
                    "description",
                    "requirements"
                ]
            },
            "ShipMount": {
                "type": "object",
                "description": "A mount is installed on the exterier of a ship.",
                "properties": {
                    "symbol": {
                        "type": "string",
                        "enum": [
                            "MOUNT_GAS_SIPHON_I",
                            "MOUNT_GAS_SIPHON_II",
                            "MOUNT_GAS_SIPHON_III",
                            "MOUNT_SURVEYOR_I",
                            "MOUNT_SURVEYOR_II",
                            "MOUNT_SURVEYOR_III",
                            "MOUNT_SENSOR_ARRAY_I",
                            "MOUNT_SENSOR_ARRAY_II",
                            "MOUNT_SENSOR_ARRAY_III",
                            "MOUNT_MINING_LASER_I",
                            "MOUNT_MINING_LASER_II",
                            "MOUNT_MINING_LASER_III",
                            "MOUNT_LASER_CANNON_I",
                            "MOUNT_MISSILE_LAUNCHER_I",
                            "MOUNT_TURRET_I"
                        ],
                        "description": "Symbo of this mount."
                    },
                    "name": {
                        "type": "string",
                        "description": "Name of this mount."
                    },
                    "description": {
                        "type": "string",
                        "description": "Description of this mount."
                    },
                    "strength": {
                        "type": "integer",
                        "minimum": 0,
                        "description": "Mounts that have this value, such as mining lasers, denote how powerful this mount's capabilities are."
                    },
                    "deposits": {
                        "type": "array",
                        "description": "Mounts that have this value denote what goods can be produced from using the mount.",
                        "items": {
                            "type": "string",
                            "enum": [
                                "QUARTZ_SAND",
                                "SILICON_CRYSTALS",
                                "PRECIOUS_STONES",
                                "ICE_WATER",
                                "AMMONIA_ICE",
                                "IRON_ORE",
                                "COPPER_ORE",
                                "SILVER_ORE",
                                "ALUMINUM_ORE",
                                "GOLD_ORE",
                                "PLATINUM_ORE",
                                "DIAMONDS",
                                "URANITE_ORE",
                                "MERITIUM_ORE"
                            ]
                        }
                    },
                    "requirements": {
                        "$ref": "#/components/schemas/ShipRequirements"
                    }
                },
                "required": [
                    "symbol",
                    "name",
                    "requirements"
                ]
            },
            "ShipNav": {
                "type": "object",
                "description": "The navigation information of the ship.",
                "properties": {
                    "systemSymbol": {
                        "$ref": "#/components/schemas/SystemSymbol"
                    },
                    "waypointSymbol": {
                        "$ref": "#/components/schemas/WaypointSymbol"
                    },
                    "route": {
                        "$ref": "#/components/schemas/ShipNavRoute"
                    },
                    "status": {
                        "$ref": "#/components/schemas/ShipNavStatus"
                    },
                    "flightMode": {
                        "$ref": "#/components/schemas/ShipNavFlightMode"
                    }
                },
                "required": [
                    "systemSymbol",
                    "waypointSymbol",
                    "route",
                    "status",
                    "flightMode"
                ]
            },
            "ShipNavFlightMode": {
                "type": "string",
                "description": "The ship's set speed when traveling between waypoints or systems.",
                "enum": [
                    "DRIFT",
                    "STEALTH",
                    "CRUISE",
                    "BURN"
                ],
                "default": "CRUISE"
            },
            "ShipNavRoute": {
                "type": "object",
                "description": "The routing information for the ship's most recent transit or current location.",
                "properties": {
                    "destination": {
                        "$ref": "#/components/schemas/ShipNavRouteWaypoint"
                    },
                    "origin": {
                        "$ref": "#/components/schemas/ShipNavRouteWaypoint"
                    },
                    "departureTime": {
                        "type": "string",
                        "format": "date-time",
                        "description": "The date time of the ship's departure."
                    },
                    "arrival": {
                        "type": "string",
                        "format": "date-time",
                        "description": "The date time of the ship's arrival. If the ship is in-transit, this is the expected time of arrival."
                    }
                },
                "required": [
                    "destination",
                    "departure",
                    "origin",
                    "departureTime",
                    "arrival"
                ]
            },
            "ShipNavRouteWaypoint": {
                "description": "The destination or departure of a ships nav route.",
                "type": "object",
                "properties": {
                    "symbol": {
                        "type": "string",
                        "minLength": 1,
                        "description": "The symbol of the waypoint."
                    },
                    "type": {
                        "$ref": "#/components/schemas/WaypointType"
                    },
                    "systemSymbol": {
                        "$ref": "#/components/schemas/SystemSymbol"
                    },
                    "x": {
                        "type": "integer",
                        "description": "Position in the universe in the x axis."
                    },
                    "y": {
                        "type": "integer",
                        "description": "Position in the universe in the y axis."
                    }
                },
                "required": [
                    "symbol",
                    "type",
                    "systemSymbol",
                    "x",
                    "y"
                ]
            },
            "ShipNavStatus": {
                "type": "string",
                "description": "The current status of the ship",
                "enum": [
                    "IN_TRANSIT",
                    "IN_ORBIT",
                    "DOCKED"
                ]
            },
            "ShipReactor": {
                "type": "object",
                "description": "The reactor of the ship. The reactor is responsible for powering the ship's systems and weapons.",
                "properties": {
                    "symbol": {
                        "type": "string",
                        "enum": [
                            "REACTOR_SOLAR_I",
                            "REACTOR_FUSION_I",
                            "REACTOR_FISSION_I",
                            "REACTOR_CHEMICAL_I",
                            "REACTOR_ANTIMATTER_I"
                        ],
                        "description": "Symbol of the reactor."
                    },
                    "name": {
                        "type": "string",
                        "description": "Name of the reactor."
                    },
                    "description": {
                        "type": "string",
                        "description": "Description of the reactor."
                    },
                    "condition": {
                        "$ref": "#/components/schemas/ShipComponentCondition"
                    },
                    "integrity": {
                        "$ref": "#/components/schemas/ShipComponentIntegrity"
                    },
                    "powerOutput": {
                        "type": "integer",
                        "minimum": 1,
                        "description": "The amount of power provided by this reactor. The more power a reactor provides to the ship, the lower the cooldown it gets when using a module or mount that taxes the ship's power."
                    },
                    "requirements": {
                        "$ref": "#/components/schemas/ShipRequirements"
                    }
                },
                "required": [
                    "symbol",
                    "name",
                    "condition",
                    "integrity",
                    "description",
                    "powerOutput",
                    "requirements"
                ]
            },
            "ShipRegistration": {
                "type": "object",
                "description": "The public registration information of the ship",
                "properties": {
                    "name": {
                        "type": "string",
                        "description": "The agent's registered name of the ship",
                        "minLength": 1
                    },
                    "factionSymbol": {
                        "type": "string",
                        "description": "The symbol of the faction the ship is registered with",
                        "minLength": 1
                    },
                    "role": {
                        "$ref": "#/components/schemas/ShipRole"
                    }
                },
                "required": [
                    "name",
                    "factionSymbol",
                    "role"
                ]
            },
            "ShipRequirements": {
                "type": "object",
                "description": "The requirements for installation on a ship",
                "properties": {
                    "power": {
                        "type": "integer",
                        "description": "The amount of power required from the reactor."
                    },
                    "crew": {
                        "type": "integer",
                        "description": "The number of crew required for operation."
                    },
                    "slots": {
                        "type": "integer",
                        "description": "The number of module slots required for installation."
                    }
                }
            },
            "ShipRole": {
                "type": "string",
                "description": "The registered role of the ship",
                "enum": [
                    "FABRICATOR",
                    "HARVESTER",
                    "HAULER",
                    "INTERCEPTOR",
                    "EXCAVATOR",
                    "TRANSPORT",
                    "REPAIR",
                    "SURVEYOR",
                    "COMMAND",
                    "CARRIER",
                    "PATROL",
                    "SATELLITE",
                    "EXPLORER",
                    "REFINERY"
                ]
            },
            "ShipType": {
                "description": "Type of ship",
                "type": "string",
                "enum": [
                    "SHIP_PROBE",
                    "SHIP_MINING_DRONE",
                    "SHIP_SIPHON_DRONE",
                    "SHIP_INTERCEPTOR",
                    "SHIP_LIGHT_HAULER",
                    "SHIP_COMMAND_FRIGATE",
                    "SHIP_EXPLORER",
                    "SHIP_HEAVY_FREIGHTER",
                    "SHIP_LIGHT_SHUTTLE",
                    "SHIP_ORE_HOUND",
                    "SHIP_REFINING_FREIGHTER",
                    "SHIP_SURVEYOR"
                ]
            },
            "Shipyard": {
                "description": "",
                "type": "object",
                "properties": {
                    "symbol": {
                        "type": "string",
                        "description": "The symbol of the shipyard. The symbol is the same as the waypoint where the shipyard is located.",
                        "minLength": 1
                    },
                    "shipTypes": {
                        "type": "array",
                        "description": "The list of ship types available for purchase at this shipyard.",
                        "items": {
                            "type": "object",
                            "properties": {
                                "type": {
                                    "$ref": "#/components/schemas/ShipType"
                                }
                            },
                            "required": [
                                "type"
                            ]
                        }
                    },
                    "transactions": {
                        "type": "array",
                        "description": "The list of recent transactions at this shipyard.",
                        "items": {
                            "$ref": "#/components/schemas/ShipyardTransaction"
                        }
                    },
                    "ships": {
                        "type": "array",
                        "description": "The ships that are currently available for purchase at the shipyard.",
                        "items": {
                            "$ref": "#/components/schemas/ShipyardShip"
                        }
                    },
                    "modificationsFee": {
                        "type": "integer",
                        "description": "The fee to modify a ship at this shipyard. This includes installing or removing modules and mounts on a ship. In the case of mounts, the fee is a flat rate per mount. In the case of modules, the fee is per slot the module occupies."
                    }
                },
                "required": [
                    "symbol",
                    "shipTypes",
                    "modificationsFee"
                ]
            },
            "ShipyardShip": {
                "description": "",
                "type": "object",
                "properties": {
                    "type": {
                        "$ref": "#/components/schemas/ShipType"
                    },
                    "name": {
                        "type": "string"
                    },
                    "description": {
                        "type": "string"
                    },
                    "supply": {
                        "$ref": "#/components/schemas/SupplyLevel"
                    },
                    "activity": {
                        "$ref": "#/components/schemas/ActivityLevel"
                    },
                    "purchasePrice": {
                        "type": "integer"
                    },
                    "frame": {
                        "$ref": "#/components/schemas/ShipFrame"
                    },
                    "reactor": {
                        "$ref": "#/components/schemas/ShipReactor"
                    },
                    "engine": {
                        "$ref": "#/components/schemas/ShipEngine"
                    },
                    "modules": {
                        "type": "array",
                        "items": {
                            "$ref": "#/components/schemas/ShipModule"
                        }
                    },
                    "mounts": {
                        "type": "array",
                        "items": {
                            "$ref": "#/components/schemas/ShipMount"
                        }
                    },
                    "crew": {
                        "type": "object",
                        "properties": {
                            "required": {
                                "type": "integer"
                            },
                            "capacity": {
                                "type": "integer"
                            }
                        },
                        "required": [
                            "required",
                            "capacity"
                        ]
                    }
                },
                "required": [
                    "type",
                    "symbol",
                    "name",
                    "description",
                    "supply",
                    "purchasePrice",
                    "frame",
                    "reactor",
                    "engine",
                    "modules",
                    "mounts",
                    "crew"
                ]
            },
            "ShipyardTransaction": {
                "type": "object",
                "description": "Results of a transaction with a shipyard.",
                "properties": {
                    "waypointSymbol": {
                        "$ref": "#/components/schemas/WaypointSymbol"
                    },
                    "shipSymbol": {
                        "type": "string",
                        "deprecated": true,
                        "description": "The symbol of the ship that was the subject of the transaction."
                    },
                    "shipType": {
                        "type": "string",
                        "description": "The symbol of the ship that was the subject of the transaction."
                    },
                    "price": {
                        "type": "integer",
                        "description": "The price of the transaction.",
                        "minimum": 0
                    },
                    "agentSymbol": {
                        "type": "string",
                        "description": "The symbol of the agent that made the transaction."
                    },
                    "timestamp": {
                        "type": "string",
                        "format": "date-time",
                        "description": "The timestamp of the transaction."
                    }
                },
                "required": [
                    "waypointSymbol",
                    "shipSymbol",
                    "shipType",
                    "price",
                    "agentSymbol",
                    "timestamp"
                ]
            },
            "Siphon": {
                "description": "Siphon details.",
                "type": "object",
                "properties": {
                    "shipSymbol": {
                        "type": "string",
                        "minLength": 1,
                        "description": "Symbol of the ship that executed the siphon."
                    },
                    "yield": {
                        "$ref": "#/components/schemas/SiphonYield"
                    }
                },
                "required": [
                    "shipSymbol",
                    "yield"
                ]
            },
            "SiphonYield": {
                "type": "object",
                "description": "A yield from the siphon operation.",
                "properties": {
                    "symbol": {
                        "$ref": "#/components/schemas/TradeSymbol"
                    },
                    "units": {
                        "type": "integer",
                        "description": "The number of units siphoned that were placed into the ship's cargo hold."
                    }
                },
                "required": [
                    "symbol",
                    "units"
                ]
            },
            "SupplyLevel": {
                "type": "string",
                "description": "The supply level of a trade good.",
                "enum": [
                    "SCARCE",
                    "LIMITED",
                    "MODERATE",
                    "HIGH",
                    "ABUNDANT"
                ]
            },
            "Survey": {
                "description": "A resource survey of a waypoint, detailing a specific extraction location and the types of resources that can be found there.",
                "type": "object",
                "properties": {
                    "signature": {
                        "type": "string",
                        "description": "A unique signature for the location of this survey. This signature is verified when attempting an extraction using this survey.",
                        "minLength": 1
                    },
                    "symbol": {
                        "type": "string",
                        "description": "The symbol of the waypoint that this survey is for.",
                        "minLength": 1
                    },
                    "deposits": {
                        "type": "array",
                        "description": "A list of deposits that can be found at this location. A ship will extract one of these deposits when using this survey in an extraction request. If multiple deposits of the same type are present, the chance of extracting that deposit is increased.",
                        "items": {
                            "$ref": "#/components/schemas/SurveyDeposit"
                        }
                    },
                    "expiration": {
                        "type": "string",
                        "format": "date-time",
                        "description": "The date and time when the survey expires. After this date and time, the survey will no longer be available for extraction."
                    },
                    "size": {
                        "type": "string",
                        "description": "The size of the deposit. This value indicates how much can be extracted from the survey before it is exhausted.",
                        "enum": [
                            "SMALL",
                            "MODERATE",
                            "LARGE"
                        ]
                    }
                },
                "required": [
                    "signature",
                    "symbol",
                    "deposits",
                    "expiration",
                    "size"
                ]
            },
            "SurveyDeposit": {
                "type": "object",
                "description": "A surveyed deposit of a mineral or resource available for extraction.",
                "properties": {
                    "symbol": {
                        "type": "string",
                        "description": "The symbol of the deposit."
                    }
                },
                "required": [
                    "symbol"
                ]
            },
            "System": {
                "type": "object",
                "properties": {
                    "symbol": {
                        "type": "string",
                        "minLength": 1,
                        "description": "The symbol of the system."
                    },
                    "sectorSymbol": {
                        "type": "string",
                        "minLength": 1,
                        "description": "The symbol of the sector."
                    },
                    "type": {
                        "$ref": "#/components/schemas/SystemType"
                    },
                    "x": {
                        "type": "integer",
                        "description": "Relative position of the system in the sector in the x axis."
                    },
                    "y": {
                        "type": "integer",
                        "description": "Relative position of the system in the sector in the y axis."
                    },
                    "waypoints": {
                        "type": "array",
                        "description": "Waypoints in this system.",
                        "items": {
                            "$ref": "#/components/schemas/SystemWaypoint"
                        }
                    },
                    "factions": {
                        "type": "array",
                        "description": "Factions that control this system.",
                        "items": {
                            "$ref": "#/components/schemas/SystemFaction"
                        }
                    }
                },
                "required": [
                    "symbol",
                    "sectorSymbol",
                    "type",
                    "x",
                    "y",
                    "waypoints",
                    "factions"
                ]
            },
            "SystemFaction": {
                "type": "object",
                "properties": {
                    "symbol": {
                        "$ref": "#/components/schemas/FactionSymbol"
                    }
                },
                "required": [
                    "symbol"
                ]
            },
            "SystemSymbol": {
                "type": "string",
                "description": "The symbol of the system.",
                "minLength": 1,
                "x-faker": {
                    "fake": [
                        "X1-{{random.alphaNumeric(5)}}"
                    ]
                }
            },
            "SystemType": {
                "type": "string",
                "description": "The type of system.",
                "enum": [
                    "NEUTRON_STAR",
                    "RED_STAR",
                    "ORANGE_STAR",
                    "BLUE_STAR",
                    "YOUNG_STAR",
                    "WHITE_DWARF",
                    "BLACK_HOLE",
                    "HYPERGIANT",
                    "NEBULA",
                    "UNSTABLE"
                ]
            },
            "SystemWaypoint": {
                "type": "object",
                "properties": {
                    "symbol": {
                        "$ref": "#/components/schemas/WaypointSymbol"
                    },
                    "type": {
                        "$ref": "#/components/schemas/WaypointType"
                    },
                    "x": {
                        "type": "integer",
                        "description": "Relative position of the waypoint on the system's x axis. This is not an absolute position in the universe."
                    },
                    "y": {
                        "type": "integer",
                        "description": "Relative position of the waypoint on the system's y axis. This is not an absolute position in the universe."
                    },
                    "orbitals": {
                        "type": "array",
                        "description": "Waypoints that orbit this waypoint.",
                        "items": {
                            "$ref": "#/components/schemas/WaypointOrbital"
                        }
                    },
                    "orbits": {
                        "type": "string",
                        "minLength": 1,
                        "description": "The symbol of the parent waypoint, if this waypoint is in orbit around another waypoint. Otherwise this value is undefined."
                    }
                },
                "required": [
                    "symbol",
                    "type",
                    "x",
                    "y",
                    "orbitals"
                ]
            },
            "TradeGood": {
                "type": "object",
                "description": "A good that can be traded for other goods or currency.",
                "properties": {
                    "symbol": {
                        "$ref": "#/components/schemas/TradeSymbol"
                    },
                    "name": {
                        "type": "string",
                        "description": "The name of the good."
                    },
                    "description": {
                        "type": "string",
                        "description": "The description of the good."
                    }
                },
                "required": [
                    "symbol",
                    "name",
                    "description"
                ]
            },
            "TradeSymbol": {
                "type": "string",
                "enum": [
                    "PRECIOUS_STONES",
                    "QUARTZ_SAND",
                    "SILICON_CRYSTALS",
                    "AMMONIA_ICE",
                    "LIQUID_HYDROGEN",
                    "LIQUID_NITROGEN",
                    "ICE_WATER",
                    "EXOTIC_MATTER",
                    "ADVANCED_CIRCUITRY",
                    "GRAVITON_EMITTERS",
                    "IRON",
                    "IRON_ORE",
                    "COPPER",
                    "COPPER_ORE",
                    "ALUMINUM",
                    "ALUMINUM_ORE",
                    "SILVER",
                    "SILVER_ORE",
                    "GOLD",
                    "GOLD_ORE",
                    "PLATINUM",
                    "PLATINUM_ORE",
                    "DIAMONDS",
                    "URANITE",
                    "URANITE_ORE",
                    "MERITIUM",
                    "MERITIUM_ORE",
                    "HYDROCARBON",
                    "ANTIMATTER",
                    "FAB_MATS",
                    "FERTILIZERS",
                    "FABRICS",
                    "FOOD",
                    "JEWELRY",
                    "MACHINERY",
                    "FIREARMS",
                    "ASSAULT_RIFLES",
                    "MILITARY_EQUIPMENT",
                    "EXPLOSIVES",
                    "LAB_INSTRUMENTS",
                    "AMMUNITION",
                    "ELECTRONICS",
                    "SHIP_PLATING",
                    "SHIP_PARTS",
                    "EQUIPMENT",
                    "FUEL",
                    "MEDICINE",
                    "DRUGS",
                    "CLOTHING",
                    "MICROPROCESSORS",
                    "PLASTICS",
                    "POLYNUCLEOTIDES",
                    "BIOCOMPOSITES",
                    "QUANTUM_STABILIZERS",
                    "NANOBOTS",
                    "AI_MAINFRAMES",
                    "QUANTUM_DRIVES",
                    "ROBOTIC_DRONES",
                    "CYBER_IMPLANTS",
                    "GENE_THERAPEUTICS",
                    "NEURAL_CHIPS",
                    "MOOD_REGULATORS",
                    "VIRAL_AGENTS",
                    "MICRO_FUSION_GENERATORS",
                    "SUPERGRAINS",
                    "LASER_RIFLES",
                    "HOLOGRAPHICS",
                    "SHIP_SALVAGE",
                    "RELIC_TECH",
                    "NOVEL_LIFEFORMS",
                    "BOTANICAL_SPECIMENS",
                    "CULTURAL_ARTIFACTS",
                    "FRAME_PROBE",
                    "FRAME_DRONE",
                    "FRAME_INTERCEPTOR",
                    "FRAME_RACER",
                    "FRAME_FIGHTER",
                    "FRAME_FRIGATE",
                    "FRAME_SHUTTLE",
                    "FRAME_EXPLORER",
                    "FRAME_MINER",
                    "FRAME_LIGHT_FREIGHTER",
                    "FRAME_HEAVY_FREIGHTER",
                    "FRAME_TRANSPORT",
                    "FRAME_DESTROYER",
                    "FRAME_CRUISER",
                    "FRAME_CARRIER",
                    "REACTOR_SOLAR_I",
                    "REACTOR_FUSION_I",
                    "REACTOR_FISSION_I",
                    "REACTOR_CHEMICAL_I",
                    "REACTOR_ANTIMATTER_I",
                    "ENGINE_IMPULSE_DRIVE_I",
                    "ENGINE_ION_DRIVE_I",
                    "ENGINE_ION_DRIVE_II",
                    "ENGINE_HYPER_DRIVE_I",
                    "MODULE_MINERAL_PROCESSOR_I",
                    "MODULE_GAS_PROCESSOR_I",
                    "MODULE_CARGO_HOLD_I",
                    "MODULE_CARGO_HOLD_II",
                    "MODULE_CARGO_HOLD_III",
                    "MODULE_CREW_QUARTERS_I",
                    "MODULE_ENVOY_QUARTERS_I",
                    "MODULE_PASSENGER_CABIN_I",
                    "MODULE_MICRO_REFINERY_I",
                    "MODULE_SCIENCE_LAB_I",
                    "MODULE_JUMP_DRIVE_I",
                    "MODULE_JUMP_DRIVE_II",
                    "MODULE_JUMP_DRIVE_III",
                    "MODULE_WARP_DRIVE_I",
                    "MODULE_WARP_DRIVE_II",
                    "MODULE_WARP_DRIVE_III",
                    "MODULE_SHIELD_GENERATOR_I",
                    "MODULE_SHIELD_GENERATOR_II",
                    "MODULE_ORE_REFINERY_I",
                    "MODULE_FUEL_REFINERY_I",
                    "MOUNT_GAS_SIPHON_I",
                    "MOUNT_GAS_SIPHON_II",
                    "MOUNT_GAS_SIPHON_III",
                    "MOUNT_SURVEYOR_I",
                    "MOUNT_SURVEYOR_II",
                    "MOUNT_SURVEYOR_III",
                    "MOUNT_SENSOR_ARRAY_I",
                    "MOUNT_SENSOR_ARRAY_II",
                    "MOUNT_SENSOR_ARRAY_III",
                    "MOUNT_MINING_LASER_I",
                    "MOUNT_MINING_LASER_II",
                    "MOUNT_MINING_LASER_III",
                    "MOUNT_LASER_CANNON_I",
                    "MOUNT_MISSILE_LAUNCHER_I",
                    "MOUNT_TURRET_I",
                    "SHIP_PROBE",
                    "SHIP_MINING_DRONE",
                    "SHIP_SIPHON_DRONE",
                    "SHIP_INTERCEPTOR",
                    "SHIP_LIGHT_HAULER",
                    "SHIP_COMMAND_FRIGATE",
                    "SHIP_EXPLORER",
                    "SHIP_HEAVY_FREIGHTER",
                    "SHIP_LIGHT_SHUTTLE",
                    "SHIP_ORE_HOUND",
                    "SHIP_REFINING_FREIGHTER",
                    "SHIP_SURVEYOR"
                ],
                "description": "The good's symbol."
            },
            "Waypoint": {
                "description": "A waypoint is a location that ships can travel to such as a Planet, Moon or Space Station.",
                "type": "object",
                "properties": {
                    "symbol": {
                        "$ref": "#/components/schemas/WaypointSymbol"
                    },
                    "type": {
                        "$ref": "#/components/schemas/WaypointType"
                    },
                    "systemSymbol": {
                        "$ref": "#/components/schemas/SystemSymbol"
                    },
                    "x": {
                        "type": "integer",
                        "description": "Relative position of the waypoint on the system's x axis. This is not an absolute position in the universe."
                    },
                    "y": {
                        "type": "integer",
                        "description": "Relative position of the waypoint on the system's y axis. This is not an absolute position in the universe."
                    },
                    "orbitals": {
                        "type": "array",
                        "description": "Waypoints that orbit this waypoint.",
                        "items": {
                            "$ref": "#/components/schemas/WaypointOrbital"
                        }
                    },
                    "orbits": {
                        "type": "string",
                        "minLength": 1,
                        "description": "The symbol of the parent waypoint, if this waypoint is in orbit around another waypoint. Otherwise this value is undefined."
                    },
                    "faction": {
                        "$ref": "#/components/schemas/WaypointFaction"
                    },
                    "traits": {
                        "type": "array",
                        "description": "The traits of the waypoint.",
                        "items": {
                            "$ref": "#/components/schemas/WaypointTrait"
                        }
                    },
                    "modifiers": {
                        "type": "array",
                        "description": "The modifiers of the waypoint.",
                        "items": {
                            "$ref": "#/components/schemas/WaypointModifier"
                        }
                    },
                    "chart": {
                        "$ref": "#/components/schemas/Chart"
                    },
                    "isUnderConstruction": {
                        "type": "boolean",
                        "description": "True if the waypoint is under construction."
                    }
                },
                "required": [
                    "symbol",
                    "type",
                    "systemSymbol",
                    "x",
                    "y",
                    "orbitals",
                    "traits",
                    "isUnderConstruction"
                ]
            },
            "WaypointFaction": {
                "type": "object",
                "description": "The faction that controls the waypoint.",
                "properties": {
                    "symbol": {
                        "$ref": "#/components/schemas/FactionSymbol"
                    }
                },
                "required": [
                    "symbol"
                ]
            },
            "WaypointModifier": {
                "type": "object",
                "properties": {
                    "symbol": {
                        "$ref": "#/components/schemas/WaypointModifierSymbol"
                    },
                    "name": {
                        "type": "string",
                        "description": "The name of the trait."
                    },
                    "description": {
                        "type": "string",
                        "description": "A description of the trait."
                    }
                },
                "required": [
                    "symbol",
                    "name",
                    "description"
                ]
            },
            "WaypointModifierSymbol": {
                "type": "string",
                "description": "The unique identifier of the modifier.",
                "enum": [
                    "STRIPPED",
                    "UNSTABLE",
                    "RADIATION_LEAK",
                    "CRITICAL_LIMIT",
                    "CIVIL_UNREST"
                ]
            },
            "WaypointOrbital": {
                "type": "object",
                "description": "An orbital is another waypoint that orbits a parent waypoint.",
                "properties": {
                    "symbol": {
                        "type": "string",
                        "minLength": 1,
                        "description": "The symbol of the orbiting waypoint."
                    }
                },
                "required": [
                    "symbol"
                ]
            },
            "WaypointSymbol": {
                "type": "string",
                "description": "The symbol of the waypoint.",
                "minLength": 1,
                "x-faker": {
                    "fake": [
                        "X1-{{random.alphaNumeric(5)}}-{{random.alphaNumeric(5)}}"
                    ]
                }
            },
            "WaypointTrait": {
                "type": "object",
                "properties": {
                    "symbol": {
                        "$ref": "#/components/schemas/WaypointTraitSymbol"
                    },
                    "name": {
                        "type": "string",
                        "description": "The name of the trait."
                    },
                    "description": {
                        "type": "string",
                        "description": "A description of the trait."
                    }
                },
                "required": [
                    "symbol",
                    "name",
                    "description"
                ]
            },
            "WaypointTraitSymbol": {
                "type": "string",
                "description": "The unique identifier of the trait.",
                "enum": [
                    "UNCHARTED",
                    "UNDER_CONSTRUCTION",
                    "MARKETPLACE",
                    "SHIPYARD",
                    "OUTPOST",
                    "SCATTERED_SETTLEMENTS",
                    "SPRAWLING_CITIES",
                    "MEGA_STRUCTURES",
                    "PIRATE_BASE",
                    "OVERCROWDED",
                    "HIGH_TECH",
                    "CORRUPT",
                    "BUREAUCRATIC",
                    "TRADING_HUB",
                    "INDUSTRIAL",
                    "BLACK_MARKET",
                    "RESEARCH_FACILITY",
                    "MILITARY_BASE",
                    "SURVEILLANCE_OUTPOST",
                    "EXPLORATION_OUTPOST",
                    "MINERAL_DEPOSITS",
                    "COMMON_METAL_DEPOSITS",
                    "PRECIOUS_METAL_DEPOSITS",
                    "RARE_METAL_DEPOSITS",
                    "METHANE_POOLS",
                    "ICE_CRYSTALS",
                    "EXPLOSIVE_GASES",
                    "STRONG_MAGNETOSPHERE",
                    "VIBRANT_AURORAS",
                    "SALT_FLATS",
                    "CANYONS",
                    "PERPETUAL_DAYLIGHT",
                    "PERPETUAL_OVERCAST",
                    "DRY_SEABEDS",
                    "MAGMA_SEAS",
                    "SUPERVOLCANOES",
                    "ASH_CLOUDS",
                    "VAST_RUINS",
                    "MUTATED_FLORA",
                    "TERRAFORMED",
                    "EXTREME_TEMPERATURES",
                    "EXTREME_PRESSURE",
                    "DIVERSE_LIFE",
                    "SCARCE_LIFE",
                    "FOSSILS",
                    "WEAK_GRAVITY",
                    "STRONG_GRAVITY",
                    "CRUSHING_GRAVITY",
                    "TOXIC_ATMOSPHERE",
                    "CORROSIVE_ATMOSPHERE",
                    "BREATHABLE_ATMOSPHERE",
                    "THIN_ATMOSPHERE",
                    "JOVIAN",
                    "ROCKY",
                    "VOLCANIC",
                    "FROZEN",
                    "SWAMP",
                    "BARREN",
                    "TEMPERATE",
                    "JUNGLE",
                    "OCEAN",
                    "RADIOACTIVE",
                    "MICRO_GRAVITY_ANOMALIES",
                    "DEBRIS_CLUSTER",
                    "DEEP_CRATERS",
                    "SHALLOW_CRATERS",
                    "UNSTABLE_COMPOSITION",
                    "HOLLOWED_INTERIOR",
                    "STRIPPED"
                ]
            },
            "WaypointType": {
                "type": "string",
                "description": "The type of waypoint.",
                "enum": [
                    "PLANET",
                    "GAS_GIANT",
                    "MOON",
                    "ORBITAL_STATION",
                    "JUMP_GATE",
                    "ASTEROID_FIELD",
                    "ASTEROID",
                    "ENGINEERED_ASTEROID",
                    "ASTEROID_BASE",
                    "NEBULA",
                    "DEBRIS_FIELD",
                    "GRAVITY_WELL",
                    "ARTIFICIAL_GRAVITY_WELL",
                    "FUEL_STATION"
                ]
            }
        },
        "securitySchemes": {
            "AgentToken": {
                "description": "When you register a new agent you will be granted a private bearer token which grants authorization to use the API.",
                "scheme": "bearer",
                "type": "http"
            }
        }
    },
    "paths": {
        "/": {
            "get": {
                "description": "Return the status of the game server.\nThis also includes a few global elements, such as announcements, server reset dates and leaderboards.",
                "operationId": "get-status",
                "responses": {
                    "200": {
                        "content": {
                            "application/json": {
                                "schema": {
                                    "type": "object",
                                    "properties": {
                                        "status": {
                                            "type": "string",
                                            "description": "The current status of the game server."
                                        },
                                        "version": {
                                            "type": "string",
                                            "description": "The current version of the API."
                                        },
                                        "resetDate": {
                                            "type": "string",
                                            "description": "The date when the game server was last reset."
                                        },
                                        "description": {
                                            "type": "string"
                                        },
                                        "stats": {
                                            "type": "object",
                                            "required": [
                                                "agents",
                                                "ships",
                                                "systems",
                                                "waypoints"
                                            ],
                                            "properties": {
                                                "agents": {
                                                    "type": "integer",
                                                    "description": "Number of registered agents in the game."
                                                },
                                                "ships": {
                                                    "type": "integer",
                                                    "description": "Total number of ships in the game."
                                                },
                                                "systems": {
                                                    "type": "integer",
                                                    "description": "Total number of systems in the game."
                                                },
                                                "waypoints": {
                                                    "type": "integer",
                                                    "description": "Total number of waypoints in the game."
                                                }
                                            }
                                        },
                                        "leaderboards": {
                                            "type": "object",
                                            "required": [
                                                "mostCredits",
                                                "mostSubmittedCharts"
                                            ],
                                            "properties": {
                                                "mostCredits": {
                                                    "type": "array",
                                                    "description": "Top agents with the most credits.",
                                                    "items": {
                                                        "type": "object",
                                                        "properties": {
                                                            "agentSymbol": {
                                                                "type": "string",
                                                                "description": "Symbol of the agent."
                                                            },
                                                            "credits": {
                                                                "type": "integer",
                                                                "format": "int64",
                                                                "description": "Amount of credits."
                                                            }
                                                        },
                                                        "required": [
                                                            "agentSymbol",
                                                            "credits"
                                                        ]
                                                    }
                                                },
                                                "mostSubmittedCharts": {
                                                    "type": "array",
                                                    "description": "Top agents with the most charted submitted.",
                                                    "items": {
                                                        "type": "object",
                                                        "properties": {
                                                            "agentSymbol": {
                                                                "type": "string",
                                                                "description": "Symbol of the agent."
                                                            },
                                                            "chartCount": {
                                                                "type": "integer",
                                                                "description": "Amount of charts done by the agent."
                                                            }
                                                        },
                                                        "required": [
                                                            "agentSymbol",
                                                            "chartCount"
                                                        ]
                                                    }
                                                }
                                            }
                                        },
                                        "serverResets": {
                                            "type": "object",
                                            "required": [
                                                "next",
                                                "frequency"
                                            ],
                                            "properties": {
                                                "next": {
                                                    "type": "string",
                                                    "description": "The date and time when the game server will reset."
                                                },
                                                "frequency": {
                                                    "type": "string",
                                                    "description": "How often we intend to reset the game server."
                                                }
                                            }
                                        },
                                        "announcements": {
                                            "type": "array",
                                            "items": {
                                                "type": "object",
                                                "properties": {
                                                    "title": {
                                                        "type": "string"
                                                    },
                                                    "body": {
                                                        "type": "string"
                                                    }
                                                },
                                                "required": [
                                                    "title",
                                                    "body"
                                                ]
                                            }
                                        },
                                        "links": {
                                            "type": "array",
                                            "items": {
                                                "type": "object",
                                                "properties": {
                                                    "name": {
                                                        "type": "string"
                                                    },
                                                    "url": {
                                                        "type": "string"
                                                    }
                                                },
                                                "required": [
                                                    "name",
                                                    "url"
                                                ]
                                            }
                                        }
                                    },
                                    "required": [
                                        "status",
                                        "version",
                                        "resetDate",
                                        "description",
                                        "stats",
                                        "leaderboards",
                                        "serverResets",
                                        "announcements",
                                        "links"
                                    ]
                                }
                            }
                        },
                        "description": "Fetched status successfully."
                    }
                },
                "summary": "Get Status",
                "tags": [],
                "security": [
                    {},
                    {
                        "AgentToken": []
                    }
                ]
            }
        },
        "/register": {
            "post": {
                "description": "Creates a new agent and ties it to an account. \nThe agent symbol must consist of a 3-14 character string, and will be used to represent your agent. This symbol will prefix the symbol of every ship you own. Agent symbols will be cast to all uppercase characters.\n\nThis new agent will be tied to a starting faction of your choice, which determines your starting location, and will be granted an authorization token, a contract with their starting faction, a command ship that can fly across space with advanced capabilities, a small probe ship that can be used for reconnaissance, and 150,000 credits.\n\n> #### Keep your token safe and secure\n>\n> Save your token during the alpha phase. There is no way to regenerate this token without starting a new agent. In the future you will be able to generate and manage your tokens from the SpaceTraders website.\n\nIf you are new to SpaceTraders, It is recommended to register with the COSMIC faction, a faction that is well connected to the rest of the universe. After registering, you should try our interactive [quickstart guide](https://docs.spacetraders.io/quickstart/new-game) which will walk you through basic API requests in just a few minutes.",
                "operationId": "register",
                "requestBody": {
                    "content": {
                        "application/json": {
                            "schema": {
                                "properties": {
                                    "faction": {
                                        "$ref": "#/components/schemas/FactionSymbol"
                                    },
                                    "symbol": {
                                        "description": "Your desired agent symbol. This will be a unique name used to represent your agent, and will be the prefix for your ships.",
                                        "example": "BADGER",
                                        "maxLength": 14,
                                        "minLength": 3,
                                        "type": "string"
                                    },
                                    "email": {
                                        "type": "string",
                                        "description": "Your email address. This is used if you reserved your call sign between resets."
                                    }
                                },
                                "required": [
                                    "symbol",
                                    "faction"
                                ],
                                "type": "object"
                            }
                        }
                    },
                    "description": ""
                },
                "responses": {
                    "201": {
                        "content": {
                            "application/json": {
                                "schema": {
                                    "properties": {
                                        "data": {
                                            "properties": {
                                                "agent": {
                                                    "$ref": "#/components/schemas/Agent"
                                                },
                                                "contract": {
                                                    "$ref": "#/components/schemas/Contract"
                                                },
                                                "faction": {
                                                    "$ref": "#/components/schemas/Faction"
                                                },
                                                "ship": {
                                                    "$ref": "#/components/schemas/Ship"
                                                },
                                                "token": {
                                                    "description": "A Bearer token for accessing secured API endpoints.",
                                                    "type": "string"
                                                }
                                            },
                                            "required": [
                                                "token",
                                                "agent",
                                                "faction",
                                                "contract",
                                                "ship"
                                            ],
                                            "type": "object"
                                        }
                                    },
                                    "required": [
                                        "data"
                                    ],
                                    "type": "object"
                                }
                            }
                        },
                        "description": "Succesfully registered."
                    }
                },
                "summary": "Register New Agent",
                "tags": [],
                "security": []
            }
        },
        "/systems": {
            "get": {
                "description": "Return a paginated list of all systems.",
                "operationId": "get-systems",
                "responses": {
                    "200": {
                        "content": {
                            "application/json": {
                                "schema": {
                                    "description": "",
                                    "properties": {
                                        "data": {
                                            "items": {
                                                "$ref": "#/components/schemas/System"
                                            },
                                            "type": "array"
                                        },
                                        "meta": {
                                            "$ref": "#/components/schemas/Meta"
                                        }
                                    },
                                    "required": [
                                        "data",
                                        "meta"
                                    ],
                                    "type": "object"
                                }
                            }
                        },
                        "description": "Successfully listed systems."
                    }
                },
                "summary": "List Systems",
                "tags": [
                    "Systems"
                ],
                "parameters": [
                    {
                        "schema": {
                            "type": "integer",
                            "minimum": 1,
                            "default": 1
                        },
                        "in": "query",
                        "name": "page",
                        "description": "What entry offset to request"
                    },
                    {
                        "schema": {
                            "type": "integer",
                            "minimum": 1,
                            "maximum": 20,
                            "default": 10
                        },
                        "in": "query",
                        "name": "limit",
                        "description": "How many entries to return per page"
                    }
                ],
                "security": [
                    {},
                    {
                        "AgentToken": []
                    }
                ]
            }
        },
        "/systems/{systemSymbol}": {
            "get": {
                "description": "Get the details of a system.",
                "operationId": "get-system",
                "responses": {
                    "200": {
                        "content": {
                            "application/json": {
                                "schema": {
                                    "description": "",
                                    "properties": {
                                        "data": {
                                            "$ref": "#/components/schemas/System"
                                        }
                                    },
                                    "required": [
                                        "data"
                                    ],
                                    "type": "object"
                                }
                            }
                        },
                        "description": "Successfully fetched the system."
                    }
                },
                "summary": "Get System",
                "tags": [
                    "Systems"
                ],
                "security": [
                    {},
                    {
                        "AgentToken": []
                    }
                ]
            },
            "parameters": [
                {
                    "description": "The system symbol",
                    "in": "path",
                    "name": "systemSymbol",
                    "required": true,
                    "schema": {
                        "default": "X1-OE",
                        "type": "string"
                    }
                }
            ]
        },
        "/systems/{systemSymbol}/waypoints": {
            "get": {
                "description": "Return a paginated list of all of the waypoints for a given system.\n\nIf a waypoint is uncharted, it will return the `Uncharted` trait instead of its actual traits.",
                "operationId": "get-system-waypoints",
                "responses": {
                    "200": {
                        "content": {
                            "application/json": {
                                "schema": {
                                    "description": "",
                                    "properties": {
                                        "data": {
                                            "items": {
                                                "$ref": "#/components/schemas/Waypoint"
                                            },
                                            "type": "array"
                                        },
                                        "meta": {
                                            "$ref": "#/components/schemas/Meta"
                                        }
                                    },
                                    "required": [
                                        "data",
                                        "meta"
                                    ],
                                    "type": "object"
                                }
                            }
                        },
                        "description": "Successfully fetched all waypoints in the system."
                    }
                },
                "summary": "List Waypoints in System",
                "tags": [
                    "Systems"
                ],
                "parameters": [
                    {
                        "schema": {
                            "type": "integer",
                            "minimum": 1,
                            "default": 1
                        },
                        "in": "query",
                        "name": "page",
                        "description": "What entry offset to request"
                    },
                    {
                        "schema": {
                            "type": "integer",
                            "minimum": 1,
                            "maximum": 20,
                            "default": 10
                        },
                        "in": "query",
                        "name": "limit",
                        "description": "How many entries to return per page"
                    },
                    {
                        "description": "Filter waypoints by type.",
                        "in": "query",
                        "name": "type",
                        "schema": {
                            "$ref": "#/components/schemas/WaypointType"
                        }
                    },
                    {
                        "description": "Filter waypoints by one or more traits.",
                        "in": "query",
                        "name": "traits",
                        "schema": {
                            "oneOf": [
                                {
                                    "$ref": "#/components/schemas/WaypointTraitSymbol"
                                },
                                {
                                    "type": "array",
                                    "items": {
                                        "$ref": "#/components/schemas/WaypointTraitSymbol"
                                    }
                                }
                            ]
                        }
                    }
                ],
                "security": [
                    {},
                    {
                        "AgentToken": []
                    }
                ]
            },
            "parameters": [
                {
                    "description": "The system symbol",
                    "in": "path",
                    "name": "systemSymbol",
                    "required": true,
                    "schema": {
                        "type": "string"
                    }
                }
            ]
        },
        "/systems/{systemSymbol}/waypoints/{waypointSymbol}": {
            "get": {
                "description": "View the details of a waypoint.\n\nIf the waypoint is uncharted, it will return the 'Uncharted' trait instead of its actual traits.",
                "operationId": "get-waypoint",
                "responses": {
                    "200": {
                        "content": {
                            "application/json": {
                                "schema": {
                                    "description": "",
                                    "properties": {
                                        "data": {
                                            "$ref": "#/components/schemas/Waypoint"
                                        }
                                    },
                                    "required": [
                                        "data"
                                    ],
                                    "type": "object"
                                }
                            }
                        },
                        "description": "Successfully fetched waypoint."
                    }
                },
                "summary": "Get Waypoint",
                "tags": [
                    "Systems"
                ],
                "security": [
                    {},
                    {
                        "AgentToken": []
                    }
                ]
            },
            "parameters": [
                {
                    "description": "The system symbol",
                    "in": "path",
                    "name": "systemSymbol",
                    "required": true,
                    "schema": {
                        "type": "string"
                    }
                },
                {
                    "description": "The waypoint symbol",
                    "in": "path",
                    "name": "waypointSymbol",
                    "required": true,
                    "schema": {
                        "type": "string"
                    }
                }
            ]
        },
        "/systems/{systemSymbol}/waypoints/{waypointSymbol}/market": {
            "get": {
                "description": "Retrieve imports, exports and exchange data from a marketplace. Requires a waypoint that has the `Marketplace` trait to use.\n\nSend a ship to the waypoint to access trade good prices and recent transactions. Refer to the [Market Overview page](https://docs.spacetraders.io/game-concepts/markets) to gain better a understanding of the market in the game.",
                "operationId": "get-market",
                "responses": {
                    "200": {
                        "content": {
                            "application/json": {
                                "schema": {
                                    "properties": {
                                        "data": {
                                            "$ref": "#/components/schemas/Market"
                                        }
                                    },
                                    "required": [
                                        "data"
                                    ],
                                    "type": "object"
                                }
                            }
                        },
                        "description": "Successfully fetched the market."
                    }
                },
                "security": [
                    {},
                    {
                        "AgentToken": []
                    }
                ],
                "summary": "Get Market",
                "tags": [
                    "Systems"
                ]
            },
            "parameters": [
                {
                    "description": "The system symbol",
                    "in": "path",
                    "name": "systemSymbol",
                    "required": true,
                    "schema": {
                        "type": "string"
                    }
                },
                {
                    "description": "The waypoint symbol",
                    "in": "path",
                    "name": "waypointSymbol",
                    "required": true,
                    "schema": {
                        "type": "string"
                    }
                }
            ]
        },
        "/systems/{systemSymbol}/waypoints/{waypointSymbol}/shipyard": {
            "get": {
                "description": "Get the shipyard for a waypoint. Requires a waypoint that has the `Shipyard` trait to use. Send a ship to the waypoint to access data on ships that are currently available for purchase and recent transactions.",
                "operationId": "get-shipyard",
                "responses": {
                    "200": {
                        "content": {
                            "application/json": {
                                "schema": {
                                    "description": "",
                                    "properties": {
                                        "data": {
                                            "$ref": "#/components/schemas/Shipyard"
                                        }
                                    },
                                    "required": [
                                        "data"
                                    ],
                                    "type": "object"
                                }
                            }
                        },
                        "description": "Successfully fetched the shipyard."
                    }
                },
                "security": [
                    {},
                    {
                        "AgentToken": []
                    }
                ],
                "summary": "Get Shipyard",
                "tags": [
                    "Systems"
                ]
            },
            "parameters": [
                {
                    "description": "The system symbol",
                    "in": "path",
                    "name": "systemSymbol",
                    "required": true,
                    "schema": {
                        "type": "string"
                    }
                },
                {
                    "description": "The waypoint symbol",
                    "in": "path",
                    "name": "waypointSymbol",
                    "required": true,
                    "schema": {
                        "type": "string"
                    }
                }
            ]
        },
        "/systems/{systemSymbol}/waypoints/{waypointSymbol}/jump-gate": {
            "get": {
                "description": "Get jump gate details for a waypoint. Requires a waypoint of type `JUMP_GATE` to use.\n\nWaypoints connected to this jump gate can be ",
                "operationId": "get-jump-gate",
                "responses": {
                    "200": {
                        "content": {
                            "application/json": {
                                "schema": {
                                    "description": "",
                                    "properties": {
                                        "data": {
                                            "$ref": "#/components/schemas/JumpGate"
                                        }
                                    },
                                    "required": [
                                        "data"
                                    ],
                                    "type": "object"
                                }
                            }
                        },
                        "description": "Successfully fetched jump gate."
                    }
                },
                "security": [
                    {},
                    {
                        "AgentToken": []
                    }
                ],
                "summary": "Get Jump Gate",
                "tags": [
                    "Systems"
                ]
            },
            "parameters": [
                {
                    "description": "The system symbol",
                    "in": "path",
                    "name": "systemSymbol",
                    "required": true,
                    "schema": {
                        "type": "string"
                    }
                },
                {
                    "description": "The waypoint symbol",
                    "in": "path",
                    "name": "waypointSymbol",
                    "required": true,
                    "schema": {
                        "type": "string"
                    }
                }
            ]
        },
        "/systems/{systemSymbol}/waypoints/{waypointSymbol}/construction": {
            "get": {
                "description": "Get construction details for a waypoint. Requires a waypoint with a property of `isUnderConstruction` to be true.",
                "operationId": "get-construction",
                "responses": {
                    "200": {
                        "content": {
                            "application/json": {
                                "schema": {
                                    "description": "",
                                    "properties": {
                                        "data": {
                                            "$ref": "#/components/schemas/Construction"
                                        }
                                    },
                                    "required": [
                                        "data"
                                    ],
                                    "type": "object"
                                }
                            }
                        },
                        "description": "Successfully fetched construction site."
                    }
                },
                "security": [
                    {},
                    {
                        "AgentToken": []
                    }
                ],
                "summary": "Get Construction Site",
                "tags": [
                    "Systems"
                ]
            },
            "parameters": [
                {
                    "description": "The system symbol",
                    "in": "path",
                    "name": "systemSymbol",
                    "required": true,
                    "schema": {
                        "type": "string"
                    }
                },
                {
                    "description": "The waypoint symbol",
                    "in": "path",
                    "name": "waypointSymbol",
                    "required": true,
                    "schema": {
                        "type": "string"
                    }
                }
            ]
        },
        "/systems/{systemSymbol}/waypoints/{waypointSymbol}/construction/supply": {
            "post": {
                "description": "Supply a construction site with the specified good. Requires a waypoint with a property of `isUnderConstruction` to be true.\n\nThe good must be in your ship's cargo. The good will be removed from your ship's cargo and added to the construction site's materials.",
                "operationId": "supply-construction",
                "requestBody": {
                    "content": {
                        "application/json": {
                            "schema": {
                                "properties": {
                                    "shipSymbol": {
                                        "type": "string",
                                        "description": "Symbol of the ship to use."
                                    },
                                    "tradeSymbol": {
                                        "type": "string",
                                        "description": "The symbol of the good to supply."
                                    },
                                    "units": {
                                        "type": "integer",
                                        "description": "Amount of units to supply."
                                    }
                                },
                                "required": [
                                    "shipSymbol",
                                    "tradeSymbol",
                                    "units"
                                ],
                                "type": "object"
                            }
                        }
                    },
                    "description": ""
                },
                "responses": {
                    "201": {
                        "content": {
                            "application/json": {
                                "schema": {
                                    "description": "",
                                    "properties": {
                                        "data": {
                                            "properties": {
                                                "construction": {
                                                    "$ref": "#/components/schemas/Construction"
                                                },
                                                "cargo": {
                                                    "$ref": "#/components/schemas/ShipCargo"
                                                }
                                            },
                                            "required": [
                                                "construction",
                                                "cargo"
                                            ],
                                            "type": "object"
                                        }
                                    },
                                    "required": [
                                        "data"
                                    ],
                                    "type": "object"
                                }
                            }
                        },
                        "description": "Successfully supplied construction site."
                    }
                },
                "security": [
                    {
                        "AgentToken": []
                    }
                ],
                "summary": "Supply Construction Site",
                "tags": [
                    "Systems"
                ]
            },
            "parameters": [
                {
                    "description": "The system symbol",
                    "in": "path",
                    "name": "systemSymbol",
                    "required": true,
                    "schema": {
                        "type": "string"
                    }
                },
                {
                    "description": "The waypoint symbol",
                    "in": "path",
                    "name": "waypointSymbol",
                    "required": true,
                    "schema": {
                        "type": "string"
                    }
                }
            ]
        },
        "/factions": {
            "get": {
                "description": "Return a paginated list of all the factions in the game.",
                "operationId": "get-factions",
                "responses": {
                    "200": {
                        "content": {
                            "application/json": {
                                "schema": {
                                    "properties": {
                                        "data": {
                                            "items": {
                                                "$ref": "#/components/schemas/Faction"
                                            },
                                            "type": "array"
                                        },
                                        "meta": {
                                            "$ref": "#/components/schemas/Meta"
                                        }
                                    },
                                    "required": [
                                        "data",
                                        "meta"
                                    ],
                                    "type": "object"
                                }
                            }
                        },
                        "description": "Succesfully fetched factions."
                    }
                },
                "summary": "List Factions",
                "tags": [
                    "Factions"
                ],
                "parameters": [
                    {
                        "schema": {
                            "type": "integer",
                            "minimum": 1,
                            "default": 1
                        },
                        "in": "query",
                        "name": "page",
                        "description": "What entry offset to request"
                    },
                    {
                        "schema": {
                            "type": "integer",
                            "minimum": 1,
                            "maximum": 20,
                            "default": 10
                        },
                        "in": "query",
                        "name": "limit",
                        "description": "How many entries to return per page"
                    }
                ],
                "security": [
                    {},
                    {
                        "AgentToken": []
                    }
                ]
            }
        },
        "/factions/{factionSymbol}": {
            "get": {
                "description": "View the details of a faction.",
                "operationId": "get-faction",
                "responses": {
                    "200": {
                        "content": {
                            "application/json": {
                                "schema": {
                                    "properties": {
                                        "data": {
                                            "$ref": "#/components/schemas/Faction"
                                        }
                                    },
                                    "required": [
                                        "data"
                                    ],
                                    "type": "object"
                                }
                            }
                        },
                        "description": "Successfully fetched a faction."
                    }
                },
                "summary": "Get Faction",
                "tags": [
                    "Factions"
                ]
            },
            "parameters": [
                {
                    "description": "The faction symbol",
                    "in": "path",
                    "name": "factionSymbol",
                    "required": true,
                    "schema": {
                        "type": "string",
                        "example": "COSMIC"
                    }
                }
            ]
        },
        "/my/agent": {
            "get": {
                "description": "Fetch your agent's details.",
                "operationId": "get-my-agent",
                "responses": {
                    "200": {
                        "content": {
                            "application/json": {
                                "schema": {
                                    "properties": {
                                        "data": {
                                            "$ref": "#/components/schemas/Agent"
                                        }
                                    },
                                    "required": [
                                        "data"
                                    ],
                                    "type": "object"
                                }
                            }
                        },
                        "description": "Successfully fetched agent details."
                    }
                },
                "security": [
                    {
                        "AgentToken": []
                    }
                ],
                "summary": "Get Agent",
                "tags": [
                    "Agents"
                ]
            }
        },
        "/agents": {
            "get": {
                "description": "Fetch agents details.",
                "operationId": "get-agents",
                "responses": {
                    "200": {
                        "content": {
                            "application/json": {
                                "schema": {
                                    "properties": {
                                        "data": {
                                            "items": {
                                                "$ref": "#/components/schemas/Agent"
                                            },
                                            "type": "array"
                                        },
                                        "meta": {
                                            "$ref": "#/components/schemas/Meta"
                                        }
                                    },
                                    "required": [
                                        "data",
                                        "meta"
                                    ],
                                    "type": "object"
                                }
                            }
                        },
                        "description": "Successfully fetched agents details."
                    }
                },
                "summary": "List Agents",
                "tags": [
                    "Agents"
                ],
                "parameters": [
                    {
                        "schema": {
                            "type": "integer",
                            "minimum": 1,
                            "default": 1
                        },
                        "in": "query",
                        "name": "page",
                        "description": "What entry offset to request"
                    },
                    {
                        "schema": {
                            "type": "integer",
                            "minimum": 1,
                            "maximum": 20,
                            "default": 10
                        },
                        "in": "query",
                        "name": "limit",
                        "description": "How many entries to return per page"
                    }
                ],
                "security": [
                    {},
                    {
                        "AgentToken": []
                    }
                ]
            }
        },
        "/agents/{agentSymbol}": {
            "get": {
                "description": "Fetch agent details.",
                "operationId": "get-agent",
                "responses": {
                    "200": {
                        "content": {
                            "application/json": {
                                "schema": {
                                    "properties": {
                                        "data": {
                                            "$ref": "#/components/schemas/Agent"
                                        }
                                    },
                                    "required": [
                                        "data"
                                    ],
                                    "type": "object"
                                }
                            }
                        },
                        "description": "Successfully fetched agent details."
                    }
                },
                "summary": "Get Public Agent",
                "tags": [
                    "Agents"
                ],
                "parameters": [
                    {
                        "description": "The agent symbol",
                        "in": "path",
                        "name": "agentSymbol",
                        "required": true,
                        "schema": {
                            "default": "FEBA66",
                            "type": "string"
                        }
                    }
                ],
                "security": [
                    {},
                    {
                        "AgentToken": []
                    }
                ]
            }
        },
        "/my/contracts": {
            "get": {
                "description": "Return a paginated list of all your contracts.",
                "operationId": "get-contracts",
                "responses": {
                    "200": {
                        "content": {
                            "application/json": {
                                "schema": {
                                    "description": "",
                                    "properties": {
                                        "data": {
                                            "items": {
                                                "$ref": "#/components/schemas/Contract"
                                            },
                                            "type": "array"
                                        },
                                        "meta": {
                                            "$ref": "#/components/schemas/Meta"
                                        }
                                    },
                                    "required": [
                                        "data",
                                        "meta"
                                    ],
                                    "type": "object"
                                }
                            }
                        },
                        "description": "Succesfully listed contracts."
                    }
                },
                "security": [
                    {
                        "AgentToken": []
                    }
                ],
                "summary": "List Contracts",
                "tags": [
                    "Contracts"
                ],
                "parameters": [
                    {
                        "schema": {
                            "type": "integer",
                            "minimum": 1,
                            "default": 1
                        },
                        "in": "query",
                        "name": "page",
                        "description": "What entry offset to request"
                    },
                    {
                        "schema": {
                            "type": "integer",
                            "minimum": 1,
                            "maximum": 20,
                            "default": 10
                        },
                        "in": "query",
                        "name": "limit",
                        "description": "How many entries to return per page"
                    }
                ]
            }
        },
        "/my/contracts/{contractId}": {
            "get": {
                "description": "Get the details of a contract by ID.",
                "operationId": "get-contract",
                "responses": {
                    "200": {
                        "content": {
                            "application/json": {
                                "schema": {
                                    "properties": {
                                        "data": {
                                            "$ref": "#/components/schemas/Contract"
                                        }
                                    },
                                    "required": [
                                        "data"
                                    ],
                                    "type": "object"
                                }
                            }
                        },
                        "description": "Successfully fetched contract."
                    }
                },
                "security": [
                    {
                        "AgentToken": []
                    }
                ],
                "summary": "Get Contract",
                "tags": [
                    "Contracts"
                ]
            },
            "parameters": [
                {
                    "description": "The contract ID",
                    "in": "path",
                    "name": "contractId",
                    "required": true,
                    "schema": {
                        "type": "string"
                    }
                }
            ]
        },
        "/my/contracts/{contractId}/accept": {
            "parameters": [
                {
                    "description": "The contract ID to accept.",
                    "in": "path",
                    "name": "contractId",
                    "required": true,
                    "schema": {
                        "type": "string"
                    }
                }
            ],
            "post": {
                "description": "Accept a contract by ID. \n\nYou can only accept contracts that were offered to you, were not accepted yet, and whose deadlines has not passed yet.",
                "operationId": "accept-contract",
                "responses": {
                    "200": {
                        "content": {
                            "application/json": {
                                "schema": {
                                    "properties": {
                                        "data": {
                                            "properties": {
                                                "agent": {
                                                    "$ref": "#/components/schemas/Agent"
                                                },
                                                "contract": {
                                                    "$ref": "#/components/schemas/Contract"
                                                }
                                            },
                                            "required": [
                                                "contract",
                                                "agent"
                                            ],
                                            "type": "object"
                                        }
                                    },
                                    "required": [
                                        "data"
                                    ],
                                    "type": "object"
                                }
                            }
                        },
                        "description": "Succesfully accepted contract."
                    }
                },
                "security": [
                    {
                        "AgentToken": []
                    }
                ],
                "summary": "Accept Contract",
                "tags": [
                    "Contracts"
                ]
            }
        },
        "/my/contracts/{contractId}/deliver": {
            "parameters": [
                {
                    "schema": {
                        "type": "string"
                    },
                    "name": "contractId",
                    "in": "path",
                    "required": true,
                    "description": "The ID of the contract."
                }
            ],
            "post": {
                "description": "Deliver cargo to a contract.\n\nIn order to use this API, a ship must be at the delivery location (denoted in the delivery terms as `destinationSymbol` of a contract) and must have a number of units of a good required by this contract in its cargo.\n\nCargo that was delivered will be removed from the ship's cargo.",
                "operationId": "deliver-contract",
                "requestBody": {
                    "content": {
                        "application/json": {
                            "schema": {
                                "properties": {
                                    "shipSymbol": {
                                        "type": "string",
                                        "description": "Symbol of a ship located in the destination to deliver a contract and that has a good to deliver in its cargo."
                                    },
                                    "tradeSymbol": {
                                        "type": "string",
                                        "description": "The symbol of the good to deliver."
                                    },
                                    "units": {
                                        "type": "integer",
                                        "description": "Amount of units to deliver."
                                    }
                                },
                                "required": [
                                    "shipSymbol",
                                    "tradeSymbol",
                                    "units"
                                ],
                                "type": "object"
                            }
                        }
                    },
                    "description": ""
                },
                "responses": {
                    "200": {
                        "content": {
                            "application/json": {
                                "schema": {
                                    "description": "",
                                    "properties": {
                                        "data": {
                                            "properties": {
                                                "contract": {
                                                    "$ref": "#/components/schemas/Contract"
                                                },
                                                "cargo": {
                                                    "$ref": "#/components/schemas/ShipCargo"
                                                }
                                            },
                                            "required": [
                                                "contract",
                                                "cargo"
                                            ],
                                            "type": "object"
                                        }
                                    },
                                    "required": [
                                        "data"
                                    ],
                                    "type": "object"
                                }
                            }
                        },
                        "description": "Successfully delivered cargo to contract."
                    }
                },
                "security": [
                    {
                        "AgentToken": []
                    }
                ],
                "summary": "Deliver Cargo to Contract",
                "tags": [
                    "Contracts"
                ]
            }
        },
        "/my/contracts/{contractId}/fulfill": {
            "parameters": [
                {
                    "description": "The ID of the contract to fulfill.",
                    "in": "path",
                    "name": "contractId",
                    "required": true,
                    "schema": {
                        "type": "string"
                    }
                }
            ],
            "post": {
                "description": "Fulfill a contract. Can only be used on contracts that have all of their delivery terms fulfilled.",
                "operationId": "fulfill-contract",
                "responses": {
                    "200": {
                        "content": {
                            "application/json": {
                                "schema": {
                                    "description": "",
                                    "properties": {
                                        "data": {
                                            "properties": {
                                                "agent": {
                                                    "$ref": "#/components/schemas/Agent"
                                                },
                                                "contract": {
                                                    "$ref": "#/components/schemas/Contract"
                                                }
                                            },
                                            "required": [
                                                "contract",
                                                "agent"
                                            ],
                                            "type": "object"
                                        }
                                    },
                                    "required": [
                                        "data"
                                    ],
                                    "type": "object"
                                }
                            }
                        },
                        "description": "Successfully fulfilled a contract."
                    }
                },
                "security": [
                    {
                        "AgentToken": []
                    }
                ],
                "summary": "Fulfill Contract",
                "tags": [
                    "Contracts"
                ]
            }
        },
        "/my/ships": {
            "get": {
                "description": "Return a paginated list of all of ships under your agent's ownership.",
                "operationId": "get-my-ships",
                "responses": {
                    "200": {
                        "content": {
                            "application/json": {
                                "schema": {
                                    "description": "",
                                    "properties": {
                                        "data": {
                                            "items": {
                                                "$ref": "#/components/schemas/Ship"
                                            },
                                            "type": "array"
                                        },
                                        "meta": {
                                            "$ref": "#/components/schemas/Meta"
                                        }
                                    },
                                    "required": [
                                        "data",
                                        "meta"
                                    ],
                                    "type": "object"
                                }
                            }
                        },
                        "description": "Succesfully listed ships."
                    }
                },
                "security": [
                    {
                        "AgentToken": []
                    }
                ],
                "summary": "List Ships",
                "tags": [
                    "Fleet"
                ],
                "parameters": [
                    {
                        "schema": {
                            "type": "integer",
                            "minimum": 1,
                            "default": 1
                        },
                        "in": "query",
                        "name": "page",
                        "description": "What entry offset to request"
                    },
                    {
                        "schema": {
                            "type": "integer",
                            "minimum": 1,
                            "maximum": 20,
                            "default": 10
                        },
                        "in": "query",
                        "name": "limit",
                        "description": "How many entries to return per page"
                    }
                ]
            },
            "post": {
                "description": "Purchase a ship from a Shipyard. In order to use this function, a ship under your agent's ownership must be in a waypoint that has the `Shipyard` trait, and the Shipyard must sell the type of the desired ship.\n\nShipyards typically offer ship types, which are predefined templates of ships that have dedicated roles. A template comes with a preset of an engine, a reactor, and a frame. It may also include a few modules and mounts.",
                "operationId": "purchase-ship",
                "requestBody": {
                    "content": {
                        "application/json": {
                            "schema": {
                                "properties": {
                                    "shipType": {
                                        "$ref": "#/components/schemas/ShipType"
                                    },
                                    "waypointSymbol": {
                                        "description": "The symbol of the waypoint you want to purchase the ship at.",
                                        "type": "string"
                                    }
                                },
                                "required": [
                                    "shipType",
                                    "waypointSymbol"
                                ],
                                "type": "object"
                            }
                        }
                    }
                },
                "responses": {
                    "201": {
                        "content": {
                            "application/json": {
                                "schema": {
                                    "description": "",
                                    "properties": {
                                        "data": {
                                            "properties": {
                                                "agent": {
                                                    "$ref": "#/components/schemas/Agent"
                                                },
                                                "ship": {
                                                    "$ref": "#/components/schemas/Ship"
                                                },
                                                "transaction": {
                                                    "$ref": "#/components/schemas/ShipyardTransaction"
                                                }
                                            },
                                            "required": [
                                                "ship",
                                                "agent",
                                                "transaction"
                                            ],
                                            "type": "object"
                                        }
                                    },
                                    "required": [
                                        "data"
                                    ],
                                    "type": "object"
                                }
                            }
                        },
                        "description": "Purchased ship successfully."
                    }
                },
                "security": [
                    {
                        "AgentToken": []
                    }
                ],
                "summary": "Purchase Ship",
                "tags": [
                    "Fleet"
                ]
            }
        },
        "/my/ships/{shipSymbol}": {
            "get": {
                "description": "Retrieve the details of a ship under your agent's ownership.",
                "operationId": "get-my-ship",
                "responses": {
                    "200": {
                        "content": {
                            "application/json": {
                                "schema": {
                                    "description": "",
                                    "properties": {
                                        "data": {
                                            "$ref": "#/components/schemas/Ship"
                                        }
                                    },
                                    "required": [
                                        "data"
                                    ],
                                    "type": "object"
                                }
                            }
                        },
                        "description": "Successfully fetched ship."
                    }
                },
                "security": [
                    {
                        "AgentToken": []
                    }
                ],
                "summary": "Get Ship",
                "tags": [
                    "Fleet"
                ]
            },
            "parameters": [
                {
                    "description": "The symbol of the ship.",
                    "in": "path",
                    "name": "shipSymbol",
                    "required": true,
                    "schema": {
                        "type": "string"
                    }
                }
            ]
        },
        "/my/ships/{shipSymbol}/cargo": {
            "parameters": [
                {
                    "description": "The symbol of the ship.",
                    "in": "path",
                    "name": "shipSymbol",
                    "required": true,
                    "schema": {
                        "type": "string"
                    }
                }
            ],
            "get": {
                "description": "Retrieve the cargo of a ship under your agent's ownership.",
                "operationId": "get-my-ship-cargo",
                "responses": {
                    "200": {
                        "content": {
                            "application/json": {
                                "schema": {
                                    "description": "",
                                    "properties": {
                                        "data": {
                                            "$ref": "#/components/schemas/ShipCargo"
                                        }
                                    },
                                    "required": [
                                        "data"
                                    ],
                                    "type": "object"
                                }
                            }
                        },
                        "description": "Successfully fetched ship's cargo."
                    }
                },
                "security": [
                    {
                        "AgentToken": []
                    }
                ],
                "summary": "Get Ship Cargo",
                "tags": [
                    "Fleet"
                ]
            }
        },
        "/my/ships/{shipSymbol}/orbit": {
            "parameters": [
                {
                    "description": "The symbol of the ship.",
                    "in": "path",
                    "name": "shipSymbol",
                    "required": true,
                    "schema": {
                        "type": "string"
                    }
                }
            ],
            "post": {
                "description": "Attempt to move your ship into orbit at its current location. The request will only succeed if your ship is capable of moving into orbit at the time of the request.\n\nOrbiting ships are able to do actions that require the ship to be above surface such as navigating or extracting, but cannot access elements in their current waypoint, such as the market or a shipyard.\n\nThe endpoint is idempotent - successive calls will succeed even if the ship is already in orbit.",
                "operationId": "orbit-ship",
                "responses": {
                    "200": {
                        "content": {
                            "application/json": {
                                "schema": {
                                    "title": "Orbit Ship 200 Response",
                                    "description": "",
                                    "properties": {
                                        "data": {
                                            "properties": {
                                                "nav": {
                                                    "$ref": "#/components/schemas/ShipNav"
                                                }
                                            },
                                            "type": "object",
                                            "required": [
                                                "nav"
                                            ]
                                        }
                                    },
                                    "required": [
                                        "data"
                                    ],
                                    "type": "object"
                                }
                            }
                        },
                        "description": "The ship has successfully moved into orbit at its current location."
                    }
                },
                "security": [
                    {
                        "AgentToken": []
                    }
                ],
                "summary": "Orbit Ship",
                "tags": [
                    "Fleet"
                ]
            }
        },
        "/my/ships/{shipSymbol}/refine": {
            "parameters": [
                {
                    "description": "The symbol of the ship.",
                    "in": "path",
                    "name": "shipSymbol",
                    "required": true,
                    "schema": {
                        "type": "string"
                    }
                }
            ],
            "post": {
                "description": "Attempt to refine the raw materials on your ship. The request will only succeed if your ship is capable of refining at the time of the request. In order to be able to refine, a ship must have goods that can be refined and have installed a `Refinery` module that can refine it.\n\nWhen refining, 30 basic goods will be converted into 10 processed goods.",
                "operationId": "ship-refine",
                "requestBody": {
                    "content": {
                        "application/json": {
                            "schema": {
                                "type": "object",
                                "properties": {
                                    "produce": {
                                        "description": "The type of good to produce out of the refining process.",
                                        "type": "string",
                                        "enum": [
                                            "IRON",
                                            "COPPER",
                                            "SILVER",
                                            "GOLD",
                                            "ALUMINUM",
                                            "PLATINUM",
                                            "URANITE",
                                            "MERITIUM",
                                            "FUEL"
                                        ]
                                    }
                                },
                                "required": [
                                    "produce"
                                ]
                            }
                        }
                    }
                },
                "responses": {
                    "201": {
                        "content": {
                            "application/json": {
                                "schema": {
                                    "title": "Ship Refine 201 Response",
                                    "type": "object",
                                    "properties": {
                                        "data": {
                                            "type": "object",
                                            "required": [
                                                "cargo",
                                                "cooldown",
                                                "produced",
                                                "consumed"
                                            ],
                                            "properties": {
                                                "cargo": {
                                                    "$ref": "#/components/schemas/ShipCargo"
                                                },
                                                "cooldown": {
                                                    "$ref": "#/components/schemas/Cooldown"
                                                },
                                                "produced": {
                                                    "type": "array",
                                                    "description": "Goods that were produced by this refining process.",
                                                    "items": {
                                                        "type": "object",
                                                        "properties": {
                                                            "tradeSymbol": {
                                                                "type": "string",
                                                                "description": "Symbol of the good."
                                                            },
                                                            "units": {
                                                                "type": "integer",
                                                                "description": "Amount of units of the good."
                                                            }
                                                        },
                                                        "required": [
                                                            "tradeSymbol",
                                                            "units"
                                                        ]
                                                    }
                                                },
                                                "consumed": {
                                                    "type": "array",
                                                    "description": "Goods that were consumed during this refining process.",
                                                    "items": {
                                                        "type": "object",
                                                        "properties": {
                                                            "tradeSymbol": {
                                                                "type": "string",
                                                                "description": "Symbol of the good."
                                                            },
                                                            "units": {
                                                                "type": "integer",
                                                                "description": "Amount of units of the good."
                                                            }
                                                        },
                                                        "required": [
                                                            "tradeSymbol",
                                                            "units"
                                                        ]
                                                    }
                                                }
                                            }
                                        }
                                    },
                                    "required": [
                                        "data"
                                    ]
                                }
                            }
                        },
                        "description": "The ship has successfully refined goods."
                    }
                },
                "security": [
                    {
                        "AgentToken": []
                    }
                ],
                "summary": "Ship Refine",
                "tags": [
                    "Fleet"
                ]
            }
        },
        "/my/ships/{shipSymbol}/chart": {
            "parameters": [
                {
                    "description": "The symbol of the ship.",
                    "in": "path",
                    "name": "shipSymbol",
                    "required": true,
                    "schema": {
                        "type": "string"
                    }
                }
            ],
            "post": {
                "description": "Command a ship to chart the waypoint at its current location.\n\nMost waypoints in the universe are uncharted by default. These waypoints have their traits hidden until they have been charted by a ship.\n\nCharting a waypoint will record your agent as the one who created the chart, and all other agents would also be able to see the waypoint's traits.",
                "operationId": "create-chart",
                "responses": {
                    "201": {
                        "content": {
                            "application/json": {
                                "schema": {
                                    "properties": {
                                        "data": {
                                            "properties": {
                                                "chart": {
                                                    "$ref": "#/components/schemas/Chart"
                                                },
                                                "waypoint": {
                                                    "$ref": "#/components/schemas/Waypoint"
                                                }
                                            },
                                            "required": [
                                                "chart",
                                                "waypoint"
                                            ],
                                            "type": "object"
                                        }
                                    },
                                    "type": "object",
                                    "required": [
                                        "data"
                                    ]
                                }
                            }
                        },
                        "description": "Created"
                    }
                },
                "security": [
                    {
                        "AgentToken": []
                    }
                ],
                "summary": "Create Chart",
                "tags": [
                    "Fleet"
                ]
            }
        },
        "/my/ships/{shipSymbol}/cooldown": {
            "get": {
                "description": "Retrieve the details of your ship's reactor cooldown. Some actions such as activating your jump drive, scanning, or extracting resources taxes your reactor and results in a cooldown.\n\nYour ship cannot perform additional actions until your cooldown has expired. The duration of your cooldown is relative to the power consumption of the related modules or mounts for the action taken.\n\nResponse returns a 204 status code (no-content) when the ship has no cooldown.",
                "operationId": "get-ship-cooldown",
                "responses": {
                    "200": {
                        "content": {
                            "application/json": {
                                "schema": {
                                    "description": "",
                                    "properties": {
                                        "data": {
                                            "$ref": "#/components/schemas/Cooldown"
                                        }
                                    },
                                    "required": [
                                        "data"
                                    ],
                                    "type": "object"
                                }
                            }
                        },
                        "description": "Succesfully fetched ship's cooldown."
                    },
                    "204": {
                        "description": "No cooldown."
                    }
                },
                "security": [
                    {
                        "AgentToken": []
                    }
                ],
                "summary": "Get Ship Cooldown",
                "tags": [
                    "Fleet"
                ]
            },
            "parameters": [
                {
                    "description": "The symbol of the ship.",
                    "in": "path",
                    "name": "shipSymbol",
                    "required": true,
                    "schema": {
                        "type": "string"
                    }
                }
            ]
        },
        "/my/ships/{shipSymbol}/dock": {
            "parameters": [
                {
                    "description": "The symbol of the ship.",
                    "in": "path",
                    "name": "shipSymbol",
                    "required": true,
                    "schema": {
                        "type": "string"
                    }
                }
            ],
            "post": {
                "description": "Attempt to dock your ship at its current location. Docking will only succeed if your ship is capable of docking at the time of the request.\n\nDocked ships can access elements in their current location, such as the market or a shipyard, but cannot do actions that require the ship to be above surface such as navigating or extracting.\n\nThe endpoint is idempotent - successive calls will succeed even if the ship is already docked.",
                "operationId": "dock-ship",
                "responses": {
                    "200": {
                        "content": {
                            "application/json": {
                                "schema": {
                                    "title": "Dock Ship 200 Response",
                                    "description": "",
                                    "properties": {
                                        "data": {
                                            "properties": {
                                                "nav": {
                                                    "$ref": "#/components/schemas/ShipNav"
                                                }
                                            },
                                            "required": [
                                                "nav"
                                            ],
                                            "type": "object"
                                        }
                                    },
                                    "required": [
                                        "data"
                                    ],
                                    "type": "object"
                                }
                            }
                        },
                        "description": "The ship has successfully docked at its current location."
                    }
                },
                "security": [
                    {
                        "AgentToken": []
                    }
                ],
                "summary": "Dock Ship",
                "tags": [
                    "Fleet"
                ]
            }
        },
        "/my/ships/{shipSymbol}/survey": {
            "parameters": [
                {
                    "description": "The symbol of the ship.",
                    "in": "path",
                    "name": "shipSymbol",
                    "required": true,
                    "schema": {
                        "type": "string"
                    }
                }
            ],
            "post": {
                "description": "Create surveys on a waypoint that can be extracted such as asteroid fields. A survey focuses on specific types of deposits from the extracted location. When ships extract using this survey, they are guaranteed to procure a high amount of one of the goods in the survey.\n\nIn order to use a survey, send the entire survey details in the body of the extract request.\n\nEach survey may have multiple deposits, and if a symbol shows up more than once, that indicates a higher chance of extracting that resource.\n\nYour ship will enter a cooldown after surveying in which it is unable to perform certain actions. Surveys will eventually expire after a period of time or will be exhausted after being extracted several times based on the survey's size. Multiple ships can use the same survey for extraction.\n\nA ship must have the `Surveyor` mount installed in order to use this function.",
                "operationId": "create-survey",
                "responses": {
                    "201": {
                        "content": {
                            "application/json": {
                                "schema": {
                                    "type": "object",
                                    "properties": {
                                        "data": {
                                            "type": "object",
                                            "required": [
                                                "cooldown",
                                                "surveys"
                                            ],
                                            "properties": {
                                                "cooldown": {
                                                    "$ref": "#/components/schemas/Cooldown"
                                                },
                                                "surveys": {
                                                    "type": "array",
                                                    "description": "Surveys created by this action.",
                                                    "items": {
                                                        "$ref": "#/components/schemas/Survey"
                                                    }
                                                }
                                            }
                                        }
                                    },
                                    "required": [
                                        "data"
                                    ]
                                }
                            }
                        },
                        "description": "Surveys has been created."
                    }
                },
                "security": [
                    {
                        "AgentToken": []
                    }
                ],
                "summary": "Create Survey",
                "tags": [
                    "Fleet"
                ]
            }
        },
        "/my/ships/{shipSymbol}/extract": {
            "parameters": [
                {
                    "description": "The ship symbol.",
                    "in": "path",
                    "name": "shipSymbol",
                    "required": true,
                    "schema": {
                        "type": "string"
                    }
                }
            ],
            "post": {
                "description": "Extract resources from a waypoint that can be extracted, such as asteroid fields, into your ship. Send an optional survey as the payload to target specific yields.\n\nThe ship must be in orbit to be able to extract and must have mining equipments installed that can extract goods, such as the `Gas Siphon` mount for gas-based goods or `Mining Laser` mount for ore-based goods.\n\nThe survey property is now deprecated. See the `extract/survey` endpoint for more details.",
                "operationId": "extract-resources",
                "requestBody": {
                    "content": {
                        "application/json": {
                            "schema": {
                                "properties": {
                                    "survey": {
                                        "deprecated": true,
                                        "$ref": "#/components/schemas/Survey"
                                    }
                                },
                                "type": "object"
                            }
                        }
                    }
                },
                "responses": {
                    "201": {
                        "content": {
                            "application/json": {
                                "schema": {
                                    "description": "",
                                    "properties": {
                                        "data": {
                                            "properties": {
                                                "cooldown": {
                                                    "$ref": "#/components/schemas/Cooldown"
                                                },
                                                "extraction": {
                                                    "$ref": "#/components/schemas/Extraction"
                                                },
                                                "cargo": {
                                                    "$ref": "#/components/schemas/ShipCargo"
                                                },
                                                "events": {
                                                    "type": "array",
                                                    "items": {
                                                        "oneOf": [
                                                            {
                                                                "$ref": "#/components/schemas/ShipConditionEvent"
                                                            }
                                                        ]
                                                    }
                                                }
                                            },
                                            "required": [
                                                "extraction",
                                                "cooldown",
                                                "cargo",
                                                "events"
                                            ],
                                            "type": "object"
                                        }
                                    },
                                    "required": [
                                        "data"
                                    ],
                                    "type": "object"
                                }
                            }
                        },
                        "description": "Extracted successfully."
                    }
                },
                "security": [
                    {
                        "AgentToken": []
                    }
                ],
                "summary": "Extract Resources",
                "tags": [
                    "Fleet"
                ]
            }
        },
        "/my/ships/{shipSymbol}/siphon": {
            "parameters": [
                {
                    "description": "The ship symbol.",
                    "in": "path",
                    "name": "shipSymbol",
                    "required": true,
                    "schema": {
                        "type": "string"
                    }
                }
            ],
            "post": {
                "description": "Siphon gases, such as hydrocarbon, from gas giants.\n\nThe ship must be in orbit to be able to siphon and must have siphon mounts and a gas processor installed.",
                "operationId": "siphon-resources",
                "responses": {
                    "201": {
                        "content": {
                            "application/json": {
                                "schema": {
                                    "description": "",
                                    "properties": {
                                        "data": {
                                            "properties": {
                                                "cooldown": {
                                                    "$ref": "#/components/schemas/Cooldown"
                                                },
                                                "siphon": {
                                                    "$ref": "#/components/schemas/Siphon"
                                                },
                                                "cargo": {
                                                    "$ref": "#/components/schemas/ShipCargo"
                                                },
                                                "events": {
                                                    "type": "array",
                                                    "items": {
                                                        "oneOf": [
                                                            {
                                                                "$ref": "#/components/schemas/ShipConditionEvent"
                                                            }
                                                        ]
                                                    }
                                                }
                                            },
                                            "required": [
                                                "siphon",
                                                "cooldown",
                                                "cargo",
                                                "events"
                                            ],
                                            "type": "object"
                                        }
                                    },
                                    "required": [
                                        "data"
                                    ],
                                    "type": "object"
                                }
                            }
                        },
                        "description": "Siphon successful."
                    }
                },
                "security": [
                    {
                        "AgentToken": []
                    }
                ],
                "summary": "Siphon Resources",
                "tags": [
                    "Fleet"
                ]
            }
        },
        "/my/ships/{shipSymbol}/extract/survey": {
            "parameters": [
                {
                    "description": "The ship symbol.",
                    "in": "path",
                    "name": "shipSymbol",
                    "required": true,
                    "schema": {
                        "type": "string"
                    }
                }
            ],
            "post": {
                "description": "Use a survey when extracting resources from a waypoint. This endpoint requires a survey as the payload, which allows your ship to extract specific yields.\n\nSend the full survey object as the payload which will be validated according to the signature. If the signature is invalid, or any properties of the survey are changed, the request will fail.",
                "operationId": "extract-resources-with-survey",
                "requestBody": {
                    "content": {
                        "application/json": {
                            "schema": {
                                "$ref": "#/components/schemas/Survey"
                            }
                        }
                    }
                },
                "responses": {
                    "201": {
                        "content": {
                            "application/json": {
                                "schema": {
                                    "description": "",
                                    "properties": {
                                        "data": {
                                            "properties": {
                                                "cooldown": {
                                                    "$ref": "#/components/schemas/Cooldown"
                                                },
                                                "extraction": {
                                                    "$ref": "#/components/schemas/Extraction"
                                                },
                                                "cargo": {
                                                    "$ref": "#/components/schemas/ShipCargo"
                                                },
                                                "events": {
                                                    "type": "array",
                                                    "items": {
                                                        "oneOf": [
                                                            {
                                                                "$ref": "#/components/schemas/ShipConditionEvent"
                                                            }
                                                        ]
                                                    }
                                                }
                                            },
                                            "required": [
                                                "extraction",
                                                "cooldown",
                                                "cargo",
                                                "events"
                                            ],
                                            "type": "object"
                                        }
                                    },
                                    "required": [
                                        "data"
                                    ],
                                    "type": "object"
                                }
                            }
                        },
                        "description": "Extracted successfully."
                    }
                },
                "security": [
                    {
                        "AgentToken": []
                    }
                ],
                "summary": "Extract Resources with Survey",
                "tags": [
                    "Fleet"
                ]
            }
        },
        "/my/ships/{shipSymbol}/jettison": {
            "parameters": [
                {
                    "description": "The ship symbol.",
                    "in": "path",
                    "name": "shipSymbol",
                    "required": true,
                    "schema": {
                        "type": "string"
                    }
                }
            ],
            "post": {
                "description": "Jettison cargo from your ship's cargo hold.",
                "operationId": "jettison",
                "requestBody": {
                    "content": {
                        "application/json": {
                            "schema": {
                                "type": "object",
                                "properties": {
                                    "symbol": {
                                        "$ref": "#/components/schemas/TradeSymbol"
                                    },
                                    "units": {
                                        "minimum": 1,
                                        "type": "integer",
                                        "description": "Amount of units to jettison of this good."
                                    }
                                },
                                "required": [
                                    "symbol",
                                    "units"
                                ]
                            }
                        }
                    }
                },
                "responses": {
                    "200": {
                        "content": {
                            "application/json": {
                                "schema": {
                                    "description": "",
                                    "properties": {
                                        "data": {
                                            "properties": {
                                                "cargo": {
                                                    "$ref": "#/components/schemas/ShipCargo"
                                                }
                                            },
                                            "required": [
                                                "cargo"
                                            ],
                                            "type": "object"
                                        }
                                    },
                                    "required": [
                                        "data"
                                    ],
                                    "type": "object"
                                }
                            }
                        },
                        "description": "Jettison successful."
                    }
                },
                "security": [
                    {
                        "AgentToken": []
                    }
                ],
                "summary": "Jettison Cargo",
                "tags": [
                    "Fleet"
                ]
            }
        },
        "/my/ships/{shipSymbol}/jump": {
            "parameters": [
                {
                    "description": "The ship symbol.",
                    "in": "path",
                    "name": "shipSymbol",
                    "required": true,
                    "schema": {
                        "type": "string"
                    }
                }
            ],
            "post": {
                "description": "Jump your ship instantly to a target connected waypoint. The ship must be in orbit to execute a jump.\n\nA unit of antimatter is purchased and consumed from the market when jumping. The price of antimatter is determined by the market and is subject to change. A ship can only jump to connected waypoints",
                "operationId": "jump-ship",
                "requestBody": {
                    "content": {
                        "application/json": {
                            "schema": {
                                "properties": {
                                    "waypointSymbol": {
                                        "description": "The symbol of the waypoint to jump to. The destination must be a connected waypoint.",
                                        "type": "string"
                                    }
                                },
                                "required": [
                                    "waypointSymbol"
                                ],
                                "type": "object"
                            }
                        }
                    }
                },
                "responses": {
                    "200": {
                        "content": {
                            "application/json": {
                                "schema": {
                                    "description": "",
                                    "properties": {
                                        "data": {
                                            "properties": {
                                                "nav": {
                                                    "$ref": "#/components/schemas/ShipNav"
                                                },
                                                "cooldown": {
                                                    "$ref": "#/components/schemas/Cooldown"
                                                },
                                                "transaction": {
                                                    "$ref": "#/components/schemas/MarketTransaction"
                                                },
                                                "agent": {
                                                    "$ref": "#/components/schemas/Agent"
                                                }
                                            },
                                            "required": [
                                                "nav",
                                                "cooldown",
                                                "transaction",
                                                "agent"
                                            ],
                                            "type": "object"
                                        }
                                    },
                                    "required": [
                                        "data"
                                    ],
                                    "type": "object"
                                }
                            }
                        },
                        "description": "Jump successful."
                    }
                },
                "security": [
                    {
                        "AgentToken": []
                    }
                ],
                "summary": "Jump Ship",
                "tags": [
                    "Fleet"
                ]
            }
        },
        "/my/ships/{shipSymbol}/navigate": {
            "parameters": [
                {
                    "description": "The ship symbol.",
                    "in": "path",
                    "name": "shipSymbol",
                    "required": true,
                    "schema": {
                        "type": "string"
                    }
                }
            ],
            "post": {
                "description": "Navigate to a target destination. The ship must be in orbit to use this function. The destination waypoint must be within the same system as the ship's current location. Navigating will consume the necessary fuel from the ship's manifest based on the distance to the target waypoint.\n\nThe returned response will detail the route information including the expected time of arrival. Most ship actions are unavailable until the ship has arrived at it's destination.\n\nTo travel between systems, see the ship's Warp or Jump actions.",
                "operationId": "navigate-ship",
                "requestBody": {
                    "content": {
                        "application/json": {
                            "schema": {
                                "properties": {
                                    "waypointSymbol": {
                                        "description": "The target destination.",
                                        "type": "string"
                                    }
                                },
                                "required": [
                                    "waypointSymbol"
                                ],
                                "type": "object"
                            }
                        }
                    },
                    "description": ""
                },
                "responses": {
                    "200": {
                        "content": {
                            "application/json": {
                                "schema": {
                                    "description": "",
                                    "properties": {
                                        "data": {
                                            "properties": {
                                                "fuel": {
                                                    "$ref": "#/components/schemas/ShipFuel"
                                                },
                                                "nav": {
                                                    "$ref": "#/components/schemas/ShipNav"
                                                },
                                                "events": {
                                                    "type": "array",
                                                    "items": {
                                                        "oneOf": [
                                                            {
                                                                "$ref": "#/components/schemas/ShipConditionEvent"
                                                            }
                                                        ]
                                                    }
                                                }
                                            },
                                            "required": [
                                                "nav",
                                                "fuel",
                                                "events"
                                            ],
                                            "type": "object"
                                        }
                                    },
                                    "required": [
                                        "data"
                                    ],
                                    "type": "object"
                                }
                            }
                        },
                        "description": "The successful transit information including the route details and changes to ship fuel. The route includes the expected time of arrival."
                    }
                },
                "security": [
                    {
                        "AgentToken": []
                    }
                ],
                "summary": "Navigate Ship",
                "tags": [
                    "Fleet"
                ]
            }
        },
        "/my/ships/{shipSymbol}/nav": {
            "parameters": [
                {
                    "description": "The ship symbol.",
                    "in": "path",
                    "name": "shipSymbol",
                    "required": true,
                    "schema": {
                        "type": "string"
                    }
                }
            ],
            "patch": {
                "description": "Update the nav configuration of a ship.\n\nCurrently only supports configuring the Flight Mode of the ship, which affects its speed and fuel consumption.",
                "operationId": "patch-ship-nav",
                "requestBody": {
                    "content": {
                        "application/json": {
                            "schema": {
                                "properties": {
                                    "flightMode": {
                                        "$ref": "#/components/schemas/ShipNavFlightMode"
                                    }
                                },
                                "type": "object"
                            }
                        }
                    }
                },
                "responses": {
                    "200": {
                        "content": {
                            "application/json": {
                                "schema": {
                                    "description": "",
                                    "properties": {
                                        "data": {
                                            "$ref": "#/components/schemas/ShipNav"
                                        }
                                    },
                                    "required": [
                                        "data"
                                    ],
                                    "type": "object"
                                }
                            }
                        },
                        "description": "The updated nav data of the ship."
                    }
                },
                "security": [
                    {
                        "AgentToken": []
                    }
                ],
                "summary": "Patch Ship Nav",
                "tags": [
                    "Fleet"
                ]
            },
            "get": {
                "description": "Get the current nav status of a ship.",
                "operationId": "get-ship-nav",
                "responses": {
                    "200": {
                        "content": {
                            "application/json": {
                                "schema": {
                                    "description": "",
                                    "properties": {
                                        "data": {
                                            "$ref": "#/components/schemas/ShipNav"
                                        }
                                    },
                                    "required": [
                                        "data"
                                    ],
                                    "type": "object"
                                }
                            }
                        },
                        "description": "The current nav status of the ship."
                    }
                },
                "security": [
                    {
                        "AgentToken": []
                    }
                ],
                "summary": "Get Ship Nav",
                "tags": [
                    "Fleet"
                ]
            }
        },
        "/my/ships/{shipSymbol}/warp": {
            "parameters": [
                {
                    "description": "The ship symbol.",
                    "in": "path",
                    "name": "shipSymbol",
                    "required": true,
                    "schema": {
                        "type": "string"
                    }
                }
            ],
            "post": {
                "description": "Warp your ship to a target destination in another system. The ship must be in orbit to use this function and must have the `Warp Drive` module installed. Warping will consume the necessary fuel from the ship's manifest.\n\nThe returned response will detail the route information including the expected time of arrival. Most ship actions are unavailable until the ship has arrived at its destination.",
                "operationId": "warp-ship",
                "requestBody": {
                    "content": {
                        "application/json": {
                            "schema": {
                                "properties": {
                                    "waypointSymbol": {
                                        "description": "The target destination.",
                                        "type": "string"
                                    }
                                },
                                "required": [
                                    "waypointSymbol"
                                ],
                                "type": "object"
                            }
                        }
                    },
                    "description": ""
                },
                "responses": {
                    "200": {
                        "content": {
                            "application/json": {
                                "schema": {
                                    "description": "",
                                    "properties": {
                                        "data": {
                                            "properties": {
                                                "fuel": {
                                                    "$ref": "#/components/schemas/ShipFuel"
                                                },
                                                "nav": {
                                                    "$ref": "#/components/schemas/ShipNav"
                                                }
                                            },
                                            "required": [
                                                "nav",
                                                "fuel"
                                            ],
                                            "type": "object"
                                        }
                                    },
                                    "required": [
                                        "data"
                                    ],
                                    "type": "object"
                                }
                            }
                        },
                        "description": "The successful transit information including the route details and changes to ship fuel. The route includes the expected time of arrival."
                    }
                },
                "security": [
                    {
                        "AgentToken": []
                    }
                ],
                "summary": "Warp Ship",
                "tags": [
                    "Fleet"
                ]
            }
        },
        "/my/ships/{shipSymbol}/sell": {
            "parameters": [
                {
                    "in": "path",
                    "name": "shipSymbol",
                    "required": true,
                    "schema": {
                        "type": "string"
                    },
                    "description": "Symbol of a ship."
                }
            ],
            "post": {
                "description": "Sell cargo in your ship to a market that trades this cargo. The ship must be docked in a waypoint that has the `Marketplace` trait in order to use this function.",
                "operationId": "sell-cargo",
                "requestBody": {
                    "content": {
                        "application/json": {
                            "schema": {
                                "title": "SellCargoRequest",
                                "type": "object",
                                "properties": {
                                    "symbol": {
                                        "$ref": "#/components/schemas/TradeSymbol"
                                    },
                                    "units": {
                                        "type": "integer",
                                        "description": "Amounts of units to sell of the selected good."
                                    }
                                },
                                "required": [
                                    "symbol",
                                    "units"
                                ]
                            }
                        }
                    }
                },
                "responses": {
                    "201": {
                        "content": {
                            "application/json": {
                                "schema": {
                                    "title": "Sell Cargo 201 Response",
                                    "description": "",
                                    "properties": {
                                        "data": {
                                            "properties": {
                                                "agent": {
                                                    "$ref": "#/components/schemas/Agent"
                                                },
                                                "cargo": {
                                                    "$ref": "#/components/schemas/ShipCargo"
                                                },
                                                "transaction": {
                                                    "$ref": "#/components/schemas/MarketTransaction"
                                                }
                                            },
                                            "required": [
                                                "cargo",
                                                "transaction",
                                                "agent"
                                            ],
                                            "type": "object"
                                        }
                                    },
                                    "required": [
                                        "data"
                                    ],
                                    "type": "object"
                                }
                            }
                        },
                        "description": "Cargo was successfully sold."
                    }
                },
                "security": [
                    {
                        "AgentToken": []
                    }
                ],
                "summary": "Sell Cargo",
                "tags": [
                    "Fleet"
                ]
            }
        },
        "/my/ships/{shipSymbol}/scan/systems": {
            "parameters": [
                {
                    "description": "The ship symbol.",
                    "in": "path",
                    "name": "shipSymbol",
                    "required": true,
                    "schema": {
                        "type": "string"
                    }
                }
            ],
            "post": {
                "description": "Scan for nearby systems, retrieving information on the systems' distance from the ship and their waypoints. Requires a ship to have the `Sensor Array` mount installed to use.\n\nThe ship will enter a cooldown after using this function, during which it cannot execute certain actions.",
                "operationId": "create-ship-system-scan",
                "responses": {
                    "201": {
                        "content": {
                            "application/json": {
                                "schema": {
                                    "type": "object",
                                    "properties": {
                                        "data": {
                                            "type": "object",
                                            "required": [
                                                "cooldown",
                                                "systems"
                                            ],
                                            "properties": {
                                                "cooldown": {
                                                    "$ref": "#/components/schemas/Cooldown"
                                                },
                                                "systems": {
                                                    "type": "array",
                                                    "description": "List of scanned systems.",
                                                    "items": {
                                                        "$ref": "#/components/schemas/ScannedSystem"
                                                    }
                                                }
                                            }
                                        }
                                    },
                                    "required": [
                                        "data"
                                    ]
                                }
                            }
                        },
                        "description": "Successfully scanned for nearby systems."
                    }
                },
                "security": [
                    {
                        "AgentToken": []
                    }
                ],
                "summary": "Scan Systems",
                "tags": [
                    "Fleet"
                ]
            }
        },
        "/my/ships/{shipSymbol}/scan/waypoints": {
            "parameters": [
                {
                    "description": "The ship symbol.",
                    "in": "path",
                    "name": "shipSymbol",
                    "required": true,
                    "schema": {
                        "type": "string"
                    }
                }
            ],
            "post": {
                "description": "Scan for nearby waypoints, retrieving detailed information on each waypoint in range. Scanning uncharted waypoints will allow you to ignore their uncharted state and will list the waypoints' traits.\n\nRequires a ship to have the `Sensor Array` mount installed to use.\n\nThe ship will enter a cooldown after using this function, during which it cannot execute certain actions.",
                "operationId": "create-ship-waypoint-scan",
                "responses": {
                    "201": {
                        "content": {
                            "application/json": {
                                "schema": {
                                    "type": "object",
                                    "properties": {
                                        "data": {
                                            "type": "object",
                                            "required": [
                                                "cooldown",
                                                "waypoints"
                                            ],
                                            "properties": {
                                                "cooldown": {
                                                    "$ref": "#/components/schemas/Cooldown"
                                                },
                                                "waypoints": {
                                                    "type": "array",
                                                    "description": "List of scanned waypoints.",
                                                    "items": {
                                                        "$ref": "#/components/schemas/ScannedWaypoint"
                                                    }
                                                }
                                            }
                                        }
                                    },
                                    "required": [
                                        "data"
                                    ]
                                }
                            }
                        },
                        "description": "Successfully scanned for nearby waypoints."
                    }
                },
                "security": [
                    {
                        "AgentToken": []
                    }
                ],
                "summary": "Scan Waypoints",
                "tags": [
                    "Fleet"
                ]
            }
        },
        "/my/ships/{shipSymbol}/scan/ships": {
            "parameters": [
                {
                    "description": "The ship symbol.",
                    "in": "path",
                    "name": "shipSymbol",
                    "required": true,
                    "schema": {
                        "type": "string"
                    }
                }
            ],
            "post": {
                "description": "Scan for nearby ships, retrieving information for all ships in range.\n\nRequires a ship to have the `Sensor Array` mount installed to use.\n\nThe ship will enter a cooldown after using this function, during which it cannot execute certain actions.",
                "operationId": "create-ship-ship-scan",
                "responses": {
                    "201": {
                        "content": {
                            "application/json": {
                                "schema": {
                                    "type": "object",
                                    "properties": {
                                        "data": {
                                            "type": "object",
                                            "required": [
                                                "cooldown",
                                                "ships"
                                            ],
                                            "properties": {
                                                "cooldown": {
                                                    "$ref": "#/components/schemas/Cooldown"
                                                },
                                                "ships": {
                                                    "type": "array",
                                                    "description": "List of scanned ships.",
                                                    "items": {
                                                        "$ref": "#/components/schemas/ScannedShip"
                                                    }
                                                }
                                            }
                                        }
                                    },
                                    "required": [
                                        "data"
                                    ]
                                }
                            }
                        },
                        "description": "Successfully scanned for nearby ships."
                    }
                },
                "security": [
                    {
                        "AgentToken": []
                    }
                ],
                "summary": "Scan Ships",
                "tags": [
                    "Fleet"
                ]
            }
        },
        "/my/ships/{shipSymbol}/refuel": {
            "parameters": [
                {
                    "description": "The ship symbol.",
                    "in": "path",
                    "name": "shipSymbol",
                    "required": true,
                    "schema": {
                        "type": "string"
                    }
                }
            ],
            "post": {
                "description": "Refuel your ship by buying fuel from the local market.\n\nRequires the ship to be docked in a waypoint that has the `Marketplace` trait, and the market must be selling fuel in order to refuel.\n\nEach fuel bought from the market replenishes 100 units in your ship's fuel.\n\nShips will always be refuel to their frame's maximum fuel capacity when using this action.",
                "operationId": "refuel-ship",
                "requestBody": {
                    "content": {
                        "application/json": {
                            "schema": {
                                "type": "object",
                                "properties": {
                                    "units": {
                                        "type": "integer",
                                        "description": "The amount of fuel to fill in the ship's tanks. When not specified, the ship will be refueled to its maximum fuel capacity. If the amount specified is greater than the ship's remaining capacity, the ship will only be refueled to its maximum fuel capacity. The amount specified is not in market units but in ship fuel units.",
                                        "example": "100",
                                        "minimum": 1
                                    },
                                    "fromCargo": {
                                        "type": "boolean",
                                        "description": "Wether to use the FUEL thats in your cargo or not. Default: false",
                                        "example": false
                                    }
                                }
                            }
                        }
                    }
                },
                "responses": {
                    "200": {
                        "content": {
                            "application/json": {
                                "schema": {
                                    "description": "",
                                    "properties": {
                                        "data": {
                                            "properties": {
                                                "agent": {
                                                    "$ref": "#/components/schemas/Agent"
                                                },
                                                "fuel": {
                                                    "$ref": "#/components/schemas/ShipFuel"
                                                },
                                                "transaction": {
                                                    "$ref": "#/components/schemas/MarketTransaction"
                                                }
                                            },
                                            "required": [
                                                "agent",
                                                "fuel",
                                                "transaction"
                                            ],
                                            "type": "object"
                                        }
                                    },
                                    "required": [
                                        "data"
                                    ],
                                    "type": "object"
                                }
                            }
                        },
                        "description": "Refueled successfully."
                    }
                },
                "security": [
                    {
                        "AgentToken": []
                    }
                ],
                "summary": "Refuel Ship",
                "tags": [
                    "Fleet"
                ]
            }
        },
        "/my/ships/{shipSymbol}/purchase": {
            "parameters": [
                {
                    "in": "path",
                    "name": "shipSymbol",
                    "required": true,
                    "schema": {
                        "type": "string"
                    },
                    "description": "The ship's symbol."
                }
            ],
            "post": {
                "description": "Purchase cargo from a market.\n\nThe ship must be docked in a waypoint that has `Marketplace` trait, and the market must be selling a good to be able to purchase it.\n\nThe maximum amount of units of a good that can be purchased in each transaction are denoted by the `tradeVolume` value of the good, which can be viewed by using the Get Market action.\n\nPurchased goods are added to the ship's cargo hold.",
                "operationId": "purchase-cargo",
                "requestBody": {
                    "content": {
                        "application/json": {
                            "schema": {
                                "title": "Purchase Cargo Request",
                                "type": "object",
                                "properties": {
                                    "symbol": {
                                        "$ref": "#/components/schemas/TradeSymbol"
                                    },
                                    "units": {
                                        "type": "integer",
                                        "description": "Amounts of units to purchase."
                                    }
                                },
                                "required": [
                                    "symbol",
                                    "units"
                                ]
                            }
                        }
                    }
                },
                "responses": {
                    "201": {
                        "content": {
                            "application/json": {
                                "schema": {
                                    "title": "Purchase Cargo 201 Response",
                                    "description": "",
                                    "properties": {
                                        "data": {
                                            "properties": {
                                                "agent": {
                                                    "$ref": "#/components/schemas/Agent"
                                                },
                                                "cargo": {
                                                    "$ref": "#/components/schemas/ShipCargo"
                                                },
                                                "transaction": {
                                                    "$ref": "#/components/schemas/MarketTransaction"
                                                }
                                            },
                                            "required": [
                                                "cargo",
                                                "transaction",
                                                "agent"
                                            ],
                                            "type": "object"
                                        }
                                    },
                                    "required": [
                                        "data"
                                    ],
                                    "type": "object"
                                }
                            }
                        },
                        "description": "Purchased goods successfully."
                    }
                },
                "security": [
                    {
                        "AgentToken": []
                    }
                ],
                "summary": "Purchase Cargo",
                "tags": [
                    "Fleet"
                ]
            }
        },
        "/my/ships/{shipSymbol}/transfer": {
            "parameters": [
                {
                    "in": "path",
                    "name": "shipSymbol",
                    "required": true,
                    "schema": {
                        "type": "string"
                    },
                    "description": "The transferring ship's symbol."
                }
            ],
            "post": {
                "description": "Transfer cargo between ships.\n\nThe receiving ship must be in the same waypoint as the transferring ship, and it must able to hold the additional cargo after the transfer is complete. Both ships also must be in the same state, either both are docked or both are orbiting.\n\nThe response body's cargo shows the cargo of the transferring ship after the transfer is complete.",
                "operationId": "transfer-cargo",
                "requestBody": {
                    "content": {
                        "application/json": {
                            "schema": {
                                "title": "Transfer Cargo Request",
                                "type": "object",
                                "properties": {
                                    "tradeSymbol": {
                                        "$ref": "#/components/schemas/TradeSymbol"
                                    },
                                    "units": {
                                        "type": "integer",
                                        "description": "Amount of units to transfer."
                                    },
                                    "shipSymbol": {
                                        "type": "string",
                                        "description": "The symbol of the ship to transfer to."
                                    }
                                },
                                "required": [
                                    "tradeSymbol",
                                    "units",
                                    "shipSymbol"
                                ]
                            }
                        }
                    }
                },
                "responses": {
                    "200": {
                        "content": {
                            "application/json": {
                                "schema": {
                                    "title": "Transfer Cargo 200 Response",
                                    "type": "object",
                                    "properties": {
                                        "data": {
                                            "type": "object",
                                            "required": [
                                                "cargo"
                                            ],
                                            "properties": {
                                                "cargo": {
                                                    "$ref": "#/components/schemas/ShipCargo"
                                                }
                                            }
                                        }
                                    },
                                    "required": [
                                        "data"
                                    ]
                                }
                            }
                        },
                        "description": "Transfer successful."
                    }
                },
                "security": [
                    {
                        "AgentToken": []
                    }
                ],
                "summary": "Transfer Cargo",
                "tags": [
                    "Fleet"
                ]
            }
        },
        "/my/ships/{shipSymbol}/negotiate/contract": {
            "parameters": [
                {
                    "in": "path",
                    "name": "shipSymbol",
                    "required": true,
                    "schema": {
                        "type": "string"
                    },
                    "description": "The ship's symbol."
                }
            ],
            "post": {
                "description": "Negotiate a new contract with the HQ.\n\nIn order to negotiate a new contract, an agent must not have ongoing or offered contracts over the allowed maximum amount. Currently the maximum contracts an agent can have at a time is 1.\n\nOnce a contract is negotiated, it is added to the list of contracts offered to the agent, which the agent can then accept. \n\nThe ship must be present at any waypoint with a faction present to negotiate a contract with that faction.",
                "operationId": "negotiateContract",
                "responses": {
                    "201": {
                        "content": {
                            "application/json": {
                                "schema": {
                                    "title": "Negotiate Contract 200 Response",
                                    "description": "",
                                    "properties": {
                                        "data": {
                                            "properties": {
                                                "contract": {
                                                    "$ref": "#/components/schemas/Contract"
                                                }
                                            },
                                            "required": [
                                                "contract"
                                            ],
                                            "type": "object"
                                        }
                                    },
                                    "required": [
                                        "data"
                                    ],
                                    "type": "object"
                                }
                            }
                        },
                        "description": "Successfully negotiated a new contract."
                    }
                },
                "security": [
                    {
                        "AgentToken": []
                    }
                ],
                "summary": "Negotiate Contract",
                "tags": [
                    "Fleet"
                ]
            }
        },
        "/my/ships/{shipSymbol}/mounts": {
            "parameters": [
                {
                    "in": "path",
                    "name": "shipSymbol",
                    "required": true,
                    "schema": {
                        "type": "string"
                    },
                    "description": "The ship's symbol."
                }
            ],
            "get": {
                "description": "Get the mounts installed on a ship.",
                "operationId": "get-mounts",
                "responses": {
                    "200": {
                        "content": {
                            "application/json": {
                                "schema": {
                                    "title": "Get Mounts 200 Response",
                                    "description": "",
                                    "properties": {
                                        "data": {
                                            "items": {
                                                "$ref": "#/components/schemas/ShipMount"
                                            },
                                            "type": "array"
                                        }
                                    },
                                    "required": [
                                        "data"
                                    ],
                                    "type": "object"
                                }
                            }
                        },
                        "description": "Got installed mounts."
                    }
                },
                "security": [
                    {
                        "AgentToken": []
                    }
                ],
                "summary": "Get Mounts",
                "tags": [
                    "Fleet"
                ]
            }
        },
        "/my/ships/{shipSymbol}/mounts/install": {
            "parameters": [
                {
                    "in": "path",
                    "name": "shipSymbol",
                    "required": true,
                    "schema": {
                        "type": "string"
                    },
                    "description": "The ship's symbol."
                }
            ],
            "post": {
                "description": "Install a mount on a ship.\n\nIn order to install a mount, the ship must be docked and located in a waypoint that has a `Shipyard` trait. The ship also must have the mount to install in its cargo hold.\n\nAn installation fee will be deduced by the Shipyard for installing the mount on the ship. ",
                "operationId": "install-mount",
                "requestBody": {
                    "content": {
                        "application/json": {
                            "schema": {
                                "title": "Install Mount Request",
                                "properties": {
                                    "symbol": {
                                        "type": "string"
                                    }
                                },
                                "required": [
                                    "symbol"
                                ],
                                "type": "object"
                            }
                        }
                    }
                },
                "responses": {
                    "201": {
                        "content": {
                            "application/json": {
                                "schema": {
                                    "title": "Install Mount 201 Response",
                                    "type": "object",
                                    "properties": {
                                        "data": {
                                            "type": "object",
                                            "required": [
                                                "agent",
                                                "mounts",
                                                "cargo",
                                                "transaction"
                                            ],
                                            "properties": {
                                                "agent": {
                                                    "$ref": "#/components/schemas/Agent"
                                                },
                                                "mounts": {
                                                    "type": "array",
                                                    "description": "List of installed mounts after the installation of the new mount.",
                                                    "items": {
                                                        "$ref": "#/components/schemas/ShipMount"
                                                    }
                                                },
                                                "cargo": {
                                                    "$ref": "#/components/schemas/ShipCargo"
                                                },
                                                "transaction": {
                                                    "$ref": "#/components/schemas/ShipModificationTransaction"
                                                }
                                            }
                                        }
                                    },
                                    "required": [
                                        "data"
                                    ]
                                }
                            }
                        },
                        "description": "Successfully installed the mount."
                    }
                },
                "security": [
                    {
                        "AgentToken": []
                    }
                ],
                "summary": "Install Mount",
                "tags": [
                    "Fleet"
                ]
            }
        },
        "/my/ships/{shipSymbol}/mounts/remove": {
            "parameters": [
                {
                    "in": "path",
                    "name": "shipSymbol",
                    "required": true,
                    "schema": {
                        "type": "string"
                    },
                    "description": "The ship's symbol."
                }
            ],
            "post": {
                "description": "Remove a mount from a ship.\n\nThe ship must be docked in a waypoint that has the `Shipyard` trait, and must have the desired mount that it wish to remove installed.\n\nA removal fee will be deduced from the agent by the Shipyard.",
                "operationId": "remove-mount",
                "requestBody": {
                    "content": {
                        "application/json": {
                            "schema": {
                                "title": "Remove Mount Request",
                                "type": "object",
                                "properties": {
                                    "symbol": {
                                        "type": "string",
                                        "description": "The symbol of the mount to remove."
                                    }
                                },
                                "required": [
                                    "symbol"
                                ]
                            }
                        }
                    }
                },
                "responses": {
                    "201": {
                        "content": {
                            "application/json": {
                                "schema": {
                                    "title": "Remove Mount 201 Response",
                                    "type": "object",
                                    "properties": {
                                        "data": {
                                            "type": "object",
                                            "required": [
                                                "agent",
                                                "mounts",
                                                "cargo",
                                                "transaction"
                                            ],
                                            "properties": {
                                                "agent": {
                                                    "$ref": "#/components/schemas/Agent"
                                                },
                                                "mounts": {
                                                    "type": "array",
                                                    "description": "List of installed mounts after the removal of the selected mount.",
                                                    "items": {
                                                        "$ref": "#/components/schemas/ShipMount"
                                                    }
                                                },
                                                "cargo": {
                                                    "$ref": "#/components/schemas/ShipCargo"
                                                },
                                                "transaction": {
                                                    "$ref": "#/components/schemas/ShipModificationTransaction"
                                                }
                                            }
                                        }
                                    },
                                    "required": [
                                        "data"
                                    ]
                                }
                            }
                        },
                        "description": "Successfully removed the mount."
                    }
                },
                "security": [
                    {
                        "AgentToken": []
                    }
                ],
                "summary": "Remove Mount",
                "tags": [
                    "Fleet"
                ]
            }
        },
        "/my/ships/{shipSymbol}/scrap": {
            "parameters": [
                {
                    "description": "The ship symbol.",
                    "in": "path",
                    "name": "shipSymbol",
                    "required": true,
                    "schema": {
                        "type": "string"
                    }
                }
            ],
            "get": {
                "x-preview-feature": true,
                "description": "Get the amount of value that will be returned when scrapping a ship.",
                "operationId": "get-scrap-ship",
                "responses": {
                    "200": {
                        "content": {
                            "application/json": {
                                "schema": {
                                    "description": "",
                                    "properties": {
                                        "data": {
                                            "properties": {
                                                "transaction": {
                                                    "$ref": "#/components/schemas/ScrapTransaction"
                                                }
                                            },
                                            "required": [
                                                "transaction"
                                            ],
                                            "type": "object"
                                        }
                                    },
                                    "required": [
                                        "data"
                                    ],
                                    "type": "object"
                                }
                            }
                        },
                        "description": "Successfully retrieved the amount of value that will be returned when scrapping a ship."
                    }
                },
                "security": [
                    {
                        "AgentToken": []
                    }
                ],
                "summary": "Get Scrap Ship",
                "tags": [
                    "Fleet"
                ]
            },
            "post": {
                "x-preview-feature": true,
                "description": "Scrap a ship, removing it from the game and returning a portion of the ship's value to the agent. The ship must be docked in a waypoint that has the `Shipyard` trait in order to use this function. To preview the amount of value that will be returned, use the Get Ship action.",
                "operationId": "scrap-ship",
                "responses": {
                    "200": {
                        "content": {
                            "application/json": {
                                "schema": {
                                    "description": "",
                                    "properties": {
                                        "data": {
                                            "properties": {
                                                "agent": {
                                                    "$ref": "#/components/schemas/Agent"
                                                },
                                                "transaction": {
                                                    "$ref": "#/components/schemas/ScrapTransaction"
                                                }
                                            },
                                            "required": [
                                                "agent",
                                                "transaction"
                                            ],
                                            "type": "object"
                                        }
                                    },
                                    "required": [
                                        "data"
                                    ],
                                    "type": "object"
                                }
                            }
                        },
                        "description": "Ship scrapped successfully."
                    }
                },
                "security": [
                    {
                        "AgentToken": []
                    }
                ],
                "summary": "Scrap Ship",
                "tags": [
                    "Fleet"
                ]
            }
        },
        "/my/ships/{shipSymbol}/repair": {
            "parameters": [
                {
                    "description": "The ship symbol.",
                    "in": "path",
                    "name": "shipSymbol",
                    "required": true,
                    "schema": {
                        "type": "string"
                    }
                }
            ],
            "get": {
                "x-preview-feature": true,
                "description": "Get the cost of repairing a ship.",
                "operationId": "get-repair-ship",
                "responses": {
                    "200": {
                        "content": {
                            "application/json": {
                                "schema": {
                                    "description": "",
                                    "properties": {
                                        "data": {
                                            "properties": {
                                                "transaction": {
                                                    "$ref": "#/components/schemas/RepairTransaction"
                                                }
                                            },
                                            "required": [
                                                "transaction"
                                            ],
                                            "type": "object"
                                        }
                                    },
                                    "required": [
                                        "data"
                                    ],
                                    "type": "object"
                                }
                            }
                        },
                        "description": "Successfully retrieved the cost of repairing a ship."
                    }
                },
                "security": [
                    {
                        "AgentToken": []
                    }
                ],
                "summary": "Get Repair Ship",
                "tags": [
                    "Fleet"
                ]
            },
            "post": {
                "x-preview-feature": true,
                "description": "Repair a ship, restoring the ship to maximum condition. The ship must be docked at a waypoint that has the `Shipyard` trait in order to use this function. To preview the cost of repairing the ship, use the Get action.",
                "operationId": "repair-ship",
                "responses": {
                    "200": {
                        "content": {
                            "application/json": {
                                "schema": {
                                    "description": "",
                                    "properties": {
                                        "data": {
                                            "properties": {
                                                "agent": {
                                                    "$ref": "#/components/schemas/Agent"
                                                },
                                                "ship": {
                                                    "$ref": "#/components/schemas/Ship"
                                                },
                                                "transaction": {
                                                    "$ref": "#/components/schemas/RepairTransaction"
                                                }
                                            },
                                            "required": [
                                                "agent",
                                                "ship",
                                                "transaction"
                                            ],
                                            "type": "object"
                                        }
                                    },
                                    "required": [
                                        "data"
                                    ],
                                    "type": "object"
                                }
                            }
                        },
                        "description": "Ship repaired successfully."
                    }
                },
                "security": [
                    {
                        "AgentToken": []
                    }
                ],
                "summary": "Repair Ship",
                "tags": [
                    "Fleet"
                ]
            }
        }
    }
}
