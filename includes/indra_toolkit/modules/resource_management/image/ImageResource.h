#pragma once

#include "modules/resource_management/IResource.h"
#include <GL/gl.h>

#pragma once

namespace indra_toolkit
{
    class ImageResource : IResource
    {
    public:
        unsigned int texID = 0;
        virtual void Release() override
        {
            if (texID)
            {
                glDeleteTextures(1, &texID);
                texID = 0;
            }
        };
    };
}
