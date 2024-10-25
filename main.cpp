
#include <future>
#include <iostream>
#include <vector>
using namespace std;
void sort_helper(size_t i,  size_t size, vector<size_t> &list, promise<size_t> &prom) {
  size_t min = i;
  for (size_t j = i + 1; j < size; j++) {
   
    if (list[j] < list[min]) {
      min = j;
    }
  }
  prom.set_value(min);
}

void my_sort(vector<size_t> &list) {
  size_t size = list.size();
  for (size_t i = 0; i < size - 1; i++) {
    promise<size_t> prom;
    size_t min = i;

  
    future<size_t> futur = prom.get_future();

    thread s1(sort_helper,i, size, ref(list),ref(prom));
    
    s1.join();
    size_t min_index = futur.get();
    if (min_index != i) {
      std::swap(list[min_index], list[i]);
    }
  }
}

int main() {


  vector<size_t> vec1;

  for (size_t i = 0; i < 50; i++) {
    size_t temp = rand() % 50;
    vec1.push_back(temp);
  }

 my_sort(vec1);

   std::copy(vec1.begin(), vec1.end(),
            std::ostream_iterator<int>(std::cout, " "));

}
