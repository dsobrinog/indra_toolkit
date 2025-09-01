#pragma once

#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>

#include "Module.h"
#include "Layer.h"
#include "comms/IClient.h"


#include "comms/comms_def.h"
#include "comms/IWorkerTask.h"


#include <vector>
#include <memory>
#include <string>

namespace indra_toolkit
{
    enum ApplicationState
    {
        NONE = 0,
        INIT = 1,
        ACTIVE = 2,
        CLOSE = 3
    };

    // Forward declared
    class WorkerThread;

    class ToolApplication
    {
    public:
        ToolApplication();
        ToolApplication(const std::string& appname);
        ToolApplication(const std::string& appname, int width, int height);
        ToolApplication(const std::string& appname, int width, int height, int minAllowedWidth, int minAllowedHeight);

        ~ToolApplication();

        // --------------------------
        // LIFE CYCLE
        // --------------------------

        bool Initialize();
        bool OpenCommsThread(std::unique_ptr<IWorkerTask> workerTask);

        void Update();

        void Shutdown(); 
        
        virtual void OnInit() = 0;
        virtual void OnEnd() = 0;

        bool IsActive();
        void QuitApplication();


        // --------------------------
        // ENVIRONMENT
        // --------------------------
        
        inline const int GetExecutivePID(){ return executive_pid; }
        inline void SetExecutivePID(int pid){ executive_pid = pid; }

        // --------------------------
        // ENVIRONMENT
        // --------------------------
  
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

        void ChangeAppTitle(const std::string& appName);
        void SetWindowSize(const int inWidth, const int inHeight);
        void ClampOSWindowResize(bool state);

        // --------------------------
        // COMMS CONFIGURATION
        // --------------------------

        std::unique_ptr<IClient> client;
        std::unique_ptr<indra_toolkit::IClient> CreateClient(const NetworkConfiguration& config);
        

        /// @brief Set IP and port configuration for networking
        /// @param config 
        inline void SetNetworkConfiguration(NetworkConfiguration& config){ network_config = config; }
        inline const std::string& GetIP(){ return network_config.ip; }
        inline const std::string& GetPort(){ return network_config.port; }
    
    protected:
        NetworkConfiguration network_config;

    private:
        // Initialization
        bool InitGLFW();
        bool InitOpenGL();
        bool InitImGui();
        bool InitCommsWorker();

        // Signals catching
        void SetupSignalHandlers();
        static void SignalHandler(int sig);

        std::vector<std::unique_ptr<Layer>> _layers;
        std::vector<Module*> _modules;
        std::unique_ptr<WorkerThread> worker_comms;
        std::unique_ptr<IWorkerTask> comms_task;


        GLFWwindow* _window = nullptr;
        std::string _appname = "Default App";
        int executive_pid = -1;


        ApplicationState app_state = NONE;

        // glfw window size
        int _width = 685;
        int _height = 315;

        int _minWidth = 685;
        int _minHeight = 315;

        bool _clampOSWindowResize = false;

        // glfw resize callback
        static void FramebufferSizeCallback(GLFWwindow* window, int width, int height);
    };

   
}