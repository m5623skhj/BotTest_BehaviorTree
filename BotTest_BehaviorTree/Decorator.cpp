#include "Decorator.h"
#include <iostream>

DecoratorLoop::DecoratorLoop(NodeIdType inTargetNodeId, unsigned short inMaxLoopCount)
	: nodeId(inTargetNodeId)
	, maxLoopCount(inMaxLoopCount)
{
}

BehaviorStatus DecoratorLoop::Do()
{
	if (childrenNode.empty() == true)
	{
		return BehaviorStatus::InvalidType;
	}

	for (; loopCount < maxLoopCount; ++loopCount)
	{
		auto result = childrenNode[nodeId]->Do();
		switch (result)
		{
		case BehaviorStatus::Success:
			break;
		case BehaviorStatus::InvalidType:
		case BehaviorStatus::Failure:
			resetFlag = false;
			return result;
		case BehaviorStatus::Running:
			resetFlag = true;
			return result;
		default:
			std::cout << "DecoratorLoop::Do() : Invalid result type " << static_cast<unsigned int>(result) << std::endl;
			break;
		}
	}

	resetFlag = true;
	return BehaviorStatus::Success;
}