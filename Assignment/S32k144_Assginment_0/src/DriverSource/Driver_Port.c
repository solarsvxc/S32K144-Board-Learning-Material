#include "DriverHeader/Driver_Common.h"
#include "DriverHeader/Driver_Port.h"


// PCC CGC enable
void PCC_Enable(uint32_t pcc_portx_index){
    IP_PCC->PCCn[pcc_portx_index] |= PCC_PCCn_CGC_MASK;
}
// PCC CGC disable
void PCC_Disable(uint32_t pcc_portx_index){
    IP_PCC->PCCn[pcc_portx_index] |= PCC_PCCn_CGC_MASK;
}



