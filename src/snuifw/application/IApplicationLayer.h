
#include "internal.h"

namespace snuifw
{
    // application layers should use static space for their application
    // this layer represents the application layer and a window context to it
    class IApplicationLayer
    {
        protected:
            typedef std::shared_ptr<IApplicationLayer> (_FrequireAppLayer*)();
            static std::map<std::string, _FrequireAppLayer> _s_requires;

        public:
            ~IApplicationLayer();
        
        public:
            // allowed to be called multiple times
            virtual void init() = 0;

            virtual std::string implementationName() = 0;

            virtual std::shared_ptr<IApplicationWindow> makeWindow(std::string name, IApplicationWindow::WindowDescription initial) = 0;
    };
}
