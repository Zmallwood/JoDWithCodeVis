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

#include "common/math_lib/BoxF.hpp"
#include "common/math_lib/ColorF.hpp"
#include "common/math_lib/Colors.hpp"
#include "common/math_lib/GLBoxF.hpp"
#include "common/math_lib/Point2F.hpp"
#include "common/math_lib/Size.hpp"
#include "common/math_lib/SizeF.hpp"
#include "common/math_lib/Vertex2F.hpp"
#include "common/math_lib/Point3F.hpp"
#include "common/math_lib/Vertex3F.hpp"
#include "common/math_lib/Point2.hpp"
#include "common/math_lib/Point3.hpp"
#include "common/math_lib/VertexTile.hpp"
#include "common/Aliases.hpp"
#include "common/FileUtilities.hpp"
#include "common/Hash.hpp"
#include "common/CanvasUtilities.hpp"
#include "common/MouseUtilities.hpp"
#include "common/math/Trigonometry.hpp"
#include "common/SDLDeleter.hpp"
#include "common/Singleton.hpp"
#include "common/Timer.hpp"
#include "common/enum_types/FontSizes.hpp"
#include "common/enum_types/CursorStyles.hpp"
#include "common/enum_types/RotationTypes.hpp"
#include "common/enum_types/BufferTypes.hpp"
#include "common/DevUtiltiies.hpp"
