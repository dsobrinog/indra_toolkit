#include "indra_toolkit/modules/ExecutiveSelector.h"
#include "indra_toolkit/ToolApplication.h"

#include <dirent.h>
#include <fstream>

#include "indra_toolkit/widgets/containers/HorizontalContainer.h"
#include "indra_toolkit/widgets/ButtonWidget.h"
#include "indra_toolkit/widgets/ComboBoxWidget.h"

namespace indra_toolkit
{
    bool ExecutiveSelector::OnInit()
    {
        original_wnd_size = tool_app->GetMainWindowSize(); 
        int numOfExec = GetRunningExecutives().size();
        if(numOfExec <= 1)
        {
            return true;
        }

        tool_app->ChangeAppTitle(name_of_selector_window);
        tool_app->SetMinWindowSize(400, 60);
        tool_app->SetWindowSize(400, 60);

        interactive_layer = tool_app->RegisterLayerPtr<indra_toolkit::InteractiveLayer>(tool_app);
        const ImVec4 interactive_bg(1.f, 0.3f, 0.3f, 1.f);
        interactive_layer->SetBackgroundColor(ImVec4 (0.f, 0.f, 0.f, 1.f));
        interactive_layer->SetSize(tool_app->GetMainWindowSize());
        interactive_layer->SetName("Executive Selector Layer");
        interactive_layer->SetWindowPadding({0.f, 0.f});
        interactive_layer->SetWindowFlags(ImGuiWindowFlags_NoTitleBar 
                                              | ImGuiWindowFlags_NoResize 
                                              | ImGuiWindowFlags_NoMove 
                                              | ImGuiWindowFlags_NoCollapse 
                                              | ImGuiWindowFlags_NoBringToFrontOnFocus
                                              | ImGuiWindowFlags_NoScrollbar);

        auto& horizontalContainer = interactive_layer->CreateWidget<HorizontalContainer>();
        horizontalContainer.SetBehaviourModes(indra_toolkit::UIBehaviourMode::Relative, indra_toolkit::UIBehaviourMode::Relative);
        horizontalContainer.SetWidgetName("Selector");
        horizontalContainer.SetSize({400.f, 60.f});
        horizontalContainer.SetWidgetStyle(indra_toolkit::UIStyleFlags::BackgroundColor | indra_toolkit::UIStyleFlags::Padding);
        horizontalContainer.SetBackgroundColor({0.f, 0.f, 0.f, 1.f});
        // horizontalContainer.SetBackgroundColor({0.2f, 0.2f, 0.2f, 1.f});
        horizontalContainer.SetWindowPadding({0, 0});
        
        CreateExecutiveComboBox(GetRunningExecutives());

        horizontalContainer.AddChild(combo_box);

            
        indra_toolkit::PositionVars buttonPosVars;
        buttonPosVars.PosMode = indra_toolkit::UIBehaviourMode::Relative;
        buttonPosVars.SizeMode = indra_toolkit::UIBehaviourMode::Relative;
        buttonPosVars.Size = {150.f, 20.f};
        buttonPosVars.VerticalAlign = indra_toolkit::UIVerticaAlignment::Center;
        buttonPosVars.HorizontalAlign = indra_toolkit::UIHorizontalAlignment::Middle;
        buttonPosVars.Position = { 75.f, 0.f};

        ImVec4 botton_background_color = ImVec4(0.3,0.3,0.3,1.f);

        // BUTTON
        ButtonWidget* confirm_button = new ButtonWidget("Confirm Selection", [this]()
            {
                std::cout << "Confirm Button Select" << std::endl;
                OnConfirmButtonPressed();
            },
            buttonPosVars,
            "Play Button"
        );
        confirm_button->SetBgColor(botton_background_color);

        horizontalContainer.AddChild(confirm_button);

        return true;
    }

    void ExecutiveSelector::CreateExecutiveComboBox(const std::vector<int>& runningExecutivesIDs)
    {
        std::vector<std::string> existingExecIds;

        for(const int& id : runningExecutivesIDs)
        {
            existingExecIds.push_back(std::to_string(id));
        }

        combo_box = new ComboBoxWidget();
        combo_box->SetOptions(existingExecIds);
        combo_box->SetLabel("Select an executive");
        combo_box->SetBehaviourModes(indra_toolkit::UIBehaviourMode::Relative, indra_toolkit::UIBehaviourMode::Relative);
        combo_box->SetSize({150.f, 20.f});
        combo_box->SetVerticalAlignment(indra_toolkit::UIVerticaAlignment::Center);
        combo_box->SetHorizontalAlignment(indra_toolkit::UIHorizontalAlignment::Middle);
        combo_box->SetPosition({ -75.f, 0.f});
    }

    void ExecutiveSelector::OnConfirmButtonPressed()
    {
        if(!combo_box) return;

        std::string selectedExecutiveID = combo_box->GetSelectedItem();
        int execID = atoi(selectedExecutiveID.c_str());
        on_exec_selected(execID); 
    }

    void ExecutiveSelector::OnShutdown()
    {
        tool_app->SetMinWindowSize(original_wnd_size.x, original_wnd_size.y);
        tool_app->SetWindowSize(original_wnd_size.x, original_wnd_size.y);

        if(!interactive_layer) return;
        
        tool_app->UnregisterLayer(interactive_layer);
    }
}

// Executive Proc
std::vector<int> indra_toolkit::ExecutiveSelector::GetRunningExecutives()
{
    std::vector<int> running_executives;

#if defined(unix) || defined(__unix__) || defined(__unix)
    std::vector<st_proc_info> executives_proc = ReadRunningExecutivesProc();
    for (size_t i = 0; i < executives_proc.size(); i++)
    {
        running_executives.push_back(executives_proc[i].pid); 
    }
#endif

    return running_executives;
}

#if defined(unix) || defined(__unix__) || defined(__unix)

std::vector<indra_toolkit::st_proc_info> indra_toolkit::ExecutiveSelector::ReadRunningExecutivesProc()
{
    const std::string PATH = "/proc";

    std::vector<st_proc_info> executives_proc;

    DIR *dir = opendir(PATH.c_str());

    struct dirent *entry = readdir(dir);

    while (entry != NULL)
    {
        entry = readdir(dir);

        if (!entry)
            break;

        if (entry->d_type != DT_DIR)
            continue;

        std::string directory_name = entry->d_name;
        if (directory_name.find_first_not_of("0123456789") == std::string::npos)
        {
            st_proc_info proc_info = ReadProcInfo(PATH + "/" + directory_name + "/stat");
            if (proc_info.comm == "(executive)")
            {
                executives_proc.push_back(proc_info);
            }
        }
    }

    closedir(dir);

    return executives_proc;
}

indra_toolkit::st_proc_info indra_toolkit::ExecutiveSelector::ReadProcInfo(std::string path)
{
    st_proc_info proc_info;

    std::ifstream in(path);

    in  >> proc_info.pid
        >> proc_info.comm
        >> proc_info.state
        >> proc_info.ppid
        >> proc_info.pgrp
        >> proc_info.session
        >> proc_info.tty_nr
        >> proc_info.tpgid
        >> proc_info.flags
        >> proc_info.minflt
        >> proc_info.cminflt
        >> proc_info.majflt
        >> proc_info.cmajflt
        >> proc_info.utime
        >> proc_info.stime
        >> proc_info.cutime
        >> proc_info.cstime
        >> proc_info.priority
        >> proc_info.nice
        >> proc_info.num_threads
        >> proc_info.itrealvalue
        >> proc_info.startime
        >> proc_info.vsize
        >> proc_info.rss
        >> proc_info.rsslim
        >> proc_info.startcode
        >> proc_info.endcode
        >> proc_info.startstack
        >> proc_info.kstkesp
        >> proc_info.kstkeip
        >> proc_info.signal
        >> proc_info.blocked
        >> proc_info.sigignore
        >> proc_info.sigcatch
        >> proc_info.wchan
        >> proc_info.nswap
        >> proc_info.cnswap
        >> proc_info.exit_signal
        >> proc_info.processor
        >> proc_info.rt_priority
        >> proc_info.policy
        >> proc_info.delayacct_blkio_ticks
        >> proc_info.guest_time
        >> proc_info.cguest_time;

    return proc_info;
}
#endif

