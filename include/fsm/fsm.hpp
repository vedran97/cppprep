#ifndef PREP_FSM_HPP
#define PREP_FSM_HPP
#include "fsm_types.hpp"

#include "fsm_statefunctions.hpp"
#include "fsm_transitions.hpp"

#include <memory>
#include <mutex>
#include <queue>
namespace prep {

class FSM {
public:
  explicit FSM();
  [[nodiscard("Check if this was successful")]] bool processFSM();
  void addEvent(const eEvents event);
  auto getCurrentState() { return this->current_state; }
  auto getPrevState() { return this->prev_state; }
  auto getAppContext() { return *this->app_context; }

private:
  static const constexpr transition_table_t_ transition_table =
      initTransitionTable();
  static const constexpr function_table_t_ function_table = initFunctionTable();
  std::shared_ptr<AppContext> app_context;
  prep::eStates current_state = prep::eStates::INIT;
  prep::eStates prev_state = prep::eStates::INIT;
  std::queue<eEvents> event_queue;
  std::mutex queue_mutex;
};
} // namespace prep
#endif