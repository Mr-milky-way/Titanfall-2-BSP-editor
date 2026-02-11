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

struct Vector3h
{
    int16_t x, y, z;
};

struct Vector3i
{
    int32_t x, y, z;
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

struct Vector2I
{
    uint32_t x, y;
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

static_assert(sizeof(Planes) == 16, "Planes struct size mismatch!");

// Lump 2
struct Texture_Data
{
    Vector3F reflectivity;
    int32_t name_index;
    Vector2i size;
    Vector2i view;
    TextureDataFlags flags;
};

static_assert(sizeof(Texture_Data) == 36, "Texture_Data struct size mismatch!");

// Lump 3
struct Vertices
{
    Vector3F vertex;
};

static_assert(sizeof(Vertices) == 12, "Vertices struct size mismatch!");

// Lump 4
// not known
struct Lightprobe_Parent_Infos
{
};

// Lump 5
struct Shadow_Environments
{
    int32_t first_csm_aabb_node;
    int32_t first_csm_obj_reference;
    int32_t first_shadow_mesh;
    int32_t last_csm_aabb_node;
    int32_t last_csm_obj_reference;
    int32_t last_shadow_mesh;
    Vector3F sun_normal;
};

static_assert(sizeof(Shadow_Environments) == 36, "Shadow_Environments struct size mismatch!");

// Lump 6
struct Lightprobe_BSP_Nodes
{
    Vector3F plane;
    float distance;
    uint32_t children[2];
};

static_assert(sizeof(Lightprobe_BSP_Nodes) == 24, "Lightprobe_BSP_Nodes struct size mismatch!");

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
    uint32_t first_mesh;
    uint32_t num_meshes;
};


static_assert(sizeof(Models) == 32, "Models struct size mismatch!");

// Lump 24
struct Entity_Partitions
{
    std::vector<std::string> partitions;
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

static_assert(sizeof(Vertex_Normals) == 12, "Vertex_Normals struct size mismatch!");

// Lump 35
struct Game_Lump
{
};

// Lump 36
struct Leaf_Water_Data
{
    float surface_z;
    float min_z;
    uint32_t texture_info;
};

static_assert(sizeof(Leaf_Water_Data) == 12, "Leaf_Water_Data struct size mismatch!");

// Lump 40
struct PAKFile
{
};

// Lump 42
struct Cubemap
{
    Vector3i origin;
    uint32_t unknown;
};

static_assert(sizeof(Cubemap) == 16, "Cubemap struct size mismatch!");

// Lump 43
struct Texture_Data_String_Data
{
    std::vector<std::string> strings;
};

// Lump 44
struct Texture_Data_String_Table
{
    uint32_t something;
};

static_assert(sizeof(Texture_Data_String_Table) == 4, "Texture_Data_String_Table struct size mismatch!");

// Lump 54
struct WORLD_LIGHTSv2
{
    Vector3F origin;
    Vector3F intensity;
    Vector3F normal;
    Vector3F shadow_offset;
    int32_t viscluster;
    EmitType type;
    int32_t style;
    float stop_dot;
    float stop_dot2;
    float exponent;
    float radius;

    float constant;
    float linear;
    float quadratic;
    WorldLightFlags flags;
    int32_t texture_data;
    int32_t parent;
    float unknown_1;
    float unknown_2;
};

static_assert(sizeof(WORLD_LIGHTSv2) == 108, "WORLD_LIGHTSv2 struct size mismatch!");

// Lump 54
struct WORLD_LIGHTSv3
{
    Vector3F origin;
    Vector3F intensity;
    Vector3F normal;
    Vector3F shadow_offset;
    int32_t viscluster;
    EmitType type;
    int32_t style;
    float stop_dot;
    float stop_dot2;
    float exponent;
    float radius;
    float constant;
    float linear;
    float quadratic;
    WorldLightFlags flags;
    int32_t texture_data;
    int32_t paren;
    float unknown_1;
    float unknown_2;
    float unknown_3;
};

static_assert(sizeof(WORLD_LIGHTSv3) == 112, "WORLD_LIGHTSv3 struct size mismatch!");

// lump 55
// unknown
struct World_Light_Parent_Infos
{
};

// lump 66
struct Tricoll_Triangles
{
    uint32_t flags: 8;
    uint32_t C: 7;
    uint32_t B: 7;
    uint32_t A: 10;
};

static_assert(sizeof(Tricoll_Triangles) == 4, "Tricoll_Triangles struct size mismatch!");

// lump 68
struct Tricoll_Nodes
{
};

// lump 69
struct Tricoll_Headers
{
    int16_t flags;
    uint16_t texture_flags; // should be TextureDataFlags but uint16_t
    int16_t texture_data;
    int16_t num_vertices;
    int16_t num_triangles;
    int16_t num_bevel_indices;
    int32_t first_vertex;
    int32_t first_triangle;
    int32_t first_node;
    int32_t first_bevel_index;
    Vector3F origin;
    float scale;
};

static_assert(sizeof(Tricoll_Headers) == 44, "Tricoll_Headers struct size mismatch!");

// lump 71
struct Vertex_Unlit
{
    uint32_t position_index;
    uint32_t normal_index;
    Vector2F albedo_uv;
    RGBA32 colour;
};

static_assert(sizeof(Vertex_Unlit) == 20, "Vertex_Unlit struct size mismatch!");

// lump 72
struct Vertex_Lit_Flat
{
    uint32_t position_index;
    uint32_t normal_index;
    Vector2F albedo_uv;
    RGBA32 colour;
    Vector2F lightmap[2];
};

static_assert(sizeof(Vertex_Lit_Flat) == 36, "Vertex_Lit_Flat struct size mismatch!");

// lump 73
struct Vertex_Lit_Bump
{
    uint32_t position_index;
    uint32_t normal_index;
    Vector2F albedo_uv;
    RGBA32 colour;
    Vector2F lightmap[2];
    int32_t tangent[2];
};

static_assert(sizeof(Vertex_Lit_Bump) == 44, "Vertex_Lit_Bump struct size mismatch!");


// lump 74
struct Vertex_unlit_TS {
    uint32_t position_index;
    uint32_t normal_index;
    Vector2F albedo_uv;
    RGBA32 colour;
    int32_t tangent[2];
};

static_assert(sizeof(Vertex_unlit_TS) == 28, "Vertex_unlit_TS struct size mismatch!");

// lump 75
struct Vertex_Blinn_Phong {
    uint32_t position_index;
    uint32_t normal_index;
    RGBA32 colour;
    Vector2F albedo_uv;
    Vector2F lightmap[2];
    float tangent[16];
};

static_assert(sizeof(Vertex_Blinn_Phong) == 100, "Vertex_Blinn_Phong struct size mismatch!");


//lump 79
struct Mesh_Indices {
    uint16_t Indices;
};

static_assert(sizeof(Mesh_Indices) == 2, "Mesh_Indices struct size mismatch!");

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

//lump 86
struct cm_Grid_Cells {
    uint16_t first_geo_set;
    uint16_t num_geo_sets;
};

static_assert(sizeof(cm_Grid_Cells) == 4, "cm_Grid_Cells struct size mismatch!");

//lump 87
struct cm_Geo_Sets {
    uint16_t straddle_group;
    uint16_t num_primitives;
    uint32_t primitive;
};

static_assert(sizeof(cm_Geo_Sets) == 8, "cm_Geo_Sets struct size mismatch!");

//lump 88
struct cm_Geo_Set_Bounds {
    Vector3h origin;
    int16_t negative_cos;
    Vector3h extents;
    int16_t positive_sin;
};

static_assert(sizeof(cm_Geo_Set_Bounds) == 16, "cm_Geo_Set_Bounds struct size mismatch!");

//lump 89
struct cm_Primitives {
    PrimitiveType type: 8;
    uint32_t index: 16;
    uint32_t unique_contents: 8;
};

static_assert(sizeof(cm_Primitives) == 4, "cm_Primitives struct size mismatch!");

//lump 90
struct cm_Primitive_Bounds {
    Vector3h origin;
    int16_t negative_cos;
    Vector3h extents;
    int16_t positive_sin;
};

static_assert(sizeof(cm_Primitive_Bounds) == 16, "cm_Primitive_Bounds struct size mismatch!");

//lump 91
struct cm_Unique_Contents {
    uint32_t count;
};

static_assert(sizeof(cm_Unique_Contents) == 4, "cm_Unique_Contents struct size mismatch!");

//lump 92
struct cm_Brushes {
    Vector3F origin;
    uint8_t num_non_axial_no_discard;
    uint8_t num_plane_offsets;
    int16_t index;
    Vector3F extents;
    int32_t brush_side_offset;
};

static_assert(sizeof(cm_Brushes) == 32, "cm_Brushes struct size mismatch!");

//lump 93
struct cm_Brush_Side_Plane_Offsets {
    uint16_t offset;
};

static_assert(sizeof(cm_Brush_Side_Plane_Offsets) == 2, "cm_Brush_Side_Plane_Offsets struct size mismatch!");

//lump 94
struct cm_Brush_Side_Properties {
    uint16_t flags: 7;
    uint16_t texture_data: 9;
};

static_assert(sizeof(cm_Brush_Side_Properties) == 2, "cm_Brush_Side_Properties struct size mismatch!");