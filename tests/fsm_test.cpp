#include "fsm/fsm.hpp"
#include <gtest/gtest.h>
#include <iostream>
TEST(FSM,TRANSITIONS){
    auto fsm=prep::FSM();
    auto prev_state=fsm.getPrevState();
    auto curr_state=fsm.getCurrentState();
    ASSERT_EQ(prev_state, prep::eStates::INIT);
    ASSERT_EQ(prev_state, curr_state);
    fsm.addEvent(prep::eEvents::INIT_COMPLETE);
    [[maybe_unused]]auto process_fsm_result = fsm.processFSM();
    ASSERT_EQ(fsm.getPrevState(),prep::eStates::INIT);
    ASSERT_EQ(fsm.getCurrentState(),prep::eStates::PREOP);
    fsm.addEvent(prep::eEvents::PREOP_COMPLETE);
    process_fsm_result=fsm.processFSM();
    ASSERT_EQ(fsm.getPrevState(),prep::eStates::PREOP);
    ASSERT_EQ(fsm.getCurrentState(),prep::eStates::READY);
    fsm.addEvent(prep::eEvents::START_DOING);
    process_fsm_result=fsm.processFSM();
    ASSERT_EQ(fsm.getPrevState(),prep::eStates::READY);
    ASSERT_EQ(fsm.getCurrentState(),prep::eStates::DO);
    process_fsm_result=fsm.processFSM();
    auto app_context=fsm.getAppContext();
    ASSERT_EQ(app_context.current_position, std::string("doOnProcess_custom\r\n"));
    process_fsm_result=fsm.processFSM();
    process_fsm_result=fsm.processFSM();
    fsm.addEvent(prep::eEvents::END_DOING);
    process_fsm_result=fsm.processFSM();
    ASSERT_EQ(fsm.getPrevState(),prep::eStates::DO);
    ASSERT_EQ(fsm.getCurrentState(),prep::eStates::READY);
}