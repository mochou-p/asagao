// asagao/includes/interface.hpp


#pragma once


#define STARTUP_VIEW 0
#define SCENE_VIEW   1
#define VIEW_COUNT   2


using ViewFunction = void (Interface::*)();


namespace Asagao
{
    class Interface
    {
    SINGLETON_CD(Interface)

    public:
        inline const u8 get_view() { return current_view; }

        void draw();

        u8 current_view = 0;
    private:
        void load_fonts();
        void startup_view();
        void objects();
        void assets();
        void details(v2& hovered_tile);
        void settings();
        void inspector();
        void scene_view();

        ImGuiIO* io;
        std::function<void()> m_views[VIEW_COUNT];
    };
}  // Asagao::
