workspace "HelloWorld"
   configurations { "Debug", "Release" }

project "hello"
   kind "ConsoleApp"
   language "C++"
   targetdir "bin/%{cfg.buildcfg}"

   files {
          "**.h",
          "**.cpp",
         }
   
   links {
      "raylib"
   }

   filter "configurations:Debug"
      defines { "DEBUG" }
      symbols "On"

   filter "configurations:Release"
      defines { "NDEBUG" }
      optimize "On"
