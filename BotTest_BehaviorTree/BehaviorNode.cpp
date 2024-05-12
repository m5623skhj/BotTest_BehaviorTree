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

	return BehaviorStatus::InvalidType;
}

BehaviorCondition::BehaviorCondition(BehaviorConditionType&& inCondition)
	: condition(std::move(inCondition))
{
}

BehaviorStatus BehaviorCondition::Do()
{
	return BehaviorStatus::Success;
}

BehaviorStatus BehaviorSequence::Do()
{
	if (childrenNode.empty() == true)
	{
		return BehaviorStatus::InvalidType;
	}

	for (auto id = GetNodeId(); id < childrenNode.size(); ++id)
	{
		const auto& status = childrenNode.at(id)->Do();
		if (status != BehaviorStatus::Success)
		{
			return status;
		}
	}

	return BehaviorStatus::Success;
}

BehaviorStatus BehaviorSelector::Do()
{
	if (childrenNode.empty() == true)
	{
		return BehaviorStatus::InvalidType;
	}

	for (auto id = GetNodeId(); id < childrenNode.size(); ++id)
	{
		const auto& status = childrenNode.at(id)->Do();
		if (status != BehaviorStatus::Success)
		{
			return status;
		}
	}

	return BehaviorStatus::Failure;
}