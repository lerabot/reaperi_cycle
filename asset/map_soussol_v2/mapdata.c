void loadSoussolData(scene* self) {
////MAP DATA////
setMapInfo(self, 2000, 2000, 523, 151);

////OBJECT DATA////
self->objNum = 103;
self->obj = malloc(self->objNum * sizeof(gameObject));
//image116
self->obj[0] = createObject("/rd/soussol_floor.png", 2155, 692, 1);
//image51-8-0-6-2
self->obj[1] = createObject("/rd/minibox2.png", 626, 1337, 1);
               flipU(&self->obj[1].t);
//image73-048
self->obj[2] = createObject("/rd/box2.png", 356, 490, 1);
//image73-04
self->obj[3] = createObject("", 263, 456, 1);
self->obj[3].t = self->obj[2].t;
               flipU(&self->obj[3].t);
//image51-8-0
self->obj[4] = createObject("", 1083, 865, 1);
self->obj[4].t = self->obj[1].t;
               flipU(&self->obj[4].t);
//image51-8
self->obj[5] = createObject("", 952, 884, 1);
self->obj[5].t = self->obj[1].t;
               flipU(&self->obj[5].t);
//image73-96-0
self->obj[6] = createObject("", 1034, 813, 1);
self->obj[6].t = self->obj[2].t;
//image84-9-4
self->obj[7] = createObject("/rd/box1.png", 909, 901, 1);
               flipU(&self->obj[7].t);
//image73-96
self->obj[8] = createObject("", 1606, 853, 1);
self->obj[8].t = self->obj[2].t;
//image84-9
self->obj[9] = createObject("", 1481, 941, 1);
self->obj[9].t = self->obj[7].t;
               flipU(&self->obj[9].t);
//image18-4-1
self->obj[10] = createObject("/rd/wallCorner.png", 1491, 1729, 1);
//image40-0-2-2-3-9-0
self->obj[11] = createObject("/rd/wall2.png", 950, 1177, 1);
//image29-5
self->obj[12] = createObject("/rd/wall1.png", 847, 1133, 1);
//image18-4-4
self->obj[13] = createObject("", 489, 1676, 1);
self->obj[13].t = self->obj[10].t;
//image40-0-2-2-3-9
self->obj[14] = createObject("", 724, 1063, 1);
self->obj[14].t = self->obj[11].t;
//image40-0-2-2-3
self->obj[15] = createObject("", 611, 1007, 1);
self->obj[15].t = self->obj[11].t;
//image18-8
self->obj[16] = createObject("", 335, 1050, 1);
self->obj[16].t = self->obj[10].t;
//image40-0-22-0
self->obj[17] = createObject("", 1612, 449, 1);
self->obj[17].t = self->obj[11].t;
//image29-3-5-8
self->obj[18] = createObject("", 486, 1021, 1);
self->obj[18].t = self->obj[12].t;
               flipU(&self->obj[18].t);
//image29-3-5
self->obj[19] = createObject("", 824, 855, 1);
self->obj[19].t = self->obj[12].t;
               flipU(&self->obj[19].t);
//image40-0-2-2
self->obj[20] = createObject("", 945, 786, 1);
self->obj[20].t = self->obj[11].t;
               flipU(&self->obj[20].t);
//image18
self->obj[21] = createObject("", 1336, 883, 1);
self->obj[21].t = self->obj[10].t;
//image40
self->obj[22] = createObject("", 1174, 840, 1);
self->obj[22].t = self->obj[11].t;
//image29
self->obj[23] = createObject("", 1071, 799, 1);
self->obj[23].t = self->obj[12].t;
//image84
self->obj[24] = createObject("", 1300, 816, 1);
self->obj[24].t = self->obj[7].t;

//image40-4
self->obj[25] = createObject("", 1497, 840, 1);
self->obj[25].t = self->obj[11].t;
               flipU(&self->obj[25].t);
//image29-3
self->obj[26] = createObject("", 1599, 798, 1);
self->obj[26].t = self->obj[12].t;
               flipU(&self->obj[26].t);
//image40-0-2
self->obj[27] = createObject("", 1721, 730, 1);
self->obj[27].t = self->obj[11].t;
               flipU(&self->obj[27].t);
//image29-4
self->obj[28] = createObject("", 711, 608, 1);
self->obj[28].t = self->obj[12].t;
//image40-0
self->obj[29] = createObject("", 589, 540, 1);
self->obj[29].t = self->obj[11].t;
//image40-0-1
self->obj[30] = createObject("", 476, 483, 1);
self->obj[30].t = self->obj[11].t;
//image29-4-1
self->obj[31] = createObject("", 373, 440, 1);
self->obj[31].t = self->obj[12].t;
//image29-4-8
self->obj[32] = createObject("", 1510, 406, 1);
self->obj[32].t = self->obj[12].t;
//image40-0-7
self->obj[33] = createObject("", 1388, 338, 1);
self->obj[33].t = self->obj[11].t;
//image40-0-1-0
self->obj[34] = createObject("", 1276, 282, 1);
self->obj[34].t = self->obj[11].t;
//image29-4-1-5
self->obj[35] = createObject("", 1173, 239, 1);
self->obj[35].t = self->obj[12].t;
//image40-0-22
self->obj[36] = createObject("", 1051, 169, 1);
self->obj[36].t = self->obj[11].t;
//image40-0-2-7
self->obj[37] = createObject("", 1832, 673, 1);
self->obj[37].t = self->obj[11].t;
               flipU(&self->obj[37].t);
//image29-4-5
self->obj[38] = createObject("", 186, 1021, 1);
self->obj[38].t = self->obj[12].t;
//image40-0-1-3
self->obj[39] = createObject("", 250, 371, 1);
self->obj[39].t = self->obj[11].t;
//image40-0-1-3-7
self->obj[40] = createObject("", 137, 314, 1);
self->obj[40].t = self->obj[11].t;
//image18-4
self->obj[41] = createObject("", 1049, 1839, 1);
self->obj[41].t = self->obj[10].t;
//image40-03
self->obj[42] = createObject("", 887, 1797, 1);
self->obj[42].t = self->obj[11].t;
//image29-0
self->obj[43] = createObject("", 785, 1755, 1);
self->obj[43].t = self->obj[12].t;
//image40-4-8
self->obj[44] = createObject("", 1210, 1797, 1);
self->obj[44].t = self->obj[11].t;
               flipU(&self->obj[44].t);
//image29-3-3
self->obj[45] = createObject("", 1313, 1755, 1);
self->obj[45].t = self->obj[12].t;
               flipU(&self->obj[45].t);
//image40-03-1
self->obj[46] = createObject("", 661, 1686, 1);
self->obj[46].t = self->obj[11].t;
//image40-03-1-8
self->obj[47] = createObject("", 327, 1634, 1);
self->obj[47].t = self->obj[11].t;
//image29-0-7
self->obj[48] = createObject("", 224, 1589, 1);
self->obj[48].t = self->obj[12].t;
//image40-0-22-0-0
self->obj[49] = createObject("", 1653, 1687, 1);
self->obj[49].t = self->obj[11].t;
               flipU(&self->obj[49].t);
//image29-4-8-1
self->obj[50] = createObject("", 1754, 1644, 1);
self->obj[50].t = self->obj[12].t;
               flipU(&self->obj[50].t);
//image40-0-7-4
self->obj[51] = createObject("", 1876, 1576, 1);
self->obj[51].t = self->obj[11].t;
               flipU(&self->obj[51].t);
//image73
self->obj[52] = createObject("", 1454, 745, 1);
self->obj[52].t = self->obj[2].t;
              flipU(&self->obj[52].t);
//image73-2
self->obj[53] = createObject("", 1289, 165, 1);
self->obj[53].t = self->obj[2].t;
               flipU(&self->obj[53].t);
//image73-2-2
self->obj[54] = createObject("", 1257, 113, 1);
self->obj[54].t = self->obj[2].t;

//image51-0
self->obj[55] = createObject("", 1640, 362, 1);
self->obj[55].t = self->obj[1].t;
//image62-1
self->obj[56] = createObject("/rd/minibox.png", 1639, 390, 1);
//image62-3
self->obj[57] = createObject("", 1287, 149, 1);
self->obj[57].t = self->obj[56].t;
//image51-6
self->obj[58] = createObject("", 1376, 145, 1);
self->obj[58].t = self->obj[1].t;
               flipU(&self->obj[58].t);
//image84-3
self->obj[59] = createObject("", 1027, 1776, 1);
self->obj[59].t = self->obj[7].t;
               flipU(&self->obj[59].t);
//image73-0
self->obj[60] = createObject("", 1499, 1646, 1);
self->obj[60].t = self->obj[2].t;
//image73-9
self->obj[61] = createObject("", 1546, 1597, 1);
self->obj[61].t = self->obj[2].t;
               flipU(&self->obj[61].t);
//image73-27
self->obj[62] = createObject("", 1630, 1559, 1);
self->obj[62].t = self->obj[2].t;
//image73-0-4
self->obj[63] = createObject("", 1536, 1330, 1);
self->obj[63].t = self->obj[2].t;
//image73-9-9
self->obj[64] = createObject("", 1583, 1281, 1);
self->obj[64].t = self->obj[2].t;
               flipU(&self->obj[64].t);
//image73-27-9
self->obj[65] = createObject("", 1667, 1242, 1);
self->obj[65].t = self->obj[2].t;
//image73-0-1
self->obj[66] = createObject("", 1423, 1307, 1);
self->obj[66].t = self->obj[2].t;
//image73-9-5
self->obj[67] = createObject("", 1470, 1258, 1);
self->obj[67].t = self->obj[2].t;
               flipU(&self->obj[67].t);
//image73-27-0
self->obj[68] = createObject("", 1554, 1220, 1);
self->obj[68].t = self->obj[2].t;
//image73-0-0
self->obj[69] = createObject("", 909, 1685, 1);
self->obj[69].t = self->obj[2].t;
//image73-0-7
self->obj[70] = createObject("", 804, 1649, 1);
self->obj[70].t = self->obj[2].t;
               flipU(&self->obj[70].t);
//image51-8-0-6
self->obj[71] = createObject("", 890, 1627, 1);
self->obj[71].t = self->obj[1].t;
               flipU(&self->obj[71].t);
//image51-8-0-9
self->obj[72] = createObject("", 1141, 1677, 1);
self->obj[72].t = self->obj[1].t;
//image62-5
self->obj[73] = createObject("", 849, 1600, 1);
self->obj[73].t = self->obj[56].t;
//image62-9
self->obj[74] = createObject("", 1023, 1830, 1);
self->obj[74].t = self->obj[56].t;
//image62-33
self->obj[75] = createObject("", 879, 1722, 1);
self->obj[75].t = self->obj[56].t;
//image84-3-4
self->obj[76] = createObject("", 336, 1003, 1);
self->obj[76].t = self->obj[7].t;
               flipU(&self->obj[76].t);
//image51-8-3
self->obj[77] = createObject("", 240, 926, 1);
self->obj[77].t = self->obj[1].t;
               flipU(&self->obj[77].t);
//image51-8-6
self->obj[78] = createObject("", 220, 900, 1);
self->obj[78].t = self->obj[1].t;
               flipU(&self->obj[78].t);
//image62-5-5
self->obj[79] = createObject("", 330, 1057, 1);
self->obj[79].t = self->obj[56].t;
               flipU(&self->obj[79].t);
//image62-5-3
self->obj[80] = createObject("", 443, 915, 1);
self->obj[80].t = self->obj[56].t;
//image73-6
self->obj[81] = createObject("", 356, 752, 1);
self->obj[81].t = self->obj[2].t;
               flipU(&self->obj[81].t);
//image73-3
self->obj[82] = createObject("", 406, 707, 1);
self->obj[82].t = self->obj[2].t;
//image62-5-5-9
self->obj[83] = createObject("", 377, 745, 1);
self->obj[83].t = self->obj[56].t;
//image62-5-5-0
self->obj[84] = createObject("", 287, 492, 1);
self->obj[84].t = self->obj[56].t;
               flipU(&self->obj[84].t);
//image73-2-5
self->obj[85] = createObject("", 493, 403, 1);
self->obj[85].t = self->obj[2].t;
               flipU(&self->obj[85].t);
//image73-2-2-0
self->obj[86] = createObject("", 461, 352, 1);
self->obj[86].t = self->obj[2].t;
               flipU(&self->obj[86].t);
//image62-3-7
self->obj[87] = createObject("", 491, 387, 1);
self->obj[87].t = self->obj[56].t;
//image73-2-0
self->obj[88] = createObject("", 600, 380, 1);
self->obj[88].t = self->obj[2].t;
               flipU(&self->obj[88].t);
//image73-2-2-5
self->obj[89] = createObject("", 569, 329, 1);
self->obj[89].t = self->obj[2].t;
               flipU(&self->obj[89].t);
//image62-3-7-5
self->obj[90] = createObject("", 523, 440, 1);
self->obj[90].t = self->obj[56].t;
               flipU(&self->obj[90].t);
//image62-3-7-4
self->obj[91] = createObject("", 483, 303, 1);
self->obj[91].t = self->obj[56].t;
//image62-3-7-1
self->obj[92] = createObject("", 411, 310, 1);
self->obj[92].t = self->obj[56].t;
//image73-0-4-0
self->obj[93] = createObject("", 480, 1600, 1);
self->obj[93].t = self->obj[2].t;
//image73-9-5-5
self->obj[94] = createObject("", 414, 1529, 1);
self->obj[94].t = self->obj[2].t;
               flipU(&self->obj[94].t);
//image73-9-5-5-3
self->obj[95] = createObject("", 614, 1310, 1);
self->obj[95].t = self->obj[2].t;
//image62-33-5
self->obj[96] = createObject("", 581, 1355, 1);
self->obj[96].t = self->obj[56].t;
//image51-8-0-6-5
self->obj[97] = createObject("", 534, 1286, 1);
self->obj[97].t = self->obj[1].t;
//lampe
self->obj[98] = createObject("/rd/coupe1.png", 1525, 1265, 1);
//tableau_2
self->obj[99] = createObject("/rd/box1_cloth.png", 1285, 755, 1);
                flipU(&self->obj[99].t);
//tableau_1
self->obj[100] = createObject("", 1007, 1723, 1);
self->obj[100].t = self->obj[99].t;
               flipU(&self->obj[100].t);
//image108
self->obj[101] = createObject("", 319, 940, 1);
self->obj[101].t = self->obj[99].t;


self->obj[102] = createObject("/rd/stair_close.png", 523, 211, 1);


int texID[10] = {0, 1, 2, 7, 10, 11, 12, 56, 98, 99};
self->tex = texID;

self->updateScene = updateSoussol;
}