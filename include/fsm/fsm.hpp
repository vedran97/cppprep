#ifndef PREP_FSM_HPP
#define PREP_FSM_HPP
#include "fsm_types.hpp"



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

  std::shared_ptr<AppContext> app_context;
  prep::eStates current_state = prep::eStates::INIT;
  prep::eStates prev_state = prep::eStates::INIT;
  std::queue<eEvents> event_queue;
  std::mutex queue_mutex;
};
} // namespace prep
#endif