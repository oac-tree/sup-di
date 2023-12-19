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
/**
 * @brief InstanceMap maps objects of type Key to AbstractInstanceContainer objects.
 */
template <typename Key>
using InstanceMap = std::map<Key, std::unique_ptr<internal::AbstractInstanceContainer>>;

/**
 * @brief ServiceStore is a templated storage map to store and retrieve instances of any type.
 *
 * @note The class uses type erasure to store the instances as AbstractInstanceContainer objects.
 */
template <typename Key>
class ServiceStore
{
public:
  ServiceStore() = default;
  ~ServiceStore() = default;

  /**
   * @brief Get an object with the correct type to inject it in a function or method that has a
   * parameter of Dep, where Dep is the I'th type in the Deps template parameter pack and its key
   * is the I'th key in the provided key_list.
   *
   * @return The instance of the correct type for injection.
   */
  template <std::size_t I, typename... Deps>
  InjectionType<NthType<TypeList<Deps...>, I>> GetInstance(const std::vector<Key>& key_list);

  /**
   * @brief Store an object with the provided type under the given key.
   *
   * @return True on success. False implies there was already an instance of the given type and key.
   */
  template <typename Service>
  bool StoreInstance(std::unique_ptr<Service> instance, const Key& key);
private:
  TypeMap<InstanceMap<Key>> m_typed_instance_map;

  /**
   * @brief Helper method for GetInstance.
   */
  template <typename Dep>
  InjectionType<Dep> GetInstanceImpl(const Key& key);

  /**
   * @brief Helper method for StoreInstance.
   */
  template <typename Service>
  InstanceMap<Key>& GetInstanceMap();
};

/**
 * @brief Helper function template to retrieve a typed value pointer from an instance container
 * and release its ownership when required.
 */
template <typename Dep>
ValueType<Dep>* GetValuePointer(AbstractInstanceContainer& container)
{
  return static_cast<ValueType<Dep>*>(GetInstancePointer(container, TransferOwnership<Dep>{}));
}

/**
 * @brief Class that retrieves an instance from an instance map by key and removes it in its
 * destructor if ownership was released.
 */
template <typename Key, typename Dep>
class DependencyRetriever
{
public:
  /**
   * @brief Construct a new Dependency Retriever object
   *
   * @throws std::runtime_error when the provided key could not be found in the map.
   */
  DependencyRetriever(InstanceMap<Key>& instance_map, const Key& key);

  /**
   * @brief Destroy the DependencyRetriever object and erase the iterator from the map if ownership
   * was transferred.
   */
  ~DependencyRetriever();

  /**
   * @brief Retrieve the instance pointed to by the contained iterator with the correct type for
   * injection.
   *
   * @throws std::runtime_error when called more than once to prevent transferring ownership more
   * than once.
   *
   * @note This method also records whether the instance was retrieved to correctly remove it
   * during destruction if needed.
   */
  InjectionType<Dep> Get();
private:
  using iterator = InstanceMap<Key>::iterator;
  InstanceMap<Key>& m_instance_map;
  iterator m_it;
  bool m_retrieved;
};

template <typename Key, typename Dep>
DependencyRetriever<Key, Dep>::DependencyRetriever(InstanceMap<Key>& instance_map, const Key& key)
  : m_instance_map{instance_map}
  , m_it{m_instance_map.find(key)}
  , m_retrieved{false}
{
  if (m_it == m_instance_map.end())
  {
    throw std::runtime_error("DependencyRetriever constructor: trying to access unknown instance");
  }
}

template <typename Key, typename Dep>
DependencyRetriever<Key, Dep>::~DependencyRetriever()
{
  if (TransferOwnership<Dep>::value && m_retrieved)
  {
    m_instance_map.erase(m_it);
  }
}

template <typename Key, typename Dep>
InjectionType<Dep> DependencyRetriever<Key, Dep>::Get()
{
  if (m_retrieved)
  {
    throw std::runtime_error("DependencyRetriever::Get(): trying to access instance more than once");
  }
  m_retrieved = true;
  return ValuePointerToInjectionType<Dep>::Forward(GetValuePointer<Dep>(*m_it->second));
}

template <typename Key>
template <std::size_t I, typename... Deps>
InjectionType<NthType<TypeList<Deps...>, I>>
ServiceStore<Key>::GetInstance(const std::vector<Key>& key_list)
{
  return GetInstanceImpl<NthType<TypeList<Deps...>, I>>(key_list[I]);
}

template <typename Key>
template <typename Service>
bool ServiceStore<Key>::StoreInstance(std::unique_ptr<Service> instance, const Key& key)
{
 auto& instance_map = GetInstanceMap<Service>();
 if (instance_map.find(key) != instance_map.end())
 {
  return false;
 }
 instance_map[key] = WrapIntoContainer(std::move(instance));
 return true;
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
  DependencyRetriever<Key, Dep> dependency_retriever(map_it->second, key);
  return dependency_retriever.Get();
}

template <typename Key>
template <typename Service>
InstanceMap<Key>& ServiceStore<Key>::GetInstanceMap()
{
  auto it = m_typed_instance_map.find<Service>();
  if (it == m_typed_instance_map.end())
  {
    m_typed_instance_map.put<T>(InstanceMap<Key>{});
    it = m_typed_instance_map.find<T>();
  }
  return it->second;
}

}  // namespace internal

}  // namespace di

}  // namespace sup

#endif  // SUP_DI_SERVICE_STORE_H_
