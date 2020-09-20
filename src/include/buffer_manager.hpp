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
* @file   buffer_manager.hpp
* @author Ryan hanson
* @date   18 Sept 2020
* @par    email: iovita\@musicboxgames.net
* @brief  Manages OpenGL buffers to allow for triviable copying of their W.E. handles
*
* 
*/
/******************************************************************************/

#ifndef _WE_BUFFER_MANAGER_HPP_
#define _WE_BUFFER_MANAGER_HPP_

#include <string>

namespace waifuengine
{
  namespace graphics
  {
    namespace buffer_manager
    {
      using buffer_raw_type = unsigned int;
      
      enum class buffer_types
      {
        VAO,
        VBO,
        EBO,
      };

      class raw_buffer_wrapper
      {
      private:
        bool released;
        buffer_types type;
        buffer_raw_type data;

      public:
        raw_buffer_wrapper(buffer_types bt, buffer_raw_type raw);
        raw_buffer_wrapper(buffer_types bt);
        ~raw_buffer_wrapper();


        void release();
        bool is_released();

        buffer_raw_type raw();

      };
      using buffer_wrapper_type = raw_buffer_wrapper;

      class buffer_handle
      {
      public:
        buffer_handle(buffer_wrapper_type const& r);
        ~buffer_handle();

        buffer_wrapper_type get_wrapper();

      private:
        buffer_wrapper_type data;
      };
      using buffer_handle_type = buffer_handle;

      class raw_buffer_reference_counter
      {
      private:
        std::size_t references;
        buffer_types type;
        buffer_wrapper_type data;
        bool released;

        void release();
        void handle_ref_count();

      public:
        raw_buffer_reference_counter(buffer_types t);
        ~raw_buffer_reference_counter();

        void add_reference();
        void remove_reference();

        buffer_handle_type spawn_handle();
        buffer_wrapper_type raw();
      };


      using buffer_request_key = buffer_raw_type;
      /**
        * @brief Requests a buffer of the given type.
        * 
        *  If there is an existing buffer being managed of the correct
        *  type that is not in use, that one will be returned instead of a new buffer being created.
        * 
        * @param bt Type of buffer requested.
        * @param key Key value to find the buffer with. If 0, a new buffer will be created.
        * @return Handle to the requested buffer.
      */
      buffer_handle_type request_buffer(buffer_types bt, buffer_request_key key = buffer_request_key());

      /**
        * @brief Releases the buffer associated with the given handle.
        * 
        * In this case, this will mark the buffer as usable for another object,
        * and not fully release the resources back to openGL. @see delete_buffer(buffer_handle_type bh).
        * 
        * @param bh Handle to the buffer to release
      */
      void release_buffer(buffer_handle_type bh);

      /**
        * @brief Releases the buffer back to openGL.
        * 
        * This completely releases the buffer's resources back to openGL. If another buffer of the same
        * type is needed, it will have to be fully made again. To only mark the buffer as out of use
        * without releasing its resources, @see release_buffer(buffer_handle_type bh).
        * 
        * @param bh
      */
      void delete_buffer(buffer_handle_type bh);

      void update();

      void debug_draw();

    }
  }
}

#endif