# OpenPAYGO Token v2

This project is supported by the EnAccess Foundation (https://enaccess.org/)

Hardware implementation with generic C version + Arduino + schematics: https://github.com/EnAccess/OpenPAYGO-HW


## GETTING STARTED

1. Have a look at the general documentation: https://github.com/EnAccess/OpenPAYGO/blob/master/documentation/general_documentation.pdf

2. The source code of the example implementation into a device (including an example for begginers implemented on Arduino): https://github.com/EnAccess/OpenPAYGO-HW

3. The guide for the example, including a quick test to see if you have implemented the code properly into your system: https://github.com/EnAccess/OpenPAYGO/blob/master/documentation/example_implementation_documentation.pdf


## NOTE 
If you have pulled or downloaded this implementation before the official OpenPAYGO Token release on the 10th of October 2019, 
please make sure to update to the latest version before using in production. 


## CHANGELOG

2019-11-15: v2.1 release
- Added documentation about how to allow entry of slightly older tokens on device (unordered token entry)
- Added an example of unordered token entry (with test scenario) on the Python implementation
- Ensured compatibility of the Python code with Python v2.7+ (in addition to Python 3+ already supported).

**Note:** This version is fully retro-compatible with the v2.0, the tokens themselves do not change. Changes can be implemented on devices that wish to support unordered token entry but are not required. No change is required on servers. 

2019-10-10: v2.0 release
- Improved the test suite
- Added an extra example in the implementation documentation
- Bugfix in the example server implementation leading to count not always being updated correctly
- Bugfix in the update of count in the python device simulator

2019-09-27:
- Added signed independent security audit
- Added documentation as PDF

2019-09-06: v2.0 rc1
- Added extended token example implementation

2019-08-28: v2.0 beta
- Fully functional version with all v2.0 features

2019-07-19: v2.0 alpha
- First functional pre-release version

**Note:** The v1.0 version was only provided to a few partners for a limited beta test and to gather feedback useful to make the v2.0, it is not published here, is not compatible with the v2.0 and should not be used in production. 



# OpenPAYGO令牌v2

本项目由EnAccess基金会(https://enaccess.org/)支持。

硬件实现与通用C版本+ Arduino +原理图:https://github.com/EnAccess/OpenPAYGO-HW


##开始

1. 查看一下通用文档:https://github.com/EnAccess/OpenPAYGO/blob/master/documentation/general_documentation.pdf

2. 将示例实现为设备的源代码(包括在Arduino上实现的初学者示例):https://github.com/EnAccess/OpenPAYGO-HW

3.该示例的指南，包括一个快速测试，以查看您是否在系统中正确地实现了代码:https://github.com/EnAccess/OpenPAYGO/blob/master/documentation/example_implementation_documentation.pdf


# #注
如果您在2019年10月10日官方OpenPAYGO令牌发布之前拉取或下载了此实现，
在生产环境中使用之前，请确保更新到最新版本。


# #的更新日志

2019-11-15: v2.1版本
增加了关于如何允许稍微旧的令牌在设备上输入的文档(无序令牌输入)
-在Python实现上添加了一个无序令牌输入(带有测试场景)的示例
-确保Python代码与Python v2.7+的兼容性(除了已经支持的Python 3+)。

**注意:**这个版本是完全向后兼容的v2.0，令牌本身不会改变。可以在希望支持无序令牌输入但不是必需的设备上实现更改。服务器上不需要更改。

2019-10-10: v2.0版本发布
-改进测试套件
-在实现文档中增加了一个额外的例子
修复了示例服务器实现中导致计数不总是正确更新的错误
-修复了python设备模拟器中count更新中的错误

2019-09-27:
—增加签名独立安全审计
增加了PDF格式的文档

2017-09-06: v2.0 rc1
-增加了扩展令牌示例实现

2019-08-28: v2.0测试版
-功能齐全的版本与所有v2.0的特点

2019-07-19: v2.0 alpha
—第一个功能完备的预发布版本

**注:** 1.0版本仅提供给少数合作伙伴进行有限的beta测试，并收集有用的反馈以制作v2.0，它不在这里发布，与v2.0不兼容，不应在生产中使用。