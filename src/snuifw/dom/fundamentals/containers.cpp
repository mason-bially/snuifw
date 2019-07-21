#include "containers.h"

using namespace snuifw;

VTile::VTile()
{
    _layout.flags = LayoutDescription::HasLayoutCalculator;
}

void VTile::draw(SkCanvas* canvas)
{
    canvas->drawColor(SkColorSetARGB(255, 255, 255, 255));
}
