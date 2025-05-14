===========
Development
===========

``sup-di`` simplifies the development process by providing tools and patterns for managing dependencies and object lifecycles. Below is a guide on how to use ``sup-di`` for development:

Adding Classes to sup-di
^^^^^^^^^^^^^^^^^^^^^^^^

To register a new class to ``sup-di``, follow these steps:

1. Define your class and its dependencies.
2. Register a factory function for the class in the `ObjectManager`.
3. Use the `ForwardingInstanceFactoryFunction` to simplify dependency injection.

Example:

.. code-block:: c++

   #include <sup/di/object_manager.h>
   #include <memory>
   #include <string>

   // Define a new class
   class MyService {
   public:
     MyService(int value, const std::string& name) : value_(value), name_(name) {}
     void Print() const {
       std::cout << "Value: " << value_ << ", Name: " << name_ << std::endl;
     }

   private:
     int value_;
     std::string name_;
   };

   // Register the class in the ObjectManager
   static const bool MyServiceRegistered =
       sup::di::GlobalObjectManager().RegisterFactoryFunction(
           "MyService",
           sup::di::ForwardingInstanceFactoryFunction<MyService, MyService, int, std::string>);


To create an instance of `MyService`, use the `CreateInstance` method:

.. code-block:: c++

   sup::di::GlobalObjectManager().CreateInstance("MyService", "my_service_instance", {"42", "example_name"});

Adding Functions to sup-di
^^^^^^^^^^^^^^^^^^^^^^^^^^

Global functions can also be registered in sup-di. These functions can take dependencies as arguments and are invoked using their registered names.

Example:

.. code-block:: c++

   #include <sup/di/object_manager.h>
   #include <iostream>

   // Define a global function
   bool PrintMessage(const std::string& message) {
     std::cout << "Message: " << message << std::endl;
     return true;
   }

   // Register the function in the ObjectManager
   static const bool PrintMessageRegistered =
       sup::di::GlobalObjectManager().RegisterGlobalFunction("PrintMessage", PrintMessage);

To call the registered function:


.. code-block:: c++

   sup::di::GlobalObjectManager().CallGlobalFunction("PrintMessage", {"Hello, sup-di!"});

Dependency types
^^^^^^^^^^^^^^^^

The ``ObjectManager`` supports dependency injection with various parameter types, including:

* Pass by (const) value
* Pass by reference
* Pass by pointer
* Pass by unique pointer (``std::unique_ptr``)

When using unique pointer parameters, the ``ObjectManager`` will ensure transfer of ownership of the injected object. This means that the registered instance will no longer be available in the ``ObjectManager`` after the injection.

Best Practices
^^^^^^^^^^^^^^

+ Use meaningful names for registered types and functions to avoid conflicts.
+ Leverage `ForwardingInstanceFactoryFunction` for constructor-based dependency injection.
+ Ensure all dependencies are registered before creating instances or calling functions.
+ Use `std::unique_ptr` for ownership transfer and memory safety.
