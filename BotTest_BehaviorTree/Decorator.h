#pragma once
#include "IBehaviorNode.h"

class DecoratorLoop : public IBehaviorNode
{
public:
	DecoratorLoop() = delete;
	explicit DecoratorLoop(NodeIdType inTargetNodeId, unsigned short inMaxLoopCount);
	~DecoratorLoop() override = default;

public:
	BehaviorStatus Do() override;

private:
	const unsigned short maxLoopCount;
	unsigned short loopCount{};

	NodeIdType nodeId{};

	bool resetFlag{};
};