/**
 * Copyright (c) Wasted Audio 2023 - GPL-3.0-or-later
 */

#include "DistrhoUI.hpp"
#include "ResizeHandle.hpp"
#include "veramobd.hpp"
#include "wstdcolors.hpp"


START_NAMESPACE_DISTRHO

// --------------------------------------------------------------------------------------------------------------------
class ImGuiPluginUI : public UI
{
    float fhigh = 0.0f;
    float fhigh_cross = 20.0f;
    float fhigh_feedback = 25.0f;
    float fhigh_mix = 50.0f;
    bool fhigh_sync = 0.0f != 0.0f;
    float fhigh_time = 500.0f;
    int fhigh_timesync = 6;

    float flow = 0.0f;
    float flow_cross = 20.0f;
    float flow_feedback = 25.0f;
    float flow_mix = 50.0f;
    bool flow_sync = 0.0f != 0.0f;
    float flow_time = 500.0f;
    int flow_timesync = 6;

    float fmid = 0.0f;
    float fmid_cross = 20.0f;
    float fmid_feedback = 25.0f;
    float fmid_freq = 1337.0f;
    float fmid_mix = 50.0f;
    bool fmid_sync = 0.0f != 0.0f;
    float fmid_time = 500.0f;
    int fmid_timesync = 6;

    int default_item_id = 6;
    int items_len = 13;

    ResizeHandle fResizeHandle;

    // ----------------------------------------------------------------------------------------------------------------

public:
   /**
      UI class constructor.
      The UI should be initialized to a default state that matches the plugin side.
    */
    ImGuiPluginUI()
        : UI(DISTRHO_UI_DEFAULT_WIDTH, DISTRHO_UI_DEFAULT_HEIGHT, true),
          fResizeHandle(this)
    {
        setGeometryConstraints(DISTRHO_UI_DEFAULT_WIDTH, DISTRHO_UI_DEFAULT_HEIGHT, true);

        ImGuiIO& io(ImGui::GetIO());

        ImFontConfig fc;
        fc.FontDataOwnedByAtlas = true;
        fc.OversampleH = 1;
        fc.OversampleV = 1;
        fc.PixelSnapH = true;

        io.Fonts->AddFontFromMemoryCompressedTTF((void*)veramobd_compressed_data, veramobd_compressed_size, 16.0f * getScaleFactor(), &fc);
        io.Fonts->AddFontFromMemoryCompressedTTF((void*)veramobd_compressed_data, veramobd_compressed_size, 21.0f * getScaleFactor(), &fc);
        io.Fonts->AddFontFromMemoryCompressedTTF((void*)veramobd_compressed_data, veramobd_compressed_size, 11.0f * getScaleFactor(), &fc);
        io.Fonts->Build();
        io.FontDefault = io.Fonts->Fonts[1];

        fResizeHandle.hide();
    }

protected:
    // ----------------------------------------------------------------------------------------------------------------
    // DSP/Plugin Callbacks

   /**
      A parameter has changed on the plugin side.@n
      This is called by the host to inform the UI about parameter changes.
    */
    void parameterChanged(uint32_t index, float value) override
    {
        switch (index) {
            case 0:
                fhigh = value;
                break;
            case 1:
                fhigh_cross = value;
                break;
            case 2:
                fhigh_feedback = value;
                break;
            case 3:
                fhigh_mix = value;
                break;
            case 4:
                fhigh_sync = value != 0.0f;
                break;
            case 5:
                fhigh_time = value;
                break;
            case 6:
                fhigh_timesync = value;
                break;
            case 7:
                flow = value;
                break;
            case 8:
                flow_cross = value;
                break;
            case 9:
                flow_feedback = value;
                break;
            case 10:
                flow_mix = value;
                break;
            case 11:
                flow_sync = value != 0.0f;
                break;
            case 12:
                flow_time = value;
                break;
            case 13:
                flow_timesync = value;
                break;
            case 14:
                fmid = value;
                break;
            case 15:
                fmid_cross = value;
                break;
            case 16:
                fmid_feedback = value;
                break;
            case 17:
                fmid_freq = value;
                break;
            case 18:
                fmid_mix = value;
                break;
            case 19:
                fmid_sync = value != 0.0f;
                break;
            case 20:
                fmid_time = value;
                break;
            case 21:
                fmid_timesync = value;
                break;

            default: return;
        }

        repaint();
    }

    // ----------------------------------------------------------------------------------------------------------------
    // Widget Callbacks

   /**
      ImGui specific onDisplay function.
    */
    void onImGuiDisplay() override
    {

        const float width = getWidth();
        const float height = getHeight();
        const float margin = 0.0f;

        ImGui::SetNextWindowPos(ImVec2(margin, margin));
        ImGui::SetNextWindowSize(ImVec2(width - 2 * margin, height - 2 * margin));

        ImGuiStyle& style = ImGui::GetStyle();
        style.WindowTitleAlign = ImVec2(0.5f, 0.5f);


        style.Colors[ImGuiCol_TitleBgActive] = (ImVec4)WstdTitleBgActive;
        style.Colors[ImGuiCol_WindowBg] = (ImVec4)WstdWindowBg;

        ImGuiIO& io(ImGui::GetIO());
        ImFont* defaultFont = ImGui::GetFont();
        ImFont* titleBarFont = io.Fonts->Fonts[2];
        ImFont* smallFont = io.Fonts->Fonts[3];

        // Colors
        auto HighColorActive     = ColorBright(Blue,   fhigh);
        auto HighColorHovered    = ColorBright(BlueBr, fhigh);
        auto MidColorActive      =    ColorMid(Blue,   Green,   Red,   fmid, fmid_freq);
        auto MidColorHovered     =    ColorMid(BlueBr, GreenBr, RedBr, fmid, fmid_freq);
        auto MidFreqColorActive  =    ColorMid(BlueBr, GreenDr, RedBr, fmid, fmid_freq);
        auto MidFreqColorHovered =    ColorMid(Blue,   Green,   Red,   fmid, fmid_freq);
        auto LowColorActive      = ColorBright(Red,    flow);
        auto LowColorHovered     = ColorBright(RedBr,  flow);

        auto HighMixActive       = ColorMix(HighColorActive,  Yellow,   fhigh, fhigh_mix);
        auto HighMixHovered      = ColorMix(HighColorHovered, YellowBr, fhigh, fhigh_mix);
        auto MidMixActive        = ColorMix(MidColorActive,   Yellow,   fmid,  fmid_mix);
        auto MidMixHovered       = ColorMix(MidColorHovered,  YellowBr, fmid,  fmid_mix);
        auto LowMixActive        = ColorMix(LowColorActive,   Yellow,   flow,  flow_mix);
        auto LowMixHovered       = ColorMix(LowColorHovered,  YellowBr, flow,  flow_mix);

        auto HighSyncSw          = ColorBright(WhiteDr, fhigh, false);
        auto HighSyncGr          = ColorBright(Grey, fhigh);
        auto HighSyncGrHovered   = ColorBright(GreyBr, fhigh);
        auto HighSyncAct         = ColorBright(BlueDr, fhigh);
        auto HighSyncActHovered  = HighColorActive;

        auto MidSyncSw           = ColorBright(WhiteDr, fmid, false);
        auto MidSyncGr           = ColorBright(Grey, fmid);
        auto MidSyncGrHovered    = ColorBright(GreyBr, fmid);
        auto MidSyncAct          = MidFreqColorActive;
        auto MidSyncActHovered   = MidColorActive;

        auto LowSyncSw           = ColorBright(WhiteDr, flow, false);
        auto LowSyncGr           = ColorBright(Grey, flow);
        auto LowSyncGrHovered    = ColorBright(GreyBr, flow);
        auto LowSyncAct          = ColorBright(RedDr, flow);
        auto LowSyncActHovered   = LowColorActive;

        // Sizes
        auto scaleFactor         = getScaleFactor();
        const float hundred      = 100 * scaleFactor;
        const float seventy      = 70 * scaleFactor;
        const float knobWidth    = 85 * scaleFactor;
        const float toggleWidth  = 18 * scaleFactor;
        const float eqText       = 45 * scaleFactor;

        auto percstep            = 1.0f;
        auto msstep              = 10.0f;
        auto syncstep            = 0.08f;
        auto dbstep              = 0.1f;
        auto hzstep              = 20.0f;

        if (io.KeyShift)
        {
            percstep = 0.1f;
            msstep = 1.0f;
            syncstep = 0.03f;
            dbstep = 0.01f;
            hzstep = 1.0f;
        }

        const char* timesync_list[13] = {
            "×6",
            "×5",
            "×4",
            "×3",
            "×2",
            "×1.5",
            "×1",
            "÷1.5",
            "÷2",
            "÷3",
            "÷4",
            "÷5",
            "÷6",
        };

        ImGui::PushFont(titleBarFont);
        if (ImGui::Begin("WSTD DL3Y", nullptr, ImGuiWindowFlags_NoResize + ImGuiWindowFlags_NoCollapse))
        {

            ImGui::Dummy(ImVec2(0.0f, 8.0f) * getScaleFactor());
            ImGui::PushFont(defaultFont);
            auto ImGuiKnob_Flags = ImGuiKnobFlags_DoubleClickReset + ImGuiKnobFlags_ValueTooltip + ImGuiKnobFlags_NoInput + ImGuiKnobFlags_ValueTooltipHideOnClick + ImGuiKnobFlags_NoTitle;
            auto ImGuiKnob_FlagsDB = ImGuiKnob_Flags + ImGuiKnobFlags_dB;
            auto ImGuiKnob_FlagsLog = ImGuiKnob_Flags + ImGuiKnobFlags_Logarithmic;

            // EQ Text
            ImGui::BeginGroup();
            {
                ImGui::PushStyleColor(ImGuiCol_Text, TextClr);
                ImGui::Dummy(ImVec2(0.0f, 38.0f) * scaleFactor);
                CenterTextX("High", eqText);
                ImGui::Dummy(ImVec2(0.0f, 80.0f) * scaleFactor);
                CenterTextX("Mid", eqText);
                ImGui::Dummy(ImVec2(0.0f, 60.0f) * scaleFactor);
                ImGui::PushFont(smallFont);
                CenterTextX("Mid", eqText);
                CenterTextX("Freq", eqText);
                ImGui::PopFont();
                ImGui::Dummy(ImVec2(0.0f, 60.0f) * scaleFactor);
                CenterTextX("Low", eqText);
                ImGui::PopStyleColor();
            }
            ImGui::EndGroup();
            ImGui::SameLine();

            // EQ Section
            ImGui::BeginGroup();
            {
                ImGui::PushStyleColor(ImGuiCol_ButtonActive,    (ImVec4)HighColorActive);
                ImGui::PushStyleColor(ImGuiCol_ButtonHovered,   (ImVec4)HighColorHovered);
                if (ImGuiKnobs::Knob("High", &fhigh, -15.0f, 15.0, dbstep, "%.2fdB", ImGuiKnobVariant_SteppedTick, hundred, ImGuiKnob_FlagsDB, 7))
                {

                    if (ImGui::IsItemActivated())
                    {
                        editParameter(0, true);
                        if (ImGui::IsMouseDoubleClicked(0))
                            fhigh = 0.0f;
                    }
                    setParameterValue(0, fhigh);
                }
                ImGui::PopStyleColor(2);

                ImGui::PushStyleColor(ImGuiCol_ButtonActive,    (ImVec4)MidColorActive);
                ImGui::PushStyleColor(ImGuiCol_ButtonHovered,   (ImVec4)MidColorHovered);
                if (ImGuiKnobs::Knob("Mid", &fmid, -15.0f, 15.0, dbstep, "%.2fdB", ImGuiKnobVariant_SteppedTick, hundred, ImGuiKnob_FlagsDB, 7))
                {
                    if (ImGui::IsItemActivated())
                    {
                        editParameter(14, true);
                        if (ImGui::IsMouseDoubleClicked(0))
                            fmid = 0.0f;
                    }
                    setParameterValue(14, fmid);
                }
                ImGui::PopStyleColor(2);

                ImGui::Dummy(ImVec2(7.5f, 0.0f) * getScaleFactor()); ImGui::SameLine();
                ImGui::PushStyleColor(ImGuiCol_ButtonActive,    (ImVec4)MidFreqColorActive);
                ImGui::PushStyleColor(ImGuiCol_ButtonHovered,   (ImVec4)MidFreqColorHovered);
                if (ImGuiKnobs::Knob("Mid Freq", &fmid_freq, 313.3f, 5705.6f, hzstep, "%.1fHz", ImGuiKnobVariant_SteppedTick, seventy, ImGuiKnob_FlagsLog, 11))
                {
                    if (ImGui::IsItemActivated())
                    {
                        editParameter(17, true);
                        if (ImGui::IsMouseDoubleClicked(0))
                            fmid_freq = 1337.0f;
                    }
                    setParameterValue(17, fmid_freq);
                }
                ImGui::PopStyleColor(2);

                ImGui::PushStyleColor(ImGuiCol_ButtonActive,    (ImVec4)LowColorActive);
                ImGui::PushStyleColor(ImGuiCol_ButtonHovered,   (ImVec4)LowColorHovered);
                if (ImGuiKnobs::Knob("Low", &flow, -15.0f, 15.0, dbstep, "%.2fdB", ImGuiKnobVariant_SteppedTick, hundred, ImGuiKnob_FlagsDB, 7))
                {
                    if (ImGui::IsItemActivated())
                    {
                        editParameter(7, true);
                        if (ImGui::IsMouseDoubleClicked(0))
                            flow = 0.0f;
                    }
                    setParameterValue(7, flow);
                }
                ImGui::PopStyleColor(2);
            }
            ImGui::EndGroup(); ImGui::SameLine();
            ImGui::Dummy(ImVec2(20.0f, 0.0f) * getScaleFactor()); ImGui::SameLine();

            // High Band
            ImGui::BeginGroup();
            {
                ImGui::BeginGroup();
                {
                    ImGui::PushStyleColor(ImGuiCol_ButtonActive,    (ImVec4)HighColorActive);
                    ImGui::PushStyleColor(ImGuiCol_ButtonHovered,   (ImVec4)HighColorHovered);
                    if (not fhigh_sync)
                    {
                        if (ImGuiKnobs::Knob(
                            "High Time", &fhigh_time, 50.0f, 5000.0f, msstep, "%.0fms",
                            ImGuiKnobVariant_SteppedTick, hundred, ImGuiKnob_FlagsLog, 21))
                        {
                            if (ImGui::IsItemActivated())
                            {
                                editParameter(5, true);
                                if (ImGui::IsMouseDoubleClicked(0))
                                    fhigh_time = 500.0f;
                            }
                            setParameterValue(5, fhigh_time);
                        }
                    }

                    if (fhigh_sync)
                    {
                        if (ImGuiKnobs::KnobInt(
                            "High TimeSync", &fhigh_timesync, 0, items_len-1, syncstep, timesync_list[fhigh_timesync],
                            ImGuiKnobVariant_SteppedTick, hundred, ImGuiKnob_Flags, items_len))
                        {
                            if (ImGui::IsItemActivated())
                            {
                                editParameter(6, true);
                                if (ImGui::IsMouseDoubleClicked(0))
                                {
                                    fhigh_timesync = default_item_id;
                                }
                            }
                            setParameterValue(6, fhigh_timesync);
                        }
                    }
                    ImGui::SameLine();

                    ImGui::BeginGroup();
                    {
                        ImGui::Dummy(ImVec2(0.0f, 35.0f) * scaleFactor);

                        // knob
                        ImGui::PushStyleColor(ImGuiCol_Text,            (ImVec4)HighSyncSw);

                        // inactive colors
                        ImGui::PushStyleColor(ImGuiCol_FrameBg,         (ImVec4)HighSyncGr);
                        ImGui::PushStyleColor(ImGuiCol_FrameBgHovered,  (ImVec4)HighSyncGrHovered);

                        // active colors
                        ImGui::PushStyleColor(ImGuiCol_Button,          (ImVec4)HighSyncAct);
                        ImGui::PushStyleColor(ImGuiCol_ButtonHovered,   (ImVec4)HighSyncActHovered);
                        if (ImGui::Toggle("##High Sync", &fhigh_sync, ImGuiToggleFlags_Animated))
                        {
                            if (ImGui::IsItemActivated())
                            {
                                editParameter(4, true);
                                setParameterValue(4, fhigh_sync);
                            }
                        }
                        ImGui::PopStyleColor(5);
                    }
                    ImGui::EndGroup();
                    ImGui::SameLine();

                    if (ImGuiKnobs::Knob("High Feedback", &fhigh_feedback, 0.0f, 100.0f, percstep, "%.1f%%", ImGuiKnobVariant_Space, hundred, ImGuiKnob_Flags))
                    {
                        if (ImGui::IsItemActivated())
                        {
                            editParameter(2, true);
                            if (ImGui::IsMouseDoubleClicked(0))
                                fhigh_feedback = 25.0f;
                        }
                        setParameterValue(2, fhigh_feedback);
                    }
                    ImGui::SameLine();

                    if (ImGuiKnobs::Knob("High Cross", &fhigh_cross, 0.0f, 100.0f, percstep, "%.1f%%", ImGuiKnobVariant_SteppedTick, hundred, ImGuiKnob_Flags, 11))
                    {
                        if (ImGui::IsItemActivated())
                        {
                            editParameter(1, true);
                            if (ImGui::IsMouseDoubleClicked(0))
                                fhigh_cross = 20.0f;
                        }
                        setParameterValue(1, fhigh_cross);
                    }
                    ImGui::PopStyleColor(2);
                    ImGui::SameLine();

                    ImGui::PushStyleColor(ImGuiCol_ButtonActive,    (ImVec4)HighMixActive);
                    ImGui::PushStyleColor(ImGuiCol_ButtonHovered,   (ImVec4)HighMixHovered);
                    if (ImGuiKnobs::Knob("High Mix", &fhigh_mix, 0.0f, 100.0f, percstep, "%.1f%%", ImGuiKnobVariant_SteppedTick, hundred, ImGuiKnob_Flags, 11))
                    {
                        if (ImGui::IsItemActivated())
                        {
                            editParameter(3, true);
                            if (ImGui::IsMouseDoubleClicked(0))
                                fhigh_mix = 50.0f;
                        }
                        setParameterValue(3, fhigh_mix);
                    }
                    ImGui::PopStyleColor(2);
                }
                ImGui::EndGroup();

                // Mid Band
                ImGui::BeginGroup();
                {
                    ImGui::PushStyleColor(ImGuiCol_ButtonActive,    (ImVec4)MidColorActive);
                    ImGui::PushStyleColor(ImGuiCol_ButtonHovered,   (ImVec4)MidColorHovered);
                    if (not fmid_sync)
                    {
                        if (ImGuiKnobs::Knob(
                            "Mid Time", &fmid_time, 50.0f, 5000.0f, msstep, "%.0fms",
                            ImGuiKnobVariant_SteppedTick, hundred, ImGuiKnob_FlagsLog, 21))
                        {
                            if (ImGui::IsItemActivated())
                            {
                                editParameter(20, true);
                                if (ImGui::IsMouseDoubleClicked(0))
                                    fmid_time = 500.0f;
                            }
                            setParameterValue(20, fmid_time);
                        }
                    }

                    if (fmid_sync)
                    {
                        if (ImGuiKnobs::KnobInt(
                            "Mid TimeSync", &fmid_timesync, 0, items_len-1, syncstep, timesync_list[fmid_timesync],
                            ImGuiKnobVariant_SteppedTick, hundred, ImGuiKnob_Flags, items_len))
                        {
                            if (ImGui::IsItemActivated())
                            {
                                editParameter(21, true);
                                if (ImGui::IsMouseDoubleClicked(0))
                                {
                                    fmid_timesync = default_item_id;
                                }
                            }
                            setParameterValue(21, fmid_timesync);
                        }
                    }
                    ImGui::SameLine();

                    ImGui::BeginGroup();
                    {
                        ImGui::Dummy(ImVec2(0.0f, 35.0f) * scaleFactor);

                        // knob
                        ImGui::PushStyleColor(ImGuiCol_Text,            (ImVec4)MidSyncSw);

                        // inactive colors
                        ImGui::PushStyleColor(ImGuiCol_FrameBg,         (ImVec4)MidSyncGr);
                        ImGui::PushStyleColor(ImGuiCol_FrameBgHovered,  (ImVec4)MidSyncGrHovered);

                        // active colors
                        ImGui::PushStyleColor(ImGuiCol_Button,          (ImVec4)MidSyncAct);
                        ImGui::PushStyleColor(ImGuiCol_ButtonHovered,   (ImVec4)MidSyncActHovered);
                        if (ImGui::Toggle("##Mid Sync", &fmid_sync, ImGuiToggleFlags_Animated))
                        {
                            if (ImGui::IsItemActivated())
                            {
                                editParameter(19, true);
                                setParameterValue(19, fmid_sync);
                            }
                        }
                        ImGui::PopStyleColor(5);
                    }
                    ImGui::EndGroup();
                    ImGui::SameLine();

                    if (ImGuiKnobs::Knob("Mid Feedback", &fmid_feedback, 0.0f, 100.0f, percstep, "%.1f%%", ImGuiKnobVariant_Space, hundred, ImGuiKnob_Flags))
                    {
                        if (ImGui::IsItemActivated())
                        {
                            editParameter(16, true);
                            if (ImGui::IsMouseDoubleClicked(0))
                                fmid_feedback = 25.0f;
                        }
                        setParameterValue(16, fmid_feedback);
                    }
                    ImGui::SameLine();

                    if (ImGuiKnobs::Knob("Mid Cross", &fmid_cross, 0.0f, 100.0f, percstep, "%.1f%%", ImGuiKnobVariant_SteppedTick, hundred, ImGuiKnob_Flags, 11))
                    {
                        if (ImGui::IsItemActivated())
                        {
                            editParameter(15, true);
                            if (ImGui::IsMouseDoubleClicked(0))
                                fmid_cross = 20.0f;
                        }
                        setParameterValue(15, fmid_cross);
                    }
                    ImGui::PopStyleColor(2);
                    ImGui::SameLine();

                    ImGui::PushStyleColor(ImGuiCol_ButtonActive,    (ImVec4)MidMixActive);
                    ImGui::PushStyleColor(ImGuiCol_ButtonHovered,   (ImVec4)MidMixHovered);
                    if (ImGuiKnobs::Knob("Mid Mix", &fmid_mix, 0.0f, 100.0f, percstep, "%.1f%%", ImGuiKnobVariant_SteppedTick, hundred, ImGuiKnob_Flags, 11))
                    {
                        if (ImGui::IsItemActivated())
                        {
                            editParameter(18, true);
                            if (ImGui::IsMouseDoubleClicked(0))
                                fmid_mix = 50.0f;
                        }
                        setParameterValue(18, fmid_mix);
                    }
                    ImGui::PopStyleColor(2);
                }
                ImGui::EndGroup();

                // Effect Headers
                ImGui::Dummy(ImVec2(0.0f, 23.0f) * scaleFactor);
                ImGui::BeginGroup();
                {
                    ImGui::PushStyleColor(ImGuiCol_Text, TextClr);
                    CenterTextX("Time", knobWidth); ImGui::SameLine();
                    CenterTextX("Sync", toggleWidth); ImGui::SameLine();
                    CenterTextX("Feedback", knobWidth); ImGui::SameLine();
                    CenterTextX("Cross", knobWidth); ImGui::SameLine();
                    CenterTextX("Mix", knobWidth);
                    ImGui::PopStyleColor();
                }
                ImGui::EndGroup();
                ImGui::Dummy(ImVec2(0.0f, 23.0f) * scaleFactor);

                // Low Band
                ImGui::BeginGroup();
                {
                    ImGui::PushStyleColor(ImGuiCol_ButtonActive,    (ImVec4)LowColorActive);
                    ImGui::PushStyleColor(ImGuiCol_ButtonHovered,   (ImVec4)LowColorHovered);
                    if (not flow_sync)
                    {
                        if (ImGuiKnobs::Knob(
                            "Low Time", &flow_time, 50.0f, 5000.0f, msstep, "%.0fms",
                            ImGuiKnobVariant_SteppedTick, hundred, ImGuiKnob_FlagsLog, 21))
                        {
                            if (ImGui::IsItemActivated())
                            {
                                editParameter(12, true);
                                if (ImGui::IsMouseDoubleClicked(0))
                                    flow_time = 500.0f;
                            }
                            setParameterValue(12, flow_time);
                        }
                    }

                    if (flow_sync)
                    {
                        if (ImGuiKnobs::KnobInt(
                            "Low TimeSync", &flow_timesync, 0, items_len-1, syncstep, timesync_list[flow_timesync],
                            ImGuiKnobVariant_SteppedTick, hundred, ImGuiKnob_Flags, items_len))
                        {
                            if (ImGui::IsItemActivated())
                            {
                                editParameter(13, true);
                                if (ImGui::IsMouseDoubleClicked(0))
                                {
                                    flow_timesync = default_item_id;
                                }
                            }
                            setParameterValue(13, flow_timesync);
                        }
                    }
                    ImGui::SameLine();

                    ImGui::BeginGroup();
                    {
                        ImGui::Dummy(ImVec2(0.0f, 35.0f) * scaleFactor);

                        // knob
                        ImGui::PushStyleColor(ImGuiCol_Text,            (ImVec4)LowSyncSw);

                        // inactive colors
                        ImGui::PushStyleColor(ImGuiCol_FrameBg,         (ImVec4)LowSyncGr);
                        ImGui::PushStyleColor(ImGuiCol_FrameBgHovered,  (ImVec4)LowSyncGrHovered);

                        // active colors
                        ImGui::PushStyleColor(ImGuiCol_Button,          (ImVec4)LowSyncAct);
                        ImGui::PushStyleColor(ImGuiCol_ButtonHovered,   (ImVec4)LowSyncActHovered);
                        if (ImGui::Toggle("##Low Sync", &flow_sync, ImGuiToggleFlags_Animated))
                        {
                            if (ImGui::IsItemActivated())
                            {
                                editParameter(11, true);
                                setParameterValue(11, flow_sync);
                            }
                        }
                        ImGui::PopStyleColor(5);
                    }
                    ImGui::EndGroup();
                    ImGui::SameLine();

                    if (ImGuiKnobs::Knob("Low Feedback", &flow_feedback, 0.0f, 100.0f, percstep, "%.1f%%", ImGuiKnobVariant_Space, hundred, ImGuiKnob_Flags))
                    {
                        if (ImGui::IsItemActivated())
                        {
                            editParameter(9, true);
                            if (ImGui::IsMouseDoubleClicked(0))
                                flow_feedback = 25.0f;

                        }
                        setParameterValue(9, flow_feedback);
                    }
                    ImGui::SameLine();

                    if (ImGuiKnobs::Knob("Low Cross", &flow_cross, 0.0f, 100.0f, percstep, "%.1f%%", ImGuiKnobVariant_SteppedTick, hundred, ImGuiKnob_Flags, 11))
                    {
                        if (ImGui::IsItemActivated())
                        {
                            editParameter(8, true);
                            if (ImGui::IsMouseDoubleClicked(0))
                                flow_cross = 20.0f;
                        }
                        setParameterValue(8, flow_cross);
                    }
                    ImGui::PopStyleColor(2);
                    ImGui::SameLine();

                    ImGui::PushStyleColor(ImGuiCol_ButtonActive,    (ImVec4)LowMixActive);
                    ImGui::PushStyleColor(ImGuiCol_ButtonHovered,   (ImVec4)LowMixHovered);
                    if (ImGuiKnobs::Knob("Low Mix", &flow_mix, 0.0f, 100.0f, percstep, "%.1f%%", ImGuiKnobVariant_SteppedTick, hundred, ImGuiKnob_Flags, 11))
                    {
                        if (ImGui::IsItemActivated())
                        {
                            editParameter(10, true);
                            if (ImGui::IsMouseDoubleClicked(0))
                                flow_mix = 50.0f;
                        }
                        setParameterValue(10, flow_mix);
                    }
                    ImGui::PopStyleColor(2);
                }
                ImGui::EndGroup();
            }
            ImGui::EndGroup();

            if (ImGui::IsItemDeactivated())
            {
                editParameter(0, false);
                editParameter(1, false);
                editParameter(2, false);
                editParameter(3, false);
                editParameter(4, false);
                editParameter(5, false);
                editParameter(6, false);
                editParameter(7, false);
                editParameter(8, false);
                editParameter(9, false);
                editParameter(10, false);
                editParameter(11, false);
                editParameter(12, false);
                editParameter(13, false);
                editParameter(14, false);
                editParameter(15, false);
                editParameter(16, false);
                editParameter(17, false);
                editParameter(18, false);
                editParameter(19, false);
                editParameter(20, false);
                editParameter(21, false);
            }

            ImGui::PopFont();
        }
        ImGui::PopFont();
        ImGui::End();
    }

    DISTRHO_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ImGuiPluginUI)
};

// --------------------------------------------------------------------------------------------------------------------

UI* createUI()
{
    return new ImGuiPluginUI();
}

// --------------------------------------------------------------------------------------------------------------------

END_NAMESPACE_DISTRHO
