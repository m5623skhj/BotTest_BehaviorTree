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

bool BehaviorTree::AddChildNode(IBehaviorNode::SPtr node)
{
	if (node == nullptr)
	{
		return false;
	}

	nodes.emplace_back(node);
	node->SetNodeId(nodeIdGenerator++);

	if (rootNode == nullptr)
	{
		rootNode = node;
		lastAddedNode = rootNode;
		
		return true;
	}

	lastAddedNode->AddChildNode(node);
	lastAddedNode = node;

	return true;
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

	if (nodeMap.insert({ myNodeId, node }).second == false)
	{
		return false;
	}

	lastAddedNode = rootNode;
	nodeMap[targetParentNodeId]->AddChildNode(node);

	return true;
}

bool BehaviorTree::AddRootNode(IBehaviorNode::SPtr node)
{
	if (node == nullptr ||
		rootNode != nullptr)
	{
		return false;
	}

	rootNode = node;
	lastAddedNode = rootNode;
	nodeMap.insert({ 0, node });

	return true;
}
