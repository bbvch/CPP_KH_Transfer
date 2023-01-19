#include <algorithm>
#include <iostream>
#include <iterator>
#include <ranges>
#include <string>
#include <tuple>
#include <type_traits>
#include <utility>


template <typename T>
concept tuple_type = requires (const T& t)
{
   std::tuple_size<std::remove_cvref_t<T>>::value;
};


template <typename T>
concept string_like = std::is_convertible_v<T&&, std::string_view>;


template <typename sink_t,
          typename non_string_range>
  requires std::ranges::range<non_string_range> && (!string_like<non_string_range>)
constexpr sink_t& print(sink_t& out, const non_string_range& range);

template <typename sink_t,
         tuple_type tuple_t>
constexpr sink_t& print(sink_t& out, const tuple_t& t);

template <typename sink_t>
constexpr sink_t& print(sink_t& out, const auto& value);

template <typename sink_t>
constexpr sink_t& print(sink_t& out,
                        const auto& first,
                        const auto& second,
                        const auto&... rest);

template <typename sink_t>
constexpr sink_t& print(sink_t& out, string_like auto const & string);


template <typename sink_t,
          typename non_string_range>
  requires std::ranges::range<non_string_range> && (!string_like<non_string_range>)
constexpr sink_t& print(sink_t& out, const non_string_range& range)
{
   out << "[";

   if (std::size(range))
   {
      for (auto it = std::ranges::begin(range),
            end = std::prev(std::ranges::end(range));
            it != end;
            ++it)
      {
         print(out, *it);
         out << ", ";
      }

      print(out, *(std::prev(std::ranges::end(range))));
   }

   out << "]";
   return out;
}


template <typename sink_t,
            tuple_type tuple_t>
constexpr sink_t& print(sink_t& out, const tuple_t& tuple)
{
   const auto fnPrint = [&out] (const auto&... values)
   {
      print(out, values...);
   };

   out << "(";
   std::apply(fnPrint, tuple);
   out << ")";

   return out;
}


template <typename sink_t>
constexpr sink_t& print(sink_t& out, const auto& value)
{
   return out << value;
}


template <typename sink_t>
constexpr sink_t& print(sink_t& out,
                        const auto& first,
                        const auto& second,
                        const auto&... rest)
{
   const auto fn_print_with_leading_comma = [&out] (const auto& value)
   {
      out << ", ";
      print(out, value);
   };

   print(out, first) << ", ";
   print(out, second);
   (fn_print_with_leading_comma(rest), ...);

   return out;
}


template <typename sink_t>
constexpr sink_t& print(sink_t& out, string_like auto const & string)
{
   std::string_view sv{string};
   out << "\"" << sv << "\"";
   return out;
}


template <typename sink_t,
            typename value_t>
constexpr void println(sink_t& out, const value_t& value)
{
   print(out, value) << "\n";
}


#include <set>
#include <vector>
#include <map>
#include <utility>


using namespace std::literals;


int main()
{
   println(std::cout, 7);

   const std::vector v = {1, 6, 3, 1, 332, 25};
   println(std::cout, v);

   println(std::cout, "hallo");
   println(std::cout, "hallo"s);
   println(std::cout, "hallo"sv);

   println(std::cout, std::vector{'h', 'a', 'l', 'l', 'o'});

   const std::set s = {1, 6, 3, 1, 332, 25};
   println(std::cout, s);

   println(std::cout, std::vector<int>{});

   println(std::cout, std::map<int, std::string_view>{{1, "1"}, {5, "5"}, {3, "3"}});

   println(std::cout, std::make_tuple(1, "hallo", 9));

   const int c_arr[] = {76, 2, 93, 0, 0};
   println(std::cout, c_arr);

   return 0;
}
