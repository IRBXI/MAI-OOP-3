#include "array.hpp"

#include <cassert>
#include <cstring>
#include <iostream>
#include <stdexcept>

#include "figure.hpp"

namespace lib::array {

ArrayFigurePointer::ArrayFigurePointer() noexcept {}

ArrayFigurePointer::ArrayFigurePointer(
    const std::initializer_list<geometry::Figure*>& init) {
    Reserve(init.size());
    for (geometry::Figure* x : init) {
        PushBack(x);
    }
}

ArrayFigurePointer::ArrayFigurePointer(const ArrayFigurePointer& other) {
    Reserve(other.capacity_);
    size_ = other.size_;
    for (std::size_t i = 0; i < other.size_; ++i) {
        data_[i] = other.data_[i];
    }
}

ArrayFigurePointer::ArrayFigurePointer(ArrayFigurePointer&& other) noexcept
    : capacity_(other.capacity_), size_(other.size_), data_(other.data_) {
    other.capacity_ = 0;
    other.size_ = 0;
    other.data_ = nullptr;
}

ArrayFigurePointer&
ArrayFigurePointer::operator=(const ArrayFigurePointer& other) {
    if (this != &other) {
        ArrayFigurePointer temp(other);
        swap(*this, temp);
    }
    return *this;
}

ArrayFigurePointer&
ArrayFigurePointer::operator=(ArrayFigurePointer&& other) noexcept {
    if (this != &other) {
        ArrayFigurePointer temp(std::move(other));
        swap(*this, temp);
    }
    return *this;
}

ArrayFigurePointer::~ArrayFigurePointer() noexcept { delete[] data_; }

geometry::Figure* ArrayFigurePointer::Front() noexcept {
    assert(size_ > 0);
    return data_[0];
}

geometry::Figure* const ArrayFigurePointer::Front() const noexcept {
    assert(size_ > 0);
    return data_[0];
}

geometry::Figure* ArrayFigurePointer::Back() noexcept {
    assert(size_ > 0);
    return data_[size_ - 1];
}

geometry::Figure* const ArrayFigurePointer::Back() const noexcept {
    assert(size_ > 0);
    return data_[size_ - 1];
}

std::size_t ArrayFigurePointer::Size() const noexcept { return size_; }

std::size_t ArrayFigurePointer::Capacity() const noexcept { return capacity_; }

geometry::Figure** ArrayFigurePointer::Data() noexcept { return data_; }

geometry::Figure* const* ArrayFigurePointer::Data() const noexcept {
    return data_;
}

geometry::Figure* ArrayFigurePointer::operator[](std::size_t pos) noexcept {
    assert(pos < size_);
    return data_[pos];
}

geometry::Figure* const
ArrayFigurePointer::operator[](std::size_t pos) const noexcept {
    assert(pos < size_);
    return data_[pos];
}

geometry::Figure* ArrayFigurePointer::At(std::size_t pos) {
    if (pos >= size_) {
        throw std::out_of_range("The index is out of range of the array");
    }
    return data_[pos];
}

geometry::Figure* const ArrayFigurePointer::At(std::size_t pos) const {
    if (pos >= size_) {
        throw std::out_of_range("The index is out of range of the array");
    }
    return data_[pos];
}

bool ArrayFigurePointer::IsEmpty() const noexcept { return size_ == 0; };

void ArrayFigurePointer::PushBack(geometry::Figure* val) {
    if (size_ == capacity_) {
        Reserve(capacity_ * 2);
    }
    data_[size_] = val;
    size_++;
};

void ArrayFigurePointer::PopBack() noexcept {
    assert(size_ > 0);
    size_--;
}

void ArrayFigurePointer::Reserve(std::size_t new_cap) {
    if (new_cap > capacity_ or capacity_ == 0) {
        std::size_t alloc_cap = std::max(new_cap, INITIAL_CAPACITY);
        geometry::Figure** new_data = new geometry::Figure*[alloc_cap];
        if (data_) {
            std::memcpy(new_data, data_, size_);
            delete[] data_;
        }
        data_ = new_data;
        capacity_ = alloc_cap;
    }
}

void ArrayFigurePointer::Clear() noexcept { size_ = 0; }

void ArrayFigurePointer::Resize(size_t count, geometry::Figure* value) {
    std::size_t old_size = size_;
    if (count < size_) {
        for (std::size_t i = 0; i < old_size - count; ++i) {
            PopBack();
        }
        return;
    }
    if (count > capacity_) {
        Reserve(count);
    }
    for (std::size_t i = 0; i < count - old_size; ++i) {
        PushBack(value);
    }
}

void ArrayFigurePointer::Insert(std::size_t pos, geometry::Figure* value) {
    if (size_ == capacity_) {
        Reserve(capacity_ * 2);
    }
    for (std::size_t i = size_; i > pos; --i) {
        data_[i] = data_[i - 1];
    }
    data_[pos] = value;
    size_++;
}

void ArrayFigurePointer::Erase(std::size_t begin_pos, std::size_t end_pos) {
    if (begin_pos >= size_) {
        return;
    }
    if (end_pos == size_) {
        size_ = size_ - (end_pos - begin_pos);
        return;
    }
    // Example:
    //       012345678
    // erase     ---
    // size_ = 9 end_pos = 6 need to copy last 9 - 6 - 1 = 2 elements to the
    // begin_pos = 4
    std::memcpy(data_ + begin_pos, data_ + end_pos + 1,
                (size_ - end_pos - 1) * sizeof(geometry::Figure*));
    size_ = size_ - (end_pos - begin_pos);
}

void ArrayFigurePointer::PrintCentroids() const noexcept {
    for (std::size_t i = 0; i < size_; ++i) {
        std::cout << "Figure " << i << " centroid: " << data_[i]->Centroid()
                  << std::endl;
    }
}

void ArrayFigurePointer::PrintAreas() const noexcept {
    for (std::size_t i = 0; i < size_; ++i) {
        std::cout << "Figure " << i
                  << " area: " << static_cast<double>(*data_[i]) << std::endl;
    }
}

double ArrayFigurePointer::GetTotalArea() const noexcept {
    double total_area = 0.0;
    for (std::size_t i = 0; i < size_; ++i) {
        total_area += static_cast<double>(*data_[i]);
    }
    return total_area;
}

void swap(ArrayFigurePointer& a, ArrayFigurePointer& b) {
    std::swap(a.capacity_, b.capacity_);
    std::swap(a.size_, b.size_);
    std::swap(a.data_, b.data_);
}

} // namespace lib::array
