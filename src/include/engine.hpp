#ifndef _W_ENGINE_HPP_
#define _W_ENGINE_HPP_

#include <memory> // std::unique_ptr

namespace waifuengine
{
    namespace core
    {
        class engine
        {
        private:
        public:
            static bool running;
            static void shutdown();

            engine();
            ~engine();

            void update();
            void draw() const;
        };

        std::unique_ptr<engine> build_engine();

        static void pick_calculation_models();
    }
}

#endif // !_W_ENGINE_HPP_
