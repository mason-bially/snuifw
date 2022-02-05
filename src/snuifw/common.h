#pragma once

#include <memory>
#include <stdexcept>
#include <variant>
#include <optional>
#include <algorithm>
#include <deque>
#include <vector>

#include <cassert>

#include "GLFW/glfw3.h"

#define SK_GL
#include "include/gpu/GrBackendSurface.h"
#include "include/gpu/GrDirectContext.h"
#include "include/gpu/gl/GrGLInterface.h"
#include "include/core/SkPaint.h"
#include "include/core/SkCanvas.h"
#include "include/core/SkColorSpace.h"
#include "include/core/SkSurface.h"
#include "include/core/SkRect.h"
#include "include/core/SkFont.h"
#include "include/core/SkFontMetrics.h"

#include "snuifw/util/type.hpp"
