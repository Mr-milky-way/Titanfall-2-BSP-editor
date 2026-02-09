#include <iostream>
#include <fstream>
#include <list>

struct Vector3 {
    float x, y, z;
};

//Lump 0
struct ENTITIES {

};

#pragma pack(push, 1)
//Lump 1
struct PLANES {
    Vector3 normal;
    float distance;
    
};
#pragma pack(pop)

//Lump 2
struct TEXTURE_DATA {
    int vertex_offset;
    int num_triangles;
    int material_sort;
};

//Lump 3
struct VERTICES {
    Vector3 vertex;
};

//Lump 4
//not known
struct LIGHTPROBE_PARENT_INFOS {

};

//Lump 5
struct SHADOW_ENVIRONMENTS {
    int first_csm_aabb_node;
    int first_csm_obj_reference;
    int first_shadow_mesh;
    int last_csm_aabb_node;
    int last_csm_obj_reference;
    int last_shadow_mesh;
    Vector3 sun_normal;
};


//Lump 6
struct LIGHTPROBE_BSP_NODES {
    std::tuple<Vector3, float> plane;
    std::list<int> children;
};

//Lump 7
//unknown
struct LIGHTPROBE_BSP_REF_IDS {

};

//Lump 14
struct MODELS {
    Vector3 mins;
    Vector3 maxs;
    int first_mesh;
    int num_meshes;
};
//Lump 24
struct ENTITY_PARTITIONS {

};


//Lump 29
struct PHYSICS_COLLIDE {

};

//Lump 30
struct VERTEX_NORMALS {
    Vector3 normal;
};

//Lump 35
struct GAME_LUMP {

};


//Lump 36
struct LEAF_WATER_DATA {
    float surface_z;
    float min_z;
    int texture_info;
};

//Lump 40
struct PAKFILE {

};


//Lump 42
struct CUBEMAPS {
    Vector3 origin;
    int unknown;
};

//Lump 43
struct TEXTURE_DATA_STRING_DATA {

};

//Lump 44
struct TEXTURE_DATA_STRING_TABLE {
    uint something;
};

enum class EmitType {
    SURFACE,
    POINT,
    SPOTLIGHT,
    SKY_LIGHT,
    QUAKE_LIGHT,
    SKY_AMBIENT
};

enum class WorldLightFlags {
    IN_AMBIENT_CUBE = 1
};

//Lump 54
struct WORLD_LIGHTS {
    Vector3 origin;
    Vector3 intensity;
    Vector3 normal;
    Vector3 shadow_offset;
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

int main() {
    return 0;
}