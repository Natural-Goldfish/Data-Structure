- # Queue

  - ## Better
    - ### Linked-List Queue
    - ### Circular Queue

  - ## Priority Queue(Min-Heap, Max-Heap)
    
  - ## In Python

    Python에서는 entry 검색 순서만 다른, 세 가지 _Queue_ 를 제공합니다. _maxsize_ 를 설정하는 것으로 queue의 범위를 지정할 수 있습니다. 만약, 0 혹은 0보다 작은 음수 값을 설정하는 경우에는 queue의 크기는 infinite 합니다. Queue가 꽉 찬 경우, insertion은 queue의 원소가 비워지기 전까지 무시됩니다.
    
    - ### _class queue.Queue(maxsize=0)_

      _First In First Out_ 을 사용하며, 첫 번째로 추가 된 entry가 첫 번째로 검색됩니다. 
    
    - ### _class queue.LifoQueue(maxsize=0)_

      _Last In First Out_ 을 사용하며, _Stack_ 과 동일한 동작을 보이며 가장 최근에 추가 된 entry가 첫 번째로 검색됩니다.
      
    - ### _class queue.PrioirtyQueue(maxsize=0)_
    - 
      _Priority Queue_ 에서는 _heapq module_ 을 사용하여 내부적으로 entries를 정렬하며, 가장 낮은 값을 가진 entry가 첫 번째로 검색됩니다.
    

    
