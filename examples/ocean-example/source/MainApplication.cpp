#include <MainApplication.hpp>

extern MainApplication::Ref g_MainApplication;

#define R_ASSERT(expr) { \
    const auto rc = (expr); \
    if(R_FAILED(rc)) { \
        diagAbortWithResult(rc); \
    } \
}

void Exit() {
    pu::ocean::FinalizeResources();
    g_MainApplication->Close(true);
}

/*

TODO:
- memory leaks?
- move the group (auto extra swiping) when moving up/down with controller
- progress bars and scrolling
- animations

- (weird overlap between to buttons one over another in different groups)?

*/

void CustomLayout::UpdateGuideButtonColors() {
    for(u32 i = 0; i < this->guide_buttons.size(); i++) {
        auto button = this->guide_buttons[i];
        if(i == this->selected_guide_button) {
            button->GetText()->SetColor(pu::ocean::defs::GetSelectedGuideButtonTextColor(std::static_pointer_cast<pu::ocean::OceanStyle>(pu::ui::GetStyle())->GetAccent()));
        } else {
            button->GetText()->SetColor(pu::ui::GetStyle()->GetTextColor(pu::ocean::OceanStyleTextFlavor_UncoloredButtonContent));
        }
    }
}

void CustomLayout::ReloadContent() {
    this->right_subgroup->ClearElements();

    switch(this->selected_guide_button) {
        case 0: {
            this->right_subgroup->SetAutoRenderStrategy(pu::ui::AutoRenderStrategy::Vertical);
            this->right_subgroup->SetMarginLeft(112);
            this->right_subgroup->SetMarginRight(165);
            this->right_subgroup->SetMarginTop(78);
            this->right_subgroup->SetInterMargin(24);
            this->right_subgroup->SetBackgroundColor({ 0, 0, 0, 0 });

            this->cnt0_text = pu::ui::elm::TextBlock::New(0, pu::ui::PositionAuto, pu::ui::Text::New("This is some example contents", pu::ui::GetDefaultFont(pu::ui::DefaultFontSize::Large), pu::ocean::OceanStyleTextFlavor_Regular));
            this->cnt0_text->SetHorizontalAlign(pu::ui::HorizontalAlign::Center);
            this->right_subgroup->AddElement(this->cnt0_text);

            this->cnt0_progress_bar = pu::ui::elm::ProgressBar::New(pu::ui::PositionAuto, pu::ui::PositionAuto, pu::ui::DimensionMatchParent, 60, 1.0f);
            this->cnt0_progress_bar->SetProgress(0.6f);
            this->cnt0_progress_bar->SetMovable(true);
            this->right_subgroup->AddElement(this->cnt0_progress_bar);

            this->cnt0_progress_bar->SetLeftElement(this->guide_buttons.front());
            for(auto &guide_button: this->guide_buttons) {
                guide_button->SetRightElement(this->cnt0_progress_bar);
            }

            this->cnt0_text->SetDownElement(this->cnt0_progress_bar);
            this->cnt0_progress_bar->SetUpElement(this->cnt0_text);

            this->cnt0_buttons.clear();
            for(u32 i = 0; i < 20; i++) {
                auto cnt0_button_text_flavor = pu::ocean::OceanStyleTextFlavor_ColoredButtonContent;
                auto cnt0_button_flavor = pu::ocean::OceanStyleButtonFlavor_Colored;

                if((rand() % 2) == 0) {
                    cnt0_button_text_flavor = pu::ocean::OceanStyleTextFlavor_UncoloredButtonContent;
                    cnt0_button_flavor = pu::ocean::OceanStyleButtonFlavor_Uncolored;
                }
                if((rand() % 3) == 0) {
                    cnt0_button_text_flavor = pu::ocean::OceanStyleTextFlavor_UncoloredButtonContent;
                    cnt0_button_flavor = pu::ocean::OceanStyleButtonFlavor_UncoloredBordered;
                }

                auto cnt0_button_text = pu::ui::Text::New("Sample button " + std::to_string(i), pu::ui::GetDefaultFont(pu::ui::DefaultFontSize::MediumLarge), cnt0_button_text_flavor);
                auto cnt0_button = pu::ui::elm::Button::New(pu::ui::PositionAuto, pu::ui::PositionAuto, pu::ui::DimensionMatchParent, 105, cnt0_button_flavor, cnt0_button_text);

                if((i % 2) == 0) {
                    cnt0_button->SetTextPlacement(pu::ui::elm::Button::TextPlacement::Left);
                }
                if((i % 3) == 0) {
                    cnt0_button->SetTextPlacement(pu::ui::elm::Button::TextPlacement::Right);
                }

                cnt0_button->SetOnClick([i, this]() {
                    auto text = pu::ui::Text::New("Clicked sample button " + std::to_string(i) + "!", pu::ui::GetDefaultFont(pu::ui::DefaultFontSize::Large), pu::ocean::OceanStyleTextFlavor_Regular);
                    this->cnt0_text->SetText(text);
                    this->cnt0_progress_bar->SetProgress((float)i / 10.0f);
                });
                this->right_subgroup->AddElement(cnt0_button);

                if(i > 0) {
                    cnt0_button->SetUpElement(this->cnt0_buttons.back());
                    this->cnt0_buttons.back()->SetDownElement(cnt0_button);
                }
                this->cnt0_buttons.push_back(std::move(cnt0_button));
            }

            this->cnt0_progress_bar->SetDownElement(this->cnt0_buttons.front());
            this->cnt0_buttons.front()->SetUpElement(this->cnt0_progress_bar);
            break;
        }
        case 1: {
            this->right_subgroup->SetAutoRenderStrategy(pu::ui::AutoRenderStrategy::Horizontal);
            this->right_subgroup->SetMarginLeft(112);
            this->right_subgroup->SetMarginRight(165);
            this->right_subgroup->SetMarginTop(78);
            this->right_subgroup->SetInterMargin(24);
            this->right_subgroup->SetBackgroundColor({ 0, 0, 0, 0 });

            this->cnt1_buttons.clear();
            for(u32 i = 0; i < 20; i++) {
                auto cnt1_button_text = pu::ui::Text::New("\uE073", pu::ui::GetDefaultFont(pu::ui::DefaultFontSize::Large), pu::ocean::OceanStyleTextFlavor_ColoredButtonContent);
                auto cnt1_button = pu::ui::elm::Button::New(pu::ui::PositionAuto, pu::ui::PositionAuto, 384, 384, pu::ocean::OceanStyleButtonFlavor_Colored, std::move(cnt1_button_text));
                this->right_subgroup->AddElement(cnt1_button);

                if(i > 0) {
                    cnt1_button->SetLeftElement(this->cnt1_buttons.back());
                    this->cnt1_buttons.back()->SetRightElement(cnt1_button);
                }
                this->cnt1_buttons.push_back(std::move(cnt1_button));
            }

            this->cnt1_buttons.front()->SetLeftElement(this->guide_buttons.front());
            for(auto &guide_button: this->guide_buttons) {
                guide_button->SetRightElement(this->cnt1_buttons.front());
            }

            break;
        }
        default:
            break;
    }
}

CustomLayout::CustomLayout() : Layout::Layout() {
    this->top_subgroup = pu::ui::Group::New(0, 0, pu::ui::render::ScreenWidth, 132);
    this->top_subgroup->SetAutoRenderStrategy(pu::ui::AutoRenderStrategy::Horizontal);
    this->top_subgroup->SetMarginLeft(98);
    this->top_subgroup->SetMarginTop(48);
    this->top_subgroup->SetBottomBorderSeparator(true);
    this->top_subgroup->SetBackgroundColor({ 0, 0, 0, 0 });

    this->title_text = pu::ui::elm::TextBlock::New(pu::ui::PositionAuto, pu::ui::PositionAuto, pu::ui::Text::New("OceanStyle Demo", pu::ui::GetDefaultFont(pu::ui::DefaultFontSize::Large), pu::ocean::OceanStyleTextFlavor_Regular));
    this->top_subgroup->AddElement(this->title_text);

    this->AddSubgroup(this->top_subgroup);

    ///////////

    this->bottom_subgroup = pu::ui::Group::New(0, pu::ui::render::ScreenHeight - 110, pu::ui::render::ScreenWidth, 110);
    this->bottom_subgroup->SetAutoRenderStrategy(pu::ui::AutoRenderStrategy::Horizontal);
    this->bottom_subgroup->SetMarginLeft(90);
    this->bottom_subgroup->SetMarginRight(90);
    this->bottom_subgroup->SetMarginTop(9);
    this->bottom_subgroup->SetInterMargin(36);
    this->bottom_subgroup->SetTopBorderSeparator(true);
    this->top_subgroup->SetBackgroundColor({ 0, 0, 0, 0 });

    #define _ADD_INPUT_BUTTON(text, key, ...) { \
        auto input_button_text = pu::ui::Text::New(text, pu::ui::GetDefaultFont(pu::ui::DefaultFontSize::MediumLarge), pu::ocean::OceanStyleTextFlavor_UncoloredButtonContent); \
        auto input_button = pu::ui::elm::Button::New(pu::ui::PositionAuto, 0, 150, 75, pu::ocean::OceanStyleButtonFlavor_Uncolored, std::move(input_button_text)); \
        input_button->SetVerticalAlign(pu::ui::VerticalAlign::Center); \
        input_button->SetTouchKey(key); \
        input_button->SetOnClick([]() { \
            __VA_ARGS__ \
        }); \
        this->bottom_subgroup->AddElement(input_button); \
        if(!this->input_buttons.empty()) { \
            input_button->SetUpElement(this->input_buttons.back()); \
            this->input_buttons.back()->SetDownElement(input_button); \
        } \
        this->input_buttons.push_back(std::move(input_button)); \
    }

    _ADD_INPUT_BUTTON("\uE0EF Exit", HidNpadButton_Plus, {
        Exit();
    });
    _ADD_INPUT_BUTTON("\uE0F0 Swap", HidNpadButton_Minus, {
        R_ASSERT(setsysInitialize());
        ColorSetId id;
        R_ASSERT(setsysGetColorSetId(&id));
        R_ASSERT(setsysSetColorSetId(id == ColorSetId_Light ? ColorSetId_Dark : ColorSetId_Light));
        setsysExit();

        envSetNextLoad("sdmc:/switch/newxample.nro", "sdmc:/switch/newxample.nro");
        g_MainApplication->Close(true);
    });

    this->AddSubgroup(this->bottom_subgroup);

    //////////

    this->left_subgroup = pu::ui::Group::New(0, 132, 615, pu::ui::render::ScreenHeight - 132 - 110);
    this->left_subgroup->SetAutoRenderStrategy(pu::ui::AutoRenderStrategy::Vertical);
    this->left_subgroup->SetMarginLeft(120);
    this->left_subgroup->SetMarginRight(45);
    this->left_subgroup->SetMarginTop(40);

    for(u32 i = 0; i < 10; i++) {
        if(i > 0) {
            auto separator = pu::ui::elm::Separator::New(pu::ui::PositionAuto, pu::ui::PositionAuto, pu::ui::DimensionMatchParent, pu::ui::elm::SeparatorOrientation::Horizontal);
            this->left_subgroup->AddElement(separator);
        }

        auto guide_button_text = pu::ui::Text::New("Guide button " + std::to_string(i), pu::ui::GetDefaultFont(pu::ui::DefaultFontSize::MediumLarge), pu::ocean::OceanStyleTextFlavor_UncoloredButtonContent);
        auto guide_button = pu::ui::elm::Button::New(pu::ui::PositionAuto, pu::ui::PositionAuto, pu::ui::DimensionMatchParent, 105, pu::ocean::OceanStyleButtonFlavor_Uncolored, std::move(guide_button_text));
        guide_button->SetTextPlacement(pu::ui::elm::Button::TextPlacement::Left);
        guide_button->SetOnClick([i, this]() {
            this->selected_guide_button = i;
            this->UpdateGuideButtonColors();
            this->ReloadContent();
        });
        this->left_subgroup->AddElement(guide_button);

        if(!this->guide_buttons.empty()) {
            guide_button->SetUpElement(this->guide_buttons.back());
            this->guide_buttons.back()->SetDownElement(guide_button);
        }
        this->guide_buttons.push_back(std::move(guide_button));
    }
    this->selected_guide_button = 0;
    this->UpdateGuideButtonColors();

    this->AddSubgroup(this->left_subgroup);

    /////

    this->guide_buttons.back()->SetDownElement(this->input_buttons.front());
    for(auto &input_button: this->input_buttons) {
        input_button->SetUpElement(this->guide_buttons.back());
    }

    /////////////

    this->right_subgroup = pu::ui::Group::New(615, 132, pu::ui::render::ScreenWidth - 615, pu::ui::render::ScreenHeight - 132 - 110);
    this->ReloadContent();
    this->AddSubgroup(this->right_subgroup);

    /////

    this->guide_buttons.front()->SetFocused(true);
}

void MainApplication::OnLoad() {
    R_ASSERT(setsysInitialize());
    ColorSetId id;
    R_ASSERT(setsysGetColorSetId(&id));
    setsysExit();

    R_ASSERT(pu::ocean::InitializeResources());

    srand(time(nullptr));

    pu::ui::SetStyle(pu::ocean::OceanStyle::New(pu::ocean::defs::GetAccentForColorSetId(id)));

    this->layout = CustomLayout::New();
    this->LoadLayout(this->layout);
}
