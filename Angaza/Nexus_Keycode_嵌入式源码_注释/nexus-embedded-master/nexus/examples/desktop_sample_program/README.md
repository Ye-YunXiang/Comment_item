# Sample Program using the Nexus C Decoder

Sample program demonstrating the use of the Nexus embedded libraries.
See "Using in Your Project" in the project's README for more details.

This sample project relies on POSIX functionality that is commonly available
on desktop-class systems (e.g., file access and `malloc`). These facilities
are generally **not** available on embedded platforms; implementers should use
this project as a guide to help them build platform-appropriate solutions.

This project will build with the default GCC toolchain in Ubuntu 18.04, and
presumably any other recent Linux distribution.

**Note**: This example program relies on the default
`nexus/include/user_config.h` settings present when this repository was cloned
to your local machine. If there are any changes to `nexus_include/user_config.h`
(which occurs as a result of running `python conf_nexus.py`), please revert
those changes before continuing.

Build
```sh
$ make clean all
```

If you have the Clang Static Analyzer (`scan-build`), you can get additional
detailed analysis. You can easily get these dependencies on Ubuntu with the
command shown below.

Install Analysis Dependencies
```sh
make install-dependencies
```

Analyze
```sh
make all BUILD=sa
```

Run
```sh
$ ./sample_nexus_keycode_program
```

## To Reset Device State

When the sample program is started, you will be prompted to specify a file to
store nonvolatile data. If the same file is provided on successive launches,
device state, including PAYG credit timekeeping, keycodes, and Nexus Channel,
will be persisted.

To start "new", simply specify a new file or delete the old one.

## Suggested Demonstration Steps (Full Keycode Protocol)

- Build the project and run it
- Enter an arbitrary path to store nonvolatile data (e.g. `test.nv`)
- Enter a serial number: 12345678
- Enter a secret key: DEADBEEF1020304004030201FEEBDAED
- Select "Enter Keycode" from the demonstration selection menu
- See that there is no credit.
- Enter in this 1 day keycode: *10029054295608#
- See that the credit has increased to one day (86400 seconds)
- Try re-entering the same keycode and see that it is rejected.
- Enter in this 1 day keycode: *47700886956615#
- See that the credit has increased to two days (slightly less than 172800 seconds due to the passage of time).
- Close the program and wait for a few minutes.
- Re-run the program, providing the same NV file.
- Note that the credit is approximately the same as when it was closed.

## Suggested Demonstration Steps (Nexus Channel, Create Link to Accessory)

- Build the project and run it
- Enter an arbitrary path to store nonvolatile data (e.g. `test.nv`)
- Enter a serial number: 12345678
- Enter a secret key: DEADBEEF1020304004030201FEEBDAED
- Select "Display Nexus Channel Status" to see that there are no linked devices
- Enter in an 'Origin Command' keycode to link accessory with Nexus ID "0x0020003322": \*8192798211668986#
- See that the system begins to initiate a link
- Select option 3 ("Enter processing loop") to complete the link (will also simulate an accessory response)
- Select "Display Nexus Channel Status" to see that there is 1 active link
- Try re-entering the same keycode and see that it is rejected.
- Close the program.
- Re-run the program, providing the same NV file.
- See that the same origin command is rejected (cannot be reused)

## Suggested Demonstration Steps (Nexus Channel, Delete Link to Accessory)

- Perform steps in above "Create Link to Acccessory" list
- Select "Display Nexus Channel Status" to see that there is 1 active link
- Select "Enter Keycode" from the demonstration selection menu
- Enter in an 'Origin Command' keycode to "Unlink All" accessories from this specific controller: \*81000856304#
    - (Generated with controller 'command count' = 4)
- Observe that all links are deleted (previous link count of 1 goes to 0)
- Select "Display Nexus Channel Status" to see that there are no linked devices
- Try re-entering the same keycode and see that it is rejected.

## Suggested Demonstration Steps for Custom Resource

Nexus Channel provides an easy way to expose 'product-specific' resources
via the same application layer data link. The example program includes an
implementation of the official OCF "Battery" resource (found here:
https://www.oneiota.org/revisions/5666). This resource is an example of how
to host a 'resource' on one Nexus Channel device, and allow other devices to
"GET" the state of that resource (battery charge, capacity, etc), and "POST"
updates to the state of that resource if authorized (change low battery
threshold).

- Select option 4 ("Simulate GET to Battery Resource")
- Observe the raw bytes (a valid CoAP message) received representing this
GET
- Select option 3 ("Enter processing loop")
- Observe the GET response
- Select option 5 ("Update Battery Resource")
- Enter a new value (e.g. 10)
- Observe the raw bytes (valid CoAP message) received representing this POST
- Select option 3 ("Enter processing loop")
- See logs indicating new battery resource is updated
- GET the resource again, see the new threshold is in place (note the timestamp is also updated)



使用Nexus C解码器的示例程序

演示使用Nexus嵌入式库的示例程序。
请参阅项目README中的“在项目中使用”了解更多详细信息。

这个样例项目依赖于常用的POSIX功能
在桌面级系统上(例如，文件访问和' malloc ')。这些设施
一般** **不可用于嵌入式平台;实现者应该使用
这个项目可以作为一个指南，帮助他们构建适合平台的解决方案。

本项目将在Ubuntu 18.04中使用默认的GCC工具链构建
可能是其他最近的Linux发行版。

**注**:此示例程序依赖于默认值
' nexus/include/user_config.h '克隆此存储库时存在的设置
到您的本地机器。如果对“nexus_include/user_config.h”有任何更改
(这是运行' python conf_nexus.py '的结果)，请恢复
在继续之前进行这些更改。

构建
' ' ' sh
$ make clean all
```

如果您有Clang静态分析器(“扫描-构建”)，您可以获得额外的
详细的分析。你可以很容易地在Ubuntu上获得这些依赖
命令如下所示。

安装分析依赖项
' ' ' sh
使安装依赖软件
```

分析
' ' ' sh
make all BUILD=sa
```

运行
' ' ' sh
美元。/ sample_nexus_keycode_program
```

##重置设备状态

当示例程序启动时，系统将提示您指定一个文件
存储非易失性数据。如果在连续启动时提供相同的文件，
设备状态，包括PAYG信用计时、密钥码和Nexus信道;
将被坚持。

要开始“new”，只需指定一个新文件或删除旧文件。

建议的演示步骤(完整密钥协议)

-构建项目并运行它
—输入任意路径来存储非易失性数据(例如:“test.nv”)
—输入序列号:12345678
—输入密钥:DEADBEEF1020304004030201FEEBDAED
-在演示选择菜单中选择“Enter Keycode”
-注意不要赊账。
-输入这个1天的密钥代码:*10029054295608#
-积分增加到一天(86400秒)
-尝试重新输入相同的密钥码，并看到它被拒绝。
-输入这个1天的密钥代码:*47700886956615#
-看到积分增加到两天(由于时间的推移略少于172800秒)
—关闭程序，等待几分钟。
—重新运行程序，提供相同的NV文件。
-请注意，信用证与结账时大致相同。

建议演示步骤(Nexus Channel，创建配件链接)

-构建项目并运行它
—输入任意路径来存储非易失性数据(例如:“test.nv”)
—输入序列号:12345678
—输入密钥:DEADBEEF1020304004030201FEEBDAED
—选择“Display Nexus Channel Status”，查看没有链接设备
-输入“Origin Command”键码链接配件与Nexus ID“0x0020003322”:\*8192798211668986#
—系统开始发起链路
-选择选项3(“进入处理循环”)以完成链接(也将模拟附件响应)
-选择“显示Nexus通道状态”，看到有1个活动链路
-尝试重新输入相同的密钥码，并看到它被拒绝。
—关闭程序。
—重新运行程序，提供相同的NV文件。
-查看相同的起源命令被拒绝(不能被重用)

建议的演示步骤(Nexus通道，删除附件链接)

-执行上述“创建附件链接”列表中的步骤
-选择“显示Nexus通道状态”，看到有1个活动链路
-在演示选择菜单中选择“Enter Keycode”
-输入“起源命令”键码，从该特定控制器“断开所有”配件:\*81000856304#
-(控制器'command count' = 4生成)
—观察所有的链路都被删除了(之前的链路计数为1变为0)
—选择“Display Nexus Channel Status”，查看没有链接设备
-尝试重新输入相同的密钥码，并看到它被拒绝。

自定义资源的建议演示步骤

Nexus Channel提供了一种简单的方式来暴露“特定于产品”的资源
通过相同的应用层数据链路。示例程序包括
官方OCF“电池”资源的实施(在这里找到:
https://www.oneiota.org/revisions/5666)。这个资源就是一个例子
在一个Nexus Channel设备上托管一个“资源”，并允许其他设备
“GET”资源的状态(电池电量、容量等)，然后“POST”
如果授权，更新该资源的状态(更改低电量)
阈值)。

-选择选项4(“模拟获取电池资源”)
-观察接收到的表示这一点的原始字节(有效的CoAP消息)
得到
-选择选项3(“进入处理循环”)
—观察GET响应
-选择选项5(“更新电池资源”)
-输入新值(例如10)
-观察收到的代表此POST的原始字节(有效的CoAP消息)
-选择选项3(“进入处理循环”)
—查看电池资源更新日志
-再次获取资源，查看新的阈值是否到位(注意时间戳也已更新)