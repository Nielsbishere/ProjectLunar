#pragma once
#include <vector>
#include "Type/OTypes.h"
#include "CrossPlatform/Context.h"
#include "DataStructures/Bitset.h"
namespace lun {
	class World;
	class Camera;
	class RenderObject;
	class ResourcePile;
	class BatchRender;
	enum EShaderType;
	class Renderer;
	class Shader;
	class UIObject;
	class RenderData;
	class DirectionalLight;
	class SpotLight;
	class PointLight;
	class WireframeObject;

	//Temporary struct for sorting RenderObjects
	struct RCHolder {
		RenderObject *ro;
		RCHolder(RenderObject *_ro) { ro = _ro; }
		bool operator<(const RCHolder &rch);
	};

	//Temporary struct for sorting WireframeObjects
	struct WOHolder {
		WireframeObject *wo;
		WOHolder(WireframeObject *_wo) { wo = _wo; }
		WOHolder() { wo = nullptr; }
		bool operator<(const WOHolder &woh);
		bool operator==(const WOHolder &woh);
	};

	//Options/flags for rendering
	enum ERenderOption {
		WIREFRAMES, UI
	};

	class RenderEngine {
		friend class Engine;

	private:

		ResourcePile *resources;

		RenderData *data;
		Shader *quadShader;

		Bitset renderOptions;
		vec3 ambient;

		std::vector<u32> createBatches(std::vector<RenderObject*> &toBatch);

		//Render
		void renderPass(std::vector<RenderObject*> &rcs, Camera *c, EShaderType breakType, EShaderType continueType);
		void wireframePass(Camera *c);
		void render(std::vector<RenderObject*> &fwd, std::vector<RenderObject*> &def, Camera *c);

		void renderScene(Camera *c);

	protected:

		RenderEngine(ResourcePile *rp);
		~RenderEngine();

		void resize(int w, int h);
		int getWidth();
		int getHeight();

		void init();

	public:

		//Render the scene without UI
		void renderNoUI(Camera *c, GLuint fbo = 0);

		//Render the scene with UI
		void render(Camera *c, GLuint fbo = 0);

		//Update the render data
		void update();


		//Add RenderObject
		void add(RenderObject *ro);

		//Remove RenderObject
		void remove(RenderObject *ro);

		//Remove all RenderObjects
		void removeAll(std::vector<RenderObject*> &ro);

		//Add all RenderObjects
		void addAll(std::vector<RenderObject*> &ro);


		//Add WireframeObject
		void add(WireframeObject *wo);

		//Remove WireframeObject
		void remove(WireframeObject *wo);

		//Remove all WireframeObjects
		void removeAll(std::vector<WireframeObject*> &wo);

		//Add all WireframeObjects
		void addAll(std::vector<WireframeObject*> &wo);


		//Add UIObject
		void add(UIObject *uio);

		//Remove UIObject
		void remove(UIObject *uio);

		//Remove all UIObjects
		void removeAll(std::vector<UIObject*> &uio);

		//Add all UIObjects
		void addAll(std::vector<UIObject*> &uio);


		//Add SpotLight
		void add(SpotLight *sl);

		//Remove SpotLight
		void remove(SpotLight *sl);

		//Remove all SpotLights
		void removeAll(std::vector<SpotLight*> &sl);

		//Add all SpotLights
		void addAll(std::vector<SpotLight*> &sl);


		//Add PointLight
		void add(PointLight *pl);

		//Remove PointLight
		void remove(PointLight *pl);

		//Remove all PointLights
		void removeAll(std::vector<PointLight*> &pl);

		//Add all PointLights
		void addAll(std::vector<PointLight*> &pl);


		//Add DirectionalLight
		void add(DirectionalLight *dl);

		//Remove DirectionalLight
		void remove(DirectionalLight *dl);

		//Remove all DirectionalLights
		void removeAll(std::vector<DirectionalLight*> &dl);

		//Add all DirectionalLights
		void addAll(std::vector<DirectionalLight*> &dl);


		//Set a render option
		void setFlag(ERenderOption option, bool value);

		//Get a render option
		bool getFlag(ERenderOption option);


		//@setter vec3 ambient
		void setAmbient(vec3 ambient);

		//@setter vec3 ambient
		void colorizeAmbient(vec3 colorizer);

		//@return vec3 ambient
		vec3 getAmbient();

		//Reset render engine
		void reset();
	};
}