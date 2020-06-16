# 2020-pd2-DoodleJump

## Video link
## How to play
左鍵往左 右鍵往右 空白鍵發射子彈  
## Requirements
都有完成，以下為說明：  
At least two kinds of platforms : 四種Platform green, blue, gray, brown   
At least two kinds of game props : 三種道具 彈簧, 火箭, 防護罩  
Monster : 三種怪物：綠色的不會動，紅色的會左右震動，藍色的會在畫面中左右移動  
At least one another hazard : 黑洞  
Eliminate/Avoid one hazard someway : 當碰到防護罩時，doodler會變成忍者造型，碰到黑洞和怪物都不會死  
## Polymorphism
BluePlatform 和 GrayPlatform 繼承自 GreenPlatform  
在doodler.cpp 226~235行中，先宣告Greenplatform 的ptr，再根據rand()的結果，決定ptr要指向哪一種Platform  
在doodler.cpp 254行中，Platform的slot repeatMove()，在class定義中為virtual，GreenPlatform的repeatMove()為空函式，Blue的為左右移動，Gray則是上下移動  
## Bonus
平台多兩種  道具多一種  怪物有三種  
左上角有計時功能  
平台會越來越少(15000之前)  
死掉後按下play again可以重新玩  
碰到火箭和防護罩後，doodler會改變造型，並且往左往右會有不同面向  