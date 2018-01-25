#pragma once
#ifndef __LIBSVR__
#define __LIBSVR__

#include <nan.h>
#include <node.h>
#include "./lib/OnlineSVR.h"

using namespace onlinesvr;

class __OnlineSVR : public node::ObjectWrap
{
public:
  static void Init(v8::Local<v8::Object> exports);

private:
  explicit __OnlineSVR(double value = 0);
  ~__OnlineSVR();

  static void New(const v8::FunctionCallbackInfo<v8::Value> &args);

  static void Train(const v8::FunctionCallbackInfo<v8::Value> &args);
  static void Predict(const v8::FunctionCallbackInfo<v8::Value> &args);
  static void Forget(const v8::FunctionCallbackInfo<v8::Value> &args);

  static void Clear(const v8::FunctionCallbackInfo<v8::Value> &args);

  static void SetC(const v8::FunctionCallbackInfo<v8::Value> &args);
  static void GetC(const v8::FunctionCallbackInfo<v8::Value> &args);
  static void SetEpsilon(const v8::FunctionCallbackInfo<v8::Value> &args);
  static void GetEpsilon(const v8::FunctionCallbackInfo<v8::Value> &args);
  static void SetKernel(const v8::FunctionCallbackInfo<v8::Value> &args);
  static void GetKernel(const v8::FunctionCallbackInfo<v8::Value> &args);
  static void SetKernelParam(const v8::FunctionCallbackInfo<v8::Value> &args);
  static void GetKernelParam(const v8::FunctionCallbackInfo<v8::Value> &args);

  static void GetSamplesTrainedNumber(const v8::FunctionCallbackInfo<v8::Value> &args);
  static void GetSupportSetElementsNumber(const v8::FunctionCallbackInfo<v8::Value> &args);
  static void GetErrorSetElementsNumber(const v8::FunctionCallbackInfo<v8::Value> &args);
  static void GetRemainingSetElementsNumber(const v8::FunctionCallbackInfo<v8::Value> &args);

  static void GetSupportSetIndexes(const v8::FunctionCallbackInfo<v8::Value> &args);
  static void GetErrorSetIndexes(const v8::FunctionCallbackInfo<v8::Value> &args);
  static void GetRemainingSetIndexes(const v8::FunctionCallbackInfo<v8::Value> &args);

  static v8::Persistent<v8::Function> constructor;

  double value_;

  OnlineSVR *_native;
};

#endif
