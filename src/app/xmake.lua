
add_requires("glfw")

target("app")
    set_kind("static")
    add_includedirs(".", {public = true})
    add_files("*.cpp", {defines = "OPEN_APPLICATION_API", includes = "."})
    add_deps("baseWindow")
    add_packages("glfw")