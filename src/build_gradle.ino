plugins {
    id "com.android.application"
    // START: FlutterFire Configuration
    id 'com.google.gms.google-services'
    // END: FlutterFire Configuration
    id "org.jetbrains.kotlin.android"
    // The Flutter Gradle Plugin must be applied after the Android and Kotlin Gradle plugins.
    id "dev.flutter.flutter-gradle-plugin"

}

android {
    namespace = ""
    compileSdkVersion 34
    ndkVersion = flutter.ndkVersion

    compileOptions {
        sourceCompatibility = JavaVersion.VERSION_1_8
        targetCompatibility = JavaVersion.VERSION_1_8
    }

    defaultConfig {
        // TODO: Specify your own unique Application ID (https://developer.android.com/studio/build/application-id.html).
        applicationId = ""
        // You can update the following values to match your application needs.
        // For more information, see: https://docs.flutter.dev/deployment/android#reviewing-the-gradle-build-configuration.
        minSdkVersion 23
        targetSdkVersion 33
        versionCode 1
        versionName "1.0"
    }

    dependencies {
        implementation platform('com.google.firebase:firebase-bom:31.2.2')
        implementation 'com.google.firebase:firebase-analytics'
        implementation 'com.google.firebase:firebase-auth'
        implementation 'com.google.firebase:firebase-firestore'
    }
 
}
