#include "dom.h"

using namespace snuifw;

DomContext::DomContext(SkSurface* surface)
    : _surface(surface)
{

}

std::shared_ptr<IElement> DomContext::getRoot()
{
    return _root;
}

void DomContext::setRoot(std::shared_ptr<IElement> i)
{
    _root = i;
}

void DomContext::_shadowRender(ShadowDom& shadow, std::shared_ptr<IElement> const& elem)
{
    shadow.shadowStack.push_front(elem);

    while(!shadow.front()->isFundamental())
    {
        auto comp = std::static_pointer_cast<IComponent>(shadow.front());
        shadow.shadowStack.push_front(comp->render());
    }

    auto children = shadow.front()->children();
    if (children != nullptr)
    {
        auto size = children->size();
        shadow.shadowChildren.resize(size);
        for (auto i = 0; i < size; ++i)
        {
            _shadowRender(shadow.shadowChildren.at(i), children->at(i));
        }
    }
}

void DomContext::_shadowDraw(SkCanvas* canvas, ShadowDom const& d)
{
    canvas->save();
    d.getFundamental()->draw(canvas);
    canvas->restore();

    for (auto cit = d.shadowChildren.cbegin(); cit != d.shadowChildren.cend(); ++cit)
    {
        _shadowDraw(canvas, *cit);
    }
}

void DomContext::render()
{
    _shadow = {};
    _shadowRender(_shadow, _root);

    SkCanvas* canvas = _surface->getCanvas();
    canvas->drawColor(SkColorSetARGB(255, 127, 127, 127));
    _shadowDraw(canvas, _shadow);
    canvas->flush();
}
