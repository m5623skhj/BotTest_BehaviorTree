#pragma once
#include "IBehaviorNode.h"

class DecoratorLoop : public IBehaviorNode
{
public:
	DecoratorLoop() = delete;
	explicit DecoratorLoop(unsigned short inMaxLoopCount);
	~DecoratorLoop() override = default;

public:
	BehaviorStatus Do() override;

private:
	const unsigned short maxLoopCount;
	unsigned short loopCount{};

	bool resetFlag{};
};

class DecoratorInverter : public IBehaviorNode
{
public:
	DecoratorInverter() = default;
	~DecoratorInverter() = default;

public:
	BehaviorStatus Do() override;
};