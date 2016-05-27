#ifndef LOCK_FREE_QUEUE_H_
#define LOCK_FREE_QUEUE_H_

//���������У��ʺ�һ���̶߳�ȡ��һ���߳�д
#include <list>
template <typename T>
class LockFreeQueue
{
public:
	LockFreeQueue()
	{
		list.push_back(T());//�ָ�ڵ�
		iHead = list.begin();
		iTail = list.end();
	};
	//����Ϣ
	void Produce(const T& t) 
	{
		list.push_back(t);
		iTail = list.end();
		list.erase(list.begin(), iHead);
	};
	//ȡ��Ϣ
	bool Consume(T& t) 
	{
		typename TList::iterator iNext = iHead;
		++iNext;
		if (iNext != iTail)
		{
			iHead = iNext;
			t = *iHead;
			return true;
		}
		return false;
	};
	//�鿴��Ϣ��ɾ��
	bool Peek(T& t) 
	{
		typename TList::iterator iNext = iHead;
		++iNext;
		if (iNext != iTail)
		{
			t = *iNext;
			return true;
		}
		return false;
	}

	bool IsEmpty()
	{
		typename TList::iterator iNext = iHead;
		++iNext;
		if (iNext != iTail)
		{
			return false;
		}
		else
		{
			return true;
		}
	}
	int GetSize()
	{
		return list.size()-2;
	};
	int GetMaxSize()
	{
		return list.max_size();
	};

private:
	typedef std::list<T> TList;
	TList list;
	typename TList::iterator iHead, iTail;
};
#endif