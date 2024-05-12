#include "BehaviorNode.h"
#include <utility>

void IBehaviorNode::AddChildNode(IBehaviorNode::SPtr childNode)
{
	childrenNode.emplace_back(childNode);
}

BehaviorAction::BehaviorAction(BehaviorActionType&& inAction)
	: action(std::move(inAction))
{
}

BehaviorStatus BehaviorAction::Do()
{
	if (action)
	{
		return action();
	}

	return BehaviorStatus::Failure;
}

BehaviorCondition::BehaviorCondition(BehaviorConditionType&& inCondition)
	: condition(std::move(inCondition))
{
}

BehaviorStatus BehaviorCondition::Do()
{
	return BehaviorStatus::Success;
}
