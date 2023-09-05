# Nexus Embedded (Zephyr) Example

Sample program demonstrating Nexus Library on an
embedded target, using Zephyr RTOS.

There are various builds, demonstrating different functionalities of the
Nexus Library (Nexus Keycode, Nexus Channel, Nexus Channel Core).

## Target

STM32 Nucleo-F103RB development board (STM32F103RB target), using Zephyr RTOS
for ease of demonstration and modification. This board is more capable than
many target devices for Nexus Channel Core and allows for rapid prototyping,
debugging, and development of new Nexus Channel Core resource types prior to
moving to more constrained hardware.

This project relies on features of the Nucleo development board,
specifically the virtual COM port provided by the ST-Link on that board.
This port is used to transfer data between the development board and a
host computer running a serial terminal at **115200 Baud**, 8N1 UART.

On Linux, this *typically* shows up as a serial port at `/dev/ttyACM0` after
the Nucleo-F103RB is connected via USB.

## Setup Steps

1. [Install PlatformIO IDE in VSCode](https://platformio.org/install/ide?install=vscode)
2. Clone this Github repository
3. Open the PlatformIO IDE and select "Open Project"
4. Open the project by selecting the directory named "Channel_Core_PIO_Zephyr_Nucleo-F103RB"
5. Connect your Nucleo-F103RB board to a USB port on your computer
6. Open the PlatformIO perspective in the IDE and expand "Project Tasks". Select a build and then click "Clean"
7. Wait until the Clean is completed, and then click "Build"
8. Wait until the Build is completed, and then click "Upload and Monitor"
9. Wait until the Upload is complete and observe the Terminal in the IDE. It should prompt for input
10. Go to the steps specific to the demonstration build you are running (below)

## Build/Run

This example is configured as a [PlatformIO](https://platformio.org/install) project.
You can optionally download PlatformIO, download this example project, and
import it using the "Add Existing" functionality in PlatformIO. This will
allow you to modify, build, and download the code onto your own
Nucleo-F103RB development board.

A minimal console is configured in all examples so that when the F103RB board
is initially booted up, `---Nexus Channel Core Demonstration---` will be
printed to the terminal (on the virtual COM port connected to USART2).
This can be used to confirm that the board is powered and connected correctly.

Additionally, some demo builds allow for user input via this console, a prompt
indicating `demo> ` will allow text input via the USART2 console. This functionality
is implemented by the `demo_console` module.

Functions required to be implemented by the product in order for Nexus to work
properly are contained in the `src/nxp_reference_implementations` folder.

Operationally, the demonstration program is structured into two primary Zephyr threads:

1. `main` thread. This executes the `main` function in `main.c`, and is used
to initialize product and Nexus functionality, as well as handle user input
from the `demo_console`.

2. `process_nexus` thread. This thread calls `nx_common_process`, and will
be woken up and called whenever `nxp_common_request_processing` is called by
the Nexus library to request processing. Any CPU intensive operations
performed by Nexus are done in this thread (to avoid long-running operations
in interrupts).

A background `logging` thread is also compiled in by default, which can be
disabled by setting `CONFIG_LOG=n` in `zephyr/prj.conf`. If this is disabled,
much of the demonstration functionality via USART2 console may be nonfunctional.
However, disabling logging will reduce RAM and flash use.

The default Zephyr `idle` thread is also present, which takes care of putting
the CPU into a low-power state when there is no work to process.

Development boards other than the ST Nucleo-F103RB may be supported
(but are not tested or formally supported), and may be used by modifying the
appropriate section of the `platformio.ini` file and relevant overlay files
in the `zephyr` folder. Please contact Angaza for more information on porting
the Zephyr example to other boards/MCUs.

## Demo: "Nexus Keycode" Demo

('nucleo_f103rb-keycode-only' PlatformIO build)

This build demonstrates Nexus Keycode running on a development board, with
keycode input from the demo console on USART2. It demonstrates the following
implementation details:

* A nonvolatile storage abstraction to write/read data to flash NV (`flash_filesystem`)
* Implementation of Nexus PAYG ID/key provisioning and storage (`product_nexus_identity`)
* Implementation of product-side PAYG credit storage (`product_payg_state_manager`)
* Implementation of `nxp_keycode` and `nxp_common` product-side functions

### Suggested Demonstration Steps (Nexus Keycode)

The `demo_console` is already configured to expect user input beginning with
`*` as a Nexus Keycode. The keycodes below assume a demonstration keycode
secret key of `0xDE, 0xAD, 0xBE, 0xEF, 0x10, 0x20, 0x30, 0x40, 0x04, 0x03, 0x02, 0x01, 0xFE, 0xEB, 0xDA, 0xED`
(already configured in this example program).

* Type `*10029054295608#` ("Add Credit", 24 hours, ID=1), notice "New/applied" keycode feedback.
* Type `pc`, see remaining PAYG credit is 86400 seconds (24 hours).
* Type `*10029054295608#`, notice "Old/duplicate" keycode feedback.
* Type `*31145334081050#` ("Wipe IDs+Credit", ID=61), notice "New/applied" keycode feedback.
* Type `pc`, see remaining PAYG credit is 0 seconds.
* Enter `*10029054295608#`, again notice "New/applied" keycode feedback.
* Type `pc`, see remaining PAYG credit is 86400 seconds (24 hours).
* Type `*09544754240514#` ("Unlock", ID=15), see "New/applied" keycode feedback.
* Type `pc`, see remaining credit is 'unlocked'.
* Cycle power, type `pc`, confirm PAYG credit is still unlocked.

Notice especially the `product_payg_state_manager` module, which *receives and stores*
changes to credit from Nexus via `nxp_keycode` functions, and *reports* the
current credit back to Nexus via `nxp_common` functions.

`product_payg_state_manager` also periodically updates PAYG credit (every 60
seconds), and stores the result in nonvolatile storage every hour.

**Note**: This keycode demo build also is configured to use 'Rate Limiting'.
The default configuration below is used:

* User gains 1 keycode attempt every 720 seconds (12 minutes)
* Initially, user has 6 keycode attempts (persists across resets)

If a valid keycode is rejected with the message, "Keycode rate limiting is active!",
every 720 seconds another keycode entry attempt will be allowed (up to 128).

## Demo: "Single Link" Controller/Accessory

XXX update

## Demo: Channel Core (no Channel Security or Keycode)

This demo refers to the 'nucleo_f103-channel-core-only' build.

The USART2 demo console is used to visualize *application layer* communication
between two Nexus Channel Core devices, where the host computer acts as a
'client', reading or updating the state of Nexus Channel Core resources hosted
on the F103RB development board.

This demonstration does not use keycode or "Nexus Security/Link" functionality.

This demonstration configures the Nucleo-F103RB as a Nexus Channel
Core device hosting the following resources:

* [Battery resource] (https://angaza.github.io/nexus-channel-models/resource_types/core/101-battery/redoc_wrapper.html)

### Suggested Demonstration Steps (GET/POST to battery resource)

This example includes a fully-implemented battery resource compliant to the 
[resource model specification](https://angaza.github.io/nexus-channel-models/resource_types/core/101-battery/redoc_wrapper.html).

* "Upload and Monitor" the "nucleo_f103rb-channel-core-only" build.
* Wait until the Upload is complete and observe the Terminal in the IDE. It should prompt for input (`demo> `)
* Type `get`. This will retrieve the current state of the battery resource. Notice the 'th' (threshold) key has a value of 20 or 35.
* Type `post20`. This will update the battery 'low capacity' threshold to "20 percent".
* Type `get`. Notice the `th` property of the battery resource is "20".
* Type `post35`. This will update the battery 'low capacity' threshold to "35 percent".
* Type `get`. Notice the `th` property of the battery resource is "35".

The console should appear similar to below:

[!get_post_gif](sample_console_get_post.gif)

## Implementing a Custom Resource / Adding New Attributes

This example can also be used to quickly prototype new resource type
implementations. Simply modify the existing `src/battery_res.c` example code,
replacing it with the resource instance you wish to test.

For example, to add a new 'hours runtime' parameter to the battery resource:

* Pick a two-character attribute name, e.g. "hr", to be the attribute key.
* Add `hr` to the payload for GET responses in `battery_res_get_handler`
by adding the following line below `oc_rep_set_int(root, vb, battery_mv);`

```
// Always report '45 hours' of runtime. Can use a variable if desired.
oc_rep_set_int(root, hr, 45);
```

Recompile and run the demonstration again. In `GET` responses, you will notice
the new 'hr' parameter present. E.g.

```
[00:00:04.364,000] <inf> demo_console: [GET Response Handler] Received response with code 0 from Nexus ID [Authority ID 0xffff, Device ID 0x00bc614e]
[00:00:04.377,000] <inf> demo_console: [GET Response Handler] Parsing payload
[00:00:04.383,000] <inf> demo_console: [GET Response Handler] Key vb
[00:00:04.389,000] <inf> demo_console: 13100
[00:00:04.393,000] <inf> demo_console: [GET Response Handler] Key hr  <<-- newly added attribute key
[00:00:04.399,000] <inf> demo_console: 45  << -- newly added attribute value
[00:00:04.403,000] <inf> demo_console: [GET Response Handler] Key cp
[00:00:04.409,000] <inf> demo_console: 31
[00:00:04.413,000] <inf> demo_console: [GET Response Handler] Key th
[00:00:04.419,000] <inf> demo_console: 20
```

If creating a completely new/different resource, also modify
`battery_res_init` to indicate the correct "RTR" (resource type) and URI
you wish to use (instead of `/batt`) to refer to this resource. See
[Nexus Channel Core Resource Models](https://angaza.github.io/nexus-channel-models/)
for more information on resource model generation, or contact Angaza.


# Nexus嵌入式(Zephyr)示例

演示Nexus库的示例程序
嵌入式目标，使用西风RTOS。

的不同构建，演示了不同的功能
Nexus库(Nexus Keycode, Nexus Channel, Nexus Channel Core)。

# #目标

STM32 Nucleo-F103RB开发板(STM32F103RB目标)，采用Zephyr RTOS
为了便于演示和修改。这个董事会比
许多目标设备的Nexus通道核心，并允许快速原型，
调试，并开发新的Nexus通道核心资源类型之前
转向更受限制的硬件。

这个项目依赖于Nucleo开发板的特点，
特别是该板上ST-Link提供的虚拟COM端口。
该接口用于开发板和主板之间的数据传输
主机运行一个串行终端在**115200波特，8N1 UART。

在Linux上，这*通常*显示为' /dev/ttyACM0 '后面的串行端口
Nucleo-F103RB通过USB连接。

##设置步骤

1. [在VSCode中安装PlatformIO IDE](https://platformio.org/install/ide?install=vscode)
2. 克隆这个Github存储库
3.打开PlatformIO IDE，选择“Open Project”
4. 通过选择名为“Channel_Core_PIO_Zephyr_Nucleo-F103RB”的目录打开项目。
5. 将Nucleo-F103RB板连接到计算机上的USB端口
6. 在IDE中打开PlatformIO透视图并展开“Project Tasks”。选择一个构建，然后单击“清除”
7. 等待直到Clean完成，然后点击“Build”
8. 等待直到Build完成，然后单击“Upload and Monitor”。
9. 等到上传完成后，在IDE中观察终端。它应该提示输入
10. 转到您正在运行的演示构建特定的步骤(如下)

# #构建/运行

本例配置为[PlatformIO](https://platformio.org/install)项目。
您可以选择下载PlatformIO、下载这个示例项目和
使用PlatformIO中的“添加现有”功能导入它。这将
允许您修改、构建和下载您自己的代码
核子- f103rb开发板。

在所有示例中都配置了最小控制台，以便当F103RB板
，“——Nexus Channel Core Demonstration——”将是
打印到终端(连接USART2的虚拟COM端口上)。
这可以用来确认单板上电和连接正确。

此外，一些演示构建允许用户通过这个控制台(一个提示符)进行输入
指示“demo>”将允许通过USART2控制台输入文本。这个功能
由' demo_console '模块实现。

为使Nexus工作，产品需要实现的功能
正确地包含在' src/nxp_reference_implementations '文件夹中。

在操作上，演示程序被构造成两个主要的Zephyr线程:

1. 主要的线程。这将执行' main.c '中的' main '函数，并被使用
初始化产品和Nexus功能，以及处理用户输入
从' demo_console '。

2. process_nexus线程。这个线程调用' nx_common_process '，并将
调用' nxp_common_request_processing '时，将被唤醒并调用
请求处理的Nexus库。任何CPU密集型操作
由Nexus执行的操作都在这个线程中完成(以避免长时间运行的操作)
在中断)。

默认情况下，还会编译一个后台' logging '线程，它可以是
通过在' zephyr/prj.conf '中设置' CONFIG_LOG=n '来禁用。如果此选项被禁用，
通过USART2控制台的许多演示功能可能是无效的。
但是，禁用日志记录将减少RAM和闪存的使用。

默认的Zephyr ' idle '线程也存在，它负责放置
当没有工作要处理时，CPU进入低功耗状态。

可支持ST Nucleo-F103RB以外的开发板
(但没有经过测试或正式支持)，并且可以通过修改
' platformio.ini '文件的适当部分和相关的覆盖文件
在“zephyr”文件夹中。有关移植的更多信息，请联系Angaza
Zephyr示例到其他板/ mcu。

## Demo:“Nexus Keycode”Demo

('nucleo_f103rb-keycode-only' PlatformIO build)

这个构建演示了运行在开发板上的Nexus Keycode
从USART2上的演示控制台输入keycode。它演示了以下内容
实现细节:

一个非易失性存储抽象，用于写入/读取数据到flash NV (' flash_filesystem ')
*实现Nexus PAYG ID/key配置和存储(' product_nexus_identity ')
*实现产品端PAYG信用存储(' product_payg_state_manager ')
*实现' nxp_keycode '和' nxp_common '产品侧功能

建议的演示步骤(Nexus Keycode)

' demo_console '已经配置为期望以开头的用户输入
“*”作为Nexus密钥码。下面的键码假定为演示键码
“0xDE, 0xAD, 0xBE, 0xEF, 0x10, 0x20, 0x30, 0x40, 0x04, 0x03, 0x02, 0x01, 0xFE, 0xEB, 0xDA, 0xED”的秘钥
(已经在这个示例程序中进行了配置)。

*输入“*10029054295608#”(“添加学分”，24小时，ID=1)，通知“新建/应用”键码反馈。
*输入“pc”，看到剩余的现收现付信用是86400秒(24小时)。
*输入“*10029054295608#”，注意“旧/重复”键码反馈。
*输入“*31145334081050#”(“擦ID +信用”，ID=61)，注意“新建/应用”键码反馈。
*键入' pc '，看到剩余的PAYG信用为0秒。
*输入“*10029054295608#”，再次注意“新建/已应用”键码反馈。
*输入“pc”，看到剩余的现收现付信用是86400秒(24小时)。
*输入“*09544754240514#”(“解锁”，ID=15)，见“新增/应用”键码反馈。
*输入“pc”，看到剩余的信用是“解锁”。
*循环电源，输入“pc”，确认PAYG信用仍未锁定。

特别注意' product_payg_state_manager '模块，它*接收并存储*
通过' nxp_keycode '函数从Nexus更改信用，并*报告*
当前信用通过' nxp_common '函数返回到Nexus。

' product_payg_state_manager '也会定期更新PAYG信用(每60次)
秒)，并每小时将结果存储在非易失性存储器中。

**注**:此keycode演示构建也被配置为使用“速率限制”。
使用以下默认配置:

*用户每720秒(12分钟)获得1次keycode尝试
*最初，用户有6次键码尝试(持续重置)

如果有效的密钥码被拒绝，并显示“密钥码速率限制已激活!”
每720秒将允许另一次键码输入尝试(最多128次)。

演示:“单链接”控制器/配件

XXX更新

演示:Channel Core(无Channel Security或Keycode)

这个演示引用的是“仅核通道-核”构建。

USART2演示控制台用于可视化*应用层*通信
在两台Nexus通道核心设备之间，其中主机作为一个
'client'，读取或更新托管的Nexus Channel Core资源的状态
在F103RB开发板。

此演示不使用keycode或“Nexus安全/链接”功能。

本演示将Nucleo-F103RB配置为Nexus通道
核心设备托管以下资源:

*[电池资源](https://angaza.github.io/nexus-channel-models/resource_types/core/101-battery/redoc_wrapper.html)

实现自定义资源/添加新属性

这个例子也可以用来快速创建新资源类型的原型
实现。只需修改现有的' src/battery_res.c '示例代码，
将其替换为希望测试的资源实例。

例如，要向电池资源添加一个新的'hours runtime'参数:

*选择一个两个字符的属性名，例如:“hr”，作为属性键。
*在' battery_res_get_handler '中为GET响应添加' hr '
通过在下面添加以下行' oc_rep_set_int(root, vb, battery_mv); '

```
//总是报告'45小时'的运行时间。如果需要，可以使用变量。
Oc_rep_set_int (root, hr, 45);
```

重新编译并再次运行演示。在“GET”响应中，您将注意到
出现了新的“hr”参数。如。

```
[00:00:04.364,000] <inf> demo_console: [GET Response Handler]从Nexus ID[权限ID 0xffff，设备ID 0x00bc614e]收到代码为0的响应
[00:00:04.377,000] <inf> demo_console: [GET Response Handler]解析负载
[00:00:04.383,000] <inf> demo_console: [GET Response Handler] Key vb
[00:00:04.389,000] <inf> demo_console: 13100
[00:00:04.39] <inf> demo_console: [GET Response Handler] Key hr <<——新添加的属性键
[00:00:04.399,000] <inf> demo_console: 45 <<——新增的属性值
[00:00:04.403,000] <inf> demo_console: [GET Response Handler] Key cp
[00:00:04. 409000] <inf> demo_console: 31
[00:00:04.413,000] <inf> demo_console: [GET Response Handler]关键字
[00:00:04. 419000] <inf> demo_console: 20
```

如果创建一个全新的/不同的资源，也修改
' battery_res_init '指示正确的“RTR”(资源类型)和URI
您希望使用(而不是' /bat ')来引用此资源。看到
[Nexus渠道核心资源模型](https://angaza.github.io/nexus-channel-models/)
有关资源模型生成的更多信息，请联系Angaza。