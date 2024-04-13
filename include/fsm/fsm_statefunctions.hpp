#ifndef PREP_FSM_STATE_FUNCTIONS_HPP
#define PREP_FSM_STATE_FUNCTIONS_HPP
#include "fsm_types.hpp"
#include <iostream>
namespace prep{
inline bool emptyOnExit(const std::shared_ptr<AppContext> app_context) {
  std::cout << "Inside " << __FUNCTION__ << std::endl;
  return true;
}
inline bool emptyOnEntry(const std::shared_ptr<AppContext> app_context) {
  std::cout << "Inside " << __FUNCTION__ << std::endl;
  return true;
}
inline void emptyOnProcess(const std::shared_ptr<AppContext> app_context) {
  app_context->current_position = __FUNCTION__;
}

inline void doOnProcess(const std::shared_ptr<AppContext> app_context) {
  app_context->current_position = __FUNCTION__;
  app_context->current_position += "_custom\r\n";
  std::cout << app_context->current_position;
}

inline consteval function_table_t_ initFunctionTable() {
  function_table_t_ function_table_;
  for (auto &state_function : function_table_) {
    state_function.onEntry = emptyOnEntry;
    state_function.onExit = emptyOnExit;
    state_function.onProcess = emptyOnProcess;
  }
  function_table_.at(GET_ENUM_VAL(eStates::DO)).onProcess =
      doOnProcess;
  return function_table_;
}
}
#endif