#pragma once
#include "BehaviorNode.h"

class BehaviorTree
{
public:
	BehaviorTree() = default;
	~BehaviorTree() = default;

public:
	bool Tick();
	void SetTickDuration(const unsigned int inTickDurationMilisecond);

public:
	void AddNode(IBehaviorNode::SPtr node);

public:
	size_t GetBehaviorTreeSize() { return nodes.size(); }

private:
	IBehaviorNode::SPtr rootNode = nullptr;
	IBehaviorNode::SPtr lastAddedNode = nullptr;
	std::vector<IBehaviorNode::SPtr> nodes{};

	NodeIdType nodeIdGenerator{};

	unsigned int tickDurationMilisecond{};
};