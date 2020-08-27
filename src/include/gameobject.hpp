/****************************************************************************
 *   Copyright (C) 2020 by Music Box Games                                  *
 *                                                                          *
 *   This file is part of WaifuEngine                                       *
 *                                                                          *
 *   WaifuEngine is free software: you can redistribute it and/or modify it *
 *   under the terms of the MIT License.                                    *
 *                                                                          *
 *   WaifuEngine is distributed in the hope that it will be useful,         *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of         *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          *
 *   MIT License for more details.                                          *
 *                                                                          *
 *   You should have received a copy of the MIT License along with          *
 *   WaifuEngine.  If not, see https://opensource.org/licenses/MIT          *
 ****************************************************************************/

/******************************************************************************/
/**
* @file   gameobject.hpp
* @author Ryan Hanson
* @date   27 Aug 2020
* @par    email: iovita\@musicboxgames.net
* @brief  gameobject class. Contains and manages components.
*
* The gameobject class is what handles creation, updating, and destruction
* of the components that contain gameplay logic.
*/
/******************************************************************************/

#ifndef _W_GAMEOBJECT_HPP_
#define _W_GAMEOBJECT_HPP_

#include <vector>
#include <unordered_map>
#include <algorithm>
#include <memory>
#include <mutex>
#include <map>
#include <glm/glm.hpp>

#include <dummy.hpp>
#include <serialization.hpp>
#include <boost/serialization/unordered_map.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/shared_ptr.hpp>

#include <fs_util.hpp>
#include "debug.hpp"
#include "utils.hpp"

namespace waifuengine
{
    namespace components
    {
        namespace _impl
        {
            class _base_component;
        }
    }
}

namespace waifuengine
{
    namespace object_management
    {
        class gameobject
        {
        // usings
        protected:
            using component_map = std::map<std::string, std::shared_ptr<waifuengine::components::_impl::_base_component>, components::component_sorter>;
            
        // friends
        private:
            friend class waifuengine::core::debug::imgui_listener;
            friend class boost::serialization::access;

        // serialized members
        protected:
            component_map components_; /**< Contains attached components, keyed to their string names. */
            std::string name_; /**< Name of gameobject. */

        // not serialized members
        protected:
            bool disabled_; /**< If gameobject is disabled. */
            std::mutex lock_; /**< Lock for safe multithreading. */
        private:         
            std::string error_; /**< Error message. */

        // private functions
        private:
            template<class Archive>
            /**
              * @brief Serializes the game object.
              * @param ar Archive to serialize object to.
              * @param v Object version.
            */
            void serialize(Archive & ar, unsigned int const v)
            {
                ar & components_;
                ar & name_;
            }

        // public member variables
        public:

        // public member functions
        public:
            /**
              * @brief Gameobject constructor.
              * @param n Name of gameobject.
            */
            gameobject(std::string n = "");
            /**
              * @brief Destructor.
            */
            virtual ~gameobject();

            template<class _CType>
            /**
              * @brief Adds a component to the object
              * @return The added component.
            */
            std::shared_ptr<_CType> add_component()
            {
                std::scoped_lock lock(lock_);

                auto ptr = std::shared_ptr<_CType>(new _CType);
                ptr->parent = this;
                components_[_CType::NAME] = ptr; // TODO: handle multiple of one component
                return ptr;
            }

            template<class _CType, class ... Types>
            /**
              * @brief Adds a component with variadic arguments.
              * @param args Arguments to pass to comopnent constructor.
              * @return Added component.
            */
            std::shared_ptr<_CType> add_component_v(Types ... args)
            {
              std::scoped_lock lock(lock_);

              auto ptr = std::shared_ptr<_CType>(new _CType(args...));
              ptr->parent = this;
              components_[_CType::NAME] = ptr;
              return ptr;
            }

            template<class _CType>
            /**
              * @brief Removes a component from the object
            */
            void remove_component()
            {
              std::scoped_lock lock(lock_);


                components_.erase(_CType::NAME);
            }

            template<class _CType>
            /**
              * @brief Gets a handle to an attached component.
              * @return Handle to the requested component, or nullptr if not present.
            */
            std::shared_ptr<_CType> get_component()
            {
                return (components_.count(_CType::NAME)) ? std::dynamic_pointer_cast<_CType, components::_impl::_base_component>(components_[_CType::NAME]) : nullptr;
            }

            template<class _CType>
            /**
              * @brief Gets a const handle to an attached component.
              * @return Const handle to the requested component, or nullptr if not present.
            */
            std::shared_ptr<_CType> const get_component_const() const
            {
                return (components_.count(_CType::NAME)) ? std::dynamic_pointer_cast<_CType, components::_impl::_base_component>(components_.at(_CType::NAME)) : nullptr;
            }

            template<class _CType>
            /**
              * @brief Checks if the object has a certain component.
              * @return If the object has the given component.
            */
            bool has_component() const
            {
              return components_.count(_CType::NAME);
            }

            /**
              * @brief Checks if the object has a certain comonent.
              * @param name Name of the component to check for.
              * @return If the object has the given component.
            */
            bool has_component(std::string name) const;

            /**
              * @brief Updates the object and its components.
              * @param dt Ms since last update.
            */
            virtual void update(float dt);
            /**
              * @brief Draws the object and its components.
            */
            virtual void draw() const;

            /**
              * @brief Gets the name of the object
              * @return The object's name.
            */
            std::string const& name() const;

            /**
              * @brief Gets the number of components attached to the object.
              * @return The number of attached components.
            */
            std::size_t components() const 
            { 
              return components_.size(); 
            }

            /**
              * @brief Checks equality to another gameobject.
              * @param rhs Object to compare against.
              * @return If the two objects are equal.
            */
            bool operator==(gameobject const& rhs);

            /**
              * @brief Creates a string with info about the object.
              * @return String describing the object.
            */
            std::string dump() const;

            /**
              * @brief Gets the error string.
              * @return The object's error string.
            */
            std::string get_error() const;

            /**
              * @brief Disables the object
              * 
              * Pass true to disable, false to enable.
              * 
              * @param set To disable, or not to disable.
            */
            void disable(bool set = true);

            /**
              * @brief Checks if the object is disabled.
              * @return If the object is disabled.
            */
            bool disabled() const;

            /**
              * @brief Saves a gameobject.
              * @param obj The object to save.
            */
            static void save(std::shared_ptr<gameobject> obj);

            /**
              * @brief Loads a gameobject.
              * @param obj The object to load into.
              * @param name The name of the object to load.
            */
            static void load(std::shared_ptr<gameobject> obj, std::string name);

            /**
              * @brief Gets a list of all serialized objects and their filepaths.
              * @return Name and filepaths of each serialized object.
            */
            static std::unordered_map<std::string, fs::path>& get_object_list();

            /**
              * @brief Updates the list of serialized objects.
            */
            static void update_object_list();

            /**
              * @brief Rotates the object's transform component, if present.
              * @param degrees The distance to rotate by.
            */
            void rotate(float degrees);

            /**
              * @brief Sets the object's transform component to a given rotation.
              * 
              * This is equivalent to rotating an object from 0 degrees by the given angle. 
              * Essentially, it resets the rotation, then rotates.
              * 
              * @param degrees The degrees to set rotation to.
              * 
            */
            void set_rotation(float degrees);
           
            /**
              * @brief Translates the object's transform component, if present.
              * @param dist The distance to translate by.
            */
            void translate(glm::vec2 dist);

            /**
              * @brief Sets the object's transform component to a given translation.
              * 
              * This is equivalent to translating the object to the origin, and then
              * by the given translation. Essentially, it resets the translation, then translates.
              * 
              * @param pos The position to set the translation to.
            */
            void set_translation(glm::vec2 pos);
            
            /**
              * @brief Scales the object's transform component, if present.
              * @param s The value to scale by.
            */
            void scale(glm::vec2 s);

            /**
              * @brief Sets the object's transform component to a given scale.
              * 
              * This is equivalent to scaling the object to (1,1), and then by the given scale.
              * Essentially, it resets the scale, then scales.
              * 
              * @param s The value to set the scale to.
            */
            void set_scale(glm::vec2 s);
        };
        using objectptr = std::shared_ptr<gameobject>;
    }
}

#endif // !_W_GAMEOBJECT_HPP_
