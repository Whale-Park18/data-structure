#pragma once

namespace park18::types
{
	template<typename T>
	class Node
	{
	public:
		Node(T data, Node<T>* pHead = nullptr, Node<T>* pNext = nullptr) : data_(data), pHead_(pHead), pNext_(pNext) {}

		void SetHead(Node<T>* pHead) { pHead_ = pHead; }
		void SetNext(Node<T>* pNext) { pNext_ = pNext; }
		void SetData(T data) { data_ = data; }

		Node<T>* GetHead() { return pHead_; }
		Node<T>* GetNext() { return pNext_; }
		const Node<T>* GetConstHead() { return pHead_; }
		const Node<T>* GetConstNext() { return pNext_; }
		T GetData() { return data_; }

	private:
		Node<T>* pHead_;
		Node<T>* pNext_;

		T data_;
	};
}
