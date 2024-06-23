#pragma once
#include "node.h"

#include <stdexcept>

namespace park18::types
{
	template<typename T>
	class TList
	{
	public:
		TList();

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
		/// <remarks>>
		/// [Todo]
		///  - 버그: 리스트의 중간 위치, pBack에 삽입할 때, 의도대로 작동 안함
		/// </remarks>
		void Insert(T data, size_t insertIndex);

		//---------------------------------------------------
		// 제거
		//---------------------------------------------------
		void Clear();
		T PopFront();
		T PopBack();
		T Erase(size_t eraseIndex);

		//---------------------------------------------------
		// 접근
		//---------------------------------------------------
		
		/// <summary>
		/// index에 위치한 데이터를 반환
		/// </summary>
		/// <param name="index">접근할 데이터 인덱스</param>
		/// <returns>index에 위치한 데이터</returns>
		T At(size_t index);

		//---------------------------------------------------
		// 유틸
		//---------------------------------------------------

		/// <summary>
		/// 리스트의 크기 반환
		/// </summary>
		/// <returns>현재 리스트 크기</returns>
		size_t GetSize();

		/// <summary>
		/// 현재 리스트가 비어있는지 확인
		/// </summary>
		/// <returns>비어있으면 true, 값이 있으면 false</returns>
		bool IsEmpty();

	private:

		/// <summary>
		/// index의 값이 옳바른 범위인지 확인
		/// </summary>
		/// <param name="index"></param>
		/// <returns></returns>
		bool isRightRange(size_t index);

		/// <summary>
		/// index에 위치한 노드 반환
		/// </summary>
		/// <param name="index">접근할 노드 인덱스</param>
		/// <returns>index에 위치한 노드</returns>
		TNode<T>* visitAt(size_t index);

		/// <summary>
		/// 노드 추가
		/// </summary>
		/// <param name="data">데이터</param>
		/// <param name="pHead">신규 노드의 head</param>
		/// <param name="pBack">신규 노드의 back</param>
		/// <returns>신규 노드 포인터</returns>
		TNode<T>* Add(T data, TNode<T>* pHead, TNode<T>* pBack);

		void Delete();

	private:
		TNode<T>* pFront_;
		TNode<T>* pBack_;

		size_t size_;
	};
}

template<typename T>
inline park18::types::TList<T>::TList() : pFront_(nullptr), pBack_(nullptr), size_(0)
{
}

template<typename T>
inline void park18::types::TList<T>::PushFront(T data)
{
	TNode<T>* newNode = this->Add(data, pBack_, pFront_);

	// 리스트의 앞, 뒤 포인터 갱신
	pFront_ = newNode;
	pBack_ = pBack_ == nullptr ? newNode : pBack_;
}

template<typename T>
inline void park18::types::TList<T>::PushBack(T data)
{
	TNode<T>* newNode = this->Add(data, pBack_, pFront_);

	// 리스트의 앞, 뒤 포인터 갱신
	pBack_ = newNode;
	pFront_ = pFront_ == nullptr ? newNode : pFront_;
}

template<typename T>
inline void park18::types::TList<T>::Insert(T data, size_t insertIndex)
{
	TNode<T>* backNode = this->visitAt(insertIndex);
	if (backNode == nullptr)
	{
		throw std::out_of_range("out of range index");
	}
	TNode<T>* headNode = backNode->GetHead();
	TNode<T>* newNode = this->Add(data, headNode, backNode);
	
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
inline T park18::types::TList<T>::At(size_t index)
{
	TNode<T>* node = this->visitAt(index);
	if (node == nullptr)
	{
		throw std::out_of_range("out of range index");
	}

	return node->GetData();
}

template<typename T>
inline size_t park18::types::TList<T>::GetSize()
{
	return size_;
}

template<typename T>
inline bool park18::types::TList<T>::IsEmpty()
{
	return size_ == 0;
}

template<typename T>
inline bool park18::types::TList<T>::isRightRange(size_t index)
{
	return 0 <= index && index < size_;
}

template<typename T>
inline park18::types::TNode<T>* park18::types::TList<T>::visitAt(size_t index)
{
	// 범위 예외처리
	if (this->isRightRange(index) == false)
	{
		return nullptr;
	}

	size_t halfIndex = size_ / 2;
	TNode<T>* node = nullptr;
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
		for (size_t i = size_ - 1; index <= i; i--)
		{
			node = node->GetHead();
		}
	}

	return node;
}

template<typename T>
inline park18::types::TNode<T>* park18::types::TList<T>::Add(T data, TNode<T>* pHead, TNode<T>* pBack)
{
	// 신규 노드 생성
	TNode<T>* newNode = new TNode<T>(data);
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