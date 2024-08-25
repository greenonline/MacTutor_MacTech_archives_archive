/*
------------------------------------------------------
T E A R O F F   P A L E T T E

 version 1.0
 by Don Melton and Mike Ritter
 
 Copyright (C)1987, 1988 by Impulse Technologies, 
 Inc., all rights reserved. 
 
 Filename:TearOffPalette.project.r
 Font:  Monaco, 9 point
 Tab setting:    2
 Compiler:MPW Rez 2.0 */



/*
--------------------------------------------------------INCLUDE TYPES 
*/

#include "Types.r"

/*
--------------------------------------------------------
TYPE DEFINITIONS */

type 'TOPD' as 'STR ';

/*
--------------------------------------------------------
RESOURCE DEFINITIONS */

resource 'BNDL' (128) {
 'TOPD',
 0,
 {
 'ICN#',
 {
 0, 128
 },
 'FREF',
 {
 0, 128
 }
 }
};

resource 'FREF' (128) {
 'APPL',
 0,
 ""
};

resource 'ICN#' (128, purgeable) {
 {
 /* Data */
 $"FFFF FFE0 8000 0030 8000 0030 EFBF FFF0"
 $"8880 0030 E8BF FFF0 8880 0030 EFBF FFF0"
 $"8000 0030 81FF FFFE FF00 0002 81BA AAAA"
 $"8128 0003 81BA AAAB 8100 0003 81FF FFFF"
 $"8100 0003 8100 0003 8100 0003 8100 0003"
 $"8100 0003 8100 0003 8100 0003 8100 0003"
 $"8100 0003 8100 0003 81FF FFFF 803F FFFF"
 $"8000 0030 8000 0030 FFFF FFF0 7FFF FFF0",
 /* Mask */
 $"FFFF FFE0 FFFF FFF0 FFFF FFF0 FFFF FFF0"
 $"FFFF FFF0 FFFF FFF0 FFFF FFF0 FFFF FFF0"
 $"FFFF FFF0 FFFF FFFE FFFF FFFE FFFF FFFE"
 $"FFFF FFFF FFFF FFFF FFFF FFFF FFFF FFFF"
 $"FFFF FFFF FFFF FFFF FFFF FFFF FFFF FFFF"
 $"FFFF FFFF FFFF FFFF FFFF FFFF FFFF FFFF"
 $"FFFF FFFF FFFF FFFF FFFF FFFF FFFF FFFF"
 $"FFFF FFF0 FFFF FFF0 FFFF FFF0 7FFF FFF0"
 }
};

resource 'PAT#' (128, preload) {
 { /* 64 elements */
 $"",
 $"80",
 $"8000 0000 08",
 $"8800 0000 08",
 $"8800 0000 88",
 $"8800 2000 88",
 $"8800 2000 8800 02",
 $"8800 2200 8800 02",
 $"8800 2200 8800 22",
 $"A800 2200 8800 22",
 $"A800 2200 8A00 22",
 $"AA00 2200 8A00 22",
 $"AA00 2200 AA00 22",
 $"AA00 A200 AA00 22",
 $"AA00 A200 AA00 2A",
 $"AA00 AA00 AA00 AA",
 $"AA40 AA00 AA00 AA",
 $"AA40 AA00 AA04 AA",
 $"AA44 AA00 AA04 AA",
 $"AA44 AA00 AA44 AA",
 $"AA44 AA10 AA44 AA",
 $"AA44 AA10 AA44 AA01",
 $"AA44 AA11 AA44 AA01",
 $"AA44 AA11 AA44 AA11",
 $"AA54 AA11 AA44 AA11",
 $"AA54 AA11 AA45 AA11",
 $"AA55 AA11 AA45 AA11",
 $"AA55 AA11 AA55 AA11",
 $"AA55 AA51 AA55 AA11",
 $"AA55 AA51 AA55 AA15",
 $"AA55 AA55 AA55 AA15",
 $"AA55 AA55 AA55 AA55",
 $"EA55 AA55 AA55 AA55",
 $"EA55 AA55 AE55 AA55",
 $"EE55 AA55 AE55 AA55",
 $"EE55 AA55 EE55 AA55",
 $"EE55 BA55 EE55 AA55",
 $"EE55 BA55 EE55 AB55",
 $"EE55 BB55 EE55 AB55",
 $"EE55 BB55 EE55 BB55",
 $"FE55 BB55 EE55 BB55",
 $"FE55 BB55 EF55 BB55",
 $"FF55 BB55 EF55 BB55",
 $"FF55 BB55 FF55 BB55",
 $"FF55 FB55 FF55 BB55",
 $"FF55 FB55 FF55 BF55",
 $"FF55 FF55 FF55 BF55",
 $"FF55 FF55 FF55 FF55",
 $"FFD5 FF55 FF55 FF55",
 $"FFD5 FF55 FF5D FF55",
 $"FFDD FF55 FF5D FF55",
 $"FFDD FF55 FFDD FF55",
 $"FFDD FF75 FFDD FF55",
 $"FFDD FF75 FFDD FF57",
 $"FFDD FF77 FFDD FF57",
 $"FFDD FF77 FFDD FF77",
 $"FFFD FF77 FFDD FF77",
 $"FFFD FF77 FFDF FF77",
 $"FFFF FF77 FFDF FF77",
 $"FFFF FF77 FFFF FF77",
 $"FFFF FFF7 FFFF FF77",
 $"FFFF FFF7 FFFF FF7F",
 $"FFFF FFFF FFFF FF7F",
 $"FFFF FFFF FFFF FFFF"
 }
};

resource 'STR ' (128, preload) {
 "Untitled"
};

resource 'PICT' (128, preload) {
 1270,
 {0, 0, 83, 99},
 $"1101 A000 8201 000A 0000 0000 02D0 0240"
 $"9800 0E00 0000 0000 5300 6800 0000 0000"
 $"5300 6300 0000 0000 5300 6300 000C FE00"
 $"0680 0000 4000 0020 FD00 0CFE 0006 8000"
 $"0040 0000 20FD 000E FE00 0880 0000 4006"
 $"0020 0380 FF00 0F0B 0F3E 7080 1FC0 4069"
 $"C020 0280 FF00 0F0B 0800 1080 E030 4099"
 $"2020 0380 FF00 0F0B 0800 1081 0008 4099"
 $"2820 0380 FF00 0EFE 0008 8200 0840 4934"
 $"2003 80FF 000E FE00 0884 0008 4049 2420"
 $"0380 FF00 0F0B 0800 1084 0030 41A0 2420"
 $"0380 FF00 0F0B 0800 1084 01C0 4260 0420"
 $"1FF0 FF00 0F0B 0800 1083 8E00 4220 0820"
 $"1010 FF00 0F0B 0800 1086 7000 4100 0820"
 $"1FF0 FF00 0EFE 0008 8540 0040 8008 2010"
 $"10FF 000E FE00 0883 8000 4080 1020 1010"
 $"FF00 0F0B 0800 1080 8000 4040 1020 1010"
 $"FF00 0F06 0800 1080 8000 40FE 2001 1550"
 $"FF00 0F0B 0E7C F081 0000 4010 2020 2AB0"
 $"FF00 0EFE 0008 8000 0040 1020 207F E0FF"
 $"000C FE00 0680 0000 4000 0020 FD00 0CFE"
 $"0006 8000 0040 0000 20FD 0005 F5FF 01E0"
 $"000C FE00 0680 0000 4000 0020 FD00 0CFE"
 $"0006 8000 0040 0000 20FD 000D 0900 0F00"
 $"8000 0040 1C00 21FD 000E 0A00 0880 8000"
 $"0040 2200 2040 FE00 0E0A 0010 8080 07F0"
 $"4026 0021 15FE 000F 0B00 1900 8008 1040"
 $"2B00 2043 80FF 000F 0B00 2700 8010 3840"
 $"32C0 2104 40FF 000F 0B00 2200 8020 5840"
 $"2270 200F E0FF 000F 0B00 4200 8040 B040"
 $"4238 2008 20FF 000F 0B00 4400 8081 6040"
 $"851C 2009 E0FF 000F 0B00 8400 8102 C041"
 $"021C 2009 20FF 000F 0B00 8800 8205 8042"
 $"003C 2009 E0FF 000F 0B01 0800 87FB 0042"
 $"005C 2009 20FF 000F 0B01 1000 840E 0041"
 $"009C 2009 E0FF 000F 0B01 E000 840C 0040"
 $"811C 2009 E0FF 000F 0B01 C000 87F8 0040"
 $"421C 2008 20FF 000F 0B01 8000 8000 0040"
 $"2418 2008 20FF 000F 0B01 0000 8000 0040"
 $"1810 200F E0FF 000C FE00 0680 0000 4000"
 $"0020 FD00 0CFE 0006 8000 0040 0000 20FD"
 $"0005 F5FF 01E0 000C FE00 0680 0000 4000"
 $"0020 FD00 0CFE 0006 8000 0040 0000 20FD"
 $"000C FE00 0680 0000 4000 0020 FD00 0DFE"
 $"0007 8000 0040 0000 2003 FE00 0EFE 0008"
 $"87FF F840 1F80 200C C0FF 000E FE00 0884"
 $"0008 4060 6020 3030 FF00 0F0B 0C00 0084"
 $"0008 4180 1820 C00C FF00 0F0B 0300 0084"
 $"0008 4100 0820 8004 FF00 0F0B 00C0 0084"
 $"0008 4200 0420 8004 FF00 0F0B 0030 0084"
 $"0008 4200 0420 8004 FF00 0F0B 000C 0084"
 $"0008 4200 0420 8004 FF00 0F0B 0003 0084"
 $"0008 4200 0420 8004 FF00 0F0B 0000 C084"
 $"0008 4100 0820 8004 FF00 0F0B 0000 3084"
 $"0008 4180 1820 C00C FF00 0EFE 0008 8400"
 $"0840 6060 2030 30FF 000E FE00 0887 FFF8"
 $"401F 8020 0CC0 FF00 0DFE 0007 8000 0040"
 $"0000 2003 FE00 0CFE 0006 8000 0040 0000"
 $"20FD 000C FE00 0680 0000 4000 0020 FD00"
 $"0CFE 0006 8000 0040 0000 20FD 0005 F5FF"
 $"01E0 000C FE00 0680 0000 4000 0020 FD00"
 $"0CFE 0006 8000 0040 0000 20FD 000C FE00"
 $"0680 0000 4000 0020 FD00 0D09 07FF E080"
 $"0000 4000 0020 FD00 0D09 0618 6081 FFE0"
 $"4000 0020 FD00 0F0B 0418 2082 0010 40E0"
 $"7020 0FE0 FF00 0F0B 0418 2084 0008 4118"
 $"8820 1020 FF00 0E08 0018 0084 0008 4207"
 $"04FE 20FF 000F 0B00 1800 8400 0842 0004"
 $"2040 20FF 000F 0B00 1800 8400 0842 0004"
 $"2080 20FF 000F 0B00 1800 8400 0842 0004"
 $"2100 10FF 000F 0B00 1800 8400 0841 0008"
 $"2080 08FF 000F 0B00 1800 8400 0841 0010"
 $"2040 04FF 000F 0700 1800 8400 0840 80FE"
 $"2000 02FF 000F 0B00 1800 8200 1040 60C0"
 $"201F FEFF 000D 0900 1800 81FF E040 1F00"
 $"20FD 000D 0900 7E00 8000 0040 0000 20FD"
 $"000C FE00 0680 0000 4000 0020 FD00 0CFE"
 $"0006 8000 0040 0000 20FD 000C FE00 0680"
 $"0000 4000 0020 FD00 A000 83FF"
};

resource 'PICT' (129, purgeable) {
 858,
 {0, 0, 51, 166},
 $"1101 A000 8201 000A 0000 0000 02D0 0240"
 $"9800 1600 0000 0000 3300 A800 0000 0000"
 $"3300 A600 0000 0000 3300 A600 0006 FE00"
 $"0080 EF00 0703 0000 0140 EF00 0703 0000"
 $"0220 EF00 0703 0000 0410 EF00 0703 0000"
 $"0808 EF00 0703 0000 1004 EF00 0703 0000"
 $"2002 EF00 0703 0000 4001 EF00 0804 0000"
 $"8000 80F0 0008 0400 0100 0040 F000 0D04"
 $"0002 0000 20FB 0001 0180 F800 0D04 0004"
 $"0000 10FB 0001 0F80 F800 0D04 0008 001C"
 $"08FB 0001 3F80 F800 0C04 0010 00FC 04FB"
 $"0000 07F7 000C 0400 2000 FC02 FB00 0007"
 $"F700 0C04 0040 00FC 01FB 0000 07F7 000D"
 $"0500 8000 F800 80FC 0000 0FF7 000D 0501"
 $"0000 F800 40FC 0000 0EF7 000D 0502 0000"
 $"F800 20FC 0000 0EF7 000B 0304 0001 F0FA"
 $"0000 0EF7 0012 0E08 0001 F070 703C 787C"
 $"1C07 0E07 F01F FA00 130F 1000 01F1 F1F4"
 $"FCF8 FE7C 0F1E 1FF0 7F80 FB00 130F 2000"
 $"01E7 F3F3 FFF9 9EFC 0E1C 3871 C380 FB00"
 $"130F 4000 01EC E673 3E33 0F9C 0E1C 3031"
 $"8380 FB00 130F 8000 01E0 EC76 B83E 0E1C"
 $"0E1C 7023 8380 FB00 130F 4000 03C0 F87D"
 $"383C 0E3C 1E1C 7003 8780 FB00 120E 2000"
 $"03C1 F0FB 7878 0E38 1C3C 7807 0FFA 0012"
 $"0E30 0003 C1F0 F778 780E 381C 383F C73C"
 $"FA00 120E 1800 0381 E0F7 7070 1C38 3C38"
 $"3FE7 E0FA 0011 0D0C 0003 81E0 F670 701C"
 $"783C 3807 FFF9 0011 0D06 0000 03C1 ECF0"
 $"F038 7078 3800 FEF9 0011 0D03 0000 03C1"
 $"E8F0 E038 70F8 7800 7EF9 0011 0401 8007"
 $"03C1 FEE0 0570 71B8 70C0 7EF9 0012 0E00"
 $"C00F 8381 C0E0 E070 F338 71C0 6E03 FA00"
 $"120E 0060 0F87 83C1 EDE0 E0F6 3B77 C0CF"
 $"06FA 0012 0E00 300F 8783 C1F9 F1C0 FC7E"
 $"7CE3 8F8C FA00 120E 0018 0F87 0B81 F1FF"
 $"00F8 7C78 FF07 F8FA 0012 0E00 0C07 071B"
 $"80C1 FC00 6070 607C 03E0 FA00 0B07 0006"
 $"0000 3C00 03C0 F300 0B07 0003 0000 7800"
 $"03C0 F300 0B07 0001 8000 F000 03C0 F300"
 $"1715 0000 C001 E000 03C1 F1F0 78E7 1CE0"
 $"F0E0 3C0F 1C7C 3C00 1715 0000 6003 C000"
 $"0381 5090 8842 0C41 1840 4611 0824 4400"
 $"1715 0000 3007 8000 0780 4081 0042 0A42"
 $"0840 8220 0820 4000 1715 0000 180F 0000"
 $"0780 40E1 007E 0A42 0840 8220 0838 3800"
 $"1715 0000 0C1E 0000 0780 4081 0042 0942"
 $"0840 8223 8820 0C00 1715 0000 063C 0000"
 $"0780 4081 0042 0942 0840 8221 0820 0400"
 $"1603 0000 0378 FD00 0D40 9188 4208 C310"
 $"44C4 3108 2444 0016 0300 0001 F0FD 000D"
 $"E1F0 F0E7 1CC1 E0FC 781E 1C7C 7800 06FE"
 $"0000 E0EF 0006 FE00 0040 EF00 A000 83FF"
};

resource 'DLOG' (128, preload) {
 {0, 0, 160, 418},
 dBoxProc,
 invisible,
 noGoAway,
 0x0,
 128,
 ""
};

resource 'DITL' (128, preload) {
 {
 {10, 10, 42, 42},
 Icon {
 enabled,
 128
 },
 {14, 52, 30, 408},
 StaticText {
 enabled,
 "TearOffPalette by Don Melton and Mike Ritter"
 },
 {30, 52, 46, 408},
 StaticText {
 enabled,
 "©1987, 1988 by Impulse Technologies, Inc."
 },
 {56, 10, 72, 408},
 StaticText {
 enabled,
 "Designed for MacTutor: The Macintosh "
 "Programming Journal"
 },
 {72, 10, 88, 408},
 StaticText {
 enabled,
 "Compiled with LightspeedC™ version 2.15"
 },
 {98, 190, 130, 408},
 StaticText {
 enabled,
 ""Sure. We can do that. We don't even have to "
 "have a reason.""
 },
 {134, 190, 150, 408},
 StaticText {
 enabled,
 "Call us at (408) 296-6110"
 },
 {98, 10, 149, 176},
 Picture {
 enabled,
 129
 }
 }
};

resource 'TOPD' (0) {
 "TearOffPalette by Don Melton and Mike Ritter, "
 "©1987, 1988 by Impulse Technologies, Inc., "
 "all rights reserved."
};

data 'TOMG' (131, preload) {
 $"0000 0000 0000 0000 0000 0000 0000"
 $"0000 0000 0000 0000 0000 0000 0000"
};

data 'TOMG' (132, preload) {
 $"0000 0000 0000 0000 0000 0000 0000"
 $"0000 0000 0000 0000 0000 0000 0000"
};

data 'TOMG' (133, preload) {
 $"0000 0000 0000 0000 0000 0000 0000"
 $"0000 0000 0000 0000 0000 0000 0000"
};

resource 'MENU' (128, preload) {
 128,
 textMenuProc,
 0x7FFFFFFD,
 enabled,
 apple,
 {
 "About TearOffPalette...", noIcon, "", "", plain,
 "-", noIcon, "", "", plain
 }
};

resource 'MENU' (129, preload) {
 129,
 textMenuProc,
 0x7FFFFFF5,
 enabled,
 "File",
 {
 "New", noIcon, "N", "", plain,
 "-", noIcon, "", "", plain,
 "Close", noIcon, "W", "", plain,
 "-", noIcon, "", "", plain,
 "Quit", noIcon, "Q", "", plain
 }
};

resource 'MENU' (130, preload) {
 130,
 textMenuProc,
 0x7FFFFFFD,
 enabled,
 "Edit",
 {
 "Undo", noIcon, "Z", "", plain,
 "-", noIcon, "", "", plain,
 "Cut", noIcon, "X", "", plain,
 "Copy", noIcon, "C", "", plain,
 "Paste", noIcon, "V", "", plain,
 "Clear", noIcon, "", "", plain
 }
};

resource 'MENU' (131, preload) {
 131,
 128,
 allEnabled,
 enabled,
 "Tool",
 { /* 16 elements */
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain
 }
};

resource 'MENU' (132, preload) {
 132,
 128,
 allEnabled,
 enabled,
 "Pattern",
 { /* 64 elements */
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain
 }
};

resource 'MENU' (133, preload) {
 133,
 128,
 allEnabled,
 enabled,
 "Color",
 { /* 256 elements */
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain,
 "*", noIcon, "", "", plain
 }
};

resource 'SIZE' (-1) {
 dontSaveScreen,
 acceptSuspendResumeEvents,
 doOwnActivate,
 393216,
 393216
};

resource 'SIZE' (0) {
 dontSaveScreen,
 acceptSuspendResumeEvents,
 doOwnActivate,
 393216,
 393216
};

resource 'ICON' (128, purgeable) {
 $"FFFF FFE0 8000 0030 8000 0030 EFBF FFF0"
 $"8880 0030 E8BF FFF0 8880 0030 EFBF FFF0"
 $"8000 0030 81FF FFFE FF00 0002 81BA AAAA"
 $"8128 0003 81BA AAAB 8100 0003 81FF FFFF"
 $"8100 0003 8100 0003 8100 0003 8100 0003"
 $"8100 0003 8100 0003 8100 0003 8100 0003"
 $"8100 0003 8100 0003 81FF FFFF 803F FFFF"
 $"8000 0030 8000 0030 FFFF FFF0 7FFF FFF0"
};