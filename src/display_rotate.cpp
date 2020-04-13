#include "display_rotate.h"
#include <windows.h>

enum Orientations
{
    DEGREES_CW_0 = 0,
    DEGREES_CW_90 = 3,
    DEGREES_CW_180 = 2,
    DEGREES_CW_270 = 1
};

bool display_rotate::rotateByDisplayNumber(int displayNumber, int orientation) {
    if (displayNumber <= 0) return false;

    bool result = false;
    DISPLAY_DEVICE d;
    DEVMODE dm;
    d.cb = sizeof(DISPLAY_DEVICE);

    if (!EnumDisplayDevices(NULL, displayNumber - 1, &d, EDD_GET_DEVICE_INTERFACE_NAME)) {
        return false;
    }

    if (0 != EnumDisplaySettings(d.DeviceName, ENUM_CURRENT_SETTINGS, &dm))
    {
        if ((dm.dmDisplayOrientation + orientation) % 2 == 1)
        {
            int temp = dm.dmPelsHeight;
            dm.dmPelsHeight = dm.dmPelsWidth;
            dm.dmPelsWidth = temp;
        }

        switch (orientation)
        {
            case DEGREES_CW_90:
                dm.dmDisplayOrientation = DMDO_90;
                break;
            case DEGREES_CW_180:
                dm.dmDisplayOrientation = DMDO_180;
                break;
            case DEGREES_CW_270:
                dm.dmDisplayOrientation = DMDO_270;
                break;
            case DEGREES_CW_0:
                dm.dmDisplayOrientation = DMDO_DEFAULT;
                break;
            default:
                break;
        }

        LONG ret = ChangeDisplaySettingsEx(d.DeviceName, &dm, NULL, CDS_UPDATEREGISTRY, NULL);

        result = ret == 0;
    }

    return result;
}

Napi::Boolean display_rotate::rotateByDisplayNumberWrapped(const Napi::CallbackInfo& info) 
{
  Napi::Env env = info.Env();

  if (info.Length() < 2) {
    Napi::TypeError::New(env, "Two params expected displayNumber and orientation").ThrowAsJavaScriptException();
  }

  if (!info[0].IsNumber() || !info[1].IsNumber()) {
    Napi::TypeError::New(env, "displayNumber or orientation not a number").ThrowAsJavaScriptException();
  } 

  Napi::Number first = info[0].As<Napi::Number>();
  Napi::Number second = info[1].As<Napi::Number>();

  int displayNumParam = first.Int32Value();

  int orientation = second.Int32Value();
  if (orientation != 0 && orientation != 90 && orientation != 180 && orientation != 270) {
    Napi::TypeError::New(env, "orientation must be 0 or 90 or 180 or 270").ThrowAsJavaScriptException();
  }

  int orientationParam = DEGREES_CW_0;
  if (orientation == 90) orientationParam = DEGREES_CW_90;
  if (orientation == 180) orientationParam = DEGREES_CW_180;
  if (orientation == 270) orientationParam = DEGREES_CW_270;

  bool returnValue = display_rotate::rotateByDisplayNumber(displayNumParam, orientationParam);
  
  return Napi::Boolean::New(env, returnValue);
}

Napi::Object display_rotate::Init(Napi::Env env, Napi::Object exports) 
{
  exports.Set(
    "rotateByDisplayNumber", Napi::Function::New(env, display_rotate::rotateByDisplayNumberWrapped)
  );
 
  return exports;
}
