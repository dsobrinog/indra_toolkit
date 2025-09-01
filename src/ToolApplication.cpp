#include "ToolApplication.h"

#include <execinfo.h>  // For backtrace
#include <unistd.h>    // For STDERR_FILENO

#include <algorithm>

#include <comms/RpcClient.h>
#include <Utils.h>


using namespace indra_toolkit;

// Initialization

indra_toolkit::ToolApplication::ToolApplication(const std::string& appname): _appname(appname)
{ 
    SetupSignalHandlers();
}

indra_toolkit::ToolApplication::ToolApplication(const std::string& name, int width, int height)
: _appname(name), _width(width), _height(height) 
{ 
    SetupSignalHandlers();
}

indra_toolkit::ToolApplication::ToolApplication(const std::string& name, int width, int height, int minAllowedWidth, int minAllowedHeight)
: _appname(name), _width(width), _height(height), _minWidth(minAllowedWidth), _minHeight(minAllowedHeight)
{ 
    SetupSignalHandlers();
}

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

std::unique_ptr<indra_toolkit::IClient> indra_toolkit::ToolApplication::CreateClient(const NetworkConfiguration& config)
{
    switch (config.lib)
    {
    case RPC:
        return std::make_unique<indra_toolkit::RpcClient>(config);
    case ZMQ:
        std::cerr << "Not implemented" << std::endl;
        return nullptr;
    default:
        return nullptr;
    }
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

    if(width <= app->_minWidth) width = app->_minWidth;

    app->_width = width;

    if(height <= app->_minHeight) height = app->_minHeight;

    app->_height = height;

    std::cout << "W: " << width << "H: "  << height << std::endl;

    glViewport(0, 0, app->_width, app->_height);
}

void ToolApplication::SetWindowSize(const int inWidth, const int inHeight)
{
    glfwSetWindowSize(_window, inWidth, inHeight);
}

void ToolApplication::ClampOSWindowResize(bool state)
{
    _clampOSWindowResize = state;
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

bool ToolApplication::InitCommsWorker()
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
    
    int display_w, display_h;
    glfwGetFramebufferSize(_window, &display_w, &display_h);
    int desiredWidth = clamp(display_w, _minWidth, _width);
    int desiredHeight = clamp(display_h, _minHeight, _height);

    if(_clampOSWindowResize && (display_w < _minWidth || display_h < _minHeight))
        glfwSetWindowSize(_window, desiredWidth, desiredHeight); 

    glViewport(0, 0, desiredWidth, desiredHeight);

    // Render view
    for (auto& layer :_layers)
    {
        // std::cout << "Rendering layer at: " << layer->GetName() << std::endl;
        layer->OnRender();
    }
        

    // Render OpenGL
    ImGui::Render();
    
    // int display_w, display_h;
    // glfwGetFramebufferSize(_window, &display_w, &display_h);
    // glViewport(0, 0, display_w, display_h);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    
    glfwSwapBuffers(_window);
}

bool indra_toolkit::ToolApplication::IsActive()
{
    return app_state != ApplicationState::ACTIVE || !glfwWindowShouldClose(_window);
}

void indra_toolkit::ToolApplication::QuitApplication()
{
    app_state = ApplicationState::CLOSE;
}

void indra_toolkit::ToolApplication::ChangeAppTitle(const std::string& appName)
{
    _appname = appName;
    glfwSetWindowTitle(_window, _appname.c_str());
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

void indra_toolkit::ToolApplication::SetupSignalHandlers()
{
    signal(SIGSEGV, ToolApplication::SignalHandler);  // Segmentation fault
    signal(SIGABRT, ToolApplication::SignalHandler);  // Abort signal
    signal(SIGFPE, ToolApplication::SignalHandler);   // Floating point exception
    signal(SIGILL, ToolApplication::SignalHandler);   // Illegal instruction
    
    std::cout << "Signal handlers installed for crash detection\n";
}

void indra_toolkit::ToolApplication::SignalHandler(int sig)
{
    void* array[20];  // Increased stack trace depth
    size_t size;

    // Get void*'s for all entries on the stack
    size = backtrace(array, 20);

    // Print out the stack trace
    std::cerr << "\n=== SEGMENTATION FAULT DETECTED ===\n";
    std::cerr << "Error: signal " << sig << " (";
    
    switch(sig) {
        case SIGSEGV: std::cerr << "SIGSEGV - Segmentation Fault"; break;
        case SIGABRT: std::cerr << "SIGABRT - Abort Signal"; break;
        case SIGFPE: std::cerr << "SIGFPE - Floating Point Exception"; break;
        case SIGILL: std::cerr << "SIGILL - Illegal Instruction"; break;
        default: std::cerr << "Unknown Signal"; break;
    }
    
    std::cerr << ")\n";
    std::cerr << "Stack trace:\n";
    
    backtrace_symbols_fd(array, size, STDERR_FILENO);
    std::cerr << "===================================\n";
    
    // Exit gracefully
    exit(1);
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
