# MAI-OOP-3

Вариант - 28

[Документ со всеми вариантами](https://github.com/DVDemon/mai_oop_examples_public/blob/main/homeworks/2025_%D0%9B%D0%A0_%D0%9E%D0%9E%D0%9F_3.pdf)

## Структура проекта

- `lib/` - исходный код библиотек
- `tests/` - unit-тесты с использованием Google Test
- `CMakeLists.txt` - конфигурация CMake

## Сборка и запуск

```bash
# Создание директории для сборки
mkdir build
cd build

# Конфигурация CMake
cmake ..

# Сборка проекта
make

# Запуск тестов массива фигур 
./tests/array_of_figures

# Запуск тестов для пятиугольника 
./tests/figures/pentagon

# Запуск тестов для ромба 
./tests/figures/rhombus

# Запуск тестов для трапеции 
./tests/figures/trapezoid

# Запуск всех тестов сразу
./tests/unit
