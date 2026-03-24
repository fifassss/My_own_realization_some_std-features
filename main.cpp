
// структура который запаковывает тип в значение
template <class Ty, Ty Val>
struct integral_constant
{
    static constexpr Ty value = Val; 
    using value_type = Ty; 
    using type = integral_constant; 

    operator value_type() const noexcept 
    {
        return value;
    }

    value_type operator()() const noexcept 
    {
        return value;
    }
};

// запаковываем true и false в типы
using true_type = integral_constant<bool, true>;
using false_type = integral_constant <bool, false>;

// 3 структуры которые удаляет ссылку от типа
template<class Ty>
struct remove_refence_t 
{
    using Type = Ty;
    using Const_refs = const Ty;
};

template<class Ty>
struct remove_refence_t<Ty&>
{
    using Type = Ty;
    using Const_refs = const Ty&;
};

template<class Ty>
struct remove_refence_t<Ty&&> 
{
    using Type = Ty;
    using Const_refs = const Ty&&;
};
// 3 структуры которые удаляет ссылку от типа

// алиес на вытаскивание типа
template<class Ty>
using remove_ref_t = typename remove_refence_t<Ty>::Type; // тут даем понять,что мы хотим вытащить тип а не переменную!

// если тип не имеет l-lvalue ссылку
template<class Ty>
struct is_lvalue_reference : false_type {}; 


// если тип имеет l-value ссылку
template<class Ty>
struct is_lvalue_reference<Ty&> : true_type {}; 

// тут шаблонная переменная
template<class T>
constexpr bool is_lvalue_reference_v = is_lvalue_reference<T>::value; // ДОЛЖЕН БЫТЬ constexpr - то есть должно быть вычисленно на этапе компиляции а не в рантайме! + переменная должна быть константой или же константным выражением, известным на этапе компиляции.Так как static_assert требует 
//Константное выражение — целочисленное константное выражение, которое можно преобразовать в логическое значение.

// реализация идеальной передачи с помощью универсальной передачи ссылки и первой перегрузки функции для lvalue значений.
template<class Ty>
constexpr Ty&& forward(remove_ref_t<Ty>& Arg) noexcept 
{
    return static_cast<Ty&&>(Arg); 
}

// реализация идеальной передачи с помощью универсальной передачи ссылки и второй перегрузки функции для rvalue значений.
template<class Ty>
constexpr Ty&& forward(remove_ref_t<Ty>&& Arg) noexcept
{
    static_assert(!is_lvalue_reference_v<Ty>, "bad forward call"); // условие должно быть известно на этапе компиляции
    return static_cast<Ty&&>(Arg);
}

// своя реализация std::move.
template<class T>
constexpr remove_ref_t<T>&& move(T&& value) noexcept
{
    return static_cast<remove_ref_t<T>&&>(value);
}

// тут я применил forward
template<class T1, class T2>
struct Pair
{
    T1 first;
    T2 second;
    Pair() : first(), second() {}

    template<class U1, class U2>
    Pair(U1&& obj1, U2&& obj2) : first(forward<U1>(obj1)), second(forward<U2>(obj2)) {}

    Pair(const Pair& obj) = default;
    Pair(Pair&& obj) = default;
    Pair& operator=(const Pair& obj) = default;
    Pair& operator=(Pair&& obj) = default;
};
