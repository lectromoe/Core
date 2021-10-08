#include <core/Editor/EditorModule.h>
#include <core/Editor/HierarchyEditorWindow.h>
#include <core/Editor/ProfilerEditorWindow.h>
#include <core/Editor/InspectorEditorWindow.h>
#include <core/Editor/ConsoleEditorWindow.h>
#include <core/Editor/SceneViewEditorWindow.h>

namespace core {

EditorModule::EditorModule(GUIModule* guiModule, InputModule* inputModule)
: IModule("Editor", EDITOR), inputModule(inputModule), guiModule(guiModule)
{
    editorDockSpaceName = "EditorDockSpace";
    dockSpaceFlags = ImGuiDockNodeFlags_PassthruCentralNode;
    windowFlags = ImGuiWindowFlags_MenuBar
                | ImGuiWindowFlags_NoDocking
                | ImGuiWindowFlags_NoTitleBar
                | ImGuiWindowFlags_NoCollapse
                | ImGuiWindowFlags_NoResize
                | ImGuiWindowFlags_NoMove
                | ImGuiWindowFlags_NoBringToFrontOnFocus
                | ImGuiWindowFlags_NoNavFocus
                | ImGuiWindowFlags_NoBackground;
}
void EditorModule::Start() {
    ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    inputModule->OnViewportEvent.Subscribe([&](ViewportEvent& event) {
        viewport = ImGui::GetMainViewport();
        viewportNeedsReload = true;
    });

    sceneView = SceneView{{}, {}};

    ConstructDockSpace();
}
void EditorModule::ConstructDockSpace() {
    viewport = ImGui::GetMainViewport();

    ImGui::NewFrame();
    ImGui::Begin("DockSpace", nullptr, windowFlags);

    {
        dockSpaceID = ImGui::GetID(editorDockSpaceName.c_str());
        ImGui::DockSpace(dockSpaceID, ImVec2(0.0f, 0.0f), dockSpaceFlags);

        ImGui::DockBuilderRemoveNode(dockSpaceID); // clear any previous layout
        ImGui::DockBuilderAddNode(dockSpaceID, dockSpaceFlags | ImGuiDockNodeFlags_DockSpace);
        ImGui::DockBuilderSetNodeSize(dockSpaceID, viewport->Size);

        // TODO: Change AddWindow to take dock space instead of creating it
        ImGuiID centerSplitID = dockSpaceID;
        ImGuiID rightSplitID = ImGui::DockBuilderSplitNode(centerSplitID, ImGuiDir_Right, 0.35, nullptr, &centerSplitID);
        ImGuiID downSplitID = ImGui::DockBuilderSplitNode(centerSplitID, ImGuiDir_Down, 0.2, nullptr, &centerSplitID);
        ImGuiID leftSplitID = ImGui::DockBuilderSplitNode(centerSplitID, ImGuiDir_Left, 0.25, nullptr, &centerSplitID);

        AddWindow<InspectorEditorWindow>(rightSplitID);
        AddWindow<ProfilerEditorWindow>(downSplitID);
        AddWindow<ConsoleWindowEditorWindow>(downSplitID);
        AddWindow<HierarchyEditorWindow>(leftSplitID);
        AddWindow<SceneViewEditorWindow>(centerSplitID);

        ImGui::DockBuilderFinish(dockSpaceID);
    }

    ImGui::End();
    ImGui::EndFrame();
}
void EditorModule::OnGUI() {
    if (viewportNeedsReload) { ReloadViewport(); }

    PushDockStyle();
    BeginEditorDockSpace();
    PopDockStyle();

    for (auto &editorWindow : windows) {
        for (auto& style : editorWindow->styles ) {
//            ImGui::PushStyleColor(style.first, style.second);
        }
        editorWindow->Draw();
//        ImGui::PopStyleColor(editorWindow->styles.size());
    }
}
void EditorModule::PopDockStyle() const {
    ImGui::PopStyleVar(3);
}
void EditorModule::BeginEditorDockSpace() {
    ImGui::Begin("DockSpace", nullptr, windowFlags);
    dockSpaceID = ImGui::GetID(editorDockSpaceName.c_str());
    ImGui::DockSpace(dockSpaceID, ImVec2(0.0f, 0.0f), dockSpaceFlags);
    ImGui::End();
}
void EditorModule::ReloadViewport() const {
    ImGui::SetNextWindowPos(viewport->Pos);
    ImGui::SetNextWindowSize(viewport->Size);
    ImGui::SetNextWindowViewport(viewport->ID);
}
void EditorModule::PushDockStyle() const {
    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
}

}

