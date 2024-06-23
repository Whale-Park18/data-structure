#pragma once

namespace park18::types
{
	template<typename T>
	class TNode
	{
	public:
		TNode(T data, TNode<T>* pHead = nullptr, TNode<T>* pNext = nullptr) : data_(data), pHead_(pHead), pNext_(pNext) {}

		void SetHead(TNode<T>* pHead) { pHead_ = pHead; }
		void SetNext(TNode<T>* pNext) { pNext_ = pNext; }
		void SetData(T data) { data_ = data; }

		TNode<T>* GetHead() { return pHead_; }
		TNode<T>* GetNext() { return pNext_; }
		const TNode<T>* GetConstHead() { return pHead_; }
		const TNode<T>* GetConstNext() { return pNext_; }
		T GetData() { return data_; }

		

	private:
		TNode<T>* pHead_;
		TNode<T>* pNext_;

		T data_;
	};
}
