#include "libsvr.h";

using namespace std;
using namespace v8;
using namespace onlinesvr;

using v8::Array;
using v8::Context;
using v8::Function;
using v8::FunctionCallbackInfo;
using v8::FunctionTemplate;
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

    std::cout << length;

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