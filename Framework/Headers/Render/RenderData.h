#pragma once
#include "../CrossPlatform/CrossPlatform.h"
#include "../GPU/Buffer.h"
#include <vector>
namespace lun {
	class ResourcePile;
	class RenderObject;
	class UIObject;
	class Shader;
	class Renderer;
	class BatchRender;
	class SpotLight;
	class PointLight;
	struct TSpotLight;
	struct TPointLight;
	struct TDirectionalLight;
	class DirectionalLight;
	class WireframeObject;
	class LineRenderer;

	class RenderData {
		friend class RenderEngine;

	protected:

		RenderData(ResourcePile *rp);
		~RenderData();

		///Resizing screen
		void resize(u32 w, u32 h);
		void update();

		///FXAA
		void destroyFxaa();
		bool createFxaa();

		///Deferred
		void destroyDef();
		bool createDef();

		///FBOS
		void destructFBOS();
		void resizeFBOS();

		///UIObjects
		void add(UIObject *uio);
		void addAll(std::vector<UIObject*> &uio);
		void remove(UIObject *uio);
		void removeAll(std::vector<UIObject*> &uio);

		///RenderObjects
		void add(RenderObject *ro);
		void addAll(std::vector<RenderObject*> &ro);
		void remove(RenderObject *ro);
		void removeAll(std::vector<RenderObject*> &ro);

		///WireframeObjects
		void add(WireframeObject *wfo);
		void addAll(std::vector<WireframeObject*> &wfo);
		void remove(WireframeObject *wfo);
		void removeAll(std::vector<WireframeObject*> &wfo);

		///DirectionalLight
		void add(DirectionalLight *dl);
		void addAll(std::vector<DirectionalLight*> &dl);
		void remove(DirectionalLight *dl);
		void removeAll(std::vector<DirectionalLight*> &dl);

		///SpotLight
		void add(SpotLight *sl);
		void addAll(std::vector<SpotLight*> &sl);
		void remove(SpotLight *sl);
		void removeAll(std::vector<SpotLight*> &sl);

		///PointLight
		void add(PointLight *pl);
		void addAll(std::vector<PointLight*> &pl);
		void remove(PointLight *pl);
		void removeAll(std::vector<PointLight*> &pl);

		///Batches
		void recalculateBatches();
		void updateBuffers();

		void reset();

	private:

		///Resource pile (Engine)
		ResourcePile *rp;

		///Framebuffer size (old/new)
		u32 w, h, oldW, oldH;

		///Whether all FBOS where initialized
		bool renderInit;

		///FXAA
		Shader *fxaaShader;
		GLuint fxaa;
		GLuint fxaaTex;
		GLuint fxaaDepth;
		Renderer *fxaaQuad;

		///Deferred
		Shader *defShader;
		GLuint def;
		GLuint defAlbedoSpec, defNormMisc, defDepth, defOutput;

		///UI
		Shader *uiShader;
		Shader *lineShader;

		///RenderData
		std::vector<RenderObject*> toRender;
		std::vector<UIObject*> uiData;
		std::vector<WireframeObject*> wires;

		///Lights
		Buffer<PointLight, TPointLight> *pLights;
		Buffer<SpotLight, TSpotLight> *sLights;
		Buffer<DirectionalLight, TDirectionalLight> *dLights;

		///Batches
		bool batchesInit;
		std::vector<BatchRender*> batchesFwd;
		std::vector<BatchRender*> batchesDef;

	};
}