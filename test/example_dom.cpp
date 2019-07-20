#include "GLFW/glfw3.h"

#include "include/gpu/GrBackendSurface.h"
#include "include/gpu/GrContext.h"
#include "include/gpu/gl/GrGLInterface.h"
#include "include/core/SkCanvas.h"
#include "include/core/SkColorSpace.h"
#include "include/core/SkSurface.h"

#include <stdio.h>
#include <stdlib.h>

#include "snuifw/snuifw.h"

using namespace snuifw;

//uncomment the two lines below to enable correct color spaces
//#define GL_FRAMEBUFFER_SRGB 0x8DB9
//#define GL_SRGB8_ALPHA8 0x8C43

void error_callback(int error, const char* description) {
	fputs(description, stderr);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}



int main(void) {
    Context c;
    c.init();

    auto dom = new snuifw::DomContext(c.sSurface);

    dom->setRoot(
        VTile() [
            VTile() [
                Text().value("hey"),
                Text().value("hey")
            ],
            Text().value("hey")
        ]);

	while (!glfwWindowShouldClose(c.window))
    {
		glfwWaitEvents();

		dom->render();

		glfwSwapBuffers(c.window);
	}

	exit(EXIT_SUCCESS);
}