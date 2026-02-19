#include <iostream>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <list>
#include <cstdint>
#include <vector>
#include <filesystem>
#include "structs.h"

using namespace std;

#ifndef HELPER_FUNCTIONS_H
#define HELPER_FUNCTIONS_H

string intToHexString(int value, int width)
{
    ostringstream oss;
    oss << hex << setfill('0') << setw(width) << value;
    return oss.str();
}

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

    if (!file || std::filesystem::file_size(filename) % sizeof(Planes)  != 0)
    {
        cout << std::filesystem::file_size(filename) << " " << sizeof(Planes) << endl;
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

    if (!file || std::filesystem::file_size(filename) % sizeof(Texture_Data)  != 0)
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

    if (!file || std::filesystem::file_size(filename) % sizeof(Vertices)  != 0)
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

    if (!file || std::filesystem::file_size(filename) % sizeof(Lightprobe_Parent_Infos)  != 0)
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

    if (!file || std::filesystem::file_size(filename) % sizeof(Shadow_Environments)  != 0)
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

    if (!file || std::filesystem::file_size(filename) % sizeof(Lightprobe_BSP_Nodes)  != 0)
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

    if (!file || std::filesystem::file_size(filename) % sizeof(Lightprobe_BSP_REF_IDS)  != 0)
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

    if (!file || std::filesystem::file_size(filename) % sizeof(Models)  != 0)
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
    int i = 0;
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

    if (!file || std::filesystem::file_size(filename) % sizeof(Physics_Collide)  != 0)
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

    if (!file || std::filesystem::file_size(filename) % sizeof(Vertex_Normals)  != 0)
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

    if (!file || std::filesystem::file_size(filename) % sizeof(Game_Lump)  != 0)
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

    if (!file || std::filesystem::file_size(filename) % sizeof(Leaf_Water_Data)  != 0)
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

    if (!file || std::filesystem::file_size(filename) % sizeof(PAKFile)  != 0)
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

    if (!file || std::filesystem::file_size(filename) % sizeof(Cubemap)  != 0)
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
    int i = 0;
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

    return data;
}

vector<Texture_Data_String_Table> readTextureDataStringTable(string filename)
{
    vector<Texture_Data_String_Table> data;
    Texture_Data_String_Table temp;
    filename = filename + "." + intToHexString(static_cast<int>(lumps::TEXTURE_DATA_STRING_TABLE), 4) + ".bsp_lump";
    ifstream file(filename, ios::binary);

    if (!file || std::filesystem::file_size(filename) % sizeof(Texture_Data_String_Table)  != 0)
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

    if (!file || std::filesystem::file_size(filename) % sizeof(WORLD_LIGHTSv3)  != 0)
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

    if (!file || std::filesystem::file_size(filename) % sizeof(World_Light_Parent_Infos)  != 0)
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

    if (!file || std::filesystem::file_size(filename) % sizeof(Tricoll_Triangles)  != 0)
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

    if (!file || std::filesystem::file_size(filename) % sizeof(Tricoll_Nodes)  != 0)
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

    if (!file || std::filesystem::file_size(filename) % sizeof(Tricoll_Headers)  != 0)
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

    if (!file || std::filesystem::file_size(filename) % sizeof(Vertex_Unlit)  != 0)
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

    if (!file || std::filesystem::file_size(filename) % sizeof(Vertex_Lit_Flat)  != 0)
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

    if (!file || std::filesystem::file_size(filename) % sizeof(Vertex_Lit_Bump)  != 0)
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

vector<Vertex_unlit_TS> readVertexUnlitTS(string filename)
{
    vector<Vertex_unlit_TS> data;
    Vertex_unlit_TS temp;
    filename = filename + "." + intToHexString(static_cast<int>(lumps::VERTEX_UNLIT_TS), 4) + ".bsp_lump";
    ifstream file(filename, ios::binary);

    if (!file || std::filesystem::file_size(filename) % sizeof(Vertex_unlit_TS)  != 0)
    {
        std::cerr << "Error opening file: " << filename << std::endl;
        return {};
    }
    else
    {
        cout << "Reading Vertex_unlit_TS from: " << filename << endl;
    }

    while (file.read(reinterpret_cast<char *>(&temp), sizeof(Vertex_unlit_TS)))
    {
        data.push_back(temp);
    }

    return data;
}

vector<Vertex_Blinn_Phong> readVertexBlinnPhong(string filename)
{
    vector<Vertex_Blinn_Phong> data;
    Vertex_Blinn_Phong temp;
    filename = filename + "." + intToHexString(static_cast<int>(lumps::VERTEX_BLINN_PHONG), 4) + ".bsp_lump";
    ifstream file(filename, ios::binary);

    if (!file || std::filesystem::file_size(filename) % sizeof(Vertex_Blinn_Phong)  != 0)
    {
        std::cerr << "Error opening file: " << filename << std::endl;
        return {};
    }
    else
    {
        cout << "Reading Vertex_Blinn_Phong from: " << filename << endl;
    }

    while (file.read(reinterpret_cast<char *>(&temp), sizeof(Vertex_Blinn_Phong)))
    {
        data.push_back(temp);
    }

    return data;
}

vector<Mesh_Indices> readMeshIndices(string filename)
{
    vector<Mesh_Indices> data;
    Mesh_Indices temp;
    filename = filename + "." + intToHexString(static_cast<int>(lumps::MESH_INDICES), 4) + ".bsp_lump";
    ifstream file(filename, ios::binary);

    if (!file || std::filesystem::file_size(filename) % sizeof(Mesh_Indices)  != 0)
    {
        std::cerr << "Error opening file: " << filename << std::endl;
        return {};
    }
    else
    {
        cout << "Reading Mesh_Indices from: " << filename << endl;
    }

    while (file.read(reinterpret_cast<char *>(&temp), sizeof(Mesh_Indices)))
    {
        data.push_back(temp);
    }

    return data;
}

vector<Mesh> readMeshes(string filename)
{
    vector<Mesh> data;
    Mesh temp;
    filename = filename + "." + intToHexString(static_cast<int>(lumps::MESHES), 4) + ".bsp_lump";
    ifstream file(filename, ios::binary);

    if (!file || std::filesystem::file_size(filename) % sizeof(Mesh)  != 0)
    {
        std::cerr << "Error opening file: " << filename << std::endl;
        return {};
    }
    else
    {
        cout << "Reading Mesh from: " << filename << endl;
    }

    while (file.read(reinterpret_cast<char *>(&temp), sizeof(Mesh)))
    {
        data.push_back(temp);
    }

    return data;
}

vector<Mesh_Bounds> readMeshBounds(string filename)
{
    vector<Mesh_Bounds> data;
    Mesh_Bounds temp;
    filename = filename + "." + intToHexString(static_cast<int>(lumps::MESH_BOUNDS), 4) + ".bsp_lump";
    ifstream file(filename, ios::binary);

    if (!file || std::filesystem::file_size(filename) % sizeof(Mesh_Bounds)  != 0)
    {
        std::cerr << "Error opening file: " << filename << std::endl;
        return {};
    }
    else
    {
        cout << "Reading Mesh_Bounds from: " << filename << endl;
    }

    while (file.read(reinterpret_cast<char *>(&temp), sizeof(Mesh_Bounds)))
    {
        data.push_back(temp);
    }

    return data;
}

vector<Material_Sorts> readMaterialSorts(string filename)
{
    vector<Material_Sorts> data;
    Material_Sorts temp;
    filename = filename + "." + intToHexString(static_cast<int>(lumps::MATERIAL_SORTS), 4) + ".bsp_lump";
    ifstream file(filename, ios::binary);

    if (!file || std::filesystem::file_size(filename) % sizeof(Material_Sorts)  != 0)
    {
        std::cerr << "Error opening file: " << filename << std::endl;
        return {};
    }
    else
    {
        cout << "Reading Material_Sorts from: " << filename << endl;
    }

    while (file.read(reinterpret_cast<char *>(&temp), sizeof(Material_Sorts)))
    {
        data.push_back(temp);
    }

    return data;
}

vector<Lightmap_Headers> readLightmapHeaders(string filename)
{
    vector<Lightmap_Headers> data;
    Lightmap_Headers temp;
    filename = filename + "." + intToHexString(static_cast<int>(lumps::LIGHTMAP_HEADERS), 4) + ".bsp_lump";
    ifstream file(filename, ios::binary);

    if (!file || std::filesystem::file_size(filename) % sizeof(Lightmap_Headers)  != 0)
    {
        std::cerr << "Error opening file: " << filename << std::endl;
        return {};
    }
    else
    {
        cout << "Reading Lightmap_Headers from: " << filename << endl;
    }

    while (file.read(reinterpret_cast<char *>(&temp), sizeof(Lightmap_Headers)))
    {
        data.push_back(temp);
    }

    return data;
}

vector<cm_Grid> readCMGrid(string filename)
{
    vector<cm_Grid> data;
    cm_Grid temp;
    filename = filename + "." + intToHexString(static_cast<int>(lumps::CM_GRID), 4) + ".bsp_lump";
    ifstream file(filename, ios::binary);

    if (!file || std::filesystem::file_size(filename) % sizeof(cm_Grid)  != 0)
    {
        std::cerr << "Error opening file: " << filename << std::endl;
        return {};
    }
    else
    {
        cout << "Reading cm_Grid from: " << filename << endl;
    }

    while (file.read(reinterpret_cast<char *>(&temp), sizeof(cm_Grid)))
    {
        data.push_back(temp);
    }

    return data;
}

vector<cm_Grid_Cells> readCMGridCells(string filename)
{
    vector<cm_Grid_Cells> data;
    cm_Grid_Cells temp;
    filename = filename + "." + intToHexString(static_cast<int>(lumps::CM_GRID_CELLS), 4) + ".bsp_lump";
    ifstream file(filename, ios::binary);

    if (!file || std::filesystem::file_size(filename) % sizeof(cm_Grid_Cells)  != 0)
    {
        std::cerr << "Error opening file: " << filename << std::endl;
        return {};
    }
    else
    {
        cout << "Reading cm_Grid_Cells from: " << filename << endl;
    }

    while (file.read(reinterpret_cast<char *>(&temp), sizeof(cm_Grid_Cells)))
    {
        data.push_back(temp);
    }

    return data;
}

vector<cm_Geo_Sets> readCMGeoSets(string filename)
{
    vector<cm_Geo_Sets> data;
    cm_Geo_Sets temp;
    filename = filename + "." + intToHexString(static_cast<int>(lumps::CM_GEO_SETS), 4) + ".bsp_lump";
    ifstream file(filename, ios::binary);

    if (!file || std::filesystem::file_size(filename) % sizeof(cm_Geo_Sets)  != 0)
    {
        std::cerr << "Error opening file: " << filename << std::endl;
        return {};
    }
    else
    {
        cout << "Reading cm_Geo_Sets from: " << filename << endl;
    }

    while (file.read(reinterpret_cast<char *>(&temp), sizeof(cm_Geo_Sets)))
    {
        data.push_back(temp);
    }

    return data;
}

vector<cm_Geo_Set_Bounds> readCMGeoSetBounds(string filename)
{
    vector<cm_Geo_Set_Bounds> data;
    cm_Geo_Set_Bounds temp;
    filename = filename + "." + intToHexString(static_cast<int>(lumps::CM_GEO_SET_BOUNDS), 4) + ".bsp_lump";
    ifstream file(filename, ios::binary);

    if (!file || std::filesystem::file_size(filename) % sizeof(cm_Geo_Set_Bounds)  != 0)
    {
        std::cerr << "Error opening file: " << filename << std::endl;
        return {};
    }
    else
    {
        cout << "Reading cm_Geo_Set_Bounds from: " << filename << endl;
    }

    while (file.read(reinterpret_cast<char *>(&temp), sizeof(cm_Geo_Set_Bounds)))
    {
        data.push_back(temp);
    }

    return data;
}

vector<cm_Primitives> readCMPrimitives(string filename)
{
    vector<cm_Primitives> data;
    cm_Primitives temp;
    filename = filename + "." + intToHexString(static_cast<int>(lumps::CM_PRIMITIVES), 4) + ".bsp_lump";
    ifstream file(filename, ios::binary);

    if (!file || std::filesystem::file_size(filename) % sizeof(cm_Primitives)  != 0)
    {
        std::cerr << "Error opening file: " << filename << std::endl;
        return {};
    }
    else
    {
        cout << "Reading cm_Primitives from: " << filename << endl;
    }

    while (file.read(reinterpret_cast<char *>(&temp), sizeof(cm_Primitives)))
    {
        data.push_back(temp);
    }

    return data;
}

vector<cm_Primitive_Bounds> readCMPrimitiveBounds(string filename)
{
    vector<cm_Primitive_Bounds> data;
    cm_Primitive_Bounds temp;
    filename = filename + "." + intToHexString(static_cast<int>(lumps::CM_PRIMITIVE_BOUNDS), 4) + ".bsp_lump";
    ifstream file(filename, ios::binary);

    if (!file || std::filesystem::file_size(filename) % sizeof(cm_Primitive_Bounds)  != 0)
    {
        std::cerr << "Error opening file: " << filename << std::endl;
        return {};
    }
    else
    {
        cout << "Reading cm_Primitive_Bounds from: " << filename << endl;
    }

    while (file.read(reinterpret_cast<char *>(&temp), sizeof(cm_Primitive_Bounds)))
    {
        data.push_back(temp);
    }

    return data;
}

vector<cm_Unique_Contents> readCMUniqueContents(string filename)
{
    vector<cm_Unique_Contents> data;
    cm_Unique_Contents temp;
    filename = filename + "." + intToHexString(static_cast<int>(lumps::CM_UNIQUE_CONTENTS), 4) + ".bsp_lump";
    ifstream file(filename, ios::binary);

    if (!file || std::filesystem::file_size(filename) % sizeof(cm_Unique_Contents)  != 0)
    {
        std::cerr << "Error opening file: " << filename << std::endl;
        return {};
    }
    else
    {
        cout << "Reading cm_Unique_Contents from: " << filename << endl;
    }

    while (file.read(reinterpret_cast<char *>(&temp), sizeof(cm_Unique_Contents)))
    {
        data.push_back(temp);
    }

    return data;
}

vector<cm_Brushes> readCMBrushes(string filename)
{
    vector<cm_Brushes> data;
    cm_Brushes temp;
    filename = filename + "." + intToHexString(static_cast<int>(lumps::CM_BRUSHES), 4) + ".bsp_lump";
    ifstream file(filename, ios::binary);

    if (!file || std::filesystem::file_size(filename) % sizeof(cm_Brushes)  != 0)
    {
        std::cerr << "Error opening file: " << filename << std::endl;
        return {};
    }
    else
    {
        cout << "Reading cm_Brushes from: " << filename << endl;
    }

    while (file.read(reinterpret_cast<char *>(&temp), sizeof(cm_Brushes)))
    {
        data.push_back(temp);
    }

    return data;
}

vector<cm_Brush_Side_Plane_Offsets> readCMBrushSidePlaneOffsets(string filename)
{
    vector<cm_Brush_Side_Plane_Offsets> data;
    cm_Brush_Side_Plane_Offsets temp;
    filename = filename + "." + intToHexString(static_cast<int>(lumps::CM_BRUSH_SIDE_PLANE_OFFSETS), 4) + ".bsp_lump";
    ifstream file(filename, ios::binary);

    if (!file || std::filesystem::file_size(filename) % sizeof(cm_Brush_Side_Plane_Offsets)  != 0)
    {
        std::cerr << "Error opening file: " << filename << std::endl;
        return {};
    }
    else
    {
        cout << "Reading cm_Brush_Side_Plane_Offsets from: " << filename << endl;
    }

    while (file.read(reinterpret_cast<char *>(&temp), sizeof(cm_Brush_Side_Plane_Offsets)))
    {
        data.push_back(temp);
    }

    return data;
}

vector<cm_Brush_Side_Properties> readCMBrushSideProperties(string filename)
{
    vector<cm_Brush_Side_Properties> data;
    cm_Brush_Side_Properties temp;
    filename = filename + "." + intToHexString(static_cast<int>(lumps::CM_BRUSH_SIDE_PROPERTIES), 4) + ".bsp_lump";
    ifstream file(filename, ios::binary);

    if (!file || std::filesystem::file_size(filename) % sizeof(cm_Brush_Side_Properties)  != 0)
    {
        std::cerr << "Error opening file: " << filename << std::endl;
        return {};
    }
    else
    {
        cout << "Reading cm_Brush_Side_Properties from: " << filename << endl;
    }

    while (file.read(reinterpret_cast<char *>(&temp), sizeof(cm_Brush_Side_Properties)))
    {
        data.push_back(temp);
    }

    return data;
}

vector<cm_Brush_Side_Texture_Vectors> readCMBrushSideTextureVectors(string filename)
{
    vector<cm_Brush_Side_Texture_Vectors> data;
    cm_Brush_Side_Texture_Vectors temp;
    filename = filename + "." + intToHexString(static_cast<int>(lumps::CM_BRUSH_SIDE_TEXTURE_VECTORS), 4) + ".bsp_lump";
    ifstream file(filename, ios::binary);

    if (!file || std::filesystem::file_size(filename) % sizeof(cm_Brush_Side_Texture_Vectors)  != 0)
    {
        std::cerr << "Error opening file: " << filename << std::endl;
        return {};
    }
    else
    {
        cout << "Reading cm_Brush_Side_Texture_Vectors from: " << filename << endl;
    }

    while (file.read(reinterpret_cast<char *>(&temp), sizeof(cm_Brush_Side_Texture_Vectors)))
    {
        data.push_back(temp);
    }

    return data;
}

vector<Tricoll_Bevel_Starts> readTricollBevelStarts(string filename)
{
    vector<Tricoll_Bevel_Starts> data;
    Tricoll_Bevel_Starts temp;
    filename = filename + "." + intToHexString(static_cast<int>(lumps::TRICOLL_BEVEL_STARTS), 4) + ".bsp_lump";
    ifstream file(filename, ios::binary);

    if (!file || std::filesystem::file_size(filename) % sizeof(Tricoll_Bevel_Starts)  != 0)
    {
        std::cerr << "Error opening file: " << filename << std::endl;
        return {};
    }
    else
    {
        cout << "Reading Tricoll_Bevel_Starts from: " << filename << endl;
    }

    while (file.read(reinterpret_cast<char *>(&temp), sizeof(Tricoll_Bevel_Starts)))
    {
        data.push_back(temp);
    }

    return data;
}

vector<Tricoll_Bevel_Indices> readTricollBevelIndices(string filename)
{
    vector<Tricoll_Bevel_Indices> data;
    Tricoll_Bevel_Indices temp;
    filename = filename + "." + intToHexString(static_cast<int>(lumps::TRICOLL_BEVEL_INDICES), 4) + ".bsp_lump";
    ifstream file(filename, ios::binary);

    if (!file || std::filesystem::file_size(filename) % sizeof(Tricoll_Bevel_Indices)  != 0)
    {
        std::cerr << "Error opening file: " << filename << std::endl;
        return {};
    }
    else
    {
        cout << "Reading Tricoll_Bevel_Indices from: " << filename << endl;
    }

    while (file.read(reinterpret_cast<char *>(&temp), sizeof(Tricoll_Bevel_Indices)))
    {
        data.push_back(temp);
    }

    return data;
}

vector<Lightmap_Data_Sky> readLightmapDataSky(string filename)
{
    vector<Lightmap_Data_Sky> data;
    Lightmap_Data_Sky temp;
    filename = filename + "." + intToHexString(static_cast<int>(lumps::LIGHTMAP_DATA_SKY), 4) + ".bsp_lump";
    ifstream file(filename, ios::binary);

    if (!file || std::filesystem::file_size(filename) % sizeof(Lightmap_Data_Sky)  != 0)
    {
        std::cerr << "Error opening file: " << filename << std::endl;
        return {};
    }
    else
    {
        cout << "Reading Lightmap_Data_Sky from: " << filename << endl;
    }

    while (file.read(reinterpret_cast<char *>(&temp), sizeof(Lightmap_Data_Sky)))
    {
        data.push_back(temp);
    }

    return data;
}

vector<csm_aabb_Nodes> readCSMaabbNodes(string filename)
{
    vector<csm_aabb_Nodes> data;
    csm_aabb_Nodes temp;
    filename = filename + "." + intToHexString(static_cast<int>(lumps::CSM_AABB_NODES), 4) + ".bsp_lump";
    ifstream file(filename, ios::binary);

    if (!file || std::filesystem::file_size(filename) % sizeof(csm_aabb_Nodes)  != 0)
    {
        std::cerr << "Error opening file: " << filename << std::endl;
        return {};
    }
    else
    {
        cout << "Reading csm_aabb_Nodes from: " << filename << endl;
    }

    while (file.read(reinterpret_cast<char *>(&temp), sizeof(csm_aabb_Nodes)))
    {
        data.push_back(temp);
    }

    return data;
}

vector<csm_obj_References> readCSMobjReferences(string filename)
{
    vector<csm_obj_References> data;
    csm_obj_References temp;
    filename = filename + "." + intToHexString(static_cast<int>(lumps::CSM_OBJ_REFERENCES), 4) + ".bsp_lump";
    ifstream file(filename, ios::binary);

    if (!file || std::filesystem::file_size(filename) % sizeof(csm_obj_References)  != 0)
    {
        std::cerr << "Error opening file: " << filename << std::endl;
        return {};
    }
    else
    {
        cout << "Reading csm_obj_References from: " << filename << endl;
    }

    while (file.read(reinterpret_cast<char *>(&temp), sizeof(csm_obj_References)))
    {
        data.push_back(temp);
    }

    return data;
}

vector<Lightprobes> readLightprobes(string filename)
{
    vector<Lightprobes> data;
    Lightprobes temp;
    filename = filename + "." + intToHexString(static_cast<int>(lumps::LIGHTPROBES), 4) + ".bsp_lump";
    ifstream file(filename, ios::binary);

    if (!file || std::filesystem::file_size(filename) % sizeof(Lightprobes)  != 0)
    {
        std::cerr << "Error opening file: " << filename << std::endl;
        return {};
    }
    else
    {
        cout << "Reading Lightprobes from: " << filename << endl;
    }

    while (file.read(reinterpret_cast<char *>(&temp), sizeof(Lightprobes)))
    {
        data.push_back(temp);
    }

    return data;
}

vector<Static_Prop_Lightprobe_Indices> readStaticPropLightprobeIndices(string filename)
{
    vector<Static_Prop_Lightprobe_Indices> data;
    Static_Prop_Lightprobe_Indices temp;
    filename = filename + "." + intToHexString(static_cast<int>(lumps::STATIC_PROP_LIGHTPROBE_INDICES), 4) + ".bsp_lump";
    ifstream file(filename, ios::binary);

    if (!file || std::filesystem::file_size(filename) % sizeof(Static_Prop_Lightprobe_Indices)  != 0)
    {
        std::cerr << "Error opening file: " << filename << std::endl;
        return {};
    }
    else
    {
        cout << "Reading Static_Prop_Lightprobe_Indices from: " << filename << endl;
    }

    while (file.read(reinterpret_cast<char *>(&temp), sizeof(Static_Prop_Lightprobe_Indices)))
    {
        data.push_back(temp);
    }

    return data;
}

vector<Lightprobe_Tree> readLightprobeTree(string filename)
{
    vector<Lightprobe_Tree> data;
    Lightprobe_Tree temp;
    filename = filename + "." + intToHexString(static_cast<int>(lumps::LIGHTPROBE_TREE), 4) + ".bsp_lump";
    ifstream file(filename, ios::binary);

    if (!file || std::filesystem::file_size(filename) % sizeof(Lightprobe_Tree)  != 0)
    {
        std::cerr << "Error opening file: " << filename << std::endl;
        return {};
    }
    else
    {
        cout << "Reading Lightprobe_Tree from: " << filename << endl;
    }

    while (file.read(reinterpret_cast<char *>(&temp), sizeof(Lightprobe_Tree)))
    {
        data.push_back(temp);
    }

    return data;
}

vector<Lightprobe_References> readLightprobeReferences(string filename)
{
    vector<Lightprobe_References> data;
    Lightprobe_References temp;
    filename = filename + "." + intToHexString(static_cast<int>(lumps::LIGHTPROBE_REFERENCES), 4) + ".bsp_lump";
    ifstream file(filename, ios::binary);

    if (!file || std::filesystem::file_size(filename) % sizeof(Lightprobe_References)  != 0)
    {
        std::cerr << "Error opening file: " << filename << std::endl;
        return {};
    }
    else
    {
        cout << "Reading Lightprobe_References from: " << filename << endl;
    }

    while (file.read(reinterpret_cast<char *>(&temp), sizeof(Lightprobe_References)))
    {
        data.push_back(temp);
    }

    return data;
}

vector<Lightmap_Data_Real_Time_Light> readLightmapDataRealTimeLight(string filename)
{
    vector<Lightmap_Data_Real_Time_Light> data;
    Lightmap_Data_Real_Time_Light temp;
    filename = filename + "." + intToHexString(static_cast<int>(lumps::LIGHTMAP_DATA_REAL_TIME_LIGHTS), 4) + ".bsp_lump";
    ifstream file(filename, ios::binary);

    if (!file || std::filesystem::file_size(filename) % sizeof(Lightmap_Data_Real_Time_Light)  != 0)
    {
        std::cerr << "Error opening file: " << filename << std::endl;
        return {};
    }
    else
    {
        cout << "Reading Lightmap_Data_Real_Time_Light from: " << filename << endl;
    }

    while (file.read(reinterpret_cast<char *>(&temp), sizeof(Lightmap_Data_Real_Time_Light)))
    {
        data.push_back(temp);
    }

    return data;
}

vector<Cell_bsp_Nodes> readCellbspNodes(string filename)
{
    vector<Cell_bsp_Nodes> data;
    Cell_bsp_Nodes temp;
    filename = filename + "." + intToHexString(static_cast<int>(lumps::CELL_BSP_NODES), 4) + ".bsp_lump";
    ifstream file(filename, ios::binary);

    if (!file || std::filesystem::file_size(filename) % sizeof(Cell_bsp_Nodes)  != 0)
    {
        std::cerr << "Error opening file: " << filename << std::endl;
        return {};
    }
    else
    {
        cout << "Reading Cell_bsp_Nodes from: " << filename << endl;
    }

    while (file.read(reinterpret_cast<char *>(&temp), sizeof(Cell_bsp_Nodes)))
    {
        data.push_back(temp);
    }

    return data;
}

vector<Cells> readCells(string filename)
{
    vector<Cells> data;
    Cells temp;
    filename = filename + "." + intToHexString(static_cast<int>(lumps::CELLS), 4) + ".bsp_lump";
    ifstream file(filename, ios::binary);

    if (!file || std::filesystem::file_size(filename) % sizeof(vector<Cells>)  != 0)
    {
        std::cerr << "Error opening file: " << filename << std::endl;
        return {};
    }
    else
    {
        cout << "Reading Cells from: " << filename << endl;
    }

    while (file.read(reinterpret_cast<char *>(&temp), sizeof(Cells)))
    {
        data.push_back(temp);
    }

    return data;
}

vector<Portals> readPortals(string filename)
{
    vector<Portals> data;
    Portals temp;
    filename = filename + "." + intToHexString(static_cast<int>(lumps::PORTALS), 4) + ".bsp_lump";
    ifstream file(filename, ios::binary);

    if (!file || std::filesystem::file_size(filename) % sizeof(Portals)  != 0)
    {
        std::cerr << "Error opening file: " << filename << std::endl;
        return {};
    }
    else
    {
        cout << "Reading Portals from: " << filename << endl;
    }

    while (file.read(reinterpret_cast<char *>(&temp), sizeof(Portals)))
    {
        data.push_back(temp);
    }

    return data;
}

vector<Portal_Vertices> readPortalVertices(string filename)
{
    vector<Portal_Vertices> data;
    Portal_Vertices temp;
    filename = filename + "." + intToHexString(static_cast<int>(lumps::PORTAL_VERTICES), 4) + ".bsp_lump";
    ifstream file(filename, ios::binary);

    if (!file || std::filesystem::file_size(filename) % sizeof(Portal_Vertices)  != 0)
    {
        std::cerr << "Error opening file: " << filename << std::endl;
        return {};
    }
    else
    {
        cout << "Reading Portal_Vertices from: " << filename << endl;
    }

    while (file.read(reinterpret_cast<char *>(&temp), sizeof(Portal_Vertices)))
    {
        data.push_back(temp);
    }

    return data;
}

vector<Portal_Edges> readPortalEdges(string filename)
{
    vector<Portal_Edges> data;
    Portal_Edges temp;
    filename = filename + "." + intToHexString(static_cast<int>(lumps::PORTAL_EDGES), 4) + ".bsp_lump";
    ifstream file(filename, ios::binary);

    if (!file || std::filesystem::file_size(filename) % sizeof(Portal_Edges)  != 0)
    {
        std::cerr << "Error opening file: " << filename << std::endl;
        return {};
    }
    else
    {
        cout << "Reading Portal_Edges from: " << filename << endl;
    }

    while (file.read(reinterpret_cast<char *>(&temp), sizeof(Portal_Edges)))
    {
        data.push_back(temp);
    }

    return data;
}

vector<Portal_Vertex_Edges> readPortalVertexEdges(string filename)
{
    vector<Portal_Vertex_Edges> data;
    Portal_Vertex_Edges temp;
    filename = filename + "." + intToHexString(static_cast<int>(lumps::PORTAL_VERTEX_EDGES), 4) + ".bsp_lump";
    ifstream file(filename, ios::binary);

    if (!file || std::filesystem::file_size(filename) % sizeof(Portal_Vertex_Edges)  != 0)
    {
        std::cerr << "Error opening file: " << filename << std::endl;
        return {};
    }
    else
    {
        cout << "Reading Portal_Vertex_Edges from: " << filename << endl;
    }

    while (file.read(reinterpret_cast<char *>(&temp), sizeof(Portal_Vertex_Edges)))
    {
        data.push_back(temp);
    }

    return data;
}

vector<Portal_Vertex_References> readPortalVertexReferences(string filename)
{
    vector<Portal_Vertex_References> data;
    Portal_Vertex_References temp;
    filename = filename + "." + intToHexString(static_cast<int>(lumps::PORTAL_VERTEX_REFERENCES), 4) + ".bsp_lump";
    ifstream file(filename, ios::binary);

    if (!file || std::filesystem::file_size(filename) % sizeof(Portal_Vertex_References)  != 0)
    {
        std::cerr << "Error opening file: " << filename << std::endl;
        return {};
    }
    else
    {
        cout << "Reading Portal_Vertex_References from: " << filename << endl;
    }

    while (file.read(reinterpret_cast<char *>(&temp), sizeof(Portal_Vertex_References)))
    {
        data.push_back(temp);
    }

    return data;
}

vector<Portal_Edge_References> readPortalEdgeReferences(string filename)
{
    vector<Portal_Edge_References> data;
    Portal_Edge_References temp;
    filename = filename + "." + intToHexString(static_cast<int>(lumps::PORTAL_EDGE_REFERENCES), 4) + ".bsp_lump";
    ifstream file(filename, ios::binary);

    if (!file || std::filesystem::file_size(filename) % sizeof(Portal_Edge_References)  != 0)
    {
        std::cerr << "Error opening file: " << filename << std::endl;
        return {};
    }
    else
    {
        cout << "Reading Portal_Edge_References from: " << filename << endl;
    }

    while (file.read(reinterpret_cast<char *>(&temp), sizeof(Portal_Edge_References)))
    {
        data.push_back(temp);
    }

    return data;
}

vector<Portal_Edge_Intersect_at_Edge> readPortalEdgeIntersectAtEdge(string filename)
{
    vector<Portal_Edge_Intersect_at_Edge> data;
    Portal_Edge_Intersect_at_Edge temp;
    filename = filename + "." + intToHexString(static_cast<int>(lumps::PORTAL_EDGE_INTERSECT_AT_EDGE), 4) + ".bsp_lump";
    ifstream file(filename, ios::binary);

    if (!file || std::filesystem::file_size(filename) % sizeof(Portal_Edge_Intersect_at_Edge)  != 0)
    {
        std::cerr << "Error opening file: " << filename << std::endl;
        return {};
    }
    else
    {
        cout << "Reading Portal_Edge_Intersect_at_Edge from: " << filename << endl;
    }

    while (file.read(reinterpret_cast<char *>(&temp), sizeof(Portal_Edge_Intersect_at_Edge)))
    {
        data.push_back(temp);
    }

    return data;
}

vector<Portal_Edge_Intersect_at_Vertex> readPortalEdgeIntersectAtVertex(string filename)
{
    vector<Portal_Edge_Intersect_at_Vertex> data;
    Portal_Edge_Intersect_at_Vertex temp;
    filename = filename + "." + intToHexString(static_cast<int>(lumps::PORTAL_EDGE_INTERSECT_AT_VERTEX), 4) + ".bsp_lump";
    ifstream file(filename, ios::binary);

    if (!file || std::filesystem::file_size(filename) % sizeof(Portal_Edge_Intersect_at_Vertex)  != 0)
    {
        std::cerr << "Error opening file: " << filename << std::endl;
        return {};
    }
    else
    {
        cout << "Reading Portal_Edge_Intersect_at_Vertex from: " << filename << endl;
    }

    while (file.read(reinterpret_cast<char *>(&temp), sizeof(Portal_Edge_Intersect_at_Vertex)))
    {
        data.push_back(temp);
    }

    return data;
}

vector<Portal_Edge_Intersect_Header> readPortalEdgeIntersectHeader(string filename)
{
    vector<Portal_Edge_Intersect_Header> data;
    Portal_Edge_Intersect_Header temp;
    filename = filename + "." + intToHexString(static_cast<int>(lumps::PORTAL_EDGE_INTERSECT_HEADER), 4) + ".bsp_lump";
    ifstream file(filename, ios::binary);

    if (!file || std::filesystem::file_size(filename) % sizeof(Portal_Edge_Intersect_Header)  != 0)
    {
        std::cerr << "Error opening file: " << filename << std::endl;
        return {};
    }
    else
    {
        cout << "Reading Portal_Edge_Intersect_Header from: " << filename << endl;
    }

    while (file.read(reinterpret_cast<char *>(&temp), sizeof(Portal_Edge_Intersect_Header)))
    {
        data.push_back(temp);
    }

    return data;
}

vector<Occlusion_Mesh_Vertices> readOcclusionMeshVertices(string filename)
{
    vector<Occlusion_Mesh_Vertices> data;
    Occlusion_Mesh_Vertices temp;
    filename = filename + "." + intToHexString(static_cast<int>(lumps::OCCLUSION_MESH_VERTICES), 4) + ".bsp_lump";
    ifstream file(filename, ios::binary);

    if (!file || std::filesystem::file_size(filename) % sizeof(Occlusion_Mesh_Vertices)  != 0)
    {
        std::cerr << "Error opening file: " << filename << std::endl;
        return {};
    }
    else
    {
        cout << "Reading Occlusion_Mesh_Vertices from: " << filename << endl;
    }

    while (file.read(reinterpret_cast<char *>(&temp), sizeof(Occlusion_Mesh_Vertices)))
    {
        data.push_back(temp);
    }

    return data;
}

vector<Occlusion_Mesh_Indices> readOcclusionMeshIndices(string filename)
{
    vector<Occlusion_Mesh_Indices> data;
    Occlusion_Mesh_Indices temp;
    filename = filename + "." + intToHexString(static_cast<int>(lumps::OCCLUSION_MESH_INDICES), 4) + ".bsp_lump";
    ifstream file(filename, ios::binary);

    if (!file || std::filesystem::file_size(filename) % sizeof(Occlusion_Mesh_Indices)  != 0)
    {
        std::cerr << "Error opening file: " << filename << std::endl;
        return {};
    }
    else
    {
        cout << "Reading Occlusion_Mesh_Indices from: " << filename << endl;
    }

    while (file.read(reinterpret_cast<char *>(&temp), sizeof(Occlusion_Mesh_Indices)))
    {
        data.push_back(temp);
    }

    return data;
}

vector<Cell_aabb_Nodes> readCellaabbNodes(string filename)
{
    vector<Cell_aabb_Nodes> data;
    Cell_aabb_Nodes temp;
    filename = filename + "." + intToHexString(static_cast<int>(lumps::CELL_AABB_NODES), 4) + ".bsp_lump";
    ifstream file(filename, ios::binary);

    if (!file || std::filesystem::file_size(filename) % sizeof(Cell_aabb_Nodes)  != 0)
    {
        std::cerr << "Error opening file: " << filename << std::endl;
        return {};
    }
    else
    {
        cout << "Reading Cell_aabb_Nodes from: " << filename << endl;
    }

    while (file.read(reinterpret_cast<char *>(&temp), sizeof(Cell_aabb_Nodes)))
    {
        data.push_back(temp);
    }

    return data;
}

vector<obj_References> readOBJReferences(string filename)
{
    vector<obj_References> data;
    obj_References temp;
    filename = filename + "." + intToHexString(static_cast<int>(lumps::OBJ_REFERENCES), 4) + ".bsp_lump";
    ifstream file(filename, ios::binary);

    if (!file || std::filesystem::file_size(filename) % sizeof(obj_References)  != 0)
    {
        std::cerr << "Error opening file: " << filename << std::endl;
        return {};
    }
    else
    {
        cout << "Reading obj_References from: " << filename << endl;
    }

    while (file.read(reinterpret_cast<char *>(&temp), sizeof(obj_References)))
    {
        data.push_back(temp);
    }

    return data;
}

vector<obj_Reference_Bounds> readOBJReferenceBounds(string filename)
{
    vector<obj_Reference_Bounds> data;
    obj_Reference_Bounds temp;
    filename = filename + "." + intToHexString(static_cast<int>(lumps::OBJ_REFERENCE_BOUNDS), 4) + ".bsp_lump";
    ifstream file(filename, ios::binary);

    if (!file || std::filesystem::file_size(filename) % sizeof(obj_Reference_Bounds)  != 0)
    {
        std::cerr << "Error opening file: " << filename << std::endl;
        return {};
    }
    else
    {
        cout << "Reading obj_Reference_Bounds from: " << filename << endl;
    }

    while (file.read(reinterpret_cast<char *>(&temp), sizeof(obj_Reference_Bounds)))
    {
        data.push_back(temp);
    }

    return data;
}

vector<Lightmap_Data_rtl_Page> readLightmapDataRTLPage(string filename)
{
    vector<Lightmap_Data_rtl_Page> data;
    Lightmap_Data_rtl_Page temp;
    filename = filename + "." + intToHexString(static_cast<int>(lumps::LIGHTMAP_DATA_RTL_PAGES), 4) + ".bsp_lump";
    ifstream file(filename, ios::binary);

    if (!file || std::filesystem::file_size(filename) % sizeof(Lightmap_Data_rtl_Page)  != 0)
    {
        std::cerr << "Error opening file: " << filename << std::endl;
        return {};
    }
    else
    {
        cout << "Reading Lightmap_Data_rtl_Page from: " << filename << endl;
    }

    while (file.read(reinterpret_cast<char *>(&temp), sizeof(Lightmap_Data_rtl_Page)))
    {
        data.push_back(temp);
    }

    return data;
}

vector<Level_Info> readLevelInfo(string filename)
{
    vector<Level_Info> data;
    Level_Info temp;
    filename = filename + "." + intToHexString(static_cast<int>(lumps::LEVEL_INFO), 4) + ".bsp_lump";
    ifstream file(filename, ios::binary);

    if (!file || std::filesystem::file_size(filename) % sizeof(Level_Info)  != 0)
    {
        std::cerr << "Error opening file: " << filename << std::endl;
        return {};
    }
    else
    {
        cout << "Reading Level_Info from: " << filename << endl;
    }

    while (file.read(reinterpret_cast<char *>(&temp), sizeof(Level_Info)))
    {
        data.push_back(temp);
    }

    return data;
}

vector<Shadow_Mesh_Opaque_Vertices> readShadowMeshOpaqueVertices(string filename)
{
    vector<Shadow_Mesh_Opaque_Vertices> data;
    Shadow_Mesh_Opaque_Vertices temp;
    filename = filename + "." + intToHexString(static_cast<int>(lumps::SHADOW_MESH_OPAQUE_VERTICES), 4) + ".bsp_lump";
    ifstream file(filename, ios::binary);

    if (!file || std::filesystem::file_size(filename) % sizeof(Shadow_Mesh_Opaque_Vertices)  != 0)
    {
        std::cerr << "Error opening file: " << filename << std::endl;
        return {};
    }
    else
    {
        cout << "Reading Shadow_Mesh_Opaque_Vertices from: " << filename << endl;
    }

    while (file.read(reinterpret_cast<char *>(&temp), sizeof(Shadow_Mesh_Opaque_Vertices)))
    {
        data.push_back(temp);
    }

    return data;
}

vector<Shadow_Mesh_Alpha_Vertices> readShadowMeshAlphaVertices(string filename)
{
    vector<Shadow_Mesh_Alpha_Vertices> data;
    Shadow_Mesh_Alpha_Vertices temp;
    filename = filename + "." + intToHexString(static_cast<int>(lumps::SHADOW_MESH_ALPHA_VERTICES), 4) + ".bsp_lump";
    ifstream file(filename, ios::binary);

    if (!file || std::filesystem::file_size(filename) % sizeof(Shadow_Mesh_Alpha_Vertices)  != 0)
    {
        std::cerr << "Error opening file: " << filename << std::endl;
        return {};
    }
    else
    {
        cout << "Reading Shadow_Mesh_Alpha_Vertices from: " << filename << endl;
    }

    while (file.read(reinterpret_cast<char *>(&temp), sizeof(Shadow_Mesh_Alpha_Vertices)))
    {
        data.push_back(temp);
    }

    return data;
}

vector<Shadow_Mesh_Indices> readShadowMeshIndices(string filename)
{
    vector<Shadow_Mesh_Indices> data;
    Shadow_Mesh_Indices temp;
    filename = filename + "." + intToHexString(static_cast<int>(lumps::SHADOW_MESH_INDICES), 4) + ".bsp_lump";
    ifstream file(filename, ios::binary);

    if (!file || std::filesystem::file_size(filename) % sizeof(Shadow_Mesh_Indices)  != 0)
    {
        std::cerr << "Error opening file: " << filename << std::endl;
        return {};
    }
    else
    {
        cout << "Reading Shadow_Mesh_Indices from: " << filename << endl;
    }

    while (file.read(reinterpret_cast<char *>(&temp), sizeof(Shadow_Mesh_Indices)))
    {
        data.push_back(temp);
    }

    return data;
}

vector<Shadow_Meshs> readShadowMeshs(string filename)
{
    vector<Shadow_Meshs> data;
    Shadow_Meshs temp;
    filename = filename + "." + intToHexString(static_cast<int>(lumps::SHADOW_MESHES), 4) + ".bsp_lump";
    ifstream file(filename, ios::binary);

    if (!file || std::filesystem::file_size(filename) % sizeof(Shadow_Meshs)  != 0)
    {
        std::cerr << "Error opening file: " << filename << std::endl;
        return {};
    }
    else
    {
        cout << "Reading Shadow_Meshs from: " << filename << endl;
    }

    while (file.read(reinterpret_cast<char *>(&temp), sizeof(Shadow_Meshs)))
    {
        data.push_back(temp);
    }

    return data;
}

BSPFILE readFullBSP(string filename){
    string basefilename = filename.substr(0, filename.find_last_of("."));
    BSPFILE mainBSP;
    mainBSP.entities = readEntities(filename + "." + intToHexString(static_cast<int>(lumps::ENTITIES), 4) + ".bsp_lump");
    // really should be done after Entity_Partitions
    mainBSP.entitiesEnv = readEntities(basefilename + "_env" + ".ent");
    mainBSP.entitiesFx = readEntities(basefilename + "_fx" + ".ent");
    mainBSP.entitiesScript = readEntities(basefilename + "_script" + ".ent");
    mainBSP.entitiesSnd = readEntities(basefilename + "_snd" + ".ent");

    mainBSP.planes = readPlanes(filename);
    mainBSP.texture_data = readTextureData(filename);
    mainBSP.vertices = readVertices(filename);
    mainBSP.lightprobe_parent_infos = readLightprobe_Parent_Infos(filename);
    mainBSP.shadow_environments = readShadow_Environments(filename);
    mainBSP.lightprobe_bsp_nodes = readLightprobe_BSP_Nodes(filename);
    mainBSP.lightprobe_bsp_ref_ids = readLightprobe_BSP_REF_IDS(filename);
    mainBSP.models = readModels(filename);
    mainBSP.entity_partitions = readEntityPartitions(filename);
    mainBSP.physics_collide = readPhysicsCollide(filename);
    mainBSP.vertex_normals = readVertexNormals(filename);
    mainBSP.game_lumps = readGameLumps(filename);
    mainBSP.LeafWaterData = readLeafWaterData(filename);
    mainBSP.pakFile = readpakFile(filename);
    mainBSP.cubemap = readcubemap(filename);
    mainBSP.TextureDataStringData = readTextureDataStringData(filename);
    mainBSP.TextureDataStringTable = readTextureDataStringTable(filename);
    mainBSP.WorldLights = readWorldLights(filename);
    mainBSP.WorldLightParentInfo = readWorldLightParentInfo(filename);
    mainBSP.tricollTriangles = readtricollTriangles(filename);
    mainBSP.tricollNodes = readtricollNodes(filename);
    mainBSP.tricollHeaders = readtricollHeaders(filename);
    mainBSP.VertexUnlit = readVertexUnlit(filename);
    mainBSP.VertexLitFlat = readVertexLitFlat(filename);
    mainBSP.VertexLitBump = readVertexLitBump(filename);
    mainBSP.VertexUnlitTS = readVertexUnlitTS(filename);
    mainBSP.VertexBlinnPhong = readVertexBlinnPhong(filename);
    mainBSP.MeshIndices = readMeshIndices(filename);
    mainBSP.Meshes = readMeshes(filename);
    mainBSP.MeshBounds = readMeshBounds(filename);
    mainBSP.MaterialSorts = readMaterialSorts(filename);
    mainBSP.LightmapHeaders = readLightmapHeaders(filename);
    mainBSP.CMGrid = readCMGrid(filename);
    mainBSP.CMGridCells = readCMGridCells(filename);
    mainBSP.CMGeoSets = readCMGeoSets(filename);
    mainBSP.CMGeoSetBounds = readCMGeoSetBounds(filename);
    mainBSP.CMPrimitives = readCMPrimitives(filename);
    mainBSP.CMPrimitiveBounds = readCMPrimitiveBounds(filename);
    mainBSP.CMUniqueContents = readCMUniqueContents(filename);
    mainBSP.CMBrushes = readCMBrushes(filename);
    mainBSP.CMBrushSidePlaneOffsets = readCMBrushSidePlaneOffsets(filename);
    mainBSP.CMBrushSideProperties = readCMBrushSideProperties(filename);
    mainBSP.CMBrushSideTextureVectors = readCMBrushSideTextureVectors(filename);
    mainBSP.TricollBevelStarts = readTricollBevelStarts(filename);
    mainBSP.TricollBevelIndices = readTricollBevelIndices(filename);
    mainBSP.LightmapDataSky = readLightmapDataSky(filename);
    mainBSP.CSMaabbNodes = readCSMaabbNodes(filename);
    mainBSP.CSMobjReferences = readCSMobjReferences(filename);
    mainBSP.Lightprobe = readLightprobes(filename);
    mainBSP.StaticPropLightprobeIndices = readStaticPropLightprobeIndices(filename);
    mainBSP.LightprobeTree = readLightprobeTree(filename);
    mainBSP.LightprobeReferences = readLightprobeReferences(filename);
    mainBSP.LightmapDataRealTimeLight = readLightmapDataRealTimeLight(filename);
    mainBSP.CellbspNodes = readCellbspNodes(filename);
    mainBSP.Cell = readCells(filename);
    mainBSP.Portal = readPortals(filename);
    mainBSP.PortalVertices = readPortalVertices(filename);
    mainBSP.PortalEdges = readPortalEdges(filename);
    mainBSP.PortalVertexEdges = readPortalVertexEdges(filename);
    mainBSP.PortalVertexReferences = readPortalVertexReferences(filename);
    mainBSP.PortalEdgeReferences = readPortalEdgeReferences(filename);
    mainBSP.PortalEdgeIntersectAtEdge = readPortalEdgeIntersectAtEdge(filename);
    mainBSP.PortalEdgeIntersectAtVertex = readPortalEdgeIntersectAtVertex(filename);
    mainBSP.PortalEdgeIntersectHeader = readPortalEdgeIntersectHeader(filename);
    mainBSP.OcclusionMeshVertices = readOcclusionMeshVertices(filename);
    mainBSP.OcclusionMeshIndices = readOcclusionMeshIndices(filename);
    mainBSP.CellaabbNodes = readCellaabbNodes(filename);
    mainBSP.OBJReferences = readOBJReferences(filename);
    mainBSP.OBJReferenceBounds = readOBJReferenceBounds(filename);
    mainBSP.LightmapDataRTLPage = readLightmapDataRTLPage(filename);
    mainBSP.LevelInfo = readLevelInfo(filename);
    mainBSP.ShadowMeshOpaqueVertices = readShadowMeshOpaqueVertices(filename);
    mainBSP.ShadowMeshAlphaVertices = readShadowMeshAlphaVertices(filename);
    mainBSP.ShadowMeshIndices = readShadowMeshIndices(filename);
    mainBSP.ShadowMeshs = readShadowMeshs(filename);
    return mainBSP;
}

#endif