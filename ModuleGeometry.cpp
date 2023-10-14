#include "ModuleGeometry.h"
#include "Application.h"



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
        for (int i = 0; i < scene->mNumMeshes; i++)
        {
            ImportMesh(scene->mMeshes[i]);
        }

        aiReleaseImport(scene);
    }
    else
    {
        LOG("Error loading scene: %s", file_path);
    }
}

void ModuleGeometry::ImportMesh(aiMesh* aiMesh)
{
    Mesh* ourMesh = new Mesh();
    ourMesh->num_vertex = aiMesh->mNumVertices;
    ourMesh->vertex = new float[ourMesh->num_vertex * 3];

    memcpy(ourMesh->vertex, aiMesh->mVertices, sizeof(float) * ourMesh->num_vertex * 3);

    if (aiMesh->HasFaces())
    {
        ourMesh->num_index = aiMesh->mNumFaces * 3;
        ourMesh->index = new uint[ourMesh->num_index];

        for (uint i = 0; i < aiMesh->mNumFaces; ++i)
        {
            if (aiMesh->mFaces[i].mNumIndices != 3)
            {
                LOG("WARNING, geometry face with != 3 indices!");
            }
            else
            {
                memcpy(&ourMesh->index[i * 3], aiMesh->mFaces[i].mIndices, 3 * sizeof(uint));
            }
        }

        ourMesh->VBO = 0;
        ourMesh->EBO = 0;

        glGenBuffers(1, &(ourMesh->VBO));
        glGenBuffers(1, &(ourMesh->EBO));
        glGenVertexArrays(1, &(ourMesh->VAO));

        glBindBuffer(GL_ARRAY_BUFFER, ourMesh->VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * ourMesh->num_vertex * VERTEX_ARGUMENTS, ourMesh->vertex, GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ourMesh->EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint) * ourMesh->num_index, ourMesh->index, GL_STATIC_DRAW);

        meshVector.push_back(ourMesh);
    }
    else
    {
        delete ourMesh;
    }
}

void Mesh::Render()
{
    glEnableClientState(GL_VERTEX_ARRAY);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    glVertexPointer(3, GL_FLOAT, 0, NULL);
    glDrawElements(GL_TRIANGLES, num_index, GL_UNSIGNED_INT, NULL);

    glDisableClientState(GL_VERTEX_ARRAY);
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

}

void ModuleGeometry::RenderScene()
{
    bool showNormals = true;
    for (size_t i = 0; i < meshVector.size(); i++) {
        meshVector[i]->Render();
        if(showNormals)
            meshVector[i]->ShowNormals();
    }
}

void Mesh::ShowNormals()
{
    //Line length
    float normalLenght = 0.2f;
    
    glColor3f(1, 0, 0);
    glBegin(GL_LINES);

    //Calculate face normals
    for (int i = 0; i < num_index; i += 3)
    {
        vec3 A = GetVectorFromIndex(&vertex[index[i] * 3]);
        vec3 B = GetVectorFromIndex(&vertex[index[i + 1] * 3]);
        vec3 C = GetVectorFromIndex(&vertex[index[i + 2] * 3]);

        vec3 middle((A.x + B.x + C.x) / 3.f, (A.y + B.y + C.y) / 3.f, (A.z + B.z + C.z) / 3.f);

        vec3 crossVec = cross((B - A), (C - A));
        vec3 normalDirection = normalize(crossVec);

        glVertex3f(middle.x, middle.y, middle.z);
        glVertex3f(middle.x + normalDirection.x * normalLenght, middle.y + normalDirection.y * normalLenght, middle.z + normalDirection.z * normalLenght);
    }
    glEnd();
    glPointSize(1.f);
    glColor3f(1, 1, 1);
}

vec3 Mesh::GetVectorFromIndex(float* startValue)
{
    float x = *startValue++;
    float y = *startValue++;
    float z = *startValue++;

    return vec3(x, y, z);
}

bool ModuleGeometry::CleanUp()
{
    aiDetachAllLogStreams();
    return true;
}