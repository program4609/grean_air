#include "help.h"
#include<QMessageBox>
#include<QSettings>
#include<QTextCodec>

help::help()
{

}
/**
  * @brief help::currenttimetostr获取当前时间并转化为字符串
  * @return
  */
 QString help::currenttimetostr()
 {
     QDateTime current_date_time =QDateTime::currentDateTime();
     QString current_date =current_date_time.toString("yyyy.MM.dd hh:mm:00");
     return current_date;
 }

 /**
   * @brief help::currenttimetostr获取当前时间并转化为字符串
   * @return
   */
  QString help::currenttimetostrinterface()
  {
      QDateTime current_date_time =QDateTime::currentDateTime();
      QString current_date =current_date_time.toString("yyyy-MM-dd hh:mm:ss");
      return current_date;
  }
 /**
   * @brief help::currenttimetostr获取当前分钟时间并转化为字符串
   * @return
   */
  QString help::minutetimetostr()
  {
      QDateTime current_date_time =QDateTime::currentDateTime();
      current_date_time=current_date_time.addSecs(-60);
      QString current_date =current_date_time.toString("yyyy.MM.dd hh:mm:00");
      return current_date;
  }
 /**
   * @brief help::currenttimetostr获取当前小时时间并转化为字符串
   * @return
   */
  QString help::hourtimetostr()
  {
      QDateTime current_date_time =QDateTime::currentDateTime();
      current_date_time=current_date_time.addSecs(-3600);
      QString current_date =current_date_time.toString("yyyy.MM.dd hh:mm:00");
      return current_date;
  }
 /**
  * @brief help::currenttimetostrid 获取时间用于ID
  * @return
  */
 QString help::currenttimetostrid()
 {
     QDateTime current_date_time =QDateTime::currentDateTime();
     QString current_date =current_date_time.toString("yyyyMMddhhmmsszzz");
     return current_date;
 }

 /**
  * @brief help::currenttimetostrid 获取时间用于ID精确到秒
  * @return
  */
 QString help::currenttimetostridnomm()
 {
     QDateTime current_date_time =QDateTime::currentDateTime();
     QString current_date =current_date_time.toString("yyyyMMddhhmmss");
     return current_date;
 }
 /**
   计算data的N次方
 * @brief help::getDataN
 * @param data
 * @param N
 * @return
 */
double help::getDataN(float data,int N)
     {
         int i=0;
         double result=1;
         for(i=0;i<N;i++)
         {
             result=result*data;
         }
         return result;
     }

QString help::getTimeToNumb(QString Timestr)
{
    QString tmp;
    for(int j = 0; j < Timestr.length(); j++)
    {
        if(Timestr[j] >= '0' && Timestr[j] <= '9')
            tmp.append(Timestr[j]);
    }
    return tmp;
}
/**显示对话框
 * @brief help::ShowMessageBox
 * @param titlestr
 * @return
 */
bool help::ShowMessageBox(QString titlestr)
{
    QMessageBox message_cd(QMessageBox::NoIcon,QString::fromUtf8("警告"),titlestr);

        message_cd.addButton(QString::fromUtf8("是"), QMessageBox::AcceptRole);
        message_cd.addButton(QString::fromUtf8("否"), QMessageBox::RejectRole);
       // message_cd.setStyleSheet("QPushButton {""background-color:#4d85db;"" border-style: outset;"" border-width: 2px;"" border-radius: 10px;" " border-color: beige;" " font: bold 15px;"" min-width: 8em;" " min-height: 2em;" "}" "QLabel { min-width: 10em;min-height:10em;font:15px;background-color:#4d85db;}");
       message_cd.setStyleSheet("QLabel {font:15px;color:#4d85db;}");
        if(message_cd.exec() == QMessageBox::AcceptRole)
            return true;
        else
            return false;

}
/**显示提示框
 * @brief help::ShowoneMessageBox
 * @param titlestr
 * @return
 */
bool help::ShowoneMessageBox(QString titlestr)
{
    QMessageBox msgBox(QMessageBox::NoIcon,QString::fromUtf8("提示"),titlestr);
    msgBox.setStyleSheet("QLabel {font:15px;color:#4d85db;}");
    msgBox.addButton(QString::fromUtf8("确定"), QMessageBox::AcceptRole);
    msgBox.exec();
}
//字符串分解，Buf表示被分解的字符串，index表示从c字符分割的第几个字符开始，c分割的字符
//startindex 开始查找的字符位所在小标，index表示第几个分隔符前，c表示分隔符,此函数需要先出去开头不满足条件的数据
QString help::GetDataFromBuf(char *Buf,int index,char c,int startindex)
{
    int i=0,start=0,end=0,bufnum=0;
    int num=strlen(Buf);
    char Data[200];//2018.6.26
    memset(Data,0,sizeof(char)*200);
    QString str;
    bool first=true;
    for(i=startindex;i<num;i++)
    {
        if(Buf[i]==c)
        {

            if(i+1<num&&Buf[i+1]!=c)
            {
                 bufnum++;
                 if(bufnum==index)
                 {
                      end=i-1;
                      break;
                 }
            }
        }
        else//꼇된黨
        {
            if(index-1==bufnum)
            {
              if(first==true)
              {
                 start=i;
                 first=false;
              }
            }
        }
    }

    /*  2018.5.17出现最后一个数据无分隔符的情况  */
     char datam[15]={0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39,0x2d,0x2b,0x2e};
     int m=0;
    if(start>0&&end==0)
    {
         for(int j=start;j<num;j++)
         {
             for( m=0;m<13;m++)
             {
                 if(Buf[j]==datam[m])
                 {
                     break;
                 }
             }
              if(m>=13)
              {
                end=j-1;
                 break;
              }
         }
    }

    /*   2018.7.30去掉start后面非数字部分  */
    for(i=start;i<end;i++)
    {
         for( m=0;m<13;m++)
             {
                 if(Buf[i]==datam[m])
                 {
                     break;
                 }
             }
         if(m>=13)
         {
           start=i+1;
         }
    }
    i=0;
    for(int j=start;j<=end&&i<200;j++)//2018.5.17把以前的i<100改为 i<200
    {
        if(Buf[j]!=c)
        {
             for( m=0;m<13;m++)
             {
                 if(Buf[j]==datam[m])
                 {
                     break;
                 }
             }
              if(m>=13)
              {
                 break;
              }
               Data[i++]=Buf[j];
        }
        else
            break;
    }
   str=Data;
   return str;
}

/**设置ini文件内容
 * @brief MainWindow::setiniData
 * @param filename
 * @param titlestr
 * @param data
 */
void help::setiniData(QString filename,QString titlestr,QString data)
{
    QSettings *configini=new QSettings(filename,QSettings::IniFormat) ;
    configini->setIniCodec(QTextCodec::codecForName("GB2312"));
    configini->setValue(titlestr,data);
    delete configini;
}
/**获取ini文件数据
 * @brief MainWindow::getiniData
 * @param filename
 * @param titlestr
 * @param data
 * @return
 */
QString help::getiniData(QString filename,QString titlestr)
{
    QSettings *configini=new QSettings(filename,QSettings::IniFormat);
    configini->setIniCodec(QTextCodec::codecForName("GB2312"));
    QString value=configini->value(titlestr).toString();
    delete configini;
    return value;
}
/** 判断字符串datastr是否是数字
 * @brief help::checknum
 * @param datastr
 * @return
 */
bool help::checknum(QString datastr)
{
    QString childstr="0123456789.-";
    int count=datastr.length();
    for(int i=0;i<count;i++)
    {
        if(childstr.indexOf(datastr.at(i))<0)
            return false;
    }
    return true;
}
