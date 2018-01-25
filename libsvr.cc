#include "libsvr.h";

using namespace std;
using namespace v8;
using namespace onlinesvr;

using v8::Array;
using v8::Context;
using v8::Function;
using v8::FunctionCallbackInfo;
using v8::FunctionTemplate;
using v8::Integer;
using v8::Isolate;
using v8::Local;
using v8::Number;
using v8::Object;
using v8::Persistent;
using v8::String;
using v8::Value;

void InitAll(Local<Object> exports)
{
  __OnlineSVR::Init(exports);
}

NODE_MODULE(NODE_GYP_MODULE_NAME, InitAll)

Persistent<Function> __OnlineSVR::constructor;

__OnlineSVR::__OnlineSVR(double value) : value_(value)
{
  this->_native = new OnlineSVR();

  this->_native->SetVerbosity(0);
}

__OnlineSVR::~__OnlineSVR()
{
  delete this->_native;
}

void __OnlineSVR::Init(Local<Object> exports)
{
  Isolate *isolate = exports->GetIsolate();

  // Prepare constructor template
  Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);
  tpl->SetClassName(String::NewFromUtf8(isolate, "OnlineSVR"));
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  // Prototype
  NODE_SET_PROTOTYPE_METHOD(tpl, "train", Train);
  NODE_SET_PROTOTYPE_METHOD(tpl, "predict", Predict);
  NODE_SET_PROTOTYPE_METHOD(tpl, "forget", Forget);
  NODE_SET_PROTOTYPE_METHOD(tpl, "clear", Clear);

  NODE_SET_PROTOTYPE_METHOD(tpl, "setC", SetC);
  NODE_SET_PROTOTYPE_METHOD(tpl, "getC", GetC);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setEpsilon", SetEpsilon);
  NODE_SET_PROTOTYPE_METHOD(tpl, "getEpsilon", GetEpsilon);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setKernel", SetKernel);
  NODE_SET_PROTOTYPE_METHOD(tpl, "getKernel", GetKernel);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setKernelParam", SetKernelParam);
  NODE_SET_PROTOTYPE_METHOD(tpl, "getKernelParam", GetKernelParam);

  NODE_SET_PROTOTYPE_METHOD(tpl, "getSamplesTrainedNumber", GetSamplesTrainedNumber);
  NODE_SET_PROTOTYPE_METHOD(tpl, "getSupportSetElementsNumber", GetSupportSetElementsNumber);
  NODE_SET_PROTOTYPE_METHOD(tpl, "getErrorSetElementsNumber", GetErrorSetElementsNumber);
  NODE_SET_PROTOTYPE_METHOD(tpl, "getRemainingSetElementsNumber", GetRemainingSetElementsNumber);

  NODE_SET_PROTOTYPE_METHOD(tpl, "getSupportSetIndexes", GetSupportSetIndexes);
  NODE_SET_PROTOTYPE_METHOD(tpl, "getErrorSetIndexes", GetErrorSetIndexes);
  NODE_SET_PROTOTYPE_METHOD(tpl, "getRemainingSetIndexes", GetRemainingSetIndexes);

  constructor.Reset(isolate, tpl->GetFunction());
  exports->Set(String::NewFromUtf8(isolate, "OnlineSVR"),
               tpl->GetFunction());
}

void __OnlineSVR::New(const FunctionCallbackInfo<Value> &args)
{
  Isolate *isolate = args.GetIsolate();

  if (args.IsConstructCall())
  {
    // Invoked as constructor: `new __OnlineSVR(...)`
    double value = args[0]->IsUndefined() ? 0 : args[0]->NumberValue();
    __OnlineSVR *obj = new __OnlineSVR(value);
    obj->Wrap(args.This());
    args.GetReturnValue().Set(args.This());
  }
  else
  {
    // Invoked as plain function `__OnlineSVR(...)`, turn into construct call.
    const int argc = 1;
    Local<Value> argv[argc] = {args[0]};
    Local<Context> context = isolate->GetCurrentContext();
    Local<Function> cons = Local<Function>::New(isolate, constructor);
    Local<Object> result =
        cons->NewInstance(context, argc, argv).ToLocalChecked();
    args.GetReturnValue().Set(result);
  }
}

void __OnlineSVR::Train(const FunctionCallbackInfo<Value> &args)
{
  Isolate *isolate = args.GetIsolate();
  Local<Context> ctx = isolate->GetCurrentContext();

  __OnlineSVR *obj = ObjectWrap::Unwrap<__OnlineSVR>(args.Holder());

  v8::Handle<v8::Value> arg0(args[0]);

  if (arg0->IsArray())
  {
    Local<Array> arr = v8::Local<v8::Array>::Cast(arg0);

    uint32_t length = arr->Length();

    Vector<double> *vec = new Vector<double>(length);

    for (int index = 0; index < length; index++)
    {
      vec->Add(arr->Get(ctx, index).ToLocalChecked()->ToNumber(isolate)->NumberValue());
    }

    double value = args[1]->ToNumber(isolate)->NumberValue();

    int index = obj->_native->Train(vec, value);

    args.GetReturnValue().Set(Number::New(isolate, index));
  }
}

void __OnlineSVR::Predict(const FunctionCallbackInfo<Value> &args)
{
  Isolate *isolate = args.GetIsolate();
  Local<Context> ctx = isolate->GetCurrentContext();

  __OnlineSVR *obj = ObjectWrap::Unwrap<__OnlineSVR>(args.Holder());

  v8::Handle<v8::Value> arg0(args[0]);

  if (arg0->IsArray())
  {
    Local<Array> arr = v8::Local<v8::Array>::Cast(arg0);

    uint32_t length = arr->Length();

    Vector<double> *vec = new Vector<double>(length);

    for (int index = 0; index < length; index++)
    {
      vec->Add(arr->Get(ctx, index).ToLocalChecked()->ToNumber(isolate)->NumberValue());
    }

    double value = obj->_native->Predict(vec);

    args.GetReturnValue().Set(Number::New(isolate, value));
  }
}

void __OnlineSVR::Forget(const FunctionCallbackInfo<Value> &args)
{
  Isolate *isolate = args.GetIsolate();
  Local<Context> ctx = isolate->GetCurrentContext();

  __OnlineSVR *obj = ObjectWrap::Unwrap<__OnlineSVR>(args.Holder());

  v8::Handle<v8::Value> arg0(args[0]);

  if (arg0->IsArray())
  {
    Local<Array> arr = v8::Local<v8::Array>::Cast(arg0);

    uint32_t length = arr->Length();

    Vector<int> *vec = new Vector<int>(length);

    for (int index = 0; index < length; index++)
    {
      vec->Add(static_cast<int>(arr->Get(ctx, index).ToLocalChecked()->ToNumber(isolate)->NumberValue()));
    }

    int value = obj->_native->Forget(vec);

    args.GetReturnValue().Set(Number::New(isolate, value));
  }
}

void __OnlineSVR::Clear(const FunctionCallbackInfo<Value> &args)
{
  Isolate *isolate = args.GetIsolate();
  Local<Context> ctx = isolate->GetCurrentContext();

  __OnlineSVR *obj = ObjectWrap::Unwrap<__OnlineSVR>(args.Holder());

  obj->_native->Clear();
}

void __OnlineSVR::SetC(const FunctionCallbackInfo<Value> &args)
{
  Isolate *isolate = args.GetIsolate();
  Local<Context> ctx = isolate->GetCurrentContext();

  __OnlineSVR *obj = ObjectWrap::Unwrap<__OnlineSVR>(args.Holder());

  double arg = args[0]->ToNumber(isolate)->NumberValue();

  obj->_native->SetC(arg);
}

void __OnlineSVR::GetC(const FunctionCallbackInfo<Value> &args)
{
  Isolate *isolate = args.GetIsolate();
  Local<Context> ctx = isolate->GetCurrentContext();

  __OnlineSVR *obj = ObjectWrap::Unwrap<__OnlineSVR>(args.Holder());

  args.GetReturnValue().Set(Number::New(isolate, obj->_native->GetC()));
}

void __OnlineSVR::SetEpsilon(const FunctionCallbackInfo<Value> &args)
{
  Isolate *isolate = args.GetIsolate();
  Local<Context> ctx = isolate->GetCurrentContext();

  __OnlineSVR *obj = ObjectWrap::Unwrap<__OnlineSVR>(args.Holder());

  double arg = args[0]->ToNumber(isolate)->NumberValue();

  obj->_native->SetEpsilon(arg);
}

void __OnlineSVR::GetEpsilon(const FunctionCallbackInfo<Value> &args)
{
  Isolate *isolate = args.GetIsolate();
  Local<Context> ctx = isolate->GetCurrentContext();

  __OnlineSVR *obj = ObjectWrap::Unwrap<__OnlineSVR>(args.Holder());

  args.GetReturnValue().Set(Number::New(isolate, obj->_native->GetEpsilon()));
}

void __OnlineSVR::SetKernel(const FunctionCallbackInfo<Value> &args)
{
  Isolate *isolate = args.GetIsolate();
  Local<Context> ctx = isolate->GetCurrentContext();

  __OnlineSVR *obj = ObjectWrap::Unwrap<__OnlineSVR>(args.Holder());

  int arg = static_cast<int>(args[0]->ToNumber(isolate)->NumberValue());

  obj->_native->SetKernelType(arg);
}

void __OnlineSVR::GetKernel(const FunctionCallbackInfo<Value> &args)
{
  Isolate *isolate = args.GetIsolate();
  Local<Context> ctx = isolate->GetCurrentContext();

  __OnlineSVR *obj = ObjectWrap::Unwrap<__OnlineSVR>(args.Holder());

  args.GetReturnValue().Set(Number::New(isolate, obj->_native->GetKernelType()));
}

void __OnlineSVR::SetKernelParam(const FunctionCallbackInfo<Value> &args)
{
  Isolate *isolate = args.GetIsolate();
  Local<Context> ctx = isolate->GetCurrentContext();

  __OnlineSVR *obj = ObjectWrap::Unwrap<__OnlineSVR>(args.Holder());

  double arg = args[0]->ToNumber(isolate)->NumberValue();

  obj->_native->SetKernelParam(arg);
}

void __OnlineSVR::GetKernelParam(const FunctionCallbackInfo<Value> &args)
{
  Isolate *isolate = args.GetIsolate();
  Local<Context> ctx = isolate->GetCurrentContext();

  __OnlineSVR *obj = ObjectWrap::Unwrap<__OnlineSVR>(args.Holder());

  args.GetReturnValue().Set(Number::New(isolate, obj->_native->GetKernelParam()));
}

void __OnlineSVR::GetSamplesTrainedNumber(const FunctionCallbackInfo<Value> &args)
{
  Isolate *isolate = args.GetIsolate();
  Local<Context> ctx = isolate->GetCurrentContext();

  __OnlineSVR *obj = ObjectWrap::Unwrap<__OnlineSVR>(args.Holder());

  args.GetReturnValue().Set(Number::New(isolate, obj->_native->GetSamplesTrainedNumber()));
}

void __OnlineSVR::GetSupportSetElementsNumber(const FunctionCallbackInfo<Value> &args)
{
  Isolate *isolate = args.GetIsolate();
  Local<Context> ctx = isolate->GetCurrentContext();

  __OnlineSVR *obj = ObjectWrap::Unwrap<__OnlineSVR>(args.Holder());

  args.GetReturnValue().Set(Number::New(isolate, obj->_native->GetSupportSetElementsNumber()));
}

void __OnlineSVR::GetErrorSetElementsNumber(const FunctionCallbackInfo<Value> &args)
{
  Isolate *isolate = args.GetIsolate();
  Local<Context> ctx = isolate->GetCurrentContext();

  __OnlineSVR *obj = ObjectWrap::Unwrap<__OnlineSVR>(args.Holder());

  args.GetReturnValue().Set(Number::New(isolate, obj->_native->GetErrorSetElementsNumber()));
}

void __OnlineSVR::GetRemainingSetElementsNumber(const FunctionCallbackInfo<Value> &args)
{
  Isolate *isolate = args.GetIsolate();
  Local<Context> ctx = isolate->GetCurrentContext();

  __OnlineSVR *obj = ObjectWrap::Unwrap<__OnlineSVR>(args.Holder());

  args.GetReturnValue().Set(Number::New(isolate, obj->_native->GetRemainingSetElementsNumber()));
}

void __OnlineSVR::GetSupportSetIndexes(const FunctionCallbackInfo<Value> &args)
{
  Isolate *isolate = args.GetIsolate();
  Local<Context> ctx = isolate->GetCurrentContext();

  __OnlineSVR *obj = ObjectWrap::Unwrap<__OnlineSVR>(args.Holder());

  Vector<int> *indices = obj->_native->GetSupportSetIndexes();

  int length = indices->GetLength();

  Handle<Array> array = Array::New(isolate, length);

  for (int index = 0; index < length; index += 1)
  {
    array->Set(index, Integer::New(isolate, indices->GetValue(index)));
  }

  args.GetReturnValue().Set(array);
}

void __OnlineSVR::GetErrorSetIndexes(const FunctionCallbackInfo<Value> &args)
{
  Isolate *isolate = args.GetIsolate();
  Local<Context> ctx = isolate->GetCurrentContext();

  __OnlineSVR *obj = ObjectWrap::Unwrap<__OnlineSVR>(args.Holder());

  Vector<int> *indices = obj->_native->GetErrorSetIndexes();

  int length = indices->GetLength();
  Handle<Array> array = Array::New(isolate, length);

  for (int index = 0; index < length; index += 1)
  {
    array->Set(index, Integer::New(isolate, indices->GetValue(index)));
  }

  args.GetReturnValue().Set(array);
}

void __OnlineSVR::GetRemainingSetIndexes(const FunctionCallbackInfo<Value> &args)
{
  Isolate *isolate = args.GetIsolate();
  Local<Context> ctx = isolate->GetCurrentContext();

  __OnlineSVR *obj = ObjectWrap::Unwrap<__OnlineSVR>(args.Holder());

  Vector<int> *indices = obj->_native->GetRemainingSetIndexes();

  int length = indices->GetLength();
  Handle<Array> array = Array::New(isolate, length);

  for (int index = 0; index < length; index += 1)
  {
    array->Set(index, Integer::New(isolate, indices->GetValue(index)));
  }

  args.GetReturnValue().Set(array);
}