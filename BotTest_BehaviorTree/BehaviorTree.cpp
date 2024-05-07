#include "BehaviorTree.h"

void IBehaviorNode::AddChildNode(IBehaviorNode::SPtr childNode)
{
	childrenNode.emplace_back(childNode);
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