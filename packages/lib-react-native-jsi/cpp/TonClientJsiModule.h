#pragma once

#include <jsi/jsilib.h>
#include <jsi/jsi.h>
#include <ReactCommon/CallInvoker.h>

#include "NativeModules.h"

using namespace facebook;

namespace tonlabs
{
  class TonClientJsiModule : public facebook::react::SchemaCxxSpecJSI
  {
  public:
    jsi::Value setResponseHandler(
        jsi::Runtime &rt,
        const jsi::Function &responseHandler) override;

    jsi::Value createContext(
        jsi::Runtime &rt,
        const jsi::String &configJson,
        const jsi::Function &onResult) override;

    jsi::Value destroyContext(
        jsi::Runtime &rt,
        const jsi::Value &context) override;

    jsi::Value sendRequest(
        jsi::Runtime &rt,
        const jsi::Value &context,
        const jsi::Value &requestId,
        const jsi::String &functionName,
        const jsi::String &functionParamsJson) override;

    TonClientJsiModule(jsi::Runtime &runtime, std::shared_ptr<facebook::react::CallInvoker> jsInvoker)
        : facebook::react::SchemaCxxSpecJSI(jsInvoker), runtime_(runtime), jsCallInvoker_(jsInvoker){};

  private:
    jsi::Runtime &runtime_;
    std::shared_ptr<facebook::react::CallInvoker> jsCallInvoker_;
    std::shared_ptr<jsi::Function> responseHandler_;
  };

  typedef struct
  {
    uint32_t requestId;
    TonClientJsiModule *jsiModule;
  } request_data_t;

} // namespace tonlabs
