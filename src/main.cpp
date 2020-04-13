#include <napi.h>
#include "display_rotate.h"

Napi::Object InitAll(Napi::Env env, Napi::Object exports) {
  return display_rotate::Init(env, exports);
}

NODE_API_MODULE(display_rotate, InitAll)
