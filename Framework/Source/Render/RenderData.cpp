#include "../../Headers/Render/RenderData.h"
#include "../../Headers/Resources/ResourcePile.h"
#include "../../Headers/Helper/OGLHelper.h"
#include "../../Headers/Render/RenderObject.h"
#include "../../Headers/RenderEngine.h"
#include "../../Headers/Render/BatchRender.h"
#include "../../Headers/Render/Shader.h"
#include "../../Headers/World/Light/DirectionalLight.h"
#include "../../Headers/World/Light/SpotLight.h"
#include "../../Headers/World/Light/PointLight.h"
#include <algorithm>
using namespace lun;

RenderData::RenderData(ResourcePile *_rp) {
	rp = _rp;

	Shader *s = rp->loadShader("Resources/Shaders/ModelShader.oglsl", "Model Shader");
	fxaaShader = rp->loadShader("Resources/Shaders/FXAA.oglsl", "FXAA Shader");
	uiShader = rp->loadShader("Resources/Shaders/UIShader.oglsl", "UI Shader");
	lineShader = rp->loadShader("Resources/Shaders/LineShader.oglsl", "Line Shader");
	defShader = rp->loadShader("Resources/Shaders/TBDR.oglsl", "TBDR Shader");
	rp->loadModel("Resources/Models/Cube.oiRM", "Cube", s);
	rp->loadModel("Resources/Models/Quad.oiRM", "Quad", s);
	fxaaQuad = rp->loadModel("Resources/Models/Quad.oiRM", "FXAA Quad", fxaaShader);

	{
		std::vector<Node> nodes(2);
		nodes[0].move(vec3(0, 0, -1));
		nodes[1].move(vec3(0, 0, 1));
		LineRenderer *line1 = rp->loadLine(nodes, "Line");

		nodes = std::vector<Node>(16);
		nodes[0].move(vec3(1, -1, -1));
		nodes[1].move(vec3(1, -1, 1));
		nodes[2].move(vec3(-1, -1, 1));
		nodes[3].move(vec3(-1, -1, -1));	
		nodes[4].move(nodes[0].getPosition());
		nodes[5].move(vec3(1, 1, -1));
		nodes[6].move(vec3(1, 1, 1));
		nodes[7].move(vec3(-1, 1, 1));
		nodes[8].move(vec3(-1, 1, -1));
		nodes[9].move(nodes[5].getPosition());
		nodes[10].move(nodes[6].getPosition());
		nodes[11].move(nodes[1].getPosition());
		nodes[12].move(nodes[2].getPosition());
		nodes[13].move(nodes[7].getPosition());
		nodes[14].move(nodes[8].getPosition());
		nodes[15].move(nodes[3].getPosition());

		LineRenderer *cubel = rp->loadLine(nodes, "Cube");

		nodes = std::vector<Node>(5);
		nodes[0].move(vec3(0, -1, 1));
		nodes[1].move(vec3(0, -1, -1));
		nodes[2].move(vec3(0, 1, -1));
		nodes[3].move(vec3(0, 1, 1));
		nodes[4].move(vec3(0, -1, 1));
		rp->loadLine(nodes, "Quad");

		Wireframe cube;
		cube.add(cubel, Transform(vec3(0, 0, 0)));
		rp->loadWireframe(cube, "Cube");

		Wireframe line;
		line.add(line1, Transform(vec3(0, 0, 0)));
		rp->loadWireframe(line, "Line");
	}

	pLights = new Buffer<PointLight, TPointLight>();
	dLights = new Buffer<DirectionalLight, TDirectionalLight>();
	sLights = new Buffer<SpotLight, TSpotLight>();

	w = h = oldH = oldW = 0;
	renderInit = false;
	batchesInit = false;
}
RenderData::~RenderData() {
	if (renderInit)
		destructFBOS();
	if (batchesInit) {
		for (u32 i = 0; i < batchesFwd.size(); ++i)
			delete batchesFwd[i];
		for (u32 i = 0; i < batchesDef.size(); ++i)
			delete batchesDef[i];
	}
	delete pLights;
	delete dLights;
	delete sLights;

	rp->unloadShader("Model Shader");
	rp->unloadShader("Model Shader-def");
	rp->unloadShader("FXAA Shader");
	rp->unloadShader("UI Shader");
	rp->unloadModel("Quad");
	rp->unloadModel("FXAA Quad");
	rp->unloadModel("Cube");
}

void RenderData::update() {
	oldW = w;
	oldH = h;

	sLights->update();
	pLights->update();
	dLights->update();
}

//FXAA
bool RenderData::createFxaa() {
	fxaa = OGLHelper::createFBO();
	fxaaTex = OGLHelper::createTexture(w, h, true);
	fxaaDepth = OGLHelper::createDepthBuffer(w, h);
	u32 buffers[1] = { 0 };
	OGLHelper::attachDepthBuffer(fxaa, fxaaDepth);
	OGLHelper::attachment(fxaa, 0, fxaaTex);
	OGLHelper::attachments(fxaa, buffers, 1);
	if (!OGLHelper::checkFBO(fxaa)) {
		printf("Couldn't create FXAA FBO!\n");
		destroyFxaa();
		OGLHelper::bindFBO(0);
		OGLHelper::bindRBO(0);
		OGLHelper::bindTexture(0);
		renderInit = false;
		return false;
	}
	return true;
}
void RenderData::destroyFxaa() {
	OGLHelper::destroyFBO(fxaa);
	OGLHelper::destroyTexture(fxaaTex);
	OGLHelper::destroyRBO(fxaaDepth);
}

//Deferred
bool RenderData::createDef() {
	defAlbedoSpec = OGLHelper::createTexture(w, h, true);
	defNormMisc = OGLHelper::createTexture(w, h);
	defDepth = OGLHelper::createDepthTexture(w, h);
	defOutput = OGLHelper::createTexture(w, h, true);
	u32 buffers[2] = { 0, 1 };
	def = OGLHelper::createFBO();
	OGLHelper::attachment(def, DEPTH_TEXTURE, defDepth);
	OGLHelper::attachment(def, 0, defAlbedoSpec);
	OGLHelper::attachment(def, 1, defNormMisc);
	OGLHelper::attachments(def, buffers, 2);
	if (!OGLHelper::checkFBO(def)) {
		printf("Couldn't create Deferred FBO!\n");
		destroyDef();
		OGLHelper::bindFBO(0);
		OGLHelper::bindTexture(0);
		renderInit = false;
		return false;
	}
	return true;
}
void RenderData::destroyDef() {
	OGLHelper::destroyFBO(def);
	OGLHelper::destroyTexture(defAlbedoSpec);
	OGLHelper::destroyTexture(defNormMisc);
	OGLHelper::destroyTexture(defDepth);
	OGLHelper::destroyTexture(defOutput);
}

//Handle FBOS
void RenderData::destructFBOS() {
	if (!renderInit)return;

	printf("Destructing FBOs\n");

	destroyFxaa();
	destroyDef();

	renderInit = false;
}
void RenderData::resizeFBOS() {
	if (renderInit)
		destructFBOS();

	printf("Constructing FBOs\n");

	if (!createFxaa())
		return;
	OGLHelper::bindRBO(0);

	if (!createDef()) {
		destroyFxaa();
		return;
	}

	OGLHelper::bindFBO(0);
	OGLHelper::bindTexture(0);
	renderInit = true;
}

//Resizing screen
void RenderData::resize(u32 iw, u32 ih) {
	w = iw;
	h = ih;

	if ((w == 0 || h == 0) && renderInit) {
		destructFBOS();
		renderInit = false;
	}
	if (w != 0 && h != 0 && ((w != oldW && h != oldH) || !renderInit)) {
		glViewport(0, 0, w, h);
		resizeFBOS();
		renderInit = true;
	}
}

//UIObject
void RenderData::remove(UIObject *uio) {
	for (u32 i = 0; i < uiData.size(); ++i)
		if (uiData[i] == uio) {
			uiData.erase(uiData.begin() + i);
			break;
		}
}
void RenderData::add(UIObject *uio) { uiData.push_back(uio); }
void RenderData::addAll(std::vector<UIObject*> &all) {
	for (u32 i = 0; i < all.size(); ++i)
		add(all[i]);
}
void RenderData::removeAll(std::vector<UIObject*> &all) {
	for (u32 i = 0; i < all.size(); ++i)
		remove(all[i]);
}

//RenderObject
void RenderData::remove(RenderObject *ro) {
	for (u32 i = 0; i < toRender.size(); ++i)
		if (toRender[i] == ro) {
			toRender.erase(toRender.begin() + i);
			break;
		}
}
void RenderData::add(RenderObject *ro) { toRender.push_back(ro); }
void RenderData::addAll(std::vector<RenderObject*> &all) {
	for (u32 i = 0; i < all.size(); ++i)
		add(all[i]);
}
void RenderData::removeAll(std::vector<RenderObject*> &all) {
	for (u32 i = 0; i < all.size(); ++i)
		remove(all[i]);
}

//WireframeObject
void RenderData::remove(WireframeObject *wfo) {
	for (u32 i = 0; i < wires.size(); ++i)
		if (wires[i] == wfo) {
			wires.erase(wires.begin() + i);
			break;
		}
}
void RenderData::add(WireframeObject *wfo) { wires.push_back(wfo); }
void RenderData::addAll(std::vector<WireframeObject*> &all) {
	for (u32 i = 0; i < all.size(); ++i)
		add(all[i]);
}
void RenderData::removeAll(std::vector<WireframeObject*> &all) {
	for (u32 i = 0; i < all.size(); ++i)
		remove(all[i]);
}

//DirectionalLight
void RenderData::add(DirectionalLight *dl) { dLights->add(dl); }
void RenderData::addAll(std::vector<DirectionalLight*> &dl) { dLights->addAll(dl); }
void RenderData::remove(DirectionalLight *dl) { dLights->remove(dl); }
void RenderData::removeAll(std::vector<DirectionalLight*> &dl) { dLights->removeAll(dl); }

//SpotLight
void RenderData::add(SpotLight *sl) { sLights->add(sl); }
void RenderData::addAll(std::vector<SpotLight*> &sl) { sLights->addAll(sl); }
void RenderData::remove(SpotLight *sl) { sLights->remove(sl); }
void RenderData::removeAll(std::vector<SpotLight*> &sl) { sLights->removeAll(sl); }

//PointLight
void RenderData::add(PointLight *pl) { pLights->add(pl); }
void RenderData::addAll(std::vector<PointLight*> &pl) { pLights->addAll(pl); }
void RenderData::remove(PointLight *pl) { pLights->remove(pl); }
void RenderData::removeAll(std::vector<PointLight*> &pl) { pLights->removeAll(pl); }

//Batches
void RenderData::recalculateBatches() {
	if (batchesInit) {
		for (u32 i = 0; i < batchesFwd.size(); ++i)
			delete batchesFwd[i];
		batchesFwd.clear();

		for (u32 i = 0; i < batchesDef.size(); ++i)
			delete batchesDef[i];
		batchesDef.clear();
	}

	std::vector<RCHolder> renderable;
	for (u32 i = 0; i < toRender.size(); ++i) {
		RenderObject *ro = toRender[i];
		Renderer *r = nullptr;
		if (ro == nullptr || ro->isHidden() || (r = ro->getRenderer()) == nullptr || ro->isDynamic())continue;

		renderable.push_back(RCHolder(ro));
	}

	//Sort objects by shader type, shader, renderer, texture(s)
	std::sort(renderable.begin(), renderable.end());

	//calculate where an old instance ends and a new one begins
	std::vector<RenderObject*> ros;
	Renderer *prevR = nullptr;
	for (u32 i = 0; i < renderable.size(); ++i) {
		RenderObject *ro = renderable[i].ro;
		Renderer *r = ro->getRenderer();
		Shader *s = r->getShader();
		if (prevR != r) {
			if (prevR != nullptr) {
				if (prevR->getType() == FORWARD)
					batchesFwd.push_back(new BatchRender(ros));
				else
					batchesDef.push_back(new BatchRender(ros));
				ros.clear();
			}
			ros.push_back(ro);
			prevR = r;
		}
		else
			ros.push_back(ro);
	}

	if (prevR != nullptr && ros.size() != 0) {
		if (prevR->getShader()->getType() == FORWARD)
			batchesFwd.push_back(new BatchRender(ros));
		else
			batchesDef.push_back(new BatchRender(ros));
	}
	batchesInit = true;
}

void RenderData::updateBuffers() {
	pLights->refreshBuffer();
	dLights->refreshBuffer();
	sLights->refreshBuffer();
}


void RenderData::reset() {
	batchesFwd.clear();
	batchesDef.clear();
	batchesInit = false;
}