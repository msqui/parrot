#include <iostream>
#include <cstdlib>

#include <utility>
#include <iterator>

#include <tbb/tick_count.h>
#include <tbb/parallel_for.h>

#include <boost/program_options.hpp>
namespace po = boost::program_options;

#include "ArrIndex.h"

using namespace std;

#ifdef CLOCK
double clock_interval(const tbb::tick_count& start, const tbb::tick_count& finish)
{
  return (finish - start).seconds();
}
#endif

int main(int argc, char** argv)
{
  size_t total_records;
  
  // Command line processing
  po::options_description generic("Generic options");
  generic.add_options()
    ("help", "show help message")
    ;
  
  po::options_description config("Configuration");
  config.add_options()
    ("total-records", po::value<size_t>(&total_records)->default_value(1000000), "total records to seed")
    ;
    
  po::options_description desc;
  desc.add(generic).add(config);
  
  po::positional_options_description p;
  p.add("total-records", -1);

  po::variables_map vm;
  po::store(po::command_line_parser(argc, argv).
    options(desc).positional(p).run(), vm);
  po::notify(vm);
    
  if (vm.count("help")) {
    cout << "Usage: sample [total_records]" << endl;
    cout << desc << endl;
    return EXIT_SUCCESS;
  }
  
#ifdef CLOCK
  tbb::tick_count start = tbb::tick_count::now();
#endif

#ifdef CLOCK
  tbb::tick_count seed_start = tbb::tick_count::now();
#endif

  ArrIndex index;

  ValItemT possible_items[] = {
      "Beef",
      "Bread",
      "Chicken",
      "Sugar",
      "Salt",
      "Tomatoes",
      "Potatoes",
      "Backon",
      "Apple",
      "Orange",
      "Cherry",
      "Beer",
      "sdfsdf",
      "sdff",
      "sdfdf",
      "sdfsdfsdf",
      "sdfsdcf",
      "sf",
      "sfsdf",
      "sdsfdvsdf",
  };

  srand(time(0));
  tbb::parallel_for(tbb::blocked_range<size_t>(0, total_records), [&possible_items, &index](const tbb::blocked_range<size_t>& r) {
    for (size_t i = r.begin(); i != r.end(); ++i) {
      ValT val;
      size_t items_count = 1 + rand() % 12;
      for (size_t j = 0; j != items_count; ++j) {
        val.insert(possible_items[rand() % 20]);
      }
  
      index.insert(make_pair(i, val));
    }
  });

  QueryT query;
  query.insert("Bread");
  query.insert("Antelope");
  query.insert("Parrot");
  query.insert("Beer");
  query.insert("Potatoes");
  query.insert("Backon");
  query.insert("Apple");
  query.insert("Orange");
  query.insert("Cherry");
  query.insert("Cherry2");
  query.insert("Cherry3");
  query.insert("Cherry4");
  query.insert("Cherry5");
  query.insert("Cherry6");
  query.insert("Cherry7");
  query.insert("Cherry8");

#ifdef CLOCK
  tbb::tick_count seed_finish = tbb::tick_count::now();
#endif

#ifdef CLOCK
  tbb::tick_count search_start = tbb::tick_count::now();
#endif

  ResVecPtrT res_ptr = index.find(query);

#ifdef CLOCK
  tbb::tick_count search_finish = tbb::tick_count::now();
#endif

#ifdef CLOCK
  tbb::tick_count finish = tbb::tick_count::now();
#endif

  cout << "Total found: " << res_ptr->size() << endl;

#ifdef CLOCK
  cout << "Total time: " << clock_interval(start, finish) << endl;
  cout << "Seed time: " << clock_interval(seed_start, seed_finish) << endl;
  cout << "Search time: " << clock_interval(search_start, search_finish) << endl;
#endif

  return EXIT_SUCCESS;
}
