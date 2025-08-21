#pragma once
#include <string>

namespace indra_toolkit
{
    class Module
    {
    public:
        Module(const std::string& name) : _name(name) {}
        virtual ~Module() = default;

        virtual bool OnInit() { return true; }
        virtual void OnUpdate() {}
        virtual void OnShutdown() {}

        inline const std::string& GetName() const { return _name; }

    protected:
        std::string _name;
    };
}
