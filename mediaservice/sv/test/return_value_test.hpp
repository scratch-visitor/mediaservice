#include <iostream>

namespace sv
{
namespace test
{

template<class T>
struct value_holder
{
  using value_type = T;
};
template<class T>
struct value_holder<const T>
{
  using value_type = T;
};
template<class T>
struct value_holder<T&>
{
  using value_type = T;
};
template<>
struct value_holder<char*>
{
  using value_type = std::string;
};
template<size_t N>
struct value_holder<char[N]>
{
  using value_type = std::string;
};
template<>
struct value_holder<wchar_t*>
{
  using value_type = std::wstring;
};
template<size_t N>
struct value_holder<wchar_t[N]>
{
  using value_type = std::wstring;
};

template<class T>
struct return_value : public value_holder<T>
{
  using value_type = typename value_holder<T>::value_type;

  return_value()
    : m_value()
  {
  }
  return_value(T const& v)
    : m_value(v)
  {
  }
  value_type get() const
  {
    return m_value;
  }

private:
  value_type m_value;
};

template<class T>
return_value<typename value_holder<T>::value_type> assign(T const& v)
{
  return return_value<typename value_holder<T>::value_type>(v);
}

void test_argument(int const& v)
{
  auto value = assign(v);
  std::cout << value.get() << std::endl;
}

struct sample
{
  int i;
  char c;
};

void test_userdefined(sample const& o)
{
  auto value = assign(o);

}

template<class T>
void test_template(T const& o)
{
  auto value = assign(o);
}

void test_return_value()
{
  auto integer = assign(100);
  auto floating = assign(10.17f);
  auto real = assign(22.17);
  auto character = assign('c');
  auto string = assign("hello");

  std::cout << integer.get() << std::endl;
  std::cout << floating.get() << std::endl;
  std::cout << real.get() << std::endl;
  std::cout << character.get() << std::endl;
  std::cout << string.get() << std::endl;

  test_template(sample{ 10, 'c' });
}

} // namespace sv::test
} // namespace sv