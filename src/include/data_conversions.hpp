#ifndef _WE_DATA_CONVERSIONS_HPP_
#define _WE_DATA_CONVERSIONS_HPP_

#include <unordered_map>

namespace waifuengine
{
  namespace utils
  {
    enum class byte_table
    {
      byte,
      kilobyte,
      megabyte,
      gigabyte,
      terabyte
    };

    namespace impl
    {
      std::unordered_map<byte_table, unsigned long double> const byte_table_conversions =
      {
        {byte_table::byte, 1.0},
        {byte_table::kilobyte, 1024.0},
        {byte_table::megabyte, 1024.0 * 1024.0},
        {byte_table::gigabyte, 1024.0 * 1024.0 * 1024.0},
        {byte_table::terabyte, 1024.0 * 1024.0 * 1024.0 * 1024.0}
      };
    }

    template<byte_table in_type, byte_table out_type>
    unsigned long double byte_conversion(unsigned long double size)
    {
      unsigned long double num_bytes = size * impl::byte_table_conversions.at(in_type);
      return num_bytes / impl::byte_table_conversions.at(out_type);
    }
  }
}

#endif