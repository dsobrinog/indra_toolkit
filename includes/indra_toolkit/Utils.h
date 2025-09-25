#pragma once

namespace indra_toolkit
{

    #pragma region METHODS

    template <typename T>
    constexpr const T& clamp(const T& v, const T& lo, const T& hi)
    {
        return (v < lo) ? lo : (hi < v) ? hi : v;
    }
    
    inline ImVec2 clampVec2(const ImVec2& v, const ImVec2& lo, const ImVec2& hi)
    {
        return ImVec2(
            (v.x < lo.x) ? lo.x : (v.x > hi.x ? hi.x : v.x),
            (v.y < lo.y) ? lo.y : (v.y > hi.y ? hi.y : v.y)
        );
    }

    inline ImVec2 GetFullContentSizeOfCurrentWindow()
    {
        // Full inner content area of the current window/child, without double-counting padding,
        // and independent of what has already been submitted.
        ImVec2 min = ImGui::GetWindowContentRegionMin();
        ImVec2 max = ImGui::GetWindowContentRegionMax();

        // return ImVec2((max.x - ImGui::GetStyle().WindowPadding.x) - min.x, max.y - min.y);
        return ImVec2(max.x  - min.x, max.y - min.y);
        // return ImGui::GetWindowSize();
    }

    inline void DrawContentRegionBounds(ImU32 R, ImU32 G, ImU32 B)
    {
        ImVec2 start = ImGui::GetCursorScreenPos();             // top-left of current content
        ImVec2 end   = ImGui::GetWindowContentRegionMax();      // bottom-right in local coords
        ImVec2 windowPos = ImGui::GetWindowPos();              // top-left of the window

        // Convert content region max to screen coordinates
        ImVec2 max = ImVec2(windowPos.x + end.x, windowPos.y + end.y);

        ImDrawList* draw_list = ImGui::GetWindowDrawList();
        draw_list->AddRect(start, max, IM_COL32(R, G, B, 255)); // red rectangle
    }

    inline void DrawInnerAreaAfterPadding(ImU32 R, ImU32 G, ImU32 B)
    {
        ImVec2 start = ImGui::GetCursorScreenPos();             // top-left of current content
        ImVec2 end   = ImGui::GetWindowContentRegionMax();      // bottom-right in local coords
        ImVec2 windowPos = ImGui::GetWindowPos();              // top-left of the window
        ImVec2 childPadding = ImGui::GetStyle().WindowPadding;
        // ImVec2 startWithPadding = {start.x + (childPadding.x / 2), start.y + (childPadding.y / 2)};

        // Convert content region max to screen coordinates
        ImVec2 max = ImVec2(windowPos.x + end.x, windowPos.y + end.y);
        // ImVec2 maxWithPadding = { max.x - (childPadding.x / 2), max.y - (childPadding.y / 2) };
        ImDrawList* draw_list = ImGui::GetWindowDrawList();
        draw_list->AddRect(start, max, IM_COL32(R, G, B, 255)); // red rectangle
    }

    #pragma endregion
}