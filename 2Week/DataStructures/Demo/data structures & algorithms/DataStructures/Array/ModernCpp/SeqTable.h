#include <algorithm>

namespace r00tk1t
{
	using std::size_t;
    using std::ptrdiff_t;

	template<typename T>
	class SeqTable
	{
	public:
        // types 
    	typedef T*                  iterator;
		typedef const T*            const_iterator;

		// constructor within compatible default version
		explicit SeqTable(size_t size = 0) : m_size(size), m_capacity(size), m_start(nullptr)
		{
			if (m_capacity != 0)
				m_start = new T[m_capacity];                // T should support default constructor
		}

		// copy constructor
		SeqTable(const SeqTable &rhs) : m_size(rhs.m_size), m_capacity(rhs.m_capacity), m_start(nullptr)
		{
			if (m_capacity != 0)
			{
				m_start = new T[m_capacity];
				for (int index = 0; index<rhs.m_size; ++index)
				{
					m_start[index] = rhs.m_start[index];    // T should support copy assignment
				}
			}
		}

		// copy assignment
		SeqTable& operator=(const SeqTable &rhs)
		{
			if (&rhs != this){
				SeqTable copy = rhs;                        // after swapping, copy which holds original resourse will call destructor automatically once returns
				std::swap(*this, copy);                     // objects will be released during the phase
			}
			return *this;
		}

		// move constructor
		SeqTable(SeqTable &&rhs) : m_size(rhs.m_size), m_capacity(rhs.m_capacity), m_start(rhs.m_start)
		{
			rhs.m_size = rhs.m_capacity = 0;
			rhs.m_start = nullptr;
		}

		// move assignment
		SeqTable& operator=(SeqTable &&rhs)
		{
			if (&rhs != this){
				std::swap(m_size, rhs.m_size);
                std::swap(m_capacity, rhs.m_capacity);
                std::swap(m_start, rhs.m_start);
			}
			return *this;
		}

		// destructor
		~SeqTable()
		{
			delete[] m_start;
		}

		void reserve(size_t size)
		{
			if (size < m_size)
				return;

			T *array = new T[size];
			for (int index = 0; index<m_size; ++index)
			{
				array[index] = std::move(m_start[index]);
			}

			m_capacity = size;
			std::swap(m_start, array);
			delete[] array;
		}

		T& operator[](size_t index)
		{
			return m_start[index];
		}

		const T& operator[](size_t index) const
		{
			return m_start[index];
		}

		bool empty() const
		{
			return size() == 0;
		}

		size_t size() const
		{
			return m_size;
		}

		size_t capacity() const
		{
			return m_capacity;
		}

		void push_back(const T &x)
		{
			if (m_size == m_capacity)
			{
				if (m_capacity == 0)
					reserve(1);
				else
					reserve(2 * m_capacity);
			}
			m_start[m_size] = x;
			++m_size;
		}

		void push_back(T &&x)
		{
			if (m_size == m_capacity)
			{
				if (m_capacity == 0)
					reserve(1);
				else
					reserve(2 * m_capacity);
			}
			m_start[m_size] = std::move(x);
			++m_size;
		}

		void pop_back()
		{
			--m_size;
            m_start[m_size].~T();
		}

		const T& back() const
		{
			return m_start[m_size - 1];
		}

		iterator begin()
		{
			return &m_start[0];
		}

		const_iterator cbegin() const
		{
			return &m_start[0];
		}

		iterator end()
		{
			return &m_start[size()];
		}

		const_iterator cend() const
		{
			return &m_start[size()];
		}

	private:
		size_t m_size;
		size_t m_capacity;
		T* m_start;
	};
}