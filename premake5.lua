workspace "Cracked"
   configurations { "Debug", "Release" }

project "cracked"
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

   postbuildcommands {
        'cp -r assets "%{cfg.targetdir}/assets"'
    } 

   filter "configurations:Debug"
      defines { "DEBUG" }
      symbols "On"

   filter "configurations:Release"
      defines { "NDEBUG" }
      optimize "On"
