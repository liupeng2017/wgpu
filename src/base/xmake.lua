
target("baseWindow")
    set_kind("static")
    add_includedirs(".", {public = true})
    add_files("*.cpp", {defines = "OPEN_BASE_WINDOW_API", includes = "."})