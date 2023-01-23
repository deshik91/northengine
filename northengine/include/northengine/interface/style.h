//
// Created by deshik on 23.01.2023.
//


// Include only once in the project
//     after ImGui include
#ifndef NORTH_ENGINE_LANG_STYLE_H
#define NORTH_ENGINE_LANG_STYLE_H

#pragma region STYLE

ImVec4 FromHex(const char *hex, float alpha) {
    unsigned int r, g, b;
    sscanf(hex, "#%02x%02x%02x", &r, &g, &b);
    return ImVec4(r / 255.0f, g / 255.0f, b / 255.0f, alpha);
}

ImVec4 FromHex(const char *hex) {
    unsigned int r, g, b, a;
    sscanf(hex, "#%02x%02x%02x%02x", &r, &g, &b, &a);
    return ImVec4(r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f);
}

ImVec4 FromHex(int hex, float alpha) {
    int r = (hex >> 16) & 0xFF;
    int g = (hex >> 8) & 0xFF;
    int b = (hex) & 0xFF;
    return ImVec4(r / 255.0f, g / 255.0f, b / 255.0f, alpha);
}

ImVec4 FromHex(int hex) {
    int r = (hex >> 24) & 0xFF;
    int g = (hex >> 16) & 0xFF;
    int b = (hex >> 8) & 0xFF;
    int a = (hex) & 0xFF;
    return ImVec4(r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f);
}

enum ColorNum {
    COLOR_1,
    COLOR_2,
    COLOR_3,
    COLOR_4,
    COLOR_5,
};


ImVec4 color_1 = FromHex("#3781FCFF");
ImVec4 color_2 = FromHex("#31A1E0FF");
ImVec4 color_3 = FromHex("#43E5F7FF");
ImVec4 color_4 = FromHex("#31E0C2FF");
ImVec4 color_5 = FromHex("#37FCA2FF");

ImVec4 GetColor(ColorNum colorNum) {
    switch (colorNum) {
        case COLOR_1:
            return color_1;
        case COLOR_2:
            return color_2;
        case COLOR_3:
            return color_3;
        case COLOR_4:
            return color_4;
        case COLOR_5:
            return color_5;
    }

    return ImVec4(0, 0, 0, 0);
}

ColorNum colors[0x34];

void SaveColors() {
    FILE *file = fopen("colors.bin", "wb");
    fwrite(&color_1, sizeof(ImVec4), 1, file);
    fwrite(&color_2, sizeof(ImVec4), 1, file);
    fwrite(&color_3, sizeof(ImVec4), 1, file);
    fwrite(&color_4, sizeof(ImVec4), 1, file);
    fwrite(&color_5, sizeof(ImVec4), 1, file);

    fwrite(&colors, sizeof(ColorNum), 0x34, file);
    fclose(file);
}

void LoadColors() {
    FILE *file = fopen("colors.bin", "rb");
    fread(&color_1, sizeof(ImVec4), 1, file);
    fread(&color_2, sizeof(ImVec4), 1, file);
    fread(&color_3, sizeof(ImVec4), 1, file);
    fread(&color_4, sizeof(ImVec4), 1, file);
    fread(&color_5, sizeof(ImVec4), 1, file);

    fread(&colors, sizeof(ColorNum), 0x34, file);
    fclose(file);
}

const char *ColorIDToString(int i) {
    switch (i + 2) {
        case ImGuiCol_WindowBg:
            return "WindowBg";
        case ImGuiCol_ChildBg:
            return "ChildBg";
        case ImGuiCol_PopupBg:
            return "PopupBg";
        case ImGuiCol_Border:
            return "Border";
        case ImGuiCol_BorderShadow:
            return "BorderShadow";
        case ImGuiCol_FrameBg:
            return "FrameBg";
        case ImGuiCol_FrameBgHovered:
            return "FrameBgHovered";
        case ImGuiCol_FrameBgActive:
            return "FrameBgActive";
        case ImGuiCol_TitleBg:
            return "TitleBg";
        case ImGuiCol_TitleBgActive:
            return "TitleBgActive";
        case ImGuiCol_TitleBgCollapsed:
            return "TitleBgCollapsed";
        case ImGuiCol_MenuBarBg:
            return "MenuBarBg";
        case ImGuiCol_ScrollbarBg:
            return "ScrollbarBg";
        case ImGuiCol_ScrollbarGrab:
            return "ScrollbarGrab";
        case ImGuiCol_ScrollbarGrabHovered:
            return "ScrollbarGrabHovered";
        case ImGuiCol_ScrollbarGrabActive:
            return "ScrollbarGrabActive";
        case ImGuiCol_CheckMark:
            return "CheckMark";
        case ImGuiCol_SliderGrab:
            return "SliderGrab";
        case ImGuiCol_SliderGrabActive:
            return "SliderGrabActive";
        case ImGuiCol_Button:
            return "Button";
        case ImGuiCol_ButtonHovered:
            return "ButtonHovered";
        case ImGuiCol_ButtonActive:
            return "ButtonActive";
        case ImGuiCol_Header:
            return "Header";
        case ImGuiCol_HeaderHovered:
            return "HeaderHovered";
        case ImGuiCol_HeaderActive:
            return "HeaderActive";
        case ImGuiCol_Separator:
            return "Separator";
        case ImGuiCol_SeparatorHovered:
            return "SeparatorHovered";
        case ImGuiCol_SeparatorActive:
            return "SeparatorActive";
        case ImGuiCol_ResizeGrip:
            return "ResizeGrip";
        case ImGuiCol_ResizeGripHovered:
            return "ResizeGripHovered";
        case ImGuiCol_ResizeGripActive:
            return "ResizeGripActive";
        case ImGuiCol_Tab:
            return "Tab";
        case ImGuiCol_TabHovered:
            return "TabHovered";
        case ImGuiCol_TabActive:
            return "TabActive";
        case ImGuiCol_TabUnfocused:
            return "TabUnfocused";
        case ImGuiCol_TabUnfocusedActive:
            return "TabUnfocusedActive";
        default:
            return "Unknown";
    }
}

void SaveStyle(ImGuiStyle &style) {
    FILE *file = fopen("style.bin", "wb");
    fwrite(&style, sizeof(style), 1, file);
    fclose(file);
}

void LoadStyle(ImGuiStyle &style) {
    FILE *file = fopen("style.bin", "rb");
    fread(&style, sizeof(style), 1, file);
    fclose(file);
}

void DrawColorsGui(ImVec4 **p_colors) {
    ImGui::Begin("Colors");
    {
        ImGui::ColorEdit4("Color 1", (float *) p_colors[0]);
        ImGui::ColorEdit4("Color 2", (float *) p_colors[1]);
        ImGui::ColorEdit4("Color 3", (float *) p_colors[2]);
        ImGui::ColorEdit4("Color 4", (float *) p_colors[3]);
        ImGui::ColorEdit4("Color 5", (float *) p_colors[4]);

        ImGui::Separator();

        if (ImGui::Button("Save Colors")) {
            SaveColors();
        }
        if (ImGui::Button("Load Colors")) {
            LoadColors();
        }
    }
    ImGui::End();
}

void DrawStylesGui() {
    ImGui::Begin("Style");
    {
        for (int i = 0; i < 36; i++) {
            ImGui::Combo(ColorIDToString(i), (int *) &colors[i], "Color 1\0Color 2\0Color 3\0Color 4\0Color 5\0");
        }
    }
    ImGui::End();
}

void DrawEditStyleGui(ImGuiStyle &style, ImVec4 **p_colors) {
    DrawColorsGui(p_colors);
    DrawStylesGui();

    ImGui::Begin("Styles");
    {
        ImGui::SliderFloat("WindowRounding", &style.WindowRounding, 0.0f, 10.0f);
        ImGui::SliderFloat("FrameRounding", &style.FrameRounding, 0.0f, 10.0f);
        ImGui::SliderFloat("GrabRounding", &style.GrabRounding, 0.0f, 10.0f);
        ImGui::SliderFloat("ScrollbarRounding", &style.ScrollbarRounding, 0.0f, 10.0f);
        ImGui::SliderFloat("ChildRounding", &style.ChildRounding, 0.0f, 10.0f);
        ImGui::SliderFloat("PopupRounding", &style.PopupRounding, 0.0f, 10.0f);
        ImGui::SliderFloat("FrameBorderSize", &style.FrameBorderSize, 0.0f, 10.0f);
        ImGui::SliderFloat("WindowBorderSize", &style.WindowBorderSize, 0.0f, 10.0f);
        ImGui::SliderFloat2("WindowPadding", (float *) &style.WindowPadding, 0.0f, 10.0f);
        ImGui::SliderFloat2("FramePadding", (float *) &style.FramePadding, 0.0f, 10.0f);
        ImGui::SliderFloat2("ItemSpacing", (float *) &style.ItemSpacing, 0.0f, 10.0f);
        ImGui::SliderFloat2("ItemInnerSpacing", (float *) &style.ItemInnerSpacing, 0.0f, 10.0f);
        ImGui::SliderFloat2("WindowTitleAlign", (float *) &style.WindowTitleAlign, -1.0f, 2.0f);

        int flags = 0;
        switch (style.WindowMenuButtonPosition) {
            case ImGuiDir_Left:
                flags = 1;
                break;
            case ImGuiDir_Right:
                flags = 2;
                break;
            case ImGuiDir_None:
                flags = 0;
        }
        ImGui::Combo("WindowMenuButtonPosition", &flags, "None\0Left\0Right\0");
        switch (flags) {
            case 1:
                style.WindowMenuButtonPosition = ImGuiDir_Left;
                break;
            case 2:
                style.WindowMenuButtonPosition = ImGuiDir_Right;
                break;
            case 0:
                style.WindowMenuButtonPosition = ImGuiDir_None;
        }

        ImGui::Separator();

        if (ImGui::Button("Save style")) {
            SaveStyle(style);
        }
        if (ImGui::Button("Load style")) {
            LoadStyle(style);
        }
    }
    ImGui::End();
}

void SetStyle() {
    ImGuiStyle &style = ImGui::GetStyle();

    ImVec4 *colors_arr[5] = {
            &color_1,
            &color_2,
            &color_3,
            &color_4,
            &color_5,
    };

    DrawEditStyleGui(style, colors_arr);

    style.Colors[ImGuiCol_WindowBg] = GetColor(colors[0x00]);
    style.Colors[ImGuiCol_ChildBg] = GetColor(colors[0x01]);
    style.Colors[ImGuiCol_PopupBg] = GetColor(colors[0x02]);
    style.Colors[ImGuiCol_Border] = GetColor(colors[0x03]);
    style.Colors[ImGuiCol_BorderShadow] = GetColor(colors[0x04]);
    style.Colors[ImGuiCol_FrameBg] = GetColor(colors[0x05]);
    style.Colors[ImGuiCol_FrameBgHovered] = GetColor(colors[0x06]);
    style.Colors[ImGuiCol_FrameBgActive] = GetColor(colors[0x07]);
    style.Colors[ImGuiCol_TitleBg] = GetColor(colors[0x08]);
    style.Colors[ImGuiCol_TitleBgActive] = GetColor(colors[0x09]);
    style.Colors[ImGuiCol_TitleBgCollapsed] = GetColor(colors[0x0A]);
    style.Colors[ImGuiCol_MenuBarBg] = GetColor(colors[0x0B]);
    style.Colors[ImGuiCol_ScrollbarBg] = GetColor(colors[0x0C]);
    style.Colors[ImGuiCol_ScrollbarGrab] = GetColor(colors[0x0D]);
    style.Colors[ImGuiCol_ScrollbarGrabHovered] = GetColor(colors[0x0E]);
    style.Colors[ImGuiCol_ScrollbarGrabActive] = GetColor(colors[0x0F]);
    style.Colors[ImGuiCol_CheckMark] = GetColor(colors[0x10]);
    style.Colors[ImGuiCol_SliderGrab] = GetColor(colors[0x11]);
    style.Colors[ImGuiCol_SliderGrabActive] = GetColor(colors[0x12]);
    style.Colors[ImGuiCol_Button] = GetColor(colors[0x13]);
    style.Colors[ImGuiCol_ButtonHovered] = GetColor(colors[0x14]);
    style.Colors[ImGuiCol_ButtonActive] = GetColor(colors[0x15]);
    style.Colors[ImGuiCol_Header] = GetColor(colors[0x16]);
    style.Colors[ImGuiCol_HeaderHovered] = GetColor(colors[0x17]);
    style.Colors[ImGuiCol_HeaderActive] = GetColor(colors[0x18]);
    style.Colors[ImGuiCol_Separator] = GetColor(colors[0x19]);
    style.Colors[ImGuiCol_SeparatorHovered] = GetColor(colors[0x1A]);
    style.Colors[ImGuiCol_SeparatorActive] = GetColor(colors[0x1B]);
    style.Colors[ImGuiCol_ResizeGrip] = GetColor(colors[0x1C]);
    style.Colors[ImGuiCol_ResizeGripHovered] = GetColor(colors[0x1D]);
    style.Colors[ImGuiCol_ResizeGripActive] = GetColor(colors[0x1E]);
    style.Colors[ImGuiCol_Tab] = GetColor(colors[0x1F]);
    style.Colors[ImGuiCol_TabHovered] = GetColor(colors[0x20]);
    style.Colors[ImGuiCol_TabActive] = GetColor(colors[0x21]);
    style.Colors[ImGuiCol_TabUnfocused] = GetColor(colors[0x22]);
    style.Colors[ImGuiCol_TabUnfocusedActive] = GetColor(colors[0x23]);
    style.Colors[ImGuiCol_PlotLines] = GetColor(colors[0x24]);
    style.Colors[ImGuiCol_PlotLinesHovered] = GetColor(colors[0x25]);
    style.Colors[ImGuiCol_PlotHistogram] = GetColor(colors[0x26]);
    style.Colors[ImGuiCol_PlotHistogramHovered] = GetColor(colors[0x27]);
    style.Colors[ImGuiCol_TextSelectedBg] = GetColor(colors[0x28]);
    style.Colors[ImGuiCol_DragDropTarget] = GetColor(colors[0x29]);
    style.Colors[ImGuiCol_NavHighlight] = GetColor(colors[0x2A]);
    style.Colors[ImGuiCol_NavWindowingHighlight] = GetColor(colors[0x2B]);
    style.Colors[ImGuiCol_NavWindowingDimBg] = GetColor(colors[0x2C]);
    style.Colors[ImGuiCol_ModalWindowDimBg] = GetColor(colors[0x2D]);
}

#pragma endregion // STYLE

#endif //NORTH_ENGINE_LANG_STYLE_H
