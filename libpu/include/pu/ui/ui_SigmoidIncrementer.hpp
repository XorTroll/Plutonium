/**
 * Plutonium library
 * @file ui_SigmoidIncrementer.hpp
 * @brief Contains pu::ui::SigmoidIncrementer, a class used to vary a value from an initial value to a final one, following the shape of a sigmoid function.
 * @author XorTroll
 * @copyright XorTroll
 */

#pragma once
#include <pu/pu_Include.hpp>

namespace pu::ui {

    /**
     * @brief Type used to vary a value, from an initial value to a final one, following the shape of a sigmoid function.
     * @tparam T Type of the value to vary.
     */
    template<typename T>
    class SigmoidIncrementer {
        private:
            double f;
            double f_incr;
            T target_initial_val;
            T target_incr;
            bool inverted_for_zero;

            inline double ComputeIncrement() {
                return (double)this->target_incr * (1.0f / (1.0f + exp(-this->f)));
            }

        public:
            /**
             * @brief Allowed error for the initial/final point reach precision.
             */
            static constexpr double AllowedError = 0.4f;

            /**
             * @brief Creates a new SigmoidIncrementer with all values reset.
             */
            constexpr SigmoidIncrementer() : f(0.0f), f_incr(0.0f), target_initial_val(0), target_incr(0) {}

            /**
             * @brief Starts the incrementation process from an initial value to a final one, with a specified number of steps.
             * @param f_steps Number of steps to reach the final value.
             * @param target_initial_val Initial value.
             * @param target_incr Final increment from the initial value (final value - initial value).
             */
            void Start(const u32 f_steps, const T target_initial_val, const T target_incr) {
                this->target_initial_val = target_initial_val;
                this->target_incr = target_incr;
                this->inverted_for_zero = false;

                auto target_final_val = target_initial_val + target_incr;
                if(target_final_val == 0) {
                    // Compute from 0 to X instead of from X to 0
                    this->inverted_for_zero = true;
                    this->target_initial_val = 0;
                    this->target_incr = target_initial_val;
                    target_final_val = target_initial_val;
                }

                const auto f_limit_abs = log((abs((double)target_final_val) - AllowedError) / AllowedError);
                this->f_incr = (2.0f * f_limit_abs) / (double)f_steps;
                this->f = -f_limit_abs;
            }

            /**
             * @brief Starts the incrementation process from 0 to a final value, with a specified number of steps.
             * @param f_steps Number of steps to reach the final value.
             * @param target_final_val Final value.
             */
            inline void StartFromZero(const u32 f_steps, const T target_final_val) {
                this->Start(f_steps, 0, target_final_val);
            }
            
            /**
             * @brief Starts the incrementation process from an initial value to 0, with a specified number of steps.
             * @param f_steps Number of steps to reach the final value.
             * @param target_initial_val Initial value.
             */
            inline void StartToZero(const u32 f_steps, const T target_initial_val) {
                this->Start(f_steps, target_initial_val, -target_initial_val);
            }

            /**
             * @brief Increments the target value (performs a step in the incrementation process).
             * @param target Output variable where the current value will be stored.
             * @note If the incrementation process has already finished, this will do nothing and return false.
             * @return Whether the target value has reached the final value.
             */
            bool Increment(T &target) {
                if(this->IsDone()) {
                    return false;
                }

                const auto target_f = (double)this->target_initial_val + this->ComputeIncrement();
                if(this->target_incr > 0) {
                    target = (T)((s32)(target_f + 0.5f));
                }
                else {
                    target = (T)((s32)(target_f - 0.5f));
                }
                this->f += this->f_incr;

                const auto is_done = abs((double)target) >= abs((double)(this->target_initial_val + this->target_incr));
                if(is_done) {
                    if(this->inverted_for_zero) {
                        target = 0;
                    }
                    else {
                        target = this->target_initial_val + this->target_incr;
                    }
                    this->target_incr = 0;
                    return true;
                }
                else if(this->inverted_for_zero) {
                    target = this->target_incr - target;
                }
                
                return false;
            }

            /**
             * @brief Checks whether the incrementation process has finished.
             * @return Whether the incrementation process has finished.
             */
            inline bool IsDone() {
                return this->target_incr == 0;
            }
    };

}
