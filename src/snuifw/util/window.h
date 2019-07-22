#pragma once
#include "snuifw/common.h"

namespace snuifw {
namespace util
{
    struct WindowEvents {
        GLFWwindowposfun onPosition;
        GLFWwindowsizefun onResize;
        GLFWwindowclosefun onClose;
        GLFWwindowrefreshfun onRefresh;
        GLFWwindowfocusfun onFocus;
        GLFWwindowiconifyfun onIconify;
        GLFWwindowmaximizefun onMaximize;
        GLFWframebuffersizefun onFramebuffer;
        GLFWwindowcontentscalefun onContentScale;

        inline WindowEvents operator<<(WindowEvents rhs) const
        {
            WindowEvents lhs = *this;
            WindowEvents res;

            res.onPosition = (lhs.onPosition) ?  lhs.onPosition: rhs.onPosition;
            res.onResize = (lhs.onResize) ? lhs.onResize: rhs.onResize;
            res.onClose = (lhs.onClose) ? lhs.onClose: rhs.onClose;
            res.onRefresh = (lhs.onRefresh) ? lhs.onRefresh: rhs.onRefresh;
            res.onFocus = (lhs.onFocus) ? lhs.onFocus: rhs.onFocus;
            res.onIconify = (lhs.onIconify) ? lhs.onIconify: rhs.onIconify;
            res.onMaximize = (lhs.onMaximize) ? lhs.onMaximize: rhs.onMaximize;
            res.onFramebuffer = (lhs.onFramebuffer) ? lhs.onFramebuffer: rhs.onFramebuffer;
            res.onContentScale = (lhs.onContentScale) ? lhs.onContentScale: rhs.onContentScale;

            return res;
        }
    };


    class WindowContainer
    {
        GLFWwindow* _window;
        public:
            inline WindowContainer(GLFWwindow* window): _window(window) {};
            inline ~WindowContainer(){ if(_window){glfwDestroyWindow(_window);}}

            inline GLFWwindow* window() {return _window;}

            inline void fillWindowEvents(WindowEvents* e)
            {
                if (e->onPosition) glfwSetWindowPosCallback(_window, e->onPosition);
                if (e->onResize) glfwSetWindowSizeCallback(_window, e->onResize);
                if (e->onClose) glfwSetWindowCloseCallback(_window, e->onClose);
                if (e->onRefresh) glfwSetWindowRefreshCallback(_window, e->onRefresh);
                if (e->onFocus) glfwSetWindowFocusCallback(_window, e->onFocus);
                if (e->onIconify) glfwSetWindowIconifyCallback(_window, e->onIconify);
                if (e->onMaximize) glfwSetWindowMaximizeCallback(_window, e->onMaximize);
                if (e->onFramebuffer) glfwSetFramebufferSizeCallback(_window, e->onFramebuffer);
                if (e->onContentScale) glfwSetWindowContentScaleCallback(_window, e->onContentScale);
            }
    }; 
}}