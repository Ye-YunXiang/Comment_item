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



ʹ��Nexus C��������ʾ������

��ʾʹ��NexusǶ��ʽ���ʾ������
�������ĿREADME�еġ�����Ŀ��ʹ�á��˽������ϸ��Ϣ��

���������Ŀ�����ڳ��õ�POSIX����
�����漶ϵͳ��(���磬�ļ����ʺ�' malloc ')����Щ��ʩ
һ��** **��������Ƕ��ʽƽ̨;ʵ����Ӧ��ʹ��
�����Ŀ������Ϊһ��ָ�ϣ��������ǹ����ʺ�ƽ̨�Ľ��������

����Ŀ����Ubuntu 18.04��ʹ��Ĭ�ϵ�GCC����������
���������������Linux���а档

**ע**:��ʾ������������Ĭ��ֵ
' nexus/include/user_config.h '��¡�˴洢��ʱ���ڵ�����
�����ı��ػ���������ԡ�nexus_include/user_config.h�����κθ���
(��������' python conf_nexus.py '�Ľ��)����ָ�
�ڼ���֮ǰ������Щ���ġ�

����
' ' ' sh
$ make clean all
```

�������Clang��̬������(��ɨ��-������)�������Ի�ö����
��ϸ�ķ���������Ժ����׵���Ubuntu�ϻ����Щ����
����������ʾ��

��װ����������
' ' ' sh
ʹ��װ�������
```

����
' ' ' sh
make all BUILD=sa
```

����
' ' ' sh
��Ԫ��/ sample_nexus_keycode_program
```

##�����豸״̬

��ʾ����������ʱ��ϵͳ����ʾ��ָ��һ���ļ�
�洢����ʧ�����ݡ��������������ʱ�ṩ��ͬ���ļ���
�豸״̬������PAYG���ü�ʱ����Կ���Nexus�ŵ�;
������֡�

Ҫ��ʼ��new����ֻ��ָ��һ�����ļ���ɾ�����ļ���

�������ʾ����(������ԿЭ��)

-������Ŀ��������
����������·�����洢����ʧ������(����:��test.nv��)
���������к�:12345678
��������Կ:DEADBEEF1020304004030201FEEBDAED
-����ʾѡ��˵���ѡ��Enter Keycode��
-ע�ⲻҪ���ˡ�
-�������1�����Կ����:*10029054295608#
-�������ӵ�һ��(86400��)
-��������������ͬ����Կ�룬�����������ܾ���
-�������1�����Կ����:*47700886956615#
-�����������ӵ�����(����ʱ�������������172800��)
���رճ��򣬵ȴ������ӡ�
���������г����ṩ��ͬ��NV�ļ���
-��ע�⣬����֤�����ʱ������ͬ��

������ʾ����(Nexus Channel�������������)

-������Ŀ��������
����������·�����洢����ʧ������(����:��test.nv��)
���������к�:12345678
��������Կ:DEADBEEF1020304004030201FEEBDAED
��ѡ��Display Nexus Channel Status�����鿴û�������豸
-���롰Origin Command���������������Nexus ID��0x0020003322��:\*8192798211668986#
��ϵͳ��ʼ������·
-ѡ��ѡ��3(�����봦��ѭ����)���������(Ҳ��ģ�⸽����Ӧ)
-ѡ����ʾNexusͨ��״̬����������1�����·
-��������������ͬ����Կ�룬�����������ܾ���
���رճ���
���������г����ṩ��ͬ��NV�ļ���
-�鿴��ͬ����Դ����ܾ�(���ܱ�����)

�������ʾ����(Nexusͨ����ɾ����������)

-ִ�������������������ӡ��б��еĲ���
-ѡ����ʾNexusͨ��״̬����������1�����·
-����ʾѡ��˵���ѡ��Enter Keycode��
-���롰��Դ������룬�Ӹ��ض����������Ͽ����С����:\*81000856304#
-(������'command count' = 4����)
���۲����е���·����ɾ����(֮ǰ����·����Ϊ1��Ϊ0)
��ѡ��Display Nexus Channel Status�����鿴û�������豸
-��������������ͬ����Կ�룬�����������ܾ���

�Զ�����Դ�Ľ�����ʾ����

Nexus Channel�ṩ��һ�ּ򵥵ķ�ʽ����¶���ض��ڲ�Ʒ������Դ
ͨ����ͬ��Ӧ�ò�������·��ʾ���������
�ٷ�OCF����ء���Դ��ʵʩ(�������ҵ�:
https://www.oneiota.org/revisions/5666)�������Դ����һ������
��һ��Nexus Channel�豸���й�һ������Դ���������������豸
��GET����Դ��״̬(��ص�����������)��Ȼ��POST��
�����Ȩ�����¸���Դ��״̬(���ĵ͵���)
��ֵ)��

-ѡ��ѡ��4(��ģ���ȡ�����Դ��)
-�۲���յ��ı�ʾ��һ���ԭʼ�ֽ�(��Ч��CoAP��Ϣ)
�õ�
-ѡ��ѡ��3(�����봦��ѭ����)
���۲�GET��Ӧ
-ѡ��ѡ��5(�����µ����Դ��)
-������ֵ(����10)
-�۲��յ��Ĵ����POST��ԭʼ�ֽ�(��Ч��CoAP��Ϣ)
-ѡ��ѡ��3(�����봦��ѭ����)
���鿴�����Դ������־
-�ٴλ�ȡ��Դ���鿴�µ���ֵ�Ƿ�λ(ע��ʱ���Ҳ�Ѹ���)