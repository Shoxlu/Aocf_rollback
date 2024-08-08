#pragma once
#include <windows.h>
#include <winuser.h>
#include <stdint.h>
#include <stdio.h>
#include <assert.h>
#include "AllocMan.h"
#include <squirrel.h>
#include <sqrat.h>
#include "PatchUtils.h"
#include "util.h"
extern HSQUIRRELVM* VM;
size_t waitime = 8;



void GetSqVM_(){
    VM = (HSQUIRRELVM*)0x4DACE4_R; 
}


void RollbackUpdate(){
    
    if(GetKeyState(VK_SHIFT) & 0x8000 && waitime == 0){
        printf("Rollback ! \n");
        rollback_allocs(31);
        waitime = 31;
    }
    if(waitime > 0){
        waitime--;
    }
    //tick_allocs();
    //tick_allocs();
}

void hook_initialization(){
    GetSqVM_();
    //sq_throwerror(*VM,_SC("Hi"));
    HSQUIRRELVM vm = *VM;
    Sqrat::RootTable rtable(vm);
    Sqrat::Table rollback_table(vm);
    rtable.Bind(_SC("rollback"), rollback_table);
    rollback_table.Func(_SC("RollbackUpdate"), RollbackUpdate);

    printf("Hook init end \n");
    
}

void rollback_test_mod_init(){
    uintptr_t addr = 0x79443_R;
    hotpatch_jump((void*)addr, (void*)hook_initialization);
}