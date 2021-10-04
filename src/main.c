#include <raylib.h>
#include <rlgl.h>
#include <janet.h>

#include "types.h"

#include "core.h"
#include "shapes.h"
#include "audio.h"
#include "gestures.h"
#include "text.h"
#include "image.h"
#include "3d.h"
#include "rlgl.h"
#include "models.h"

JANET_MODULE_ENTRY(JanetTable *env) {
    janet_cfuns(env, "freja-jaylib", core_cfuns);
    janet_cfuns(env, "freja-jaylib", shapes_cfuns);
    janet_cfuns(env, "freja-jaylib", audio_cfuns);
    janet_cfuns(env, "freja-jaylib", gesture_cfuns);
    janet_cfuns(env, "freja-jaylib", text_cfuns);
    janet_cfuns(env, "freja-jaylib", image_cfuns);
    janet_cfuns(env, "freja-jaylib", threed_cfuns);
    janet_cfuns(env, "freja-jaylib", rlgl_cfuns);
    janet_cfuns(env, "freja-jaylib", models_cfuns);
}
