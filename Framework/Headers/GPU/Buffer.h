#pragma once
#include "../CrossPlatform/CrossPlatform.h"
#include "../Helper/OGLHelper.h"
#include <vector>
namespace lun {
	template<class CPUClass, class GPUClass> class Buffer {

	public:

		Buffer(): gpuBuffer(0){}

		~Buffer() {
			destroyBuffer();

			for (u32 i = 0; i < cpuBuffer.size(); ++i)
				delete cpuBuffer[i];
		}

		bool hasBuffer() { return gpuBuffer != 0; }

		void add(CPUClass *cpuc, bool recalculateBuffer = true) { cpuBuffer.push_back(cpuc); cpuc->link(this); if (recalculateBuffer) refreshBuffer(); }

		void addAll(std::vector<CPUClass*> &classes, bool recalculateBuffer = true) {
			u32 oldSize;
			cpuBuffer.resize((oldSize = (u32)cpuBuffer.size()) + (u32)classes.size());
			for (u32 i = 0; i < classes.size(); ++i) {
				cpuBuffer[oldSize + i] = classes[i];
				classes[i]->link(this);
			}

			if (recalculateBuffer)
				refreshBuffer();
		}

		bool remove(CPUClass *cpuc, bool recalculateBuffer=true) {
			for (u32 i = 0; i < cpuBuffer.size(); ++i)
				if (cpuBuffer[i] == cpuc) {
					delete cpuBuffer[i];
					cpuBuffer.erase(cpuBuffer.begin() + i);

					if (recalculateBuffer)
						refreshBuffer();

					return true;
				}
			return false;
		}

		void removeAll(std::vector<CPUClass*> &classes, bool recalculateBuffer = true) {
			for (u32 i = 0; i < classes.size(); ++i)
				for (u32 j = 0; j < cpuBuffer.size(); ++j)
					if (cpuBuffer[j] == classes[i]) {
						delete[] cpuBuffer[j];
						cpuBuffer.erase(cpuBuffer.begin() + j);
					}

			if (recalculateBuffer)
				refreshBuffer();
		}

		void refreshBuffer() {
			destroyBuffer();

			GPUClass *classes = new GPUClass[cpuBuffer.size()];
			for (u32 i = 0; i < cpuBuffer.size(); ++i) 
				classes[i] = cpuBuffer[i]->getData();

			gpuBuffer = OGLHelper::createSSBO((GLubyte*)classes, sizeof(GPUClass) * (u32)cpuBuffer.size());
			delete[] classes;
		}

		void update() {
			if (gpuBuffer == 0)return;

			for (u32 i = 0; i < toUpdate.size(); ++i) {
				u32 j = indexOf(cpuBuffer, toUpdate[i]);
				if (j == cpuBuffer.size())continue;
				GPUClass g = cpuBuffer[j]->getData();
				OGLHelper::updateSSBO(gpuBuffer, j * sizeof(GPUClass), sizeof(GPUClass), (GLubyte*)&g);
			}

			toUpdate.clear();
		}
		
		void bind(u32 i=3) {
			OGLHelper::bindSSBO(gpuBuffer, i);
		}

		void edit(CPUClass *c) {
			u32 i = indexOf(toUpdate, c);
			if (i != toUpdate.size())return;
			toUpdate.push_back(c);
		}

		u32 size() { return (u32)cpuBuffer.size(); }

		void clear() {
			destroyBuffer();
			for (u32 i = 0; i < cpuBuffer.size(); ++i)
				delete cpuBuffer[i];
			cpuBuffer.clear();
			toUpdate.clear();
		}

	protected:

		void destroyBuffer() {
			if (!hasBuffer())return;
			OGLHelper::destroySSBO(gpuBuffer);
			gpuBuffer = 0;
		}

	private:

		std::vector<CPUClass*> cpuBuffer;
		std::vector<CPUClass*> toUpdate;
		GLuint gpuBuffer;

		u32 indexOf(std::vector<CPUClass*> v, CPUClass *c) {
			for (u32 i = 0; i < v.size(); ++i)
				if (v[i] == c)
					return i;
			return (u32)v.size();
		}
	};
}