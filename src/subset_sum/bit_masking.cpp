#include "assignment/subset_sum/bit_masking.hpp"

#include <cassert>  // assert

#include "assignment/bits.hpp"  // is_bit_set, mask2indices

namespace assignment {

  std::vector<std::vector<int>> SubsetSumBitMasking::search(const std::vector<int>& set, int target_sum) const {
    assert(target_sum > 0 && set.size() <= 16);

    std::vector<std::vector<int>> indices;

    const auto num_elems = static_cast<int>(set.size());  // N
    const int num_subsets = 1 << num_elems;               // 2^N

    // 1. Внешний цикл: пробегаемся по всем битовым маскам от 0..00 до 1..11
    // 2. Внутренний цикл: проверка разрядов битовой маски и генерация подмножества, ассоциирующегося с этой маской
    // 3. Подсчет суммы текущего подмножества, сохранение индексов подмножества с целевой суммой в результат
    // Tips: можно пропустить итерацию, если сумма текущего подмножества стала больше целевой суммы
    for (int x = 0; x < num_subsets; x++){
      std::vector<int> subset;
      for (int y = 0; y < num_elems; y++){
        if (is_bit_set(x, y)){
          subset.push_back(y);
        }
      }
      int cur = 0;
      for (int x = 0; x <subset.size(); x++){
        cur += set[subset[x]];
        if (cur>target_sum){
          break;
        }
      }
      if (cur == target_sum){
        indices.push_back(subset);
      }
    }
    return indices;
  }

}  // namespace assignment