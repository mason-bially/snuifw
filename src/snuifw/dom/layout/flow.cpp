#include "flow.h"

using namespace snuifw;

template<bool IsVertical>
_details::Flow<IsVertical>::Flow()
{
    _layout.flags = LayoutDescription::HasLayoutCalculator;
}

template<bool IsVertical>
void _details::Flow<IsVertical>::draw(DrawContext& ctx, LayoutResult const& layout) const
{
    
}

template class _details::Flow<true>;
template class _details::Flow<false>;
