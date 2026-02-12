#include <iostream>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <list>
#include <cstdint>
#include <vector>
#include <filesystem>
#include <QApplication>
#include <QPushButton>
#include <QMainWindow>
#include <QWidget>

#include "titanfall2bspData/structs.h"
#include "titanfall2bspData/helperfunctions.h"

using namespace std;

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
    // really should be done after Entity_Partitions
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
    vector<Vertex_unlit_TS> VertexUnlitTS = readVertexUnlitTS(filename);
    vector<Mesh_Indices> MeshIndices = readMeshIndices(filename);
    vector<Mesh> Meshes = readMeshes(filename);
    vector<Mesh_Bounds> MeshBounds = readMeshBounds(filename);
    vector<Material_Sorts> MaterialSorts = readMaterialSorts(filename);
    vector<Lightmap_Headers> LightmapHeaders = readLightmapHeaders(filename);
    vector<cm_Grid> CMGrid = readCMGrid(filename);
    vector<cm_Grid_Cells> CMGridCells = readCMGridCells(filename);
    vector<cm_Geo_Sets> CMGeoSets = readCMGeoSets(filename);
    vector<cm_Geo_Set_Bounds> CMGeoSetBounds = readCMGeoSetBounds(filename);
    vector<cm_Primitives> CMPrimitives = readCMPrimitives(filename);
    vector<cm_Primitive_Bounds> CMPrimitiveBounds = readCMPrimitiveBounds(filename);
    vector<cm_Unique_Contents> CMUniqueContents = readCMUniqueContents(filename);
    vector<cm_Brushes> CMBrushes = readCMBrushes(filename);
    vector<cm_Brush_Side_Plane_Offsets> CMBrushSidePlaneOffsets = readCMBrushSidePlaneOffsets(filename);
    vector<cm_Brush_Side_Properties> CMBrushSideProperties = readCMBrushSideProperties(filename);
    vector<cm_Brush_Side_Texture_Vectors> CMBrushSideTextureVectors = readCMBrushSideTextureVectors(filename);
    vector<Tricoll_Bevel_Starts> TricollBevelStarts = readTricollBevelStarts(filename);
    vector<Tricoll_Bevel_Indices> TricollBevelIndices = readTricollBevelIndices(filename);
    vector<Lightmap_Data_Sky> LightmapDataSky = readLightmapDataSky(filename);
    vector<csm_aabb_Nodes> CSMaabbNodes = readCSMaabbNodes(filename);
    vector<csm_obj_References> CSMobjReferences = readCSMobjReferences(filename);
    vector<Lightprobes> Lightprobes = readLightprobes(filename);
    vector<Static_Prop_Lightprobe_Indices> StaticPropLightprobeIndices = readStaticPropLightprobeIndices(filename);
    vector<Lightprobe_Tree> LightprobeTree = readLightprobeTree(filename);
    vector<Lightprobe_References> LightprobeReferences = readLightprobeReferences(filename);
    vector<Lightmap_Data_Real_Time_Light> LightmapDataRealTimeLight = readLightmapDataRealTimeLight(filename);
    vector<Cell_bsp_Nodes> CellbspNodes = readCellbspNodes(filename);
    vector<Cells> Cells = readCells(filename);
    vector<Portals> Portals = readPortals(filename);
    vector<Portal_Vertices> PortalVertices = readPortalVertices(filename);
    vector<Portal_Edges> PortalEdges = readPortalEdges(filename);
    vector<Portal_Vertex_Edges> PortalVertexEdges = readPortalVertexEdges(filename);
    vector<Portal_Vertex_References> PortalVertexReferences = readPortalVertexReferences(filename);
    vector<Portal_Edge_References> PortalEdgeReferences = readPortalEdgeReferences(filename);
    vector<Portal_Edge_Intersect_at_Edge> PortalEdgeIntersectAtEdge = readPortalEdgeIntersectAtEdge(filename);
    vector<Portal_Edge_Intersect_at_Vertex> PortalEdgeIntersectAtVertex = readPortalEdgeIntersectAtVertex(filename);
    vector<Portal_Edge_Intersect_Header> PortalEdgeIntersectHeader = readPortalEdgeIntersectHeader(filename);
    vector<Occlusion_Mesh_Vertices> OcclusionMeshVertices = readOcclusionMeshVertices(filename);
    vector<Occlusion_Mesh_Indices> OcclusionMeshIndices = readOcclusionMeshIndices(filename);
    vector<Cell_aabb_Nodes> CellaabbNodes = readCellaabbNodes(filename);
    vector<obj_References> OBJReferences = readOBJReferences(filename);
    vector<obj_Reference_Bounds> OBJReferenceBounds = readOBJReferenceBounds(filename);
    vector<Lightmap_Data_rtl_Page> LightmapDataRTLPage = readLightmapDataRTLPage(filename);
    vector<Level_Info> LevelInfo = readLevelInfo(filename);
    vector<Shadow_Mesh_Opaque_Vertices> ShadowMeshOpaqueVertices = readShadowMeshOpaqueVertices(filename);
    vector<Shadow_Mesh_Alpha_Vertices> ShadowMeshAlphaVertices = readShadowMeshAlphaVertices(filename);
    vector<Shadow_Mesh_Indices> ShadowMeshIndices = readShadowMeshIndices(filename);
    vector<Shadow_Meshs> ShadowMeshs = readShadowMeshs(filename);

    cout << "Read " << VertexLitBump.size() + VertexLitFlat.size() + VertexUnlit.size() + tricollHeaders.size() + tricollNodes.size() + tricollTriangles.size() + WorldLightParentInfo.size() + WorldLights.size() + TextureDataStringTable.size() + TextureDataStringData.size() + cubemap.size() + pakFile.size() + LeafWaterData.size() + planes.size() + texture_data.size() + vertices.size() + entitiesEnv.size() + entitiesFx.size() + entitiesScript.size() + entitiesSnd.size() + models.size() + entity_partitions.size() + physics_collide.size() + vertex_normals.size() + game_lumps.size() << " structs." << endl;
    QApplication app(argc, argv);

    QWidget window;

    QPushButton *button = new QPushButton("Hello World", &window);
    button->setGeometry(10, 10, 80, 30);

    window.show();
    return app.exec();
    // return 0;
}