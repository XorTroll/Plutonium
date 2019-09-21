#include <pu/ui/elm/elm_MotionCursor.hpp>
#include <pu/ui/ui_Layout.hpp>

namespace pu::ui::elm
{
    MotionCursor::MotionCursor(String CursorImage, HidControllerID Player, JoyCon JoyCon) : Element::Element()
    {
        this->lastx = -1;
        this->lasty = -1;
        this->cursorimg = NULL;
        this->joycon = JoyCon;
        this->SetCursorImage(CursorImage);
        this->click = [&](u32 X, u32 Y)
        {
            ((ui::Layout*)this->GetParent())->SimulateTouch({ X, Y });
        };

        hidGetSixAxisSensorHandles(this->sixaxishandles, 2, Player, TYPE_JOYCON_PAIR);
        hidStartSixAxisSensor(this->sixaxishandles[static_cast<u32>(this->joycon)]);
    }

    MotionCursor::~MotionCursor()
    {
        if(this->cursorimg != NULL)
        {
            render::DeleteTexture(this->cursorimg);
            this->cursorimg = NULL;
        }
        hidStopSixAxisSensor(this->sixaxishandles[static_cast<u32>(this->joycon)]);
    }

    s32 MotionCursor::GetX()
    {
        return this->lastx;
    }

    s32 MotionCursor::GetY()
    {
        return this->lasty;
    }

    s32 MotionCursor::GetWidth()
    {
        return render::GetTextureWidth(this->cursorimg);
    }

    s32 MotionCursor::GetHeight()
    {
        return render::GetTextureHeight(this->cursorimg);
    }

    String MotionCursor::GetCursorImage()
    {
        return this->imgpath;
    }

    void MotionCursor::SetCursorImage(String Path)
    {
        if(this->cursorimg != NULL) render::DeleteTexture(this->cursorimg);
        this->cursorimg = NULL;
        std::ifstream ifs(Path.AsUTF8());
        bool ok = ifs.good();
        ifs.close();
        if(ok)    
        {
            this->imgpath = Path;
            this->cursorimg = render::LoadImage(Path.AsUTF8());
        }
    }

    void MotionCursor::OnRender(render::Renderer::Ref &Drawer, s32 X, s32 Y)
    {
        if(this->lastx < 0) return;
        if(this->lasty < 0) return;
        Drawer->RenderTexture(this->cursorimg, this->lastx, this->lasty);
    }

    void MotionCursor::OnInput(u64 Down, u64 Up, u64 Held, Touch Pos)
    {
        if(hidIsControllerConnected(this->player))
        {
            SixAxisSensorValues sixaxis;
            hidSixAxisSensorValuesRead(&sixaxis, this->player, 1);

            // SUPER, super hacky way to get X and Y, after several hours of testing six-axis vector variables this is the most accurate way to get them
            auto py = ((sixaxis.accelerometer.y + 0.2f) / 0.6f) * 720.0f;
            auto px = sixaxis.orientation[1].x * 1280.0f;
            
            this->lastx = (s32)px;
            this->lasty = (s32)py;

            if((this->lastx >= 0) && (this->lastx <= 1280) && (this->lasty >= 0) && (this->lasty <= 720))
            {
                if(Down & KEY_A)
                {
                    (this->click)(this->lastx, this->lasty);
                }
            }
        }
        else
        {
            this->lastx = -1;
            this->lasty = -1;
        }
    }
}