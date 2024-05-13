#pragma once
#include "IBehaviorNode.h"
#include <functional>

using BehaviorActionType = std::function<BehaviorStatus()>;

class BehaviorAction : public IBehaviorNode
{
public:
	BehaviorAction() = delete;
	explicit BehaviorAction(BehaviorActionType&& inAction);
	~BehaviorAction() override = default;

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
	~BehaviorCondition() override = default;

public:
	BehaviorStatus Do() override;

private:
	BehaviorConditionType condition;
};

class BehaviorSequence : public IBehaviorNode
{
public:
	BehaviorSequence() = default;
	~BehaviorSequence() override = default;

public:
	BehaviorStatus Do() override;
};

class BehaviorSelector : public IBehaviorNode
{
public:
	BehaviorSelector() = default;
	~BehaviorSelector() override = default;

public:
	BehaviorStatus Do() override;
};