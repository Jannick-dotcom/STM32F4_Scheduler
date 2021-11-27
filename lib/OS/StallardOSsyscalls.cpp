#include "StallardOS.hpp"


void StallardOS::call_pendPendSV(void){
    __ASM volatile("svc 2");
}