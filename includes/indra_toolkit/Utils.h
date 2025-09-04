#pragma once

namespace indra_toolkit
{
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
        // return ImVec2(max.x - min.x, max.y - min.y);
        return ImGui::GetWindowSize();
    }
}