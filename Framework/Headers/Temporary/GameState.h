#pragma once
#include "../State/State.h"
class GameState : public lun::State {
public:

	void init() override;
	void update(f64 delta) override;
};