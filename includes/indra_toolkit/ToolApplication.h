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

#include "CommonDefinitions.h"

#include <vector>
#include <map>
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
        ToolApplication(const std::string& app_name_);
        ToolApplication(const std::string& app_name_, int _width, int _height);
        ToolApplication(const std::string& app_name_, int _width, int _height, int _min_allowed_width, int _min_allowed_height);

        ~ToolApplication();

        // --------------------------
        // LIFE CYCLE
        // --------------------------

        bool Initialize();
        bool OpenCommsThread(std::unique_ptr<IWorkerTaskBase> worker_Task_);
        inline void SetCommsThreadFecuency(int miliseconds){ worker_frecuency = miliseconds; }

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
        inline void SetExecutivePID(int pid_){ executive_pid = pid_; }

        // --------------------------
        // ENVIRONMENT
        // --------------------------
  
        // --------------------------
        // LAYER MANAGEMENT
        // --------------------------

        /// @brief Create a layer in the ToolApp and return a reference to edit.
        /// @param args_ Constructor arguments
        /// @return reference to the module
        template<typename T, typename... Args>
        T& RegisterLayerRef(Args&&... args_)
        {
            static_assert(std::is_base_of<Layer, T>::value, 
                "T must derive from Layer");

            static_assert(std::is_constructible<T, Args...>::value,
                "ToolApplication::RegisterLayer: Wrong constructor arguments for layer type T");
            
            auto layer = std::make_unique<T>(std::forward<Args>(args_)...);
            T& ref = *layer;
            layers.push_back(std::move(layer));
            return ref;
        }

        /// @brief Create a layer in the ToolApp and return a reference to edit.
        /// @param args_ Constructor arguments
        /// @return reference to the module
        template<typename T, typename... Args>
        T* RegisterLayerPtr(Args&&... args_)
        {
            static_assert(std::is_base_of<Layer, T>::value, 
                "T must derive from Layer");

            static_assert(std::is_constructible<T, Args...>::value,
                "ToolApplication::RegisterLayer: Wrong constructor arguments for layer type T");
            
            auto layer = std::make_unique<T>(std::forward<Args>(args_)...);
            T& ref = *layer;
            layers.push_back(std::move(layer));
            return &ref; 
        }

        void UnregisterLayer(Layer* layer_);
        inline Layer* GetLayer(int index_){ return layers[index_].get();}

        // --------------------------
        // MODULES MANAGEMENT
        // --------------------------

        /// @brief Create a module in the ToolApp and return a reference to edit.
        /// @param _moduleEnum Identity of module
        /// @param _args Constructor arguments
        /// @return reference to the module
        template<typename T, typename... Args>
        T& RegisterModule(ToolModules module_enum_, Args&&... args_)
        {
            static_assert(std::is_base_of<Module, T>::value, 
                "T must derive from Module");
            
            static_assert(std::is_destructible<T>::value,
                "T must be destructible (needed by unique_ptr)");

            static_assert(!std::is_abstract<T>::value,
                "T must not be abstract (cannot instantiate abstract class)");
            static_assert(
                    std::is_constructible<T, ToolApplication*, ToolModules, Args...>::value,
                    "Wrong constructor arguments for module type T (must accept ToolApplication*, ToolModules, ...)"
                );
            
            auto it = module_map.find(module_enum_);
            if (it != module_map.end())
                throw std::runtime_error("Tried to register an already registered module");
            
            auto module = std::make_unique<T>(this, module_enum_, std::forward<Args>(args_)...);
            T& ref = *module;  // safe before moving
            module_map.emplace(module_enum_, std::move(module));
            return ref;
        }

        void UnregisterModule(ToolModules module_enum_)
        {
            auto it = module_map.find(module_enum_);
            if (it == module_map.end())
                throw std::runtime_error("tried to unregister a module that isn´t registered");

            it->second->OnShutdown();
            module_map.erase(module_enum_);
        }

        /// @brief Get module by type, if not found returns nullptr
        template <typename T>
        T& GetModule(const ToolModules& module_enum_)
        {
            static_assert(std::is_base_of<Module, T>::value, 
                "T must derive from Module");

            auto it = module_map.find(module_enum_);
            if (it == module_map.end())
                throw std::runtime_error("Module not found");

            auto derived = dynamic_cast<T*>(it->second.get());
            if (!derived)
                throw std::runtime_error("Module type mismatch");

            return *derived;
        }

        // --------------------------
        // GLFW WINDOW
        // --------------------------

        /// @brief Get size of GLFW window
        /// @return 
        inline const ImVec2 GetMainWindowSize() { return ImVec2((float)wnd_width, (float)wnd_height); } 

        void ChangeAppTitle(const std::string& app_name_);
        std::string GetAppName() const { return app_name; }
        void SetWindowSize(const int in_width_, const int in_height_);
        void SetMinWindowSize(const int in_min_width_, const int in_min_height_);
        void ClampOSWindowResize(bool state_);

        // --------------------------
        // COMMS CONFIGURATION
        // --------------------------

        std::unique_ptr<IClient> client;
        std::unique_ptr<indra_toolkit::IClient> CreateClient(const NetworkConfiguration& config_);
        

        /// @brief Set IP and port configuration for networking
        /// @param config 
        inline void SetNetworkConfiguration(NetworkConfiguration& config_){ network_config = config_; }
        inline const std::string& GetIP(){ return network_config.ip; }
        inline const std::string& GetPort(){ return network_config.port; }
        
        // --------------------------
        // DEBUG CONFIGURATION
        // --------------------------

        bool IsDebugEnabled() const { return draw_debug_info; }
        void DrawDebugInfo(bool state_) { draw_debug_info = state_; }

    protected:
        NetworkConfiguration network_config;

    private:
        // Initialization
        bool InitGLFW();
        bool InitOpenGL();
        bool InitImGui();
        bool InitCommsWorker();
        bool InitModules();
        void EndModules();

        // Signals catching
        void SetupSignalHandlers();
        static void SignalHandler(int sig_);

        // glfw resize callback
        static void FramebufferSizeCallback(GLFWwindow* window_, int width_, int height_);

        std::vector<std::unique_ptr<Layer>> layers;
        std::vector<Layer*> layers_to_remove;
        std::map<ToolModules, std::unique_ptr<Module>> module_map;

        std::unique_ptr<WorkerThread> worker_comms;
        int worker_frecuency = 10; //ms
        std::unique_ptr<IWorkerTaskBase> comms_task;

        GLFWwindow* window = nullptr;
        std::string app_name = "Default App";
        int executive_pid = -1;

        ApplicationState app_state = NONE;

        // glfw window size
        int wnd_width = 685;
        int wnd_height = 315;

        int wnd_min_width = 685;
        int wnd_min_height = 315;

        bool clamp_OS_Window_Resize = false;

        bool draw_debug_info = false;
    };
}