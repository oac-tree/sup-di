#include "registration.h"

// Registered global and factory functions:

// Registered as creator with typename "Service"
std::unique_ptr<IService> CreateService()
{
  return std::unique_ptr<IService>(new Service());
}

// Registered as creator with typename "Client"
std::unique_ptr<Client> CreateClient(
  const std::string& name, std::unique_ptr<IService>&& service)
{
  return std::unique_ptr<Client>(new Client(name, std::move(service)));
}

// Registered as global function with function name "LaunchClient"
bool LaunchClient(Client* client)
{
  client->Launch();
  return true;
}