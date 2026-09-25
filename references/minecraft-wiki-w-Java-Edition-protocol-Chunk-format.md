[![This article is licensed under a Creative Commons Attribution-ShareAlike 3.0 license. Derivative works must be licensed using the same or a compatible license.](https://minecraft.wiki/images/Cc-by-sa.svg?fc1a9)](https://creativecommons.org/licenses/by-sa/3.0/ "This article is licensed under a Creative Commons Attribution-ShareAlike 3.0 license. Derivative works must be licensed using the same or a compatible license.")

# Java Edition protocol/Chunk format  Share article feedback

From Minecraft Wiki

< [Java Edition protocol](https://minecraft.wiki/w/Java_Edition_protocol "Java Edition protocol")

[Jump to navigation](https://minecraft.wiki/w/Java_Edition_protocol/Chunk_format#mw-head) [Jump to search](https://minecraft.wiki/w/Java_Edition_protocol/Chunk_format#searchInput)

This article describes in additional detail the format of the [Chunk Data](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Chunk_Data_and_Update_Light "Java Edition protocol/Packets") packet.

## Contents

- [1Concepts](https://minecraft.wiki/w/Java_Edition_protocol/Chunk_format#Concepts)
  - [1.1Chunks columns and Chunk sections](https://minecraft.wiki/w/Java_Edition_protocol/Chunk_format#Chunks_columns_and_Chunk_sections)
  - [1.2Global palettes](https://minecraft.wiki/w/Java_Edition_protocol/Chunk_format#Global_palettes)
    - [1.2.1Global block state palette](https://minecraft.wiki/w/Java_Edition_protocol/Chunk_format#Global_block_state_palette)
    - [1.2.2Biome registry](https://minecraft.wiki/w/Java_Edition_protocol/Chunk_format#Biome_registry)
  - [1.3Local palettes](https://minecraft.wiki/w/Java_Edition_protocol/Chunk_format#Local_palettes)
  - [1.4Notes](https://minecraft.wiki/w/Java_Edition_protocol/Chunk_format#Notes)
- [2Packet structure](https://minecraft.wiki/w/Java_Edition_protocol/Chunk_format#Packet_structure)
  - [2.1Heightmap structure](https://minecraft.wiki/w/Java_Edition_protocol/Chunk_format#Heightmap_structure)
  - [2.2Data structure](https://minecraft.wiki/w/Java_Edition_protocol/Chunk_format#Data_structure)
    - [2.2.1Chunk Section structure](https://minecraft.wiki/w/Java_Edition_protocol/Chunk_format#Chunk_Section_structure)
- [3Paletted Container structure](https://minecraft.wiki/w/Java_Edition_protocol/Chunk_format#Paletted_Container_structure)
  - [3.1Palette formats](https://minecraft.wiki/w/Java_Edition_protocol/Chunk_format#Palette_formats)
    - [3.1.1Single valued](https://minecraft.wiki/w/Java_Edition_protocol/Chunk_format#Single_valued)
    - [3.1.2Indirect](https://minecraft.wiki/w/Java_Edition_protocol/Chunk_format#Indirect)
    - [3.1.3Direct](https://minecraft.wiki/w/Java_Edition_protocol/Chunk_format#Direct)
    - [3.1.4Example](https://minecraft.wiki/w/Java_Edition_protocol/Chunk_format#Example)
  - [3.2Data Array format](https://minecraft.wiki/w/Java_Edition_protocol/Chunk_format#Data_Array_format)
    - [3.2.1Visual example](https://minecraft.wiki/w/Java_Edition_protocol/Chunk_format#Visual_example)
    - [3.2.2Hints for implementers](https://minecraft.wiki/w/Java_Edition_protocol/Chunk_format#Hints_for_implementers)
- [4Tips and notes](https://minecraft.wiki/w/Java_Edition_protocol/Chunk_format#Tips_and_notes)
- [5Full implementations](https://minecraft.wiki/w/Java_Edition_protocol/Chunk_format#Full_implementations)
- [6Sample data](https://minecraft.wiki/w/Java_Edition_protocol/Chunk_format#Sample_data)
  - [6.1Old format](https://minecraft.wiki/w/Java_Edition_protocol/Chunk_format#Old_format)

## Concepts

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Chunk_format?section=1&veaction=edit "Edit section: Concepts") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Chunk_format?action=edit&section=1 "Edit section's source code: Concepts")\]

### Chunks columns and Chunk sections

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Chunk_format?section=2&veaction=edit "Edit section: Chunks columns and Chunk sections") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Chunk_format?action=edit&section=2 "Edit section's source code: Chunks columns and Chunk sections")\]

You've probably heard the term "chunk" before. Minecraft uses chunks to store and transfer world data. However, there are actually 2 different concepts that are both called "chunks" in different contexts: chunk columns and chunk sections.

A **chunk column** is a collection of blocks with a horizontal size of 16×16, spanning the entire buildable area on the vertical axis. This is what most players think of when they hear the term "chunk". However, these are not the smallest unit data is stored in the game; chunk columns are vertically divided into chunk sections, each 16 blocks tall.

Chunk columns store block entities, entities, tick data, and an array of sections.

A **chunk section** is a 16×16×16 collection of blocks (chunk sections are cubic). This is the actual area that blocks are stored in, and is often the concept Mojang refers to via "chunk". Breaking columns into sections wouldn't be useful, except that you don't need to send all chunk sections in a column: If a section is empty, then it doesn't need to be sent (more on this later).

Chunk sections store blocks, biomes and light data (both block light and sky light). Additionally, they can be associated with at most two [local palettes](https://minecraft.wiki/w/Java_Edition_protocol/Chunk_format#Local_palettes)—one for blocks, one for biomes. A chunk section can contain at maximum 4096 (16×16×16, or 212) unique block state IDs, and 64 (4×4×4) unique biome IDs (but, it is highly unlikely that such a section will occur in normal circumstances).

Chunk columns and chunk sections are both displayed when chunk border rendering is enabled ( `F3` + `G`). Chunk columns borders are indicated via the red vertical lines, while chunk sections borders are indicated by the blue lines.

### Global palettes

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Chunk_format?section=3&veaction=edit "Edit section: Global palettes") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Chunk_format?action=edit&section=3 "Edit section's source code: Global palettes")\]

The global palettes map block states and biomes to protocol-wide numeric identifiers.

#### Global block state palette

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Chunk_format?section=4&veaction=edit "Edit section: Global block state palette") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Chunk_format?action=edit&section=4 "Edit section's source code: Global block state palette")\]

The global block state palette is generated based on the `minecraft:block` [registry](https://minecraft.wiki/w/Java_Edition_protocol/Registries "Java Edition protocol/Registries"), which in turn is hardcoded into Minecraft, and can only be changed via modding. Such changes break protocol compatibility, and as such, modding frameworks typically include protocol extensions to negotiate which IDs the client and server have in common.

One block state ID is allocated for each unique block state of a block; if a block has multiple properties then the number of allocated states is the product of the number of values for each property. The block state IDs belonging to a given block are always consecutive. Other than that, the ordering of block states is hardcoded, and somewhat arbitrary.

The [Data Generators](https://minecraft.wiki/w/Minecraft_Wiki:Projects/wiki.vg_merge/Data_Generators "Minecraft Wiki:Projects/wiki.vg merge/Data Generators") system can be used to generate a list of all block state IDs.

#### Biome registry

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Chunk_format?section=5&veaction=edit "Edit section: Biome registry") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Chunk_format?action=edit&section=5 "Edit section's source code: Biome registry")\]

The global palette for biomes is the `minecraft:worldgen/biome` [synchronized registry](https://minecraft.wiki/w/Java_Edition_protocol/Registries#Synchronized_registries "Java Edition protocol/Registries"), which is defined at runtime in a [Registry Data](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Registry_Data_2 "Java Edition protocol/Packets") packet sent by the server during the Configuration phase.

The vanilla server pulls these biome definitions [from data packs](https://minecraft.wiki/w/Biome_definition "Biome definition").

### Local palettes

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Chunk_format?section=6&veaction=edit "Edit section: Local palettes") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Chunk_format?action=edit&section=6 "Edit section's source code: Local palettes")\]

[![](https://minecraft.wiki/images/Indexed_palette.png?cf445)](https://minecraft.wiki/w/File:Indexed_palette.png) Illustration of an indexed palette ( [Source](https://commons.wikimedia.org/wiki/File:Indexed_palette.png "commons:File:Indexed palette.png"))

A local palette maps a smaller set of IDs within a [chunk section](https://minecraft.wiki/w/Java_Edition_protocol/Chunk_format#Chunk_section) to global palette IDs. Other than skipping empty sections, correct use of palettes is the biggest place where data can be saved. For example, encoding any of the IDs in the global block state palette as of vanilla 1.20.2 requires 15 bits. Given that most sections contain only a few different blocks, using 15 bits per block to represent a chunk section that is only stone, gravel, and air would be extremely wasteful. Instead, a list of global palette IDs is sent to define the local palette (for instance, `40 57 0`), and indices into that list are sent as the block state or biome values within the chunk (so `40` would be sent as `0`, `57` as `1`, and `0` as `2`).[\[concept note 1\]](https://minecraft.wiki/w/Java_Edition_protocol/Chunk_format#cite_note-1)

The number of bits used to encode local palette indices varies based on the number of indices, and the global palette in question. If a threshold on the number of unique IDs in the section is exceeded, a local palette is not used, and global palette IDs are used directly instead.

The concept of palettes is more commonly used with colors in an image; Wikipedia's articles on [color look-up tables](https://en.wikipedia.org/wiki/Color_look-up_table "wikipedia:Color look-up table"), [indexed colors](https://en.wikipedia.org/wiki/Indexed_color "wikipedia:Indexed color"), and [palettes in general](https://en.wikipedia.org/wiki/Palette_(computing) "wikipedia:Palette (computing)") may be helpful for fully grokking it.

[![](https://minecraft.wiki/images/thumb/Ambox_warning_pn.png/32px-Ambox_warning_pn.png?b6e1c)](https://minecraft.wiki/w/File:Ambox_warning_pn.png "File:Ambox warning pn.png")

Note that the notchian client (and server) store their chunk data within the compacted, paletted format. Sending non-compacted data not only wastes bandwidth, but also leads to increased memory use clientside; while this is OK for an initial implementation it is strongly encouraged that one compacts the block data as soon as possible.

### Notes

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Chunk_format?section=7&veaction=edit "Edit section: Notes") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Chunk_format?action=edit&section=7 "Edit section's source code: Notes")\]

1. [↑](https://minecraft.wiki/w/Java_Edition_protocol/Chunk_format#cite_ref-1 "Jump up")There is no requirement for the global palette IDs listed in a local palette to be [monotonic](https://en.wikipedia.org/wiki/Monotonic "wikipedia:Monotonic"); the order within the list is entirely arbitrary and often has to do with how the palette is built (if it finds a stone block before an air block, stone can come first). (However, although the order of the palette entries can be arbitrary, it can theoretically be optimized to ensure the maximum possible DEFLATE compression. This optimization offers little to no gain, so generally do not attempt it.) However, there shouldn't be any gaps in the palette, as gaps would increase the size of the palette when it is sent.

## Packet structure

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Chunk_format?section=8&veaction=edit "Edit section: Packet structure") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Chunk_format?action=edit&section=8 "Edit section's source code: Packet structure")\]

| Packet ID | State | Bound To | Field Name | Field Type | Notes |
| --- | --- | --- | --- | --- | --- |
| 0x2C | Play | Client | Chunk X | [Int](https://minecraft.wiki/w/Java_Edition_protocol/Data_types#Type:Int "Java Edition protocol/Data types") | Chunk coordinate (block coordinate divided by 16, rounded down). |
| Chunk Z | [Int](https://minecraft.wiki/w/Java_Edition_protocol/Data_types#Type:Int "Java Edition protocol/Data types") | Chunk coordinate (block coordinate divided by 16, rounded down). |
| Heightmaps | [Prefixed Array](https://minecraft.wiki/w/Java_Edition_protocol/Data_types#Type:Prefixed_Array "Java Edition protocol/Data types") of [Heightmap](https://minecraft.wiki/w/Java_Edition_protocol/Chunk_format#Heightmap_structure) | See [#Heightmap structure](https://minecraft.wiki/w/Java_Edition_protocol/Chunk_format#Heightmap_structure) below. |
| Size | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Data_types#Type:VarInt "Java Edition protocol/Data types") | Size of Data in bytes; in some cases this is larger than it needs to be (e.g. [MC-131684](https://bugs.mojang.com/browse/MC-131684), [MC-247438](https://bugs.mojang.com/browse/MC-247438)) in which case extra bytes should be skipped before reading fields after Data. |
| Data | [Byte Array](https://minecraft.wiki/w/Java_Edition_protocol/Data_types#Type:Byte_Array "Java Edition protocol/Data types") | See [#Data structure](https://minecraft.wiki/w/Java_Edition_protocol/Chunk_format#Data_structure) below. |
| Additional Data | Various | See [Protocol#Chunk Data and Update Light](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Chunk_Data_and_Update_Light "Java Edition protocol/Packets"). |

### Heightmap structure

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Chunk_format?section=9&veaction=edit "Edit section: Heightmap structure") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Chunk_format?action=edit&section=9 "Edit section's source code: Heightmap structure")\]

Minecraft uses heightmaps to optimize various operations on both the server and the client. All heightmaps encode the position of the highest "occupied" block in each column of blocks within a chunk column. The differences have to do with which blocks are considered to be "occupied".

Rather than calculating them from the chunk data, the client receives the initial heightmaps it needs from the server. This trades an increase in network usage for a decrease in client-side processing. Once a chunk is loaded, the client updates its heightmaps based on block changes independently from the server.

No heightmaps are strictly required for the client to accept a chunk. If a heightmap is missing from a Chunk Data packet, the client will initialize it with all heights set to their minimum values. However, block changes will still cause the corresponding height values to be updated as normal.

As of 1.21.5, the Heightmap structure is as follows.

| Field Name | Field Type | Notes |
| --- | --- | --- |
| Type | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Data_types#Type:VarInt "Java Edition protocol/Data types") [Enum](https://minecraft.wiki/w/Java_Edition_protocol/Data_types#Type:Enum "Java Edition protocol/Data types") | See the table below. |
| Data | [Prefixed Array](https://minecraft.wiki/w/Java_Edition_protocol/Data_types#Type:Prefixed_Array "Java Edition protocol/Data types") of [Long](https://minecraft.wiki/w/Java_Edition_protocol/Data_types#Type:Long "Java Edition protocol/Data types") | Packed data array. Described below. |

Heightmap Structure

The height values of a heightmap are packed into the long array in the same manner described in [#Data Array format](https://minecraft.wiki/w/Java_Edition_protocol/Chunk_format#Data_Array_format), and ordered such that the fastest-increasing coordinate is x. (However, there are only 256 entries—one for each block column.) The Bits Per Entry value used is calculated as ceil(log2(world\_height \+ 1)). This is because the number of possible height values is one more than the world height—ranging from 0 (completely blank column; not even bedrock) to world height (highest position is occupied). Note that this means, for example, that a world with height 256 will use a Bits Per Entry of 9. Since the minimum world height might be negative, it must be added as an offset to get the actual highest occupied Y coordinate.

The following heightmaps are currently used by the client:

| Name | ID | Considers Occupied | Purposes |
| --- | --- | --- | --- |
| WORLD\_SURFACE | 1 | All blocks other than air, cave air and void air. | To determine if a beacon beam is obstructed. |
| MOTION\_BLOCKING | 4 | "Solid" blocks, except bamboo saplings and cactuses; fluids. | To determine where to display rain and snow. |
| MOTION\_BLOCKING\_NO\_LEAVES | 5 | Same as MOTION\_BLOCKING, excluding leaf blocks. |  |

This list is exhaustive as of 1.21.8. The listed purposes appear to be exhaustive as of 1.20.2.

### Data structure

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Chunk_format?section=10&veaction=edit "Edit section: Data structure") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Chunk_format?action=edit&section=10 "Edit section's source code: Data structure")\]

The data section of the packet contains most of the useful data for the chunk.

| Field Name | Field Type | Notes |
| --- | --- | --- |
| Data | [Array](https://minecraft.wiki/w/Java_Edition_protocol/Data_types#Type:Array "Java Edition protocol/Data types") of [Chunk Section](https://minecraft.wiki/w/Java_Edition_protocol/Chunk_format#Chunk_Section_structure) | This array is NOT length-prefixed. The number of elements in the array is calculated based on the world's height. Sections are sent bottom-to-top. Starting with 1.18, the world height changes based on the dimension. The height of each dimension is assigned by the server in its corresponding entry in the `minecraft:dimension_type` [synchronized registry](https://minecraft.wiki/w/Java_Edition_protocol/Registries#Synchronized_registries "Java Edition protocol/Registries"). For example, the vanilla overworld is 384 blocks tall, meaning 24 chunk sections will be included in this array. |

#### Chunk Section structure

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Chunk_format?section=11&veaction=edit "Edit section: Chunk Section structure") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Chunk_format?action=edit&section=11 "Edit section's source code: Chunk Section structure")\]

[![](https://minecraft.wiki/images/thumb/Clock_JE3_BE3.gif/16px-Clock_JE3_BE3.gif?a4011)](https://minecraft.wiki/w/File:Clock_JE3.gif "File:Clock JE3.gif")

This section needs to be updated.

Please update this section to reflect recent updates or newly available information. The [talk page](https://minecraft.wiki/w/Special:TalkPage/Java_Edition_protocol/Chunk_format "Special:TalkPage/Java Edition protocol/Chunk format") may contain suggestions.

**Reason:** How do biomes work now? The biome change happened at the same time as the seed change, but it's not clear how/if biomes could be computed given that it's not the actual seed... ( [/r/mojira discussion](https://www.reddit.com/r/Mojira/comments/e5at6i/a_discussion_for_the_changes_to_how_biomes_are/) which notes that it seems to be some kind of interpolation)

A Chunk Section is defined in terms of other [data types](https://minecraft.wiki/w/Java_Edition_protocol/Data_types "Java Edition protocol/Data types"). A Chunk Section consists of the following fields:

| Field Name | Field Type | Notes |
| --- | --- | --- |
| Block count | [Short](https://minecraft.wiki/w/Java_Edition_protocol/Data_types#Type:Short "Java Edition protocol/Data types") | Number of non-air blocks present in the chunk section. "Non-air" is defined as any fluid and block other than air, cave air, and void air. The client will keep count of the blocks as they are broken and placed, and, if the block count reaches 0, the whole chunk section is not rendered, even if it still has blocks. |
| Fluid count | [Short](https://minecraft.wiki/w/Java_Edition_protocol/Data_types#Type:Short "Java Edition protocol/Data types") | Number of fluids (waterlogged blocks, and `minecraft:water` or `minecraft:lava` with any block state) in this chunk section. |
| Block states | [Paletted Container](https://minecraft.wiki/w/Java_Edition_protocol/Chunk_format#Paletted_Container_structure) | Consists of 4096 entries, representing all the blocks in the chunk section. |
| Biomes | [Paletted Container](https://minecraft.wiki/w/Java_Edition_protocol/Chunk_format#Paletted_Container_structure) | Consists of 64 entries, representing 4×4×4 biome regions in the chunk section. |

## Paletted Container structure

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Chunk_format?section=12&veaction=edit "Edit section: Paletted Container structure") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Chunk_format?action=edit&section=12 "Edit section's source code: Paletted Container structure")\]

A Paletted Container is a palette-based storage of entries. Paletted Containers have an associated global palette (either block states or biomes as of now), where values are mapped from. A Paletted Container consists of the following fields:

| Field Name | Field Type | Notes |
| --- | --- | --- |
| Bits Per Entry | [Unsigned Byte](https://minecraft.wiki/w/Java_Edition_protocol/Data_types#Type:Unsigned_Byte "Java Edition protocol/Data types") | Determines how many bits are used to encode entries. Note that not all numbers are valid here. |
| Palette | Varies | See [#Palette formats](https://minecraft.wiki/w/Java_Edition_protocol/Chunk_format#Palette_formats) below. |
| Data Array | [Array](https://minecraft.wiki/w/Java_Edition_protocol/Data_types#Type:Array "Java Edition protocol/Data types") of [Long](https://minecraft.wiki/w/Java_Edition_protocol/Data_types#Type:Long "Java Edition protocol/Data types") | See [#Data Array format](https://minecraft.wiki/w/Java_Edition_protocol/Chunk_format#Data_Array_format) below. |

### Palette formats

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Chunk_format?section=13&veaction=edit "Edit section: Palette formats") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Chunk_format?action=edit&section=13 "Edit section's source code: Palette formats")\]

The Bits Per Entry value determines what format is used for the Palette field, which in turn determines how values in the Data Array map to the global palette.

[![](https://minecraft.wiki/images/thumb/Ambox_warning_pn.png/32px-Ambox_warning_pn.png?b6e1c)](https://minecraft.wiki/w/File:Ambox_warning_pn.png "File:Ambox warning pn.png")

Values not listed in the following table are rounded upwards to the next one specified, or downwards if larger than the value for Direct. Therefore such values will lead to unexpected results, and should not be used.

There are currently three possible palette formats:

| BPE (blocks) | BPE (biomes) | Palette Format |
| --- | --- | --- |
| 0 | 0 | [Single valued](https://minecraft.wiki/w/Java_Edition_protocol/Chunk_format#Single_valued) |
| 4-8 | 1-3 | [Indirect](https://minecraft.wiki/w/Java_Edition_protocol/Chunk_format#Indirect) |
| 15\*\* | 7\* | [Direct](https://minecraft.wiki/w/Java_Edition_protocol/Chunk_format#Direct) |

\*The Notchian client calculates the Bits Per Entry values for the Direct palette format at runtime based on the sizes of the global block state and biome palettes. As such, the value used for biomes is entirely dependent on the contents of the biome registry sent in the [Registry Data](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Registry_Data_2 "Java Edition protocol/Packets") packet; the value shown is only valid for vanilla servers with no custom data packs. If the BPE requirement for Direct is less than or equal to the maximum for Indirect, Direct will never be used given BPE values within the valid range.

\*\*Similarly, if a sufficiently large number of blocks is added with mods, the value will be increased to compensate for the increased ID count. This increase can go up to 31 bits per entry (since registry IDs are signed integers). In case of Minecraft Forge, you can get the number of blocks with the "Number of ids" field found in the [RegistryData packet in the Forge Handshake](https://minecraft.wiki/w/Minecraft_Wiki:Projects/wiki.vg_merge/Minecraft_Forge_Handshake#RegistryData "Minecraft Wiki:Projects/wiki.vg merge/Minecraft Forge Handshake").

#### Single valued

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Chunk_format?section=14&veaction=edit "Edit section: Single valued") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Chunk_format?action=edit&section=14 "Edit section's source code: Single valued")\]

When this palette format is used, the Data Array sent/received is empty, since entries can be inferred from the palette's single value.

| Field Name | Field Type | Notes |
| --- | --- | --- |
| Value | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Data_types#Type:VarInt "Java Edition protocol/Data types") | ID of the entry in the global palette. |

#### Indirect

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Chunk_format?section=15&veaction=edit "Edit section: Indirect") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Chunk_format?action=edit&section=15 "Edit section's source code: Indirect")\]

This is an actual palette which lists the entries used. Values in the Data Array are indices into the local palette, which in turn gives a proper global palette ID.

| Field Name | Field Type | Notes |
| --- | --- | --- |
| Palette | [Prefixed Array](https://minecraft.wiki/w/Java_Edition_protocol/Data_types#Type:Prefixed_Array "Java Edition protocol/Data types") of [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Data_types#Type:VarInt "Java Edition protocol/Data types") | Mapping of IDs in the global palette to indices of this array. |

#### Direct

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Chunk_format?section=16&veaction=edit "Edit section: Direct") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Chunk_format?action=edit&section=16 "Edit section's source code: Direct")\]

Global palette IDs are stored directly as entries in the Data Array.

| Field Name | Field Type | Notes |
| --- | --- | --- |
| _no fields_ |

#### Example

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Chunk_format?section=17&veaction=edit "Edit section: Example") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Chunk_format?action=edit&section=17 "Edit section's source code: Example")\]

Here is an example showing a Chunk Section using a single-valued palette for block states, and an indirect palette with 2 indices for biomes:

`00 0000 000000010227 03CC FF CC FF CC FF CC FF`

The first bytes 00 00 are the number of non-air blocks in the chunk.
Right after, 00 00 are the number of fluid in the chunk.
They are followed by the Bits Per Entry 00, which is zero so we know the palette will have one element (not prefixed with length). This single element is the block state ID of air, 00.

The second part of the packet is for biomes. The first byte is their Bits Per Entry 01, followed by the length of the palette 02 and the two elements 27 03. The indexed data of this biome has 1 long element, which are 8 bytes each, giving the long CC FF CC FF CC FF CC FF.

### Data Array format

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Chunk_format?section=18&veaction=edit "Edit section: Data Array format") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Chunk_format?action=edit&section=18 "Edit section's source code: Data Array format")\]

As of 1.21.5, the length of the data array is no longer sent with the packet, but is instead calculated from the bits per entry and the number of entries.

The Data Array stores entries as Bits Per Entry–bit integers, corresponding to either local or global palette indices depending on the palette format in use. If Bits Per Entry is 0, it is empty.

Entries are stored in order of increasing x coordinate, within rows at increasing z coordinates, within layers at increasing y coordinates. In other words, the x coordinate increases the fastest, and the y coordinate the slowest.

A single long of the array holds several entries. The entries are tightly packed within the long, with the first entry on the least significant bits. An entry cannot span across multiple longs; instead, padding is inserted as required, starting from the most significant bits.

For example, assuming a bits per block value of 15, and that bit 0 is the least significant bit, the data is stored such that bits 0 through 14 are the first entry, 15 through 29 are the second, and so on. The fourth entry ends on bit 59, and since only 4 bits are left, they become padding, and the fifth entry starts on the next long.

Note that since longs are sent in big endian order, the least significant bit of the first entry in a long will be on the _last_ byte of the long on the wire.

[![](https://minecraft.wiki/images/thumb/Ambox_warning_pn.png/32px-Ambox_warning_pn.png?b6e1c)](https://minecraft.wiki/w/File:Ambox_warning_pn.png "File:Ambox warning pn.png")

This format was changed in Minecraft 1.16. In prior versions, entries could cross long boundaries, and there was no padding.

#### Visual example

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Chunk_format?section=19&veaction=edit "Edit section: Visual example") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Chunk_format?action=edit&section=19 "Edit section's source code: Visual example")\]

5 bits per block, containing the following references to entries in a palette (not shown):
`122344566480743131516914101202`

`0020863148418841``0000000000100000100001100011000101001000010000011000100001000001`

`01018A7260F68C87``0000000100000001100010100111001001100000111101101000110010000111`

#### Hints for implementers

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Chunk_format?section=20&veaction=edit "Edit section: Hints for implementers") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Chunk_format?action=edit&section=20 "Edit section's source code: Hints for implementers")\]

The number of entries per long may be calculated as floor(64 / bits\_per\_entry). The number of longs in the array may then be calculated as ceil(number\_of\_entries / entries\_per\_long). It may seem like this calculation could be simplified as number\_of\_entries times bits\_per\_entry divided by 64, but that formula is incorrect, since the intermediate rounding is significant and accounts for the padding at the end of each long.

In languages that lack a ceiling division operator, one can do the following:

```
// assuming integer division rounds towards 0, which is usually the case.
entries_per_long = 64 / bits_per_entry
number_of_longs = (number_of_entries + entries_per_long - 1) / entries_per_long
```

The index of the long an entry is located in may be calculated as floor(entry\_index / entries\_per\_long), and the 0-based index of the least significant bit of the entry within the long as (entry\_index % entries\_per\_long × bits\_per\_entry) (where % is the remainder operator).

To read an entry in a language with C-like bitwise operators, one can do the following:

```
// in some languages it is necessary to cast the 1 to a 64-bit type first, or else
// the shift will be performed in 32 bits. a C-style cast is shown as an example.
entry_mask = ((uint64_t)1 << bits_per_entry) - 1
long_index = entry_index / entries_per_long
bit_index = entry_index % entries_per_long * bits_per_entry
value = (data_array[long_index] >> bit_index) & entry_mask
```

And to write an entry:

```
data_array[long_index] &= ~(entry_mask << bit_index)
// if value has a smaller integer type, it may again be necessary to cast it to 64 bits.
data_array[long_index] |= (uint64_t)value << bit_index
```

Note that there are more efficient ways to convert all entries in a section to/from this format, as well as more efficient ways of doing the division and remainder computations for individual accesses with specific bit\_per\_entry values. This code merely represents the simplest possible implementation.

## Tips and notes

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Chunk_format?section=21&veaction=edit "Edit section: Tips and notes") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Chunk_format?action=edit&section=21 "Edit section's source code: Tips and notes")\]

There are several things that can make it easier to implement this format.

- Servers do _not_ need to implement the local palette initially (instead always using 15 bits per block), although it is an important optimization later on.
- The Notchian server implementation does not send values that are out of bounds for the palette. If such a value is received, the format is being parsed incorrectly. In particular, if you're reading a number with all bits set (15, 31, etc), you might be reading skylight data (or you may have a sign error and you're reading negative numbers).
- The Notchian client generally does not render chunks that lack neighbors. (As of 1.20.2 such chunks appear to sporadically become visible anyway, and do so consistently when interacted with.) This means that if you only send a fixed set of chunks with no empty chunks around them, then some of them will not be visible, although you can still interact with them. This is intended behavior, so that lighting and connected blocks can be handled correctly.

## Full implementations

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Chunk_format?section=22&veaction=edit "Edit section: Full implementations") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Chunk_format?action=edit&section=22 "Edit section's source code: Full implementations")\]

- [Java, 1.12.2, writing only, with palette](https://github.com/GlowstoneMC/Glowstone/blob/dev/src/main/java/net/glowstone/chunk/ChunkSection.java)
- [Rust, 1.16.5, with palette](https://github.com/feather-rs/feather/blob/main/feather/base/src/chunk.rs)
- [Java, 1.9, both sides](https://github.com/Steveice10/MCProtocolLib/blob/4ed72deb75f2acb0a81d641717b7b8074730f701/src/main/java/org/spacehq/mc/protocol/data/game/chunk/BlockStorage.java#L42)
- [Python, 1.7 through 1.13](https://github.com/barneygale/quarry). Read/write, paletted/unpaletted, [packets](https://github.com/barneygale/quarry/blob/master/quarry/types/buffer/v1_7.py#L403)/ [arrays](https://github.com/barneygale/quarry/blob/master/quarry/types/chunk.py)
- [Python, 1.9, reading only](https://github.com/SpockBotMC/SpockBot/blob/0535c31/spockbot/plugins/tools/smpmap.py#L144-L183)
- [C, 1.9, reading only](https://github.com/Protryon/Osmium/blob/fdd61b9/MinecraftClone/src/ingame.c#L512-L632)
- [C, 1.11.2, writing only](https://github.com/Protryon/Basin/blob/master/basin/src/packet.c#L1124)
- [C++, 1.12.2, writing only](https://github.com/cuberite/cuberite/blob/master/src/Protocol/ChunkDataSerializer.cpp#L190)
- [Node.js, 1.8->1.18](https://github.com/PrismarineJS/prismarine-chunk)

## Sample data

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Chunk_format?section=23&veaction=edit "Edit section: Sample data") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Chunk_format?action=edit&section=23 "Edit section's source code: Sample data")\]

- [some sample data](https://gist.github.com/Pokechu22/0b89f928b381dede0387fe5f88faf8c0) from 1.13.2, with both complete packets and just the data structures
- [prismarine test data](https://github.com/PrismarineJS/prismarine-chunk/tree/master/test) chunks from 1.8 to 1.20 used as testing data, generated using automated [chunk-dumper](https://github.com/PrismarineJS/minecraft-chunk-dumper)

### Old format

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Chunk_format?section=24&veaction=edit "Edit section: Old format") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Chunk_format?action=edit&section=24 "Edit section's source code: Old format")\]

The following implement the [previous](https://web.archive.org/https://wiki.vg/index.php?title=SMP_Map_Format&oldid=7164) (before 1.9) format:

- [Java, 1.8](https://github.com/GlowstoneMC/Glowstone/blob/d3ed79ea7d284df1d2cd1945bf53d5652962a34f/src/main/java/net/glowstone/GlowChunk.java#L640)
- [Python, 1.4](https://github.com/barneygale/smpmap)

[![](https://minecraft.wiki/images/License_cc.svg?7c689)](https://minecraft.wiki/w/File:License_cc.svg "File:License cc.svg")

[![](https://minecraft.wiki/images/License_cc-by.svg?818e9)](https://minecraft.wiki/w/File:License_cc-by.svg)[![](https://minecraft.wiki/images/License_cc-by-sa.svg?75cd1)](https://minecraft.wiki/w/File:License_cc-by-sa.svg)

This article is licensed under a [Creative Commons Attribution-ShareAlike 3.0](https://creativecommons.org/licenses/by-sa/3.0/) license.

This article has been imported from [wiki.vg](https://minecraft.wiki/w/Minecraft_Wiki:Projects/wiki.vg_merge "Minecraft Wiki:Projects/wiki.vg merge") or is a derivative of such a page. Thus, the wiki's [usual license](https://minecraft.wiki/w/Minecraft_Wiki:Copyrights "Minecraft Wiki:Copyrights") does not apply.

Derivative works must be licensed using the same or a compatible license.

Retrieved from " [https://minecraft.wiki/w/Java\_Edition\_protocol/Chunk\_format?oldid=3661930](https://minecraft.wiki/w/Java_Edition_protocol/Chunk_format?oldid=3661930)"

[Categories](https://minecraft.wiki/w/Special:Categories "Special:Categories"):

- [Protocol Details](https://minecraft.wiki/w/Category:Protocol_Details "Category:Protocol Details")
- [Java Edition protocol](https://minecraft.wiki/w/Category:Java_Edition_protocol "Category:Java Edition protocol")
- [CC BY-SA pages](https://minecraft.wiki/w/Category:CC_BY-SA_pages "Category:CC BY-SA pages")

Hidden category:

- [Needs updating](https://minecraft.wiki/w/Category:Needs_updating "Category:Needs updating")

## Navigation menu

Search

[Visit the main page](https://minecraft.wiki/ "Visit the main page")

[X](https://minecraft.wiki/w/Minecraft_Wiki:Indie_Wiki_Buddy)

**To leave feedback for the game, [click here](https://feedback.minecraft.net/).**

Feedback will be posted anonymously and shared to our [Discord](https://discord.gg/fGdE5ZE).

Something went wrong

Dismiss