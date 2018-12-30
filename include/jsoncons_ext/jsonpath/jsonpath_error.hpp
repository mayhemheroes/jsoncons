/// Copyright 2013 Daniel Parker
// Distributed under the Boost license, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// See https://github.com/danielaparker/jsoncons for latest version

#ifndef JSONCONS_JSONPATH_JSONPATH_ERROR_HPP
#define JSONCONS_JSONPATH_JSONPATH_ERROR_HPP

#include <jsoncons/json_exception.hpp>
#include <system_error>

namespace jsoncons { namespace jsonpath {

enum class jsonpath_errc 
{
    ok = 0,
    expected_root = 1,
    expected_current_node = 2,
    expected_right_bracket = 3,
    expected_name = 4,
    expected_separator = 5,
    invalid_filter = 6,
    invalid_filter_expected_slash = 7,
    invalid_filter_unbalanced_paren = 8,
    invalid_filter_unsupported_operator = 9,
    invalid_filter_expected_right_brace = 10,
    invalid_filter_expected_primary = 11,
    expected_index = 12,
    expected_left_bracket_token = 13,
    unexpected_operator = 14,
    invalid_function_name = 15,
    invalid_function_argument = 16
};

class jsonpath_error_category_impl
   : public std::error_category
{
public:
    const char* name() const noexcept override
    {
        return "jsoncons/jsonpath";
    }
    std::string message(int ev) const override
    {
        switch (static_cast<jsonpath_errc>(ev))
        {
        case jsonpath_errc::expected_root:
            return "Expected $";
        case jsonpath_errc::expected_current_node:
            return "Expected @";
        case jsonpath_errc::expected_right_bracket:
            return "Expected ]";
        case jsonpath_errc::expected_name:
            return "Expected a name following a dot";
        case jsonpath_errc::expected_index:
            return "Expected index";
        case jsonpath_errc::expected_separator:
            return "Expected dot or left bracket separator";
        case jsonpath_errc::invalid_filter:
            return "Invalid path filter";
        case jsonpath_errc::invalid_filter_expected_slash:
            return "Invalid path filter, expected '/'";
        case jsonpath_errc::invalid_filter_unbalanced_paren:
            return "Invalid path filter, unbalanced parenthesis";
        case jsonpath_errc::invalid_filter_unsupported_operator:
            return "Unsupported operator";
        case jsonpath_errc::invalid_filter_expected_right_brace:
            return "Invalid path filter, expected right brace }";
        case jsonpath_errc::invalid_filter_expected_primary:
            return "Invalid path filter, expected primary expression.";
        case jsonpath_errc::expected_left_bracket_token:
            return "Expected ?,',\",0-9,*";
        case jsonpath_errc::invalid_function_name:
            return "Invalid function name";
        default:
            return "Unknown jsonpath parser error";
        }
    }
};

inline
const std::error_category& jsonpath_error_category()
{
  static jsonpath_error_category_impl instance;
  return instance;
}

inline 
std::error_code make_error_code(jsonpath_errc result)
{
    return std::error_code(static_cast<int>(result),jsonpath_error_category());
}

}}

namespace std {
    template<>
    struct is_error_code_enum<jsoncons::jsonpath::jsonpath_errc> : public true_type
    {
    };
}

#endif
