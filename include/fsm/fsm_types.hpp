#ifndef PREP_FSM_TYPES_HPP
#define PREP_FSM_TYPES_HPP
#include <array>
#include <cstddef>
#include <memory>
#include <string>
#include <type_traits>
namespace prep {

template <typename T> inline constexpr auto getEnumVal(const T &val) {
  return static_cast<std::underlying_type_t<T>>(val);
}

enum class eStates : std::size_t { INIT, PREOP, READY, DO, ERROR, SENTINEL };
enum class eEvents : std::size_t {
  INIT_COMPLETE,
  PREOP_COMPLETE,
  RESET_ERROR,
  START_DOING,
  END_DOING,
  ERROR,
  SENTINEL
};
struct AppContext {
  std::string current_position = "";
};

struct StateFunctions {
  bool (*onEntry)(const std::shared_ptr<AppContext>) = nullptr;
  bool (*onExit)(const std::shared_ptr<AppContext>) = nullptr;
  void (*onProcess)(const std::shared_ptr<AppContext>) = nullptr;
};

using transition_table_t_ =
    std::array<std::array<eStates, getEnumVal(eEvents::SENTINEL)>,
               getEnumVal(eStates::SENTINEL)>;

using function_table_t_ =
    std::array<StateFunctions, getEnumVal(eStates::SENTINEL)>;
} // namespace prep
#endif