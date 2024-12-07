QT += quick svg multimedia
CONFIG += c++17
VERSION = 1.0.0.0

HEADERS += \
    src/gamecontroller.h \
    src/gamehistory.h

SOURCES += \
    src/gamehistory.cpp \
    src/main.cpp \
    src/gamecontroller.cpp

RESOURCES += qml.qrc

android {
    DISTFILES += \
        android/AndroidManifest.xml \
        android/src/org/qtproject/example/activityhandler/CustomActivity.java \
        android/res/layout/second_activity.xml \
        android/res/values/strings.xml

    ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android
}

DISTFILES += \
    android/AndroidManifest.xml \
    android/build.gradle \
    android/gradle.properties \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew \
    android/gradlew.bat \
    android/res/values/libs.xml
