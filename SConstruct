#!/usr/bin/env python

EnsureSConsVersion(0, 98, 1)

# System
import atexit
import glob
import os
import pickle
import sys
import time
from collections import OrderedDict

# Local
import methods
import gles_builders
from platform_methods import run_in_subprocess

# scan possible build platforms

platform_list = []  # list of platforms
platform_opts = {}  # options for each platform
platform_flags = {}  # flags for each platform

active_platforms = []
active_platform_ids = []
platform_exporters = []
platform_apis = []

time_at_start = time.time()

custom_tools = ["default"]

# We let SCons build its default ENV as it includes OS-specific things which we don't
# want to have to pull in manually.
# Then we prepend PATH to make it take precedence, while preserving SCons' own entries.
env_base = Environment(tools=custom_tools)
env_base.PrependENVPath("PATH", os.getenv("PATH"))
env_base.PrependENVPath("PKG_CONFIG_PATH", os.getenv("PKG_CONFIG_PATH"))

if "TERM" in os.environ:  # Used for colored output.
    env_base["ENV"]["TERM"] = os.environ["TERM"]

env_base.disabled_modules = []
env_base.use_ptrcall = False
env_base.module_version_string = ""
env_base.msvc = False

env_base.__class__.disable_module = methods.disable_module

env_base.__class__.add_module_version_string = methods.add_module_version_string

env_base.__class__.add_source_files = methods.add_source_files
env_base.__class__.use_windows_spawn_fix = methods.use_windows_spawn_fix
env_base.__class__.split_lib = methods.split_lib

env_base.__class__.add_shared_library = methods.add_shared_library
env_base.__class__.add_library = methods.add_library
env_base.__class__.add_program = methods.add_program
env_base.__class__.CommandNoCache = methods.CommandNoCache
env_base.__class__.disable_warnings = methods.disable_warnings

env_base["x86_libtheora_opt_gcc"] = False
env_base["x86_libtheora_opt_vc"] = False

# avoid issues when building with different versions of python out of the same directory
env_base.SConsignFile(".sconsign{0}.dblite".format(pickle.HIGHEST_PROTOCOL))

env_base.Prepend(CPPPATH=["#"])

# Build options

env = env_base.Clone()

# Environment flags
CCFLAGS = env.get("CCFLAGS", "")
env["CCFLAGS"] = ""
env.Append(CCFLAGS=str(CCFLAGS).split())

CFLAGS = env.get("CFLAGS", "")
env["CFLAGS"] = ""
env.Append(CFLAGS=str(CFLAGS).split())

CXXFLAGS = env.get("CXXFLAGS", "")
env["CXXFLAGS"] = ""
env.Append(CXXFLAGS=str(CXXFLAGS).split())

LINKFLAGS = env.get("LINKFLAGS", "")
env["LINKFLAGS"] = "-lm"
env.Append(LINKFLAGS=str(LINKFLAGS).split())

methods.no_verbose(sys, env)

scons_cache_path = os.environ.get("SCONS_CACHE")
if scons_cache_path != None:
    CacheDir(scons_cache_path)
    print("Scons cache enabled... (path: '" + scons_cache_path + "')")

Export("env")

SConscript("core/SCsub")
SConscript("main/SCsub")


