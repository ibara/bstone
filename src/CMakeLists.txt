cmake_minimum_required(VERSION 3.1.3 FATAL_ERROR)
project(bstone VERSION 1.1.9 LANGUAGES CXX)


find_package(SDL2 REQUIRED)


option(BSTONE_USE_STATIC_LINKING "Link build statically.")
option(BSTONE_PANDORA "Build for Pandora.")
option(BSTONE_USE_PCH "Use precompiled headers.")


#
# Target.
#
add_executable(bstone "")


#
# Target properties.
#
set_target_properties(
	bstone
	PROPERTIES
	CXX_STANDARD 11
	CXX_STANDARD_REQUIRED ON
	CXX_EXTENSIONS OFF
)

if (WIN32)
	set_target_properties(
		bstone
		PROPERTIES
			WIN32_EXECUTABLE TRUE
	)
endif ()


#
# Target compile definitions.
#
if (BSTONE_USE_PCH)
	target_compile_definitions(
		bstone
		PRIVATE
			BSTONE_USE_PCH
	)
endif ()

if (MSVC)
	target_compile_definitions(
		bstone
		PRIVATE
			_CRT_SECURE_NO_WARNINGS
			_SCL_SECURE_NO_WARNINGS
			_BIND_TO_CURRENT_VCLIBS_VERSION=1
	)
endif ()

if (BSTONE_PANDORA)
	target_compile_definitions(
		bstone
		PRIVATE
			BSTONE_PANDORA
	)
endif ()


#
# Target compile options.
#
if (MSVC)
	if (BSTONE_USE_PCH)
		target_compile_options(
			bstone
			PRIVATE
				-Yubstone_precompiled.h
				-FIbstone_precompiled.h
		)
	endif ()

	if (BSTONE_USE_STATIC_LINKING)
		target_compile_options(
			bstone
			PRIVATE
				$<$<CONFIG:DEBUG>:-MTd>
				$<$<NOT:$<CONFIG:DEBUG>>:-MT>
		)
	endif ()
endif ()

if (BSTONE_PANDORA)
	target_compile_options(
		bstone
		PRIVATE
			-fsigned-char
			-fsigned-char
			-mcpu=cortex-a8
			-mfpu=neon
			-mfloat-abi=softfp
			-ffast-math
			-fsingle-precision-constant
			-fno-inline-functions
	)
endif ()


#
# Target link libraries.
#
if (BSTONE_USE_STATIC_LINKING AND NOT WIN32)
	target_link_libraries(
		bstone
		-static
	)
endif ()

if (WIN32 AND NOT MINGW)
	target_link_libraries(
		bstone
		SDL2::SDL2main
	)

	if (BSTONE_USE_STATIC_LINKING)
		target_link_libraries(
			bstone
			SDL2::SDL2-static
		)
	else ()
		target_link_libraries(
			bstone
			SDL2::SDL2
		)
	endif ()
else ()
	target_link_libraries(
		bstone
		${SDL2_LIBRARIES}
	)
endif ()

if (BSTONE_USE_STATIC_LINKING AND MINGW)
	target_link_libraries(
		bstone
		imm32
		version
		winmm
	)
endif ()

if (BSTONE_PANDORA)
	target_link_libraries(
		bstone
		Xext
		Xau
		Xdmcp
		X11
		GLESv2
		EGL
		IMGegl
		srv_um
		ts
	)
endif ()


#
# Target include directories.
#
target_include_directories(
	bstone
	PRIVATE
		dosbox
)

if (NOT WIN32 OR MINGW)
	target_include_directories(
		bstone
		PRIVATE
			${SDL2_INCLUDE_DIRS}
			dosbox
	)
endif ()

if (BSTONE_PANDORA)
	target_include_directories(
		bstone
		PRIVATE
			$ENV{PNDSDK}
	)
endif ()


#
# Target sources.
#
target_sources(
	bstone
	PRIVATE
		dosbox/adlib.h
		dosbox/dbopl.h
		dosbox/dosbox.h
		dosbox/hardware.h
		dosbox/inout.h
		dosbox/mixer.h
		dosbox/pic.h
		dosbox/setup.h
		3d_def.h
		3d_menu.h
		an_codes.h
		audio.h
		bstone_adlib_decoder.h
		bstone_adlib_music_decoder.h
		bstone_adlib_sfx_decoder.h
		bstone_audio_decoder.h
		bstone_audio_mixer.h
		bstone_atomic.h
		bstone_binary_reader.h
		bstone_binary_writer.h
		bstone_cl_args.h
		bstone_crc32.h
		bstone_endian.h
		bstone_file_stream.h
		bstone_fizzle_fx.h
		bstone_fixed_point.h
		bstone_format_string.h
		bstone_generic_fizzle_fx.h
		bstone_stream.h
		bstone_log.h
		bstone_memory_binary_reader.h
		bstone_memory_stream.h
		bstone_mt_queue_1r1w.h
		bstone_opl2.h
		bstone_ref_values.h
		bstone_pcm_decoder.h
		bstone_precompiled.h
		bstone_ps_fizzle_fx.h
		bstone_scope_guard.h
		bstone_sha1.h
		bstone_sprite.h
		bstone_sprite_cache.h
		bstone_string_helper.h
		bstone_text_reader.h
		bstone_text_writer.h
		bstone_un_value.h
		gfxv.h
		id_ca.h
		id_heads.h
		id_in.h
		id_pm.h
		id_sd.h
		id_us.h
		id_vh.h
		id_vl.h
		jam_io.h
		jm_cio.h
		jm_io.h
		jm_lzh.h
		jm_tp.h
		jm_vl.h
		movie.h
)

target_sources(
	bstone
	PRIVATE
		dosbox/dbopl.cpp
		3d_act1.cpp
		3d_act2.cpp
		3d_agent.cpp
		3d_debug.cpp
		3d_draw.cpp
		3d_draw2.cpp
		3d_game.cpp
		3d_inter.cpp
		3d_main.cpp
		3d_menu.cpp
		3d_msgs.cpp
		3d_play.cpp
		3d_scale.cpp
		3d_state.cpp
		bstone_adlib_decoder.cpp
		bstone_adlib_music_decoder.cpp
		bstone_adlib_sfx_decoder.cpp
		bstone_audio_decoder.cpp
		bstone_audio_mixer.cpp
		bstone_binary_reader.cpp
		bstone_binary_writer.cpp
		bstone_cl_args.cpp
		bstone_crc32.cpp
		bstone_file_stream.cpp
		bstone_fizzle_fx.cpp
		bstone_format_string.cpp
		bstone_generic_fizzle_fx.cpp
		bstone_stream.cpp
		bstone_log.cpp
		bstone_memory_binary_reader.cpp
		bstone_memory_stream.cpp
		bstone_opl2.cpp
		bstone_pcm_decoder.cpp
		bstone_precompiled.cpp
		bstone_ps_fizzle_fx.cpp
		bstone_sha1.cpp
		bstone_sprite.cpp
		bstone_sprite_cache.cpp
		bstone_string_helper.cpp
		bstone_text_reader.cpp
		bstone_text_writer.cpp
		colormap.cpp
		d3_d2.cpp
		d3_dr2.cpp
		id_ca.cpp
		id_in.cpp
		id_pm.cpp
		id_sd.cpp
		id_sdd.cpp
		id_us.cpp
		id_us_1.cpp
		id_vh.cpp
		id_vl.cpp
		jm_cio.cpp
		jm_free.cpp
		jm_io.cpp
		jm_lzh.cpp
		jm_tp.cpp
		markhack.cpp
		movie.cpp
		scale.cpp
		stub.cpp
		vgapal.cpp
)

if (WIN32)
	target_sources(
		bstone
		PRIVATE
			sys/win32/bstone_win32.rc
	)
endif ()


#
# Source properties.
#
if (MSVC AND BSTONE_USE_PCH)
	set_source_files_properties(
		bstone_precompiled.cpp
		PROPERTIES
			# Precompiled Header (Create)
			COMPILE_FLAGS -Yc
	)
endif ()


#
# Install.
#
install(
	TARGETS
	bstone
		RUNTIME DESTINATION "."
)

install(
	FILES
		../CHANGELOG.md
	DESTINATION "."
	RENAME bstone_changelog.txt
)

install(
	FILES
		../README.md
	DESTINATION "."
	RENAME bstone_readme.txt
)

install(
	FILES
		../LICENSE
	DESTINATION "."
	RENAME bstone_license.txt
)

install(
	FILES
		../COPYING-SDL2.txt
	DESTINATION "."
	RENAME bstone_sdl2_license.txt
)
