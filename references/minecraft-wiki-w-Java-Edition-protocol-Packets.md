1 language

- [Deutsch](https://de.minecraft.wiki/w/Minecraft-Server-Protokoll/Pakete "Minecraft-Server-Protokoll/Pakete – Deutsch")

[![This article is licensed under a Creative Commons Attribution-ShareAlike 3.0 license. Derivative works must be licensed using the same or a compatible license.](https://minecraft.wiki/images/Cc-by-sa.svg?fc1a9)](https://creativecommons.org/licenses/by-sa/3.0/ "This article is licensed under a Creative Commons Attribution-ShareAlike 3.0 license. Derivative works must be licensed using the same or a compatible license.")

# _Java Edition_ protocol/Packets  Share article feedback

From Minecraft Wiki

< [Java Edition protocol](https://minecraft.wiki/w/Java_Edition_protocol "Java Edition protocol")

[Jump to navigation](https://minecraft.wiki/w/Java_Edition_protocol/Packets#mw-head) [Jump to search](https://minecraft.wiki/w/Java_Edition_protocol/Packets#searchInput)

![](https://minecraft.wiki/images/Disambig_color.svg?2db52) This article is about the protocol for a stable release of _[Java Edition](https://minecraft.wiki/w/Java_Edition "Java Edition")_. For the protocol used in development versions of _[Java Edition](https://minecraft.wiki/w/Java_Edition "Java Edition")_, see [Java Edition protocol/Development version](https://minecraft.wiki/w/Java_Edition_protocol/Development_version "Java Edition protocol/Development version"). For the protocol used in _[Bedrock Edition](https://minecraft.wiki/w/Bedrock_Edition "Bedrock Edition")_, see [Bedrock Edition protocol](https://minecraft.wiki/w/Bedrock_Edition_protocol "Bedrock Edition protocol"). For the protocol used in old _[Pocket Edition](https://minecraft.wiki/w/Pocket_Edition "Pocket Edition")_ versions, see [Pocket Edition protocol](https://minecraft.wiki/w/Pocket_Edition_protocol "Pocket Edition protocol").

See also: [Java Edition protocol/FAQ](https://minecraft.wiki/w/Java_Edition_protocol/FAQ "Java Edition protocol/FAQ")

[![](https://minecraft.wiki/images/Information_icon.svg?15c1c)](https://minecraft.wiki/w/File:Information_icon.svg "File:Information icon.svg")

This feature is exclusive to [_Java Edition_](https://minecraft.wiki/w/Java_Edition "Java Edition").

[![](https://minecraft.wiki/images/Information_icon.svg?15c1c)](https://minecraft.wiki/w/File:Information_icon.svg "File:Information icon.svg")

While you may use the contents of this page without restriction to create servers, clients, bots, etc; keep in mind that the contents of this page are distributed under the terms of [CC BY-SA 3.0 Unported](https://creativecommons.org/licenses/by-sa/3.0/). Reproductions and derivative works must be distributed accordingly.

## Contents

- [1Definitions](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Definitions)
  - [1.1Data types](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Data_types)
  - [1.2Identifier](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Identifier)
  - [1.3VarInt and VarLong](https://minecraft.wiki/w/Java_Edition_protocol/Packets#VarInt_and_VarLong)
  - [1.4Position](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Position)
  - [1.5Fixed-point numbers](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Fixed-point_numbers)
  - [1.6Arrays](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Arrays)
    - [1.6.1Array](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Array)
    - [1.6.2Prefixed Array](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Prefixed_Array)
  - [1.7Bit sets](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Bit_sets)
    - [1.7.1BitSet](https://minecraft.wiki/w/Java_Edition_protocol/Packets#BitSet)
    - [1.7.2Fixed BitSet](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Fixed_BitSet)
  - [1.8Registry references](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Registry_references)
    - [1.8.1ID or X](https://minecraft.wiki/w/Java_Edition_protocol/Packets#ID_or_X)
    - [1.8.2ID Set](https://minecraft.wiki/w/Java_Edition_protocol/Packets#ID_Set)
  - [1.9Inline data](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Inline_data)
    - [1.9.1Sound Event](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Sound_Event)
    - [1.9.2Chat Type](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Chat_Type)
  - [1.10Teleport Flags](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Teleport_Flags)
  - [1.11Light Data](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Light_Data)
  - [1.12Game Profile](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Game_Profile)
  - [1.13Resolvable Profile](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Resolvable_Profile)
  - [1.14Debug subscriptions](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Debug_subscriptions)
    - [1.14.1Debug Subscription Event](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Debug_Subscription_Event)
    - [1.14.2Debug Subscription Update](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Debug_Subscription_Update)
    - [1.14.3Debug Subscription Data](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Debug_Subscription_Data)
    - [1.14.4Debug Path Node](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Debug_Path_Node)
    - [1.14.5Debug Structure Info](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Debug_Structure_Info)
  - [1.15Other definitions](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Other_definitions)
- [2Packet format](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Packet_format)
  - [2.1Without compression](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Without_compression)
  - [2.2With compression](https://minecraft.wiki/w/Java_Edition_protocol/Packets#With_compression)
- [3List of packets](https://minecraft.wiki/w/Java_Edition_protocol/Packets#List_of_packets)
  - [3.1Handshaking](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Handshaking)
  - [3.2Status](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Status)
  - [3.3Login](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Login)
  - [3.4Configuration](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Configuration)
  - [3.5Play](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Play)
- [4Handshaking](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Handshaking_2)
  - [4.1Clientbound](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Clientbound)
  - [4.2Serverbound](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Serverbound)
    - [4.2.1Handshake](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Handshake)
    - [4.2.2Legacy Server List Ping](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Legacy_Server_List_Ping)
- [5Status](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Status_2)
  - [5.1Clientbound](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Clientbound_2)
    - [5.1.1Status Response](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Status_Response)
    - [5.1.2Pong Response (status)](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Pong_Response_(status))
  - [5.2Serverbound](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Serverbound_2)
    - [5.2.1Status Request](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Status_Request)
    - [5.2.2Ping Request (status)](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Ping_Request_(status))
- [6Login](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Login_2)
  - [6.1Clientbound](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Clientbound_3)
    - [6.1.1Disconnect (login)](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Disconnect_(login))
    - [6.1.2Encryption Request](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Encryption_Request)
    - [6.1.3Login Success](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Login_Success)
    - [6.1.4Set Compression](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Set_Compression)
    - [6.1.5Login Plugin Request](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Login_Plugin_Request)
  - [6.2Serverbound](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Serverbound_3)
    - [6.2.1Login Start](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Login_Start)
    - [6.2.2Encryption Response](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Encryption_Response)
    - [6.2.3Login Plugin Response](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Login_Plugin_Response)
    - [6.2.4Login Acknowledged](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Login_Acknowledged)
- [7Login, configuration and play](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Login,_configuration_and_play)
  - [7.1Clientbound](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Clientbound_4)
    - [7.1.1Cookie Request](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Cookie_Request)
  - [7.2Serverbound](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Serverbound_4)
    - [7.2.1Cookie Response](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Cookie_Response)
- [8Configuration and play](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Configuration_and_play)
  - [8.1Clientbound](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Clientbound_5)
    - [8.1.1Plugin Message (clientbound)](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Plugin_Message_(clientbound))
    - [8.1.2Disconnect](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Disconnect)
    - [8.1.3Keep Alive (clientbound)](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Keep_Alive_(clientbound))
    - [8.1.4Ping](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Ping)
    - [8.1.5Remove Resource Pack](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Remove_Resource_Pack)
    - [8.1.6Add Resource Pack](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Add_Resource_Pack)
    - [8.1.7Post Effects](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Post_Effects)
    - [8.1.8Store Cookie](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Store_Cookie)
    - [8.1.9Transfer](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Transfer)
    - [8.1.10Update Tags](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Update_Tags)
    - [8.1.11Custom Report Details](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Custom_Report_Details)
    - [8.1.12Server Links](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Server_Links)
    - [8.1.13Clear Dialog](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Clear_Dialog)
  - [8.2Serverbound](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Serverbound_5)
    - [8.2.1Client Information](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Client_Information)
    - [8.2.2Plugin Message (serverbound)](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Plugin_Message_(serverbound))
    - [8.2.3Keep Alive (serverbound)](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Keep_Alive_(serverbound))
    - [8.2.4Pong](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Pong)
    - [8.2.5Resource Pack Response](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Resource_Pack_Response)
    - [8.2.6Custom Click Action](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Custom_Click_Action)
- [9Configuration](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Configuration_2)
  - [9.1Clientbound](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Clientbound_6)
    - [9.1.1Finish Configuration](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Finish_Configuration)
    - [9.1.2Reset Chat](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Reset_Chat)
    - [9.1.3Registry Data](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Registry_Data)
    - [9.1.4Feature Flags](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Feature_Flags)
    - [9.1.5Known Packs (clientbound)](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Known_Packs_(clientbound))
    - [9.1.6Show Dialog (configuration)](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Show_Dialog_(configuration))
    - [9.1.7Code of Conduct](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Code_of_Conduct)
  - [9.2Serverbound](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Serverbound_6)
    - [9.2.1Acknowledge Finish Configuration](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Acknowledge_Finish_Configuration)
    - [9.2.2Known Packs (serverbound)](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Known_Packs_(serverbound))
    - [9.2.3Accept Code of Conduct](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Accept_Code_of_Conduct)
- [10Play](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Play_2)
  - [10.1Clientbound](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Clientbound_7)
    - [10.1.1Bundle Delimiter](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Bundle_Delimiter)
    - [10.1.2Spawn Entity](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Spawn_Entity)
    - [10.1.3Entity Animation](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Entity_Animation)
    - [10.1.4Award Statistics](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Award_Statistics)
    - [10.1.5Acknowledge Block Change](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Acknowledge_Block_Change)
    - [10.1.6Set Block Destroy Stage](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Set_Block_Destroy_Stage)
    - [10.1.7Block Entity Data](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Block_Entity_Data)
    - [10.1.8Block Action](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Block_Action)
    - [10.1.9Block Update](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Block_Update)
    - [10.1.10Boss Bar](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Boss_Bar)
    - [10.1.11Change Difficulty](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Change_Difficulty)
    - [10.1.12Chunk Batch Finished](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Chunk_Batch_Finished)
    - [10.1.13Chunk Batch Start](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Chunk_Batch_Start)
    - [10.1.14Chunk Biomes](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Chunk_Biomes)
    - [10.1.15Clear Titles](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Clear_Titles)
    - [10.1.16Command Suggestions Response](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Command_Suggestions_Response)
    - [10.1.17Commands](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Commands)
    - [10.1.18Close Container](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Close_Container)
    - [10.1.19Set Container Content](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Set_Container_Content)
    - [10.1.20Set Container Property](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Set_Container_Property)
    - [10.1.21Set Container Slot](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Set_Container_Slot)
    - [10.1.22Set Cooldown](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Set_Cooldown)
    - [10.1.23Chat Suggestions](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Chat_Suggestions)
    - [10.1.24Damage Event](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Damage_Event)
    - [10.1.25Debug Block Value](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Debug_Block_Value)
    - [10.1.26Debug Chunk Value](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Debug_Chunk_Value)
    - [10.1.27Debug Entity Value](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Debug_Entity_Value)
    - [10.1.28Debug Event](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Debug_Event)
    - [10.1.29Debug Sample](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Debug_Sample)
    - [10.1.30Delete Message](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Delete_Message)
    - [10.1.31Disguised Chat Message](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Disguised_Chat_Message)
    - [10.1.32Entity Event](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Entity_Event)
    - [10.1.33Teleport Entity](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Teleport_Entity)
    - [10.1.34Explosion](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Explosion)
    - [10.1.35Add Transient Block](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Add_Transient_Block)
    - [10.1.36Unload Chunk](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Unload_Chunk)
    - [10.1.37Game Event](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Game_Event)
    - [10.1.38Game Rule Values](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Game_Rule_Values)
    - [10.1.39Game Test Highlight Position](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Game_Test_Highlight_Position)
    - [10.1.40Open Horse Screen](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Open_Horse_Screen)
    - [10.1.41Hurt Animation](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Hurt_Animation)
    - [10.1.42Initialize World Border](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Initialize_World_Border)
    - [10.1.43Chunk Data and Update Light](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Chunk_Data_and_Update_Light)
    - [10.1.44World Event](https://minecraft.wiki/w/Java_Edition_protocol/Packets#World_Event)
    - [10.1.45Particle](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Particle)
    - [10.1.46Update Light](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Update_Light)
    - [10.1.47Login (play)](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Login_(play))
    - [10.1.48Low Disk Space Warning](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Low_Disk_Space_Warning)
    - [10.1.49Map Data](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Map_Data)
    - [10.1.50Merchant Offers](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Merchant_Offers)
    - [10.1.51Update Entity Position](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Update_Entity_Position)
    - [10.1.52Update Entity Position and Rotation](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Update_Entity_Position_and_Rotation)
    - [10.1.53Move Minecart Along Track](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Move_Minecart_Along_Track)
    - [10.1.54Update Entity Rotation](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Update_Entity_Rotation)
    - [10.1.55Move Vehicle (clientbound)](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Move_Vehicle_(clientbound))
    - [10.1.56Open Book](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Open_Book)
    - [10.1.57Open Screen](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Open_Screen)
    - [10.1.58Open Sign Editor](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Open_Sign_Editor)
    - [10.1.59Place Ghost Recipe](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Place_Ghost_Recipe)
    - [10.1.60Player Abilities (clientbound)](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Player_Abilities_(clientbound))
    - [10.1.61Player Chat Message](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Player_Chat_Message)
    - [10.1.62End Combat](https://minecraft.wiki/w/Java_Edition_protocol/Packets#End_Combat)
    - [10.1.63Enter Combat](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Enter_Combat)
    - [10.1.64Combat Death](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Combat_Death)
    - [10.1.65Player Info Remove](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Player_Info_Remove)
    - [10.1.66Player Info Update](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Player_Info_Update)
    - [10.1.67Look At](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Look_At)
    - [10.1.68Synchronize Player Position](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Synchronize_Player_Position)
    - [10.1.69Player Rotation](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Player_Rotation)
    - [10.1.70Recipe Book Add](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Recipe_Book_Add)
    - [10.1.71Recipe Book Remove](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Recipe_Book_Remove)
    - [10.1.72Recipe Book Settings](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Recipe_Book_Settings)
    - [10.1.73Remove Entities](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Remove_Entities)
    - [10.1.74Remove Entity Effect](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Remove_Entity_Effect)
    - [10.1.75Reset Score](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Reset_Score)
    - [10.1.76Respawn](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Respawn)
    - [10.1.77Set Head Rotation](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Set_Head_Rotation)
    - [10.1.78Update Section Blocks](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Update_Section_Blocks)
    - [10.1.79Select Advancements Tab](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Select_Advancements_Tab)
    - [10.1.80Server Data](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Server_Data)
    - [10.1.81Set Action Bar Text](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Set_Action_Bar_Text)
    - [10.1.82Set Border Center](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Set_Border_Center)
    - [10.1.83Set Border Lerp Size](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Set_Border_Lerp_Size)
    - [10.1.84Set Border Size](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Set_Border_Size)
    - [10.1.85Set Border Warning Delay](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Set_Border_Warning_Delay)
    - [10.1.86Set Border Warning Distance](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Set_Border_Warning_Distance)
    - [10.1.87Set Camera](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Set_Camera)
    - [10.1.88Set Center Chunk](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Set_Center_Chunk)
    - [10.1.89Set Render Distance](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Set_Render_Distance)
    - [10.1.90Set Cursor Item](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Set_Cursor_Item)
    - [10.1.91Set Default Spawn Position](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Set_Default_Spawn_Position)
    - [10.1.92Display Objective](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Display_Objective)
    - [10.1.93Set Entity Metadata](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Set_Entity_Metadata)
    - [10.1.94Link Entities](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Link_Entities)
    - [10.1.95Set Entity Velocity](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Set_Entity_Velocity)
    - [10.1.96Set Equipment](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Set_Equipment)
    - [10.1.97Set Experience](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Set_Experience)
    - [10.1.98Set Health](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Set_Health)
    - [10.1.99Set Held Item (clientbound)](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Set_Held_Item_(clientbound))
    - [10.1.100Update Objectives](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Update_Objectives)
    - [10.1.101Set Passengers](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Set_Passengers)
    - [10.1.102Set Player Inventory Slot](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Set_Player_Inventory_Slot)
    - [10.1.103Update Teams](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Update_Teams)
    - [10.1.104Update Score](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Update_Score)
    - [10.1.105Set Simulation Distance](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Set_Simulation_Distance)
    - [10.1.106Set Subtitle Text](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Set_Subtitle_Text)
    - [10.1.107Update Time](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Update_Time)
    - [10.1.108Set Title Text](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Set_Title_Text)
    - [10.1.109Set Title Animation Times](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Set_Title_Animation_Times)
    - [10.1.110Entity Sound Effect](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Entity_Sound_Effect)
    - [10.1.111Sound Effect](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Sound_Effect)
    - [10.1.112Start Configuration](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Start_Configuration)
    - [10.1.113Stop Sound](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Stop_Sound)
    - [10.1.114Swing Animation](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Swing_Animation)
    - [10.1.115System Chat Message](https://minecraft.wiki/w/Java_Edition_protocol/Packets#System_Chat_Message)
    - [10.1.116Set Tab List Header And Footer](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Set_Tab_List_Header_And_Footer)
    - [10.1.117Tag Query Response](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Tag_Query_Response)
    - [10.1.118Pickup Item](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Pickup_Item)
    - [10.1.119Synchronize Vehicle Position](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Synchronize_Vehicle_Position)
    - [10.1.120Test Instance Block Status](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Test_Instance_Block_Status)
    - [10.1.121Set Ticking State](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Set_Ticking_State)
    - [10.1.122Step Tick](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Step_Tick)
    - [10.1.123Update Advancements](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Update_Advancements)
    - [10.1.124Update Attributes](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Update_Attributes)
    - [10.1.125Entity Effect](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Entity_Effect)
    - [10.1.126Update Recipes](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Update_Recipes)
    - [10.1.127Projectile Power](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Projectile_Power)
    - [10.1.128Waypoint](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Waypoint)
    - [10.1.129Show Dialog (play)](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Show_Dialog_(play))
  - [10.2Serverbound](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Serverbound_7)
    - [10.2.1Confirm Teleportation](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Confirm_Teleportation)
    - [10.2.2Attack](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Attack)
    - [10.2.3Query Block Entity Tag](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Query_Block_Entity_Tag)
    - [10.2.4Bundle Item Selected](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Bundle_Item_Selected)
    - [10.2.5Change Difficulty](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Change_Difficulty_2)
    - [10.2.6Change Game Mode](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Change_Game_Mode)
    - [10.2.7Acknowledge Message](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Acknowledge_Message)
    - [10.2.8Chat Command](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Chat_Command)
    - [10.2.9Signed Chat Command](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Signed_Chat_Command)
    - [10.2.10Chat Message](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Chat_Message)
    - [10.2.11Player Session](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Player_Session)
    - [10.2.12Chunk Batch Received](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Chunk_Batch_Received)
    - [10.2.13Client Status](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Client_Status)
    - [10.2.14Client Tick End](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Client_Tick_End)
    - [10.2.15Command Suggestions Request](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Command_Suggestions_Request)
    - [10.2.16Acknowledge Configuration](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Acknowledge_Configuration)
    - [10.2.17Click Container Button](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Click_Container_Button)
    - [10.2.18Click Container](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Click_Container)
    - [10.2.19Close Container](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Close_Container_2)
    - [10.2.20Change Container Slot State](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Change_Container_Slot_State)
    - [10.2.21Debug Subscription Request](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Debug_Subscription_Request)
    - [10.2.22Edit Book](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Edit_Book)
    - [10.2.23Query Entity Tag](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Query_Entity_Tag)
    - [10.2.24Interact](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Interact)
    - [10.2.25Jigsaw Generate](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Jigsaw_Generate)
    - [10.2.26Lock Difficulty](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Lock_Difficulty)
    - [10.2.27Set Player Position](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Set_Player_Position)
    - [10.2.28Set Player Position and Rotation](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Set_Player_Position_and_Rotation)
    - [10.2.29Set Player Rotation](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Set_Player_Rotation)
    - [10.2.30Set Player Movement Flags](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Set_Player_Movement_Flags)
    - [10.2.31Move Vehicle (serverbound)](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Move_Vehicle_(serverbound))
    - [10.2.32Paddle Boat](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Paddle_Boat)
    - [10.2.33Pick Item From Block](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Pick_Item_From_Block)
    - [10.2.34Pick Item From Entity](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Pick_Item_From_Entity)
    - [10.2.35Place Recipe](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Place_Recipe)
    - [10.2.36Player Abilities (serverbound)](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Player_Abilities_(serverbound))
    - [10.2.37Player Action](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Player_Action)
    - [10.2.38Player Command](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Player_Command)
    - [10.2.39Player Input](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Player_Input)
    - [10.2.40Player Loaded](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Player_Loaded)
    - [10.2.41Punch](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Punch)
    - [10.2.42Change Recipe Book Settings](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Change_Recipe_Book_Settings)
    - [10.2.43Set Seen Recipe](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Set_Seen_Recipe)
    - [10.2.44Rename Item](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Rename_Item)
    - [10.2.45Seen Advancements](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Seen_Advancements)
    - [10.2.46Select Trade](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Select_Trade)
    - [10.2.47Set Beacon Effect](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Set_Beacon_Effect)
    - [10.2.48Set Held Item (serverbound)](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Set_Held_Item_(serverbound))
    - [10.2.49Program Command Block](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Program_Command_Block)
    - [10.2.50Program Command Block Minecart](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Program_Command_Block_Minecart)
    - [10.2.51Set Creative Mode Slot](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Set_Creative_Mode_Slot)
    - [10.2.52Set Game Rules](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Set_Game_Rules)
    - [10.2.53Program Jigsaw Block](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Program_Jigsaw_Block)
    - [10.2.54Program Structure Block](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Program_Structure_Block)
    - [10.2.55Set Test Block](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Set_Test_Block)
    - [10.2.56Update Sign](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Update_Sign)
    - [10.2.57Spectator Action](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Spectator_Action)
    - [10.2.58Teleport To Entity](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Teleport_To_Entity)
    - [10.2.59Test Instance Block Action](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Test_Instance_Block_Action)
    - [10.2.60Use Item On](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Use_Item_On)
    - [10.2.61Use Item](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Use_Item)
- [11Navigation](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Navigation)

This article presents a dissection of the current _[Java Edition](https://minecraft.wiki/w/Java_Edition "Java Edition")_ **protocol** for [26.3, protocol 777](https://minecraft.wiki/w/Minecraft_Wiki:Projects/wiki.vg_merge/Protocol_version_numbers "Minecraft Wiki:Projects/wiki.vg merge/Protocol version numbers").

The changes between versions may be viewed at [Protocol History](https://minecraft.wiki/w/Minecraft_Wiki:Projects/wiki.vg_merge/Protocol_History "Minecraft Wiki:Projects/wiki.vg merge/Protocol History").

## Definitions

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=1&veaction=edit "Edit section: Definitions") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=1 "Edit section's source code: Definitions")\]

The Minecraft server accepts connections from TCP clients and communicates with them using _packets_. A packet is a sequence of bytes sent over the TCP connection. The meaning of a packet depends both on its packet ID and the current state of the connection. The initial state of each connection is [Handshaking](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Handshaking), and state is switched using the packets [Handshake](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Handshake) and [Login Success](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Login_Success).

### Data types

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=2&veaction=edit "Edit section: Data types") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=2 "Edit section's source code: Data types")\]

All data sent over the network (except for VarInt and VarLong) is [big-endian](https://en.wikipedia.org/wiki/Endianness#Big-endian "wikipedia:Endianness"), that is the bytes are sent from most significant byte to least significant byte. The majority of everyday computers are little-endian, therefore it may be necessary to change the endianness before sending data over the network.

| Name | Size (bytes) | Encodes | Notes |
| --- | --- | --- | --- |
| [Boolean](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Boolean) | 1 | Either false or true | True is encoded as `0x01`, false as `0x00`. |
| [Byte](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Byte) | 1 | An integer between -128 and 127 | Signed 8-bit integer, [two's complement](https://en.wikipedia.org/wiki/Two%27s_complement "wikipedia:Two's complement") |
| [Unsigned Byte](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Unsigned_Byte) | 1 | An integer between 0 and 255 | Unsigned 8-bit integer |
| [Short](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Short) | 2 | An integer between -32 768 and 32 767 | Signed 16-bit integer, two's complement |
| [Unsigned Short](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Unsigned_Short) | 2 | An integer between 0 and 65 535 | Unsigned 16-bit integer |
| [Int](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Int) | 4 | An integer between -2 147 483 648 and 2 147 483 647 | Signed 32-bit integer, two's complement |
| [Long](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Long) | 8 | An integer between -9 223 372 036 854 775 808 and 9 223 372 036 854 775 807 | Signed 64-bit integer, two's complement |
| [Float](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Float) | 4 | A [single-precision 32-bit IEEE 754 floating point number](https://en.wikipedia.org/wiki/Single-precision_floating-point_format "wikipedia:Single-precision floating-point format") |  |
| [Double](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Double) | 8 | A [double-precision 64-bit IEEE 754 floating point number](https://en.wikipedia.org/wiki/Double-precision_floating-point_format "wikipedia:Double-precision floating-point format") |  |
| [String](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:String) (n) | ≥ 1 <br>≤ (n×3) + 3 | A sequence of [Unicode](https://en.wikipedia.org/wiki/Unicode "wikipedia:Unicode") [scalar values](http://unicode.org/glossary/#unicode_scalar_value) | [UTF-8](https://en.wikipedia.org/wiki/UTF-8 "wikipedia:UTF-8") string prefixed with its size in bytes as a VarInt. Maximum length of `n` characters, which varies by context. The encoding used on the wire is regular UTF-8, _not_ [Java's "slight modification"](https://docs.oracle.com/en/java/javase/18/docs/api/java.base/java/io/DataInput.html#modified-utf-8). However, the length of the string for purposes of the length limit is its number of [UTF-16](https://en.wikipedia.org/wiki/UTF-16 "wikipedia:UTF-16") code units, that is, scalar values > U+FFFF are counted as two. Up to `n × 3` bytes can be used to encode a UTF-8 string comprising `n` code units when converted to UTF-16, and both of those limits are checked. Maximum `n` value is 32767. The + 3 is due to the max size of a valid length VarInt. |
| [Text Component](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Text_Component) | Varies | See [Text component format](https://minecraft.wiki/w/Text_component_format "Text component format") | Encoded as a [NBT Tag](https://minecraft.wiki/w/Minecraft_Wiki:Projects/wiki.vg_merge/NBT "Minecraft Wiki:Projects/wiki.vg merge/NBT"), with the type of tag used depending on the case:<br>- As a [String Tag](https://minecraft.wiki/w/Minecraft_Wiki:Projects/wiki.vg_merge/NBT#Specification:string_tag "Minecraft Wiki:Projects/wiki.vg merge/NBT"): For components only containing text (no styling, no events etc.).<br>- As a [Compound Tag](https://minecraft.wiki/w/Minecraft_Wiki:Projects/wiki.vg_merge/NBT#Specification:compound_tag "Minecraft Wiki:Projects/wiki.vg merge/NBT"): Every other case. |
| [JSON Text Component](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:JSON_Text_Component) | ≥ 1 <br>≤ (262144×3) + 3 | See [Text component format](https://minecraft.wiki/w/Text_component_format "Text component format") | The maximum permitted length when decoding is 262 144, but the vanilla server since 1.20.3 refuses to encode longer than 32 767. This may be a bug. |
| [Identifier](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Identifier) | ≥ 1 <br>≤ (32767×3) + 3 | See [Identifier](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Identifier) below | Encoded as a String with max length of 32 767. |
| [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) | ≥ 1 <br>≤ 5 | An integer between -2 147 483 648 and 2 147 483 647 | Variable-length data encoding a two's complement signed 32-bit integer; more info in [their section](https://minecraft.wiki/w/Java_Edition_protocol/Packets#VarInt_and_VarLong) |
| [VarLong](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarLong) | ≥ 1 <br>≤ 10 | An integer between -9 223 372 036 854 775 808 and 9 223 372 036 854 775 807 | Variable-length data encoding a two's complement signed 64-bit integer; more info in [their section](https://minecraft.wiki/w/Java_Edition_protocol/Packets#VarInt_and_VarLong) |
| [Entity Metadata](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Entity_Metadata) | Varies | Miscellaneous information about an entity | See [Entity metadata#Entity Metadata Format](https://minecraft.wiki/w/Java_Edition_protocol/Entity_metadata#Entity_Metadata_Format "Java Edition protocol/Entity metadata") |
| [Slot](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Slot) | Varies | An item stack in an inventory or container | See [Slot Data](https://minecraft.wiki/w/Java_Edition_protocol/Slot_Data "Java Edition protocol/Slot Data") |
| [Hashed Slot](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Hashed_Slot) | Varies | Similar to Slot, but with the data component values being sent as a hash instead of their actual contents | See [Slot Data#Hashed Format](https://minecraft.wiki/w/Java_Edition_protocol/Slot_Data#Hashed_Format "Java Edition protocol/Slot Data") |
| [NBT](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:NBT) | Varies | Depends on context | See [NBT](https://minecraft.wiki/w/Minecraft_Wiki:Projects/wiki.vg_merge/NBT "Minecraft Wiki:Projects/wiki.vg merge/NBT") |
| [Position](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Position) | 8 | An integer/block position: x (-33 554 432 to 33 554 431), z (-33 554 432 to 33 554 431), y (-2048 to 2047) | x as a 26-bit integer, followed by z as a 26-bit integer, followed by y as a 12-bit integer (all signed, two's complement). See also [the section below](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Position). |
| [Angle](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Angle) | 1 | A rotation angle in steps of 1/256 of a full turn | Whether or not this is signed does not matter, since the resulting angles are the same. |
| [UUID](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:UUID) | 16 | A [UUID](https://en.wikipedia.org/wiki/Universally_unique_identifier "wikipedia:Universally unique identifier") | Encoded as an unsigned 128-bit integer (or two unsigned 64-bit integers: the most significant 64 bits and then the least significant 64 bits) |
| [BitSet](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:BitSet) | Varies | See [#BitSet](https://minecraft.wiki/w/Java_Edition_protocol/Packets#BitSet) below | A length-prefixed bit set. |
| [Fixed BitSet](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Fixed_BitSet) (n) | ceil(n / 8) | See [#Fixed BitSet](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Fixed_BitSet) below | A bit set with a fixed length of n bits. |
| [Optional](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Optional) X | 0 or size of X | A field of type X, or nothing | Whether or not the field is present must be known from the context. |
| [Prefixed Optional](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Prefixed_Optional) X | size of [Boolean](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Boolean) \+ (is present [?](https://en.wikipedia.org/wiki/Ternary_conditional_operator "wikipedia:Ternary conditional operator") Size of X : 0) | A boolean and if present, a field of type X | The boolean is true if the field is present. |
| [Array](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Array) of X | length times size of X | Zero or more fields of type X | The length must be known from the context. |
| [Prefixed Array](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Prefixed_Array) of X | size of [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) \+ size of X \* length | See [#Prefixed Array](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Prefixed_Array) below | A length-prefixed array. |
| X [Enum](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Enum) | size of X | A specific value from a given list | The list of possible values and how each is encoded as an X must be known from the context. An invalid value sent by either side will usually result in the client being disconnected with an error or even crashing. |
| [Byte Array](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Byte_Array) | Varies | Depends on context | This is just a sequence of zero or more bytes, its meaning should be explained somewhere else, e.g. in the packet description. The length must also be known from the context. |
| [ID or](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:ID_or) X | size of [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) \+ (size of X or 0) | See [#ID or X](https://minecraft.wiki/w/Java_Edition_protocol/Packets#ID_or_X) below | Either a registry ID or an inline data definition of type X. |
| [ID Set](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:ID_Set) | Varies | See [#ID Set](https://minecraft.wiki/w/Java_Edition_protocol/Packets#ID_Set) below | Set of registry IDs specified either inline or as a reference to a tag. |
| [Sound Event](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Sound_Event) | Varies | See [#Sound Event](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Sound_Event) below | Parameters for a sound event. |
| [Chat Type](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Chat_Type) | Varies | See [#Chat Type](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Chat_Type) below | Parameters for a direct chat type. |
| [Teleport Flags](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Teleport_Flags) | 4 | See [#Teleport Flags](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Teleport_Flags) below | Bit field specifying how a teleportation is to be applied on each axis. |
| [Recipe Display](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Recipe_Display) | Varies | See [Recipes#Recipe Display structure](https://minecraft.wiki/w/Minecraft_Wiki:Projects/wiki.vg_merge/Recipes#Recipe_Display_structure "Minecraft Wiki:Projects/wiki.vg merge/Recipes") | Description of a recipe for use for use by the client. |
| [Slot Display](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Slot_Display) | Varies | See [Recipes#Slot Display structure](https://minecraft.wiki/w/Minecraft_Wiki:Projects/wiki.vg_merge/Recipes#Slot_Display_structure "Minecraft Wiki:Projects/wiki.vg merge/Recipes") | Description of a recipe ingredient slot for use for use by the client. |
| [Light Data](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Light_Data) | Varies | See [#Light Data](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Light_Data) below |  |
| [Either](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Either) X or Y | size of [Boolean](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Boolean) \+ (isX ? size of X : size of Y) | A boolean followed by either X or Y | The boolean is true if X is encoded, and false if Y is encoded. |
| [Game Profile](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Game_Profile) | Varies | See [#Game Profile](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Game_Profile) below | A Minecraft player profile. |
| [Resolvable Profile](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Resolvable_Profile) | Varies | See [#Resolvable Profile](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Resolvable_Profile) below |  |
| [Debug Subscription Event](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Debug_Subscription_Event) | Varies | See [#Debug Subscription Event](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Debug_Subscription_Event) below |  |
| [Debug Subscription Update](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Debug_Subscription_Update) | Varies | See [#Debug Subscription Update](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Debug_Subscription_Update) below |  |
| [LpVec3](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:LpVec3) | Varies | See [#LpVec3](https://minecraft.wiki/w/Java_Edition_protocol/Data_types#LpVec3 "Java Edition protocol/Data types") below | Usually used for low velocities. |

### Identifier

Identifiers are a namespaced location, in the form of `minecraft:thing`. If the namespace is not provided, it defaults to `minecraft` (i.e. `thing` is `minecraft:thing`). Custom content should always be in its own namespace, not the default one. Both the namespace and value can use all lowercase alphanumeric characters (a-z and 0-9), dot (`.`), dash (`-`), and underscore (`_`). In addition, values can use slash (`/`). The naming convention is `lower_case_with_underscores`. [More information](https://minecraft.net/en-us/article/minecraft-snapshot-17w43a).
For ease of determining whether a namespace or value is valid, here are regular expressions for each:

- Namespace: `[a-z0-9.\-_]`
- Value: `[a-z0-9.\-_/]`

### VarInt and VarLong

Variable-length format such that smaller numbers use fewer bytes. These are very similar to [Protocol Buffer Varints](http://developers.google.com/protocol-buffers/docs/encoding#varints): the 7 least significant bits are used to encode the value and the most significant bit indicates whether there's another byte after it for the next part of the number. The least significant group is written first, followed by each of the more significant groups; thus, VarInts are effectively little endian (however, groups are 7 bits, not 8).

VarInts are never longer than 5 bytes, and VarLongs are never longer than 10 bytes. Within these limits, unnecessarily long encodings (e.g. `81 00` to encode 1) are allowed.

Pseudocode to read and write VarInts:

```
int readVarInt() {
    int value = 0;

    for (int position = 0; position < 32; position += 7) {
        byte currentByte = readByte();

        // Note: In C this must be performed on an unsigned type to avoid undefined overflow
        // behavior with negative VarInts.
        value |= (int)(currentByte & 0x7F) << position;

        if ((currentByte & 0x80) == 0)
            return value;
    }

    error("VarInt too big");
}
```

```
void writeVarInt(int value) {
    while ((value & ~0x7F) != 0) {
        writeByte((value & 0x7F) | 0x80);

        // Note: >>> means that the leftmost bits are filled with zeroes regardless of the sign,
        // rather than being filled with copies of the sign bit to preserve the sign.
        // In languages that don't have a ">>>" operator, This behavior can often be selected by
        // performing the shift on an unsigned type.
        value >>>= 7;
    }

    writeByte(value);
}
```

The above code may be adapted for VarLongs by changing the type of `value` to `long` and the for loop condition to `position < 64`.

[![](https://minecraft.wiki/images/thumb/Ambox_warning_pn.png/32px-Ambox_warning_pn.png?b6e1c)](https://minecraft.wiki/w/File:Ambox_warning_pn.png "File:Ambox warning pn.png")

Note Minecraft's VarInts are identical to [LEB128](https://en.wikipedia.org/wiki/LEB128 "wikipedia:LEB128") with the slight change of throwing an exception if it goes over a set amount of bytes.

[![](https://minecraft.wiki/images/thumb/Ambox_warning_pn.png/32px-Ambox_warning_pn.png?b6e1c)](https://minecraft.wiki/w/File:Ambox_warning_pn.png "File:Ambox warning pn.png")

Note that Minecraft's VarInts are not encoded using Protocol Buffers; it's just similar. If you try to use Protocol Buffers Varints with Minecraft's VarInts, you'll get incorrect results in some cases. The major differences:

- Minecraft's VarInts are all signed, but do not use the ZigZag encoding. Protocol buffers have 3 types of Varints: `uint32` (normal encoding, unsigned), `sint32` (ZigZag encoding, signed), and `int32` (normal encoding, signed). Minecraft's are the `int32` variety. Because Minecraft uses the normal encoding instead of ZigZag encoding, negative values always use the maximum number of bytes.
- Minecraft's VarInts are never longer than 5 bytes and its VarLongs will never be longer than 10 bytes, while Protocol Buffer Varints will always use 10 bytes when encoding negative numbers, even if it's an `int32`.

Sample VarInts:

| Value | Hex bytes | Decimal bytes |
| --- | --- | --- |
| 0 | 0x00 | 0 |
| 1 | 0x01 | 1 |
| 2 | 0x02 | 2 |
| 127 | 0x7F | 127 |
| 128 | 0x80 0x01 | 128 1 |
| 255 | 0xFF 0x01 | 255 1 |
| 25565 | 0xDD 0xC7 0x01 | 221 199 1 |
| 2097151 | 0xFF 0xFF 0x7F | 255 255 127 |
| 2147483647 | 0xFF 0xFF 0xFF 0xFF 0x07 | 255 255 255 255 7 |
| -1 | 0xFF 0xFF 0xFF 0xFF 0x0F | 255 255 255 255 15 |
| -2147483648 | 0x80 0x80 0x80 0x80 0x08 | 128 128 128 128 8 |

Sample VarLongs:

| Value | Hex bytes | Decimal bytes |
| --- | --- | --- |
| 0 | 0x00 | 0 |
| 1 | 0x01 | 1 |
| 2 | 0x02 | 2 |
| 127 | 0x7F | 127 |
| 128 | 0x80 0x01 | 128 1 |
| 255 | 0xFF 0x01 | 255 1 |
| 2147483647 | 0xFF 0xFF 0xFF 0xFF 0x07 | 255 255 255 255 7 |
| 9223372036854775807 | 0xFF 0xFF 0xFF 0xFF 0xFF 0xFF 0xFF 0xFF 0x7F | 255 255 255 255 255 255 255 255 127 |
| -1 | 0xFF 0xFF 0xFF 0xFF 0xFF 0xFF 0xFF 0xFF 0xFF 0x01 | 255 255 255 255 255 255 255 255 255 1 |
| -2147483648 | 0x80 0x80 0x80 0x80 0xF8 0xFF 0xFF 0xFF 0xFF 0x01 | 128 128 128 128 248 255 255 255 255 1 |
| -9223372036854775808 | 0x80 0x80 0x80 0x80 0x80 0x80 0x80 0x80 0x80 0x01 | 128 128 128 128 128 128 128 128 128 1 |

### Position

**Note:** What you are seeing here is the latest version of the [Data types](https://minecraft.wiki/w/Minecraft_Wiki:Projects/wiki.vg_merge/Data_types "Minecraft Wiki:Projects/wiki.vg merge/Data types") article, but the position type was [different before 1.14](https://minecraft.wiki/w/Java_Edition_protocol/Data_types?oldid=2767033#Position).

64-bit value split into three **signed** integer parts:

- x: 26 MSBs
- z: 26 middle bits
- y: 12 LSBs

For example, a 64-bit position can be broken down as follows:

Example value (big endian): `01000110000001110110001100 10110000010101101101001000 001100111111`

- The red value is the X coordinate, which is `18357644` in this example.

- The blue value is the Z coordinate, which is `-20882616` in this example.

- The green value is the Y coordinate, which is `831` in this example.


Encoded as follows:

```
((x & 0x3FFFFFF) << 38) | ((z & 0x3FFFFFF) << 12) | (y & 0xFFF)
```

And decoded as:

```
val = read_long();
x = val >> 38;
y = val << 52 >> 52;
z = val << 26 >> 38;
```

Note: The above assumes that the right shift operator sign extends the value (this is called an [arithmetic shift](https://en.wikipedia.org/wiki/arithmetic_shift "wikipedia:arithmetic shift")), so that the signedness of the coordinates is preserved. In many languages, this requires the integer type of `val` to be signed. In the absence of such an operator, the following may be useful:

```
if x >= 1 << 25 { x -= 1 << 26 }
if y >= 1 << 11 { y -= 1 << 12 }
if z >= 1 << 25 { z -= 1 << 26 }
```

### Fixed-point numbers

Some fields may be stored as [fixed-point numbers](https://en.wikipedia.org/wiki/Fixed-point_arithmetic "wikipedia:Fixed-point arithmetic"), where a certain number of bits represent the signed integer part (number to the left of the decimal point) and the rest represent the fractional part (to the right). Floating point numbers (float and double), in contrast, keep the number itself (mantissa) in one chunk, while the location of the decimal point (exponent) is stored beside it. Essentially, while fixed-point numbers have lower range than floating point numbers, their fractional precision is greater for higher values.

Prior to version 1.9 a fixed-point format with 5 fraction bits and 27 integer bits was used to send entity positions to the client. Some uses of fixed point remain in modern versions, but they differ from that format.

Most programming languages lack support for fractional integers directly, but you can represent them as integers. The following C or Java-like pseudocode converts a double to a fixed-point integer with n fraction bits:

```
 x_fixed = (int)(x_double * (1 << n));
```

And back again:

```
 x_double = (double)x_fixed / (1 << n);
```

### Arrays

The types [Array](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Array) and [Prefixed Array](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Prefixed_Array) represent a collection of X in a specified order.

#### Array

Represents a list where the length is not encoded. The length must be known from the context. If the array is empty nothing will be encoded.

A [String](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:String) Array with the values \["Hello", "World!"\] has the following data when encoded:

| Field Name | Field Type | Value |
| --- | --- | --- |
| First element | [String](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:String) | Hello |
| Second element | [String](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:String) | World! |

#### Prefixed Array

Represents an array prefixed by its length. If the array is empty the length will still be encoded.

| Field Name | Field Type |
| --- | --- |
| Length | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) |
| Data | [Array](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Array) of X |

### Bit sets

The types [BitSet](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:BitSet) and [Fixed BitSet](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Fixed_BitSet) represent packed lists of bits. The vanilla implementation uses Java's [`BitSet`](https://docs.oracle.com/javase/8/docs/api/java/util/BitSet.html) class.

#### BitSet

Bit sets of type BitSet are prefixed by their length in longs.

| Field Name | Field Type | Meaning |
| --- | --- | --- |
| Length | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) | Number of longs in the following array. May be 0 (if no bits are set). |
| Data | [Array](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Array) of [Long](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Long) | A packed representation of the bit set as created by [`BitSet.toLongArray`](https://docs.oracle.com/javase/8/docs/api/java/util/BitSet.html#toLongArray--). |

The ith bit is set when `(Data[i / 64] & (1 << (i % 64))) != 0`, where i starts at 0.

#### Fixed BitSet

Bit sets of type Fixed BitSet (n) have a fixed length of n bits, encoded as `ceil(n / 8)` bytes. Note that this is different from BitSet, which uses longs.

| Field Name | Field Type | Meaning |
| --- | --- | --- |
| Data | [Byte Array](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Byte_Array) (n) | A packed representation of the bit set as created by [`BitSet.toByteArray`](https://docs.oracle.com/javase/8/docs/api/java/util/BitSet.html#toByteArray--), padded with zeroes at the end to fit the specified length. |

The ith bit is set when `(Data[i / 8] & (1 << (i % 8))) != 0`, where i starts at 0. This encoding is _not_ equivalent to the long array in BitSet.

### Registry references

#### ID or X

Represents a data record of type X, either inline, or by reference to a registry implied by context.

| Field Name | Field Type | Meaning |
| --- | --- | --- |
| ID | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) | 0 if value of type X is given inline; otherwise registry ID + 1. |
| Value | [Optional](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Optional) X | Only present if ID is 0. |

#### ID Set

Represents a set of IDs in a certain registry (implied by context), either directly (enumerated IDs) or indirectly (tag name).

| Field Name | Field Type | Meaning |
| --- | --- | --- |
| Type | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) | Value used to determine the data that follows. It can be either:<br>- 0 - Represents a named set of IDs defined by a tag.<br>- Anything else - Represents an ad-hoc set of IDs enumerated inline. |
| Tag Name | [Optional](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Optional) [Identifier](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Identifier) | The registry tag defining the ID set. Only present if Type is 0. |
| IDs | [Optional](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Optional) [Array](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Array) of [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) | An array of registry IDs. Only present if Type is not 0.<br>The size of the array is equal to `Type - 1`. |

### Inline data

These types are commonly used in conjuction with [ID or](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:ID_or) X to specify custom data inline.

#### Sound Event

Describes a sound that can be played.

| Name | Type | Description |
| --- | --- | --- |
| Sound Name | [Identifier](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Identifier) |  |
| Has Fixed Range | [Boolean](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Boolean) | Whether this sound has a fixed range, as opposed to a variable volume based on distance. |
| Fixed Range | [Optional](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Optional) [Float](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Float) | The maximum range of the sound. Only present if Has Fixed Range is true. |

#### Chat Type

Describes a direct chat type that a message can be sent with.

| Name | Type | Description |
| --- | --- | --- |
| Chat | (See below) |  |
| Narration | (See below) |  |

The chat type decorations look like:

| Name | Type | Description |
| --- | --- | --- |
| Translation Key | [String](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:String) |  |
| Parameters | [Prefixed Array](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Prefixed_Array) of [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) [Enum](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Enum) | 0: sender, 1: target, 2: content |
| Style | [NBT](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:NBT) |  |

### Teleport Flags

A bit field represented as an [Int](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Int), specifying how a teleportation is to be applied on each axis.

In the lower 8 bits of the bit field, a set bit means the teleportation on the corresponding axis is relative, and an unset bit that it is absolute.

| Hex Mask | Field |
| --- | --- |
| 0x0001 | Relative X |
| 0x0002 | Relative Y |
| 0x0004 | Relative Z |
| 0x0008 | Relative Yaw |
| 0x0010 | Relative Pitch |
| 0x0020 | Relative Velocity X |
| 0x0040 | Relative Velocity Y |
| 0x0080 | Relative Velocity Z |
| 0x0100 | Rotate velocity according to the change in rotation, _before_ applying the velocity change in this packet. Combining this with absolute rotation works as expected—the difference in rotation is still used. |

### Light Data

| Field Name | Field Type | Notes |
| --- | --- | --- |
| Sky Light Mask | [BitSet](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:BitSet) | BitSet containing bits for each section in the world + 2. Each set bit indicates that the corresponding 16×16×16 chunk section has data in the Sky Light array below. The least significant bit is for blocks 16 blocks to 1 block below the min world height (one section below the world), while the most significant bit covers blocks 1 to 16 blocks above the max world height (one section above the world). |
| Block Light Mask | [BitSet](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:BitSet) | BitSet containing bits for each section in the world + 2. Each set bit indicates that the corresponding 16×16×16 chunk section has data in the Block Light array below. The order of bits is the same as in Sky Light Mask. |
| Empty Sky Light Mask | [BitSet](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:BitSet) | BitSet containing bits for each section in the world + 2. Each set bit indicates that the corresponding 16×16×16 chunk section has all zeros for its Sky Light data. The order of bits is the same as in Sky Light Mask. |
| Empty Block Light Mask | [BitSet](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:BitSet) | BitSet containing bits for each section in the world + 2. Each set bit indicates that the corresponding 16×16×16 chunk section has all zeros for its Block Light data. The order of bits is the same as in Sky Light Mask. |
| Sky Light arrays | Sky Light array | [Prefixed Array](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Prefixed_Array) | [Prefixed Array](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Prefixed_Array) (2048) of [Byte](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Byte) | The length of any inner array is always 2048; There is 1 array for each bit set to true in the sky light mask, starting with the lowest value. Half a byte per light value. |
| Block Light arrays | Block Light array | [Prefixed Array](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Prefixed_Array) | [Prefixed Array](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Prefixed_Array) (2048) of [Byte](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Byte) | The length of any inner array is always 2048; There is 1 array for each bit set to true in the block light mask, starting with the lowest value. Half a byte per light value. |

### Game Profile

Describes a Minecraft player profile.

| Name | Type | Description |
| --- | --- | --- |
| UUID | [UUID](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:UUID) |  |
| Username | [String](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:String) (16) |  |
| Properties | Name | [Prefixed Array](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Prefixed_Array) (16) | [String](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:String) (64) |  |
| Value | [String](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:String) (32767) |  |
| Signature | [Prefixed Optional](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Prefixed_Optional) [String](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:String) (1024) |  |

The Properties field looks like the response of [querying a player's skin and cape](https://minecraft.wiki/w/Mojang_API#Query_player's_skin_and_cape "Mojang API") from Mojang's official API, with the difference being the usage of the protocol format instead of JSON. That is, each player will usually have one property with Name being “textures” and Value being a JSON string encoded using Base64. An empty properties array is also acceptable, and will cause clients to display the player with one of the default skins depending on their UUID. For more information, refer to the aforementioned Mojang API page.

### Resolvable Profile

| Name | Type | Meaning |
| --- | --- | --- |
| Profile Kind | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) [Enum](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Enum) | Defines how the next field is read; either partial or complete. |
| Unpack | Varies | | Profile Kind | Name | Type | Description |
| --- | --- | --- | --- |
| 0 | Partial | Username | [Prefixed Optional](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Prefixed_Optional) [String](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:String) (16) |  |
| UUID | [Prefixed Optional](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Prefixed_Optional) [UUID](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:UUID) |  |
| Properties | Name | [Prefixed Array](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Prefixed_Array) (16) | [String](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:String) (64) |  |
| Value | [String](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:String) (32767) |  |
| Signature | [Prefixed Optional](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Prefixed_Optional) [String](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:String) (1024) |  |
| 1 | Complete | [Game Profile](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Game_Profile) |  | |
| Body | [Prefixed Optional](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Prefixed_Optional) [Identifier](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Identifier) | An override for the skin texture to use, from the player's `textures` directory. |
| Cape | [Prefixed Optional](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Prefixed_Optional) [Identifier](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Identifier) | An override for the cape texture to use, same format as body. |
| Elytra | [Prefixed Optional](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Prefixed_Optional) [Identifier](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Identifier) | An override for the elytra texture to use, same format as body. |
| Model | [Prefixed Optional](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Prefixed_Optional) [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) | WIDE = 0, SLIM = 1 |

### Debug subscriptions

Types used in certain packets that are meant to help with debugging the game.

#### Debug Subscription Event

| Name | Type | Description |
| --- | --- | --- |
| Debug subscription type | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) [Enum](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Enum) | ID of the debug subscription type for the next field. |
| Data | [Debug Subscription Data](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Debug_Subscription_Data) | Value of the debug subscription. |

#### Debug Subscription Update

| Name | Type | Description |
| --- | --- | --- |
| Subscription type | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) [Enum](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Enum) | ID of the debug subscription type for the next field. |
| Data | [Prefixed Optional](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Prefixed_Optional) [Debug Subscription Data](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Debug_Subscription_Data) | Value of the debug subscription. |

#### Debug Subscription Data

| Subscription Type | Field Name | Field Type | Meaning |
| --- | --- | --- | --- |
| 0: Dedicated server tick time | _no fields_ |
| 1: Bee | Hive position | [Prefixed Optional](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Prefixed_Optional) [Position](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Position) |  |
| Flower position | [Prefixed Optional](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Prefixed_Optional) [Position](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Position) |  |
| Travel ticks | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) |  |
| Blacklisted hives | [Prefixed Array](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Prefixed_Array) of [Position](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Position) |  |
| 2: Villager brain | Name | [String](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:String) |  |
| Profession | [String](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:String) |  |
| XP | [Int](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Int) |  |
| Health | [Float](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Float) |  |
| Max health | [Float](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Float) |  |
| Inventory | [String](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:String) |  |
| Wants golem | [Boolean](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Boolean) |  |
| Anger level | [Int](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Int) |  |
| Activities | [Prefixed Array](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Prefixed_Array) of [String](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:String) |  |
| Behaviors | [Prefixed Array](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Prefixed_Array) of [String](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:String) |  |
| Memories | [Prefixed Array](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Prefixed_Array) of [String](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:String) |  |
| Gossips | [Prefixed Array](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Prefixed_Array) of [String](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:String) |  |
| POIs | [Prefixed Array](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Prefixed_Array) of [Position](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Position) |  |
| Potential POIs | [Prefixed Array](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Prefixed_Array) of [Position](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Position) |  |
| 3: Breeze | Attack target | [Prefixed Optional](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Prefixed_Optional) [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) |  |
| Jump target | [Prefixed Optional](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Prefixed_Optional) [Position](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Position) |  |
| 4: Goal selector | Priority | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) |  |
| Is running | [Boolean](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Boolean) |  |
| Name | [String](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:String) (255) |  |
| 5: Entity path | Reached | [Boolean](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Boolean) |  |
| Next block index | [Int](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Int) |  |
| Block position | [Position](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Position) |  |
| Nodes | [Prefixed Array](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Prefixed_Array) of [Debug Path Node](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Debug_Path_Node) |  |
| Target nodes | [Prefixed Array](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Prefixed_Array) of [Debug Path Node](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Debug_Path_Node) |  |
| Open set | [Prefixed Array](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Prefixed_Array) of [Debug Path Node](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Debug_Path_Node) |  |
| Closed set | [Prefixed Array](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Prefixed_Array) of [Debug Path Node](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Debug_Path_Node) |  |
| Max node distance | [Float](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Float) |  |
| 6: Entity block intersection | ID | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) [Enum](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Enum) | IN\_BLOCK = 0, IN\_FLUID = 1, IN\_AIR = 2 |
| 7: Bee hive | Type | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) [Enum](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Enum) | ID in the `minecraft:block` registry. |
| Occupant count | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) |  |
| Honey level | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) |  |
| Sedated | [Boolean](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Boolean) |  |
| 8: POI | Position | [Position](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Position) |  |
| Type | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) [Enum](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Enum) | ID in the `minecraft:point_of_interest_type` registry. |
| Free ticket count | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) |  |
| 9: Redstone wire orientation | ID | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) |  |
| 10: Village section | _no fields_ |
| 11: Raid | Positions | [Prefixed Array](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Prefixed_Array) of [Position](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Position) |  |
| 12: Structure | Structures | [Prefixed Array](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Prefixed_Array) of [Debug Structure Info](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Debug_Structure_Info) |  |
| 13: Game event listener | Listener radius | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) |  |
| 14: Neighbor update | Position | [Position](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Position) |  |
| 15: Game event | Event | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) [Enum](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Enum) | ID in the `minecraft:game_event` registry. |
| X | [Double](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Double) |
| Y | [Double](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Double) |
| Z | [Double](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Double) |

#### Debug Path Node

| Field name | Field type | Meaning |
| --- | --- | --- |
| X | [Int](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Int) |  |
| Y | [Int](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Int) |  |
| Z | [Int](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Int) |  |
| Walked distance | [Float](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Float) |  |
| Cost malus | [Float](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Float) |  |
| Closed | [Boolean](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Boolean) |  |
| Type | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) [Enum](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Enum) | BLOCKED = 0, OPEN = 1, WALKABLE = 2, WALKABLE\_DOOR = 3, TRAPDOOR = 4, POWDER\_SNOW = 5, DANGER\_POWDER\_SNOW = 6, FENCE = 7, LAVA = 8, WATER = 9, WATER\_BORDER = 10, RAIL = 11, UNPASSABLE\_RAIL = 12, DANGER\_FIRE = 13, DAMAGE\_FIRE = 14, DANGER\_OTHER = 15, DAMAGE\_OTHER = 16, DOOR\_OPEN = 17, DOOR\_WOOD\_CLOSED = 18, DOOR\_IRON\_CLOSED = 19, BREACH = 20, LEAVES = 21, STICKY\_HONEY = 22, COCOA = 23, DAMAGE\_CAUTIOUS = 24, DANGER\_TRAPDOOR = 25 |
| F | [Float](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Float) |  |

#### Debug Structure Info

| Field name | Field type | Meaning |
| --- | --- | --- |
| Bounding box min | [Position](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Position) |  |
| Bounding box max | [Position](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Position) |  |
| Pieces | Piece bounding box min | [Prefixed Array](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Prefixed_Array) | [Position](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Position) |  |
| Piece bounding box max | [Position](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Position) |  |
| Is start | [Boolean](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Boolean) |  |

### Other definitions

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=3&veaction=edit "Edit section: Other definitions") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=3 "Edit section's source code: Other definitions")\]

| Term | Definition |
| --- | --- |
| Player | When used in the singular, Player always refers to the client connected to the server. |
| Entity | Entity refers to any item, player, mob, minecart or boat etc. See [the Minecraft Wiki article](https://minecraft.wiki/w/Entity "Entity") for a full list. |
| EID | An EID — or Entity ID — is a 4-byte sequence used to identify a specific entity. An entity's EID is unique on the entire server. The same entity is not guaranteed to always have the same EID. The EID is set every time an entity appears on a world, so it is recomputed every time the entity changes dimension, gets unloaded and re-loaded, etc. |
| XYZ | In this document, the axis names are the same as those shown in the debug screen (F3). Y points upwards, X points east, and Z points south. |
| Meter | The meter is Minecraft's base unit of length, equal to the length of a vertex of a solid block. The term “block” may be used to mean “meter” or “cubic meter”. |
| Registry | A table describing static, gameplay-related objects of some kind, such as the types of entities, blocks or biomes. The entries of a registry are associated with both namespaced textual identifiers (see [#Identifier](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Identifier)), and signed (positive) 32-bit numeric identifiers. There is also a registry of registries listing all of the registries in the registry system.<br>Some registries, such as biomes and dimensions, can be customized at runtime by the server (see [Java Edition protocol/Registries#Synchronized registries](https://minecraft.wiki/w/Java_Edition_protocol/Registries#Synchronized_registries "Java Edition protocol/Registries")), while others, such as blocks, items and entities, are hardcoded. The contents of the hardcoded registries can be extracted via the built-in [Data Generators](https://minecraft.wiki/w/Minecraft_Wiki:Projects/wiki.vg_merge/Data_Generators "Minecraft Wiki:Projects/wiki.vg merge/Data Generators") system. |
| Block state | Each block in Minecraft has 0 or more properties, which in turn may have any number of possible values. These represent, for example, the orientations of blocks, poweredness states of redstone components, and so on. Each of the possible permutations of property values for a block is a distinct block state. The [global block state palette](https://minecraft.wiki/w/Java_Edition_protocol/Chunk_format#Global_block_state_palette "Java Edition protocol/Chunk format") assigns a numeric identifier to every block state of every block.<br>A current list of properties and state ID ranges is found on [burger](https://pokechu22.github.io/Burger/26.3.html).<br>Alternatively, the vanilla server now includes an option to export the current block state ID mapping by running `java -DbundlerMainClass=net.minecraft.data.Main -jar minecraft_server.jar --reports`. See [Data Generators](https://minecraft.wiki/w/Minecraft_Wiki:Projects/wiki.vg_merge/Data_Generators "Minecraft Wiki:Projects/wiki.vg merge/Data Generators") for more information. |
| Vanilla | The official implementation of Minecraft as developed and released by Mojang. |
| Sequence | The action number counter for local block changes, incremented by one when using [![](https://minecraft.wiki/images/Left_mouse_button.png?485a7)](https://minecraft.wiki/w/File:Left_mouse_button.png) Left Mouse Button on a block with a hand, using [![](https://minecraft.wiki/images/Right_mouse_button.png?cd132)](https://minecraft.wiki/w/File:Right_mouse_button.png) Right Mouse Button with an item, or starting or finishing digging a block. Counter handles latency to avoid applying outdated block changes to the local world. It is also used to revert ghost blocks created when placing blocks, using buckets, or breaking blocks. |

## Packet format

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=4&veaction=edit "Edit section: Packet format") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=4 "Edit section's source code: Packet format")\]

Packets cannot be larger than 221 − 1 or 2097151 bytes (the maximum that can be sent in a 3-byte [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt)). Moreover, the length field must not be longer than 3 bytes, even if the encoded value is within the limit. Unnecessarily long encodings at 3 bytes or below are still allowed. For compressed packets, this applies to the Packet Length field, i.e. the compressed length.

### Without compression

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=5&veaction=edit "Edit section: Without compression") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=5 "Edit section's source code: Without compression")\]

| Field Name | Field Type | Notes |
| --- | --- | --- |
| Length | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) | Length of Packet ID + Data |
| Packet ID | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) | Corresponds to `protocol_id` from [the server's packet report](https://minecraft.wiki/w/Minecraft_Wiki:Projects/wiki.vg_merge/Data_Generators#Packets_report "Minecraft Wiki:Projects/wiki.vg merge/Data Generators") |
| Data | [Byte Array](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Byte_Array) | Depends on the connection state and packet ID, see the sections below |

### With compression

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=6&veaction=edit "Edit section: With compression") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=6 "Edit section's source code: With compression")\]

Once a [Set Compression](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Set_Compression) packet (with a non-negative threshold) is sent, [zlib](https://en.wikipedia.org/wiki/Zlib "wikipedia:Zlib") compression is enabled for all following packets. The format of a packet changes slightly to include the size of the uncompressed packet.

| Present? | Compressed? | Field Name | Field Type | Notes |
| --- | --- | --- | --- | --- |
| always | No | Packet Length | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) | Length of (Data Length) + length of compressed (Packet ID + Data) |
| if size >= threshold | No | Data Length | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) | Length of uncompressed (Packet ID + Data) |
| Yes | Packet ID | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) | zlib compressed packet ID (see the sections below) |
| Data | [Byte Array](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Byte_Array) | zlib compressed packet data (see the sections below) |
| if size < threshold | No | Data Length | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) | 0 to indicate uncompressed |
| Packet ID | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) | packet ID (see the sections below) |
| Data | [Byte Array](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Byte_Array) | packet data (see the sections below) |

For serverbound packets, the uncompressed length of (Packet ID + Data) must not be greater than 223 or 8388608 bytes. Note that a length equal to 223 is permitted, which differs from the compressed length limit. The vanilla client, on the other hand, has no limit for the uncompressed length of incoming compressed packets.

If the size of the buffer containing the packet data and ID (as a [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt)) is smaller than the threshold specified in the packet [Set Compression](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Set_Compression). It will be sent as uncompressed. This is done by setting the data length to 0. (Comparable to sending a non-compressed format with an extra 0 between the length and packet data).

If it's larger than or equal to the threshold, then it follows the regular compressed protocol format.

The vanilla server (but not client) rejects compressed packets smaller than the threshold. Uncompressed packets exceeding the threshold, however, are accepted.

Compression can be disabled by sending the packet [Set Compression](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Set_Compression) with a negative Threshold, or not sending the Set Compression packet at all.

## List of packets

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=7&veaction=edit "Edit section: List of packets") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=7 "Edit section's source code: List of packets")\]

**Note:** The packet IDs listed here are valid only for the protocol version documented on this page, currently 777. The IDs tend to move around as packets are added and removed, so hardcoding them is highly discouraged. A list of packet IDs and corresponding official names for any version since 1.21 (protocol 767) can be obtained from the built-in [data generators](https://minecraft.wiki/w/Minecraft_Wiki:Projects/wiki.vg_merge/Data_Generators "Minecraft Wiki:Projects/wiki.vg merge/Data Generators").

### Handshaking

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=8&veaction=edit "Edit section: Handshaking") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=8 "Edit section's source code: Handshaking")\]

| \[hide\]Handshaking serverbound packets |
| --- |
| ID | ID (hex) | Packet name | Official name |
| 0 | 0x0 | [Handshake](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Handshake) | `intention` |

### Status

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=9&veaction=edit "Edit section: Status") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=9 "Edit section's source code: Status")\]

| \[hide\]Status clientbound packets |
| --- |
| ID | ID (hex) | Packet name | Official name |
| 0 | 0x0 | [Status Response](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Status_Response) | `status_response` |
| 1 | 0x1 | [Pong Response (status)](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Pong_Response_(status)) | `pong_response` |

| \[hide\]Status serverbound packets |
| --- |
| ID | ID (hex) | Packet name | Official name |
| 0 | 0x0 | [Status Request](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Status_Request) | `status_request` |
| 1 | 0x1 | [Ping Request (status)](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Ping_Request_(status)) | `ping_request` |

### Login

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=10&veaction=edit "Edit section: Login") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=10 "Edit section's source code: Login")\]

| \[hide\]Login clientbound packets |
| --- |
| ID | ID (hex) | Packet name | Official name |
| 0 | 0x0 | [Disconnect (login)](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Disconnect_(login)) | `login_disconnect` |
| 1 | 0x1 | [Encryption Request](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Encryption_Request) | `hello` |
| 2 | 0x2 | [Login Success](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Login_Success) | `login_finished` |
| 3 | 0x3 | [Set Compression](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Set_Compression) | `login_compression` |
| 4 | 0x4 | [Login Plugin Request](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Login_Plugin_Request) | `custom_query` |
| 5 | 0x5 | [Cookie Request](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Cookie_Request) | `cookie_request` |

| \[hide\]Login serverbound packets |
| --- |
| ID | ID (hex) | Packet name | Official name |
| 0 | 0x0 | [Login Start](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Login_Start) | `hello` |
| 1 | 0x1 | [Encryption Response](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Encryption_Response) | `key` |
| 2 | 0x2 | [Login Plugin Response](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Login_Plugin_Response) | `custom_query_answer` |
| 3 | 0x3 | [Login Acknowledged](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Login_Acknowledged) | `login_acknowledged` |
| 4 | 0x4 | [Cookie Response](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Cookie_Response) | `cookie_response` |

### Configuration

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=11&veaction=edit "Edit section: Configuration") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=11 "Edit section's source code: Configuration")\]

| \[hide\]Configuration clientbound packets |
| --- |
| ID | ID (hex) | Packet name | Official name |
| 0 | 0x0 | [Cookie Request](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Cookie_Request) | `cookie_request` |
| 1 | 0x1 | [Plugin Message (clientbound)](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Plugin_Message_(clientbound)) | `custom_payload` |
| 2 | 0x2 | [Disconnect](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Disconnect) | `disconnect` |
| 3 | 0x3 | [Finish Configuration](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Finish_Configuration) | `finish_configuration` |
| 4 | 0x4 | [Keep Alive (clientbound)](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Keep_Alive_(clientbound)) | `keep_alive` |
| 5 | 0x5 | [Ping](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Ping) | `ping` |
| 6 | 0x6 | [Reset Chat](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Reset_Chat) | `reset_chat` |
| 7 | 0x7 | [Registry Data](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Registry_Data) | `registry_data` |
| 8 | 0x8 | [Remove Resource Pack](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Remove_Resource_Pack) | `resource_pack_pop` |
| 9 | 0x9 | [Add Resource Pack](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Add_Resource_Pack) | `resource_pack_push` |
| 10 | 0xA | [Post Effects](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Post_Effects) | `post_effects` |
| 11 | 0xB | [Store Cookie](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Store_Cookie) | `store_cookie` |
| 12 | 0xC | [Transfer](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Transfer) | `transfer` |
| 13 | 0xD | [Feature Flags](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Feature_Flags) | `update_enabled_features` |
| 14 | 0xE | [Update Tags](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Update_Tags) | `update_tags` |
| 15 | 0xF | [Known Packs (clientbound)](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Known_Packs_(clientbound)) | `select_known_packs` |
| 16 | 0x10 | [Custom Report Details](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Custom_Report_Details) | `custom_report_details` |
| 17 | 0x11 | [Server Links](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Server_Links) | `server_links` |
| 18 | 0x12 | [Clear Dialog](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Clear_Dialog) | `clear_dialog` |
| 19 | 0x13 | [Show Dialog (configuration)](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Show_Dialog_(configuration)) | `show_dialog` |
| 20 | 0x14 | [Code of Conduct](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Code_of_Conduct) | `code_of_conduct` |

| \[hide\]Configuration serverbound packets |
| --- |
| ID | ID (hex) | Packet name | Official name |
| 0 | 0x0 | [Client Information](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Client_Information) | `client_information` |
| 1 | 0x1 | [Cookie Response](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Cookie_Response) | `cookie_response` |
| 2 | 0x2 | [Plugin Message (serverbound)](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Plugin_Message_(serverbound)) | `custom_payload` |
| 3 | 0x3 | [Acknowledge Finish Configuration](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Acknowledge_Finish_Configuration) | `finish_configuration` |
| 4 | 0x4 | [Keep Alive (serverbound)](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Keep_Alive_(serverbound)) | `keep_alive` |
| 5 | 0x5 | [Pong](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Pong) | `pong` |
| 6 | 0x6 | [Resource Pack Response](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Resource_Pack_Response) | `resource_pack` |
| 7 | 0x7 | [Known Packs (serverbound)](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Known_Packs_(serverbound)) | `select_known_packs` |
| 8 | 0x8 | [Custom Click Action](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Custom_Click_Action) | `custom_click_action` |
| 9 | 0x9 | [Accept Code of Conduct](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Accept_Code_of_Conduct) | `accept_code_of_conduct` |

### Play

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=12&veaction=edit "Edit section: Play") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=12 "Edit section's source code: Play")\]

| \[hide\]Play clientbound packets |
| --- |
| ID | ID (hex) | Packet name | Official name |
| 0 | 0x0 | [Bundle Delimiter](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Bundle_Delimiter) | `bundle_delimiter` |
| 1 | 0x1 | [Spawn Entity](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Spawn_Entity) | `add_entity` |
| 2 | 0x2 | [Entity Animation](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Entity_Animation) | `animate` |
| 3 | 0x3 | [Award Statistics](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Award_Statistics) | `award_stats` |
| 4 | 0x4 | [Acknowledge Block Change](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Acknowledge_Block_Change) | `block_changed_ack` |
| 5 | 0x5 | [Set Block Destroy Stage](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Set_Block_Destroy_Stage) | `block_destruction` |
| 6 | 0x6 | [Block Entity Data](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Block_Entity_Data) | `block_entity_data` |
| 7 | 0x7 | [Block Action](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Block_Action) | `block_event` |
| 8 | 0x8 | [Block Update](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Block_Update) | `block_update` |
| 9 | 0x9 | [Boss Bar](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Boss_Bar) | `boss_event` |
| 10 | 0xA | [Change Difficulty](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Change_Difficulty) | `change_difficulty` |
| 11 | 0xB | [Chunk Batch Finished](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Chunk_Batch_Finished) | `chunk_batch_finished` |
| 12 | 0xC | [Chunk Batch Start](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Chunk_Batch_Start) | `chunk_batch_start` |
| 13 | 0xD | [Chunk Biomes](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Chunk_Biomes) | `chunks_biomes` |
| 14 | 0xE | [Clear Titles](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Clear_Titles) | `clear_titles` |
| 15 | 0xF | [Command Suggestions Response](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Command_Suggestions_Response) | `command_suggestions` |
| 16 | 0x10 | [Commands](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Commands) | `commands` |
| 17 | 0x11 | [Close Container](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Close_Container) | `container_close` |
| 18 | 0x12 | [Set Container Content](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Set_Container_Content) | `container_set_content` |
| 19 | 0x13 | [Set Container Property](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Set_Container_Property) | `container_set_data` |
| 20 | 0x14 | [Set Container Slot](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Set_Container_Slot) | `container_set_slot` |
| 21 | 0x15 | [Cookie Request](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Cookie_Request) | `cookie_request` |
| 22 | 0x16 | [Set Cooldown](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Set_Cooldown) | `cooldown` |
| 23 | 0x17 | [Chat Suggestions](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Chat_Suggestions) | `custom_chat_completions` |
| 24 | 0x18 | [Plugin Message (clientbound)](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Plugin_Message_(clientbound)) | `custom_payload` |
| 25 | 0x19 | [Damage Event](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Damage_Event) | `damage_event` |
| 26 | 0x1A | [Debug Block Value](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Debug_Block_Value) | `debug_block_value` |
| 27 | 0x1B | [Debug Chunk Value](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Debug_Chunk_Value) | `debug_chunk_value` |
| 28 | 0x1C | [Debug Entity Value](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Debug_Entity_Value) | `debug_entity_value` |
| 29 | 0x1D | [Debug Event](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Debug_Event) | `debug_event` |
| 30 | 0x1E | [Debug Sample](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Debug_Sample) | `debug_sample` |
| 31 | 0x1F | [Delete Message](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Delete_Message) | `delete_chat` |
| 32 | 0x20 | [Disconnect](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Disconnect) | `disconnect` |
| 33 | 0x21 | [Disguised Chat Message](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Disguised_Chat_Message) | `disguised_chat` |
| 34 | 0x22 | [Entity Event](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Entity_Event) | `entity_event` |
| 35 | 0x23 | [Teleport Entity](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Teleport_Entity) | `entity_position_sync` |
| 36 | 0x24 | [Explosion](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Explosion) | `explode` |
| 37 | 0x25 | [Add Transient Block](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Add_Transient_Block) | `add_transient_block` |
| 38 | 0x26 | [Unload Chunk](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Unload_Chunk) | `forget_level_chunk` |
| 39 | 0x27 | [Game Event](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Game_Event) | `game_event` |
| 40 | 0x28 | [Game Rule Values](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Game_Rule_Values) | `game_rule_values` |
| 41 | 0x29 | [Game Test Highlight Position](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Game_Test_Highlight_Position) | `game_test_highlight_pos` |
| 42 | 0x2A | [Open Horse Screen](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Open_Horse_Screen) | `mount_screen_open` |
| 43 | 0x2B | [Hurt Animation](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Hurt_Animation) | `hurt_animation` |
| 44 | 0x2C | [Initialize World Border](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Initialize_World_Border) | `initialize_border` |
| 45 | 0x2D | [Keep Alive (clientbound)](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Keep_Alive_(clientbound)) | `keep_alive` |
| 46 | 0x2E | [Chunk Data and Update Light](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Chunk_Data_and_Update_Light) | `level_chunk_with_light` |
| 47 | 0x2F | [World Event](https://minecraft.wiki/w/Java_Edition_protocol/Packets#World_Event) | `level_event` |
| 48 | 0x30 | [Particle](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Particle) | `level_particles` |
| 49 | 0x31 | [Update Light](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Update_Light) | `light_update` |
| 50 | 0x32 | [Login (play)](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Login_(play)) | `login` |
| 51 | 0x33 | [Low Disk Space Warning](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Low_Disk_Space_Warning) | `low_disk_space_warning` |
| 52 | 0x34 | [Map Data](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Map_Data) | `map_item_data` |
| 53 | 0x35 | [Merchant Offers](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Merchant_Offers) | `merchant_offers` |
| 54 | 0x36 | [Update Entity Position](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Update_Entity_Position) | `move_entity_pos` |
| 55 | 0x37 | [Update Entity Position and Rotation](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Update_Entity_Position_and_Rotation) | `move_entity_pos_rot` |
| 56 | 0x38 | [Move Minecart Along Track](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Move_Minecart_Along_Track) | `move_minecart_along_track` |
| 57 | 0x39 | [Update Entity Rotation](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Update_Entity_Rotation) | `move_entity_rot` |
| 58 | 0x3A | [Move Vehicle (clientbound)](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Move_Vehicle_(clientbound)) | `move_vehicle` |
| 59 | 0x3B | [Open Book](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Open_Book) | `open_book` |
| 60 | 0x3C | [Open Screen](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Open_Screen) | `open_screen` |
| 61 | 0x3D | [Open Sign Editor](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Open_Sign_Editor) | `open_sign_editor` |
| 62 | 0x3E | [Ping](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Ping) | `ping` |
| 63 | 0x3F | [Ping Response](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Ping_Response) | `pong_response` |
| 64 | 0x40 | [Place Ghost Recipe](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Place_Ghost_Recipe) | `place_ghost_recipe` |
| 65 | 0x41 | [Player Abilities (clientbound)](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Player_Abilities_(clientbound)) | `player_abilities` |
| 66 | 0x42 | [Player Chat Message](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Player_Chat_Message) | `player_chat` |
| 67 | 0x43 | [End Combat](https://minecraft.wiki/w/Java_Edition_protocol/Packets#End_Combat) | `player_combat_end` |
| 68 | 0x44 | [Enter Combat](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Enter_Combat) | `player_combat_enter` |
| 69 | 0x45 | [Combat Death](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Combat_Death) | `player_combat_kill` |
| 70 | 0x46 | [Player Info Remove](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Player_Info_Remove) | `player_info_remove` |
| 71 | 0x47 | [Player Info Update](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Player_Info_Update) | `player_info_update` |
| 72 | 0x48 | [Look At](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Look_At) | `player_look_at` |
| 73 | 0x49 | [Synchronize Player Position](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Synchronize_Player_Position) | `player_position` |
| 74 | 0x4A | [Player Rotation](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Player_Rotation) | `player_rotation` |
| 75 | 0x4B | [Recipe Book Add](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Recipe_Book_Add) | `recipe_book_add` |
| 76 | 0x4C | [Recipe Book Remove](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Recipe_Book_Remove) | `recipe_book_remove` |
| 77 | 0x4D | [Recipe Book Settings](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Recipe_Book_Settings) | `recipe_book_settings` |
| 78 | 0x4E | [Remove Entities](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Remove_Entities) | `remove_entities` |
| 79 | 0x4F | [Remove Entity Effect](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Remove_Entity_Effect) | `remove_mob_effect` |
| 80 | 0x50 | [Reset Score](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Reset_Score) | `reset_score` |
| 81 | 0x51 | [Remove Resource Pack](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Remove_Resource_Pack) | `resource_pack_pop` |
| 82 | 0x52 | [Add Resource Pack](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Add_Resource_Pack) | `resource_pack_push` |
| 83 | 0x53 | [Post Effects](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Post_Effects) | `post_effects` |
| 84 | 0x54 | [Respawn](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Respawn) | `respawn` |
| 85 | 0x55 | [Set Head Rotation](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Set_Head_Rotation) | `rotate_head` |
| 86 | 0x56 | [Update Section Blocks](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Update_Section_Blocks) | `section_blocks_update` |
| 87 | 0x57 | [Select Advancements Tab](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Select_Advancements_Tab) | `select_advancements_tab` |
| 88 | 0x58 | [Server Data](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Server_Data) | `server_data` |
| 89 | 0x59 | [Set Action Bar Text](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Set_Action_Bar_Text) | `set_action_bar_text` |
| 90 | 0x5A | [Set Border Center](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Set_Border_Center) | `set_border_center` |
| 91 | 0x5B | [Set Border Lerp Size](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Set_Border_Lerp_Size) | `set_border_lerp_size` |
| 92 | 0x5C | [Set Border Size](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Set_Border_Size) | `set_border_size` |
| 93 | 0x5D | [Set Border Warning Delay](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Set_Border_Warning_Delay) | `set_border_warning_delay` |
| 94 | 0x5E | [Set Border Warning Distance](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Set_Border_Warning_Distance) | `set_border_warning_distance` |
| 95 | 0x5F | [Set Camera](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Set_Camera) | `set_camera` |
| 96 | 0x60 | [Set Center Chunk](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Set_Center_Chunk) | `set_chunk_cache_center` |
| 97 | 0x61 | [Set Render Distance](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Set_Render_Distance) | `set_chunk_cache_radius` |
| 98 | 0x62 | [Set Cursor Item](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Set_Cursor_Item) | `set_cursor_item` |
| 99 | 0x63 | [Set Default Spawn Position](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Set_Default_Spawn_Position) | `set_default_spawn_position` |
| 100 | 0x64 | [Display Objective](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Display_Objective) | `set_display_objective` |
| 101 | 0x65 | [Set Entity Metadata](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Set_Entity_Metadata) | `set_entity_data` |
| 102 | 0x66 | [Link Entities](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Link_Entities) | `set_entity_link` |
| 103 | 0x67 | [Set Entity Velocity](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Set_Entity_Velocity) | `set_entity_motion` |
| 104 | 0x68 | [Set Equipment](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Set_Equipment) | `set_equipment` |
| 105 | 0x69 | [Set Experience](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Set_Experience) | `set_experience` |
| 106 | 0x6A | [Set Health](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Set_Health) | `set_health` |
| 107 | 0x6B | [Set Held Item (clientbound)](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Set_Held_Item_(clientbound)) | `set_held_slot` |
| 108 | 0x6C | [Update Objectives](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Update_Objectives) | `set_objective` |
| 109 | 0x6D | [Set Passengers](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Set_Passengers) | `set_passengers` |
| 110 | 0x6E | [Set Player Inventory Slot](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Set_Player_Inventory_Slot) | `set_player_inventory` |
| 111 | 0x6F | [Update Teams](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Update_Teams) | `set_player_team` |
| 112 | 0x70 | [Update Score](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Update_Score) | `set_score` |
| 113 | 0x71 | [Set Simulation Distance](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Set_Simulation_Distance) | `set_simulation_distance` |
| 114 | 0x72 | [Set Subtitle Text](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Set_Subtitle_Text) | `set_subtitle_text` |
| 115 | 0x73 | [Update Time](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Update_Time) | `set_time` |
| 116 | 0x74 | [Set Title Text](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Set_Title_Text) | `set_title_text` |
| 117 | 0x75 | [Set Title Animation Times](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Set_Title_Animation_Times) | `set_titles_animation` |
| 118 | 0x76 | [Entity Sound Effect](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Entity_Sound_Effect) | `sound_entity` |
| 119 | 0x77 | [Sound Effect](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Sound_Effect) | `sound` |
| 120 | 0x78 | [Start Configuration](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Start_Configuration) | `start_configuration` |
| 121 | 0x79 | [Stop Sound](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Stop_Sound) | `stop_sound` |
| 122 | 0x7A | [Store Cookie](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Store_Cookie) | `store_cookie` |
| 123 | 0x7B | [Swing Animation](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Swing_Animation) | `swing_animation` |
| 124 | 0x7C | [System Chat Message](https://minecraft.wiki/w/Java_Edition_protocol/Packets#System_Chat_Message) | `system_chat` |
| 125 | 0x7D | [Set Tab List Header And Footer](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Set_Tab_List_Header_And_Footer) | `tab_list` |
| 126 | 0x7E | [Tag Query Response](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Tag_Query_Response) | `tag_query` |
| 127 | 0x7F | [Pickup Item](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Pickup_Item) | `take_item_entity` |
| 128 | 0x80 | [Synchronize Vehicle Position](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Synchronize_Vehicle_Position) | `teleport_entity` |
| 129 | 0x81 | [Test Instance Block Status](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Test_Instance_Block_Status) | `test_instance_block_status` |
| 130 | 0x82 | [Set Ticking State](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Set_Ticking_State) | `ticking_state` |
| 131 | 0x83 | [Step Tick](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Step_Tick) | `ticking_step` |
| 132 | 0x84 | [Transfer](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Transfer) | `transfer` |
| 133 | 0x85 | [Update Advancements](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Update_Advancements) | `update_advancements` |
| 134 | 0x86 | [Update Attributes](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Update_Attributes) | `update_attributes` |
| 135 | 0x87 | [Entity Effect](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Entity_Effect) | `update_mob_effect` |
| 136 | 0x88 | [Update Recipes](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Update_Recipes) | `update_recipes` |
| 137 | 0x89 | [Update Tags](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Update_Tags) | `update_tags` |
| 138 | 0x8A | [Projectile Power](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Projectile_Power) | `projectile_power` |
| 139 | 0x8B | [Custom Report Details](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Custom_Report_Details) | `custom_report_details` |
| 140 | 0x8C | [Server Links](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Server_Links) | `server_links` |
| 141 | 0x8D | [Waypoint](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Waypoint) | `waypoint` |
| 142 | 0x8E | [Clear Dialog](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Clear_Dialog) | `clear_dialog` |
| 143 | 0x8F | [Show Dialog (play)](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Show_Dialog_(play)) | `show_dialog` |

| \[hide\]Play serverbound packets |
| --- |
| ID | ID (hex) | Packet name | Official name |
| 0 | 0x0 | [Confirm Teleportation](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Confirm_Teleportation) | `accept_teleportation` |
| 1 | 0x1 | [Attack](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Attack) | `attack` |
| 2 | 0x2 | [Query Block Entity Tag](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Query_Block_Entity_Tag) | `block_entity_tag_query` |
| 3 | 0x3 | [Bundle Item Selected](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Bundle_Item_Selected) | `bundle_item_selected` |
| 4 | 0x4 | [Change Difficulty](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Change_Difficulty) | `change_difficulty` |
| 5 | 0x5 | [Change Game Mode](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Change_Game_Mode) | `change_game_mode` |
| 6 | 0x6 | [Acknowledge Message](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Acknowledge_Message) | `chat_ack` |
| 7 | 0x7 | [Chat Command](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Chat_Command) | `chat_command` |
| 8 | 0x8 | [Signed Chat Command](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Signed_Chat_Command) | `chat_command_signed` |
| 9 | 0x9 | [Chat Message](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Chat_Message) | `chat` |
| 10 | 0xA | [Player Session](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Player_Session) | `chat_session_update` |
| 11 | 0xB | [Chunk Batch Received](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Chunk_Batch_Received) | `chunk_batch_received` |
| 12 | 0xC | [Client Status](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Client_Status) | `client_command` |
| 13 | 0xD | [Client Tick End](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Client_Tick_End) | `client_tick_end` |
| 14 | 0xE | [Client Information](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Client_Information) | `client_information` |
| 15 | 0xF | [Command Suggestions Request](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Command_Suggestions_Request) | `command_suggestion` |
| 16 | 0x10 | [Acknowledge Configuration](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Acknowledge_Configuration) | `configuration_acknowledged` |
| 17 | 0x11 | [Click Container Button](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Click_Container_Button) | `container_button_click` |
| 18 | 0x12 | [Click Container](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Click_Container) | `container_click` |
| 19 | 0x13 | [Close Container](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Close_Container) | `container_close` |
| 20 | 0x14 | [Change Container Slot State](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Change_Container_Slot_State) | `container_slot_state_changed` |
| 21 | 0x15 | [Cookie Response](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Cookie_Response) | `cookie_response` |
| 22 | 0x16 | [Plugin Message (serverbound)](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Plugin_Message_(serverbound)) | `custom_payload` |
| 23 | 0x17 | [Debug Subscription Request](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Debug_Subscription_Request) | `debug_subscription_request` |
| 24 | 0x18 | [Edit Book](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Edit_Book) | `edit_book` |
| 25 | 0x19 | [Query Entity Tag](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Query_Entity_Tag) | `entity_tag_query` |
| 26 | 0x1A | [Interact](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Interact) | `interact` |
| 27 | 0x1B | [Jigsaw Generate](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Jigsaw_Generate) | `jigsaw_generate` |
| 28 | 0x1C | [Keep Alive (serverbound)](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Keep_Alive_(serverbound)) | `keep_alive` |
| 29 | 0x1D | [Lock Difficulty](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Lock_Difficulty) | `lock_difficulty` |
| 30 | 0x1E | [Set Player Position](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Set_Player_Position) | `move_player_pos` |
| 31 | 0x1F | [Set Player Position and Rotation](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Set_Player_Position_and_Rotation) | `move_player_pos_rot` |
| 32 | 0x20 | [Set Player Rotation](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Set_Player_Rotation) | `move_player_rot` |
| 33 | 0x21 | [Set Player Movement Flags](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Set_Player_Movement_Flags) | `move_player_status_only` |
| 34 | 0x22 | [Move Vehicle (serverbound)](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Move_Vehicle_(serverbound)) | `move_vehicle` |
| 35 | 0x23 | [Paddle Boat](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Paddle_Boat) | `paddle_boat` |
| 36 | 0x24 | [Pick Item From Block](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Pick_Item_From_Block) | `pick_item_from_block` |
| 37 | 0x25 | [Pick Item From Entity](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Pick_Item_From_Entity) | `pick_item_from_entity` |
| 38 | 0x26 | [Ping Request](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Ping_Request) | `ping_request` |
| 39 | 0x27 | [Place Recipe](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Place_Recipe) | `place_recipe` |
| 40 | 0x28 | [Player Abilities (serverbound)](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Player_Abilities_(serverbound)) | `player_abilities` |
| 41 | 0x29 | [Player Action](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Player_Action) | `player_action` |
| 42 | 0x2A | [Player Command](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Player_Command) | `player_command` |
| 43 | 0x2B | [Player Input](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Player_Input) | `player_input` |
| 44 | 0x2C | [Player Loaded](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Player_Loaded) | `player_loaded` |
| 45 | 0x2D | [Pong](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Pong) | `pong` |
| 46 | 0x2E | [Punch](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Punch) | `punch` |
| 47 | 0x2F | [Change Recipe Book Settings](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Change_Recipe_Book_Settings) | `recipe_book_change_settings` |
| 48 | 0x30 | [Set Seen Recipe](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Set_Seen_Recipe) | `recipe_book_seen_recipe` |
| 49 | 0x31 | [Rename Item](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Rename_Item) | `rename_item` |
| 50 | 0x32 | [Resource Pack Response](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Resource_Pack_Response) | `resource_pack` |
| 51 | 0x33 | [Seen Advancements](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Seen_Advancements) | `seen_advancements` |
| 52 | 0x34 | [Select Trade](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Select_Trade) | `select_trade` |
| 53 | 0x35 | [Set Beacon Effect](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Set_Beacon_Effect) | `set_beacon` |
| 54 | 0x36 | [Set Held Item (serverbound)](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Set_Held_Item_(serverbound)) | `set_carried_item` |
| 55 | 0x37 | [Program Command Block](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Program_Command_Block) | `set_command_block` |
| 56 | 0x38 | [Program Command Block Minecart](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Program_Command_Block_Minecart) | `set_command_minecart` |
| 57 | 0x39 | [Set Creative Mode Slot](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Set_Creative_Mode_Slot) | `set_creative_mode_slot` |
| 58 | 0x3A | [Set Game Rules](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Set_Game_Rules) | `set_game_rule` |
| 59 | 0x3B | [Program Jigsaw Block](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Program_Jigsaw_Block) | `set_jigsaw_block` |
| 60 | 0x3C | [Program Structure Block](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Program_Structure_Block) | `set_structure_block` |
| 61 | 0x3D | [Set Test Block](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Set_Test_Block) | `set_test_block` |
| 62 | 0x3E | [Update Sign](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Update_Sign) | `sign_update` |
| 63 | 0x3F | [Spectator Action](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Spectator_Action) | `spectator_action` |
| 64 | 0x40 | [Teleport To Entity](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Teleport_To_Entity) | `teleport_to_entity` |
| 65 | 0x41 | [Test Instance Block Action](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Test_Instance_Block_Action) | `test_instance_block_action` |
| 66 | 0x42 | [Use Item On](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Use_Item_On) | `use_item_on` |
| 67 | 0x43 | [Use Item](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Use_Item) | `use_item` |
| 68 | 0x44 | [Custom Click Action](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Custom_Click_Action) | `custom_click_action` |

## Handshaking

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=13&veaction=edit "Edit section: Handshaking") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=13 "Edit section's source code: Handshaking")\]

### Clientbound

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=14&veaction=edit "Edit section: Clientbound") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=14 "Edit section's source code: Clientbound")\]

There are no clientbound packets in the Handshaking state, since the protocol immediately switches to a different state after the client sends the first packet.

### Serverbound

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=15&veaction=edit "Edit section: Serverbound") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=15 "Edit section's source code: Serverbound")\]

#### Handshake

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=16&veaction=edit "Edit section: Handshake") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=16 "Edit section's source code: Handshake")\]

This packet causes the server to switch into the target state. It should be sent right after opening the TCP connection to prevent the server from disconnecting.

| Serverbound `intention`, Handshaking ID: 0 (0x0) |
| --- |
| Field Name | Field Type | Notes |
| Protocol Version | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) | See [protocol version numbers](https://minecraft.wiki/w/Minecraft_Wiki:Projects/wiki.vg_merge/Protocol_version_numbers "Minecraft Wiki:Projects/wiki.vg merge/Protocol version numbers") (currently 777 in Minecraft 26.3). |
| Server Address | [String](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:String) (255) | Hostname or IP, e.g. localhost or 127.0.0.1, that was used to connect. The vanilla server does not use this information. This is the name obtained after [SRV record](https://en.wikipedia.org/wiki/SRV_record "w:SRV record") resolution, except in 1.17 (and no older or newer version) and during server list ping ( [MC-278651](https://bugs.mojang.com/browse/MC-278651)), where it is the host portion of the address specified by the user directly. In 1.17.1 and later if a literal IP address is specified by the user, [reverse DNS lookup](https://en.wikipedia.org/wiki/Reverse_DNS_lookup "w:Reverse DNS lookup") is attempted, and the result is used as the value of this field if successful. |
| Server Port | [Unsigned Short](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Unsigned_Short) | Default is 25565. The vanilla server does not use this information. |
| Intent | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) [Enum](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Enum) | 1 for [Status](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Status), 2 for [Login](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Login), 3 for [Transfer](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Login). Intents 2 and 3 both transition to the Login state, but 3 indicates that the client is connecting due to a [Transfer](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Transfer) packet received from another server. If the server is not expecting transfers, it may choose to reject the connection by replying with a [Disconnect (login)](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Disconnect_(login)) packet. |

#### Legacy Server List Ping

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=17&veaction=edit "Edit section: Legacy Server List Ping") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=17 "Edit section's source code: Legacy Server List Ping")\]

[![](https://minecraft.wiki/images/thumb/Ambox_warning_pn.png/32px-Ambox_warning_pn.png?b6e1c)](https://minecraft.wiki/w/File:Ambox_warning_pn.png "File:Ambox warning pn.png")

This packet uses a nonstandard format. It is never length-prefixed, and the packet ID is an [Unsigned Byte](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Unsigned_Byte) instead of a [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt).

While not technically part of the current protocol, (legacy) clients may send this packet to initiate [Server List Ping](https://minecraft.wiki/w/Java_Edition_protocol/Server_List_Ping "Java Edition protocol/Server List Ping"), and modern servers should handle it correctly.
The format of this packet is a remnant of the pre-Netty age, before the switch to Netty in 1.7 brought the standard format that is recognized now. This packet merely exists to inform legacy clients that they can't join our modern server.

Modern clients (tested with 1.21.5 + 1.21.4) also send this packet when the server does not send any response within a 30 seconds time window or when the connection is immediately closed.

[![](https://minecraft.wiki/images/thumb/Ambox_warning_pn.png/32px-Ambox_warning_pn.png?b6e1c)](https://minecraft.wiki/w/File:Ambox_warning_pn.png "File:Ambox warning pn.png")

The client does not close the connection with the legacy packet on its own!
It only gets closed when the Minecraft client is closed.

| Packet ID | State | Bound To | Field Name | Field Type | Notes |
| --- | --- | --- | --- | --- | --- |
| 0xFE | Handshaking | Server | Payload | [Unsigned Byte](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Unsigned_Byte) | always 1 (`0x01`). |

See [Java Edition protocol/Server List Ping#1.6](https://minecraft.wiki/w/Java_Edition_protocol/Server_List_Ping#1.6 "Java Edition protocol/Server List Ping") for the details of the protocol that follows this packet.

## Status

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=18&veaction=edit "Edit section: Status") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=18 "Edit section's source code: Status")\]

Main article: [Java Edition protocol/Server List Ping](https://minecraft.wiki/w/Java_Edition_protocol/Server_List_Ping "Java Edition protocol/Server List Ping")

### Clientbound

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=19&veaction=edit "Edit section: Clientbound") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=19 "Edit section's source code: Clientbound")\]

#### Status Response

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=20&veaction=edit "Edit section: Status Response") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=20 "Edit section's source code: Status Response")\]

| Clientbound `status_response`, Status ID: 0 (0x0) |
| --- |
| Field Name | Field Type | Notes |
| JSON Response | [String](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:String) (32767) | See [Java Edition protocol/Server List Ping#Status Response](https://minecraft.wiki/w/Java_Edition_protocol/Server_List_Ping#Status_Response "Java Edition protocol/Server List Ping"); as with all strings, this is prefixed by its length as a [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt). |

#### Pong Response (status)

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=21&veaction=edit "Edit section: Pong Response (status)") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=21 "Edit section's source code: Pong Response (status)")\]

| Clientbound `pong_response`, Status ID: 1 (0x1) |
| --- |
| Field Name | Field Type | Notes |
| Timestamp | [Long](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Long) | Should match the one sent by the client. |

### Serverbound

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=22&veaction=edit "Edit section: Serverbound") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=22 "Edit section's source code: Serverbound")\]

#### Status Request

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=23&veaction=edit "Edit section: Status Request") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=23 "Edit section's source code: Status Request")\]

The status can only be requested once, immediately after the handshake, before any ping. The server won't respond otherwise.

| Serverbound `status_request`, Status ID: 0 (0x0) |
| --- |
| Field Name | Field Type | Notes |
| _no fields_ |

#### Ping Request (status)

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=24&veaction=edit "Edit section: Ping Request (status)") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=24 "Edit section's source code: Ping Request (status)")\]

| Serverbound `ping_request`, Status ID: 1 (0x1) |
| --- |
| Field Name | Field Type | Notes |
| Timestamp | [Long](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Long) | May be any number, but vanilla clients will always use the timestamp in milliseconds. |

## Login

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=25&veaction=edit "Edit section: Login") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=25 "Edit section's source code: Login")\]

The login process is as follows:

01. C→S: [Handshake](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Handshake) with intent set to 2 (login) or 3 (transfer)
02. C→S: [Login Start](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Login_Start)
03. S→C: [Encryption Request](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Encryption_Request)
04. Client auth (if enabled)
05. C→S: [Encryption Response](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Encryption_Response)
06. Server auth (if enabled)
07. Both enable encryption
08. S→C: [Set Compression](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Set_Compression) (optional)
09. S→C: [Login Success](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Login_Success)
10. C→S: [Login Acknowledged](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Login_Acknowledged)

Set Compression, if present, must be sent before Login Success. Note that anything sent after Set Compression must use the [Post Compression packet format](https://minecraft.wiki/w/Java_Edition_protocol/Packets#With_compression).

Three modes of operation are possible depending on how the packets are sent:

- Online-mode with encryption
- Offline-mode with encryption
- Offline-mode without encryption

For online-mode servers (the ones with authentication enabled), encryption is always mandatory, and the entire process described above needs to be followed.

For offline-mode servers (the ones with authentication disabled), encryption is optional, and part of the process can be skipped. In that case, [Login Start](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Login_Start) is directly followed by [Login Success](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Login_Success). The vanilla server only uses UUID v3 for offline player UUIDs, deriving it from the string `OfflinePlayer:<player's name>`. For example, Notch’s offline UUID would be chosen from the string `OfflinePlayer:Notch`. This is not a requirement however, the UUID can be set to anything.

As of 1.21, the vanilla server never uses encryption in offline mode.

See [protocol encryption](https://minecraft.wiki/w/Protocol_encryption "Protocol encryption") for details.

### Clientbound

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=26&veaction=edit "Edit section: Clientbound") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=26 "Edit section's source code: Clientbound")\]

#### Disconnect (login)

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=27&veaction=edit "Edit section: Disconnect (login)") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=27 "Edit section's source code: Disconnect (login)")\]

| Clientbound `login_disconnect`, Login ID: 0 (0x0) |
| --- |
| Field Name | Field Type | Notes |
| Reason | [JSON Text Component](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:JSON_Text_Component) | The reason why the player was disconnected. |

#### Encryption Request

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=28&veaction=edit "Edit section: Encryption Request") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=28 "Edit section's source code: Encryption Request")\]

| Clientbound `hello`, Login ID: 1 (0x1) |
| --- |
| Field Name | Field Type | Notes |
| Server ID | [String](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:String) (20) | Always empty when sent by the vanilla server. |
| Public Key | [Prefixed Array](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Prefixed_Array) of [Byte](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Byte) | The server's public key, in bytes. |
| Verify Token | [Prefixed Array](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Prefixed_Array) of [Byte](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Byte) | A sequence of random bytes generated by the server. |
| Should authenticate | [Boolean](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Boolean) | Whether the client should attempt to [authenticate through mojang servers](https://minecraft.wiki/w/Java_Edition_protocol/Encryption#Authentication "Java Edition protocol/Encryption"). |

See [protocol encryption](https://minecraft.wiki/w/Protocol_encryption "Protocol encryption") for details.

#### Login Success

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=29&veaction=edit "Edit section: Login Success") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=29 "Edit section's source code: Login Success")\]

| Clientbound `login_finished`, Login ID: 2 (0x2) |
| --- |
| Field Name | Field Type | Notes |
| Profile | [Game Profile](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Game_Profile) |  |
| Session ID | [UUID](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:UUID) |  |

#### Set Compression

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=30&veaction=edit "Edit section: Set Compression") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=30 "Edit section's source code: Set Compression")\]

Enables compression. If compression is enabled, all following packets are encoded in the [compressed packet format](https://minecraft.wiki/w/Java_Edition_protocol/Packets#With_compression). Negative values will disable compression, meaning the packet format should remain in the [uncompressed packet format](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Without_compression). However, this packet is entirely optional, and if not sent, compression will also not be enabled (the vanilla server does not send the packet when compression is disabled).

| Clientbound `login_compression`, Login ID: 3 (0x3) |
| --- |
| Field Name | Field Type | Notes |
| Threshold | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) | Maximum size of a packet before it is compressed. |

#### Login Plugin Request

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=31&veaction=edit "Edit section: Login Plugin Request") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=31 "Edit section's source code: Login Plugin Request")\]

Used to implement a custom handshaking flow together with [Login Plugin Response](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Login_Plugin_Response).

Unlike plugin messages in "play" mode, these messages follow a lock-step request/response scheme, where the client is expected to respond to a request indicating whether it understood. The vanilla client always responds that it hasn't understood and sends an empty payload.

| Clientbound `custom_query`, Login ID: 4 (0x4) |
| --- |
| Field Name | Field Type | Notes |
| Message ID | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) | Generated by the server - should be unique to the connection. |
| Channel | [Identifier](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Identifier) | Name of the [plugin channel](https://minecraft.wiki/w/Java_Edition_protocol/Plugin_channels "Java Edition protocol/Plugin channels") used to send the data. |
| Data | Varies | Any data, depending on the channel. Typically this would be a sequence of fields using standard data types, but some unofficial channels have unusual formats. There is no length prefix that applies to all channel types, but the format specific to the channel may or may not include one or more length prefixes (e.g. for strings). The vanilla client enforces a length limit of 1048576 bytes on this data, but only if the channel type is unrecognized (which is the case for all login plugin messages with a completely vanilla client). |

### Serverbound

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=32&veaction=edit "Edit section: Serverbound") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=32 "Edit section's source code: Serverbound")\]

#### Login Start

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=33&veaction=edit "Edit section: Login Start") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=33 "Edit section's source code: Login Start")\]

| Serverbound `hello`, Login ID: 0 (0x0) |
| --- |
| Field Name | Field Type | Notes |
| Name | [String](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:String) (16) | Player's Username. |
| Player UUID | [UUID](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:UUID) | The [UUID](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:UUID) of the player logging in. Unused by the vanilla server. |

#### Encryption Response

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=34&veaction=edit "Edit section: Encryption Response") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=34 "Edit section's source code: Encryption Response")\]

| Serverbound `key`, Login ID: 1 (0x1) |
| --- |
| Field Name | Field Type | Notes |
| Shared Secret | [Prefixed Array](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Prefixed_Array) of [Byte](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Byte) | Shared Secret value, encrypted with the server's public key. |
| Verify Token | [Prefixed Array](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Prefixed_Array) of [Byte](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Byte) | Verify Token value, encrypted with the same public key as the shared secret. |

See [protocol encryption](https://minecraft.wiki/w/Protocol_encryption "Protocol encryption") for details.

#### Login Plugin Response

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=35&veaction=edit "Edit section: Login Plugin Response") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=35 "Edit section's source code: Login Plugin Response")\]

| Serverbound `custom_query_answer`, Login ID: 2 (0x2) |
| --- |
| Field Name | Field Type | Notes |
| Message ID | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) | Should match ID from server. |
| Data | [Prefixed Optional](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Prefixed_Optional) Varies | Any data, depending on the channel. Only present if the client understood the request. Typically this would be a sequence of fields using standard data types, but some unofficial channels have unusual formats. There is no length prefix that applies to all channel types, but the format specific to the channel may or may not include one or more length prefixes (e.g. for strings). |

#### Login Acknowledged

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=36&veaction=edit "Edit section: Login Acknowledged") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=36 "Edit section's source code: Login Acknowledged")\]

Acknowledgement to the [Login Success](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Login_Success) packet sent by the server.

| Serverbound `login_acknowledged`, Login ID: 3 (0x3) |
| --- |
| Field Name | Field Type | Notes |
| _no fields_ |

This packet switches the connection state to [configuration](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Configuration).

## Login, configuration and play

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=37&veaction=edit "Edit section: Login, configuration and play") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=37 "Edit section's source code: Login, configuration and play")\]

### Clientbound

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=38&veaction=edit "Edit section: Clientbound") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=38 "Edit section's source code: Clientbound")\]

#### Cookie Request

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=39&veaction=edit "Edit section: Cookie Request") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=39 "Edit section's source code: Cookie Request")\]

Requests a cookie that was previously stored.

| Clientbound `cookie_request`, Login ID: 5 (0x5), Configuration ID: 0 (0x0), Play ID: 21 (0x15) |
| --- |
| Field Name | Field Type | Notes |
| Key | [Identifier](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Identifier) | The identifier of the cookie. |

### Serverbound

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=40&veaction=edit "Edit section: Serverbound") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=40 "Edit section's source code: Serverbound")\]

#### Cookie Response

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=41&veaction=edit "Edit section: Cookie Response") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=41 "Edit section's source code: Cookie Response")\]

Response to a [Cookie Request](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Cookie_Request) from the server. The vanilla server only accepts responses of up to 5 kiB in size.

| Serverbound `cookie_response`, Login ID: 4 (0x4), Configuration ID: 1 (0x1), Play ID: 21 (0x15) |
| --- |
| Field Name | Field Type | Notes |
| Key | [Identifier](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Identifier) | The identifier of the cookie. |
| Payload | [Prefixed Optional](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Prefixed_Optional) [Prefixed Array](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Prefixed_Array) (5120) of [Byte](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Byte) | The data of the cookie. |

## Configuration and play

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=42&veaction=edit "Edit section: Configuration and play") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=42 "Edit section's source code: Configuration and play")\]

### Clientbound

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=43&veaction=edit "Edit section: Clientbound") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=43 "Edit section's source code: Clientbound")\]

#### Plugin Message (clientbound)

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=44&veaction=edit "Edit section: Plugin Message (clientbound)") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=44 "Edit section's source code: Plugin Message (clientbound)")\]

Main article: [Java Edition protocol/Plugin channels](https://minecraft.wiki/w/Java_Edition_protocol/Plugin_channels "Java Edition protocol/Plugin channels")

Mods and plugins can use this to send their data. Minecraft itself uses several [plugin channels](https://minecraft.wiki/w/Java_Edition_protocol/Plugin_channels "Java Edition protocol/Plugin channels"). These internal channels are in the `minecraft` namespace.

More information on how it works on [Dinnerbone's blog](https://web.archive.org/web/20220831140929/https://dinnerbone.com/blog/2012/01/13/minecraft-plugin-channels-messaging/). More documentation about internal and popular registered channels are [here](https://minecraft.wiki/w/Java_Edition_protocol/Plugin_channels "Java Edition protocol/Plugin channels").

| Clientbound `custom_payload`, Configuration ID: 1 (0x1), Play ID: 24 (0x18) |
| --- |
| Field Name | Field Type | Notes |
| Channel | [Identifier](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Identifier) | Name of the [plugin channel](https://minecraft.wiki/w/Java_Edition_protocol/Plugin_channels "Java Edition protocol/Plugin channels") used to send the data. |
| Data | Varies | Any data, depending on the channel. Typically this would be a sequence of fields using standard data types, but some unofficial channels have unusual formats. There is no length prefix that applies to all channel types, but the format specific to the channel may or may not include one or more length prefixes (such as the string length prefix in the standard [`minecraft:brand`](https://minecraft.wiki/w/Java_Edition_protocol/Plugin_channels#Brand "Java Edition protocol/Plugin channels") channel). The vanilla client enforces a length limit of 1048576 bytes on this data, but only if the channel type is unrecognized. |

#### Disconnect

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=45&veaction=edit "Edit section: Disconnect") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=45 "Edit section's source code: Disconnect")\]

| Clientbound `disconnect`, Configuration ID: 2 (0x2), Play ID: 32 (0x20) |
| --- |
| Field Name | Field Type | Notes |
| Reason | [Text Component](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Text_Component) | The reason why the player was disconnected. |

#### Keep Alive (clientbound)

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=46&veaction=edit "Edit section: Keep Alive (clientbound)") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=46 "Edit section's source code: Keep Alive (clientbound)")\]

The server will frequently send out a keep-alive, each containing a random ID. The client must respond with the same payload (see [Keep Alive (serverbound)](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Keep_Alive_(serverbound))). If the client does not respond to a Keep Alive packet within 15 seconds after it was sent, the server kicks the client. Vice versa, if the server does not send any keep-alives for 20 seconds, the client will disconnect and yield a "Timed out" exception.

The vanilla server uses a system-dependent time in milliseconds to generate the keep alive ID value.

| Clientbound `keep_alive`, Configuration ID: 4 (0x4), Play ID: 45 (0x2D) |
| --- |
| Field Name | Field Type | Notes |
| Keep Alive ID | [Long](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Long) |  |

#### Ping

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=47&veaction=edit "Edit section: Ping") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=47 "Edit section's source code: Ping")\]

Packet is not used by the vanilla server. When sent to the client, the client responds with a [Pong](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Pong) packet with the same ID.

| Clientbound `ping`, Configuration ID: 5 (0x5), Play ID: 62 (0x3E) |
| --- |
| Field Name | Field Type | Notes |
| ID | [Int](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Int) |  |

#### Remove Resource Pack

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=48&veaction=edit "Edit section: Remove Resource Pack") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=48 "Edit section's source code: Remove Resource Pack")\]

| Clientbound `resource_pack_pop`, Configuration ID: 8 (0x8), Play ID: 81 (0x51) |
| --- |
| Field Name | Field Type | Notes |
| UUID | [Prefixed Optional](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Prefixed_Optional) [UUID](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:UUID) | The [UUID](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:UUID) of the resource pack to be removed. If not present, every resource pack will be removed. |

#### Add Resource Pack

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=49&veaction=edit "Edit section: Add Resource Pack") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=49 "Edit section's source code: Add Resource Pack")\]

| Clientbound `resource_pack_push`, Configuration ID: 9 (0x9), Play ID: 82 (0x52) |
| --- |
| Field Name | Field Type | Notes |
| UUID | [UUID](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:UUID) | The unique identifier of the resource pack. |
| URL | [String](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:String) (32767) | The URL to the resource pack. |
| Hash | [String](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:String) (40) | A 40 character hexadecimal, case-insensitive [SHA-1](https://en.wikipedia.org/wiki/SHA-1 "wikipedia:SHA-1") hash of the resource pack file.<br>If it's not a 40-character hexadecimal string, the client will not use it for hash verification and likely waste bandwidth. |
| Forced | [Boolean](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Boolean) | The vanilla client will be forced to use the resource pack from the server. If they decline, they will be kicked from the server. |
| Prompt Message | [Prefixed Optional](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Prefixed_Optional) [Text Component](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Text_Component) | This is shown in the prompt making the client accept or decline the resource pack (only if present). |

#### Post Effects

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=50&veaction=edit "Edit section: Post Effects") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=50 "Edit section's source code: Post Effects")\]

Sends the list of post-processing effects that should be active for the client. This packet is available in both the Configuration and Play states.

| Clientbound `post_effects`, Configuration ID: 10 (0xA), Play ID: 83 (0x53) |
| --- |
| Field Name | Field Type | Notes |
| Post Effects | [Prefixed Array](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Prefixed_Array) of [Identifier](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Identifier) | Identifiers of the post-processing effects to activate. |

#### Store Cookie

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=51&veaction=edit "Edit section: Store Cookie") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=51 "Edit section's source code: Store Cookie")\]

Stores some arbitrary data on the client, which persists between server transfers. The vanilla client only accepts cookies of up to 5 kiB in size.

| Clientbound `store_cookie`, Configuration ID: 11 (0xB), Play ID: 122 (0x7A) |
| --- |
| Field Name | Field Type | Notes |
| Key | [Identifier](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Identifier) | The identifier of the cookie. |
| Payload | [Prefixed Array](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Prefixed_Array) (5120) of [Byte](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Byte) | The data of the cookie. |

#### Transfer

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=52&veaction=edit "Edit section: Transfer") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=52 "Edit section's source code: Transfer")\]

Notifies the client that it should transfer to the given server.

The client will close its connection to the current server, open a connection to the specified address and send a [Handshake](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Handshake) with intent set to 3 (Transfer). If the server chooses to accept the transfer, the usual login process will follow.

Cookies previously stored are preserved between server transfers.

| Clientbound `transfer`, Configuration ID: 12 (0xC), Play ID: 132 (0x84) |
| --- |
| Field Name | Field Type | Notes |
| Host | [String](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:String) (32767) | The hostname or IP of the server. |
| Port | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) | The port of the server. |

#### Update Tags

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=53&veaction=edit "Edit section: Update Tags") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=53 "Edit section's source code: Update Tags")\]

| Clientbound `update_tags`, Configuration ID: 14 (0xE), Play ID: 137 (0x89) |
| --- |
| Field Name | Field Type | Notes |
| Tagged Registries | Registry | [Prefixed Array](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Prefixed_Array) | [Identifier](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Identifier) | Registry identifier, such as `minecraft:block`. |
| Tags | [Prefixed Array](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Prefixed_Array) of Tag | Array of tags defined for the registry, each containing a sub-array of entries that have the tag (see below). |

Each tag looks like:

| Field Name | Field Type | Notes |
| --- | --- | --- |
| Tag Name | [Identifier](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Identifier) | Name of the tag without the #-prefix, such as `minecraft:climbable`. |
| Entries | [Prefixed Array](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Prefixed_Array) of [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) | Numeric IDs of the given type (block, item, etc.). This list replaces the previous list of IDs for the given tag. |

See [Tag](https://minecraft.wiki/w/Tag_(Java_Edition) "Tag (Java Edition)") for more information, including a list of vanilla tags.

Due to [MC-249007](https://mojira.dev/MC-249007 "mojira:MC-249007"), any tags that were defined in built-in registries in previous game sessions of a client process will be present by default in new sessions, unless overridden by the server. This occurs on a per-tag basis, so defining a specific tag in a registry will not cause any other tags in that registry to be overridden.

If the server sends [Finish Configuration](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Finish_Configuration) without sending any [Registry Data](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Registry_Data) packets during the configuration phase, previously specified tags in synchronized registries will also be retained unless respecified on a per-tag basis. The server must have already sent registries during a previous configuration phase. Note that it is also possible to [update tags in play state](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Update_Tags), so entering configuration is not necessary to do this.

If any Registry Data packets are sent during reconfiguration, all previous tags in all synchronized registries are forgotten, as are the registries themselves.

When used in play state, this packet always only replaces the tags mentioned in the packet. Other tags, including ones belonging to the registries mentioned in the packet, are unaffected.

#### Custom Report Details

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=54&veaction=edit "Edit section: Custom Report Details") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=54 "Edit section's source code: Custom Report Details")\]

Contains a list of key-value text entries that are included in any crash or disconnection report generated during connection to the server.

| Clientbound `custom_report_details`, Configuration ID: 16 (0x10), Play ID: 139 (0x8B) |
| --- |
| Field Name | Field Type | Notes |
| Details | Title | [Prefixed Array](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Prefixed_Array) (32) | [String](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:String) (128) |  |
| Description | [String](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:String) (4096) |  |

#### Server Links

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=55&veaction=edit "Edit section: Server Links") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=55 "Edit section's source code: Server Links")\]

This packet contains a list of links that the vanilla client will display in the menu available from the pause menu. Link labels can be built-in or custom (i.e., any text).

| Clientbound `server_links`, Configuration ID: 17 (0x11), Play ID: 140 (0x8C) |
| --- |
| Field Name | Field Type | Notes |
| Links | Label | [Prefixed Array](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Prefixed_Array) | [Either](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Either) [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) [Enum](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Enum) or [Text Component](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Text_Component) | Enums are used for built-in labels (see below), and text components for custom labels. |
| URL | [String](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:String) | Valid URL. |

| ID | Name | Notes |
| --- | --- | --- |
| 0 | Bug Report | Displayed on connection error screen; included as a comment in the disconnection report. |
| 1 | Community Guidelines |  |
| 2 | Support |  |
| 3 | Status |  |
| 4 | Feedback |  |
| 5 | Community |  |
| 6 | Website |  |
| 7 | Forums |  |
| 8 | News |  |
| 9 | Announcements |  |

#### Clear Dialog

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=56&veaction=edit "Edit section: Clear Dialog") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=56 "Edit section's source code: Clear Dialog")\]

If we're currently in a dialog screen, then this removes the current screen and switches back to the previous one.

| Clientbound `clear_dialog`, Configuration ID: 18 (0x12), Play ID: 142 (0x8E) |
| --- |
| Field Name | Field Type | Notes |
| _no fields_ |

### Serverbound

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=57&veaction=edit "Edit section: Serverbound") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=57 "Edit section's source code: Serverbound")\]

#### Client Information

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=58&veaction=edit "Edit section: Client Information") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=58 "Edit section's source code: Client Information")\]

Sent when the player connects, or when settings are changed.

| Serverbound `client_information`, Configuration ID: 0 (0x0), Play ID: 14 (0xE) |
| --- |
| Field Name | Field Type | Notes |
| Locale | [String](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:String) (16) | e.g. `en_GB`. |
| View Distance | [Byte](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Byte) | Client-side render distance, in chunks. |
| Chat Mode | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) [Enum](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Enum) | 0: enabled, 1: commands only, 2: hidden. See [Java Edition protocol/Chat#Client chat mode](https://minecraft.wiki/w/Java_Edition_protocol/Chat#Client_chat_mode "Java Edition protocol/Chat") for more information. |
| Chat Colors | [Boolean](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Boolean) | “Colors” multiplayer setting. The vanilla server stores this value but does nothing with it (see [MC-64867](https://mojira.dev/MC-64867 "mojira:MC-64867")). Some third-party servers disable all coloring in chat and system messages when it is false. |
| Displayed Skin Parts | [Unsigned Byte](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Unsigned_Byte) | Bit mask, see below. |
| Main Hand | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) [Enum](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Enum) | 0: Left, 1: Right. |
| Enable text filtering | [Boolean](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Boolean) | Enables filtering of text on signs and written book titles. The vanilla client sets this according to the `profanityFilterPreferences.profanityFilterOn` account attribute indicated by the [Mojang API endpoint for player attributes](https://minecraft.wiki/w/Mojang_API#Query_player_attributes "Mojang API"). In offline mode, it is always false. |
| Allow server listings | [Boolean](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Boolean) | Servers usually list online players; this option should let you not show up in that list. |
| Particle Status | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) [Enum](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Enum) | 0: all, 1: decreased, 2: minimal |

_Displayed Skin Parts_ flags:

- Bit 0 (0x01): Cape enabled
- Bit 1 (0x02): Jacket enabled
- Bit 2 (0x04): Left Sleeve enabled
- Bit 3 (0x08): Right Sleeve enabled
- Bit 4 (0x10): Left Pants Leg enabled
- Bit 5 (0x20): Right Pants Leg enabled
- Bit 6 (0x40): Hat enabled

The most significant bit (bit 7, 0x80) appears to be unused.

#### Plugin Message (serverbound)

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=59&veaction=edit "Edit section: Plugin Message (serverbound)") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=59 "Edit section's source code: Plugin Message (serverbound)")\]

Main article: [Java Edition protocol/Plugin channels](https://minecraft.wiki/w/Java_Edition_protocol/Plugin_channels "Java Edition protocol/Plugin channels")

Mods and plugins can use this to send their data. Minecraft itself uses some [plugin channels](https://minecraft.wiki/w/Java_Edition_protocol/Plugin_channels "Java Edition protocol/Plugin channels"). These internal channels are in the `minecraft` namespace.

More documentation on this: [https://dinnerbone.com/blog/2012/01/13/minecraft-plugin-channels-messaging/](https://dinnerbone.com/blog/2012/01/13/minecraft-plugin-channels-messaging/)

| Serverbound `custom_payload`, Configuration ID: 2 (0x2), Play ID: 22 (0x16) |
| --- |
| Field Name | Field Type | Notes |
| Channel | [Identifier](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Identifier) | Name of the [plugin channel](https://minecraft.wiki/w/Java_Edition_protocol/Plugin_channels "Java Edition protocol/Plugin channels") used to send the data. |
| Data | Varies | Any data, depending on the channel. Typically this would be a sequence of fields using standard data types, but some unofficial channels have unusual formats. There is no length prefix that applies to all channel types, but the format specific to the channel may or may not include one or more length prefixes (such as the string length prefix in the standard [`minecraft:brand`](https://minecraft.wiki/w/Java_Edition_protocol/Plugin_channels#Brand "Java Edition protocol/Plugin channels") channel). The vanilla server enforces a length limit of 32767 bytes on this data, but only if the channel type is unrecognized. |

#### Keep Alive (serverbound)

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=60&veaction=edit "Edit section: Keep Alive (serverbound)") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=60 "Edit section's source code: Keep Alive (serverbound)")\]

The server will frequently send out a keep-alive (see [Keep Alive (clientbound)](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Keep_Alive_(clientbound))), each containing a random ID. The client must respond with the same packet.

| Serverbound `keep_alive`, Configuration ID: 4 (0x4), Play ID: 28 (0x1C) |
| --- |
| Field Name | Field Type | Notes |
| Keep Alive ID | [Long](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Long) |  |

#### Pong

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=61&veaction=edit "Edit section: Pong") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=61 "Edit section's source code: Pong")\]

Response to the clientbound packet ( [Ping](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Ping)) with the same id.

| Serverbound `pong`, Configuration ID: 5 (0x5), Play ID: 45 (0x2D) |
| --- |
| Field Name | Field Type | Notes |
| ID | [Int](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Int) |  |

#### Resource Pack Response

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=62&veaction=edit "Edit section: Resource Pack Response") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=62 "Edit section's source code: Resource Pack Response")\]

| Serverbound `resource_pack`, Configuration ID: 6 (0x6), Play ID: 50 (0x32) |
| --- |
| Field Name | Field Type | Notes |
| UUID | [UUID](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:UUID) | The unique identifier of the resource pack received in the [Add Resource Pack](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Add_Resource_Pack) request. |
| Result | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) [Enum](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Enum) | Result ID (see below). |

Result can be one of the following values:

| ID | Result |
| --- | --- |
| 0 | Successfully downloaded |
| 1 | Declined |
| 2 | Failed to download |
| 3 | Accepted |
| 4 | Downloaded |
| 5 | Invalid URL |
| 6 | Failed to reload |
| 7 | Discarded |

#### Custom Click Action

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=63&veaction=edit "Edit section: Custom Click Action") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=63 "Edit section's source code: Custom Click Action")\]

Sent when the client clicks a [Text Component](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Text_Component) with the `minecraft:custom` click action. This is meant as an alternative to running a command, but will not have any effect on vanilla servers.

| Serverbound `custom_click_action`, Configuration ID: 8 (0x8), Play ID: 68 (0x44) |
| --- |
| Field Name | Field Type | Notes |
| ID | [Identifier](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Identifier) | The identifier for the click action. |
| Payload size | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) | The number of bytes in the payload |
| Payload | [NBT](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:NBT) | The data to send with the click action. May be a TAG\_END (0). |

## Configuration

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=64&veaction=edit "Edit section: Configuration") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=64 "Edit section's source code: Configuration")\]

### Clientbound

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=65&veaction=edit "Edit section: Clientbound") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=65 "Edit section's source code: Clientbound")\]

#### Finish Configuration

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=66&veaction=edit "Edit section: Finish Configuration") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=66 "Edit section's source code: Finish Configuration")\]

Sent by the server to notify the client that the configuration process has finished. The client validates the [registry](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Registry_Data) and [tag](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Update_Tags) data received from the server, and answers with [Acknowledge Finish Configuration](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Acknowledge_Finish_Configuration) whenever it is ready to continue.

| Clientbound `finish_configuration`, Configuration ID: 3 (0x3) |
| --- |
| Field Name | Field Type | Notes |
| _no fields_ |

This packet switches the connection state to [play](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Play).

#### Reset Chat

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=67&veaction=edit "Edit section: Reset Chat") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=67 "Edit section's source code: Reset Chat")\]

| Clientbound `reset_chat`, Configuration ID: 6 (0x6) |
| --- |
| Field Name | Field Type | Notes |
| _no fields_ |

#### Registry Data

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=68&veaction=edit "Edit section: Registry Data") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=68 "Edit section's source code: Registry Data")\]

Sent by the server to inform the client of the contents of [synchronized registries](https://minecraft.wiki/w/Java_Edition_protocol/Registries#Synchronized_registries "Java Edition protocol/Registries"), which are sourced from the server's [data packs](https://minecraft.wiki/w/Data_pack "Data pack"). Each packet contains the contents of a single registry. The client will accumulate the data contained in these packets during the configuration phase, and validate it once [Finish Configuration](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Finish_Configuration) is received from the server.

| Clientbound `registry_data`, Configuration ID: 7 (0x7) |
| --- |
| Field Name | Field Type | Notes |
| Registry ID | [Identifier](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Identifier) | Name of the registry, such as `minecraft:dimension_type`. |
| Entries | Entry ID | [Prefixed Array](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Prefixed_Array) | [Identifier](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Identifier) | Name of the entry, such as `minecraft:overworld`. |
| Data | [Prefixed Optional](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Prefixed_Optional) [NBT](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:NBT) | Entry data. If omitted, sourced from the selected [known packs](https://minecraft.wiki/w/Java_Edition_protocol/Registries#Known_packs_negotiation "Java Edition protocol/Registries"). |

The ordering of the entries in the Entries array defines the numeric IDs that they will be assigned to, starting from 0 and counting upwards. It is essential to maintain consistency between server and client, since many parts of the protocol reference these entries by their ID. The client will disconnect upon receiving a reference to a non-existing entry.

The NBT data of registry entries has the same structure as their definitions in [data packs](https://minecraft.wiki/w/Data_packs "Data packs"), but [represented in NBT instead of JSON](https://minecraft.wiki/w/NBT_format#Conversion_from_JSON "NBT format"). The format for each registry is defined in [Java Edition protocol/Registries#List of synchronized registries](https://minecraft.wiki/w/Java_Edition_protocol/Registries#List_of_synchronized_registries "Java Edition protocol/Registries").

#### Feature Flags

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=69&veaction=edit "Edit section: Feature Flags") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=69 "Edit section's source code: Feature Flags")\]

Used to enable and disable features, generally experimental ones, on the client.

| Clientbound `update_enabled_features`, Configuration ID: 13 (0xD) |
| --- |
| Field Name | Field Type | Notes |
| Feature Flags | [Prefixed Array](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Prefixed_Array) of [Identifier](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Identifier) |  |

There is one special feature flag, which is in most versions:

- minecraft:vanilla - enables vanilla features

For the other feature flags, which may change between versions, see [Experiments#Java Edition](https://minecraft.wiki/w/Experiments#Java_Edition "Experiments").

#### Known Packs (clientbound)

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=70&veaction=edit "Edit section: Known Packs (clientbound)") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=70 "Edit section's source code: Known Packs (clientbound)")\]

Main article: [Java Edition protocol/Registries § Known packs negotiation](https://minecraft.wiki/w/Java_Edition_protocol/Registries#Known_packs_negotiation "Java Edition protocol/Registries")

Informs the client of which data packs are present on the server.
The client is expected to respond with its own [Known Packs (serverbound)](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Known_Packs_(serverbound)) packet containing the subset of packs also known to the client, in the same order as they were listed by the server.
The vanilla server does not continue with Configuration until it receives a response.

| Clientbound `select_known_packs`, Configuration ID: 15 (0xF) |
| --- |
| Field Name | Field Type | Notes |
| Known Packs | Namespace | [Prefixed Array](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Prefixed_Array) | [String](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:String) (32767) | Namespace part of the name of the pack, such as `minecraft`. |
| ID | [String](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:String) (32767) | Pathname part of the name of the pack, such as `core`. |
| Version | [String](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:String) (32767) | Version of the pack. For `minecraft:core` this corresponds to Minecraft version numbers, such as `1.21.10`. Note that the vanilla data pack can change without a protocol version bump, and even a completely vanilla server talking to a vanilla client may fall back to sending all registry data over the wire, if the two are on different protocol-compatible patch versions. |

#### Show Dialog (configuration)

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=71&veaction=edit "Edit section: Show Dialog (configuration)") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=71 "Edit section's source code: Show Dialog (configuration)")\]

Show a custom dialog screen to the client.

| Clientbound `show_dialog`, Configuration ID: 19 (0x13) |
| --- |
| Field Name | Field Type | Notes |
| Dialog | [NBT](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:NBT) | Inline definition as described at [Dialog#Dialog format](https://minecraft.wiki/w/Dialog#Dialog_format "Dialog"). |

#### Code of Conduct

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=72&veaction=edit "Edit section: Code of Conduct") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=72 "Edit section's source code: Code of Conduct")\]

Show the client the server Code of Conduct. Server will not continue with the configuration stage until the client has accepted the Code of Conduct via the [Accept Code of Conduct](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Accept_Code_of_Conduct) packet.

| Clientbound `code_of_conduct`, Configuration ID: 20 (0x14) |
| --- |
| Field Name | Field Type | Notes |
| Code of Conduct | [String](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:String) | Code of Conduct of the server. |

### Serverbound

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=73&veaction=edit "Edit section: Serverbound") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=73 "Edit section's source code: Serverbound")\]

#### Acknowledge Finish Configuration

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=74&veaction=edit "Edit section: Acknowledge Finish Configuration") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=74 "Edit section's source code: Acknowledge Finish Configuration")\]

Sent by the client to notify the server that the configuration process has finished. It is sent in response to the server's [Finish Configuration](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Finish_Configuration).

| Serverbound `finish_configuration`, Configuration ID: 3 (0x3) |
| --- |
| Field Name | Field Type | Notes |
| _no fields_ |

This packet switches the connection state to [play](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Play).

#### Known Packs (serverbound)

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=75&veaction=edit "Edit section: Known Packs (serverbound)") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=75 "Edit section's source code: Known Packs (serverbound)")\]

Main article: [Java Edition protocol/Registries § Known packs negotiation](https://minecraft.wiki/w/Java_Edition_protocol/Registries#Known_packs_negotiation "Java Edition protocol/Registries")

Informs the server of which of the data packs it knows are also present on the client. The client sends this in response to [Known Packs (clientbound)](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Known_Packs_(clientbound)).

If the client specifies a pack in this packet, the server may omit its contained NBT data (but not entry listings) from the [Registry Data](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Registry_Data) packet.

| Serverbound `select_known_packs`, Configuration ID: 7 (0x7) |
| --- |
| Field Name | Field Type | Notes |
| Known Packs | Namespace | [Prefixed Array](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Prefixed_Array) | [String](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:String) (32767) | Namespace part of the name of the pack, such as `minecraft`. |
| ID | [String](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:String) (32767) | Pathname part of the name of the pack, such as `core`. |
| Version | [String](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:String) (32767) | Version of the pack. For `minecraft:core` this corresponds to Minecraft version numbers, such as `1.21.10`. Note that the vanilla data pack can change without a protocol version bump, and even a completely vanilla server talking to a vanilla client may fall back to sending all registry data over the wire, if the two are on different protocol-compatible patch versions. |

#### Accept Code of Conduct

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=76&veaction=edit "Edit section: Accept Code of Conduct") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=76 "Edit section's source code: Accept Code of Conduct")\]

Sent when the client clicks on the "Acknowledge" field in the "Code of Conduct" view. Sent in response to the [Code of Conduct](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Code_of_Conduct) packet.

| Serverbound `accept_code_of_conduct`, Configuration ID: 9 (0x9) |
| --- |
| Field Name | Field Type | Notes |
| _no fields_ |

## Play

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=77&veaction=edit "Edit section: Play") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=77 "Edit section's source code: Play")\]

### Clientbound

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=78&veaction=edit "Edit section: Clientbound") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=78 "Edit section's source code: Clientbound")\]

#### Bundle Delimiter

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=79&veaction=edit "Edit section: Bundle Delimiter") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=79 "Edit section's source code: Bundle Delimiter")\]

The delimiter for a bundle of packets. When received, the client should store every subsequent packet it receives and wait until another delimiter is received. Once that happens, the client is guaranteed to process every packet in the bundle on the same tick, and the client should stop storing packets.

As of 1.20.6, the vanilla server only uses this to ensure [Spawn Entity](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Spawn_Entity) and associated packets used to configure the entity happen on the same tick. Each entity gets a separate bundle.

The vanilla client doesn't allow more than 4096 packets in the same bundle.

| Clientbound `bundle_delimiter`, Play ID: 0 (0x0) |
| --- |
| Field Name | Field Type | Notes |
| _no fields_ |

#### Spawn Entity

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=80&veaction=edit "Edit section: Spawn Entity") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=80 "Edit section's source code: Spawn Entity")\]

Sent by the server to create an entity on the client, normally upon the entity spawning within or entering the player's view range.

The local player entity is automatically created by the client, and must not be created explicitly using this packet. Doing so on the vanilla client will have strange consequences.

| Clientbound `add_entity`, Play ID: 1 (0x1) |
| --- |
| Field Name | Field Type | Notes |
| Entity ID | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) | A unique integer ID mostly used in the protocol to identify the entity. If an entity with the same ID already exists on the client, it is automatically deleted and replaced by the new entity. On the vanilla server entity IDs are globally unique across all dimensions and never reused while the server is running, but not preserved across server restarts. |
| Entity UUID | [UUID](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:UUID) | A unique identifier that is mostly used in persistence and places where the uniqueness matters more. It is possible to create multiple entities with the same UUID on the vanilla client, but a warning will be logged, and functionality dependent on UUIDs may ignore the entity or otherwise misbehave. |
| Type | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) | ID in the `minecraft:entity_type` registry (see "type" field in [Java Edition protocol/Entity metadata#Entities](https://minecraft.wiki/w/Java_Edition_protocol/Entity_metadata#Entities "Java Edition protocol/Entity metadata")). |
| X | [Double](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Double) |  |
| Y | [Double](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Double) |  |
| Z | [Double](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Double) |  |
| Velocity | [LpVec3](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:LpVec3) |  |
| Pitch | [Angle](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Angle) |  |
| Yaw | [Angle](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Angle) |  |
| Head Yaw | [Angle](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Angle) | Only used by living entities, where the head of the entity may differ from the general body rotation. |
| Data | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) | Meaning dependent on the value of the Type field, see [Java Edition protocol/Object data](https://minecraft.wiki/w/Java_Edition_protocol/Object_data "Java Edition protocol/Object data") for details. |

[![](https://minecraft.wiki/images/thumb/Ambox_warning_pn.png/32px-Ambox_warning_pn.png?b6e1c)](https://minecraft.wiki/w/File:Ambox_warning_pn.png "File:Ambox warning pn.png")

The points listed below should be considered when this packet is used to spawn a player entity.

When in [online mode](https://minecraft.wiki/w/Server.properties#online-mode "Server.properties"), the UUIDs must be valid and have valid skin blobs.
In offline mode, the vanilla server uses [UUID v3](https://en.wikipedia.org/wiki/Universally_unique_identifier#Versions_3_and_5_.28namespace_name-based.29 "wikipedia:Universally unique identifier") and chooses the player's UUID by using the String `OfflinePlayer:<player name>`, encoding it in UTF-8 (and case-sensitive), then processes it with `UUID.nameUUIDFromBytes`.

For NPCs UUID v2 should be used. Note:

```
<+Grum> i will never confirm this as a feature you know that :)
```

In an example UUID, `xxxxxxxx-xxxx-Yxxx-xxxx-xxxxxxxxxxxx`, the UUID version is specified by `Y`. So, for UUID v3, `Y` will always be `3`, and for UUID v2, `Y` will always be `2`.

#### Entity Animation

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=81&veaction=edit "Edit section: Entity Animation") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=81 "Edit section's source code: Entity Animation")\]

Sent whenever an entity should play an animation.

| Clientbound `animate`, Play ID: 2 (0x2) |
| --- |
| Field Name | Field Type | Notes |
| Entity ID | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) | Entity ID. |
| Animation | [Unsigned Byte](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Unsigned_Byte) | Animation ID (see below). |

Animation can be one of the following values:

| ID | Animation |
| --- | --- |
| 0 | Wake up / leave bed |
| 1 | Critical effect |
| 2 | Magic critical effect |

#### Award Statistics

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=82&veaction=edit "Edit section: Award Statistics") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=82 "Edit section's source code: Award Statistics")\]

Sent as a response to [Client Status](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Client_Status) (id 1). Will only send the changed values if previously requested.

| Clientbound `award_stats`, Play ID: 3 (0x3) |
| --- |
| Field Name | Field Type | Notes |
| Statistics | Category ID | [Prefixed Array](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Prefixed_Array) | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) | ID in the `minecraft:stat_type` registry; see below. |
| Statistic ID | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) | See below. |
| Value | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) | The amount to set it to. |

Categories (defined in the `minecraft:stat_type` registry).

| Name | ID | Registry |
| --- | --- | --- |
| `minecraft:mined` | 0 | `minecraft:block` |
| `minecraft:crafted` | 1 | `minecraft:item` |
| `minecraft:used` | 2 | `minecraft:item` |
| `minecraft:broken` | 3 | `minecraft:item` |
| `minecraft:picked_up` | 4 | `minecraft:item` |
| `minecraft:dropped` | 5 | `minecraft:item` |
| `minecraft:killed` | 6 | `minecraft:entity_type` |
| `minecraft:killed_by` | 7 | `minecraft:entity_type` |
| `minecraft:custom` | 8 | `minecraft:custom_stat` |

Blocks, Items, and Entities use block (not block state), item, and entity ids.

Custom uses IDs in the `minecraft:custom_stat` registry:

| Name | ID | Unit |
| --- | --- | --- |
| `minecraft:leave_game` | 0 | None |
| `minecraft:play_time` | 1 | Time |
| `minecraft:total_world_time` | 2 | Time |
| `minecraft:time_since_death` | 3 | Time |
| `minecraft:time_since_rest` | 4 | Time |
| `minecraft:sneak_time` | 5 | Time |
| `minecraft:walk_one_cm` | 6 | Distance |
| `minecraft:crouch_one_cm` | 7 | Distance |
| `minecraft:sprint_one_cm` | 8 | Distance |
| `minecraft:walk_on_water_one_cm` | 9 | Distance |
| `minecraft:fall_one_cm` | 10 | Distance |
| `minecraft:climb_one_cm` | 11 | Distance |
| `minecraft:fly_one_cm` | 12 | Distance |
| `minecraft:walk_under_water_one_cm` | 13 | Distance |
| `minecraft:minecart_one_cm` | 14 | Distance |
| `minecraft:boat_one_cm` | 15 | Distance |
| `minecraft:pig_one_cm` | 16 | Distance |
| `minecraft:happy_ghast_one_cm` | 17 | Distance |
| `minecraft:horse_one_cm` | 18 | Distance |
| `minecraft:aviate_one_cm` | 19 | Distance |
| `minecraft:swim_one_cm` | 20 | Distance |
| `minecraft:strider_one_cm` | 21 | Distance |
| `minecraft:jump` | 22 | None |
| `minecraft:drop` | 23 | None |
| `minecraft:damage_dealt` | 24 | Damage |
| `minecraft:damage_dealt_absorbed` | 25 | Damage |
| `minecraft:damage_dealt_resisted` | 26 | Damage |
| `minecraft:damage_taken` | 27 | Damage |
| `minecraft:damage_blocked_by_shield` | 28 | Damage |
| `minecraft:damage_absorbed` | 29 | Damage |
| `minecraft:damage_resisted` | 30 | Damage |
| `minecraft:deaths` | 31 | None |
| `minecraft:mob_kills` | 32 | None |
| `minecraft:animals_bred` | 33 | None |
| `minecraft:player_kills` | 34 | None |
| `minecraft:fish_caught` | 35 | None |
| `minecraft:talked_to_villager` | 36 | None |
| `minecraft:traded_with_villager` | 37 | None |
| `minecraft:eat_cake_slice` | 38 | None |
| `minecraft:fill_cauldron` | 39 | None |
| `minecraft:use_cauldron` | 40 | None |
| `minecraft:clean_armor` | 41 | None |
| `minecraft:clean_banner` | 42 | None |
| `minecraft:clean_shulker_box` | 43 | None |
| `minecraft:interact_with_brewingstand` | 44 | None |
| `minecraft:interact_with_beacon` | 45 | None |
| `minecraft:inspect_dropper` | 46 | None |
| `minecraft:inspect_hopper` | 47 | None |
| `minecraft:inspect_dispenser` | 48 | None |
| `minecraft:play_noteblock` | 49 | None |
| `minecraft:tune_noteblock` | 50 | None |
| `minecraft:pot_flower` | 51 | None |
| `minecraft:trigger_trapped_chest` | 52 | None |
| `minecraft:open_enderchest` | 53 | None |
| `minecraft:enchant_item` | 54 | None |
| `minecraft:play_record` | 55 | None |
| `minecraft:interact_with_furnace` | 56 | None |
| `minecraft:interact_with_crafting_table` | 57 | None |
| `minecraft:open_chest` | 58 | None |
| `minecraft:sleep_in_bed` | 59 | None |
| `minecraft:open_shulker_box` | 60 | None |
| `minecraft:open_barrel` | 61 | None |
| `minecraft:interact_with_blast_furnace` | 62 | None |
| `minecraft:interact_with_smoker` | 63 | None |
| `minecraft:interact_with_lectern` | 64 | None |
| `minecraft:interact_with_campfire` | 65 | None |
| `minecraft:interact_with_cartography_table` | 66 | None |
| `minecraft:interact_with_loom` | 67 | None |
| `minecraft:interact_with_stonecutter` | 68 | None |
| `minecraft:bell_ring` | 69 | None |
| `minecraft:raid_trigger` | 70 | None |
| `minecraft:raid_win` | 71 | None |
| `minecraft:interact_with_anvil` | 72 | None |
| `minecraft:interact_with_grindstone` | 73 | None |
| `minecraft:target_hit` | 74 | None |
| `minecraft:interact_with_smithing_table` | 75 | None |

Units:

- None: just a normal number (formatted with 0 decimal places)
- Damage: value is 10 times the normal amount
- Distance: a distance in centimeters (hundredths of blocks)
- Time: a time span in ticks

#### Acknowledge Block Change

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=83&veaction=edit "Edit section: Acknowledge Block Change") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=83 "Edit section's source code: Acknowledge Block Change")\]

Acknowledges a user-initiated block change. After receiving this packet, the client will display the block state sent by the server instead of the one predicted by the client.

| Clientbound `block_changed_ack`, Play ID: 4 (0x4) |
| --- |
| Field Name | Field Type | Notes |
| Sequence ID | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) | Represents the sequence to acknowledge; this is used for properly syncing block changes to the client after interactions. |

#### Set Block Destroy Stage

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=84&veaction=edit "Edit section: Set Block Destroy Stage") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=84 "Edit section's source code: Set Block Destroy Stage")\]

0–9 are the displayable destroy stages and each other number means that there is no animation on this coordinate.

Block break animations can still be applied on air; the animation will remain visible, although there is no block being broken. However, if this is applied to a transparent block, odd graphical effects may happen, including water losing its transparency. (An effect similar to this can be seen in normal gameplay when breaking ice blocks)

If you need to display several break animations at the same time, you have to give each of them a unique Entity ID. The entity ID does not need to correspond to an actual entity on the client. It is valid to use a randomly generated number.

When removing the break animation, you must use the ID of the entity that set it.

| Clientbound `block_destruction`, Play ID: 5 (0x5) |
| --- |
| Field Name | Field Type | Notes |
| Entity ID | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) | The ID of the entity breaking the block. |
| Location | [Position](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Position) | Block Position. |
| Destroy Stage | [Unsigned Byte](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Unsigned_Byte) | 0–9 to set it, any other value to remove it. |

#### Block Entity Data

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=85&veaction=edit "Edit section: Block Entity Data") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=85 "Edit section's source code: Block Entity Data")\]

Sets the block entity associated with the block at the given location.

| Clientbound `block_entity_data`, Play ID: 6 (0x6) |
| --- |
| Field Name | Field Type | Notes |
| Location | [Position](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Position) |  |
| Type | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) | ID in the `minecraft:block_entity_type` registry |
| NBT Data | [NBT](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:NBT) | Data to set. |

#### Block Action

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=86&veaction=edit "Edit section: Block Action") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=86 "Edit section's source code: Block Action")\]

This packet is used for a number of actions and animations performed by blocks, usually non-persistent. The client ignores the provided block type and instead uses the block state in their world.

See [Java Edition protocol/Block actions](https://minecraft.wiki/w/Java_Edition_protocol/Block_actions "Java Edition protocol/Block actions") for a list of values.

[![](https://minecraft.wiki/images/thumb/Ambox_warning_pn.png/32px-Ambox_warning_pn.png?b6e1c)](https://minecraft.wiki/w/File:Ambox_warning_pn.png "File:Ambox warning pn.png")

This packet uses a block ID from the `minecraft:block` registry, not a block state.

| Clientbound `block_event`, Play ID: 7 (0x7) |
| --- |
| Field Name | Field Type | Notes |
| Location | [Position](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Position) | Block coordinates. |
| Action ID (Byte 1) | [Unsigned Byte](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Unsigned_Byte) | Varies depending on block — see [Java Edition protocol/Block actions](https://minecraft.wiki/w/Java_Edition_protocol/Block_actions "Java Edition protocol/Block actions"). |
| Action Parameter (Byte 2) | [Unsigned Byte](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Unsigned_Byte) | Varies depending on block — see [Java Edition protocol/Block actions](https://minecraft.wiki/w/Java_Edition_protocol/Block_actions "Java Edition protocol/Block actions"). |
| Block Type | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) | ID in the `minecraft:block` registry. This value is unused by the vanilla client, as it will infer the type of block based on the given position. |

#### Block Update

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=87&veaction=edit "Edit section: Block Update") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=87 "Edit section's source code: Block Update")\]

Fired whenever a block is changed within the render distance.

| Clientbound `block_update`, Play ID: 8 (0x8) |
| --- |
| Field Name | Field Type | Notes |
| Location | [Position](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Position) | Block Coordinates. |
| Block ID | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) | The new block state ID for the block as given in the [global block state palette](https://minecraft.wiki/w/Java_Edition_protocol/Chunk_format#Global_block_state_palette "Java Edition protocol/Chunk format"). |

#### Boss Bar

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=88&veaction=edit "Edit section: Boss Bar") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=88 "Edit section's source code: Boss Bar")\]

| Clientbound `boss_event`, Play ID: 9 (0x9) |
| --- |
| Field Name | Field Type | Notes |
| UUID | [UUID](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:UUID) | Unique ID for this bar. |
| Action | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) [Enum](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Enum) | Determines the layout of the remaining packet. |
| Action | Field Name |  |  |
| 0: add | Title | [Text Component](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Text_Component) |  |
| Health | [Float](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Float) | From 0 to 1. Values greater than 1 do not crash a vanilla client, and start [rendering part of a second health bar](https://i.johni0702.de/nA.png) at around 1.5. |
| Color | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) [Enum](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Enum) | Color ID (see below). |
| Division | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) [Enum](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Enum) | Type of division (see below). |
| Flags | [Unsigned Byte](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Unsigned_Byte) | Bit mask. 0x01: should darken sky, 0x02: is dragon bar (used to play end music), 0x04: create fog (previously was also controlled by 0x02). |
| 1: remove | _no fields_ | _no fields_ | Removes this boss bar. |
| 2: update health | Health | [Float](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Float) | _as above_ |
| 3: update title | Title | [Text Component](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Text_Component) |  |
| 4: update style | Color | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) [Enum](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Enum) | Color ID (see below). |
| Dividers | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) [Enum](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Enum) | _as above_ |
| 5: update flags | Flags | [Unsigned Byte](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Unsigned_Byte) | _as above_ |

| ID | Color |
| --- | --- |
| 0 | Pink |
| 1 | Blue |
| 2 | Red |
| 3 | Green |
| 4 | Yellow |
| 5 | Purple |
| 6 | White |

| ID | Type of division |
| --- | --- |
| 0 | No division |
| 1 | 6 notches |
| 2 | 10 notches |
| 3 | 12 notches |
| 4 | 20 notches |

#### Change Difficulty

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=89&veaction=edit "Edit section: Change Difficulty") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=89 "Edit section's source code: Change Difficulty")\]

Changes the difficulty setting in the client's option menu

| Clientbound `change_difficulty`, Play ID: 10 (0xA) |
| --- |
| Field Name | Field Type | Notes |
| Difficulty | [Unsigned Byte](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Unsigned_Byte) [Enum](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Enum) | 0: peaceful, 1: easy, 2: normal, 3: hard. |
| Difficulty locked? | [Boolean](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Boolean) |  |

#### Chunk Batch Finished

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=90&veaction=edit "Edit section: Chunk Batch Finished") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=90 "Edit section's source code: Chunk Batch Finished")\]

Marks the end of a chunk batch. The vanilla client marks the time it receives this packet and calculates the elapsed duration since the [beginning of the chunk batch](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Chunk_Batch_Start). The client uses this duration and the batch size received in this packet to estimate the number of milliseconds elapsed per chunk received. This value is then used to calculate the desired number of chunks per tick through the formula `25 / millisPerChunk`, which is reported to the server through [Chunk Batch Received](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Chunk_Batch_Received). This likely uses `25` instead of the normal tick duration of `50` so chunk processing will only use half of the client's and network's bandwidth.

The vanilla client uses the samples from the latest 15 batches to estimate the milliseconds per chunk number.

| Clientbound `chunk_batch_finished`, Play ID: 11 (0xB) |
| --- |
| Field Name | Field Type | Notes |
| Batch size | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) | Number of chunks. |

#### Chunk Batch Start

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=91&veaction=edit "Edit section: Chunk Batch Start") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=91 "Edit section's source code: Chunk Batch Start")\]

Marks the start of a chunk batch. The vanilla client marks and stores the time it receives this packet.

| Clientbound `chunk_batch_start`, Play ID: 12 (0xC) |
| --- |
| Field Name | Field Type | Notes |
| _no fields_ |

#### Chunk Biomes

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=92&veaction=edit "Edit section: Chunk Biomes") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=92 "Edit section's source code: Chunk Biomes")\]

| Clientbound `chunks_biomes`, Play ID: 13 (0xD) |
| --- |
| Field Name | Field Type | Notes |
| Chunk biome data | Chunk Z | [Prefixed Array](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Prefixed_Array) | [Int](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Int) | Chunk coordinate (block coordinate divided by 16, rounded down) |
| Chunk X | [Int](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Int) | Chunk coordinate (block coordinate divided by 16, rounded down) |
| Data | [Prefixed Array](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Prefixed_Array) of [Byte](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Byte) | Chunk [data structure](https://minecraft.wiki/w/Java_Edition_protocol/Chunk_format#Data_structure "Java Edition protocol/Chunk format"), with [sections](https://minecraft.wiki/w/Java_Edition_protocol/Chunk_format#Chunk_Section "Java Edition protocol/Chunk format") containing only the `Biomes` field |

Note: The order of X and Z is inverted, because the client reads them as one big-endian [Long](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Long), with Z being the upper 32 bits.

#### Clear Titles

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=93&veaction=edit "Edit section: Clear Titles") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=93 "Edit section's source code: Clear Titles")\]

Clear the client's current title information, with the option to also reset it.

| Clientbound `clear_titles`, Play ID: 14 (0xE) |
| --- |
| Field Name | Field Type | Notes |
| Reset | [Boolean](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Boolean) |  |

#### Command Suggestions Response

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=94&veaction=edit "Edit section: Command Suggestions Response") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=94 "Edit section's source code: Command Suggestions Response")\]

The server responds with a list of auto-completions of the last word sent to it. In the case of regular chat, this is a player username. Command names and parameters are also supported. The client sorts these alphabetically before listing them.

| Clientbound `command_suggestions`, Play ID: 15 (0xF) |
| --- |
| Field Name | Field Type | Notes |
| ID | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) | Transaction ID. |
| Start | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) | Start of the text to replace. |
| Length | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) | Length of the text to replace. |
| Matches | Match | [Prefixed Array](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Prefixed_Array) | [String](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:String) (32767) | One eligible value to insert, note that each command is sent separately instead of in a single string, hence the need for Count. |
| Tooltip | [Prefixed Optional](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Prefixed_Optional) [Text Component](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Text_Component) | Tooltip to display. |

#### Commands

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=95&veaction=edit "Edit section: Commands") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=95 "Edit section's source code: Commands")\]

Lists all of the commands on the server, and how they are parsed.

This is a directed graph, with one root node. Each redirect or child node must refer only to nodes that have already been declared.

| Clientbound `commands`, Play ID: 16 (0x10) |
| --- |
| Field Name | Field Type | Notes |
| Nodes | [Prefixed Array](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Prefixed_Array) of [Node](https://minecraft.wiki/w/Java_Edition_protocol/Command_data#Node_Format "Java Edition protocol/Command data") | An array of nodes. |
| Root index | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) | Index of the `root` node in the previous array. |

For more information on this packet, see the [Java Edition protocol/Command data](https://minecraft.wiki/w/Java_Edition_protocol/Command_data "Java Edition protocol/Command data") article.

#### Close Container

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=96&veaction=edit "Edit section: Close Container") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=96 "Edit section's source code: Close Container")\]

This packet is sent from the server to the client when a window is forcibly closed, such as when a chest is destroyed while it's open. The vanilla client disregards the provided window ID and closes any active window.

| Clientbound `container_close`, Play ID: 17 (0x11) |
| --- |
| Field Name | Field Type | Notes |
| Window ID | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) | This is the ID of the window that was closed. 0 for inventory. |

#### Set Container Content

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=97&veaction=edit "Edit section: Set Container Content") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=97 "Edit section's source code: Set Container Content")\]

[![](https://minecraft.wiki/images/thumb/Inventory-slots.png/300px-Inventory-slots.png?e5b77)](https://minecraft.wiki/w/File:Inventory-slots.png) The inventory slots

Replaces the contents of a container window. Sent by the server upon initialization of a container window or the player's inventory, and in response to state ID mismatches (see [#Click Container](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Click_Container)).

| Clientbound `container_set_content`, Play ID: 18 (0x12) |
| --- |
| Field Name | Field Type | Notes |
| Window ID | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) | The ID of window which items are being sent for. 0 for player inventory. The client ignores any packets targeting a Window ID other than the current one. However, an exception is made for the player inventory, which may be targeted at any time. (The vanilla server does not appear to utilize this special case.) |
| State ID | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) | A server-managed sequence number used to avoid desynchronization; see [#Click Container](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Click_Container). |
| Slot Data | [Prefixed Array](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Prefixed_Array) of [Slot](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Slot) |
| Carried Item | [Slot](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Slot) | Item being dragged with the mouse. |

See [inventory windows](https://minecraft.wiki/w/Java_Edition_protocol/Inventory#Windows "Java Edition protocol/Inventory") for further information about how slots are indexed.
Use [Open Screen](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Open_Screen) to open the container on the client.

#### Set Container Property

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=98&veaction=edit "Edit section: Set Container Property") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=98 "Edit section's source code: Set Container Property")\]

This packet is used to inform the client that part of a GUI window should be updated.

| Clientbound `container_set_data`, Play ID: 19 (0x13) |
| --- |
| Field Name | Field Type | Notes |
| Window ID | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) |  |
| Property | [Short](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Short) | The property to be updated, see below. |
| Value | [Short](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Short) | The new value for the property, see below. |

The meaning of the Property field depends on the type of the window. The following table shows the known combinations of window type and property, and how the value is to be interpreted.

| Window type | Property | Value |
| --- | --- | --- |
| Furnace | 0: Fire icon (fuel left) | counting from fuel burn time down to 0 (in-game ticks) |
| 1: Maximum fuel burn time | fuel burn time or 0 (in-game ticks) |
| 2: Progress arrow | counting from 0 to maximum progress (in-game ticks) |
| 3: Maximum progress | always 200 on the vanilla server |
| Enchantment Table | 0: Level requirement for top enchantment slot | The enchantment's xp level requirement |
| 1: Level requirement for middle enchantment slot |
| 2: Level requirement for bottom enchantment slot |
| 3: The enchantment seed | Used for drawing the enchantment names (in [SGA](https://en.wikipedia.org/wiki/Standard_Galactic_Alphabet "wikipedia:Standard Galactic Alphabet")) clientside. The same seed _is_ used to calculate enchantments, but some of the data isn't sent to the client to prevent easily guessing the entire list (the seed value here is the regular seed bitwise and `0xFFFFFFF0`). |
| 4: Enchantment ID shown on mouse hover over top enchantment slot | The enchantment ID (set to -1 to hide it), see below for values |
| 5: Enchantment ID shown on mouse hover over middle enchantment slot |
| 6: Enchantment ID shown on mouse hover over bottom enchantment slot |
| 7: Enchantment level shown on mouse hover over the top slot | The enchantment level (1 = I, 2 = II, 6 = VI, etc.), or -1 if no enchant |
| 8: Enchantment level shown on mouse hover over the middle slot |
| 9: Enchantment level shown on mouse hover over the bottom slot |
| Beacon | 0: Power level | 0-4, controls what effect buttons are enabled |
| 1: First potion effect | [Potion effect ID](https://minecraft.wiki/w/Data_values#Status_effects "Data values") for the first effect, or -1 if no effect |
| 2: Second potion effect | [Potion effect ID](https://minecraft.wiki/w/Data_values#Status_effects "Data values") for the second effect, or -1 if no effect |
| Anvil | 0: Repair cost | The repair's cost in XP levels |
| Brewing Stand | 0: Brew time | 0 – 400, with 400 making the arrow empty, and 0 making the arrow full |
| 1: Fuel time | 0 - 20, with 0 making the arrow empty, and 20 making the arrow full |
| Stonecutter | 0: Selected recipe | The index of the selected recipe. -1 means none is selected. |
| Loom | 0: Selected pattern | The index of the selected pattern. 0 means none is selected, 0 is also the internal ID of the "base" pattern. |
| Lectern | 0: Page number | The current page number, starting from 0. |
| Smithing Table | 0: Has recipe error | True if greater than zero. |
| Crafter | 0-9: Slot Disabled | 0 If the slot is enabled, 1 if the slot is disabled |

For an enchanting table, the following numerical IDs are used:

| Numerical ID | Enchantment ID | Enchantment Name |
| --- | --- | --- |
| 0 | minecraft:protection | Protection |
| 1 | minecraft:fire\_protection | Fire Protection |
| 2 | minecraft:feather\_falling | Feather Falling |
| 3 | minecraft:blast\_protection | Blast Protection |
| 4 | minecraft:projectile\_protection | Projectile Protection |
| 5 | minecraft:respiration | Respiration |
| 6 | minecraft:aqua\_affinity | Aqua Affinity |
| 7 | minecraft:thorns | Thorns |
| 8 | minecraft:depth\_strider | Depth Strider |
| 9 | minecraft:frost\_walker | Frost Walker |
| 10 | minecraft:binding\_curse | Curse of Binding |
| 11 | minecraft:soul\_speed | Soul Speed |
| 12 | minecraft:swift\_sneak | Swift Sneak |
| 13 | minecraft:sharpness | Sharpness |
| 14 | minecraft:smite | Smite |
| 15 | minecraft:bane\_of\_arthropods | Bane of Arthropods |
| 16 | minecraft:knockback | Knockback |
| 17 | minecraft:fire\_aspect | Fire Aspect |
| 18 | minecraft:looting | Looting |
| 19 | minecraft:sweeping\_edge | Sweeping Edge |
| 20 | minecraft:efficiency | Efficiency |
| 21 | minecraft:silk\_touch | Silk Touch |
| 22 | minecraft:unbreaking | Unbreaking |
| 23 | minecraft:fortune | Fortune |
| 24 | minecraft:power | Power |
| 25 | minecraft:punch | Punch |
| 26 | minecraft:flame | Flame |
| 27 | minecraft:infinity | Infinity |
| 28 | minecraft:luck\_of\_the\_sea | Luck of the Sea |
| 29 | minecraft:lure | Lure |
| 30 | minecraft:loyalty | Loyalty |
| 31 | minecraft:impaling | Impaling |
| 32 | minecraft:riptide | Riptide |
| 33 | minecraft:channeling | Channeling |
| 34 | minecraft:multishot | Multishot |
| 35 | minecraft:quick\_charge | Quick Charge |
| 36 | minecraft:piercing | Piercing |
| 37 | minecraft:density | Density |
| 38 | minecraft:breach | Breach |
| 39 | minecraft:wind\_burst | Wind Burst |
| 40 | minecraft:mending | Mending |
| 41 | minecraft:vanishing\_curse | Curse of Vanishing |

#### Set Container Slot

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=99&veaction=edit "Edit section: Set Container Slot") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=99 "Edit section's source code: Set Container Slot")\]

Sent by the server when an item in a slot (in a window) is added/removed.

| Clientbound `container_set_slot`, Play ID: 20 (0x14) |
| --- |
| Field Name | Field Type | Notes |
| Window ID | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) | The window that is being updated. 0 for player inventory. The client ignores any packets targeting a Window ID other than the current one; see below for exceptions. |
| State ID | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) | A server-managed sequence number used to avoid desynchronization; see [#Click Container](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Click_Container). |
| Slot | [Short](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Short) | The slot that should be updated. |
| Slot Data | [Slot](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Slot) |  |

If Window ID is 0, the hotbar and offhand slots (slots 36 through 45) may be updated even when a different container window is open. (The vanilla server does not appear to utilize this special case.) Updates are also restricted to those slots when the player is looking at a creative inventory tab other than the survival inventory. (The vanilla server does _not_ handle this restriction in any way, leading to [MC-242392](https://bugs.mojang.com/browse/MC-242392).)

When a container window is open, the server never sends updates targeting Window ID 0—all of the [window types](https://minecraft.wiki/w/Java_Edition_protocol/Inventory "Java Edition protocol/Inventory") include slots for the player inventory. The client must automatically apply changes targeting the inventory portion of a container window to the main inventory; the server does not resend them for ID 0 when the window is closed. However, since the armor and offhand slots are only present on ID 0, updates to those slots occurring while a window is open must be deferred by the server until the window's closure.

#### Set Cooldown

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=100&veaction=edit "Edit section: Set Cooldown") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=100 "Edit section's source code: Set Cooldown")\]

Applies a cooldown period to all items with the given type. Used by the vanilla server with enderpearls. This packet should be sent when the cooldown starts and also when the cooldown ends (to compensate for lag), although the client will end the cooldown automatically. Can be applied to any item, note that interactions still get sent to the server with the item, but the client does not play the animation nor attempt to predict results (i.e, block placing).

| Clientbound `cooldown`, Play ID: 22 (0x16) |
| --- |
| Field Name | Field Type | Notes |
| Cooldown Group | [Identifier](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Identifier) | Identifier of the item (minecraft:stone) or the cooldown group ("use\_cooldown" item component) |
| Cooldown Ticks | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) | Number of ticks to apply a cooldown for, or 0 to clear the cooldown. |

#### Chat Suggestions

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=101&veaction=edit "Edit section: Chat Suggestions") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=101 "Edit section's source code: Chat Suggestions")\]

Unused by the vanilla server. Likely provided for custom servers to send chat message completions to clients.

| Clientbound `custom_chat_completions`, Play ID: 23 (0x17) |
| --- |
| Field Name | Field Type | Notes |
| Action | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) [Enum](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Enum) | 0: Add, 1: Remove, 2: Set |
| Entries | [Prefixed Array](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Prefixed_Array) of [String](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:String) (32767) |  |

#### Damage Event

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=102&veaction=edit "Edit section: Damage Event") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=102 "Edit section's source code: Damage Event")\]

| Clientbound `damage_event`, Play ID: 25 (0x19) |
| --- |
| Field Name | Field Type | Notes |
| Entity ID | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) | The ID of the entity taking damage |
| Source Type ID | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) | The type of damage in the `minecraft:damage_type` registry, defined by the [Registry Data](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Registry_Data) packet. |
| Source Cause ID | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) | The ID + 1 of the entity responsible for the damage, if present. If not present, the value is 0 |
| Source Direct ID | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) | The ID + 1 of the entity that directly dealt the damage, if present. If not present, the value is 0. If this field is present:<br>- and damage was dealt indirectly, such as by the use of a projectile, this field will contain the ID of such projectile;<br>- and damage was dealt directly, such as by manually attacking, this field will contain the same value as Source Cause ID. |
| Source Position | X | [Prefixed Optional](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Prefixed_Optional) | [Double](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Double) | The vanilla server sends the Source Position when the damage was dealt by the /damage command and a position was specified |
| Y | [Double](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Double) |
| Z | [Double](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Double) |

#### Debug Block Value

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=103&veaction=edit "Edit section: Debug Block Value") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=103 "Edit section's source code: Debug Block Value")\]

| Clientbound `debug_block_value`, Play ID: 26 (0x1A) |
| --- |
| Field Name | Field Type | Notes |
| Location | [Position](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Position) |  |
| Update | [Debug Subscription Update](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Debug_Subscription_Update) |  |

#### Debug Chunk Value

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=104&veaction=edit "Edit section: Debug Chunk Value") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=104 "Edit section's source code: Debug Chunk Value")\]

| Clientbound `debug_chunk_value`, Play ID: 27 (0x1B) |
| --- |
| Field Name | Field Type | Notes |
| Chunk Z | [Int](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Int) |  |
| Chunk X | [Int](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Int) |  |
| Update | [Debug Subscription Update](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Debug_Subscription_Update) |  |

Note: The order of X and Z is inverted, because the client reads them as one big-endian [Long](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Long), with Z being the upper 32 bits.

#### Debug Entity Value

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=105&veaction=edit "Edit section: Debug Entity Value") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=105 "Edit section's source code: Debug Entity Value")\]

| Clientbound `debug_entity_value`, Play ID: 28 (0x1C) |
| --- |
| Field Name | Field Type | Notes |
| Entity ID | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) |  |
| Update | [Debug Subscription Update](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Debug_Subscription_Update) |  |

#### Debug Event

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=106&veaction=edit "Edit section: Debug Event") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=106 "Edit section's source code: Debug Event")\]

| Clientbound `debug_event`, Play ID: 29 (0x1D) |
| --- |
| Field Name | Field Type | Notes |
| Event | [Debug Subscription Event](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Debug_Subscription_Event) |  |

#### Debug Sample

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=107&veaction=edit "Edit section: Debug Sample") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=107 "Edit section's source code: Debug Sample")\]

Sample data that is sent periodically after the client has subscribed with [Debug Sample Subscription](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Debug_Sample_Subscription).

The vanilla server only sends debug samples to players who are server operators.

| Clientbound `debug_sample`, Play ID: 30 (0x1E) |
| --- |
| Field Name | Field Type | Notes |
| Sample | [Prefixed Array](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Prefixed_Array) of [Long](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Long) | Array of type-dependent samples. |
| Sample Type | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) [Enum](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Enum) | See below. |

Types:

| Id | Name | Description |
| --- | --- | --- |
| 0 | Tick time | Four different tick-related metrics, each one represented by one long on the array.<br>They are measured in nano-seconds, and are as follows:<br>- 0: Full tick time: Aggregate of the three times below;<br>- 1: Server tick time: Main server tick logic;<br>- 2: Tasks time: Tasks scheduled to execute after the main logic;<br>- 3: Idle time: Time idling to complete the full 50ms tick cycle.<br>Note that the vanilla client calculates the timings used for min/max/average display by subtracting the idle time from the full tick time. This can cause the displayed values to go negative if the idle time is (nonsensically) greater than the full tick time. |

#### Delete Message

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=108&veaction=edit "Edit section: Delete Message") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=108 "Edit section's source code: Delete Message")\]

Removes a message from the client's chat. This only works for messages with signatures; system messages cannot be deleted with this packet.

| Clientbound `delete_chat`, Play ID: 31 (0x1F) |
| --- |
| Field Name | Field Type | Notes |
| Message ID | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) | The message ID + 1, used for validating message signature. The next field is present only when value of this field is equal to 0. |
| Signature | [Optional](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Optional) [Byte Array](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Byte_Array) (256) | The previous message's signature. Always 256 bytes and not length-prefixed. |

#### Disguised Chat Message

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=109&veaction=edit "Edit section: Disguised Chat Message") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=109 "Edit section's source code: Disguised Chat Message")\]

Main article: [Java Edition protocol/Chat](https://minecraft.wiki/w/Java_Edition_protocol/Chat "Java Edition protocol/Chat")

Sends the client a chat message, but without any message signing information.

The vanilla server uses this packet when the console is communicating with players through commands, such as `/say`, `/tell`, `/me`, among others.

| Clientbound `disguised_chat`, Play ID: 33 (0x21) |
| --- |
| Field Name | Field Type | Notes |
| Message | [Text Component](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Text_Component) | This is used as the `content` parameter when formatting the message on the client. |
| Chat Type | [ID or](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:ID_or) [Chat Type](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Chat_Type) | Either the type of chat in the `minecraft:chat_type` registry, defined by the [Registry Data](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Registry_Data) packet, or an inline definition. |
| Sender Name | [Text Component](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Text_Component) | The name of the one sending the message, usually the sender's display name.<br>This is used as the `sender` parameter when formatting the message on the client. |
| Target Name | [Prefixed Optional](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Prefixed_Optional) [Text Component](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Text_Component) | The name of the one receiving the message, usually the receiver's display name.<br>This is used as the `target` parameter when formatting the message on the client. |

#### Entity Event

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=110&veaction=edit "Edit section: Entity Event") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=110 "Edit section's source code: Entity Event")\]

Entity statuses generally trigger an animation for an entity. The available statuses vary by the entity's type (and are available to subclasses of that type as well).

| Clientbound `entity_event`, Play ID: 34 (0x22) |
| --- |
| Field Name | Field Type | Notes |
| Entity ID | [Int](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Int) |  |
| Entity Status | [Byte](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Byte) [Enum](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Enum) | See [Java Edition protocol/Entity statuses](https://minecraft.wiki/w/Java_Edition_protocol/Entity_statuses "Java Edition protocol/Entity statuses") for a list of which statuses are valid for each type of entity. |

#### Teleport Entity

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=111&veaction=edit "Edit section: Teleport Entity") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=111 "Edit section's source code: Teleport Entity")\]

[![](https://minecraft.wiki/images/thumb/Ambox_warning_pn.png/32px-Ambox_warning_pn.png?b6e1c)](https://minecraft.wiki/w/File:Ambox_warning_pn.png "File:Ambox warning pn.png")

The Mojang-specified name of this packet was changed in 1.21.2 from `teleport_entity` to `entity_position_sync`. There is a newer `teleport_entity`, which this document more appropriately calls [Synchronize Vehicle Position](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Synchronize_Vehicle_Position). That packet has a different function and will lead to confusing results if used in place of this one.

Synchronizes an entity's position path and rotation. The position path may contain either one absolute position or a sequence of absolute position steps.

| Clientbound `entity_position_sync`, Play ID: 35 (0x23) |
| --- |
| Condition | Field Name | Field Type | Notes |
| Always | Entity ID | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) |  |
| Always | Position Path Type | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) [Enum](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Enum) | Determines how the following position path data is encoded; see below. |
| Path type = 0 (Linear) | X | [Double](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Double) | Absolute end position. |
| Path type = 0 (Linear) | Y | [Double](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Double) |
| Path type = 0 (Linear) | Z | [Double](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Double) |
| Path type = 1 (Stepped) | Steps | [Prefixed Array](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Prefixed_Array) of Position Step | Sequence of absolute position steps; see below. |
| Always | Yaw | [Float](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Float) | Rotation around the vertical axis, in degrees. |
| Always | Pitch | [Float](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Float) | Rotation around the horizontal axis, in degrees. |
| Always | On Ground | [Boolean](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Boolean) |  |

Position Path Type can be one of the following values:

| ID | Name |
| --- | --- |
| 0 | Linear |
| 1 | Stepped |

Each Position Step contains:

| Field Name | Field Type | Notes |
| --- | --- | --- |
| X | [Double](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Double) | Absolute position for this step. |
| Y | [Double](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Double) |
| Z | [Double](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Double) |
| Tick Offset | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) | Tick offset of this step. |

#### Explosion

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=112&veaction=edit "Edit section: Explosion") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=112 "Edit section's source code: Explosion")\]

Sent when an explosion occurs (creepers, TNT, and ghast fireballs).

| Clientbound `explode`, Play ID: 36 (0x24) |
| --- |
| Field Name | Field Type | Notes |
| X | [Double](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Double) |  |
| Y | [Double](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Double) |  |
| Z | [Double](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Double) |  |
| Radius | [Float](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Float) |  |
| Block Count | [Int](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Int) |  |
| Player Delta Velocity | X | [Prefixed Optional](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Prefixed_Optional) | [Double](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Double) | Velocity difference of the player being pushed by the explosion. |
| Y | [Double](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Double) |
| Z | [Double](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Double) |
| Explosion Particle ID | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) | ID in the `minecraft:particle_type` registry. |
| Explosion Particle Data | Varies | Particle data as specified in [Java Edition protocol/Particles](https://minecraft.wiki/w/Java_Edition_protocol/Particles "Java Edition protocol/Particles"). |
| Explosion Sound | [ID or](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:ID_or) [Sound Event](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Sound_Event) | ID in the `minecraft:sound_event` registry, or an inline definition. |
| Block Particle Alternatives | Particle ID | [Prefixed Array](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Prefixed_Array) | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) |  |
| Particle Data | Varies | Particle data as specified in [Java Edition protocol/Particles](https://minecraft.wiki/w/Java_Edition_protocol/Particles "Java Edition protocol/Particles"). |
| Scaling | [Float](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Float) |  |
| Speed | [Float](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Float) |  |
| Weight | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) |  |
| Play Sound | [Boolean](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Boolean) | Whether the explosion sound should be played. |

#### Add Transient Block

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=113&veaction=edit "Edit section: Add Transient Block") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=113 "Edit section's source code: Add Transient Block")\]

Sends a block state to the client that exists for a finite amount of time.

| Clientbound `add_transient_block`, Play ID: 37 (0x25) |
| --- |
| Field Name | Field Type | Notes |
| Location | [Position](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Position) | Position of the transient block. |
| Block State | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) | Block state ID from the [global block state palette](https://minecraft.wiki/w/Java_Edition_protocol/Chunk_format#Global_block_state_palette "Java Edition protocol/Chunk format"). |

#### Unload Chunk

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=114&veaction=edit "Edit section: Unload Chunk") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=114 "Edit section's source code: Unload Chunk")\]

Tells the client to unload a chunk column.

| Clientbound `forget_level_chunk`, Play ID: 38 (0x26) |
| --- |
| Field Name | Field Type | Notes |
| Chunk Z | [Int](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Int) | Block coordinate divided by 16, rounded down. |
| Chunk X | [Int](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Int) | Block coordinate divided by 16, rounded down. |

Note: The order is inverted, because the client reads this packet as one big-endian [Long](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Long), with Z being the upper 32 bits.

It is legal to send this packet even if the given chunk is not currently loaded.

#### Game Event

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=115&veaction=edit "Edit section: Game Event") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=115 "Edit section's source code: Game Event")\]

Used for a wide variety of game events, such as weather, respawn availability (from [bed](https://minecraft.wiki/w/Bed "Bed") and [respawn anchor](https://minecraft.wiki/w/Respawn_anchor "Respawn anchor")), game mode, some game rules, and [demo](https://minecraft.wiki/w/Demo "Demo") messages.

| Clientbound `game_event`, Play ID: 39 (0x27) |
| --- |
| Field Name | Field Type | Notes |
| Event | [Unsigned Byte](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Unsigned_Byte) | See below. |
| Value | [Float](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Float) | Depends on Event. |

_Events_:

| Event | Effect | Value |
| --- | --- | --- |
| 0 | No respawn block available | Note: Displays message 'block.minecraft.spawn.not\_valid' (You have no home bed or charged respawn anchor, or it was obstructed) to the player. |
| 1 | "Begin raining" | Note: Actually stops rain; see below. |
| 2 | "End raining" | Note: Actually starts rain; see below. |
| 3 | Change game mode | 0: Survival, 1: Creative, 2: Adventure, 3: Spectator. |
| 4 | Win game | Note: Rolls the credits. When closing the credits screen, the client sends [Client Status](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Client_Status) with the "Perform respawn" action. |
| 5 | Demo event | 0: Show welcome to demo screen.<br>101: Tell movement controls.<br>102: Tell jump control.<br>103: Tell inventory control.<br>104: Tell that the demo is over and print a message about how to take a screenshot. |
| 6 | Play arrow hit sound | Note: Sent when an arrow shot by the client hits another player. |
| 7 | Change rain level | Note: Seems to change both sky color and lighting.<br>Rain level ranging from 0 to 1. |
| 8 | Change thunder level | Note: Seems to change both sky color and lighting (same as Rain level change, but doesn't start rain). It also requires rain to render by vanilla client.<br>Thunder level ranging from 0 to 1. |
| 9 | Play pufferfish sting sound |
| 10 | Play elder guardian jump scare | 0: Visual effect only.<br>1: Sound and visual effect. |
| 11 | Toggle immediate respawn | 0: Enable respawn screen.<br>1: Immediately respawn (sent when the `doImmediateRespawn` gamerule changes). |
| 12 | Toggle limited crafting | 0: Disable limited crafting.<br>1: Enable limited crafting (sent when the `doLimitedCrafting` gamerule changes). |
| 13 | Start waiting for chunks | Note: This event is one of the [prerequisites for the client to close the loading screen when spawning](https://minecraft.wiki/w/Java_Edition_protocol/FAQ#%E2%80%A6my_player_isn't_spawning! "Java Edition protocol/FAQ"). It is required following each [Login (play)](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Login_(play)) and [Respawn](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Respawn) packet, even when respawning to the same dimension. The vanilla server does not send any chunks before sending this event, but it is still valid to do so. |

"Begin raining" and "End raining" are equivalent to Change rain level with levels 0.0 and 1.0 respectively, as in, they have the opposite of the expected effect. However the vanilla server sends "Begin raining" when rain starts, and "End raining" when rain ends, which is why they are named as such. It then sends Change rain level immediately afterwards, effectively overriding the incorrect level set by the preceding packet. These events are redundant and useless; use Change rain level instead.

#### Game Rule Values

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=116&veaction=edit "Edit section: Game Rule Values") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=116 "Edit section's source code: Game Rule Values")\]

| Clientbound `game_rule_values`, Play ID: 40 (0x28) |
| --- |
| Field Name | Field Type | Notes |
| Rules | Name | [Prefixed Array](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Prefixed_Array) | [Identifier](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Identifier) |  |
| Value | [String](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:String) (32767) |  |

#### Game Test Highlight Position

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=117&veaction=edit "Edit section: Game Test Highlight Position") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=117 "Edit section's source code: Game Test Highlight Position")\]

| Clientbound `game_test_highlight_pos`, Play ID: 41 (0x29) |
| --- |
| Field Name | Field Type | Notes |
| Absolute Location | [Position](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Position) |  |
| Relative Location | [Position](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Position) |  |

#### Open Horse Screen

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=118&veaction=edit "Edit section: Open Horse Screen") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=118 "Edit section's source code: Open Horse Screen")\]

This packet is used exclusively for opening the horse GUI. [Open Screen](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Open_Screen) is used for all other GUIs. The client will not open the inventory if the Entity ID does not point to a horse-like animal.

| Clientbound `mount_screen_open`, Play ID: 42 (0x2A) |
| --- |
| Field Name | Field Type | Notes |
| Window ID | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) | Same as the field of [Open Screen](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Open_Screen). |
| Inventory columns count | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) | How many columns of horse inventory slots exist in the GUI, 3 slots per column. |
| Entity ID | [Int](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Int) | The "owner" entity of the GUI. The client should close the GUI if the owner entity dies or is cleared. |

#### Hurt Animation

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=119&veaction=edit "Edit section: Hurt Animation") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=119 "Edit section's source code: Hurt Animation")\]

Plays a bobbing animation for the entity receiving damage.

| Clientbound `hurt_animation`, Play ID: 43 (0x2B) |
| --- |
| Field Name | Field Type | Notes |
| Entity ID | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) | The ID of the entity taking damage |
| Yaw | [Float](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Float) | The direction the damage is coming from in relation to the entity |

#### Initialize World Border

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=120&veaction=edit "Edit section: Initialize World Border") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=120 "Edit section's source code: Initialize World Border")\]

| Clientbound `initialize_border`, Play ID: 44 (0x2C) |
| --- |
| Field Name | Field Type | Notes |
| Center X | [Double](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Double) |  |
| Center Z | [Double](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Double) |  |
| Old Diameter | [Double](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Double) | Current length of a single side of the world border, in meters. |
| New Diameter | [Double](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Double) | Target length of a single side of the world border, in meters. |
| Speed | [VarLong](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarLong) | Number of real-time _milli_ seconds until New Diameter is reached. It appears that vanilla server does not sync world border speed to game ticks, so it gets out of sync with server lag. If the world border is not moving, this is set to 0. |
| Portal Teleport Boundary | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) | Resulting coordinates from a portal teleport are limited to ±value. Usually 29999984. |
| Warning Blocks | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) | In meters. |
| Warning Time | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) | In seconds as set by `/worldborder warning time`. |

The vanilla client determines how solid to display the warning by comparing to whichever is higher, the warning distance or whichever is lower, the distance from the current diameter to the target diameter or the place the border will be after warningTime seconds. In pseudocode:

```
distance = max(min(resizeSpeed * 1000 * warningTime, abs(targetDiameter - currentDiameter)), warningDistance);
if (playerDistance < distance) {
    warning = 1.0 - playerDistance / distance;
} else {
    warning = 0.0;
}
```

#### Chunk Data and Update Light

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=121&veaction=edit "Edit section: Chunk Data and Update Light") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=121 "Edit section's source code: Chunk Data and Update Light")\]

Main article: [Java Edition protocol/Chunk format](https://minecraft.wiki/w/Java_Edition_protocol/Chunk_format "Java Edition protocol/Chunk format")

See also: [§ Unload Chunk](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Unload_Chunk)

Sent when a chunk comes into the client's view distance, specifying its terrain, lighting and block entities.

The chunk must be within the view area previously specified with [Set Center Chunk](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Set_Center_Chunk); see that packet for details.

It is not strictly necessary to send all block entities in this packet; it is still legal to send them with [Block Entity Data](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Block_Entity_Data) later.

| Clientbound `level_chunk_with_light`, Play ID: 46 (0x2E) |
| --- |
| Field Name | Field Type | Notes |
| Chunk X | [Int](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Int) | Chunk coordinate (block coordinate divided by 16, rounded down) |
| Chunk Z | [Int](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Int) | Chunk coordinate (block coordinate divided by 16, rounded down) |
| Heightmaps | [Prefixed Array](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Prefixed_Array) of [Heightmap](https://minecraft.wiki/w/Java_Edition_protocol/Chunk_format#Heightmap_structure "Java Edition protocol/Chunk format") | See [Chunk Format#Heightmap structure](https://minecraft.wiki/w/Minecraft_Wiki:Projects/wiki.vg_merge/Chunk_Format#Heightmap_structure "Minecraft Wiki:Projects/wiki.vg merge/Chunk Format") |
| Data | [Prefixed Array](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Prefixed_Array) of [Byte](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Byte) | See [Chunk Format#Data structure](https://minecraft.wiki/w/Minecraft_Wiki:Projects/wiki.vg_merge/Chunk_Format#Data_structure "Minecraft Wiki:Projects/wiki.vg merge/Chunk Format") |
| Block Entities | Packed XZ | [Prefixed Array](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Prefixed_Array) | [Unsigned Byte](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Unsigned_Byte) | The packed section coordinates are relative to the chunk they are in. Values 0-15 are valid. <br>```<br>packed_xz = ((blockX & 15) << 4) | (blockZ & 15) // encode<br>x = packed_xz >> 4, z = packed_xz & 15 // decode<br>``` |
| Y | [Short](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Short) | The height relative to the world |
| Type | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) | The type of block entity |
| Data | [NBT](https://minecraft.wiki/w/Minecraft_Wiki:Projects/wiki.vg_merge/NBT "Minecraft Wiki:Projects/wiki.vg merge/NBT") | The block entity's data, without the X, Y, and Z values |
| Light | [Light Data](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Light_Data) |  |

Unlike the [Update Light](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Update_Light) packet, which uses the same format, setting the bit corresponding to a section to 0 in both of the block light or sky light masks does not appear to be useful, and the results in testing have been highly inconsistent.

#### World Event

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=122&veaction=edit "Edit section: World Event") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=122 "Edit section's source code: World Event")\]

Sent when a client is to play a sound or particle effect.

By default, the Minecraft client adjusts the volume of sound effects based on distance. The final boolean field is used to disable this, and instead, the effect is played from 2 blocks away in the correct direction. Currently, this is only used for effect 1023 (wither spawn), effect 1028 (enderdragon death), and effect 1038 (end portal opening); it is ignored on other effects.

| Clientbound `level_event`, Play ID: 47 (0x2F) |
| --- |
| Field Name | Field Type | Notes |
| Event | [Int](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Int) | The event, see below. |
| Location | [Position](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Position) | The location of the event. |
| Data | [Int](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Int) | Extra data for certain events, see below. |
| Disable Relative Volume | [Boolean](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Boolean) | See above. |

Events:

| ID | Name | Data |
| --- | --- | --- |
| Sound |
| 1000 | Dispenser dispenses |  |
| 1001 | Dispenser fails to dispense |  |
| 1002 | Dispenser shoots |  |
| 1004 | Firework shot |  |
| 1009 | Fire extinguished |  |
| 1010 | Play record | An ID in the `minecraft:item` registry, corresponding to a [record item](https://minecraft.wiki/w/Music_Disc "Music Disc"). If the ID doesn't correspond to a record, the packet is ignored. Any record already being played at the given location is overwritten. See [Data Generators](https://minecraft.wiki/w/Minecraft_Wiki:Projects/wiki.vg_merge/Data_Generators "Minecraft Wiki:Projects/wiki.vg merge/Data Generators") for information on item IDs. |
| 1011 | Stop record |  |
| 1015 | Ghast warns |  |
| 1016 | Ghast shoots |  |
| 1017 | Ender dragon shoots |  |
| 1018 | Blaze shoots |  |
| 1019 | Zombie attacks wooden door |  |
| 1020 | Zombie attacks iron door |  |
| 1021 | Zombie breaks wooden door |  |
| 1022 | Wither breaks block |  |
| 1023 | Wither spawned |  |
| 1024 | Wither shoots |  |
| 1025 | Bat takes off |  |
| 1026 | Zombie infects |  |
| 1027 | Zombie villager converted |  |
| 1028 | Ender dragon dies |  |
| 1029 | Anvil destroyed |  |
| 1030 | Anvil used |  |
| 1031 | Anvil lands |  |
| 1032 | Portal travel |  |
| 1033 | Chorus flower grows |  |
| 1034 | Chorus flower dies |  |
| 1035 | Brewing stand brews |  |
| 1038 | End portal created |  |
| 1039 | Phantom bites |  |
| 1040 | Zombie converts to drowned |  |
| 1041 | Husk converts to zombie by drowning |  |
| 1042 | Grindstone used |  |
| 1043 | Book page turned |  |
| 1044 | Smithing table used |  |
| 1045 | Pointed dripstone landing |  |
| 1046 | Lava dripping on cauldron from dripstone |  |
| 1047 | Water dripping on cauldron from dripstone |  |
| 1048 | Skeleton converts to stray |  |
| 1049 | Crafter successfully crafts item |  |
| 1050 | Crafter fails to craft item |  |
| Particle |
| 1500 | Composter composts |  |
| 1501 | Lava converts block (either water to stone, or removes existing blocks such as torches) |  |
| 1502 | Redstone torch burns out |  |
| 1503 | Ender eye placed in end portal frame |  |
| 1504 | Fluid drips from dripstone |  |
| 1505 | Bone meal particles and sound | How many particles to spawn. |
| 2000 | Dispenser activation smoke | Direction, see below. |
| 2001 | Block break + block break sound | Block state ID from the [global block state palette](https://minecraft.wiki/w/Java_Edition_protocol/Chunk_format#Global_block_state_palette "Java Edition protocol/Chunk format"). |
| 2002 | Splash potion. Particle effect + glass break sound. | RGB color as an integer (e.g. 8364543 for #7FA1FF). |
| 2003 | Eye of ender entity break animation — particles and sound |  |
| 2004 | Spawner spawns mob: smoke + flames |  |
| 2006 | Dragon breath |  |
| 2007 | Instant splash potion. Particle effect + glass break sound. | RGB color as an integer (e.g. 8364543 for #7FA1FF). |
| 2008 | Ender dragon destroys block |  |
| 2009 | Wet sponge vaporizes |  |
| 2010 | Crafter activation smoke | Direction, see below. |
| 2011 | Bee fertilizes plant | How many particles to spawn. |
| 2012 | Turtle egg placed | How many particles to spawn. |
| 2013 | Smash attack (mace) | How many particles to spawn. |
| 3000 | End gateway spawns |  |
| 3001 | Ender dragon resurrected |  |
| 3002 | Electric spark |  |
| 3003 | Copper apply wax |  |
| 3004 | Copper remove wax |  |
| 3005 | Copper scrape oxidation |  |
| 3006 | Sculk charge |  |
| 3007 | Sculk shrieker shriek |  |
| 3008 | Block finished brushing | Block state ID from the [global block state palette](https://minecraft.wiki/w/Java_Edition_protocol/Chunk_format#Global_block_state_palette "Java Edition protocol/Chunk format"). |
| 3009 | Sniffer egg cracks | If 1, 3-6, if any other number, 1-3 particles will be spawned. |
| 3011 | Trial spawner spawns mob (at spawner) |  |
| 3012 | Trial spawner spawns mob (at spawn location) |  |
| 3013 | Trial spawner detects player | Number of players nearby |
| 3014 | Trial spawner ejects item |  |
| 3015 | Vault activates |  |
| 3016 | Vault deactivates |  |
| 3017 | Vault ejects item |  |
| 3018 | Cobweb weaved |  |
| 3019 | Ominous trial spawner detects player | Number of players nearby |
| 3020 | Trial spawner turns ominous | If 0, the sound will be played at 0.3 volume. Otherwise, it is played at full volume. |
| 3021 | Ominous item spawner spawns item |  |

Smoke directions:

| ID | Direction |
| --- | --- |
| 0 | Down |
| 1 | Up |
| 2 | North |
| 3 | South |
| 4 | West |
| 5 | East |

#### Particle

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=123&veaction=edit "Edit section: Particle") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=123 "Edit section's source code: Particle")\]

Displays the specified particle.

| Clientbound `level_particles`, Play ID: 48 (0x30) |
| --- |
| Field Name | Field Type | Notes |
| Particle ID | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) | ID in the `minecraft:particle_type` registry. |
| Data | Varies | Particle data as specified in [Java Edition protocol/Particles](https://minecraft.wiki/w/Java_Edition_protocol/Particles "Java Edition protocol/Particles"). |
| Override Limiter | [Boolean](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Boolean) | Whether normal particle limiting rules should be overridden. |
| Always Visible | [Boolean](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Boolean) | Whether this particle should always be visible. |
| X | [Double](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Double) | X position of the particle. |
| Y | [Double](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Double) | Y position of the particle. |
| Z | [Double](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Double) | Z position of the particle. |
| X Distance | [Float](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Float) | X-axis randomization distance/offset. |
| Y Distance | [Float](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Float) | Y-axis randomization distance/offset. |
| Z Distance | [Float](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Float) | Z-axis randomization distance/offset. |
| X Max Speed | [Float](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Float) | X-axis maximum/randomized speed parameter. |
| Y Max Speed | [Float](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Float) | Y-axis maximum/randomized speed parameter. |
| Z Max Speed | [Float](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Float) | Z-axis maximum/randomized speed parameter. |
| Particle Count | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) | The number of particles to create. |
| Randomization Type | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) [Enum](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Enum) | Controls how the particle is randomized when spawned; see below. |

Randomization Type can be one of the following values:

| ID | Name |
| --- | --- |
| 0 | Default |
| 1 | Alternative |
| 2 | Alternative with speed |

#### Update Light

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=124&veaction=edit "Edit section: Update Light") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=124 "Edit section's source code: Update Light")\]

Updates light levels for a chunk. See [Light](https://minecraft.wiki/w/Light "Light") for information on how lighting works in Minecraft.

| Clientbound `light_update`, Play ID: 49 (0x31) |
| --- |
| Field Name | Field Type | Notes |
| Chunk X | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) | Chunk coordinate (block coordinate divided by 16, rounded down) |
| Chunk Z | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) | Chunk coordinate (block coordinate divided by 16, rounded down) |
| Data | [Light Data](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Light_Data) |  |

A bit will never be set in both the block light mask and the empty block light mask, though it may be present in neither of them (if the block light does not need to be updated for the corresponding chunk section). The same applies to the sky light mask and the empty sky light mask.

#### Login (play)

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=125&veaction=edit "Edit section: Login (play)") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=125 "Edit section's source code: Login (play)")\]

See [protocol encryption](https://minecraft.wiki/w/Protocol_encryption "Protocol encryption") for information on logging in.

| Clientbound `login`, Play ID: 50 (0x32) |
| --- |
| Field Name | Field Type | Notes |
| Entity ID | [Int](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Int) | The player's Entity ID (EID). |
| Is hardcore | [Boolean](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Boolean) |  |
| Dimension Names | [Prefixed Array](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Prefixed_Array) of [Identifier](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Identifier) | Identifiers for all dimensions on the server. |
| Max Players | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) | Was once used by the client to draw the tab list, but now it is ignored. |
| View Distance | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) | Render distance (2-32). |
| Simulation Distance | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) | Server simulation distance. See [Set Simulation Distance](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Set_Simulation_Distance). |
| Reduced Debug Info | [Boolean](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Boolean) | If true, a vanilla client shows reduced information on the [debug screen](https://minecraft.wiki/w/Debug_screen "Debug screen"). For servers in development, this should almost always be false. |
| Enable respawn screen | [Boolean](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Boolean) | Set to false when the doImmediateRespawn gamerule is true. |
| Do limited crafting | [Boolean](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Boolean) | Whether players can only craft recipes they have already unlocked. Currently unused by the client. |
| Dimension Type | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) | The ID of the type of dimension in the `minecraft:dimension_type` registry, defined by the Registry Data packet. |
| Dimension Name | [Identifier](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Identifier) | Name of the dimension being spawned into. |
| Hashed seed | [Long](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Long) | First 8 bytes of the SHA-256 hash of the world's seed. Used client-side for biome noise |
| Game mode | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) [Enum](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Enum) | 0: Survival, 1: Creative, 2: Adventure, 3: Spectator. |
| Previous Game mode | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) [Enum](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Enum) | Optional game mode encoding: 0 means undefined; otherwise the value is the game mode ID plus 1 (1: Survival, 2: Creative, 3: Adventure, 4: Spectator). Vanilla client uses this for the debug (F3 + N & F3 + F4) game mode switch. |
| Is Debug | [Boolean](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Boolean) | True if the world is a [debug mode](https://minecraft.wiki/w/Debug_mode "Debug mode") world; debug mode worlds cannot be modified and have predefined blocks. |
| Is Flat | [Boolean](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Boolean) | True if the world is a [superflat](https://minecraft.wiki/w/Superflat "Superflat") world; flat worlds have different void fog and a horizon at Y=0 instead of Y=63. |
| Has death location | [Boolean](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Boolean) | If true, then the next two fields are present. |
| Death dimension name | [Optional](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Optional) [Identifier](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Identifier) | Name of the dimension the player died in. |
| Death location | [Optional](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Optional) [Position](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Position) | The location that the player died at. |
| Portal cooldown | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) | The number of ticks until the player can use the last used portal again. Looks like it's an attempt to fix MC-180. |
| Sea level | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) |  |
| Online mode | [Boolean](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Boolean) |  |
| Enforces Secure Chat | [Boolean](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Boolean) |  |

#### Low Disk Space Warning

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=126&veaction=edit "Edit section: Low Disk Space Warning") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=126 "Edit section's source code: Low Disk Space Warning")\]

| Clientbound `low_disk_space_warning`, Play ID: 51 (0x33) |
| --- |
| Field Name | Field Type | Notes |
| _no fields_ |

#### Map Data

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=127&veaction=edit "Edit section: Map Data") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=127 "Edit section's source code: Map Data")\]

Updates a rectangular area on a [map](https://minecraft.wiki/w/Map "Map") item.

| Clientbound `map_item_data`, Play ID: 52 (0x34) |
| --- |
| Field Name | Field Type | Notes |
| Map ID | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) | Map ID of the map being modified |
| Scale | [Byte](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Byte) | From 0 for a fully zoomed-in map (1 block per pixel) to 4 for a fully zoomed-out map (16 blocks per pixel) |
| Locked | [Boolean](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Boolean) | True if the map has been locked in a cartography table |
| Icons | Type | [Prefixed Optional](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Prefixed_Optional) [Prefixed Array](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Prefixed_Array) | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) [Enum](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Enum) | See below |
| X | [Byte](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Byte) | Map coordinates: -128 for furthest left, +127 for furthest right |
| Z | [Byte](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Byte) | Map coordinates: -128 for highest, +127 for lowest |
| Direction | [Byte](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Byte) | 0-15 |
| Display Name | [Prefixed Optional](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Prefixed_Optional) [Text Component](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Text_Component) |  |
| Color Patch | Columns | [Unsigned Byte](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Unsigned_Byte) | Number of columns updated |
| Rows | [Optional](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Optional) [Unsigned Byte](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Unsigned_Byte) | Only if Columns is more than 0; number of rows updated |
| X | [Optional](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Optional) [Unsigned Byte](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Unsigned_Byte) | Only if Columns is more than 0; x offset of the westernmost column |
| Z | [Optional](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Optional) [Unsigned Byte](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Unsigned_Byte) | Only if Columns is more than 0; z offset of the northernmost row |
| Data | [Optional](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Optional) [Prefixed Array](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Prefixed_Array) of [Unsigned Byte](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Unsigned_Byte) | Only if Columns is more than 0; see [Map item format](https://minecraft.wiki/w/Map_item_format "Map item format") |

For icons, a direction of 0 is a vertical icon and increments by 22.5° (360/16).

Types are based off of rows and columns in `map_icons.png`:

| Icon type | Result |
| --- | --- |
| 0 | White arrow (players) |
| 1 | Green arrow (item frames) |
| 2 | Red arrow |
| 3 | Blue arrow |
| 4 | White cross |
| 5 | Red pointer |
| 6 | White circle (off-map players) |
| 7 | Small white circle (far-off-map players) |
| 8 | Mansion |
| 9 | Monument |
| 10 | White Banner |
| 11 | Orange Banner |
| 12 | Magenta Banner |
| 13 | Light Blue Banner |
| 14 | Yellow Banner |
| 15 | Lime Banner |
| 16 | Pink Banner |
| 17 | Gray Banner |
| 18 | Light Gray Banner |
| 19 | Cyan Banner |
| 20 | Purple Banner |
| 21 | Blue Banner |
| 22 | Brown Banner |
| 23 | Green Banner |
| 24 | Red Banner |
| 25 | Black Banner |
| 26 | Treasure marker |
| 27 | Desert Village |
| 28 | Plains Village |
| 29 | Savanna Village |
| 30 | Snowy Village |
| 31 | Taiga Village |
| 32 | Jungle Temple |
| 33 | Swamp Hut |
| 34 | Trial Chambers |

#### Merchant Offers

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=128&veaction=edit "Edit section: Merchant Offers") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=128 "Edit section's source code: Merchant Offers")\]

The list of trades a villager NPC is offering.

| Clientbound `merchant_offers`, Play ID: 53 (0x35) |
| --- |
| Field Name | Field Type | Notes |
| Window ID | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) | The ID of the window that is open; this is an int rather than a byte. |
| Trades | Input item 1 | [Prefixed Array](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Prefixed_Array) | Trade Item | See below. The first item the player has to supply for this villager trade. The count of the item stack is the default "price" of this trade. |
| Output item | [Slot](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Slot) | The item the player will receive from this villager trade. |
| Input item 2 | [Prefixed Optional](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Prefixed_Optional) Trade Item | The second item the player has to supply for this villager trade. |
| Trade disabled | [Boolean](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Boolean) | True if the trade is disabled; false if the trade is enabled. |
| Number of trade uses | [Int](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Int) | Number of times the trade has been used so far. If equal to the maximum number of trades, the client will display a red X. |
| Maximum number of trade uses | [Int](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Int) | Number of times this trade can be used before it's exhausted. |
| XP | [Int](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Int) | Amount of XP the villager will earn each time the trade is used. |
| Special Price | [Int](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Int) | Can be zero or negative. The number is added to the price when an item is discounted due to player reputation or other effects. |
| Price Multiplier | [Float](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Float) | Can be low (0.05) or high (0.2). Determines how much demand, player reputation, and temporary effects will adjust the price. |
| Demand | [Int](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Int) | If positive, causes the price to increase. Negative values seem to be treated the same as zero. |
| Villager level | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) | Appears on the trade GUI; meaning comes from the translation key `merchant.level.` \+ level.<br>1: Novice, 2: Apprentice, 3: Journeyman, 4: Expert, 5: Master. |
| Experience | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) | Total experience for this villager (always 0 for the wandering trader). |
| Is regular villager | [Boolean](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Boolean) | True if this is a regular villager; false for the wandering trader. When false, hides the villager level and some other GUI elements. |
| Can restock | [Boolean](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Boolean) | True for regular villagers and false for the wandering trader. If true, the "Villagers restock up to two times per day." message is displayed when hovering over disabled trades. |

Trade Item:

| Field Name | Field Type | Meaning |
| --- | --- | --- |
| Item ID | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) | The [item ID](https://minecraft.wiki/w/Java_Edition_data_values#Blocks "Java Edition data values"). Item IDs are distinct from block IDs; see [Data Generators](https://minecraft.wiki/w/Minecraft_Wiki:Projects/wiki.vg_merge/Data_Generators "Minecraft Wiki:Projects/wiki.vg merge/Data Generators") for more information. |
| Item Count | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) | The item count. |
| Components | Component type | [Prefixed Array](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Prefixed_Array) | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) [Enum](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Enum) | The type of component. See [Structured components](https://minecraft.wiki/w/Java_Edition_protocol/Slot_data#Structured_components "Java Edition protocol/Slot data") for more detail. |
| Component data | Varies | The component-dependent data. See [Structured components](https://minecraft.wiki/w/Java_Edition_protocol/Slot_data#Structured_components "Java Edition protocol/Slot data") for more detail. |

Modifiers can increase or decrease the number of items for the first input slot. The second input slot and the output slot never change the number of items. The number of items may never be less than 1, and never more than the stack size. If special price and demand are both zero, only the default price is displayed. If either is non-zero, then the adjusted price is displayed next to the crossed-out default price. The adjusted prices is calculated as follows:

Adjusted price = default price + floor(default price x multiplier x demand) + special price

[![](https://minecraft.wiki/images/thumb/Merchant-slots.png/300px-Merchant-slots.png?6b2ed)](https://minecraft.wiki/w/File:Merchant-slots.png) The merchant UI, for reference

#### Update Entity Position

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=129&veaction=edit "Edit section: Update Entity Position") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=129 "Edit section's source code: Update Entity Position")\]

This packet is sent by the server when an entity moves a small distance. Position deltas use fixed-point values with 12 fractional bits. In 26.3 the packet can carry either one linear delta or a sequence of stepped deltas. The low bit of Properties stores On Ground; the remaining bits store the step count.

When the step count is 0, one X/Y/Z delta triplet follows. When the step count is greater than 0, exactly that many step records follow, each containing a tick offset and an X/Y/Z delta triplet.

| Condition | Field Name | Field Type | Notes |
| --- | --- | --- | --- |
| Always | Entity ID | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) |  |
| Properties | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) | Bit 0 is On Ground. Bits 1 and above encode the step count (`properties >>> 1`). |
| Step count = 0 | Delta X | [Short](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Short) | Fixed-point X delta with 12 fractional bits. |
| Delta Y | [Short](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Short) | Fixed-point Y delta with 12 fractional bits. |
| Delta Z | [Short](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Short) | Fixed-point Z delta with 12 fractional bits. |
| Step count > 0<br>(the length of the array is Step count) | Tick Offset | [Array](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Array) | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) | Tick offset of this movement step. |
| Delta X | [Short](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Short) | Fixed-point X delta for this step. |
| Delta Y | [Short](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Short) | Fixed-point Y delta for this step. |
| Delta Z | [Short](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Short) | Fixed-point Z delta for this step. |

#### Update Entity Position and Rotation

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=130&veaction=edit "Edit section: Update Entity Position and Rotation") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=130 "Edit section's source code: Update Entity Position and Rotation")\]

This packet is sent by the server when an entity rotates and moves. Position data uses the same Properties and linear/stepped delta encoding as [Update Entity Position](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Update_Entity_Position). Yaw and Pitch follow the complete delta data.

| Condition | Field Name | Field Type | Notes |
| --- | --- | --- | --- |
| Always | Entity ID | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) |  |
| Properties | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) | Bit 0 is On Ground. Bits 1 and above encode the step count (`properties >>> 1`). |
| Step count = 0 | Delta X | [Short](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Short) | Fixed-point X delta with 12 fractional bits. |
| Delta Y | [Short](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Short) | Fixed-point Y delta with 12 fractional bits. |
| Delta Z | [Short](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Short) | Fixed-point Z delta with 12 fractional bits. |
| Step count > 0<br>(the length of the array is Step count) | Tick Offset | [Array](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Array) | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) | Tick offset of this movement step. |
| Delta X | [Short](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Short) | Fixed-point X delta for this step. |
| Delta Y | [Short](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Short) | Fixed-point Y delta for this step. |
| Delta Z | [Short](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Short) | Fixed-point Z delta for this step. |
| Always, after position data | Yaw | [Angle](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Angle) | New angle, not a delta. For entities that have a separately rotating head and body, this sets the rotation of the body while the entity is moving. To rotate the head, and the body while the entity is stationary, use [Set Head Rotation](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Set_Head_Rotation). |
| Pitch | [Angle](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Angle) | New angle, not a delta. |

#### Move Minecart Along Track

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=131&veaction=edit "Edit section: Move Minecart Along Track") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=131 "Edit section's source code: Move Minecart Along Track")\]

| Clientbound `move_minecart_along_track`, Play ID: 56 (0x38) |
| --- |
| Field Name | Field Type | Notes |
| Entity ID | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) |  |
| Steps | X | [Prefixed Array](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Prefixed_Array) | [Double](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Double) |  |
| Y | [Double](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Double) |  |
| Z | [Double](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Double) |  |
| Velocity X | [Double](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Double) |  |
| Velocity Y | [Double](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Double) |  |
| Velocity Z | [Double](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Double) |  |
| Yaw | [Angle](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Angle) |  |
| Pitch | [Angle](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Angle) |  |
| Weight | [Float](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Float) |

#### Update Entity Rotation

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=132&veaction=edit "Edit section: Update Entity Rotation") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=132 "Edit section's source code: Update Entity Rotation")\]

This packet is sent by the server when an entity rotates.

| Clientbound `move_entity_rot`, Play ID: 57 (0x39) |
| --- |
| Field Name | Field Type | Notes |
| Entity ID | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) |  |
| On Ground | [Boolean](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Boolean) |  |
| Yaw | [Angle](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Angle) | New angle, not a delta. For entities that have a separately rotating head and body, this sets the rotation of the body while the entity is moving. To rotate the head, and the body while the entity is stationary, use [Set Head Rotation](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Set_Head_Rotation). |
| Pitch | [Angle](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Angle) | New angle, not a delta. |

#### Move Vehicle (clientbound)

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=133&veaction=edit "Edit section: Move Vehicle (clientbound)") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=133 "Edit section's source code: Move Vehicle (clientbound)")\]

If the player is riding a client-side-controlled vehicle, teleports the vehicle to the specified position. Sent by the vanilla server in response to serverbound [Move Vehicle (serverbound)](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Move_Vehicle_(serverbound)) packets that fail the movement speed check. Note that all fields use absolute positioning and do not allow for relative positioning.

| Clientbound `move_vehicle`, Play ID: 58 (0x3A) |
| --- |
| Field Name | Field Type | Notes |
| X | [Double](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Double) | Absolute position (X coordinate). |
| Y | [Double](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Double) | Absolute position (Y coordinate). |
| Z | [Double](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Double) | Absolute position (Z coordinate). |
| Yaw | [Float](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Float) | Absolute rotation on the vertical axis, in degrees. |
| Pitch | [Float](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Float) | Absolute rotation on the horizontal axis, in degrees. |

#### Open Book

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=134&veaction=edit "Edit section: Open Book") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=134 "Edit section's source code: Open Book")\]

Sent when a player uses the interact key when holding a signed book. This tells the client to open the book GUI.

| Clientbound `open_book`, Play ID: 59 (0x3B) |
| --- |
| Field Name | Field Type | Notes |
| Hand | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) [Enum](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Enum) | 0: Main hand, 1: Off hand . |

#### Open Screen

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=135&veaction=edit "Edit section: Open Screen") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=135 "Edit section's source code: Open Screen")\]

This is sent to the client when it should open an inventory, such as a chest, workbench, furnace, or other container. Resending this packet with the already existing window ID, will update the window title and window type without closing the window.

This message is not sent to clients opening their own inventory, nor do clients inform the server in any way when doing so. From the server's perspective, the inventory is always "open" whenever no other windows are.

For horses, use [Open Horse Screen](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Open_Horse_Screen).

| Clientbound `open_screen`, Play ID: 60 (0x3C) |
| --- |
| Field Name | Field Type | Notes |
| Window ID | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) | An identifier for the window to be displayed. The vanilla server implementation is a counter, starting at 1. There can only be one window at a time; this is only used to ignore outdated packets targeting already-closed windows. Note also that the Window ID field in most other packets is only a single byte, and indeed, the vanilla server wraps around after 100. |
| Window Type | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) | The window type to use for display. Contained in the `minecraft:menu` registry; see [Java Edition protocol/Inventory](https://minecraft.wiki/w/Java_Edition_protocol/Inventory "Java Edition protocol/Inventory") for the different values. |
| Window Title | [Text Component](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Text_Component) | The title of the window. |

#### Open Sign Editor

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=136&veaction=edit "Edit section: Open Sign Editor") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=136 "Edit section's source code: Open Sign Editor")\]

Sent when the client has placed a sign and is allowed to send [Update Sign](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Update_Sign). There must already be a sign at the given location (which the client does not do automatically) - send a [Block Update](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Block_Update) first.

| Clientbound `open_sign_editor`, Play ID: 61 (0x3D) |
| --- |
| Field Name | Field Type | Notes |
| Location | [Position](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Position) |  |
| Text Slot | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) [Enum](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Enum) | Selects which sign text slot is opened; see below. |

Text Slot can be one of the following values:

| ID | Name |
| --- | --- |
| 0 | Back |
| 1 | Front |

#### Place Ghost Recipe

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=137&veaction=edit "Edit section: Place Ghost Recipe") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=137 "Edit section's source code: Place Ghost Recipe")\]

Response to the serverbound packet ( [Place Recipe](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Place_Recipe)), with the same recipe ID. Appears to be used to notify the UI.

| Clientbound `place_ghost_recipe`, Play ID: 64 (0x40) |
| --- |
| Field Name | Field Type | Notes |
| Window ID | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) |  |
| Recipe Display | [Recipe Display](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Recipe_Display) |  |

#### Player Abilities (clientbound)

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=138&veaction=edit "Edit section: Player Abilities (clientbound)") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=138 "Edit section's source code: Player Abilities (clientbound)")\]

The latter 2 floats are used to indicate the flying speed and field of view respectively, while the first byte is used to determine the value of 4 booleans.

| Clientbound `player_abilities`, Play ID: 65 (0x41) |
| --- |
| Field Name | Field Type | Notes |
| Flags | [Byte](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Byte) | Bit field, see below. |
| Flying Speed | [Float](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Float) | 0.05 by default. |
| Field of View Modifier | [Float](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Float) | Modifies the field of view, like a speed potion. A vanilla server will use the same value as the movement speed sent in the [Update Attributes](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Update_Attributes) packet, which defaults to 0.1 for players. |

About the flags:

| Field | Bit |
| --- | --- |
| Invulnerable | 0x01 |
| Flying | 0x02 |
| Allow Flying | 0x04 |
| Creative Mode (Instant Break) | 0x08 |

If Flying is set but Allow Flying is unset, the player is unable to stop flying.

#### Player Chat Message

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=139&veaction=edit "Edit section: Player Chat Message") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=139 "Edit section's source code: Player Chat Message")\]

Main article: [Java Edition protocol/Chat](https://minecraft.wiki/w/Java_Edition_protocol/Chat "Java Edition protocol/Chat")

Sends the client a chat message from a player.

Currently, a lot is unknown about this packet, blank descriptions are for those that are unknown

| Clientbound `player_chat`, Play ID: 66 (0x42) |
| --- |
| Sector | Field Name | Field Type | Notes |
| Header | Global Index | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) | A counter that starts at zero and gets increased by one for each chat message sent to the client. Each client has its own counter. |
| Sender | [UUID](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:UUID) | Used by the vanilla client for the disableChat launch option. Setting both longs to 0 will always display the message regardless of the setting. |
| Index | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) | A counter that starts at zero and gets increased by one for each chat message sent to the client. Each sender has its own counter, which differentiates this with the Global Index field. For example, the message counter of player A and player B are independent). This is used for maintaining the message order. |
| Message Signature bytes | [Prefixed Optional](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Prefixed_Optional) [Byte Array](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Byte_Array) (256) | Cryptography, the signature consists of:<br>- Format version (currently, `1` as a 4-byte array)<br>- the Sender UUID<br>- Session UUID from the [Player Session](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Player_Session) packet<br>- Index<br>- Salt<br>- Timestamp in epoch seconds<br>- the length of the original chat content<br>- the original content itself<br>- the length of Previous Messages<br>- all of the Previous message signatures.<br>These values are hashed with [SHA-256](https://en.wikipedia.org/wiki/SHA-2 "wikipedia:SHA-2") and signed using the [RSA](https://en.wikipedia.org/wiki/RSA_(cryptosystem) "wikipedia:RSA (cryptosystem)") cryptosystem. Modifying any of these values in the packet will cause this signature to fail. This buffer is always 256 bytes long and it is not length-prefixed. |
| Body | Message | [String](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:String) (256) | Raw (optionally) signed sent message content.<br>This is used as the `content` parameter when formatting the message on the client. |
| Timestamp | [Long](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Long) | Represents the time the message was signed as milliseconds since the [epoch](https://en.wikipedia.org/wiki/Unix_time "wikipedia:Unix time"), used to check if the message was received within 2 minutes of it being sent. |
| Salt | [Long](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Long) | Cryptography, used for validating the message signature. |
| [Prefixed Array](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Prefixed_Array) (20) | Message ID | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) | The message ID + 1, used for validating message signature. The next field is present only when value of this field is equal to 0. The message ID is the index of the message in a global [MRU cache](https://en.wikipedia.org/wiki/Cache_replacement_policies#Most_recently_used_.28MRU.29 "w:Cache replacement policies"). |
| Signature | [Optional](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Optional) [Byte Array](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Byte_Array) (256) | The previous message's signature. Contains the same type of data as `Message Signature bytes` (256 bytes) above. Not length-prefixed. |
| Other | Unsigned Content | [Prefixed Optional](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Prefixed_Optional) [Text Component](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Text_Component) |  |
| Filter Type | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) [Enum](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Enum) | If the message has been filtered |
| Filter Type Bits | [Optional](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Optional) [BitSet](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:BitSet) | Only present if the Filter Type is Partially Filtered. Specifies the indices at which characters in the original message string should be replaced with the `#` symbol (i.e., filtered) by the vanilla client |
| Chat Formatting | Chat Type | [ID or](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:ID_or) [Chat Type](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Chat_Type) | Either the type of chat in the `minecraft:chat_type` registry, defined by the [Registry Data](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Registry_Data) packet, or an inline definition. |
| Sender Name | [Text Component](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Text_Component) | The name of the one sending the message, usually the sender's display name.<br>This is used as the `sender` parameter when formatting the message on the client. |
| Target Name | [Prefixed Optional](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Prefixed_Optional) [Text Component](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Text_Component) | The name of the one receiving the message, usually the receiver's display name.<br>This is used as the `target` parameter when formatting the message on the client. |

[![](https://minecraft.wiki/images/thumb/MinecraftChat.drawio4.png/300px-MinecraftChat.drawio4.png?ccc6e)](https://minecraft.wiki/w/File:MinecraftChat.drawio4.png) Player Chat Handling Logic

Filter Types:

The filter type mask should NOT be specified unless partially filtered is selected

| ID | Name | Description |
| --- | --- | --- |
| 0 | PASS\_THROUGH | Message is not filtered at all |
| 1 | FULLY\_FILTERED | Message is fully filtered |
| 2 | PARTIALLY\_FILTERED | Only some characters in the message are filtered |

#### End Combat

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=140&veaction=edit "Edit section: End Combat") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=140 "Edit section's source code: End Combat")\]

Unused by the vanilla client. This data was once used for twitch.tv metadata circa 1.8.

| Clientbound `player_combat_end`, Play ID: 67 (0x43) |
| --- |
| Field Name | Field Type | Notes |
| Duration | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) | Length of the combat in ticks. |

#### Enter Combat

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=141&veaction=edit "Edit section: Enter Combat") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=141 "Edit section's source code: Enter Combat")\]

Unused by the vanilla client. This data was once used for twitch.tv metadata circa 1.8.

| Clientbound `player_combat_enter`, Play ID: 68 (0x44) |
| --- |
| Field Name | Field Type | Notes |
| _no fields_ |

#### Combat Death

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=142&veaction=edit "Edit section: Combat Death") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=142 "Edit section's source code: Combat Death")\]

Used to send a respawn screen.

| Clientbound `player_combat_kill`, Play ID: 69 (0x45) |
| --- |
| Field Name | Field Type | Notes |
| Player ID | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) | Entity ID of the player that died (should match the client's entity ID). |
| Message | [Text Component](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Text_Component) | The death message. |

#### Player Info Remove

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=143&veaction=edit "Edit section: Player Info Remove") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=143 "Edit section's source code: Player Info Remove")\]

Sent by the server to remove players from the client's player list.

| Clientbound `player_info_remove`, Play ID: 70 (0x46) |
| --- |
| Field Name | Field Type | Notes |
| UUIDs | [Prefixed Array](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Prefixed_Array) of [UUID](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:UUID) | UUIDs of players to remove. |

#### Player Info Update

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=144&veaction=edit "Edit section: Player Info Update") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=144 "Edit section's source code: Player Info Update")\]

Sent by the server to add or update players on the client's player list. The player list determines which player names can be tab-completed, player skins (player profiles), player display names and who shows up on the tab list (<tab> in the client).

| Clientbound `player_info_update`, Play ID: 71 (0x47) |
| --- |
| Field Name | Field Type | Notes |
| Actions | [Unsigned Byte](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Unsigned_Byte) | Determines what actions are present. |
| Players | UUID | [Prefixed Array](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Prefixed_Array) | [UUID](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:UUID) | The player UUID |
| Player Actions | [Array](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Array) of [Player Actions](https://minecraft.wiki/w/Java_Edition_protocol/Packets#player-info:player-actions) | The length of this array is determined by the number of [Player Actions](https://minecraft.wiki/w/Java_Edition_protocol/Packets#player-info:player-actions) that give a non-zero value when applying its mask to the actions flag. For example, given the decimal number 5, binary 00000101. The masks 0x01 and 0x04 would return a non-zero value, meaning the Player Actions array would include two actions: Add Player and Update Game Mode. |

| Action | Mask | Field Name | Type | Notes |
| --- | --- | --- | --- | --- |
| Add Player | 0x01 | Name | [String](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:String) (16) |  |
| [Game Profile](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Game_Profile) properties | Name | [Prefixed Array](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Prefixed_Array) (16) | [String](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:String) (64) |  |
| Value | [String](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:String) (32767) |  |
| Signature | [Prefixed Optional](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Prefixed_Optional) [String](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:String) (1024) |  |
| Initialize Chat | 0x02 | Data | Chat session ID | [Prefixed Optional](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Prefixed_Optional) | [UUID](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:UUID) |  |
| Public key expiry time | [Long](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Long) | Key expiry time, as a UNIX timestamp in milliseconds. Only sent if Has Signature Data is true. |
| Encoded public key | [Prefixed Array](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Prefixed_Array) (512) of [Byte](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Byte) | The player's public key, in bytes. Only sent if Has Signature Data is true. |
| Public key signature | [Prefixed Array](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Prefixed_Array) (4096) of [Byte](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Byte) | The public key's digital signature. Only sent if Has Signature Data is true. |
| Update Game Mode | 0x04 | Game Mode | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) |
| Update Listed | 0x08 | Listed | [Boolean](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Boolean) | Whether the player should be listed on the tab list. |
| Update Latency | 0x10 | Ping | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) | Measured in milliseconds. |
| Update Display Name | 0x20 | Display Name | [Prefixed Optional](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Prefixed_Optional) [Text Component](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Text_Component) |
| Update List Priority | 0x40 | Priority | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) | See below. |
| Update Hat | 0x80 | Visible | [Boolean](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Boolean) | Whether the player's hat skin layer is shown. |

Player Actions

The properties included in this packet are the same as in [Login Success](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Login_Success), for the current player.

Ping values correspond with icons in the following way:

- A ping that is negative (i.e., not known to the server yet) will result in the no connection icon.
- A ping under 150 milliseconds will result in 5 bars
- A ping under 300 milliseconds will result in 4 bars
- A ping under 600 milliseconds will result in 3 bars
- A ping under 1000 milliseconds (1 second) will result in 2 bars
- A ping greater than or equal to 1 second will result in 1 bar.

The order of players on the tab list is determined as follows:

- Players with higher priorities are sorted before those with lower priorities.
- Among players of equal priorities, spectators are sorted after non-spectators.
- Within each of those groups, players are sorted into teams. The teams are ordered case-sensitively by team name in ascending order. Players with no team are listed first.
- The players of each team (and non-team) are sorted case-insensitively by name in ascending order.

#### Look At

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=145&veaction=edit "Edit section: Look At") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=145 "Edit section's source code: Look At")\]

Used to rotate the client player to face the given location or entity (for `/teleport [<targets>] <x> <y> <z> facing`).

| Clientbound `player_look_at`, Play ID: 72 (0x48) |
| --- |
| Field Name | Field Type | Notes |
| Feet/eyes | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) [Enum](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Enum) | Values are feet=0, eyes=1. If set to eyes, aims using the head position; otherwise, aims using the feet position. |
| Target x | [Double](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Double) | x coordinate of the point to face towards. |
| Target y | [Double](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Double) | y coordinate of the point to face towards. |
| Target z | [Double](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Double) | z coordinate of the point to face towards. |
| Is entity | [Boolean](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Boolean) | If true, additional information about an entity is provided. |
| Entity ID | [Optional](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Optional) [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) | Only if is entity is true — the entity to face towards. |
| Entity feet/eyes | [Optional](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Optional) [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) [Enum](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Enum) | Whether to look at the entity's eyes or feet. Same values and meanings as before, just for the entity's head/feet. |

If the entity given by entity ID cannot be found, this packet should be treated as if is entity was false.

#### Synchronize Player Position

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=146&veaction=edit "Edit section: Synchronize Player Position") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=146 "Edit section's source code: Synchronize Player Position")\]

Teleports the client, e.g., during login, when using an ender pearl, in response to invalid move packets, etc.

Due to latency, the server may receive outdated movement packets sent before the client was aware of the teleport. To account for this, the server ignores movement packets until a [Confirm Teleportation](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Confirm_Teleportation) packet with an ID matching the one sent in the teleport packet is received. In 26.3, that confirmation packet also echoes the resulting X, Y, Z, yaw, and pitch. The vanilla client also sends a [Set Player Position and Rotation](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Set_Player_Position_and_Rotation) packet after the confirmation.

Yaw is measured in degrees and does not follow classical trigonometry rules. The unit circle of yaw on the XZ-plane starts at (0, 1) and turns counterclockwise, with 90 at (-1, 0), 180 at (0, -1) and 270 at (1, 0). Additionally, yaw is not clamped to between 0 and 360 degrees; any number is valid, including negative numbers and numbers greater than 360 (see [MC-90097](https://bugs.mojang.com/browse/MC-90097)).

Pitch is measured in degrees, where 0 is looking straight ahead, -90 is looking straight up, and 90 is looking straight down.

If the player is riding a vehicle, this packet has no effect, but both the [Confirm Teleportation](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Confirm_Teleportation) and [Set Player Position and Rotation](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Set_Player_Position_and_Rotation) packets are still sent.

| Clientbound `player_position`, Play ID: 73 (0x49) |
| --- |
| Field Name | Field Type | Notes |
| Teleport ID | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) | Client should confirm this packet with [Confirm Teleportation](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Confirm_Teleportation) containing the same Teleport ID. |
| X | [Double](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Double) | Absolute or relative position, depending on Flags. |
| Y | [Double](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Double) | Absolute or relative position, depending on Flags. |
| Z | [Double](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Double) | Absolute or relative position, depending on Flags. |
| Velocity X | [Double](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Double) |  |
| Velocity Y | [Double](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Double) |  |
| Velocity Z | [Double](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Double) |  |
| Yaw | [Float](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Float) | Absolute or relative rotation on the X axis, in degrees. |
| Pitch | [Float](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Float) | Absolute or relative rotation on the Y axis, in degrees. |
| Flags | [Teleport Flags](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Teleport_Flags) |  |

#### Player Rotation

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=147&veaction=edit "Edit section: Player Rotation") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=147 "Edit section's source code: Player Rotation")\]

| Clientbound `player_rotation`, Play ID: 74 (0x4A) |
| --- |
| Field Name | Field Type | Notes |
| Yaw | [Float](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Float) | Rotation on the X axis, in degrees. |
| Relative Yaw | [Boolean](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Boolean) |  |
| Pitch | [Float](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Float) | Rotation on the Y axis, in degrees. |
| Relative Pitch | [Boolean](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Boolean) |  |

#### Recipe Book Add

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=148&veaction=edit "Edit section: Recipe Book Add") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=148 "Edit section's source code: Recipe Book Add")\]

| Clientbound `recipe_book_add`, Play ID: 75 (0x4B) |
| --- |
| Field Name | Field Type | Notes |
| Recipes | Recipe ID | [Prefixed Array](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Prefixed_Array) | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) | ID to assign to the recipe. |
| Display | [Recipe Display](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Recipe_Display) |  |
| Group ID | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) |  |
| Category ID | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) | ID in the `minecraft:recipe_book_category` registry. |
| Ingredients | [Prefixed Optional](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Prefixed_Optional) [Prefixed Array](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Prefixed_Array) of [ID Set](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:ID_Set) | IDs in the `minecraft:item` registry, or an inline definition. |
| Flags | [Byte](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Byte) | 0x01: show notification; 0x02: highlight as new |
| Replace | [Boolean](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Boolean) | Replace or Add to known recipes |

#### Recipe Book Remove

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=149&veaction=edit "Edit section: Recipe Book Remove") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=149 "Edit section's source code: Recipe Book Remove")\]

| Clientbound `recipe_book_remove`, Play ID: 76 (0x4C) |
| --- |
| Field Name | Field Type | Notes |
| Recipes | [Prefixed Array](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Prefixed_Array) of [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) | IDs of recipes to remove. |

#### Recipe Book Settings

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=150&veaction=edit "Edit section: Recipe Book Settings") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=150 "Edit section's source code: Recipe Book Settings")\]

| Clientbound `recipe_book_settings`, Play ID: 77 (0x4D) |
| --- |
| Field Name | Field Type | Notes |
| Crafting Recipe Book Open | [Boolean](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Boolean) | If true, then the crafting recipe book will be open when the player opens its inventory. |
| Crafting Recipe Book Filter Active | [Boolean](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Boolean) | If true, then the filtering option is active when the player opens its inventory. |
| Smelting Recipe Book Open | [Boolean](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Boolean) | If true, then the smelting recipe book will be open when the player opens its inventory. |
| Smelting Recipe Book Filter Active | [Boolean](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Boolean) | If true, then the filtering option is active when the player opens its inventory. |
| Blast Furnace Recipe Book Open | [Boolean](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Boolean) | If true, then the blast furnace recipe book will be open when the player opens its inventory. |
| Blast Furnace Recipe Book Filter Active | [Boolean](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Boolean) | If true, then the filtering option is active when the player opens its inventory. |
| Smoker Recipe Book Open | [Boolean](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Boolean) | If true, then the smoker recipe book will be open when the player opens its inventory. |
| Smoker Recipe Book Filter Active | [Boolean](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Boolean) | If true, then the filtering option is active when the player opens its inventory. |

#### Remove Entities

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=151&veaction=edit "Edit section: Remove Entities") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=151 "Edit section's source code: Remove Entities")\]

Sent by the server when an entity is to be destroyed on the client.

| Clientbound `remove_entities`, Play ID: 78 (0x4E) |
| --- |
| Field Name | Field Type | Notes |
| Entity IDs | [Prefixed Array](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Prefixed_Array) of [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) | The list of entities to destroy. |

#### Remove Entity Effect

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=152&veaction=edit "Edit section: Remove Entity Effect") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=152 "Edit section's source code: Remove Entity Effect")\]

| Clientbound `remove_mob_effect`, Play ID: 79 (0x4F) |
| --- |
| Field Name | Field Type | Notes |
| Entity ID | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) |  |
| Effect ID | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) | See [this table](https://minecraft.wiki/w/Status_effect#Effect_list "Status effect"). |

#### Reset Score

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=153&veaction=edit "Edit section: Reset Score") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=153 "Edit section's source code: Reset Score")\]

This is sent to the client when it should remove a scoreboard item.

| Clientbound `reset_score`, Play ID: 80 (0x50) |
| --- |
| Field Name | Field Type | Notes |
| Entity Name | [String](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:String) (32767) | The entity whose score this is. For players, this is their username; for other entities, it is their UUID. |
| Objective Name | [Prefixed Optional](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Prefixed_Optional) [String](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:String) (32767) | The name of the objective the score belongs to. |

#### Respawn

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=154&veaction=edit "Edit section: Respawn") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=154 "Edit section's source code: Respawn")\]

[![](https://minecraft.wiki/images/Information_icon.svg?15c1c)](https://minecraft.wiki/w/File:Information_icon.svg "File:Information icon.svg")

This section is missing information about: Although the number of portal cooldown ticks is included in this packet, the whole portal usage process is still dictated entirely by the server. What kind of effect does this value have on the client, if any?

Please expand the section to include this information. Further details may exist on the [talk page](https://minecraft.wiki/w/Talk:Java_Edition_protocol/Packets).

To change the player's dimension (overworld/nether/end), send them a respawn packet with the appropriate dimension, followed by prechunks/chunks for the new dimension, and finally a position and look packet. You do not need to unload chunks; the client will do it automatically.

The background of the loading screen is determined based on the Dimension Name specified in this packet and the one specified in the previous Login or Respawn packet. If either the current or the previous dimension is `minecraft:nether`, the Nether portal background is used. Otherwise, if the current or the previous dimension is `minecraft:the_end`, the End portal background is used. If the player is dead (health is 0), the default background is always used.

| Clientbound `respawn`, Play ID: 84 (0x54) |
| --- |
| Field Name | Field Type | Notes |
| Dimension Type | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) | The ID of type of dimension in the `minecraft:dimension_type` registry, defined by the [Registry Data](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Registry_Data) packet. |
| Dimension Name | [Identifier](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Identifier) | Name of the dimension being spawned into. |
| Hashed seed | [Long](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Long) | First 8 bytes of the SHA-256 hash of the world's seed. Used client-side for biome noise |
| Game mode | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) [Enum](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Enum) | 0: Survival, 1: Creative, 2: Adventure, 3: Spectator. |
| Previous Game mode | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) [Enum](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Enum) | Optional game mode encoding: 0 means undefined; otherwise the value is the game mode ID plus 1 (1: Survival, 2: Creative, 3: Adventure, 4: Spectator). Vanilla client uses this for the debug (F3 + N & F3 + F4) game mode switch. |
| Is Debug | [Boolean](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Boolean) | True if the world is a [debug mode](https://minecraft.wiki/w/Debug_mode "Debug mode") world; debug mode worlds cannot be modified and have predefined blocks. |
| Is Flat | [Boolean](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Boolean) | True if the world is a [superflat](https://minecraft.wiki/w/Superflat "Superflat") world; flat worlds have different void fog and a horizon at y=0 instead of y=63. |
| Has death location | [Boolean](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Boolean) | If true, then the next two fields are present. |
| Death dimension Name | [Optional](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Optional) [Identifier](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Identifier) | Name of the dimension the player died in. |
| Death location | [Optional](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Optional) [Position](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Position) | The location that the player died at. |
| Portal cooldown | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) | The number of ticks until the player can use the portal again. |
| Sea level | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) |  |
| Data kept | [Byte](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Byte) | Bit mask. 0x01: Keep attributes, 0x02: Keep metadata. Tells which data should be kept on the client side once the player has respawned.<br>In the vanilla implementation, this is context-dependent:<br>- normal respawns (after death) keep no data;<br>- exiting the end poem/credits keeps the attributes;<br>- other dimension changes (portals or teleports) keep all data. |

[![](https://minecraft.wiki/images/thumb/Ambox_warning_pn.png/32px-Ambox_warning_pn.png?b6e1c)](https://minecraft.wiki/w/File:Ambox_warning_pn.png "File:Ambox warning pn.png")

Avoid changing a player's dimension to the same dimension they were already in unless they are dead. If you change the dimension to one they are already in, weird bugs can occur, such as the player being unable to attack other players in the new world (until they die and respawn).
Before 1.16, if you must respawn a player in the same dimension without killing them, send two respawn packets, one to a different world and then another to the world you want. You do not need to complete the first respawn; it only matters that you send two packets.

#### Set Head Rotation

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=155&veaction=edit "Edit section: Set Head Rotation") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=155 "Edit section's source code: Set Head Rotation")\]

Changes the horizontal rotation of an entity's head.

While the entity is stationary (its position is not changing, but rotation may be), the body is also rotated towards this direction after a delay. This does not change the actual yaw value of the entity, and the body rotates back towards the yaw when the entity starts moving.

While the entity is moving, the head rotation is clamped to a maximum distance from the body rotation. This permanently changes the head rotation value until updated again by the server.

For player entities (other than the client's local player), the vanilla server always updates the head rotation to be the same as the yaw set in [Set Player Rotation](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Set_Player_Rotation). The client-side behavior for remote players is the same as for other entities with a separately rotating head.

| Clientbound `rotate_head`, Play ID: 85 (0x55) |
| --- |
| Field Name | Field Type | Notes |
| Entity ID | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) |  |
| Head Yaw | [Angle](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Angle) | New angle, not a delta. |

#### Update Section Blocks

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=156&veaction=edit "Edit section: Update Section Blocks") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=156 "Edit section's source code: Update Section Blocks")\]

Fired whenever 2 or more blocks are changed within the same chunk on the same tick.

| Clientbound `section_blocks_update`, Play ID: 86 (0x56) |
| --- |
| Field Name | Field Type | Notes |
| Chunk section position | [Long](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Long) | Chunk section coordinate (encoded chunk x and z with each 22 bits, and section y with 20 bits, from left to right). |
| Blocks | [Prefixed Array](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Prefixed_Array) of [VarLong](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarLong) | Each entry is composed of the block state id, shifted left by 12, and the relative block position in the chunk section (4 bits for x, z, and y, from left to right). |

Chunk section position is encoded:

```
((sectionX & 0x3FFFFF) << 42) | (sectionY & 0xFFFFF) | ((sectionZ & 0x3FFFFF) << 20);
```

and decoded:

```
sectionX = long >> 42;
sectionY = long << 44 >> 44;
sectionZ = long << 22 >> 42;
```

Blocks are encoded:

```
blockStateId << 12 | (blockLocalX << 8 | blockLocalZ << 4 | blockLocalY)
//Uses the local position of the given block position relative to its respective chunk section
```

and decoded:

```
blockStateId = long >> 12;
blockLocalX = (long >> 8) & 0xF;
blockLocalY = long & 0xF;
blockLocalZ = (long >> 4) & 0xF;
```

#### Select Advancements Tab

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=157&veaction=edit "Edit section: Select Advancements Tab") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=157 "Edit section's source code: Select Advancements Tab")\]

Sent by the server to indicate that the client should switch advancement tab. Sent either when the client switches tab in the GUI or when an advancement is made in another tab.

| Clientbound `select_advancements_tab`, Play ID: 87 (0x57) |
| --- |
| Field Name | Field Type | Notes |
| Identifier | [Prefixed Optional](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Prefixed_Optional) [Identifier](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Identifier) | See below. |

The [Identifier](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Identifier) must be one of the following if no custom data pack is loaded:

| Identifier |
| --- |
| minecraft:story/root |
| minecraft:nether/root |
| minecraft:end/root |
| minecraft:adventure/root |
| minecraft:husbandry/root |

If no or an invalid identifier is sent, the client will switch to the first tab in the GUI.

#### Server Data

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=158&veaction=edit "Edit section: Server Data") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=158 "Edit section's source code: Server Data")\]

| Clientbound `server_data`, Play ID: 88 (0x58) |
| --- |
| Field Name | Field Type | Notes |
| MOTD | [Text Component](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Text_Component) |  |
| Icon | [Prefixed Optional](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Prefixed_Optional) [Prefixed Array](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Prefixed_Array) of [Byte](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Byte) | Icon bytes in the PNG format. |

#### Set Action Bar Text

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=159&veaction=edit "Edit section: Set Action Bar Text") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=159 "Edit section's source code: Set Action Bar Text")\]

Displays a message above the hotbar. Equivalent to [System Chat Message](https://minecraft.wiki/w/Java_Edition_protocol/Packets#System_Chat_Message) with Overlay set to true, except that [chat message blocking](https://minecraft.wiki/w/Java_Edition_protocol/Chat#Social_Interactions_(blocking) "Java Edition protocol/Chat") isn't performed. Used by the vanilla server only to implement the `/title` command.

| Clientbound `set_action_bar_text`, Play ID: 89 (0x59) |
| --- |
| Field Name | Field Type | Notes |
| Action bar text | [Text Component](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Text_Component) |

#### Set Border Center

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=160&veaction=edit "Edit section: Set Border Center") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=160 "Edit section's source code: Set Border Center")\]

| Clientbound `set_border_center`, Play ID: 90 (0x5A) |
| --- |
| Field Name | Field Type | Notes |
| X | [Double](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Double) |  |
| Z | [Double](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Double) |  |

#### Set Border Lerp Size

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=161&veaction=edit "Edit section: Set Border Lerp Size") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=161 "Edit section's source code: Set Border Lerp Size")\]

| Clientbound `set_border_lerp_size`, Play ID: 91 (0x5B) |
| --- |
| Field Name | Field Type | Notes |
| Old Diameter | [Double](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Double) | Current length of a single side of the world border, in meters. |
| New Diameter | [Double](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Double) | Target length of a single side of the world border, in meters. |
| Speed | [VarLong](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarLong) | Number of real-time _milli_ seconds until New Diameter is reached. It appears that vanilla server does not sync world border speed to game ticks, so it gets out of sync with server lag. If the world border is not moving, this is set to 0. |

#### Set Border Size

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=162&veaction=edit "Edit section: Set Border Size") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=162 "Edit section's source code: Set Border Size")\]

| Clientbound `set_border_size`, Play ID: 92 (0x5C) |
| --- |
| Field Name | Field Type | Notes |
| Diameter | [Double](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Double) | Length of a single side of the world border, in meters. |

#### Set Border Warning Delay

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=163&veaction=edit "Edit section: Set Border Warning Delay") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=163 "Edit section's source code: Set Border Warning Delay")\]

| Clientbound `set_border_warning_delay`, Play ID: 93 (0x5D) |
| --- |
| Field Name | Field Type | Notes |
| Warning Time | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) | In seconds as set by `/worldborder warning time`. |

#### Set Border Warning Distance

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=164&veaction=edit "Edit section: Set Border Warning Distance") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=164 "Edit section's source code: Set Border Warning Distance")\]

| Clientbound `set_border_warning_distance`, Play ID: 94 (0x5E) |
| --- |
| Field Name | Field Type | Notes |
| Warning Blocks | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) | In meters. |

#### Set Camera

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=165&veaction=edit "Edit section: Set Camera") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=165 "Edit section's source code: Set Camera")\]

Sets the entity that the player renders from. This is normally used when the player left-clicks an entity while in spectator mode.

The player's camera will move with the entity and look where it is looking. The entity is often another player, but can be any type of entity. The player is unable to move this entity (move packets will act as if they are coming from the other entity).

If the given entity is not loaded by the player, this packet is ignored. To return control to the player, send this packet with their entity ID.

The vanilla server resets this (sends it back to the default entity) whenever the spectated entity is killed or the player sneaks, but only if they were spectating an entity. It also sends this packet whenever the player switches out of spectator mode (even if they weren't spectating an entity).

| Clientbound `set_camera`, Play ID: 95 (0x5F) |
| --- |
| Field Name | Field Type | Notes |
| Camera ID | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) | ID of the entity to set the client's camera to. |

The vanilla client also loads certain shaders for given entities:

- Creeper → `shaders/post/creeper.json`
- Spider (and cave spider) → `shaders/post/spider.json`
- Enderman → `shaders/post/invert.json`
- Anything else → the current shader is unloaded

#### Set Center Chunk

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=166&veaction=edit "Edit section: Set Center Chunk") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=166 "Edit section's source code: Set Center Chunk")\]

Sets the center position of the client's chunk loading area. The area is square-shaped, spanning 2 × server view distance + 7 chunks on both axes (width, not radius!). Since the area's width is always an odd number, there is no ambiguity as to which chunk is the center.

The vanilla client never renders or simulates chunks located outside the loading area, but keeps them in memory (unless explicitly unloaded by the server while still in range), and only automatically unloads a chunk when another chunk is loaded at coordinates congruent to the old chunk's coordinates modulo (2 × server view distance + 7). This means that a chunk may reappear after leaving and later re-entering the loading area through successive uses of this packet, unless it is replaced in the meantime by a different chunk in the same "slot".

The vanilla client ignores attempts to load or unload chunks located outside the loading area. This applies even to unloads targeting chunks that are still loaded, but currently located outside the loading area (per the previous paragraph).

The vanilla server does not rely on any specific behavior for chunks leaving the loading area, and custom clients need not replicate the above exactly. A client may instead choose to immediately unload any chunks outside the loading area, to use a different modulus, or to ignore the loading area completely and keep chunks loaded regardless of their location until the server requests to unload them. Servers aiming for maximal interoperability should always explicitly unload any loaded chunks before they go outside the loading area.

The center chunk is normally the chunk the player is in, but apart from the implications on chunk loading, the (vanilla) client takes no issue with this not being the case. Indeed, as long as chunks are sent only within the default loading area centered on the world origin, it is not necessary to send this packet at all. This may be useful for servers with small bounded worlds, such as minigames, since it ensures chunks never need to be resent after the client has joined, saving on bandwidth.

The vanilla server sends this packet whenever the player moves across a chunk border horizontally, and also (according to testing) for any integer change in the vertical axis, even if it doesn't go across a chunk section border.

| Clientbound `set_chunk_cache_center`, Play ID: 96 (0x60) |
| --- |
| Field Name | Field Type | Notes |
| Chunk X | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) | Chunk X coordinate of the loading area center. |
| Chunk Z | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) | Chunk Z coordinate of the loading area center. |

#### Set Render Distance

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=167&veaction=edit "Edit section: Set Render Distance") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=167 "Edit section's source code: Set Render Distance")\]

Sent by the integrated singleplayer server when changing render distance. This packet is sent by the server when the client reappears in the overworld after leaving the end.

| Clientbound `set_chunk_cache_radius`, Play ID: 97 (0x61) |
| --- |
| Field Name | Field Type | Notes |
| View Distance | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) | Render distance (2-32). |

#### Set Cursor Item

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=168&veaction=edit "Edit section: Set Cursor Item") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=168 "Edit section's source code: Set Cursor Item")\]

Replaces or sets the inventory item that's being dragged with the mouse.

| Clientbound `set_cursor_item`, Play ID: 98 (0x62) |
| --- |
| Field Name | Field Type | Notes |
| Carried item | [Slot](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Slot) |  |

#### Set Default Spawn Position

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=169&veaction=edit "Edit section: Set Default Spawn Position") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=169 "Edit section's source code: Set Default Spawn Position")\]

Sent by the server after login to specify the coordinates of the spawn point (the point at which players spawn at, and which the compass points to). It can be sent at any time to update the point compasses point at.

Before receiving this packet, the client uses the default position 8, 64, 8, and angle 0.0.

| Clientbound `set_default_spawn_position`, Play ID: 99 (0x63) |
| --- |
| Field Name | Field Type | Notes |
| Dimension Name | [Identifier](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Identifier) | Name of spawn dimension. |
| Location | [Position](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Position) | Spawn location. |
| Yaw | [Float](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Float) | Yaw after respawning. |
| Pitch | [Float](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Float) | Pitch after respawning. |

#### Display Objective

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=170&veaction=edit "Edit section: Display Objective") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=170 "Edit section's source code: Display Objective")\]

This is sent to the client when it should display a scoreboard.

| Clientbound `set_display_objective`, Play ID: 100 (0x64) |
| --- |
| Field Name | Field Type | Notes |
| Position | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) | The position of the scoreboard. 0: list, 1: sidebar, 2: below name, 3 - 18: team-specific sidebar, indexed as 3 + team color. |
| Score Name | [String](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:String) (32767) | The unique name for the scoreboard to be displayed. |

#### Set Entity Metadata

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=171&veaction=edit "Edit section: Set Entity Metadata") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=171 "Edit section's source code: Set Entity Metadata")\]

Updates one or more [metadata](https://minecraft.wiki/w/Java_Edition_protocol/Entity_metadata#Entity_Metadata_Format "Java Edition protocol/Entity metadata") properties for an existing entity. Any properties not included in the Metadata field are left unchanged.

| Clientbound `set_entity_data`, Play ID: 101 (0x65) |
| --- |
| Field Name | Field Type | Notes |
| Entity ID | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) |  |
| Metadata | [Entity Metadata](https://minecraft.wiki/w/Java_Edition_protocol/Entity_metadata#Entity_Metadata_Format "Java Edition protocol/Entity metadata") |  |

#### Link Entities

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=172&veaction=edit "Edit section: Link Entities") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=172 "Edit section's source code: Link Entities")\]

This packet is sent when an entity has been [leashed](https://minecraft.wiki/w/Lead "Lead") to another entity.

| Clientbound `set_entity_link`, Play ID: 102 (0x66) |
| --- |
| Field Name | Field Type | Notes |
| Attached Entity ID | [Int](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Int) | Attached entity's EID. |
| Holding Entity ID | [Int](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Int) | ID of the entity holding the lead. Set to -1 to detach. |

#### Set Entity Velocity

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=173&veaction=edit "Edit section: Set Entity Velocity") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=173 "Edit section's source code: Set Entity Velocity")\]

| Clientbound `set_entity_motion`, Play ID: 103 (0x67) |
| --- |
| Field Name | Field Type | Notes |
| Entity ID | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) |  |
| Velocity | [LpVec3](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:LpVec3) |  |

#### Set Equipment

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=174&veaction=edit "Edit section: Set Equipment") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=174 "Edit section's source code: Set Equipment")\]

| Clientbound `set_equipment`, Play ID: 104 (0x68) |
| --- |
| Field Name | Field Type | Notes |
| Entity ID | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) | Entity's ID. |
| Equipment | Slot | [Array](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Array) | [Byte](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Byte) [Enum](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Enum) | The length of the array is not known beforehand and has to be determined by reading all entries, as the most significant bit of the slot indicates if there is a next entry. | Equipment slot (see below). Also has the top bit set if another entry follows, and otherwise unset if this is the last item in the array. |
| Item | [Slot](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Slot) |  |

Equipment slot can be one of the following:

| ID | Equipment slot |
| --- | --- |
| 0 | Main hand |
| 1 | Off hand |
| 2 | Boots |
| 3 | Leggings |
| 4 | Chestplate |
| 5 | Helmet |
| 6 | Body |
| 7 | Saddle |

#### Set Experience

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=175&veaction=edit "Edit section: Set Experience") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=175 "Edit section's source code: Set Experience")\]

Sent by the server when the client should change experience levels.

| Clientbound `set_experience`, Play ID: 105 (0x69) |
| --- |
| Field Name | Field Type | Notes |
| Experience bar | [Float](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Float) | Between 0 and 1. |
| Level | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) |  |
| Total Experience | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) | See [Experience#Leveling up](https://minecraft.wiki/w/Experience#Leveling_up "Experience") on the Minecraft Wiki for Total Experience to Level conversion. |

#### Set Health

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=176&veaction=edit "Edit section: Set Health") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=176 "Edit section's source code: Set Health")\]

Sent by the server to set the health of the player it is sent to.

Food [saturation](https://minecraft.wiki/w/Food#Hunger_and_saturation "Food") acts as a food “overcharge”. Food values will not decrease while the saturation is over zero. New players logging in or respawning automatically get a saturation of 5.0. Eating food increases the saturation as well as the food bar.

| Clientbound `set_health`, Play ID: 106 (0x6A) |
| --- |
| Field Name | Field Type | Notes |
| Health | [Float](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Float) | 0 or less = dead, 20 = full HP. |
| Food | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) | 0–20. |
| Food Saturation | [Float](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Float) | Seems to vary from 0.0 to 5.0 in integer increments. |

#### Set Held Item (clientbound)

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=177&veaction=edit "Edit section: Set Held Item (clientbound)") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=177 "Edit section's source code: Set Held Item (clientbound)")\]

Sent to change the player's slot selection.

| Clientbound `set_held_slot`, Play ID: 107 (0x6B) |
| --- |
| Field Name | Field Type | Notes |
| Slot | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) | The slot which the player has selected (0–8). |

#### Update Objectives

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=178&veaction=edit "Edit section: Update Objectives") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=178 "Edit section's source code: Update Objectives")\]

This is sent to the client when it should create a new [scoreboard](https://minecraft.wiki/w/Scoreboard "Scoreboard") objective or remove one.

| Clientbound `set_objective`, Play ID: 108 (0x6C) |
| --- |
| Field Name | Field Type | Notes |
| Objective Name | [String](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:String) (32767) | A unique name for the objective. |
| Mode | [Byte](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Byte) | 0 to create the scoreboard. 1 to remove the scoreboard. 2 to update the display text. |
| Objective Value | [Optional](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Optional) [Text Component](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Text_Component) | Only if mode is 0 or 2.The text to be displayed for the score. |
| Type | [Optional](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Optional) [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) [Enum](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Enum) | Only if mode is 0 or 2. 0 = "integer", 1 = "hearts". |
| Has Number Format | [Optional](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Optional) [Boolean](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Boolean) | Only if mode is 0 or 2. Whether this objective has a set number format for the scores. |
| Number Format | [Optional](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Optional) [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) [Enum](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Enum) | Only if mode is 0 or 2 and the previous boolean is true. Determines how the score number should be formatted. |
| Number Format | Field Name |  |  |
| 0: blank | _no fields_ | Show nothing. |
| 1: styled | Styling | [Compound Tag](https://minecraft.wiki/w/Minecraft_Wiki:Projects/wiki.vg_merge/NBT#Specification:compound_tag "Minecraft Wiki:Projects/wiki.vg merge/NBT") | The styling to be used when formatting the score number. Contains the [text component](https://minecraft.wiki/w/Text_component_format#Java_Edition "Text component format") formatting fields ("color", "bold", etc., but not "text", "extra", etc.). |
| 2: fixed | Content | [Text Component](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Text_Component) | The text to be used as placeholder. |

#### Set Passengers

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=179&veaction=edit "Edit section: Set Passengers") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=179 "Edit section's source code: Set Passengers")\]

| Clientbound `set_passengers`, Play ID: 109 (0x6D) |
| --- |
| Field Name | Field Type | Notes |
| Entity ID | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) | Vehicle's EID. |
| Passengers | [Prefixed Array](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Prefixed_Array) of [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) | EIDs of entity's passengers. |

#### Set Player Inventory Slot

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=180&veaction=edit "Edit section: Set Player Inventory Slot") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=180 "Edit section's source code: Set Player Inventory Slot")\]

Sets the contents of a player inventory slot directly, bypassing the usual container window mechanism. This packet is used by the vanilla server only when placing items in temporary slots back into the inventory upon closing a container window, and likely exists to work around implementation issues specific to vanilla. It is prone to race conditions because it doesn't include a State ID, and there is generally no reason not to use [Set Container Content](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Set_Container_Content) or [Set Container Slot](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Set_Container_Slot) instead.

| Clientbound `set_player_inventory`, Play ID: 110 (0x6E) |
| --- |
| Field Name | Field Type | Notes |
| Slot | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) | Index of the slot to be modified in the player inventory. _Not_ a container window slot index, to the survival inventory or any other window—there is no crafting grid, and the slot order is different. |
| Slot Data | [Slot](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Slot) |  |

#### Update Teams

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=181&veaction=edit "Edit section: Update Teams") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=181 "Edit section's source code: Update Teams")\]

Creates and updates teams.

| Clientbound `set_player_team`, Play ID: 111 (0x6F) |
| --- |
| Field Name | Field Type | Notes |
| Team Name | [String](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:String) (32767) | A unique name for the team. (Shared with scoreboard). |
| Method | [Byte](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Byte) | Determines the layout of the remaining packet. |
| 0: create team | Team Display Name | [Text Component](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Text_Component) |  |
| Team Prefix | [Text Component](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Text_Component) | Displayed before the names of players that are part of this team. |
| Team Suffix | [Text Component](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Text_Component) | Displayed after the names of players that are part of this team. |
| Name Tag Visibility | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) [Enum](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Enum) | 0 = ALWAYS, 1 = NEVER, 2 = HIDE\_FOR\_OTHER\_TEAMS, 3 = HIDE\_FOR\_OWN\_TEAMS |
| Collision Rule | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) [Enum](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Enum) | 0 = ALWAYS, 1 = NEVER, 2 = PUSH\_OTHER\_TEAMS, 3 = PUSH\_OWN\_TEAM |
| Team Color | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) [Enum](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Enum) | Used to color the names of players on the team; see below. |
| Friendly Flags | [Byte](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Byte) | Bit mask. 0x01: Allow friendly fire, 0x02: can see invisible players on the same team. |
| Entities | [Prefixed Array](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Prefixed_Array) of [String](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:String) (32767) | Identifiers for the entities in this team. For players, this is their username; for other entities, it is their UUID. |
| 1: remove team | _no fields_ | _no fields_ |  |
| 2: update team info | Team Display Name | [Text Component](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Text_Component) |  |
| Team Prefix | [Text Component](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Text_Component) | Displayed before the names of players that are part of this team. |
| Team Suffix | [Text Component](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Text_Component) | Displayed after the names of players that are part of this team. |
| Name Tag Visibility | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) [Enum](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Enum) | 0 = ALWAYS, 1 = NEVER, 2 = HIDE\_FOR\_OTHER\_TEAMS, 3 = HIDE\_FOR\_OWN\_TEAMS |
| Collision Rule | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) [Enum](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Enum) | 0 = ALWAYS, 1 = NEVER, 2 = PUSH\_OTHER\_TEAMS, 3 = PUSH\_OWN\_TEAM |
| Team Color | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) [Enum](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Enum) | Used to color the names of players on the team; see below. |
| Friendly Flags | [Byte](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Byte) | Bit mask. 0x01: Allow friendly fire, 0x02: can see invisible players on the same team. |
| 3: add entities to team | Entities | [Prefixed Array](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Prefixed_Array) of [String](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:String) (32767) | Identifiers for the added entities. For players, this is their username; for other entities, it is their UUID. |
| 4: remove entities from team | Entities | [Prefixed Array](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Prefixed_Array) of [String](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:String) (32767) | Identifiers for the removed entities. For players, this is their username; for other entities, it is their UUID. |

Team Color: The color of a team defines how the names of the team members are visualized; any formatting code can be used. The following table lists all the possible values.

| ID | Formatting |
| --- | --- |
| 0-15 | Color formatting, same values as in [Formatting codes#Color codes](https://minecraft.wiki/w/Formatting_codes#Color_codes "Formatting codes"). |
| 16 | Obfuscated |
| 17 | Bold |
| 18 | Strikethrough |
| 19 | Underlined |
| 20 | Italic |
| 21 | Reset |

#### Update Score

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=182&veaction=edit "Edit section: Update Score") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=182 "Edit section's source code: Update Score")\]

This is sent to the client when it should update a scoreboard item.

| Clientbound `set_score`, Play ID: 112 (0x70) |
| --- |
| Field Name | Field Type | Notes |
| Entity Name | [String](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:String) (32767) | The entity whose score this is. For players, this is their username; for other entities, it is their UUID. |
| Objective Name | [String](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:String) (32767) | The name of the objective the score belongs to. |
| Value | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) | The score to be displayed next to the entry. |
| Display Name | [Prefixed Optional](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Prefixed_Optional) [Text Component](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Text_Component) | The custom display name. |
| Number Format | [Prefixed Optional](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Prefixed_Optional) [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) [Enum](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Enum) | Determines how the score number should be formatted. |
| Number Format | Field Name |  |  |
| 0: blank | _no fields_ | Show nothing. |
| 1: styled | Styling | [Compound Tag](https://minecraft.wiki/w/Minecraft_Wiki:Projects/wiki.vg_merge/NBT#Specification:compound_tag "Minecraft Wiki:Projects/wiki.vg merge/NBT") | The styling to be used when formatting the score number. Contains the [text component](https://minecraft.wiki/w/Text_component_format#Java_Edition "Text component format") formatting fields ("color", "bold", etc., but not "text", "extra", etc.). |
| 2: fixed | Content | [Text Component](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Text_Component) | The text to be used as placeholder. |

#### Set Simulation Distance

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=183&veaction=edit "Edit section: Set Simulation Distance") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=183 "Edit section's source code: Set Simulation Distance")\]

| Clientbound `set_simulation_distance`, Play ID: 113 (0x71) |
| --- |
| Field Name | Field Type | Notes |
| Simulation Distance | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) | Server simulation distance. |

The server simulation distance is used by the vanilla client only to determine whether the death animation of an entity should progress. If the integer [chessboard distance](https://en.wikipedia.org/wiki/chessboard_distance "w:chessboard distance") between the chunk the local player is in (not the chunk cache center) and the chunk the entity is in is greater than the simulation distance, the animation will be paused.

#### Set Subtitle Text

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=184&veaction=edit "Edit section: Set Subtitle Text") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=184 "Edit section's source code: Set Subtitle Text")\]

| Clientbound `set_subtitle_text`, Play ID: 114 (0x72) |
| --- |
| Field Name | Field Type | Notes |
| Subtitle Text | [Text Component](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Text_Component) |  |

#### Update Time

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=185&veaction=edit "Edit section: Update Time") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=185 "Edit section's source code: Update Time")\]

Time is based on ticks, where 20 ticks happen every second. There are 24000 ticks in a day, making Minecraft days exactly 20 minutes long.

The time of day is based on the timestamp modulo 24000. 0 is sunrise, 6000 is noon, 12000 is sunset, and 18000 is midnight.

The default SMP server increments the time by `20` every second.

| Clientbound `set_time`, Play ID: 115 (0x73) |
| --- |
| Field Name | Field Type | Notes |
| World Age | [Long](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Long) | In ticks; not changed by server commands. |
| Clocks | Clock ID | [Prefixed Array](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Prefixed_Array) | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) | ID in the `minecraft:world_clock` registry. |
| Time | [VarLong](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarLong) | Current time of the clock, in ticks. |
| Fractional time | [Float](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Float) | Fractional part of the time in ticks, normally a nonnegative number less than 1. |
| Rate | [Float](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Float) | Rate at which the client should automatically advance the time of the clock, in clock ticks per client tick. |

#### Set Title Text

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=186&veaction=edit "Edit section: Set Title Text") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=186 "Edit section's source code: Set Title Text")\]

| Clientbound `set_title_text`, Play ID: 116 (0x74) |
| --- |
| Field Name | Field Type | Notes |
| Title Text | [Text Component](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Text_Component) |  |

#### Set Title Animation Times

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=187&veaction=edit "Edit section: Set Title Animation Times") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=187 "Edit section's source code: Set Title Animation Times")\]

| Clientbound `set_titles_animation`, Play ID: 117 (0x75) |
| --- |
| Field Name | Field Type | Notes |
| Fade In | [Int](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Int) | Ticks to spend fading in. |
| Stay | [Int](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Int) | Ticks to keep the title displayed. |
| Fade Out | [Int](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Int) | Ticks to spend fading out, not when to start fading out. |

#### Entity Sound Effect

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=188&veaction=edit "Edit section: Entity Sound Effect") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=188 "Edit section's source code: Entity Sound Effect")\]

Plays a sound effect from an entity, either by hardcoded ID or Identifier. Sound IDs and names can be found [here](https://pokechu22.github.io/Burger/1.21.html#sounds).

| Clientbound `sound_entity`, Play ID: 118 (0x76) |
| --- |
| Field Name | Field Type | Notes |
| Sound Event | [ID or](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:ID_or) [Sound Event](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Sound_Event) | ID in the `minecraft:sound_event` registry, or an inline definition. |
| Sound Category | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) [Enum](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Enum) | The category that this sound will be played from ( [current categories](https://gist.github.com/konwboj/7c0c380d3923443e9d55)). |
| Entity ID | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) |  |
| Volume | [Float](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Float) | 1.0 is 100%, capped between 0.0 and 1.0 by vanilla clients. |
| Pitch | [Float](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Float) | Float between 0.5 and 2.0 by vanilla clients. |
| Seed | [Long](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Long) | Seed used to pick sound variant. |

#### Sound Effect

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=189&veaction=edit "Edit section: Sound Effect") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=189 "Edit section's source code: Sound Effect")\]

Plays a sound effect at the given location, either by hardcoded ID or Identifier. Sound IDs and names can be found [here](https://pokechu22.github.io/Burger/1.21.html#sounds).

| Clientbound `sound`, Play ID: 119 (0x77) |
| --- |
| Field Name | Field Type | Notes |
| Sound Event | [ID or](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:ID_or) [Sound Event](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Sound_Event) | ID in the `minecraft:sound_event` registry, or an inline definition. |
| Sound Category | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) [Enum](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Enum) | The category that this sound will be played from ( [current categories](https://gist.github.com/konwboj/7c0c380d3923443e9d55)). |
| Effect Position X | [Int](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Int) | Effect X multiplied by 8 ( [fixed-point number](https://minecraft.wiki/w/Java_Edition_protocol/Data_types#Fixed-point_numbers "Java Edition protocol/Data types") with only 3 bits dedicated to the fractional part). |
| Effect Position Y | [Int](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Int) | Effect Y multiplied by 8 ( [fixed-point number](https://minecraft.wiki/w/Java_Edition_protocol/Data_types#Fixed-point_numbers "Java Edition protocol/Data types") with only 3 bits dedicated to the fractional part). |
| Effect Position Z | [Int](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Int) | Effect Z multiplied by 8 ( [fixed-point number](https://minecraft.wiki/w/Java_Edition_protocol/Data_types#Fixed-point_numbers "Java Edition protocol/Data types") with only 3 bits dedicated to the fractional part). |
| Volume | [Float](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Float) | 1.0 is 100%, capped between 0.0 and 1.0 by vanilla clients. |
| Pitch | [Float](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Float) | Float between 0.5 and 2.0 by vanilla clients. |
| Seed | [Long](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Long) | Seed used to pick sound variant. |

#### Start Configuration

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=190&veaction=edit "Edit section: Start Configuration") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=190 "Edit section's source code: Start Configuration")\]

Sent during gameplay in order to redo the configuration process. The client must respond with [Acknowledge Configuration](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Acknowledge_Configuration) for the process to start.

| Clientbound `start_configuration`, Play ID: 120 (0x78) |
| --- |
| Field Name | Field Type | Notes |
| _no fields_ |

This packet switches the connection state to [configuration](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Configuration).

#### Stop Sound

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=191&veaction=edit "Edit section: Stop Sound") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=191 "Edit section's source code: Stop Sound")\]

| Clientbound `stop_sound`, Play ID: 121 (0x79) |
| --- |
| Field Name | Field Type | Notes |
| Flags | [Byte](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Byte) | Controls which fields are present. |
| Source | [Optional](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Optional) [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) [Enum](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Enum) | Only if flags is 3 or 1 (bit mask 0x1). See below. If not present, then sounds from all sources are cleared. |
| Sound | [Optional](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Optional) [Identifier](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Identifier) | Only if flags is 2 or 3 (bit mask 0x2). A sound effect name, see [Custom Sound Effect](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Custom_Sound_Effect). If not present, then all sounds are cleared. |

Categories:

| Name | Value |
| --- | --- |
| master | 0 |
| music | 1 |
| record | 2 |
| weather | 3 |
| block | 4 |
| hostile | 5 |
| neutral | 6 |
| player | 7 |
| ambient | 8 |
| voice | 9 |

#### Swing Animation

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=192&veaction=edit "Edit section: Swing Animation") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=192 "Edit section's source code: Swing Animation")\]

Sent when an entity swings one of its hands.

| Clientbound `swing_animation`, Play ID: 123 (0x7B) |
| --- |
| Field Name | Field Type | Notes |
| Entity ID | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) | Entity performing the swing. |
| Hand | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) [Enum](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Enum) | Hand used for the swing; see below. |
| Animation Type | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) [Enum](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Enum) | Type of swing animation; see below. |
| Duration | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) | Duration of the swing animation, in ticks. |

Hand can be one of the following values:

| ID | Name |
| --- | --- |
| 0 | Main hand |
| 1 | Off hand |

Animation Type can be one of the following values:

| ID | Name |
| --- | --- |
| 0 | None |
| 1 | Whack |
| 2 | Stab |

#### System Chat Message

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=193&veaction=edit "Edit section: System Chat Message") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=193 "Edit section's source code: System Chat Message")\]

Main article: [Java Edition protocol/Chat](https://minecraft.wiki/w/Java_Edition_protocol/Chat "Java Edition protocol/Chat")

Sends the client a raw system message.

| Clientbound `system_chat`, Play ID: 124 (0x7C) |
| --- |
| Field Name | Field Type | Notes |
| Content | [Text Component](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Text_Component) | Limited to 262144 bytes. |
| Overlay | [Boolean](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Boolean) | Whether the message is an actionbar or chat message. See also [#Set Action Bar Text](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Set_Action_Bar_Text). |

#### Set Tab List Header And Footer

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=194&veaction=edit "Edit section: Set Tab List Header And Footer") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=194 "Edit section's source code: Set Tab List Header And Footer")\]

This packet may be used by custom servers to display additional information above/below the tab list. It is never sent by the vanilla server.

| Clientbound `tab_list`, Play ID: 125 (0x7D) |
| --- |
| Field Name | Field Type | Notes |
| Header | [Text Component](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Text_Component) | To remove the header, send an empty text component: `{"text":""}`. |
| Footer | [Text Component](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Text_Component) | To remove the footer, send an empty text component: `{"text":""}`. |

#### Tag Query Response

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=195&veaction=edit "Edit section: Tag Query Response") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=195 "Edit section's source code: Tag Query Response")\]

Sent in response to [Query Block Entity Tag](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Query_Block_Entity_Tag) or [Query Entity Tag](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Query_Entity_Tag).

| Clientbound `tag_query`, Play ID: 126 (0x7E) |
| --- |
| Field Name | Field Type | Notes |
| Transaction ID | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) | Can be compared to the one sent in the original query packet. |
| NBT | [NBT](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:NBT) | The NBT of the block or entity. May be a TAG\_END (0), in which case no NBT is present. |

#### Pickup Item

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=196&veaction=edit "Edit section: Pickup Item") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=196 "Edit section's source code: Pickup Item")\]

Sent by the server when someone picks up an item lying on the ground — its sole purpose appears to be the animation of the item flying towards you. It doesn't destroy the entity in the client memory, and it doesn't add it to your inventory. The server only checks for items to be picked up after each [Set Player Position](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Set_Player_Position) (and [Set Player Position And Rotation](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Set_Player_Position_And_Rotation)) packet sent by the client. The collector entity can be any entity; it does not have to be a player. The collected entity can also be any entity, but the vanilla server only uses this for items, experience orbs, the different varieties of arrows and tridents.

| Clientbound `take_item_entity`, Play ID: 127 (0x7F) |
| --- |
| Field Name | Field Type | Notes |
| Collected Entity ID | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) |  |
| Collector Entity ID | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) |  |
| Pickup Item Count | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) | Seems to be 1 for XP orbs, otherwise the number of items in the stack. |

#### Synchronize Vehicle Position

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=197&veaction=edit "Edit section: Synchronize Vehicle Position") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=197 "Edit section's source code: Synchronize Vehicle Position")\]

Teleports the entity on the client without changing the reference point of movement deltas in future [Update Entity Position](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Update_Entity_Position) packets. Seems to be used to make relative adjustments to vehicle positions; more information needed.

| Clientbound `teleport_entity`, Play ID: 128 (0x80) |
| --- |
| Field Name | Field Type | Notes |
| Entity ID | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) |  |
| X | [Double](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Double) |  |
| Y | [Double](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Double) |  |
| Z | [Double](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Double) |  |
| Velocity X | [Double](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Double) |  |
| Velocity Y | [Double](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Double) |  |
| Velocity Z | [Double](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Double) |  |
| Yaw | [Float](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Float) | Rotation on the Y axis, in degrees. |
| Pitch | [Float](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Float) | Rotation on the Y axis, in degrees. |
| Flags | [Teleport Flags](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Teleport_Flags) |  |
| On Ground | [Boolean](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Boolean) |  |

#### Test Instance Block Status

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=198&veaction=edit "Edit section: Test Instance Block Status") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=198 "Edit section's source code: Test Instance Block Status")\]

Updates the status of the currently open [Test Instance Block](https://minecraft.wiki/w/Test_Instance_Block "Test Instance Block") screen, if any.

| Clientbound `test_instance_block_status`, Play ID: 129 (0x81) |
| --- |
| Field Name | Field Type | Notes |
| Status | [Text Component](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Text_Component) |  |
| Has Size | [Boolean](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Boolean) |  |
| Size X | [Optional](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Optional) [Double](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Double) | Only present if Has Size is true. |
| Size Y | [Optional](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Optional) [Double](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Double) | Only present if Has Size is true. |
| Size Z | [Optional](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Optional) [Double](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Double) | Only present if Has Size is true. |

#### Set Ticking State

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=199&veaction=edit "Edit section: Set Ticking State") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=199 "Edit section's source code: Set Ticking State")\]

Used to adjust the ticking rate of the client, and whether it's frozen.

| Clientbound `ticking_state`, Play ID: 130 (0x82) |
| --- |
| Field Name | Field Type | Notes |
| Tick rate | [Float](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Float) |  |
| Is frozen | [Boolean](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Boolean) |  |

#### Step Tick

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=200&veaction=edit "Edit section: Step Tick") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=200 "Edit section's source code: Step Tick")\]

Advances the client processing by the specified number of ticks. Has no effect unless client ticking is frozen.

| Clientbound `ticking_step`, Play ID: 131 (0x83) |
| --- |
| Field Name | Field Type | Notes |
| Tick steps | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) |  |

#### Update Advancements

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=201&veaction=edit "Edit section: Update Advancements") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=201 "Edit section's source code: Update Advancements")\]

| Clientbound `update_advancements`, Play ID: 133 (0x85) |
| --- |
| Field Name | Field Type | Notes |
| Reset/Clear | [Boolean](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Boolean) | Whether to reset/clear the current advancements. |
| Advancement mapping | Key | [Prefixed Array](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Prefixed_Array) | [Identifier](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Identifier) | The identifier of the advancement. |
| Value | Advancement | See below |
| Identifiers | [Prefixed Array](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Prefixed_Array) of [Identifier](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Identifier) | The identifiers of the advancements that should be removed. |
| Progress mapping | Key | [Prefixed Array](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Prefixed_Array) | [Identifier](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Identifier) | The identifier of the advancement. |
| Value | Advancement progress | See below. |
| Show advancements | [Boolean](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Boolean) |  |

Advancement structure:

| Field Name | Field Type | Notes |
| --- | --- | --- |
| Parent id | [Prefixed Optional](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Prefixed_Optional) [Identifier](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Identifier) | The identifier of the parent advancement. |
| Display data | [Prefixed Optional](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Prefixed_Optional) Advancement display | See below. |
| Nested requirements | [Prefixed Array](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Prefixed_Array) | [Prefixed Array](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Prefixed_Array) of [String](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:String) (32767) | Array with a sub-array of criteria. To check if the requirements are met, each sub-array must be tested and mapped with the OR operator, resulting in a boolean array.<br>These booleans must be mapped with the AND operator to get the result. |
| Sends telemetry data | [Boolean](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Boolean) | Whether the client should include this achievement in the telemetry data when it's completed.<br>The vanilla client only sends data for advancements on the `minecraft` namespace. |

Advancement display:

| Field Name | Field Type | Notes |
| --- | --- | --- |
| Title | [Text Component](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Text_Component) |  |
| Description | [Text Component](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Text_Component) |  |
| Icon | [Slot](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Slot) |  |
| Frame type | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) [Enum](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Enum) | 0 = `task`, 1 = `challenge`, 2 = `goal`. |
| Flags | [Int](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Int) | 0x01: has background texture; 0x02: `show_toast`; 0x04: `hidden`. |
| Background texture | [Optional](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Optional) [Identifier](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Identifier) | Background texture location. Only if flags indicates it. |
| X coord | [Float](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Float) |  |
| Y coord | [Float](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Float) |  |

Advancement progress:

| Field Name | Field Type | Notes |
| --- | --- | --- |
| Criteria | Criterion identifier | [Prefixed Array](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Prefixed_Array) | [Identifier](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Identifier) | The identifier of the criterion. |
| Date of achieving | [Prefixed Optional](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Prefixed_Optional) [Long](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Long) | Present if achieved. As returned by [`Date.getTime`](https://docs.oracle.com/javase/6/docs/api/java/util/Date.html#getTime()). |

#### Update Attributes

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=202&veaction=edit "Edit section: Update Attributes") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=202 "Edit section's source code: Update Attributes")\]

Sets [attributes](https://minecraft.wiki/w/Attribute "Attribute") on the given entity.

| Clientbound `update_attributes`, Play ID: 134 (0x86) |
| --- |
| Field Name | Field Type | Notes |
| Entity ID | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) |  |
| Property | Id | [Prefixed Array](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Prefixed_Array) | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) | ID in the `minecraft:attribute` registry. See also [Attribute#Attributes](https://minecraft.wiki/w/Attribute#Attributes "Attribute"). |
| Value | [Double](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Double) | See below. |
| Modifiers | [Prefixed Array](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Prefixed_Array) of Modifier Data | See [Attribute#Modifiers](https://minecraft.wiki/w/Attribute#Modifiers "Attribute"). Modifier Data defined below. |

_Modifier Data_ structure:

| Field Name | Field Type | Notes |
| --- | --- | --- |
| Id | [Identifier](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Identifier) |  |
| Amount | [Double](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Double) | May be positive or negative. |
| Operation | [Byte](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Byte) | See below. |

The operation controls how the base value of the modifier is changed.

- 0: Add/subtract amount
- 1: Add/subtract amount percent of the current value
- 2: Multiply by amount percent

All of the 0's are applied first, and then the 1's, and then the 2's.

#### Entity Effect

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=203&veaction=edit "Edit section: Entity Effect") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=203 "Edit section's source code: Entity Effect")\]

| Clientbound `update_mob_effect`, Play ID: 135 (0x87) |
| --- |
| Field Name | Field Type | Notes |
| Entity ID | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) |  |
| Effect ID | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) | See [this table](https://minecraft.wiki/w/Status_effect#Effect_list "Status effect"). |
| Amplifier | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) | Vanilla client displays effect level as Amplifier + 1. |
| Duration | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) | Duration in ticks. (-1 for infinite) |
| Flags | [Byte](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Byte) | Bit field, see below. |

[![](https://minecraft.wiki/images/Information_icon.svg?15c1c)](https://minecraft.wiki/w/File:Information_icon.svg "File:Information icon.svg")

This section is missing information about: What exact effect does the blend bit flag have on the client? What happens if it is used on effects besides DARKNESS?

Please expand the section to include this information. Further details may exist on the [talk page](https://minecraft.wiki/w/Talk:Java_Edition_protocol/Packets).

Within flags:

- 0x01: Is ambient - was the effect spawned from a beacon? All beacon-generated effects are ambient. Ambient effects use a different icon in the HUD (blue border rather than gray). If all effects on an entity are ambient, the ["Is potion effect ambient" living metadata field](https://minecraft.wiki/w/Java_Edition_protocol/Entity_metadata#Living_Entity "Java Edition protocol/Entity metadata") should be set to true. Usually should not be enabled.
- 0x02: Show particles - should all particles from this effect be hidden? Effects with particles hidden are not included in the calculation of the effect color, and are not rendered on the HUD (but are still rendered within the inventory). Usually should be enabled.
- 0x04: Show icon - should the icon be displayed on the client? Usually should be enabled.
- 0x08: Blend - should the effect's hard-coded blending be applied? Currently only used in the DARKNESS effect to apply extra void fog and adjust the gamma value for lighting.

#### Update Recipes

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=204&veaction=edit "Edit section: Update Recipes") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=204 "Edit section's source code: Update Recipes")\]

| Clientbound `update_recipes`, Play ID: 136 (0x88) |
| --- |
| Field Name | Field Type | Notes |
| Property Sets | Property Set ID | [Prefixed Array](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Prefixed_Array) | [Identifier](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Identifier) |  |
| Items | [Prefixed Array](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Prefixed_Array) of [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) | IDs in the `minecraft:item` registry. |
| Stonecutter Recipes | Ingredients | [Prefixed Array](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Prefixed_Array) | [ID Set](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:ID_Set) |  |
| Slot Display | [Slot Display](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Slot_Display) |  |

#### Projectile Power

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=205&veaction=edit "Edit section: Projectile Power") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=205 "Edit section's source code: Projectile Power")\]

| Clientbound `projectile_power`, Play ID: 138 (0x8A) |
| --- |
| Field Name | Field Type | Notes |
| Entity ID | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) |  |
| Power | [Double](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Double) |  |

#### Waypoint

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=206&veaction=edit "Edit section: Waypoint") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=206 "Edit section's source code: Waypoint")\]

Adds, removes, or updates an entry that will be tracked on the player locator bar.

| Clientbound `waypoint`, Play ID: 141 (0x8D) |
| --- |
| Field Name | Field Type | Notes |
| Operation | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) [Enum](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Enum) | 0: track, 1: untrack, 2: update. |
| Identifier | [Either](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Either) [Uuid](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Uuid) or [String](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:String) | Something that uniquely identifies this specific waypoint. |
| Icon style | [Identifier](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Identifier) | Path to the waypoint style JSON: `assets/<namespace>/waypoint_style/<value>.json.` |
| Color |
| Red | [Prefixed Optional](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Prefixed_Optional) | [Unsigned Byte](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Unsigned_Byte) | The color of the waypoint icon. |
| Green | [Unsigned Byte](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Unsigned_Byte) |
| Blue | [Unsigned Byte](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Unsigned_Byte) |
| Waypoint type | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) [Enum](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Enum) | Defines how the following field is read. |
| Waypoint data | Varies | | Type | Field Name | Field Data | Notes |
| --- | --- | --- | --- |
| 0: Empty | _no fields_ |
| 1: Vec3i | X | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) | The position that the waypoint will point to. |
| Y | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) |
| Z | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) |
| 2: Chunk | X | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) | The chunk coordinates that the waypoint will point to. |
| Z | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) |
| 3: Azimuth | Angle | [Float](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Float) | The angle that will be pointed to, in radians. | |

#### Show Dialog (play)

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=207&veaction=edit "Edit section: Show Dialog (play)") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=207 "Edit section's source code: Show Dialog (play)")\]

Show a custom dialog screen to the client.

| Clientbound `show_dialog`, Play ID: 143 (0x8F) |
| --- |
| Field Name | Field Type | Notes |
| Dialog | [ID or](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:ID_or) [NBT](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:NBT) | Inline definition as described at [Dialog#Dialog format](https://minecraft.wiki/w/Dialog#Dialog_format "Dialog"). |

### Serverbound

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=208&veaction=edit "Edit section: Serverbound") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=208 "Edit section's source code: Serverbound")\]

#### Confirm Teleportation

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=209&veaction=edit "Edit section: Confirm Teleportation") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=209 "Edit section's source code: Confirm Teleportation")\]

Sent by the client as confirmation of [Synchronize Player Position](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Synchronize_Player_Position). In 26.3 it also reports the position and rotation resulting from the teleport.

| Serverbound `accept_teleportation`, Play ID: 0 (0x0) |
| --- |
| Field Name | Field Type | Notes |
| Teleport ID | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) | The ID given by the [Synchronize Player Position](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Synchronize_Player_Position) packet. |
| X | [Double](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Double) | Resulting X position. |
| Y | [Double](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Double) | Resulting Y position. |
| Z | [Double](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Double) | Resulting Z position. |
| Yaw | [Float](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Float) | Resulting yaw. |
| Pitch | [Float](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Float) | Resulting pitch. |

#### Attack

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=210&veaction=edit "Edit section: Attack") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=210 "Edit section's source code: Attack")\]

This packet is sent from the client to the server when the client attacks another entity (a player, minecart, etc).

A vanilla server only accepts this packet if the entity being attacked is visible without obstruction and within a 4-unit radius of the player's position.

| Serverbound `attack`, Play ID: 1 (0x1) |
| --- |
| Field Name | Field Type | Notes |
| Entity ID | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) | The ID of the attacked entity. Note the special case of the ender dragon described on the [Interact](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Interact) packet. |

#### Query Block Entity Tag

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=211&veaction=edit "Edit section: Query Block Entity Tag") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=211 "Edit section's source code: Query Block Entity Tag")\]

Used when `F3` + `I` is pressed while looking at a block.

| Serverbound `block_entity_tag_query`, Play ID: 2 (0x2) |
| --- |
| Field Name | Field Type | Notes |
| Transaction ID | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) | An incremental ID so that the client can verify that the response matches. |
| Location | [Position](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Position) | The location of the block to check. |

#### Bundle Item Selected

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=212&veaction=edit "Edit section: Bundle Item Selected") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=212 "Edit section's source code: Bundle Item Selected")\]

| Serverbound `bundle_item_selected`, Play ID: 3 (0x3) |
| --- |
| Field Name | Field Type | Notes |
| Slot of Bundle | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) |  |
| Slot in Bundle | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) |  |

#### Change Difficulty

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=213&veaction=edit "Edit section: Change Difficulty") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=213 "Edit section's source code: Change Difficulty")\]

Must have at least op level 2 to use. Appears to only be used on singleplayer; the difficulty buttons are still disabled in multiplayer.

| Serverbound `change_difficulty`, Play ID: 4 (0x4) |
| --- |
| Field Name | Field Type | Notes |
| New difficulty | [Unsigned Byte](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Unsigned_Byte) [Enum](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Enum) | 0: peaceful, 1: easy, 2: normal, 3: hard. |

#### Change Game Mode

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=214&veaction=edit "Edit section: Change Game Mode") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=214 "Edit section's source code: Change Game Mode")\]

Requests for the server to update our game mode. Has no effect on vanilla servers if the client doesn't have the required permissions.

| Serverbound `change_game_mode`, Play ID: 5 (0x5) |
| --- |
| Field Name | Field Type | Notes |
| Game mode | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) [Enum](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Enum) | 0: survival, 1: creative, 2: adventure, 3: spectator. |

#### Acknowledge Message

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=215&veaction=edit "Edit section: Acknowledge Message") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=215 "Edit section's source code: Acknowledge Message")\]

| Serverbound `chat_ack`, Play ID: 6 (0x6) |
| --- |
| Field Name | Field Type | Notes |
| Message Count | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) |  |

#### Chat Command

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=216&veaction=edit "Edit section: Chat Command") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=216 "Edit section's source code: Chat Command")\]

Main article: [Java Edition protocol/Chat](https://minecraft.wiki/w/Java_Edition_protocol/Chat "Java Edition protocol/Chat")

| Serverbound `chat_command`, Play ID: 7 (0x7) |
| --- |
| Field Name | Field Type | Notes |
| Command | [String](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:String) (32767) | The command typed by the client excluding the `/`. |

#### Signed Chat Command

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=217&veaction=edit "Edit section: Signed Chat Command") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=217 "Edit section's source code: Signed Chat Command")\]

Main article: [Java Edition protocol/Chat](https://minecraft.wiki/w/Java_Edition_protocol/Chat "Java Edition protocol/Chat")

| Serverbound `chat_command_signed`, Play ID: 8 (0x8) |
| --- |
| Field Name | Field Type | Notes |
| Command | [String](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:String) (32767) | The command typed by the client excluding the `/`. |
| Timestamp | [Long](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Long) | The timestamp that the command was executed. |
| Salt | [Long](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Long) | The salt for the following argument signatures. |
| Array of argument signatures | Argument name | [Prefixed Array](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Prefixed_Array) (8) | [String](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:String) (16) | The name of the argument that is signed by the following signature. |
| Signature | [Byte Array](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Byte_Array) (256) | The signature that verifies the argument. Always 256 bytes and is not length-prefixed. |
| Message Count | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) |  |
| Acknowledged | [Fixed BitSet](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Fixed_BitSet) (20) |  |
| Checksum | [Byte](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Byte) |  |

#### Chat Message

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=218&veaction=edit "Edit section: Chat Message") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=218 "Edit section's source code: Chat Message")\]

Main article: [Java Edition protocol/Chat](https://minecraft.wiki/w/Java_Edition_protocol/Chat "Java Edition protocol/Chat")

Used to send a chat message to the server. The message may not be longer than 256 characters or else the server will kick the client.

The server will broadcast a [Player Chat Message](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Player_Chat_Message) packet with Chat Type `minecraft:chat` to all players that haven't disabled chat (including the player that sent the message). See [Java Edition protocol/Chat#Processing chat](https://minecraft.wiki/w/Java_Edition_protocol/Chat#Processing_chat "Java Edition protocol/Chat") for more information.

| Serverbound `chat`, Play ID: 9 (0x9) |
| --- |
| Field Name | Field Type | Notes |
| Message | [String](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:String) (256) | Content of the message |
| Timestamp | [Long](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Long) | Number of milliseconds since the epoch (1 Jan 1970, midnight, UTC) |
| Salt | [Long](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Long) | The salt used to verify the signature hash. Randomly generated by the client |
| Signature | [Prefixed Optional](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Prefixed_Optional) [Byte Array](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Byte_Array) (256) | The signature used to verify the chat message's authentication. When present, always 256 bytes and not length-prefixed.<br>This is a SHA256 with RSA digital signature computed over the following:<br>- The number 1 as a 4-byte int. Always 00 00 00 01.<br>- The player's 16-byte UUID.<br>- The chat session (a 16-byte UUID randomly generated by the client).<br>- The index of the message within this chat session as a 4-byte int. First message is 0, next message is 1, etc. Incremented each time the client sends a chat message.<br>- The salt (from above) as an 8-byte long.<br>- The timestamp (from above) converted from milliseconds to seconds, so divide by 1000, as an 8-byte long.<br>- The length of the message in bytes (from above) as a 4-byte int.<br>- The message bytes.<br>- The number of messages in the last seen set, as a 4-byte int. Always in the range \[0,20\].<br>- For each message in the last seen set, from oldest to newest, the 256-byte signature of that message.<br>The client's chat private key is used for the message signature. |
| Message Count | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) | Number of signed clientbound chat messages the client has seen from the server since the last serverbound chat message from this client. The server will use this to update its last seen list for the client. |
| Acknowledged | [Fixed BitSet](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Fixed_BitSet) (20) | Bitmask of which message signatures from the last seen set were used to sign this message. The most recent is the highest bit. If there are fewer than 20 messages in the last seen set, the lower bits will be zeros. |
| Checksum | [Byte](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Byte) | Checksum is computed over all the message signature checksums in the last seen set, from oldest to newest. Both the packet checksum and signature checksums use the same logic as Java's Arrays.hashCode(byte\[\]) implementation. The packet checksum additionally casts the resulting int to a byte, and if that byte is 0 returns 1, otherwise returns said byte |

#### Player Session

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=219&veaction=edit "Edit section: Player Session") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=219 "Edit section's source code: Player Session")\]

| Serverbound `chat_session_update`, Play ID: 10 (0xA) |
| --- |
| Field Name | Field Type | Notes |
| Session Id | [UUID](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:UUID) |  |
| Public Key | Expires At | [Long](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Long) | The time the play session key expires in [epoch](https://en.wikipedia.org/wiki/Unix_time "wikipedia:Unix time") milliseconds. |
| Public Key | [Prefixed Array](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Prefixed_Array) (512) of [Byte](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Byte) | A byte array of an X.509-encoded public key. Get this from [Mojang API#Get keypair for signature](https://minecraft.wiki/w/Mojang_API#Get_keypair_for_signature "Mojang API") |
| Key Signature | [Prefixed Array](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Prefixed_Array) (4096) of [Byte](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Byte) | The signature consists of the player UUID, the key expiration timestamp, and the public key data. These values are hashed using [SHA-1](https://en.wikipedia.org/wiki/SHA-1 "wikipedia:SHA-1") and signed using Mojang's private [RSA](https://en.wikipedia.org/wiki/RSA_(cryptosystem) "wikipedia:RSA (cryptosystem)") key. |

#### Chunk Batch Received

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=220&veaction=edit "Edit section: Chunk Batch Received") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=220 "Edit section's source code: Chunk Batch Received")\]

Notifies the server that the chunk batch has been received by the client. The server uses the value sent in this packet to adjust the number of chunks to be sent in a batch.

The vanilla server will stop sending further chunk data until the client acknowledges the sent chunk batch. After the first acknowledgement, the server adjusts this number to allow up to 10 unacknowledged batches.

| Serverbound `chunk_batch_received`, Play ID: 11 (0xB) |
| --- |
| Field Name | Field Type | Notes |
| Chunks per tick | [Float](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Float) | Desired chunks per tick. |

#### Client Status

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=221&veaction=edit "Edit section: Client Status") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=221 "Edit section's source code: Client Status")\]

| Serverbound `client_command`, Play ID: 12 (0xC) |
| --- |
| Field Name | Field Type | Notes |
| Action ID | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) [Enum](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Enum) | See below |

_Action ID_ values:

| Action ID | Action | Notes |
| --- | --- | --- |
| 0 | Perform respawn | Sent when the client is ready to respawn after death. |
| 1 | Request stats | Sent when the client opens the Statistics menu. |
| 2 | Request game rule values | Sent when the client opens the Edit Game Rules menu. |

#### Client Tick End

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=222&veaction=edit "Edit section: Client Tick End") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=222 "Edit section's source code: Client Tick End")\]

| Serverbound `client_tick_end`, Play ID: 13 (0xD) |
| --- |
| Field Name | Field Type | Notes |
| _no fields_ |

#### Command Suggestions Request

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=223&veaction=edit "Edit section: Command Suggestions Request") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=223 "Edit section's source code: Command Suggestions Request")\]

Sent when the client needs to tab-complete a `minecraft:ask_server` suggestion type.

| Serverbound `command_suggestion`, Play ID: 15 (0xF) |
| --- |
| Field Name | Field Type | Notes |
| Transaction Id | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) | The ID of the transaction that the server will send back to the client in the response of this packet. Client generates this and increments it each time it sends another tab completion that doesn't get a response. |
| Text | [String](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:String) (32500) | All the text behind the cursor including the `/` (e.g. to the left of the cursor in left-to-right languages like English). |

#### Acknowledge Configuration

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=224&veaction=edit "Edit section: Acknowledge Configuration") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=224 "Edit section's source code: Acknowledge Configuration")\]

Sent by the client upon receiving a [Start Configuration](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Start_Configuration) packet from the server.

| Serverbound `configuration_acknowledged`, Play ID: 16 (0x10) |
| --- |
| Field Name | Field Type | Notes |
| _no fields_ |

This packet switches the connection state to [configuration](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Configuration).

#### Click Container Button

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=225&veaction=edit "Edit section: Click Container Button") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=225 "Edit section's source code: Click Container Button")\]

Used when clicking on window buttons. Until 1.14, this was only used by enchantment tables.

| Serverbound `container_button_click`, Play ID: 17 (0x11) |
| --- |
| Field Name | Field Type | Notes |
| Window ID | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) | The ID of the window sent by [Open Screen](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Open_Screen). |
| Button ID | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) | Meaning depends on window type; see below. |

| Window type | ID | Meaning |
| --- | --- | --- |
| Enchantment Table | 0 | Topmost enchantment. |
| 1 | Middle enchantment. |
| 2 | Bottom enchantment. |
| Lectern | 1 | Previous page (which does give a redstone output). |
| 2 | Next page. |
| 3 | Take Book. |
| 100+page | Opened page number - 100 + number. |
| Stonecutter | Recipe button number - 4\*row + col. Depends on the item. |
| Loom | Recipe button number - 4\*row + col. Depends on the item. |

#### Click Container

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=226&veaction=edit "Edit section: Click Container") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=226 "Edit section's source code: Click Container")\]

This packet is sent by the client when the player clicks on a slot in a window.

| Serverbound `container_click`, Play ID: 18 (0x12) |
| --- |
| Field Name | Field Type | Notes |
| Window ID | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) | The ID of the window that was clicked. 0 for player inventory. The server ignores any packets targeting a Window ID other than the current one, including ignoring 0 when any other window is open. |
| State ID | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) | The last received State ID from either a [Set Container Slot](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Set_Container_Slot) or a [Set Container Content](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Set_Container_Content) packet. |
| Slot | [Short](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Short) | The clicked slot number, see below. |
| Button | [Byte](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Byte) | The button used in the click, see below. |
| Mode | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) [Enum](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Enum) | Inventory operation mode, see below. |
| Array of changed slots | Slot number | [Prefixed Array](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Prefixed_Array) (128) | [Short](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Short) |  |
| Slot data | [Hashed Slot](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Hashed_Slot) | New data for this slot, in the client's opinion; see below. |
| Carried item | [Hashed Slot](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Hashed_Slot) | Item carried by the cursor. |

See [Java Edition protocol/Inventory](https://minecraft.wiki/w/Java_Edition_protocol/Inventory "Java Edition protocol/Inventory") for further information about how slots are indexed.

After performing the action, the server compares the results to the slot change information included in the packet, as applied on top of the server's view of the container's state prior to the action. For any slots that do not match, it sends [Set Container Slot](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Set_Container_Slot) packets containing the correct results. If State ID does not match the last ID sent by the server, it will instead send a full [Set Container Content](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Set_Container_Content) to resynchronize the client.

When right-clicking on a stack of items, half the stack will be picked up and half left in the slot. If the stack is an odd number, the half left in the slot will be the smaller of the amounts.

The distinct type of click performed by the client is determined by the combination of the Mode and Button fields.

| Mode | Button | Slot | Trigger |
| --- | --- | --- | --- |
| 0 | 0 | Normal | Left mouse click |
| 1 | Normal | Right mouse click |
| 0 | -999 | Left click outside inventory (drop cursor stack) |
| 1 | -999 | Right click outside inventory (drop cursor single item) |
| 1 | 0 | Normal | Shift + left mouse click |
| 1 | Normal | Shift + right mouse click _(identical behavior)_ |
| 2 | 0 | Normal | Number key 1 |
| 1 | Normal | Number key 2 |
| 2 | Normal | Number key 3 |
| ⋮ | ⋮ | ⋮ |
| 8 | Normal | Number key 9 |
| ⋮ | ⋮ | Used to allow swapping with arbitrary inventory slots. Ignored since 1.20.3. |
| 40 | Normal | Offhand swap key F |
| 3 | 2 | Normal | Middle click, only defined for creative players in non-player inventories. |
| 4 | 0 | Normal | Drop key (Q) |
| 1 | Normal | Control + Drop key (Q) |
| 5 | 0 | -999 | Starting left mouse drag |
| 4 | -999 | Starting right mouse drag |
| 8 | -999 | Starting middle mouse drag, only defined for creative players in non-player inventories. |
| 1 | Normal | Add slot for left-mouse drag |
| 5 | Normal | Add slot for right-mouse drag |
| 9 | Normal | Add slot for middle-mouse drag, only defined for creative players in non-player inventories. |
| 2 | -999 | Ending left mouse drag |
| 6 | -999 | Ending right mouse drag |
| 10 | -999 | Ending middle mouse drag, only defined for creative players in non-player inventories. |
| 6 | 0 | Normal | Double click |
| 1 | Normal | Pickup all but check items in reverse order (impossible in vanilla clients) |

Starting from version 1.5, “painting mode” is available for use in inventory windows. It is done by picking up a stack of something (more than 1 item), then holding [![](https://minecraft.wiki/images/Left_mouse_button.png?485a7)](https://minecraft.wiki/w/File:Left_mouse_button.png) Left Mouse Button, [![](https://minecraft.wiki/images/Right_mouse_button.png?cd132)](https://minecraft.wiki/w/File:Right_mouse_button.png) Right Mouse Button or [![](https://minecraft.wiki/images/Middle_mouse_button.png?de253)](https://minecraft.wiki/w/File:Middle_mouse_button.png) Middle Mouse Button and dragging the held stack over empty (or same type in case of right button) slots. In that case client sends the following to the server after the mouse button release (omitting the first pickup packet, which is sent as usual):

1. packet with mode 5, slot -999, button (0 for left \| 4 for right);
2. packet for every slot painted on, mode is still 5, button (1 \| 5);
3. packet with mode 5, slot -999, button (2 \| 6);

If any of the painting packets other than the “progress” ones are sent out of order (for example, a start, some slots, then another start; or a left-click in the middle) the painting status will be reset.

#### Close Container

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=227&veaction=edit "Edit section: Close Container") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=227 "Edit section's source code: Close Container")\]

This packet is sent by the client when closing a window.

vanilla clients send a Close Window packet with Window ID 0 to close their inventory, even though there is never an [Open Screen](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Open_Screen) packet for the inventory.

| Serverbound `container_close`, Play ID: 19 (0x13) |
| --- |
| Field Name | Field Type | Notes |
| Window ID | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) | This is the ID of the window that was closed. 0 for player inventory. |

#### Change Container Slot State

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=228&veaction=edit "Edit section: Change Container Slot State") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=228 "Edit section's source code: Change Container Slot State")\]

This packet is sent by the client when toggling the state of a Crafter.

| Serverbound `container_slot_state_changed`, Play ID: 20 (0x14) |
| --- |
| Field Name | Field Type | Notes |
| Slot ID | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) | This is the ID of the slot that was changed. |
| Window ID | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) | This is the ID of the window that was changed. |
| State | [Boolean](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Boolean) | The new state of the slot. True for enabled, false for disabled. |

#### Debug Subscription Request

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=229&veaction=edit "Edit section: Debug Subscription Request") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=229 "Edit section's source code: Debug Subscription Request")\]

Sent by the client whenever debug subscriptions, used by [debug graphs](https://minecraft.wiki/w/Debug_graphs "Debug graphs") and [renderers](https://minecraft.wiki/w/Debug_renderer "Debug renderer"), are activated or deactivated. The list in the packet replaces the previous set of active subscriptions. Subscriptions not in the list are deactivated.

If the client does not have permission to receive the requested debug information, the subscriptions are nonetheless retained by the server, and it is not necessary to send this packet again if the permissions change.

| Serverbound `debug_subscription_request`, Play ID: 23 (0x17) |
| --- |
| Field Name | Field Type | Notes |
| Subscriptions | [Prefixed Array](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Prefixed_Array) of [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) | List of active debug subscriptions. IDs in the `minecraft:debug_subscription` registry. |

#### Edit Book

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=230&veaction=edit "Edit section: Edit Book") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=230 "Edit section's source code: Edit Book")\]

| Serverbound `edit_book`, Play ID: 24 (0x18) |
| --- |
| Field Name | Field Type | Notes |
| Slot | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) | The hotbar slot where the written book is located |
| Entries | [Prefixed Array](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Prefixed_Array) (100) of [String](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:String) (1024) | Text from each page. Maximum string length is 1024 chars. |
| Title | [Prefixed Optional](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Prefixed_Optional) [String](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:String) (32) | Title of book. Present if book is being signed, not present if book is being edited. |

#### Query Entity Tag

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=231&veaction=edit "Edit section: Query Entity Tag") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=231 "Edit section's source code: Query Entity Tag")\]

Used when `F3` + `I` is pressed while looking at an entity.

| Serverbound `entity_tag_query`, Play ID: 25 (0x19) |
| --- |
| Field Name | Field Type | Notes |
| Transaction ID | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) | An incremental ID so that the client can verify that the response matches. |
| Entity ID | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) | The ID of the entity to query. |

#### Interact

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=232&veaction=edit "Edit section: Interact") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=232 "Edit section's source code: Interact")\]

This packet is sent from the client to the server when the client right-clicks another entity (a player, minecart, etc).

A vanilla server only accepts this packet if the entity being clicked is visible without obstruction and within a 4-unit radius of the player's position.

The target offset field represents the difference between the vector location of the cursor at the time of the packet and the entity's position.

Note that middle-click in creative mode is interpreted by the client and sent as a [Set Creative Mode Slot](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Set_Creative_Mode_Slot) packet instead.

| Serverbound `interact`, Play ID: 26 (0x1A) |
| --- |
| Field Name | Field Type | Notes |
| Entity ID | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) | The ID of the entity to interact. Note the special case described below. |
| Hand | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) [Enum](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Enum) | Only if Type is interact or interact at; 0: main hand, 1: off hand. |
| Target offset | [LpVec3](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:LpVec3) |  |
| Sneak Key Pressed | [Boolean](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Boolean) | If the client is pressing the sneak key. Has the same effect as a Player Command Press/Release sneak key preceding the interaction, and the state is permanently changed. |

Interaction with the ender dragon is an odd special case characteristic of release deadline–driven design. 8 consecutive entity IDs following the dragon's ID (id \+ 1, id \+ 2, ..., id \+ 8) are reserved for the 8 hitboxes that make up the dragon:

| ID offset | Description |
| --- | --- |
| 0 | The dragon itself (never used in this packet) |
| 1 | Head |
| 2 | Neck |
| 3 | Body |
| 4 | Tail 1 |
| 5 | Tail 2 |
| 6 | Tail 3 |
| 7 | Wing 1 |
| 8 | Wing 2 |

#### Jigsaw Generate

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=233&veaction=edit "Edit section: Jigsaw Generate") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=233 "Edit section's source code: Jigsaw Generate")\]

Sent when Generate is pressed on the [Jigsaw Block](https://minecraft.wiki/w/Jigsaw_Block "Jigsaw Block") interface.

| Serverbound `jigsaw_generate`, Play ID: 27 (0x1B) |
| --- |
| Field Name | Field Type | Notes |
| Location | [Position](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Position) | Block entity location. |
| Levels | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) | Value of the levels slider/max depth to generate. |
| Keep Jigsaws | [Boolean](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Boolean) |  |

#### Lock Difficulty

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=234&veaction=edit "Edit section: Lock Difficulty") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=234 "Edit section's source code: Lock Difficulty")\]

Must have at least op level 2 to use. Appears to only be used on singleplayer; the difficulty buttons are still disabled in multiplayer.

| Serverbound `lock_difficulty`, Play ID: 29 (0x1D) |
| --- |
| Field Name | Field Type | Notes |
| Locked | [Boolean](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Boolean) |  |

#### Set Player Position

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=235&veaction=edit "Edit section: Set Player Position") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=235 "Edit section's source code: Set Player Position")\]

Updates the player's XYZ position on the server.

If the player is in a vehicle, the position is ignored (but in case of [Set Player Position and Rotation](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Set_Player_Position_and_Rotation), the rotation is still used as normal). No validation steps other than value range clamping are performed in this case.

If the player is sleeping, the position (or rotation) is not changed, and a [Synchronize Player Position](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Synchronize_Player_Position) is sent if the received position deviated from the server's view by more than a meter.

The vanilla server silently clamps the x and z coordinates between -30,000,000 and 30,000,000, and the y coordinate between -20,000,000 and 20,000,000. A similar condition has historically caused a kick for "Illegal position"; this is no longer the case. However, infinite or NaN coordinates (or angles) still result in a kick for `multiplayer.disconnect.invalid_player_movement`.

As of 1.20.6, checking for moving too fast is achieved like this (sic):

- Each server tick, the player's current position is stored.
- When the player moves, the offset from the stored position to the requested position is computed (Δx, Δy, Δz).
- The requested movement distance squared is computed as Δx² + Δy² + Δz².
- The baseline expected movement distance squared is computed based on the player's server-side velocity as Vx² + Vy² + Vz². The player's server-side velocity is a somewhat ill-defined quantity that includes, among other things, gravity, jump velocity and knockback, but _not_ regular horizontal movement. A proper description would bring much of Minecraft's physics engine with it. It is accessible as the `Motion` NBT tag on the player entity.
- The maximum permitted movement distance squared is computed as 100 (300 if the player is using an elytra), multiplied by the number of movement packets received since the last tick, including this one, unless that value is greater than 5, in which case no multiplier is applied.
- If the requested movement distance squared minus the baseline distance squared is more than the maximum squared, the player is moving too fast.

If the player is moving too fast, it is logged that "<player> moved too quickly! " followed by the change in x, y, and z, and the player is teleported back to their current (before this packet) server-side position.

Checking for block collisions is achieved like this:

- A temporary collision-checked move of the player is attempted from its current position to the requested one.
- The offset from the resulting position to the requested position is computed. If the absolute value of the offset on the y axis is less than 0.5, it (only the y component) is rounded down to 0.
- If the magnitude of the offset is greater than 0.25 and the player isn't in creative or spectator mode, it is logged that "<player> moved wrongly!", and the player is teleported back to their current (before this packet) server-side position.
- In addition, if the player's hitbox, stationary at the requested position, would intersect with a block, and they aren't in spectator mode, they are teleported back without a log message.

Checking for illegal flight is achieved like this:

- When a movement packet is received, a flag indicating whether or not the player is floating mid-air is updated. The flag is set if the move test described above detected no collision below the player _and_ the y component of the offset from the player's current position to the requested one is greater than -0.5, unless any of various conditions permitting flight (creative mode, elytra, levitation effect, etc., but not jumping) are met.
- Each server tick, it is checked if the flag has been set for more than 80 consecutive ticks. If so, and the player isn't currently sleeping, dead or riding a vehicle, they are kicked for `multiplayer.disconnect.flying`.

| Serverbound `move_player_pos`, Play ID: 30 (0x1E) |
| --- |
| Field Name | Field Type | Notes |
| X | [Double](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Double) | Absolute position. |
| Feet Y | [Double](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Double) | Absolute feet position, normally Head Y - 1.62. |
| Z | [Double](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Double) | Absolute position. |
| Flags | [Byte](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Byte) | Bit field: 0x01: on ground, 0x02: pushing against wall. |

#### Set Player Position and Rotation

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=236&veaction=edit "Edit section: Set Player Position and Rotation") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=236 "Edit section's source code: Set Player Position and Rotation")\]

A combination of [Set Player Rotation](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Set_Player_Rotation) and [Set Player Position](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Set_Player_Position).

| Serverbound `move_player_pos_rot`, Play ID: 31 (0x1F) |
| --- |
| Field Name | Field Type | Notes |
| X | [Double](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Double) | Absolute position. |
| Feet Y | [Double](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Double) | Absolute feet position, normally Head Y - 1.62. |
| Z | [Double](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Double) | Absolute position. |
| Yaw | [Float](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Float) | Absolute rotation on the X Axis, in degrees. |
| Pitch | [Float](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Float) | Absolute rotation on the Y Axis, in degrees. |
| Flags | [Byte](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Byte) | Bit field: 0x01: on ground, 0x02: pushing against wall. |

#### Set Player Rotation

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=237&veaction=edit "Edit section: Set Player Rotation") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=237 "Edit section's source code: Set Player Rotation")\]

[![](https://minecraft.wiki/images/thumb/Minecraft-trig-yaw.png/300px-Minecraft-trig-yaw.png?c58d0)](https://minecraft.wiki/w/File:Minecraft-trig-yaw.png) The unit circle for yaw[![](https://minecraft.wiki/images/thumb/Yaw.png/300px-Yaw.png?3475f)](https://minecraft.wiki/w/File:Yaw.png) The unit circle of yaw, redrawn

Updates the direction the player is looking in.

Yaw is measured in degrees and does not follow classical trigonometry rules. The unit circle of yaw on the XZ-plane starts at (0, 1) and turns counterclockwise, with 90 at (-1, 0), 180 at (0,-1) and 270 at (1, 0). Additionally, yaw is not clamped to between 0 and 360 degrees; any number is valid, including negative numbers and numbers greater than 360.

Pitch is measured in degrees, where 0 is looking straight ahead, -90 is looking straight up, and 90 is looking straight down.

The yaw and pitch of the player (in degrees), standing at point (x0, y0, z0) and looking towards point (x, y, z) can be calculated with:

```
dx = x-x0
dy = y-y0
dz = z-z0
r = sqrt( dx*dx + dy*dy + dz*dz )
yaw = -atan2(dx,dz)/PI*180
if yaw < 0 then
    yaw = 360 + yaw
pitch = -arcsin(dy/r)/PI*180
```

You can get a unit vector from a given yaw/pitch via:

```
x = -cos(pitch) * sin(yaw)
y = -sin(pitch)
z =  cos(pitch) * cos(yaw)
```

| Serverbound `move_player_rot`, Play ID: 32 (0x20) |
| --- |
| Field Name | Field Type | Notes |
| Yaw | [Float](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Float) | Absolute rotation on the X Axis, in degrees. |
| Pitch | [Float](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Float) | Absolute rotation on the Y Axis, in degrees. |
| Flags | [Byte](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Byte) | Bit field: 0x01: on ground, 0x02: pushing against wall. |

#### Set Player Movement Flags

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=238&veaction=edit "Edit section: Set Player Movement Flags") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=238 "Edit section's source code: Set Player Movement Flags")\]

This packet, as well as [Set Player Position](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Set_Player_Position), [Set Player Rotation](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Set_Player_Rotation), and [Set Player Position and Rotation](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Set_Player_Position_and_Rotation) are called the “serverbound movement packets”. Vanilla clients will send Move Player Position once every 20 ticks, even for a stationary player.

This packet is used to indicate whether the player is on ground (walking/swimming) or airborne (jumping/falling).

When dropping from a sufficient height, fall damage is applied when this state goes from false to true. The amount of damage applied is based on the point where it last changed from true to false. Note that there are several movement related packets containing this state.

| Serverbound `move_player_status_only`, Play ID: 33 (0x21) |
| --- |
| Field Name | Field Type | Notes |
| Flags | [Byte](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Byte) | Bit field: 0x01: on ground, 0x02: pushing against wall. |

#### Move Vehicle (serverbound)

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=239&veaction=edit "Edit section: Move Vehicle (serverbound)") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=239 "Edit section's source code: Move Vehicle (serverbound)")\]

Sent when a player moves in a client-side-controlled vehicle. Fields are the same position and rotation values as in [Set Player Position and Rotation](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Set_Player_Position_and_Rotation), followed by On Ground. All position and rotation fields are absolute.

| Serverbound `move_vehicle`, Play ID: 34 (0x22) |
| --- |
| Field Name | Field Type | Notes |
| X | [Double](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Double) | Absolute position (X coordinate). |
| Y | [Double](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Double) | Absolute position (Y coordinate). |
| Z | [Double](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Double) | Absolute position (Z coordinate). |
| Yaw | [Float](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Float) | Absolute rotation on the vertical axis, in degrees. |
| Pitch | [Float](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Float) | Absolute rotation on the horizontal axis, in degrees. |
| On Ground | [Boolean](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Boolean) | Whether the vehicle is on the ground. |

#### Paddle Boat

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=240&veaction=edit "Edit section: Paddle Boat") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=240 "Edit section's source code: Paddle Boat")\]

Used to _visually_ update whether boat paddles are turning. The server will update the [Boat entity metadata](https://minecraft.wiki/w/Java_Edition_protocol/Entity_metadata#Boat "Java Edition protocol/Entity metadata") to match the values here.

| Serverbound `paddle_boat`, Play ID: 35 (0x23) |
| --- |
| Field Name | Field Type | Notes |
| Left paddle turning | [Boolean](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Boolean) |  |
| Right paddle turning | [Boolean](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Boolean) |  |

Right paddle turning is set to true when the left button or forward button is held, left paddle turning is set to true when the right button or forward button is held.

#### Pick Item From Block

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=241&veaction=edit "Edit section: Pick Item From Block") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=241 "Edit section's source code: Pick Item From Block")\]

Used for pick block functionality (middle click) on blocks to retrieve items from the inventory in survival or creative mode or create them in creative mode. See [Controls#Pick Block](https://minecraft.wiki/w/Controls#Pick_Block "Controls") for more information.

| Serverbound `pick_item_from_block`, Play ID: 36 (0x24) |
| --- |
| Field Name | Field Type | Notes |
| Location | [Position](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Position) | The location of the block. |
| Include Data | [Boolean](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Boolean) | Used to tell the server to include block data in the new stack, works only if in creative mode. |

#### Pick Item From Entity

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=242&veaction=edit "Edit section: Pick Item From Entity") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=242 "Edit section's source code: Pick Item From Entity")\]

Used for pick block functionality (middle click) on entities to retrieve items from the inventory in survival or creative mode or create them in creative mode. See [Controls#Pick Block](https://minecraft.wiki/w/Controls#Pick_Block "Controls") for more information.

| Serverbound `pick_item_from_entity`, Play ID: 37 (0x25) |
| --- |
| Field Name | Field Type | Notes |
| Entity ID | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) | The ID of the entity to pick. |
| Include Data | [Boolean](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Boolean) | Unused by the vanilla server. |

#### Place Recipe

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=243&veaction=edit "Edit section: Place Recipe") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=243 "Edit section's source code: Place Recipe")\]

This packet is sent when a player clicks a recipe in the crafting book that is craftable (white border).

| Serverbound `place_recipe`, Play ID: 39 (0x27) |
| --- |
| Field Name | Field Type | Notes |
| Window ID | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) |  |
| Recipe ID | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) | ID of recipe previously defined in [Recipe Book Add](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Recipe_Book_Add). |
| Make all | [Boolean](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Boolean) | Affects the amount of items processed; true if shift is down when clicked. |

#### Player Abilities (serverbound)

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=244&veaction=edit "Edit section: Player Abilities (serverbound)") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=244 "Edit section's source code: Player Abilities (serverbound)")\]

The vanilla client sends this packet when the player starts/stops flying with the Flags parameter changed accordingly.

| Serverbound `player_abilities`, Play ID: 40 (0x28) |
| --- |
| Field Name | Field Type | Notes |
| Flags | [Byte](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Byte) | Bit mask. 0x02: is flying. |

#### Player Action

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=245&veaction=edit "Edit section: Player Action") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=245 "Edit section's source code: Player Action")\]

Sent when the player mines a block. A vanilla server only accepts digging packets with coordinates within a 6-unit radius between the center of the block and the player's eyes.

| Serverbound `player_action`, Play ID: 41 (0x29) |
| --- |
| Field Name | Field Type | Notes |
| Status | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) [Enum](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Enum) | The action the player is taking against the block (see below). |
| Location | [Position](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Position) | Block position. |
| Face | [Byte](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Byte) [Enum](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Enum) | The face being hit (see below). |
| Sequence | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) | Block change sequence number (see [#Acknowledge Block Change](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Acknowledge_Block_Change)). |

Status can be one of seven values:

| Value | Meaning | Notes |
| --- | --- | --- |
| 0 | Started digging | Sent when the player starts digging a block. If the block was instamined or the player is in creative mode, the client will _not_ send Status = Finished digging, and will assume the server completed the destruction. To detect this, it is necessary to [calculate the block destruction speed](https://minecraft.wiki/w/Breaking#Speed "Breaking") server-side. |
| 1 | Cancelled digging | Sent when the player lets go of the Mine Block key (default: left click). Face is always set to -Y. |
| 2 | Finished digging | Sent when the client thinks it is finished. |
| 3 | Drop item stack | Triggered by using the Drop Item key (default: Q) with the modifier to drop the entire selected stack (default: Control or Command, depending on OS). Location is always set to 0/0/0, Face is always set to -Y. Sequence is always set to 0. |
| 4 | Drop item | Triggered by using the Drop Item key (default: Q). Location is always set to 0/0/0, Face is always set to -Y. Sequence is always set to 0. |
| 5 | Shoot arrow / finish eating | Indicates that the currently held item should have its state updated, such as eating food, pulling back bows, using buckets, etc. Location is always set to 0/0/0, Face is always set to -Y. Sequence is always set to 0. |
| 6 | Swap item in hand | Used to swap or assign an item to the second hand. Location is always set to 0/0/0, Face is always set to -Y. Sequence is always set to 0. |
| 7 | Stab |  |

The Face field can be one of the following values, representing the face being hit:

| Value | Offset | Face |
| --- | --- | --- |
| 0 | -Y | Bottom |
| 1 | +Y | Top |
| 2 | -Z | North |
| 3 | +Z | South |
| 4 | -X | West |
| 5 | +X | East |

#### Player Command

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=246&veaction=edit "Edit section: Player Command") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=246 "Edit section's source code: Player Command")\]

Sent by the client to indicate that it has performed certain actions: sprinting, exiting a bed, jumping with a horse, and opening a horse's inventory while riding it.

| Serverbound `player_command`, Play ID: 42 (0x2A) |
| --- |
| Field Name | Field Type | Notes |
| Entity ID | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) | Player ID (ignored by the vanilla server) |
| Action ID | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) [Enum](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Enum) | The ID of the action, see below. |
| Jump Boost | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) | Only used by the “start jump with horse” action, in which case it ranges from 0 to 100. In all other cases it is 0. |

Action ID can be one of the following values:

| ID | Action |
| --- | --- |
| 0 | Leave bed |
| 1 | Start sprinting |
| 2 | Stop sprinting |
| 3 | Start jump with horse |
| 4 | Stop jump with horse |
| 5 | Open vehicle inventory |
| 6 | Start flying with elytra |

Leave bed is only sent when the “Leave Bed” button is clicked on the sleep GUI, not when waking up in the morning.

Open vehicle inventory is only sent when pressing the inventory key (default: E) while on a horse or chest boat — all other methods of opening such an inventory (involving right-clicking or shift-right-clicking it) do not use this packet.

#### Player Input

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=247&veaction=edit "Edit section: Player Input") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=247 "Edit section's source code: Player Input")\]

Sent whenever the player presses or releases certain keys. The flags correspond directly to the states of their corresponding keys—the Sprint flag does not depend on whether the player is actually able to sprint at the moment, etc.

Used by the vanilla server for minecart controls, player inputs in the `entity_properties` [predicate](https://minecraft.wiki/w/Predicate "Predicate"), and sneaking (sprinting is still controlled by [Player Command](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Player_Command)).

| Serverbound `player_input`, Play ID: 43 (0x2B) |
| --- |
| Field Name | Field Type | Notes |
| Flags | [Unsigned Byte](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Unsigned_Byte) | Bit mask; see below |

The flags are as follows:

| Hex Mask | Field |
| --- | --- |
| 0x01 | Forward |
| 0x02 | Backward |
| 0x04 | Left |
| 0x08 | Right |
| 0x10 | Jump |
| 0x20 | Sneak |
| 0x40 | Sprint |

#### Player Loaded

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=248&veaction=edit "Edit section: Player Loaded") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=248 "Edit section's source code: Player Loaded")\]

Sent by the client to indicate that it is ready to start simulating the player. The vanilla client sends this [when the "Loading terrain..." screen is closed](https://minecraft.wiki/w/Java_Edition_protocol/FAQ#%E2%80%A6my_player_isn't_spawning! "Java Edition protocol/FAQ"). (But see the caveat below.)

The vanilla client skips ticking the player entity until the tick on which this packet is sent (the first tick will happen between this packet and the next [Client Tick End](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Client_Tick_End)). Other entities and objects will still be ticked.

Once 60 ticks have elapsed since the last Login or Respawn packet, the vanilla client will start ticking the player and **skip sending this packet completely**, even after the usual conditions for it have been met. This can happen even before the "Start waiting for level chunks" [Game Event](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Game_Event) is received. The loading screen is not affected in any way by this timer (except indirectly by the player falling into the void after ticking has started). Likewise, the vanilla server will assume that the client has loaded if it takes longer than 60 server ticks to send this packet. A more robust way to detect this condition is to count the number of [Client Tick End](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Client_Tick_End) packets sent by the client. The first player tick will occur after 60 Client Tick End packets have been sent. To determine when this counter should be restarted following a respawn, the Respawn packet can be sent in a [bundle](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Bundle_Delimiter) together with a [Ping](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Ping) packet.

| Serverbound `player_loaded`, Play ID: 44 (0x2C) |
| --- |
| Field Name | Field Type | Notes |
| _no fields_ |

#### Punch

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=249&veaction=edit "Edit section: Punch") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=249 "Edit section's source code: Punch")\]

Sent when the client punches.

| Serverbound `punch`, Play ID: 46 (0x2E) |
| --- |
| Field Name | Field Type | Notes |
| _no fields_ |

#### Change Recipe Book Settings

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=250&veaction=edit "Edit section: Change Recipe Book Settings") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=250 "Edit section's source code: Change Recipe Book Settings")\]

Replaces Recipe Book Data, type 1.

| Serverbound `recipe_book_change_settings`, Play ID: 47 (0x2F) |
| --- |
| Field Name | Field Type | Notes |
| Book ID | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) [Enum](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Enum) | 0: crafting, 1: furnace, 2: blast furnace, 3: smoker. |
| Book Open | [Boolean](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Boolean) |  |
| Filter Active | [Boolean](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Boolean) |  |

#### Set Seen Recipe

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=251&veaction=edit "Edit section: Set Seen Recipe") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=251 "Edit section's source code: Set Seen Recipe")\]

Sent when recipe is first seen in recipe book. Replaces Recipe Book Data, type 0.

| Serverbound `recipe_book_seen_recipe`, Play ID: 48 (0x30) |
| --- |
| Field Name | Field Type | Notes |
| Recipe ID | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) | ID of recipe previously defined in Recipe Book Add. |

#### Rename Item

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=252&veaction=edit "Edit section: Rename Item") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=252 "Edit section's source code: Rename Item")\]

Sent as a player is renaming an item in an anvil (each keypress in the anvil UI sends a new Rename Item packet). If the new name is empty, then the item loses its custom name (this is different from setting the custom name to the normal name of the item). The item name may be no longer than 50 characters, and if it is longer than that, then the rename is silently ignored.

| Serverbound `rename_item`, Play ID: 49 (0x31) |
| --- |
| Field Name | Field Type | Notes |
| Item name | [String](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:String) (32767) | The new name of the item. |

#### Seen Advancements

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=253&veaction=edit "Edit section: Seen Advancements") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=253 "Edit section's source code: Seen Advancements")\]

| Serverbound `seen_advancements`, Play ID: 51 (0x33) |
| --- |
| Field Name | Field Type | Notes |
| Action | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) [Enum](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Enum) | 0: Opened tab, 1: Closed screen. |
| Tab ID | [Optional](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Optional) [Identifier](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Identifier) | Only present if action is Opened tab. |

#### Select Trade

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=254&veaction=edit "Edit section: Select Trade") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=254 "Edit section's source code: Select Trade")\]

When a player selects a specific trade offered by a villager NPC.

| Serverbound `select_trade`, Play ID: 52 (0x34) |
| --- |
| Field Name | Field Type | Notes |
| Selected slot | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) | The selected slot in the player's current (trading) inventory. |

#### Set Beacon Effect

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=255&veaction=edit "Edit section: Set Beacon Effect") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=255 "Edit section's source code: Set Beacon Effect")\]

Changes the effect of the current beacon.

| Serverbound `set_beacon`, Play ID: 53 (0x35) |
| --- |
| Field Name | Field Type | Notes |
| Primary Effect | [Prefixed Optional](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Prefixed_Optional) [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) | A [Potion ID](https://minecraft.wiki/w/Potion#ID "Potion"). |
| Secondary Effect | [Prefixed Optional](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Prefixed_Optional) [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) | A [Potion ID](https://minecraft.wiki/w/Potion#ID "Potion"). |

#### Set Held Item (serverbound)

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=256&veaction=edit "Edit section: Set Held Item (serverbound)") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=256 "Edit section's source code: Set Held Item (serverbound)")\]

Sent when the player changes the slot selection.

| Serverbound `set_carried_item`, Play ID: 54 (0x36) |
| --- |
| Field Name | Field Type | Notes |
| Slot | [Short](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Short) | The slot which the player has selected (0–8). |

#### Program Command Block

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=257&veaction=edit "Edit section: Program Command Block") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=257 "Edit section's source code: Program Command Block")\]

| Serverbound `set_command_block`, Play ID: 55 (0x37) |
| --- |
| Field Name | Field Type | Notes |
| Location | [Position](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Position) |  |
| Command | [String](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:String) (32767) |  |
| Mode | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) [Enum](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Enum) | 0: chain, 1: repeating, 2: impulse. |
| Flags | [Byte](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Byte) | 0x01: Track Output (if false, the output of the previous command will not be stored within the command block); 0x02: Is conditional; 0x04: Automatic. |

#### Program Command Block Minecart

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=258&veaction=edit "Edit section: Program Command Block Minecart") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=258 "Edit section's source code: Program Command Block Minecart")\]

| Serverbound `set_command_minecart`, Play ID: 56 (0x38) |
| --- |
| Field Name | Field Type | Notes |
| Entity ID | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) |  |
| Command | [String](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:String) (32767) |  |
| Track Output | [Boolean](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Boolean) | If false, the output of the previous command will not be stored within the command block. |

#### Set Creative Mode Slot

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=259&veaction=edit "Edit section: Set Creative Mode Slot") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=259 "Edit section's source code: Set Creative Mode Slot")\]

While the user is in the standard inventory (i.e., not a crafting bench) in Creative mode, the player will send this packet.

Clicking in the creative inventory menu is quite different from non-creative inventory management. Picking up an item with the mouse actually deletes the item from the server, and placing an item into a slot or dropping it out of the inventory actually tells the server to create the item from scratch. (This can be verified by clicking an item that you don't mind deleting, then severing the connection to the server; the item will be nowhere to be found when you log back in.) As a result of this implementation strategy, the "Destroy Item" slot is just a client-side implementation detail that means "I don't intend to recreate this item.". Additionally, the long listings of items (by category, etc.) are a client-side interface for choosing which item to create. Picking up an item from such listings sends no packets to the server; only when you put it somewhere does it tell the server to create the item in that location.

This action can be described as "set inventory slot". Picking up an item sets the slot to item ID -1. Placing an item into an inventory slot sets the slot to the specified item. Dropping an item (by clicking outside the window) effectively sets slot -1 to the specified item, which causes the server to spawn the item entity, etc.. All other inventory slots are numbered the same as the non-creative inventory (including slots for the 2×2 crafting menu, even though they aren't visible in the vanilla client).

| Serverbound `set_creative_mode_slot`, Play ID: 57 (0x39) |
| --- |
| Field Name | Field Type | Notes |
| Slot | [Short](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Short) | Inventory slot. |
| Clicked Item | [Slot](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Slot) |  |

#### Set Game Rules

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=260&veaction=edit "Edit section: Set Game Rules") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=260 "Edit section's source code: Set Game Rules")\]

| Serverbound `set_game_rule`, Play ID: 58 (0x3A) |
| --- |
| Field Name | Field Type | Notes |
| Rules | Name | [Prefixed Array](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Prefixed_Array) | [Identifier](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Identifier) |  |
| Value | [String](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:String) (32767) |  |

#### Program Jigsaw Block

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=261&veaction=edit "Edit section: Program Jigsaw Block") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=261 "Edit section's source code: Program Jigsaw Block")\]

Sent when Done is pressed on the [Jigsaw Block](https://minecraft.wiki/w/Jigsaw_Block "Jigsaw Block") interface.

| Serverbound `set_jigsaw_block`, Play ID: 59 (0x3B) |
| --- |
| Field Name | Field Type | Notes |
| Location | [Position](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Position) | Block entity location |
| Name | [Identifier](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Identifier) |  |
| Target | [Identifier](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Identifier) |  |
| Pool | [Identifier](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Identifier) |  |
| Final state | [String](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:String) (32767) | "Turns into" on the GUI, `final_state` in NBT. |
| Joint type | [String](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:String) (32767) | `rollable` if the attached piece can be rotated, else `aligned`. |
| Selection priority | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) |  |
| Placement priority | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) |  |

#### Program Structure Block

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=262&veaction=edit "Edit section: Program Structure Block") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=262 "Edit section's source code: Program Structure Block")\]

| Serverbound `set_structure_block`, Play ID: 60 (0x3C) |
| --- |
| Field Name | Field Type | Notes |
| Location | [Position](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Position) | Block entity location. |
| Action | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) [Enum](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Enum) | An additional action to perform beyond simply saving the given data; see below. |
| Mode | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) [Enum](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Enum) | One of SAVE (0), LOAD (1), CORNER (2), DATA (3). |
| Name | [String](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:String) (32767) |  |
| Offset X | [Byte](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Byte) | Between -48 and 48. |
| Offset Y | [Byte](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Byte) | Between -48 and 48. |
| Offset Z | [Byte](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Byte) | Between -48 and 48. |
| Size X | [Byte](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Byte) | Between 0 and 48. |
| Size Y | [Byte](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Byte) | Between 0 and 48. |
| Size Z | [Byte](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Byte) | Between 0 and 48. |
| Mirror | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) [Enum](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Enum) | One of NONE (0), LEFT\_RIGHT (1), FRONT\_BACK (2). |
| Rotation | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) [Enum](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Enum) | One of NONE (0), CLOCKWISE\_90 (1), CLOCKWISE\_180 (2), COUNTERCLOCKWISE\_90 (3). |
| Metadata | [String](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:String) (128) |  |
| Integrity | [Float](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Float) | Between 0 and 1. |
| Seed | [VarLong](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarLong) |  |
| Flags | [Byte](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Byte) | 0x01: Ignore entities; 0x02: Show air; 0x04: Show bounding box; 0x08: Strict placement. |

Possible actions:

- 0 - Update data
- 1 - Save the structure
- 2 - Load the structure
- 3 - Detect size

The vanilla client uses update data to indicate no special action should be taken (i.e. the done button).

#### Set Test Block

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=263&veaction=edit "Edit section: Set Test Block") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=263 "Edit section's source code: Set Test Block")\]

Updates the value of the [Test Block](https://minecraft.wiki/w/Test_Block "Test Block") at the given position.

| Serverbound `set_test_block`, Play ID: 61 (0x3D) |
| --- |
| Field Name | Field Type | Notes |
| Position | [Position](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Position) |  |
| Mode | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) [Enum](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Enum) | 0: start, 1: log, 2: fail, 3: accept |
| Message | [String](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:String) |  |

#### Update Sign

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=264&veaction=edit "Edit section: Update Sign") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=264 "Edit section's source code: Update Sign")\]

This message is sent from the client to the server when the “Done” button is pushed after editing a sign.

The server only accepts this packet after [Open Sign Editor](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Open_Sign_Editor), otherwise this packet is silently ignored.

| Serverbound `sign_update`, Play ID: 62 (0x3E) |
| --- |
| Field Name | Field Type | Notes |
| Location | [Position](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Position) | Block coordinates. |
| Line 1 | [String](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:String) (384) | First line of text in the sign. |
| Line 2 | [String](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:String) (384) | Second line of text in the sign. |
| Line 3 | [String](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:String) (384) | Third line of text in the sign. |
| Line 4 | [String](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:String) (384) | Fourth line of text in the sign. |
| Text Slot | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) [Enum](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Enum) | Selects which sign text slot is updated; see below. |

Text Slot can be one of the following values:

| ID | Name |
| --- | --- |
| 0 | Back |
| 1 | Front |

#### Spectator Action

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=265&veaction=edit "Edit section: Spectator Action") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=265 "Edit section's source code: Spectator Action")\]

Sent when the player left-clicks in spectator mode.

| Serverbound `spectator_action`, Play ID: 63 (0x3F) |
| --- |
| Field Name | Field Type | Notes |
| Entity ID | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) | If 0, the player was not targeting an entity. Otherwise the ID of the targeted entity plus 1. |

#### Teleport To Entity

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=266&veaction=edit "Edit section: Teleport To Entity") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=266 "Edit section's source code: Teleport To Entity")\]

Teleports the player to the given entity. The player must be in spectator mode.

The vanilla client only uses this to teleport to players, but it appears to accept any type of entity. The entity does not need to be in the same dimension as the player; if necessary, the player will be respawned in the right world. If the given entity cannot be found (or isn't loaded), this packet will be ignored.

| Serverbound `teleport_to_entity`, Play ID: 64 (0x40) |
| --- |
| Field Name | Field Type | Notes |
| Target Player | [UUID](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:UUID) | UUID of the player to teleport to (can also be an entity UUID). |

#### Test Instance Block Action

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=267&veaction=edit "Edit section: Test Instance Block Action") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=267 "Edit section's source code: Test Instance Block Action")\]

Tries to perform an action the [Test Instance Block](https://minecraft.wiki/w/Test_Instance_Block "Test Instance Block") at the given position.

| Serverbound `test_instance_block_action`, Play ID: 65 (0x41) |
| --- |
| Field Name | Field Type | Notes |
| Position | [Position](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Position) |  |
| Action | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) [Enum](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Enum) | 0: init, 1: query, 2: set, 3: reset, 4: save, 5: export, 6: run. |
| Test | [Prefixed Optional](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Prefixed_Optional) [Identifier](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Identifier) | ID in the `minecraft:test_instance` registry. |
| Size X | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) |  |
| Size Y | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) |  |
| Size Z | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) |  |
| Rotation | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) [Enum](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Enum) | 0: none, 1: clockwise 90°, 2: clockwise 180°, 3: counter-clockwise 90°. |
| Ignore Entities | [Boolean](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Boolean) |  |
| Status | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) [Enum](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Enum) | 0: cleared, 1: running, 2: finished. |
| Error Message | [Prefixed Optional](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Prefixed_Optional) [Text Component](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Text_Component) |  |

#### Use Item On

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=268&veaction=edit "Edit section: Use Item On") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=268 "Edit section's source code: Use Item On")\]

| Serverbound `use_item_on`, Play ID: 66 (0x42) |
| --- |
| Field Name | Field Type | Notes |
| Hand | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) [Enum](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Enum) | The hand from which the block is placed; 0: main hand, 1: off hand. |
| Location | [Position](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Position) | Block position. |
| Face | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) [Enum](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Enum) | The face on which the block is placed (as documented at [Player Action](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Player_Action)). |
| Cursor Position X | [Float](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Float) | The position of the crosshair on the block, from 0 to 1 increasing from west to east. |
| Cursor Position Y | [Float](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Float) | The position of the crosshair on the block, from 0 to 1 increasing from bottom to top. |
| Cursor Position Z | [Float](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Float) | The position of the crosshair on the block, from 0 to 1 increasing from north to south. |
| Inside block | [Boolean](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Boolean) | True when the player's head is inside of a block. |
| World Border Hit | [Boolean](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Boolean) | Seems to always be false, even when interacting with blocks around or outside the world border, or while the player is outside the border. |
| Sequence | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) | Block change sequence number (see [#Acknowledge Block Change](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Acknowledge_Block_Change)). |

Upon placing a block, this packet is sent once.

The Cursor Position X/Y/Z fields (also known as in-block coordinates) are calculated using raytracing. The unit corresponds to sixteen pixels in the default resource pack. For example, let's say a slab is being placed against the south face of a full block. The Cursor Position X will be higher if the player was pointing near the right (east) edge of the face, lower if pointing near the left. The Cursor Position Y will be used to determine whether it will appear as a bottom slab (values 0.0–0.5) or as a top slab (values 0.5-1.0). The Cursor Position Z should be 1.0 since the player was looking at the southernmost part of the block.

Inside block is true when a player's head (specifically eyes) are inside of a block's collision. In 1.13 and later versions, collision is rather complicated and individual blocks can have multiple collision boxes. For instance, a ring of vines has a non-colliding hole in the middle. This value is only true when the player is directly in the box. In practice, though, this value is only used by scaffolding to place in front of the player when sneaking inside of it (other blocks will place behind when you intersect with them -- try with glass for instance).

#### Use Item

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=269&veaction=edit "Edit section: Use Item") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=269 "Edit section's source code: Use Item")\]

Sent when pressing the Use Item key (default: right click) with an item in hand.

| Serverbound `use_item`, Play ID: 67 (0x43) |
| --- |
| Field Name | Field Type | Notes |
| Hand | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) [Enum](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Enum) | Hand used for the animation. 0: main hand, 1: off hand. |
| Sequence | [VarInt](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:VarInt) | Block change sequence number (see [#Acknowledge Block Change](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Acknowledge_Block_Change)). |
| Yaw | [Float](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Float) | Player head rotation around the Y-Axis. |
| Pitch | [Float](https://minecraft.wiki/w/Java_Edition_protocol/Packets#Type:Float) | Player head rotation around the X-Axis. |

The player's rotation is permanently updated according to the Yaw and Pitch fields before performing the action, unless there is no item in the specified hand.

## Navigation

\[ [edit](https://minecraft.wiki/w/Java_Edition_protocol/Packets?section=270&veaction=edit "Edit section: Navigation") \| [edit source](https://minecraft.wiki/w/Java_Edition_protocol/Packets?action=edit&section=270 "Edit section's source code: Navigation")\]

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
| [Level format](https://minecraft.wiki/w/Java_Edition_level_format "Java Edition level format") | - [![](https://minecraft.wiki/images/BlockSprite_anvil.png?a26c9)](https://minecraft.wiki/w/Anvil_file_format "Anvil file format")[Anvil file format](https://minecraft.wiki/w/Anvil_file_format "Anvil file format")
- [![](https://minecraft.wiki/images/EnvSprite_chunk.png?b2cf1)](https://minecraft.wiki/w/Chunk_format "Chunk format")[Chunk format](https://minecraft.wiki/w/Chunk_format "Chunk format")
- [![](https://minecraft.wiki/images/EntitySprite_steve.png?856f8)](https://minecraft.wiki/w/Player.dat_format "Player.dat format")[Player format](https://minecraft.wiki/w/Player.dat_format "Player.dat format")
- [![](https://minecraft.wiki/images/BlockSprite_lodestone.png?00f1a)](https://minecraft.wiki/w/Point_of_Interest_format "Point of Interest format")[Point of Interest format](https://minecraft.wiki/w/Point_of_Interest_format "Point of Interest format")
- [![](https://minecraft.wiki/images/EntitySprite_ravager.png?40196)](https://minecraft.wiki/w/Raids.dat_format "Raids.dat format")[raids.dat format](https://minecraft.wiki/w/Raids.dat_format "Raids.dat format")
- [![](https://minecraft.wiki/images/BlockSprite_chain-command-block.png?0afa8)](https://minecraft.wiki/w/Command_storage_format "Command storage format")[Command storage format](https://minecraft.wiki/w/Command_storage_format "Command storage format")
- [![](https://minecraft.wiki/images/EnvSprite_scoreboard.png?38feb)](https://minecraft.wiki/w/Scoreboard#NBT_format "Scoreboard")[Scoreboard format](https://minecraft.wiki/w/Scoreboard#NBT_format "Scoreboard")

| Legacy | - [![](https://minecraft.wiki/images/LegacyBlockSprite_bricks-je1.png?9a58b)](https://minecraft.wiki/w/Java_Edition_Classic_level_format "Java Edition Classic level format")[Classic level format](https://minecraft.wiki/w/Java_Edition_Classic_level_format "Java Edition Classic level format")<br>- [Classic server protocol](https://minecraft.wiki/w/Classic_server_protocol "Classic server protocol")<br>- [![](https://minecraft.wiki/images/EntitySprite_rana.png?3f2f9)](https://minecraft.wiki/w/Java_Edition_Indev_level_format "Java Edition Indev level format")[Indev level format](https://minecraft.wiki/w/Java_Edition_Indev_level_format "Java Edition Indev level format")<br>- [![](https://minecraft.wiki/images/EnvSprite_nether-portal.png?47646)](https://minecraft.wiki/w/Java_Edition_Alpha_level_format "Java Edition Alpha level format")[Alpha level format](https://minecraft.wiki/w/Java_Edition_Alpha_level_format "Java Edition Alpha level format")<br>  - [![](https://minecraft.wiki/images/LegacyItemSprite_oak-door-revision-1.png?b7426)](https://minecraft.wiki/w/Zone_file_format "Zone file format")[Zone file format](https://minecraft.wiki/w/Zone_file_format "Zone file format")<br>- [![](https://minecraft.wiki/images/ItemSprite_locked-map.png?66bd6)](https://minecraft.wiki/w/Region_file_format "Region file format")[Region file format](https://minecraft.wiki/w/Region_file_format "Region file format")<br>- [![](https://minecraft.wiki/images/Servers.png?b1dc2)](https://minecraft.wiki/w/Server_level.dat "Server level.dat")[server\_level.dat format](https://minecraft.wiki/w/Server_level.dat "Server level.dat")<br>- [![](https://minecraft.wiki/images/EnvSprite_new-village.png?43174)](https://minecraft.wiki/w/Villages.dat_format "Villages.dat format")[villages.dat format](https://minecraft.wiki/w/Villages.dat_format "Villages.dat format")<br>- [![](https://minecraft.wiki/images/EnvSprite_abandoned-mineshaft.png?fab65)](https://minecraft.wiki/w/Generated_structures_data_file_format "Generated structures data file format")[Generated structures format](https://minecraft.wiki/w/Generated_structures_data_file_format "Generated structures data file format") | | |
| [.minecraft](https://minecraft.wiki/w/.minecraft ".minecraft") | - [![](https://minecraft.wiki/images/thumb/File_archive.png/16px-File_archive.png?5ba7d)](https://minecraft.wiki/w/Client.jar "Client.jar")[client.jar](https://minecraft.wiki/w/Client.jar "Client.jar")<br>  - [![](https://minecraft.wiki/images/EnvSprite_number.png?9ceb9)](https://minecraft.wiki/w/Version.json "Version.json")[version.json](https://minecraft.wiki/w/Version.json "Version.json")<br>- [![](https://minecraft.wiki/images/ItemSprite_book-and-quill.png?f190b)](https://minecraft.wiki/w/Client.json "Client.json")[client.json](https://minecraft.wiki/w/Client.json "Client.json")<br>- [![](https://minecraft.wiki/images/BlockSprite_command-block.png?e7078)](https://minecraft.wiki/w/Command_history.txt "Command history.txt")[command\_history.txt](https://minecraft.wiki/w/Command_history.txt "Command history.txt")<br>- [![](https://minecraft.wiki/images/BlockSprite_chest.png?15d81)](https://minecraft.wiki/w/Launcher_profiles.json "Launcher profiles.json")[launcher\_profiles.json](https://minecraft.wiki/w/Launcher_profiles.json "Launcher profiles.json")<br>- [![](https://minecraft.wiki/images/BlockSprite_gear.png?03da3)](https://minecraft.wiki/w/Launcher_settings.json "Launcher settings.json")[launcher\_settings.json](https://minecraft.wiki/w/Launcher_settings.json "Launcher settings.json")<br>- [![](https://minecraft.wiki/images/Chat_settings_gear.png?6a179)](https://minecraft.wiki/w/Options.txt "Options.txt")[options.txt](https://minecraft.wiki/w/Options.txt "Options.txt")<br>- [![](https://minecraft.wiki/images/EnvSprite_number.png?9ceb9)](https://minecraft.wiki/w/Version_manifest.json "Version manifest.json")[version\_manifest.json](https://minecraft.wiki/w/Version_manifest.json "Version manifest.json")<br>- [![](https://minecraft.wiki/images/ItemSprite_paper.png?565a1)](https://minecraft.wiki/w/Hotbar.nbt_format "Hotbar.nbt format")[hotbar.nbt format](https://minecraft.wiki/w/Hotbar.nbt_format "Hotbar.nbt format")<br>- [![](https://minecraft.wiki/images/Servers.png?b1dc2)](https://minecraft.wiki/w/Servers.dat_format "Servers.dat format")[Server list format](https://minecraft.wiki/w/Servers.dat_format "Servers.dat format") |
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
| [Protocol](https://minecraft.wiki/w/Java_Edition_protocol "Java Edition protocol") | - [![](https://minecraft.wiki/images/EnvSprite_number.png?9ceb9)](https://minecraft.wiki/w/Protocol_version "Protocol version")[Protocol version](https://minecraft.wiki/w/Protocol_version "Protocol version")<br>- [![](https://minecraft.wiki/images/ItemSprite_bundle.png?9eb9f)](https://minecraft.wiki/w/Java_Edition_protocol/Packets "Java Edition protocol/Packets")Packets<br>- [Data types](https://minecraft.wiki/w/Java_Edition_protocol/Data_types "Java Edition protocol/Data types")<br>- [![](https://minecraft.wiki/images/ItemSprite_trial-key.png?9e6c1)](https://minecraft.wiki/w/Java_Edition_protocol/Encryption "Java Edition protocol/Encryption")[Encryption](https://minecraft.wiki/w/Java_Edition_protocol/Encryption "Java Edition protocol/Encryption") |
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
- [![](https://minecraft.wiki/images/ItemSprite_footprint.png?1c844)](https://minecraft.wiki/w/Slot_sources "Slot sources")[Slot sources](https://minecraft.wiki/w/Slot_sources "Slot sources")
- [![](https://minecraft.wiki/images/ItemSprite_danger-pottery-sherd.png?b8147)](https://minecraft.wiki/w/Decorated_pot_pattern_definition "Decorated pot pattern definition")[Decorated pot pattern](https://minecraft.wiki/w/Decorated_pot_pattern_definition "Decorated pot pattern definition")
- [![](https://minecraft.wiki/images/EnvSprite_number.png?9ceb9)](https://minecraft.wiki/w/Number_provider "Number provider")[Number provider](https://minecraft.wiki/w/Number_provider "Number provider")
- [![](https://minecraft.wiki/images/ItemSprite_wooden-hoe.png?30fb3)](https://minecraft.wiki/w/Block_transformer_definition "Block transformer definition")[Block transformer](https://minecraft.wiki/w/Block_transformer_definition "Block transformer definition")

| [Tag](https://minecraft.wiki/w/Tag_(Java_Edition) "Tag (Java Edition)") | - [![](https://minecraft.wiki/images/BlockSprite_grass-block.png?97c2e)](https://minecraft.wiki/w/Block_tag_(Java_Edition) "Block tag (Java Edition)")[Block](https://minecraft.wiki/w/Block_tag_(Java_Edition) "Block tag (Java Edition)")<br>- [![](https://minecraft.wiki/images/EnvSprite_item.png?89d23)](https://minecraft.wiki/w/Item_tag_(Java_Edition) "Item tag (Java Edition)")[Item](https://minecraft.wiki/w/Item_tag_(Java_Edition) "Item tag (Java Edition)")<br>- [![](https://minecraft.wiki/images/BlockSprite_repeating-command-block.png?1dad0)](https://minecraft.wiki/w/Function_tag_(Java_Edition) "Function tag (Java Edition)")[Function](https://minecraft.wiki/w/Function_tag_(Java_Edition) "Function tag (Java Edition)")<br>- [![](https://minecraft.wiki/images/ItemSprite_water-bucket.png?6e72b)](https://minecraft.wiki/w/Fluid_tag_(Java_Edition) "Fluid tag (Java Edition)")[Fluid](https://minecraft.wiki/w/Fluid_tag_(Java_Edition) "Fluid tag (Java Edition)")<br>- [![](https://minecraft.wiki/images/EnvSprite_entities.png?94711)](https://minecraft.wiki/w/Entity_type_tag_(Java_Edition) "Entity type tag (Java Edition)")[Entity type](https://minecraft.wiki/w/Entity_type_tag_(Java_Edition) "Entity type tag (Java Edition)")<br>- [![](https://minecraft.wiki/images/BlockSprite_sculk-sensor.png?ccbdb)](https://minecraft.wiki/w/Game_event_tag_(Java_Edition) "Game event tag (Java Edition)")[Game event](https://minecraft.wiki/w/Game_event_tag_(Java_Edition) "Game event tag (Java Edition)")<br>- [![](https://minecraft.wiki/images/BiomeSprite_forest.png?98e29)](https://minecraft.wiki/w/Biome_tag_(Java_Edition) "Biome tag (Java Edition)")[Biome](https://minecraft.wiki/w/Biome_tag_(Java_Edition) "Biome tag (Java Edition)")<br>- [![](https://minecraft.wiki/images/EnvSprite_superflat.png?54c14)](https://minecraft.wiki/w/Flat_level_generator_preset_tag_(Java_Edition) "Flat level generator preset tag (Java Edition)")[Flat level generator preset](https://minecraft.wiki/w/Flat_level_generator_preset_tag_(Java_Edition) "Flat level generator preset tag (Java Edition)")<br>- [![](https://minecraft.wiki/images/EnvSprite_mountain.png?2e0ae)](https://minecraft.wiki/w/World_preset_tag_(Java_Edition) "World preset tag (Java Edition)")[World preset](https://minecraft.wiki/w/World_preset_tag_(Java_Edition) "World preset tag (Java Edition)")<br>- [![](https://minecraft.wiki/images/EnvSprite_jungle-pyramid.png?be383)](https://minecraft.wiki/w/Structure_tag_(Java_Edition) "Structure tag (Java Edition)")[Structure](https://minecraft.wiki/w/Structure_tag_(Java_Edition) "Structure tag (Java Edition)")<br>- [![](https://minecraft.wiki/images/BlockSprite_lodestone.png?00f1a)](https://minecraft.wiki/w/Point_of_interest_type_tag_(Java_Edition) "Point of interest type tag (Java Edition)")[Point of interest type](https://minecraft.wiki/w/Point_of_interest_type_tag_(Java_Edition) "Point of interest type tag (Java Edition)")<br>- [![](https://minecraft.wiki/images/ItemSprite_painting.png?55d20)](https://minecraft.wiki/w/Painting_variant_tag_(Java_Edition) "Painting variant tag (Java Edition)")[Painting variant](https://minecraft.wiki/w/Painting_variant_tag_(Java_Edition) "Painting variant tag (Java Edition)")<br>- [![](https://minecraft.wiki/images/BlockSprite_white-banner.png?8b4d0)](https://minecraft.wiki/w/Banner_pattern_tag_(Java_Edition) "Banner pattern tag (Java Edition)")[Banner pattern](https://minecraft.wiki/w/Banner_pattern_tag_(Java_Edition) "Banner pattern tag (Java Edition)")<br>- [![](https://minecraft.wiki/images/ItemSprite_goat-horn.png?e5a9f)](https://minecraft.wiki/w/Instrument_tag_(Java_Edition) "Instrument tag (Java Edition)")[Instrument](https://minecraft.wiki/w/Instrument_tag_(Java_Edition) "Instrument tag (Java Edition)")<br>- ![❤️](https://minecraft.wiki/images/Heart_%28icon%29.png?faf83)[Damage type](https://minecraft.wiki/w/Damage_type_tag_(Java_Edition) "Damage type tag (Java Edition)")<br>- [![](https://minecraft.wiki/images/ItemSprite_enchanted-book.png?b7877)](https://minecraft.wiki/w/Enchantment_tag_(Java_Edition) "Enchantment tag (Java Edition)")[Enchantment](https://minecraft.wiki/w/Enchantment_tag_(Java_Edition) "Enchantment tag (Java Edition)")<br>- [![](https://minecraft.wiki/images/ItemSprite_paper.png?565a1)](https://minecraft.wiki/w/Dialog_tag_(Java_Edition) "Dialog tag (Java Edition)")[Dialog](https://minecraft.wiki/w/Dialog_tag_(Java_Edition) "Dialog tag (Java Edition)")<br>- [![](https://minecraft.wiki/images/ItemSprite_clock.png?30324)](https://minecraft.wiki/w/Timeline_tag_(Java_Edition) "Timeline tag (Java Edition)")[Timeline](https://minecraft.wiki/w/Timeline_tag_(Java_Edition) "Timeline tag (Java Edition)")<br>- [![](https://minecraft.wiki/images/ItemSprite_water-bottle.png?fe7c2)](https://minecraft.wiki/w/Potion_tag_(Java_Edition) "Potion tag (Java Edition)")[Potion](https://minecraft.wiki/w/Potion_tag_(Java_Edition) "Potion tag (Java Edition)")<br>- [![](https://minecraft.wiki/images/EntitySprite_villager.png?05433)](https://minecraft.wiki/w/Villager_trade_tag_(Java_Edition) "Villager trade tag (Java Edition)")[Villager trade](https://minecraft.wiki/w/Villager_trade_tag_(Java_Edition) "Villager trade tag (Java Edition)")<br>- [![](https://minecraft.wiki/images/thumb/Wrench.png/16px-Wrench.png?fae21)](https://minecraft.wiki/w/Configured_feature_tag_(Java_Edition) "Configured feature tag (Java Edition)")[Configured feature](https://minecraft.wiki/w/Configured_feature_tag_(Java_Edition) "Configured feature tag (Java Edition)") |
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

[![](https://minecraft.wiki/images/License_cc.svg?7c689)](https://minecraft.wiki/w/File:License_cc.svg "File:License cc.svg")

[![](https://minecraft.wiki/images/License_cc-by.svg?818e9)](https://minecraft.wiki/w/File:License_cc-by.svg)[![](https://minecraft.wiki/images/License_cc-by-sa.svg?75cd1)](https://minecraft.wiki/w/File:License_cc-by-sa.svg)

This article is licensed under a [Creative Commons Attribution-ShareAlike 3.0](https://creativecommons.org/licenses/by-sa/3.0/) license.

This article has been imported from [wiki.vg](https://minecraft.wiki/w/Minecraft_Wiki:Projects/wiki.vg_merge "Minecraft Wiki:Projects/wiki.vg merge") or is a derivative of such a page. Thus, the wiki's [usual license](https://minecraft.wiki/w/Minecraft_Wiki:Copyrights "Minecraft Wiki:Copyrights") does not apply.

Derivative works must be licensed using the same or a compatible license.

Retrieved from " [https://minecraft.wiki/w/Java\_Edition\_protocol/Packets?oldid=3790659](https://minecraft.wiki/w/Java_Edition_protocol/Packets?oldid=3790659)"

[Categories](https://minecraft.wiki/w/Special:Categories "Special:Categories"):

- [Java Edition](https://minecraft.wiki/w/Category:Java_Edition "Category:Java Edition")
- [Java Edition technical](https://minecraft.wiki/w/Category:Java_Edition_technical "Category:Java Edition technical")
- [Protocol Details](https://minecraft.wiki/w/Category:Protocol_Details "Category:Protocol Details")
- [Java Edition protocol](https://minecraft.wiki/w/Category:Java_Edition_protocol "Category:Java Edition protocol")
- [CC BY-SA pages](https://minecraft.wiki/w/Category:CC_BY-SA_pages "Category:CC BY-SA pages")

Hidden category:

- [Articles to be expanded](https://minecraft.wiki/w/Category:Articles_to_be_expanded "Category:Articles to be expanded")

## Navigation menu

Search

[Visit the main page](https://minecraft.wiki/ "Visit the main page")

[X](https://minecraft.wiki/w/Minecraft_Wiki:Indie_Wiki_Buddy)

**To leave feedback for the game, [click here](https://feedback.minecraft.net/).**

Feedback will be posted anonymously and shared to our [Discord](https://discord.gg/fGdE5ZE).

Something went wrong

Dismiss