FROM mingc/android-build-box:latest

ENV ANDROID_NDK_ROOT=$ANDROID_HOME/ndk-bundle  ANDROID_NDK_HOME=$ANDROID_NDK_ROOT
   
RUN apt-get update
RUN apt-get install -y yes ninja-build

RUN yes | sdkmanager "ndk-bundle"
RUN yes | sdkmanager "ndk"
RUN yes | sdkmanager "cmake"

RUN mkdir -p /build/buildfiles/
RUN mkdir -p /build/scr/
WORKDIR /build/buildfiles/

COPY files /build/buildfiles/
COPY get_dependencies.sh /build/buildfiles/

RUN sh ./get_dependencies.sh