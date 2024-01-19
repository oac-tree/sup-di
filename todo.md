# To do list

* Unit tests for sup-di-composer

Dependency traits:

Use dependency traits by passing `std::remove_cv<T>::type` to it. This removes the topmost const/volatile qualifiers that do not have any impact. Remember that it will not remove const from references such as `const int&`.

## Inject by value

Parameter type is `T`, with `std::is_object<T>::value == true` (no void, function or reference). This does not exclude pointer types but those will be handled by a specialization.

The traits are as follows:

* `ValueType`: `T`
* `InjectionType`: `T&` forwards stored lvalue
* `FactoryArgumentType`: `T&`

## Inject by pointer

Parameter type is `(cv) T*`, with `ValueType<T>` equal to `T`. This disables storing pointers in the `ServiceStore` (as that would require a dependency type of `T**`). Although there might be uses for storing pointers (if they point to some global object), enabling them would cause a lot of complexity, e.g. how would we know a pointer is stored if the dependency type is just `T*`?

The traits are as follows:

* `ValueType`: `T`
* `InjectionType`: `T*` forwards pointer by value (always accepted by parameter `(cv) T*` as this is a qualification conversion)
* `FactoryArgumentType`: `T*`

## Inject by lvalue reference

Parameter type is `(cv) T&`, with `ValueType<T>` equal to `T`. See injection by pointer for the reason of this restriction.

The traits are as follows:

* `ValueType`: `T`
* `InjectionType`: `T&` forwards pointer by value (always accepted by parameter `(cv) T*` as this is a qualification conversion)
* `FactoryArgumentType`: `T&`

## Inject by unique pointer value

Parameter type is `std::unique_ptr<(cv) T>`, with `ValueType<T>` equal to `T`. See injection by pointer for the reason of this restriction.

The traits are as follows:

* `ValueType`: `T`
* `InjectionType`: `std::unique_ptr<(cv) T>`, which as a return type is a prvalue
* `FactoryArgumentType`: `std::unique_ptr<(cv) T>&&`

## Inject by rvalue reference to unique pointer

Parameter type is `std::unique_ptr<(cv) T>&&`, with `ValueType<T>` equal to `T`. See injection by pointer for the reason of this restriction.

The traits are as follows:

* `ValueType`: `T`
* `InjectionType`: `std::unique_ptr<(cv) T>`, which as a return type is a prvalue
* `FactoryArgumentType`: `std::unique_ptr<(cv) T>&&`
