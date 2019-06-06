#ifndef _R00TK1T_BM_TRAITS_H
#define _R00TK1T_BM_TRAITS_H

#include <iostream>
#include <iterator>
#include <unordered_map>

namespace r00tk1t {
    namespace algorithm {
        namespace detail {
            template<typename key_type, typename value_type>
            class skip_table{
            private:
                typedef std::unordered_map<key_type, value_type> skip_map;

                const value_type m_default_value;
                skip_map         m_skip;
            public:
                skip_table(std::size_t pat_size, value_type default_value)
                    : m_default_value(default_value), m_skip(pat_size) { }
                
                void insert(key_type key, value_type val) {
                    m_skip[key] = val;
                }

                value_type operator[](key_type key) const {
                    skip_map::const_iterator it = m_skip.find(key);
                    return it == m_skip.end() ? m_default_value : it->second;
                }

                void print_skip_table() const {
                    std::cout << "BM(H) Skip Table <unordered_map>:" << std::endl;
                    for(skip_map::const_iterator it = m_skip.cbegin(); it != m_skip.cend(); ++it) {
                        if(it->second != m_default_value)
                            std::cout << "  " << it->first << " : " << it->second << std::endl;
                    }
                    std::cout << std::endl;
                }
            };

            template<typename Iterator>
            struct BM_traits {
                typedef typename std::iterator_traits<Iterator>::difference_type value_type;
                typedef typename std::iterator_traits<Iterator>::value_type key_type;
                typedef skip_table<key_type, value_type> skip_table_t;
            };
        }
    }
}

#endif