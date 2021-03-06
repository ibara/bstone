/*
BStone: A Source port of
Blake Stone: Aliens of Gold and Blake Stone: Planet Strike

Copyright (c) 1992-2013 Apogee Entertainment, LLC
Copyright (c) 2013-2015 Boris I. Bendovsky (bibendovsky@hotmail.com)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the
Free Software Foundation, Inc.,
51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
*/


//
// Logging facility
//


#ifndef BSTONE_LOG_INCLUDED
#define BSTONE_LOG_INCLUDED


#include <functional>
#include <sstream>
#include <string>
#include <vector>
#include "bstone_file_stream.h"


namespace bstone
{


//
// Writes messages to standard output, file and
// shows message box (on critical error).
//
// - Argument placements are figured parentheses - {}.
// - Any non digit character between parentheses discards formating
//   till another non-double opening parenthese.
// - Use double opening parenthese to write the opening parenthese.
// - Specify a number between 0 and 9 for a positional argument.
//
// Examples:
//    1) write("coords: {{{}, {}}", 0.5, 1.0);
//
//       writes: "{0.5, 1.0}"
//
//    2) write("size: {}x{} (width: {0}; height: {1})", 5, 6);
//
//       writes: "size 5x6 (width: 5; height: 6)"
//
// WARNING: Max allowed argument count: 10 (0..9)
//
class Log
{
public:
	static void write();

	// Writes the game's version to standart output and shows a message box.
	static void write_version();

	// Writes an informational message to the log.
	template<typename... TArgs>
	static void write(
		const std::string& format,
		TArgs... args)
	{
		write_internal(MessageType::information, format, std::forward<TArgs>(args)...);
	}

	// Writes a warning message to the log.
	template<typename... TArgs>
	static void write_warning(
		const std::string& format,
		TArgs... args)
	{
		write_internal(MessageType::warning, format, std::forward<TArgs>(args)...);
	}

	// Writes an error message to the log.
	template<typename... TArgs>
	static void write_error(
		const std::string& format,
		TArgs... args)
	{
		write_internal(MessageType::error, format, std::forward<TArgs>(args)...);
	}

	// Similar to error but with message box.
	template<typename... TArgs>
	static void write_critical(
		const std::string& format,
		TArgs... args)
	{
		write_internal(MessageType::critical_error, format, std::forward<TArgs>(args)...);
	}


private:
	using Arguments = std::vector<std::string>;


	enum class MessageType
	{
		none,
		version,
		information,
		warning,
		error,
		critical_error,
	}; // MessageType


	Log();

	Log(
		const Log& rhs) = delete;

	Log& operator=(
		const Log& rhs) = delete;

	~Log();


	static Log& get_local();


	void write_internal(
		const std::string& format);

	template<
		typename... TArgs,
		typename TArg>
		void write_internal(
			const std::string& format,
			const std::reference_wrapper<TArg>& arg,
			TArgs... args)
	{
		write_internal(format, arg.get(), std::forward<TArgs>(args)...);
	}

	template<
		typename... TArgs,
		typename TArg>
		void write_internal(
			const std::string& format,
			const TArg& arg,
			TArgs... args)
	{
		sstream_.clear();
		sstream_.str({});
		sstream_ << arg;

		args_.emplace_back(sstream_.str());
		write_internal(format, std::forward<TArgs>(args)...);
	}

	static void clean_up();

	template<typename... TArgs>
	static void write_internal(
		const MessageType message_type,
		const std::string& format,
		TArgs... args)
	{
		clean_up();

		auto& local = get_local();
		local.message_type_ = message_type;
		local.write_internal(format, std::forward<TArgs>(args)...);
	}


	FileStream fstream_;
	Arguments args_;
	std::ostringstream sstream_;
	std::string message_;
	MessageType message_type_;
};


} // bstone


#endif // BSTONE_LOG_INCLUDED
