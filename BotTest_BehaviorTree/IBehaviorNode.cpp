#include "IBehaviorNode.h"
#include <iostream>

void IBehaviorNode::AddChildNode(IBehaviorNode::SPtr childNode)
{
	if (not CanHaveChild())
	{
		std::cout << "AddChildNode() failed with " << GetNodeId() 
			<< " and " << childNode->GetNodeId() << std::endl;
		return;
	}

	childrenNode.emplace_back(childNode);
}