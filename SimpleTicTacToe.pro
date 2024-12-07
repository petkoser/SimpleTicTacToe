QT += quick svg multimedia
CONFIG += c++17
VERSION = 1.1.0.0

HEADERS += \
    src/gamecontroller.h \
    src/gamehistory.h

SOURCES += \
    src/gamehistory.cpp \
    src/main.cpp \
    src/gamecontroller.cpp

RESOURCES += qml.qrc

DISTFILES += \
    android/AndroidManifest.xml \
    android/build.gradle \
    android/gradle.properties \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew \
    android/gradlew.bat \
    android/res/values/libs.xml

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android
