```
r1 = testsavestr(true);
testdelstr(r1);
r2 = testsavestr(false);
testloadstr(r2);
```
```
newnode:1
newnode:2
新建索引成功
root节点地址是1
newnode:3
newnode:4
newnode:5
newnode:6
newnode:7
newnode:8
newnode:9
newnode:10
erasenode:10,9,6,8,5,3,7,4
-> 3,4,5,6,7,8,9,10
```
```
newnode:3
newnode:4
新建索引成功
root节点地址是3
newnode:5
newnode:6
newnode:7
newnode:8
newnode:9
newnode:10
```
```
loadnode:3
loadnode:4
loadnode:6
loadnode:9
```
str第二次稳定出错
而int第二次不会出错
```
newnode:1
newnode:2
新建索引成功
root节点地址是1
newnode:3
newnode:4
newnode:5
newnode:6
newnode:7
newnode:8
- - -
newnode:3
newnode:4
新建索引成功
root节点地址是3
newnode:5
newnode:6
newnode:7
newnode:8
newnode:9
newnode:10
newnode:11
loadnode:3
loadnode:4
loadnode:6 x
loadnode:8 x
loadnode:7 x
loadnode:9 
loadnode:11
loadnode:5 x
loadnode:10
_ _ _
10r[16689],1t[14898],020t[16434],021h[32609],blet[41057],bsoluteh[8545],bsolutely[188],acknowledgedt[17761],ddedt[39265],dministration[126],advantageous[59],after?[46945],gaint[44385],greedo[49761],greement[29],aims[60],all[182],allowi[70241],llowedg[1121],lreadyu[67681],mbitious[79],america[42],among[28],an[99],andr[82785],nother[187],appear[137],application[215],around[152],as[27],aspect[140],at[158],backbencher[180],backstop[200],bad[123],basis[189],bbcs[262],be[197],becauset[64354],eena[31330],efore[40],being[24],between[266],bilateral5[79104]
10[65],11[58],2020[64],2021[127],able[160],absolute[33],absolutely[188],acknowledged[69],added[153],administration[126],advantageous[59],after[183],again[173],agreed[194],agreement[29],aims[60],all[182],allow[274],allowed[4],already[264],ambitious[79],america[42],among[28],an[99],and[323],another[187],appear[137],application[215],around[152],as[27],aspect[140],at[158],backbencher[180],backstop[200],bad[123],basis[189],bbcs[262],be[197],because[251],been[122],before[40],being[24],between[266],bilateral[309]
_ _ _
billions[72],blackford[26],border[87],borders[288],botched[80],both[254],brexit[223],brexiteers[272],britain[96],britains[41],british[113],brought[208],brussels[74],businesses[221],but[279],buts[333],by[326],cable[163],called[207],came[303],can[104],caroline[156],carry[332],certainty[230],claiming[109],clear[37],come[117],comments[32],commons[86],communication[316],concerned[286],continue[201],control[138],corbyn[280],could[241],countries[268],criticism[19],currently[34],customs[144],days[18],dead[106],deal[247],deals[282],december[242],delayed[55],delivered[90],dem[250],designed[154],determine[218],did[191],dodds[238],dodo[220],doing[14],donald[89],dont[30],downing[219],dups[199],during[150],economy[166],editor[85],end[235],eu[193],
billions[72],blackfordu[6754],orderr[22370],ordersn[73826],otched[80],both[254],brexit[223],brexiteers[272],britaina[24674],ritainsg[10594],ritishe[29026],rought[208],brussels[74],businesses[221],but[279],buts[333],by[326],cable[163],called[207],came[303],can[104],caroline?[40035],arry?[85091],ertaintye[58979],laiming[109],clear[37],come[117],comments[32],commons?[22115],ommunicationr[80995],oncerned[286],continue[201],control[138],corbyn?[71779],oulds[61795],ountries[268],criticismh[4963],urrently[34],customs[144],days[18],dead[106],deal[247],deals[282],december[242],delayed:[14180],elivered[90],dem[250],designedo[39524],etermine[218],did[191],dodds[238],dodo[220],doing[14],donald[89],donte[7780],owning[219],dups[199],during[150],economy[166],editor[85],end[235],eu[193],
```
<B>大概率是数据没有擦干净
