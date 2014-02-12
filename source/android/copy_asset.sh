APPNAME="Adventure"
# options
buildexternalsfromsource=

usage(){
cat << EOF
usage: $0 [options]

Build C/C++ code for $APPNAME using Android NDK

OPTIONS:
-s	Build externals from source
-h	this help
EOF
}
while getopts "sh" OPTION; do
case "$OPTION" in
s)
buildexternalsfromsource=1
;;
h)
usage
exit 0
;;
esac
done

# paths

NDK=`which ndk-build`
NDK_ROOT=`dirname $NDK`

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
# ... use paths relative to current directory
COCOS2DX_ROOT="$DIR/.."
APP_ROOT="$DIR/.."
APP_ANDROID_ROOT="$DIR"



# make sure assets is exist
if [ -d "$APP_ANDROID_ROOT"/assets ]; then
    rm -rf "$APP_ANDROID_ROOT"/assets
fi

mkdir "$APP_ANDROID_ROOT"/assets

# copy resources
for file in "$APP_ROOT"/Resources/*
do
if [ -d "$file" ]; then
    cp -rf "$file" "$APP_ANDROID_ROOT"/assets
fi

if [ -f "$file" ]; then
    cp "$file" "$APP_ANDROID_ROOT"/assets
fi
done

#cp "$APP_ANDROID_ROOT"/libs/libcrashme/libcrashme.so "$APP_ANDROID_ROOT"/libs/armeabi

find "$APP_ANDROID_ROOT"/assets -name .svn -print0 | xargs -0 rm -r -f

# remove test_image_rgba4444.pvr.gz

