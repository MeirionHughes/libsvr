#pragma once
#ifndef __LIBSVR__
#define __LIBSVR__

#include <nan.h>
#include <node.h>
#include "./lib/OnlineSVR.h"

using namespace onlinesvr;

class __OnlineSVR : public node::ObjectWrap {
 public:
  static void Init(v8::Local<v8::Object> exports);

 private:
  explicit __OnlineSVR(double value = 0);
  ~__OnlineSVR();

  static void New(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void Train(const v8::FunctionCallbackInfo<v8::Value> &args);
  static void Predict(const v8::FunctionCallbackInfo<v8::Value> &args);
  static v8::Persistent<v8::Function> constructor;

  double value_;

  OnlineSVR* _native;
};


#endif

