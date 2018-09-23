/*
 * Copyright © 2011-2018 BTicino S.p.A.
 * 
 * This file is part of bt_drover.
 * 
 * bt_drover is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * bt_drover is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public License
 * along with bt_drover. If not, see <http://www.gnu.org/licenses/>.
 * 
 * 
 */
#ifndef S3IT_TECH_CHALLENGE_ERROR_HPP
#define S3IT_TECH_CHALLENGE_ERROR_HPP

#include <string>

class Error
{
    int error_code;
    std::string error_message;
public:
    Error() :
            error_code(0), error_message("")
    {}

    Error(int code, std::string message) :
            error_code(code), error_message(std::move(message))
    {}

    int getError_code() const
    {
        return error_code;
    }

    void setError_code(int error_code)
    {
        Error::error_code = error_code;
    }

    const std::string &getError_message() const
    {
        return error_message;
    }

    void setError_message(const std::string &error_message)
    {
        Error::error_message = error_message;
    }
};

class TIFFWrongFormatError final : public Error
{
public:
    TIFFWrongFormatError() :
            Error(-32001, "TIFF wrong format")
    {}
};

class TIFFWrongBitNumberError final : public Error
{
public:
    TIFFWrongBitNumberError() :
            Error(-32002, "TIFF wrong bit per pixel")
    {}
};

#endif //S3IT_TECH_CHALLENGE_ERROR_HPP
