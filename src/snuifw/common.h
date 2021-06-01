#pragma once

#include <memory>
#include <variant>
#include <optional>
#include <algorithm>
#include <deque>
#include <vector>

#include "GLFW/glfw3.h"


#include "include/gpu/GrBackendSurface.h"
#include "include/gpu/GrContext.h"
#include "include/gpu/gl/GrGLInterface.h"
#include "include/core/SkPaint.h"
#include "include/core/SkCanvas.h"
#include "include/core/SkColorSpace.h"
#include "include/core/SkSurface.h"
#include "include/core/SkRect.h"
#include "include/core/SkFont.h"
#include "include/core/SkFontMetrics.h"
