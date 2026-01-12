#include <iostream>
#include <vector>
#include <stdexcept>

template<typename T>
class Iterator {
public:
    virtual ~Iterator() = default;
    virtual bool HasNext() const = 0;
    virtual T Next() = 0;
};

template<typename T>
class VectorIterator : public Iterator<T> {
private:
    std::vector<T>& items;
    size_t position;
    
public:
    VectorIterator(std::vector<T>& vec) : items(vec), position(0) {}
    
    bool HasNext() const override {
        return position < items.size();
    }
    
    T Next() override {
        if (!HasNext()) {
            throw std::out_of_range("No more elements");
        }
        return items[position++];
    }
};

template<typename T>
class Container {
private:
    std::vector<T> items;
    
public:
    void Add(const T& item) {
        items.push_back(item);
    }
    
    std::unique_ptr<Iterator<T>> createIterator() {
        return std::make_unique<VectorIterator<T>>(items);
    }
};

int main() {
    Container<int> container;
    container.Add(1);
    container.Add(2);
    container.Add(3);
    container.Add(4);
    
    auto iterator = container.createIterator();
    while (iterator->HasNext()) {
        std::cout << iterator->Next() << " ";
    }
    
    return 0;
}
