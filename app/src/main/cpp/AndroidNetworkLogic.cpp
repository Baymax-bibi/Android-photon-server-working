#include <string.h>
#include <android/log.h>

#include "AndroidNetworkLogic.h"
#include "../../../../../../../Users/erikking/Library/Android/sdk/ndk/21.0.6113669/toolchains/llvm/prebuilt/darwin-x86_64/sysroot/usr/include/jni.h"

AndroidNetworkLogic::AndroidNetworkLogic(JNIEnv* env, jobject obj, jmethodID writeMethod, jmethodID stateUpdateMethod)
        : NetworkLogic(this)
        , mEnv(env)
        , mObj(env->NewGlobalRef(obj))
        , mWriteMethod(writeMethod)
        , mStateUpdateMethod(stateUpdateMethod)
{
    registerForStateUpdates(this);
}

AndroidNetworkLogic::~AndroidNetworkLogic()
{
    mEnv->DeleteGlobalRef(mObj);
}

void AndroidNetworkLogic::write(const ExitGames::Common::JString& str)
{
    jstring jstr = mEnv->NewStringUTF(str.UTF8Representation().cstr());
    mEnv->CallVoidMethod(mObj, mWriteMethod, jstr);
    mEnv->DeleteLocalRef(jstr);
}

void AndroidNetworkLogic::writeLine(const ExitGames::Common::JString& str)
{
    write((str+'\n').UTF8Representation().cstr());
}

void AndroidNetworkLogic::debugReturn(int debugLevel, const ExitGames::Common::JString& string)
{
    OutputListener::debugReturn(debugLevel, string);
}

void AndroidNetworkLogic::stateUpdate(State newState)
{
    mEnv->CallVoidMethod(mObj, mStateUpdateMethod, newState);
}