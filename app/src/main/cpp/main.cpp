#include <iostream>
#include "AndroidNetworkLogic.h"

#include "../../../../../../../Users/erikking/Library/Android/sdk/ndk/21.0.6113669/toolchains/llvm/prebuilt/darwin-x86_64/sysroot/usr/include/jni.h"

extern "C"
{
JNIEXPORT void JNICALL Java_demo_android_loadBalancing_MainActivity_startDemo(JNIEnv* env, jobject obj);
JNIEXPORT void JNICALL Java_demo_android_loadBalancing_MainActivity_createGame(JNIEnv* env, jobject obj);
JNIEXPORT void JNICALL Java_demo_android_loadBalancing_MainActivity_createGameDirectAllToAll(JNIEnv* env, jobject obj);
JNIEXPORT void JNICALL Java_demo_android_loadBalancing_MainActivity_createGameDirectMasterToAll(JNIEnv* env, jobject obj);
JNIEXPORT void JNICALL Java_demo_android_loadBalancing_MainActivity_joinRandomGame(JNIEnv* env, jobject obj);
JNIEXPORT void JNICALL Java_demo_android_loadBalancing_MainActivity_leaveGame(JNIEnv* env, jobject obj);
JNIEXPORT void JNICALL Java_demo_android_loadBalancing_MainActivity_gameRun(JNIEnv* env, jobject obj);
};

AndroidNetworkLogic* gGameLogic = nullptr;

extern "C" JNIEXPORT void JNICALL Java_demo_android_loadBalancing_MainActivity_startDemo(JNIEnv* env, jobject obj)
{
    jclass clazz = env->FindClass("demo/android/loadBalancing/MainActivity");
    jmethodID addTextMethod = env->GetMethodID(clazz, "addText", "(Ljava/lang/String;)V");
    jmethodID stateUpdateMethod = env->GetMethodID(clazz, "stateUpdate", "(I)V");

    std::wcout << "where INPUT_0";
    gGameLogic = new AndroidNetworkLogic(env, obj, addTextMethod, stateUpdateMethod);
}

extern "C" JNIEXPORT void JNICALL Java_demo_android_loadBalancing_MainActivity_createGame(JNIEnv* env, jobject obj)
{
    std::wcout << "where INPUT_1";
    gGameLogic->setLastInput(INPUT_1);
}

extern "C" JNIEXPORT void JNICALL Java_demo_android_loadBalancing_MainActivity_createGameDirectAllToAll(JNIEnv* env, jobject obj)
{
    std::wcout << "where INPUT_3";
    gGameLogic->setLastInput(INPUT_3);
}

extern "C" JNIEXPORT void JNICALL Java_demo_android_loadBalancing_MainActivity_createGameDirectMasterToAll(JNIEnv* env, jobject obj)
{
    std::wcout << "where INPUT_4";
    gGameLogic->setLastInput(INPUT_4);
}

extern "C" JNIEXPORT void JNICALL Java_demo_android_loadBalancing_MainActivity_joinRandomGame(JNIEnv* env, jobject obj)
{
    std::wcout << "where INPUT_2";
    gGameLogic->setLastInput(INPUT_2);
}

extern "C" JNIEXPORT void JNICALL Java_demo_android_loadBalancing_MainActivity_leaveGame(JNIEnv* env, jobject obj)
{
    std::wcout << "where INPUT_1";
    gGameLogic->setLastInput(INPUT_1);
}

extern "C" JNIEXPORT void JNICALL Java_demo_android_loadBalancing_MainActivity_gameRun(JNIEnv* env, jobject obj)
{

    std::wcout << "where run";
    gGameLogic->run();
}