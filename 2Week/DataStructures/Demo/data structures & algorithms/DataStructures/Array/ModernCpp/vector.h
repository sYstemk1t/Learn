#ifndef _R00TK1T_VECTOR_H
#define _R00TK1T_VECTOR_H 1

#include <utility>
#include <iterator>
#include <stdexcept>
#include <cstring>

namespace r00tk1t
{
    template<typename T>
    class vector
    {
    public:
        // types
        typedef T                                     value_type;
		typedef T&                                    reference;
		typedef const T&                              const_reference;
		typedef T*                                    pointer;
		typedef const T*                              const_pointer;
		typedef T*                                    iterator;
		typedef const T*                              const_iterator;
        typedef std::reverse_iterator<iterator>       reverse_iterator;
		typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
        typedef std::ptrdiff_t                        difference_type;
        typedef std::size_t                           size_type;

        // default constructor
        vector() noexcept;
        // common constructors
        explicit vector(size_type);
        vector(size_type, const T &);
        vector(typename vector<T>::iterator, typename vector<T>::iterator);
        vector(std::initializer_list<T>);
        // copy constructor
        vector(const vector<T> &);
        // move constructor
        vector(vector<T> &&) noexcept;
        // destructor
        ~vector();

        // copy assignment
        vector<T>& operator=(const vector<T> &);
        // move assignment
        vector<T>& operator=(vector<T> &&);
        
        vector<T>& operator=(std::initializer_list<T>);

        void assign(size_type, const T &);
        void assign(typename vector<T>::iterator, typename vector<T>::iterator);
        void assign(std::initializer_list<T>);

        // iterators
        iterator begin() noexcept;
        const_iterator cbegin() const noexcept;
        iterator end() noexcept;
        const_iterator cend() const noexcept;
        reverse_iterator rbegin() noexcept;
        const_reverse_iterator crbegin() const noexcept;
        reverse_iterator rend() noexcept;
        const_reverse_iterator crend() const noexcept;

        bool empty() const noexcept;
        size_type size() const noexcept;
        size_type capacity() const noexcept;
        void resize(size_type);
        void resize(size_type, const T&);
        void reserve(size_type);
        void shrink_to_fit();

        reference operator[](size_type);
        const_reference operator[](size_type) const;
        reference at(size_type);
        const_reference at(size_type) const;
        reference front();
        const_reference front() const;
        reference back();
        const_reference back() const;

        T* data() noexcept;
        const T* data() const noexcept;

        template<typename ... Args>
        void emplace_back(Args && ...);
        void push_back(const T&);
        void push_back(T &&);
        void pop_back();

        template<typename ... Args>
        iterator emplace(const_iterator, Args && ...);
        iterator insert(const_iterator, const T&);
        iterator insert(const_iterator, T &&);
        iterator insert(const_iterator, size_type, const T&);
        template<typename InputIt>
        iterator insert(const_iterator, InputIt, InputIt);
        iterator insert(const_iterator, std::initializer_list<T>);
        iterator erase(const_iterator);
        iterator erase(const_iterator, const_iterator);
        void swap(vector<T> &);
        void clear() noexcept;

        bool operator==(const vector<T> &) const;
        bool operator!=(const vector<T> &) const;

    private:
        size_type m_size;
		size_type m_capacity;
		T* m_start;

        inline void reallocate();
    };

    template<typename T>
    vector<T>::vector() noexcept
    : m_size(0), m_capacity(0), m_start(nullptr)
    { }

    template<typename T>
    vector<T>::vector(typename vector<T>::size_type n) 
    : m_size(n), m_capacity(n), m_start(new T[n])
    { }

    template<typename T>
    vector<T>::vector(typename vector<T>::size_type n, const T& value)
    : vector(n)
    { 
        for(size_type i=0;i<n;++i)
        {
            m_start[i] = value;
        }
    }

    template<typename T>
    vector<T>::vector(typename vector<T>::iterator first, typename vector<T>::iterator last)
    : vector(static_cast<size_type>(last-first))
    { 
        for(size_type i=0; first != last; ++first, ++i)
        {
            m_start[i] = *first;
        }
    }

    template<typename T>
    vector<T>::vector(std::initializer_list<T> lst)
    : vector(lst.size())
    {
        size_type i = 0;
        for(auto &item : lst)
        {
            m_start[i] = item;
            ++i;
        }
    }

    template<typename T>
    vector<T>::vector(const vector<T> &rhs)
    : m_size(rhs.m_size), m_capacity(rhs.m_capacity), m_start(new T[rhs.m_capacity])
    {
        for(size_type i=0; i<m_size; ++i)
        {
            m_start[i] = rhs.m_start[i];
        }
    }
    
    template<typename T>
    vector<T>::vector(vector<T> &&rhs) noexcept
    : m_size(std::move(rhs.m_size)), m_capacity(std::move(rhs.m_capacity)), m_start(std::move(rhs.m_start))
    {
        rhs.m_size = rhs.m_capacity = 0;
        rhs.m_start = nullptr;
    }

    template<typename T>
    vector<T>::~vector()
    {
        delete [] m_start;
    }

    template<typename T>
    vector<T>& vector<T>::operator=(const vector<T> &rhs)
    {   
        if(this != *rhs)
        {
            if(m_capacity != rhs.m_capacity)
            {
                m_capacity = rhs.m_capacity;
                reallocate();
            }
            for(size_type i=0; i<rhs.m_size; ++i)
            {
                m_start[i] = rhs.m_start[i];
            }
            m_size = rhs.m_size;
        }
        return *this;
    }

    template<typename T>
    vector<T>& vector<T>::operator=(vector<T> &&rhs)
    {
        if(this != *rhs)
        {
            delete [] m_start;
            m_size = std::move(rhs.size);
            m_capacity = std::move(rhs.m_capacity);
            m_start = std::move(rhs.start);
            rhs.size = rhs.m_capacity = 0;
            rhs.start = nullptr;
        }
        return *this;
    }

    template<typename T>
    vector<T>& vector<T>::operator=(std::initializer_list<T> lst)
    {
        if(m_capacity != lst.size())
        {
            m_capacity = lst.size();
            reallocate();
        }
        size_type i = 0;
        for(auto &item : lst)
        {
            m_start[i] = item;
            ++i;
        }
        return *this;
    }

    template<typename T>
    void vector<T>::assign(typename vector<T>::size_type count, const T& value)
    {
        if(count > m_capacity)
        {
            m_capacity = count;
            reallocate();
        }

        for(size_type i=0;i<count;++i)
        {
            m_start[i] = value;
        }
        m_size = count;
    }

    template<typename T>
    void vector<T>::assign(typename vector<T>::iterator first, typename vector<T>::iterator last)
    {
        size_type length = last - first;
        if(length > m_capacity)
        {
            m_capacity = length;
            reallocate();
        }
        for(size_type i=0;i<length;++i, ++first)
        {
            m_start[i] = *first;
        }
        m_size = length;
    }

    template<typename T>
    void vector<T>::assign(std::initializer_list<T> lst)
    {
        size_type length = lst.size();
        if(length > m_capacity)
        {
            m_capacity = length;
            reallocate();
        }
        size_type i=0;
        for(auto &item : lst)
        {
            m_start[i] = item;
            ++i;
        }
        m_size = length;
    }

    template<typename T>
    typename vector<T>::iterator vector<T>::begin() noexcept
    {
        return m_start;
    }

    template<typename T>
    typename vector<T>::const_iterator vector<T>::cbegin() const noexcept
    {
        return m_start;
    }

    template<typename T>
    typename vector<T>::iterator vector<T>::end() noexcept
    {
        return m_start + m_size;
    }

    template<typename T>
    typename vector<T>::const_iterator vector<T>::cend() const noexcept
    {
        return m_start + m_size;
    }

    template<typename T>
    typename vector<T>::reverse_iterator vector<T>::rbegin() noexcept
    {
        return reverse_iterator(m_start + m_size);
    }

    template<typename T>
    typename vector<T>::const_reverse_iterator vector<T>::crbegin() const noexcept
    {
        return reverse_iterator(m_start + m_size);
    }

    template<typename T>
    typename vector<T>::reverse_iterator vector<T>::rend() noexcept
    {
        return reverse_iterator(m_start);
    }

    template<typename T>
    typename vector<T>::const_reverse_iterator vector<T>::crend() const noexcept
    {
        return reverse_iterator(m_start);
    }

    template<typename T>
    inline void vector<T>::reallocate()
    {
        T *temp = new T[m_capacity];
        for(size_type i=0;i<m_size;++i)
        {
            temp[i] = std::move(m_start[i]);
        }
        std::swap(temp, m_start);
        delete [] temp;        
    }

    template<typename T>
    bool vector<T>::empty() const noexcept
    {
        return m_size == 0;
    }

    template<typename T>
    typename vector<T>::size_type vector<T>::size() const noexcept
    {
        return m_size;
    }

    template<typename T>
    typename vector<T>::size_type vector<T>::capacity() const noexcept
    {
        return m_capacity;
    }

    template<typename T>
    void vector<T>::resize(typename vector<T>::size_type sz)
    {
        if(sz > m_size)
        {
            if(sz > m_capacity)
            {
                m_capacity = sz;
                reallocate();
            }
        }
        else
        {
            for(size_type i=sz; i<m_size; ++i)
            {
                m_start[i].~T();
            }
        }
        m_size = sz;
    }

    template<typename T>
    void vector<T>::resize(typename vector<T>::size_type sz, const T& c)
    {
        if(sz > m_size)
        {
            if(sz > m_capacity)
            {
                m_capacity = sz;
                reallocate();
            }
            for(size_type i=m_size; i<sz; ++i)
            {
                m_start[i] = c;
            }
        }
        else
        {
            for(size_type i=sz; i<m_size; ++i)
            {
                m_start[i].~T();
            }
        }
        m_size = sz;
    }

    template<typename T>
    void vector<T>::reserve(typename vector<T>::size_type sz)
    {
        if(sz > m_capacity)
        {
            sz = m_capacity;
            reallocate();
        }
    }

    template<typename T>
    void vector<T>::shrink_to_fit()
    {
        m_capacity = m_size;
        reallocate();
    }

    template<typename T>
    typename vector<T>::reference vector<T>::operator[](typename vector<T>::size_type idx)
    {
        if(idx < m_size)
            return m_start[idx];
        else
            throw std::out_of_range("accessed position is out of range");
    }

    template<typename T>
    typename vector<T>::const_reference vector<T>::operator[](typename vector<T>::size_type idx) const
    {
        if(idx < m_size)
            return m_start[idx];
        else
            throw std::out_of_range("accessed position is out of range");
    }

    template<typename T>
    typename vector<T>::reference vector<T>::at(size_type pos)
    {
        if(pos < m_size)
            return m_start[pos];
        else
            throw std::out_of_range("accessed position is out of range");
    }

    template<typename T>
    typename vector<T>::const_reference vector<T>::at(size_type pos) const
    {
        if(pos < m_size)
            return m_start[pos];
        else
            throw std::out_of_range("accessed position is out of range");
    }

    template<typename T>
    typename vector<T>::reference vector<T>::front()
    {
        if(empty())
            return nullptr;
        return m_start[0];
    }

    template<typename T>
    typename vector<T>::const_reference vector<T>::front() const
    {
        if(empty())
            return nullptr;
        return m_start[0];
    }

    template<typename T>
    typename vector<T>::reference vector<T>::back()
    {
        if(empty())
            return nullptr;
        return m_start[m_size - 1];
    }

    template<typename T>
    typename vector<T>::const_reference vector<T>::back() const
    {
        if(empty())
            return nullptr;
        return m_start[m_size - 1];
    }

    template<typename T>
    T* vector<T>::data() noexcept
    {
        return m_start;
    }

    template<typename T>
    const T* vector<T>::data() const noexcept
    {
        return m_start;
    }

    template<typename T>
    template<typename ... Args>
    void vector<T>::emplace_back(Args && ... args)
    {
        if(m_size == m_capacity)
        {
            if(m_capacity == 0)
                m_capacity = 1;
            else
                m_capacity <<= 1;
            reallocate();
        }
        m_start[m_size] = std::move(T(std::forward<Args>(args) ... ));
        ++m_size;
    }

    template<typename T>
    void vector<T>::push_back(const T &val)
    {
        if(m_size == m_capacity)
        {
            if(m_capacity == 0)
                m_capacity = 1;
            else
                m_capacity <<= 1;
            reallocate();
        }
        m_start[m_size] = val;
        ++m_size;
    }

    template<typename T>
    void vector<T>::push_back(T &&val)
    {
        if(m_size == m_capacity)
        {
            if(m_capacity == 0)
                m_capacity = 1;
            else
                m_capacity <<= 1;
            reallocate();
        }
        m_start[m_size] = std::move(val);
        ++m_size;
    }

    template<typename T>
    void vector<T>::pop_back()
    {
        --m_size;
        m_start[m_size].~T();
    }

    template<typename T>
    template<typename ... Args>
    typename vector<T>::iterator vector<T>::emplace(typename vector<T>::const_iterator it, Args && ... args)
    {
        iterator iter = &m_start[it - m_start];
        if(m_size == m_capacity)
        {
            if(m_capacity == 0)
                m_capacity = 1;
            else
                m_capacity <<= 1;
            reallocate(iter+1, iter, (m_size - (it - m_start)) * sizeof(T));
        }
        memmove(iter + 1, iter, (m_size - (it - m_start)) * sizeof(T));
        *iter = std::move(T(std::forward<Args>(args) ... ));
        ++m_size;
        return iter;
    }

    template<typename T>
    typename vector<T>::iterator vector<T>::insert(typename vector<T>::const_iterator it, const T& val)
    {
        iterator iter = &m_start[it - m_start];
        if(m_size == m_capacity)
        {
            if(m_capacity == 0)
                m_capacity = 1;
            else
                m_capacity <<= 1;
            reallocate(iter+1, iter, (m_size- (it - m_start)) * sizeof(T));
        }
        memmove(iter + 1, iter, (m_size - (it - m_start)) * sizeof(T));
        *iter = val;
        ++m_size;
        return iter;
    }

    template<typename T>
    typename vector<T>::iterator vector<T>::insert(typename vector<T>::const_iterator it, T&& val)
    {
        iterator iter = &m_start[it - m_start];
        if(m_size == m_capacity)
        {
            if(m_capacity == 0)
                m_capacity = 1;
            else
                m_capacity <<= 1;
            reallocate(iter+1, iter, (m_size- (it - m_start)) * sizeof(T));
        }
        memmove(iter + 1, iter, (m_size - (it - m_start)) * sizeof(T));
        *iter = std::move(val);
        ++m_size;
        return iter;
    }

    template<typename T>
    typename vector<T>::iterator vector<T>::insert(typename vector<T>::const_iterator it, typename vector<T>::size_type cnt, const T& val)
    {
        iterator iter = &m_start[it - m_start];
        if(cnt == 0)
            return iter;
        if(m_size + cnt > m_capacity)
        {
            m_capacity = (m_size+cnt) << 1;
            reallocate();
        }
        memmove(iter + cnt, iter, (m_size - (it - m_start)) * sizeof(T));
        m_size += cnt;
        for(iterator tmp = iter; cnt--; ++tmp)
            *tmp = val;
        return iter;
    }

    template<typename T>
    template<typename InputIt>
    typename vector<T>::iterator vector<T>::insert(typename vector<T>::const_iterator it, InputIt first, InputIt last)
    {
        iterator iter = &m_start[it - m_start];
        size_type cnt = last - first;
        if(cnt == 0)
            return iter;
        if(m_size + cnt > m_capacity)
        {
            m_capacity = (m_size + cnt) << 1;
            reallocate();
        }
        memmove(iter + cnt, iter, (m_size - (it - m_start)) * sizeof(T));
        for(iterator tmp = iter; first != last; ++tmp, ++first)
            *tmp = *first;
        m_size += cnt;
        return iter;
    }

    template<typename T>
    typename vector<T>::iterator vector<T>::insert(typename vector<T>::const_iterator it, std::initializer_list<T> lst)
    {
        iterator iter = &m_start[it - m_start];
        size_type cnt = lst.size();
        if(cnt == 0)
            return iter;
        if(m_size + cnt > m_capacity)
        {
            m_capacity = (m_size + cnt) << 1;
            reallocate();
        }
        memmove(iter + cnt, iter, (m_size - (it - m_start)) * sizeof(T));
        iterator tmp = iter;
        for(auto &item : lst)
        {
            *tmp = item;
            ++tmp;
        }
        m_size += cnt;
        return iter;
    }

    template<typename T>
    typename vector<T>::iterator vector<T>::erase(typename vector<T>::const_iterator it)
    {
        iterator iter = &m_start[it - m_start];
        (*iter).~T();
        memmove(iter, iter + 1, (m_size - (it - m_start) - 1) * sizeof(T));
        --m_size;
        return iter;
    }

    template<typename T>
    typename vector<T>::iterator vector<T>::erase(typename vector<T>::const_iterator first, typename vector<T>::const_iterator last)
    {
        iterator iter = &m_start[it - m_start];
        size_type cnt = last - first;
        if(cnt == 0)
            return iter;
        for(; first != last; ++first)
        {
            (*first).~T();
        }
        memmove(iter, last, (m_size - (last - m_start)) * sizeof(T));
        m_size -= cnt;
        return iter;
    }

    template<typename T>
    void vector<T>::swap(vector<T>& rhs)
    {
        std::swap(m_size, rhs.m_size);
        std::swap(m_capacity, rhs.m_capacity);
        std::swap(m_start, rhs.m_start);
    }

    template<typename T>
    void vector<T>::clear() noexcept
    {
        for(size_type i=0;i<m_Size; ++i)
            m_start[i].~T();
        m_size = 0;
    }

    template<typename T>
    bool vector<T>::operator==(const vector<T>& rhs) const
    {
        if(m_size != rhs.m_size)
            return false;
        for(size_type i=0; i<m_size; ++i)
        {
            if(m_start[i] != rhs.m_start[i])
                return false;
        }
        return true;
    }

    template<typename T>
    bool vector<T>::operator!=(const vector<T>& rhs) const
    {
        return (operator==(rhs) == true) ? false : true;
    }
}  
#endif 