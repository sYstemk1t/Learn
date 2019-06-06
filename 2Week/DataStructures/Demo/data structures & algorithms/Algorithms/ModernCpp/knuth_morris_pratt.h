#ifndef _R00TK1T_KNUTH_MORRIS_PRATT_H
#define _R00TK1T_KNUTH_MORRIS_PRATT_H

#include <vector>
#include <iterator> 

namespace r00tk1t {
    namespace algorithm {
        template <typename patIter>
        class knuth_morris_pratt {
            typedef typename std::iterator_traits<patIter>::difference_type difference_type;
        public:
            knuth_morris_pratt(patIter first, patIter last) 
                : m_pattern_first(first), m_pattern_last(last), 
                m_pattern_length(std::distance(m_pattern_first, m_pattern_last)), 
                m_next(m_pattern_length+1) {
                init_next_table();
            }
            
            ~knuth_morris_pratt () { }

            template<typename corpusIter>
            std::pair<corpusIter, corpusIter>
            operator()(corpusIter corpus_first, corpusIter corpus_last) const {
                static_assert(
                    std::is_same<
                        typename std::iterator_traits<patIter>::value_type, 
                        typename std::iterator_traits<corpusIter>::value_type
                    >::value,
                    "pattern type dismatch corpus type" 
                );
                if(corpus_first == corpus_last)
                    return std::make_pair(corpus_last, corpus_last);
                if(m_pattern_first == m_pattern_last)
                    return std::make_pair(corpus_first, corpus_first);
                
                const difference_type corpus_length = std::distance(corpus_first, corpus_last);
                if(corpus_length < m_pattern_length)
                    return std::make_pair(corpus_last, corpus_last);

                return do_search(corpus_first, corpus_last, corpus_length);
            }

        private:
            void init_next_table() {
                difference_type i = 0, j = -1;

                m_next[0] = -1;
                while(i < m_pattern_length) {
                    while(j > -1 && m_pattern_first[i] != m_pattern_first[j]) {
                        j = m_next[j];
                    }
                    ++i, ++j;
                    if(m_pattern_first[i] == m_pattern_first[j])
                        m_next[i] = m_next[j];
                    else
                        m_next[i] = j;
                }
            }

            template<typename corpusIter>
            std::pair<corpusIter, corpusIter>
            do_search(corpusIter corpus_first, corpusIter corpus_last, difference_type corpus_length) const {
                difference_type match_index = 0, pattern_index = 0;
                while(match_index < corpus_length) {
                    while(pattern_index > -1 && m_pattern_first[pattern_index] != corpus_first[match_index]) {
                        pattern_index = m_next[pattern_index];
                    }
                    ++pattern_index, ++match_index;
                    
                    if(pattern_index == m_pattern_length) {
                        return std::make_pair(corpus_first + match_index - m_pattern_length, corpus_first + match_index);
                    }
                }
                return std::make_pair(corpus_last, corpus_last);
            }

        private:
            patIter m_pattern_first, m_pattern_last;
            const difference_type m_pattern_length;
            std::vector<difference_type> m_next;
        };

        template<typename patIter, typename corpusIter>
        std::pair<corpusIter, corpusIter> 
        knuth_morris_pratt_search(corpusIter corpus_first, corpusIter corpus_last, 
                patIter pat_first, patIter pat_last) 
        {
            knuth_morris_pratt<patIter> kmp(pat_first, pat_last);
            return kmp(corpus_first, corpus_last);
        }
    }
}

#endif /* _R00TK1T_KNUTH_MORRIS_PRATT_H */