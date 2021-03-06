# 天猫精灵AT固件

本示例实现了天猫精灵AT传输功能，编译烧录后烧录任意三元组与天猫精灵配对即可实现AT交互。

## 操作说明

本示例基于TB-02_Kit开发板，使用PB1与PB7作为串口引脚，默认波特率为115200。

## AT指令

|   指令   |       功能      |      备注     |
|----------|-----------------|--------------|
|AT        |测试AT
|AT+GMR    |查询版本号
|AT+RST    |复位模块
|AT+RESTORE|恢复出厂设置
|AT+STATE  |查询配网状态
|AT+SLEEP  |深度睡眠         |暂未实现|
|AT+SEND2ALI|发送数据到天猫精灵音箱  |
|AT+SEND2APP|发送数据到用户手机APP   |
|+DATA:    |收到天猫精灵数据
|+APP:     |收到用户手机APP发来的数据

## 语音控制指令
与天猫精灵成功连接后可使用语音进行控制，常用指令如下：

    “天猫精灵，打开插座”

    “天猫精灵，关闭插座”

    “天猫精灵，两分钟后关闭插座”

## 三元组

下面是我自己创建的一些产品申请的三元组，可以用来测试，不保证每个都能够着正常使用

|product ID|Product Secret|MAC地址|
|:----------:|:------------:|:-----:|
|空调|
|10586|d82cacf2993cfa46b42f6f25100c7655|f8a76385b9ea
|10586|efbe4f1cba3b01705fc2463f5bc5374d|f8a76385b9eb
|10586|1e7f37d99909b43835bf7b84ff2abfd3|f8a76385b9ec
|10586|af7f8f10f649f3f0b975f031420c583f|f8a76385b9ed
|10586|349fca807e7ba6b2485e03ea39249941|f8a76385b9ee
|风扇|
|11159|b58427faca6c0233be26294c2cdc8ed2|f8a76393a433
|11159|276f5393c517900c15df45fa8591ce11|f8a76393a434
|11159|1c0c2905805ba98e8c7c25a1cae9f092|f8a76393a435
|11159|5ae11e6b81593cf0848bbaffeabbdd91|f8a76393a436
|11159|1c02ec81e70a03928cf77c40df3d7169|f8a76393a437

## 指令使用示例

正确烧录固件与三元组后，复位模组，使用天猫精灵音箱找队友，与模组配对成功后，模组将通过串口输出：

    +STATE:1

配对成功后和通过天猫精灵控制模块，模块收到天猫精灵的控制指令后会通过串口将指令发出来，具体格式如下：

    +DATA:<OpCode>,<长度>,<参数>

数据示例如下：

- 关灯 ```+DATA:8202,4,00714100```

- 开灯```+DATA:8202,4,01724100```

- 将灯的亮度调为80 ```+DATA:824C,5,CCCC734100```

- 将灯的色温调整为 ```+DATA:825E,9,CCCCA0190000744100```

- 将灯的颜色调整为红色 ```+DATA:D100,9,C2230100800000FFFF```

- 将灯调整为阅读模式 ```+DATA:8242,5,0300750000```

- 将风扇调整为三挡 ```+DATA:D100,4,220A0103```

- 将风扇调整静音模式 ```+DATA:D100,5,4504F01100```

- 打开风扇的摇头功能 ```+DATA:D100,4,A3000501```

具体的数据值需要自己来解析！

用户手动操作了设备，可主动将当前设备状态上报给天猫精灵，具体数据格式如下：

    AT+SEND2ALI=<OpCode>,<参数>

指令示例如下：

- 关灯 ```AT+SEND2ALI=0482,010100```