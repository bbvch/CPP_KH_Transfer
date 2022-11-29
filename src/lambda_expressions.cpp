// SPDX-License-Identifier: GPL-3.0

// This header demonstrates the usage of lambda expressions.

#include <algorithm>
#include <functional>
#include <iostream>
#include <iterator>
#include <memory>
#include <string>
#include <variant>
#include <vector>


template <typename T>
struct pseudo_future
{
  pseudo_future(const T& t) : v(t) { }
  pseudo_future(T&& t) : v(std::forward<T>(t)) { }
  const T& get() const { return v; }
  template <typename F> void then(F&& f) { std::invoke(std::forward<F>(f), *this); }
  T v;
};


class some_service
{
public:
  pseudo_future<int> get_num_pending_orders()
  {
    // Do RPC stuff
    return 7;
  }

  void show_num_pending_orders(int num_orders)
  {
    std::cout << "There are " << num_orders << " pending orders.\n";
  }
};


template <typename Sequence>
void print_sequence(std::ostream& o, const Sequence& sequence)
{
  // Capture by reference
  using std::begin;
  using std::end;
  std::for_each(begin(sequence), end(sequence),
                [&o] (const auto& v)
                {
                  o << v;
                });
}


int main()
{
  const auto print_int = [] (int i) -> void { std::cout << "I have been called with " << i << ".\n"; };
  //                     ^  ^       ^       ^
  //           captures /   |       |        \ Lambda body
  //                        |       |
  //  parameters (optional) /       \ return type (optional)

  print_int(9);

  const auto int_sequence =  {1, 2, 3, 4, 5};
  std::for_each(int_sequence.begin(), int_sequence.end(), print_int);


  // Capture by value
  int threshold = 4;

  std::for_each(int_sequence.begin(), int_sequence.end(),
                [threshold] (int i)
                {
                  if (i >= threshold) std::cout << i;
                });

  std::cout << "\n";


  // Capture by reference (see print_sequence)
  print_sequence(std::cout, int_sequence);
  std::cout << "\n";


  // Init capture
  const auto service = std::make_shared<some_service>();

  service->get_num_pending_orders()
    .then([guard = std::weak_ptr{service}] (auto&& future)
    {
      if (const auto service = guard.lock())
      {
          service->show_num_pending_orders(future.get());
      }
    });


  // Generic lambdas
  const auto print_to_cout = [] (auto&& val) { std::cout << val << "\n"; };
  std::vector<std::variant<int, std::string>> items = {"this is a string", 2, 0, "this is not a number"};
  const auto print_item_to_cout = [&print_to_cout] (auto&& variant) { std::visit(print_to_cout, variant); };

  std::for_each(items.begin(), items.end(), print_item_to_cout);


  return 0;
}
