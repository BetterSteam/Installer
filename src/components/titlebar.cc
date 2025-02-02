#include <imgui.h>
#include <texture.h>
#include <dpi.h>
#include <components.h>
#include <animate.h>
#include <iostream>

using namespace ImGui;

/**
 * Render the title bar component.
 * @return Whether the title bar component is hovered.
 */
bool RenderTitleBarComponent(std::shared_ptr<RouterNav> router)
{
    static const char* strTitleText = "Steam Homebrew";

    ImGuiViewport* viewport = GetMainViewport();
    PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(ScaleX(15), ScaleY(15)));

    BeginChild("##TitleBar", ImVec2(viewport->Size.x, ScaleY(75)), false, ImGuiWindowFlags_NoScrollbar);
    {
        float iconDimension  = ScaleX(20);
        float closeButtonDim = ScaleY(20);
        float titlePadding   = ScaleX(20);
        float backButtonPos  = ScaleX(EaseInOutFloat("##TitleBarBackButton", 0.f, 45, !router->canGoBack(), 0.3f));

        SetCursorPos(ImVec2(ScaleX(5) - backButtonPos, titlePadding));

        ImVec2 backButtonDim = ImVec2(ScaleX(45), ScaleY(43));
        SetCursorPosY(ScaleX(5));

        PushStyleVar(ImGuiStyleVar_ChildRounding, ScaleX(6));
        // PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.098f, 0.102f, 0.11f, 1.0f));
        BeginChild("##BackButtonChild", ImVec2(backButtonDim.x, backButtonDim.y), true, ImGuiWindowFlags_NoScrollbar);
        {
            SetCursorPos(ImVec2(ScaleX(13), ScaleY(11)));
            Image((ImTextureID)(intptr_t)backBtnTexture, ImVec2(iconDimension, iconDimension));
        }
        PopStyleVar();
        // PopStyleColor();    
        EndChild();
        SameLine(0);

        SetCursorPosY(ScaleY(16));

        if (IsItemClicked(ImGuiMouseButton_Left))
        {
            router->navigateBack();
        }

        if (IsItemHovered())
        {
            SetMouseCursor(ImGuiMouseCursor_Hand);
        }

        Image((ImTextureID)(intptr_t)logoTexture, ImVec2(iconDimension, iconDimension));

        SameLine(0, titlePadding);
        SetCursorPosY(GetCursorPosY() + ScaleY(10));
        Text(strTitleText);
        SameLine(0, titlePadding);
        SetCursorPosY(GetCursorPosY() + ScaleY(10));

        Text("FPS: %.1f", GetIO().Framerate);
        SameLine(0, 0);

        static bool isCloseButtonHovered = false;

        if (isCloseButtonHovered) 
        {
            PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.769f, 0.169f, 0.11f, 1.0f));
        }

        ImVec2 closeButtonDimensions = ImVec2(ScaleX(70), ScaleY(43));
        SetCursorPos(ImVec2(viewport->Size.x - closeButtonDimensions.x, 0));

        PushStyleVar(ImGuiStyleVar_ChildRounding, 0);
        BeginChild("##CloseButton", ImVec2(closeButtonDimensions.x, closeButtonDimensions.y), true, ImGuiWindowFlags_NoScrollbar);
        {
            SetCursorPos(ImVec2(ScaleX(25), ScaleY(12)));
            Image((ImTextureID)(intptr_t)closeButtonTexture, ImVec2(closeButtonDim, closeButtonDim));
        }
        PopStyleVar();
        EndChild();

        if (IsItemClicked(ImGuiMouseButton_Left))
        {
            ExitProcess(0);
        }

        if (isCloseButtonHovered)
        {
            PopStyleColor();
        }

        isCloseButtonHovered = IsItemHovered();
    }
    EndChild();
    PopStyleVar();

    return IsItemHovered() || (IsItemHovered(ImGuiHoveredFlags_AllowWhenBlockedByActiveItem) && IsMouseDown(ImGuiMouseButton_Left));
}