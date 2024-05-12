#pragma once
#include <vector>
#include <memory>
#include <functional>

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

private:
	NodeIdType nodeId{};

private:
	std::vector<IBehaviorNode::SPtr> childrenNode{};
};

using BehaviorActionType = std::function<BehaviorStatus()>;

class BehaviorAction : public IBehaviorNode
{
public:
	BehaviorAction() = delete;
	explicit BehaviorAction(BehaviorActionType&& inAction);
	virtual ~BehaviorAction() = default;

public:
	BehaviorStatus Do() override;

private:
	BehaviorActionType action;
};

using BehaviorConditionType = std::function<bool()>;

class BehaviorCondition : public IBehaviorNode
{
public:
	BehaviorCondition() = delete;
	explicit BehaviorCondition(BehaviorConditionType&& inCondition);
	virtual ~BehaviorCondition() = default;

public:
	BehaviorStatus Do() override;

private:
	BehaviorConditionType condition;
};
