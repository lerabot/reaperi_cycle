void loadDesertData(scene* self) {
////MAP DATA////
setMapInfo(self, 8000, 8000, 814, 476);

////OBJECT DATA////
self->objNum = 61;
self->obj = malloc(self->objNum * sizeof(gameObject));
//image1537
self->obj[0] = createObject("/rd/desert_floor.png", 8311, 2141, 1);
//image117-9-1
self->obj[1] = createObject("/rd/flag1.png", 625, 501, 1);
//image29
self->obj[2] = createObject("/rd/arc.png", 636, 397, 1);
//image40
self->obj[3] = createObject("/rd/brique1.png", 3312, 1493, 1);
//head
self->obj[4] = createObject("/rd/statue_tete.png", 1398, 5319, 1);
//image51
self->obj[5] = createObject("/rd/brique2.png", 1607, 5283, 1);
//image95-3-1-5
self->obj[6] = createObject("/rd/palmier.png", 5513, 6846, 1);
//image95-3-1-26
self->obj[7] = createObject("", 5338, 6814, 1);
self->obj[7].t = self->obj[6].t;
//tent
self->obj[8] = createObject("/rd/tent_small.png", 5454, 6689, 1);
               flipU(&self->obj[8].t);
//image84
self->obj[9] = createObject("/rd/fontaine.png", 5862, 6526, 1);
//image51-3-0
self->obj[10] = createObject("", 6368, 1479, 1);
self->obj[10].t = self->obj[5].t;
//organ_2
self->obj[11] = createObject("/rd/orgue.png", 6278, 1499, 1);
//image117
self->obj[12] = createObject("", 3283, 1675, 1);
self->obj[12].t = self->obj[1].t;
//organ_1
self->obj[13] = createObject("", 3400, 1495, 1);
self->obj[13].t = self->obj[11].t;
//image51-3-0-4-6
self->obj[14] = createObject("", 6485, 4335, 1);
self->obj[14].t = self->obj[5].t;
//organ_3
self->obj[15] = createObject("", 6402, 4325, 1);
self->obj[15].t = self->obj[11].t;
//image117-9
self->obj[16] = createObject("", 833, 361, 1);
self->obj[16].t = self->obj[1].t;
               flipU(&self->obj[16].t);
//image117-9-3
self->obj[17] = createObject("", 1010, 432, 1);
self->obj[17].t = self->obj[1].t;
               flipU(&self->obj[17].t);
//image117-9-2
self->obj[18] = createObject("", 1170, 481, 1);
self->obj[18].t = self->obj[1].t;
               flipU(&self->obj[18].t);
//image117-9-8
self->obj[19] = createObject("", 1335, 535, 1);
self->obj[19].t = self->obj[1].t;
               flipU(&self->obj[19].t);
//image117-9-3-7
self->obj[20] = createObject("", 791, 606, 1);
self->obj[20].t = self->obj[1].t;
//image117-9-2-6
self->obj[21] = createObject("", 979, 697, 1);
self->obj[21].t = self->obj[1].t;
//image117-9-8-4
self->obj[22] = createObject("", 1181, 804, 1);
self->obj[22].t = self->obj[1].t;
//image117-9-8-4-6
self->obj[23] = createObject("", 3469, 1488, 1);
self->obj[23].t = self->obj[1].t;
               flipU(&self->obj[23].t);
//image117-9-8-4-6-3
self->obj[24] = createObject("", 3309, 1455, 1);
self->obj[24].t = self->obj[1].t;
//image117-9-8-4-6-36
self->obj[25] = createObject("", 3674, 1492, 1);
self->obj[25].t = self->obj[1].t;
               flipU(&self->obj[25].t);
//image51-3
self->obj[26] = createObject("", 4787, 1479, 1);
self->obj[26].t = self->obj[5].t;
//image117-9-8-4-6-36-7
self->obj[27] = createObject("", 4795, 1471, 1);
self->obj[27].t = self->obj[1].t;
               flipU(&self->obj[27].t);
//image117-9-8-4-6-36-7-9
self->obj[28] = createObject("", 6191, 1460, 1);
self->obj[28].t = self->obj[1].t;
//image117-9-8-4-6-36-7-9-0
self->obj[29] = createObject("", 6386, 1452, 1);
self->obj[29].t = self->obj[1].t;
               flipU(&self->obj[29].t);
//image117-9-8-4-6-36-7-9-0-0
self->obj[30] = createObject("", 6356, 1770, 1);
self->obj[30].t = self->obj[1].t;
               flipU(&self->obj[30].t);
//image117-9-8-4-6-36-7-9-0-0-1
self->obj[31] = createObject("", 6414, 2935, 1);
self->obj[31].t = self->obj[1].t;
               flipU(&self->obj[31].t);
//image51-3-0-4
self->obj[32] = createObject("", 6136, 4310, 1);
self->obj[32].t = self->obj[5].t;
               flipU(&self->obj[32].t);
//image40-1
self->obj[33] = createObject("", 6226, 4301, 1);
self->obj[33].t = self->obj[3].t;
//image117-9-8-4-6-36-7-9-0-0-1-5
self->obj[34] = createObject("", 6480, 4274, 1);
self->obj[34].t = self->obj[1].t;
               flipU(&self->obj[34].t);
//image117-9-8-4-6-36-7-9-0-0-1-5-2
self->obj[35] = createObject("", 6285, 4271, 1);
self->obj[35].t = self->obj[1].t;
//image117-9-8-4-6-36-7-9-0-0-1-5-2-6
self->obj[36] = createObject("", 6354, 4568, 1);
self->obj[36].t = self->obj[1].t;
//image95-3-1
self->obj[37] = createObject("", 5999, 6138, 1);
self->obj[37].t = self->obj[6].t;
//image117-9-8-4-6-36-7-9-0-0-1-5-2-9
self->obj[38] = createObject("", 5969, 6269, 1);
self->obj[38].t = self->obj[1].t;
//image95
self->obj[39] = createObject("", 6258, 6632, 1);
self->obj[39].t = self->obj[6].t;
//image117-9-8-4-6-36-7-9-0-0-1-5-2-9-6
self->obj[40] = createObject("", 6287, 6488, 1);
self->obj[40].t = self->obj[1].t;
               flipU(&self->obj[40].t);
//image117-9-8-4-6-36-7-9-0-0-1-5-2-9-6-8
self->obj[41] = createObject("", 6175, 6528, 1);
self->obj[41].t = self->obj[1].t;
               flipU(&self->obj[41].t);
//image117-9-8-4-6-36-7-9-0-0-1-5-2-9-6-1
self->obj[42] = createObject("", 6402, 6453, 1);
self->obj[42].t = self->obj[1].t;
               flipU(&self->obj[42].t);
//image117-9-8-4-6-36-7-9-0-0-1-5-2-9-6-1-4
self->obj[43] = createObject("", 6196, 6127, 1);
self->obj[43].t = self->obj[1].t;
//image117-9-8-4-6-36-7-9-0-0-1-5-2-9-9
self->obj[44] = createObject("", 6079, 6202, 1);
self->obj[44].t = self->obj[1].t;
//image95-3
self->obj[45] = createObject("", 6303, 6611, 1);
self->obj[45].t = self->obj[6].t;
//image95-3-4
self->obj[46] = createObject("", 6576, 6402, 1);
self->obj[46].t = self->obj[6].t;
//image95-3-5
self->obj[47] = createObject("", 6057, 6108, 1);
self->obj[47].t = self->obj[6].t;
//image95-3-1-4
self->obj[48] = createObject("", 5754, 6468, 1);
self->obj[48].t = self->obj[6].t;
//image95-3-1-3
self->obj[49] = createObject("", 5933, 6683, 1);
self->obj[49].t = self->obj[6].t;
//image95-3-1-9
self->obj[50] = createObject("", 5893, 6663, 1);
self->obj[50].t = self->obj[6].t;
//image95-3-1-8
self->obj[51] = createObject("", 5963, 6631, 1);
self->obj[51].t = self->obj[6].t;
//image95-3-1-2
self->obj[52] = createObject("", 5670, 6789, 1);
self->obj[52].t = self->obj[6].t;
//image95-3-1-1
self->obj[53] = createObject("", 5553, 6842, 1);
self->obj[53].t = self->obj[6].t;
//image95-3-1-29
self->obj[54] = createObject("", 5330, 6659, 1);
self->obj[54].t = self->obj[6].t;
//image95-3-1-49
self->obj[55] = createObject("", 5354, 6609, 1);
self->obj[55].t = self->obj[6].t;
//image95-3-1-34
self->obj[56] = createObject("", 6184, 4426, 1);
self->obj[56].t = self->obj[6].t;
//image40-1-1
self->obj[57] = createObject("", 1150, 5354, 1);
self->obj[57].t = self->obj[3].t;
//image117-1
self->obj[58] = createObject("", 3407, 1544, 1);
self->obj[58].t = self->obj[1].t;
//image117-0
self->obj[59] = createObject("", 3057, 1938, 1);
self->obj[59].t = self->obj[1].t;
//image117-0-0
self->obj[60] = createObject("", 1612, 5159, 1);
self->obj[60].t = self->obj[1].t;
int texID[10] = { 0, 1, 2, 3, 4, 5, 6, 8, 9, 11};
self->tex = texID;

self->updateScene = updateDesert;
}