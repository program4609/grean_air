#include "mainwindow.h"
#include <QApplication>
#include <synchapi.h>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // 信号量的意义，把操作共享内存的代码锁住。因为有可能同时点击2次APP, 防止并发
        QSystemSemaphore sema("grean_air Key", 1, QSystemSemaphore::Open);
        sema.acquire();

    #ifdef Q_OS_LINUX
        /* Windows平台上不存在应用程序崩溃后，共享内存段还存在的情况
         * LINUX应用程序崩溃后,共享内存段不会自动销毁,则该程序再次运行会出问题
         * 所以程序启动时先去检查是否有程序崩溃后还存留的共享内存段，如果有，先销毁,再创建
         */
        QSharedMemory mem("grean_air");
        // 尝试将进程附加到共享内存段
        if (mem.attach()) {
            // 将共享内存与主进程分离, 如果此进程是附加到共享存储器段的最后一个进程，则系统释放共享存储器段，即销毁内容
            mem.detach();
        }
    #endif

        /*
         * 每个App打开的时候，获取一次共享内存。
         * 如果获取失败，说明是第一个启动的APP，直接创建共享内存就好了。
         * 如果获取成功，说明不是第一个，直接退出就好了。
         * 保证App在系统里只能打开一个。
         */
        QSharedMemory unimem("grean_air");
        bool isRunning = false;
        if (unimem.attach()) {
            isRunning = true;
        } else {
            unimem.create(1);
            isRunning = false;
        }

        sema.release();

        if (isRunning) {
            qWarning() << QStringLiteral("已经有一个grean_air在运行，即将退出");
            QMessageBox box;
            box.setText("程序已经在运行中");
            box.exec();
            exit(0);
        }

           QPixmap pixmap(":/image/loading.gif");
              QMovie mv(":/image/loading.gif");
              QSplashScreen screen(pixmap);
              QLabel label(&screen);
              label.setMovie(&mv);
              mv.start();
              screen.show();
              int delayTime = 5;
              QElapsedTimer timer;
              timer.start();
              while(timer.elapsed() < (delayTime * 1000))
              {
                  a.processEvents();
              }
         screen.showMessage(QString("加载完成正在\n启动请稍后..."),NULL,Qt::green);
         MainWindow w;
         w.show();
         screen.finish(&w);
    return a.exec();
}
