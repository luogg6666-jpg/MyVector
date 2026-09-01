#include <iostream>
#include <stdexcept>
using namespace std;

template <typename T>
class MyVector
{
private:
	T* data;
	size_t size;
	size_t capacity;
public:
	MyVector()
		: data(nullptr), size(0), capacity(0)
	{
	}
	~MyVector()
	{
		delete[] data;
		cout << "data已析构" << endl;
	}
	void show()
	{
		cout << "data = " << data << endl;
		cout << "size = " << size << endl;
		cout << "capacity = " << capacity << endl;
	}
	void push_back(const T& value)
	{
		if (size == capacity)
		{
			expand();
		}
		data[size] = value;
		size++;
	}
	size_t getSize() const
	{
		return size;
	}
	size_t getCapacity() const
	{
		return capacity;
	}
	int& operator[](int index)
	{
		return data[index];
	}
	void expand()
	{
		size_t newcapacity;
		if (capacity == 0)
		{
			newcapacity = 1;
		}
		else
		{
			newcapacity = capacity * 2;
		}
		int* newdata = new T[newcapacity];
		for (int i = 0;i < size;i++)
		{
			newdata[i] = data[i];
		}
		delete[]data;
		data = newdata;
		capacity = newcapacity;
	}
	MyVector(const MyVector& other)
	{
		size = other.size;
		capacity = other.capacity;
		data = new T[capacity];
		for (int i = 0; i < size;i++)
		{
			data[i] = other.data[i];
		}
	}
	MyVector& operator=(const MyVector& other)
	{
		if (this == &other)
		{
			return *this;
		}
		delete[] data;
		size = other.size;
		capacity = other.capacity;
		data = new int[capacity];
		for (int i = 0; i < size;i++)
		{
			data[i] = other.data[i];
		}
		return *this;
	}
	bool empty() const
	{
		return size == 0;
	}
	void clear()
	{
		size = 0;
	}
	T& at(size_t index)
	{
		if (index >= size)
		{
			throw std::out_of_range("index out of range");
		}
		return data[index];
	}
	T& front()
	{
		return data[0];
	}
	T& back()
	{
		return data[size - 1];
	}
	void reserve(size_t newcapacity)
	{
		if (capacity >= newcapacity)
		{
			return;
		}
		T* newdata = new T[newcapacity];
		for (int i = 0; i < size;i++)
		{
			newdata[i] = data[i];
		}
		delete[]data;
		data = newdata;
		capacity = newcapacity;
	}
	void resize(size_t newsize)
	{
		if (newsize < size)
		{
			size = newsize;
			return;
		}
		if (newsize > size)
		{
			reserve(newsize);
		}
		while (size < newsize)
		{
			data[size] = T();
			size++;
		}
	}
	T* begin()
	{
		return data;
	}
	T* end()
	{
		return data + size;
	}
};

int main()
{
	MyVector <int> v;
	cout << "MyVector创建成功" << endl;
	for (int i = 0; i < 10;i++)
	{
		v.push_back(i);
		cout << "size = " << v.getSize()
			<< ",capacity = " << v.getCapacity()
			<< endl;
	}
	try
	{
		cout << v.at(100) << endl;
	}
	catch (const out_of_range& e)
	{
		cout << e.what() << endl;
	}
	MyVector a = v;
	

	return 0;
}