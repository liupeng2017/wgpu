-- 设置工程名
set_project("openui")

-- 设置工程版本
set_version("0.0.1", {build = "%Y%m%d%H%M"})
set_license("LGPL3")
-- set warning all as error
set_warnings("none", "error", "allextra", "pedantic")
set_policy("check.auto_ignore_flags", false)
-- set language: c99, c++11
set_languages("c99", "cxx20")  -- "clatest", "cxxlatest"
add_cxflags("clang::-Wno-deprecated-declarations -Wno-unknown-attributes")
add_cxflags("clang::-fcolor-diagnostics", "clang::-fansi-escape-codes", "gcc::-fdiagnostics-color=always")
-- add_cxflags("-Wno-gnu-statement-expression-from-macro-expansion -Wno-gnu-statement-expression", {tools = { "clang", "gcc" })
set_optimize("fastest")

add_cxxflags("clang::-fexperimental-library", {force = true}) -- Pour avoir std::jthread
add_cxxflags("cl::/EHsc", {force = true}) -- Pour avoir std::jthread

if is_plat("windows") and is_config("cxx", "cl") and not is_plat("mingw") then
    set_runtimes(is_mode("debug") and "MDd" or "MD")
    add_defines("NOMINMAX", "VC_EXTRALEAN", "WIN32_LEAN_AND_MEAN", { public = true })
    add_cxflags("/wd4251", {force = true}) -- ‘identifier’ : class ‘type’ needs to have dll-interface to be used by clients of class ‘type2’
elseif is_plat("linux", "macosx") then
    add_syslinks("pthread", "dl")
end

toolchain("xcode")
    on_check("macosx", function (toolchain)
        -- xcode下启用帧捕获以进行 GPU 调试
        add_defines("XCODE_GENERATE_SCHEME=ON", "XCODE_SCHEME_ENABLE_GPU_FRAME_CAPTURE_MODE=Metal")
    end)

    on_load(function (toolchain)
        ---- set toolset
        --toolchain:set("toolset", "cc", "clang")
        --toolchain:set("toolset", "ld", "clang++")
        --
        ---- init flags
        --local march = toolchain:is_arch("x86_64", "x64") and "-m64" or "-m32"
        --toolchain:add("cxflags", march)
        --toolchain:add("ldflags", march)
        --toolchain:add("shflags", march)
    end)
toolchain_end()

includes("thirdparty")
includes("src")

--target("wgpu_native")
--    webgpu_root = os.projectdir().."/cmake/webgpu/cmake-build-debug-visual-studio/_deps/webgpu-backend-wgpu-src"
--    set_kind("static") -- 或者 "staticlib", "sharedlib" 等
--    add_includedirs(webgpu_root.."/include", {public = true})
--    add_linkdirs(webgpu_root.."/bin/windows-x86_64")
--    add_links("wgpu_native.dll.lib")
--    --set_extension(".dll")
--    -- on_load(function(target)
--    on_install("windows", function (package)
--        os.cp("include", package:installdir())
--        os.cp("lib/$(arch)/*.lib", package:installdir("lib"))
--        os.cp("lib/$(arch)/*.dll", package:installdir("lib"))
--    end)

set_policy("package.fetch_only", true)
-- add_repositories("xmake-repo https://github.com/MorganCaron/CppUtils")
-- add_requires("CppUtils")

target("openui")
    set_kind("binary")
    add_files("main.cpp")
    add_deps("app")
    add_deps("window")
    add_deps("glm")
    add_deps("glfw")
    -- add_deps("wgpu_native")
    add_deps("webgpu")
    add_files("*.cpp", {defines = "OPEN_WINDOW_API", includes = "."})

    -- webgpu
    -- add_includedirs("webgpu/include", {public = true})
    -- add_linkdirs("webgpu/lib/")
    add_links("wgpu_native")

    -- github
    -- add_packages("CppUtils", {public = true})


