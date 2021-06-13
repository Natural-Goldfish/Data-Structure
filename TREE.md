# Tree

  
  _**Tree**_ 는 _**cycle이 없는 connected graph의 일환으로**_ , value나 condition을 포함하는 _**node**_ 와, 이러한 node를 연결하는 _**edge**_ 로 구성되어 있습니다.  
  
  _**Root node**_ 는 tree의 최상단에 위치한 _**부모 노드가 없는 노드**_ 를 의미합니다.  
  
  _**Leaf node**_ 는 tree의 말단에 위치하여 _**자식 노드가 없는 노드**_ 를 의미합니다.  
  
  _**Internal node**_ 는 _**leaf node와 root node 를 제외한 다른 노드**_ 를 의미합니다.  
  
  _**Path**_ 는 임의의 A node부터 B node까지 _**인접한 node들로 이루어진 sequence**_ 를 의미합니다.  
  
  _**Height**_ 는 _**root node에서 leaf node까지 가능한 경로중에서 가장 긴 경로**_ 를 의미합니다.  
  
  </br>

  - ## Binary Tree(이진 트리)

    _**Binary Tree**_ 는 _**자식 노드가 최대 2개로 제한된 tree**_ 입니다.  
    
    _**Perfect Binary Tree(포화 이진 트리)**_ 는 _**leaf node를 제외한 모든 노드가 2개의 자식 노드를 가지는 트리**_ 를 의미합니다.  
    
    _**Complete Binary Tree(완전 이진 트리)**_ 는 _**perfect binary tree에서 마지막 level의 우측 노드를 하나씩 제거하여 얻은 트리**_ 를 의미합니다.  

    _**Skewed Binary Tree(편향 이진 트리)**_ 는 _**모든 노드가 부모 노드의 왼쪽에 존재하거나, 우측에 존재하는 트리**_ 를 의미합니다.  
    
    </br>
    
    - ### Binary Tree Traversal(이진 트리 순회)
      ---
      
      - #### Preorder Traversal(전위 순회)
        _**Current Node -> Left Sub-Tree -> Right Sub-Tree**_ 순으로 순회합니다.
      - #### Inorder Traversal(중위 순회)
        _**Left Sub-Tree -> Current Node -> Right Sub-Tree**_ 순으로 순회합니다.
      - #### Postorder Traversal(후위 순회)
        _**Left Sub-Tree -> Right Sub-Tree -> Current Node**_ 순으로 순회합니다.
      - #### Level-Order Traversal    

    </br>

    - ### Binary Search Tree(이진 탐색 트리)
      ---
      
      _**Binary Search Tree**_ 는 _**binary search**_ 와 _**linked list**_ 를 결합한 자료구조의 일환으로, 효율적인 탐색 능력을 유지하면서도 빈번한 삽입과 삭제를 가능하게 하고자 고안되었습니다.
      - Binary search에서 탐색은 ![image](https://user-images.githubusercontent.com/45135668/120072205-9379e500-c0cd-11eb-8c3f-053d40ad5c79.png) 이 소요 되지만, 삽입과 삭제가 불가능 하다는 단점이 있습니다.
      - Linked list의 경우, 삽입과 삭제는 ![image](https://user-images.githubusercontent.com/45135668/120072230-bc9a7580-c0cd-11eb-81a7-9a1891b32483.png) 로 효율적이지만, 탐색은 ![image](https://user-images.githubusercontent.com/45135668/120072243-cb812800-c0cd-11eb-89fd-224b0dd7bb1b.png) 으로 삽입과 삭제 연산에 비해 상대적으로 높은 비용이 소모됩니다.
       
      </br>

      _**Binary Search Tree**_ 는 아래와 같은 특징을 가집니다.  
      
      - _**Left node**_ 는 _**parent node보다 작은 값**_ 을 가져야 합니다.
      - _**Right node**_ 는 _**parent node보다 큰 값**_ 을 가져야 합니다.
      - _**중복된 노드를 가지지 않습니다.**_
      - _**왼쪽 서브 트리와 오른쪽 서브 트리 또한 binary search tree입니다.**_

      </br>

      _**Time complexity**_ 는 평균적으로 ![image](https://latex.codecogs.com/gif.latex?O%28log%5C%3A%20n%29) 가 소요되지만, worst case(좌측 혹은 우측으로 편향된 경우)에는 ![image](https://latex.codecogs.com/gif.latex?O%28n%29) 가 소요됩니다.  
      
      </br>

      - #### Insertion
      - #### Deletion
        - #### No Children
          삭제 대상 노드를 삭제합니다.
        - #### One Child
          _**Child node가 삭제된 노드를 대체합니다.**_
        - #### Two Children
          삭제되는 노드의 _**왼쪽 서브 트리에서 가장 오른쪽에 있는 노드**_ 혹은 _**오른쪽 서브 트리에서 가장 왼쪽에 있는 노드**_ 가 삭제되는 노드를 대체합니다.

    </br>

    - ### Segment/Statistic Tree(세그먼트 트리)
      ---
      
      _**Segment Tree**_ 는 _**각 노드가 배열의 부분 합을 나타내는 binary tree의 종류 중 하나 입니다.**_  
      
      _**Leaf node**_ 는  _**해당 index의 배열의 값**_ 을 의미합니다.  
      
      _**Other nodes**_ 는 _**임의의 배열<sub>i</sub> ~ 배열<sub>k</sub>(k > i >= 1) 사이의 부분 합**_ 을 의미합니다.

    </br>
  
    - ### Heap
      ---
      
      - ### Heap Sort

    </br>
    
  </br>    
    
  - ## Balanced Tree(균형 트리)
    
    - ### Adelson-Velsky and Landis Tree(AVL Tree)
    - ### Red-Black Tree
    - ### B-Tree
