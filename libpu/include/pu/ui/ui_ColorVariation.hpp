/**
* Plutonium library
* @file ui_ColorVariation.hpp
* @brief Contains pu::ui::ColorVariation class
* @author XorTroll
* @copyright XorTroll
*/

#pragma once
#include <pu/ui/ui_Types.hpp>
#include <pu/ui/ui_SigmoidIncrementer.hpp>
#include <pu/ui/ui_Style.hpp>

namespace pu::ui {

   /**
    * @brief Helper class to oscillate between two colors.
    */
    class ColorVariation final {
        private:
            enum class State {
                AToB,
                BToA
            };

            Color clr_a;
            Color clr_b;
            s32 cur_param;
            u32 speed_steps;
            SigmoidIncrementer<s32> incrementer;
            State state;
            Color cur_clr;

        public:
            /**
            * @brief Creates a new instance of a ColorVariation object.
            * @param clr_a Color A.
            * @param clr_b Color B.
            * @param speed_steps Number of steps to use for the color variation.
            */
            ColorVariation(const Color clr_a, const Color clr_b) : clr_a(clr_a), clr_b(clr_b), cur_param(0), speed_steps(GetStyle()->GetColorVariateSpeedSteps()), incrementer(), state(State::AToB), cur_clr(clr_a) {
                this->Reset();
            }

            /**
            * @brief Resets the color variation to its initial state.
            * @note This will set the current color to Color A, and restart the oscillation.
            */
            void Reset();

            /**
            * @brief Updates the color variation.
            * @note Computes the next oscillation step. This should be called every frame to update the color.
            */
            void Update();

            PU_CLASS_POD_GETSET(ColorA, clr_a, Color)
            PU_CLASS_POD_GETSET(ColorB, clr_b, Color)
            PU_CLASS_POD_GETSET(SpeedSteps, speed_steps, u32)

            /**
            * @brief Gets the current color.
            * @return The current color.
            */
            inline Color Get() {
                return this->cur_clr;
            }
    };

}
