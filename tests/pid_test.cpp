#include "pid.hpp"
#include <gtest/gtest.h>

TEST(pid_test, proportional_test) {
  prep::Gains gains{100,0,0,10,-10};
  prep::MotorController controller{.delta_t=1.0,.control_action_max=48,.control_action_min=-48};
  auto control_action = controller.computeControlAction(0, 1.0, gains);
  EXPECT_FLOAT_EQ(control_action,-48);
}