/*
* By: Philip Eklund
* Course: DT047G
* Date 15 JAN 2021
* PROJECT: ASTEROIDS GAME
*/
#ifndef OBJECTLIST_HPP
#define OBJECTLIST_HPP
#include <stdexcept>
/*!
*  \brief     Object node used in ObjectList
*  \details   Contains <Type>Data next* and prev*
*  \author    Philip EKlund
*  \version   1.1
*  \date      2021
*/
template <typename Type>
class Object {
public:
	/**
	*Default constructor, everything nullptr/zero
	*/
	Object() : next(nullptr), prev(nullptr), Data() {	}; //Default constructor
	/**
	*Default constructor, everything nullptr/zero
	*/
	Object(Type args) : next(nullptr), prev(nullptr), Data(args) {};
	/**
	*Default destructor
	*/
	~Object() {}; //Default destructor

	Object * next; //Next node
	Object * prev; //Prev node
	Type Data; //This node's data

};
/*!
*  \brief     Object list, a simple double directed linked list.
*  \details   Linked list, pro: can remove objects in the middle of the list. Con: NO iterator
*  \author    Philip EKlund
*  \version   1.1
*  \date      2021
*  \warning   Improper use can crash your application!
*\bug       Feature: there is no iterator class, use for loop
*/
template<typename Type>
class ObjectList {
public:
	/**
	*Default constructor, everything nullptr/zero
	*/
	ObjectList() : head(nullptr), tail(nullptr), mSize(0) {};//Default constructor
		/**
	*Default destructor
	*/
	~ObjectList() {											//Default Destructor
		//delete[] head;
		while (!isEmpty())
			pop_front();
	};
	/**
	* DEEP copy constructor
	* copy one list into another.
	* @param src,  ObjectList& object desired to be copied into current object.
	*/
	ObjectList(const ObjectList& src) //DEEP copy constructor
	{
		head = nullptr;
		tail = nullptr;
		mSize = 0;
		for (int i = 0; i < src.size(); i++)
		{
			push_back(src.at(i));
		}
	};

	// copyconstruct
	//ObjectList(const  ObjectList& rhs) : ObjectList(rhs.head, rhs.size()) {  }

	// moveconstruct
	/**
	* moveconstruct
	* @param rhs, will swap rhs ObjectList to current object
	*/
	ObjectList(ObjectList && rhs) : head(nullptr), tail(nullptr)
	{
		swap(rhs);
	}
	bool isEmpty() {										//Is it empty?
		return head == nullptr;
	};
	/**
	* push_back insert data into the back of the list
	* @param data, data of Type to be inserted into the list
	*/
	void push_back(Type data) {								 //Put data at the end of list
		Object<Type> *obj = new Object<Type>(data);
		//obj->Data = data;
		if (!isEmpty()) 			//Set head to this node and old head should get a prev
		{
			tail->next = obj;
			obj->prev = tail;
			tail = obj;
		}
		else							//If list WAS empty, this is both head and tail
		{
			head = obj;
			tail = obj;
		}
		mSize++;
	};
	/**
	* pop_back retrieve and remove last element in list
	* @return data, data of Type from the rear of the list.
	*/
	Type& pop_back()											//Return and Remove data at back of list
	{
		Type data;
		if (isEmpty())											//If empty, throw error
		{
			throw std::invalid_argument("List is empty, cannot pop");
		}
		Object<Type> * obj = tail;
		data = obj->Data;
		if (obj->prev != nullptr)		  //Next element is now tail	
		{
			obj->prev->next = nullptr;
			tail = obj->prev;
		}
		else							//If we popped the last element, the list is empty, no head or tail
		{
			tail = nullptr;
			head = nullptr;
		}

		obj->~Object();

		mSize--;
		return data;
	};
	/**
	* push_front insert data into the front of the list
	* @param data, data of Type to be inserted into the list
	*/
	void push_front(Type data)								//Insert data at front of list
	{
		Object<Type> * obj = new Object<Type>(data);
		//obj->Data = data;
		if (!isEmpty())				//Set head to this node and old head should get a prev
		{
			head->prev = obj;
			obj->next = head;
			head = obj;
		}
		else						//If list WAS empty, this is both head and tail
		{
			tail = obj;
			head = obj;
		}
		mSize++;

	};
	/**
* pop_front retrieve and remove first element in list
* @return data, data of Type& from the front of the list.
*/
	Type& pop_front() {										//Return and Remove data at front of the list
		Type data;

		if (isEmpty())											//If empty, throw error
		{
			throw std::invalid_argument("List is empty, cannot pop");
		}

		Object<Type> * obj = head;
		data = obj->Data;

		if (obj->next == nullptr) //If we popped the last element, the list is empty, no head or tail
		{
			head = nullptr;
			tail = nullptr;
		}
		else
		{
			obj->next->prev = nullptr; //Next element is now head
			head = obj->next;
		}

		obj->~Object();
		mSize--;
		return data;
	};
	/**
* setData insert data into the specified position of the list. This WILL OVERWRITE data at that position
* @param pos, size_t position where to overwrite data.
* @param data, data of Type to be inserted into the list
*/
	void setData(size_t pos, Type data)					//Set data at a specific position in list
	{
		Object<Type>* obj = head;
		for (int i = 0; i < pos; i++)
		{
			if (obj->next == nullptr)									//If position is outside list, throw error
				throw std::invalid_argument("[-] ERROR: Out of bounds");
			obj = obj->next;
		}
		obj->Data = data;
	};
	/**
* at retrieve data from position
* @return data, data of Type& from the desired position of the list.
*/
	Type& at(size_t pos) const									//Return data in a specific position in list
	{
		Object<Type>* obj = head;

		for (int i = 0; i < pos; i++)
		{
			if (obj->next == nullptr)									//If position is outside list, throw error
			{
				throw std::invalid_argument("[-] ERROR: Out of bounds");
			}
			obj = obj->next;
		}

		return obj->Data;
	};
	/**
* remove data at specified position reducing the size of 1.
* @param pos, size_t remove the data at position.
*/
	void remove(size_t pos)									//remove data in a specific position in list
	{
		Object<Type>* obj = head;

		if (pos == 0) //If position is first or last, just pop back or front
		{
			pop_front();
		}
		else if (pos == mSize - 1)
		{
			pop_back();
		}
		else //It is somewhere in the middle, go to position
		{
			for (int i = 0; i < pos; i++)
			{
				if (obj->next == nullptr)									//If position is outside list, throw error
				{
					throw std::invalid_argument("[-] ERROR: Out of bounds");
				}
				obj = obj->next;
			}

			obj->next->prev = obj->prev; //Make sure next and prev nodes are connected when we disconnect this node.

			obj->prev->next = obj->next;
			delete obj;
			mSize--;
		}

	};
	/**
* front retrieve data from the front of the list.
* @return data, return the data of Type&
*/
	Type& front() const							//Return first data value in list
	{
		if (head == nullptr)
			throw std::invalid_argument("[-] ERROR: List is empty");	//If empty, throw error
		Object<Type>* obj = head;
		return obj->Data;
	};
	/**
* back retrieve data from the back of the list.
* @return data, return the data of Type&
*/
	Type& back() const							//Return last data value in list
	{
		if (tail == nullptr)
			throw std::invalid_argument("[-] ERROR: List is empty");	//If empty, throw error
		Object<Type>* obj = tail;
		return obj->Data;
	};
	/**
* size get the size of the list.
* @return size_t size of the list.
*/
	size_t size() const							//Return the size of the list
	{
		//return tail - head;
		return mSize;
	};

	ObjectList<Type>& operator=(const ObjectList& src)
	{
		while (!isEmpty())
		{
			pop_front();
		}

		head = nullptr;
		tail = nullptr;
		mSize = 0;
		for (int i = 0; i < src.size(); i++)
		{
			push_back(src.at(i));
		}
		return *this;
	};
	/**
	* operator[] overload
	* can use list[size_t index] to get data at position index.
	*/
	Type& operator[](size_t index)
	{
		//return head[index];
		return at(index);
	}
	/**
	*Begin()
	*@return pointer to the first object in the list
	*/
	Object<Type>* begin() { return head; }
	/**
*end()
*@return pointer to the last object in the list
*/
	Object<Type>* end() { return tail->next;/*Should be nullptr*/ }



private:

	int mSize;

	Object<Type> * head;
	Object<Type> * tail;
};


#endif
