#pragma once

#define XXX KC_NO
#include "quantum.h"

#define LAYOUT_all( \
    K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C, K0D, K0E, K0F, K0G, K0H, \
	K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, K1D, K1E, K1F, K1G, K1H, \
    K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B,      K2D, K2E, K2F, K2G,      \
    K30, K31, K32, K33, K34, K35, K36, K37, K38,      K3A, K3B, K3C, K3D, K3E, K3F, K3G,      \
    K40, K41, K42,                K46,      K48,      K4A, K4B, K4C, K4D, K4E, K4F, K4G       \
    ) \
{ \
    { K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C, K0D, K0E, K0F, K0G, K0H }, \
    { K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, K1D, K1E, K1F, K1G, K1H },  \
    { K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, XXX, K2D, K2E, K2F, K2G, XXX },  \
    { K30, K31, K32, K33, K34, K35, K36, K37, K38, XXX, K3A, K3B, K3C, K3D, K3E, K3F, K3G, XXX },  \
    { K40, K41, K42, XXX, XXX, XXX, K46, XXX, K48, XXX, K4A, K4B, K4C, K4D, K4E, K4F, K4G, XXX }  \
}
