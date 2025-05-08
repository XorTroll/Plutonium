#include <pu/ocean/OceanStyle.hpp>

namespace pu::ocean {

    namespace {

        PLSR_BFSAR g_QlaunchBfsar;
        PLSR_PlayerSoundId g_SeBtnFocus = PLSR_PLAYER_INVALID_SOUND;
        PLSR_PlayerSoundId g_SeKeyError = PLSR_PLAYER_INVALID_SOUND;
        PLSR_PlayerSoundId g_SeBtnDecide = PLSR_PLAYER_INVALID_SOUND;

    }

    OceanStyle::OceanStyle(const OceanStyleAccent accent) : pu::ui::Style(), focused_border_clr(defs::GetFocusedBorderColorA(accent), defs::GetFocusedBorderColorB(accent)) {
        this->SetAccent(accent);
        this->SetButtonRadius(5);
        this->SetColorVariateSpeedSteps(50);
        this->SetButtonTextMarginLeft(30);
        this->SetButtonTextMarginRight(30);
        this->SetGroupScrollbarMargin(10);
        this->SetGroupScrollbarSize(3);
    }
    
    void OceanStyle::Update() {
        this->focused_border_clr.Update();
    }
    
    void OceanStyle::OnElementFocusChanged(pu::ui::elm::Element::Ref _elem_lost_focus, pu::ui::elm::Element::Ref _elem_gained_focus) {
        R_ASSERT(plsrPlayerSetPitch(g_SeBtnFocus, 1.0f));
        R_ASSERT(plsrPlayerSetVolume(g_SeBtnFocus, 1.0f));
        R_ASSERT(plsrPlayerPlay(g_SeBtnFocus));
    }
    
    void OceanStyle::OnElementFocusFailed(pu::ui::elm::Element::Ref _elem_failed_focus) {
        R_ASSERT(plsrPlayerSetPitch(g_SeKeyError, 1.0f));
        R_ASSERT(plsrPlayerSetVolume(g_SeKeyError, 1.0f));
        R_ASSERT(plsrPlayerPlay(g_SeKeyError));
    }
    
    void OceanStyle::OnBeforeFocusedElementRendered(pu::ui::render::Renderer::Ref &drawer, pu::ui::elm::Element::Ref _elem_focused, const s32 elem_x, const s32 elem_y, const s32 elem_width, const s32 elem_height) {
        // TODO
    }
    
    void OceanStyle::OnAfterFocusedElementRendered(pu::ui::render::Renderer::Ref &drawer, pu::ui::elm::Element::Ref _elem_focused, const s32 elem_x, const s32 elem_y, const s32 elem_width, const s32 elem_height) {
        drawer->RenderRoundedRectangleBorder(this->focused_border_clr.Get(), elem_x - 4, elem_y - 4, elem_width + 8, elem_height + 8, 4, 8);
    }
    
    void OceanStyle::OnButtonClickDown(pu::ui::elm::Element::Ref _elem_clicked) {
        R_ASSERT(plsrPlayerSetPitch(g_SeBtnFocus, 1.0f));
        R_ASSERT(plsrPlayerSetVolume(g_SeBtnFocus, 1.0f));
        R_ASSERT(plsrPlayerPlay(g_SeBtnFocus));
    }
    
    void OceanStyle::OnButtonClickUp(pu::ui::elm::Element::Ref _elem_clicked) {
        R_ASSERT(plsrPlayerSetPitch(g_SeBtnDecide, 1.0f));
        R_ASSERT(plsrPlayerSetVolume(g_SeBtnDecide, 1.0f));
        R_ASSERT(plsrPlayerPlay(g_SeBtnDecide));
    }

    Result InitializeResources() {
        PU_RC_TRY(romfsMountDataStorageFromProgram(0x0100000000001000, "qlaunch"));
        PU_RC_TRY(plsrPlayerInit());
        PU_RC_TRY(plsrBFSAROpen("qlaunch:/sound/qlaunch.bfsar", &g_QlaunchBfsar));
        PU_RC_TRY(plsrPlayerLoadSoundByName(&g_QlaunchBfsar, "SeBtnFocus", &g_SeBtnFocus));
        PU_RC_TRY(plsrPlayerLoadSoundByName(&g_QlaunchBfsar, "SeKeyError", &g_SeKeyError));
        PU_RC_TRY(plsrPlayerLoadSoundByName(&g_QlaunchBfsar, "SeBtnDecide", &g_SeBtnDecide));
        romfsUnmount("qlaunch");
        return 0;
    }

    void FinalizeResources() {
        plsrPlayerFree(g_SeBtnFocus);
        plsrPlayerFree(g_SeKeyError);
        plsrPlayerFree(g_SeBtnDecide);
        plsrBFSARClose(&g_QlaunchBfsar);
        plsrPlayerExit();
    }

}
