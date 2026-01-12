#include <iostream>
#include <vector>
#include <memory>

class SortingStrategy {
public:
    virtual ~SortingStrategy() = default;
    virtual void Sort(std::vector<int>& array) = 0;
};

class BubbleSortStrategy : public SortingStrategy {
public:
    void Sort(std::vector<int>& array) override {
        std::cout << "Sorting using Bubble Sort\n";
        for (size_t i = 0; i < array.size(); ++i) {
            for (size_t j = 0; j < array.size() - i - 1; ++j) {
                if (array[j] > array[j + 1]) {
                    std::swap(array[j], array[j + 1]);
                }
            }
        }
    }
};

class QuickSortStrategy : public SortingStrategy {
private:
    void QuickSort(std::vector<int>& array, int low, int high) {
        if (low < high) {
            int pi = Partition(array, low, high);
            QuickSort(array, low, pi - 1);
            QuickSort(array, pi + 1, high);
        }
    }
    
    int Partition(std::vector<int>& array, int low, int high) {
        int pivot = array[high];
        int i = low - 1;
        for (int j = low; j < high; ++j) {
            if (array[j] <= pivot) {
                ++i;
                std::swap(array[i], array[j]);
            }
        }
        std::swap(array[i + 1], array[high]);
        return i + 1;
    }
    
public:
    void Sort(std::vector<int>& array) override {
        std::cout << "Sorting using Quick Sort\n";
        if (!array.empty()) {
            QuickSort(array, 0, array.size() - 1);
        }
    }
};

class Sorter {
private:
    std::unique_ptr<SortingStrategy> strategy;
    
public:
    void SetStrategy(std::unique_ptr<SortingStrategy> newStrategy) {
        strategy = std::move(newStrategy);
    }
    
    void SortArray(std::vector<int>& array) {
        if (strategy) {
            strategy->Sort(array);
        }
    }
};

int main() {
    Sorter sorter;
    std::vector<int> data1 = {5, 3, 8, 4, 2};
    std::vector<int> data2 = {5, 3, 8, 4, 2};
    
    sorter.SetStrategy(std::make_unique<BubbleSortStrategy>());
    sorter.SortArray(data1);
    
    sorter.SetStrategy(std::make_unique<QuickSortStrategy>());
    sorter.SortArray(data2);
    
    return 0;
}
