#include "I2C_Thread.h"
#include <stdio.h>

#include <linux/types.h>

#include <stdlib.h>

#include <fcntl.h>

#include <unistd.h>

#include <sys/types.h>

#include <sys/ioctl.h>

#include <errno.h>

#include "delay.h"




#define I2C_RETRIES 0x0701

#define I2C_TIMEOUT 0x0702

#define I2C_RDWR 0x0707

//#define Q_QDOC true
#include <string.h>

struct i2c_msg {

    unsigned short addr;

    unsigned short flags;

    #define I2C_M_TEN 0x0010

    #define I2C_M_RD 0x0001

    unsigned short len;

    unsigned char *buf;

};



struct i2c_rdwr_ioctl_data{

    struct i2c_msg *msgs;

    int nmsgs;

};



struct i2c_rdwr_ioctl_data storage_data;

struct i2c_msg storage_msg[2];





int i2c_write(int fd, unsigned char slvAddr, unsigned short index, unsigned char * const data, unsigned char len )

{

        int ret;

        unsigned char *tmp = (unsigned char*) malloc(1024);



        if (tmp == NULL) {

            perror("memory allocate error(write)!!");

            return -1;

        }



        memcpy(tmp, (unsigned char *)&index, sizeof(unsigned short));

        memcpy((tmp + sizeof(unsigned short)), data, len);

        len += sizeof(unsigned short);



        /***write data to storage**/

        storage_data.nmsgs = 1;

        (storage_data.msgs[0]).len = len; // Data length

        (storage_data.msgs[0]).addr = slvAddr;//Device Addr

        (storage_data.msgs[0]).flags = 0; //write

        (storage_data.msgs[0]).buf = tmp;

        ret = ioctl(fd, I2C_RDWR, &storage_data);



        if (tmp)

          free(tmp);



        return (ret < 0) ? -1 : 0;

}



int i2c_read(int fd, unsigned char slvAddr, unsigned short index, unsigned char *data, int len)

{

        storage_data.nmsgs = 2;

        (storage_data.msgs[0]).len = sizeof(unsigned short);

        (storage_data.msgs[0]).addr = slvAddr;

        (storage_data.msgs[0]).flags = 0;  //Dummy write

        (storage_data.msgs[0]).buf = (unsigned char *)&index;



        (storage_data.msgs[1]).len = len;

        (storage_data.msgs[1]).addr = slvAddr;

        (storage_data.msgs[1]).flags = 1;

        (storage_data.msgs[1]).buf = data;



        if(ioctl(fd,I2C_RDWR, &storage_data) < 0){

            perror("ioctl error");

                return -1;

        }



        return 0;

}

void I2C_Thread::run()
{



    int fd = 0, ret = 0;
    int iTemp=0;
    int iRemoteTemp=0;
    char szTemp[4];
    float fTemp=0;
            storage_data.nmsgs = 2;

            storage_data.msgs = storage_msg;





            fd = open("/dev/i2c-0",O_RDWR);

            if(fd < 0){

                    perror("open I2C Dev error!!");

                    exit(1);

            }

            ioctl(fd, I2C_TIMEOUT, 1);/*set timeout value*/

            ioctl(fd, I2C_RETRIES, 2);/*set retry times*/
            unsigned char tmp_buffer[1];

            unsigned char tmp_buffer1[1];

            memset(tmp_buffer, 0x58, 1);

            memset(tmp_buffer1, 0x57, 1);

            i2c_read(fd,0x56,0x10,tmp_buffer,1);
            sprintf(szTemp,"%d",tmp_buffer[0]);
            iTemp = strtol(szTemp,NULL,10);
           // iTemp=iTemp-64;
            //printf("Data ==> %d\n", iTemp);
            //i2c_read(fd,0x56,0x0,tmp_buffer,1);
            //printf("Data ==> %x\n", tmp_buffer[0]);
            //i2c_read(fd,0x56,0x15,tmp_buffer,1);
            //printf("Data ==> %x\n", tmp_buffer[0]);

            i2c_read(fd,0x56,0x11,tmp_buffer,1);
            sprintf(szTemp,"%d",tmp_buffer[0]);
            iRemoteTemp = strtol(szTemp,NULL,10);
           // iRemoteTemp=iRemoteTemp-64;
            //printf("Data ==> %d\n", iTemp);
            i2c_read(fd,0x56,0x12,tmp_buffer,1);
            sprintf(szTemp,"%d",tmp_buffer[0]>>3);
            fTemp = strtol(szTemp,NULL,10);
           // fTemp=fTemp*0.0625+iRemoteTemp;
            //printf("Data ==> %0.4f\n", fTemp);
            //i2c_read(fd,0x56,0x1,tmp_buffer,1);
            //printf("Data ==> %x\n", tmp_buffer[0]);
            i2c_write(fd, 0x56, 0x37, 0x60, 1 );


    if (fd)
           close(fd);
    this->LocalTemp = QString("%1").arg(iTemp);
    this->RemoteTemp = QString("%1").arg(fTemp);


    //emit finished();
}

//int i2c_write(int fd, unsigned char slvAddr, unsigned short index, unsigned char * const data, unsigned char len )
//i2c_write(fd, 0x56, 0x20, 0x55, 1 );
//int i2c_read(int fd, unsigned char slvAddr, unsigned short index, unsigned char *data, int len)
//i2c_read(fd,0x56,0x20,tmp_buffer,1);
