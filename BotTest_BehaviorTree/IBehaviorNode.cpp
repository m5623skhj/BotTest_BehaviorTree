#include "IBehaviorNode.h"
#include <iostream>

void IBehaviorNode::AddChildNode(IBehaviorNode::SPtr childNode)
{
	if (not CanAddChild())
	{
		std::cout << "AddChildNode() failed with " << GetNodeId() 
			<< " and " << childNode->GetNodeId() << std::endl;
		return;
	}

	childrenNode.emplace_back(childNode);
}