=================
 sup-di Composer
=================

The ``sup-di-composer`` application is a command-line tool for executing dependency injection configurations. It provides a convenient way to test, debug, and automate DI workflows.

**Command-Line Options**

+ ``-h`` or ``--help``: Display usage information.
+ ``-f <filename>`` or ``--file <filename>``: Load, parse, and execute the specified XML file.

Example usage:

.. code-block:: sh

   ./sup-di-composer --file example.xml

**Use Cases**

1. **Dynamic Configuration**: Modify object graphs and dependencies at runtime by editing the XML configuration.
2. **Testing and Debugging**: Quickly test DI configurations without modifying the source code.
3. **Automation**: Integrate ``sup-di-composer`` into build pipelines or scripts for automated testing and deployment.

**Example**

With the following code compiled as a shared library named libdi-test.so:

.. code-block:: c++

   #include <sup/di/object_manager.h>

   #include <iostream>
   #include <string>

   const std::string PRINT_STRING_NAME = "PrintString";

   bool PrintStringFactoryFunction(std::string str) {
     std::cout << str << std::endl;
     return true;
   }

   const bool PrintStringRegistered = sup::di::GlobalObjectManager().RegisterGlobalFunction(
       PRINT_STRING_NAME, PrintStringFactoryFunction);

And the following XML configuration, example.xml:

.. code-block:: xml

   <?xml version="1.0" encoding="UTF-8"?>
   <ObjectComposer xmlns="http://codac.iter.org/sup/di" version="1.0"
              name="Print Hello World!"
              xmlns:xs="http://www.w3.org/2001/XMLSchema-instance"
              xs:schemaLocation="http://codac.iter.org/sup/di sup-di.xsd">
       <LoadLibrary>./libdi-test.so</LoadLibrary>
        <!-- Setup string to print -->
       <StringInstance>
           <InstanceName>HelloWorld</InstanceName>
           <Value>Hello, World!</Value>
       </StringInstance>
       <!-- Print the defined string -->
       <CallFunction>
           <FunctionName>PrintString</FunctionName>
           <Dependency>HelloWorld</Dependency>
       </CallFunction>
   </ObjectComposer>

Run the ``sup-di-composer`` tool with the XML file:

.. code-block:: sh

                ./sup-di-composer --file example.xml

Expected output:

.. code-block:: text

   Hello, World!

This workflow demonstrates how SUP-DI simplifies the process of creating, managing, and testing object graphs and dependencies. By leveraging ``sup-di-composer``, developers can focus on building functionality while SUP-DI handles the complexity of dependency management.
