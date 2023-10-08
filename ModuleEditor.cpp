#include "Globals.h"
#include "ModuleEditor.h"
#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleRenderer3D.h"
#include "ImGui/imgui.h"
#include "ImGui/backends/imgui_impl_opengl3.h"
#include "ImGui/backends/imgui_impl_sdl.h"

ModuleEditor::ModuleEditor(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModuleEditor::~ModuleEditor()
{
}

bool ModuleEditor::Init()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // Setup Platform/Renderer backends
    ImGui_ImplSDL2_InitForOpenGL(App->window->window, App->renderer3D->context);
    ImGui_ImplOpenGL3_Init();

    //mFPSLog.reserve(30);

    return true;
}

void ModuleEditor::DrawEditor()
{
    // Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();

    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            //ShowExampleMenuFile();

            ImGui::MenuItem("(demo menu)", NULL, false, false);
            if (ImGui::MenuItem("New")) {}
            if (ImGui::MenuItem("Open", "Ctrl+O")) {}
            if (ImGui::BeginMenu("Open Recent"))
            {
                ImGui::MenuItem("fish_hat.c");
                ImGui::MenuItem("fish_hat.inl");
                ImGui::MenuItem("fish_hat.h");
                if (ImGui::BeginMenu("More.."))
                {
                    ImGui::MenuItem("Hello");
                    ImGui::MenuItem("Sailor");
                    if (ImGui::BeginMenu("Recurse.."))
                    {
                        //ShowExampleMenuFile();
                        ImGui::EndMenu();
                    }
                    ImGui::EndMenu();
                }
                ImGui::EndMenu();
            }



            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Edit"))
        {
            if (ImGui::MenuItem("Undo", "CTRL+Z")) {}
            if (ImGui::MenuItem("Redo", "CTRL+Y", false, false)) {}  // Disabled item
            ImGui::Separator();
            if (ImGui::MenuItem("Cut", "CTRL+X")) {}
            if (ImGui::MenuItem("Copy", "CTRL+C")) {}
            if (ImGui::MenuItem("Paste", "CTRL+V")) {}
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }



    //if (ImGui::BeginMainMenuBar())
    //{
    //    if (ImGui::BeginMenu("File"))
    //    {
    //        ImGui::Text("Hello world!");
    //        ImGui::EndMenu();
    //    }
    //    if (ImGui::BeginMenu("Assets"))
    //    {
    //        ImGui::Text("Hello world!");
    //        ImGui::EndMenu();
    //    }
    //    if (ImGui::BeginMenu("Objects"))
    //    {
    //        ImGui::Text("Hello world!");
    //        ImGui::EndMenu();
    //    }
    //    if (ImGui::BeginMenu("About"))
    //    {
    //        ImGui::Text("Hello world!");
    //        ImGui::EndMenu();
    //    }
    //    ImGui::EndMainMenuBar();
    //}
    //if (ImGui::Begin("Configuration"))
    //{
    //    //ImGui::PlotHistogram("FPS", mFPSLog.data(), mFPSLog.size());
    //    ImGui::End();
    //}

    //ImGui::ShowDemoWindow();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}



bool ModuleEditor::CleanUp()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    return true;
}

void ModuleEditor::AddFPS(const float aFPS)
{
    //if (mFPSLog.size() < 30)
    //{
    //    mFPSLog.push_back(aFPS);
    //}
    //else
    //{
    //    for (unsigned int i = 0; i < mFPSLog.size(); i++)
    //    {
    //        if (i + 1 < mFPSLog.size())
    //        {
    //            float iCopy = mFPSLog[i + 1];
    //            mFPSLog[i] = iCopy;
    //        }
    //    }
    //    mFPSLog[mFPSLog.capacity() - 1] = aFPS;
    //}
}