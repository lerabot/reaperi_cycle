void loadJardinData(scene* self) {
////MAP DATA////
self->mapSize[0] = 2000;
self->mapSize[1] = 2000;

////OBJECT DATA////
self->objNum = 56;
self->obj = malloc(self->objNum * sizeof(gameObject));
//floor
self->obj[0] = createObject("/rd/jardin.png", 2649, 1064, 1);
//image60-3
self->obj[1] = createObject("/rd/rox1.png", 1188, 1432, 1);
               flipU(&self->obj[1].t);
//image71
self->obj[2] = createObject("/rd/lac.png", 1293, 1521, 1);
//image16-4
self->obj[3] = createObject("/rd/tree.png", 1340, 1564, 1);
//image902-2-6
self->obj[4] = createObject("/rd/tree2.png", 1374, 1567, 1);
//image902-2-7
self->obj[5] = createObject("", 1451, 1495, 1);
self->obj[5].t = self->obj[4].t;
//image902-2-68
self->obj[6] = createObject("", 1350, 1472, 1);
self->obj[6].t = self->obj[4].t;
//image16-0-5
self->obj[7] = createObject("", 1409, 1299, 1);
self->obj[7].t = self->obj[3].t;
//image16-0-8
self->obj[8] = createObject("", 1483, 1247, 1);
self->obj[8].t = self->obj[3].t;
//image902-2-5-4-8-5
self->obj[9] = createObject("", 387, 513, 1);
self->obj[9].t = self->obj[4].t;
               flipU(&self->obj[9].t);
//image16-0-8-7
self->obj[10] = createObject("", 1390, 1175, 1);
self->obj[10].t = self->obj[3].t;
//image16-1-1
self->obj[11] = createObject("", 718, 1583, 1);
self->obj[11].t = self->obj[3].t;
               flipU(&self->obj[11].t);
//image902-2
self->obj[12] = createObject("", 879, 1689, 1);
self->obj[12].t = self->obj[4].t;
//image902
self->obj[13] = createObject("", 1016, 1722, 1);
self->obj[13].t = self->obj[4].t;
               flipU(&self->obj[13].t);
//gazebo
self->obj[14] = createObject("/rd/structure.png", 954, 1530, 1);
//serpent
self->obj[15] = createObject("/rd/snake.png", 965, 1390, 1);
//image49
self->obj[16] = createObject("/rd/rox2.png", 1015, 1424, 1);
//image60
self->obj[17] = createObject("", 902, 1429, 1);
self->obj[17].t = self->obj[1].t;
               flipU(&self->obj[17].t);
//image902-2-5
self->obj[18] = createObject("", 577, 1615, 1);
self->obj[18].t = self->obj[4].t;
               flipU(&self->obj[18].t);
//image16-1-0-7
self->obj[19] = createObject("", 652, 1517, 1);
self->obj[19].t = self->obj[3].t;
               flipU(&self->obj[19].t);
//image16-1-0-72
self->obj[20] = createObject("", 715, 1437, 1);
self->obj[20].t = self->obj[3].t;
               flipU(&self->obj[20].t);
//image60-4
self->obj[21] = createObject("", 757, 1254, 1);
self->obj[21].t = self->obj[1].t;
//image902-2-5-0
self->obj[22] = createObject("", 485, 1474, 1);
self->obj[22].t = self->obj[4].t;
               flipU(&self->obj[22].t);
//image16-1-0-72-3
self->obj[23] = createObject("", 442, 1345, 1);
self->obj[23].t = self->obj[3].t;
               flipU(&self->obj[23].t);
//image16-1-0-72-1-8
self->obj[24] = createObject("", 474, 1207, 1);
self->obj[24].t = self->obj[3].t;
               flipU(&self->obj[24].t);
//image16-1-0-72-1-0
self->obj[25] = createObject("", 628, 1109, 1);
self->obj[25].t = self->obj[3].t;
               flipU(&self->obj[25].t);
//image902-2-5-4
self->obj[26] = createObject("", 477, 1106, 1);
self->obj[26].t = self->obj[4].t;
               flipU(&self->obj[26].t);
//image16-1-0-72-1-0-5
self->obj[27] = createObject("", 596, 1000, 1);
self->obj[27].t = self->obj[3].t;
               flipU(&self->obj[27].t);
//image16-1-0-72-1-0-6
self->obj[28] = createObject("", 742, 926, 1);
self->obj[28].t = self->obj[3].t;
               flipU(&self->obj[28].t);
//image902-2-5-4-6
self->obj[29] = createObject("", 617, 939, 1);
self->obj[29].t = self->obj[4].t;
//image16-1-0-72-1-0-0
self->obj[30] = createObject("", 829, 836, 1);
self->obj[30].t = self->obj[3].t;
               flipU(&self->obj[30].t);
//image16-1-0-72-1-0-7
self->obj[31] = createObject("", 718, 857, 1);
self->obj[31].t = self->obj[3].t;
               flipU(&self->obj[31].t);
//image16-1-0-72-1-0-7-7-75
self->obj[32] = createObject("", 519, 669, 1);
self->obj[32].t = self->obj[3].t;
               flipU(&self->obj[32].t);
//image16-1-0-72-1-0-7-7-4
self->obj[33] = createObject("", 514, 585, 1);
self->obj[33].t = self->obj[3].t;
               flipU(&self->obj[33].t);
//image902-2-5-4-62
self->obj[34] = createObject("", 681, 661, 1);
self->obj[34].t = self->obj[4].t;
//image16-0-4
self->obj[35] = createObject("", 1570, 1292, 1);
self->obj[35].t = self->obj[3].t;
//image16-0-1
self->obj[36] = createObject("", 1602, 1167, 1);
self->obj[36].t = self->obj[3].t;
//image16-0-47
self->obj[37] = createObject("", 1568, 1037, 1);
self->obj[37].t = self->obj[3].t;
//image902-2-72-5
self->obj[38] = createObject("", 1679, 1027, 1);
self->obj[38].t = self->obj[4].t;
//image16-0-0-1
self->obj[39] = createObject("", 1509, 826, 1);
self->obj[39].t = self->obj[3].t;
//image16-0-0-4
self->obj[40] = createObject("", 1721, 892, 1);
self->obj[40].t = self->obj[3].t;
//image16-0-0-6
self->obj[41] = createObject("", 1663, 741, 1);
self->obj[41].t = self->obj[3].t;
//image16-0-0-44
self->obj[42] = createObject("", 1718, 622, 1);
self->obj[42].t = self->obj[3].t;
//image16-1-0-72-1-0-7-7-4-0-4
self->obj[43] = createObject("", 720, 458, 1);
self->obj[43].t = self->obj[3].t;
               flipU(&self->obj[43].t);
//image49-4
self->obj[44] = createObject("", 1337, 1016, 1);
self->obj[44].t = self->obj[16].t;
               flipU(&self->obj[44].t);
//image60-4-0
self->obj[45] = createObject("", 734, 291, 1);
self->obj[45].t = self->obj[1].t;
               flipU(&self->obj[45].t);
//image49-4-1
self->obj[46] = createObject("", 787, 278, 1);
self->obj[46].t = self->obj[16].t;
//image60-4-0-1
self->obj[47] = createObject("", 1446, 650, 1);
self->obj[47].t = self->obj[1].t;
               flipU(&self->obj[47].t);
//image49-4-1-3
self->obj[48] = createObject("", 1499, 636, 1);
self->obj[48].t = self->obj[16].t;
//image49-4-1-3-1
self->obj[49] = createObject("", 1673, 444, 1);
self->obj[49].t = self->obj[16].t;
               flipU(&self->obj[49].t);
//image16-0-0-46-7
self->obj[50] = createObject("", 1752, 542, 1);
self->obj[50].t = self->obj[3].t;
//image16-1-0-72-1-0-7-7-4-0-7-8
self->obj[51] = createObject("", 503, 460, 1);
self->obj[51].t = self->obj[3].t;
               flipU(&self->obj[51].t);
//image16-1-0-72-1-0-7-7-4-0-7-3
self->obj[52] = createObject("", 564, 402, 1);
self->obj[52].t = self->obj[3].t;
               flipU(&self->obj[52].t);
//image16-1-0-72-1-0-7-7-4-0-7-85
self->obj[53] = createObject("", 493, 328, 1);
self->obj[53].t = self->obj[3].t;
               flipU(&self->obj[53].t);
//image16-0
self->obj[54] = createObject("", 1210, 1506, 1);
self->obj[54].t = self->obj[3].t;
//gate
self->obj[55] = createObject("/rd/gate.png", 1586, 130, 1);
int texID[9] = { 0, 1, 2, 3, 4, 14, 15, 16, 55};
self->tex = texID;

self->updateScene = updateJardin;
}