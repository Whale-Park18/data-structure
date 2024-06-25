#pragma once
#include "node.h"

#include <iostream>
#include <stdexcept>
#include <cmath>

namespace park18::types
{
	template<typename T>
	class List
	{
	public:
		List();

		//---------------------------------------------------
		// 추가
		//---------------------------------------------------
		
		/// <summary>
		/// 앞쪽에서 추가
		/// </summary>
		/// <param name="data">데이터</param>
		void PushFront(T data);

		/// <summary>
		/// 뒤쪽에서 추가
		/// </summary>
		/// <param name="data">데이터</param>
		void PushBack(T data);

		/// <summary>
		/// InserIndex 위치에 추가
		/// </summary>
		/// <param name="data">데이터</param>
		/// <param name="insertIndex">삽입할 인덱스</param>
		void Insert(T data, size_t insertIndex);

		//---------------------------------------------------
		// 제거
		//---------------------------------------------------

		/// <summary>
		/// 모든 요소를 제거
		/// </summary>
		void Clear();

		/// <summary>
		/// 리스트의 맨 앞 요소 제거
		/// </summary>
		/// <returns>레스트의 맨 앞 요소</returns>
		T PopFront();

		/// <summary>
		/// 리스트의 맨 뒤 요소 제거
		/// </summary>
		/// <returns>리스트의 맨 뒤 요소</returns>
		T PopBack();

		/// <summary>
		/// 리스트의 index 요소를 제거
		/// </summary>
		/// <param name="index">삭제할 index</param>
		/// <returns>삭제할 리스트의 요소</returns>
		T Erase(size_t index);

		//---------------------------------------------------
		// 접근
		//---------------------------------------------------
		
		/// <summary>
		/// index에 위치한 데이터를 반환
		/// </summary>
		/// <param name="index">접근할 데이터 인덱스</param>
		/// <returns>index에 위치한 데이터</returns>
		T At(size_t index) const;

		//---------------------------------------------------
		// 유틸
		//---------------------------------------------------

		/// <summary>
		/// 리스트의 크기 반환
		/// </summary>
		/// <returns>현재 리스트 크기</returns>
		size_t GetSize() const;

		/// <summary>
		/// 현재 리스트가 비어있는지 확인
		/// </summary>
		/// <returns>비어있으면 true, 값이 있으면 false</returns>
		bool IsEmpty() const;

		/// <summary>
		/// 리스트의 요소들을 출력
		/// </summary>
		void Print() const;

	private:

		/// <summary>
		/// index의 값이 옳바른 범위인지 확인
		/// </summary>
		/// <param name="index"></param>
		/// <returns></returns>
		bool isRightRange(size_t index) const;

		/// <summary>
		/// index에 위치한 노드 반환
		/// </summary>
		/// <param name="index">접근할 노드 인덱스</param>
		/// <returns>index에 위치한 노드</returns>
		Node<T>* visitAt(size_t index) const;

		/// <summary>
		/// 노드 추가
		/// </summary>
		/// <param name="data">데이터</param>
		/// <param name="pHead">신규 노드의 head</param>
		/// <param name="pBack">신규 노드의 back</param>
		/// <returns>신규 노드 포인터</returns>
		Node<T>* Add(T data, Node<T>* pHead, Node<T>* pBack);

		/// <summary>
		/// pDeleteNode 삭제
		/// </summary>
		/// <param name="pDeleteNode">삭제할 노드</param>
		void Delete(Node<T>* pDeleteNode);

	private:
		Node<T>* pFront_;
		Node<T>* pBack_;

		size_t size_;
	};
}

template<typename T>
inline park18::types::List<T>::List() : pFront_(nullptr), pBack_(nullptr), size_(0)
{
}

template<typename T>
inline void park18::types::List<T>::PushFront(T data)
{
	Node<T>* newNode = this->Add(data, pBack_, pFront_);

	// 리스트의 앞, 뒤 포인터 갱신
	pFront_ = newNode;
	pBack_ = pBack_ == nullptr ? newNode : pBack_;
}

template<typename T>
inline void park18::types::List<T>::PushBack(T data)
{
	Node<T>* newNode = this->Add(data, pBack_, pFront_);

	// 리스트의 앞, 뒤 포인터 갱신
	pBack_ = newNode;
	pFront_ = pFront_ == nullptr ? newNode : pFront_;
}

template<typename T>
inline void park18::types::List<T>::Insert(T data, size_t insertIndex)
{
	Node<T>* backNode = this->visitAt(insertIndex);
	if (backNode == nullptr)
	{
		throw std::out_of_range("out of range index");
	}
	Node<T>* headNode = backNode->GetHead();
	Node<T>* newNode = this->Add(data, headNode, backNode);
	
	if (insertIndex == 0)
	{
		pFront_ = newNode;
	}
	else if (insertIndex == size_ - 1)
	{
		pBack_ = newNode;
	}
}

template<typename T>
inline void park18::types::List<T>::Clear()
{
	Node<T>* node = pFront_;
	for (int i = 0; i < size_; i++)
	{
		Node<T>* nextNode = node->GetNext();
		delete(node);
		node = nextNode;
	}

	size_ = 0;
	pFront_ = nullptr;
	pBack_ = nullptr;
}

template<typename T>
inline T park18::types::List<T>::PopFront()
{
	if (pFront_ == nullptr)
	{
		throw std::runtime_error("pFront is nullptr");
	}

	return this->Erase(0);
}

template<typename T>
inline T park18::types::List<T>::PopBack()
{
	if (pBack_ == nullptr)
	{
		throw std::runtime_error("pFront is nullptr");
	}

	return this->Erase(size_ - 1);
}

template<typename T>
inline T park18::types::List<T>::Erase(size_t index)
{
	Node<T>* node = this->visitAt(index);
	if (node == nullptr)
	{
		throw std::out_of_range("out of range index");
	}

	if (index == 0)
	{
		pFront_ = node->GetNext();
	}
	else if (index == size_ - 1)
	{
		pBack_ = node->GetHead();
	}
	T tempData = node->GetData();

	this->Delete(node);

	return tempData;
}

template<typename T>
inline T park18::types::List<T>::At(size_t index) const
{
	Node<T>* node = this->visitAt(index);
	if (node == nullptr)
	{
		throw std::out_of_range("out of range index");
	}

	return node->GetData();
}

template<typename T>
inline size_t park18::types::List<T>::GetSize() const
{
	return size_;
}

template<typename T>
inline bool park18::types::List<T>::IsEmpty() const
{
	return size_ == 0;
}

template<typename T>
inline void park18::types::List<T>::Print() const
{
	if (this->IsEmpty() == true)
	{
		std::cout << "List is empty" << std::endl;
		return;
	}

	Node<T>* node = pFront_;
	for (int i = 0; i < size_; i++)
	{
		std::cout << node->GetData() << ' ';
		node = node->GetNext();
	}
	std::cout << std::endl;
}

template<typename T>
inline bool park18::types::List<T>::isRightRange(size_t index) const
{
	return 0 <= index && index < size_;
}

template<typename T>
inline park18::types::Node<T>* park18::types::List<T>::visitAt(size_t index) const
{
	// 범위 예외처리
	if (this->isRightRange(index) == false)
	{
		return nullptr;
	}

	size_t halfIndex = static_cast<size_t>(std::round((static_cast<float>(size_) * 0.5f)));
	Node<T>* node = nullptr;
	if (index <= halfIndex)
	{
		node = pFront_;
		for (size_t i = 1; i <= index; i++)
		{
			node = node->GetNext();
		}
	}
	else
	{
		node = pBack_;
		for (size_t i = size_ - 2; index <= i; i--)
		{
			node = node->GetHead();
		}
	}

	return node;
}

template<typename T>
inline park18::types::Node<T>* park18::types::List<T>::Add(T data, Node<T>* pHead, Node<T>* pBack)
{
	// 신규 노드 생성
	Node<T>* newNode = new Node<T>(data);
	if (newNode == nullptr)
	{
		throw std::runtime_error("TNode<T> malloc falied");
	}

	// 신규 노드의 링크 연결
	newNode->SetHead(pHead);
	newNode->SetNext(pBack);

	// 기존 노드의 링크 갱신
	if (pHead != nullptr)
	{
		pHead->SetNext(newNode);
	}
	if (pBack != nullptr)
	{
		pBack->SetHead(newNode);
	}

	size_++;

	return newNode;
}

template<typename T>
inline void park18::types::List<T>::Delete(Node<T>* pDeleteNode)
{
	Node<T>* frontNode = pDeleteNode->GetHead();
	Node<T>* backNode = pDeleteNode->GetNext();

	// 기존 노드의 링크 갱신
	if (frontNode != nullptr)
	{
		frontNode->SetNext(backNode);
	}
	if (backNode != nullptr)
	{
		backNode->SetHead(frontNode);
	}

	delete(pDeleteNode);

	size_--;
}
