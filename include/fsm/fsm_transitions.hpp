#ifndef PREP_FSM_TRANSITIONS_HPP
#define PREP_FSM_TRANSITIONS_HPP

#include "fsm_types.hpp"
namespace prep{
#define STATE_TRANSITION(FROM_STATE, EVENT, NEXT_STATE)                        \
  local_table_.at(GET_ENUM_VAL(eStates, FROM_STATE))                           \
      .at(GET_ENUM_VAL(eEvents, EVENT)) = NEXT_STATE;

;

inline consteval transition_table_t_ initTransitionTable() {
  transition_table_t_ local_table_;
  for (auto &row : local_table_) {
    for (auto &col_element : row) {
      col_element = eStates::SENTINEL;
    }
  }

  // Functional state transitions
  STATE_TRANSITION(eStates::INIT, eEvents::INIT_COMPLETE, eStates::PREOP)
  STATE_TRANSITION(eStates::PREOP, eEvents::PREOP_COMPLETE, eStates::READY)
  STATE_TRANSITION(eStates::READY, eEvents::START_DOING, eStates::DO)
  STATE_TRANSITION(eStates::DO, eEvents::END_DOING, eStates::READY)
  // Transition to error
  STATE_TRANSITION(eStates::INIT, eEvents::ERROR, eStates::ERROR)
  STATE_TRANSITION(eStates::PREOP, eEvents::ERROR, eStates::ERROR)
  STATE_TRANSITION(eStates::DO, eEvents::ERROR, eStates::ERROR)
  STATE_TRANSITION(eStates::READY, eEvents::ERROR, eStates::ERROR)
  // Error to PRE_OP
  STATE_TRANSITION(eStates::ERROR, eEvents::RESET_ERROR, eStates::PREOP)

  return local_table_;
}
}

#endif