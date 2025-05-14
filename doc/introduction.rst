============
Introduction
============

Dependency Injection (DI) is a cornerstone of modern software development, enabling developers to build modular, maintainable, and testable systems. The SUP Dependency Injection (``sup-di``) framework is a robust tool designed to simplify the creation and management of complex object trees. By providing a templated approach to dependency injection, ``sup-di`` promotes separation of concerns without enforcing a specific interface to services or clients.

``sup-di`` is built around the concept of an ``ObjectManager``, which acts as the central hub for managing objects, dependencies, and functions. It supports XML-based configuration, modular design, and extensibility, making it a versatile framework for a wide range of applications.

Key features of ``sup-di`` include:

+ **Dependency Injection for Object Creation and Function Execution**: Inject dependencies into constructors and (member) functions.
+ **XML-Based Configuration**: Define object trees and dependencies declaratively.
+ **Modular Design**: Extend functionality with custom components and services.
+ **Command-Line Application**: Use ``sup-di-composer`` as the composition root.
+ **Error Handling and Validation**: Robust mechanisms for diagnosing and resolving issues.
+ **Support for Shared Libraries**: Dynamically load external components.
