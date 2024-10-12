#pragma once

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <algorithm>
#include <filesystem>
#include <iostream>
#include <map>
#include <memory>
#include <numeric>
#include <string>
#include <vector>
#include <set>

#include "Common/MathLib/BoxF.hpp"
#include "Common/MathLib/ColorF.hpp"
#include "Common/MathLib/Colors.hpp"
#include "Common/MathLib/GLBoxF.hpp"
#include "Common/MathLib/PointF.hpp"
#include "Common/MathLib/Size.hpp"
#include "Common/MathLib/SizeF.hpp"
#include "Common/MathLib/Vertex2F.hpp"
#include "Common/Aliases.hpp"
#include "Common/FileUtilities.hpp"
#include "Common/Hash.hpp"
#include "Common/CanvasUtilities.hpp"
#include "Common/MouseUtilities.hpp"
#include "Common/SDLDeleter.hpp"
#include "Common/Singleton.hpp"
