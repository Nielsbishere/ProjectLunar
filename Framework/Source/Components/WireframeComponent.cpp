#include "../../Headers/Components/WireframeComponent.h"
#include "../../Headers/Render/Line/Wireframe.h"
#include "../../Headers/Render/Line/WireframeObject.h"
#include "../../Headers/GameObjectBehaviour/GameObject.h"
#include "../../Headers/World/World.h"
#include "../../Headers/RenderEngine.h"
using namespace lun;

WireframeComponent::WireframeComponent(Transform t) : wires(nullptr), tempTransform(t) {}
WireframeComponent::~WireframeComponent() {
	delete wires;
	if (started) {
		GameObject *go = getOwner();
		RenderEngine *re = go->getWorld()->getRenderEngine();
		re->remove(wires);
	}
}

void WireframeComponent::onAttach() {
	GameObject *go = getOwner();
	wires = new WireframeObject(true, tempTransform, go->getTransform(), nullptr);
}

void WireframeComponent::start() {
	GameObject *go = getOwner();
	RenderEngine *re = go->getWorld()->getRenderEngine();
	re->add(wires);
	started = true;
}
void WireframeComponent::update(f32 delta) {}

void WireframeComponent::attachWires(Wireframe *wires) { this->wires->wires = wires; }


bool WireframeComponent::isHidden() { return wires->isHidden(); }
void WireframeComponent::toggleVisiblity() { wires->toggleVisiblity(); }
void WireframeComponent::hide() { wires->hide(); }
void WireframeComponent::show() { wires->show(); }
void WireframeComponent::setHidden(bool hide) { wires->setHidden(hide); }

vec3 WireframeComponent::getLineColor() { return wires->getLineColor(); }
f32 WireframeComponent::getLineSize() { return wires->getLineSize(); }
void WireframeComponent::setLineColor(vec3 lineColor) { wires->setLineColor(lineColor); }
void WireframeComponent::setLineSize(f32 lineSize) { wires->setLineSize(lineSize); }
void WireframeComponent::colorize(vec3 tint) { wires->colorize(tint); }
void WireframeComponent::setUsesDepth(bool b) { wires->setUsesDepth(b); }

Transform &WireframeComponent::getObjectTransform() { return wires->getTransform(); }
Transform &WireframeComponent::getLocalTransform() { return wires->getLocalTransform(); }