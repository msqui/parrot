#include "ArrIndex.h"

#include <algorithm>

#include <tbb/parallel_for.h>

using namespace std;

const size_t ArrIndex::THRESHOLD = 3;

void ArrIndex::insert(const IndPairT& pair)
{
  _index.push_back(pair);
}

ResVecPtrT ArrIndex::find(const QueryT & query) const
{
  ResVecPtrT res_ptr(new ResVecT);
  if (_index.empty()) return res_ptr;
  
  // Search Kernels
  const auto manual_kernel =
    [&query, res_ptr](const IndPairT& p) {
      const ValT& val = p.second;
      const size_t val_size = val.size();
      const size_t need_to_count = val_size > THRESHOLD
                                    ? val_size - THRESHOLD
                                    : 1;

      if (query.size() < need_to_count
          || val_size == 0) return;
      
      size_t count = 0;
      size_t rest_to_count = need_to_count;
      QueryT::const_iterator q_iter;
      ValT::const_iterator val_iter;
      for (q_iter = query.begin(); q_iter != query.end(); ++q_iter) {
        if (std::distance(q_iter, query.end()) < rest_to_count) return;
        val_iter = val.find(*q_iter);
        if (val_iter != val.end()) {
          ++count;
          --rest_to_count;
          if (std::distance(val_iter, val.end()) < rest_to_count) return;
        }
        
        if (count >= need_to_count) {
          res_ptr->push_back(p.first);
          return;
        }
      }
    };
    
  const auto intersection_kernel = 
    [&query, res_ptr](const IndPairT& p) {
      const ValT& val = p.second;
      const size_t val_size = val.size();
      const size_t q_size = query.size();
      const size_t need_to_count = val_size > THRESHOLD
                                    ? val_size - THRESHOLD
                                    : 1;

      if (q_size < need_to_count
          || val_size == 0) return;

      typedef vector<ValItemT> InterVecT;
      InterVecT v( max(val_size, q_size) );
      const InterVecT::const_iterator it = set_intersection(val.begin(), val.end(),
                                                            query.begin(), query.end(),
                                                            v.begin());
      const size_t count = static_cast<size_t>(it - v.begin());

      if (count >= need_to_count) {
        res_ptr->push_back(p.first);
        return;
      }
    };
  
  // Selected kernel
  // TODO: Add compile-time definition to select kernel
  const auto& kernel = intersection_kernel;
  
  // Parallel loops
  static tbb::affinity_partitioner ap;
  tbb::parallel_for(_index.range(), [&kernel](const IndT::const_range_type& r) {
    IndT::const_range_type::const_iterator i;
    for (i = r.begin(); i != r.end(); ++i) {
      kernel(*i);
    }
  }, ap);
  
  return res_ptr;
}



