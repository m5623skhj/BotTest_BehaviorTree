#include <iostream>
#include "BehaviorTree.h"
#include "BehaviorNode.h"
#include "Decorator.h"
#include <Windows.h>

class Actor
{
public:
	Actor() = default;
	~Actor() = default;

public:
	void AddNodeToTree(IBehaviorNode::SPtr node, const NodeIdType targetParentNodeId, const NodeIdType myNodeId)
	{
		behaviorTree.AddChildNode(node, targetParentNodeId, myNodeId);
	}

	BehaviorStatus DoAction()
	{
		return behaviorTree.Tick();
	}

private:
	BehaviorTree behaviorTree;
};

std::chrono::system_clock::time_point ParseTimePoint(const std::string& timeStr) 
{
	std::istringstream ss(timeStr);
	std::tm tm = {};
	ss >> std::get_time(&tm, "%Y-%m-%d %H:%M:%S");
	if (ss.fail()) {
		throw std::runtime_error("Failed to parse time string");
	}
	return std::chrono::system_clock::from_time_t(std::mktime(&tm));
}

int main()
{
	Actor testActor;

	BehaviorSelector::SPtr selector = std::make_shared<BehaviorSelector>();
	BehaviorSequence::SPtr sequence1 = std::make_shared<BehaviorSequence>();
	BehaviorSequence::SPtr sequence2 = std::make_shared<BehaviorSequence>();
	testActor.AddNodeToTree(selector, 0, 0);
	testActor.AddNodeToTree(sequence1, 0, 1);
	testActor.AddNodeToTree(sequence2, 0, 2);

	DecoratorDelay::SPtr delay = std::make_shared<DecoratorDelay>(3000);
	testActor.AddNodeToTree(delay, 1, 3);

	DecoratorLoop::SPtr loop = std::make_shared<DecoratorLoop>(5, false);
	testActor.AddNodeToTree(loop, 3, 4);

	BehaviorCondition::SPtr condition = std::make_shared<BehaviorCondition>([] {
		if (std::chrono::system_clock::now() > ParseTimePoint("2024-05-15 19:00:00"))
		{
			return true;
		}

		return false;
		});
	testActor.AddNodeToTree(condition, 4, 5);

	BehaviorAction::SPtr action = std::make_shared<BehaviorAction>([] {
		std::cout << "BehaviorAction : Start" << std::endl;
		return BehaviorStatus::Success;
		});
	testActor.AddNodeToTree(action, 5, 6);

	BehaviorAction::SPtr secondAction = std::make_shared<BehaviorAction>([] {
		std::cout << "BehaviorAction : Second start" << std::endl;
		return BehaviorStatus::Success;
		});
	testActor.AddNodeToTree(action, 2, 7);

	while (true)
	{
		const auto& result = testActor.DoAction();
		Sleep(100);
	}

	return 0;
}