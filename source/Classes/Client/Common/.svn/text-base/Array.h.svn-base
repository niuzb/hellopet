
#ifndef ARRAY_2013_12_16_H
#define ARRAY_2013_12_16_H
#include <stdio.h>
#include <stdlib.h>


template<class T>
class Array2D
{
protected:
	T* m_data;
	int m_width;
	int m_height;
public:
	inline Array2D(void):m_data(NULL),m_width(0),m_height(0){}
	
	inline Array2D( int width,  int height)
		:m_data(NULL)
		,m_width(width)
		,m_height(width)
	{
		Create(width, height);
	}

	inline Array2D( int width,  int height,  const T& data)
	{
		Create(width, height, data);
	}

	~Array2D(){delete [] m_data;}

	inline void operator = (const Array2D<T>& rhs)
	{
		if(m_data != NULL)
		{	
			delete[] m_data;
		}

		Create(rhs.GetWidth(), rhs.GetHeight());
		::memcpy(m_data, rhs.m_data, rhs.GetSize());
	}

	inline void Create( int width,  int height)
	{
		if(m_data)
		{
			delete[] m_data;
		}
		m_width = width;
		m_height = height;
		m_data = new T[width * height];
	}

	inline void Malloc(int width, int height)
	{
		assert(m_data == NULL);

		m_width = width;
		m_height = height;
		m_data = (T*)new char[width * height * sizeof(T)];
	}

	inline void Create( int width,  int height,  const T& data)
	{
		Create(width, height);
		Init(data);
	}

	inline T*& Get(void)
	{
		return m_data;
	}

	inline T& Get( int x,  int y) const
	{
		assert(x >= 0 && x < m_width);
		assert(y >= 0 && y < m_height);
		assert(m_data);
		return m_data[x + y * m_width];
	}

	inline void Set( int x,  int y,  const T& data)
	{
		assert(x >= 0 && x < m_width);
		assert(y >= 0 && y < m_height);
		assert(m_data);
		m_data[x + y * m_width] = data;
	}

	// ©ирт[y][x]
	inline T* operator[]( int y) const
	{
		assert(y >= 0 && y < m_height);
		assert(m_data);
		return &m_data[y * m_width];
	}

	inline T& operator()( int x,  int y)
	{
		return Get(x, y);
	}

	inline void Init( const T& data)
	{
		assert(m_data);
		for(int j = 0; j < m_height; j++)
		{
			for(int i = 0; i < m_width; i++)
			{
				m_data[i + j * m_width] = data;
			}
		}
	}
	
	inline void Release(void)
	{
		SafeDeleteArray(m_data);
		m_width = 0;
		m_height = 0;
	}

	inline void Memset(int val)
	{
		::memset(m_data, val, GetSize());
	}

	inline int GetWidth(void) const{return m_width;}
	inline int GetHeight(void)const{return m_height;}
	inline unsigned int GetSize(void)const{return m_width * m_height * sizeof(T);}
	inline unsigned int GetCount(void)const{return m_width * m_height;}
};

#endif // ARRAY_2013_12_16_H