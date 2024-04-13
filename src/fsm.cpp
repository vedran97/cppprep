#include "fsm/fsm.hpp"
#include "fsm/fsm_types.hpp"
#include <iostream>
#include <memory>
#include <mutex>

namespace prep {
static const constexpr transition_table_t_ transition_table = initTransitionTable();
static const constexpr function_table_t_ function_table = initFunctionTable();

FSM::FSM() {
  app_context = std::make_shared<AppContext>();
  this->prev_state = eStates::INIT;
  this->current_state = eStates::INIT;
}

bool FSM::processFSM() {
  std::unique_lock<std::mutex> lock(this->queue_mutex);
  if (!event_queue.empty()) {
    auto current_event = event_queue.front();
    event_queue.pop();
    lock.unlock();
    auto next_requested_state =
        transition_table.at(GET_ENUM_VAL(eStates, current_state))
            .at(GET_ENUM_VAL(eEvents, current_event));
    if (next_requested_state != eStates::SENTINEL) {
      auto on_exit = function_table.at(GET_ENUM_VAL(eStates, current_state));
      if (on_exit.onExit != nullptr) {
        auto on_exit_result = on_exit.onExit(this->app_context);
        if (on_exit_result) {
          auto on_entry =
              function_table.at(GET_ENUM_VAL(eStates, next_requested_state));
          if (on_entry.onEntry != nullptr) {
            auto on_entry_result = on_entry.onEntry(this->app_context);
            if (on_entry_result) {
              this->prev_state = current_state;
              this->current_state = next_requested_state;
            } else {
              std::cout << "onEntry to state "
                        << GET_ENUM_VAL(eStates, next_requested_state)
                        << " from state "
                        << GET_ENUM_VAL(eStates, current_state) << " failed"
                        << std::endl;
            }
          } else {
            throw(std::runtime_error("onEntry function undefined"));
          }
        } else {
          std::cout << "onExit from state "
                    << GET_ENUM_VAL(eStates, current_state) << " to state "
                    << GET_ENUM_VAL(eStates, next_requested_state) << " failed"
                    << std::endl;
        }
      } else {
        throw(std::runtime_error("onExit function undefined"));
      }
    }
  }
  if (lock.owns_lock())
    lock.unlock();
  auto on_process = function_table.at(GET_ENUM_VAL(eStates, current_state));
  if (on_process.onProcess != nullptr) {
    on_process.onProcess(this->app_context);
  } else {
    throw(std::runtime_error("onProcess function undefined"));
  }
  return true;
}

void FSM::addEvent(const eEvents event) {
  std::unique_lock<std::mutex> lock(this->queue_mutex);
  return event_queue.push(event);
}

} // namespace prep