include "Dependencies.lua"

workspace "MemoryFS"
   architecture "x64"
   startproject "MemoryFS"
   configurations { "Debug", "Release" }

outputdir = "%{cfg.system}-%{cfg.architecture}-%{cfg.buildcfg}"

group "Dependencies"
   include "Dependencies/spdlog"
group ""

include "project"
