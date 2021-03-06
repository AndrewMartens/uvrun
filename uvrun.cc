#include <node.h>
#include <v8.h>
#include <uv.h>

using namespace v8;

Handle<Value> Run(const Arguments& args) {
  HandleScope scope;
#if (UV_VERSION_MAJOR == 0) && (UV_VERSION_MINOR < 9)
  uv_run(uv_default_loop());
#else
    uv_run(uv_default_loop(), UV_RUN_DEFAULT);
#endif
  return scope.Close(Null());
}

Handle<Value> RunOnce(const Arguments& args) {
  HandleScope scope;
#if (UV_VERSION_MAJOR == 0) && (UV_VERSION_MINOR < 9)
  int r = uv_run_once(uv_default_loop());
#else
  int r = uv_run(uv_default_loop(), UV_RUN_ONCE);
#endif
  return scope.Close(Number::New(r));
}

void init(Handle<Object> target) {
  NODE_SET_METHOD(target, "run", Run);
  NODE_SET_METHOD(target, "runOnce", RunOnce);
}

NODE_MODULE(uvrun, init);
