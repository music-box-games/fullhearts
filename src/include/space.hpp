
#ifndef _W_SPACE_HPP_
#define _W_SPACE_HPP_

#include <unordered_map>
#include <memory>

namespace waifuengine
{
    namespace object_management
    {
        class gameobject;

        class space
        {
        private:
            std::string name_;

            std::unordered_map<std::string, std::shared_ptr<gameobject>> objects_;

        public:
            space(std::string n);
            ~space();

            void add_object(std::string name);
            void remove_object(std::string name);
            std::shared_ptr<gameobject> get_object(std::string name);

            void update(float dt);
            void draw() const;

            std::size_t objects() const;
            std::size_t components() const;
        };
    }
}

#endif // !_W_SPACE_HPP_
