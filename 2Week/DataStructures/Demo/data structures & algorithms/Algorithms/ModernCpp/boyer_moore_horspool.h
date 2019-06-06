#ifndef _R00TK1T_BOYER_MOORE_HORSPOOL_H
#define _R00TK1T_BOYER_MOORE_HORSPOOL_H

#include <iterator>
#include "bm_traits.h"

namespace r00tk1t {
    namespace algorithm {
        template<typename patIter, typename traits = detail::BM_traits<patIter> >
        class boyer_moore_horspool {
            typedef typename std::iterator_traits<patIter>::difference_type difference_type;
        public:
            boyer_moore_horspool(patIter first, patIter last)
                : m_pat_first(first), m_pat_last(last), 
                  m_pat_length(std::distance(first, last)),
                  m_skip(m_pat_length, m_pat_length) {

                std::size_t i = 0;
                if(first != last) {
                    for(patIter iter = first; iter != last-1; ++iter, ++i) {
                        m_skip.insert(*iter, m_pat_length - 1 - i);
                    }
                    m_skip.print_skip_table();
                }
            }

            ~boyer_moore_horspool() { }

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
            template<typename corpusIter>
            std::pair<corpusIter, corpusIter>
            do_search(corpusIter corpus_first, corpusIter corpus_last) const {
                corpusIter curPos = corpus_first;
                const corpusIter lastPos = corpus_last - m_pat_length;

                while(curPos <= lastPos) {
                    std::size_t j = m_pat_length - 1;
                    while(m_pat_first[j] == curPos[j]) {
                        if(j == 0)
                            return std::make_pair(curPos, curPos + m_pat_length);
                        --j;
                    }
                    curPos += m_skip[curPos[m_pat_length - 1 ]];
                }
                return std::make_pair(corpus_last, corpus_last); 
            }
        private:
            patIter m_pat_first, m_pat_last;
            const difference_type m_pat_length;
            typename traits::skip_table_t m_skip;
        };
    }
}

#endif