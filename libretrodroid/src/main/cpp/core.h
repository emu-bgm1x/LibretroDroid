/*
 *     Copyright (C) 2019  Filippo Scognamiglio
 *
 *     This program is free software: you can redistribute it and/or modify
 *     it under the terms of the GNU General Public License as published by
 *     the Free Software Foundation, either version 3 of the License, or
 *     (at your option) any later version.
 *
 *     This program is distributed in the hope that it will be useful,
 *     but WITHOUT ANY WARRANTY; without even the implied warranty of
 *     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *     GNU General Public License for more details.
 *
 *     You should have received a copy of the GNU General Public License
 *     along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef LIBRETRODROID_CORE_H
#define LIBRETRODROID_CORE_H

#include <string>

#include "../../libretro-common/include/libretro.h"

namespace libretrodroid {

class Core {
public:
    void (*retro_init)(void);
    void (*retro_deinit)(void);
    unsigned (*retro_api_version)(void);
    void (*retro_cheat_reset)(void);
    void (*retro_cheat_set)(unsigned index, bool enabled, const char *code);
    void (*retro_get_system_info)(struct retro_system_info *info);
    void (*retro_get_system_av_info)(struct retro_system_av_info *info);
    void (*retro_set_controller_port_device)(unsigned port, unsigned device);
    void (*retro_reset)(void);
    void (*retro_run)(void);
    size_t (*retro_serialize_size)(void);
    bool (*retro_serialize)(void *data, size_t size);
    bool (*retro_unserialize)(const void *data, size_t size);
    size_t (*retro_get_memory_size)(unsigned id);
    void* (*retro_get_memory_data)(unsigned id);
    bool (*retro_load_game)(const struct retro_game_info *game);
    void (*retro_unload_game)(void);
    void (*retro_set_video_refresh)(retro_video_refresh_t);
    void (*retro_set_environment)(retro_environment_t);
    void (*retro_set_audio_sample)(retro_audio_sample_t);
    void (*retro_set_audio_sample_batch)(retro_audio_sample_batch_t);
    void (*retro_set_input_poll)(retro_input_poll_t);
    void (*retro_set_input_state)(retro_input_state_t);

    // ff-bgm1x: 수정한 mGBA 코어만 가진 함수 (없으면 nullptr)
    void (*ff_bgm1x_mix)(int16_t* stereo, int frames, int sampleRate) = nullptr;
    bool (*ff_bgm1x_speed_hold)(void) = nullptr;
    // ff-bgm1x 소리 분류 (있는 코어만): 문자열 명령, 분류 화면의 재생 소리
    const char* (*ff_catalog_command)(const char* cmd) = nullptr;
    int (*ff_preview_render)(int16_t* stereo, int frames, int sampleRate) = nullptr;

    Core(const std::string& soCorePath);
    ~Core();

private:
    void open(const std::string& soCorePath);
    void close();

    void* libHandle = nullptr;
};

}



#endif //LIBRETRODROID_CORE_H
