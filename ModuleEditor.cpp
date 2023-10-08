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

    isInputWindow = false;

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
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Configuration"))
        {
            if (ImGui::MenuItem("Inputs")) {
                isInputWindow = !isInputWindow;
            }
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }

    if (isInputWindow)
        ShowInputInfo();

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
}


void ModuleEditor::ShowInputInfo() 
{
    ImGuiIO& io = ImGui::GetIO();
    if (ImGui::Begin("Inputs", nullptr, ImGuiWindowFlags_NoCollapse))
    {
        if (ImGui::IsMousePosValid())
            ImGui::Text("Mouse pos: (%g, %g)", io.MousePos.x, io.MousePos.y);
        else
            ImGui::Text("Mouse pos: <INVALID>");
        ImGui::Text("Mouse delta: (%g, %g)", io.MouseDelta.x, io.MouseDelta.y);
        ImGui::Text("Mouse down:");
        for (int i = 0; i < IM_ARRAYSIZE(io.MouseDown); i++) if (ImGui::IsMouseDown(i)) { ImGui::SameLine(); ImGui::Text("b%d (%.02f secs)", i, io.MouseDownDuration[i]); }
        ImGui::Text("Mouse wheel: %.1f", io.MouseWheel);

        // We iterate both legacy native range and named ImGuiKey ranges, which is a little odd but this allows displaying the data for old/new backends.
        // User code should never have to go through such hoops! You can generally iterate between ImGuiKey_NamedKey_BEGIN and ImGuiKey_NamedKey_END.
#ifdef IMGUI_DISABLE_OBSOLETE_KEYIO
        struct funcs { static bool IsLegacyNativeDupe(ImGuiKey) { return false; } };
        ImGuiKey start_key = ImGuiKey_NamedKey_BEGIN;
#else
        struct funcs { static bool IsLegacyNativeDupe(ImGuiKey key) { return key < 512 && ImGui::GetIO().KeyMap[key] != -1; } }; // Hide Native<>ImGuiKey duplicates when both exists in the array
        ImGuiKey start_key = (ImGuiKey)0;
#endif
        ImGui::Text("Keys down:");         for (ImGuiKey key = start_key; key < ImGuiKey_NamedKey_END; key = (ImGuiKey)(key + 1)) { if (funcs::IsLegacyNativeDupe(key) || !ImGui::IsKeyDown(key)) continue; ImGui::SameLine(); ImGui::Text((key < ImGuiKey_NamedKey_BEGIN) ? "\"%s\"" : "\"%s\" %d", ImGui::GetKeyName(key), key); }
        ImGui::Text("Keys mods: %s%s%s%s", io.KeyCtrl ? "CTRL " : "", io.KeyShift ? "SHIFT " : "", io.KeyAlt ? "ALT " : "", io.KeySuper ? "SUPER " : "");
        ImGui::Text("Chars queue:");       for (int i = 0; i < io.InputQueueCharacters.Size; i++) { ImWchar c = io.InputQueueCharacters[i]; ImGui::SameLine();  ImGui::Text("\'%c\' (0x%04X)", (c > ' ' && c <= 255) ? (char)c : '?', c); } // FIXME: We should convert 'c' to UTF-8 here but the functions are not public.

        ImGui::End();
    }
}