Any .so libraries you have can go here. Combined with the gradle file provided,
these files will be copied to the Android native lib directory. Accessible with
`context.getApplicationInfo().nativeLibraryDir`

You must keep the arch specific folders, as you can see, this one is `arm64-v8a`
