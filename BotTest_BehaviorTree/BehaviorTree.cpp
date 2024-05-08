#include "BehaviorTree.h"
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

void BehaviorTree::AddNode(IBehaviorNode::SPtr node)
{
	nodes.emplace_back(node);
	node->SetNodeId(nodeIdGenerator++);

	if (rootNode == nullptr)
	{
		rootNode = node;
		lastAddedNode = rootNode;
		
		return ;
	}

	lastAddedNode->AddChildNode(node);
}