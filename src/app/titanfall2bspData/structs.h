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

#ifndef STRUCTS_H
#define STRUCTS_H


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

struct Vector4f
{
    float x, y, z, w;
};

struct Vector4B
{
    uint8_t x, y, z, w;
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
    uint32_t first_mesh_index; // index into MeshIndices
    uint16_t num_triangles;
    uint16_t first_vertex; // index to this Mesh's first VertexReservedX
    uint16_t num_vertices;
    int8_t   vertex_type; // VERTEX_RESERVED_X index
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

//lump 95
struct cm_Brush_Side_Texture_Vectors {
    Vector4f s;
    Vector4f t;
};

static_assert(sizeof(cm_Brush_Side_Texture_Vectors) == 32, "cm_Brush_Side_Texture_Vectors struct size mismatch!");

//lump 96
struct Tricoll_Bevel_Starts {
    uint16_t start;
};

static_assert(sizeof(Tricoll_Bevel_Starts) == 2, "Tricoll_Bevel_Starts struct size mismatch!");

//lump 97
struct Tricoll_Bevel_Indices {
    uint32_t Indices;
};

static_assert(sizeof(Tricoll_Bevel_Indices) == 4, "Tricoll_Bevel_Indices struct size mismatch!");

//lump 98
struct Lightmap_Data_Sky {
    //TODO
};

//lump 99
struct csm_aabb_Nodes {
    Vector3F mins;
    uint8_t num_children;
    uint8_t num_obj_refs;
    uint16_t total_obj_refs;
    Vector3F maxs;
    uint16_t first_child;
    uint16_t first_obj_ref;
};

static_assert(sizeof(csm_aabb_Nodes) == 32, "csm_aabb_Nodes struct size mismatch!");

//lump 100
struct csm_obj_References {
    uint16_t ref;
};

static_assert(sizeof(csm_obj_References) == 2, "csm_obj_References struct size mismatch!");

//lump 101
struct Lightprobes {
    Vector4B cube[6];
    int16_t sky_dir_sun_vis[4];
    uint8_t static_light_weights[4];
    int16_t static_light_indices[4];
    uint32_t padding;
};

static_assert(sizeof(Lightprobes) == 48, "Lightprobes struct size mismatch!");

//lump 102
struct Static_Prop_Lightprobe_Indices {
    //unkown
};

//lump 103
struct Lightprobe_Tree {
    uint32_t tag;
    uint32_t num_entries;
};

static_assert(sizeof(Lightprobe_Tree) == 8, "Lightprobe_Tree struct size mismatch!");


//lump 104
struct Lightprobe_References {
    Vector3F origin;
    uint32_t lightprobe;
    int32_t unknown;
};

static_assert(sizeof(Lightprobe_References) == 20, "Lightprobe_References struct size mismatch!");

//lump 105
struct Lightmap_Data_Real_Time_Light {
    //TODO
};


//lump 106
struct Cell_bsp_Nodes {
    int32_t plane;
    int32_t child;
};

static_assert(sizeof(Cell_bsp_Nodes) == 8, "Cell_bsp_Nodes struct size mismatch!");

//lump 107
struct Cells {
    int16_t num_portals;
    int16_t first_portal;
    int16_t flags;
    int16_t leaf_water_data;
};

static_assert(sizeof(Cells) == 8, "Cells struct size mismatch!");

//lump 108
struct Portals {
    uint8_t is_reversed;
    PortalType type;
    uint8_t num_edges;
    uint8_t padding;
    int16_t first_reference;
    int16_t cell;
    int32_t plane;
};

static_assert(sizeof(Portals) == 12, "Portals struct size mismatch!");

//lump 109
struct Portal_Vertices {
    Vector3F vertex;
};

static_assert(sizeof(Portal_Vertices) == 12, "Portal_Vertices struct size mismatch!");

//lump 110
struct Portal_Edges {
    uint16_t edges;
};

static_assert(sizeof(Portal_Edges) == 2, "Portal_Edges struct size mismatch!");

//lump 111
struct Portal_Vertex_Edges {
    int16_t index[8];
};

static_assert(sizeof(Portal_Vertex_Edges) == 16, "Portal_Vertex_Edges struct size mismatch!");

//lump 112
struct Portal_Vertex_References {
    uint16_t ref;
};

static_assert(sizeof(Portal_Vertex_References) == 2, "Portal_Vertex_References struct size mismatch!");

//lump 113
struct Portal_Edge_References {
    uint16_t ref;
};

static_assert(sizeof(Portal_Edge_References) == 2, "Portal_Edge_References struct size mismatch!");

//lump 114
struct Portal_Edge_Intersect_at_Edge {
    int16_t index[8];
};

static_assert(sizeof(Portal_Edge_Intersect_at_Edge) == 16, "Portal_Edge_Intersect_at_Edge struct size mismatch!");

//lump 115
struct Portal_Edge_Intersect_at_Vertex {
    int16_t index[8];
};

static_assert(sizeof(Portal_Edge_Intersect_at_Vertex) == 16, "Portal_Edge_Intersect_at_Vertex struct size mismatch!");

//lump 116
struct Portal_Edge_Intersect_Header {
    uint32_t start;
    uint32_t count;
};

static_assert(sizeof(Portal_Edge_Intersect_Header) == 8, "Portal_Edge_Intersect_Header struct size mismatch!");

//lump 117
struct Occlusion_Mesh_Vertices {
    Vector3F vertex;
};

static_assert(sizeof(Occlusion_Mesh_Vertices) == 12, "Occlusion_Mesh_Vertices struct size mismatch!");

//lump 118
struct Occlusion_Mesh_Indices {
    int16_t indices;
};

static_assert(sizeof(Occlusion_Mesh_Indices) == 2, "Occlusion_Mesh_Indices struct size mismatch!");

//lump 119
struct Cell_aabb_Nodes {
    Vector3F origin;
    uint8_t num_children;
    uint8_t num_obj_refs;
    uint16_t total_obj_refs;
    Vector3F extents;
    uint16_t first_child;
    uint16_t first_obj_ref;
};

static_assert(sizeof(Cell_aabb_Nodes) == 32, "Cell_aabb_Nodes struct size mismatch!");

//lump 120
struct obj_References {
    uint16_t ref;
};

static_assert(sizeof(obj_References) == 2, "obj_References struct size mismatch!");

//lump 121
struct obj_Reference_Bounds {
    Vector3F mins;
    int32_t mins_zero;
    Vector3F maxs;
    int32_t maxs_zero;
};

static_assert(sizeof(obj_Reference_Bounds) == 32, "obj_Reference_Bounds struct size mismatch!");

//lump 122
struct Lightmap_Data_rtl_Page {
    //unkown
};

//lump 123
struct Level_Info {
    uint32_t first_decal_mesh;
    uint32_t first_transparent_mesh;
    uint32_t first_sky_mesh;
    uint32_t num_static_props;
    Vector3F sun_normal;
};

static_assert(sizeof(Level_Info) == 28, "Level_Info struct size mismatch!");


//lump 124
struct Shadow_Mesh_Opaque_Vertices {
    Vector3F vertex;
};

static_assert(sizeof(Shadow_Mesh_Opaque_Vertices) == 12, "Shadow_Mesh_Opaque_Vertices struct size mismatch!");

//lump 125
struct Shadow_Mesh_Alpha_Vertices {
    Vector3F position;
    Vector2F uv;
};

static_assert(sizeof(Shadow_Mesh_Alpha_Vertices) == 20, "Shadow_Mesh_Alpha_Vertices struct size mismatch!");

//lump 126
struct Shadow_Mesh_Indices {
    uint16_t indices;
};

static_assert(sizeof(Shadow_Mesh_Indices) == 2, "Shadow_Mesh_Indices struct size mismatch!");


//lump 127
struct Shadow_Meshs {
    uint32_t vertex_offset;
    uint32_t num_triangles;
    int16_t is_opaque;
    int16_t material_sort;
};

static_assert(sizeof(Shadow_Meshs) == 12, "Shadow_Meshs struct size mismatch!");


struct BSPFILE {
    std::vector<Entities> entities;
    std::vector<Entities> entitiesEnv;
    std::vector<Entities> entitiesFx;
    std::vector<Entities> entitiesScript;
    std::vector<Entities> entitiesSnd;
    std::vector<Planes> planes;
    std::vector<Texture_Data> texture_data;
    std::vector<Vertices> vertices;
    std::vector<Lightprobe_Parent_Infos> lightprobe_parent_infos;
    std::vector<Shadow_Environments> shadow_environments;
    std::vector<Lightprobe_BSP_Nodes> lightprobe_bsp_nodes;
    std::vector<Lightprobe_BSP_REF_IDS> lightprobe_bsp_ref_ids;
    std::vector<Models> models;
    std::vector<Entity_Partitions> entity_partitions;
    std::vector<Physics_Collide> physics_collide;
    std::vector<Vertex_Normals> vertex_normals;
    std::vector<Game_Lump> game_lumps;
    std::vector<Leaf_Water_Data> LeafWaterData;
    std::vector<PAKFile> pakFile;
    std::vector<Cubemap> cubemap;
    std::vector<Texture_Data_String_Data> TextureDataStringData;
    std::vector<Texture_Data_String_Table> TextureDataStringTable;
    std::vector<WORLD_LIGHTSv3> WorldLights;
    std::vector<World_Light_Parent_Infos> WorldLightParentInfo;
    std::vector<Tricoll_Triangles> tricollTriangles;
    std::vector<Tricoll_Nodes> tricollNodes;
    std::vector<Tricoll_Headers> tricollHeaders;
    std::vector<Vertex_Unlit> VertexUnlit;
    std::vector<Vertex_Lit_Flat> VertexLitFlat;
    std::vector<Vertex_Lit_Bump> VertexLitBump;
    std::vector<Vertex_unlit_TS> VertexUnlitTS;
    std::vector<Vertex_Blinn_Phong> VertexBlinnPhong;
    std::vector<Mesh_Indices> MeshIndices;
    std::vector<Mesh> Meshes;
    std::vector<Mesh_Bounds> MeshBounds;
    std::vector<Material_Sorts> MaterialSorts;
    std::vector<Lightmap_Headers> LightmapHeaders;
    std::vector<cm_Grid> CMGrid;
    std::vector<cm_Grid_Cells> CMGridCells;
    std::vector<cm_Geo_Sets> CMGeoSets;
    std::vector<cm_Geo_Set_Bounds> CMGeoSetBounds;
    std::vector<cm_Primitives> CMPrimitives;
    std::vector<cm_Primitive_Bounds> CMPrimitiveBounds;
    std::vector<cm_Unique_Contents> CMUniqueContents;
    std::vector<cm_Brushes> CMBrushes;
    std::vector<cm_Brush_Side_Plane_Offsets> CMBrushSidePlaneOffsets;
    std::vector<cm_Brush_Side_Properties> CMBrushSideProperties;
    std::vector<cm_Brush_Side_Texture_Vectors> CMBrushSideTextureVectors;
    std::vector<Tricoll_Bevel_Starts> TricollBevelStarts;
    std::vector<Tricoll_Bevel_Indices> TricollBevelIndices;
    std::vector<Lightmap_Data_Sky> LightmapDataSky;
    std::vector<csm_aabb_Nodes> CSMaabbNodes;
    std::vector<csm_obj_References> CSMobjReferences;
    std::vector<Lightprobes> Lightprobe;
    std::vector<Static_Prop_Lightprobe_Indices> StaticPropLightprobeIndices;
    std::vector<Lightprobe_Tree> LightprobeTree;
    std::vector<Lightprobe_References> LightprobeReferences;
    std::vector<Lightmap_Data_Real_Time_Light> LightmapDataRealTimeLight;
    std::vector<Cell_bsp_Nodes> CellbspNodes;
    std::vector<Cells> Cell;
    std::vector<Portals> Portal;
    std::vector<Portal_Vertices> PortalVertices;
    std::vector<Portal_Edges> PortalEdges;
    std::vector<Portal_Vertex_Edges> PortalVertexEdges;
    std::vector<Portal_Vertex_References> PortalVertexReferences;
    std::vector<Portal_Edge_References> PortalEdgeReferences;
    std::vector<Portal_Edge_Intersect_at_Edge> PortalEdgeIntersectAtEdge;
    std::vector<Portal_Edge_Intersect_at_Vertex> PortalEdgeIntersectAtVertex;
    std::vector<Portal_Edge_Intersect_Header> PortalEdgeIntersectHeader;
    std::vector<Occlusion_Mesh_Vertices> OcclusionMeshVertices;
    std::vector<Occlusion_Mesh_Indices> OcclusionMeshIndices;
    std::vector<Cell_aabb_Nodes> CellaabbNodes;
    std::vector<obj_References> OBJReferences;
    std::vector<obj_Reference_Bounds> OBJReferenceBounds;
    std::vector<Lightmap_Data_rtl_Page> LightmapDataRTLPage;
    std::vector<Level_Info> LevelInfo;
    std::vector<Shadow_Mesh_Opaque_Vertices> ShadowMeshOpaqueVertices;
    std::vector<Shadow_Mesh_Alpha_Vertices> ShadowMeshAlphaVertices;
    std::vector<Shadow_Mesh_Indices> ShadowMeshIndices;
    std::vector<Shadow_Meshs> ShadowMeshs;
};


#endif