#include "../../Headers/Components/RenderComponent.h"
#include "../../Headers/GameObjectBehaviour/GameObject.h"
#include "../../Headers/World/World.h"
#include "../../Headers/RenderEngine.h"
#include "../../Headers/Render/RenderObject.h"
using namespace lun;

RenderComponent::RenderComponent() : renderer(nullptr) {}
RenderComponent::~RenderComponent() {
	delete renderer;
	if (started) {
		GameObject *go = getOwner();
		RenderEngine *re = go->getWorld()->getRenderEngine();
		re->remove(renderer);
	}
}

void RenderComponent::onAttach() {
	GameObject *go = getOwner();
	renderer = new RenderObject(true, go->isStatic(), go->getTransform(), nullptr);
}

void RenderComponent::start() {
	GameObject *go = getOwner();
	RenderEngine *re = go->getWorld()->getRenderEngine();
	re->add(renderer);
}
void RenderComponent::update(f32 delta) {}

void RenderComponent::attachRenderer(Renderer *r) { renderer->r = r; }


bool RenderComponent::isHidden() { return renderer->isHidden(); }
void RenderComponent::toggleVisiblity() { renderer->toggleVisiblity(); }
void RenderComponent::hide() { renderer->hide(); }
void RenderComponent::show() { renderer->show(); }
void RenderComponent::setHidden(bool hide) { renderer->setHidden(hide); }

bool RenderComponent::isDynamic() { return renderer->isDynamic(); }
Transform &RenderComponent::getTransform() { return renderer->getTransform(); }