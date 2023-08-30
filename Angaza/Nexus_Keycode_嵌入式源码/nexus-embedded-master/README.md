# Nexus Firmware Libraries

This repository contains the embedded implementations of Nexus technology.
These platform-independent libraries are standard, portable C99 requiring
no dynamic memory allocation, suitable for use on highly constrained
embedded platforms.

> 本存储库包含Nexus计技术的嵌入式实现。这些与平台无关的库是标准的、可移植的C99，不需要动态内存分配。适合在高度受限的嵌入式平台上使用。

[![Build status](https://badge.buildkite.com/082d9802561b1880273c1cc570f98c39e00b79ea7dd99425d1.svg?branch=master)](https://buildkite.com/angaza/nexus-embedded-nexus-keycode)
[![Quality Gate Status](https://sonarcloud.io/api/project_badges/measure?project=angaza_nexus-keycode-embedded-internal&metric=alert_status&token=3c0218f9fde1d544fd2060ec1075c15fefeffd4f)](https://sonarcloud.io/dashboard?id=angaza_nexus-keycode-embedded-internal)
[![Coverage](https://sonarcloud.io/api/project_badges/measure?project=angaza_nexus-keycode-embedded-internal&metric=coverage&token=3c0218f9fde1d544fd2060ec1075c15fefeffd4f)](https://sonarcloud.io/dashboard?id=angaza_nexus-keycode-embedded-internal)

## Using in Your Project
> > 上面翻译
> 在项目中使用

1. Copy the `nexus` directory into your project
2. Add include paths for `nexus` and `nexus/include`
3. Run `cd nexus && python conf_nexus.py` and select configuration options (*Important*: Must run `python conf_nexus.py` from within the `nexus` folder).
4. Implement the functidons specified in `nexus/include/nxp_common.h`
5. [Keycode only] Implement the functions specified in `nexus/include/nxp_keycode.h`
6. [Channel only] Implement the functions specified in `nexus/include/nxp_channel.h`
7. Use the functions provided by `nexus/include/nx_keycode.h`, `nexus/include/nx_channel.h`, and `nexus/include/nx_common.h` to interact with Nexus

> > 上面翻译
> 1. 将 `nexus`目录复制到你的项目中。
> 2. 为 `nexus` 和 `nexus/include` 添加包路径。
> 3. 运行 `cd nexus & python conf_nexus.py` 并选择配置选项（*重要*： 必须从 `nexus` 文件夹运行 `python conf_nexus.py`）。
> 4. 实现 ’nexus/include/nxp_common.h` 中指定的功能。
> 5. [Keycode only]实现 `nexus/include/nxp_keycode.h` 中指定功能。
> 6. [Channel only]实现 `nexus/include/nxp_channel.h`  中指定功能。
> 7. 使用  `nexus/include/nx_keycode.h`, `nexus/include/nx_channel.h`, 和 `nexus/include/nx_common.h` 提供的功能与nexus进行交互。

The functions declared in `include/nxp_common.h` provide the Nexus
System with the ability to store and retrieve data from nonvolatile
storage (flash), as well as determine the current system uptime. These are
platform dependent, which is why they must be implemented by your code.
(This is a non-exhaustive list).

> > 上面翻译
> 在 `include/nxp_common.h` 中声明的函数为Nexus系统提供了从非易失性存储器（闪存）中存储和检索数据的能力，以及确定当前系统正常运行时间的能力。
> 这些都是平台相关的，这就是为什么它们必须由您的代码实现。（这是一个不详尽的代码。）

The functions declared in `include/nxp_keycode.h` are platform independent
and provide Nexus Keycode with a way to signal keycode feedback (rejected,
accepted, etc), methods to modify remaining PAYG credit based on keycode
receipt, and a way to retrieve the secret key (used for keycode validation)
from the implementing system. (This is a non-exhaustive list).

> > 上面翻译
> 在 `include/nxp_keycode.h` 中声明的函数是平台无关的并为Nexus Keycode提供一种方式来表示Keycode反馈(拒绝，已接受等)，基于keycode修改剩余PAYG信用的方法收据，以及检索密钥的方法(用于密钥验证)从实施系统来看。(这是一个不详尽的列表)。

The functions declared in `include/nxp_channel.h` are platform independent
and provide Nexus Channel with a way to signal channel events (link established,
link handshake begun, etc), send outbound Nexus Channel messages to the network
hardware (dependent on the implementing platform), and retrieve unique keying
information used to validate Nexus Channel link communications.
(This is a non-exhaustive list).

> > 上面翻译
> 在 `include/nxp_channel.h`中声明的函数是平台无关的并为Nexus Channel提供一种信号通道事件的方式(链接建立，链路握手开始等)，向网络发送出站Nexus Channel消息硬件(取决于实现平台)，并检索唯一密钥用于验证Nexus信道链路通信的信息。


Please add the following folders to your project include paths:
> 请将以下文件夹添加到项目包含路径中：

* `nexus`
* `nexus/src`
* `nexus/include`
* `nexus/utils`
* `nexus/oc` (Required only for Nexus Channel or Nexus debug logs  用于调试日志)

Other folders are used for automated testing or support, and are not required
to build a project using Nexus.

其他文件夹用于自动化测试或支持，并且不是必需的
使用Nexus构建一个项目。

## Project Structure        项目结构

The C implementation of Nexus uses the [ceedling](https://www.throwtheswitch.org/ceedling)
framework to organize automated testing of this source code.

All source code is contained under the `nexus` folder.

Note that files named `nxp` contain functions that *your code* must implement,
and files named `nx` expose functions and structures that the Nexus system
and modules provide.

Nexus的C实现使用[ceedling](https://www.throwtheswitch.org/ceedling)框架来组织该源代码的自动测试。所有源代码都包含在“nexus”文件夹下。请注意，名为' nxp '的文件包含*你的代码*必须实现的函数，和名为“nx”的文件揭示了Nexus系统的功能和结构模块提供。

**The only folders which must be copied to your own project when using the Nexus
Keycode protocol are `nexus/include`, `nexus/src`, and `nexus/utils`**.

**唯一的文件夹，必须复制到您自己的项目时，使用Nexus Keycode协议是' nexus/include '， ' nexus/src '和' nexus/utils ' **。

The folders in this project are:    这个项目中的文件夹是

* `nexus/include` - Header files that must be included in a project using the   必须包含在项目的头文件。
Nexus embedded solutions (do not modify)     Nexus嵌入式解决方案（请勿修改）。
* `nexus/src` - Nexus module implementation files (do not modify)       Nexus模块实现文件（请勿修改）。
* `nexus/oc` - IoTivity-based files for Nexus Channel (do not modify)   基于IoTivity的Nexus Channel文件（请勿修改）。
* `nexus/utils` - Nexus support utilities and functions (do not modify) 支持Nexus的程序和功能（请勿修改）。
* `nexus/stub` - Stub functions used during static analysis             静态分析期间使用的存根函数。
* `nexus/build` - temporary output artifacts related to unit tests and static  与单元测试和静态测试相关的临时输出构件
* `nexus/test` - Unit tests for the code contained in `src`        对' src '中包含的代码进行单元测试
* `nexus/examples` - Examples of the Nexus protocol in use       使用中的Nexus协议示例
* `buildkite` - Scripts for continuous integration tests (on Buildkite)      用于持续集成测试的脚本(在Buildkite上)
* `support` - Scripts related to code formatting and analysis   与代码格式化和分析相关的脚本

### Configuration Options   配置选项

To adjust configuration options (such as keycode protocol options), run
the configuration tool located at `nexus/conf_nexus.py`.

The tool can be run on any platform using Python 3, as below:

```
python conf_nexus.py
```

You may also need to install the package `python3-tk`.

This tool must be run from within the `nexus` directory to gain access to
the required `Kconfiglib` files.

This tool will launch an interactive configuration menu, where you may
modify the configuration of Nexus features to suit your application.
Afterwards, the tool automatically updates and saves your selections into
a header which is parsed by the Nexus code to determine what features to
expose to your application.

如果需要调整配置选项(如keycode协议选项)，执行命令配置工具位于' nexus/conf_nexus.py '。
该工具可以在任何使用Python 3的平台上运行，如下所示:

' ' '
python conf_nexus.py
' ' '

您可能还需要安装' python3-tk '包。
此工具必须从“nexus”目录中运行才能访问所需的“Kconfiglib”文件。
此工具将启动一个交互式配置菜单，您可以在其中修改Nexus功能的配置以适应您的应用程序。之后，该工具会自动更新并将您的选择保存到一个由Nexus代码解析的头文件，以确定哪些特性可以被调用向应用程序公开。

## Static analysis  静态分析

`ceedling release` will attempt to build a stub implementation of Nexus (
contained in `nexus/stub`) with Channel and Keycode featured enabled. This
build is used as a supplemental static analysis build (static analysis is also
performed against unit test builds).

'ceedling release'将尝试构建Nexus (包含在' nexus/stub '中)，Channel和Keycode功能启用。
这构建被用作补充的静态分析构建(静态分析也是)对单元测试构建执行)。

## Unit tests 单元测试
The unit tests themselves are found within the `nexus/test` folder. The
configuration of `ceedling` is contained within the `nexus/project.yml` file.

### Installing Tools for Unit Tests  安装用于单元测试的工具

First, install [Conda](https://docs.conda.io/en/latest/), which is used to
manage the packages for building and testing the `nexus-embedded` repository.

Conda ensures that these tools are installed and managed in an independent
environment that does not modify your host/system environment, and ensures
that `nexus-embedded` unit tests and static analysis can be run consistently
on almost any development system.

To install Conda on Linux:

1. `wget https://repo.anaconda.com/miniconda/Miniconda3-latest-Linux-x86_64.sh`
2. `bash Miniconda3-latest-Linux-x86_64.sh`
3. Respond 'yes' to defaults during the installation process
4. Close and reopen your terminal or shell after installing
5. Reload your terminal or shell, and run `conda --version` to confirm conda installed successfully.

Next, set up a Conda environment with nexus-embedded specific tools:

6. `conda env create -f support/condaenv.yml` (from same directory as this README)

Now, the prerequisite tools are installed into a conda environment named
`nexusemb`. You can enter this environment (and gain access to the tools
used by the `nexus-embedded` project by typing):

* `conda activate nexusemb`.

7. If the `support/condaenv.yml` file changes (for example, due to new tools
being added in the future) run `conda env update -f=support/condaenv.yml` to
pick up the new changes.

8. Finally, check that GCC is installed with `gcc --version`. To run unit
tests and static analysis (e.g. `ceedling clobber test:all`), GCC-10 is
required. Check that GCC-10 is installed with `gcc-10 --version`.

### Using Ceedling (Running Tests)  使用Ceeding（运行测试）

After installing the Conda package as described above,
type `conda activate nexusemb`. Now, from the `nexus` folder, type the
following commands:

* `ceedling clobber` - destroy all generated test files
* `ceedling test:all` - compile and execute all unit tests
* `ceedling gcov:all` - generate gcov test coverage reports

## Documentation  文档

To regenerate the code documentation locally, execute:      
要在本地重新生成代码文档，运行：

`doxygen ./Doxyfile`

from the repository root directory.  The documentation will be placed in a
从存储库根目录，文件将放在：
`docs` folder, open `html/index.html` to view it.
