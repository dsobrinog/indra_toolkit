#include "indra_toolkit/ToolApplication.h"

#include <execinfo.h>  // For backtrace
#include <unistd.h>    // For STDERR_FILENO

#include <algorithm>

#include "comms/WorkerThread.h"
#include <comms/clients/RpcClient.h>
#include <indra_toolkit/Utils.h>


using namespace indra_toolkit;

// Initialization

indra_toolkit::ToolApplication::ToolApplication(const std::string& app_name_): app_name(app_name_)
{ 
    SetupSignalHandlers();
}

indra_toolkit::ToolApplication::ToolApplication(const std::string& app_name_, int width_, int height_)
: app_name(app_name_), wnd_width(width_), wnd_height(height_) 
{ 
    SetupSignalHandlers();
}

indra_toolkit::ToolApplication::ToolApplication(const std::string& app_name_, int width_, int height_, int min_allowed_width_, int min_allowed_height_)
: app_name(app_name_), wnd_width(width_), wnd_height(height_), wnd_min_width(min_allowed_width_), wnd_min_height(min_allowed_height_)
{ 
    SetupSignalHandlers();
}

indra_toolkit::ToolApplication::~ToolApplication()
{
  
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

    //Inicializacion de modulos
    if(!InitModules())
    {
        std::cout << "Initializing Modules Failed! " << std::endl;
        return false;
    }

    OnInit();

    app_state = ApplicationState::ACTIVE;
    return true;
}

bool ToolApplication::OpenCommsThread(std::unique_ptr<IWorkerTaskBase> worker_task_)
{
    // Validate input
    if (!worker_task_) {
        throw std::runtime_error("Communications task cannot be null");
    }

    try {
        worker_comms = std::make_unique<WorkerThread>(std::move(worker_task_));
        worker_comms->Start();
        
        std::cout << "Initialized Comms Worker" << std::endl;
        return true;
    }
    catch (const std::exception& e) {
        std::cerr << "Failed to open comms thread: " << e.what() << std::endl;
        throw;
    }   
}

std::unique_ptr<indra_toolkit::IClient> indra_toolkit::ToolApplication::CreateClient(const NetworkConfiguration& config_)
{
    switch (config_.lib)
    {
    case RPC:
        return std::make_unique<indra_toolkit::RpcClient>(config_);
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

    window = glfwCreateWindow(wnd_width, wnd_height, app_name.c_str(), NULL, NULL);
    if (!window) return false;

    glfwMakeContextCurrent(window);           
    glfwSwapInterval(1);    // V Sync

    glfwSetWindowUserPointer(window, this);
    glfwSetFramebufferSizeCallback(window, FramebufferSizeCallback);   // Resize Callback

    // DPI scaling
    glfwSetWindowContentScaleCallback(window, [](GLFWwindow* window, float xscale, float yscale) {
        auto* app = static_cast<ToolApplication*>(glfwGetWindowUserPointer(window));
        ImGuiIO& io = ImGui::GetIO();
        io.DisplayFramebufferScale = ImVec2(xscale, yscale);
        std::cout << "DPI Scale changed: " << xscale << "x" << yscale << std::endl;
    });

    std::cout << "Initialize GLFW" << std::endl;
    return true;
}

void ToolApplication::FramebufferSizeCallback(GLFWwindow* window_, int width_, int height_)
{
    auto* app = static_cast<ToolApplication*>(glfwGetWindowUserPointer(window_));

    width_ = std::max(width_, app->wnd_min_width);
    height_ = std::max(height_, app->wnd_min_height);
    
    app->wnd_width = width_;
    app->wnd_height = height_;

    glViewport(0, 0, width_, height_);
    
    // Forzar update de escala
    float xscale, yscale;
    glfwGetWindowContentScale(window_, &xscale, &yscale);
    ImGui::GetIO().DisplayFramebufferScale = ImVec2(xscale, yscale);
}

void ToolApplication::SetWindowSize(const int in_width_, const int in_height_)
{
    glfwSetWindowSize(window, in_width_, in_height_);
}

void ToolApplication::SetMinWindowSize(const int in_min_width_, const int in_min_height_)
{
    wnd_min_width = in_min_width_;
    wnd_min_height = in_min_height_;
}

void ToolApplication::ClampOSWindowResize(bool state_)
{
    clamp_OS_Window_Resize = state_;
}

bool ToolApplication::InitImGui()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();

    io.MouseDrawCursor = false;

    float xscale, yscale;
    glfwGetWindowContentScale(window, &xscale, &yscale);
    io.DisplayFramebufferScale = ImVec2(xscale, yscale);

    // Apply configuration flags
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    //io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // IF using Docking Branch
    io.ConfigFlags |= ImGuiConfigFlags_NoMouseCursorChange;
    ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_NoMouseCursorChange;
    ImGui::StyleColorsDark();
    std::cout << "Initialize ImGui" << std::endl;
    return true;
}

bool ToolApplication::InitOpenGL()
{
    bool success = ImGui_ImplGlfw_InitForOpenGL(window, true) && ImGui_ImplOpenGL3_Init("#version 330");
    std::cout << "Initialize OpenGL" << std::endl;
    return success;
}

bool ToolApplication::InitModules()
{
    bool initAllModules = true;
    for (auto& module : module_map)
    {
        if(!module.second->OnInit())
            initAllModules = false;
    }

    return initAllModules;
}

// Update
void ToolApplication::Update()
{
    glfwPollEvents();

    for(auto& module : module_map)
    {
        module.second->OnUpdate();
    }

    // New Frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    // Process data from layers
    for (auto& layer :layers){
        // std::cout << "Process layer at: " << layer->GetName() << std::endl;
        layer->OnProcess();
    }
    
    int display_w, display_h;
    glfwGetFramebufferSize(window, &display_w, &display_h);
    int desiredWidth = clamp(display_w, wnd_min_width, wnd_width);
    int desiredHeight = clamp(display_h, wnd_min_height, wnd_height);

    if(clamp_OS_Window_Resize && (display_w < wnd_min_width || display_h < wnd_min_height))
        glfwSetWindowSize(window, desiredWidth, desiredHeight); 

    glViewport(0, 0, desiredWidth, desiredHeight);

    // Render view
    for (auto& layer :layers)
    {
        layer->OnRender();
    }

    for(Layer* layerToRemove : layers_to_remove)
    {
        auto it = std::find_if(layers.begin(), layers.end(),
            [layerToRemove](const std::unique_ptr<Layer>& l) { return l.get() == layerToRemove; });

        if (it != layers.end())
        {
            layers.erase(it); // erases and destroys the layer
        }
    }
    layers_to_remove.clear();
    
    // ImGui::ShowMetricsWindow();
    // ImGui::ShowStyleEditor();

    // Render OpenGL
    ImGui::Render();

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    
    glfwSwapBuffers(window);
}

bool indra_toolkit::ToolApplication::IsActive()
{
    return app_state != ApplicationState::ACTIVE || !glfwWindowShouldClose(window);
}

void indra_toolkit::ToolApplication::QuitApplication()
{
    app_state = ApplicationState::CLOSE;
}

void indra_toolkit::ToolApplication::ChangeAppTitle(const std::string& app_name_)
{
    app_name = app_name_;
    glfwSetWindowTitle(window, app_name.c_str());
}

void ToolApplication::Shutdown()
{
    if(worker_comms)
        worker_comms->Stop();

    EndModules();
    OnEnd();
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(window);
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

void indra_toolkit::ToolApplication::SignalHandler(int sig_)
{
    void* array[20];  // Increased stack trace depth
    size_t size;

    // Get void*'s for all entries on the stack
    size = backtrace(array, 20);

    // Print out the stack trace
    std::cerr << "\n=== SEGMENTATION FAULT DETECTED ===\n";
    std::cerr << "Error: signal " << sig_ << " (";
    
    switch(sig_) {
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

void ToolApplication::UnregisterLayer(Layer* layer_)
{
    layers_to_remove.push_back(layer_); 
}

void ToolApplication::EndModules()
{
    for (auto& module : module_map)
    {
        module.second->OnShutdown();
    }

    module_map.clear();
}
