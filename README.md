# Ru:

# Этот репозиторий содержит некоторую реализацию функционала стандартной библиотеки.

## forward
Свои две перегрузки функции forward для разбора механизма идеальной передачи и столкновения ссылок.Также учтены все проверки как в STL и записаны все зависимости вроде constexpr булевой переменной для проверки в static_assert или же запаковки значения в тип.И в некотором роде свои type_traits.

## move
своя функция move.Использует все те же алиесы и структуры что и обычный std::move.Сама функция move ничего не перемещает.А лишь делает cast к rvalue ссылке

## Pair
собственный объект который хранит пару.Его конструктор использует 'универсальные' ссылки и forward для идеальной передачи


# Eng:


# This repository contain some realization functional standart library.

## Forward 

Own two overloads function forward for get knowledge mehanicsm perfect forward and collapsing reference.And taken into account all verify like STL,like constexpr or static_assert.And own Type_traits

## move

Own function move.Using all what and usually std::move.Move dont move resource.Move make resource movable

## Pair

Own object,which store pair object.Pair constructor use 'universal' reference and forward for perfect forward
