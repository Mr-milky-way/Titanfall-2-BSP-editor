#include <iostream>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <list>
#include <cstdint>
#include <vector>
#include <filesystem>
#include <filesystem>
#include "../titanfall2bspData/structs.h"

using namespace std;

string intToHexString(int value, int width)
{
    ostringstream oss;
    oss << hex << setfill('0') << setw(width) << value;
    return oss.str();
}

// TODO: Go back thru and check that the file can evenly be / by struct size at runtime

vector<Entities> readEntities(string filename)
{
    vector<Entities> data;
    Entities temp;
    ifstream file(filename);

    if (!file)
    {
        std::cerr << "Error opening file: " << filename << std::endl;
        return {};
    }
    else
    {
        cout << "Reading entities from: " << filename << endl;
    }

    string line;
    bool in_entity = false;

    regex kv_regex(R"(\"([^\"]*)\"\s+\"([^\"]*)\")");

    while (getline(file, line))
    {
        if (line.find("{") != string::npos)
        {
            in_entity = true;
            temp.keyvalues.clear();
            temp.values.clear();
        }
        else if (line.find("}") != string::npos)
        {
            in_entity = false;
            data.push_back(temp);
        }
        else if (in_entity)
        {
            smatch matches;
            while (regex_search(line, matches, kv_regex))
            {
                temp.keyvalues.push_back(matches[1].str());
                temp.values.push_back(matches[2].str());
                line = matches.suffix().str();
            }
        }
    }

    return data;
}

vector<Planes> readPlanes(string filename)
{
    vector<Planes> data;
    Planes temp;

    filename = filename + "." + intToHexString(static_cast<int>(lumps::PLANES), 4) + ".bsp_lump";
    ifstream file(filename, ios::binary);

    if (!file)
    {
        std::cerr << "Error opening file: " << filename << std::endl;
        return {};
    }
    else
    {
        cout << "Reading planes from: " << filename << endl;
    }

    while (file.read(reinterpret_cast<char *>(&temp), sizeof(Planes)))
    {
        data.push_back(temp);
    }

    return data;
}

vector<Texture_Data> readTextureData(string filename)
{
    vector<Texture_Data> data;
    Texture_Data temp;
    filename = filename + "." + intToHexString(static_cast<int>(lumps::TEXTURE_DATA), 4) + ".bsp_lump";
    ifstream file(filename, ios::binary);

    if (!file)
    {
        std::cerr << "Error opening file: " << filename << std::endl;
        return {};
    }
    else
    {
        cout << "Reading texture data from: " << filename << endl;
    }

    while (file.read(reinterpret_cast<char *>(&temp), sizeof(Texture_Data)))
    {
        data.push_back(temp);
    }

    return data;
}

vector<Vertices> readVertices(string filename)
{
    vector<Vertices> data;
    Vertices temp;
    filename = filename + "." + intToHexString(static_cast<int>(lumps::VERTICES), 4) + ".bsp_lump";
    ifstream file(filename, ios::binary);

    if (!file)
    {
        std::cerr << "Error opening file: " << filename << std::endl;
        return {};
    }
    else
    {
        cout << "Reading vertices from: " << filename << endl;
    }

    while (file.read(reinterpret_cast<char *>(&temp), sizeof(Vertices)))
    {
        data.push_back(temp);
    }

    return data;
}

vector<Lightprobe_Parent_Infos> readLightprobe_Parent_Infos(string filename)
{
    vector<Lightprobe_Parent_Infos> data;
    Lightprobe_Parent_Infos temp;

    filename = filename + "." + intToHexString(static_cast<int>(lumps::LIGHTPROBE_PARENT_INFOS), 4) + ".bsp_lump";
    ifstream file(filename, ios::binary);

    if (!file)
    {
        std::cerr << "Error opening file: " << filename << std::endl;
        return {};
    }
    else
    {
        cout << "Reading lightprobe parent infos from: " << filename << endl;
    }

    while (file.read(reinterpret_cast<char *>(&temp), sizeof(Lightprobe_Parent_Infos)))
    {
        data.push_back(temp);
    }

    return data;
}

vector<Shadow_Environments> readShadow_Environments(string filename)
{
    vector<Shadow_Environments> data;
    Shadow_Environments temp;

    filename = filename + "." + intToHexString(static_cast<int>(lumps::SHADOW_ENVIRONMENTS), 4) + ".bsp_lump";
    ifstream file(filename, ios::binary);

    if (!file)
    {
        std::cerr << "Error opening file: " << filename << std::endl;
        return {};
    }
    else
    {
        cout << "Reading shadow environments from: " << filename << endl;
    }

    while (file.read(reinterpret_cast<char *>(&temp), sizeof(Shadow_Environments)))
    {
        data.push_back(temp);
    }

    return data;
}

vector<Lightprobe_BSP_Nodes> readLightprobe_BSP_Nodes(string filename)
{
    vector<Lightprobe_BSP_Nodes> data;
    Lightprobe_BSP_Nodes temp;

    filename = filename + "." + intToHexString(static_cast<int>(lumps::LIGHTPROBE_BSP_NODES), 4) + ".bsp_lump";
    ifstream file(filename, ios::binary);

    if (!file)
    {
        std::cerr << "Error opening file: " << filename << std::endl;
        return {};
    }
    else
    {
        cout << "Reading lightprobe BSP nodes from: " << filename << endl;
    }

    while (file.read(reinterpret_cast<char *>(&temp), sizeof(Lightprobe_BSP_Nodes)))
    {
        data.push_back(temp);
    }
    return data;
}

vector<Lightprobe_BSP_REF_IDS> readLightprobe_BSP_REF_IDS(string filename)
{
    vector<Lightprobe_BSP_REF_IDS> data;
    Lightprobe_BSP_REF_IDS temp;
    filename = filename + "." + intToHexString(static_cast<int>(lumps::LIGHTPROBE_BSP_REF_IDS), 4) + ".bsp_lump";
    ifstream file(filename, ios::binary);

    if (!file)
    {
        std::cerr << "Error opening file: " << filename << std::endl;
        return {};
    }
    else
    {
        cout << "Reading lightprobe BSP ref IDs from: " << filename << endl;
    }

    while (file.read(reinterpret_cast<char *>(&temp), sizeof(Lightprobe_BSP_REF_IDS)))
    {
        data.push_back(temp);
    }

    return data;
}

vector<Models> readModels(string filename)
{
    vector<Models> data;
    Models temp;
    filename = filename + "." + intToHexString(static_cast<int>(lumps::MODELS), 4) + ".bsp_lump";
    ifstream file(filename, ios::binary);

    if (!file)
    {
        std::cerr << "Error opening file: " << filename << std::endl;
        return {};
    }
    else
    {
        cout << "Reading models from: " << filename << endl;
    }

    while (file.read(reinterpret_cast<char *>(&temp), sizeof(Models)))
    {
        data.push_back(temp);
    }

    return data;
}

vector<Entity_Partitions> readEntityPartitions(string filename)
{
    vector<Entity_Partitions> data;
    Entity_Partitions temp;

    filename = filename + "." + intToHexString(static_cast<int>(lumps::ENTITY_PARTITIONS), 4) + ".bsp_lump";
    ifstream file(filename);

    if (!file)
    {
        std::cerr << "Error opening file: " << filename << std::endl;
        return {};
    }
    else
    {
        cout << "Reading entity partitions from: " << filename << endl;
    }

    string line;
    string word;
    int i=0;
    while (getline(file, line))
    {
        std::stringstream ss(line);
        while (ss >> word)
        {
            temp.partitions.push_back(word);
            i++;
        }
        data.push_back(temp);
    }

    return data;
}

vector<Physics_Collide> readPhysicsCollide(string filename)
{
    vector<Physics_Collide> data;
    Physics_Collide temp;
    filename = filename + "." + intToHexString(static_cast<int>(lumps::PHYSICS_COLLIDE), 4) + ".bsp_lump";
    ifstream file(filename, ios::binary);

    if (!file)
    {
        std::cerr << "Error opening file: " << filename << std::endl;
        return {};
    }
    else
    {
        cout << "Reading physics collide from: " << filename << endl;
    }

    while (file.read(reinterpret_cast<char *>(&temp), sizeof(Physics_Collide)))
    {
        data.push_back(temp);
    }

    return data;
}

vector<Vertex_Normals> readVertexNormals(string filename)
{
    vector<Vertex_Normals> data;
    Vertex_Normals temp;
    filename = filename + "." + intToHexString(static_cast<int>(lumps::VERTEX_NORMALS), 4) + ".bsp_lump";
    ifstream file(filename, ios::binary);

    if (!file)
    {
        std::cerr << "Error opening file: " << filename << std::endl;
        return {};
    }
    else
    {
        cout << "Reading vertex normals from: " << filename << endl;
    }

    while (file.read(reinterpret_cast<char *>(&temp), sizeof(Vertex_Normals)))
    {
        data.push_back(temp);
    }

    return data;
}

vector<Game_Lump> readGameLumps(string filename)
{
    vector<Game_Lump> data;
    Game_Lump temp;
    filename = filename + "." + intToHexString(static_cast<int>(lumps::GAME_LUMP), 4) + ".bsp_lump";
    ifstream file(filename, ios::binary);

    if (!file)
    {
        std::cerr << "Error opening file: " << filename << std::endl;
        return {};
    }
    else
    {
        cout << "Reading game lumps from: " << filename << endl;
    }

    while (file.read(reinterpret_cast<char *>(&temp), sizeof(Game_Lump)))
    {
        data.push_back(temp);
    }

    return data;
}

vector<Leaf_Water_Data> readLeafWaterData(string filename)
{
    vector<Leaf_Water_Data> data;
    Leaf_Water_Data temp;
    filename = filename + "." + intToHexString(static_cast<int>(lumps::LEAF_WATER_DATA), 4) + ".bsp_lump";
    ifstream file(filename, ios::binary);

    if (!file)
    {
        std::cerr << "Error opening file: " << filename << std::endl;
        return {};
    }
    else
    {
        cout << "Reading Leaf Water Data from: " << filename << endl;
    }

    while (file.read(reinterpret_cast<char *>(&temp), sizeof(Leaf_Water_Data)))
    {
        data.push_back(temp);
    }

    return data;
}

vector<PAKFile> readpakFile(string filename)
{
    vector<PAKFile> data;
    PAKFile temp;
    filename = filename + "." + intToHexString(static_cast<int>(lumps::PAKFILE), 4) + ".bsp_lump";
    ifstream file(filename, ios::binary);

    if (!file)
    {
        std::cerr << "Error opening file: " << filename << std::endl;
        return {};
    }
    else
    {
        cout << "Reading Pakfile from: " << filename << endl;
    }

    while (file.read(reinterpret_cast<char *>(&temp), sizeof(PAKFile)))
    {
        data.push_back(temp);
    }

    return data;
}

vector<Cubemap> readcubemap(string filename)
{
    vector<Cubemap> data;
    Cubemap temp;
    filename = filename + "." + intToHexString(static_cast<int>(lumps::CUBEMAP), 4) + ".bsp_lump";
    ifstream file(filename, ios::binary);

    if (!file)
    {
        std::cerr << "Error opening file: " << filename << std::endl;
        return {};
    }
    else
    {
        cout << "Reading Cubemap from: " << filename << endl;
    }

    while (file.read(reinterpret_cast<char *>(&temp), sizeof(Cubemap)))
    {
        data.push_back(temp);
    }

    return data;
}

vector<Texture_Data_String_Data> readTextureDataStringData(string filename)
{
    vector<Texture_Data_String_Data> data;
    Texture_Data_String_Data temp;
    filename = filename + "." + intToHexString(static_cast<int>(lumps::TEXTURE_DATA_STRING_DATA), 4) + ".bsp_lump";
    ifstream file(filename, ios::binary);

    if (!file)
    {
        std::cerr << "Error opening file: " << filename << std::endl;
        return {};
    }
    else
    {
        cout << "Reading Texture data string data from: " << filename << endl;
    }

    string line;
    string word;
    int i=0;
    while (getline(file, line, '\0'))
    {
        std::stringstream ss(line);
        while (ss >> word)
        {
            temp.strings.push_back(word);
            i++;
        }
        data.push_back(temp);
    }

    for (int i =0; i < temp.strings.size(); i++) {
        cout << temp.strings[i] << endl;
    }

    return data;
}

vector<Texture_Data_String_Table> readTextureDataStringTable(string filename)
{
    vector<Texture_Data_String_Table> data;
    Texture_Data_String_Table temp;
    filename = filename + "." + intToHexString(static_cast<int>(lumps::TEXTURE_DATA_STRING_TABLE), 4) + ".bsp_lump";
    ifstream file(filename, ios::binary);

    if (!file)
    {
        std::cerr << "Error opening file: " << filename << std::endl;
        return {};
    }
    else
    {
        cout << "Reading texture data string table from: " << filename << endl;
    }

    while (file.read(reinterpret_cast<char *>(&temp), sizeof(Texture_Data_String_Table)))
    {
        data.push_back(temp);
    }

    return data;
}

vector<WORLD_LIGHTSv3> readWorldLights(string filename)
{
    vector<WORLD_LIGHTSv3> data;
    WORLD_LIGHTSv3 temp;
    filename = filename + "." + intToHexString(static_cast<int>(lumps::WORLD_LIGHTS), 4) + ".bsp_lump";
    ifstream file(filename, ios::binary);

    if (!file)
    {
        std::cerr << "Error opening file: " << filename << std::endl;
        return {};
    }
    else
    {
        cout << "Reading world lights from: " << filename << endl;
    }

    while (file.read(reinterpret_cast<char *>(&temp), sizeof(WORLD_LIGHTSv3)))
    {
        data.push_back(temp);
    }

    return data;
}

vector<World_Light_Parent_Infos> readWorldLightParentInfo(string filename)
{
    vector<World_Light_Parent_Infos> data;
    World_Light_Parent_Infos temp;
    filename = filename + "." + intToHexString(static_cast<int>(lumps::WORLD_LIGHT_PARENT_INFOS), 4) + ".bsp_lump";
    ifstream file(filename, ios::binary);

    if (!file)
    {
        std::cerr << "Error opening file: " << filename << std::endl;
        return {};
    }
    else
    {
        cout << "Reading world light parent info from: " << filename << endl;
    }

    while (file.read(reinterpret_cast<char *>(&temp), sizeof(World_Light_Parent_Infos)))
    {
        data.push_back(temp);
    }

    return data;
}

vector<Tricoll_Triangles> readtricollTriangles(string filename)
{
    vector<Tricoll_Triangles> data;
    Tricoll_Triangles temp;
    filename = filename + "." + intToHexString(static_cast<int>(lumps::TRICOLL_TRIANGLES), 4) + ".bsp_lump";
    ifstream file(filename, ios::binary);

    if (!file)
    {
        std::cerr << "Error opening file: " << filename << std::endl;
        return {};
    }
    else
    {
        cout << "Reading Tricoll triangles from: " << filename << endl;
    }

    while (file.read(reinterpret_cast<char *>(&temp), sizeof(Tricoll_Triangles)))
    {
        data.push_back(temp);
    }

    return data;
}

vector<Tricoll_Nodes> readtricollNodes(string filename)
{
    vector<Tricoll_Nodes> data;
    Tricoll_Nodes temp;
    filename = filename + "." + intToHexString(static_cast<int>(lumps::TRICOLL_NODES), 4) + ".bsp_lump";
    ifstream file(filename, ios::binary);

    if (!file)
    {
        std::cerr << "Error opening file: " << filename << std::endl;
        return {};
    }
    else
    {
        cout << "Reading tricoll nodes from: " << filename << endl;
    }

    while (file.read(reinterpret_cast<char *>(&temp), sizeof(Tricoll_Nodes)))
    {
        data.push_back(temp);
    }

    return data;
}

vector<Tricoll_Headers> readtricollHeaders(string filename)
{
    vector<Tricoll_Headers> data;
    Tricoll_Headers temp;
    filename = filename + "." + intToHexString(static_cast<int>(lumps::TRICOLL_HEADERS), 4) + ".bsp_lump";
    ifstream file(filename, ios::binary);

    if (!file)
    {
        std::cerr << "Error opening file: " << filename << std::endl;
        return {};
    }
    else
    {
        cout << "Reading tricoll headers from: " << filename << endl;
    }

    while (file.read(reinterpret_cast<char *>(&temp), sizeof(Tricoll_Headers)))
    {
        data.push_back(temp);
    }

    return data;
}

vector<Vertex_Unlit> readVertexUnlit(string filename)
{
    vector<Vertex_Unlit> data;
    Vertex_Unlit temp;
    filename = filename + "." + intToHexString(static_cast<int>(lumps::VERTEX_UNLIT), 4) + ".bsp_lump";
    ifstream file(filename, ios::binary);

    if (!file)
    {
        std::cerr << "Error opening file: " << filename << std::endl;
        return {};
    }
    else
    {
        cout << "Reading vertex unlit from: " << filename << endl;
    }

    while (file.read(reinterpret_cast<char *>(&temp), sizeof(Vertex_Unlit)))
    {
        data.push_back(temp);
    }

    return data;
}

vector<Vertex_Lit_Flat> readVertexLitFlat(string filename)
{
    vector<Vertex_Lit_Flat> data;
    Vertex_Lit_Flat temp;
    filename = filename + "." + intToHexString(static_cast<int>(lumps::VERTEX_LIT_FLAT), 4) + ".bsp_lump";
    ifstream file(filename, ios::binary);

    if (!file)
    {
        std::cerr << "Error opening file: " << filename << std::endl;
        return {};
    }
    else
    {
        cout << "Reading vertex lit flat from: " << filename << endl;
    }

    while (file.read(reinterpret_cast<char *>(&temp), sizeof(Vertex_Lit_Flat)))
    {
        data.push_back(temp);
    }

    return data;
}

vector<Vertex_Lit_Bump> readVertexLitBump(string filename)
{
    vector<Vertex_Lit_Bump> data;
    Vertex_Lit_Bump temp;
    filename = filename + "." + intToHexString(static_cast<int>(lumps::VERTEX_LIT_BUMP), 4) + ".bsp_lump";
    ifstream file(filename, ios::binary);

    if (!file)
    {
        std::cerr << "Error opening file: " << filename << std::endl;
        return {};
    }
    else
    {
        cout << "Reading vertex lit bump from: " << filename << endl;
    }

    while (file.read(reinterpret_cast<char *>(&temp), sizeof(Vertex_Lit_Bump)))
    {
        data.push_back(temp);
    }

    return data;
}

int main(int argc, char *argv[])
{
    string filename;
    if (argc == 2)
    {
        filename = argv[1];
    }
    else
    {
        cout << "Please provide a filename as an argument." << endl;
        return 1;
    }
    string basefilename = filename.substr(0, filename.find_last_of("."));

    vector<Entities> entities = readEntities(filename + "." + intToHexString(static_cast<int>(lumps::ENTITIES), 4) + ".bsp_lump");
    vector<Entities> entitiesEnv = readEntities(basefilename + "_env" + ".ent");
    vector<Entities> entitiesFx = readEntities(basefilename + "_fx" + ".ent");
    vector<Entities> entitiesScript = readEntities(basefilename + "_script" + ".ent");
    vector<Entities> entitiesSnd = readEntities(basefilename + "_snd" + ".ent");
    vector<Planes> planes = readPlanes(filename);
    vector<Texture_Data> texture_data = readTextureData(filename);
    vector<Vertices> vertices = readVertices(filename);
    vector<Lightprobe_Parent_Infos> lightprobe_parent_infos = readLightprobe_Parent_Infos(filename);
    vector<Shadow_Environments> shadow_environments = readShadow_Environments(filename);
    vector<Lightprobe_BSP_Nodes> lightprobe_bsp_nodes = readLightprobe_BSP_Nodes(filename);
    vector<Lightprobe_BSP_REF_IDS> lightprobe_bsp_ref_ids = readLightprobe_BSP_REF_IDS(filename);
    vector<Models> models = readModels(filename);
    vector<Entity_Partitions> entity_partitions = readEntityPartitions(filename);
    vector<Physics_Collide> physics_collide = readPhysicsCollide(filename);
    vector<Vertex_Normals> vertex_normals = readVertexNormals(filename);
    vector<Game_Lump> game_lumps = readGameLumps(filename);
    vector<Leaf_Water_Data> LeafWaterData = readLeafWaterData(filename);
    vector<PAKFile> pakFile = readpakFile(filename);
    vector<Cubemap> cubemap = readcubemap(filename);
    vector<Texture_Data_String_Data> TextureDataStringData = readTextureDataStringData(filename);
    vector<Texture_Data_String_Table> TextureDataStringTable = readTextureDataStringTable(filename);
    vector<WORLD_LIGHTSv3> WorldLights = readWorldLights(filename);
    vector<World_Light_Parent_Infos> WorldLightParentInfo = readWorldLightParentInfo(filename);
    vector<Tricoll_Triangles> tricollTriangles = readtricollTriangles(filename);
    vector<Tricoll_Nodes> tricollNodes = readtricollNodes(filename);
    vector<Tricoll_Headers> tricollHeaders = readtricollHeaders(filename);
    vector<Vertex_Unlit> VertexUnlit = readVertexUnlit(filename);
    vector<Vertex_Lit_Flat> VertexLitFlat = readVertexLitFlat(filename);
    vector<Vertex_Lit_Bump> VertexLitBump = readVertexLitBump(filename);

    cout << "Read " << VertexLitBump.size() + VertexLitFlat.size() + VertexUnlit.size() + tricollHeaders.size() + tricollNodes.size() + tricollTriangles.size() + WorldLightParentInfo.size() + WorldLights.size() + TextureDataStringTable.size() + TextureDataStringData.size() + cubemap.size() + pakFile.size() + LeafWaterData.size() + planes.size() + texture_data.size() + vertices.size() + entitiesEnv.size() + entitiesFx.size() + entitiesScript.size() + entitiesSnd.size() + models.size() + entity_partitions.size() + physics_collide.size() + vertex_normals.size() + game_lumps.size() << " structs." << endl;
    return 0;
}