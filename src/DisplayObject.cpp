#include "DisplayObject.h"

DisplayObject::DisplayObject() = default;

DisplayObject::~DisplayObject()
{
	m_pParentScene = nullptr;
}

Scene * DisplayObject::getParent() const
{
	return m_pParentScene;
}

void DisplayObject::setParent(Scene * parent)
{
	m_pParentScene = parent;
}
