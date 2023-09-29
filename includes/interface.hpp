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
    public:
        static Interface& get_instance()
        {
            static Interface instance;

            return instance;
        }
    private:
        Interface();
        ~Interface();

        Interface           (const Interface&) = delete;
        Interface& operator=(const Interface&) = delete;


    public:
        inline const u8 get_view() { return current_view; }

        void draw();

        u8 current_view = 0;
    private:
        void startup_view();
        void objects();
        void details();
        void components();
        void scene_view();

        std::function<void()> m_views[VIEW_COUNT];
    };
}  // Asagao::
