# Comment_item
看各种开源项目记录。

## 两个小型的支付系统
- Open PAYGO。
- Angaza 的Nexus。

### Open PAYGO
> 本体就是一个解码库，用于嵌入小型的消费设备，进行输码付费，获得使用时间等操作。
> 它带有一个加密的库，在PC端通过加密库加密要要给的天数和此时输入的次数，在把码给嵌入PAYGO的设备。
密钥通过加密算法加密，然后发送给嵌入解码库的设备，能解析出两个值：
1. TokenCount    输入次数。
2. TokenValue    密钥带的值，范围为0~1000(这个值指的是可以用额度)。

通过 TokenCount 值，可以检测这个码是不是重复输入，Count是从0不断向上累计的，只要小于或等于内存中的Count值，都可算做重复码。
TokenValue 为获得的天数，可以在设备中根据时间在减少这个值，来实现时间计费的功能。

加密算法：通过官方给的 Python 加密算法进行加密，加密参数：充值天数、Count、StartingCode、SecretKey。

解码算法里面包含参数：
- InputToken    输入的密钥，用于解码。
- TokenCout     输入次数的地址，用于比对解码后的Count和赋值更新Count。
- StartingCode  起始码，也就是设备的ID。
- SecretKey     安全码，通过安全码和ID才可以对密钥进行解码。
  
#### 注释的代码
目前注释过的代码位置：OpenPAYGO\OpenPAYGO-HW-master\neutral_example_implentation

### Angaza
> 目前看的不多，它的库比较大，比较完整。

#### 主要位置
核心代码位置： nexus-embedded-master\nexus
使用时直接把核心代码nexus文件夹复制到项目内就行，可以根据需要裁切，一般是根据examples目录下的例程进行修改；修改完毕后删除掉不需要的例程。

例程介绍（examples目录下）：
> 只看下面两个例程，其他的不用管
- Nexus_Channel_Accessory_F103RB    从机例程。
- Nexus_Channel_Controller_F103RB   主机例程。

## 其他代码

### MQTT
> 这个项目主要是用来做服务端和MQTT项目配置工具的。
> 还是多看看MQTT中文手册。

### 其他的还没有碰。
