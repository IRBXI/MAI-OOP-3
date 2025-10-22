#pragma once

#include "figure.hpp"

#include <initializer_list>

namespace lib::array {

const std::size_t INITIAL_CAPACITY = 10;

class ArrayFigurePointer {
  private:
    std::size_t capacity_ = 0;
    std::size_t size_ = 0;
    geometry::Figure** data_ = nullptr;

  public:
    ArrayFigurePointer() noexcept;
    ArrayFigurePointer(const std::initializer_list<geometry::Figure*>& init);
    ArrayFigurePointer(const ArrayFigurePointer& other);
    ArrayFigurePointer(ArrayFigurePointer&& other) noexcept;
    ~ArrayFigurePointer() noexcept;

    ArrayFigurePointer& operator=(const ArrayFigurePointer& other);
    ArrayFigurePointer& operator=(ArrayFigurePointer&& other) noexcept;

    geometry::Figure* const Front() const noexcept;
    geometry::Figure* Front() noexcept;
    geometry::Figure* const Back() const noexcept;
    geometry::Figure* Back() noexcept;

    std::size_t Size() const noexcept;
    std::size_t Capacity() const noexcept;

    geometry::Figure** Data() noexcept;
    geometry::Figure* const* Data() const noexcept;

    // I wish I could use operator[] here
    // I now can use operator[] here :)
    geometry::Figure* operator[](std::size_t pos) noexcept;
    geometry::Figure* const operator[](std::size_t pos) const noexcept;

    geometry::Figure* At(std::size_t pos);
    geometry::Figure* const At(std::size_t pos) const;

    bool IsEmpty() const noexcept;

    void PushBack(geometry::Figure* val);
    void PopBack() noexcept;
    void Reserve(std::size_t new_cap);
    void Clear() noexcept;
    void Resize(std::size_t count, geometry::Figure* value);

    void Insert(std::size_t pos, geometry::Figure* value);
    void Erase(std::size_t begin_pos, std::size_t end_pos);

    // Figure* specific functions
    void PrintCentroids() const noexcept;
    void PrintAreas() const noexcept;
    double GetTotalArea() const noexcept;

    friend void swap(ArrayFigurePointer& a, ArrayFigurePointer& b);
};

} // namespace lib::array
