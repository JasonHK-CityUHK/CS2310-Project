10 languages

- [Deutsch](https://de.minecraft.wiki/w/Weltdaten "Weltdaten – Deutsch")
- [Español](https://es.minecraft.wiki/w/Formato_de_nivel_de_Java_Edition "Formato de nivel de Java Edition – español")
- [Français](https://fr.minecraft.wiki/w/Format_de_niveau_de_l%27%C3%A9dition_Java "Format de niveau de l'édition Java – français")
- [日本語](https://ja.minecraft.wiki/w/%E3%83%AF%E3%83%BC%E3%83%AB%E3%83%89%E3%83%95%E3%82%A9%E3%83%BC%E3%83%9E%E3%83%83%E3%83%88/Java_Edition "ワールドフォーマット/Java Edition – 日本語")
- [한국어](https://ko.minecraft.wiki/w/Java_Edition_%EB%A0%88%EB%B2%A8_%ED%8F%AC%EB%A7%B7 "Java Edition 레벨 포맷 – 한국어")
- [文言](https://lzh.minecraft.wiki/w/%E7%88%AA%E5%93%87%E7%89%88%E7%94%9F%E7%95%8C%E7%AF%84%E5%BC%8F "爪哇版生界範式 – 文言")
- [Nederlands](https://nl.minecraft.wiki/w/Level_formaat "Level formaat – Nederlands")
- [Português](https://pt.minecraft.wiki/w/Formato_de_n%C3%ADvel_da_Edi%C3%A7%C3%A3o_Java "Formato de nível da Edição Java – português")
- [Русский](https://ru.minecraft.wiki/w/Level.dat "Level.dat – русский")
- [中文](https://zh.minecraft.wiki/w/Java%E7%89%88%E5%AD%98%E6%A1%A3%E6%A0%BC%E5%BC%8F "Java版存档格式 – 中文")

# Java Edition level format  Share article feedback

From Minecraft Wiki

[Jump to navigation](https://minecraft.wiki/w/Java_Edition_level_format#mw-head) [Jump to search](https://minecraft.wiki/w/Java_Edition_level_format#searchInput)

[![](https://minecraft.wiki/images/thumb/Minecart_with_Furnace_JE3.png/32px-Minecart_with_Furnace_JE3.png?c3c11)](https://minecraft.wiki/w/File:Minecart_with_Furnace_JE3.png "File:Minecart with Furnace JE3.png")

This feature is exclusive to [_Java Edition_](https://minecraft.wiki/w/Java_Edition "Java Edition").

Each level (world) has its own folder. A level folder is often identified by having a [level.dat](https://minecraft.wiki/w/Java_Edition_level_format#level.dat_format) file, along with other subfolders to store the maps and regions of the level.

## Contents

- [1Directory structure](https://minecraft.wiki/w/Java_Edition_level_format#Directory_structure)
  - [1.1Current](https://minecraft.wiki/w/Java_Edition_level_format#Current)
  - [1.2Deprecated](https://minecraft.wiki/w/Java_Edition_level_format#Deprecated)
- [2level.dat format](https://minecraft.wiki/w/Java_Edition_level_format#level.dat_format)
- [3generatorOptions tag format](https://minecraft.wiki/w/Java_Edition_level_format#generatorOptions_tag_format)
- [4session.lock format](https://minecraft.wiki/w/Java_Edition_level_format#session.lock_format)
- [5poi format](https://minecraft.wiki/w/Java_Edition_level_format#poi_format)
- [6History](https://minecraft.wiki/w/Java_Edition_level_format#History)
  - [6.1Level format](https://minecraft.wiki/w/Java_Edition_level_format#Level_format)
  - [6.2level.dat](https://minecraft.wiki/w/Java_Edition_level_format#level.dat)
  - [6.3weather.dat](https://minecraft.wiki/w/Java_Edition_level_format#weather.dat)
  - [6.4wandering\_trader.dat](https://minecraft.wiki/w/Java_Edition_level_format#wandering_trader.dat)
  - [6.5ender\_dragon\_fight.dat](https://minecraft.wiki/w/Java_Edition_level_format#ender_dragon_fight.dat)
  - [6.6scheduled\_events.dat](https://minecraft.wiki/w/Java_Edition_level_format#scheduled_events.dat)
  - [6.7world\_gen\_settings.dat](https://minecraft.wiki/w/Java_Edition_level_format#world_gen_settings.dat)
- [7See also](https://minecraft.wiki/w/Java_Edition_level_format#See_also)
- [8References](https://minecraft.wiki/w/Java_Edition_level_format#References)
- [9Navigation](https://minecraft.wiki/w/Java_Edition_level_format#Navigation)

## Directory structure

\[ [edit](https://minecraft.wiki/w/Java_Edition_level_format?section=1&veaction=edit "Edit section: Directory structure") \| [edit source](https://minecraft.wiki/w/Java_Edition_level_format?action=edit&section=1 "Edit section's source code: Directory structure")\]

### Current

\[ [edit](https://minecraft.wiki/w/Java_Edition_level_format?section=2&veaction=edit "Edit section: Current") \| [edit source](https://minecraft.wiki/w/Java_Edition_level_format?action=edit&section=2 "Edit section's source code: Current")\]

This is the directory structure of the `.minecraft/saves` folder, where the game saves the entire [world](https://minecraft.wiki/w/World "World") data:

- ![File directory.png: Sprite image for directory in Minecraft](https://minecraft.wiki/images/thumb/File_directory.png/16px-File_directory.png?8a409): A world directory.

  - ![File file.png: Sprite image for file in Minecraft](https://minecraft.wiki/images/thumb/File_file.png/16px-File_file.png?e19ce)level.dat: Stores global information about the level. See [below](https://minecraft.wiki/w/Java_Edition_level_format#level.dat_format).
  - ![File file.png: Sprite image for file in Minecraft](https://minecraft.wiki/images/thumb/File_file.png/16px-File_file.png?e19ce)level.dat\_new: Program writes new global information about the level, and after that file is renamed to level.dat.
  - ![File file.png: Sprite image for file in Minecraft](https://minecraft.wiki/images/thumb/File_file.png/16px-File_file.png?e19ce)level.dat\_old: A backup of the previous level.dat file.
  - ![File file.png: Sprite image for file in Minecraft](https://minecraft.wiki/images/thumb/File_file.png/16px-File_file.png?e19ce)session.lock: Used to give write access to the last program to modify this file. See [below](https://minecraft.wiki/w/Java_Edition_level_format#session.lock_format).

    - ![File file.png: Sprite image for file in Minecraft](https://minecraft.wiki/images/thumb/File_file.png/16px-File_file.png?e19ce)_<uuid>_.dat: A data file of the player. See [Player.dat format](https://minecraft.wiki/w/Player.dat_format "Player.dat format").
    - ![File file.png: Sprite image for file in Minecraft](https://minecraft.wiki/images/thumb/File_file.png/16px-File_file.png?e19ce)_<uuid>_.json: A data file of the player. See [Statistics storage format](https://minecraft.wiki/w/Statistics#Storage "Statistics").
    - ![File file.png: Sprite image for file in Minecraft](https://minecraft.wiki/images/thumb/File_file.png/16px-File_file.png?e19ce)_<uuid>_.json: A data file of the player. See [Advancement storage format](https://minecraft.wiki/w/Advancement#Storage "Advancement").
  - ![File directory.png: Sprite image for directory in Minecraft](https://minecraft.wiki/images/thumb/File_directory.png/16px-File_directory.png?8a409)data: Miscellaneous data of the world.

    - ![File directory.png: Sprite image for directory in Minecraft](https://minecraft.wiki/images/thumb/File_directory.png/16px-File_directory.png?8a409)minecraft: Vanilla namespace for Miscellaneous data of the world.

      - ![File file.png: Sprite image for file in Minecraft](https://minecraft.wiki/images/thumb/File_file.png/16px-File_file.png?e19ce)game\_rules.dat: [Gamerules](https://minecraft.wiki/w/Gamerules "Gamerules") of the world.
      - ![File file.png: Sprite image for file in Minecraft](https://minecraft.wiki/images/thumb/File_file.png/16px-File_file.png?e19ce)random\_sequences.dat: Stores random number sequences for [loot tables](https://minecraft.wiki/w/Loot_table "Loot table") or the `/random` command. See [Random sequence format](https://minecraft.wiki/w/Random_sequence_format "Random sequence format").
      - ![File file.png: Sprite image for file in Minecraft](https://minecraft.wiki/images/thumb/File_file.png/16px-File_file.png?e19ce)scoreboard.dat: Stores [scoreboard](https://minecraft.wiki/w/Scoreboard "Scoreboard") data, such as objectives' definition, entities' scores, teams, and display slots of objectives. See [Scoreboard § NBT format](https://minecraft.wiki/w/Scoreboard#NBT_format "Scoreboard").
      - ![File file.png: Sprite image for file in Minecraft](https://minecraft.wiki/images/thumb/File_file.png/16px-File_file.png?e19ce)stopwatches.dat: Stores [Stopwatch](https://minecraft.wiki/w/Stopwatch "Stopwatch") data.
      - ![File file.png: Sprite image for file in Minecraft](https://minecraft.wiki/images/thumb/File_file.png/16px-File_file.png?e19ce)wandering\_trader.dat: Stores [Wandering Trader](https://minecraft.wiki/w/Wandering_Trader "Wandering Trader") data.
      - ![File file.png: Sprite image for file in Minecraft](https://minecraft.wiki/images/thumb/File_file.png/16px-File_file.png?e19ce)world\_clocks.dat: Stores [World Clock](https://minecraft.wiki/w/World_Clock "World Clock") data.
      - ![File file.png: Sprite image for file in Minecraft](https://minecraft.wiki/images/thumb/File_file.png/16px-File_file.png?e19ce)world\_gen\_settings.dat: Stores World Generation Settings data.
      - ![File file.png: Sprite image for file in Minecraft](https://minecraft.wiki/images/thumb/File_file.png/16px-File_file.png?e19ce)scheduled\_events.dat: Stores Scheduled Events data.
      - ![File file.png: Sprite image for file in Minecraft](https://minecraft.wiki/images/thumb/File_file.png/16px-File_file.png?e19ce)custom\_boss\_events.dat: Stores Boss Events data.
      - ![File file.png: Sprite image for file in Minecraft](https://minecraft.wiki/images/thumb/File_file.png/16px-File_file.png?e19ce)weather.dat: Stores [Weather](https://minecraft.wiki/w/Weather "Weather") related data.
  - ![File directory.png: Sprite image for directory in Minecraft](https://minecraft.wiki/images/thumb/File_directory.png/16px-File_directory.png?8a409)datapacks: Stores the world's [data packs](https://minecraft.wiki/w/Data_pack "Data pack").

    - ![File archive.png: Sprite image for archive in Minecraft](https://minecraft.wiki/images/thumb/File_archive.png/16px-File_archive.png?5ba7d)![File directory.png: Sprite image for directory in Minecraft](https://minecraft.wiki/images/thumb/File_directory.png/16px-File_directory.png?8a409)_<datapack>_: A data pack.
  - ![File directory.png: Sprite image for directory in Minecraft](https://minecraft.wiki/images/thumb/File_directory.png/16px-File_directory.png?8a409)dimensions: Contains region files of dimensions, added by vanilla, data packs or [mods](https://minecraft.wiki/w/Mod "Mod").

    - ![File directory.png: Sprite image for directory in Minecraft](https://minecraft.wiki/images/thumb/File_directory.png/16px-File_directory.png?8a409)_<namespace>_: [Namespace](https://minecraft.wiki/w/Resource_location "Resource location") of the defined dimension.

      - ![File directory.png: Sprite image for directory in Minecraft](https://minecraft.wiki/images/thumb/File_directory.png/16px-File_directory.png?8a409)_<path>_: [Path](https://minecraft.wiki/w/Resource_location "Resource location") of the defined dimension.

        - ![File directory.png: Sprite image for directory in Minecraft](https://minecraft.wiki/images/thumb/File_directory.png/16px-File_directory.png?8a409)data: Miscellaneous data of the custom dimension.

          - ![File file.png: Sprite image for file in Minecraft](https://minecraft.wiki/images/thumb/File_file.png/16px-File_file.png?e19ce)raids.dat: Stores information about the ongoing raids in this dimension.
        - ![File directory.png: Sprite image for directory in Minecraft](https://minecraft.wiki/images/thumb/File_directory.png/16px-File_directory.png?8a409)region: See above.
        - ![File directory.png: Sprite image for directory in Minecraft](https://minecraft.wiki/images/thumb/File_directory.png/16px-File_directory.png?8a409)entities: See above.
        - ![File directory.png: Sprite image for directory in Minecraft](https://minecraft.wiki/images/thumb/File_directory.png/16px-File_directory.png?8a409)poi: See above.
    - ![File directory.png: Sprite image for directory in Minecraft](https://minecraft.wiki/images/thumb/File_directory.png/16px-File_directory.png?8a409)minecraft: [Namespace](https://minecraft.wiki/w/Resource_location "Resource location") of the vanilla dimension.

      - ![File directory.png: Sprite image for directory in Minecraft](https://minecraft.wiki/images/thumb/File_directory.png/16px-File_directory.png?8a409)overworld: [Path](https://minecraft.wiki/w/Resource_location "Resource location") of the Overworld dimension.

        - ![File directory.png: Sprite image for directory in Minecraft](https://minecraft.wiki/images/thumb/File_directory.png/16px-File_directory.png?8a409)data: Contains data of the Overworld.

          - ![File directory.png: Sprite image for directory in Minecraft](https://minecraft.wiki/images/thumb/File_directory.png/16px-File_directory.png?8a409)_<namespace>_: Namespace for the Overworld data.
          - ![File directory.png: Sprite image for directory in Minecraft](https://minecraft.wiki/images/thumb/File_directory.png/16px-File_directory.png?8a409)minecraft: Vanilla Namespace for the Overworld data.

            - ![File file.png: Sprite image for file in Minecraft](https://minecraft.wiki/images/thumb/File_file.png/16px-File_file.png?e19ce)raids.dat: Stores information about the ongoing [raids](https://minecraft.wiki/w/Raid "Raid") in [Overworld](https://minecraft.wiki/w/Overworld "Overworld"). See [raids.dat format](https://minecraft.wiki/w/Raids.dat_format "Raids.dat format").
            - ![File file.png: Sprite image for file in Minecraft](https://minecraft.wiki/images/thumb/File_file.png/16px-File_file.png?e19ce)world\_border.dat: Stores information about the [World Border](https://minecraft.wiki/w/World_Border "World Border").
            - ![File file.png: Sprite image for file in Minecraft](https://minecraft.wiki/images/thumb/File_file.png/16px-File_file.png?e19ce)chunk\_tickets.dat: `/forceload`.
        - ![File directory.png: Sprite image for directory in Minecraft](https://minecraft.wiki/images/thumb/File_directory.png/16px-File_directory.png?8a409)entities:

          - ![File directory.png: Sprite image for directory in Minecraft](https://minecraft.wiki/images/thumb/File_directory.png/16px-File_directory.png?8a409)entities: Contains entity files for the [Overworld](https://minecraft.wiki/w/Overworld "Overworld"). These used to be part of region.
        - ![File directory.png: Sprite image for directory in Minecraft](https://minecraft.wiki/images/thumb/File_directory.png/16px-File_directory.png?8a409)poi:

          - ![File directory.png: Sprite image for directory in Minecraft](https://minecraft.wiki/images/thumb/File_directory.png/16px-File_directory.png?8a409)poi: Villager identified beds, job sites, and bells in the Overworld. Nether portals, bee nests, bee hives, and lodestones also use this.
        - ![File directory.png: Sprite image for directory in Minecraft](https://minecraft.wiki/images/thumb/File_directory.png/16px-File_directory.png?8a409)region:

          - ![File file.png: Sprite image for file in Minecraft](https://minecraft.wiki/images/thumb/File_file.png/16px-File_file.png?e19ce)r. _<x>_. _<y>_.mca: A region file. See [Anvil file format](https://minecraft.wiki/w/Anvil_file_format "Anvil file format").
      - ![File directory.png: Sprite image for directory in Minecraft](https://minecraft.wiki/images/thumb/File_directory.png/16px-File_directory.png?8a409)the\_end: [Path](https://minecraft.wiki/w/Resource_location "Resource location") of the End dimension.
      - ![File directory.png: Sprite image for directory in Minecraft](https://minecraft.wiki/images/thumb/File_directory.png/16px-File_directory.png?8a409)the\_nether: [Path](https://minecraft.wiki/w/Resource_location "Resource location") of the End dimension.
  - ![File directory.png: Sprite image for directory in Minecraft](https://minecraft.wiki/images/thumb/File_directory.png/16px-File_directory.png?8a409)resourcepacks: Contains resourcepacks of the world.

    - ![File archive.png: Sprite image for archive in Minecraft](https://minecraft.wiki/images/thumb/File_archive.png/16px-File_archive.png?5ba7d)resources.zip: A [resource pack](https://minecraft.wiki/w/Resource_pack "Resource pack") applied when the world loads in.

### Deprecated

\[ [edit](https://minecraft.wiki/w/Java_Edition_level_format?section=3&veaction=edit "Edit section: Deprecated") \| [edit source](https://minecraft.wiki/w/Java_Edition_level_format?action=edit&section=3 "Edit section's source code: Deprecated")\]

- ![File directory.png: Sprite image for directory in Minecraft](https://minecraft.wiki/images/thumb/File_directory.png/16px-File_directory.png?8a409): A world directory.

  - ![File file.png: Sprite image for file in Minecraft](https://minecraft.wiki/images/thumb/File_file.png/16px-File_file.png?e19ce)level.dat\_mcr: A backup of the level.dat file before conversion from [MCRegion](https://minecraft.wiki/w/MCRegion "MCRegion") to [Anvil](https://minecraft.wiki/w/Anvil_file_format "Anvil file format").
  - ![File directory.png: Sprite image for directory in Minecraft](https://minecraft.wiki/images/thumb/File_directory.png/16px-File_directory.png?8a409)players: Stores the individual states of the players that have played on this level, for versions before [1.7.6](https://minecraft.wiki/w/1.7.6 "1.7.6").

    - ![File file.png: Sprite image for file in Minecraft](https://minecraft.wiki/images/thumb/File_file.png/16px-File_file.png?e19ce)_<player>_.dat: A data file of the player. See [Player.dat format](https://minecraft.wiki/w/Player.dat_format "Player.dat format").
  - ![File directory.png: Sprite image for directory in Minecraft](https://minecraft.wiki/images/thumb/File_directory.png/16px-File_directory.png?8a409)data: Miscellaneous data of the world.

    - ![File file.png: Sprite image for file in Minecraft](https://minecraft.wiki/images/thumb/File_file.png/16px-File_file.png?e19ce)villages.dat: Stores information about the [villages](https://minecraft.wiki/w/Village "Village") in the world. The "nether" and "end" files have been added in [1.8](https://minecraft.wiki/w/Java_Edition_1.8 "Java Edition 1.8"). Replaced by point of interest region files in [1.14](https://minecraft.wiki/w/Java_Edition_1.14 "Java Edition 1.14").
    - ![File file.png: Sprite image for file in Minecraft](https://minecraft.wiki/images/thumb/File_file.png/16px-File_file.png?e19ce)villages\_nether.dat: See above.
    - ![File file.png: Sprite image for file in Minecraft](https://minecraft.wiki/images/thumb/File_file.png/16px-File_file.png?e19ce)villages\_end.dat: See above.
  - ![File directory.png: Sprite image for directory in Minecraft](https://minecraft.wiki/images/thumb/File_directory.png/16px-File_directory.png?8a409)region: Backups of the region files before conversion from [MCRegion](https://minecraft.wiki/w/MCRegion "MCRegion") to [Anvil](https://minecraft.wiki/w/Anvil_file_format "Anvil file format").

    - ![File file.png: Sprite image for file in Minecraft](https://minecraft.wiki/images/thumb/File_file.png/16px-File_file.png?e19ce)r. _<x>_. _<y>_.mcr: A region file. See [Region file format](https://minecraft.wiki/w/Region_file_format "Region file format").
  - ![File directory.png: Sprite image for directory in Minecraft](https://minecraft.wiki/images/thumb/File_directory.png/16px-File_directory.png?8a409)DIM-1: Nether dimension.

    - ![File file.png: Sprite image for file in Minecraft](https://minecraft.wiki/images/thumb/File_file.png/16px-File_file.png?e19ce)r. _<x>_. _<y>_.mcr: A region file. See [Region file format](https://minecraft.wiki/w/Region_file_format "Region file format").
  - ![File directory.png: Sprite image for directory in Minecraft](https://minecraft.wiki/images/thumb/File_directory.png/16px-File_directory.png?8a409)DIM1: The End dimension.

    - ![File file.png: Sprite image for file in Minecraft](https://minecraft.wiki/images/thumb/File_file.png/16px-File_file.png?e19ce)r. _<x>_. _<y>_.mcr: A region file. See [Region file format](https://minecraft.wiki/w/Region_file_format "Region file format").
  - ![File directory.png: Sprite image for directory in Minecraft](https://minecraft.wiki/images/thumb/File_directory.png/16px-File_directory.png?8a409)_<?​\[ _[more information needed](https://minecraft.wiki/w/Special:TalkPage/Java_Edition_level_format "Special:TalkPage/Java Edition level format")_\]>_
    - ![File directory.png: Sprite image for directory in Minecraft](https://minecraft.wiki/images/thumb/File_directory.png/16px-File_directory.png?8a409)_<?​\[ _[more information needed](https://minecraft.wiki/w/Special:TalkPage/Java_Edition_level_format "Special:TalkPage/Java Edition level format")_\]>_
      - ![File file.png: Sprite image for file in Minecraft](https://minecraft.wiki/images/thumb/File_file.png/16px-File_file.png?e19ce)c. _<x>_. _<y>_.dat: Backups of the chunk files before conversion from the Alpha level format to [MCRegion](https://minecraft.wiki/w/MCRegion "MCRegion"). See [Alpha level format](https://minecraft.wiki/w/Java_Edition_Alpha_level_format "Java Edition Alpha level format").

## level.dat format

\[ [edit](https://minecraft.wiki/w/Java_Edition_level_format?section=4&veaction=edit "Edit section: level.dat format") \| [edit source](https://minecraft.wiki/w/Java_Edition_level_format?action=edit&section=4 "Edit section's source code: level.dat format")\]

The level.dat file contains global information about the world such as the time of day, the singleplayer player, the level generator used, and the seed. When a world is loaded, the current `level.dat` is backed up to `level.dat_old`.
It is an [NBT](https://minecraft.wiki/w/NBT "NBT") file with this structure:

- \[NBT Compound / JSON Object\]The root tag.

  - \[NBT Compound / JSON Object\] Data: This tag contains all the level data.

    - \[Boolean\] allowCommands: 1 or 0 (true/false) - true if cheats are enabled.
    - \[NBT Compound / JSON Object\] DataPacks: Options for data packs.

      - \[NBT List / JSON Array\] Disabled: List of disabled data packs.

        - \[String\]: A single data pack.
      - \[NBT List / JSON Array\] Enabled: List of enabled data packs. By default, this is populated with a single string "vanilla".

        - \[String\]: A single data pack.
    - \[Int\] DataVersion: An integer displaying the [data version](https://minecraft.wiki/w/Data_version "Data version").
    - \[NBT Compound / JSON Object\] difficulty\_settings: This tag contains all difficulty settings.

      - \[String\] difficulty: The difficulty of the world. e.g. "normal".
      - \[Boolean\] hardcore: 1 or 0 (true/false) - If true, the player respawns in [Spectator](https://minecraft.wiki/w/Spectator "Spectator") on death in singleplayer. Affects all four game modes.
      - \[Boolean\] locked: 1 or 0 (true/false) - If true, the player cannot change the difficulty of the world.
    - \[NBT List / JSON Array\] enabled\_features: List of experimental features enabled for this world. Doesn't appear if there are no experimental features enabled.

      - \[String\]: A single experimental feature.
    - \[Int\] GameType: The default game mode for the singleplayer player when they initially spawn. 0 is [Survival](https://minecraft.wiki/w/Survival "Survival"), 1 is [Creative](https://minecraft.wiki/w/Creative "Creative"), 2 is [Adventure](https://minecraft.wiki/w/Adventure "Adventure"), 3 is [Spectator](https://minecraft.wiki/w/Spectator "Spectator"). Note: singleplayer worlds do not use this field to save which game mode the player is currently in.
    - \[Boolean\] initialized: 1 or 0 (true/false) - Normally true after a world has been initialized properly after creation. If the initial simulation was canceled somehow, this can be false and the world is re-initialized on next load.
    - \[Long\] LastPlayed: The Unix time in milliseconds when the level was last loaded.
    - \[String\] LevelName: The name of the level.
    - \[Int Array\] singleplayer\_uuid: UUID of the player in singleplayer
    - \[NBT List / JSON Array\] ServerBrands: List of brands of the level.

      - \[String\]: A single server brand. e.g. "vanilla".
    - \[NBT Compound / JSON Object\] spawn: The world spawn data.

      - \[String\] dimension: The spawn dimension, as three integers
      - \[Int\] pitch: The pitch.
      - \[Int\] yaw: The yaw.
      - \[Int Array\] pos: The spawn position.
    - \[Long\] Time: The number of ticks since the start of the level.
    - \[Int\] version: File format version of level.dat. Values 19132 or 19133 represent [Region](https://minecraft.wiki/w/Region_file_format "Region file format") and [Anvil](https://minecraft.wiki/w/Anvil_file_format "Anvil file format") respectively.
    - \[NBT Compound / JSON Object\] Version: Information about the _Minecraft_ version the world was saved in.

      - \[Int\] Id: An integer displaying the [data version](https://minecraft.wiki/w/Data_version "Data version").
      - \[String\] Name: The version name as a string, e.g. "15w32b".
      - \[String\] Series: Developing series. In 1.18 experimental snapshots, it was set to "ccpreview". In others, set to "main".
      - \[Boolean\] Snapshot: 1 or 0 (true/false) – Whether the version is a snapshot or not.
    - \[NBT List / JSON Array\] version\_history: A list of [data versions](https://minecraft.wiki/w/Data_version "Data version") that this world has used in the past, from earliest to latest. The last entry will be the same as \[Int\] Version.Id.

      - \[Int\]: A [data version](https://minecraft.wiki/w/Data_version "Data version").
    - \[Boolean\] WasModded: 1 or 0 (true/false) - true if the world was opened in a modified version.

## generatorOptions tag format

\[ [edit](https://minecraft.wiki/w/Java_Edition_level_format?section=5&veaction=edit "Edit section: generatorOptions tag format") \| [edit source](https://minecraft.wiki/w/Java_Edition_level_format?action=edit&section=5 "Edit section's source code: generatorOptions tag format")\]

The \[NBT Compound / JSON Object\] generatorOptions tag format varies depending on the generator name. It affects only the [Overworld](https://minecraft.wiki/w/Overworld "Overworld") dimension. This applies to 1.15 and below.

This is the format for the [Buffet](https://minecraft.wiki/w/Buffet "Buffet") world type:

- \[NBT Compound / JSON Object\] generatorOptions:

  - \[NBT Compound / JSON Object\] biome\_source:

    - \[NBT Compound / JSON Object\] options: Ignored if the [biome source ID](https://minecraft.wiki/w/Java_Edition_data_values#Biome_sources "Java Edition data values") is `minecraft:vanilla_layered`.

      - \[NBT List / JSON Array\] biomes:

        - \[String\]: A [biome ID](https://minecraft.wiki/w/Java_Edition_data_values#Biomes "Java Edition data values"). If this or the biome source ID is omitted or invalid, the code assumes `minecraft:ocean`.
      - \[Byte\] size: The size of the biomes. Only used when the biome source ID is `minecraft:checkerboard`. The biome squares have sides of 2`<size>` (which can be < 1) [chunks](https://minecraft.wiki/w/Chunk "Chunk"). If no value is entered, the code assumes `2`.
    - \[String\] type: An applicable biome source ID. It determines how the biomes are distributed. Cannot be selected in-game and defaults to `minecraft:fixed` for unmodified [worlds](https://minecraft.wiki/w/World "World").
  - \[NBT Compound / JSON Object\] chunk\_generator:

    - \[NBT Compound / JSON Object\] options:

      - \[String\] default\_block: A [block ID](https://minecraft.wiki/w/Java_Edition_data_values#Blocks "Java Edition data values"), by default `minecraft:stone`.
      - \[String\] default\_fluid: A [fluid ID](https://minecraft.wiki/w/Java_Edition_data_values#Fluids "Java Edition data values"), by default `minecraft:water`.
    - \[String\] type: An applicable [chunk generator ID](https://minecraft.wiki/w/Java_Edition_data_values#Chunk_generators "Java Edition data values"). It determines the overall structure of the dimension. If this is omitted or invalid, the code assumes `minecraft:surface`.

This is the format for the [Superflat](https://minecraft.wiki/w/Superflat "Superflat") world type:

- \[NBT Compound / JSON Object\] generatorOptions:

  - \[NBT Compound / JSON Object\] structures:

    - \[NBT Compound / JSON Object\] <structure name>: An empty compound named as the [structure](https://minecraft.wiki/w/Superflat#Structure_generation_options "Superflat"), for example `decoration`. If parameters are set, for example `village(distance=9 size=1)`, then the compound contains this information.

      - \[String\] <parameter name>: The parameter value is a number represented by a string.
  - \[NBT List / JSON Array\] layers:

    - \[NBT Compound / JSON Object\]: A layer.

      - \[String\] block: The [block ID](https://minecraft.wiki/w/Java_Edition_data_values#Blocks "Java Edition data values").
      - \[Int\] height: The height of the layer, used in worlds created before [1.13-pre5](https://minecraft.wiki/w/1.13-pre5 "1.13-pre5").
      - \[Byte\] height: The height of the layer, used in worlds created since 1.13-pre5, if it's < 128 blocks.
      - \[Short\] height: The height of the layer, used in worlds created since 1.13-pre5, if it's >= 128 blocks.
  - \[String\] biome: The [biome ID](https://minecraft.wiki/w/Java_Edition_data_values#Biomes "Java Edition data values").
  - \[String\] flat\_world\_options: The unescaped " [generator-settings](https://minecraft.wiki/w/Server.properties#Java_Edition_3 "Server.properties")" string. Created only if the [world](https://minecraft.wiki/w/World "World") was generated through a [server](https://minecraft.wiki/w/Server "Server"). Until snapshot [20w11a](https://minecraft.wiki/w/20w11a "20w11a"), it is not parsed by the game due to [MC-134900](https://mojira.dev/MC-134900 "mojira:MC-134900"), thus the above compounds won't be created, making "generator-settings" ineffective.

This is the format for the [Old Customized](https://minecraft.wiki/w/Old_Customized "Old Customized") world type that existed before [18w06a](https://minecraft.wiki/w/18w06a "18w06a"):

- \[String\] generatorOptions: Controls options for the world generator. Used only if the world type is Superflat or Customized. The format for Superflat is a comma separated list of block IDs from the bottom of the map up, and each block ID may optionally be preceded by the number of layers and an "\*" ("x" before 1.8). Damage values are not supported.[\[1\]](https://minecraft.wiki/w/Java_Edition_level_format#cite_note-1) See detailed format for Superflat world type: [before 1.8](https://minecraft.wiki/w/Special:PermanentLink/685992#Preset_code_format "Special:PermanentLink/685992") and in [1.8-1.12](https://minecraft.wiki/w/Special:PermanentLink/1178871#Preset_code_format "Special:PermanentLink/1178871"). Refer also to [Superflat#History](https://minecraft.wiki/w/Superflat#History "Superflat") that shows how the format has been changing over time. The format for Customized world type is an extremely long String which consists of _name:value_ pairs resembling JSON (as shown in [Old\_Customized#Presets](https://minecraft.wiki/w/Old_Customized#Presets "Old Customized")).

## session.lock format

\[ [edit](https://minecraft.wiki/w/Java_Edition_level_format?section=6&veaction=edit "Edit section: session.lock format") \| [edit source](https://minecraft.wiki/w/Java_Edition_level_format?action=edit&section=6 "Edit section's source code: session.lock format")\]

This file contains a single character U+2603 ☃ SNOWMAN encoded (E2 98 83) in UTF8.

The process goes something like this:

1. Program opens session.lock.
2. Program writes a single character ☃ (\\u2603) to session.lock.
3. Program tries to acquire a lock on a session.lock.
4. If the lock on a session.lock fails, program aborts and gives up its lock on the level.

_Minecraft_ can sometimes try to hold the lock on a level even after the player has started playing a different level, and this can cause strange behavior. It is recommended to ensure that _Minecraft_ is closed before trying to acquire a lock on a level.

Before 1.16, the lock contained a [big endian](https://en.wikipedia.org/wiki/big_endian "wikipedia:big endian") 64-bit integer timestamp of when the level was last accessed since the [epoch](https://en.wikipedia.org/wiki/Unix_time "wikipedia:Unix time"). The program, instead of writing a snowman and acquiring a lock, would monitor the file for changes, and would abort if changed.

## `poi` format

\[ [edit](https://minecraft.wiki/w/Java_Edition_level_format?section=7&veaction=edit "Edit section: poi format") \| [edit source](https://minecraft.wiki/w/Java_Edition_level_format?action=edit&section=7 "Edit section's source code: poi format")\]

Files in the _`poi`_ folder use similar structure to _`region`_ [Anvil](https://minecraft.wiki/w/Anvil_file_format "Anvil file format") files (hence the _`mca`_ extension), but the [NBT](https://minecraft.wiki/w/NBT "NBT") content is different.

- \[NBT Compound / JSON Object\]The root tag.

  - \[NBT Compound / JSON Object\] Data: This tag contains all the level data.

    - \[NBT Compound / JSON Object\] Sections: Keys are stringified chunk section's Y coordinate _(can be negative, a section at Y=2 starts at block Y=32)_.

      - \[NBT Compound / JSON Object\] <number>:

        - \[Boolean\] Valid: True (1) when created by the game, however, if the decoding of POI NBT (from the region file) data fails, and the game then save the region file again, it might save false (0). This key is internally set to true when the POI section is refreshed, and a refresh always happens when the chunk section (with terrain data) at the same coordinates is decoded. **To sum up, it is very unlikely to get false.**
        - \[NBT List / JSON Array\] Records: May be empty.

          - \[NBT Compound / JSON Object\]: Single record.

            - \[Int Array\] pos: 3-element array encoding X, Y and Z.
            - \[Int\] free\_tickets: Indicates how many "tickets" are available for villagers to claim. A value of zero indicates that this poi is not available for any villager to claim. Internally _Minecraft_ specifies a max tickets for each poi type. This is the maximum number of villagers which can "take a ticket" (aka be using that poi type at the same time; aka max number of villagers which can claim that poi and store it in their "brain"). As of 1.17 all villager eligible poi type's have a ticket limit of one (1), with the single exception being `minecraft:meeting`, (block minecraft:bell) which has a limit of 32. Poi entries which are not for villager interaction such as beehives, nether portals, lighting rods, etc., have a max ticket count of zero (0) and therefore always have a **free\_tickets** of zero as well.
            - \[String\] type: Type of the point, for example: `minecraft:home`, `minecraft:meeting`, `minecraft:butcher`, `minecraft:armorer`, etc.
  - \[Int\] DataVersion: An integer displaying the [data version](https://minecraft.wiki/w/Data_version "Data version").

## History

\[ [edit](https://minecraft.wiki/w/Java_Edition_level_format?section=8&veaction=edit "Edit section: History") \| [edit source](https://minecraft.wiki/w/Java_Edition_level_format?action=edit&section=8 "Edit section's source code: History")\]

### Level format

\[ [edit](https://minecraft.wiki/w/Java_Edition_level_format?section=9&veaction=edit "Edit section: Level format") \| [edit source](https://minecraft.wiki/w/Java_Edition_level_format?action=edit&section=9 "Edit section's source code: Level format")\]

| \[hide\] [_Java Edition_](https://minecraft.wiki/w/Java_Edition_version_history "Java Edition version history") |
| --- |
| [1.14](https://minecraft.wiki/w/Java_Edition_1.14 "Java Edition 1.14") | [19w11a](https://minecraft.wiki/w/Java_Edition_19w11a "Java Edition 19w11a") | The poi folder was added to world saves and village data is moved to it. |
| [1.16](https://minecraft.wiki/w/Java_Edition_1.16 "Java Edition 1.16") | [20w14a](https://minecraft.wiki/w/Java_Edition_20w14a "Java Edition 20w14a") | Timestamps are no longer written to the session.lock file. |
| [1.16](https://minecraft.wiki/w/Java_Edition_1.16 "Java Edition 1.16") | [pre1](https://minecraft.wiki/w/Java_Edition_1.16-pre1 "Java Edition 1.16-pre1") | A single character ☃(E2 98 83) is now written to the session.lock file. |
| [26.1](https://minecraft.wiki/w/Java_Edition_26.1 "Java Edition 26.1") | [snap6](https://minecraft.wiki/w/Java_Edition_26.1_Snapshot_6 "Java Edition 26.1 Snapshot 6") | Restructured the entirety of the world save format : |
| All default dimensions are now stored in the dimensions subfolder, renamed the `DIM-1` and `DIM1` folders to `dimensions/minecraft/the_nether` and `dimensions/minecraft/the_end` respectively. |
| The Overworld data has been moved to `dimensions/minecraft/overworld`, this includes the `region`, `entities`, and `poi` folders, as well as related files out of data. |
| The top level `data` folder is now only for data shared across dimensions instead. |
| Player storage has been moved to the `players` subdirectory : `advancements``players/advancements`, `playerdata` -\> `players/data`, `stats` -\> `players/stats`. |
| The world resource pack (`resources.zip`) has been moved to the `resourcepacks` subdirectory. |
| Data saved in the data folder is now namespaced. All the data is stored in a namespace subfolder in the corresponding data folder, all existing vanilla data files have been moved accordingly. |
| Command storage is now stored in namespace subfolders instead of having a namespace suffix. |
| `chunks.dat` has been renamed to `chunk_tickets.dat`. |
| Data for maps is now stored in the `data/minecraft/maps` subfolder, map index files have been renamed to only the number. |
| `idcounts.dat` has been renamed to `last_id.dat`. |
| There is no more `raids_end.dat` special case, the End now uses `raids.dat`. |
| Structures saved by Structure Blocks have been moved from `generated/namespace/structures` to `generated/namespace/structure`. |
| [26.3](https://minecraft.wiki/w/Java_Edition_26.3 "Java Edition 26.3") | [snap7](https://minecraft.wiki/w/Java_Edition_26.3_Snapshot_7 "Java Edition 26.3 Snapshot 7") | `level.dat` now contains a `version_history` list with prior data versions of the file. |

### level.dat

\[ [edit](https://minecraft.wiki/w/Java_Edition_level_format?section=10&veaction=edit "Edit section: level.dat") \| [edit source](https://minecraft.wiki/w/Java_Edition_level_format?action=edit&section=10 "Edit section's source code: level.dat")\]

| \[hide\] [_Java Edition_](https://minecraft.wiki/w/Java_Edition_version_history "Java Edition version history") |
| --- |
| [26.1](https://minecraft.wiki/w/Java_Edition_26.1 "Java Edition 26.1") | [snap6](https://minecraft.wiki/w/Java_Edition_26.1_Snapshot_6 "Java Edition 26.1 Snapshot 6") | Restructured level.dat format : |
| The \[NBT Compound / JSON Object\] Player tag in level.dat has been replaced with a \[Int Array\] singleplayer\_uuid tag, referencing the player data file to use. |
| Difficulty-related settings have been moved into a \[NBT Compound / JSON Object\] difficulty\_settings tag. |
| \[Int\] Difficulty is changed to \[String\] difficulty with theses allowed values : `peaceful`, `easy`, `normal` and `hard`, \[Boolean\] DifficultyLocked is renamed to \[Boolean\] locked. |
| Data for the Ender Dragon fight has been moved out to the data folder to `dimensions/minecraft/the_end/data/minecraft/ender_dragon_fight.dat` |
| Wandering Trader data has been moved out to the data folder to `data/minecraft/wandering_trader.dat` |
| \[NBT Compound / JSON Object\] CustomBossEvents has been moved to the data folder to `data/minecraft/custom_boss_events.dat` |
| Weather-related data has been moved to the data folder to `data/minecraft/weather.dat` |
| \[NBT Compound / JSON Object\] ScheduledEvents has been moved out to the data folder to `data/minecraft/scheduled_events.dat` |
| \[NBT Compound / JSON Object\] game\_rules has been moved out to the data folder to `data/minecraft/game_rules.dat` |
| \[NBT Compound / JSON Object\] WorldGenSettings has been moved out to the data folder to `data/minecraft/world_gen_settings.dat` |
| \[NBT Compound / JSON Object\] world\_clocks has been moved out to the data folder to `data/minecraft/world_clocks.dat` |

### weather.dat

\[ [edit](https://minecraft.wiki/w/Java_Edition_level_format?section=11&veaction=edit "Edit section: weather.dat") \| [edit source](https://minecraft.wiki/w/Java_Edition_level_format?action=edit&section=11 "Edit section's source code: weather.dat")\]

| \[hide\] [_Java Edition_](https://minecraft.wiki/w/Java_Edition_version_history "Java Edition version history") |
| --- |
| [26.1](https://minecraft.wiki/w/Java_Edition_26.1 "Java Edition 26.1") | [snap6](https://minecraft.wiki/w/Java_Edition_26.1_Snapshot_6 "Java Edition 26.1 Snapshot 6") | Moved the weather data from `level.dat` to `data/minecraft/weather.dat` |
| \[Int\] clearWeatherTime has been renamed to \[Int\] clear\_weather\_time |
| \[Int\] rainTime has been renamed to \[Int\] rain\_time |
| \[Int\] thunderTime has been renamed to \[Int\] thunder\_time |

### wandering\_trader.dat

\[ [edit](https://minecraft.wiki/w/Java_Edition_level_format?section=12&veaction=edit "Edit section: wandering_trader.dat") \| [edit source](https://minecraft.wiki/w/Java_Edition_level_format?action=edit&section=12 "Edit section's source code: wandering_trader.dat")\]

| \[hide\] [_Java Edition_](https://minecraft.wiki/w/Java_Edition_version_history "Java Edition version history") |
| --- |
| [26.1](https://minecraft.wiki/w/Java_Edition_26.1 "Java Edition 26.1") | [snap6](https://minecraft.wiki/w/Java_Edition_26.1_Snapshot_6 "Java Edition 26.1 Snapshot 6") | Moved the Wandering trader data from `level.dat` to `data/minecraft/wandering_trader.dat` |
| \[Int Array\] WanderingTraderId has been removed. |
| \[Int\] WanderingTraderSpawnChance has been renamed to \[Int\] spawn\_chance |
| \[Int\] WanderingTraderSpawnDelay has been renamed to \[Int\] spawn\_delay |

### ender\_dragon\_fight.dat

\[ [edit](https://minecraft.wiki/w/Java_Edition_level_format?section=13&veaction=edit "Edit section: ender_dragon_fight.dat") \| [edit source](https://minecraft.wiki/w/Java_Edition_level_format?action=edit&section=13 "Edit section's source code: ender_dragon_fight.dat")\]

| \[hide\] [_Java Edition_](https://minecraft.wiki/w/Java_Edition_version_history "Java Edition version history") |
| --- |
| [26.1](https://minecraft.wiki/w/Java_Edition_26.1 "Java Edition 26.1") | [snap6](https://minecraft.wiki/w/Java_Edition_26.1_Snapshot_6 "Java Edition 26.1 Snapshot 6") | Moved the Ender Dragon Fight data from `level.dat` to `data/minecraft/ender_dragon_fight.dat` |
| \[Undefined\] NeedsStateScanning has been renamed to \[Undefined\] needs\_state\_scanning |
| \[Boolean\] DragonKilled has been renamed to \[Boolean\] dragon\_killed |
| \[Boolean\] PreviouslyKilled has been renamed to \[Boolean\] previously\_killed |
| \[Undefined\] IsRespawning has been replaced by \[Undefined\] respawn\_stage with theses allowed values : `start`, `preparing_to_summon_pillars`, `summoning_pillars`, `summoning_dragon`, `end` |
| \[Undefined\] Dragon has been renamed to \[Undefined\] dragon\_uuid |
| \[NBT Compound / JSON Object\] ExitPortalLocation has been renamed to \[NBT Compound / JSON Object\] exit\_portal\_location |
| \[NBT List / JSON Array\] Gateways has been renamed to \[NBT List / JSON Array\] gateways |
| Added \[Undefined\] respawn\_time, the time that has elapsed since the current stage of the respawn sequence started. |
| Added \[NBT List / JSON Array\] respawn\_crystals \- a list of UUIDs for the end crystals used to trigger the respawn sequence. |

### scheduled\_events.dat

\[ [edit](https://minecraft.wiki/w/Java_Edition_level_format?section=14&veaction=edit "Edit section: scheduled_events.dat") \| [edit source](https://minecraft.wiki/w/Java_Edition_level_format?action=edit&section=14 "Edit section's source code: scheduled_events.dat")\]

| \[hide\] [_Java Edition_](https://minecraft.wiki/w/Java_Edition_version_history "Java Edition version history") |
| --- |
| [26.1](https://minecraft.wiki/w/Java_Edition_26.1 "Java Edition 26.1") | [snap6](https://minecraft.wiki/w/Java_Edition_26.1_Snapshot_6 "Java Edition 26.1 Snapshot 6") | Moved the Scheduled Events data from `level.dat` to `data/minecraft/scheduled_events.dat` |
| \[Undefined\] Name has been renamed to \[Undefined\] id |
| \[Undefined\] TriggerTime has been renamed to \[Undefined\] trigger\_time |
| \[Undefined\] Callback has been renamed to \[Undefined\] callback |
| \[Undefined\] Type has been renamed to \[Undefined\] type |

### world\_gen\_settings.dat

\[ [edit](https://minecraft.wiki/w/Java_Edition_level_format?section=15&veaction=edit "Edit section: world_gen_settings.dat") \| [edit source](https://minecraft.wiki/w/Java_Edition_level_format?action=edit&section=15 "Edit section's source code: world_gen_settings.dat")\]

| \[hide\] [_Java Edition_](https://minecraft.wiki/w/Java_Edition_version_history "Java Edition version history") |
| --- |
| [26.1](https://minecraft.wiki/w/Java_Edition_26.1 "Java Edition 26.1") | [snap6](https://minecraft.wiki/w/Java_Edition_26.1_Snapshot_6 "Java Edition 26.1 Snapshot 6") | Moved the World Generation Settings data from `level.dat` to `data/minecraft/world_gen_settings.dat` |
| \[Boolean\] generate\_features has been renamed to \[Boolean\] generate\_structures |

## See also

\[ [edit](https://minecraft.wiki/w/Java_Edition_level_format?section=16&veaction=edit "Edit section: See also") \| [edit source](https://minecraft.wiki/w/Java_Edition_level_format?action=edit&section=16 "Edit section's source code: See also")\]

- [Bedrock Edition level format](https://minecraft.wiki/w/Bedrock_Edition_level_format "Bedrock Edition level format")

## References

\[ [edit](https://minecraft.wiki/w/Java_Edition_level_format?section=17&veaction=edit "Edit section: References") \| [edit source](https://minecraft.wiki/w/Java_Edition_level_format?action=edit&section=17 "Edit section's source code: References")\]

1. [↑](https://minecraft.wiki/w/Java_Edition_level_format#cite_ref-1 "Jump up")[http://www.reddit.com/r/Minecraft/comments/ywjbk/superflat\_customization/c5zusxl](http://www.reddit.com/r/Minecraft/comments/ywjbk/superflat_customization/c5zusxl)

## Navigation

\[ [edit](https://minecraft.wiki/w/Java_Edition_level_format?section=18&veaction=edit "Edit section: Navigation") \| [edit source](https://minecraft.wiki/w/Java_Edition_level_format?action=edit&section=18 "Edit section's source code: Navigation")\]

| \[hide\]<br>- [v](https://minecraft.wiki/w/Template:Navbox_Java_Edition_technical "Template:Navbox Java Edition technical")<br>- [t](https://minecraft.wiki/w/Special:TalkPage/Template:Navbox_Java_Edition_technical "Special:TalkPage/Template:Navbox Java Edition technical")<br>- [e](https://minecraft.wiki/w/Special:EditPage/Template:Navbox_Java_Edition_technical "Special:EditPage/Template:Navbox Java Edition technical")<br>_[Java Edition](https://minecraft.wiki/w/Java_Edition "Java Edition")_ technical |
| --- |
| | \[hide\]General |
| --- |
| Concepts | - [![](https://minecraft.wiki/images/BlockSprite_chest.png?15d81)](https://minecraft.wiki/w/Block_entity "Block entity")[Block entity](https://minecraft.wiki/w/Block_entity "Block entity")<br>- [![](https://minecraft.wiki/images/EnvSprite_map.png?b863e)](https://minecraft.wiki/w/Coordinates "Coordinates")[Coordinates](https://minecraft.wiki/w/Coordinates "Coordinates")<br>- [![](https://minecraft.wiki/images/EffectSprite_infested.png?4562a)](https://minecraft.wiki/w/Crash "Crash")[Crashes](https://minecraft.wiki/w/Crash "Crash")<br>- [Loot context](https://minecraft.wiki/w/Loot_context "Loot context")<br>- [![](https://minecraft.wiki/images/EntitySprite_cow.png?893cf)](https://minecraft.wiki/w/Mob_AI "Mob AI")[Mob AI](https://minecraft.wiki/w/Mob_AI "Mob AI")<br>- [![](https://minecraft.wiki/images/BlockSprite_lodestone.png?00f1a)](https://minecraft.wiki/w/Point_of_Interest "Point of Interest")[Point of Interest](https://minecraft.wiki/w/Point_of_Interest "Point of Interest")<br>- [![](https://minecraft.wiki/images/thumb/File_directory.png/16px-File_directory.png?8a409)](https://minecraft.wiki/w/Identifier "Identifier")[Identifier](https://minecraft.wiki/w/Identifier "Identifier")<br>- [![](https://minecraft.wiki/images/BlockSprite_camera.png?7ee99)](https://minecraft.wiki/w/Screenshot "Screenshot")[Screenshot](https://minecraft.wiki/w/Screenshot "Screenshot")<br>- [![](https://minecraft.wiki/images/EnvSprite_scoreboard.png?38feb)](https://minecraft.wiki/w/Statistics "Statistics")[Statistics](https://minecraft.wiki/w/Statistics "Statistics")<br>- [![](https://minecraft.wiki/images/ItemSprite_book.png?791a5)](https://minecraft.wiki/w/Telemetry "Telemetry")[Telemetry](https://minecraft.wiki/w/Telemetry "Telemetry")<br>- [![](https://minecraft.wiki/images/ItemSprite_clock.png?30324)](https://minecraft.wiki/w/Tick "Tick")[Tick](https://minecraft.wiki/w/Tick "Tick")<br>- [![](https://minecraft.wiki/images/ItemSprite_wheat-seeds.png?b83e5)](https://minecraft.wiki/w/Random_Tick "Random Tick")[Random Tick](https://minecraft.wiki/w/Random_Tick "Random Tick")<br>- [![](https://minecraft.wiki/images/EnvSprite_number.png?9ceb9)](https://minecraft.wiki/w/UUID "UUID")[UUID](https://minecraft.wiki/w/UUID "UUID")<br>- [![](https://minecraft.wiki/images/Json_icon.png?f2b35)](https://minecraft.wiki/w/JSON "JSON")[JSON](https://minecraft.wiki/w/JSON "JSON") |
| [General format](https://minecraft.wiki/w/Development_resources "Development resources") | - [![](https://minecraft.wiki/images/EnvSprite_number.png?9ceb9)](https://minecraft.wiki/w/Java_Edition_data_values "Java Edition data values")[Data values](https://minecraft.wiki/w/Java_Edition_data_values "Java Edition data values")<br>  - [![](https://minecraft.wiki/images/LegacyBlockSprite_bricks-je1.png?9a58b)](https://minecraft.wiki/w/Java_Edition_Classic_data_values "Java Edition Classic data values")[Classic](https://minecraft.wiki/w/Java_Edition_Classic_data_values "Java Edition Classic data values")<br>    - [Remake](https://minecraft.wiki/w/Classic_remake_data_values "Classic remake data values")<br>  - [![](https://minecraft.wiki/images/EntitySprite_rana.png?3f2f9)](https://minecraft.wiki/w/Java_Edition_Indev_data_values "Java Edition Indev data values")[Indev](https://minecraft.wiki/w/Java_Edition_Indev_data_values "Java Edition Indev data values")<br>  - [![](https://minecraft.wiki/images/BlockSprite_stone.png?e9a91)](https://minecraft.wiki/w/Java_Edition_pre-flattening_data_values "Java Edition pre-flattening data values")[Pre-flattening](https://minecraft.wiki/w/Java_Edition_pre-flattening_data_values "Java Edition pre-flattening data values")<br>- [![](https://minecraft.wiki/images/EnvSprite_item.png?89d23)](https://minecraft.wiki/w/Data_component_format "Data component format")[Data component format](https://minecraft.wiki/w/Data_component_format "Data component format")<br>  - [![](https://minecraft.wiki/images/BlockSprite_test-block-start.png?35191)](https://minecraft.wiki/w/Data_component_predicate "Data component predicate")[Predicate](https://minecraft.wiki/w/Data_component_predicate "Data component predicate")<br>- [![](https://minecraft.wiki/images/EnvSprite_entities.png?94711)](https://minecraft.wiki/w/Entity_format "Entity format")[Entity format](https://minecraft.wiki/w/Entity_format "Entity format")<br>- [![](https://minecraft.wiki/images/BlockSprite_chest.png?15d81)](https://minecraft.wiki/w/Block_entity_format "Block entity format")[Block entity format](https://minecraft.wiki/w/Block_entity_format "Block entity format")<br>- [![](https://minecraft.wiki/images/ItemSprite_map.png?d8b77)](https://minecraft.wiki/w/Map_item_format "Map item format")[Map item format](https://minecraft.wiki/w/Map_item_format "Map item format")<br>- [NBT Format](https://minecraft.wiki/w/NBT_format "NBT format")<br>- [![](https://minecraft.wiki/images/EffectSprite_particle-healing.png?1357a)](https://minecraft.wiki/w/Particle_format "Particle format")[Particle format](https://minecraft.wiki/w/Particle_format "Particle format")<br>- [![](https://minecraft.wiki/images/ItemSprite_book-and-quill.png?f190b)](https://minecraft.wiki/w/Text_component_format "Text component format")[Text component format](https://minecraft.wiki/w/Text_component_format "Text component format")<br>- [§](https://minecraft.wiki/w/Formatting_codes "Formatting codes") [Formatting codes](https://minecraft.wiki/w/Formatting_codes "Formatting codes")<br>- [![](https://minecraft.wiki/images/thumb/Movement_hint.png/16px-Movement_hint.png?92667)](https://minecraft.wiki/w/Key_codes "Key codes")[Key codes](https://minecraft.wiki/w/Key_codes "Key codes")<br>- [![](https://minecraft.wiki/images/Dice_2d.png?d5a01)](https://minecraft.wiki/w/Random_sequence_format "Random sequence format")[Random sequence](https://minecraft.wiki/w/Random_sequence_format "Random sequence format")<br>- [![](https://minecraft.wiki/images/BlockSprite_structure-block.png?381fc)](https://minecraft.wiki/w/Structure_file "Structure file")[Structure file format](https://minecraft.wiki/w/Structure_file "Structure file")<br>  - [![](https://minecraft.wiki/images/EnvSprite_chunk.png?b2cf1)](https://minecraft.wiki/w/Schematic_file_format "Schematic file format")[Schematic file format](https://minecraft.wiki/w/Schematic_file_format "Schematic file format")<br>- [Flattening](https://minecraft.wiki/w/The_Flattening_(Java_Edition) "The Flattening (Java Edition)") |
| [World](https://minecraft.wiki/w/World "World") | - [![](https://minecraft.wiki/images/EnvSprite_altitude.png?9b274)](https://minecraft.wiki/w/Heightmap "Heightmap")[Heightmap](https://minecraft.wiki/w/Heightmap "Heightmap")
- [![](https://minecraft.wiki/images/EnvSprite_mountain.png?2e0ae)](https://minecraft.wiki/w/World_seed "World seed")[Seed](https://minecraft.wiki/w/World_seed "World seed")
  - [Anomalous](https://minecraft.wiki/w/Anomalous_world_seeds "Anomalous world seeds")
- [![](https://minecraft.wiki/images/EnvSprite_number.png?9ceb9)](https://minecraft.wiki/w/Data_version "Data version")[Data version](https://minecraft.wiki/w/Data_version "Data version")

| Legacy | - [![](https://minecraft.wiki/images/EnvSprite_chunk.png?b2cf1)](https://minecraft.wiki/w/Spawn_chunk "Spawn chunk")[Spawn chunk](https://minecraft.wiki/w/Spawn_chunk "Spawn chunk") |
| Level format | - [![](https://minecraft.wiki/images/BlockSprite_anvil.png?a26c9)](https://minecraft.wiki/w/Anvil_file_format "Anvil file format")[Anvil file format](https://minecraft.wiki/w/Anvil_file_format "Anvil file format")
- [![](https://minecraft.wiki/images/EnvSprite_chunk.png?b2cf1)](https://minecraft.wiki/w/Chunk_format "Chunk format")[Chunk format](https://minecraft.wiki/w/Chunk_format "Chunk format")
- [![](https://minecraft.wiki/images/EntitySprite_steve.png?856f8)](https://minecraft.wiki/w/Player.dat_format "Player.dat format")[Player format](https://minecraft.wiki/w/Player.dat_format "Player.dat format")
- [![](https://minecraft.wiki/images/BlockSprite_lodestone.png?00f1a)](https://minecraft.wiki/w/Point_of_Interest_format "Point of Interest format")[Point of Interest format](https://minecraft.wiki/w/Point_of_Interest_format "Point of Interest format")
- [![](https://minecraft.wiki/images/EntitySprite_ravager.png?40196)](https://minecraft.wiki/w/Raids.dat_format "Raids.dat format")[raids.dat format](https://minecraft.wiki/w/Raids.dat_format "Raids.dat format")
- [![](https://minecraft.wiki/images/BlockSprite_chain-command-block.png?0afa8)](https://minecraft.wiki/w/Command_storage_format "Command storage format")[Command storage format](https://minecraft.wiki/w/Command_storage_format "Command storage format")
- [![](https://minecraft.wiki/images/EnvSprite_scoreboard.png?38feb)](https://minecraft.wiki/w/Scoreboard#NBT_format "Scoreboard")[Scoreboard format](https://minecraft.wiki/w/Scoreboard#NBT_format "Scoreboard")

| Legacy | - [![](https://minecraft.wiki/images/LegacyBlockSprite_bricks-je1.png?9a58b)](https://minecraft.wiki/w/Java_Edition_Classic_level_format "Java Edition Classic level format")[Classic level format](https://minecraft.wiki/w/Java_Edition_Classic_level_format "Java Edition Classic level format")<br>- [Classic server protocol](https://minecraft.wiki/w/Classic_server_protocol "Classic server protocol")<br>- [![](https://minecraft.wiki/images/EntitySprite_rana.png?3f2f9)](https://minecraft.wiki/w/Java_Edition_Indev_level_format "Java Edition Indev level format")[Indev level format](https://minecraft.wiki/w/Java_Edition_Indev_level_format "Java Edition Indev level format")<br>- [![](https://minecraft.wiki/images/EnvSprite_nether-portal.png?47646)](https://minecraft.wiki/w/Java_Edition_Alpha_level_format "Java Edition Alpha level format")[Alpha level format](https://minecraft.wiki/w/Java_Edition_Alpha_level_format "Java Edition Alpha level format")<br>  - [![](https://minecraft.wiki/images/LegacyItemSprite_oak-door-revision-1.png?b7426)](https://minecraft.wiki/w/Zone_file_format "Zone file format")[Zone file format](https://minecraft.wiki/w/Zone_file_format "Zone file format")<br>- [![](https://minecraft.wiki/images/ItemSprite_locked-map.png?66bd6)](https://minecraft.wiki/w/Region_file_format "Region file format")[Region file format](https://minecraft.wiki/w/Region_file_format "Region file format")<br>- [![](https://minecraft.wiki/images/Servers.png?b1dc2)](https://minecraft.wiki/w/Server_level.dat "Server level.dat")[server\_level.dat format](https://minecraft.wiki/w/Server_level.dat "Server level.dat")<br>- [![](https://minecraft.wiki/images/EnvSprite_new-village.png?43174)](https://minecraft.wiki/w/Villages.dat_format "Villages.dat format")[villages.dat format](https://minecraft.wiki/w/Villages.dat_format "Villages.dat format")<br>- [![](https://minecraft.wiki/images/EnvSprite_abandoned-mineshaft.png?fab65)](https://minecraft.wiki/w/Generated_structures_data_file_format "Generated structures data file format")[Generated structures format](https://minecraft.wiki/w/Generated_structures_data_file_format "Generated structures data file format") | | |
| [.minecraft](https://minecraft.wiki/w/.minecraft ".minecraft") | - [![](https://minecraft.wiki/images/thumb/File_archive.png/16px-File_archive.png?5ba7d)](https://minecraft.wiki/w/Client.jar "Client.jar")[client.jar](https://minecraft.wiki/w/Client.jar "Client.jar")<br>  - [![](https://minecraft.wiki/images/EnvSprite_number.png?9ceb9)](https://minecraft.wiki/w/Version.json "Version.json")[version.json](https://minecraft.wiki/w/Version.json "Version.json")<br>- [![](https://minecraft.wiki/images/ItemSprite_book-and-quill.png?f190b)](https://minecraft.wiki/w/Client.json "Client.json")[client.json](https://minecraft.wiki/w/Client.json "Client.json")<br>- [![](https://minecraft.wiki/images/BlockSprite_command-block.png?e7078)](https://minecraft.wiki/w/Command_history.txt "Command history.txt")[command\_history.txt](https://minecraft.wiki/w/Command_history.txt "Command history.txt")<br>- [![](https://minecraft.wiki/images/BlockSprite_chest.png?15d81)](https://minecraft.wiki/w/Launcher_profiles.json "Launcher profiles.json")[launcher\_profiles.json](https://minecraft.wiki/w/Launcher_profiles.json "Launcher profiles.json")<br>- [![](https://minecraft.wiki/images/BlockSprite_gear.png?03da3)](https://minecraft.wiki/w/Launcher_settings.json "Launcher settings.json")[launcher\_settings.json](https://minecraft.wiki/w/Launcher_settings.json "Launcher settings.json")<br>- [![](https://minecraft.wiki/images/Chat_settings_gear.png?6a179)](https://minecraft.wiki/w/Options.txt_(Java_Edition) "Options.txt (Java Edition)")[options.txt](https://minecraft.wiki/w/Options.txt_(Java_Edition) "Options.txt (Java Edition)")<br>- [![](https://minecraft.wiki/images/EnvSprite_number.png?9ceb9)](https://minecraft.wiki/w/Version_manifest.json "Version manifest.json")[version\_manifest.json](https://minecraft.wiki/w/Version_manifest.json "Version manifest.json")<br>- [![](https://minecraft.wiki/images/ItemSprite_paper.png?565a1)](https://minecraft.wiki/w/Hotbar.nbt_format "Hotbar.nbt format")[hotbar.nbt format](https://minecraft.wiki/w/Hotbar.nbt_format "Hotbar.nbt format")<br>- [![](https://minecraft.wiki/images/Servers.png?b1dc2)](https://minecraft.wiki/w/Servers.dat_format "Servers.dat format")[Server list format](https://minecraft.wiki/w/Servers.dat_format "Servers.dat format") |
| Tools | - `F3` [Debug screen](https://minecraft.wiki/w/Debug_screen "Debug screen")
  - [hotkey](https://minecraft.wiki/w/Debug_hotkey "Debug hotkey")
  - [renderer](https://minecraft.wiki/w/Debug_renderer "Debug renderer")
- [![](https://minecraft.wiki/images/Mojang_logo.svg?0b294)](https://minecraft.wiki/w/Java_developer_tools "Java developer tools")[Developer Tools](https://minecraft.wiki/w/Java_developer_tools "Java developer tools")
  - [![](https://minecraft.wiki/images/BlockSprite_test-instance-block.png?27a39)](https://minecraft.wiki/w/GameTest "GameTest")[GameTest](https://minecraft.wiki/w/GameTest "GameTest")
  - [DataFixerUpper](https://minecraft.wiki/w/DataFixerUpper "DataFixerUpper")
  - [![](https://minecraft.wiki/images/thumb/Wrench.png/16px-Wrench.png?fae21)](https://minecraft.wiki/w/Debug_property "Debug property")[Debug properties](https://minecraft.wiki/w/Debug_property "Debug property")

| Legacy | - [![](https://minecraft.wiki/images/Obfuscated.png?8e663)](https://minecraft.wiki/w/Obfuscation_map "Obfuscation map")[Obfuscation map](https://minecraft.wiki/w/Obfuscation_map "Obfuscation map") | |
| Sound | - [![](https://minecraft.wiki/images/BlockSprite_jukebox-side.png?8477e)](https://minecraft.wiki/w/Block_sound_type "Block sound type")[Block sound type](https://minecraft.wiki/w/Block_sound_type "Block sound type")<br>- [![](https://minecraft.wiki/images/EnvSprite_chat.png?0dd92)](https://minecraft.wiki/w/Closed_captions "Closed captions")[Closed captions](https://minecraft.wiki/w/Closed_captions "Closed captions")<br>- [![](https://minecraft.wiki/images/EnvSprite_ambience.png?d7c92)](https://minecraft.wiki/w/Sounds.json "Sounds.json")[sounds.json](https://minecraft.wiki/w/Sounds.json "Sounds.json") |
| [Commands](https://minecraft.wiki/w/Commands "Commands") | - [Brigadier](https://minecraft.wiki/w/Brigadier "Brigadier")<br>- [![](https://minecraft.wiki/images/BlockSprite_repeating-command-block.png?1dad0)](https://minecraft.wiki/w/Function_(Java_Edition) "Function (Java Edition)")[Functions](https://minecraft.wiki/w/Function_(Java_Edition) "Function (Java Edition)")<br>**[All commands](https://minecraft.wiki/w/Template:Navbox_commands "Template:Navbox commands")** |
| [Launching](https://minecraft.wiki/w/Minecraft_Launcher "Minecraft Launcher") | - [Mojang API](https://minecraft.wiki/w/Mojang_API "Mojang API")
- [![](https://minecraft.wiki/images/Microsoft_logo.svg?7e87a)](https://minecraft.wiki/w/Microsoft_authentication "Microsoft authentication")[Microsoft authentication](https://minecraft.wiki/w/Microsoft_authentication "Microsoft authentication")
- [![](https://minecraft.wiki/images/thumb/Java_Edition_icon_3.png/16px-Java_Edition_icon_3.png?f7112)](https://minecraft.wiki/w/Quick_Play "Quick Play")[Quick Play](https://minecraft.wiki/w/Quick_Play "Quick Play")

| Legacy | - [Legacy Minecraft authentication](https://minecraft.wiki/w/Legacy_Minecraft_authentication "Legacy Minecraft authentication")<br>- [Yggdrasil](https://minecraft.wiki/w/Yggdrasil "Yggdrasil") | |
| [Protocol](https://minecraft.wiki/w/Java_Edition_protocol "Java Edition protocol") | - [![](https://minecraft.wiki/images/EnvSprite_number.png?9ceb9)](https://minecraft.wiki/w/Protocol_version "Protocol version")[Protocol version](https://minecraft.wiki/w/Protocol_version "Protocol version")<br>- [![](https://minecraft.wiki/images/ItemSprite_bundle.png?9eb9f)](https://minecraft.wiki/w/Java_Edition_protocol/Packets "Java Edition protocol/Packets")[Packets](https://minecraft.wiki/w/Java_Edition_protocol/Packets "Java Edition protocol/Packets")<br>- [Data types](https://minecraft.wiki/w/Java_Edition_protocol/Data_types "Java Edition protocol/Data types")<br>- [![](https://minecraft.wiki/images/ItemSprite_trial-key.png?9e6c1)](https://minecraft.wiki/w/Java_Edition_protocol/Encryption "Java Edition protocol/Encryption")[Encryption](https://minecraft.wiki/w/Java_Edition_protocol/Encryption "Java Edition protocol/Encryption") |
| [Server](https://minecraft.wiki/w/Server "Server") | - [![](https://minecraft.wiki/images/thumb/File_archive.png/16px-File_archive.png?5ba7d)](https://minecraft.wiki/w/Server.jar "Server.jar")[server.jar](https://minecraft.wiki/w/Server.jar "Server.jar")
- [![](https://minecraft.wiki/images/BlockSprite_test-instance-block.png?27a39)](https://minecraft.wiki/w/Server.properties "Server.properties")[server.properties](https://minecraft.wiki/w/Server.properties "Server.properties")
- [![](https://minecraft.wiki/images/BlockSprite_test-instance-block.png?27a39)](https://minecraft.wiki/w/Server/Requirements "Server/Requirements")[Server requirements](https://minecraft.wiki/w/Server/Requirements "Server/Requirements")
- [![](https://minecraft.wiki/images/BlockSprite_test-block-accept.png?08355)](https://minecraft.wiki/w/Whitelist "Whitelist")[Whitelist](https://minecraft.wiki/w/Whitelist "Whitelist")
- [Operator list](https://minecraft.wiki/w/Server#Operator_list "Server")
- [![](https://minecraft.wiki/images/ItemSprite_rule-book.png?c3215)](https://minecraft.wiki/w/Code_of_conduct "Code of conduct")[Code of conduct](https://minecraft.wiki/w/Code_of_conduct "Code of conduct")

| Protocols | - [Query](https://minecraft.wiki/w/Query "Query")<br>- [RCON](https://minecraft.wiki/w/RCON "RCON")<br>- [Server Management Protocol](https://minecraft.wiki/w/Minecraft_Server_Management_Protocol "Minecraft Server Management Protocol") | |
| Legacy | - [al\_version](https://minecraft.wiki/w/Al_version "Al version")<br>- [![](https://minecraft.wiki/images/EnvSprite_item.png?89d23)](https://minecraft.wiki/w/Item_format/Before_1.20.5 "Item format/Before 1.20.5")[Item format](https://minecraft.wiki/w/Item_format/Before_1.20.5 "Item format/Before 1.20.5") | |
| | \[show\][Data pack](https://minecraft.wiki/w/Data_pack "Data pack") |
| --- |
| Components | - [pack.mcmeta](https://minecraft.wiki/w/Pack.mcmeta "Pack.mcmeta")
  - [![](https://minecraft.wiki/images/EnvSprite_number.png?9ceb9)](https://minecraft.wiki/w/Pack_format "Pack format")[Pack format](https://minecraft.wiki/w/Pack_format "Pack format")
- [![](https://minecraft.wiki/images/ItemSprite_map.png?d8b77)](https://minecraft.wiki/w/Advancement_definition "Advancement definition")[Advancements](https://minecraft.wiki/w/Advancement_definition "Advancement definition")
- [![](https://minecraft.wiki/images/BlockSprite_repeating-command-block.png?1dad0)](https://minecraft.wiki/w/Function_(Java_Edition) "Function (Java Edition)")[Functions](https://minecraft.wiki/w/Function_(Java_Edition) "Function (Java Edition)")
- [![](https://minecraft.wiki/images/BlockSprite_red-banner.png?8b4d0)](https://minecraft.wiki/w/Item_modifier "Item modifier")[Item modifier](https://minecraft.wiki/w/Item_modifier "Item modifier")
- [![](https://minecraft.wiki/images/ItemSprite_diamond.png?8f019)](https://minecraft.wiki/w/Loot_table "Loot table")[Loot tables](https://minecraft.wiki/w/Loot_table "Loot table")
- [![](https://minecraft.wiki/images/BlockSprite_test-block-start.png?35191)](https://minecraft.wiki/w/Predicate "Predicate")[Predicate](https://minecraft.wiki/w/Predicate "Predicate")
- [![](https://minecraft.wiki/images/BlockSprite_crafting-table.png?6e126)](https://minecraft.wiki/w/Recipe_(Java_Edition) "Recipe (Java Edition)")[Recipe](https://minecraft.wiki/w/Recipe_(Java_Edition) "Recipe (Java Edition)")
- [![](https://minecraft.wiki/images/EffectSprite_strength.png?05e79)](https://minecraft.wiki/w/Damage_type "Damage type")[Damage type](https://minecraft.wiki/w/Damage_type "Damage type")
- [![](https://minecraft.wiki/images/EnvSprite_chat.png?0dd92)](https://minecraft.wiki/w/Chat_type "Chat type")[Chat type](https://minecraft.wiki/w/Chat_type "Chat type")
- [![](https://minecraft.wiki/images/ItemSprite_enchanted-book.png?b7877)](https://minecraft.wiki/w/Enchantment_definition "Enchantment definition")[Enchantment](https://minecraft.wiki/w/Enchantment_definition "Enchantment definition")
- [![](https://minecraft.wiki/images/BlockSprite_enchanting-table.png?45e2c)](https://minecraft.wiki/w/Enchantment_provider "Enchantment provider")[Enchantment provider](https://minecraft.wiki/w/Enchantment_provider "Enchantment provider")
- [![](https://minecraft.wiki/images/ItemSprite_oak-sign-pre-texture-update.png?a5693)](https://minecraft.wiki/w/Font_definition "Font definition")[Font definition](https://minecraft.wiki/w/Font_definition "Font definition")
- [![](https://minecraft.wiki/images/ItemSprite_painting.png?55d20)](https://minecraft.wiki/w/Painting_variant_definition "Painting variant definition")[Painting variant](https://minecraft.wiki/w/Painting_variant_definition "Painting variant definition")
- [![](https://minecraft.wiki/images/BlockSprite_white-banner.png?8b4d0)](https://minecraft.wiki/w/Banner_pattern_definition "Banner pattern definition")[Banner pattern](https://minecraft.wiki/w/Banner_pattern_definition "Banner pattern definition")
- [![](https://minecraft.wiki/images/ItemSprite_goat-horn.png?e5a9f)](https://minecraft.wiki/w/Instrument_definition "Instrument definition")[Instrument](https://minecraft.wiki/w/Instrument_definition "Instrument definition")
- [![](https://minecraft.wiki/images/BlockSprite_jukebox.png?86205)](https://minecraft.wiki/w/Jukebox_song_definition "Jukebox song definition")[Jukebox song](https://minecraft.wiki/w/Jukebox_song_definition "Jukebox song definition")
- [![](https://minecraft.wiki/images/BlockSprite_trial-spawner.png?0a3dc)](https://minecraft.wiki/w/Trial_spawner_configuration "Trial spawner configuration")[Trial spawner configuration](https://minecraft.wiki/w/Trial_spawner_configuration "Trial spawner configuration")
- [![](https://minecraft.wiki/images/EntitySprite_pig.png?5435e)](https://minecraft.wiki/w/Mob_variant_definitions "Mob variant definitions")[Mob variants](https://minecraft.wiki/w/Mob_variant_definitions "Mob variant definitions")
- [![](https://minecraft.wiki/images/ItemSprite_paper.png?565a1)](https://minecraft.wiki/w/Dialog "Dialog")[Dialog](https://minecraft.wiki/w/Dialog "Dialog")
- [![](https://minecraft.wiki/images/ItemSprite_wayfinder-armor-trim.png?ffaf0)](https://minecraft.wiki/w/Armor_trim_definition "Armor trim definition")[Armor trim](https://minecraft.wiki/w/Armor_trim_definition "Armor trim definition")
- [![](https://minecraft.wiki/images/ItemSprite_clock.png?30324)](https://minecraft.wiki/w/Timeline "Timeline")[Timeline](https://minecraft.wiki/w/Timeline "Timeline")
- [![](https://minecraft.wiki/images/EntitySprite_villager.png?05433)](https://minecraft.wiki/w/Villager_trade_definition "Villager trade definition")[Villager trade](https://minecraft.wiki/w/Villager_trade_definition "Villager trade definition")
- [Trade set](https://minecraft.wiki/w/Trade_set "Trade set")
- [World clock](https://minecraft.wiki/w/World_clock "World clock")
- [![](https://minecraft.wiki/images/EntitySprite_sulfur-cube.png?ad68d)](https://minecraft.wiki/w/Sulfur_cube_archetype_definition "Sulfur cube archetype definition")[Sulfur cube archetype](https://minecraft.wiki/w/Sulfur_cube_archetype_definition "Sulfur cube archetype definition")
- [![](https://minecraft.wiki/images/ItemSprite_footprint.png?1c844)](https://minecraft.wiki/w/Slot_source "Slot source")[Slot source](https://minecraft.wiki/w/Slot_source "Slot source")
- [![](https://minecraft.wiki/images/ItemSprite_danger-pottery-sherd.png?b8147)](https://minecraft.wiki/w/Decorated_pot_pattern_definition "Decorated pot pattern definition")[Decorated pot pattern](https://minecraft.wiki/w/Decorated_pot_pattern_definition "Decorated pot pattern definition")
- [![](https://minecraft.wiki/images/EnvSprite_number.png?9ceb9)](https://minecraft.wiki/w/Number_provider "Number provider")[Number provider](https://minecraft.wiki/w/Number_provider "Number provider")
- [![](https://minecraft.wiki/images/ItemSprite_wooden-hoe.png?30fb3)](https://minecraft.wiki/w/Block_transformer_definition "Block transformer definition")[Block transformer](https://minecraft.wiki/w/Block_transformer_definition "Block transformer definition")
- [Block sound set](https://minecraft.wiki/w/Block_sound_set_definition "Block sound set definition") ​\[ _upcoming: [JE 26.4](https://minecraft.wiki/w/Java_Edition_26.4 "Java Edition 26.4")_\]

| [Tag](https://minecraft.wiki/w/Tag_(Java_Edition) "Tag (Java Edition)") | - [![](https://minecraft.wiki/images/BlockSprite_grass-block.png?97c2e)](https://minecraft.wiki/w/Block_tag_(Java_Edition) "Block tag (Java Edition)")[Block](https://minecraft.wiki/w/Block_tag_(Java_Edition) "Block tag (Java Edition)")<br>- [![](https://minecraft.wiki/images/EnvSprite_item.png?89d23)](https://minecraft.wiki/w/Item_tag_(Java_Edition) "Item tag (Java Edition)")[Item](https://minecraft.wiki/w/Item_tag_(Java_Edition) "Item tag (Java Edition)")<br>- [![](https://minecraft.wiki/images/BlockSprite_repeating-command-block.png?1dad0)](https://minecraft.wiki/w/Function_tag_(Java_Edition) "Function tag (Java Edition)")[Function](https://minecraft.wiki/w/Function_tag_(Java_Edition) "Function tag (Java Edition)")<br>- [![](https://minecraft.wiki/images/ItemSprite_water-bucket.png?6e72b)](https://minecraft.wiki/w/Fluid_tag_(Java_Edition) "Fluid tag (Java Edition)")[Fluid](https://minecraft.wiki/w/Fluid_tag_(Java_Edition) "Fluid tag (Java Edition)")<br>- [![](https://minecraft.wiki/images/EnvSprite_entities.png?94711)](https://minecraft.wiki/w/Entity_type_tag_(Java_Edition) "Entity type tag (Java Edition)")[Entity type](https://minecraft.wiki/w/Entity_type_tag_(Java_Edition) "Entity type tag (Java Edition)")<br>- [![](https://minecraft.wiki/images/BlockSprite_sculk-sensor.png?ccbdb)](https://minecraft.wiki/w/Game_event_tag_(Java_Edition) "Game event tag (Java Edition)")[Game event](https://minecraft.wiki/w/Game_event_tag_(Java_Edition) "Game event tag (Java Edition)")<br>- [![](https://minecraft.wiki/images/BiomeSprite_forest.png?98e29)](https://minecraft.wiki/w/Biome_tag_(Java_Edition) "Biome tag (Java Edition)")[Biome](https://minecraft.wiki/w/Biome_tag_(Java_Edition) "Biome tag (Java Edition)")<br>- [![](https://minecraft.wiki/images/EnvSprite_superflat.png?54c14)](https://minecraft.wiki/w/Flat_level_generator_preset_tag_(Java_Edition) "Flat level generator preset tag (Java Edition)")[Flat level generator preset](https://minecraft.wiki/w/Flat_level_generator_preset_tag_(Java_Edition) "Flat level generator preset tag (Java Edition)")<br>- [![](https://minecraft.wiki/images/EnvSprite_mountain.png?2e0ae)](https://minecraft.wiki/w/World_preset_tag_(Java_Edition) "World preset tag (Java Edition)")[World preset](https://minecraft.wiki/w/World_preset_tag_(Java_Edition) "World preset tag (Java Edition)")<br>- [![](https://minecraft.wiki/images/EnvSprite_jungle-pyramid.png?be383)](https://minecraft.wiki/w/Structure_tag_(Java_Edition) "Structure tag (Java Edition)")[Structure](https://minecraft.wiki/w/Structure_tag_(Java_Edition) "Structure tag (Java Edition)")<br>- [![](https://minecraft.wiki/images/BlockSprite_lodestone.png?00f1a)](https://minecraft.wiki/w/Point_of_interest_type_tag_(Java_Edition) "Point of interest type tag (Java Edition)")[Point of interest type](https://minecraft.wiki/w/Point_of_interest_type_tag_(Java_Edition) "Point of interest type tag (Java Edition)")<br>- [![](https://minecraft.wiki/images/ItemSprite_painting.png?55d20)](https://minecraft.wiki/w/Painting_variant_tag_(Java_Edition) "Painting variant tag (Java Edition)")[Painting variant](https://minecraft.wiki/w/Painting_variant_tag_(Java_Edition) "Painting variant tag (Java Edition)")<br>- [![](https://minecraft.wiki/images/BlockSprite_white-banner.png?8b4d0)](https://minecraft.wiki/w/Banner_pattern_tag_(Java_Edition) "Banner pattern tag (Java Edition)")[Banner pattern](https://minecraft.wiki/w/Banner_pattern_tag_(Java_Edition) "Banner pattern tag (Java Edition)")<br>- [![](https://minecraft.wiki/images/ItemSprite_goat-horn.png?e5a9f)](https://minecraft.wiki/w/Instrument_tag_(Java_Edition) "Instrument tag (Java Edition)")[Instrument](https://minecraft.wiki/w/Instrument_tag_(Java_Edition) "Instrument tag (Java Edition)")<br>- ![❤️](https://minecraft.wiki/images/Heart_%28icon%29.png?faf83)[Damage type](https://minecraft.wiki/w/Damage_type_tag_(Java_Edition) "Damage type tag (Java Edition)")<br>- [![](https://minecraft.wiki/images/ItemSprite_enchanted-book.png?b7877)](https://minecraft.wiki/w/Enchantment_tag_(Java_Edition) "Enchantment tag (Java Edition)")[Enchantment](https://minecraft.wiki/w/Enchantment_tag_(Java_Edition) "Enchantment tag (Java Edition)")<br>- [![](https://minecraft.wiki/images/ItemSprite_paper.png?565a1)](https://minecraft.wiki/w/Dialog_tag_(Java_Edition) "Dialog tag (Java Edition)")[Dialog](https://minecraft.wiki/w/Dialog_tag_(Java_Edition) "Dialog tag (Java Edition)")<br>- [![](https://minecraft.wiki/images/ItemSprite_clock.png?30324)](https://minecraft.wiki/w/Timeline_tag_(Java_Edition) "Timeline tag (Java Edition)")[Timeline](https://minecraft.wiki/w/Timeline_tag_(Java_Edition) "Timeline tag (Java Edition)")<br>- [![](https://minecraft.wiki/images/ItemSprite_water-bottle.png?fe7c2)](https://minecraft.wiki/w/Potion_tag_(Java_Edition) "Potion tag (Java Edition)")[Potion](https://minecraft.wiki/w/Potion_tag_(Java_Edition) "Potion tag (Java Edition)")<br>- [![](https://minecraft.wiki/images/EntitySprite_villager.png?05433)](https://minecraft.wiki/w/Villager_trade_tag_(Java_Edition) "Villager trade tag (Java Edition)")[Villager trade](https://minecraft.wiki/w/Villager_trade_tag_(Java_Edition) "Villager trade tag (Java Edition)")<br>- [![](https://minecraft.wiki/images/EnvSprite_oak.png?742a4)](https://minecraft.wiki/w/Feature_tag_(Java_Edition) "Feature tag (Java Edition)")[Feature](https://minecraft.wiki/w/Feature_tag_(Java_Edition) "Feature tag (Java Edition)")<br>- [Block sound set](https://minecraft.wiki/w/Block_sound_set_tag_(Java_Edition) "Block sound set tag (Java Edition)") ​\[ _upcoming: [JE 26.4](https://minecraft.wiki/w/Java_Edition_26.4 "Java Edition 26.4")_\] |
| [GameTest](https://minecraft.wiki/w/GameTest "GameTest") | - [![](https://minecraft.wiki/images/BlockSprite_test-block-start.png?35191)](https://minecraft.wiki/w/Test_environment_definition "Test environment definition")[Test environment](https://minecraft.wiki/w/Test_environment_definition "Test environment definition")<br>- [![](https://minecraft.wiki/images/BlockSprite_test-instance-block.png?27a39)](https://minecraft.wiki/w/Test_instance_definition "Test instance definition")[Test instance](https://minecraft.wiki/w/Test_instance_definition "Test instance definition") |
| [World generation](https://minecraft.wiki/w/Custom_world_generation "Custom world generation") | - [Dimension](https://minecraft.wiki/w/Dimension_definition "Dimension definition")
- [![](https://minecraft.wiki/images/EnvSprite_nether-portal.png?47646)](https://minecraft.wiki/w/Dimension_type "Dimension type")[Dimension type](https://minecraft.wiki/w/Dimension_type "Dimension type")
- [![](https://minecraft.wiki/images/EnvSprite_mountain.png?2e0ae)](https://minecraft.wiki/w/World_preset_definition "World preset definition")[World preset](https://minecraft.wiki/w/World_preset_definition "World preset definition")
- [![](https://minecraft.wiki/images/EnvSprite_biomes.png?0a976)](https://minecraft.wiki/w/Biome_definition_(Java_Edition) "Biome definition (Java Edition)")[Biomes](https://minecraft.wiki/w/Biome_definition_(Java_Edition) "Biome definition (Java Edition)")
- [![](https://minecraft.wiki/images/EnvSprite_cave.png?47a17)](https://minecraft.wiki/w/Carver_definition "Carver definition")[Carver](https://minecraft.wiki/w/Carver_definition "Carver definition")
- [![](https://minecraft.wiki/images/thumb/Wrench.png/16px-Wrench.png?fae21)](https://minecraft.wiki/w/Configured_feature "Configured feature")[Configured feature](https://minecraft.wiki/w/Configured_feature "Configured feature")
  - [![](https://minecraft.wiki/images/EnvSprite_oak.png?742a4)](https://minecraft.wiki/w/Tree_definition "Tree definition")[Tree](https://minecraft.wiki/w/Tree_definition "Tree definition")
- [![](https://minecraft.wiki/images/EnvSprite_map.png?b863e)](https://minecraft.wiki/w/Placed_feature "Placed feature")[Placed feature](https://minecraft.wiki/w/Placed_feature "Placed feature")
- [Environment attribute](https://minecraft.wiki/w/Environment_attribute "Environment attribute")

| [Noise settings](https://minecraft.wiki/w/Noise_settings "Noise settings") | - [![](https://minecraft.wiki/images/EnvSprite_mountain.png?2e0ae)](https://minecraft.wiki/w/Noise_router "Noise router")[Noise router](https://minecraft.wiki/w/Noise_router "Noise router")<br>- [![](https://minecraft.wiki/images/EnvSprite_number.png?9ceb9)](https://minecraft.wiki/w/Density_function "Density function")[Density function](https://minecraft.wiki/w/Density_function "Density function")<br>- [Noises](https://minecraft.wiki/w/Noise "Noise")<br>- [![](https://minecraft.wiki/images/EnvSprite_surface.png?75bf7)](https://minecraft.wiki/w/Material_rule "Material rule")[Material rule](https://minecraft.wiki/w/Material_rule "Material rule") |
| [Structures](https://minecraft.wiki/w/Structure_definition "Structure definition") | - [![](https://minecraft.wiki/images/EnvSprite_abandoned-mineshaft.png?fab65)](https://minecraft.wiki/w/Structure_set "Structure set")[Structure set](https://minecraft.wiki/w/Structure_set "Structure set")<br>- [![](https://minecraft.wiki/images/BlockSprite_jigsaw.png?ec5e3)](https://minecraft.wiki/w/Template_pool "Template pool")[Template pool](https://minecraft.wiki/w/Template_pool "Template pool")<br>- [![](https://minecraft.wiki/images/BlockSprite_cracked-stone-bricks.png?f3f1d)](https://minecraft.wiki/w/Processor_list "Processor list")[Processor list](https://minecraft.wiki/w/Processor_list "Processor list")<br>- [![](https://minecraft.wiki/images/EnvSprite_nether-fossil.png?93621)](https://minecraft.wiki/w/Structure_file "Structure file")[Structure templates](https://minecraft.wiki/w/Structure_file "Structure file") |
| Removed | - [![](https://minecraft.wiki/images/ItemSprite_iron-pickaxe.png?77536)](https://minecraft.wiki/w/Configured_surface_builder "Configured surface builder")[Configured surface builder](https://minecraft.wiki/w/Configured_surface_builder "Configured surface builder") | | |
| Data packs | - [![](https://minecraft.wiki/images/BlockSprite_deepslate.png?d7361)](https://minecraft.wiki/w/Caves_%26_Cliffs_Prototype_Data_Pack "Caves & Cliffs Prototype Data Pack")[Caves & Cliffs Prototype Data Pack](https://minecraft.wiki/w/Caves_%26_Cliffs_Prototype_Data_Pack "Caves & Cliffs Prototype Data Pack")<br>- [![](https://minecraft.wiki/images/ItemSprite_magical-painting.png?b0bf0)](https://minecraft.wiki/w/Phantom_Frames "Phantom Frames")[Phantom Frames](https://minecraft.wiki/w/Phantom_Frames "Phantom Frames") |
| Tutorials | - [![](https://minecraft.wiki/images/thumb/EnvSprite_autosave.png/16px-EnvSprite_autosave.png?a55e7)](https://minecraft.wiki/w/Tutorial:Importing_a_data_pack "Tutorial:Importing a data pack")[Importing](https://minecraft.wiki/w/Tutorial:Importing_a_data_pack "Tutorial:Importing a data pack")
- [![](https://minecraft.wiki/images/thumb/Wrench.png/16px-Wrench.png?fae21)](https://minecraft.wiki/w/Tutorial:Creating_a_data_pack "Tutorial:Creating a data pack")[Creating](https://minecraft.wiki/w/Tutorial:Creating_a_data_pack "Tutorial:Creating a data pack")
- [Optimizing](https://minecraft.wiki/w/Tutorial:Optimizing_a_data_pack "Tutorial:Optimizing a data pack")
- [![](https://minecraft.wiki/images/BlockSprite_command-block.png?e7078)](https://minecraft.wiki/w/Tutorial:Command_blocks_and_functions "Tutorial:Command blocks and functions")[Command blocks and functions](https://minecraft.wiki/w/Tutorial:Command_blocks_and_functions "Tutorial:Command blocks and functions")
- [Repairing a world corrupted by a data pack](https://minecraft.wiki/w/Tutorial:Repairing_a_world_corrupted_by_a_data_pack "Tutorial:Repairing a world corrupted by a data pack")

| Content | - [![](https://minecraft.wiki/images/ItemSprite_enchanted-book.png?b7877)](https://minecraft.wiki/w/Tutorial:Adding_custom_enchantments "Tutorial:Adding custom enchantments")[Custom enchantments](https://minecraft.wiki/w/Tutorial:Adding_custom_enchantments "Tutorial:Adding custom enchantments")<br>- [![](https://minecraft.wiki/images/ItemSprite_painting.png?55d20)](https://minecraft.wiki/w/Tutorial:Adding_custom_paintings "Tutorial:Adding custom paintings")[Custom paintings](https://minecraft.wiki/w/Tutorial:Adding_custom_paintings "Tutorial:Adding custom paintings")<br>- [![](https://minecraft.wiki/images/ItemSprite_armor-trim.png?1d672)](https://minecraft.wiki/w/Tutorial:Adding_custom_trims "Tutorial:Adding custom trims")[Custom trims](https://minecraft.wiki/w/Tutorial:Adding_custom_trims "Tutorial:Adding custom trims") |
| World generation | - [![](https://minecraft.wiki/images/EnvSprite_other-portal.png?ca57b)](https://minecraft.wiki/w/Tutorial:Adding_a_new_dimension "Tutorial:Adding a new dimension")[New dimension](https://minecraft.wiki/w/Tutorial:Adding_a_new_dimension "Tutorial:Adding a new dimension")<br>- [![](https://minecraft.wiki/images/EnvSprite_lunar-base.png?648e4)](https://minecraft.wiki/w/Tutorial:Custom_structures "Tutorial:Custom structures")[Custom structures](https://minecraft.wiki/w/Tutorial:Custom_structures "Tutorial:Custom structures") | | |
| | \[show\][Resource pack](https://minecraft.wiki/w/Resource_pack "Resource pack") |
| --- |
| Components | - [pack.mcmeta](https://minecraft.wiki/w/Pack.mcmeta "Pack.mcmeta")<br>- [![](https://minecraft.wiki/images/EnvSprite_number.png?9ceb9)](https://minecraft.wiki/w/Pack_format "Pack format")[Pack format](https://minecraft.wiki/w/Pack_format "Pack format")<br>- [![](https://minecraft.wiki/images/EnvSprite_language.png?39da2)](https://minecraft.wiki/w/Resource_pack#Language "Resource pack")[Language](https://minecraft.wiki/w/Resource_pack#Language "Resource pack")<br>- [![](https://minecraft.wiki/images/EntitySprite_creeper.png?703e9)](https://minecraft.wiki/w/Model "Model")[Models](https://minecraft.wiki/w/Model "Model")<br>- [![](https://minecraft.wiki/images/BlockSprite_double-stone-slab.png?62750)](https://minecraft.wiki/w/Blockstates_definition "Blockstates definition")[Blockstates](https://minecraft.wiki/w/Blockstates_definition "Blockstates definition")<br>- [![](https://minecraft.wiki/images/EnvSprite_item.png?89d23)](https://minecraft.wiki/w/Items_model_definition "Items model definition")[Items](https://minecraft.wiki/w/Items_model_definition "Items model definition")<br>- [![](https://minecraft.wiki/images/EnvSprite_ambience.png?d7c92)](https://minecraft.wiki/w/Sound "Sound")[Sounds](https://minecraft.wiki/w/Sound "Sound") ( [sounds.json](https://minecraft.wiki/w/Sounds.json "Sounds.json"))<br>- [Shaders](https://minecraft.wiki/w/Shader "Shader")<br>- [![](https://minecraft.wiki/images/EnvSprite_texture-pack.png?a4213)](https://minecraft.wiki/w/Resource_pack#Textures "Resource pack")[Textures](https://minecraft.wiki/w/Resource_pack#Textures "Resource pack")<br>- [![](https://minecraft.wiki/images/ItemSprite_compass.png?2364d)](https://minecraft.wiki/w/Atlas "Atlas")[Atlases](https://minecraft.wiki/w/Atlas "Atlas")<br>- [Aa](https://minecraft.wiki/w/Font "Font") [Fonts](https://minecraft.wiki/w/Font "Font")<br>- [![](https://minecraft.wiki/images/BlockSprite_oak-leaves.png?81553)](https://minecraft.wiki/w/Resource_pack#Colormaps "Resource pack")[Colormaps](https://minecraft.wiki/w/Resource_pack#Colormaps "Resource pack")<br>- [Texts](https://minecraft.wiki/w/Resource_pack#Texts "Resource pack")<br>- [![](https://minecraft.wiki/images/Locator_Bar_icon_bowtie.png?a8cd8)](https://minecraft.wiki/w/Waypoint_style "Waypoint style")[Waypoint styles](https://minecraft.wiki/w/Waypoint_style "Waypoint style")<br>- [regional\_compliancies.json](https://minecraft.wiki/w/Resource_pack#Regional_compliancies_warnings "Resource pack")<br>- [![](https://minecraft.wiki/images/ItemSprite_all-iron-armor.png?87e31)](https://minecraft.wiki/w/Equipment "Equipment")[Equipment](https://minecraft.wiki/w/Equipment "Equipment") |
| Debug | - [Missing font character](https://minecraft.wiki/w/Missing_font_character "Missing font character")<br>- [![](https://minecraft.wiki/images/BlockSprite_missingno.png?031f4)](https://minecraft.wiki/w/Missing_model "Missing model")[Missing model](https://minecraft.wiki/w/Missing_model "Missing model")<br>- [![](https://minecraft.wiki/images/BlockSprite_missingno.png?031f4)](https://minecraft.wiki/w/Missing_texture "Missing texture")[Missing texture](https://minecraft.wiki/w/Missing_texture "Missing texture") |
| Tools | - [Slicer](https://minecraft.wiki/w/Slicer "Slicer")

| Legacy | - [Texture Ender](https://minecraft.wiki/w/Texture_Ender "Texture Ender")<br>- [Unstitcher](https://minecraft.wiki/w/Unstitcher "Unstitcher") | |
| Tutorials | - [![](https://minecraft.wiki/images/thumb/Wrench.png/16px-Wrench.png?fae21)](https://minecraft.wiki/w/Tutorial:Creating_a_resource_pack "Tutorial:Creating a resource pack")[Creating](https://minecraft.wiki/w/Tutorial:Creating_a_resource_pack "Tutorial:Creating a resource pack")<br>- [![](https://minecraft.wiki/images/Download.png?048e3)](https://minecraft.wiki/w/Tutorial:Loading_a_resource_pack "Tutorial:Loading a resource pack")[Loading](https://minecraft.wiki/w/Tutorial:Loading_a_resource_pack "Tutorial:Loading a resource pack")<br>- [![](https://minecraft.wiki/images/EnvSprite_fluids.png?58a6a)](https://minecraft.wiki/w/Tutorial:Models "Tutorial:Models")[Models](https://minecraft.wiki/w/Tutorial:Models "Tutorial:Models")<br>- [![](https://minecraft.wiki/images/EnvSprite_ambience.png?d7c92)](https://minecraft.wiki/w/Tutorial:Sound_directory "Tutorial:Sound directory")[Sound directory](https://minecraft.wiki/w/Tutorial:Sound_directory "Tutorial:Sound directory") | |

Retrieved from " [https://minecraft.wiki/w/Java\_Edition\_level\_format?oldid=3795569](https://minecraft.wiki/w/Java_Edition_level_format?oldid=3795569)"

[Categories](https://minecraft.wiki/w/Special:Categories "Special:Categories"):

- [Java Edition](https://minecraft.wiki/w/Category:Java_Edition "Category:Java Edition")
- [Java Edition technical](https://minecraft.wiki/w/Category:Java_Edition_technical "Category:Java Edition technical")
- [Development](https://minecraft.wiki/w/Category:Development "Category:Development")

Hidden category:

- [Information needed](https://minecraft.wiki/w/Category:Information_needed "Category:Information needed")

## Navigation menu

Search

[Visit the main page](https://minecraft.wiki/ "Visit the main page")

[X](https://minecraft.wiki/w/Minecraft_Wiki:Indie_Wiki_Buddy)

**To leave feedback for the game, [click here](https://feedback.minecraft.net/).**

Feedback will be posted anonymously and shared to our [Discord](https://discord.gg/fGdE5ZE).

Something went wrong

Dismiss