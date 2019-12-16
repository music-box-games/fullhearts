#ifndef _WE_DELEGATE_HPP_
#define _WE_DELEGATE_HPP_

#include <string_view>

#define EVENT_NAME(x) static constexpr std::string_view NAME = #x

namespace waifuengine
{
  class delegate_base
  {
  protected:
    void * inst_;

  public:
    delegate_base() : inst_(nullptr) {}
    ~delegate_base() {}
    virtual void invoke() {}
  };

  template<typename Class>
  class delegate
  {
  private:

  public:
    delegate() {}
    virtual ~delegate() override {}

    virtual void invoke()
    {

    }

    void bind()
    {

    }
  };
}

#endif // !_WE_DELEGATE_HPP_