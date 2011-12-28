#ifndef ARRINDEX_H_
#define ARRINDEX_H_

#include <string>
#include <set>
#include <map>
#include <vector>
#include <memory>

#include <tbb/concurrent_vector.h>

typedef size_t IdT;
typedef std::string ValItemT;
typedef std::set<ValItemT> ValT;

typedef size_t IndKeyT;
typedef std::pair<IdT, ValT> IndPairT;
typedef tbb::concurrent_vector<IndPairT> IndT;

typedef tbb::concurrent_vector<IdT> ResVecT;
typedef std::shared_ptr<ResVecT> ResVecPtrT;

typedef std::set<ValItemT> QueryT;

class ArrIndex
{
  IndT _index;

public:
  ArrIndex() {}
  virtual ~ArrIndex() {}
  
  static const size_t THRESHOLD;

  void insert(const IndPairT& pair);

  ResVecPtrT find(const QueryT& query) const;
};

#endif /* ARRINDEX_H_ */
