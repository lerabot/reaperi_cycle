void loadTempleData(scene* self) {
////MAP DATA////
setMapInfo(self, 2000, 2000, 945, 200);

////OBJECT DATA////
self->objNum = 29;
self->obj = malloc(self->objNum * sizeof(gameObject));
//image422
self->obj[0] = createObject("/rd/floor.png", 2168, 841, 1);
//image411
self->obj[1] = createObject("/rd/sand.png", 490, 1724, 1);
//gate
self->obj[2] = createObject("/rd/grass.png", 1397, 1741, 1);
//image40-5-4-8
self->obj[3] = createObject("/rd/autel_colonne.png", 947, 1106, 1);
//autel
self->obj[4] = createObject("/rd/autel.png", 944, 980, 1);
//image40
self->obj[5] = createObject("", 944, 838, 1);
self->obj[5].t = self->obj[3].t;
//image51
self->obj[6] = createObject("/rd/grande_colonne.png", 947, 2280, 1);
//image62
self->obj[7] = createObject("/rd/vitrail_2.png", 1119, 1437, 1);
//image73
self->obj[8] = createObject("/rd/vitrail.png", 786, 1427, 1);
//trap
self->obj[9] = createObject("/rd/stair_close.png", 302, 404, 1);
//image106
self->obj[10] = createObject("/rd/gate.png", 1421, 1769, 1);
               flipU(&self->obj[10].t);
//arc
self->obj[11] = createObject("/rd/arc.png", 493, 1784, 1);
               flipU(&self->obj[11].t);
//image40-5
self->obj[12] = createObject("", 1257, 973, 1);
self->obj[12].t = self->obj[3].t;
//image40-5-4
self->obj[13] = createObject("", 633, 974, 1);
self->obj[13].t = self->obj[3].t;
//image62-5
self->obj[14] = createObject("", 1587, 1238, 1);
self->obj[14].t = self->obj[7].t;
//image73-9
self->obj[15] = createObject("", 343, 1235, 1);
self->obj[15].t = self->obj[8].t;
//image51-2
self->obj[16] = createObject("", 179, 1398, 1);
self->obj[16].t = self->obj[6].t;
//image51-5
self->obj[17] = createObject("", 1747, 1399, 1);
self->obj[17].t = self->obj[6].t;
//image95-5
self->obj[18] = createObject("/rd/lampe_orange_lum.png", 787, 1075, 1);
//image95-6
self->obj[19] = createObject("", 779, 929, 1);
self->obj[19].t = self->obj[18].t;
//image95-6-0
self->obj[20] = createObject("", 813, 830, 1);
self->obj[20].t = self->obj[18].t;
//image95-6-0-3
self->obj[21] = createObject("", 864, 732, 1);
self->obj[21].t = self->obj[18].t;
//image95-6-03
self->obj[22] = createObject("", 1107, 925, 1);
self->obj[22].t = self->obj[18].t;
               flipU(&self->obj[22].t);
//image95-6-0-9
self->obj[23] = createObject("", 1077, 834, 1);
self->obj[23].t = self->obj[18].t;
               flipU(&self->obj[23].t);
//image95-6-0-3-1
self->obj[24] = createObject("", 1026, 729, 1);
self->obj[24].t = self->obj[18].t;
               flipU(&self->obj[24].t);
//image95-5-1
self->obj[25] = createObject("", 1096, 1077, 1);
self->obj[25].t = self->obj[18].t;
//image95-6-0-3-1-3
self->obj[26] = createObject("", 154, 380, 1);
self->obj[26].t = self->obj[18].t;
               flipU(&self->obj[26].t);
//image95-6-0-3-1-0
self->obj[27] = createObject("", 304, 485, 1);
self->obj[27].t = self->obj[18].t;
               flipU(&self->obj[27].t);
//image95-6-0-3-1-8
self->obj[28] = createObject("", 457, 374, 1);
self->obj[28].t = self->obj[18].t;
               flipU(&self->obj[28].t);
int texID[12] = { 0, 1, 2, 3, 4, 6, 7, 8, 9, 10, 11, 18};
self->tex = texID;
self->updateScene = updateTemple;
}