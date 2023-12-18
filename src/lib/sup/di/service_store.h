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
 * Copyright (c) : 2010-2023 ITER Organization,
 *                 CS 90 046
 *                 13067 St. Paul-lez-Durance Cedex
 *                 France
 *
 * This file is part of ITER CODAC software.
 * For the terms and conditions of redistribution or use of this software
 * refer to the file ITER-LICENSE.TXT located in the top level directory
 * of the distribution package.
 ******************************************************************************/

#ifndef SUP_DI_SERVICE_STORE_H_
#define SUP_DI_SERVICE_STORE_H_

#include <sup/di/dependency_traits.h>
#include <sup/di/error_codes.h>
#include <sup/di/index_sequence.h>
#include <sup/di/instance_container.h>
#include <sup/di/type_functions.h>
#include <sup/di/type_map.h>
#include <sup/di/type_list.h>

#include <map>
#include <stdexcept>
#include <string>
#include <vector>

namespace sup
{
namespace di
{
namespace internal
{
template <typename Key>
using InstanceMap = std::map<Key, std::unique_ptr<internal::AbstractInstanceContainer>>;

template <typename Key>
class ServiceStore
{
public:
  ServiceStore() = default;
  ~ServiceStore() = default;

  template <std::size_t I, typename... Deps>
  InjectionType<NthType<TypeList<Deps...>, I>> GetInstance(const std::vector<Key>& key_list);
private:
  TypeMap<InstanceMap<Key>> m_typed_instance_map;

  template <typename Dep>
  InjectionType<Dep> GetInstanceImpl(const Key& key);
};

template <typename Key>
template <std::size_t I, typename... Deps>
InjectionType<NthType<TypeList<Deps...>, I>>
ServiceStore<Key>::GetInstance(const std::vector<Key>& key_list)
{
  return GetInstanceImpl<NthType<TypeList<Deps...>, I>>(key_list[I]);
}

template <typename Key>
template <typename Dep>
InjectionType<Dep> ServiceStore<Key>::GetInstanceImpl(const Key& key)
{
  auto map_it = m_typed_instance_map.find<ValueType<Dep>>();
  if (map_it == m_typed_instance_map.end())
  {
    throw std::runtime_error("ServiceStore::GetInstance: accessing unknown service type");
  }
  auto instance_it = map_it->second.find(key);
  if (instance_it == map_it->second.end())
  {
    throw std::runtime_error("ServiceStore::GetInstance: accessing unknown instance");
  }
  return PointerToInjectionType<Dep>::Forward(instance_it->second->Get());
}

}  // namespace internal

}  // namespace di

}  // namespace sup

#endif  // SUP_DI_SERVICE_STORE_H_
