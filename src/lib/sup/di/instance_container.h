/******************************************************************************
 * $HeadURL: $
 * $Id: $
 *
 * Project       : Supervision and Automation - Dependency injection
 *
 * Description   : The definition and implementation for dependency injection templates in SUP.
 *
 * Author        : Walter Van Herck (IO)
 *
 * Copyright (c) : 2010-2025 ITER Organization,
 *                 CS 90 046
 *                 13067 St. Paul-lez-Durance Cedex
 *                 France
 * SPDX-License-Identifier: MIT
 *
 * This file is part of ITER CODAC software.
 * For the terms and conditions of redistribution or use of this software
 * refer to the file LICENSE located in the top level directory
 * of the distribution package.
 ******************************************************************************/

#ifndef SUP_DI_INSTANCE_CONTAINER_H_
#define SUP_DI_INSTANCE_CONTAINER_H_

#include <memory>

namespace sup
{
namespace di
{
namespace internal
{

/**
 * @brief Interface for a container that owns a single pointer with type erasure.
 */
class AbstractInstanceContainer
{
public:
  virtual ~AbstractInstanceContainer();

  virtual void* Get() = 0;
  virtual void* Release() = 0;
};

/**
 * @brief Class template for a container that owns a single pointer of the provided type.
 */
template <class T, class Deleter>
class InstanceContainer : public AbstractInstanceContainer
{
public:
  ~InstanceContainer() = default;

  explicit InstanceContainer(std::unique_ptr<T, Deleter>&& p)
    : pointer(std::move(p)) {}

  void* Get() override
  {
    return pointer.get();
  }

  void* Release() override
  {
    return pointer.release();
  }

private:
  std::unique_ptr<T, Deleter> pointer;
};

/**
 * @brief Function template that creates a new InstanceContainer using template argument deduction.
 */
template <class T, class Deleter>
InstanceContainer<T, Deleter>* MakeInstanceContainer(std::unique_ptr<T, Deleter>&& p)
{
  return new InstanceContainer<T, Deleter>(std::move(p));
}

/**
 * @brief Function template that wraps a unique_ptr to a type into a unique_ptr to an
 * AbstractInstanceContainer.
 */
template <class T, class Deleter>
std::unique_ptr<AbstractInstanceContainer> WrapIntoContainer(std::unique_ptr<T, Deleter>&& p)
{
  return std::unique_ptr<AbstractInstanceContainer>{MakeInstanceContainer(std::move(p))};
}

/**
 * @brief Retrieve the instance pointer of the container. This function is overloaded to distinguish
 * between the need to just retrieve the pointer or release the object.
 */
void* GetInstancePointer(AbstractInstanceContainer& container, std::true_type release);

void* GetInstancePointer(AbstractInstanceContainer& container, std::false_type do_not_release);

}  // namespace internal

}  // namespace di

}  // namespace sup

#endif  // SUP_DI_INSTANCE_CONTAINER_H_
