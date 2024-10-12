/*
 * Copyright 2024 Andreas Åkerberg
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

#include "Common/MathLib/BoxF.hpp"
#include "Common/MathLib/ColorF.hpp"
#include "Common/MathLib/Colors.hpp"
#include "Common/MathLib/GLBoxF.hpp"
#include "Common/MathLib/Point2F.hpp"
#include "Common/MathLib/Size.hpp"
#include "Common/MathLib/SizeF.hpp"
#include "Common/MathLib/Vertex2F.hpp"
#include "Common/MathLib/Point3F.hpp"
#include "Common/MathLib/Vertex3F.hpp"
#include "Common/Aliases.hpp"
#include "Common/FileUtilities.hpp"
#include "Common/Hash.hpp"
#include "Common/CanvasUtilities.hpp"
#include "Common/MouseUtilities.hpp"
#include "Common/SDLDeleter.hpp"
#include "Common/Singleton.hpp"
