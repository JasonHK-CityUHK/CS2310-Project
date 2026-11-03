[![This article is licensed under a Creative Commons Attribution-ShareAlike 3.0 license. Derivative works must be licensed using the same or a compatible license.](https://minecraft.wiki/images/Cc-by-sa.svg?fc1a9)](https://creativecommons.org/licenses/by-sa/3.0/ "This article is licensed under a Creative Commons Attribution-ShareAlike 3.0 license. Derivative works must be licensed using the same or a compatible license.")

# Java Edition protocol/Registries  Share article feedback

From Minecraft Wiki

< [Java Edition protocol](https://minecraft.wiki/w/Java_Edition_protocol "Java Edition protocol")

[Jump to navigation](https://minecraft.wiki/w/Java_Edition_protocol/Registries#mw-head) [Jump to search](https://minecraft.wiki/w/Java_Edition_protocol/Registries#searchInput)

See also: [Identifier § Registries and registry objects](https://minecraft.wiki/w/Identifier#Registries_and_registry_objects "Identifier")

**Registries** are repositories of data that contain entries pertaining to certain aspects of the game, such as the world, the player, among others. Each registry enumerates entries of a certain type, such as `minecraft:block` or `minecraft:enchantment`, assigning each entry a [namespaced identifier](https://minecraft.wiki/w/Namespaced_identifier "Namespaced identifier"), a numeric ID, and [tags](https://minecraft.wiki/w/Tag_(Java_Edition) "Tag (Java Edition)").

The contents of **built-in registries** are fixed for a given protocol version. These registries can only be changed through [modding](https://minecraft.wiki/w/Modding "Modding"). **Data-driven registries** on the other hand can be modified through [data packs](https://minecraft.wiki/w/Data_packs "Data packs"). Some data-driven registries are only used by the server, while other **synchronized registries** are sent over the network when a player connects, and used by both the client and the server. This ability for the server to send customized registries to the client was introduced in 1.16.3, and allows for a great deal of customization over certain features of the game.

Of these, synchronized registries demand the most consideration from a protocol implementer. Supporting built-in registries properly is also important, as their contents, and consequently IDs, are liable to change between versions.

## Contents

- [1Built-in registries](https://minecraft.wiki/w/Java_Edition_protocol/Registries#Built-in_registries)
  - [1.1List of built-in registries](https://minecraft.wiki/w/Java_Edition_protocol/Registries#List_of_built-in_registries)
- [2Synchronized registries](https://minecraft.wiki/w/Java_Edition_protocol/Registries#Synchronized_registries)
  - [2.1Obtaining vanilla registry data](https://minecraft.wiki/w/Java_Edition_protocol/Registries#Obtaining_vanilla_registry_data)
  - [2.2Known packs negotiation](https://minecraft.wiki/w/Java_Edition_protocol/Registries#Known_packs_negotiation)
  - [2.3List of synchronized registries](https://minecraft.wiki/w/Java_Edition_protocol/Registries#List_of_synchronized_registries)
    - [2.3.1Banner pattern requirements](https://minecraft.wiki/w/Java_Edition_protocol/Registries#Banner_pattern_requirements)
    - [2.3.2Damage type requirements](https://minecraft.wiki/w/Java_Edition_protocol/Registries#Damage_type_requirements)
    - [2.3.3Instrument requirements](https://minecraft.wiki/w/Java_Edition_protocol/Registries#Instrument_requirements)
    - [2.3.4Jukebox song requirements](https://minecraft.wiki/w/Java_Edition_protocol/Registries#Jukebox_song_requirements)
    - [2.3.5Trim material requirements](https://minecraft.wiki/w/Java_Edition_protocol/Registries#Trim_material_requirements)
    - [2.3.6Dimension type requirements](https://minecraft.wiki/w/Java_Edition_protocol/Registries#Dimension_type_requirements)
    - [2.3.7Biome requirements](https://minecraft.wiki/w/Java_Edition_protocol/Registries#Biome_requirements)
    - [2.3.8Chicken variant requirements](https://minecraft.wiki/w/Java_Edition_protocol/Registries#Chicken_variant_requirements)

## Built-in registries

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Registries?section=1&veaction=edit "Edit section: Built-in registries") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Registries?action=edit&section=1 "Edit section's source code: Built-in registries")\]

These registries are defined directly in Minecraft's code, and can only be changed though modding. The client and server implicitly agree on which numeric IDs correspond to which entries. Unlike [pre-flattening block and item IDs](https://minecraft.wiki/w/Java_Edition_pre-flattening_data_values "Java Edition pre-flattening data values"), these IDs can and often do change between versions.

For versions 1.14 and above the mapping from names to IDs can be obtained from the built-in [data generators](https://minecraft.wiki/w/Minecraft_Wiki:Projects/wiki.vg_merge/Data_Generators#Registries_report "Minecraft Wiki:Projects/wiki.vg merge/Data Generators").

### List of built-in registries

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Registries?section=2&veaction=edit "Edit section: List of built-in registries") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Registries?action=edit&section=2 "Edit section's source code: List of built-in registries")\]

This list only includes built-in registries that are used directly in the protocol, including ones that are only referenced in [Update Tags](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Update_Tags "Java Edition protocol/Packets") but excluding those that are only referenced in registry data NBT.

| Name | Entries | Description |
| --- | --- | --- |
| `minecraft:attribute` | [Entries](https://minecraft.wiki/w/Attribute#Attributes "Attribute") | Entity [attributes](https://minecraft.wiki/w/Attribute "Attribute"). |
| `minecraft:block` | [Entries](https://minecraft.wiki/w/Java_Edition_data_values/Blocks "Java Edition data values/Blocks") | Types of [blocks](https://minecraft.wiki/w/Block "Block"). Note that the IDs in this registry are separate from (but related to) block state IDs. |
| `minecraft:block_entity_type` | [Entries](https://minecraft.wiki/w/Block_entity_format#Types "Block entity format") | Types of [block entities](https://minecraft.wiki/w/Block_entities "Block entities"). |
| `minecraft:consume_effect_type` | [Entries](https://minecraft.wiki/w/Java_Edition_protocol/Slot_Data#Consume_Effect "Java Edition protocol/Slot Data") |  |
| `minecraft:custom_stat` | [Entries](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Award_Statistics "Java Edition protocol/Packets") | [Statistics](https://minecraft.wiki/w/Statistics "Statistics") which do not fit into any of the other categories. |
| `minecraft:data_component_type` | [Entries](https://minecraft.wiki/w/Java_Edition_protocol/Slot_Data#Structured_components "Java Edition protocol/Slot Data") | [Data components](https://minecraft.wiki/w/Data_component "Data component"). |
| `minecraft:entity_type` | [Entries](https://minecraft.wiki/w/Java_Edition_protocol/Entity_metadata#Entities "Java Edition protocol/Entity metadata") | Types of [entities](https://minecraft.wiki/w/Entities "Entities"). |
| `minecraft:fluid` | [Entries](https://minecraft.wiki/w/Java_Edition_data_values#Fluids "Java Edition data values") | Types of [fluids](https://minecraft.wiki/w/Fluid "Fluid"). Currently only used in the protocol in tag definitions. |
| `minecraft:game_event` | [Entries](https://minecraft.wiki/w/Skulk_Sensor#Vibration_frequencies "Skulk Sensor") | Sources of [vibrations](https://minecraft.wiki/w/Vibrations "Vibrations") detected by [sculk](https://minecraft.wiki/w/Sculk "Sculk") components and [wardens](https://minecraft.wiki/w/Warden "Warden"). |
| `minecraft:item` | [Entries](https://minecraft.wiki/w/Java_Edition_data_values/Items "Java Edition data values/Items") | Types of [items](https://minecraft.wiki/w/Item "Item"). |
| `minecraft:menu` | [Entries](https://minecraft.wiki/w/Java_Edition_protocol/Inventory#Types "Java Edition protocol/Inventory") | Types of [container](https://minecraft.wiki/w/Container "Container") windows. |
| `minecraft:mob_effect` | [Entries](https://minecraft.wiki/w/Effect#Descriptions "Effect") | Types of [status effects](https://minecraft.wiki/w/Status_effects "Status effects"). |
| `minecraft:particle_type` | [Entries](https://minecraft.wiki/w/Java_Edition_protocol/Particles "Java Edition protocol/Particles") | Types of [particle](https://minecraft.wiki/w/Particles_(Java_Edition) "Particles (Java Edition)") effects. |
| `minecraft:potion` | [Entries](https://minecraft.wiki/w/Potion#Item_data "Potion") | Built-in [potion](https://minecraft.wiki/w/Potion "Potion") types. Note that these have "long" and "strong" variants, as would be seen on brewing. |
| `minecraft:recipe_book_category` |  | [Recipe book](https://minecraft.wiki/w/Recipe_book "Recipe book") tabs. |
| `minecraft:recipe_display` | [Entries](https://minecraft.wiki/w/Java_Edition_protocol/Recipes#Recipe_Display_types "Java Edition protocol/Recipes") |  |
| `minecraft:slot_display` | [Entries](https://minecraft.wiki/w/Java_Edition_protocol/Recipes#Slot_Display_types "Java Edition protocol/Recipes") |  |
| `minecraft:sound_event` | [Entries](https://minecraft.wiki/w/Sounds.json#Sound_events "Sounds.json") | Built-in [sound events](https://minecraft.wiki/w/Sound_event "Sound event"). |
| `minecraft:stat_type` | [Entries](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Award_Statistics "Java Edition protocol/Packets") | [Statistic](https://minecraft.wiki/w/Statistic "Statistic") categories. |
| `minecraft:villager_type` | [Entries](https://minecraft.wiki/w/Villager#Type_data_values "Villager") | [Villager](https://minecraft.wiki/w/Villager "Villager") biome types. |

## Synchronized registries

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Registries?section=3&veaction=edit "Edit section: Synchronized registries") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Registries?action=edit&section=3 "Edit section's source code: Synchronized registries")\]

The server sends these registries to the client via [Registry Data](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Registry_Data "Java Edition protocol/Packets") packets during the configuration phase, one packet for each registry.

| Packet ID | State | Bound To | Field Name | Field Type | Notes |
| --- | --- | --- | --- | --- | --- |
| [Varies](https://minecraft.wiki/w/Minecraft_Wiki:Projects/wiki.vg_merge/Protocol#Registry_Data "Minecraft Wiki:Projects/wiki.vg merge/Protocol") | Configuration | Client | Registry ID | [Identifier](https://minecraft.wiki/w/Java_Edition_protocol/Data_types#Type:Identifier "Java Edition protocol/Data types") | Name of the registry, such as `minecraft:dimension_type`. |
| Entries | Entry ID | [Prefixed Array](https://minecraft.wiki/w/Java_Edition_protocol/Data_types#Type:Prefixed_Array "Java Edition protocol/Data types") | [Identifier](https://minecraft.wiki/w/Java_Edition_protocol/Data_types#Type:Identifier "Java Edition protocol/Data types") | Name of the entry, such as `minecraft:overworld`. |
| Data | [Prefixed Optional](https://minecraft.wiki/w/Java_Edition_protocol/Data_types#Type:Prefixed_Optional "Java Edition protocol/Data types") [NBT](https://minecraft.wiki/w/Java_Edition_protocol/Data_types#Type:NBT "Java Edition protocol/Data types") | Entry data. If omitted, sourced from the selected [known packs](https://minecraft.wiki/w/Java_Edition_protocol/Registries#Known_packs_negotiation). |

The ordering of the entries in the Entries array defines the numeric IDs that they will be assigned to, starting from 0 and counting upwards. It is essential to maintain consistency between server and client, since many parts of the protocol reference these entries by their ID. The client will disconnect upon receiving a reference to a non-existing entry.

The NBT data of registry entries has the same structure as their definitions in [data packs](https://minecraft.wiki/w/Data_packs "Data packs"), but [represented in NBT instead of JSON](https://minecraft.wiki/w/NBT_format#Conversion_from_JSON "NBT format"). The format for each registry is defined in the [list of registries below](https://minecraft.wiki/w/Java_Edition_protocol/Registries#List_of_synchronized_registries).

### Obtaining vanilla registry data

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Registries?section=4&veaction=edit "Edit section: Obtaining vanilla registry data") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Registries?action=edit&section=4 "Edit section's source code: Obtaining vanilla registry data")\]

The default contents of data-driven registries are defined as JSON in the default [data pack](https://minecraft.wiki/w/Data_pack "Data pack"), which is located inside both [client.jar](https://minecraft.wiki/w/Client.jar "Client.jar") and [server.jar](https://minecraft.wiki/w/Server.jar "Server.jar") under data/. These files can be extracted using any ZIP extraction utility. Note however that since 1.18 the server.jar (but not client.jar) distributed by Mojang is wrapped inside a [bundler](https://minecraft.wiki/w/Server.jar#Bundler_options "Server.jar"), and extracting the data pack requires first extracting the inner server.jar located at META-INF/versions/\*/server-\*.jar from the outer server.jar.

Alternatively, the data is available as a single JSON file for the following versions:

- [1.21](https://gist.github.com/Mansitoh/e6c5cf8bbf17e9faf4e4e75bb3f4789d)
- [1.20.6](https://gist.github.com/WinX64/ab8c7a8df797c273b32d3a3b66522906)
- [1.20.2](https://gist.github.com/WinX64/3675ffee90360e9fc1e45074e49f6ede)
- [1.20.1](https://gist.github.com/WinX64/2d257d3df3c7ab9c4b02dc90be881ab2)
- [1.19.2](https://gist.github.com/nikes/aff59b758a807858da131a1881525b14)
- [1.19](https://gist.github.com/rj00a/f2970a8ce4d09477ec8f16003b9dce86)

### Known packs negotiation

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Registries?section=5&veaction=edit "Edit section: Known packs negotiation") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Registries?action=edit&section=5 "Edit section's source code: Known packs negotiation")\]

In order to save bandwidth, the client and server can negotiate which data packs are known by both peers, and avoid sending NBT sourced from those packs over the network. In practice the vanilla client and server as of 1.21.8 only recognize one data pack, `minecraft:core`, which contains the default definitions. Data from custom data packs is always sent over the network.

1. **S** → **C**: [Known Packs (clientbound)](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Known_Packs_(clientbound) "Java Edition protocol/Packets") (with all data packs known by the server)
2. **C** → **S**: [Known Packs (serverbound)](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Known_Packs_(serverbound) "Java Edition protocol/Packets") (with the subset of data packs also known by the client)
3. _Server computes the mutually supported data packs_
4. **S** → **C**: Multiple [Registry Data](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Registry_Data "Java Edition protocol/Packets") (for each registry, containing all entries, but excluding mutually known NBT)
5. **S** → **C**: [Update Tags](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Update_Tags "Java Edition protocol/Packets")
6. _Client accumulates registry and tag data for later resolution_
7. **S** → **C**: [Finish Configuration](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Finish_Configuration "Java Edition protocol/Packets")
8. _Client resolves registry and tag data, loading data from packs when requested, and detecting unbound references to entries and tags_

When resolving an entry from a Registry Data packet, the client will always use the NBT data specified in the packet if it is present. Otherwise it will look for the data in the selected known packs. Tag data is never sourced from known packs, and must always be sent by the server in full.

**If an entry is not mentioned in a Registry Data packet, it will not exist in the game session, even if it exists in one of the known packs. All entries that will be used in the session must be listed in Registry Data packets; only the NBT part can be omitted.**

When multiple known packs are selected, the client will combine them the same way resource and data packs are normally combined. The packs are listed in Clientbound Known Packs from the bottom of the stack to the top, so earlier packs are overridden by later ones.

A custom server implementation may choose to skip sending Clientbound Known Packs, in which case all NBT data must be present in the Registry Data packets, or to require that the client knows about `minecraft:core`, in which case no NBT needs to be sent. Similarly a custom client may respond with an empty Serverbound Known Packs packet, and require the server to send all registry NBT. All of these incomplete implementations are compatible with the vanilla implementation, but interoperability between them will be limited.

### List of synchronized registries

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Registries?section=6&veaction=edit "Edit section: List of synchronized registries") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Registries?action=edit&section=6 "Edit section's source code: List of synchronized registries")\]

| Name | NBT format | Requirements | Description |
| --- | --- | --- | --- |
| `minecraft:banner_pattern` | [NBT format](https://minecraft.wiki/w/Banner_pattern_definition#JSON_Format "Banner pattern definition") | [See below](https://minecraft.wiki/w/Java_Edition_protocol/Registries#Banner_pattern_requirements) | Types of [banner patterns](https://minecraft.wiki/w/Banner#Patterns "Banner"), specifying their textures. |
| `minecraft:chat_type` | [NBT format](https://minecraft.wiki/w/Chat_type#JSON_format "Chat type") | Optional | [Chat types](https://minecraft.wiki/w/Chat_type "Chat type"), specifying how [chat](https://minecraft.wiki/w/Chat "Chat") messages are formatted. Referenced in the [Disguised Chat Message](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Disguised_Chat_Message "Java Edition protocol/Packets") and [Player Chat Message](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Player_Chat_Message "Java Edition protocol/Packets") packets. |
| `minecraft:damage_type` | [NBT format](https://minecraft.wiki/w/Damage_type#JSON_format "Damage type") | [See below](https://minecraft.wiki/w/Java_Edition_protocol/Registries#Damage_type_requirements) | [Damage types](https://minecraft.wiki/w/Damage_type "Damage type"), specifying audiovisual effects generated by damage events. Referenced in the [Damage Event](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Damage_Event "Java Edition protocol/Packets") packet. |
| `minecraft:dialog` | [NBT format](https://minecraft.wiki/w/Dialog#Dialog_format "Dialog") | Optional | Types of [dialogs](https://minecraft.wiki/w/Dialog "Dialog"). |
| `minecraft:dimension_type` | [NBT format](https://minecraft.wiki/w/Dimension_type#JSON_format "Dimension type") | [See below](https://minecraft.wiki/w/Java_Edition_protocol/Registries#Dimension_type_requirements) | Types of [dimensions](https://minecraft.wiki/w/Dimension "Dimension"), specifying characteristics such as the [build height limit](https://minecraft.wiki/w/Build_height_limit "Build height limit"). Referenced in the [Login (play)](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Login_(play) "Java Edition protocol/Packets") and [Respawn](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Respawn "Java Edition protocol/Packets") packets. |
| `minecraft:enchantment` | [NBT format](https://minecraft.wiki/w/Enchantment_definition#JSON_format "Enchantment definition") | Optional | Types of [enchantments](https://minecraft.wiki/w/Enchantment "Enchantment"). |
| `minecraft:instrument` | [NBT format](https://minecraft.wiki/w/Instrument_definition#JSON_Format "Instrument definition") | [See below](https://minecraft.wiki/w/Java_Edition_protocol/Registries#Instrument_requirements) | [Goat horn](https://minecraft.wiki/w/Goat_horn "Goat horn") instruments, specifying their tooltip description and the sound event used when the local player uses a goat horn. |
| `minecraft:jukebox_song` | [NBT format](https://minecraft.wiki/w/Jukebox_song_definition#JSON_format "Jukebox song definition") | [See below](https://minecraft.wiki/w/Java_Edition_protocol/Registries#Jukebox_song_requirements) | Types of [music discs](https://minecraft.wiki/w/Music_disc "Music disc"). |
| `minecraft:painting_variant` | [NBT format](https://minecraft.wiki/w/Painting_variant_definition#JSON_Format "Painting variant definition") | Non-empty | [Painting variants](https://minecraft.wiki/w/Painting_variant "Painting variant"). |
| `minecraft:sulfur_cube_archetype` | [NBT format](https://minecraft.wiki/w/Sulfur_cube_archetype_definition#JSON_format "Sulfur cube archetype definition") | Non-empty | [Sulfur cube archetypes](https://minecraft.wiki/w/Sulfur_cube_archetype "Sulfur cube archetype"). |
| `minecraft:test_environment` | [NBT format](https://minecraft.wiki/w/Test_environment_definition#JSON_Format "Test environment definition") | Optional | [GameTest](https://minecraft.wiki/w/GameTest "GameTest") environments. |
| `minecraft:test_instance` | [NBT format](https://minecraft.wiki/w/Test_instance_definition#JSON_Format "Test instance definition") | Optional | [GameTest](https://minecraft.wiki/w/GameTest "GameTest") instances. |
| `minecraft:timeline` | [NBT format](https://minecraft.wiki/w/Timeline#JSON_format "Timeline") | Optional | [Timelines](https://minecraft.wiki/w/Timeline "Timeline"), which can manipulate environment attributes on the client based on the time values of world clocks. |
| `minecraft:trim_material` | [NBT format](https://minecraft.wiki/w/Armor_trim_definition#Trim_material "Armor trim definition") | [See below](https://minecraft.wiki/w/Java_Edition_protocol/Registries#Trim_material_requirements) | [Armor trim](https://minecraft.wiki/w/Smithing#Trimming "Smithing") materials. |
| `minecraft:trim_pattern` | [NBT format](https://minecraft.wiki/w/Armor_trim_definition#Trim_pattern "Armor trim definition") | Optional | [Armor trim](https://minecraft.wiki/w/Smithing#Trimming "Smithing") patterns. |
| `minecraft:world_clock` | [NBT format](https://minecraft.wiki/w/World_clock#Format "World clock") | Optional | [World clocks](https://minecraft.wiki/w/World_clock "World clock"). |
| `minecraft:worldgen/biome` | [NBT format](https://minecraft.wiki/w/Biome_definition#JSON_format "Biome definition") | [See below](https://minecraft.wiki/w/Java_Edition_protocol/Registries#Biome_requirements) | [Biomes](https://minecraft.wiki/w/Biome "Biome"). The name is an artifact of the directory structure used in data packs; the uses of biome information on the client are unrelated to world generation. Referenced in the [Chunk Biomes](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Chunk_Biomes "Java Edition protocol/Packets") and [Chunk Data and Update Light](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Chunk_Data_and_Update_Light "Java Edition protocol/Packets") packets. |
| `minecraft:cat_variant` | [NBT format](https://minecraft.wiki/w/Mob_variant_definitions#Cat "Mob variant definitions") | Non-empty | [Cat variants](https://minecraft.wiki/w/Cat_variant "Cat variant"). |
| `minecraft:cat_sound_variant` | [NBT format](https://minecraft.wiki/w/Mob_variant_definitions#Cat_sounds "Mob variant definitions") | Non-empty | [Cat sound variants](https://minecraft.wiki/w/Cat_sound_variant "Cat sound variant"). |
| `minecraft:chicken_variant` | [NBT format](https://minecraft.wiki/w/Mob_variant_definitions#Chicken "Mob variant definitions") | [See below](https://minecraft.wiki/w/Java_Edition_protocol/Registries#Chicken_variant_requirements) | [Chicken variants](https://minecraft.wiki/w/Chicken_variant "Chicken variant"). |
| `minecraft:chicken_sound_variant` | [NBT format](https://minecraft.wiki/w/Mob_variant_definitions#Chicken_sounds "Mob variant definitions") | Non-empty | [Chicken sound variants](https://minecraft.wiki/w/Chicken_sound_variant "Chicken sound variant"). |
| `minecraft:cow_variant` | [NBT format](https://minecraft.wiki/w/Mob_variant_definitions#Cow "Mob variant definitions") | Non-empty | [Cow variants](https://minecraft.wiki/w/Cow_variant "Cow variant"). |
| `minecraft:cow_sound_variant` | [NBT format](https://minecraft.wiki/w/Mob_variant_definitions#Cow_sounds "Mob variant definitions") | Non-empty | [Cow sound variants](https://minecraft.wiki/w/Cow_sound_variant "Cow sound variant"). |
| `minecraft:frog_variant` | [NBT format](https://minecraft.wiki/w/Mob_variant_definitions#Frog "Mob variant definitions") | Non-empty | [Frog variants](https://minecraft.wiki/w/Frog_variant "Frog variant"). |
| `minecraft:pig_variant` | [NBT format](https://minecraft.wiki/w/Mob_variant_definitions#Pig "Mob variant definitions") | Non-empty | [Pig variants](https://minecraft.wiki/w/Pig_variant "Pig variant"). |
| `minecraft:pig_sound_variant` | [NBT format](https://minecraft.wiki/w/Mob_variant_definitions#Pig_sounds "Mob variant definitions") | Non-empty | [Pig sound variants](https://minecraft.wiki/w/Pig_sound_variant "Pig sound variant"). |
| `minecraft:wolf_variant` | [NBT format](https://minecraft.wiki/w/Mob_variant_definitions#Wolf "Mob variant definitions") | Non-empty | [Wolf variants](https://minecraft.wiki/w/Wolf_variant "Wolf variant"). |
| `minecraft:wolf_sound_variant` | [NBT format](https://minecraft.wiki/w/Mob_variant_definitions#Wolf_sounds "Mob variant definitions") | Non-empty | [Wolf sound variants](https://minecraft.wiki/w/Wolf_sound_variant "Wolf sound variant"). |
| `minecraft:zombie_nautilus_variant` | [NBT format](https://minecraft.wiki/w/Mob_variant_definitions#Zombie_Nautilus "Mob variant definitions") | Non-empty | Zombie Nautilus variants. |

#### Banner pattern requirements

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Registries?section=7&veaction=edit "Edit section: Banner pattern requirements") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Registries?action=edit&section=7 "Edit section's source code: Banner pattern requirements")\]

Due to their use in the default values of [item components](https://minecraft.wiki/w/Item_component "Item component"), the following banner pattern tags must be defined (in [Update Tags](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Update_Tags "Java Edition protocol/Packets")) for the vanilla client to accept a [Finish Configuration](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Finish_Configuration "Java Edition protocol/Packets") packet:

- `minecraft:pattern_item/bordure_indented`
- `minecraft:pattern_item/creeper`
- `minecraft:pattern_item/field_masoned`
- `minecraft:pattern_item/flow`
- `minecraft:pattern_item/flower`
- `minecraft:pattern_item/globe`
- `minecraft:pattern_item/guster`
- `minecraft:pattern_item/mojang`
- `minecraft:pattern_item/piglin`
- `minecraft:pattern_item/skull`

#### Damage type requirements

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Registries?section=8&veaction=edit "Edit section: Damage type requirements") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Registries?action=edit&section=8 "Edit section's source code: Damage type requirements")\]

The following damage types must be defined for the vanilla client to accept a [Login (play)](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Login_(play) "Java Edition protocol/Packets") packet:

- `minecraft:cactus`
- `minecraft:campfire`
- `minecraft:cramming`
- `minecraft:dragon_breath`
- `minecraft:drown`
- `minecraft:dry_out`
- `minecraft:ender_pearl`
- `minecraft:fall`
- `minecraft:fly_into_wall`
- `minecraft:freeze`
- `minecraft:generic`
- `minecraft:generic_kill`
- `minecraft:hot_floor`
- `minecraft:in_fire`
- `minecraft:in_wall`
- `minecraft:lava`
- `minecraft:lightning_bolt`
- `minecraft:magic`
- `minecraft:on_fire`
- `minecraft:out_of_world`
- `minecraft:outside_border`
- `minecraft:spear`
- `minecraft:stalagmite`
- `minecraft:starve`
- `minecraft:sweet_berry_bush`
- `minecraft:wither`

Due to their use in the default values of [item components](https://minecraft.wiki/w/Item_component "Item component"), the following damage type tags must be defined (in [Update Tags](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Update_Tags "Java Edition protocol/Packets")) for the vanilla client to accept a [Finish Configuration](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Finish_Configuration "Java Edition protocol/Packets") packet:

- `minecraft:bypasses_shield`
- `minecraft:is_explosion`
- `minecraft:is_fire`

#### Instrument requirements

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Registries?section=9&veaction=edit "Edit section: Instrument requirements") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Registries?action=edit&section=9 "Edit section's source code: Instrument requirements")\]

Due to its use as the default value of the `minecraft:instrument` data component for goat horns, an instrument named `minecraft:ponder_goat_horn` must be defined for the vanilla client to accept a [Finish Configuration](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Finish_Configuration "Java Edition protocol/Packets") packet.

#### Jukebox song requirements

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Registries?section=10&veaction=edit "Edit section: Jukebox song requirements") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Registries?action=edit&section=10 "Edit section's source code: Jukebox song requirements")\]

Due to their use in the default values of [item components](https://minecraft.wiki/w/Item_component "Item component"), the following jukebox songs must be defined for the vanilla client to accept a [Finish Configuration](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Finish_Configuration "Java Edition protocol/Packets") packet:

- `minecraft:11`
- `minecraft:13`
- `minecraft:5`
- `minecraft:blocks`
- `minecraft:bounce`
- `minecraft:cat`
- `minecraft:chirp`
- `minecraft:creator`
- `minecraft:creator_music_box`
- `minecraft:far`
- `minecraft:lava_chicken`
- `minecraft:mall`
- `minecraft:mellohi`
- `minecraft:otherside`
- `minecraft:pigstep`
- `minecraft:precipice`
- `minecraft:relic`
- `minecraft:stal`
- `minecraft:strad`
- `minecraft:tears`
- `minecraft:wait`
- `minecraft:ward`

#### Trim material requirements

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Registries?section=11&veaction=edit "Edit section: Trim material requirements") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Registries?action=edit&section=11 "Edit section's source code: Trim material requirements")\]

Due to their use in the default values of [item components](https://minecraft.wiki/w/Item_component "Item component"), the following trim materials must be defined for the vanilla client to accept a [Finish Configuration](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Finish_Configuration "Java Edition protocol/Packets") packet:

- `minecraft:amethyst`
- `minecraft:copper`
- `minecraft:diamond`
- `minecraft:emerald`
- `minecraft:gold`
- `minecraft:iron`
- `minecraft:lapis`
- `minecraft:netherite`
- `minecraft:quartz`
- `minecraft:redstone`
- `minecraft:resin`

#### Dimension type requirements

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Registries?section=12&veaction=edit "Edit section: Dimension type requirements") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Registries?action=edit&section=12 "Edit section's source code: Dimension type requirements")\]

The `minecraft:dimension_type` registry is technically optional, but due to the required Dimension Type field, it is impossible to send a valid [Login (play)](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Login_(play) "Java Edition protocol/Packets") packet unless the registry has at least one entry.

#### Biome requirements

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Registries?section=13&veaction=edit "Edit section: Biome requirements") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Registries?action=edit&section=13 "Edit section's source code: Biome requirements")\]

A biome named `minecraft:plains` must be defined for the vanilla client to accept a [Login (play)](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Login_(play) "Java Edition protocol/Packets") packet. It is used as the default for unloaded chunks.

#### Chicken variant requirements

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Registries?section=14&veaction=edit "Edit section: Chicken variant requirements") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Registries?action=edit&section=14 "Edit section's source code: Chicken variant requirements")\]

Due to their use in the default values of [item components](https://minecraft.wiki/w/Item_component "Item component"), the following chicken variants must be defined for the vanilla client to accept a [Finish Configuration](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Finish_Configuration "Java Edition protocol/Packets") packet:

- `minecraft:cold`
- `minecraft:temperate`
- `minecraft:warm`

[![](https://minecraft.wiki/images/License_cc.svg?7c689)](https://minecraft.wiki/w/File:License_cc.svg "File:License cc.svg")

[![](https://minecraft.wiki/images/License_cc-by.svg?818e9)](https://minecraft.wiki/w/File:License_cc-by.svg)[![](https://minecraft.wiki/images/License_cc-by-sa.svg?75cd1)](https://minecraft.wiki/w/File:License_cc-by-sa.svg)

This article is licensed under a [Creative Commons Attribution-ShareAlike 3.0](https://creativecommons.org/licenses/by-sa/3.0/) license.

This article has been imported from [wiki.vg](https://minecraft.wiki/w/Minecraft_Wiki:Projects/wiki.vg_merge "Minecraft Wiki:Projects/wiki.vg merge") or is a derivative of such a page. Thus, the wiki's [usual license](https://minecraft.wiki/w/Minecraft_Wiki:Copyrights "Minecraft Wiki:Copyrights") does not apply.

Derivative works must be licensed using the same or a compatible license.

Retrieved from " [https://minecraft.wiki/w/Java\_Edition\_protocol/Registries?oldid=3749652](https://minecraft.wiki/w/Java_Edition_protocol/Registries?oldid=3749652)"

[Categories](https://minecraft.wiki/w/Special:Categories "Special:Categories"):

- [Protocol Details](https://minecraft.wiki/w/Category:Protocol_Details "Category:Protocol Details")
- [Java Edition protocol](https://minecraft.wiki/w/Category:Java_Edition_protocol "Category:Java Edition protocol")
- [CC BY-SA pages](https://minecraft.wiki/w/Category:CC_BY-SA_pages "Category:CC BY-SA pages")

## Navigation menu

Search

[Visit the main page](https://minecraft.wiki/ "Visit the main page")

[X](https://minecraft.wiki/w/Minecraft_Wiki:Indie_Wiki_Buddy)

**To leave feedback for the game, [click here](https://feedback.minecraft.net/).**

Feedback will be posted anonymously and shared to our [Discord](https://discord.gg/fGdE5ZE).

Something went wrong

Dismiss