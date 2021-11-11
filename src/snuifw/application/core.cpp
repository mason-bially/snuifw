#include "IApplicationLayer.h"
#include "IApplicationWindow.h"

using namespace snuifw;

std::map<std::string, _FrequireAppLayer> IApplicationLayer::_s_requires;

IApplicationLayer::~IApplicationLayer()
{

}

IApplicationWindow::~IApplicationWindow()
{

}

