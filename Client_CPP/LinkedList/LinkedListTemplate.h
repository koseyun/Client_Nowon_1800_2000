#pragma once

// 구조체 vs 클래스
// 멤버들을 뭉쳐서 하나의 자료형으로 관리해야 할 때,
// 구조체와 클래스 중에 어떤 것을 사용하는 것이 적합한지를 판단하는 기준은 일반적으로
// 
// 1. 멤버들의 데이터 총 량이 16byte 이하면 구조체, 이상이면 클래스
// 구조체 객체를 인자로 전달할 때는 모든 멤버의 값을 복사하고,
// 클래스 객체를 인자로 전달할 때는 해당 객체의 주소를 복사한다.
// 구조체 객체의 장점은 값을 직접 복사해서 쓰므로
// 주소를 가져와서 간접 참조해야하는 클래스보다 기본적으로 빠르다.
// 하지만 레지스터의 크기가 16byte 이기 때문에 구조체의 멤버 데이터 총 량이 16byte 를 넘어가게 되면
// 값을 읽어들이고 쓰는데 두배 이상의 시간이 소요되며,
// 이런 경우에는 클래스 객체의 간접 참조보다 느리다.
// 
// 2. 데이터 세팅을 위한 테이블 용도로 사용할 때 ( 함수의 인자로 전달하거나 객체를 수정할 일이 거의 없을 때 )
// 객체간의 상호작용보다는 단순히 값을 가져다 쓰기 위한 테이블이라는 것을
// 명확하게 표현하기 좋기 때문에 이런 경우 16byte 를 넘겨도 종종 사용할 수 있다.
// 
// 구조체 vs 클래스 선정 기준에 정답은 없지만 보편적으로 위 기준으로 선정함.
template <typename T>
class Node
{
	T _item;
	Node* _prev;
	Node* _next;
};

template <typename T>
class LinkedList
{
	Node* _first, * _last, * _tmp, * _tmp2;

	// (더블리) 링크드 리스트 템플릿 구현해보기
	// C 때 했던거 참고
	// 멤버함수는
	// void AddFirst(T item)
	// void AddLast(T item)
	// void AddAfter(Node& node, T item)
	// void AddBefore(Node& node, T item)
	// Node<T>& First()
	// Node<T>& Last()
	// Node<T>& Find(T item)
	// Node<T>& FindLast(T item)
	// bool Remove(T item)
	// bool RemoveLast(T item)
	// void Delete()
	void AddFirst(T _item);

	void AddLast(T _item);

	void AddAfter(Node& node, T item);

	void AddBefore(Node& node, T item);

	Node<T>& First();

	Node<T>& Last();

	Node<T>& Find(T item);

	Node<T>& FindLast(T item);

	bool Remove(T item);
	
	bool RemoveLast(T item);
	
	void Delete();

};
/// <summary>
/// 리스트의 가장 앞에 신규 노드 삽입하는 함수
/// </summary>
template<typename T>
inline void LinkedList<T>::AddFirst(T _item)
{
	_tmp = new Node<T>(); // 신규노드 생성
	_tmp->_item = item; // 신규노드 값 대입

	// first 가 존재함 ?
	if (_first != nullptr) {
		_tmp->_next = _first; // 신규노드의 다음 노드가 first 를 가리키게 한다.
		_first->_prev = _tmp; // first 의 이전 노드가 신규 노드를 가리키게 한다.
	}

	// last 가 존재안함?
	// : 이번 신규노드가 가장 처음으로 생성된 노드다
	// 즉, first 와 last 포인터가 둘다 신규노드를 가리켜야 한다.
	if (_last == nullptr) {
		_last = _tmp;
		// _first = _tmp; // 어차피 마지막에 first 가 신규노드를 가리키게 할거니까 생략가능
	}

	_first = _tmp; // 추가 완료되었으니 first 가 신규 노드를 가리키게 함
}

/// <summary>
/// 리스트의 가장 뒤에 신규 노드 삽입하는 함수
/// </summary>
template<typename T>
inline void LinkedList<T>::AddLast(T _item)
{
	_tmp = new Node<T>(); // 신규노드 생성
	_tmp->_item = item; // 신규노드 값 대입

	// last 가 존재함 ?
	if (_last != nullptr) {
		_tmp->_prev = _last; // 신규노드의 다음 노드가 last 를 가리키게 한다.
		_last->_next = _tmp; // last 의 다음 노드가 신규 노드를 가리키게 한다.
	}

	// first 가 존재안함?
	// : 이번 신규노드가 가장 처음으로 생성된 노드다
	// 즉, first 와 last 포인터가 둘다 신규노드를 가리켜야 한다.
	if (_last == nullptr)
		//_last = _tmp; // 어차피 마지막에 first 가 신규노드를 가리키게 할거니까 생략가능
		_first = _tmp;
	}

	_last = _tmp; // 추가 완료되었으니 last가 신규 노드를 가리키게 함

	/*_tmp = new Node<T>();
	_tmp->_item = item;
	if (_last != nullptr)
		_tmp->_prev = _last;
	_last->_next = _tmp;

	if (_first == nullptr)
		_first = _tmp;
	_first = _tmp;*/
}

template<typename T>
inline void LinkedList<T>::AddAfter(Node& node, T item)
{
	_tmp = _first;
	while (_tmp != NULL)
	{
		if (_tmp->_item == node) {
			_tmp2 = new Node<T>();

			_tmp2->_next = _tmp->_next;
			_tmp->_next = _tmp2;
			_tmp2 = in_item;
			return;
		}
		_tmp = _tmp->_next;
	}
	return;
}

template<typename T>
inline void LinkedList<T>::AddBefore(Node& node, T item)
{
}
