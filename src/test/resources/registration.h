#include <memory>
#include <string>

class IService
{
public:
  virtual ~IService() = default;
};

class Client
{
public:
  Client(const std::string& name, std::unique_ptr<IService>&& service);
  ~Client() = default;

  void Launch();
};

class Service : public IService
{
public:
  Service();
  ~Service() = default;
};
