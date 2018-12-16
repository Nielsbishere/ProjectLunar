#include "../Headers/RenderEngine.h"
#include "../Headers/Helper/OGLHelper.h"
#include "../Headers/Resources/ResourcePile.h"
#include "../Headers/Render/Shader.h"
#include "../Headers/Render/RenderObject.h"
#include "../Headers/Render/Line/WireframeObject.h"
#include "../Headers/Render/Shader.h"
#include "../Headers/Render/UIObject.h"
#include "../Headers/Shapes/Frustum.h"
#include "../Headers/Render/BatchRender.h"
#include "../Headers/Render/RenderData.h"
#include "../Headers/Render/ComputeShader.h"
#include "../Headers/Math/Math.h"
#include "../Headers/Settings/Settings.h"
#include <algorithm>

#define BATCH_COUNT_OPTIMAL 500

using namespace lun;

//SSHHH this is just temporary...
//Don't kill me pl0x
Texture *t;
//You've seen nothing... TODO:

//General RenderEngine stuff
RenderEngine::RenderEngine(ResourcePile *_rp): renderOptions(Bitset(32)), ambient(vec3(.3f, .3f, .3f)) {
	resources = _rp;

	#ifdef __DEBUG__
	setFlag(WIREFRAMES, true);
	#endif

	#ifdef NOUI
	setFlag(UI, false);
	#else
	setFlag(UI, true);
	#endif

	data = new RenderData(resources);
	t = resources->loadTexture("Resources/Textures/Rare.png", "Frog");
	quadShader = resources->loadShader("Resources/Shaders/QuadShader.oglsl", "Quad Shader");
}

void RenderEngine::init() {
	data->recalculateBatches();
	data->updateBuffers();
}

void RenderEngine::resize(int iw, int ih) {
	data->resize(iw, ih);
}

RenderEngine::~RenderEngine() {
	delete data;
	resources->unloadTexture("Frog");
	resources->unloadShader("Quad Shader");
}

int RenderEngine::getWidth() { return data->w; }
int RenderEngine::getHeight() { return data->h; }

void RenderEngine::setFlag(ERenderOption option, bool value) { renderOptions.set(option, value); }
bool RenderEngine::getFlag(ERenderOption option){ return renderOptions[option]; }

void RenderEngine::setAmbient(vec3 _ambient) { ambient = _ambient; }
void RenderEngine::colorizeAmbient(vec3 colorizer) { ambient = ambient * colorizer; }
vec3 RenderEngine::getAmbient() { return ambient; }

//Sorting
bool RCHolder::operator<(const RCHolder &rch) {
	Renderer *r = ro->getRenderer();
	Renderer * or = rch.ro->getRenderer();
	Shader *s = r->getShader();
	Shader *os = or ->getShader();

	return s->getType() < os->getType() || ((s->getType() == os->getType() && s < os) || (s->getType() == os->getType() && s == os && r < or ));
}

bool WOHolder::operator<(const WOHolder &woh) {
	return woh.wo == nullptr && wo != nullptr || (wo != nullptr && woh.wo != nullptr && (wo->fakes3D() > woh.wo->fakes3D() || (woh.wo->fakes3D() == wo->fakes3D() && (wo->getWireframe() < woh.wo->getWireframe() || ((wo->getWireframe() == woh.wo->getWireframe() && wo->getLineSize() < woh.wo->getLineSize()) || (wo->getWireframe() == woh.wo->getWireframe() && wo->getLineSize() == woh.wo->getLineSize() && wo->getLineColor() < woh.wo->getLineColor()))))));
}

bool WOHolder::operator==(const WOHolder &woh) {
	return wo == nullptr && woh.wo == nullptr || (wo != nullptr && woh.wo != nullptr && (wo->fakes3D() == woh.wo->fakes3D() && wo->getWireframe() == woh.wo->getWireframe() && wo->getLineColor() == woh.wo->getLineColor() && wo->getLineSize() == woh.wo->getLineSize()));
}


//Adding/removing world objects
void RenderEngine::add(RenderObject *ro) { data->add(ro); }
void RenderEngine::remove(RenderObject *ro) { data->remove(ro); }
void RenderEngine::addAll(std::vector<RenderObject*> &ro) { data->addAll(ro); }
void RenderEngine::removeAll(std::vector<RenderObject*> &ro) { data->removeAll(ro); }

void RenderEngine::add(WireframeObject *wo) { data->add(wo); }
void RenderEngine::remove(WireframeObject *wo) { data->remove(wo); }
void RenderEngine::addAll(std::vector<WireframeObject*> &wo) { data->addAll(wo); }
void RenderEngine::removeAll(std::vector<WireframeObject*> &wo) { data->removeAll(wo); }

void RenderEngine::add(UIObject *uio) { data->add(uio); }
void RenderEngine::remove(UIObject *uio) { data->remove(uio); }
void RenderEngine::addAll(std::vector<UIObject*> &uio) { data->addAll(uio); }
void RenderEngine::removeAll(std::vector<UIObject*> &uio) { data->removeAll(uio); }

void RenderEngine::add(PointLight *pl) { data->add(pl); }
void RenderEngine::remove(PointLight *pl) { data->remove(pl); }
void RenderEngine::addAll(std::vector<PointLight*> &pl) { data->addAll(pl); }
void RenderEngine::removeAll(std::vector<PointLight*> &pl) { data->removeAll(pl); }

void RenderEngine::add(SpotLight *sl) { data->add(sl); }
void RenderEngine::remove(SpotLight *sl) { data->remove(sl); }
void RenderEngine::addAll(std::vector<SpotLight*> &sl) { data->addAll(sl); }
void RenderEngine::removeAll(std::vector<SpotLight*> &sl) { data->removeAll(sl); }

void RenderEngine::add(DirectionalLight *dl) { data->add(dl); }
void RenderEngine::remove(DirectionalLight *dl) { data->remove(dl); }
void RenderEngine::addAll(std::vector<DirectionalLight*> &dl) { data->addAll(dl); }
void RenderEngine::removeAll(std::vector<DirectionalLight*> &dl) { data->removeAll(dl); }

//Batch rendering
std::vector<u32> RenderEngine::createBatches(std::vector<RenderObject*> &rcs) {
	std::vector<u32> startEnd;

	Renderer *prev = nullptr;
	u32 count = 0;
	u32 firstIndex = 0;

	for (u32 i = 0; i < rcs.size(); ++i) {
		if (!rcs[i]->isDynamic())continue;
		Renderer *next = rcs[i]->getRenderer();
		if (prev == next)
			count++;
		else {
			if (count > BATCH_COUNT_OPTIMAL) {
				startEnd.push_back(firstIndex);
				startEnd.push_back(i - 1);
			}
			count = 0;
			firstIndex = i;
		}

		prev = next;
	}

	if (count > BATCH_COUNT_OPTIMAL) {
		startEnd.push_back(firstIndex);
		startEnd.push_back((u32)rcs.size() - 1);
	}

	return startEnd;
}

//Render parts of the scene and/or get things to be drawn
void RenderEngine::renderPass(std::vector<RenderObject*> &rcs, Camera *c, EShaderType breakType, EShaderType continueType) {

	//Use static batches; all RenderObject's that are static will be pre-batched.
	//It holds VBOs and doesn't have to create/destroy the VBO every frame.
	Frustum f = c->getFrustum();

	std::vector<BatchRender*> &renders = (breakType == FORWARD ? data->batchesDef : data->batchesFwd);
	for (u32 i = 0; i < renders.size(); i++)
		if (f.intersection(renders[i]->boundingBox, 0))
			renders[i]->render(c);

	//Create batches (a batch is when you have x renderers that are the same; where x > BATCH_COUNT_OPTIMAL)
	//So if you have 256 cubes on the screen;	batches[0] = 0 and batches[1] = 255.
	//256 cubes and 128 spheres;				batches[0] = 0 and batches[1] = 255, batches[2] = 256 and batches[3] = 383

	//Only use batches when not static
	std::vector<u32> batches = createBatches(rcs);
	if (batches.size() > 0) {
		for (u32 i = 0; i < batches.size() / 2; ++i) {
			u32 start = batches[2 * i];
			u32 end = batches[2 * i + 1];
			u32 size = end - start + 1;

			std::vector<RenderObject*> ros;
			for (u32 j = 0; j < size; ++j)
				ros.push_back(rcs[start + j]);

			BatchRender *br = new BatchRender(ros);
			br->render(c);
			delete br;
		}

	}

	Shader *_s = nullptr;
	Renderer *_r = nullptr;
	for (u32 i = 0; i < rcs.size(); ++i) {

		bool contains = false;
		for (u32 j = 0; j < batches.size() / 2; ++j) {
			u32 start = batches[2 * j];
			u32 end = batches[2 * j + 1];
			if (i >= start && i <= end) {
				contains = true;
				break;
			}
		}
		//Only render if it isn't batched
		if (contains)continue;

		Renderer *r = rcs[i]->getRenderer();
		Shader *s = r->getShader();
		if (s->getType() == breakType)break;
		if (s->getType() == continueType)continue;
		if (s != _s) {
			s->use();
			s->set("V", c->getView());
			s->set("P", c->getProjection());
			s->set("eye", c->getPosition());
			s->set("instanced", false);
			_s = s;
		}
		if (r != _r) {
			if (_r != nullptr)
				_r->unbind();
			r->bind();
			_r = r;
		}
		r->nobindRender(rcs[i]->getTransform().makeModelMatrix(), c);
	}
	if (_r != nullptr)
		_r->unbind();
}

void RenderEngine::render(std::vector<RenderObject*> &fwd, std::vector<RenderObject*> &def, Camera *c) {
	if (c == nullptr)return;
	Frustum f = c->getFrustum();

	std::vector<RenderObject*> &toRender = data->toRender;

	//Cull objects that can't be rendered, are hidden or are not on screen
	std::vector<RCHolder> renderable;
	for (u32 i = 0; i < toRender.size(); ++i) {
		RenderObject *ro = toRender[i];
		Renderer *r = nullptr;
		if (ro == nullptr || ro->isHidden() || (r = ro->getRenderer()) == nullptr || !ro->isDynamic())continue;

		//Frustum cull it
		AABB box = r->getAABB();
		box = box * ro->getTransform().makeModelMatrix();
		if (!f.intersection(box, 0))continue;

		renderable.push_back(RCHolder(ro));
	}

	//Sort objects by shader type, shader, renderer, texture(s)
	std::sort(renderable.begin(), renderable.end());

	for (u32 i = 0; i < renderable.size(); ++i) {
		if (renderable[i].ro->getRenderer()->getShader()->getType() == FORWARD)
			fwd.push_back(renderable[i].ro);
		else
			def.push_back(renderable[i].ro);
	}
}

void RenderEngine::wireframePass(Camera *c) {
	Frustum f = c->getFrustum();

	std::vector<WOHolder> wcs(data->wires.size());
	u32 index = 0;
	for (u32 i = 0; i < (u32)data->wires.size(); ++i) {
		WireframeObject *wf = data->wires[i];
		if (!wf->canRender()) continue;

		mat4 m = wf->getTransform().makeModelMatrix() * wf->getLocalTransform().makeModelMatrix();

		//Check if wireframe on screen
		AABB box = wf->getAABB();
		if (!f.intersection(box)) continue;

		wcs[index].wo = wf;
		index++;
	}

	wcs.resize(index);
	if (wcs.size() == 0)
		return;

	std::sort(wcs.begin(), wcs.end());

	WOHolder *prev = nullptr;
	u32 start = 0;
	bool active = true;
	bool lastDepth = true;
	for (u32 i = 0; i < (u32)wcs.size(); ++i) {
		if (prev != nullptr && !(*prev == wcs[i])) {
			Wireframe *wf = nullptr;
			WireframeObject *wfo = nullptr;
			std::vector<mat4> wires(i - start);
			for (u32 j = start; j < i; ++j) {
				if (j == start) {
					wf = (wfo = wcs[j].wo)->getWireframe();
				}

				wires[j - start] = wcs[j].wo->getTransform().makeModelMatrix() * wcs[j].wo->getLocalTransform().makeModelMatrix();
			}
			wf->render(wires, data->lineShader, c, wfo->getLineColor(), wfo->getLineSize());

			if (active != !wcs[i].wo->fakes3D()) {
				active = !active;
				OGLHelper::depthTest(active);
			}

			start = i;
		}
		else if (prev == nullptr) {
			if (active != !wcs[i].wo->fakes3D()) {
				active = !active;
				OGLHelper::depthTest(active);
			}

			start = i;
		}

		prev = &wcs[i];
	}

	if (prev != nullptr) {
		u32 i = (u32)wcs.size();

		Wireframe *wf = nullptr;
		WireframeObject *wfo = nullptr;
		std::vector<mat4> wires(i - start);
		for (u32 j = start; j < i; ++j) {
			if (j == start) {
				wf = (wfo = wcs[j].wo)->getWireframe();
			}

			wires[j - start] = wcs[j].wo->getTransform().makeModelMatrix() * wcs[j].wo->getLocalTransform().makeModelMatrix();
		}
		
		wf->render(wires, data->lineShader, c, wfo->getLineColor(), wfo->getLineSize());
	}

	if(!active)
		OGLHelper::depthTest(true);


	//TODO: Create oiLR & oiWF
}

//Render the scene
void RenderEngine::renderScene(Camera *c) {
	if (c == nullptr)return;

	std::vector<RenderObject*> fwd;
	std::vector<RenderObject*> def;
	render(fwd, def, c);

	//Bind deferred buffer
	OGLHelper::bindFBO(data->def);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	t->bind(TEXTURE_2D, TEXTURE00);
	renderPass(def, c, FORWARD, COMPUTE);

	//Wire frames
	if (getFlag(WIREFRAMES)) {
		data->lineShader->use();
		data->lineShader->set("V", c->getView());
		data->lineShader->set("P", c->getProjection());
		wireframePass(c);
	}

	//Copy deferred depth to forward+ buffer
	OGLHelper::copyDepth(data->def, data->fxaa, data->w, data->h);

	//Process G-buffer using TBDR
	Shader *s = data->defShader;

	if (s == nullptr || s->getType() != COMPUTE) {
		printf("Couldn't find TBDR compute shader!\n");
		return;
	}

	s->use();
	//Textures
	{
		s->set("outTex", 3);
		OGLHelper::bindWriteTexture(3, data->defOutput);

		s->set("depth", 2);
		OGLHelper::bindTexture(TEXTURE02, TEXTURE_2D, data->defDepth);

		s->set("normalMisc", 1);
		OGLHelper::bindTexture(TEXTURE01, TEXTURE_2D, data->defNormMisc);

		s->set("albedoSpecular", 0);
		OGLHelper::bindTexture(TEXTURE00, TEXTURE_2D, data->defAlbedoSpec);
	}

	//Lights
	{
		if (data->pLights->hasBuffer()) {
			data->pLights->bind(3);
			s->set("pLightNum", (int)data->pLights->size());
		}
		else
			s->set("pLightNum", 0);

		if (data->dLights->hasBuffer()) {
			data->dLights->bind(4);
			s->set("dLightNum", (int)data->dLights->size());
		}
		else
			s->set("dLightNum", 0);

		if (data->sLights->hasBuffer()) {
			data->sLights->bind(5);
			s->set("sLightNum", (int)data->sLights->size());
		}
		else
			s->set("sLightNum", 0);
	}

	s->set("V", c->getView());
	s->set("P", c->getProjection());
	s->set("eyeNear", vec4(c->getPosition(), c->getNear()));
	s->set("dirFar", vec4(c->getDirection(), c->getFar()));
	s->set("ambient", ambient);
	((ComputeShader*)s)->execute((u32)Math<f32>::ceil(data->w / 16.f), (u32)Math<f32>::ceil(data->h / 16.f), 1);

	//Bind foward+ buffer
	OGLHelper::bindFBO(data->fxaa);

	//TBDR quad
	OGLHelper::bindTexture(TEXTURE_2D, data->defOutput);
	OGLHelper::noDepth();
	quadShader->use();
	Renderer *quad = resources->fetchModel("Quad");
	quad->bind();
	quad->instancedRender(1);
	quad->unbind();
	OGLHelper::bindTexture(TEXTURE_2D, 0);

	//Forward
	OGLHelper::depth();
	t->bind(TEXTURE_2D, TEXTURE00);
	renderPass(fwd, c, COMPUTE, DEFERRED);		//Don't even use textures... such a shame

	//Use deferred shader types in deferred buffer and forward shader types in forward
	//When the shader ptr changes, you have to rebind the shader
	//When the render ptr changes, you have to rebind the renderer
	//When the texture(s) change, you have to rebind the texture(s)
}
void RenderEngine::renderNoUI(Camera *c, GLuint fbo) {
	if (c == nullptr || !data->renderInit)return;

	//Render scene
	renderScene(c);

	Shader *fxaaShader = data->fxaaShader;

	//FXAA
	OGLHelper::bindFBO(fbo);
	OGLHelper::bindTexture(data->fxaaTex);
	OGLHelper::noDepth();
	fxaaShader->use();
	fxaaShader->set("t", 0);
	fxaaShader->set("FXAA_SUBPIX_SHIFT", 0.f);
	fxaaShader->set("FXAA_REDUCE_MUL", 0.f);
	fxaaShader->set("FXAA_REDUCE_MIN", 1 / 128.f);
	fxaaShader->set("FXAA_SPAN_MAX", 8.f);
	fxaaShader->set("screenW", (f32)data->w);
	fxaaShader->set("screenH", (f32)data->h);
	data->fxaaQuad->render(mat4(), mat4(), mat4(), vec3());

	//Unbind
	OGLHelper::bindTexture(0);
	OGLHelper::bindFBO(0);
	OGLHelper::depth();
}
void RenderEngine::render(Camera *c, GLuint fbo) {
	OGLHelper::bindFBO(fbo);
	OGLHelper::clearFBO();

	renderNoUI(c, fbo);

	if (getFlag(UI)) {

		std::vector<UIObject*> &uiData = data->uiData;

		std::vector<UIObject> uiObjs = std::vector<UIObject>(uiData.size());
		for (u32 i = 0; i < uiData.size(); ++i)
			if (uiData[i]->canRender())
				uiObjs[i] = *uiData[i];

		std::sort(uiObjs.begin(), uiObjs.end());

		OGLHelper::alphaBlend();

		data->uiShader->use();
		Renderer *r = nullptr;
		Texture *t = nullptr;
		for (u32 i = 0; i < uiObjs.size(); ++i) {
			if (!uiObjs[i].canRender())continue;
			UIObject &o = uiObjs[i];
			Renderer *tr = nullptr;
			if ((tr = o.getRenderer()) != r) {
				if (r != nullptr)r->unbind();
				tr->bind();
				r = tr;
			}
			Texture *tt = nullptr;
			if ((tt = o.getTexture()) != t) {
				tt->bind(TEXTURE_2D);
				t = tt;
			}
			uiObjs[i].nobindRender(data->uiShader);
		}

		OGLHelper::noBlend();

	}
}

//Other functions; like update
void RenderEngine::update() {
	data->update();
}

void RenderEngine::reset() {
	renderOptions = Bitset(32);
	ambient = vec3(.3f, .3f, .3f);

	#ifdef __DEBUG__
	setFlag(WIREFRAMES, true);
	#endif

	#ifdef NOUI
	setFlag(UI, false);
	#else
	setFlag(UI, true);
	#endif

	data->reset();
}