#include "containers.h"

using namespace snuifw;

SkRect VTile::layout(SkRect const& container_bounds) const
{
    return container_bounds;
}

void VTile::draw(SkCanvas* canvas)
{
    canvas->drawColor(SkColorSetARGB(255, 255, 255, 255));
}