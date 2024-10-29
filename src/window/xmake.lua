
--add_requires("glfw")
add_requires("vulkansdk")

-- Define a custom rule to compile GLSL shaders to SPIR-V
rule("compile_shaders")
    set_extensions(".vert", ".frag")

    on_build_file(function (target, sourcefile)
        print("Compiling shader for file: " .. sourcefile)
        local outputdir = path.join(target:targetdir(), "shaders")
        print("Creating output directory: " .. outputdir)
        os.mkdir(outputdir)
        local outputfile = path.join(outputdir, path.filename(sourcefile) .. ".spv")
        print("Output file: " .. outputfile)

        -- Execute the command and capture the result
        local compile_command = {"-V", sourcefile, "-o", outputfile}
        local ret = os.execv("glslangValidator", compile_command)
        if ret ~= 0 then
            os.raise("Failed to compile shader: " .. sourcefile .. " with error code: " .. ret)
        else
            print("Shader compiled successfully: " .. outputfile)
        end
    end)

    on_clean(function (target)
        local outputdir = path.join(target:targetdir(), "shaders")
        print("Cleaning directory: " .. outputdir)
        os.rmdir(outputdir)
    end)
rule_end()

--add_deps("cmake")
--on_install(function (package)
--    import("package.tools.cmake").install(package, {"-Dxxx=ON"})
--end)

--add_requires("cmake::webgpu", {configs = {alias = "webgpu", moduledirs = os.projectdir().."/cmake/", link_libraries = {"webgpu"}}})

package("webgpu")
    add_deps("cmake")
    set_sourcedir(path.join(os.projectdir(), "/cmake/webgpu"))
    set_policy("package.install_always", true)
    --set_policy("package.download.http_headers", "TEST1: foo", "TEST2: bar")
    add_moduledirs(os.projectdir().."/cmake/webgpu")
    --set_base("webgpu")
    --add_urls("https://github.com/eliemichel/WebGPU-distribution", {alias = "github"})
    --add_versions("github:0.19", "wgpu-static-v0.19.4.1")
    on_install(function (package)
        --local configs = {envs = {CMAKE_PREFIX_PATH = os.projectdir().."/cmake/webgpu"}, moduledirs = os.projectdir().."/cmake/webgpu", link_libraries = {"webgpu"}}
        local configs = {}
        table.insert(configs, "-DCMAKE_BUILD_TYPE=" .. (package:debug() and "Debug" or "Release"))
        table.insert(configs, "-DBUILD_SHARED_LIBS=" .. (package:config("shared") and "ON" or "OFF"))
        import("package.tools.cmake").install(package, configs)
    end)
package_end()

-- add_requires("webgpu")

target("vulkan")
    vulkan_root = "D:/program/vulkan1_3_290"
    set_kind("static") -- 或者 "staticlib", "sharedlib" 等
    add_includedirs(vulkan_root.."/Include", {public = true})
    add_linkdirs(vulkan_root.."/Lib")
    add_links("vulkan-1")

target("window")
    set_kind("static")
    add_defines("WGPU_SHARED_LIBRARY")
    add_includedirs(".", {public = true})
    add_files("*.cpp", {defines = "OPEN_WINDOW_API", includes = "."})
    add_deps("baseWindow")
    add_deps("vulkan")
    add_deps("glfw")
    -- add_packages("webgpu")
    -- add_files("shaders/spinning_circle.vert", "shaders/spinning_circle.frag")
    -- add_includedirs("include/Vulkan", "include")
    add_packages("vulkansdk")
    -- add_rules("compile_shaders")
