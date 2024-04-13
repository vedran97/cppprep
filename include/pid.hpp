#ifndef PID_HPP
#define PID_HPP
#include <algorithm>
#include <assert.h>
namespace prep {
struct Gains {
  float k_p{0};
  float k_i{0};
  float k_d{0};
  float i_sat_max{0};
  float i_sat_min{0};
};
struct MotorController {
  float motor_error{0};
  float motor_error_prev{0};
  float motor_error_integral{0};
  float delta_t{1.0};
  float control_action_max{0};
  float control_action_min{0};
  float computeControlAction(const float current_state,
                             const float target_state, const Gains &gains,
                             const float feedforwards = 0) noexcept {
    assert(delta_t != 0);
    assert(gains.i_sat_max >= gains.i_sat_min);
    assert(control_action_max >= control_action_min);
    auto motor_error = current_state - target_state;
    this->motor_error_integral += motor_error * delta_t;
    auto proportional_action = motor_error * (gains.k_p);
    auto integral_action = this->motor_error_integral * gains.k_i;
    auto derivative_action = (motor_error - this->motor_error_prev) / delta_t;
    auto saturated_integral =
        std::clamp(integral_action, gains.i_sat_min, gains.i_sat_max);
    auto control_action = proportional_action + saturated_integral +
                          derivative_action + feedforwards;
    return std::clamp(control_action, control_action_min, control_action_max);
  }
};

} // namespace prep
#endif