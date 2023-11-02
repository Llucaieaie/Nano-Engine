#include "ModuleGeometry.h"
#include "Application.h"
#include "Globals.h"
#include "ModuleTextures.h"
#include "ModuleWindow.h"
#include "ModuleRenderer3D.h"
#include "ModuleHierarchy.h"
#include "GameObject.h"
#include "Component.h"
#include "Mesh.h"

#include "Glew/include/glew.h"

ModuleGeometry::ModuleGeometry(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModuleGeometry::~ModuleGeometry(){}

bool ModuleGeometry::Init()
{
    return true;
}

bool ModuleGeometry::Start()
{
    bool ret = true;

    struct aiLogStream stream;
    stream = aiGetPredefinedLogStream(aiDefaultLogStream_DEBUGGER, nullptr);
    aiAttachLogStream(&stream);

    return ret;
}

void ModuleGeometry::LoadFile(const char* file_path)
{
    const aiScene* scene = aiImportFile(file_path, aiProcessPreset_TargetRealtime_MaxQuality);

    if (scene != nullptr && scene->HasMeshes())
    {
        GameObject* newObject = new GameObject(App->hierarchy->root);

        for (int i = 0; i < scene->mNumMeshes; i++)
        {
            ImportMesh(scene->mMeshes[i], newObject);
        }
        aiReleaseImport(scene);
    }
    else
    {
        LOG("Error loading scene: %s", file_path);
    }
}

void ModuleGeometry::ImportMesh(aiMesh* aiMesh, GameObject* object)
{
    Mesh* mesh = new Mesh();
    mesh->num_vertex = aiMesh->mNumVertices;
    mesh->vertex = new float[mesh->num_vertex * VERTEX_ARGUMENTS];

    //memcpy(ourMesh->vertex, aiMesh->mVertices, sizeof(float) * ourMesh->num_vertex * 3);
    
    for (int i = 0; i < mesh->num_vertex; i++) {

        mesh->vertex[i * VERTEX_ARGUMENTS] = aiMesh->mVertices[i].x;
        mesh->vertex[i * VERTEX_ARGUMENTS + 1] = aiMesh->mVertices[i].y;
        mesh->vertex[i * VERTEX_ARGUMENTS + 2] = aiMesh->mVertices[i].z;

        mesh->vertex[i * VERTEX_ARGUMENTS + 3] = aiMesh->mTextureCoords[0][i].x;
        mesh->vertex[i * VERTEX_ARGUMENTS + 4] = aiMesh->mTextureCoords[0][i].y;
        //mesh->vertex[i * VERTEX_ARGUMENTS + 4] = 1 - aiMesh->mTextureCoords[0][i].y;
    }

    if (aiMesh->HasFaces())
    {
        mesh->num_index = aiMesh->mNumFaces * 3;
        mesh->index = new uint[mesh->num_index];

        for (uint i = 0; i < aiMesh->mNumFaces; ++i)
        {
            if (aiMesh->mFaces[i].mNumIndices != 3)
            {
                LOG("WARNING, geometry face with != 3 indices!");
            }
            else
            {
                memcpy(&mesh->index[i * 3], aiMesh->mFaces[i].mIndices, 3 * sizeof(uint));
            }
        }
        mesh->VBO = 0;
        mesh->EBO = 0;
        mesh->VAO = App->textures->textureID;
        mesh->texture_height = App->textures->textureWidth;
        mesh->texture_width = App->textures->textureWidth;

        glGenBuffers(1, (GLuint*)&(mesh->id_vertex));
        glBindBuffer(GL_ARRAY_BUFFER, mesh->id_vertex);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * mesh->num_vertex * VERTEX_ARGUMENTS, mesh->vertex, GL_STATIC_DRAW);

        glGenBuffers(1, (GLuint*)&(mesh->id_index));
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->id_index);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint) * mesh->num_index, mesh->index, GL_STATIC_DRAW);

        ComponentMesh* component = new ComponentMesh(object);
        mesh->owner = object;
        component->mesh = mesh;
        if (object->components.size() == 1)
            object->components.push_back(component);

        meshVector.push_back(mesh);
        LOG("Mesh imported.")
    }
    else
    {
        LOG("Error importing mesh.")
        delete mesh;
    }
}

void Mesh::Render()
{
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_TEXTURE_COORD_ARRAY);
    glEnableClientState(GL_VERTEX_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER, id_vertex);

    glVertexPointer(3, GL_FLOAT, sizeof(float) * VERTEX_ARGUMENTS, NULL);
    glTexCoordPointer(2, GL_FLOAT, sizeof(float) * VERTEX_ARGUMENTS, (void*)(sizeof(float) * 3));
    glBindTexture(GL_TEXTURE_2D, VAO);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_index);
    glPushMatrix();

    if (owner != nullptr) {
       glMultMatrixf(&owner->objectTransform->lTransform);
    }

    glDrawElements(GL_TRIANGLES, num_index, GL_UNSIGNED_INT, NULL);

    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D, 0);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_TEXTURE_COORD_ARRAY);
}

void ModuleGeometry::BufferMesh(Mesh* mesh)
{
    glEnableClientState(GL_VERTEX_ARRAY); 

    glGenBuffers(1, &(mesh->VBO));
    glGenBuffers(1, &(mesh->EBO));

    glBindBuffer(GL_ARRAY_BUFFER, mesh->VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * mesh->num_vertex * VERTEX_ARGUMENTS, mesh->vertex, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint) * mesh->num_index, mesh->index, GL_STATIC_DRAW);

    LOG("Mesh buffered.")
}

void ModuleGeometry::RenderScene()
{
    for (size_t i = 0; i < meshVector.size(); i++) {
        meshVector[i]->Render();
        if(showNormals)
            meshVector[i]->ShowNormals();
    }
}

void Mesh::ShowNormals()
{    
    float normalLenght = 0.25f;

    glColor3f(0.8, 0, 0);
    glBegin(GL_LINES);
    
    float3 a, b, c;
    for (int i = 0; i < num_index; i += 3)
    {
        a = GetVectorFromIndex(&vertex[index[i] * VERTEX_ARGUMENTS]);
        b = GetVectorFromIndex(&vertex[index[i + 1] * VERTEX_ARGUMENTS]);
        c = GetVectorFromIndex(&vertex[index[i + 2] * VERTEX_ARGUMENTS]);

        float3 center((a.x + b.x + c.x) / 3, (a.y + b.y + c.y) / 3, (a.z + b.z + c.z) / 3);
        float3 crossVec = Cross((b - a), (c - a));
        float normalLenght = crossVec.Length()/100;
        if (normalLenght < 0.2f) { normalLenght = 0.2f; }
        float3 normalDirection = crossVec.Normalized();
        
        glVertex3f(center.x, center.y, center.z);
        glVertex3f(center.x + normalDirection.x * normalLenght, center.y + normalDirection.y * normalLenght, center.z + normalDirection.z * normalLenght);
    }
    glColor3f(1, 1, 1);
    glEnd();

    LOG("Showing face normals");
}

float3 Mesh::GetVectorFromIndex(float* startValue)
{
    float x = *startValue++;
    float y = *startValue++;
    float z = *startValue++;

    return float3(x, y, z);
}

bool ModuleGeometry::CleanUp()
{
    aiDetachAllLogStreams();
    return true;
}