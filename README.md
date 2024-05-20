클래스 참고

---

* IBehaviorNode는 모든 노드가 상속 받아야 하는 최상위 부모이며, 상속 받은 노드들은 반드시 Do()를 재정의 해야 함
* IDecorator를 상속 받는 노드들은 반드시 자식 노드가 1개만 존재할 수 있음

---

1. BehaviorAction

실제 행동을 취할 수 있게 하는 노드

아래와 같이 지정할 행동을 BehaviorActionType으로 등록하고 BehaviorStatus 반환값을 지정

![image](https://github.com/m5623skhj/BotTest_BehaviorTree/assets/42509418/f94f4997-f904-4cce-98db-15816d25d10e)

위 노드의 경우, 추가적인 자식 노드를 가질 수 없음

---

2. BehaviorCondition

외부에서 참 거짓을 판별할 수 있는 효과를 추가하여 

해당 내용이 거짓일 경우 즉시 Failure를, 참일 경우 자식 노드들을 순회하여 결과를 반환하게 하는 노드

아래와 같이 판별식을 BehaviorCondition으로 등록하고 bool 반환값을 지정

![image](https://github.com/m5623skhj/BotTest_BehaviorTree/assets/42509418/3b344305-1a03-44e6-b5be-42ab9c04ba32)

---

3. BehaviorSequence

자식 노드가 모두 성공해야 Success를 반환하는 노드

---

4. BehaviorSelector

자식 노드들 중 하나라도 Success를 반환하면 이후의 평가를 취소하고 즉시 Success를 반환하는 노드

---

5. DecoratorLoop

자식 노드들을 임의의 값 만큼 순회시키는 노드

생성시에 루프를 몇 회 반복할지, 한 번에 모든 순회를 처리할지 등을 인자로 넣음

---

6. DecoratorInverter

모든 자식 노드들의 평가가 Failure라면 Success를, 하나의 자식 노드라도 평가가 Success라면 Failure를 반환하는 노드

---

7. DecoratorDelay

해당 노드 이후의 모든 노드들에 대해서 외부에서 지정한 시간(단위 : ms)만큼 지연하여 평가하는 노드

---

8. DecoratorRetry

Success가 아닌 상황에 대해서, 외부에서 지정한 값 만큼 재시도를 해보는 노드

---

참고 자료 :

https://github.com/draghan/behavior_tree/tree/master
