// =============== main.h =============== \\
//
//  - All the main includes are included here
//  -
//  -
//
#pragma once


#include <stdio.h>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <deque>
#include <unordered_map>
#include <map>
#include <dlfcn.h>
#include <libproc.h>
#include <codecvt>
#include <iomanip>
#include <zconf.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <mach-o/dyld_images.h>

using namespace std;

#include "SDK/SDK.h"

#include "Interfaces/Interfaces.h"

#include "Variables/settings.h"

#include "Render/renderer.h"

#include "Utilities//util.h"
#include "Utilities//util_math.h"

#include "Hooks/hooks.h"
