void loadJardinData(scene* self) {
////MAP DATA////
setMapInfo(self, 4000, 4000, 3400, 670);

////OBJECT DATA////
self->objNum = 128;
self->obj = malloc(self->objNum * sizeof(gameObject));
//image1919
self->obj[0] = createObject("/rd/floor.png", 4191, 1876, 1);
//image825
self->obj[1] = createObject("/rd/dirt_1.png", 2783, 1216, 1);
//image836
self->obj[2] = createObject("/rd/dirt_2.png", 3251, 675, 1);
               flipU(&self->obj[2].t);
//gate
self->obj[3] = createObject("/rd/gate.png", 3443, 483, 1);
//image1280-1-4-0-76
self->obj[4] = createObject("/rd/tree.png", 1010, 3517, 1);
//gazebo
self->obj[5] = createObject("/rd/structure.png", 903, 3332, 1);
//lake
self->obj[6] = createObject("/rd/lac.png", 1078, 1280, 1);
//image836-6-4
self->obj[7] = createObject("", 3171, 754, 1);
self->obj[7].t = self->obj[2].t;
               flipU(&self->obj[7].t);
//image836-6-3
self->obj[8] = createObject("", 3013, 918, 1);
self->obj[8].t = self->obj[2].t;
               flipU(&self->obj[8].t);
//image836-6-7
self->obj[9] = createObject("", 2844, 1126, 1);
self->obj[9].t = self->obj[2].t;
               flipU(&self->obj[9].t);
//image825-2
self->obj[10] = createObject("", 2782, 1328, 1);
self->obj[10].t = self->obj[1].t;
//image943
self->obj[11] = createObject("/rd/dirt_3.png", 2700, 1186, 1);
//image1280-1-4-0-8-0
self->obj[12] = createObject("", 1054, 3466, 1);
self->obj[12].t = self->obj[4].t;
//image836-6-7-5
self->obj[13] = createObject("", 1218, 3027, 1);
self->obj[13].t = self->obj[2].t;
               flipU(&self->obj[13].t);
//image1280-1-4-0-7-2-5-0-1-0-6-2
self->obj[14] = createObject("", 1345, 3517, 1);
self->obj[14].t = self->obj[4].t;
//image1280-1-4-0-1-3
self->obj[15] = createObject("", 1261, 3416, 1);
self->obj[15].t = self->obj[4].t;
//image836-6-7-4
self->obj[16] = createObject("", 1297, 2948, 1);
self->obj[16].t = self->obj[2].t;
               flipU(&self->obj[16].t);
//image943-2
self->obj[17] = createObject("", 2532, 1177, 1);
self->obj[17].t = self->obj[11].t;
//image943-6
self->obj[18] = createObject("", 2421, 1179, 1);
self->obj[18].t = self->obj[11].t;
//image943-4
self->obj[19] = createObject("", 2227, 1189, 1);
self->obj[19].t = self->obj[11].t;
//image943-28
self->obj[20] = createObject("", 2034, 1202, 1);
self->obj[20].t = self->obj[11].t;
//image943-5
self->obj[21] = createObject("", 1921, 1212, 1);
self->obj[21].t = self->obj[11].t;
//image943-8
self->obj[22] = createObject("", 1730, 1223, 1);
self->obj[22].t = self->obj[11].t;
//image836-6-7-3
self->obj[23] = createObject("", 1473, 2771, 1);
self->obj[23].t = self->obj[2].t;
               flipU(&self->obj[23].t);
//image943-8-5
self->obj[24] = createObject("", 1570, 2720, 1);
self->obj[24].t = self->obj[11].t;
//image943-8-9
self->obj[25] = createObject("", 1677, 2722, 1);
self->obj[25].t = self->obj[11].t;
//image943-8-2
self->obj[26] = createObject("", 1812, 2724, 1);
self->obj[26].t = self->obj[11].t;
//image943-8-8
self->obj[27] = createObject("", 1921, 2726, 1);
self->obj[27].t = self->obj[11].t;
//image825-2-8-5
self->obj[28] = createObject("", 2778, 1589, 1);
self->obj[28].t = self->obj[1].t;
//image825-2-8-5-5
self->obj[29] = createObject("", 2758, 1697, 1);
self->obj[29].t = self->obj[1].t;
//image825-2-8-5-3
self->obj[30] = createObject("", 2742, 1891, 1);
self->obj[30].t = self->obj[1].t;
//image825-2-8-5-50
self->obj[31] = createObject("", 2732, 2088, 1);
self->obj[31].t = self->obj[1].t;
//image836-6-7-39
self->obj[32] = createObject("", 2709, 2189, 1);
self->obj[32].t = self->obj[2].t;
               flipU(&self->obj[32].t);
//image836-6-7-1
self->obj[33] = createObject("", 2544, 2371, 1);
self->obj[33].t = self->obj[2].t;
               flipU(&self->obj[33].t);
//image836-6-7-07
self->obj[34] = createObject("", 2469, 2452, 1);
self->obj[34].t = self->obj[2].t;
               flipU(&self->obj[34].t);
//image836-6-7-7
self->obj[35] = createObject("", 2388, 2530, 1);
self->obj[35].t = self->obj[2].t;
               flipU(&self->obj[35].t);
//image836-6-7-54
self->obj[36] = createObject("", 2234, 2680, 1);
self->obj[36].t = self->obj[2].t;
               flipU(&self->obj[36].t);
//image943-8-6-8
self->obj[37] = createObject("", 2148, 2736, 1);
self->obj[37].t = self->obj[11].t;
//image1280
self->obj[38] = createObject("", 3753, 426, 1);
self->obj[38].t = self->obj[4].t;
//image1280-1
self->obj[39] = createObject("", 3693, 375, 1);
self->obj[39].t = self->obj[4].t;
//image1280-1-4
self->obj[40] = createObject("", 3118, 457, 1);
self->obj[40].t = self->obj[4].t;
               flipU(&self->obj[40].t);
//image1280-1-4-2
self->obj[41] = createObject("", 3185, 384, 1);
self->obj[41].t = self->obj[4].t;
               flipU(&self->obj[41].t);
//image1280-1-4-0-7-2
self->obj[42] = createObject("", 1373, 3361, 1);
self->obj[42].t = self->obj[4].t;
//image1280-1-4-0
self->obj[43] = createObject("", 759, 3480, 1);
self->obj[43].t = self->obj[4].t;
               flipU(&self->obj[43].t);
//image1280-1-4-0-8
self->obj[44] = createObject("", 715, 3429, 1);
self->obj[44].t = self->obj[4].t;
               flipU(&self->obj[44].t);
//image1280-1-4-0-17
self->obj[45] = createObject("", 465, 3524, 1);
self->obj[45].t = self->obj[4].t;
               flipU(&self->obj[45].t);
//image1280-1-4-0-1
self->obj[46] = createObject("", 560, 3316, 1);
self->obj[46].t = self->obj[4].t;
               flipU(&self->obj[46].t);
//image1280-1-4-0-7
self->obj[47] = createObject("", 500, 3201, 1);
self->obj[47].t = self->obj[4].t;
               flipU(&self->obj[47].t);
//image1426
self->obj[48] = createObject("/rd/tree2.png", 594, 3178, 1);
               flipU(&self->obj[48].t);
//image1280-1-4-0-7-2-5
self->obj[49] = createObject("", 3208, 3424, 1);
self->obj[49].t = self->obj[4].t;
//image1426-3
self->obj[50] = createObject("", 3071, 3429, 1);
self->obj[50].t = self->obj[48].t;
               flipU(&self->obj[50].t);
//image1280-1-4-0-7-2-5-0
self->obj[51] = createObject("", 2864, 3337, 1);
self->obj[51].t = self->obj[4].t;
               flipU(&self->obj[51].t);
//image1426-3-5
self->obj[52] = createObject("", 3000, 3345, 1);
self->obj[52].t = self->obj[48].t;
               flipU(&self->obj[52].t);
//image1280-1-4-0-7-2-5-0-1
self->obj[53] = createObject("", 2828, 3216, 1);
self->obj[53].t = self->obj[4].t;
               flipU(&self->obj[53].t);
//image1280-1-4-0-7-2-5-0-1-0
self->obj[54] = createObject("", 2385, 4253, 1);
self->obj[54].t = self->obj[4].t;
               flipU(&self->obj[54].t);
//image1280-1-4-0-7-2-5-0-1-0-6
self->obj[55] = createObject("", 2491, 3725, 1);
self->obj[55].t = self->obj[4].t;
               flipU(&self->obj[55].t);
//image1280-1-4-0-7-2-5-0-1-0-60
self->obj[56] = createObject("", 3624, 4255, 1);
self->obj[56].t = self->obj[4].t;
//image1280-1-4-0-7-2-5-0-1-0-6-23
self->obj[57] = createObject("", 3518, 3723, 1);
self->obj[57].t = self->obj[4].t;
//image1280-1-4-0-7-2-5-0-1-0-6-23-1
self->obj[58] = createObject("", 3606, 3570, 1);
self->obj[58].t = self->obj[4].t;
//image1280-1-4-0-7-2-5-0-1-0-6-23-4
self->obj[59] = createObject("", 3536, 3433, 1);
self->obj[59].t = self->obj[4].t;
//image1280-1-4-0-7-2-5-0-1-0-60-0
self->obj[60] = createObject("", 3062, 2333, 1);
self->obj[60].t = self->obj[4].t;
//image1280-1-4-0-7-2-5-0-1-0-6-23-4-1
self->obj[61] = createObject("", 3002, 2153, 1);
self->obj[61].t = self->obj[4].t;
//image1426-3-5-4
self->obj[62] = createObject("", 3049, 2039, 1);
self->obj[62].t = self->obj[48].t;
//image1280-1-4-0-7-2-5-0-1-0-60-0-4
self->obj[63] = createObject("", 3018, 1898, 1);
self->obj[63].t = self->obj[4].t;
//image1280-1-4-0-7-2-5-0-1-0-60-0-2
self->obj[64] = createObject("", 3137, 1823, 1);
self->obj[64].t = self->obj[4].t;
//image1280-1-4-0-7-2-5-0-1-0-60-0-9
self->obj[65] = createObject("", 3098, 1588, 1);
self->obj[65].t = self->obj[4].t;
//image1952-8-9-8
self->obj[66] = createObject("/rd/rox2.png", 3081, 1414, 1);
//image1941-5-5
self->obj[67] = createObject("/rd/rox1.png", 3025, 1423, 1);
               flipU(&self->obj[67].t);
//image1280-1-4-0-7-2-5-0-1-0-60-0-8
self->obj[68] = createObject("", 3235, 1420, 1);
self->obj[68].t = self->obj[4].t;
//image1280-1-4-0-7-2-5-0-1-0-60-0-49
self->obj[69] = createObject("", 2370, 2323, 1);
self->obj[69].t = self->obj[4].t;
               flipU(&self->obj[69].t);
//image1280-1-4-0-7-2-5-0-1-0-6-23-4-1-6
self->obj[70] = createObject("", 2431, 2143, 1);
self->obj[70].t = self->obj[4].t;
               flipU(&self->obj[70].t);
//image1426-3-5-4-9
self->obj[71] = createObject("", 2384, 2030, 1);
self->obj[71].t = self->obj[48].t;
               flipU(&self->obj[71].t);
//image1280-1-4-0-7-2-5-0-1-0-60-0-4-5
self->obj[72] = createObject("", 2415, 1888, 1);
self->obj[72].t = self->obj[4].t;
               flipU(&self->obj[72].t);
//image1280-1-4-0-7-2-5-0-1-0-60-0-2-0
self->obj[73] = createObject("", 2295, 1813, 1);
self->obj[73].t = self->obj[4].t;
               flipU(&self->obj[73].t);
//image1280-1-4-0-7-2-5-0-1-0-60-0-9-0
self->obj[74] = createObject("", 2335, 1579, 1);
self->obj[74].t = self->obj[4].t;
               flipU(&self->obj[74].t);
//image1280-1-4-0-7-2-5-0-1-0-60-0-4-5-2
self->obj[75] = createObject("", 2487, 1601, 1);
self->obj[75].t = self->obj[4].t;
               flipU(&self->obj[75].t);
//image1280-1-4-0-7-2-5-0-1-0-60-0-4-5-7
self->obj[76] = createObject("", 2429, 1446, 1);
self->obj[76].t = self->obj[4].t;
               flipU(&self->obj[76].t);
//image1426-3-5-4-9-0
self->obj[77] = createObject("", 2208, 1491, 1);
self->obj[77].t = self->obj[48].t;
               flipU(&self->obj[77].t);
//image1280-1-4-0-7-2-5-0-1-0-60-0-4-5-2-4
self->obj[78] = createObject("", 2653, 984, 1);
self->obj[78].t = self->obj[4].t;
               flipU(&self->obj[78].t);
//image1280-1-4-0-7-2-5-0-1-0-60-0-4-5-7-6
self->obj[79] = createObject("", 2595, 829, 1);
self->obj[79].t = self->obj[4].t;
               flipU(&self->obj[79].t);
//image1426-3-5-4-9-0-9
self->obj[80] = createObject("", 2768, 829, 1);
self->obj[80].t = self->obj[48].t;
               flipU(&self->obj[80].t);
//image1280-1-4-0-7-2-5-0-1-0-60-0-4-5-2-3
self->obj[81] = createObject("", 3511, 1143, 1);
self->obj[81].t = self->obj[4].t;
               flipU(&self->obj[81].t);
//image1280-1-4-0-7-2-5-0-1-0-60-0-4-5-7-8
self->obj[82] = createObject("", 3454, 988, 1);
self->obj[82].t = self->obj[4].t;
               flipU(&self->obj[82].t);
//image1426-3-5-4-9-0-7
self->obj[83] = createObject("", 3233, 1033, 1);
self->obj[83].t = self->obj[48].t;
               flipU(&self->obj[83].t);
//image1280-1-4-0-7-2-5-0-1-0-60-0-4-5-7-6-2
self->obj[84] = createObject("", 2248, 924, 1);
self->obj[84].t = self->obj[4].t;
               flipU(&self->obj[84].t);
//image1280-1-4-0-7-2-5-0-1-0-60-0-4-5-7-6-8
self->obj[85] = createObject("", 2124, 814, 1);
self->obj[85].t = self->obj[4].t;
               flipU(&self->obj[85].t);
//image1280-1-4-0-7-2-5-0-1-0-60-0-4-5-7-6-3
self->obj[86] = createObject("", 1363, 946, 1);
self->obj[86].t = self->obj[4].t;
               flipU(&self->obj[86].t);
//image1280-1-4-0-7-2-5-0-1-0-60-0-4-5-7-6-4
self->obj[87] = createObject("", 1531, 884, 1);
self->obj[87].t = self->obj[4].t;
               flipU(&self->obj[87].t);
//image1280-1-4-0-7-2-5-0-1-0-60-0-4-5-7-6-5
self->obj[88] = createObject("", 1181, 1724, 1);
self->obj[88].t = self->obj[4].t;
               flipU(&self->obj[88].t);
//image1280-1-4-0-7-2-5-0-1-0-60-0-4-5-7-6-6
self->obj[89] = createObject("", 1301, 1645, 1);
self->obj[89].t = self->obj[4].t;
               flipU(&self->obj[89].t);
//image1280-1-4-0-7-2-5-0-1-0-60-0-4-5-7-6-80
self->obj[90] = createObject("", 1093, 1645, 1);
self->obj[90].t = self->obj[4].t;
               flipU(&self->obj[90].t);
//image1280-1-4-0-7-2-5-0-1-0-60-0-4-5-7-6-807
self->obj[91] = createObject("", 712, 1513, 1);
self->obj[91].t = self->obj[4].t;
               flipU(&self->obj[91].t);
//image1426-3-5-4-9-0-0
self->obj[92] = createObject("", 602, 1384, 1);
self->obj[92].t = self->obj[48].t;
               flipU(&self->obj[92].t);
//image1426-3-5-4-9-0-5
self->obj[93] = createObject("", 681, 1039, 1);
self->obj[93].t = self->obj[48].t;
               flipU(&self->obj[93].t);
//image1426-3-5-4-9-0-0-0
self->obj[94] = createObject("", 620, 2420, 1);
self->obj[94].t = self->obj[48].t;
               flipU(&self->obj[94].t);
//image1426-3-5-4-9-0-0-2
self->obj[95] = createObject("", 717, 2327, 1);
self->obj[95].t = self->obj[48].t;
               flipU(&self->obj[95].t);
//image1280-1-4-0-7-2-5-0-1-0-60-0-4-5-7-6-80-7
self->obj[96] = createObject("", 814, 2203, 1);
self->obj[96].t = self->obj[4].t;
//image1280-1-4-0-7-2-5-0-1-0-60-0-4-5-7-6-80-3
self->obj[97] = createObject("", 708, 2128, 1);
self->obj[97].t = self->obj[4].t;
               flipU(&self->obj[97].t);
//image1426-3-5-4-9-0-0-2-3
self->obj[98] = createObject("", 1783, 3166, 1);
self->obj[98].t = self->obj[48].t;
               flipU(&self->obj[98].t);
//image1280-1-4-0-7-2-5-0-1-0-60-0-4-5-7-6-80-7-5
self->obj[99] = createObject("", 1881, 3042, 1);
self->obj[99].t = self->obj[4].t;
//image1952-8
self->obj[100] = createObject("", 1843, 2863, 1);
self->obj[100].t = self->obj[66].t;
//image1941-6
self->obj[101] = createObject("", 1787, 2867, 1);
self->obj[101].t = self->obj[67].t;
               flipU(&self->obj[101].t);
//image1280-1-4-0-7-2-5-0-1-0-60-0-4-5-7-6-80-3-6
self->obj[102] = createObject("", 1774, 2966, 1);
self->obj[102].t = self->obj[4].t;
               flipU(&self->obj[102].t);
//image1426-3-5-4-9-0-0-2-30
self->obj[103] = createObject("", 1704, 2431, 1);
self->obj[103].t = self->obj[48].t;
               flipU(&self->obj[103].t);
//image1280-1-4-0-7-2-5-0-1-0-60-0-4-5-7-6-80-7-0
self->obj[104] = createObject("", 1801, 2307, 1);
self->obj[104].t = self->obj[4].t;
//snake
self->obj[105] = createObject("/rd/snake.png", 924, 3209, 1);
//image1941
self->obj[106] = createObject("", 618, 2956, 1);
self->obj[106].t = self->obj[67].t;
//image1952
self->obj[107] = createObject("", 1206, 3249, 1);
self->obj[107].t = self->obj[66].t;
               flipU(&self->obj[107].t);
//image1941-5
self->obj[108] = createObject("", 3027, 3122, 1);
self->obj[108].t = self->obj[67].t;
//image1952-8-8
self->obj[109] = createObject("", 3505, 3256, 1);
self->obj[109].t = self->obj[66].t;
//image1952-8-9
self->obj[110] = createObject("", 2485, 1273, 1);
self->obj[110].t = self->obj[66].t;
//image1941-5-5-5
self->obj[111] = createObject("", 2761, 603, 1);
self->obj[111].t = self->obj[67].t;
               flipU(&self->obj[111].t);
//image1941-5-5-8
self->obj[112] = createObject("", 885, 1190, 1);
self->obj[112].t = self->obj[67].t;
               flipU(&self->obj[112].t);
//image1952-8-9-8-6
self->obj[113] = createObject("", 1311, 1235, 1);
self->obj[113].t = self->obj[66].t;
//image1952-8-9-8-3
self->obj[114] = createObject("", 1114, 1477, 1);
self->obj[114].t = self->obj[66].t;
               flipU(&self->obj[114].t);
//image1941-5-5-8-8
self->obj[115] = createObject("", 1579, 713, 1);
self->obj[115].t = self->obj[67].t;
//image1941-6-1
self->obj[116] = createObject("", 1327, 3192, 1);
self->obj[116].t = self->obj[67].t;
               flipU(&self->obj[116].t);
//image943-8-1
self->obj[117] = createObject("", 1543, 1241, 1);
self->obj[117].t = self->obj[11].t;
//image836-6-7-5-4
self->obj[118] = createObject("", 1135, 3042, 1);
self->obj[118].t = self->obj[2].t;
               flipU(&self->obj[118].t);
//image836-6-7-5-2
self->obj[119] = createObject("", 1051, 3065, 1);
self->obj[119].t = self->obj[2].t;
               flipU(&self->obj[119].t);
//image836-6-7-54-2
self->obj[120] = createObject("", 2182, 2665, 1);
self->obj[120].t = self->obj[2].t;
               flipU(&self->obj[120].t);
//image825-2-8-5-50-2
self->obj[121] = createObject("", 2779, 2113, 1);
self->obj[121].t = self->obj[1].t;
//image825-5
self->obj[122] = createObject("", 2727, 1264, 1);
self->obj[122].t = self->obj[1].t;
//image836-5
self->obj[123] = createObject("", 3275, 720, 1);
self->obj[123].t = self->obj[2].t;
               flipU(&self->obj[123].t);
//image836-3
self->obj[124] = createObject("", 3354, 641, 1);
self->obj[124].t = self->obj[2].t;
               flipU(&self->obj[124].t);
//image836-9
self->obj[125] = createObject("", 3168, 693, 1);
self->obj[125].t = self->obj[2].t;
               flipU(&self->obj[125].t);
//image943-8-1-6
self->obj[126] = createObject("", 1634, 1287, 1);
self->obj[126].t = self->obj[11].t;
//image943-8-1-2
self->obj[127] = createObject("", 1746, 1274, 1);
self->obj[127].t = self->obj[11].t;
               flipU(&self->obj[127].t);
int texID[12] = { 0, 1, 2, 3, 4, 5, 6, 11, 48, 66, 67, 105};
self->tex = texID;

self->updateScene = updateJardin;
}