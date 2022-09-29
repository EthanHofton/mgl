#ifndef mgl_hpp
#define mgl_hpp

// * use of mgl applications

// * mgl main application
#include "core/application.hpp"
#include "core/timer.hpp"

// * entry point
#include "core/entryPoint.hpp"

// * logger and config
#include "util/util.hpp"

// * events
#include "events/event.hpp"
#include "events/keyEvent.hpp"
#include "events/mouseEvent.hpp"
#include "events/applicationEvent.hpp"

// * window
#include "core/window.hpp"
#include "core/input.hpp"

// * layers
#include "core/layer.hpp"
#include "imgui/imguiLayer.hpp"

// * codes
#include "core/mouseButtonCodes.hpp"
#include "core/keyCodes.hpp"

// * renderer
#include "renderer/renderer.hpp"

// * ecs
#include "ecs/entity.hpp"
#include "ecs/objLoader.hpp"

// * ecs-components
#include "ecs/components/modelIndices.hpp"
#include "ecs/components/modelPoints.hpp"
#include "ecs/components/transform.hpp"
#include "ecs/components/camera3D.hpp"
#include "ecs/components/camera2D.hpp"
#include "ecs/components/color.hpp"
#include "ecs/components/textureCoordinates.hpp"
#include "ecs/components/UUID.hpp"
#include "ecs/components/tag.hpp"

#endif