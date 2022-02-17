#include "snuifw/snuifw.h"
#include "interfaces.h"

using namespace snuifw;

decltype(ILayoutProviderElement::s_type) ILayoutProviderElement::s_type;
decltype(ILayoutElement::s_type) ILayoutElement::s_type;
decltype(IDrawableElement::s_type) IDrawableElement::s_type;
decltype(IInteractableElement::s_type) IInteractableElement::s_type;

decltype(IElement::s_type) IElement::s_type;
decltype(IComponent::s_type) IComponent::s_type;



ILayoutProviderElement::~ILayoutProviderElement() = default;



ILayoutElement::~ILayoutElement() = default;



IDrawableElement::~IDrawableElement() = default;



IInteractableElement::~IInteractableElement() = default;



IElement::~IElement() = default;

    ILayoutProviderElement*
IElement::layoutProviderElement()
    { return nullptr; }

    ILayoutElement*
IElement::layoutElement()
    { return nullptr; }

    IDrawableElement*
IElement::drawableElement()
    { return nullptr; }

    IInteractableElement*
IElement::interactableElement()
    { return nullptr; }

    IComponent*
IElement::component()
    { return nullptr; }

    std::vector<std::shared_ptr<IElement>> const*
IElement::children() const
    { return nullptr; }



IComponent::~IComponent() = default;
