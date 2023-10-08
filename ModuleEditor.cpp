#include "Globals.h"
#include "ModuleEditor.h"
#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleRenderer3D.h"
#include "ModuleInput.h"
#include "ImGui/imgui.h"
#include "ImGui/backends/imgui_impl_opengl3.h"
#include "ImGui/backends/imgui_impl_sdl2.h"


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

    mFPSLog.reserve(30);

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
            ImGui::Text("Hello world!");
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Assets"))
        {
            ImGui::Text("Hello world!");
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Objects"))
        {
            ImGui::Text("Hello world!");
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Help"))
        {
            ShowAboutInfo();
        }
        if (ImGui::BeginMenu("Configuration"))
        {
            ImGui::Text("Hello world!");
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }

    //if (ImGui::Begin("Configuration"))
    //{
    //    ImGui::PlotHistogram("FPS", mFPSLog.data(), mFPSLog.size());
    //    ImGui::End();
    //}

    ImGui::ShowDemoWindow();
    
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
    if (mFPSLog.size() < 30)
    {
        mFPSLog.push_back(aFPS);
    }
    else
    {
        for (unsigned int i = 0; i < mFPSLog.size(); i++)
        {
            if (i + 1 < mFPSLog.size())
            {
                float iCopy = mFPSLog[i + 1];
                mFPSLog[i] = iCopy;
            }
        }
        mFPSLog[mFPSLog.capacity() - 1] = aFPS;
    }
}


void ModuleEditor::ShowAboutInfo()
{
    if (ImGui::BeginMenu("About")) {
        ImGui::SeparatorText("NANO ENGINE");
        ImGui::Text("3D Graphic Engine made by Lluc Estruch and Rafael Esquius");
        ImGui::Text("Github: https://github.com/Llucaieaie/Nano-Engine");
        ImGui::Text("\n");

        ImGui::TextColored({ 1,1,0.5,1 }, "Used libraries:");
        ImGui::BulletText("SDL          http://www.libsdl.org/              version: 2.0");
        ImGui::BulletText("ImGui        https://github.com/ocornut/imgui	version: 1.89.9");
        ImGui::BulletText("Glew         https://glew.sourceforge.net/       version: 2.1.0");
        ImGui::BulletText("MathGeoLib   http://clb.demon.fi/MathGeoLib/");
        ImGui::BulletText("Parson       https://github.com/kgabis/parson");
        ImGui::Text("\n");

        ImGui::TextColored({ 1,1,0.5,1 }, "License:");
        ImGui::Text("\n");
        ImGui::Text("Copyright 2023 Lluc Estruch");
        ImGui::Text("\n");
        ImGui::Text("Permission is hereby granted, free of charge, to any person");
        ImGui::Text("obtaining a copy of this softwareand associated documentation");
        ImGui::Text("files(the 'Software'), to deal in the Software without");
        ImGui::Text("restriction, including without limitation the rights to use, ");
        ImGui::Text("copy, modify, merge, publish, distribute, sublicense, ");
        ImGui::Text("and /or sell copies of the Software, and to permit persons to ");
        ImGui::Text("whom the Software is furnished to do so, subject to ");
        ImGui::Text("the following conditions : ");
        ImGui::Text("\n");
        ImGui::Text("The above copyright noticeand this permission notice shall be ");
        ImGui::Text("included in all copies or substantial portions of the Software.");
        ImGui::Text("\n");
        ImGui::Text("THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, ");
        ImGui::Text("EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES ");
        ImGui::Text("OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND");
        ImGui::Text("NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS");
        ImGui::Text("BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ");
        ImGui::Text("ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN ");
        ImGui::Text("CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE ");
        ImGui::Text("SOFTWARE.");

        ImGui::EndMenu();
    }
    ImGui::EndMenu();
}