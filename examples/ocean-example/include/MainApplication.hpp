
#pragma once
#include <pu/Plutonium>
#include <pu/Ocean>

class CustomLayout : public pu::ui::Layout {
    private:
        pu::ui::Group::Ref top_subgroup;
        pu::ui::elm::TextBlock::Ref title_text;

        pu::ui::Group::Ref bottom_subgroup;
        std::vector<pu::ui::elm::Button::Ref> input_buttons;

        pu::ui::Group::Ref left_subgroup;
        std::vector<pu::ui::elm::Button::Ref> guide_buttons;
        u32 selected_guide_button;
        
        /////

        pu::ui::Group::Ref right_subgroup;

        pu::ui::elm::TextBlock::Ref cnt0_text;
        pu::ui::elm::ProgressBar::Ref cnt0_progress_bar;
        std::vector<pu::ui::elm::Button::Ref> cnt0_buttons;

        std::vector<pu::ui::elm::Button::Ref> cnt1_buttons;

        /////

        void UpdateGuideButtonColors();
        void ReloadContent();

    public:
        CustomLayout();
        PU_SMART_CTOR(CustomLayout)
};

class MainApplication : public pu::ui::Application {
    private:
        CustomLayout::Ref layout;
    
    public:
        using Application::Application;
        PU_SMART_CTOR(MainApplication)

        void OnLoad() override;
};
