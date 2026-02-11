#include "enums.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <list>
#include <cstdint>
#include <vector>
#include <filesystem>
#include <regex>

//TODO: Go back thru and check sizes

struct RGBA32
{
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
};

struct Vector3F
{
    float x, y, z;
};

struct Vector4
{
    float x, y, z, w;
};

struct Vector2F
{
    float x, y;
};

struct Vector2i
{
    int32_t x, y;
};


// Lump 0
struct Entities
{
    std::vector<std::string> keyvalues;
    std::vector<std::string> values;
};

// Lump 1
struct Planes
{
    Vector3F normal;
    float distance;
};

// Lump 2
struct Texture_Data
{
    int vertex_offset;
    int num_triangles;
    int material_sort;
};

// Lump 3
struct Vertices
{
    Vector3F vertex;
};

// Lump 4
// not known
struct Lightprobe_Parent_Infos
{
};

// Lump 5
struct Shadow_Environments
{
    int first_csm_aabb_node;
    int first_csm_obj_reference;
    int first_shadow_mesh;
    int last_csm_aabb_node;
    int last_csm_obj_reference;
    int last_shadow_mesh;
    Vector3F sun_normal;
};

// Lump 6
struct Lightprobe_BSP_Nodes
{
    Vector3F plane;
    float distance;
    int children[2];
};

// Lump 7
// unknown
struct Lightprobe_BSP_REF_IDS
{
};

// Lump 14
struct Models
{
    Vector3F mins;
    Vector3F maxs;
    int first_mesh;
    int num_meshes;
};
// Lump 24
struct Entity_Partitions
{
};

// Lump 29
struct Physics_Collide
{
};

// Lump 30
struct Vertex_Normals
{
    Vector3F normal;
};

// Lump 35
struct Game_Lump
{
};

// Lump 36
struct Leaf_Water_Data
{
    float surface_z;
    float min_z;
    int texture_info;
};

// Lump 40
struct PAKFile
{
};

// Lump 42
struct Cubemap
{
    Vector3F origin;
    int unknown;
};

// Lump 43
struct Texture_Data_String_Data
{
};

// Lump 44
struct Texture_Data_String_Table
{
    uint something;
};

// Lump 54
struct WORLD_LIGHTSv2
{
    Vector3F origin;
    Vector3F intensity;
    Vector3F normal;
    Vector3F shadow_offset;
    int viscluster;
    EmitType type;
    int style;
    float stop_dot;
    float stop_dot2;
    float exponent;
    float radius;

    float constant;
    float linear;
    float quadratic;
    WorldLightFlags flags;
    int texture_data;
    int parent;
    float unknown_1;
    float unknown_2;
};

// Lump 54
struct WORLD_LIGHTSv3
{
    Vector3F origin;
    Vector3F intensity;
    Vector3F normal;
    Vector3F shadow_offset;
    int viscluster;
    EmitType type;
    int style;
    float stop_dot;
    float stop_dot2;
    float exponent;
    float radius;
    float constant;
    float linear;
    float quadratic;
    WorldLightFlags flags;
    int texture_data;
    int paren;
    float unknown_1;
    float unknown_2;
    float unknown_3;
};

// lump 55
// unknown
struct World_Light_Parent_Infos
{
};

// lump 66
struct Tricoll_Triangles
{
    int A;
    int B;
    int C;
    int flags;
};

// lump 68
struct Tricoll_Nodes
{
};

// lump 69
struct Tricoll_Headers
{
    int flags;
    TextureDataFlags texture_flags;
    int texture_data;
    int num_vertices;
    int num_triangles;
    int num_bevel_indices;
    int first_vertex;
    int first_triangle;
    int first_node;
    int first_bevel_index;
    Vector3F origin;
    float scale;
};

// lump 71
struct Vertex_Unlit
{
    int position_index;
    int normal_index;
    Vector2F albedo_uv;
    RGBA32 colour;
};

// lump 72
struct Vertex_Lit_Flat
{
    int position_index;
    int normal_index;
    Vector2F albedo_uv;
    RGBA32 colour;
    Vector2F lightmap[2];
};

// lump 73
struct Vertex_Lit_Bump
{
    int position_index;
    int normal_index;
    Vector2F albedo_uv;
    RGBA32 colour;
    Vector2F lightmap[2];
    int tangent[2];
};


// lump 74
struct Vertex_unlit_TS {
    int position_index;
    int normal_index;
    Vector2F albedo_uv;
    RGBA32 colour;
    int tangent[2];
};

// lump 75
struct Vertex_Blinn_Phong {
    int position_index;
    int normal_index;
    RGBA32 colour;
    Vector2F albedo_uv;
    Vector2F lightmap[2];
    float tangent[16];
};


//lump 79
struct Mesh_Indices {
    unsigned short int Indices;
};

//lump 80
struct Mesh {
    uint32_t first_mesh_index;
    uint16_t num_triangles;
    uint16_t first_vertex;
    uint16_t num_vertices;
    int8_t   vertex_type;
    int8_t   cubemap;
    int8_t   styles[4];
    int16_t  luxel_origin[2];
    uint8_t  luxel_offset_max[2];
    uint16_t material_sort;
    uint32_t flags;
};

static_assert(sizeof(Mesh) == 28, "Mesh struct size mismatch!");

//lump 81
struct Mesh_Bounds {
    Vector3F origin;
    float radius;
    Vector3F extents;
    float tan_yaw;
};

static_assert(sizeof(Mesh_Bounds) == 32, "Mesh_Bounds struct size mismatch!");

//lump 82
struct Material_Sorts {
    int16_t texture_data;
    int16_t lightmap_header;
    int16_t cubemap;
    int16_t last_vertex;
    int vertex_offset;
};

static_assert(sizeof(Material_Sorts) == 12, "Material_Sorts struct size mismatch!");

//lump 83
struct Lightmap_Headers {
    uint32_t type;
    uint16_t width;
    uint16_t height;
};

static_assert(sizeof(Lightmap_Headers) == 8, "Lightmap_Headers struct size mismatch!");

//lump 85
struct cm_Grid {
    float scale;
    Vector2i offset;
    Vector2i count;
    int32_t num_straddle_groups;
    int32_t first_brush_plane;
};

static_assert(sizeof(cm_Grid) == 28, "cm_Grid struct size mismatch!");