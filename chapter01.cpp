/*
创建线程
把每个线程分别不同的CPU核心

tip:这段代码放vscode里用g++编译有问题，放visual studio反而没问题。
*/

#include <iostream>
#include <thread>  


void func(int a)
{
    while (true)
    {
        std::cout<<"This is func!\n";
        std::this_thread::sleep_for(std::chrono::microseconds(50));  //这个线程休眠50ms
    }

}

int main()
{
    int a = 0;

    //新建线程，并开始执行。
    //传入 函数名 和 函数的参数
    std::thread newThread(func, a);
    
    //----------------主线程main函数在创建完子线程后不能没有任何代码-------------------------
    //方案一(推荐)：join, 等待子线程执行完毕再返回main函数的返回值。
    newThread.join();

    //方案二：detach，将主线程与子线程分离。分离之后会直接返回mian的返回值，不会等待子线程执行完毕。
    //使用detah的时候，要保证传入子线程中参数a的有效性
    //newThread.detach();

    return 0;
}

