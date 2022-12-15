#include <napi.h>

namespace display_rotate {
  bool rotateByDisplayNumber(int displayNumber, int orientation);
  Napi::Boolean rotateByDisplayNumberWrapped(const Napi::CallbackInfo& info);

  bool rotateByDisplayPosition(int orientation, int x, int y);
  Napi::Boolean rotateByDisplayPositionWrapped(const Napi::CallbackInfo& info);

  Napi::Object Init(Napi::Env env, Napi::Object exports);
}
