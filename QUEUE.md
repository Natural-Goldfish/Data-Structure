# Queue
  _**Queue**_ 는 _**먼저 입력된 자료가 먼저 출력되는(first in first out)**_ 자료 구조입니다. 기본적으로 자료를 입력하는 _**enqueue**_ 와 입력된 자료를 꺼내는 _**dequeue**_ 를 가지고 있습니다.  
  
  _**List(or array)로 구현된 queue**_ 는 deletion연산이 발생했을 때, front pointer가 가리키는 원소에 pop연산을 적용하고 남아 있는 원소들을 앞으로 한 칸씩 이동합니다. 따라서, _**time complexity**_ 는 _**search, insertion and deletion**_ 에서 ![image](https://user-images.githubusercontent.com/45135668/120778965-90fe0c00-c561-11eb-83a5-79a77e372f12.png) 을 가집니다. 이와 같은 구현 방식은 deletion 이후에 _**list(array)를 재구성하는 과정에서 time complexity가 증가**_ 했고, 이를 개선한 방법들이 고안되었습니다. :  

  - ### Linked List Queue
  - ### Circular Queue

  </br>

  _**Time complexity**_ 는 _**search**_ 에서 ![image](https://user-images.githubusercontent.com/45135668/120778965-90fe0c00-c561-11eb-83a5-79a77e372f12.png) , _**insertion과 deletion**_ 에서는 ![image](https://user-images.githubusercontent.com/45135668/120779062-a7a46300-c561-11eb-9261-8b7af4149ef2.png) 을 가집니다.

  </br>

  - ## Priority Queue(Min-Heap, Max-Heap)
    
  - ## In Python

    Python에서는 entry 검색 순서만 다른, 세 가지 _Queue_ 를 제공합니다. _maxsize_ 를 설정하는 것으로 queue의 범위를 지정할 수 있습니다. 만약, 0 혹은 0보다 작은 음수 값을 설정하는 경우에는 queue의 크기는 infinite 합니다. Queue가 꽉 찬 경우, insertion은 queue의 원소가 비워지기 전까지 무시됩니다.
    
    - ### _class queue.Queue(maxsize=0)_

      _**First In First Out**_ 을 사용하며, 첫 번째로 추가 된 entry가 첫 번째로 검색됩니다. 
    
    - ### _class queue.LifoQueue(maxsize=0)_

      _**Last In First Out**_ 을 사용하며, _Stack_ 과 동일한 동작을 보이며 가장 최근에 추가 된 entry가 첫 번째로 검색됩니다.
      
    - ### _class queue.PrioirtyQueue(maxsize=0)_

      _Priority Queue_ 에서는 _**heapq module**_ 을 사용하여 내부적으로 entries를 정렬하며, 가장 낮은 값을 가진 entry가 첫 번째로 검색됩니다.
    

    
