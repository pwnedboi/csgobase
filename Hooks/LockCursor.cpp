//
//  LockCursor.cpp
//  csgobase
//
//  Created by James Henson on 2/3/19.
//  Copyright © 2019 pwned. All rights reserved.
//

#include "../main.h"

void LockCursor_hk(void* thisptr) {
    if(set.menu) {
        pSurface->UnlockCursor();
    } else {
        surfaceVMT->GetOriginalMethod<oLockCursor>(LockCursorIndex)(thisptr);
    }
}
