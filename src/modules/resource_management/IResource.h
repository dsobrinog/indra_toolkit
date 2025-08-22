#pragma once

namespace indra_toolkit
{
    class IResource
    {
    public:
        virtual ~IResource() {}
        virtual void Release() = 0;
    };
}