
/*

    Plutonium library

    @file ui_Types.hpp
    @brief Several basic types helpful for UI and rendering
    @author XorTroll

    @copyright Plutonium project - an easy-to-use UI framework for Nintendo Switch homebrew

*/

#pragma once
#include <pu/pu_Include.hpp>

namespace pu::ui {

    // Font sizes Plutonium components use by default

    enum class DefaultFontSize : u32 {
        Small,
        Medium,
        MediumLarge,
        Large,

        Count
    };
    
    constexpr u32 DefaultFontSizes[static_cast<u32>(DefaultFontSize::Count)] = { 27, 30, 37, 45 };

    inline std::string MakeDefaultFontName(const u32 font_size) {
        return "DefaultFont@" + std::to_string(font_size);
    }

    inline constexpr u32 GetDefaultFontSize(const DefaultFontSize kind) {
        return DefaultFontSizes[static_cast<u32>(kind)];
    }

    inline std::string GetDefaultFont(const DefaultFontSize kind) {
        return MakeDefaultFontName(GetDefaultFontSize(kind));
    }

    struct Color {
        u8 r;
        u8 g;
        u8 b;
        u8 a;

        constexpr Color() : r(0), g(0), b(0), a(0xFF) {}
        constexpr Color(const u8 r, const u8 g, const u8 b, const u8 a) : r(r), g(g), b(b), a(a) {}

        // Expected format: '#rrggbbaa'
        static Color FromHex(const std::string &str_clr);

        inline Color WithAlpha(const u8 a) {
            return { this->r, this->g, this->b, a };
        }
    };

    static inline constexpr bool TouchHitsRegion(const i32 touch_x, const i32 touch_y, const i32 region_x, const i32 region_y, const i32 region_w, const i32 region_h) {
        return (touch_x >= region_x) && (touch_x < (region_x + region_w)) && (touch_y >= region_y) && (touch_y < (region_y + region_h));
    }

    constexpr u64 TouchPseudoKey = 1 << 29;

    struct TouchPoint {
        i32 x;
        i32 y;

        constexpr TouchPoint() : x(-1), y(-1) {}
        constexpr TouchPoint(const u32 x, const u32 y) : x(x), y(y) {}

        inline constexpr bool IsEmpty() const {
            return (this->x < 0) && (this->y < 0);
        }

        inline constexpr bool HitsRegion(const i32 region_x, const i32 region_y, const i32 region_w, const i32 region_h) const {
            if(this->IsEmpty()) {
                return false;
            }
            
            return TouchHitsRegion(this->x, this->y, region_x, region_y, region_w, region_h);
        }
    };

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
            static constexpr double AllowedError = 0.4f;

            constexpr SigmoidIncrementer() : f(0.0f), f_incr(0.0f), target_initial_val(0), target_incr(0) {}

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

            inline void StartFromZero(const u32 f_steps, const T target_final_val) {
                this->Start(f_steps, 0, target_final_val);
            }
            
            inline void StartToZero(const u32 f_steps, const T target_initial_val) {
                this->Start(f_steps, target_initial_val, -target_initial_val);
            }

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

            inline bool IsDone() {
                return this->target_incr == 0;
            }
    };

}
