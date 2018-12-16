#include "Headers/Engine.h"
using namespace lun;

#ifndef __LIBDLL__

#include "Headers/Temporary/GameState.h"

void main() {
	Engine::start<GameState>("Lunar Core example");
}

#endif
