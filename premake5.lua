workspace "Model Transformations"
    location "Generated"
    language "C++"
    architecture "x86_64"

    configurations {"Debug", "Release"}

    filter {"configurations:Debug"}
        symbols "On"
    filter {"configurations:Release"}
        optimize "On"
    filter { }

    targetdir ("Build/Bin/%{prj.name}/%{cfg.longname}")
    objdir ("Build/Bin/%{prj.name}/%{cfg.longname}")

function includeGLFW()
    includedirs {"Libraries/GLFW/Include", "Libraries/GLEW/include", "Libraries/GLM/include"}
end

function linkGLFW()
    libdirs "Libraries/GLFW/Lib"
    libdirs "Libraries/GLEW/lib/Release/x64"

    filter "kind:not StaticLib"
        links "glfw3"
    filter {}
    filter "kind:not StaticLib"
        links "glew32"
    filter {}
end


project "App"
    kind "WindowedApp"
    files "Projects/App/**"

    includeGLFW()
    linkGLFW()

    filter {"system:windows"}
        links {"OpenGL32"}
    filter {"system:not windows"}
        links {"GL"}