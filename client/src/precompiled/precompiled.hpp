/*
 * Copyright 2024 Andreas Åkerberg.
 */
#pragma once

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/ext/matrix_projection.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/closest_point.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <algorithm>
#include <filesystem>
#include <iostream>
#include <map>
#include <memory>
#include <numeric>
#include <string>
#include <vector>
#include <set>
#include <functional>
#include <array>
#include <source_location>
#include <sys/socket.h>
#include <netinet/in.h>

#include "common/math_lib/box_f.hpp"
#include "common/math_lib/color_f.hpp"
#include "common/math_lib/colors.hpp"
#include "common/math_lib/gl_box_f.hpp"
#include "common/math_lib/point2_f.hpp"
#include "common/math_lib/size.hpp"
#include "common/math_lib/size_f.hpp"
#include "common/math_lib/vertex2_f.hpp"
#include "common/math_lib/point3_f.hpp"
#include "common/math_lib/vertex3_f.hpp"
#include "common/math_lib/point2.hpp"
#include "common/math_lib/point3.hpp"
#include "common/math_lib/vertex_tile.hpp"
#include "common/aliases.hpp"
#include "common/file_utilities.hpp"
#include "common/hash.hpp"
#include "common/canvas_utilities.hpp"
#include "common/mouse_utilities.hpp"
#include "common/math/trigonometry.hpp"
#include "common/sdl_deleter.hpp"
#include "common/singleton.hpp"
#include "common/timer.hpp"
#include "common/enum_types/font_sizes.hpp"
#include "common/enum_types/cursor_styles.hpp"
#include "common/enum_types/rotation_types.hpp"
#include "common/enum_types/buffer_types.hpp"
#include "common/dev_utilities.hpp"
