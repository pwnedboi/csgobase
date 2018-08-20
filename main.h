/*
 *  main.h
 */
#pragma once


#include <stdio.h>
#include <string>
#include <deque>
#include <vector>
#include <map>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <codecvt>  // codecvt_utf8 // string to wchar
#include <dlfcn.h>
#include <zconf.h>  // Byte
#include <sys/stat.h>
#include <sys/mman.h> // used in protect_addr
#include <mach-o/dyld_images.h>

using namespace std;

#include "SDK.h"

#include "settings.h"

#include "global.h"

#include "renderer.h"

#include "util.h"
#include "util_math.h"

#include "hooks.h"
