#!/bin/sh
install_apk=false
run_apk=false
not_copy=false
ant_debug=true

# options need it?
buildexternalsfromsource=

usage(){
cat << EOF
usage: $0 [options]

build C/C++ code for $APPNAME using Android NDK

OPTIONS:
-d    build debug apk
-i    install apk to phone
-r    run the apk
-a    do not copy asset to asset directory
-s    Build externals from source. this is build cocos2dx related lib src
-h    show this help
EOF
}




NDK=`which ndk-build`
NDK_ROOT=`dirname $NDK`


DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
# ... use paths relative to current directory
COCOS2DX_ROOT="$DIR/.."
APP_ROOT="$DIR/.."
APP_ANDROID_ROOT="$DIR"
echo "NDK_ROOT = $NDK_ROOT"
echo "COCOS2DX_ROOT = $COCOS2DX_ROOT"
echo "APP_ROOT = $APP_ROOT"
echo "APP_ANDROID_ROOT = $APP_ANDROID_ROOT"


if [ "$#" -gt 0 -a "$1" = "-h" ]; then
   usage
   exit 0
fi
if [ "$#" -gt 0 -a "$1" = "-d" ]; then
    shift
#    sign_apk=true
    ant_debug=true
fi

if [ "$#" -gt 0 -a "$1" = "-i" ]; then
    shift
    ant_debug=true
    install_apk=true
fi

if [ "$#" -gt 0 -a "$1" = "-r" ]; then
    shift
	ant_debug=false
    install_apk=true
fi

if [ "$#" -gt 0 -a "$1" = "-a" ]; then
    shift
    not_copy=true
fi


if $not_copy ; then 
	true; #do nothing
else
echo "We copy assets every time. if you do not want copy"
echo "use ./build_native.sh -a to disable it"
	./copy_asset.sh

fi


if uname -s | grep -i "darwin" > /dev/null ; then
    if [[ "$buildexternalsfromsource" ]]; then
		echo "Building external dependencies from source"
		"$NDK_ROOT"/ndk-build -C "$APP_ANDROID_ROOT" $* \
        "NDK_MODULE_PATH=${COCOS2DX_ROOT}:${COCOS2DX_ROOT}/cocos2dx/cocos2dx/platform/third_party/android/source"
	else
		echo "Using prebuilt externals"
		"$NDK_ROOT"/ndk-build -C "$APP_ANDROID_ROOT" $* \
        "NDK_MODULE_PATH=${COCOS2DX_ROOT}:${COCOS2DX_ROOT}/cocos2dx/cocos2dx/platform/third_party/android/prebuilt"
	fi
fi
if uname -s | grep -i "cygwin" >/dev/null ; then
	NDKBUILD="$NDK_ROOT"/ndk-build.cmd
	NDKBUILD=`cygpath -d $NDKBUILD`
	cmd /c win_build.bat $NDKBUILD

fi
  




$ant_debug && ant debug 
$install_apk && echo "install apk to phone..." && \
		 adb install -r bin/Hellopet-debug.apk  && \
		$run_apk && { \
		ActivityName="com.taomee.adventure/.adventure"; \
		RUN_APK="adb shell am start -n $ActivityName" ; \
		echo "Running $ActivityName on the USB-connected device:" ; \
		echo "$RUN_APK" ; \
		eval $RUN_APK ; \
	}