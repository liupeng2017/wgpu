target("webgpu")
    set_kind("static") -- 或者 "staticlib", "sharedlib" 等
    add_includedirs("include", {public = true})
    add_includedirs("include/webgpu", {public = true})
    add_linkdirs("lib")
    -- add_rules("win.sdk.application")
    add_links("wgpu_native")
    -- kernel32.lib user32.lib gdi32.lib winspool.lib shell32.lib ole32.lib oleaut32.lib uuid.lib comdlg32.lib advapi32.lib
    add_syslinks("opengl32", "user32", "gdi32", "ws2_32", "d3d11", "d3dcompiler", "ntdll", "ole32", "wsock32")
    add_syslinks("IPHLPAPI", "Psapi", "Userenv", "oleaut32", "Advapi32")
    add_files("*.cpp", {defines = "WEBGPU_API", includes = "."})