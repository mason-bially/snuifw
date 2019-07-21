#include "dom.h"

using namespace snuifw;

DomRoot::DomRoot(Context* context)
    : _context(context)
{

}

std::shared_ptr<IElement> DomRoot::getRoot()
{
    return _root;
}

void DomRoot::setRoot(std::shared_ptr<IElement> i)
{
    _root = i;
}

void DomRoot::_shadowRender(ShadowDom& shadow, std::shared_ptr<IElement> const& elem)
{
    shadow.shadowStack.push_front(elem);

    while(!shadow.front()->isFundamental())
    {
        auto comp = std::static_pointer_cast<IComponent>(shadow.front());
        shadow.shadowStack.push_front(comp->render());
    }

    auto fundamental = shadow.getFundamental();
    auto children = fundamental->children();
    if (children != nullptr)
    {
        auto size = children->size();
        shadow.shadowChildren.resize(size);
        for (unsigned i = 0; i < size; ++i)
        {
            _shadowRender(shadow.shadowChildren.at(i), children->at(i));
        }
    }
}

void DomRoot::_shadowLayout(ShadowDom& shadow, SkRect* bounds)
{
    auto childCount = shadow.shadowChildren.size();
    if (childCount != 0)
    {
        auto fundamental = shadow.getFundamental();
        auto layouter = fundamental->layoutCalculator();
        if (layouter != nullptr)
        {
            SimpleLayoutEngine engine([&](auto index, SkRect* rect, bool preferWidth){
                ShadowDom& childShadow = shadow.shadowChildren.at(index);

                auto layoutDescription = childShadow.getFundamental()->layoutDescription();

                if ((layoutDescription.flags & LayoutDescription::UnboundedWidth) && (layoutDescription.flags & LayoutDescription::UnboundedHeight))
                {
                    this->_shadowLayout(childShadow, rect);
                    return true;
                }
                else if (rect->width() < layoutDescription.minWidth || rect->height() < layoutDescription.minHeight)
                {
                    childShadow.bounds = SkRect();
                    return false;
                }
                else if (layoutDescription.prefWidth != 0.f && layoutDescription.prefHeight != 0.f
                    && layoutDescription.prefWidth < rect->width() && layoutDescription.prefHeight < rect->height())
                {
                    rect->fRight = rect->fLeft + layoutDescription.prefWidth;
                    rect->fBottom = rect->fTop + layoutDescription.prefHeight;
                    this->_shadowLayout(childShadow, rect);
                    return true;
                }
                else if (layoutDescription.flags & LayoutDescription::HasLayoutCalculator)
                {
                    this->_shadowLayout(childShadow, rect);
                    return true;
                }
                else if ((layoutDescription.flags & LayoutDescription::HasHeightCalculator) || (layoutDescription.flags & LayoutDescription::HasWidthCalculator))
                {
                    bool hasHeightCalc = (layoutDescription.flags & LayoutDescription::HasHeightCalculator);
                    bool hasWidthCalc = (layoutDescription.flags & LayoutDescription::HasWidthCalculator);

                    if (hasHeightCalc && hasWidthCalc)
                    {
                        childShadow.getFundamental()->layoutBounds(rect, preferWidth);
                    }
                    else
                    {
                        childShadow.getFundamental()->layoutBounds(rect, hasHeightCalc);
                    }

                    this->_shadowLayout(childShadow, rect);
                    return true;
                }
                else 
                {
                    childShadow.bounds = SkRect();
                    return false;
                }
            });

            *bounds = layouter->layout(&engine, fundamental.get(), bounds, childCount);
        }
    }

    
    shadow.bounds = *bounds;
}

void DomRoot::_shadowDraw(SkCanvas* canvas, ShadowDom const& d)
{
    canvas->save();
    canvas->translate(d.bounds.left(), d.bounds.top());
    canvas->clipRect(SkRect::MakeWH(d.bounds.width(), d.bounds.height()));
    d.getFundamental()->draw(canvas);
    canvas->restore();

    for (auto cit = d.shadowChildren.cbegin(); cit != d.shadowChildren.cend(); ++cit)
    {
        _shadowDraw(canvas, *cit);
    }
}

void DomRoot::render()
{
    _shadow = {};
    _shadowRender(_shadow, _root);


    SkCanvas* canvas = _context->getSurface()->getCanvas();
    canvas->drawColor(SkColorSetARGB(255, 127, 127, 127));

    auto bounds = canvas->getLocalClipBounds();
    _shadowLayout(_shadow, &bounds);

    _shadowDraw(canvas, _shadow);
    canvas->flush();
}
