#include <pu/ui/ui_ColorVariation.hpp>

namespace pu::ui {

    namespace {

        inline u8 Interpolate(const u8 a, const u8 b, const float t) {
            return (u8)((float)a + ((float)b - (float)a) * t);
        }

    }

    void ColorVariation::Reset() {
        this->state = State::AToB;
        this->incrementer.StartFromZero(this->speed_steps, this->speed_steps);
        this->cur_param = 0;
    }

    void ColorVariation::Update() {
        const auto done = this->incrementer.Increment(this->cur_param);

        const auto p = (float)this->cur_param / (float)this->speed_steps;
        this->cur_clr = {
            Interpolate(this->clr_a.r, this->clr_b.r, p),
            Interpolate(this->clr_a.g, this->clr_b.g, p),
            Interpolate(this->clr_a.b, this->clr_b.b, p),
            Interpolate(this->clr_a.a, this->clr_b.a, p)
        };

        if(done) {
            switch(this->state) {
                case State::AToB:
                    this->state = State::BToA;
                    this->incrementer.StartToZero(this->speed_steps, this->speed_steps);
                    this->cur_param = this->speed_steps;
                    break;
                case State::BToA:
                    this->state = State::AToB;
                    this->incrementer.StartFromZero(this->speed_steps, this->speed_steps);
                    this->cur_param = 0;
                    break;
            }
        }
    }

}
