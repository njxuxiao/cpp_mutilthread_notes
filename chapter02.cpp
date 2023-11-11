/*
互斥量mutex
原子变量atomic
*/

#include <iostream>
#include <thread>
#include <mutex>  //新导入的头文件
#include <atomic>



int gloablVal = 0;

//--------------------- sample 1 ----------------------
//std::mutex mtx;   //新建的互斥量
// void task1()
// {
//     for (int i = 0; i<100; i++)
//     {
//         mtx.lock();
//         gloablVal++;
//         gloablVal--;
//         mtx.unlock();
//     }
// }

//--------------------- sample 2 ----------------------
//死锁问题    在unlock之前，直接进行了return或者抛出异常
//解决方案    直接用 std::lock_guard<std::mutex>lock(mtx); 替代上锁和解锁
//std::mutex mtx;   //新建的互斥量
// void task1()
// {
//     for (int i = 0; i<100; i++)
//     {
           //std::lock_guard<std::mutex>lock(mtx);
//         mtx.lock();
//         gloablVal++;
//         gloablVal--;

//         //callFunc() -> throw
        
//         // if (a == b)
//         // {
//         //     return
//         // }

//         mtx.unlock();
//     }

// }

//--------------------- sample 3 ----------------------
//死锁问题  上锁顺序问题
//解决方案  (1)保证两个fun中上锁和解锁的顺序相同  (2)上锁代码替换为 std::lock(mtx1, mtx2);
//         (3)std::lock_guard<std::mutex> lock1(mtx1); std::lock_guard<std::mutex> lock2(mtx2);   不过这种方法api较少，用起来不够灵活
//         (4)std::unique_lock<std::mutex> lock1(mtx1);  std::unique_lock<std::mutex> lock2(mtx2);
// std::mutex mtx1;   //新建的互斥量
// std::mutex mtx2;   //新建的互斥量
// void task1()
// {
//     for (int i = 0; i<100; i++)
//     {
//         mtx1.lock();
//         mtx2.lock();
        
//         gloablVal++;
//         gloablVal--;

//         mtx1.unlock();
//         mtx2.unlock();
//     }

// }

// void task2()
// {
//     for (int i = 0; i<100; i++)
//     {
//         mtx2.lock();
//         mtx1.lock();
        
//         gloablVal++;
//         gloablVal--;

//         mtx2.unlock();
//         mtx1.unlock();
//     }

// }


//--------------------- sample 3 ----------------------
//直接用std::atomic<int> globalVal = 0; 那些上锁解锁的过程就可以全部省略

int main()
{
    std::thread t1(task1);
    std::thread t2(task1);

    t1.join();
    t2.join();

    std::cout<<"gloablVal = "<<gloablVal<<std::endl;
}