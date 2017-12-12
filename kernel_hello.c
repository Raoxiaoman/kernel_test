/**
 *  * @file    kernel_hello.c
 *   * @author  raohui
 *     * @version 0.1
 *      * @brief  入门的可加载内核模块“Hello World!”，当模块加载和移除的时候，会在/var/log/kern.log文件输出消息。
 *       * 该模块在加载的时候接受一个参数：名字，它将显示在内核日志文件中。
 *        * @see http://www.derekmolloy.ie/ 查看完整描述和补充描述。
 *        */

#include <linux/init.h>             // 用于标记函数的宏，如__init、__exit
#include <linux/module.h>           // 加载内核模块到内核使用的核心头文件
#include <linux/kernel.h>           // 包含内核使用的类型、宏和函数

MODULE_LICENSE("GPL");              ///< 许可类型，它会影响到运行时行为
MODULE_AUTHOR("raohui");      ///< 作者，当使用modinfo命令时可见
MODULE_DESCRIPTION("A simple Linux driver for the BBB.");  ///< 模块描述，参见modinfo命令
MODULE_VERSION("0.1");              ///< 模块版本

static char *name = "world";        ///< 可加载内核模块参数示例，这里默认值设置为“world”
module_param(name, charp, S_IRUGO); ///< 参数描述。charp表示字符指针（char ptr），S_IRUGO表示该参数只读，无法修改
MODULE_PARM_DESC(name, "The name to display in /var/log/kern.log");  ///< 参数描述

/** @brief 可加载内核模块初始化函数
 *  *  static关键字限制了该函数的可见范围为当前C文件。
 *   *  __init宏表示对于内置驱动（不是可加载内核模块），该函数只在初始化的时候执行，
 *    *  在此之后，该函数可以废弃，且内存可以被回收。
 *     *  @return 当执行成功返回0
 *      */
static int __init hello_raohui_init(void){
       printk(KERN_INFO "EBB: Hello %s from the BBB LKM!\n", name);
          return 0;

}

/** @brief 可加载内核模块清理函数
 *  *  和初始化函数类似，它是静态（static）的。__exit函数表示如果这个代码是给内置驱动（非可加载内核模块）使用，该方法是不需要的。 
 *   */
static void __exit hello_raohui_exit(void){
       printk(KERN_INFO "EBB: Goodbye %s from the BBB LKM!\n", name);

}

/** @brief 内核模块必须使用linux/init.h头文件提供的module_init()和module_exit()宏，
 *  *  它们标识了在模块插入时的初始化函数和移除时的清理函数（如上描述）
 *   */
module_init(hello_raohui_init);
module_exit(hello_raohui_exit);
