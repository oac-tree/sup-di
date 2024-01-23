# Type functions

In the following table, the `Dependency` type denotes the type of the function parameters (for factory or global functions). The `ValueType` is the type used to store instances in a map. `InjectionType` is the return type of functions that inject a value into the original factory of global functions and `FactoryArgumentType` is used as a parameter type for functions that need to forward their arguments to the registered factory or global functions.

The following code excerpt shows the different usages, starting from a global function with a `Dep` parameter type:

```c++
// Global function that is registered:
bool f(Dep dep);

// The argument for that function will be stored in a map as:
std::unique_ptr<ValueType<Dep>> instance;

// A function that forwards such an instance:
bool forward_f(FactoryArgumentType<Dep> dep)
{
  f(ForwardDependency<Dep>::Forward(dep));
}

// A function that retrieves an instance and returns it in the correct type to be injected into the global function:
InjectionType<Dep> GetInstance(Key instance_key);

// Call the globale function with the instance:
f(GetInstance(instance_key));
```

The following table shows the possible type mappings, where `UP` denotes `std::unique_ptr` and `(CV)` is an optional CV qualification of the type that follows.

| Dependency   | ValueType | InjectionType | ForwardingArgType |
| ------------ | --------- | ------------- | ----------------- |
| (CV) T       | T         | T&            | T&                |
| (CV) T*      | T         | T*            | T*                |
| (CV) T&      | T         | T&            | T&                |
| UP\<T>       | T         | UP\<T>        | UP\<T>&&          |
| UP\<T>&&     | T         | UP\<T>        | UP\<T>&&          |
