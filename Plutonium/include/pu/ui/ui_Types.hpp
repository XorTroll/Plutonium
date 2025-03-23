/**
 * Plutonium library
 * @file ui_Types.hpp
 * @brief Main UI types header.
 * @author XorTroll
 * @copyright XorTroll
 */

#pragma once
#include <pu/pu_Include.hpp>

namespace pu::ui {

    /**
     * @brief Enum containing the default font sizes used by Plutonium components.
     */
    enum class DefaultFontSize : u32 {
        Small,
        Medium,
        MediumLarge,
        Large,

        Count
    };
    
    /**
     * @brief Array containing the default font size values used by Plutonium components, for all DefaultFontSize values.
     */
    constexpr u32 DefaultFontSizes[static_cast<u32>(DefaultFontSize::Count)] = { 27, 30, 37, 45 };

    /**
     * @brief Makes a default font name with the specified font size.
     * @param font_size Font size to use.
     * @return Default font name.
     */
    inline std::string MakeDefaultFontName(const u32 font_size) {
        return "DefaultFont@" + std::to_string(font_size);
    }

    /**
     * @brief Gets the default font size value for the specified DefaultFontSize.
     * @param kind DefaultFontSize to get the value from.
     * @return Default font size value.
     */
    inline constexpr u32 GetDefaultFontSize(const DefaultFontSize kind) {
        return DefaultFontSizes[static_cast<u32>(kind)];
    }

    /**
     * @brief Gets the default font name for the specified DefaultFontSize.
     * @param kind DefaultFontSize to get the font name from.
     * @return Default font name.
     */
    inline std::string GetDefaultFont(const DefaultFontSize kind) {
        return MakeDefaultFontName(GetDefaultFontSize(kind));
    }

    /**
     * @brief Type encoding a RGBA-8888 color.
     */
    struct Color {
        u8 r;
        u8 g;
        u8 b;
        u8 a;

        /**
         * @brief Creates a new Color with all values set to 0 (black color by default).
         */
        constexpr Color() : r(0), g(0), b(0), a(0xFF) {}

        /**
         * @brief Creates a new Color with the specified values.
         * @param r Red value.
         * @param g Green value.
         * @param b Blue value.
         * @param a Alpha value.
         */
        constexpr Color(const u8 r, const u8 g, const u8 b, const u8 a) : r(r), g(g), b(b), a(a) {}

        /**
         * @brief Creates a new Color from a hexadecimal string ("#rrggbbaa" format).
         * @param str_clr Hexadecimal string to create the Color from.
         * @return Created Color.
         */
        static Color FromHex(const std::string &str_clr);

        /**
         * @brief Creates a new Color with this Color's RGB values and the specified alpha value.
         * @param a Alpha value to set.
         * @return Created Color.
         */
        inline Color WithAlpha(const u8 a) {
            return { this->r, this->g, this->b, a };
        }
    };

    /**
     * @brief Helper function to check whether a touch point hits a rectangle region.
     * @param touch_x X coordinate of the touch point.
     * @param touch_y Y coordinate of the touch point.
     * @param region_x X coordinate of the region.
     * @param region_y Y coordinate of the region.
     * @param region_w Width of the region.
     * @param region_h Height of the region.
     * @return Whether the touch point hits the region.
     */
    static inline constexpr bool TouchHitsRegion(const i32 touch_x, const i32 touch_y, const i32 region_x, const i32 region_y, const i32 region_w, const i32 region_h) {
        return (touch_x >= region_x) && (touch_x < (region_x + region_w)) && (touch_y >= region_y) && (touch_y < (region_y + region_h));
    }

    /**
     * @brief Input key value used internally by Plutonium to represent the presence of a touch input.
     */
    constexpr u64 TouchPseudoKey = 1 << 29;

    /**
     * @brief Type encoding a touch point.
     */
    struct TouchPoint {
        i32 x;
        i32 y;

        /**
         * @brief Creates a new, invalid TouchPoint (with both coordinates set to -1).
         */
        constexpr TouchPoint() : x(-1), y(-1) {}

        /**
         * @brief Creates a new TouchPoint with the specified coordinates.
         * @param x X coordinate.
         * @param y Y coordinate.
         */
        constexpr TouchPoint(const u32 x, const u32 y) : x(x), y(y) {}

        /**
         * @brief Checks whether this TouchPoint is not valid (both coordinates are less than 0).
         * @return Whether this TouchPoint is invalid/empty.
         */
        inline constexpr bool IsEmpty() const {
            return (this->x < 0) && (this->y < 0);
        }

        /**
         * @brief Checks whether this TouchPoint hits a rectangle region.
         * @param region_x X coordinate of the region.
         * @param region_y Y coordinate of the region.
         * @param region_w Width of the region.
         * @param region_h Height of the region.
         * @return Whether this TouchPoint hits the region.
         */
        inline constexpr bool HitsRegion(const i32 region_x, const i32 region_y, const i32 region_w, const i32 region_h) const {
            if(this->IsEmpty()) {
                return false;
            }
            
            return TouchHitsRegion(this->x, this->y, region_x, region_y, region_w, region_h);
        }
    };

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
                    target = (T)((i32)(target_f + 0.5f));
                }
                else {
                    target = (T)((i32)(target_f - 0.5f));
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
