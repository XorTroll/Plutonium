
#pragma once
#include <pu/Plutonium>
#include <pulsar.h>

#define R_ASSERT(expr) { \
    const auto rc = (expr); \
    if(R_FAILED(rc)) { \
        diagAbortWithResult(rc); \
    } \
}

namespace pu::ocean {

    enum class OceanStyleAccent {
        Light,
        Dark
    };
    
    enum OceanStyleButtonFlavor {
        OceanStyleButtonFlavor_Colored,
        OceanStyleButtonFlavor_Uncolored,
        OceanStyleButtonFlavor_UncoloredBordered
    };
    
    enum OceanStyleTextFlavor {
        OceanStyleTextFlavor_Regular,
        OceanStyleTextFlavor_ColoredButtonContent,
        OceanStyleTextFlavor_UncoloredButtonContent
    };
    
    namespace defs {

        inline OceanStyleAccent GetAccentForColorSetId(const ColorSetId id) {
            switch(id) {
                case ColorSetId_Light:
                    return OceanStyleAccent::Light;
                default:
                    return OceanStyleAccent::Dark;
            }
        }
        
        inline pu::ui::Color GetLayoutBackgroundColor(const OceanStyleAccent accent) {
            switch(accent) {
                case OceanStyleAccent::Light:
                    return pu::ui::Color::FromConstHexRGBA("#F0F0F0FF");
                case OceanStyleAccent::Dark:
                    return pu::ui::Color::FromConstHexRGBA("#2D2D2DFF");
                default:
                    return pu::ui::Color::FromConstHexRGBA("#00000000");
            }
        }
        
        inline pu::ui::Color GetGroupBackgroundColor(const OceanStyleAccent accent) {
            switch(accent) {
                case OceanStyleAccent::Light:
                    return pu::ui::Color::FromConstHexRGBA("#0000000A");
                case OceanStyleAccent::Dark:
                    return pu::ui::Color::FromConstHexRGBA("#FFFFFF0A");
                default:
                    return pu::ui::Color::FromConstHexRGBA("#00000000");
            }
        }
        
        inline pu::ui::Color GetGroupBorderSeparatorColor(const OceanStyleAccent accent) {
            switch(accent) {
                case OceanStyleAccent::Light:
                    return pu::ui::Color::FromConstHexRGBA("#2D2D2DFF");
                case OceanStyleAccent::Dark:
                    return pu::ui::Color::FromConstHexRGBA("#FFFFFFFF");
                default:
                    return pu::ui::Color::FromConstHexRGBA("#00000000");
            }
        }
        
        inline pu::ui::Color GetGroupScrollbarColor(const OceanStyleAccent accent) {
            switch(accent) {
                case OceanStyleAccent::Light:
                    return pu::ui::Color::FromConstHexRGBA("#C6C6C6FF");
                case OceanStyleAccent::Dark:
                    return pu::ui::Color::FromConstHexRGBA("#565656FF");
                default:
                    return pu::ui::Color::FromConstHexRGBA("#00000000");
            }
        }
        
        inline pu::ui::Color GetTextColor(const OceanStyleAccent accent, const u32 flavor) {
            switch(flavor) {
                case OceanStyleTextFlavor_Regular: 
                case OceanStyleTextFlavor_UncoloredButtonContent: {
                    switch(accent) {
                        case OceanStyleAccent::Light:
                            return pu::ui::Color::FromConstHexRGBA("#2C2C2CFF");
                        case OceanStyleAccent::Dark:
                            return pu::ui::Color::FromConstHexRGBA("#FFFFFFFF");
                    }
                }
                case OceanStyleTextFlavor_ColoredButtonContent: {
                    switch(accent) {
                        case OceanStyleAccent::Light:
                            return pu::ui::Color::FromConstHexRGBA("#FFFFFFFF");
                        case OceanStyleAccent::Dark:
                            return pu::ui::Color::FromConstHexRGBA("#2C2C2CFF");
                    }
                }
            }
        
            return pu::ui::Color::FromConstHexRGBA("#00000000");
        }
        
        inline u32 GetButtonBorderThickness(const OceanStyleAccent accent, const u32 flavor) {
            switch(flavor) {
                case OceanStyleButtonFlavor_UncoloredBordered: {
                    return 3;
                }
            }
        
            return 0;
        }
        
        inline pu::ui::Color GetButtonBorderColor(const OceanStyleAccent accent, const u32 flavor) {
            switch(flavor) {
                case OceanStyleButtonFlavor_UncoloredBordered: {
                    switch(accent) {
                        case OceanStyleAccent::Light:
                            return pu::ui::Color::FromConstHexRGBA("#2C2C2CFF");
                        case OceanStyleAccent::Dark:
                            return pu::ui::Color::FromConstHexRGBA("#FFFFFFFF");
                    }
                }
            }
        
            return pu::ui::Color::FromConstHexRGBA("#00000000");
        }
        
        inline pu::ui::Color GetButtonBackgroundColor(const OceanStyleAccent accent, const u32 flavor) {
            switch(flavor) {
                case OceanStyleButtonFlavor_Colored: {
                    switch(accent) {
                        case OceanStyleAccent::Light:
                            return pu::ui::Color::FromConstHexRGBA("#3250F0FF");
                        case OceanStyleAccent::Dark:
                            return pu::ui::Color::FromConstHexRGBA("#00FFC9FF");
                    }
                }
                case OceanStyleButtonFlavor_Uncolored: {
                    return pu::ui::Color::FromConstHexRGBA("#00000000");
                }
            }
        
            return pu::ui::Color::FromConstHexRGBA("#00000000");
        }
        
        inline pu::ui::Color GetButtonBackgroundHeldColor(const OceanStyleAccent accent, const u32 flavor) {
            switch(flavor) {
                case OceanStyleButtonFlavor_Colored: {
                    switch(accent) {
                        case OceanStyleAccent::Light:
                            return pu::ui::Color::FromConstHexRGBA("#2F64F2FF");
                        case OceanStyleAccent::Dark:
                            return pu::ui::Color::FromConstHexRGBA("#00FCCEFF");
                    }
                }
                case OceanStyleButtonFlavor_Uncolored: {
                    switch(accent) {
                        case OceanStyleAccent::Light:
                            return pu::ui::Color::FromConstHexRGBA("#D1EDEEFF");
                        case OceanStyleAccent::Dark:
                            return pu::ui::Color::FromConstHexRGBA("#264347FF");
                    }
                }
            }
        
            return pu::ui::Color::FromConstHexRGBA("#00000000");
        }
        
        inline pu::ui::Color GetProgressBarProgressColor(const OceanStyleAccent accent) {
            switch(accent) {
                case OceanStyleAccent::Light:
                    return pu::ui::Color::FromConstHexRGBA("#314FEFFF");
                case OceanStyleAccent::Dark:
                    return pu::ui::Color::FromConstHexRGBA("#00FFCBFF");
                default:
                    return pu::ui::Color::FromConstHexRGBA("#00000000");
            }
        }
        
        inline pu::ui::Color GetProgressBarBackgroundColor(const OceanStyleAccent accent) {
            switch(accent) {
                case OceanStyleAccent::Light:
                    return pu::ui::Color::FromConstHexRGBA("#AFAFAFFF");
                case OceanStyleAccent::Dark:
                    return pu::ui::Color::FromConstHexRGBA("#6F6F6FFF");
                default:
                    return pu::ui::Color::FromConstHexRGBA("#00000000");
            }
        }
        
        inline pu::ui::Color GetSeparatorColor(const OceanStyleAccent accent) {
            switch(accent) {
                case OceanStyleAccent::Light:
                    return pu::ui::Color::FromConstHexRGBA("#B4BDC2FF");
                case OceanStyleAccent::Dark:
                    return pu::ui::Color::FromConstHexRGBA("#4D4D4DFF");
                default:
                    return pu::ui::Color::FromConstHexRGBA("#00000000");
            }
        }
        
        inline pu::ui::Color GetFocusedBorderColorA(const OceanStyleAccent accent) {
            return pu::ui::Color::FromConstHexRGBA("#5BFCDAFF");
        }
        
        inline pu::ui::Color GetFocusedBorderColorB(const OceanStyleAccent accent) {
            return pu::ui::Color::FromConstHexRGBA("#1CCFCBFF");
        }
        
        inline pu::ui::Color GetSelectedGuideButtonTextColor(const OceanStyleAccent accent) {
            switch(accent) {
                case OceanStyleAccent::Light:
                    return pu::ui::Color::FromConstHexRGBA("#3350F4FF");
                case OceanStyleAccent::Dark:
                    return pu::ui::Color::FromConstHexRGBA("#00FFCBFF");
                default:
                    return pu::ui::Color::FromConstHexRGBA("#00000000");
            }
        }

    }
    
    class OceanStyle : public pu::ui::Style {
        private:
            OceanStyleAccent accent;
            pu::ui::ColorVariation focused_border_clr;
    
        public:
            OceanStyle(const OceanStyleAccent accent);
            PU_SMART_CTOR(OceanStyle)
    
            PU_CLASS_POD_GET(Accent, accent, OceanStyleAccent)
    
            inline void SetAccent(OceanStyleAccent new_accent) {
                this->accent = new_accent;
                this->focused_border_clr = pu::ui::ColorVariation(defs::GetFocusedBorderColorA(this->accent), defs::GetFocusedBorderColorB(this->accent));
                this->SetLayoutBackgroundColor(defs::GetLayoutBackgroundColor(this->accent));
                this->SetGroupBackgroundColor(defs::GetGroupBackgroundColor(this->accent));
                this->SetGroupBorderSeparatorColor(defs::GetGroupBorderSeparatorColor(this->accent));
                this->SetGroupScrollbarColor(defs::GetGroupScrollbarColor(this->accent));
                this->SetProgressBarProgressColor(defs::GetProgressBarProgressColor(this->accent));
                this->SetProgressBarBackgroundColor(defs::GetProgressBarBackgroundColor(this->accent));
                this->SetSeparatorColor(defs::GetSeparatorColor(this->accent));
            }
    
            inline pu::ui::Color GetTextColor(const u32 flavor) override {
                return defs::GetTextColor(this->accent, flavor);
            }
    
            inline u32 GetButtonBorderThickness(const u32 flavor) override {
                return defs::GetButtonBorderThickness(this->accent, flavor);
            }
    
            inline pu::ui::Color GetButtonBorderColor(const u32 flavor) override {
                return defs::GetButtonBorderColor(this->accent, flavor);
            }
    
            inline pu::ui::Color GetButtonBackgroundColor(const u32 flavor) override {
                return defs::GetButtonBackgroundColor(this->accent, flavor);
            }
    
            inline pu::ui::Color GetButtonBackgroundHeldColor(const u32 flavor) override {
                return defs::GetButtonBackgroundHeldColor(this->accent, flavor);
            }
    
            void Update() override;
            
            void OnElementFocusChanged(pu::ui::elm::Element::Ref elem_lost_focus, pu::ui::elm::Element::Ref elem_gained_focus) override;
            void OnElementFocusFailed(pu::ui::elm::Element::Ref elem_failed_focus) override;
    
            void OnBeforeFocusedElementRendered(pu::ui::render::Renderer::Ref &drawer, pu::ui::elm::Element::Ref elem_focused, const s32 elem_x, const s32 elem_y, const s32 elem_width, const s32 elem_height) override;
            void OnAfterFocusedElementRendered(pu::ui::render::Renderer::Ref &drawer, pu::ui::elm::Element::Ref elem_focused, const s32 elem_x, const s32 elem_y, const s32 elem_width, const s32 elem_height) override;
    
            void OnButtonClickDown(pu::ui::elm::Element::Ref elem_clicked) override;
            void OnButtonClickUp(pu::ui::elm::Element::Ref elem_clicked) override;
    };

    Result InitializeResources();
    void FinalizeResources();

}
