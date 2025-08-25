#include "ToolApplication.h"

#include <algorithm>



using namespace indra_toolkit;

// Initialization

indra_toolkit::ToolApplication::ToolApplication(const std::string& appname): _appname(appname)
{ }

indra_toolkit::ToolApplication::ToolApplication(const std::string& name, int width, int height)
: _appname(name), _width(width), _height(height) 
{ }


bool ToolApplication::Initialize()
{
    app_state = ApplicationState::INIT;

    if(!InitGLFW())
    {
        std::cout << "GLFW Failed! " << std::endl;
        return false;
    }
    if(!InitImGui())
    {
        std::cout << "ImGui Failed! " << std::endl;
        return false;
    } 
    if(!InitOpenGL())
    {
        std::cout << "OpenGL Failed! " << std::endl;
        return false;
    } 

    InitCommsWorker();

    OnInit();

    app_state = ApplicationState::ACTIVE;
    return true;
}

bool ToolApplication::InitGLFW()
{
    if (!glfwInit()) {
        return false;
    }

    _window = glfwCreateWindow(_width, _height, _appname.c_str(), NULL, NULL);
    if (!_window) return false;
    glfwMakeContextCurrent(_window);           
    glfwSwapInterval(1);    // V Sync

    glfwSetWindowUserPointer(_window, this);
    glfwSetFramebufferSizeCallback(_window, FramebufferSizeCallback);   // Resize Callback

    std::cout << "Initialize GLFW" << std::endl;
    return true;
}

void ToolApplication::FramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    auto* app = static_cast<ToolApplication*>(glfwGetWindowUserPointer(window));
    app->_width = width;
    app->_height = height;

    std::cout << "W: " << width << "H: "  << height << std::endl;
}

bool ToolApplication::InitImGui()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();

    // Apply configuration flags
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    //io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // IF using Docking Branch
  

    ImGui::StyleColorsDark();
    std::cout << "Initialize ImGui" << std::endl;
    return true;
}

bool indra_toolkit::ToolApplication::InitCommsWorker()
{
    channel = DataChannel();
    worker_comms = new WorkerThread(&channel);
    worker_comms->Start();
    std::cout << "Initialize Comms Worker" << std::endl;
    return true;
}

bool ToolApplication::InitOpenGL()
{
    bool success = ImGui_ImplGlfw_InitForOpenGL(_window, true) && ImGui_ImplOpenGL3_Init("#version 330");
    std::cout << "Initialize OpenGL" << std::endl;
    return success;
}

// Update
void ToolApplication::Update()
{
    glfwPollEvents();

    // New Frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    // Process data from layers
    for (auto& layer :_layers){
        // std::cout << "Process layer at: " << layer->GetName() << std::endl;
        layer->OnProcess();
    }
    
    // Render view
    for (auto& layer :_layers)
    {
        // std::cout << "Rendering layer at: " << layer->GetName() << std::endl;
        layer->OnRender();
    }
        

    // Render OpenGL
    ImGui::Render();
    
    int display_w, display_h;
    glfwGetFramebufferSize(_window, &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    
    glfwSwapBuffers(_window);

    ImGuiIO& io = ImGui::GetIO();
    //std::cout << "FPS: " << io.Framerate << std::endl;
}

bool indra_toolkit::ToolApplication::IsActive()
{
    return app_state != ApplicationState::ACTIVE || !glfwWindowShouldClose(_window);
}

void indra_toolkit::ToolApplication::QuitApplication()
{
    app_state = ApplicationState::CLOSE;
}

void ToolApplication::Shutdown()
{
    OnEnd();
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(_window);
    glfwTerminate();
}


// Layers
Layer* ToolApplication::RegisterLayer(Layer* layer)
{
    _layers.push_back(std::unique_ptr<Layer>(layer));
    return layer; // non-owning pointer
}

void ToolApplication::UnregisterLayer(Layer* layer)
{
    auto it = std::find_if(_layers.begin(), _layers.end(),
        [layer](const std::unique_ptr<Layer>& l) { return l.get() == layer; });

    if (it != _layers.end())
    {
        _layers.erase(it); // erases and destroys the layer
    }
}


// Modules
void ToolApplication::RegisterModule(Module* module)
{
    if (module->OnInit())
    {
        _modules.push_back(module);
    }
}

Module* indra_toolkit::ToolApplication::GetModuleByName(const std::string& module_name)
{
    return nullptr;
}
