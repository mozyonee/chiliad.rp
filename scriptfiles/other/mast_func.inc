#define PAINT_VALUE (1000)
#define VYNIL_VALUE (3000)

new PlayerText:CustomTDPl[MAX_PLAYERS][6];
new Text:ColorTD[20];
new Text:CustomTD[22];
new PlayerText:ColorTDPl[MAX_PLAYERS][7];
new RGBArray[256] = {
	0x000000FF, 0xF5F5F5FF, 0x2A77A1FF, 0x840410FF, 0x263739FF, 0x86446EFF, 0xD78E10FF, 0x4C75B7FF, 0xBDBEC6FF, 0x5E7072FF,
	0x46597AFF, 0x656A79FF, 0x5D7E8DFF, 0x58595AFF, 0xD6DAD6FF, 0x9CA1A3FF, 0x335F3FFF, 0x730E1AFF, 0x7B0A2AFF, 0x9F9D94FF,
	0x3B4E78FF, 0x732E3EFF, 0x691E3BFF, 0x96918CFF, 0x515459FF, 0x3F3E45FF, 0xA5A9A7FF, 0x635C5AFF, 0x3D4A68FF, 0x979592FF,
	0x421F21FF, 0x5F272BFF, 0x8494ABFF, 0x767B7CFF, 0x646464FF, 0x5A5752FF, 0x252527FF, 0x2D3A35FF, 0x93A396FF, 0x6D7A88FF,
	0x221918FF, 0x6F675FFF, 0x7C1C2AFF, 0x5F0A15FF, 0x193826FF, 0x5D1B20FF, 0x9D9872FF, 0x7A7560FF, 0x989586FF, 0xADB0B0FF,
	0x848988FF, 0x304F45FF, 0x4D6268FF, 0x162248FF, 0x272F4BFF, 0x7D6256FF, 0x9EA4ABFF, 0x9C8D71FF, 0x6D1822FF, 0x4E6881FF,
	0x9C9C98FF, 0x917347FF, 0x661C26FF, 0x949D9FFF, 0xA4A7A5FF, 0x8E8C46FF, 0x341A1EFF, 0x6A7A8CFF, 0xAAAD8EFF, 0xAB988FFF,
	0x851F2EFF, 0x6F8297FF, 0x585853FF, 0x9AA790FF, 0x601A23FF, 0x20202CFF, 0xA4A096FF, 0xAA9D84FF, 0x78222BFF, 0x0E316DFF,
	0x722A3FFF, 0x7B715EFF, 0x741D28FF, 0x1E2E32FF, 0x4D322FFF, 0x7C1B44FF, 0x2E5B20FF, 0x395A83FF, 0x6D2837FF, 0xA7A28FFF,
	0xAFB1B1FF, 0x364155FF, 0x6D6C6EFF, 0x0F6A89FF, 0x204B6BFF, 0x2B3E57FF, 0x9B9F9DFF, 0x6C8495FF, 0x4D8495FF, 0xAE9B7FFF,
	0x406C8FFF, 0x1F253BFF, 0xAB9276FF, 0x134573FF, 0x96816CFF, 0x64686AFF, 0x105082FF, 0xA19983FF, 0x385694FF, 0x525661FF,
	0x7F6956FF, 0x8C929AFF, 0x596E87FF, 0x473532FF, 0x44624FFF, 0x730A27FF, 0x223457FF, 0x640D1BFF, 0xA3ADC6FF, 0x695853FF,
	0x9B8B80FF, 0x620B1CFF, 0x5B5D5EFF, 0x624428FF, 0x731827FF, 0x1B376DFF, 0xEC6AAEFF, 0x000000FF,
	0x177517FF, 0x210606FF, 0x125478FF, 0x452A0DFF, 0x571E1EFF, 0x010701FF, 0x25225AFF, 0x2C89AAFF, 0x8A4DBDFF, 0x35963AFF,
	0xB7B7B7FF, 0x464C8DFF, 0x84888CFF, 0x817867FF, 0x817A26FF, 0x6A506FFF, 0x583E6FFF, 0x8CB972FF, 0x824F78FF, 0x6D276AFF,
	0x1E1D13FF, 0x1E1306FF, 0x1F2518FF, 0x2C4531FF, 0x1E4C99FF, 0x2E5F43FF, 0x1E9948FF, 0x1E9999FF, 0x999976FF, 0x7C8499FF,
	0x992E1EFF, 0x2C1E08FF, 0x142407FF, 0x993E4DFF, 0x1E4C99FF, 0x198181FF, 0x1A292AFF, 0x16616FFF, 0x1B6687FF, 0x6C3F99FF,
	0x481A0EFF, 0x7A7399FF, 0x746D99FF, 0x53387EFF, 0x222407FF, 0x3E190CFF, 0x46210EFF, 0x991E1EFF, 0x8D4C8DFF, 0x805B80FF,
	0x7B3E7EFF, 0x3C1737FF, 0x733517FF, 0x781818FF, 0x83341AFF, 0x8E2F1CFF, 0x7E3E53FF, 0x7C6D7CFF, 0x020C02FF, 0x072407FF,
	0x163012FF, 0x16301BFF, 0x642B4FFF, 0x368452FF, 0x999590FF, 0x818D96FF, 0x99991EFF, 0x7F994CFF, 0x839292FF, 0x788222FF,
	0x2B3C99FF, 0x3A3A0BFF, 0x8A794EFF, 0x0E1F49FF, 0x15371CFF, 0x15273AFF, 0x375775FF, 0x060820FF, 0x071326FF, 0x20394BFF,
	0x2C5089FF, 0x15426CFF, 0x103250FF, 0x241663FF, 0x692015FF, 0x8C8D94FF, 0x516013FF, 0x090F02FF, 0x8C573AFF, 0x52888EFF,
	0x995C52FF, 0x99581EFF, 0x993A63FF, 0x998F4EFF, 0x99311EFF, 0x0D1842FF, 0x521E1EFF, 0x42420DFF, 0x4C991EFF, 0x082A1DFF,
	0x96821DFF, 0x197F19FF, 0x3B141FFF, 0x745217FF, 0x893F8DFF, 0x7E1A6CFF, 0x0B370BFF, 0x27450DFF, 0x071F24FF, 0x784573FF,
	0x8A653AFF, 0x732617FF, 0x319490FF, 0x56941DFF, 0x59163DFF, 0x1B8A2FFF, 0x38160BFF, 0x041804FF, 0x355D8EFF, 0x2E3F5BFF,
	0x561A28FF, 0x4E0E27FF, 0x706C67FF, 0x3B3E42FF, 0x2E2D33FF, 0x7B7E7DFF, 0x4A4442FF, 0x28344EFF
};
stock VehicleModelToPaintjobNum(modelid) {
	switch(modelid) {
		case 483: return 1;
		case 575: return 2;
		case 534..536,558..562,565,567,576: return 3;
	}
	return 0;
}
new VinylJob[MAX_PLAYERS];
new PrimaryColor[MAX_PLAYERS];
new SecondaryColor[MAX_PLAYERS];
new RepaintValue[MAX_PLAYERS];
new bool:ChangedPrimaryColor[MAX_PLAYERS];
new bool:ChangedSecondaryColor[MAX_PLAYERS];
new bool:ChangedVinylJob[MAX_PLAYERS];
new const CustomTypeName[12][15] = {"Spoilers","Hoods","Wheels","Front bumpers","Rear bumpers","Vents","Roofs","Exhausts","Sideskirts","Lights","Nitro","Hydraulics"};
new TypeBorder[12] = {20,4,17,23,22,2,16,29,20,2,3,1};
new CustomType[MAX_PLAYERS];
new CustomListNum[MAX_PLAYERS];
new CustomLimitNum[MAX_PLAYERS];
stock IsVehicleUpgradeCompatible(model,componentid) {
	switch(model) {
		case 400: {
			switch(componentid) {
				case 1008,1009,1010,1013,1018,1019,1020,1021,1024,1025,1073,1074,1075,1076,1077,1078,1079,1080,1081,1082,
				1083,1084,1085,1087,1096,1097,1098: return 1;
			}
		}
		case 401: {
			switch(componentid) {
				case 1001,1003,1004,1005,1006,1007,1008,1009,1010,1013,1017,1019,1020,1025,1073,1074,1075,1076,1077,1078,
				1079,1080,1081,1082,1083,1084,1085,1087,1096,1097,1098,1142,1143,1144: return 1;
			}
		}
		case 404: {
			switch(componentid) {
				case 1000,1002,1007,1008,1009,1010,1013,1016,1017,1019,1020,1021,1025,1073,1074,1075,1076,1077,1078,1079,
				1080,1081,1082,1083,1084,1085,1087,1096,1097,1098: return 1;
			}
		}
		case 405: {
			switch(componentid) {
				case 1000,1001,1008,1009,1010,1014,1018,1019,1020,1021,1023,1025,1073,1074,1075,1076,1077,1078,1079,1080,
				1081,1082,1083,1084,1085,1087,1096,1097,1098: return 1;
			}
		}
		case 410: {
			switch(componentid) {
				case 1001,1003,1007,1008,1009,1010,1013,1017,1019,1020,1021,1023,1024,1025,1073,1074,1075,1076,1077,1078,
				1079,1080,1081,1082,1083,1084,1085,1087,1096,1097,1098: return 1;
			}
		}
		case 415: {
			switch(componentid) {
				case 1001,1003,1007,1008,1009,1010,1017,1018,1019,1023,1025,1073,1074,1075,1076,1077,1078,1079,1080,1081,
				1082,1083,1084,1085,1087,1096,1097,1098: return 1;
			}
		}
		case 418: {
			switch(componentid) {
				case 1002,1006,1008,1009,1010,1016,1020,1021,1025,1073,1074,1075,1076,1077,1078,1079,1080,1081,1082,1083,
				1084,1085,1087,1096,1097,1098: return 1;
			}
		}
		case 420: {
			switch(componentid) {
				case 1001,1003,1004,1005,1008,1009,1010,1019,1021,1025,1073,1074,1075,1076,1077,1078,1079,1080,1081,1082,
				1083,1084,1085,1087,1096,1097,1098: return 1;
			}
		}
		case 421: {
			switch(componentid) {
				case 1000,1008,1009,1010,1014,1016,1018,1019,1020,1021,1023,1025,1073,1074,1075,1076,1077,1078,1079,1080,
				1081,1082,1083,1084,1085,1087,1096,1097,1098: return 1;
			}
		}
		case 422: {
			switch(componentid) {
				case 1007,1008,1009,1010,1013,1017,1019,1020,1021,1025,1073,1074,1075,1076,1077,1078,1079,1080,1081,1082,
				1083,1084,1085,1087,1096,1097,1098: return 1;
			}
		}
		case 426: {
			switch(componentid) {
				case 1001,1003,1004,1005,1006,1008,1009,1010,1019,1021,1025,1073,1074,1075,1076,1077,1078,1079,1080,1081,
				1082,1083,1084,1085,1087,1096,1097,1098: return 1;
			}
		}
		case 436: {
			switch(componentid) {
				case 1001,1003,1006,1007,1008,1009,1010,1013,1017,1019,1020,1021,1022,1025,1073,1074,1075,1076,1077,1078,
				1079,1080,1081,1082,1083,1084,1085,1087,1096,1097,1098: return 1;
			}
		}
		case 439: {
			switch(componentid) {
				case 1001,1003,1007,1008,1009,1010,1013,1017,1023,1025,1073,1074,1075,1076,1077,1078,1079,1080,1081,1082,
				1083,1084,1085,1087,1096,1097,1098,1142,1143,1144,1145: return 1;
			}
		}
		case 477: {
			switch(componentid) {
				case 1006,1007,1008,1009,1010,1017,1018,1019,1020,1021,1025,1073,1074,1075,1076,1077,1078,1079,1080,1081,
				1082,1083,1084,1085,1087,1096,1097,1098: return 1;
			}
		}
		case 478: {
			switch(componentid) {
				case 1004,1005,1008,1009,1010,1012,1013,1020,1021,1022,1024,1025,1073,1074,1075,1076,1077,1078,1079,1080,
				1081,1082,1083,1084,1085,1087,1096,1097,1098: return 1;
			}
		}
		case 489: {
			switch(componentid) {
				case 1000,1002,1004,1005,1006,1008,1009,1010,1013,1016,1018,1019,1020,1024,1025,1073,1074,1075,1076,1077,
				1078,1079,1080,1081,1082,1083,1084,1085,1087,1096,1097,1098: return 1;
			}
		}
		case 491: {
			switch(componentid) {
				case 1003,1007,1008,1009,1010,1014,1017,1018,1019,1020,1021,1023,1025,1073,1074,1075,1076,1077,1078,1079,
				1080,1081,1082,1083,1084,1085,1087,1096,1097,1098,1142,1143,1144,1145: return 1;
			}
		}
		case 492: {
			switch(componentid) {
				case 1000,1004,1005,1006,1008,1009,1010,1016,1025,1073,1074,1075,1076,1077,1078,1079,1080,1081,1082,1083,
				1084,1085,1087,1096,1097,1098: return 1;
			}
		}
		case 496: {
			switch(componentid) {
				case 1001,1002,1003,1006,1007,1008,1009,1010,1011,1017,1019,1020,1023,1025,1073,1074,1075,1076,1077,1078,
				1079,1080,1081,1082,1083,1084,1085,1087,1096,1097,1098,1142,1143: return 1;
			}
		}
		case 500: {
			switch(componentid) {
				case 1008,1009,1010,1013,1019,1020,1021,1024,1025,1073,1074,1075,1076,1077,1078,1079,1080,1081,1082,1083,
				1084,1085,1087,1096,1097,1098: return 1;
			}
		}
		case 516: {
			switch(componentid) {
				case 1000,1002,1004,1007,1008,1009,1010,1015,1016,1017,1018,1019,1020,1021,1025,1073,1074,1075,1076,1077,
				1078,1079,1080,1081,1082,1083,1084,1085,1087,1096,1097,1098: return 1;
			}
		}
		case 517: {
			switch(componentid) {
				case 1002,1003,1007,1008,1009,1010,1016,1017,1018,1019,1020,1023,1025,1073,1074,1075,1076,1077,1078,1079,
				1080,1081,1082,1083,1084,1085,1087,1096,1097,1098,1142,1143,1144,1145: return 1;
			}
		}
		case 518: {
			switch(componentid) {
				case 1001,1003,1005,1006,1007,1008,1009,1010,1013,1017,1018,1020,1023,1025,1073,1074,1075,1076,1077,1078,
				1079,1080,1081,1082,1083,1084,1085,1087,1096,1097,1098,1142,1143,1144,1145: return 1;
			}
		}
		case 527: {
			switch(componentid) {
				case 1001,1007,1008,1009,1010,1014,1015,1017,1018,1020,1021,1025,1073,1074,1075,1076,1077,1078,1079,1080,
				1081,1082,1083,1084,1085,1087,1096,1097,1098: return 1;
			}
		}
		case 529: {
			switch(componentid) {
				case 1001,1003,1006,1007,1008,1009,1010,1011,1012,1017,1018,1019,1020,1023,1025,1073,1074,1075,1076,1077,
				1078,1079,1080,1081,1082,1083,1084,1085,1087,1096,1097,1098: return 1;
			}
		}
		case 534: {
			switch(componentid) {
				case 1008,1009,1010,1025,1073,1074,1075,1076,1077,1078,1079,1080,1081,1082,1083,1084,1085,1087,1096,1097,
				1098,1100,1101,1106,1122,1123,1124,1125,1126,1127,1178,1179,1180,1185: return 1;
			}
		}
		case 535: {
			switch(componentid) {
				case 1008,1009,1010,1025,1073,1074,1075,1076,1077,1078,1079,1080,1081,1082,1083,1084,1085,1087,1096,1097,
				1098,1109,1110,1113,1114,1115,1116,1117,1118,1119,1120,1121: return 1;
			}
		}
		case 536: {
			switch(componentid) {
				case 1008,1009,1010,1025,1073,1074,1075,1076,1077,1078,1079,1080,1081,1082,1083,1084,1085,1087,1096,1097,
				1098,1103,1104,1105,1107,1108,1128,1181,1182,1183,1184: return 1;
			}
		}
		case 540: {
			switch(componentid) {
				case 1001,1004,1006,1007,1008,1009,1010,1017,1018,1019,1020,1023,1024,1025,1073,1074,1075,1076,1077,1078,
				1079,1080,1081,1082,1083,1084,1085,1087,1096,1097,1098,1142,1143,1144,1145: return 1;
			}
		}
		case 542: {
			switch(componentid) {
				case 1008,1009,1010,1014,1015,1018,1019,1020,1021,1025,1073,1074,1075,1076,1077,1078,1079,1080,1081,1082,
				1083,1084,1085,1087,1096,1097,1098,1144,1145: return 1;
			}
		}
		case 546: {
			switch(componentid) {
				case 1001,1002,1004,1006,1007,1008,1009,1010,1017,1018,1019,1023,1024,1025,1073,1074,1075,1076,1077,1078,
				1079,1080,1081,1082,1083,1084,1085,1087,1096,1097,1098,1142,1143,1144,1145: return 1;
			}
		}
		case 547: {
			switch(componentid) {
				case 1000,1003,1008,1009,1010,1016,1018,1019,1020,1021,1025,1073,1074,1075,1076,1077,1078,1079,1080,1081,
				1082,1083,1084,1085,1087,1096,1097,1098,1142,1143: return 1;
			}
		}
		case 549: {
			switch(componentid) {
				case 1001,1003,1007,1008,1009,1010,1011,1012,1017,1018,1019,1020,1023,1025,1073,1074,1075,1076,1077,1078,
				1079,1080,1081,1082,1083,1084,1085,1087,1096,1097,1098,1142,1143,1144,1145: return 1;
			}
		}
		case 550: {
			switch(componentid) {
				case 1001,1003,1004,1005,1006,1008,1009,1010,1018,1019,1020,1023,1025,1073,1074,1075,1076,1077,1078,1079,
				1080,1081,1082,1083,1084,1085,1087,1096,1097,1098,1142,1143,1144,1145: return 1;
			}
		}
		case 551: {
			switch(componentid) {
				case 1002,1003,1005,1006,1008,1009,1010,1016,1018,1019,1020,1021,1023,1025,1073,1074,1075,1076,1077,1078,
				1079,1080,1081,1082,1083,1084,1085,1087,1096,1097,1098: return 1;
			}
		}
		case 558: {
			switch(componentid) {
				case 1008,1009,1010,1025,1073,1074,1075,1076,1077,1078,1079,1080,1081,1082,1083,1084,1085,1087,1088,1089,
				1090,1091,1092,1093,1094,1095,1096,1097,1098,1163,1164,1165,1166,1167,1168: return 1;
			}
		}
		case 559: {
			switch(componentid) {
				case 1008,1009,1010,1025,1065,1066,1067,1068,1069,1070,1071,1072,1073,1074,1075,1076,1077,1078,1079,1080,
				1081,1082,1083,1084,1085,1087,1096,1097,1098,1158,1159,1160,1161,1162,1173: return 1;
			}
		}
		case 560: {
			switch(componentid) {
				case 1008,1009,1010,1025,1026,1027,1028,1029,1030,1031,1032,1033,1073,1074,1075,1076,1077,1078,1079,1080,
				1081,1082,1083,1084,1085,1087,1096,1097,1098,1138,1139,1140,1141,1169,1170: return 1;
			}
		}
		case 561: {
			switch(componentid) {
				case 1008,1009,1010,1025,1055,1056,1057,1058,1059,1060,1061,1062,1063,1064,1073,1074,1075,1076,1077,1078,
				1079,1080,1081,1082,1083,1084,1085,1087,1096,1097,1098,1154,1155,1156,1157: return 1;
			}
		}
		case 562: {
			switch(componentid) {
				case 1008,1009,1010,1025,1034,1035,1036,1037,1038,1039,1040,1041,1073,1074,1075,1076,1077,1078,1079,1080,
				1081,1082,1083,1084,1085,1087,1096,1097,1098,1146,1147,1148,1149,1171,1172: return 1;
			}
		}
		case 565: {
			switch(componentid) {
				case 1008,1009,1010,1025,1045,1046,1047,1048,1049,1050,1051,1052,1053,1054,1073,1074,1075,1076,1077,1078,
				1079,1080,1081,1082,1083,1084,1085,1087,1096,1097,1098,1150,1151,1152,1153: return 1;
			}
		}
		case 567: {
			switch(componentid) {
				case 1008,1009,1010,1025,1073,1074,1075,1076,1077,1078,1079,1080,1081,1082,1083,1084,1085,1087,1096,1097,
				1098,1102,1129,1130,1131,1132,1133,1186,1187,1188,1189: return 1;
			}
		}
		case 575: {
			switch(componentid) {
				case 1008,1009,1010,1025,1042,1043,1044,1073,1074,1075,1076,1077,1078,1079,1080,1081,1082,1083,1084,1085,
				1087,1096,1097,1098,1099,1174,1175,1176,1177: return 1;
			}
		}
		case 576: {
			switch(componentid) {
				case 1008,1009,1010,1025,1073,1074,1075,1076,1077,1078,1079,1080,1081,1082,1083,1084,1085,1087,1096,1097,
				1098,1134,1135,1136,1137,1190,1191,1192,1193: return 1;
			}
		}
		case 580: {
			switch(componentid) {
				case 1001,1006,1007,1008,1009,1010,1017,1018,1020,1023,1025,1073,1074,1075,1076,1077,1078,1079,1080,1081,
				1082,1083,1084,1085,1087,1096,1097,1098: return 1;
			}
		}
		case 585: {
			switch(componentid) {
				case 1001,1003,1006,1007,1008,1009,1010,1013,1017,1018,1019,1020,1023,1025,1073,1074,1075,1076,1077,1078,
				1079,1080,1081,1082,1083,1084,1085,1087,1096,1097,1098,1142,1143,1144,1145: return 1;
			}
		}
		case 589: {
			switch(componentid) {
				case 1000,1004,1005,1006,1007,1008,1009,1010,1013,1016,1017,1018,1020,1024,1025,1073,1074,1075,1076,1077,
				1078,1079,1080,1081,1082,1083,1084,1085,1087,1096,1097,1098,1144,1145: return 1;
			}
		}
		case 600: {
			switch(componentid) {
				case 1004,1005,1006,1007,1008,1009,1010,1013,1017,1018,1020,1022,1025,1073,1074,1075,1076,1077,1078,1079,
				1080,1081,1082,1083,1084,1085,1087,1096,1097,1098: return 1;
			}
		}
		case 603: {
			switch(componentid) {
				case 1001,1006,1007,1008,1009,1010,1017,1018,1019,1020,1023,1024,1025,1073,1074,1075,1076,1077,1078,1079,
				1080,1081,1082,1083,1084,1085,1087,1096,1097,1098,1142,1143,1144,1145: return 1;
			}
		}
		case 402,403,406..409,411..414,416,419,423,424,427..429,431..435,437,438,440..445,448,450,451,455..459,461..463,
		466..468,470,471,474,475,479..486,490,494,495,498,499,502..510,514,515,521..526,528,530..533,541,552,543..545,554..557,
		566,568,578,571..574,579,581..584,586..588,591,594,596..599,601,602,604..611: {
			switch(componentid) {
				case 1008,1009,1010,1025,1073,1074,1075,1076,1077,1078,1079,1080,1081,1082,1083,1084,1085,1087,1096,1097,1098: return 1;
			}
		}
	}
	return 0;
}
stock CameraViewChange(playerid,id) {
	new Float:x,Float:y,Float:z,Float:x2,Float:y2,Float:angle,idx = GetPlayerVehicleID(playerid),Float:ZX,Float:ZY,Float:ZZ;
	GetPlayerCameraPos(playerid,x,y,z);
	GetVehiclePos(idx,ZX,ZY,ZZ);
	switch(id) {
		case 0,4,7,10: {
			GetVehicleZAngle(idx, angle);
			x2 = ZX + (5 * floatsin(-angle + 180.0, degrees));
			y2 = ZY + (5 * floatcos(-angle + 180.0, degrees));
			InterpolateCameraPos(playerid,x,y,z,x2,y2,ZZ+1,1500);
		}
		case 2,8: {
			GetVehicleZAngle(idx, angle);
			x2 = ZX + (5 * floatsin(-angle + 90.0, degrees));
			y2 = ZY + (5 * floatcos(-angle + 90.0, degrees));
			InterpolateCameraPos(playerid,x,y,z,x2,y2,ZZ+1,1500);
		}
		case 1,3,5,6,9: {
			GetVehicleZAngle(idx, angle);
			x2 = ZX + (5 * floatsin(-angle + 0.0, degrees));
			y2 = ZY + (5 * floatcos(-angle + 0.0, degrees));
			InterpolateCameraPos(playerid,x,y,z,x2,y2,ZZ+1,1500);
		}
	}
	InterpolateCameraLookAt(playerid,ZX,ZY,ZZ,ZX,ZY,ZZ,1500);
	return 1;
}
stock load_tune() {
	ColorTD[0] = TextDrawCreate(642.500000, 121.666664, "usebox");
	TextDrawLetterSize(ColorTD[0], 0.000000, 23.846313);
	TextDrawTextSize(ColorTD[0], 485.500000, 0.000000);
	TextDrawAlignment(ColorTD[0], 1);
	TextDrawColor(ColorTD[0], 0);
	TextDrawUseBox(ColorTD[0], true);
	TextDrawBoxColor(ColorTD[0], 102);
	TextDrawSetShadow(ColorTD[0], 0);
	TextDrawSetOutline(ColorTD[0], 0);
	TextDrawFont(ColorTD[0], 0);
	ColorTD[1] = TextDrawCreate(493.842651, 121.333335, "Paint catalog");
	TextDrawLetterSize(ColorTD[1], 0.286500, 1.372498);
	TextDrawAlignment(ColorTD[1], 1);
	TextDrawColor(ColorTD[1], 0xf5EAFFC99);
	TextDrawSetShadow(ColorTD[1], 0);
	TextDrawSetOutline(ColorTD[1], 0);
	TextDrawBackgroundColor(ColorTD[1], 51);
	TextDrawFont(ColorTD[1], 2);
	TextDrawSetProportional(ColorTD[1], true);
	ColorTD[2] = TextDrawCreate(563.000000, 139.416641, "Primary color");
	TextDrawLetterSize(ColorTD[2], 0.302998, 1.290832);
	TextDrawAlignment(ColorTD[2], 2);
	TextDrawColor(ColorTD[2], -1);
	TextDrawSetShadow(ColorTD[2], 0);
	TextDrawSetOutline(ColorTD[2], 1);
	TextDrawBackgroundColor(ColorTD[2], 51);
	TextDrawFont(ColorTD[2], 2);
	TextDrawSetProportional(ColorTD[2], true);
	ColorTD[3] = TextDrawCreate(563.000000, 202.416580, "Secondary color");
	TextDrawLetterSize(ColorTD[3], 0.302998, 1.290832);
	TextDrawAlignment(ColorTD[3], 2);
	TextDrawColor(ColorTD[3], -1);
	TextDrawSetShadow(ColorTD[3], 0);
	TextDrawSetOutline(ColorTD[3], 1);
	TextDrawBackgroundColor(ColorTD[3], 51);
	TextDrawFont(ColorTD[3], 2);
	TextDrawSetProportional(ColorTD[3], true);
	ColorTD[4] = TextDrawCreate(564.000000, 257.249877, "Vinyl");
	TextDrawLetterSize(ColorTD[4], 0.302998, 1.290832);
	TextDrawAlignment(ColorTD[4], 2);
	TextDrawColor(ColorTD[4], -1);
	TextDrawSetShadow(ColorTD[4], 0);
	TextDrawSetOutline(ColorTD[4], 1);
	TextDrawBackgroundColor(ColorTD[4], 51);
	TextDrawFont(ColorTD[4], 2);
	TextDrawSetProportional(ColorTD[4], true);
	ColorTD[5] = TextDrawCreate(615.000000, 168.583389, "LD_BEAT:right");
	TextDrawLetterSize(ColorTD[5], 0.000000, 0.000000);
	TextDrawTextSize(ColorTD[5], 15.500000, 15.750000);
	TextDrawAlignment(ColorTD[5], 1);
	TextDrawColor(ColorTD[5], -1);
	TextDrawSetShadow(ColorTD[5], 0);
	TextDrawSetOutline(ColorTD[5], 0);
	TextDrawFont(ColorTD[5], 4);
	TextDrawSetSelectable(ColorTD[5], true);
	ColorTD[6] = TextDrawCreate(494.500000, 169.166595, "LD_BEAT:left");
	TextDrawLetterSize(ColorTD[6], 0.000000, 0.000000);
	TextDrawTextSize(ColorTD[6], 15.500000, 15.750000);
	TextDrawAlignment(ColorTD[6], 1);
	TextDrawColor(ColorTD[6], -1);
	TextDrawSetShadow(ColorTD[6], 0);
	TextDrawSetOutline(ColorTD[6], 0);
	TextDrawFont(ColorTD[6], 4);
	TextDrawSetSelectable(ColorTD[6], true);
	ColorTD[7] = TextDrawCreate(613.500000, 231.583450, "LD_BEAT:right");
	TextDrawLetterSize(ColorTD[7], 0.000000, 0.000000);
	TextDrawTextSize(ColorTD[7], 15.500000, 15.750000);
	TextDrawAlignment(ColorTD[7], 1);
	TextDrawColor(ColorTD[7], -1);
	TextDrawSetShadow(ColorTD[7], 0);
	TextDrawSetOutline(ColorTD[7], 0);
	TextDrawFont(ColorTD[7], 4);
	TextDrawSetSelectable(ColorTD[7], true);
	ColorTD[8] = TextDrawCreate(495.000000, 231.583251, "LD_BEAT:left");
	TextDrawLetterSize(ColorTD[8], 0.000000, 0.000000);
	TextDrawTextSize(ColorTD[8], 15.500000, 15.750000);
	TextDrawAlignment(ColorTD[8], 1);
	TextDrawColor(ColorTD[8], -1);
	TextDrawSetShadow(ColorTD[8], 0);
	TextDrawSetOutline(ColorTD[8], 0);
	TextDrawFont(ColorTD[8], 4);
	TextDrawSetSelectable(ColorTD[8], true);
	ColorTD[9] = TextDrawCreate(547.000000, 161.000122, "LD_SPAC:white");
	TextDrawLetterSize(ColorTD[9], 0.000000, 0.000000);
	TextDrawTextSize(ColorTD[9], 30.500000, 30.333311);
	TextDrawAlignment(ColorTD[9], 1);
	TextDrawColor(ColorTD[9], -1);
	TextDrawSetShadow(ColorTD[9], 0);
	TextDrawSetOutline(ColorTD[9], 0);
	TextDrawFont(ColorTD[9], 4);
	ColorTD[10] = TextDrawCreate(547.000000, 223.999923, "LD_SPAC:white");
	TextDrawLetterSize(ColorTD[10], 0.000000, 0.000000);
	TextDrawTextSize(ColorTD[10], 30.500000, 30.333311);
	TextDrawAlignment(ColorTD[10], 1);
	TextDrawColor(ColorTD[10], -1);
	TextDrawSetShadow(ColorTD[10], 0);
	TextDrawSetOutline(ColorTD[10], 0);
	TextDrawFont(ColorTD[10], 4);
	ColorTD[11] = TextDrawCreate(517.000000, 273.583496, "None");
	TextDrawLetterSize(ColorTD[11], 0.295498, 1.185832);
	TextDrawTextSize(ColorTD[11], 5.000000, 31.499998);
	TextDrawAlignment(ColorTD[11], 2);
	TextDrawColor(ColorTD[11], -1);
	TextDrawUseBox(ColorTD[11], true);
	TextDrawBoxColor(ColorTD[11], 255);
	TextDrawSetShadow(ColorTD[11], 0);
	TextDrawSetOutline(ColorTD[11], 1);
	TextDrawBackgroundColor(ColorTD[11], 51);
	TextDrawFont(ColorTD[11], 2);
	TextDrawSetProportional(ColorTD[11], true);
	TextDrawSetSelectable(ColorTD[11], true);
	ColorTD[12] = TextDrawCreate(561.500000, 273.583435, "Type 1");
	TextDrawLetterSize(ColorTD[12], 0.295498, 1.185832);
	TextDrawTextSize(ColorTD[12], 5.500000, 40.249980);
	TextDrawAlignment(ColorTD[12], 2);
	TextDrawColor(ColorTD[12], -1);
	TextDrawUseBox(ColorTD[12], true);
	TextDrawBoxColor(ColorTD[12], 255);
	TextDrawSetShadow(ColorTD[12], 0);
	TextDrawSetOutline(ColorTD[12], 1);
	TextDrawBackgroundColor(ColorTD[12], 51);
	TextDrawFont(ColorTD[12], 2);
	TextDrawSetProportional(ColorTD[12], true);
	TextDrawSetSelectable(ColorTD[12], true);
	ColorTD[13] = TextDrawCreate(612.000000, 273.583496, "Type 2");
	TextDrawLetterSize(ColorTD[13], 0.295498, 1.185832);
	TextDrawTextSize(ColorTD[13], 5.000000, 43.749973);
	TextDrawAlignment(ColorTD[13], 2);
	TextDrawColor(ColorTD[13], -1);
	TextDrawUseBox(ColorTD[13], true);
	TextDrawBoxColor(ColorTD[13], 255);
	TextDrawSetShadow(ColorTD[13], 0);
	TextDrawSetOutline(ColorTD[13], 1);
	TextDrawBackgroundColor(ColorTD[13], 51);
	TextDrawFont(ColorTD[13], 2);
	TextDrawSetProportional(ColorTD[13], true);
	TextDrawSetSelectable(ColorTD[13], true);
	ColorTD[14] = TextDrawCreate(561.500000, 292.250061, "Type 3");
	TextDrawLetterSize(ColorTD[14], 0.295498, 1.185832);
	TextDrawTextSize(ColorTD[14], 6.000000, 42.583293);
	TextDrawAlignment(ColorTD[14], 2);
	TextDrawColor(ColorTD[14], -1);
	TextDrawUseBox(ColorTD[14], true);
	TextDrawBoxColor(ColorTD[14], 255);
	TextDrawSetShadow(ColorTD[14], 0);
	TextDrawSetOutline(ColorTD[14], 1);
	TextDrawBackgroundColor(ColorTD[14], 51);
	TextDrawFont(ColorTD[14], 2);
	TextDrawSetProportional(ColorTD[14], true);
	TextDrawSetSelectable(ColorTD[14], true);
	ColorTD[15] = TextDrawCreate(517.000000, 318.500091, "Apply");
	TextDrawLetterSize(ColorTD[15], 0.317499, 1.296666);
	TextDrawTextSize(ColorTD[15], 10.500000, 43.166648);
	TextDrawAlignment(ColorTD[15], 2);
	TextDrawColor(ColorTD[15], -1);
	TextDrawUseBox(ColorTD[15], true);
	TextDrawBoxColor(ColorTD[15], 255);
	TextDrawSetShadow(ColorTD[15], 0);
	TextDrawSetOutline(ColorTD[15], 1);
	TextDrawBackgroundColor(ColorTD[15], 51);
	TextDrawFont(ColorTD[15], 2);
	TextDrawSetProportional(ColorTD[15], true);
	TextDrawSetSelectable(ColorTD[15], true);
	ColorTD[16] = TextDrawCreate(496.500000, 271.249938, "(       )");
	TextDrawLetterSize(ColorTD[16], 0.295998, 1.518334);
	TextDrawAlignment(ColorTD[16], 1);
	TextDrawColor(ColorTD[16], 0xf5EAFFC99);
	TextDrawSetShadow(ColorTD[16], 0);
	TextDrawSetOutline(ColorTD[16], 1);
	TextDrawBackgroundColor(ColorTD[16], 51);
	TextDrawFont(ColorTD[16], 3);
	TextDrawSetProportional(ColorTD[16], true);
	ColorTD[17] = TextDrawCreate(537.500000, 270.083221, "(           )");
	TextDrawLetterSize(ColorTD[17], 0.350998, 1.763334);
	TextDrawAlignment(ColorTD[17], 1);
	TextDrawColor(ColorTD[17], 0xf5EAFFC99);
	TextDrawSetShadow(ColorTD[17], 0);
	TextDrawSetOutline(ColorTD[17], 1);
	TextDrawBackgroundColor(ColorTD[17], 51);
	TextDrawFont(ColorTD[17], 3);
	TextDrawSetProportional(ColorTD[17], true);
	ColorTD[18] = TextDrawCreate(587.000000, 270.083129, "(           )");
	TextDrawLetterSize(ColorTD[18], 0.370997, 1.792497);
	TextDrawAlignment(ColorTD[18], 1);
	TextDrawColor(ColorTD[18], 0xf5EAFFC99);
	TextDrawSetShadow(ColorTD[18], 0);
	TextDrawSetOutline(ColorTD[18], 1);
	TextDrawBackgroundColor(ColorTD[18], 51);
	TextDrawFont(ColorTD[18], 3);
	TextDrawSetProportional(ColorTD[18], true);
	ColorTD[19] = TextDrawCreate(537.000000, 288.749755, "(           )");
	TextDrawLetterSize(ColorTD[19], 0.362996, 1.786666);
	TextDrawAlignment(ColorTD[19], 1);
	TextDrawColor(ColorTD[19], 0xf5EAFFC99);
	TextDrawSetShadow(ColorTD[19], 0);
	TextDrawSetOutline(ColorTD[19], 1);
	TextDrawBackgroundColor(ColorTD[19], 51);
	TextDrawFont(ColorTD[19], 3);
	TextDrawSetProportional(ColorTD[19], true);
	//======================================
	CustomTD[0] = TextDrawCreate(642.000000, 121.666664, "usebox");
	TextDrawLetterSize(CustomTD[0], 0.000000, 23.346323);
	TextDrawTextSize(CustomTD[0], 485.500000, 0.000000);
	TextDrawAlignment(CustomTD[0], 1);
	TextDrawColor(CustomTD[0], 0);
	TextDrawUseBox(CustomTD[0], true);
	TextDrawBoxColor(CustomTD[0], 102);
	TextDrawSetShadow(CustomTD[0], 0);
	TextDrawSetOutline(CustomTD[0], 0);
	TextDrawFont(CustomTD[0], 0);
	CustomTD[1] = TextDrawCreate(493.842651, 121.333335, "TUNING");
	TextDrawLetterSize(CustomTD[1], 0.286500, 1.372498);
	TextDrawAlignment(CustomTD[1], 1);
	TextDrawColor(CustomTD[1], 0xf5EAFFC99);
	TextDrawSetShadow(CustomTD[1], 0);
	TextDrawSetOutline(CustomTD[1], 0);
	TextDrawBackgroundColor(CustomTD[1], 51);
	TextDrawFont(CustomTD[1], 2);
	TextDrawSetProportional(CustomTD[1], true);
	CustomTD[2] = TextDrawCreate(622.000000, 137.083312, "LD_BEAT:right");
	TextDrawLetterSize(CustomTD[2], 0.000000, 0.000000);
	TextDrawTextSize(CustomTD[2], 15.500000, 15.750000);
	TextDrawAlignment(CustomTD[2], 1);
	TextDrawColor(CustomTD[2], -1);
	TextDrawSetShadow(CustomTD[2], 0);
	TextDrawSetOutline(CustomTD[2], 0);
	TextDrawFont(CustomTD[2], 4);
	TextDrawSetSelectable(CustomTD[2], true);
	CustomTD[3] = TextDrawCreate(490.500000, 137.083312, "LD_BEAT:left");
	TextDrawLetterSize(CustomTD[3], 0.000000, 0.000000);
	TextDrawTextSize(CustomTD[3], 15.500000, 15.750000);
	TextDrawAlignment(CustomTD[3], 1);
	TextDrawColor(CustomTD[3], -1);
	TextDrawSetShadow(CustomTD[3], 0);
	TextDrawSetOutline(CustomTD[3], 0);
	TextDrawFont(CustomTD[3], 4);
	TextDrawSetSelectable(CustomTD[3], true);
	CustomTD[4] = TextDrawCreate(621.500000, 162.166687, "LD_BEAT:up");
	TextDrawLetterSize(CustomTD[4], 0.000000, 0.000000);
	TextDrawTextSize(CustomTD[4], 15.500000, 15.750035);
	TextDrawAlignment(CustomTD[4], 1);
	TextDrawColor(CustomTD[4], -1);
	TextDrawSetShadow(CustomTD[4], 0);
	TextDrawSetOutline(CustomTD[4], 0);
	TextDrawFont(CustomTD[4], 4);
	TextDrawSetSelectable(CustomTD[4], true);
	CustomTD[5] = TextDrawCreate(617.500000, 164.833435, "usebox");
	TextDrawLetterSize(CustomTD[5], 0.000000, 2.405555);
	TextDrawTextSize(CustomTD[5], 495.500000, 0.000000);
	TextDrawAlignment(CustomTD[5], 1);
	TextDrawColor(CustomTD[5], 0);
	TextDrawUseBox(CustomTD[5], true);
	TextDrawBoxColor(CustomTD[5], 102);
	TextDrawSetShadow(CustomTD[5], 0);
	TextDrawSetOutline(CustomTD[5], 0);
	TextDrawFont(CustomTD[5], 0);
	CustomTD[6] = TextDrawCreate(617.500000, 192.833419, "usebox");
	TextDrawLetterSize(CustomTD[6], 0.000000, 2.405555);
	TextDrawTextSize(CustomTD[6], 496.000000, 0.000000);
	TextDrawAlignment(CustomTD[6], 1);
	TextDrawColor(CustomTD[6], 0);
	TextDrawUseBox(CustomTD[6], true);
	TextDrawBoxColor(CustomTD[6], 102);
	TextDrawSetShadow(CustomTD[6], 0);
	TextDrawSetOutline(CustomTD[6], 0);
	TextDrawFont(CustomTD[6], 0);
	CustomTD[7] = TextDrawCreate(617.500000, 221.416732, "usebox");
	TextDrawLetterSize(CustomTD[7], 0.000000, 2.405555);
	TextDrawTextSize(CustomTD[7], 496.000000, 0.000000);
	TextDrawAlignment(CustomTD[7], 1);
	TextDrawColor(CustomTD[7], 0);
	TextDrawUseBox(CustomTD[7], true);
	TextDrawBoxColor(CustomTD[7], 102);
	TextDrawSetShadow(CustomTD[7], 0);
	TextDrawSetOutline(CustomTD[7], 0);
	TextDrawFont(CustomTD[7], 0);
	CustomTD[8] = TextDrawCreate(617.500000, 249.416610, "usebox");
	TextDrawLetterSize(CustomTD[8], 0.000000, 2.405555);
	TextDrawTextSize(CustomTD[8], 496.000000, 0.000000);
	TextDrawAlignment(CustomTD[8], 1);
	TextDrawColor(CustomTD[8], 0);
	TextDrawUseBox(CustomTD[8], true);
	TextDrawBoxColor(CustomTD[8], 102);
	TextDrawSetShadow(CustomTD[8], 0);
	TextDrawSetOutline(CustomTD[8], 0);
	TextDrawFont(CustomTD[8], 0);
	CustomTD[9] = TextDrawCreate(617.500000, 278.583221, "usebox");
	TextDrawLetterSize(CustomTD[9], 0.000000, 2.405555);
	TextDrawTextSize(CustomTD[9], 496.000000, 0.000000);
	TextDrawAlignment(CustomTD[9], 1);
	TextDrawColor(CustomTD[9], 0);
	TextDrawUseBox(CustomTD[9], true);
	TextDrawBoxColor(CustomTD[9], 102);
	TextDrawSetShadow(CustomTD[9], 0);
	TextDrawSetOutline(CustomTD[9], 0);
	TextDrawFont(CustomTD[9], 0);
	CustomTD[10] = TextDrawCreate(495.000000, 160.416656, "(                          )");
	TextDrawLetterSize(CustomTD[10], 0.479000, 3.069998);
	TextDrawAlignment(CustomTD[10], 1);
	TextDrawColor(CustomTD[10], 0xf5EAFFC99);
	TextDrawSetShadow(CustomTD[10], 0);
	TextDrawSetOutline(CustomTD[10], 0);
	TextDrawBackgroundColor(CustomTD[10], 51);
	TextDrawFont(CustomTD[10], 3);
	TextDrawSetProportional(CustomTD[10], true);
	CustomTD[11] = TextDrawCreate(495.000000, 188.999923, "(                          )");
	TextDrawLetterSize(CustomTD[11], 0.479000, 3.069998);
	TextDrawAlignment(CustomTD[11], 1);
	TextDrawColor(CustomTD[11], 0xf5EAFFC99);
	TextDrawSetShadow(CustomTD[11], 0);
	TextDrawSetOutline(CustomTD[11], 0);
	TextDrawBackgroundColor(CustomTD[11], 51);
	TextDrawFont(CustomTD[11], 3);
	TextDrawSetProportional(CustomTD[11], true);
	CustomTD[12] = TextDrawCreate(495.000000, 217.583343, "(                          )");
	TextDrawLetterSize(CustomTD[12], 0.479000, 3.069998);
	TextDrawAlignment(CustomTD[12], 1);
	TextDrawColor(CustomTD[12], 0xf5EAFFC99);
	TextDrawSetShadow(CustomTD[12], 0);
	TextDrawSetOutline(CustomTD[12], 0);
	TextDrawBackgroundColor(CustomTD[12], 51);
	TextDrawFont(CustomTD[12], 3);
	TextDrawSetProportional(CustomTD[12], true);
	CustomTD[13] = TextDrawCreate(495.000000, 246.166473, "(                          )");
	TextDrawLetterSize(CustomTD[13], 0.479000, 3.069998);
	TextDrawAlignment(CustomTD[13], 1);
	TextDrawColor(CustomTD[13], 0xf5EAFFC99);
	TextDrawSetShadow(CustomTD[13], 0);
	TextDrawSetOutline(CustomTD[13], 0);
	TextDrawBackgroundColor(CustomTD[13], 51);
	TextDrawFont(CustomTD[13], 3);
	TextDrawSetProportional(CustomTD[13], true);
	CustomTD[14] = TextDrawCreate(495.000000, 274.749481, "(                          )");
	TextDrawLetterSize(CustomTD[14], 0.479000, 3.069998);
	TextDrawAlignment(CustomTD[14], 1);
	TextDrawColor(CustomTD[14], 0xf5EAFFC99);
	TextDrawSetShadow(CustomTD[14], 0);
	TextDrawSetOutline(CustomTD[14], 0);
	TextDrawBackgroundColor(CustomTD[14], 51);
	TextDrawFont(CustomTD[14], 3);
	TextDrawSetProportional(CustomTD[14], true);
	CustomTD[15] = TextDrawCreate(553.000000, 171.699954, TranslateText("Íåäîñòóïíî"));
	TextDrawLetterSize(CustomTD[15], 0.326000, 0.818333);
	TextDrawAlignment(CustomTD[15], 1);
	TextDrawColor(CustomTD[15], -16776961);
	TextDrawSetShadow(CustomTD[15], 0);
	TextDrawSetOutline(CustomTD[15], 0);
	TextDrawBackgroundColor(CustomTD[15], 51);
	TextDrawFont(CustomTD[15], 1);
	TextDrawSetProportional(CustomTD[15], true);
	CustomTD[16] = TextDrawCreate(553.000000, 199.699893, TranslateText("Íåäîñòóïíî"));
	TextDrawLetterSize(CustomTD[16], 0.326000, 0.818333);
	TextDrawAlignment(CustomTD[16], 1);
	TextDrawColor(CustomTD[16], -16776961);
	TextDrawSetShadow(CustomTD[16], 0);
	TextDrawSetOutline(CustomTD[16], 0);
	TextDrawBackgroundColor(CustomTD[16], 51);
	TextDrawFont(CustomTD[16], 1);
	TextDrawSetProportional(CustomTD[16], true);
	CustomTD[17] = TextDrawCreate(553.000000, 228.283282, TranslateText("Íåäîñòóïíî"));
	TextDrawLetterSize(CustomTD[17], 0.326000, 0.818333);
	TextDrawAlignment(CustomTD[17], 1);
	TextDrawColor(CustomTD[17], -16776961);
	TextDrawSetShadow(CustomTD[17], 0);
	TextDrawSetOutline(CustomTD[17], 0);
	TextDrawBackgroundColor(CustomTD[17], 51);
	TextDrawFont(CustomTD[17], 1);
	TextDrawSetProportional(CustomTD[17], true);
	CustomTD[18] = TextDrawCreate(553.000000, 257.449847, TranslateText("Íåäîñòóïíî"));
	TextDrawLetterSize(CustomTD[18], 0.326000, 0.818333);
	TextDrawAlignment(CustomTD[18], 1);
	TextDrawColor(CustomTD[18], -16776961);
	TextDrawSetShadow(CustomTD[18], 0);
	TextDrawSetOutline(CustomTD[18], 0);
	TextDrawBackgroundColor(CustomTD[18], 51);
	TextDrawFont(CustomTD[18], 1);
	TextDrawSetProportional(CustomTD[18], true);
	CustomTD[19] = TextDrawCreate(553.000000, 285.449816, TranslateText("Íåäîñòóïíî"));
	TextDrawLetterSize(CustomTD[19], 0.326000, 0.818333);
	TextDrawAlignment(CustomTD[19], 1);
	TextDrawColor(CustomTD[19], -16776961);
	TextDrawSetShadow(CustomTD[19], 0);
	TextDrawSetOutline(CustomTD[19], 0);
	TextDrawBackgroundColor(CustomTD[19], 51);
	TextDrawFont(CustomTD[19], 1);
	TextDrawSetProportional(CustomTD[19], true);
	CustomTD[20] = TextDrawCreate(621.500000, 289.333160, "LD_BEAT:down");
	TextDrawLetterSize(CustomTD[20], 0.000000, 0.000000);
	TextDrawTextSize(CustomTD[20], 15.500000, 15.750000);
	TextDrawAlignment(CustomTD[20], 1);
	TextDrawColor(CustomTD[20], -1);
	TextDrawSetShadow(CustomTD[20], 0);
	TextDrawSetOutline(CustomTD[20], 0);
	TextDrawFont(CustomTD[20], 4);
	TextDrawSetSelectable(CustomTD[20], true);
	CustomTD[21] = TextDrawCreate(516.500000, 314.999816, "Buy");
	TextDrawLetterSize(CustomTD[21], 0.421499, 1.168331);
	TextDrawTextSize(CustomTD[21], 6.000000, 36.166664);
	TextDrawAlignment(CustomTD[21], 2);
	TextDrawColor(CustomTD[21], -1);
	TextDrawUseBox(CustomTD[21], true);
	TextDrawBoxColor(CustomTD[21], 255);
	TextDrawSetShadow(CustomTD[21], 0);
	TextDrawSetOutline(CustomTD[21], 0);
	TextDrawBackgroundColor(CustomTD[21], 51);
	TextDrawFont(CustomTD[21], 2);
	TextDrawSetProportional(CustomTD[21], true);
	TextDrawSetSelectable(CustomTD[21], true);
}
stock load_tunes(playerid) {
	ColorTDPl[playerid][0] = CreatePlayerTextDraw(playerid, 593.500000, 319.666412, "$1000");
	PlayerTextDrawLetterSize(playerid, ColorTDPl[playerid][0], 0.324499, 1.209166);
	PlayerTextDrawAlignment(playerid, ColorTDPl[playerid][0], 1);
	PlayerTextDrawColor(playerid, ColorTDPl[playerid][0], -1);
	PlayerTextDrawSetShadow(playerid, ColorTDPl[playerid][0], 0);
	PlayerTextDrawSetOutline(playerid, ColorTDPl[playerid][0], 1);
	PlayerTextDrawBackgroundColor(playerid, ColorTDPl[playerid][0], 51);
	PlayerTextDrawFont(playerid, ColorTDPl[playerid][0], 2);
	PlayerTextDrawSetProportional(playerid, ColorTDPl[playerid][0], true);
	ColorTDPl[playerid][1] = CreatePlayerTextDraw(playerid, 515.000000, 163.333435, "LD_SPAC:white");
	PlayerTextDrawLetterSize(playerid, ColorTDPl[playerid][1], 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid, ColorTDPl[playerid][1], 26.500000, 26.249990);
	PlayerTextDrawAlignment(playerid, ColorTDPl[playerid][1], 1);
	PlayerTextDrawColor(playerid, ColorTDPl[playerid][1], -16776961);
	PlayerTextDrawSetShadow(playerid, ColorTDPl[playerid][1], 0);
	PlayerTextDrawSetOutline(playerid, ColorTDPl[playerid][1], 0);
	PlayerTextDrawFont(playerid, ColorTDPl[playerid][1], 4);
	ColorTDPl[playerid][2] = CreatePlayerTextDraw(playerid, 549.000000, 163.333633, "LD_SPAC:white");
	PlayerTextDrawLetterSize(playerid, ColorTDPl[playerid][2], 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid, ColorTDPl[playerid][2], 26.500000, 26.249990);
	PlayerTextDrawAlignment(playerid, ColorTDPl[playerid][2], 1);
	PlayerTextDrawColor(playerid, ColorTDPl[playerid][2], -16776961);
	PlayerTextDrawSetShadow(playerid, ColorTDPl[playerid][2], 0);
	PlayerTextDrawSetOutline(playerid, ColorTDPl[playerid][2], 0);
	PlayerTextDrawFont(playerid, ColorTDPl[playerid][2], 4);
	ColorTDPl[playerid][3] = CreatePlayerTextDraw(playerid, 583.500000, 163.333389, "LD_SPAC:white");
	PlayerTextDrawLetterSize(playerid, ColorTDPl[playerid][3], 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid, ColorTDPl[playerid][3], 26.500000, 26.249990);
	PlayerTextDrawAlignment(playerid, ColorTDPl[playerid][3], 1);
	PlayerTextDrawColor(playerid, ColorTDPl[playerid][3], -16776961);
	PlayerTextDrawSetShadow(playerid, ColorTDPl[playerid][3], 0);
	PlayerTextDrawSetOutline(playerid, ColorTDPl[playerid][3], 0);
	PlayerTextDrawFont(playerid, ColorTDPl[playerid][3], 4);
	ColorTDPl[playerid][4] = CreatePlayerTextDraw(playerid, 515.500000, 226.333435, "LD_SPAC:white");
	PlayerTextDrawLetterSize(playerid, ColorTDPl[playerid][4], 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid, ColorTDPl[playerid][4], 26.500000, 26.249990);
	PlayerTextDrawAlignment(playerid, ColorTDPl[playerid][4], 1);
	PlayerTextDrawColor(playerid, ColorTDPl[playerid][4], -16776961);
	PlayerTextDrawSetShadow(playerid, ColorTDPl[playerid][4], 0);
	PlayerTextDrawSetOutline(playerid, ColorTDPl[playerid][4], 0);
	PlayerTextDrawFont(playerid, ColorTDPl[playerid][4], 4);
	ColorTDPl[playerid][5] = CreatePlayerTextDraw(playerid, 549.000000, 226.333404, "LD_SPAC:white");
	PlayerTextDrawLetterSize(playerid, ColorTDPl[playerid][5], 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid, ColorTDPl[playerid][5], 26.500000, 26.249990);
	PlayerTextDrawAlignment(playerid, ColorTDPl[playerid][5], 1);
	PlayerTextDrawColor(playerid, ColorTDPl[playerid][5], -16776961);
	PlayerTextDrawSetShadow(playerid, ColorTDPl[playerid][5], 0);
	PlayerTextDrawSetOutline(playerid, ColorTDPl[playerid][5], 0);
	PlayerTextDrawFont(playerid, ColorTDPl[playerid][5], 4);
	ColorTDPl[playerid][6] = CreatePlayerTextDraw(playerid, 582.500000, 226.916702, "LD_SPAC:white");
	PlayerTextDrawLetterSize(playerid, ColorTDPl[playerid][6], 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid, ColorTDPl[playerid][6], 26.500000, 26.249990);
	PlayerTextDrawAlignment(playerid, ColorTDPl[playerid][6], 1);
	PlayerTextDrawColor(playerid, ColorTDPl[playerid][6], -16776961);
	PlayerTextDrawSetShadow(playerid, ColorTDPl[playerid][6], 0);
	PlayerTextDrawSetOutline(playerid, ColorTDPl[playerid][6], 0);
	PlayerTextDrawFont(playerid, ColorTDPl[playerid][6], 4);
	//=====================================================
	CustomTDPl[playerid][0] = CreatePlayerTextDraw(playerid, 564.000000, 139.416702, "Part type");
	PlayerTextDrawLetterSize(playerid, CustomTDPl[playerid][0], 0.410499, 1.244163);
	PlayerTextDrawTextSize(playerid, CustomTDPl[playerid][0], 11.000000, 107.333282);
	PlayerTextDrawAlignment(playerid, CustomTDPl[playerid][0], 2);
	PlayerTextDrawColor(playerid, CustomTDPl[playerid][0], -1);
	PlayerTextDrawUseBox(playerid, CustomTDPl[playerid][0], true);
	PlayerTextDrawBoxColor(playerid, CustomTDPl[playerid][0], 255);
	PlayerTextDrawSetShadow(playerid, CustomTDPl[playerid][0], 0);
	PlayerTextDrawSetOutline(playerid, CustomTDPl[playerid][0], 1);
	PlayerTextDrawBackgroundColor(playerid, CustomTDPl[playerid][0], 1941040400);
	PlayerTextDrawFont(playerid, CustomTDPl[playerid][0], 1);
	PlayerTextDrawSetProportional(playerid, CustomTDPl[playerid][0], true);
	CustomTDPl[playerid][1] = CreatePlayerTextDraw(playerid, 505.000000, 164.500015, "Part info 1");
	PlayerTextDrawLetterSize(playerid, CustomTDPl[playerid][1], 0.209000, 1.086665);
	PlayerTextDrawAlignment(playerid, CustomTDPl[playerid][1], 1);
	PlayerTextDrawColor(playerid, CustomTDPl[playerid][1], -1);
	PlayerTextDrawSetShadow(playerid, CustomTDPl[playerid][1], 0);
	PlayerTextDrawSetOutline(playerid, CustomTDPl[playerid][1], 0);
	PlayerTextDrawBackgroundColor(playerid, CustomTDPl[playerid][1], 51);
	PlayerTextDrawFont(playerid, CustomTDPl[playerid][1], 2);
	PlayerTextDrawSetProportional(playerid, CustomTDPl[playerid][1], true);
	CustomTDPl[playerid][2] = CreatePlayerTextDraw(playerid, 505.000000, 191.916687, "Part info 2");
	PlayerTextDrawLetterSize(playerid, CustomTDPl[playerid][2], 0.209000, 1.086665);
	PlayerTextDrawAlignment(playerid, CustomTDPl[playerid][2], 1);
	PlayerTextDrawColor(playerid, CustomTDPl[playerid][2], -1);
	PlayerTextDrawSetShadow(playerid, CustomTDPl[playerid][2], 0);
	PlayerTextDrawSetOutline(playerid, CustomTDPl[playerid][2], 0);
	PlayerTextDrawBackgroundColor(playerid, CustomTDPl[playerid][2], 51);
	PlayerTextDrawFont(playerid, CustomTDPl[playerid][2], 2);
	PlayerTextDrawSetProportional(playerid, CustomTDPl[playerid][2], true);

	CustomTDPl[playerid][3] = CreatePlayerTextDraw(playerid, 505.000000, 220.500045, "part info 3");
	PlayerTextDrawLetterSize(playerid, CustomTDPl[playerid][3], 0.209000, 1.086665);
	PlayerTextDrawAlignment(playerid, CustomTDPl[playerid][3], 1);
	PlayerTextDrawColor(playerid, CustomTDPl[playerid][3], -1);
	PlayerTextDrawSetShadow(playerid, CustomTDPl[playerid][3], 0);
	PlayerTextDrawSetOutline(playerid, CustomTDPl[playerid][3], 0);
	PlayerTextDrawBackgroundColor(playerid, CustomTDPl[playerid][3], 51);
	PlayerTextDrawFont(playerid, CustomTDPl[playerid][3], 2);
	PlayerTextDrawSetProportional(playerid, CustomTDPl[playerid][3], true);

	CustomTDPl[playerid][4] = CreatePlayerTextDraw(playerid, 505.000000, 249.666717, "part info 4");
	PlayerTextDrawLetterSize(playerid, CustomTDPl[playerid][4], 0.209000, 1.086665);
	PlayerTextDrawAlignment(playerid, CustomTDPl[playerid][4], 1);
	PlayerTextDrawColor(playerid, CustomTDPl[playerid][4], -1);
	PlayerTextDrawSetShadow(playerid, CustomTDPl[playerid][4], 0);
	PlayerTextDrawSetOutline(playerid, CustomTDPl[playerid][4], 0);
	PlayerTextDrawBackgroundColor(playerid, CustomTDPl[playerid][4], 51);
	PlayerTextDrawFont(playerid, CustomTDPl[playerid][4], 2);
	PlayerTextDrawSetProportional(playerid, CustomTDPl[playerid][4], true);

	CustomTDPl[playerid][5] = CreatePlayerTextDraw(playerid, 505.000000, 278.250000, "part info 5");
	PlayerTextDrawLetterSize(playerid, CustomTDPl[playerid][5], 0.209000, 1.086665);
	PlayerTextDrawAlignment(playerid, CustomTDPl[playerid][5], 1);
	PlayerTextDrawColor(playerid, CustomTDPl[playerid][5], -1);
	PlayerTextDrawSetShadow(playerid, CustomTDPl[playerid][5], 0);
	PlayerTextDrawSetOutline(playerid, CustomTDPl[playerid][5], 0);
	PlayerTextDrawBackgroundColor(playerid, CustomTDPl[playerid][5], 51);
	PlayerTextDrawFont(playerid, CustomTDPl[playerid][5], 2);
	PlayerTextDrawSetProportional(playerid, CustomTDPl[playerid][5], true);
}
stock TranslateText(const string[])
{
	new result[256];
	for(new i = 0; i < strlen(string); i++)
	{
		switch(string[i])
		{
		case 'à':
			result[i] = 'a';
		case 'À':
			result[i] = 'A';
		case 'á':
			result[i] = '—';
		case 'Á':
			result[i] = '€';
		case 'â':
			result[i] = '¢';
		case 'Â':
			result[i] = '‹';
		case 'ã':
			result[i] = '™';
		case 'Ã':
			result[i] = '‚';
		case 'ä':
			result[i] = 'š';
		case 'Ä':
			result[i] = 'ƒ';
		case 'å':
			result[i] = 'e';
		case 'Å':
			result[i] = 'E';
		case '¸':
			result[i] = 'e';
		case '¨':
			result[i] = 'E';
		case 'æ':
			result[i] = '›';
		case 'Æ':
			result[i] = '„';
		case 'ç':
			result[i] = 'Ÿ';
		case 'Ç':
			result[i] = 'ˆ';
		case 'è':
			result[i] = 'œ';
		case 'È':
			result[i] = '…';
		case 'é':
			result[i] = '';
		case 'É':
			result[i] = '…';
		case 'ê':
			result[i] = 'k';
		case 'Ê':
			result[i] = 'K';
		case 'ë':
			result[i] = 'ž';
		case 'Ë':
			result[i] = '‡';
		case 'ì':
			result[i] = '¯';
		case 'Ì':
			result[i] = 'M';
		case 'í':
			result[i] = '®';
		case 'Í':
			result[i] = '­';
		case 'î':
			result[i] = 'o';
		case 'Î':
			result[i] = 'O';
		case 'ï':
			result[i] = '£';
		case 'Ï':
			result[i] = 'Œ';
		case 'ð':
			result[i] = 'p';
		case 'Ð':
			result[i] = 'P';
		case 'ñ':
			result[i] = 'c';
		case 'Ñ':
			result[i] = 'C';
		case 'ò':
			result[i] = '¦';
		case 'Ò':
			result[i] = '';
		case 'ó':
			result[i] = 'y';
		case 'Ó':
			result[i] = 'Y';
		case 'ô':
			result[i] = '';
		case 'Ô':
			result[i] = '';
		case 'õ':
			result[i] = 'x';
		case 'Õ':
			result[i] = 'X';
		case 'ö':
			result[i] = '‰';
		case 'Ö':
			result[i] = '‰';
		case '÷':
			result[i] = '¤';
		case '×':
			result[i] = '';
		case 'ø':
			result[i] = '¥';
		case 'Ø':
			result[i] = 'Ž';
		case 'ù':
			result[i] = '¡';
		case 'Ù':
			result[i] = 'Š';
		case 'ü':
			result[i] = '©';
		case 'Ü':
			result[i] = '’';
		case 'ú':
			result[i] = '';
		case 'Ú':
			result[i] = '§';
		case 'û':
			result[i] = '¨';
		case 'Û':
			result[i] = '‘';
		case 'ý':
			result[i] = 'ª';
		case 'Ý':
			result[i] = '“';
		case 'þ':
			result[i] = '«';
		case 'Þ':
			result[i] = '”';
		case 'ÿ':
			result[i] = '¬';
		case 'ß':
			result[i] = '•';
		default:
			result[i] = string[i];
		}
	}
	return result;
}
stock AddFixVehicleComponent(vehicleid, model) {
	if(IsVehicleUpgradeCompatible(GetVehicleModel(vehicleid),model)) {
	    AddVehicleComponent(vehicleid, model);
		return true;
	}
	return false;
}
stock components_name() {
	SetGVarInt("TUN[0][ModelID]",1000,0);
	SetGVarString("TUN[0][Name]","Pro",0);
	SetGVarInt("TUN[0][Value]",15000,0);

	SetGVarInt("TUN[1][ModelID]",1001,0);
	SetGVarString("TUN[1][Name]","Win",0);
	SetGVarInt("TUN[1][Value]",15000,0);

	SetGVarInt("TUN[2][ModelID]",1002,0);
	SetGVarString("TUN[2][Name]","Drag",0);
	SetGVarInt("TUN[2][Value]",15000,0);

	SetGVarInt("TUN[3][ModelID]",1003,0);
	SetGVarString("TUN[3][Name]","Alpha",0);
	SetGVarInt("TUN[3][Value]",15000,0);

	SetGVarInt("TUN[4][ModelID]",1014,0);
	SetGVarString("TUN[4][Name]","Champ",0);
	SetGVarInt("TUN[4][Value]",15000,0);

	SetGVarInt("TUN[5][ModelID]",1015,0);
	SetGVarString("TUN[5][Name]","Race",0);
	SetGVarInt("TUN[5][Value]",15000,0);

	SetGVarInt("TUN[6][ModelID]",1016,0);
	SetGVarString("TUN[6][Name]","Worx",0);
	SetGVarInt("TUN[6][Value]",15000,0);

	SetGVarInt("TUN[7][ModelID]",1023,0);
	SetGVarString("TUN[7][Name]","Fury",0);
	SetGVarInt("TUN[7][Value]",15000,0);

	SetGVarInt("TUN[8][ModelID]",1049,0);
	SetGVarString("TUN[8][Name]","Alien (Flash)",0);
	SetGVarInt("TUN[8][Value]",25000,0);

	SetGVarInt("TUN[9][ModelID]",1050,0);
	SetGVarString("TUN[9][Name]","X-Flow (Flash)",0);
	SetGVarInt("TUN[9][Value]",25000,0);

	SetGVarInt("TUN[10][ModelID]",1058,0);
	SetGVarString("TUN[10][Name]","Alien (Stratum)",0);
	SetGVarInt("TUN[10][Value]",25000,0);

	SetGVarInt("TUN[11][ModelID]",1060,0);
	SetGVarString("TUN[11][Name]","X-Flow (Stratum)",0);
	SetGVarInt("TUN[11][Value]",25000,0);

	SetGVarInt("TUN[12][ModelID]",1138,0);
	SetGVarString("TUN[12][Name]","Alien (Sultan)",0);
	SetGVarInt("TUN[12][Value]",25000,0);

	SetGVarInt("TUN[13][ModelID]",1139,0);
	SetGVarString("TUN[13][Name]","X-Flow (Sultan)",0);
	SetGVarInt("TUN[13][Value]",25000,0);

	SetGVarInt("TUN[14][ModelID]",1147,0);
	SetGVarString("TUN[14][Name]","Alien (Elegy)",0);
	SetGVarInt("TUN[14][Value]",25000,0);

	SetGVarInt("TUN[15][ModelID]",1146,0);
	SetGVarString("TUN[15][Name]","X-Flow (Elegy)",0);
	SetGVarInt("TUN[15][Value]",25000,0);

	SetGVarInt("TUN[16][ModelID]",1162,0);
	SetGVarString("TUN[16][Name]","Alien (Jester)",0);
	SetGVarInt("TUN[16][Value]",25000,0);

	SetGVarInt("TUN[17][ModelID]",1158,0);
	SetGVarString("TUN[17][Name]","X-Flow (Jester)",0);
	SetGVarInt("TUN[17][Value]",25000,0);

	SetGVarInt("TUN[18][ModelID]",1164,0);
	SetGVarString("TUN[18][Name]","Alien (Uranus)",0);
	SetGVarInt("TUN[18][Value]",25000,0);

	SetGVarInt("TUN[19][ModelID]",1163,0);
	SetGVarString("TUN[19][Name]","X-Flow (Uranus)",0);
	SetGVarInt("TUN[19][Value]",25000,0);
	//
	SetGVarInt("TUN[0][ModelID]",1004,1);
	SetGVarString("TUN[0][Name]","Champ",1);
	SetGVarInt("TUN[0][Value]",10000,1);

	SetGVarInt("TUN[1][ModelID]",1005,1);
	SetGVarString("TUN[1][Name]","Fury",1);
	SetGVarInt("TUN[1][Value]",10000,1);

	SetGVarInt("TUN[2][ModelID]",1011,1);
	SetGVarString("TUN[2][Name]","Race",1);
	SetGVarInt("TUN[2][Value]",10000,1);

	SetGVarInt("TUN[3][ModelID]",1012,1);
	SetGVarString("TUN[3][Name]","Worx",1);
	SetGVarInt("TUN[3][Value]",10000,1);
	//
	SetGVarInt("TUN[0][ModelID]",1025,2);
	SetGVarString("TUN[0][Name]","Offroad",2);
	SetGVarInt("TUN[0][Value]",25000,2);

	SetGVarInt("TUN[1][ModelID]",1073,2);
	SetGVarString("TUN[1][Name]","Shadow",2);
	SetGVarInt("TUN[1][Value]",40000,2);

	SetGVarInt("TUN[2][ModelID]",1074,2);
	SetGVarString("TUN[2][Name]","Mega",2);
	SetGVarInt("TUN[2][Value]",40000,2);

	SetGVarInt("TUN[3][ModelID]",1075,2);
	SetGVarString("TUN[3][Name]","Rimshine",2);
	SetGVarInt("TUN[3][Value]",40000,2);

	SetGVarInt("TUN[4][ModelID]",1076,2);
	SetGVarString("TUN[4][Name]","Wires",2);
	SetGVarInt("TUN[4][Value]",35000,2);

	SetGVarInt("TUN[5][ModelID]",1077,2);
	SetGVarString("TUN[5][Name]","Classic",2);
	SetGVarInt("TUN[5][Value]",50000,2);

	SetGVarInt("TUN[6][ModelID]",1078,2);
	SetGVarString("TUN[6][Name]","Twist",2);
	SetGVarInt("TUN[6][Value]",50000,2);

	SetGVarInt("TUN[7][ModelID]",1079,2);
	SetGVarString("TUN[7][Name]","Cutter",2);
	SetGVarInt("TUN[7][Value]",75000,2);

	SetGVarInt("TUN[8][ModelID]",1080,2);
	SetGVarString("TUN[8][Name]","Switch",2);
	SetGVarInt("TUN[8][Value]",75000,2);

	SetGVarInt("TUN[9][ModelID]",1081,2);
	SetGVarString("TUN[9][Name]","Grove",2);
	SetGVarInt("TUN[9][Value]",50000,2);

	SetGVarInt("TUN[10][ModelID]",1082,2);
	SetGVarString("TUN[10][Name]","Import",2);
	SetGVarInt("TUN[10][Value]",35000,2);

	SetGVarInt("TUN[11][ModelID]",1083,2);
	SetGVarString("TUN[11][Name]","Dollar",2);
	SetGVarInt("TUN[11][Value]",35000,2);

	SetGVarInt("TUN[12][ModelID]",1084,2);
	SetGVarString("TUN[12][Name]","Trance",2);
	SetGVarInt("TUN[12][Value]",35000,2);

	SetGVarInt("TUN[13][ModelID]",1085,2);
	SetGVarString("TUN[13][Name]","Atomic",2);
	SetGVarInt("TUN[13][Value]",45000,2);

	SetGVarInt("TUN[14][ModelID]",1096,2);
	SetGVarString("TUN[14][Name]","Ahab",2);
	SetGVarInt("TUN[14][Value]",35000,2);

	SetGVarInt("TUN[15][ModelID]",1097,2);
	SetGVarString("TUN[15][Name]","Virtual",2);
	SetGVarInt("TUN[15][Value]",35000,2);

	SetGVarInt("TUN[16][ModelID]",1098,2);
	SetGVarString("TUN[16][Name]","Access",2);
	SetGVarInt("TUN[16][Value]",30000,2);

	//
	SetGVarInt("TUN[0][ModelID]",1153,3);
	SetGVarString("TUN[0][Name]","Alien (Flash)",3);
	SetGVarInt("TUN[0][Value]",30000,3);

	SetGVarInt("TUN[1][ModelID]",1152,3);
	SetGVarString("TUN[1][Name]","X-Flow (Flash)",3);
	SetGVarInt("TUN[1][Value]",30000,3);

	SetGVarInt("TUN[2][ModelID]",1155,3);
	SetGVarString("TUN[2][Name]","Alien (Stratum)",3);
	SetGVarInt("TUN[2][Value]",30000,3);

	SetGVarInt("TUN[3][ModelID]",1157,3);
	SetGVarString("TUN[3][Name]","X-Flow (Stratum)",3);
	SetGVarInt("TUN[3][Value]",30000,3);

	SetGVarInt("TUN[4][ModelID]",1160,3);
	SetGVarString("TUN[4][Name]","Alien (Jester)",3);
	SetGVarInt("TUN[4][Value]",30000,3);

	SetGVarInt("TUN[5][ModelID]",1173,3);
	SetGVarString("TUN[5][Name]","X-Flow (Jester)",3);
	SetGVarInt("TUN[5][Value]",30000,3);

	SetGVarInt("TUN[6][ModelID]",1166,3);
	SetGVarString("TUN[6][Name]","Alien (Uranus)",3);
	SetGVarInt("TUN[6][Value]",30000,3);

	SetGVarInt("TUN[7][ModelID]",1165,3);
	SetGVarString("TUN[7][Name]","X-Flow (Uranus)",3);
	SetGVarInt("TUN[7][Value]",30000,3);

	SetGVarInt("TUN[8][ModelID]",1169,3);
	SetGVarString("TUN[8][Name]","Alien (Sultan)",3);
	SetGVarInt("TUN[8][Value]",30000,3);

	SetGVarInt("TUN[9][ModelID]",1170,3);
	SetGVarString("TUN[9][Name]","X-Flow (Sultan)",3);
	SetGVarInt("TUN[9][Value]",30000,3);

	SetGVarInt("TUN[10][ModelID]",1171,3);
	SetGVarString("TUN[10][Name]","Alien (Elegy)",3);
	SetGVarInt("TUN[10][Value]",30000,3);

	SetGVarInt("TUN[11][ModelID]",1172,3);
	SetGVarString("TUN[11][Name]","X-Flow (Elegy)",3);
	SetGVarInt("TUN[11][Value]",30000,3);

	SetGVarInt("TUN[12][ModelID]",1117,3);
	SetGVarString("TUN[12][Name]","Chrome (Slamvan)",3);
	SetGVarInt("TUN[12][Value]",15000,3);

	SetGVarInt("TUN[13][ModelID]",1174,3);
	SetGVarString("TUN[13][Name]","Chrome (Broadway)",3);
	SetGVarInt("TUN[13][Value]",15000,3);

	SetGVarInt("TUN[14][ModelID]",1175,3);
	SetGVarString("TUN[14][Name]","Slamin (Broadway)",3);
	SetGVarInt("TUN[14][Value]",15000,3);

	SetGVarInt("TUN[15][ModelID]",1179,3);
	SetGVarString("TUN[15][Name]","Chrome (Remington)",3);
	SetGVarInt("TUN[15][Value]",15000,3);

	SetGVarInt("TUN[16][ModelID]",1185,3);
	SetGVarString("TUN[16][Name]","Slamin (Remington)",3);
	SetGVarInt("TUN[16][Value]",15000,3);

	SetGVarInt("TUN[17][ModelID]",1182,3);
	SetGVarString("TUN[17][Name]","Chrome (Blade)",3);
	SetGVarInt("TUN[17][Value]",15000,3);

	SetGVarInt("TUN[18][ModelID]",1181,3);
	SetGVarString("TUN[18][Name]","Slamin (Blade)",3);
	SetGVarInt("TUN[18][Value]",15000,3);

	SetGVarInt("TUN[19][ModelID]",1189,3);
	SetGVarString("TUN[19][Name]","Chrome (Savanna)",3);
	SetGVarInt("TUN[19][Value]",15000,3);

	SetGVarInt("TUN[20][ModelID]",1188,3);
	SetGVarString("TUN[20][Name]","Slamin (Savanna)",3);
	SetGVarInt("TUN[20][Value]",15000,3);

	SetGVarInt("TUN[21][ModelID]",1191,3);
	SetGVarString("TUN[21][Name]","Chrome (Tornado)",3);
	SetGVarInt("TUN[21][Value]",15000,3);

	SetGVarInt("TUN[22][ModelID]",1190,3);
	SetGVarString("TUN[22][Name]","Slamin (Tornado)",3);
	SetGVarInt("TUN[22][Value]",15000,3);
	//
	SetGVarInt("TUN[0][ModelID]",1141,4);
	SetGVarString("TUN[0][Name]","Alien (Sultan)",4);
	SetGVarInt("TUN[0][Value]",30000,4);

	SetGVarInt("TUN[1][ModelID]",1140,4);
	SetGVarString("TUN[1][Name]","X-Flow (Sultan)",4);
	SetGVarInt("TUN[1][Value]",30000,4);

	SetGVarInt("TUN[2][ModelID]",1149,4);
	SetGVarString("TUN[2][Name]","Alien (Elegy)",4);
	SetGVarInt("TUN[2][Value]",30000,4);

	SetGVarInt("TUN[3][ModelID]",1148,4);
	SetGVarString("TUN[3][Name]","X-Flow (Elegy)",4);
	SetGVarInt("TUN[3][Value]",30000,4);

	SetGVarInt("TUN[4][ModelID]",1150,4);
	SetGVarString("TUN[4][Name]","Alien (Flash)",4);
	SetGVarInt("TUN[4][Value]",30000,4);

	SetGVarInt("TUN[5][ModelID]",1151,4);
	SetGVarString("TUN[5][Name]","X-Flow (Flash)",4);
	SetGVarInt("TUN[5][Value]",30000,4);

	SetGVarInt("TUN[6][ModelID]",1154,4);
	SetGVarString("TUN[6][Name]","Alien (Stratum)",4);
	SetGVarInt("TUN[6][Value]",30000,4);

	SetGVarInt("TUN[7][ModelID]",1156,4);
	SetGVarString("TUN[7][Name]","X-Flow (Stratum)",4);
	SetGVarInt("TUN[7][Value]",30000,4);

	SetGVarInt("TUN[8][ModelID]",1159,4);
	SetGVarString("TUN[8][Name]","Alien (Jester)",4);
	SetGVarInt("TUN[8][Value]",30000,4);

	SetGVarInt("TUN[9][ModelID]",1161,4);
	SetGVarString("TUN[9][Name]","X-Flow (Jester)",4);
	SetGVarInt("TUN[9][Value]",30000,4);

	SetGVarInt("TUN[10][ModelID]",1168,4);
	SetGVarString("TUN[10][Name]","Alien (Uranus)",4);
	SetGVarInt("TUN[10][Value]",30000,4);

	SetGVarInt("TUN[11][ModelID]",1167,4);
	SetGVarString("TUN[11][Name]","X-Flow (Uranus)",4);
	SetGVarInt("TUN[11][Value]",30000,4);

	SetGVarInt("TUN[12][ModelID]",1176,4);
	SetGVarString("TUN[12][Name]","Chrome (Broadway)",4);
	SetGVarInt("TUN[12][Value]",15000,4);

	SetGVarInt("TUN[13][ModelID]",1177,4);
	SetGVarString("TUN[13][Name]","Slamin (Broadway)",4);
	SetGVarInt("TUN[13][Value]",15000,4);

	SetGVarInt("TUN[14][ModelID]",1180,4);
	SetGVarString("TUN[14][Name]","Chrome (Remington)",4);
	SetGVarInt("TUN[14][Value]",15000,4);

	SetGVarInt("TUN[15][ModelID]",1178,4);
	SetGVarString("TUN[15][Name]","Slamin (Remington)",4);
	SetGVarInt("TUN[15][Value]",15000,4);

	SetGVarInt("TUN[16][ModelID]",1184,4);
	SetGVarString("TUN[16][Name]","Chrome (Blade)",4);
	SetGVarInt("TUN[16][Value]",15000,4);

	SetGVarInt("TUN[17][ModelID]",1183,4);
	SetGVarString("TUN[17][Name]","Slamin (Blade)",4);
	SetGVarInt("TUN[17][Value]",15000,4);

	SetGVarInt("TUN[18][ModelID]",1187,4);
	SetGVarString("TUN[18][Name]","Chrome (Savanna)",4);
	SetGVarInt("TUN[18][Value]",15000,4);

	SetGVarInt("TUN[19][ModelID]",1186,4);
	SetGVarString("TUN[19][Name]","Slamin (Savanna)",4);
	SetGVarInt("TUN[19][Value]",15000,4);

	SetGVarInt("TUN[20][ModelID]",1192,4);
	SetGVarString("TUN[20][Name]","Chrome (Tornado)",4);
	SetGVarInt("TUN[20][Value]",15000,4);

	SetGVarInt("TUN[21][ModelID]",1193,4);
	SetGVarString("TUN[21][Name]","Slamin (Tornado)",4);
	SetGVarInt("TUN[21][Value]",15000,4);
	//
	SetGVarInt("TUN[0][ModelID]",1143,5);
	SetGVarString("TUN[0][Name]","Round Vent",5);
	SetGVarInt("TUN[0][Value]",5000,5);

	SetGVarInt("TUN[1][ModelID]",1145,5);
	SetGVarString("TUN[1][Name]","Squard Vent",5);
	SetGVarInt("TUN[1][Value]",5000,5);
	//
	SetGVarInt("TUN[0][ModelID]",1103,6);
	SetGVarString("TUN[0][Name]","Convertible (Blade)",6);
	SetGVarInt("TUN[0][Value]",5000,6);

	SetGVarInt("TUN[1][ModelID]",1128,6);
	SetGVarString("TUN[1][Name]","Vinyl Hardtop (Blade)",6);
	SetGVarInt("TUN[1][Value]",7500,6);

	SetGVarInt("TUN[2][ModelID]",1130,6);
	SetGVarString("TUN[2][Name]","Hardtop (Savanna)",6);
	SetGVarInt("TUN[2][Value]",7500,6);

	SetGVarInt("TUN[3][ModelID]",1131,6);
	SetGVarString("TUN[3][Name]","Softtop (Savanna)",6);
	SetGVarInt("TUN[3][Value]",7500,6);

	SetGVarInt("TUN[4][ModelID]",1032,6);
	SetGVarString("TUN[4][Name]","Alien (Sultan)",6);
	SetGVarInt("TUN[4][Value]",10000,6);

	SetGVarInt("TUN[5][ModelID]",1033,6);
	SetGVarString("TUN[5][Name]","X-Flow (Sultan)",6);
	SetGVarInt("TUN[5][Value]",10000,6);

	SetGVarInt("TUN[6][ModelID]",1038,6);
	SetGVarString("TUN[6][Name]","Alien (Elegy)",6);
	SetGVarInt("TUN[6][Value]",10000,6);

	SetGVarInt("TUN[7][ModelID]",1035,6);
	SetGVarString("TUN[7][Name]","X-Flow (Elegy)",6);
	SetGVarInt("TUN[7][Value]",10000,6);

	SetGVarInt("TUN[8][ModelID]",1054,6);
	SetGVarString("TUN[8][Name]","Alien (Flash)",6);
	SetGVarInt("TUN[8][Value]",10000,6);

	SetGVarInt("TUN[8][ModelID]",1053,6);
	SetGVarString("TUN[8][Name]","X-Flow (Flash)",6);
	SetGVarInt("TUN[8][Value]",10000,6);

	SetGVarInt("TUN[9][ModelID]",1055,6);
	SetGVarString("TUN[9][Name]","Alien (Startum)",6);
	SetGVarInt("TUN[9][Value]",10000,6);

	SetGVarInt("TUN[10][ModelID]",1061,6);
	SetGVarString("TUN[10][Name]","X-Flow (Startum)",6);
	SetGVarInt("TUN[10][Value]",10000,6);

	SetGVarInt("TUN[11][ModelID]",1067,6);
	SetGVarString("TUN[11][Name]","Alien (Jester)",6);
	SetGVarInt("TUN[11][Value]",10000,6);

	SetGVarInt("TUN[12][ModelID]",1068,6);
	SetGVarString("TUN[12][Name]","X-Flow (Jester)",6);
	SetGVarInt("TUN[12][Value]",10000,6);

	SetGVarInt("TUN[13][ModelID]",1088,6);
	SetGVarString("TUN[13][Name]","Alien (Uranus)",6);
	SetGVarInt("TUN[13][Value]",10000,6);

	SetGVarInt("TUN[14][ModelID]",1091,6);
	SetGVarString("TUN[14][Name]","X-Flow (Uranus)",6);
	SetGVarInt("TUN[14][Value]",10000,6);
	//
	SetGVarInt("TUN[0][ModelID]",1018,7);
	SetGVarString("TUN[0][Name]","Upswept",7);
	SetGVarInt("TUN[0][Value]",7500,7);

	SetGVarInt("TUN[1][ModelID]",1019,7);
	SetGVarString("TUN[1][Name]","Twin",7);
	SetGVarInt("TUN[1][Value]",7500,7);

	SetGVarInt("TUN[2][ModelID]",1020,7);
	SetGVarString("TUN[2][Name]","Large",7);
	SetGVarInt("TUN[2][Value]",7500,7);

	SetGVarInt("TUN[3][ModelID]",1021,7);
	SetGVarString("TUN[3][Name]","Medium",7);
	SetGVarInt("TUN[3][Value]",7500,7);

	SetGVarInt("TUN[4][ModelID]",1022,7);
	SetGVarString("TUN[4][Name]","Small",7);
	SetGVarInt("TUN[4][Value]",7500,7);

	SetGVarInt("TUN[5][ModelID]",1028,7);
	SetGVarString("TUN[5][Name]","Alien (Sultan)",7);
	SetGVarInt("TUN[5][Value]",10000,7);

	SetGVarInt("TUN[6][ModelID]",1029,7);
	SetGVarString("TUN[6][Name]","X-Flow (Sultan)",7);
	SetGVarInt("TUN[6][Value]",10000,7);

	SetGVarInt("TUN[7][ModelID]",1034,7);
	SetGVarString("TUN[7][Name]","Alien (Elegy)",7);
	SetGVarInt("TUN[7][Value]",10000,7);

	SetGVarInt("TUN[8][ModelID]",1037,7);
	SetGVarString("TUN[8][Name]","X-Flow (Elegy)",7);
	SetGVarInt("TUN[8][Value]",10000,7);

	SetGVarInt("TUN[9][ModelID]",1046,7);
	SetGVarString("TUN[9][Name]","Alien (Flash)",7);
	SetGVarInt("TUN[9][Value]",10000,7);

	SetGVarInt("TUN[10][ModelID]",1045,7);
	SetGVarString("TUN[10][Name]","X-Flow (Flash)",7);
	SetGVarInt("TUN[10][Value]",10000,7);

	SetGVarInt("TUN[11][ModelID]",1064,7);
	SetGVarString("TUN[11][Name]","Alien (Stratum)",7);
	SetGVarInt("TUN[11][Value]",10000,7);

	SetGVarInt("TUN[12][ModelID]",1059,7);
	SetGVarString("TUN[12][Name]","X-Flow (Stratum)",7);
	SetGVarInt("TUN[12][Value]",10000,7);

	SetGVarInt("TUN[13][ModelID]",1065,7);
	SetGVarString("TUN[13][Name]","Alien (Jester)",7);
	SetGVarInt("TUN[13][Value]",10000,7);

	SetGVarInt("TUN[14][ModelID]",1066,7);
	SetGVarString("TUN[14][Name]","X-Flow (Jester)",7);
	SetGVarInt("TUN[14][Value]",10000,7);

	SetGVarInt("TUN[15][ModelID]",1092,7);
	SetGVarString("TUN[15][Name]","Alien (Uranus)",7);
	SetGVarInt("TUN[15][Value]",10000,7);

	SetGVarInt("TUN[16][ModelID]",1089,7);
	SetGVarString("TUN[16][Name]","X-Flow (Uranus)",7);
	SetGVarInt("TUN[16][Value]",10000,7);

	SetGVarInt("TUN[17][ModelID]",1043,7);
	SetGVarString("TUN[17][Name]","Slamin (Broadway)",7);
	SetGVarInt("TUN[17][Value]",7500,7);

	SetGVarInt("TUN[18][ModelID]",1044,7);
	SetGVarString("TUN[18][Name]","Chrome (Broadway)",7);
	SetGVarInt("TUN[18][Value]",7500,7);

	SetGVarInt("TUN[19][ModelID]",1105,7);
	SetGVarString("TUN[19][Name]","Slamin (Blade)",7);
	SetGVarInt("TUN[19][Value]",7500,7);

	SetGVarInt("TUN[20][ModelID]",1104,7);
	SetGVarString("TUN[20][Name]","Chrome (Blade)",7);
	SetGVarInt("TUN[20][Value]",7500,7);

	SetGVarInt("TUN[21][ModelID]",1114,7);
	SetGVarString("TUN[21][Name]","Slamin (Slamvan)",7);
	SetGVarInt("TUN[21][Value]",7500,7);

	SetGVarInt("TUN[22][ModelID]",1113,7);
	SetGVarString("TUN[22][Name]","Chrome (Slavman)",7);
	SetGVarInt("TUN[22][Value]",7500,7);

	SetGVarInt("TUN[23][ModelID]",1127,7);
	SetGVarString("TUN[23][Name]","Slamin (Remington)",7);
	SetGVarInt("TUN[23][Value]",7500,7);

	SetGVarInt("TUN[24][ModelID]",1126,7);
	SetGVarString("TUN[24][Name]","Chrome (Remington)",7);
	SetGVarInt("TUN[24][Value]",7500,7);

	SetGVarInt("TUN[25][ModelID]",1132,7);
	SetGVarString("TUN[25][Name]","Slamin (Savanna)",7);
	SetGVarInt("TUN[25][Value]",7500,7);

	SetGVarInt("TUN[26][ModelID]",1129,7);
	SetGVarString("TUN[26][Name]","Chrome (Savanna)",7);
	SetGVarInt("TUN[26][Value]",7500,7);

	SetGVarInt("TUN[27][ModelID]",1135,7);
	SetGVarString("TUN[27][Name]","Slamin (Tornado)",7);
	SetGVarInt("TUN[27][Value]",7500,7);

	SetGVarInt("TUN[28][ModelID]",1136,7);
	SetGVarString("TUN[28][Name]","Chrome (Tornado)",7);
	SetGVarInt("TUN[28][Value]",7500,7);
	//
	SetGVarInt("TUN[0][ModelID]",1007,8);
	SetGVarString("TUN[0][Name]","Standart",8);
	SetGVarInt("TUN[0][Value]",7500,8);

	SetGVarInt("TUN[1][ModelID]",1026,8);
	SetGVarString("TUN[1][Name]","Alien (Sultan)",8);
	SetGVarInt("TUN[1][Value]",10000,8);

	SetGVarInt("TUN[2][ModelID]",1031,8);
	SetGVarString("TUN[2][Name]","X-Flow (Sultan)",8);
	SetGVarInt("TUN[2][Value]",10000,8);

	SetGVarInt("TUN[3][ModelID]",1036,8);
	SetGVarString("TUN[3][Name]","Alien (Elegy)",8);
	SetGVarInt("TUN[3][Value]",10000,8);

	SetGVarInt("TUN[4][ModelID]",1041,8);
	SetGVarString("TUN[4][Name]","X-Flow (Elegy)",8);
	SetGVarInt("TUN[4][Value]",10000,8);

	SetGVarInt("TUN[5][ModelID]",1047,8);
	SetGVarString("TUN[5][Name]","Alien (Flash)",8);
	SetGVarInt("TUN[5][Value]",10000,8);

	SetGVarInt("TUN[6][ModelID]",1048,8);
	SetGVarString("TUN[6][Name]","X-Flow (Flash)",8);
	SetGVarInt("TUN[6][Value]",10000,8);

	SetGVarInt("TUN[7][ModelID]",1056,8);
	SetGVarString("TUN[7][Name]","Alien (Stratum)",8);
	SetGVarInt("TUN[7][Value]",10000,8);

	SetGVarInt("TUN[8][ModelID]",1057,8);
	SetGVarString("TUN[8][Name]","X-Flow (Stratum)",8);
	SetGVarInt("TUN[8][Value]",10000,8);

	SetGVarInt("TUN[9][ModelID]",1069,8);
	SetGVarString("TUN[9][Name]","Alien (Jester)",8);
	SetGVarInt("TUN[9][Value]",10000,8);

	SetGVarInt("TUN[10][ModelID]",1070,8);
	SetGVarString("TUN[10][Name]","X-Flow (Jester)",8);
	SetGVarInt("TUN[10][Value]",10000,8);

	SetGVarInt("TUN[11][ModelID]",1090,8);
	SetGVarString("TUN[11][Name]","Alien (Uranus)",8);
	SetGVarInt("TUN[11][Value]",10000,8);

	SetGVarInt("TUN[12][ModelID]",1095,8);
	SetGVarString("TUN[12][Name]","X-Flow (Uranus)",8);
	SetGVarInt("TUN[12][Value]",10000,8);

	SetGVarInt("TUN[13][ModelID]",1042,8);
	SetGVarString("TUN[13][Name]","Chrome (Broadway)",8);
	SetGVarInt("TUN[13][Value]",7500,8);

	SetGVarInt("TUN[14][ModelID]",1122,8);
	SetGVarString("TUN[14][Name]","Chrome Flames (Remington)",8);
	SetGVarInt("TUN[14][Value]",7500,8);

	SetGVarInt("TUN[15][ModelID]",1124,8);
	SetGVarString("TUN[15][Name]","Chrome Arches (Remington)",8);
	SetGVarInt("TUN[15][Value]",7500,8);

	SetGVarInt("TUN[16][ModelID]",1102,8);
	SetGVarString("TUN[16][Name]","Chrome Strip (Savanna)",8);
	SetGVarInt("TUN[16][Value]",7500,8);

	SetGVarInt("TUN[17][ModelID]",1108,8);
	SetGVarString("TUN[17][Name]","Chrome Strip (Blade)",8);
	SetGVarInt("TUN[17][Value]",7500,8);

	SetGVarInt("TUN[18][ModelID]",1118,8);
	SetGVarString("TUN[18][Name]","Chrome Trim (Slamvan)",8);
	SetGVarInt("TUN[18][Value]",7500,8);

	SetGVarInt("TUN[19][ModelID]",1119,8);
	SetGVarString("TUN[19][Name]","Wheelcovers (Slamvan)",8);
	SetGVarInt("TUN[19][Value]",7500,8);
	//
	SetGVarInt("TUN[0][ModelID]",1013,9);
	SetGVarString("TUN[0][Name]","Round Lights",9);
	SetGVarInt("TUN[0][Value]",5000,9);

	SetGVarInt("TUN[1][ModelID]",1024,9);
	SetGVarString("TUN[1][Name]","Squard Lights",9);
	SetGVarInt("TUN[1][Value]",5000,9);

	SetGVarInt("TUN[0][ModelID]",1009,10);
	SetGVarString("TUN[0][Name]","Nitro x2",10);
	SetGVarInt("TUN[0][Value]",15000,10);

	SetGVarInt("TUN[1][ModelID]",1008,10);
	SetGVarString("TUN[1][Name]","Nitro x5",10);
	SetGVarInt("TUN[1][Value]",50000,10);

	SetGVarInt("TUN[2][ModelID]",1010,10);
	SetGVarString("TUN[2][Name]","Nitro x10",10);
	SetGVarInt("TUN[2][Value]",100000,10);

	SetGVarInt("TUN[0][ModelID]",1087,11);
	SetGVarString("TUN[0][Name]","Hydraulics",11);
	SetGVarInt("TUN[0][Value]",75000,11);
	
	
}