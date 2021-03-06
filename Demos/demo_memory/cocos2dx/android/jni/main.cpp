#include "AppDelegate.h"
#include "platform/android/jni/JniHelper.h"
#include <jni.h>
#include <android/log.h>

#include "cocos2d.h"

using namespace cocos2d;
using namespace ExitGames::Common;


extern "C"
{
	jint JNI_OnLoad(JavaVM* vm, void* reserved)
	{
		JniHelper::setJavaVM(vm);

		return JNI_VERSION_1_4;
	}

	void Java_org_cocos2dx_lib_Cocos2dxRenderer_nativeInit(JNIEnv*  env, jobject thiz, jint w, jint h)
	{
		if(!CCDirector::sharedDirector()->getOpenGLView())
		{
			CCEGLView *view = CCEGLView::sharedOpenGLView();
			view->setFrameSize(w, h);

			AppDelegate *pAppDelegate = new AppDelegate();
			CCApplication::sharedApplication()->run();
		}
		else
		{
			ccGLInvalidateStateCache();
			CCShaderCache::sharedShaderCache()->reloadDefaultShaders();
			ccDrawInit();
			CCTextureCache::reloadAllTextures();
			CCNotificationCenter::sharedNotificationCenter()->postNotification(EVENT_COME_TO_FOREGROUND, NULL);
			CCDirector::sharedDirector()->setGLDefaultValues(); 
		}
	}

	static JavaVM * jvm = NULL;
	static jobject jniAppObj = NULL;

	JNIEXPORT void JNICALL Java_org_cocos2dx_application_ApplicationDemo_nativeInit(JNIEnv * env, jobject obj) 
	{
		env->GetJavaVM(&jvm);
		jniAppObj = env->NewGlobalRef(obj);
	}    
}

void parsePushSubscribeToUserChannel(const JString& userId)
{
	Logger mLogger;
	JNIEnv* env = NULL;
	JavaVMAttachArgs args;
	args.version = JNI_VERSION_1_6; // choose your JNI version
	args.name = NULL; // you might want to give the java thread a name
	args.group = NULL; // you might want to assign the java thread to a ThreadGroup
	int getEnvStat = jvm->GetEnv((void **)&env, JNI_VERSION_1_4);
	if(getEnvStat == JNI_EDETACHED)
	{
		if(jvm->AttachCurrentThread(&env, NULL) != 0)
			EGLOG(DebugLevel::ERRORS, L"Failed to attach");
	}
	else if(getEnvStat == JNI_EVERSION)
		EGLOG(DebugLevel::ERRORS, L"GetEnv: version not supported");
	jstring jstr = env->NewStringUTF(userId.UTF8Representation().cstr());
	jclass clazz = env->FindClass("org/cocos2dx/application/ApplicationDemo");
	jmethodID m = env->GetMethodID(clazz, "parsePushSubscribeToUserChannel", "(Ljava/lang/String;)V");
	env->CallVoidMethod (jniAppObj, m, jstr);
}