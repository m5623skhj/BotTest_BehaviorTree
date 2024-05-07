#pragma once
#include <vector>
#include <memory>

enum class BehaviorStatus
{
	Success = 0,
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

public:
	NodeIdType GetNodeId() { return nodeId; }
	void SetNodeId(NodeIdType inNodeId) { nodeId = inNodeId; }

private:
	NodeIdType nodeId{};

private:
	std::vector<IBehaviorNode::SPtr> childrenNode{};
};

class BehaviorTree
{
public:
	BehaviorTree() = default;
	~BehaviorTree() = default;

public:
	void AddNode(IBehaviorNode::SPtr node);

public:
	size_t GetBehaviorTreeSize() { return nodes.size(); }

private:
	IBehaviorNode::SPtr rootNode = nullptr;
	IBehaviorNode::SPtr lastAddedNode = nullptr;
	std::vector<IBehaviorNode::SPtr> nodes{};

	NodeIdType nodeIdGenerator{};
};