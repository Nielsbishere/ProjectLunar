#include "../../Headers/Temporary/GameState.h"
#include "../../Headers/RenderEngine.h"
#include "../../Headers/World/Light/PointLight.h"
#include "../../Headers/World/Light/DirectionalLight.h"
#include "../../Headers/Render/UIObject.h"
#include "../../Headers/Components/RenderComponent.h"
#include "../../Headers/Components/WireframeComponent.h"
#include "../../Headers/Resources/Model/MeshHelper.h"
#include "../../Headers/DataStructures/Grid2D.h"
#include "../../Headers/Math/SimplexNoise.h"
#include "../../Headers/Math/WorleyNoise.h"
using namespace lun;

f32 linear(f32 x, f32 y) {
	return WorleyNoise::worley2D(vec2(x, y) * 7);
}

GameObject *temp;

void GameState::init() {
	std::vector<GameObject*> objs(4 * 32 * 32);
	for (u32 i = 0; i < 4 * 32 * 32; i++) {
		GameObject *go = objs[i] = new GameObject(vec3(5, -3, 1) - vec3((f32)(i % 32), -(f32)((i / 32) % 32), (f32)(i / 32 / 32) * 3) * 2.5f);
		RenderComponent *rc = go->addComponent<RenderComponent>("", false);
		rc->attachRenderer(getGlobalPile()->fetchModel("Cube"));
		go->setStatic();
	}

	getWorld()->spawnAll(objs);

	Grid2D *g = new Grid2D(128, 128, linear);
	g->normalize();
	MeshHelper::createTopDown(getPile(), "Random stuff", getGlobalPile()->fetchShader("Model Shader"), g);

	{
		GameObject *go = temp = new GameObject(vec3(0, 0, 50), vec3(80, 0, 0), vec3(50, 40, 50));
		RenderComponent *rc = go->addComponent<RenderComponent>("", false);
		rc->attachRenderer(getPile()->fetchModel("Random stuff"));
		go->setStatic();
		getWorld()->spawn(go);
	}

	getRenderer()->add(new UIObject(getGlobalPile()->fetchModel("Quad"), getGlobalPile()->fetchTexture("Frog"), vec2(0.75f, 1 - 0.25f / 9 * 16), vec2(0.25f, 0.25f / 9 * 16), 0, 0, vec2(), vec2(1, 1), vec4(1, 1, 1, 0.3f)));

	std::vector<PointLight*> pls(4);

	pls[0] = new PointLight(vec3(5 - 15.5f * 2.5f, -3 + 15.5f * 2.5f, 3), vec3(1, 0, 0), 3);
	pls[1] = new PointLight(vec3(5 - 11.5f * 2.5f, -3 + 11.5f * 2.5f, 3), vec3(0, 1, 0), 3);
	pls[2] = new PointLight(vec3(5 - 11.5f * 2.5f, -3 + 15.5f * 2.5f, 3), vec3(0, 0, 1), 3);
	pls[3] = new PointLight(vec3(5 - 15.5f * 2.5f, -3 + 11.5f * 2.5f, 3), vec3(1, 0, 1), 3);

	getRenderer()->addAll(pls);

	getRenderer()->add(new DirectionalLight(vec3(-1, -1, 0), vec3(0, 1, 0), 0.5f));

	getWorld()->getMainCamera()->setFar(250);
	getRenderer()->setAmbient(vec3(.1f, .1f, .1f));
}

void GameState::update(f64 delta) {
	//temp->getTransform().addRotation(vec3(0, 10, 0) * delta);
}