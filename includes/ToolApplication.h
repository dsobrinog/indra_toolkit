#pragma once

#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>

#include "Module.h"
#include "Layer.h"

#include "comms/WorkerThread.h"
#include "comms/DataChannel.h"

#include <vector>
#include <memory>
#include <string>

namespace indra_toolkit
{
    struct NetworkConfiguration
    {
        std::string ip = "127.0.0.1";
        std::string port = "5556";
    };

    enum ApplicationState
    {
        NONE = 0,
        INIT = 1,
        ACTIVE = 2,
        CLOSE = 3
    };

    struct st_proc_info;

    class ToolApplication
    {
    public:
        ToolApplication();
        ToolApplication(const std::string& appname);
        ToolApplication(const std::string& appname, int width, int height);

        // --------------------------
        // LIFE CYCLE
        // --------------------------

        bool Initialize();
        void Update();
        void Shutdown(); 
        
        virtual void OnInit() {};
        virtual void OnEnd() {};

        bool IsActive();
        void QuitApplication();

        // --------------------------
        // ENVIRONMENT
        // --------------------------
        
        inline int GetExecutivePID(){ return executivePid; }
        inline void SetExecutivePID(int pid){ executivePid = pid; }
  

        // --------------------------
        // LAYER MANAGEMENT
        // --------------------------

        Layer* RegisterLayer(Layer* layer);
        void UnregisterLayer(Layer* layer);
        inline Layer* GetLayer(int index){ return _layers[index].get();}

        // --------------------------
        // MODULES MANAGEMENT
        // --------------------------

        void RegisterModule(Module* module);

        /// @brief Get module by name, if not found returns nullptr
        Module* GetModuleByName(const std::string& module_name);

        
        /// @brief Get module by type, if not found returns nullptr
        template <typename T>
        T* GetModule()
        {
            for (auto* module : _modules)
            {
                if (auto derived = dynamic_cast<T*>(module))
                    return derived;
            }
            return nullptr;
        }

        // --------------------------
        // GLFW WINDOW
        // --------------------------

        /// @brief Get size of GLFW window
        /// @return 
        inline const ImVec2 GetMainWindowSize() { return ImVec2((float)_width, (float)_height); } 

        // --------------------------
        // NETWORK CONFIGURATION
        // --------------------------

        /// @brief Set IP and port configuration for networking
        /// @param config 
        inline void SetNetworkConfiguration(NetworkConfiguration& config){ network_config = config; }
        inline const std::string& GetIP(){ return network_config.ip; }
        inline const std::string& GetPort(){ return network_config.port; }


    private:
        bool InitGLFW();
        bool InitOpenGL();
        bool InitImGui();
        bool InitCommsWorker();

        std::vector<std::unique_ptr<Layer>> _layers;
        std::vector<Module*> _modules;
        WorkerThread* worker_comms;
        DataChannel channel;

        GLFWwindow* _window = nullptr;
        std::string _appname = "Default App";

        ApplicationState app_state = NONE;
        int executivePid = -1;

        NetworkConfiguration network_config;

        // glfw window size
        int _width = 685;
        int _height = 315;

        // glfw resize callback
        static void FramebufferSizeCallback(GLFWwindow* window, int width, int height);
    };

   
}