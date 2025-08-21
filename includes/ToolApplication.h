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
    class ToolApplication
    {
    public:
        ToolApplication(const std::string& appname);

        bool Initialize();
        void Update();
        void Shutdown(); 
        
        virtual void OnInit(){};
        virtual void OnEnd(){};
 
        Layer* RegisterLayer(Layer* layer);
        void UnregisterLayer(Layer* layer);
        inline Layer* GetLayer(int index){ return _layers[index].get();}

        void RegisterModule(Module* module);

        bool IsExecuting();

        inline const ImVec2 GetSize() { return ImVec2((float)_width, (float)_height); } 

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
        bool executing = false;

        // main glfw size
        int _width = 685;
        int _height = 315;

        // glfw resize callback
        static void FramebufferSizeCallback(GLFWwindow* window, int width, int height);
    };
}