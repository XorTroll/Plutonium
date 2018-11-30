
#pragma once
#include <pn/fw/Element.hpp>
#include <vector>

namespace pn::fw
{
    enum class DialogResult
    {
        Ok,
        Cancel,
    };

    class DialogOption
    {
        public:
            DialogOption(std::string Name, DialogResult Type);
            std::string GetName();
            void SetName(std::string Name);
            DialogResult GetType();
            void SetType(DialogResult Type);
        private:
            std::string name;
            DialogResult type;
    };

    class Dialog
    {
        public:
            Dialog(std::string Title, std::string Content);
            void AddOption(DialogOption *Option);
            void Show(render::Renderer *Drawer);
            bool GotOk();
            bool GotCancel();
            DialogOption *GetSelectedOption();
        private:
            std::string title;
            std::string cnt;
            std::vector<DialogOption*> opts;
            u32 osel;
            u32 prevosel;
            s32 pselfact;
            s32 selfact;
    };
}