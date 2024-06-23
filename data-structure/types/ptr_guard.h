#pragma once
template<typename T>
class TPtrGuard
{
public:
	TPtrGuard(T t) : pData(new T(t)) {}
	~TPtrGuard() { delete pData; }


private:
	T* pData;
};