#include "drivers/common/fsl_common.h"
#include "dcd/dcd_retention.h"

#include "ddr_table.h"

struct dram_cfg_param dcd_table[] = {
	{DCD_WRITE, 0x41a40208U, 0x1U},
	{DCD_WRITE, 0x41d00208U, 0x1U},
	{DCD_WRITE, 0x41a40040U, 0xBU},
	{DCD_WRITE, 0x41d00040U, 0xBU},
	{DCD_WRITE, 0x41a40204U, 0x1U},
	{DCD_WRITE, 0x41d00204U, 0x1U},
	{DCD_WRITE, 0x5c000000U, 0xC1080020U},
	{DCD_WRITE, 0x5c000020U, 0x00000213U},
	{DCD_WRITE, 0x5c000024U, 0x0186A000U},
	{DCD_WRITE, 0x5c000050U, 0x0021F000U},
	{DCD_WRITE, 0x5c000064U, 0x006100E0U},
	{DCD_WRITE, 0x5c0000d0U, 0x4003061CU},
	{DCD_WRITE, 0x5c0000d4U, 0x009E0000U},
	{DCD_WRITE, 0x5c0000dcU, 0x0054002DU},
	{DCD_WRITE, 0x5c0000e0U, 0x00F100C0U},
	{DCD_WRITE, 0x5c0000f4U, 0x0000066FU},
	{DCD_WRITE, 0x5c000100U, 0x1A201B22U},
	{DCD_WRITE, 0x5c000104U, 0x00060633U},
	{DCD_WRITE, 0x5c000108U, 0x07101617U},
	{DCD_WRITE, 0x5c00010cU, 0x00C0C000U},
	{DCD_WRITE, 0x5c000110U, 0x0F04080FU},
	{DCD_WRITE, 0x5c000114U, 0x02040C0CU},
	{DCD_WRITE, 0x5c000118U, 0x02020007U},
	{DCD_WRITE, 0x5c00011cU, 0x00000401U},
	{DCD_WRITE, 0x5c000130U, 0x00020610U},
	{DCD_WRITE, 0x5c000134U, 0x0C100002U},
	{DCD_WRITE, 0x5c000138U, 0x000000E6U},
	{DCD_WRITE, 0x5c000180U, 0x03200018U},
	{DCD_WRITE, 0x5c000184U, 0x028061A8U},
	{DCD_WRITE, 0x5c000190U, 0x049E820CU},
	{DCD_WRITE, 0x5c000194U, 0x00070303U},
	{DCD_WRITE, 0x5c0001b4U, 0x00001C0AU},
	{DCD_WRITE, 0x5c0001b0U, 0x00000005U},
	{DCD_WRITE, 0x5c0001a0U, 0x00400003U},
	{DCD_WRITE, 0x5c0001a4U, 0x008000A0U},
	{DCD_WRITE, 0x5c0001a8U, 0x80000000U},
	{DCD_WRITE, 0x5c000200U, 0x0000001FU},
	{DCD_WRITE, 0x5c00020cU, 0x00000000U},
	{DCD_WRITE, 0x5c000210U, 0x00001F1FU},
	{DCD_WRITE, 0x5c000204U, 0x00080808U},
	{DCD_WRITE, 0x5c000214U, 0x07070707U},
	{DCD_WRITE, 0x5c000218U, 0x07070707U},
	{DCD_WRITE, 0x5c0001c0U, 0x00000007U},
	{DCD_WRITE, 0x5c000244U, 0x00000000U},
	{DCD_WRITE, 0x5c000490U, 0x00000001U},
	{DCD_WRITE, 0x5c100000U, 0xC1080020U},
	{DCD_WRITE, 0x5c100020U, 0x00000213U},
	{DCD_WRITE, 0x5c100024U, 0x0186A000U},
	{DCD_WRITE, 0x5c100050U, 0x0021F000U},
	{DCD_WRITE, 0x5c100064U, 0x006100E0U},
	{DCD_WRITE, 0x5c1000d0U, 0x4003061CU},
	{DCD_WRITE, 0x5c1000d4U, 0x009E0000U},
	{DCD_WRITE, 0x5c1000dcU, 0x0054002DU},
	{DCD_WRITE, 0x5c1000e0U, 0x00F100C0U},
	{DCD_WRITE, 0x5c1000f4U, 0x0000066FU},
	{DCD_WRITE, 0x5c100100U, 0x1A201B22U},
	{DCD_WRITE, 0x5c100104U, 0x00060633U},
	{DCD_WRITE, 0x5c100108U, 0x07101617U},
	{DCD_WRITE, 0x5c10010cU, 0x00C0C000U},
	{DCD_WRITE, 0x5c100110U, 0x0F04080FU},
	{DCD_WRITE, 0x5c100114U, 0x02040C0CU},
	{DCD_WRITE, 0x5c100118U, 0x02020007U},
	{DCD_WRITE, 0x5c10011cU, 0x00000401U},
	{DCD_WRITE, 0x5c100130U, 0x00020610U},
	{DCD_WRITE, 0x5c100134U, 0x0C100002U},
	{DCD_WRITE, 0x5c100138U, 0x000000E6U},
	{DCD_WRITE, 0x5c100180U, 0x03200018U},
	{DCD_WRITE, 0x5c100184U, 0x028061A8U},
	{DCD_WRITE, 0x5c100190U, 0x049E820CU},
	{DCD_WRITE, 0x5c100194U, 0x00070303U},
	{DCD_WRITE, 0x5c1001b4U, 0x00001C0AU},
	{DCD_WRITE, 0x5c1001b0U, 0x00000005U},
	{DCD_WRITE, 0x5c1001a0U, 0x00400003U},
	{DCD_WRITE, 0x5c1001a4U, 0x008000A0U},
	{DCD_WRITE, 0x5c1001a8U, 0x80000000U},
	{DCD_WRITE, 0x5c100200U, 0x0000001FU},
	{DCD_WRITE, 0x5c10020cU, 0x00000000U},
	{DCD_WRITE, 0x5c100210U, 0x00001F1FU},
	{DCD_WRITE, 0x5c100204U, 0x00080808U},
	{DCD_WRITE, 0x5c100214U, 0x07070707U},
	{DCD_WRITE, 0x5c100218U, 0x07070707U},
	{DCD_WRITE, 0x5c1001c0U, 0x00000007U},
	{DCD_WRITE, 0x5c100244U, 0x00000000U},
	{DCD_WRITE, 0x5c100490U, 0x00000001U},
	{DCD_WRITE, 0x5c000030U, 0x0000010AU},
	{DCD_WRITE, 0x5c100030U, 0x0000010AU},
	{DCD_WRITE, 0x5c000034U, 0x00402010U},
	{DCD_WRITE, 0x5c100034U, 0x00402010U},
	{DCD_WRITE, 0x5c000038U, 0x06FF0001U},
	{DCD_WRITE, 0x5c100038U, 0x06FF0001U},
	{DCD_WRITE, 0x5c000198U, 0x0700B100U},
	{DCD_WRITE, 0x5c100198U, 0x0700B100U},
	{DCD_WRITE, 0x41a40208U, 0x1U},
	{DCD_WRITE, 0x41d00208U, 0x1U},
	{DCD_WRITE, 0x41a40040U, 0xFU},
	{DCD_WRITE, 0x41d00040U, 0xFU},
	{DCD_WRITE, 0x41a40204U, 0x1U},
	{DCD_WRITE, 0x41d00204U, 0x1U},
	{DCD_WRITE, 0x5c010100U, 0x0000040DU},
	{DCD_WRITE, 0x5c010248U, 0x000F0009U},
	{DCD_WRITE, 0x5c010728U, 0x00003465U},
	{DCD_WRITE, 0x5c01072cU, 0x00008271U},
	{DCD_WRITE, 0x5c010828U, 0x00075632U},
	{DCD_WRITE, 0x5c01082cU, 0x00008104U},
	{DCD_WRITE, 0x5c010928U, 0x00064732U},
	{DCD_WRITE, 0x5c01092cU, 0x00008015U},
	{DCD_WRITE, 0x5c010a28U, 0x00012574U},
	{DCD_WRITE, 0x5c010a2cU, 0x00008360U},
	{DCD_WRITE, 0x5c010240U, 0x00141032U},
	{DCD_WRITE, 0x5c010244U, 0x0013AAAAU},
	{DCD_SET_BIT, 0x5c010014U, 0x000A0040U},
	{DCD_WRITE, 0x5c010010U, 0x87001E00U},
	{DCD_WRITE, 0x5c010018U, 0x00F0D879U},
	{DCD_WRITE, 0x5c01001cU, 0x050A1080U},
	{DCD_WRITE, 0x5c010040U, 0x64032010U},
	{DCD_WRITE, 0x5c010044U, 0x4E201C20U},
	{DCD_WRITE, 0x5c010068U, 0x801C0000U},
	{DCD_WRITE, 0x5c0117c4U, 0x801C0000U},
	{DCD_WRITE, 0x5c010680U, 0x008C2C58U},
	{DCD_WRITE, 0x5c010684U, 0x0001B9BBU},
	{DCD_WRITE, 0x5c0106a4U, 0x0001B9BBU},
	{DCD_WRITE, 0x5c110100U, 0x0000040DU},
	{DCD_WRITE, 0x5c110248U, 0x000F0009U},
	{DCD_WRITE, 0x5c110728U, 0x00003465U},
	{DCD_WRITE, 0x5c11072cU, 0x00008271U},
	{DCD_WRITE, 0x5c110828U, 0x00075632U},
	{DCD_WRITE, 0x5c11082cU, 0x00008104U},
	{DCD_WRITE, 0x5c110928U, 0x00064732U},
	{DCD_WRITE, 0x5c11092cU, 0x00008015U},
	{DCD_WRITE, 0x5c110a28U, 0x00012574U},
	{DCD_WRITE, 0x5c110a2cU, 0x00008360U},
	{DCD_WRITE, 0x5c110240U, 0x00141032U},
	{DCD_WRITE, 0x5c110244U, 0x0013AAAAU},
	{DCD_SET_BIT, 0x5c110014U, 0x000A0040U},
	{DCD_WRITE, 0x5c110010U, 0x87001E00U},
	{DCD_WRITE, 0x5c110018U, 0x00F0D879U},
	{DCD_WRITE, 0x5c11001cU, 0x050A1080U},
	{DCD_WRITE, 0x5c110040U, 0x64032010U},
	{DCD_WRITE, 0x5c110044U, 0x4E201C20U},
	{DCD_WRITE, 0x5c110068U, 0x801C0000U},
	{DCD_WRITE, 0x5c1117c4U, 0x801C0000U},
	{DCD_WRITE, 0x5c110680U, 0x008C2C58U},
	{DCD_WRITE, 0x5c110684U, 0x0001B9BBU},
	{DCD_WRITE, 0x5c1106a4U, 0x0001B9BBU},
	{DCD_WRITE, 0x5c010004U, 0x10U},
	{DCD_WRITE, 0x5c010004U, 0x11U},
	{DCD_WRITE, 0x5c110004U, 0x10U},
	{DCD_WRITE, 0x5c110004U, 0x11U},
	{DCD_CHECK_BITS_SET, 0x5c010030U, 0x1U},
	{DCD_CHECK_BITS_SET, 0x5c110030U, 0x1U},
	{DCD_WRITE, 0x5c010068U, 0xA01C0000U},
	{DCD_WRITE, 0x5c0117c4U, 0xA01C0000U},
	{DCD_WRITE, 0x41a40208U, 0x1U},
	{DCD_WRITE, 0x41a40504U, 0x00800000U},
	{DCD_WRITE, 0x41a40204U, 0x1U},
	{DCD_WRITE, 0x5c010040U, 0x03201901U},
	{DCD_WRITE, 0x5c010044U, 0x027100E1U},
	{DCD_WRITE, 0x5c010004U, 0x22U},
	{DCD_WRITE, 0x5c010004U, 0x23U},
	{DCD_WRITE, 0x5c110068U, 0xA01C0000U},
	{DCD_WRITE, 0x5c1117c4U, 0xA01C0000U},
	{DCD_WRITE, 0x41d00208U, 0x1U},
	{DCD_WRITE, 0x41d00504U, 0x00800000U},
	{DCD_WRITE, 0x41d00204U, 0x1U},
	{DCD_WRITE, 0x5c110040U, 0x03201901U},
	{DCD_WRITE, 0x5c110044U, 0x027100E1U},
	{DCD_WRITE, 0x5c110004U, 0x22U},
	{DCD_WRITE, 0x5c110004U, 0x23U},
	{DCD_WRITE, 0x5c010184U, 0x54U},
	{DCD_WRITE, 0x5c010188U, 0x2DU},
	{DCD_WRITE, 0x5c01018cU, 0xF1U},
	{DCD_WRITE, 0x5c0101acU, 0x54U},
	{DCD_WRITE, 0x5c0101b4U, 0xC0U},
	{DCD_WRITE, 0x5c0101d8U, 0x16U},
	{DCD_WRITE, 0x5c0101b0U, 0x48U},
	{DCD_WRITE, 0x5c0101b8U, 0x48U},
	{DCD_WRITE, 0x5c010110U, 0x1044220CU},
	{DCD_WRITE, 0x5c010114U, 0x28400417U},
	{DCD_WRITE, 0x5c010118U, 0x006CA1CCU},
	{DCD_WRITE, 0x5c01011cU, 0x01800602U},
	{DCD_WRITE, 0x5c010120U, 0x01C02B0FU},
	{DCD_WRITE, 0x5c010124U, 0x21651D11U},
	{DCD_WRITE, 0x5c010048U, 0x000A3DEFU},
	{DCD_WRITE, 0x5c01004cU, 0x000186A0U},
	{DCD_WRITE, 0x5c010050U, 0x00000064U},
	{DCD_WRITE, 0x5c010054U, 0x00002710U},
	{DCD_WRITE, 0x5c010058U, 0x00B00032U},
	{DCD_WRITE, 0x5c0104dcU, 0x00000001U},
	{DCD_WRITE, 0x5c010098U, 0x00000000U},
	{DCD_WRITE, 0x5c0104dcU, 0x00000000U},
	{DCD_WRITE, 0x5c010098U, 0x00000000U},
	{DCD_WRITE, 0x5c010500U, 0x30070801U},
	{DCD_WRITE, 0x5c010514U, 0x09000000U},
	{DCD_WRITE, 0x5c010504U, 0x44000000U},
	{DCD_WRITE, 0x5c010528U, 0xF0032008U},
	{DCD_WRITE, 0x5c01052cU, 0x07F001AFU},
	{DCD_SET_BIT, 0x5c010024U, 0x4U},
	{DCD_WRITE, 0x5c010028U, 0x00033200U},
	{DCD_WRITE, 0x5c010714U, 0x09092020U},
	{DCD_WRITE, 0x5c010814U, 0x09092020U},
	{DCD_WRITE, 0x5c010914U, 0x09092020U},
	{DCD_WRITE, 0x5c010a14U, 0x09092020U},
	{DCD_WRITE, 0x5c010710U, 0x0E00BF3CU},
	{DCD_WRITE, 0x5c010810U, 0x0E00BF3CU},
	{DCD_WRITE, 0x5c010910U, 0x0E00BF3CU},
	{DCD_WRITE, 0x5c010a10U, 0x0E00BF3CU},
	{DCD_WRITE, 0x5c0117ecU, 0x001C1600U},
	{DCD_WRITE, 0x5c010020U, 0x001900B1U},
	{DCD_WRITE, 0x5c0117f0U, 0x79000000U},
	{DCD_WRITE, 0x5c110184U, 0x54U},
	{DCD_WRITE, 0x5c110188U, 0x2DU},
	{DCD_WRITE, 0x5c11018cU, 0xF1U},
	{DCD_WRITE, 0x5c1101acU, 0x54U},
	{DCD_WRITE, 0x5c1101b4U, 0xC0U},
	{DCD_WRITE, 0x5c1101d8U, 0x16U},
	{DCD_WRITE, 0x5c1101b0U, 0x48U},
	{DCD_WRITE, 0x5c1101b8U, 0x48U},
	{DCD_WRITE, 0x5c110110U, 0x1044220CU},
	{DCD_WRITE, 0x5c110114U, 0x28400417U},
	{DCD_WRITE, 0x5c110118U, 0x006CA1CCU},
	{DCD_WRITE, 0x5c11011cU, 0x01800602U},
	{DCD_WRITE, 0x5c110120U, 0x01C02B0FU},
	{DCD_WRITE, 0x5c110124U, 0x21651D11U},
	{DCD_WRITE, 0x5c110048U, 0x000A3DEFU},
	{DCD_WRITE, 0x5c11004cU, 0x000186A0U},
	{DCD_WRITE, 0x5c110050U, 0x00000064U},
	{DCD_WRITE, 0x5c110054U, 0x00002710U},
	{DCD_WRITE, 0x5c110058U, 0x00B00032U},
	{DCD_WRITE, 0x5c1104dcU, 0x00000001U},
	{DCD_WRITE, 0x5c110098U, 0x00000000U},
	{DCD_WRITE, 0x5c1104dcU, 0x00000000U},
	{DCD_WRITE, 0x5c110098U, 0x00000000U},
	{DCD_WRITE, 0x5c110500U, 0x30070801U},
	{DCD_WRITE, 0x5c110514U, 0x09000000U},
	{DCD_WRITE, 0x5c110504U, 0x44000000U},
	{DCD_WRITE, 0x5c110528U, 0xF0032008U},
	{DCD_WRITE, 0x5c11052cU, 0x07F001AFU},
	{DCD_SET_BIT, 0x5c110024U, 0x4U},
	{DCD_WRITE, 0x5c110028U, 0x00033200U},
	{DCD_WRITE, 0x5c110714U, 0x09092020U},
	{DCD_WRITE, 0x5c110814U, 0x09092020U},
	{DCD_WRITE, 0x5c110914U, 0x09092020U},
	{DCD_WRITE, 0x5c110a14U, 0x09092020U},
	{DCD_WRITE, 0x5c110710U, 0x0E00BF3CU},
	{DCD_WRITE, 0x5c110810U, 0x0E00BF3CU},
	{DCD_WRITE, 0x5c110910U, 0x0E00BF3CU},
	{DCD_WRITE, 0x5c110a10U, 0x0E00BF3CU},
	{DCD_WRITE, 0x5c1117ecU, 0x001C1600U},
	{DCD_WRITE, 0x5c110020U, 0x001900B1U},
	{DCD_WRITE, 0x5c1117f0U, 0x79000000U},
	{DCD_CHECK_BITS_SET, 0x5c010030U, 0x1U},
	{DCD_WRITE, 0x5c010004U, 0x180U},
	{DCD_WRITE, 0x5c010004U, 0x181U},
	{DCD_CHECK_BITS_SET, 0x5c110030U, 0x1U},
	{DCD_WRITE, 0x5c110004U, 0x180U},
	{DCD_WRITE, 0x5c110004U, 0x181U},
	{DCD_CHECK_BITS_SET, 0x5c010030U, 0x1U},
	{DCD_WRITE, 0x5c01004cU, 0x00000064U},
	{DCD_WRITE, 0x5c010004U, 0x100U},
	{DCD_WRITE, 0x5c010004U, 0x101U},
	{DCD_CHECK_BITS_SET, 0x5c110030U, 0x1U},
	{DCD_WRITE, 0x5c11004cU, 0x00000064U},
	{DCD_WRITE, 0x5c110004U, 0x100U},
	{DCD_WRITE, 0x5c110004U, 0x101U},
	{DCD_CHECK_BITS_SET, 0x5c010030U, 0x1U},
	{DCD_CHECK_BITS_SET, 0x5c110030U, 0x1U},
	{DCD_RUN_CBT, 0x64032010, 0x4E201C20},
	{DCD_CLR_BIT, 0x5c010250U, 0x00000001U},
	{DCD_SET_BIT, 0x5c010028U, 0x00000001U},
	{DCD_CHECK_BITS_SET, 0x5c010034U, 0x40000000U},
	{DCD_SET_BIT, 0x5c010014U, 0x00020040U},
	{DCD_WRITE, 0x5c01041cU, 0x00010100U},
	{DCD_WRITE, 0x5c010420U, 0x700003FFU},
	{DCD_WRITE, 0x5c010428U, 0x00003FFFU},
	{DCD_CLR_BIT, 0x5c110250U, 0x00000001U},
	{DCD_SET_BIT, 0x5c110028U, 0x00000001U},
	{DCD_CHECK_BITS_SET, 0x5c110034U, 0x40000000U},
	{DCD_SET_BIT, 0x5c110014U, 0x00020040U},
	{DCD_WRITE, 0x5c11041cU, 0x00010100U},
	{DCD_WRITE, 0x5c110420U, 0x700003FFU},
	{DCD_WRITE, 0x5c110428U, 0x00003FFFU},
	{DCD_WRITE, 0x5c010200U, 0x000031C7U},
	{DCD_WRITE, 0x5c010204U, 0x00010236U},
	{DCD_WRITE, 0x5c110200U, 0x000031C7U},
	{DCD_WRITE, 0x5c110204U, 0x00010236U},
	{DCD_WRITE, 0x5c010004U, 0x200U},
	{DCD_WRITE, 0x5c010004U, 0x201U},
	{DCD_WRITE, 0x5c110004U, 0x200U},
	{DCD_WRITE, 0x5c110004U, 0x201U},
	{DCD_CHECK_BITS_SET, 0x5c010030U, 0x1U},
	{DCD_CHECK_BITS_CLR, 0x5c010030U, 0x00200000U},
	{DCD_WRITE, 0x5c0117dcU, 0x012240B3U},
	{DCD_WRITE, 0x5c010004U, 0x400U},
	{DCD_WRITE, 0x5c010004U, 0x401U},
	{DCD_CHECK_BITS_SET, 0x5c110030U, 0x1U},
	{DCD_CHECK_BITS_CLR, 0x5c110030U, 0x00200000U},
	{DCD_WRITE, 0x5c1117dcU, 0x012240B3U},
	{DCD_WRITE, 0x5c110004U, 0x400U},
	{DCD_WRITE, 0x5c110004U, 0x401U},
	{DCD_CHECK_BITS_SET, 0x5c010030U, 0x1U},
	{DCD_CHECK_BITS_CLR, 0x5c010030U, 0x00400000U},
	{DCD_WRITE, 0x5c0117dcU, 0x01224000U},
	{DCD_WRITE, 0x5c010004U, 0x0010F800U},
	{DCD_WRITE, 0x5c010004U, 0x0010F801U},
	{DCD_CHECK_BITS_SET, 0x5c110030U, 0x1U},
	{DCD_CHECK_BITS_CLR, 0x5c110030U, 0x00400000U},
	{DCD_WRITE, 0x5c1117dcU, 0x01224000U},
	{DCD_WRITE, 0x5c110004U, 0x0010F800U},
	{DCD_WRITE, 0x5c110004U, 0x0010F801U},
	{DCD_CHECK_BITS_SET, 0x5c010030U, 0x1U},
	{DCD_CHECK_BITS_CLR, 0x5c010030U, 0x7FF40000U},
	{DCD_CHECK_BITS_SET, 0x5c110030U, 0x1U},
	{DCD_CHECK_BITS_CLR, 0x5c110030U, 0x7FF40000U},
	{DCD_RDBI_BIT_DESKEW, 0},
	{DCD_RDBI_BIT_DESKEW, 1},
	{DCD_WRITE, 0x5c010004U, 0x00020000U},
	{DCD_WRITE, 0x5c010004U, 0x00020001U},
	{DCD_WRITE, 0x5c110004U, 0x00020000U},
	{DCD_WRITE, 0x5c110004U, 0x00020001U},
	{DCD_CHECK_BITS_SET, 0x5c010030U, 0x1U},
	{DCD_CHECK_BITS_CLR, 0x5c010030U, 0x00080000U},
	{DCD_CHECK_BITS_SET, 0x5c110030U, 0x1U},
	{DCD_CHECK_BITS_CLR, 0x5c110030U, 0x00080000U},
	{DCD_WRITE, 0x5c0117e4U, 0x00100002U},
	{DCD_WRITE, 0x5c1117e4U, 0x00100002U},
	{DCD_CLR_BIT, 0x5c010014U, 0x00020040U},
	{DCD_CLR_BIT, 0x5c110014U, 0x00020040U},
	{DCD_CLR_BIT, 0x5c01070cU, 0x08000000U},
	{DCD_CLR_BIT, 0x5c01080cU, 0x08000000U},
	{DCD_CLR_BIT, 0x5c01090cU, 0x08000000U},
	{DCD_CLR_BIT, 0x5c010a0cU, 0x08000000U},
	{DCD_WRITE, 0x5c010250U, 0x20188005U},
	{DCD_WRITE, 0x5c010254U, 0xA8AA0000U},
	{DCD_WRITE, 0x5c010258U, 0x00070200U},
	{DCD_CLR_BIT, 0x5c11070cU, 0x08000000U},
	{DCD_CLR_BIT, 0x5c11080cU, 0x08000000U},
	{DCD_CLR_BIT, 0x5c11090cU, 0x08000000U},
	{DCD_CLR_BIT, 0x5c110a0cU, 0x08000000U},
	{DCD_WRITE, 0x5c110250U, 0x20188005U},
	{DCD_WRITE, 0x5c110254U, 0xA8AA0000U},
	{DCD_WRITE, 0x5c110258U, 0x00070200U},
	{DCD_WRITE, 0x41A40504U, 0x400U},
	{DCD_WRITE, 0x41D00504U, 0x400U},
	{DCD_CLR_BIT, 0x5c010028U, 0x1U},
	{DCD_CLR_BIT, 0x5c110028U, 0x1U},
	{DCD_CHECK_BITS_SET, 0x5c000004U, 0x1U},
	{DCD_CHECK_BITS_SET, 0x5c100004U, 0x1U},
	{DCD_LPDDR4_DERATE_INIT, BD_DDR_RET_NUM_DRC},
};

int dcd_table_size = ARRAY_SIZE(dcd_table);
