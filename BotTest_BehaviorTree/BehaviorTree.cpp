#include "BehaviorTree.h"

BehaviorStatus BehaviorTree::Tick()
{
	if (rootNode == nullptr)
	{
		return BehaviorStatus::InvalidType;
	}

	return rootNode->Do();
}

void BehaviorTree::SetTickDuration(const unsigned int inTickDurationMilisecond)
{
	tickDurationMilisecond = inTickDurationMilisecond;
}

bool BehaviorTree::AddRootNode(IBehaviorNode::SPtr node)
{
	return AddChildNode(node, 0, 0);
}

bool BehaviorTree::AddChildNode(IBehaviorNode::SPtr node, const NodeIdType targetParentNodeId, const NodeIdType myNodeId)
{
	if (node == nullptr)
	{
		return false;
	}

	if (myNodeId == 0)
	{
		if (rootNode != nullptr)
		{
			return false;
		}

		rootNode = node;
		lastAddedNode = rootNode;
		nodeMap.insert({ 0, node });

		return true;
	}

	const auto& parentNode = nodeMap.find(targetParentNodeId);
	if (parentNode == nodeMap.end() ||
		parentNode->second == nullptr ||
		parentNode->second->CanAddChild() == false)
	{
		return false;
	}

	if (nodeMap.insert({ myNodeId, node }).second == false)
	{
		return false;
	}

	lastAddedNode = rootNode;
	parentNode->second->AddChildNode(node);

	return true;
}