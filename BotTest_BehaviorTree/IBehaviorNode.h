#pragma once
#include <vector>
#include <memory>

enum class BehaviorStatus
{
	InvalidType = 0,
	Success,
	Failure,
	Running,
};
using NodeIdType = unsigned int;

class IBehaviorNode
{
public:
	using SPtr = std::shared_ptr<IBehaviorNode>;

public:
	virtual ~IBehaviorNode() = default;

public:
	void AddChildNode(IBehaviorNode::SPtr childNode);
	virtual BehaviorStatus Do() = 0;

public:
	NodeIdType GetNodeId() { return nodeId; }
	void SetNodeId(NodeIdType inNodeId) { nodeId = inNodeId; }

protected:
	std::vector<IBehaviorNode::SPtr> childrenNode{};

private:
	NodeIdType nodeId{};
};
